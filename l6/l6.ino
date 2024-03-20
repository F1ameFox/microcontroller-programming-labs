#include "render.h"
ShiftRegister shiftRegister(PD4, PB0, PD7); //latch data clk

float valADC;

void setup() {
  DDRD|= 1<<PD4 | 1<<PD7;
  DDRB|= 1<<PB0;
  
  ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADIE);
  ADCSRB = B00000001;
  ADMUX  = B01000000;
}

ISR(ADC_vect){
  valADC = ADC/204.8;
}

void loop() {
  ADCSRA|=_BV(ADSC);
  shiftRegister.SHRSendNum(valADC);
}