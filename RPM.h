/*
    Written By: Tyler Barnes
    2024

    No warranty expressed or implied.
 */

#ifndef RPM_h
#define RPM_h

#define DYNAMIC -1
#define SEPARATE 0
#define AGGREGATE 1
#define r_spaces 3
#define maxBuffSize 5000000
#define halt() while(1){}

void incRPM();

#define construct_ISR(vect) \
    ISR(vect) {             \
        incRPM();           \
    }

#include <cores/cores.h>

uint8_t r_pindex[r_nPins] = {0};    // pin's index into the cpus array; r_nPins defined in cores.h
uint8_t r_mode = AGGREGATE; 
uint8_t r_sensors = 0;  
uint8_t r_pin[r_spaces] = {0};      // contains the pin number of active sensors
uint8_t r_state[r_spaces] = {0};    // pin state after digitalRead in interrupt
volatile uint32_t r_intMicros; 
volatile uint32_t r_lastTick; 
volatile uint32_t r_cpus0[r_spaces] = {0};
volatile uint32_t r_cpus1[r_spaces] = {0};
volatile uint32_t *r_cpus[2] = {r_cpus0, r_cpus1}; // index [][0] used for aggregate..

void incRPM() {                                                     
    r_intMicros = micros();                                             
    r_lastTick = micros();                                              
    if (r_mode == AGGREGATE) {                                          
        r_cpus[0][0]++;                                                 
        r_cpus[1][0]++;                                                 
    }else if (r_mode == SEPARATE) {                                     
        for (int i = 1; i <= r_sensors; i++) {                          
            uint8_t state = digitalRead(r_pin[i]);                     
            if (state != r_state[i]) {                              
                r_state[i] = state;                                  
                r_cpus[0][r_pindex[r_pin[i]]]++;                             
                r_cpus[1][r_pindex[r_pin[i]]]++;                             
            }                                                           
        }                                                               
    }                                                                   
}

class RPMclass {
private:
    int bufferMode = DYNAMIC; 
    uint8_t tooManySensors = 0;
    uint8_t trigger[r_spaces] = {0}; 
    uint8_t active[r_spaces] = {0};
    uint16_t RPM;
    uint32_t intMicros;
    uint32_t userBufferSize = 0; 
    uint32_t bufferSize[r_spaces] = {0};    
    uint32_t duration1[r_spaces] = {0}; 
    uint32_t duration2[r_spaces] = {0}; 
    uint32_t *duration[2] = {duration1, duration2};
    uint32_t delta1[r_spaces] = {0}; 
    uint32_t delta2[r_spaces] = {0}; 
    uint32_t *delta[2] = {delta1, delta2};

    void addPin(uint8_t _pin) {
        r_sensors++;    // skip index 0
        r_pin[r_sensors] = _pin;
        r_pindex[r_avrPin(_pin)] = r_sensors; 
    }

    void checkError() {
        if (tooManySensors) {
            char buff[10]; 
            sprintf(buff, "\nMaximum number of sensors is %d.\n", r_spaces - 1);
            Serial.end();
            Serial.begin(9600);
            Serial.print(buff);
            halt();  
        }; 
    }

public:
    void pin(uint8_t _pin) {
        if (r_sensors >= r_spaces - 1) {
            tooManySensors = 1;
            return;
        }
        addPin(_pin);
        pinMode(_pin, INPUT);
        r_enable(_pin);
    }

    uint16_t get(uint8_t _pin = 0) {
        checkError(); // doesn't work inside pin() method for some reason
        uint8_t PIN = (r_mode) ? 0 : r_pindex[r_avrPin(_pin)];
        intMicros = r_intMicros; 
        duration[active[PIN]][PIN] = (intMicros - delta[active[PIN]][PIN]);
        RPM = ceil((double)(r_cpus[active[PIN]][PIN] * 30000000.0) / (double)duration[active[PIN]][PIN]);
        
        // Change buffer size based on calculated RPM
        float bufferSamples; 
        if (bufferMode == DYNAMIC) {
            if (RPM > 20000) bufferSamples = 500; 
            else if (RPM > 10000) bufferSamples = 200; 
            else if (RPM > 5000) bufferSamples = 100; 
            else if (RPM > 500) bufferSamples = 50; 
            else bufferSamples = 10; 
            bufferSize[PIN] = 1.0 / ((double)RPM / (30000000.0 * bufferSamples));
            if (bufferSize[PIN] > maxBuffSize) bufferSize[PIN] = maxBuffSize; 
        } else {
            bufferSize[PIN] = userBufferSize; 
        }

        // Split buffering allows cpus values to reset without any issues. 
        if (duration[active[PIN]][PIN] > bufferSize[PIN] / 2 && trigger[PIN]) {
            delta[active[PIN]^1][PIN] = intMicros;
            r_cpus[active[PIN]^1][PIN] = 0; 
            trigger[PIN] = 0; 
        }
        if (duration[active[PIN]][PIN] > bufferSize[PIN]) {
            active[PIN] ^= 1; 
            trigger[PIN] = 1; 
        } 
        return (micros() - r_lastTick < 1500000) ? ceil(RPM / ((r_mode) ? r_sensors : 1)) : 0;
    }

    void buffer(int _size) {
        userBufferSize = (uint32_t)_size * 1000ul;
        bufferMode = _size;  
    }
    void mode(uint8_t _mode) {
        r_mode = _mode; 
    }

    void redefine(uint8_t _old, uint8_t _new) {
        r_disable(_old);
        r_pin[r_pindex[r_avrPin(_old)]] = _new; 
        r_pindex[r_avrPin(_new)] = r_pindex[r_avrPin(_old)]; 
        r_pindex[r_avrPin(_old)] = 0; 
        pinMode(_new, INPUT);
        r_enable(_new);
    }
};

static RPMclass RPM;

#endif
