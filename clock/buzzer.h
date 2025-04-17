#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>

void playMelody();
void tone(uint8_t num, uint8_t dur);