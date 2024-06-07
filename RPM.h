/*
    Written By: Tyler Barnes 
    2024

    No warranty expressed or implied. 
*/

#ifndef RPM_h
#define RPM_h

static uint32_t
        r_cpms = 0,
        r_elapsed;
uint8_t r_pin;

#define incRPM()                    \
        if (!digitalRead(r_pin)) {  \
            r_cpms++;                \
        }                           \

#define construct_ISR(vect)         \
    ISR(vect) {                     \
        incRPM();                   \
    }

#if defined(__AVR_ATmega32U4__)
# include <cores/r_ATmega32U4.h>
#elif defined(__AVR_ATmega328P__)
# include <cores/r_ATmega328P.h>
#elif defined(__AVR_ATmega2560__)
# include <cores/r_ATmega2560.h>
#else
# error Your archetecture is not yet supported.
#endif

class RPMclass {
public:

    void pin(uint8_t _pin) {
        r_pin = _pin;
        pinMode(_pin, INPUT);
        r_setup(_pin); 
    }

    uint32_t get() {
    	uint32_t RPM = (r_cpms * 60000) / (millis() - r_elapsed);
        r_elapsed = millis();
        r_cpms = 0;
        return RPM;
    }
};

static RPMclass RPM;

#endif
