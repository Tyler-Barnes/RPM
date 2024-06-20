#if defined(__AVR_ATmega32U4__)
# include <cores/ATmega32U4.h>
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328A__) || defined(__AVR_ATmega328PB__) 
# include <cores/ATmega328P.h>
#elif defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega168A__ ) || defined(__AVR_ATmega168PB__)
# include <cores/ATmega168P.h>
#elif defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__ ) || defined(__AVR_ATmega88PB__)
# include <cores/ATmega168P.h>
#elif defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__ ) || defined(__AVR_ATmega48PB__)
# include <cores/ATmega168P.h>
#elif defined(__AVR_ATmega8__)
# include <cores/ATmega168P.h>
#elif defined(__AVR_ATmega2560__)
# include <cores/ATmega2560.h>
#elif defined(__AVR_ATmega4809__)
# include <cores/ATmega4809.h>
#elif defined(__AVR_ATtiny10__) || defined(__AVR_ATtiny9__) || defined(__AVR_ATtiny4__) || defined(__AVR_ATtiny5__)
# include <cores/ATtiny10.h>
#else
# error Your archetecture is not yet supported.
#endif
