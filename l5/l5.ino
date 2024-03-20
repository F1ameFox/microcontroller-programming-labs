#include "render.h"

ShiftRegister shiftRegister(PD4, PB0, PD7); //latch data clk

void setup() {
  DDRD|=1<<PD4 | 1<<PD7;
  DDRB|=1<<PB0;
}

void loop() {
  shiftRegister.render(Num[1],Num[2], Num[3], Num[4]);
}