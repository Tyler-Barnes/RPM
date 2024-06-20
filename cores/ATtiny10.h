#define r_prsclr 64.0
#define r_rpm(x) 60.0 * F_CPU / (x * r_prsclr)

volatile uint8_t r_overFlow = 0;
volatile uint8_t r_reset = 0;

ISR(TIM0_CAPT_vect) {
    TCNT0 = 0;      // reset timer
    if (++r_reset > r_overFlow) {
        r_overFlow = 0; 
        r_reset = 0; 
    }
}

ISR(TIM0_OVF_vect) {
    if (++r_overFlow > 3) {
        r_overFlow = 2; 
        r_reset = 0;
    } 
}

double RPMclass::getRPM() {
    return (r_overFlow) ? 0 : r_rpm(ICR0); 
}

void RPMclass::config() {
    CCP = 0xD8;             // unlock clock register 
    CLKMSR = 0x00;          // 8MHz internal clock 
    TCCR0A = 0x00;          // clear any previous configuration
    TCCR0B = 0x03;          // timer prescaler 64
    TIMSK0 = 0x21;          // enable input capture interrupt; enable overflow interrupt
    DDRB &= ~(_BV(PB1));
}

