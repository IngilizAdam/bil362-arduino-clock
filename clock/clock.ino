#include "i2c.h"
#include "define.h"
#include "rtc.h"

void setup() {
  PORTC |= (1 << PORTC4) | (1 << PORTC5);

  // Initialize I2C as master
  TWSR = 0;  // Prescaler value = 1
  TWBR = 72; // Set bit rate register (for 100kHz at 16MHz CPU)
  TWCR = (1 << TWEN);  // Enable TWI (I2C)
  
  Serial.begin(9600);
}

void loop() {
  updateTime();

  // Display time
  Serial.print("Time: ");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(minute, DEC);
  Serial.print(":");
  Serial.print(second, DEC);
  
  Serial.print("  Date: ");
  Serial.print(date, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  
  Serial.print("  Day: ");
  Serial.println(day, DEC);

  delay(1000);
}
