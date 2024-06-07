#ifndef rpm_release_vectors
construct_ISR(PCINT0_vect)
construct_ISR(PCINT1_vect)
construct_ISR(PCINT2_vect)
#endif

void r_setup(uint8_t _pin) {
	switch(_pin) {
	case 0:
		PCICR |= _BV(PCIE2);
		PCMSK2 |= _BV(PCINT17);
		break;
	case 1:
		PCICR |= _BV(PCIE2);
		PCMSK2 |= _BV(PCINT16);
		break;
	case 2:
		PCICR |= _BV(PCIE2);
		PCMSK2 |= _BV(PCINT18);
		break;
	case 3:
		PCICR |= _BV(PCIE2);
		PCMSK2 |= _BV(PCINT19);
		break;
	case 4:
		PCICR |= _BV(PCIE2);
		PCMSK2 |= _BV(PCINT20);
		break;
	case 5:
		PCICR |= _BV(PCIE2);
		PCMSK2 |= _BV(PCINT21);
		break;
	case 6:
		PCICR |= _BV(PCIE2);
		PCMSK2 |= _BV(PCINT22);
		break;
	case 7:
		PCICR |= _BV(PCIE2);
		PCMSK2 |= _BV(PCINT23);
		break;
	case 8:
		PCICR |= _BV(PCIE0);
		PCMSK0 |= _BV(PCINT0);
		break;
	case 9:
		PCICR |= _BV(PCIE0);
		PCMSK0 |= _BV(PCINT1);
		break;
	case 10:
		PCICR |= _BV(PCIE0);
		PCMSK0 |= _BV(PCINT2);
		break;
	case 11:
		PCICR |= _BV(PCIE0);
		PCMSK0 |= _BV(PCINT3);
		break;
	case 12:
		PCICR |= _BV(PCIE0);
		PCMSK0 |= _BV(PCINT4);
		break;
	case 13:
		PCICR |= _BV(PCIE0);
		PCMSK0 |= _BV(PCINT5);
		break;
	case 14:
		PCICR |= _BV(PCIE1);
		PCMSK1 |= _BV(PCINT9);
		break;
	case 15:
		PCICR |= _BV(PCIE1);
		PCMSK1 |= _BV(PCINT10);
		break;
	case 16:
		PCICR |= _BV(PCIE1);
		PCMSK1 |= _BV(PCINT11);
		break;
	case 17:
		PCICR |= _BV(PCIE1);
		PCMSK1 |= _BV(PCINT12);
		break;
	case 18:
		PCICR |= _BV(PCIE1);
		PCMSK1 |= _BV(PCINT13);
	default:
		break;
	}
}
