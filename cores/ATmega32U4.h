#ifndef rpm_release_vectors
construct_ISR(PCINT0_vect)
#endif


void r_setup(uint8_t _pin) {
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
