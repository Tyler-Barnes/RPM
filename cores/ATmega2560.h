
#define r_capture ICR4

uint16_t r_PRSCLR = 64; 

ISR(TIMER4_CAPT_vect) {
    TCNT4 = 0;      // reset timer
    if (++r_reset > r_timeOut) {
        r_timeOut = 0; 
        r_reset = 0; 
    }
}

ISR(TIMER4_OVF_vect) {
    if (++r_timeOut > 5) {
        r_timeOut = 3; 
        r_reset = 0;
    } 
}

void r_ic() {
    CLKPR = 0x80;           // no CPU prscaler
    TIMSK4 = 0x21;          // enable input capture interrupt; enable overflow interrupt
    TCCR4A = 0x00;          // clear any previous configuration
    TCCR4B = 0x03;          // set prescaler
    DDRL &= ~(_BV(PL1));    // pinMode(48, INPUT);
}
