#if defined(__AVR_ATmega32U4__)
# include <cores/ATmega32U4.h>
#elif defined(__AVR_ATmega328P__)
# include <cores/ATmega328P.h>
#elif defined(__AVR_ATmega2560__)
# include <cores/ATmega2560.h>
#elif defined(__AVR_ATtiny402__)
# include <cores/ATtiny402.h>
#else
# error Your archetecture is not yet supported.
#endif
