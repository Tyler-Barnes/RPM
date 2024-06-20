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

uint16_t RPMclass::getRPM(){
    r_incTimeOut();     // if interrupt stops firing, then also detect 0 RPM
    return (r_overFlow) ? 0 : r_rpm(r_capture);
}

void r_ic() {
    CLKCTRL.MCLKCTRLA = 0x00;       // internal 20MHz clock
    CLKCTRL.MCLKCTRLB = 0x09;       // /32 prescaler
    EVSYS.ASYNCCH0 = 0x0D;          // PA3 pin set to trigger ASYNCCH0
    EVSYS.ASYNCUSER0 = 0x03;        // TCB0 User = ASYNCCH0
    TCB0.CTRLA = 0x05;              // enable TimerB, precaler /2
    TCB0.CTRLB = 0x03;              // input capture FRQ mode
    TCB0.INTCTRL = 0x01;            // Enable input capture
    PORTA.DIR &= ~(_BV(PIN_PA3));   // pinMode(PA3, HIGH);
}
