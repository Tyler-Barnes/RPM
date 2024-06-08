/*
    Written By: Tyler Barnes
    2024

    No warranty expressed or implied.
 */

#ifndef RPM_h
#define RPM_h

volatile uint32_t r_cpms = 0;

#define incRPM() {r_cpms++;}

#define construct_ISR(vect)         \
    ISR(vect) {                     \
        incRPM();                   \
    }

#include <cores.h>


class RPMclass {
private:
    uint16_t bufferSize = 0;
    uint32_t elapsed = 0; 
public:
    void pin(uint8_t _pin) {
        pinMode(_pin, INPUT);
        r_setup(_pin);
    }

    uint32_t get() {
        uint32_t RPM = (r_cpms * 30000) / (millis() - elapsed);
        if (millis() - elapsed > bufferSize) {
            elapsed = millis();
            r_cpms = 0;
        }
        return RPM;
    }

    void buffer(uint16_t _size){
        bufferSize = _size; 
    }
};

static RPMclass RPM;

#endif
