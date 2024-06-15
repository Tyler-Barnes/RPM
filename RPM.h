/*
    Written By: Tyler Barnes 2024

    No warranty expressed or implied.
 */

#ifndef RPM_h
#define RPM_h

volatile uint8_t r_timeOut = 0;
volatile uint16_t r_reset = 0;
double r_error = 1.0; 

#include <cores/cores.h>

#define hz2us 1000000 / (F_CPU / r_PRSCLR)
#define r_rpm(x) 60000000 / (hz2us * x)

class RPMclass{
public:
    void start() {
        r_ic();
    }  

    uint16_t get() {
        return (r_timeOut) ? 0 : r_rpm(r_capture) * r_error;
    }

    void error(double _error) {
        r_error = 1.0 + _error;
    }
};

static RPMclass RPM;

#endif
