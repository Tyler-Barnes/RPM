#define r_prsclr 64.0
#define r_rpm(x) 60.0 * F_CPU / (x * r_prsclr)

volatile uint8_t r_overFlow = 0;
volatile uint8_t r_reset = 0;

ISR(TIMER1_CAPT_vect) {
    TCNT1 = 0;      // reset timer
    if (++r_reset > r_overFlow) {
        r_overFlow = 0; 
        r_reset = 0; 
    }
}

ISR(TIMER1_OVF_vect) {
    if (++r_overFlow > 3) {
        r_overFlow = 2; 
        r_reset = 0;
    } 
}

double RPMclass::getRPM() {
    return (r_overFlow) ? 0 : r_rpm(ICR1); 
}

void RPMclass::config(uint8_t _pullup) {
    CLKPR = 0x80;                   // no CPU prescaler
    TIMSK1 = 0x21;                  // enable input capture interrupt; enable overflow interrupt
    TCCR1A = 0x00;                  // clear any previous configuration
    TCCR1B = 0x03;                  // timer prescaler 64
    DDRB &= ~(_BV(PIN_PB0));        // pinMode(8, INPUT); 
    switch(_pullup){
    case INTERNAL_PULLUP:
        PORTB |= _BV(PIN_PB0);      // enable pullup
        break;
    default:
        PORTB &= ~(_BV(PIN_PB0));   // disable pullup 
        break;
    }   
}

