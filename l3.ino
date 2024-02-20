#define DEBUG 1
#define PULLUP 1

int pin[]={2,3,4,5};
volatile bool a0;
volatile bool b0;
volatile bool c0;
int counter = 0;

void setup() {
  pinMode(A1,2);//DDRC &= ~(1 << PC1); // INPUT
  pinMode(A2,2);
  pinMode(A3,2);
  if(PULLUP)PORTC |= 1 << PC1 | 1 << PC2 | 1 << PC3;
  DDRB|= 1<<pin[3] | 1<<pin[2] | 1<<pin[1] | 1<<pin[0];

  PCICR = 1<<1;
  PCMSK1 = 1<<1 | 1<<2 | 1<<3;

  if(DEBUG)Serial.begin(9600);
}

ISR(PCINT1_vect){
  int a = PINC>>PC1 & 1;
  int b = PINC>>PC2 & 1;
  int c = PINC>>PC3 & 1;

  if(a!=a0){  
    a0 = a;
    if(a==0) changeVal(0);
  }
  if(b!=b0){
    b0 = b;
    if(b==0) off();
  }
  if(c!=c0){
    c0 = c;
    if(c==0) changeVal(1);
  }
}

void off(){
  counter = 0;
  PORTB=~(counter<<2);
}

void changeVal(bool up){
  //binary();
  counter = max(min(counter + (up ? 1 : -1), 15), 0);
  PORTB=~(counter<<2);
  if(DEBUG)debug();
}

void debug(){
  Serial.print("0b");
  Serial.print(counter,2);
  Serial.print("\t");
  Serial.println(counter);
}
void loop(){}
