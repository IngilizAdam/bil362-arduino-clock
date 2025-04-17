#pragma once

#define I2C_DS3231_ADDRESS 0x68 // RTC module

#define F_CPU 16000000UL

enum MENU_ITEM{
  BLANK,
  HOUR,
  MINUTE,
  SECOND
};