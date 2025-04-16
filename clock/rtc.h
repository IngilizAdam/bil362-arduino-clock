#pragma once

#include <stdint.h>
#include "i2c.h"
#include "define.h"

extern uint8_t second;
extern uint8_t minute;
extern uint8_t hour;
extern uint8_t day;
extern uint8_t date;
extern uint8_t month;
extern uint16_t year;

void updateTime();
uint8_t bcd_to_decimal(uint8_t bcd);
