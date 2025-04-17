#include "rotary_encoder.h"

uint8_t pos;
uint8_t switchPressed;
uint8_t selectionActive;
uint8_t changeActive;

void initRotaryEncoder() {
  pos = 0;
  switchPressed = 0;
  selectionActive = 0;
  changeActive = 0;

  // setup ports
  DDRD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4)); // PD2 (A), PD3 (B), PD4 (SW) as input
  PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4);   // Enable pull-ups

  // setup interrupts
  EICRA |= (1 << ISC00);  // Any change on INT0
  EICRA |= (1 << ISC10);  // Any change on INT1
  EIMSK |= (1 << INT0) | (1 << INT1); // Enable INT0 and INT1

  // === Pin Change Interrupt for PD4 (PCINT20) ===
  PCICR |= (1 << PCIE2);     // Enable PCINT[23:16] for PORTD
  PCMSK2 |= (1 << PCINT20);  // Enable PCINT20 for PD4

  sei(); // Enable global interrupts
}

void increasePos() {
  pos++;
  updateSelection(+1);
}

void decreasePos() {
  pos--;
  updateSelection(-1);
}

void pressButton() {
  cli();

  switchPressed = true;

  if(selectedItem == ALARM_TONE_1) {
    selectedN = n1;
    selectedTone = tone1;
    selectedDur = dur1;
    playMelody(n1, tone1, dur1);
  }
  else if(selectedItem == ALARM_TONE_2) {
    selectedN = n4;
    selectedTone = tone4;
    selectedDur = dur4;
    playMelody(n4, tone4, dur4);
  }
  else if(selectedItem == ALARM_TONE_3) {
    selectedN = n5;
    selectedTone = tone5;
    selectedDur = dur5;
    playMelody(n5, tone5, dur5);
  }
  else {
    playMelody(n2, tone2, dur2);

    if(selectionActive) {
      // Play a melody or sound to indicate selection is inactive
      playMelody(n2, tone2, dur2);

      //while(i2cBusy){}
      //i2cBusy = 1;
      //_delay_ms(500); // Debounce delay
      //writeTimeToRTC();
      changeActive = 1;
      //_delay_ms(500); // Debounce delay
      //i2cBusy = 0;
      
      //selectionActive = 0;
    }
    else {
      selectionActive = 1;
      // Play a melody or sound to indicate selection is active
      playMelody(n3, tone3, dur3);

      _delay_ms(500); // Debounce delay
    }

    playMelody(n2, tone2, dur2);
  }

  sei();
}

void releaseButton() {
  switchPressed = false;
}

ISR(INT0_vect) {
  cli();

  // Rotary A changed
  if (PIND & (1 << PD2)) {
    if (PIND & (1 << PD3)) {
      increasePos();
    } else {
      decreasePos();
    }
  } else {
    if (PIND & (1 << PD3)) {
      decreasePos();
    } else {
      increasePos();
    }
  }

  _delay_ms(50);
  sei();
}

ISR(INT1_vect) {
  // Rotary B changed (optional, redundant with INT0 for direction detection)
}

ISR(PCINT2_vect) {
  // Check if switch is pressed (active LOW)
  if (!(PIND & (1 << PD4))) {
    pressButton();
  } else {
    releaseButton();
  }
}