#ifndef rpm_release_vectors
construct_ISR(PCINT0_vect)
#endif

const uint8_t r_nPins = 8; 

uint8_t r_avrPin(uint8_t _pin) {
    switch(_pin) {
    case 8:
        return 0;
        break;
    case 9:
        return 1;
        break;
    case 10:
        return 2;
        break;
    case 11:
        return 3;
        break;
    case 14:
        return 4;
        break;
    case 15:
        return 5;
        break;
    case 16:
        return 6;
        break;
    case 17:
        return 7;
    default:
        break;
    }
}

void r_enable(uint8_t _pin) {
    switch(_pin) {
    case 8:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT4);
        break;
    case 9:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT5);
        break;
    case 10:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT6);
        break;
    case 11:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT7);
        break;
    case 14:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT3);
        break;
    case 15:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT1);
        break;
    case 16:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT2);
        break;
    case 17:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT0);
        break;
    default:
        break;
    }
}

void r_disable(uint8_t _pin) {
    switch(_pin) {
    case 8:
        PCICR &= ~(_BV(PCIE0));
        PCMSK0 &= ~(_BV(PCINT4));
        break;
    case 9:
        PCICR &= ~(_BV(PCIE0));
        PCMSK0 &= ~(_BV(PCINT5));
        break;
    case 10:
        PCICR &= ~(_BV(PCIE0));
        PCMSK0 &= ~(_BV(PCINT6));
        break;
    case 11:
        PCICR &= ~(_BV(PCIE0));
        PCMSK0 &= ~(_BV(PCINT7));
        break;
    case 14:
        PCICR &= ~(_BV(PCIE0));
        PCMSK0 &= ~(_BV(PCINT3));
        break;
    case 15:
        PCICR &= ~(_BV(PCIE0));
        PCMSK0 &= ~(_BV(PCINT1));
        break;
    case 16:
        PCICR &= ~(_BV(PCIE0));
        PCMSK0 &= ~(_BV(PCINT2));
        break;
    case 17:
        PCICR &= ~(_BV(PCIE0));
        PCMSK0 &= ~(_BV(PCINT0));
        break;
    default:
        break;
    }
}
