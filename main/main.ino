
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>


#define CHECK 16

#define LED_PIN1 D8
#define LED_PIN2 D7

#define SERVO D6

#define TOUCH D0

#define RELLAY D5

Servo servo;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  
  matchPin();
  
  servo.attach(SERVO);
  
  check_sys();
  servoClose();
  lcd.begin();
  lcd.backlight();
  lcd.print("UV-Cleaner");
  delay(1000);
  
}
int count = 0;
  
void loop() {

  if(digitalRead(TOUCH) == 1){ //clicked
    if(count == 0){
      count = 1;
      ledOn();
      lcd.setCursor(0,1);
      lcd.print("                ");
      digitalWrite(RELLAY,LOW);
      servoOpen();
     
    }
    else if(count == 1){
      count = 0;
      ledOff();
      servoClose(); 
      digitalWrite(RELLAY,HIGH);
      
      lcd.setCursor(0, 1);
      
      lcd.print("Progress : ");
      lcd.setCursor(11, 1);
      for(int i = 0; i <= 100; i++){
        lcd.print(String(i)+"%");
        delay(100);
        lcd.setCursor(11,1);
        lcd.print("     ");
        lcd.setCursor(11,1);
      }
       lcd.print("Done");
    }
  }

  
}

void matchPin(){
  
  pinMode(CHECK, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(RELLAY, OUTPUT);
  pinMode(TOUCH, INPUT);
  
}
  
void check_sys(){
  for(int i = 0; i < 5; i++){
    digitalWrite(CHECK, HIGH);
    delay(100);
    digitalWrite(CHECK, LOW);
    delay(100);
  }
}

void ledOn(){
  digitalWrite(LED_PIN1, HIGH);
  digitalWrite(LED_PIN2, HIGH);
  
}

void ledOff(){
  digitalWrite(LED_PIN1, LOW);
  digitalWrite(LED_PIN2, LOW);
}

void servoOpen(){
  for(int i = 0; i <= 160; i){
    servo.write(i);
    i += 5;
    delay(40);
  }

}

void servoClose(){
  servo.write(0);
  for(int i = 160; i >= 0; i){
    servo.write(i);
    i -= 5;
    delay(40);
  }
}
