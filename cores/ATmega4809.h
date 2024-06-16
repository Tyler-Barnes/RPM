#define r_prsclr 64.0
#define r_rpm(x) 60.0 * F_CPU / (x * r_prsclr)
#define r_maxTimer 0xFFFF * r_prsclr / F_CPU

volatile int r_overFlow = 0; 
volatile uint16_t r_capture = 0;
volatile uint32_t r_timeOut = 0;

void r_incTimeout() {
    if (micros() - r_timeOut < r_maxTimer) {
        r_overFlow += 2;    // the hare
        if (r_overFlow > 3) r_overFlow = 3; 
    }
}

ISR(TCB0_INT_vect){
    r_capture = TCB0.CCMP;
    r_incTimeout(); 
    r_timeOut = micros();
    if (--r_overFlow < 0) r_overFlow = 0; // the tortoise 
}

uint16_t RPMclass::getRPM(){
    r_incTimeOut(); 
    return (r_overFlow) ? 0 : r_rpm(r_capture);
}

void RPMclass::config() {
    CLKCTRL.MCLKCTRLA = 0x00;                       // internal 20MHz clock
    CLKCTRL.MCLKCTRLB = 0x00;                       // no prescaler
    EVSYS.CHANNEL4 = EVSYS_GENERATOR_PORT1_PIN4_gc; // Pin 6 (PF4) set as capture pin
    EVSYS.USERTCB0 = EVSYS_CHANNEL_CHANNEL4_gc;     // TCB0 user connected to event channel4
    TCB0.EVCTRL = 0x11;                             // enable input capture on falling edge 
    TCB0.INTCTRL = 0x01;                            // enable input capture interrupt
    TCB0.CTRLB = TCB_CNTMODE_FRQ_gc;                // frequency measurement mode               
    TCB0.CTRLA = TCB_CLKSEL_CLKTCA_gc;              // use TCA timer prescaler 64
}