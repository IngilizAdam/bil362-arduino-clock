#include "i2c.h"
#include "define.h"
#include "rtc.h"
#include "oled.h"
#include "buzzer.h"
#include "rotary_encoder.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void mainLoop();

volatile unsigned long uptime = 0;
volatile unsigned long last100ms = 0;
volatile unsigned long last1000ms = 0;

void setup() {
  initRotaryEncoder();
  initScreen();

  playMelody();

  while(1){
    mainLoop();
  }
}

void mainLoop() {
  uptime = millis();

  if (uptime - last1000ms > 1000) {
    last1000ms = uptime;
    updateTime();
  }

  if (uptime - last100ms > 100) {
    last100ms = uptime;
    clearScreen();
    drawMainScreen();
    applyScreenBuffer();
  }
}
