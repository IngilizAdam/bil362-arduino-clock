#include "rtc.h"

uint8_t second = 0;
uint8_t minute = 0;
uint8_t hour = 0;
uint8_t day = 0;
uint8_t date = 0;
uint8_t month = 0;
uint16_t year = 0;

void updateTime() {
  // Initialize I2C as master
  TWSR = 0;  // Prescaler value = 1
  TWBR = 72; // Set bit rate register (for 100kHz at 16MHz CPU)
  TWCR = (1 << TWEN);  // Enable TWI (I2C)
  
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
  second = bcdToDecimal(second);
  minute = bcdToDecimal(minute);
  hour = bcdToDecimal(hour & 0x3F); // Mask AM/PM bit if in 12-hour mode
  day = bcdToDecimal(day);
  date = bcdToDecimal(date);
  month = bcdToDecimal(month & 0x1F); // Mask century bit
  year = 2000 + bcdToDecimal(year);
}

void writeTimeToRTC() {
// Init I2C if not already done
  TWSR = 0;  // Prescaler value = 1
  TWBR = 72; // Set bit rate register (for 100kHz at 16MHz CPU)
  //TWCR = (1 << TWEN);  // Enable TWI (I2C)

  startI2C();
  sendI2C((I2C_DS3231_ADDRESS << 1) | 0); // Write mode
  sendI2C(0x00); // Start from register 0

  sendI2C(decToBcd(second));
  sendI2C(decToBcd(minute));
  sendI2C(decToBcd(hour));
  sendI2C(decToBcd(day)); // 1–7
  sendI2C(decToBcd(date));      // Day of month
  sendI2C(decToBcd(month));     // Month
  sendI2C(decToBcd(year % 100)); // Two-digit year

  stopI2C();
}


uint8_t bcdToDecimal(uint8_t bcd) {
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t decToBcd(uint8_t val) {
  return ((val / 10) << 4) | (val % 10);
}