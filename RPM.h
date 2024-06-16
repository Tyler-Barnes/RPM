/*
    Written By: Tyler Barnes 2024

    No warranty expressed or implied.
 */

#ifndef RPM_h
#define RPM_h

void r_incTimeout(); // used on chips without overflow interrupt

class RPMclass{
private:
    float err = 1.0;
    void config();
    uint16_t getRPM();
public:
    void start() {
        config();
    }  

    uint16_t get() {
        return getRPM() * err;
    }

    void error(float _error) {
        err = 1.0 + _error;
    }
};

#include <cores/cores.h>

static RPMclass RPM;

#endif
