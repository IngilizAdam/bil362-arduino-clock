#pragma once

#include "U8g2lib.h"
#include "rtc.h"

extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

void initScreen();
void drawMainScreen();