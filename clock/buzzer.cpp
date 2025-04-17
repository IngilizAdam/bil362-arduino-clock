#include "buzzer.h"

uint8_t n1 = 16;
uint8_t tone1[] = {5,5,4,7,6,4,1,7,4,9,7,5,7,9,9};
uint8_t dur1[]  = {4,4,4,4,4,4,4,4,4,4,4,4,6,2,30};

uint8_t n2 = 3;
uint8_t tone2[] = {2, 4, 2};
uint8_t dur2[]  = {10, 5, 10};

uint8_t n3 = 3;
uint8_t tone3[] = {2, 1, 2};
uint8_t dur3[]  = {10, 5, 10};

void playMelody(uint8_t n, uint8_t tones[], uint8_t durs[]) {
  DDRB |= (1 << DDB1); // PB1 (OC1A) output

  // TIMER1 Settings: CTC Mode, Toggle OC1A
  TCCR1A = (1 << COM1A0); // Toggle OC1A on compare
  TCCR1B = (1 << WGM12);  // CTC mode
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Stop timer for now

  for (uint8_t t = 0; t < (n-1); t++) {
    tone(tones[t], durs[t]);
  }
}


void tone(uint8_t num, uint8_t dur) {
  // Convert note number to frequency (approximate formula for equal temperament)
  double freq = 440.0 * pow(2.0, (num - 9) / 12.0); // A4 = 440Hz, num=9 -> A4

  // OCR1A calculation: OCR1A = (F_CPU / (2 * prescaler * freq)) - 1
  uint16_t prescaler = 8;
  uint16_t ocr = (uint16_t)((F_CPU / (2UL * prescaler * freq)) - 1);
  OCR1A = ocr;

  // Start Timer1 with prescaler 8
  TCCR1B = (1 << WGM12) | (1 << CS11);

  // Duration
  for (uint8_t i = 0; i < dur; i++) {
    _delay_ms(20);
  }

  // Stop timer
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

  // Short pause between notes
  _delay_ms(100);
}
