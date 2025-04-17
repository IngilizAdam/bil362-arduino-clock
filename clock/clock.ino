#include "i2c.h"
#include "define.h"
#include "rtc.h"
#include "oled.h"
#include "buzzer.h"

void setup() {
  Serial.begin(9600);

  initScreen();
  playMelody();
}

void loop() {
  updateTime();
  drawMainScreen();

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
