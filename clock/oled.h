#pragma once

#include "U8g2lib.h"
#include "rtc.h"
#include "define.h"

extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

extern MENU_ITEM selectedItem;

void initScreen();
void clearScreen();
void applyScreenBuffer();
void drawMainScreen();
void drawAlarmScreen();
void updateSelection(uint8_t direction);