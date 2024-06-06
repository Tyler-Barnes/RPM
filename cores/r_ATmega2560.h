#ifndef rpm_release_vectors
construct_ISR(PCINT0_vect)
construct_ISR(PCINT1_vect)
construct_ISR(PCINT2_vect)
#endif


void r_setup(uint8_t _pin) {
switch(_pin) {
case 0:
	PCICR |= PCIE2;
	PCMSK2 |= PCINT8;
	break;
case 10:
	PCICR |= PCIE0;
	PCMSK0 |= PCINT4;
	break;    
    case 11:
        PCICR |= PCIE0;
        PCMSK0 |= PCINT5;
        break;
    case 12:
        PCICR |= PCIE0;
        PCMSK0 |= PCINT6;
        break;
    case 13:
        PCICR |= PCIE0;
        PCMSK0 |= PCINT7;
        break;
    case 14:
        PCICR |= PCIE1;
        PCMSK1 |= PCINT10;
        break;
    case 15:
        PCICR |= PCIE1;
        PCMSK1 |= PCINT9;
        break;
    case 50:
        PCICR |= PCIE0;
        PCMSK0 |= PCINT3;
        break;
    case 51:
        PCICR |= PCIE0;
        PCMSK0 |= PCINT2;
        break;
    case 52:
        PCICR |= PCIE0;
        PCMSK0 |= PCINT1;
        break;
    case 62:
        PCICR |= PCIE2;
        PCMSK2 |= PCINT16;
        break;
    case 63:
        PCICR |= PCIE2;
        PCMSK2 |= PCINT17;
        break;
    case 64:
        PCICR |= PCIE2;
        PCMSK2 |= PCINT18;
        break;
    case 65:
        PCICR |= PCIE2;
        PCMSK2 |= PCINT19;
        break;
    case 66:
        PCICR |= PCIE2;
        PCMSK2 |= PCINT20;
        break;
    case 67:
        PCICR |= PCIE2;
        PCMSK2 |= PCINT21;
        break;
    case 68:
        PCICR |= PCIE2;
        PCMSK2 |= PCINT22;
        break;
    case 69:
        PCICR |= PCIE2;
        PCMSK2 |= PCINT23;
        break;

	default:
		break;
	}
}
