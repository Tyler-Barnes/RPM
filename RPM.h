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
#define hz2us (1.0 / (F_CPU * clkError / r_PRSCLR)) * 1000000
#define cpus(x) 1.0 / (hz2us * x)

class RPMclass{
public:
    void start() {
        r_ic();
    }  

    uint16_t get() {
        return (r_timeOut) ? 0 : cpus(r_capture) * 60000000;
    }
};

static RPMclass RPM;

#endif
