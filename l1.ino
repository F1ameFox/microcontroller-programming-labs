//{PB2,PB3,PB4,PB5};
void setup() {
  DDRB|= 1<<2 | 1<<3 | 1<<4 | 1<<5;
}

void loop() {
  for (int i = 2; i <= 5; i++){
    PORTB|= 1<<i;
    delay(500);
    PORTB^= 1<<i;
  }
}
