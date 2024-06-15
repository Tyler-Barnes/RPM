
#define r_capture ICP1

uint16_t r_PRSCLR = 64; 

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

void r_ic() {
    CLKPR = 0x80;           // no CPU prscaler
    TIMSK1 = 0x21;          // enable input capture interrupt; enable overflow interrupt
    TCCR1A = 0x00;          // clear any previous configuration
    TCCR1B = 0x03;          // set prescaler
    DDRB &= ~(_BV(PB0));    // pinMode(8, INPUT);    
}

