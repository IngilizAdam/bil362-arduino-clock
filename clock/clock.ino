#include "i2c.h"
#include "define.h"
#include "rtc.h"
#include "oled.h"
#include "buzzer.h"
#include "rotary_encoder.h"

void setup() {
  Serial.begin(9600);

  initRotaryEncoder();
  initScreen();

  playMelody();
}

void loop() {
  updateTime();
  drawMainScreen();

  Serial.println(switchPressed);
  Serial.println(pos);

  delay(1000);
}
