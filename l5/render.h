#include "HardwareSerial.h"
// render.h
#ifndef RENDER_H
#define RENDER_H

static const byte Num[] = {
  ~B11111100,//0
  ~B01100000,//1
  ~B11011010,//2
  ~B11110010,//3
  ~B01100110,//4
  ~B10110110,//5
  ~B10111110,//6
  ~B11100000,//7
  ~B11111110,//8
  ~B11110110,//9
  ~B00000000 //none
};

class ShiftRegister {
public:
  ShiftRegister(int latch, int dpin, int clk) : latch(latch), dpin(dpin), clk(clk) {}

  void sendBit(bool bit) {
    PORTD&= ~(1<<clk);
    bit ? PORTB|=(1<<dpin) : PORTB&=~(1<<dpin);
    PORTD^= 1<<clk;
  }
  void sendbyte(byte data) {
      for (int i = 0; i < 8; i++) {
          sendBit(data & (1 << i));
      }
  }
  void render(byte data1, byte data2, byte data3, byte data4){
    
    sendbyte(data4); sendbyte(B00011111);
    PORTD^=(1<<latch); PORTD|=(1<<latch);
    sendbyte(data3); sendbyte(B00101111);
    PORTD^=(1<<latch); PORTD|=(1<<latch);
    sendbyte(data2); sendbyte(B01001111);
    PORTD^=(1<<latch); PORTD|=(1<<latch);
    sendbyte(data1); sendbyte(B10001111);
    PORTD^=(1<<latch); PORTD|=(1<<latch);
  }

  void SHRSendNum(float num) {
  float tmp = 1000;
  int numAfterPoint = 0;
  while ((tmp > num) && (tmp > 1)) {
    tmp /= 10;
    numAfterPoint++;
  }
  int numBeforePoint = 4 - numAfterPoint;
  for (int i = 0; i < numAfterPoint; ++i) num *= 10;
  int intNum = num;
  int num4 = intNum % 10;
  intNum /= 10;
  int num3 = intNum % 10;
  intNum /= 10;
  int num2 = intNum % 10;
  intNum /= 10;
  int num1 = intNum % 10;
  render(Num[num1]&~(numBeforePoint==1),Num[num2]&~(numBeforePoint==2),Num[num3]&~(numBeforePoint==3),Num[num4]);
}

private:
  int latch;
  int dpin;
  int clk;
};

#endif