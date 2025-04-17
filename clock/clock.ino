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

  clearScreen();
  drawMainScreen();
  applyScreenBuffer();

  delay(1000);
}
