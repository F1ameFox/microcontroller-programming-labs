#define DEBUG 1
#define FUNC 0
#define PULLUP 1

int pin[]={2,3,4,5};
bool flag = 1;
bool a0;
bool b0;
bool c0;
int counter = 0;
bool binar[4];

void setup() {
  pinMode(PC1,0);
  pinMode(PC2,0);
  pinMode(PC3,0);
  if(PULLUP)PORTC |= 1 << PC1 | 1 << PC2 | 1 << PC3;
  DDRB|= 1<<pin[3] | 1<<pin[2] | 1<<pin[1] | 1<<pin[0];
  if(DEBUG)Serial.begin(9600);
}

void loop() {
  int a = PINC>>PC1 & 1;
  int b = PINC>>PC2 & 1;
  int c = PINC>>PC3 & 1;

  if(a!=a0){  
    a0 = a;
    if(a==1) FUNC ? changeValf(0):changeVal(0);
  }
  if(b!=b0){
    b0 = b;
    if(b==1) off();
  }
  if(c!=c0){
    c0 = c;
    if(c==1) FUNC ? changeValf(1):changeVal(1);
  }
}

void off(){
  counter = 0;
  PORTB=~(counter<<2);
}

void changeVal(bool up){
  counter = max(min(counter + (up ? 1 : -1), 15), 0);
  PORTB=~(counter<<2);
  if(DEBUG)debug();
}

void changeValf(bool up){
  counter = max(min(counter + (up ? 1 : -1), 15), 0);
  if(DEBUG)debug();
  binary();
  binar[0]==0?digitalWrite(10,1):digitalWrite(10,0);
  binar[1]==0?digitalWrite(11,1):digitalWrite(11,0);
  binar[2]==0?digitalWrite(12,1):digitalWrite(12,0);
  binar[3]==0?digitalWrite(13,1):digitalWrite(13,0);
}

void debug(){
  Serial.print("0b");
  Serial.print(counter,2);
  Serial.print("\t");
  Serial.println(counter);
}

void binary(){
  int dec = counter;
  for(int i = 3;i>=0;i--){
    binar[i]=dec%2;
    dec = dec/2;
  }
}
