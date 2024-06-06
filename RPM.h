/*
	Written By: Tyler Barnes 
	2024

	No warranty expressed or implied. 
*/


#ifndef RPM_h
#define RPM_h

uint32_t
        r_rpm,
        r_elapsed;
uint8_t r_pin;


#define incRPM() 					\
		if (!digitalRead(r_pin)) {	\
			r_rpm++;				\
		}							\

// Convert pin number to register config
#define construct_ISR(vect)			\
	ISR(vect) {						\
		incRPM();					\
	}

#if defined(__AVR_ATmega32U4__)
# include <cores/r_ATmega32U4.h>
#elif defined(__AVR_ATmega328P__)
# include <cores/r_ATmega328P.h>
#else
# error Your archetecture is not yet supported.
#endif

class RPMclass {
public:

	void pin(uint8_t _pin) {
		r_pin = _pin;
		r_setup(_pin); 
	}

	uint32_t get() {
		uint32_t cpms = r_rpm / (millis() - r_elapsed);
		r_elapsed = millis();
		r_rpm = 0;
		return cpms / 60000;
	}
};

static RPMclass RPM;

#endif
