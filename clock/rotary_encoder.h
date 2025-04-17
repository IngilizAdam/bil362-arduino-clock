#pragma once

#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

extern uint8_t pos;
extern uint8_t switchPressed;

void initRotaryEncoder();

ISR(INT0_vect);
ISR(INT1_vect);
ISR(PCINT2_vect);