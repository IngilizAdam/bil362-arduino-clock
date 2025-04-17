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

extern uint8_t n4;
extern uint8_t tone4[];
extern uint8_t dur4[];

extern uint8_t n5;
extern uint8_t tone5[];
extern uint8_t dur5[];

extern uint8_t selectedN;
extern uint8_t *selectedTone;
extern uint8_t *selectedDur;

void playMelody(uint8_t n, uint8_t tones[], uint8_t durs[]);
void tone(uint8_t num, uint8_t dur);