
#define CHECK 16

#define LED_PIN1 D8
#define LED_PIN2 D7


void setup() {
  
  pinMode(CHECK, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D7, OUTPUT);
  
  check_sys();
  
}

void loop() {
  LED_ON();
  delay(1000);
  LED_OFF();
  delay(4000);
}


  
void check_sys(){
  for(int i = 0; i < 5; i++){
    digitalWrite(CHECK, HIGH);
    delay(100);
    digitalWrite(CHECK, LOW);
    delay(100);
  }
}

void LED_ON(){
  digitalWrite(LED_PIN1, HIGH);
  digitalWrite(LED_PIN2, HIGH);
  
}

void LED_OFF(){
  digitalWrite(LED_PIN1, LOW);
  digitalWrite(LED_PIN2, LOW);
}
