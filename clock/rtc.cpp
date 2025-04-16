#include "rtc.h"

uint8_t second = 0;
uint8_t minute = 0;
uint8_t hour = 0;
uint8_t day = 0;
uint8_t date = 0;
uint8_t month = 0;
uint16_t year = 0;

void updateTime() {
  startI2C();
  sendI2C((I2C_DS3231_ADDRESS << 1) & 0xFE);
  sendI2C(0x00);
  startI2C();
  sendI2C((I2C_DS3231_ADDRESS << 1) | 0x01);
  
  // Read all time registers with ACK
  second = receiveI2C(1);
  minute = receiveI2C(1);
  hour = receiveI2C(1);
  day = receiveI2C(1);
  date = receiveI2C(1);
  month = receiveI2C(1);
  year = receiveI2C(0);
  
  stopI2C();
  
  // Convert from BCD to decimal
  second = bcd_to_decimal(second);
  minute = bcd_to_decimal(minute);
  hour = bcd_to_decimal(hour & 0x3F); // Mask AM/PM bit if in 12-hour mode
  day = bcd_to_decimal(day);
  date = bcd_to_decimal(date);
  month = bcd_to_decimal(month & 0x1F); // Mask century bit
  year = bcd_to_decimal(year);
}

uint8_t bcd_to_decimal(uint8_t bcd) {
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}