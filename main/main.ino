
#define CHECK 16

static const uint8_t D0  = 16;
static const uint8_t D1  = 05;
static const uint8_t D2  = 04;
static const uint8_t D3  = 00;
static const uint8_t D4  = 02;
static const uint8_t D5  = 14;
static const uint8_t D6  = 12;
static const uint8_t D7  = 13;
static const uint8_t D8  = 15;
static const uint8_t D9  = 03;
static const uint8_t D10 = 01;


void setup() {
  pinMode(CHECK, OUTPUT);
}

void loop() {
  check_sys();
}


  
void check_sys(){
  for(int i = 0; i < 3; i++){
    digitalWrite(CHECK, HIGH);
    delay(100);
    digitalWrite(CHECK, LOW);
    delay(100);
  }
}
