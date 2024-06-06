#ifndef rpm_release_vectors
construct_ISR(PCINT0_vect)
#endif


void r_setup(uint8_t _pin) {
	switch(_pin) {
	case 8:
		PCICR |= PCIE0;
		PCMSK0 |= PCINT4;
		break;
	case 9:
		PCICR |= PCIE0;
		PCMSK0 |= PCINT5;
		break;
	case 10:
		PCICR |= PCIE0;
		PCMSK0 |= PCINT6;
		break;
	case 11:
		PCICR |= PCIE0;
		PCMSK0 |= PCINT7;
		break;
	case 14:
		PCICR |= PCIE0;
		PCMSK0 |= PCINT3;
		break;
	case 16:
		PCICR |= PCIE0;
		PCMSK0 |= PCINT1;
		break;
	case 16:
		PCICR |= PCIE0;
		PCMSK0 |= PCINT2;
		break;
	case 17:
		PCICR |= PCIE0;
		PCMSK0 |= PCINT0;
		break;
	default:
		break;
	}
}