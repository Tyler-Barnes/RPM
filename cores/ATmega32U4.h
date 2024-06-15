#define r_PRSCLR 64
#define hz2us 1000000 / (F_CPU / r_PRSCLR)
#define r_rpm(x) 60000000 / (hz2us * x)

volatile uint8_t r_timeOut = 0;
volatile uint16_t r_reset = 0;

ISR(TIMER1_CAPT_vect) {
    TCNT1 = 0;      // reset timer
    if (++r_reset > r_timeOut) {
        r_timeOut = 0; 
        r_reset = 0; 
    }
}

ISR(TIMER1_OVF_vect) {
    if (++r_timeOut > 5) {
        r_timeOut = 3; 
        r_reset = 0;
    } 
}

uint16_t RPMclass::getRPM() {
    return (r_timeOut) ? 0 : r_rpm(ICR1) * RPMclass::err;
}

void RPMclass::config() {
    CLKPR = 0x80;           // no CPU prscaler
    TIMSK1 = 0x21;          // enable input capture interrupt; enable overflow interrupt
    TCCR1A = 0x00;          // clear any previous configuration
    TCCR1B = 0x03;          // set prescaler
    DDRD &= ~(_BV(PD4));    // pinMode(4, INPUT);
}

