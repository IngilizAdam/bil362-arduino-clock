#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>

extern uint8_t n1;
extern uint8_t tone1[];
extern uint8_t dur1[];

extern uint8_t n2;
extern uint8_t tone2[];
extern uint8_t dur2[];

extern uint8_t n3;
extern uint8_t tone3[];
extern uint8_t dur3[];

void playMelody(uint8_t n, uint8_t tones[], uint8_t durs[]);
void tone(uint8_t num, uint8_t dur);