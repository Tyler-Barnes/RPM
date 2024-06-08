/*
    Written By: Tyler Barnes
    2024

    No warranty expressed or implied.
 */

#ifndef RPM_h
#define RPM_h

// volatile uint32_t r_cpms = 0;
volatile uint32_t r_cpms1 = 0;
volatile uint32_t r_cpms2 = 0;
volatile uint32_t *r_cpms[2] = {&r_cpms1, &r_cpms2};
#define DYNAMIC -1

#define incRPM() {r_cpms1++;r_cpms2++;}

#define construct_ISR(vect)         \
    ISR(vect) {                     \
        incRPM();                   \
    }

#include <cores/cores.h>



class RPMclass {
private:
	int bufferMode = DYNAMIC; 
    int bufferSize = 0;
    uint8_t trigger = 1; 
    uint32_t delta1 = 0; 
    uint32_t delta2 = 0; 
    uint32_t *delta [2] = {&delta1, &delta2}; 
    uint16_t duration1, duration2; 
	uint16_t *duration[2] = {&duration1, &duration2};
	uint8_t active = 0;
public:
    void pin(uint8_t _pin) {
        pinMode(_pin, INPUT);
        r_setup(_pin);
    }

    uint32_t get() {
    	*duration[active] = (millis() - *delta[active]);
        uint32_t RPM = (*r_cpms[active] * 30000) / *duration[active];

        if (bufferMode == DYNAMIC) {
	        if (RPM > 10000) bufferSize = 0; 
	        else if (RPM > 5000) bufferSize = 500;
	        else if (RPM > 1000) bufferSize = 1000;
	        else if (RPM > 500) bufferSize = 2000;
	        else bufferSize = 3000;
	    }
        if (*duration[active] > bufferSize / 2 && trigger) {
        	*delta[active^1] = millis();
        	*r_cpms[active^1] = 0; 
        	trigger = 0; 
        }
        if (*duration[active] > bufferSize) {
            active ^= 1; 
            trigger = 1; 
        }
        return RPM;
    }

    void buffer(int _size){
        bufferSize = _size; 
        bufferMode = _size; 
    }
};

static RPMclass RPM;

#endif
