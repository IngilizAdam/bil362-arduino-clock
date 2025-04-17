#pragma once

#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include "oled.h"
#include "buzzer.h"

extern uint8_t pos;
extern uint8_t switchPressed;
extern uint8_t selectionActive;
extern uint8_t changeActive;

void initRotaryEncoder();
void increasePos();
void decreasePos();
void pressButton();
void releaseButton();

ISR(INT0_vect);
ISR(INT1_vect);
ISR(PCINT2_vect);