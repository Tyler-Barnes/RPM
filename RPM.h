/*
    Written By: Tyler Barnes 
    2024

    No warranty expressed or implied. 
*/

#ifndef RPM_h
#define RPM_h

volatile uint32_t r_cpms = 0;
uint32_t r_elapsed; 
uint8_t r_pin;

#define incRPM() {r_cpms++;}

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
	uint8_t numOfSamples = 1; 

private:
	uint32_t arr_samples[100];
	uint8_t index = 0; 
	void addSample(uint32_t _sample) {
		arr_samples[index] = _sample; 
		if (++index > numOfSamples) index = 0; 
	}
	uint32_t avgSample(){
		uint32_t sum = 0; 
		for (int i = 0; i < numOfSamples; i++) {
			sum += arr_samples[i];
		}
		return sum / numOfSamples; 
	}
public:
	void samples(uint8_t _val){
		numOfSamples = _val; 
	}

    void pin(uint8_t _pin) {
        r_pin = _pin;
        pinMode(_pin, INPUT);
        r_setup(_pin); 
    }

    uint32_t get() {
    	uint32_t RPM = (r_cpms * 30000) / (millis() - r_elapsed);
    	addSample(RPM); 
        r_elapsed = millis();
        r_cpms = 0;
        return avgSample();
    }
};

static RPMclass RPM;

#endif
