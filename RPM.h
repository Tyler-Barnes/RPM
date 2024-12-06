/*
    Written By: Tyler Barnes 2024

    No warranty expressed or implied.
 */

#ifndef RPM_h
#define RPM_h

void r_incTimeout(); // used on chips without overflow interrupt

enum PULLUP{
    EXTERNAL_PULLUP, 
    INTERNAL_PULLUP
};

class RPMclass{
private:
    float err = 1.0;
    void config(uint8_t _pullup);
    double getRPM();
public:
    void start(uint8_t _pullup = INTERNAL_PULLUP) {
        config(_pullup);
    }  

    uint16_t get() {
        return (getRPM() * this->err) + 0.5;
    }

    void error(float _error) {
        this->err = 1.0 + _error;
    }
};

#include <cores/cores.h>

static RPMclass RPM;

#endif
