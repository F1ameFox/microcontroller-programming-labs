#define DEBUG 1 // Включение вывода отладочной информации
#define PULLUP 1 // Включение подтяжек

volatile bool a0; // Флаг состояния a
volatile bool b0; // Флаг состояния b
volatile bool c0; // Флаг состояния c
int counter = 0; // Счетчик

ISR(PCINT1_vect){
  int a = PINC >> PC1 & 1; // Считываем состояние пина PC1
  int b = PINC >> PC2 & 1; // Считываем состояние пина PC2
  int c = PINC >> PC3 & 1; // Считываем состояние пина PC3

  if(a != a0){  
    a0 = a;
    if(a == 0) changeVal(0);
  }
  if(b != b0){
    b0 = b;
    if(b == 0) off();
  }
  if(c != c0){
    c0 = c;
    if(c == 0) changeVal(1);
  }
}

void setup() {
  pinMode(A1,0); // Устанавливаем пин A1 как INPUT
  pinMode(A2,0); // Устанавливаем пин A2 как INPUT
  pinMode(A3,0); // Устанавливаем пин A3 как INPUT
  if(PULLUP) PORTC |= 1 << PC1 | 1 << PC2 | 1 << PC3; // Включаем подтяжки для PC1, PC2, PC3
  //DDRB |= 1<<pin[3] | 1<<pin[2] | 1<<pin[1] | 1<<pin[0]; // Устанавливаем пины 2, 3, 4, 5 порта B как выходные
  DDRB |= 1<<PB3;

  TCCR2A = 0; 
  TCCR2B = 0;
  TCNT2 = 0;

  TCCR2B = B00001010;

  OCR2A = 8;

  TCNT2 = 1;

  TIMSK2 = B00000011;

  PCICR = 1<<1; // Разрешаем прерывания на PCINT1
  PCMSK1 = 1<<1 | 1<<2 | 1<<3; // Разрешаем прерывания для пинов 1, 2, 3 на PCINT1

  if(DEBUG) Serial.begin(9600);
}

void changeVal(bool up){
  counter = max(min(counter + (up ? 1 : -1), 16), 0); // Изменяем значение счетчика в зависимости от значения up
  OCR2A = counter>0 ? (16*counter)-1 : 0;
  if(DEBUG) debug(); // Выводим отладочную информацию
}

void loop() {
}

void off(){
  counter = 0; // Сбрасываем счетчик
  //PORTB = ~(counter << 2); // Устанавливаем порт B в соответствии со значением счетчика
  OCR1A = counter;
}

void debug(){
  Serial.print("0b"); // Выводим префикс для двоичного числа
  Serial.print(counter, 2); // Выводим значение счетчика в двоичной системе
  Serial.print("\t"); 
  Serial.println(counter); // Выводим значение счетчика
}

ISR(TIMER2_COMPA_vect) {
  digitalWrite(11, 1);
}
ISR(TIMER2_OVF_vect) {
  digitalWrite(11, 0);
}