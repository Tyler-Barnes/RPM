#if defined(__AVR_ATmega32U4__)
# include <cores/r_ATmega32U4.h>
#elif defined(__AVR_ATmega328P__)
# include <cores/r_ATmega328P.h>
#elif defined(__AVR_ATmega2560__)
# include <cores/r_ATmega2560.h>
#else
# error Your archetecture is not yet supported.
#endif