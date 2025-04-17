#include "rotary_encoder.h"

uint8_t pos;
uint8_t switchPressed;

void initRotaryEncoder() {
  pos = 0;

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
  switchPressed = true;
}

void releaseButton() {
  switchPressed = false;
}

ISR(INT0_vect) {
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