#define r_prsclr 64.0
#define r_rpm(x) 60.0 * F_CPU / (x * r_prsclr)
#define r_maxTimer 0xFFFF * r_prsclr * 1000000 / F_CPU // Timer B has no ovefolow interrupt

volatile int r_overFlow = 0; 
volatile uint16_t r_capture = 0;
volatile uint32_t r_timeOut = 0;

// if overflow counter outruns interrupts then detect 0 RPM
void r_incTimeout() {
    if (micros() - r_timeOut > r_maxTimer) {
        if (++r_overFlow > 3) r_overFlow = 3; // the hare
    }
}

ISR(TCB0_INT_vect){
    r_capture = TCB0.CCMP;
    r_incTimeout(); 
    r_timeOut = micros();
    if (--r_overFlow < 0) r_overFlow = 0; // the tortoise 
}

double RPMclass::getRPM() {
    r_incTimeout();     // if interrupt stops firing, then also detect 0 RPM
    return (r_overFlow) ? 0 : r_rpm(r_capture);
}

void RPMclass::config() {
    CCP = 0x9D;                 // unlock CPU registers
    CLKCTRL.MCLKCTRLA = 0x00;   // 20MHz Clock
    CLKCTRL.MCLKCTRLB = 0x00;   // no prescaler
    EVSYS.ASYNCCH0 = 0x10;      // PA6 input capture pin channel 0
    EVSYS.ASYNCUSER0 = 0x00;    // TCB0 async user listening to ch0
    TCB0.CTRLA = 0x03;          // Use TCA prescaler 64
    TCB0.CTRLB = 0x03;          // frequency capture mode
    TCB0.EVCTRL = 0x11;         // Enable input capture on falling edge
    TCB0.INTCTRL = 0x01;        // enable capture interrupt
    pinMode(PIN_PA6, INPUT);    // PA6 set to input
}
