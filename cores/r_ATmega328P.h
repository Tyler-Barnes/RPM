#ifndef rpm_release_vectors
construct_ISR(PCINT0_vect)
construct_ISR(PCINT1_vect)
construct_ISR(PCINT2_vect)
#endif

void r_setup(uint8_t _pin) {
	switch(_pin) {
	case 0:
		PCICR = PCIE2;
		PCMSK2 = PCINT17;
		break;
	case 1:
		PCICR = PCIE2;
		PCMSK2 = PCINT16;
		break;
	case 2:
		PCICR = PCIE2;
		PCMSK2 = PCINT18;
		break;
	case 3:
		PCICR = PCIE2;
		PCMSK2 = PCINT19;
		break;
	case 4:
		PCICR = PCIE2;
		PCMSK2 = PCINT20;
		break;
	case 5:
		PCICR = PCIE2;
		PCMSK2 = PCINT21;
		break;
	case 6:
		PCICR = PCIE2;
		PCMSK2 = PCINT22;
		break;
	case 7:
		PCICR = PCIE2;
		PCMSK2 = PCINT23;
		break;
	case 8:
		PCICR = PCIE0;
		PCMSK0 = PCINT0;
		break;
	case 9:
		PCICR = PCIE0;
		PCMSK0 = PCINT1;
		break;
	case 10:
		PCICR = PCIE0;
		PCMSK0 = PCINT2;
		break;
	case 11:
		PCICR = PCIE0;
		PCMSK0 = PCINT3;
		break;
	case 12:
		PCICR = PCIE0;
		PCMSK0 = PCINT4;
		break;
	case 13:
		PCICR = PCIE0;
		PCMSK0 = PCINT5;
		break;
	case 14:
		PCICR = PCIE1;
		PCMSK1 = PCINT9;
		break;
	case 15:
		PCICR = PCIE1;
		PCMSK1 = PCINT10;
		break;
	case 16:
		PCICR = PCIE1;
		PCMSK1 = PCINT11;
		break;
	case 17:
		PCICR = PCIE1;
		PCMSK1 = PCINT12;
		break;
	case 18:
		PCICR = PCIE1;
		PCMSK1 = PCINT13;
	default:
		break;
	}
}