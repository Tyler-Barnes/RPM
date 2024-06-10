#ifndef rpm_release_vectors
construct_ISR(PCINT0_vect)
construct_ISR(PCINT1_vect)
construct_ISR(PCINT2_vect)
#endif

const uint8_t r_nPins = 18; 

uint8_t r_avrPin(uint8_t _pin) {
	switch(_pin) {
	case 0:
		return 0;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 4;
		break;
	case 5:
		return 5;
		break;
	case 6:
		return 6;
		break;
	case 7:
		return 7;
		break;
	case 8:
		return 8;
		break;
	case 9:
		return 9;
		break;
	case 10:
		return 10;
		break;
	case 11:
		return 11;
		break;
	case 12:
		return 12;
		break;
	case 13:
		return 13;
		break;
	case 14:
		return 14;
		break;
	case 15:
		return 15;
		break;
	case 16:
		return 16;
		break;
	case 17:
		return 17;
		break;
	case 18:
		return 18;
	default:
		break;
	}
};


void r_enable(uint8_t _pin) {
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


void r_disable(uint8_t _pin) {
	switch(_pin) {
	case 0:
		PCICR &= ~(_BV(PCIE2));
		PCMSK2 &= ~(_BV(PCINT17));
		break;
	case 1:
		PCICR &= ~(_BV(PCIE2));
		PCMSK2 &= ~(_BV(PCINT16));
		break;
	case 2:
		PCICR &= ~(_BV(PCIE2));
		PCMSK2 &= ~(_BV(PCINT18));
		break;
	case 3:
		PCICR &= ~(_BV(PCIE2));
		PCMSK2 &= ~(_BV(PCINT19));
		break;
	case 4:
		PCICR &= ~(_BV(PCIE2));
		PCMSK2 &= ~(_BV(PCINT20));
		break;
	case 5:
		PCICR &= ~(_BV(PCIE2));
		PCMSK2 &= ~(_BV(PCINT21));
		break;
	case 6:
		PCICR &= ~(_BV(PCIE2));
		PCMSK2 &= ~(_BV(PCINT22));
		break;
	case 7:
		PCICR &= ~(_BV(PCIE2));
		PCMSK2 &= ~(_BV(PCINT23));
		break;
	case 8:
		PCICR &= ~(_BV(PCIE0));
		PCMSK0 &= ~(_BV(PCINT0));
		break;
	case 9:
		PCICR &= ~(_BV(PCIE0));
		PCMSK0 &= ~(_BV(PCINT1));
		break;
	case 10:
		PCICR &= ~(_BV(PCIE0));
		PCMSK0 &= ~(_BV(PCINT2));
		break;
	case 11:
		PCICR &= ~(_BV(PCIE0));
		PCMSK0 &= ~(_BV(PCINT3));
		break;
	case 12:
		PCICR &= ~(_BV(PCIE0));
		PCMSK0 &= ~(_BV(PCINT4));
		break;
	case 13:
		PCICR &= ~(_BV(PCIE0));
		PCMSK0 &= ~(_BV(PCINT5));
		break;
	case 14:
		PCICR &= ~(_BV(PCIE1));
		PCMSK1 &= ~(_BV(PCINT9));
		break;
	case 15:
		PCICR &= ~(_BV(PCIE1));
		PCMSK1 &= ~(_BV(PCINT10));
		break;
	case 16:
		PCICR &= ~(_BV(PCIE1));
		PCMSK1 &= ~(_BV(PCINT11));
		break;
	case 17:
		PCICR &= ~(_BV(PCIE1));
		PCMSK1 &= ~(_BV(PCINT12));
		break;
	case 18:
		PCICR &= ~(_BV(PCIE1));
		PCMSK1 &= ~(_BV(PCINT13));
	default:
		break;
	}
}
