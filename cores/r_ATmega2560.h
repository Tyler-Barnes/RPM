#ifndef rpm_release_vectors
construct_ISR(PCINT0_vect)
construct_ISR(PCINT1_vect)
construct_ISR(PCINT2_vect)
#endif


void r_setup(uint8_t _pin) {
switch(_pin) {
case 0:
	PCICR |= _BV(PCIE2);
	PCMSK2 |= _BV(PCINT8);
	break;
case 10:
	PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT4);
	break;    
    case 11:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT5);
        break;
    case 12:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT6);
        break;
    case 13:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT7);
        break;
    case 14:
        PCICR |= _BV(PCIE1);
        PCMSK1 |= _BV(PCINT10);
        break;
    case 15:
        PCICR |= _BV(PCIE1);
        PCMSK1 |= _BV(PCINT9);
        break;
    case 50:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT3);
        break;
    case 51:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT2);
        break;
    case 52:
        PCICR |= _BV(PCIE0);
        PCMSK0 |= _BV(PCINT1);
        break;
    case 62:
        PCICR |= _BV(PCIE2;
        PCMSK2 |= _BV(PCINT16;
        break;
    case 63:
        PCICR |= _BV(PCIE2);
        PCMSK2 |= _BV(PCINT17);
        break;
    case 64:
        PCICR |= _BV(PCIE2);
        PCMSK2 |= _BV(PCINT18);
        break;
    case 65:
        PCICR |= _BV(PCIE2);
        PCMSK2 |= _BV(PCINT19);
        break;
    case 66:
        PCICR |= _BV(PCIE2);
        PCMSK2 |= _BV(PCINT20);
        break;
    case 67:
        PCICR |= _BV(PCIE2);
        PCMSK2 |= _BV(PCINT21);
        break;
    case 68:
        PCICR |= _BV(PCIE2);
        PCMSK2 |= _BV(PCINT22);
        break;
    case 69:
        PCICR |= _BV(PCIE2);
        PCMSK2 |= _BV(PCINT23);
        break;

	default:
		break;
	}
}
