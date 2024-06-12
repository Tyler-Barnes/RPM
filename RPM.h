/*
    Written By: Tyler Barnes
    2024

    No warranty expressed or implied.
 */

/*
r_pin[] holds the avr pin number of a defined sensor; r_pin[0] is reserved.
r_pindex[] is an array that holds the index into r_pin
r_sensors gets incremented when a new RPM.pin() is defined; it becomes the index value held in r_pindex
r_state[] holds the last measured pin state by digitalRead() within the interrupt
r_avrPin() takes in an avr pin number and returns the index into r_pindex
*/

#ifndef RPM_h
#define RPM_h

#define DYNAMIC -1
#define SAMPLES -2
#define SEPARATE 0
#define AGGREGATE 1
#define r_arrSize 3     // {aggregate, separate1, separate2}
#define maxBuffSize 1000000
#define halt() while(1){}

void incRPM();

#define construct_ISR(vect) \
    ISR(vect) {             \
        incRPM();           \
    }

#include <cores/cores.h>

uint8_t r_pindex[r_nPins] = {0};                    // pin's index into the ticks array; r_nPins defined in cores.h
uint8_t r_mode = AGGREGATE; 
uint8_t r_sensors = 0;  
uint8_t r_pin[r_arrSize] = {0};                     // contains the pin number of active sensors
uint8_t r_state[r_arrSize] = {0};                   // pin state after digitalRead in interrupt
volatile uint32_t r_intMicros; 
volatile uint32_t r_lastTick; 
volatile uint16_t r_ticks0[r_arrSize] = {0};
volatile uint16_t r_ticks1[r_arrSize] = {0};
volatile uint16_t *r_ticks[2] = {r_ticks0, r_ticks1};  // r_ticks[x][0] used for aggregate..

void incRPM() {                                                     
    r_intMicros = micros();    // psuedo input capture                                          
    r_lastTick = micros();     // micros() doesn't update within interrupt                                        
    if (r_mode == AGGREGATE) {                                          
        r_ticks[0][0]++;                                                 
        r_ticks[1][0]++;                                                 
    } else if (r_mode == SEPARATE) {                                     
        for (int i = 1; i <= r_sensors; i++) {                          
            uint8_t state = digitalRead(r_pin[i]);                     
            if (state != r_state[i]) {                              
                r_state[i] = state;                                  
                r_ticks[0][r_pindex[r_pin[i]]]++;                             
                r_ticks[1][r_pindex[r_pin[i]]]++;                             
            }                                                           
        }                                                               
    }                                                                   
}

#define r_pindex(x) r_pindex[r_avrPin(x)]
#define r_pin(x) r_pin[r_pindex[r_avrPin(x)]]
#define r_duration duration[active[PIN]][PIN]
#define r_activeDelta delta[active[PIN]][PIN]
#define r_inactiveDelta delta[active[PIN]^1][PIN]
#define r_activeTicks r_ticks[active[PIN]][PIN]
#define r_inactiveTicks r_ticks[active[PIN]^1][PIN]

class RPMclass {
public:
    int bufferMode = DYNAMIC; 
    uint8_t PIN;
    uint8_t tooManySensors = 0;
    uint8_t trigger[r_arrSize] = {0}; 
    uint8_t active[r_arrSize] = {0};
    uint16_t RPM;
    uint16_t lastRPM;
    uint16_t timeOut = 0;
    uint32_t intMicros;
    uint32_t userBufferSize = 0; 
    uint32_t bufferSize[r_arrSize] = {0};    
    uint32_t duration1[r_arrSize] = {0}; 
    uint32_t duration2[r_arrSize] = {0}; 
    uint32_t *duration[2] = {duration1, duration2};
    uint32_t delta1[r_arrSize] = {0}; 
    uint32_t delta2[r_arrSize] = {0}; 
    uint32_t *delta[2] = {delta1, delta2};
    float bufferSamples; 


    void addPin(uint8_t _pin) {
        r_sensors++;                // skip index 0
        r_pin[r_sensors] = _pin;    
        r_pindex(_pin) = r_sensors; 
    }

    void checkError() {
        if (tooManySensors) {
            char buff[10]; 
            sprintf(buff, "\nMaximum number of sensors is %d.\n", r_arrSize - 1);
            Serial.end();
            Serial.begin(9600);
            Serial.print(buff);
            halt();  
        }; 
    }

    void calcRPM() {
        intMicros = r_intMicros; // r_intMicros can get changed by interrupt before calculation is made
        r_duration = (intMicros - r_activeDelta);
        RPM = (r_activeTicks * 30000000.0) / r_duration;
    }

    void incTimeout() {
        if (RPM == lastRPM) {
            timeOut++;
        } else {
            timeOut = 0; 
        }
        lastRPM = RPM; 
    }

    void calcBuffer() {
        if (bufferMode == DYNAMIC) {
            if (RPM > 5000) bufferSamples = 50; 
            else if (RPM > 500) bufferSamples = 25; 
            else bufferSamples = 10; 
            bufferSize[PIN] = 1.0 / (RPM / (30000000.0 * bufferSamples));
            if (bufferSize[PIN] > maxBuffSize) bufferSize[PIN] = maxBuffSize; 
        } else if (bufferMode == SAMPLES) {
            bufferSize[PIN] = 1.0 / (RPM / (30000000.0 * bufferSamples));
        } else {
            bufferSize[PIN] = userBufferSize; 
        }
    }

    void splitBuffer() {
        // if duration has past half the buffer size, reset the background buffer
        if (r_duration > bufferSize[PIN] / 2 && trigger[PIN]) {
            r_inactiveDelta = intMicros;
            r_inactiveTicks = 0; 
            trigger[PIN] = 0; 
        }
        // if the duration has past the bufferSize, set current buffer to background, and set background buffer to active
        if (r_duration > bufferSize[PIN]) {
            active[PIN] ^= 1; 
            trigger[PIN] = 1; 
        } 
    }
public:
    void pin(uint8_t _pin) {
        if (r_sensors >= r_arrSize - 1) {
            tooManySensors = 1;
            return;
        }
        addPin(_pin);
        pinMode(_pin, INPUT);
        r_enable(_pin);
    }

    uint16_t get(uint8_t _pin = 0) {
        checkError(); // doesn't work inside pin() method for some reason
        PIN = (r_mode) ? 0 : r_pindex(_pin);
        // Calculate RPM
        calcRPM(); 
        // Change buffer size based on calculated RPM
        calcBuffer();
        // Split buffering allows ticks values to reset without any issues. 
        splitBuffer();
        // micros() only called within interrupt, so timeout is required for 0
        return (micros() - r_lastTick < bufferSize[PIN]) ? RPM / ((r_mode) ? r_sensors : 1) : 0;
    }
    void buffer(int _size) {
        userBufferSize = _size * 1000ul;
        bufferMode = _size;  
    }
    void mode(uint8_t _mode) {
        r_mode = _mode; 
    }

    void redefine(uint8_t _old, uint8_t _new) {
        r_disable(_old);
        r_pin(_old) = _new; 
        r_pindex(_new) = r_pindex(_old); 
        r_pindex(_old)  = 0; 
        pinMode(_new, INPUT);
        r_enable(_new);
    }

    void samples(uint8_t _samples) {
        bufferMode = SAMPLES; 
        bufferSamples = _samples; 
    }
};

static RPMclass RPM;

#endif
