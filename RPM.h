/*
    Written By: Tyler Barnes 2024

    No warranty expressed or implied.
 */

#ifndef RPM_h
#define RPM_h

volatile uint8_t r_timeOut = 0;
volatile uint16_t r_reset = 0;

#include <cores/cores.h>

#define clkError 1.0005
#define hz2us 1000000 / (F_CPU * clkError / r_PRSCLR)
#define r_rpm(x) 60000000 / (hz2us * x)

class RPMclass{
public:
    void start() {
        r_ic();
    }  

    uint16_t get() {
        return (r_timeOut) ? 0 : r_rpm(r_capture);
    }
};

static RPMclass RPM;

#endif
