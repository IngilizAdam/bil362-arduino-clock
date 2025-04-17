#pragma once

#include <stdint.h>
#include "i2c.h"
#include "define.h"

extern int second;
extern int minute;
extern int hour;
extern int day;
extern int date;
extern int month;
extern int year;

extern int alarmHour;
extern int alarmMinute;

void updateTime();
void writeTimeToRTC();
uint8_t bcdToDecimal(uint8_t bcd);
uint8_t decToBcd(uint8_t val);
