#include "i2c.h"
#include "define.h"
#include "rtc.h"
#include "oled.h"
#include "buzzer.h"
#include "rotary_encoder.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "rotary_encoder.h"

void mainLoop();

volatile unsigned long uptime = 0;
volatile unsigned long last100ms = 0;
volatile unsigned long last1000ms = 0;
uint8_t adjustMode = 0;

void setup() {
  initRotaryEncoder();
  initScreen();

  playMelody(n1, tone1, dur1);

  while(1){
    mainLoop();
  }
}

void mainLoop() {
  uptime = millis();

  if(changeActive) {
    while(i2cBusy){}
    i2cBusy = 1;
    writeTimeToRTC();
    changeActive = 0;
    selectionActive = 0;
    i2cBusy = 0;
  }

  if(!selectionActive) {
    if (uptime - last1000ms > 1000) {
      while(i2cBusy){}
      i2cBusy = 1;
      last1000ms = uptime;
      updateTime();
      i2cBusy = 0;

      if(alarmHour == hour && alarmMinute == minute) {
        playMelody(selectedN, selectedTone, selectedDur);
      }
    }
  }
  
  if (uptime - last100ms > 100) {
    while(i2cBusy){}
    i2cBusy = 1;
    last100ms = uptime;
    clearScreen();
    drawScreen();
    applyScreenBuffer();
    i2cBusy = 0;
  }
}
