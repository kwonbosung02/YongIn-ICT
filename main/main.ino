#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define CHECK 16
#define LED_PIN1 D8
#define LED_PIN2 D7
#define SERVO D6
#define TOUCH D0
#define RELLAY D5

const char* ssid = "pinecondo";
const char* password = "pine2001";
const char * host = "http://ec2-3-34-140-140.ap-northeast-2.compute.amazonaws.com/set?status=";

WiFiClient client;
HTTPClient http;

Servo servo;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);
  matchPin();
  
  servo.attach(SERVO);
  
  check_sys();
  servoClose();
  lcd.begin();
  lcd.backlight();
  lcd.print("UV-Cleaner");
  //Serial.println("[-----UV_Cleaner-----]");
  //linSpace();
  Wifi_connect();
  //Serial.println("[   Wifi Connnected  ]");
  //linSpace();
  lcd.setCursor(0,1);
  
  lcd.print("WiFi Connected");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("                   ");
  
  lcd.setCursor(10,0);
  lcd.print("(WiFi)");
  //Serial.println("[--UV_Cleaner(WiFi)--]");
  //linSpace();
  digitalWrite(RELLAY,LOW);
}
int count = 0;
  
void loop() {
  if(WiFi.status() != WL_CONNECTED){
     Wifi_connect();
     Serial.println("[ WiFi Reconnected ]");
     linSpace();
  }
  
  if(digitalRead(TOUCH) == 1){ //clicked
    if(count == 0){
      count = 1;
      ledOn();
      Serial.println("[                    ]");
      linSpace();
      digitalWrite(RELLAY,HIGH);
      servoOpen();
     
    }
    else if(count == 1){
      count = 0;
      ledOff();
      servoClose(); 
      digitalWrite(RELLAY,LOW);
      
      lcd.setCursor(0, 1);
      
      lcd.print("Progress : ");
      lcd.setCursor(11, 1);
      
      for(int i = 0; i <= 100; i++){
        send_data(i);
        lcd.print(String(i)+"%");
        delay(100);
        lcd.setCursor(11,1);
        lcd.print("     ");
        lcd.setCursor(11,1);
        
        //if(i < 10)
        //  Serial.println("[---------"+String(i)+"----------]");
        //else if(i < 100)
        //  Serial.println("[--------"+String(i)+"----------]");
        //else
        //  Serial.println("[--------"+String(i)+"---------]");
        //linSpace();
        //delay(50);
      }
      lcd.print("Done");
      digitalWrite(RELLAY,HIGH);
      delay(700);
      digitalWrite(RELLAY,LOW);
      delay(700);
      digitalWrite(RELLAY,HIGH);
      delay(700);
      digitalWrite(RELLAY,LOW);
      delay(700);
      digitalWrite(RELLAY,HIGH);
      delay(700);
      //Serial.println("[--------Done--------]");
      //linSpace();
    }
  }

  
}

void send_data(int count) {
  Serial.printf("count = %d\n", count);
  http.begin(client, "http://ec2-3-34-140-140.ap-northeast-2.compute.amazonaws.com/set?status="+String(count));
  http.setTimeout(1000);
  int httpCode = http.GET();
 
  if(httpCode > 0) {
    Serial.printf("GET code : %d\n\n", httpCode);
    
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } 
  else {
    Serial.printf("GET failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
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

    servo.write(160);
    delay(2000);

}

void servoClose(){
  servo.write(0);
  for(int i = 160; i >= 0; i){
    servo.write(i);
    i -= 5;
    delay(10);
  }
}

void Wifi_connect() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    }
 }

void linSpace(){
          for(int i = 0; i <= 20; i++){
          Serial.println(" ");
        } 
}#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define CHECK 16
#define LED_PIN1 D8
#define LED_PIN2 D7
#define SERVO D6
#define TOUCH D0
#define RELLAY D5

const char* ssid = "pinecondo";
const char* password = "pine2001";
const char * host = "http://ec2-3-34-140-140.ap-northeast-2.compute.amazonaws.com/set?status=";

WiFiClient client;
HTTPClient http;

Servo servo;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);
  matchPin();
  
  servo.attach(SERVO);
  
  check_sys();
  servoClose();
  lcd.begin();
  lcd.backlight();
  lcd.print("UV-Cleaner");
  //Serial.println("[-----UV_Cleaner-----]");
  //linSpace();
  Wifi_connect();
  //Serial.println("[   Wifi Connnected  ]");
  //linSpace();
  lcd.setCursor(0,1);
  
  lcd.print("WiFi Connected");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("                   ");
  
  lcd.setCursor(10,0);
  lcd.print("(WiFi)");
  //Serial.println("[--UV_Cleaner(WiFi)--]");
  //linSpace();
  digitalWrite(RELLAY,LOW);
}
int count = 0;
  
void loop() {
  if(WiFi.status() != WL_CONNECTED){
     Wifi_connect();
     Serial.println("[ WiFi Reconnected ]");
     linSpace();
  }
  
  if(digitalRead(TOUCH) == 1){ //clicked
    if(count == 0){
      count = 1;
      ledOn();
      Serial.println("[                    ]");
      linSpace();
      digitalWrite(RELLAY,HIGH);
      servoOpen();
     
    }
    else if(count == 1){
      count = 0;
      ledOff();
      servoClose(); 
      digitalWrite(RELLAY,LOW);
      
      lcd.setCursor(0, 1);
      
      lcd.print("Progress : ");
      lcd.setCursor(11, 1);
      
      for(int i = 0; i <= 100; i++){
        send_data(i);
        lcd.print(String(i)+"%");
        delay(100);
        lcd.setCursor(11,1);
        lcd.print("     ");
        lcd.setCursor(11,1);
        
        //if(i < 10)
        //  Serial.println("[---------"+String(i)+"----------]");
        //else if(i < 100)
        //  Serial.println("[--------"+String(i)+"----------]");
        //else
        //  Serial.println("[--------"+String(i)+"---------]");
        //linSpace();
        //delay(50);
      }
      lcd.print("Done");
      digitalWrite(RELLAY,HIGH);
      delay(700);
      digitalWrite(RELLAY,LOW);
      delay(700);
      digitalWrite(RELLAY,HIGH);
      delay(700);
      digitalWrite(RELLAY,LOW);
      delay(700);
      digitalWrite(RELLAY,HIGH);
      delay(700);
      //Serial.println("[--------Done--------]");
      //linSpace();
    }
  }

  
}

void send_data(int count) {
  Serial.printf("count = %d\n", count);
  http.begin(client, "http://ec2-3-34-140-140.ap-northeast-2.compute.amazonaws.com/set?status="+String(count));
  http.setTimeout(1000);
  int httpCode = http.GET();
 
  if(httpCode > 0) {
    Serial.printf("GET code : %d\n\n", httpCode);
    
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } 
  else {
    Serial.printf("GET failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
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

    servo.write(160);
    delay(2000);

}

void servoClose(){
  servo.write(0);
  for(int i = 160; i >= 0; i){
    servo.write(i);
    i -= 5;
    delay(10);
  }
}

void Wifi_connect() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    }
 }

void linSpace(){
          for(int i = 0; i <= 20; i++){
          Serial.println(" ");
        } 
}
