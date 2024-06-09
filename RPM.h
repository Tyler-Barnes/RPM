/*
    Written By: Tyler Barnes
    2024

    No warranty expressed or implied.
 */

#ifndef RPM_h
#define RPM_h

uint8_t r_nSensors = 0;  
volatile uint32_t r_intMicros; 
volatile uint32_t r_lastTick; 
volatile uint32_t r_cpms1 = 0;
volatile uint32_t r_cpms2 = 0;
volatile uint32_t *r_cpms[2] = {&r_cpms1, &r_cpms2};
#define DYNAMIC -1

#define incRPM() {          \
    r_intMicros = micros(); \
    r_cpms1++; r_cpms2++;   \
    r_lastTick = micros();  \
}

#define construct_ISR(vect)         \
    ISR(vect) {                     \
        incRPM();                   \
    }

#include <cores/cores.h>

class RPMclass {
public:
    int bufferMode = DYNAMIC; 
    int sampleMode = DYNAMIC;   
    uint8_t nSamples;
    uint8_t index = 0;
    uint8_t trigger = 1; 
    uint8_t active = 0;
    uint16_t aSamples[100] = {0};
    uint32_t bufferSize = 0;    
    uint32_t delta1 = 0; 
    uint32_t delta2 = 0; 
    uint32_t *aDelta [2] = {&delta1, &delta2}; 
    uint32_t duration1, duration2; 
    uint32_t *duration[2] = {&duration1, &duration2};
    uint32_t RPM;
    uint32_t intMicros;

    void addSample(uint16_t _sample) {
        if (++index > nSamples) index = 0;
        aSamples[index] = _sample;
    }

    double avgSamples() {
        uint32_t sum = 0;
        for (int i = 0; i < nSamples; i++) {
            sum += aSamples[i]; 
        }
        return (double)sum / (double)nSamples; 
    }

    void fillArr(uint32_t _rpm) {
        for (int i = 0; i < nSamples; i++) {
            aSamples[i] = _rpm; 
        }
    }

public:
    void pin(uint8_t _pin) {
        r_nSensors++; 
        pinMode(_pin, INPUT);
        r_setup(_pin);
    }

    uint32_t get() {
        intMicros = r_intMicros; 
        *duration[active] = (intMicros - *aDelta[active]);
        RPM = ceil((double)(*r_cpms[active] * 30000000.0) / (double)*duration[active]);
        if (avgSamples() == 0) {
            fillArr(RPM); 
        } else {
            addSample(RPM); 
        }

        if (bufferMode == DYNAMIC) {
            if (RPM > 10000) bufferSize = 250; 
            else if (RPM > 1000) bufferSize = 500;
            else if (RPM > 500) bufferSize = 1000;
            else if (RPM > 100) bufferSize = 5000;
            else bufferSize = 10000;
            bufferSize *= 1000; 
        }

        if (sampleMode == DYNAMIC) {
            if (RPM > 5000) nSamples = 3;
            else if (RPM > 250) nSamples = 5;
            else nSamples = 8;
        }

        if (*duration[active] > bufferSize / 2 && trigger) {
            *aDelta[active^1] = intMicros;
            *r_cpms[active^1] = 0; 
            trigger = 0; 
        }
        if (*duration[active] > bufferSize) {
            active ^= 1; 
            trigger = 1; 
        } 
        return (micros() - r_lastTick < 1500000) ? ceil(avgSamples() / r_nSensors) : 0;
    }

    void samples(int _samples) {
        nSamples = _samples;
        sampleMode = _samples;  
    }

    void buffer(int _size) {
        bufferSize = (uint32_t)_size * 1000ul;
        bufferMode = _size;  
    }
};

static RPMclass RPM;

#endif
