#include <SoftwareSerial.h>

const String PHONE = "+919160620854";

#define rxPin 2
#define txPin 3
SoftwareSerial sim800(rxPin, txPin);

int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;
int ldrpin = A2;
int pirpin = 4;
int ir1pin = 9;
int ir2pin = 8;
int ir3pin = 7;
int ir4pin = 6;
int pirstat = 0;
int ir1stat = 0;
int ir2stat = 0;
int ir3stat = 0;
int ir4stat = 0;
unsigned long ir1_timer = 0;
unsigned long ir2_timer = 0;
unsigned long ir3_timer = 0;
unsigned long ir4_timer = 0;
void setup() {
  pinMode(ir1pin, INPUT_PULLUP);
  pinMode(ir2pin, INPUT_PULLUP);
  pinMode(ir3pin, INPUT_PULLUP);
  pinMode(ir4pin, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(pirpin, INPUT);
  pinMode(ldrpin, INPUT);
  Serial.begin(9600);
   sim800.begin(9600);
  delay(2000);
}

void loop() {
  int ldrpinStatus = analogRead(ldrpin); // Read LDR output value
  Serial.println(ldrpinStatus);
  delay(1);

  if (ldrpinStatus <1000) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    Serial.println("Good Morning");

     sim800.println("AT+CMGF= Good Morning");
    
    sim800.println("AT+CMGS=\"+PHONE+\"");
    
    sim800.print("the system is activted");
   
    sim800.write(30);
  }
  else {
    
   
    
    pirstat = digitalRead(pirpin);
    if (pirstat == HIGH) {
      digitalWrite(led1, HIGH);
      delay(100);
      digitalWrite(led2, HIGH);
      delay(200);
      digitalWrite(led3, HIGH);
      delay(300);
      digitalWrite(led4, HIGH);
      delay(400);
      
      digitalWrite(led1, LOW);
      delay(1000);
      digitalWrite(led2, LOW);
      delay(1200);
      digitalWrite(led3, LOW);
      delay(1400);
      digitalWrite(led4, LOW);
      delay(1600);

      Serial.println("Motion Detected");
    }
    else {
      ir1stat = digitalRead(ir1pin);
      if (ir1stat == LOW) {
        digitalWrite(led1, HIGH);
        if (ir1_timer == 0) {
          ir1_timer = millis();
        }
        if ((millis() - ir1_timer) > 20000) {
          Serial.println("Object Detected by IR1!");
          sim800.println("ATD" + PHONE + ";");
          delay(20000);
        }
        
      } else {
        digitalWrite(led1, LOW);
        ir1_timer = 0;
      }
      
      ir2stat = digitalRead(ir2pin);
      if (ir2stat == LOW) {
        digitalWrite(led2, HIGH);
        if (ir2_timer == 0) {
          ir2_timer = millis();
        }
        if ((millis() - ir2_timer) > 20000) {
          Serial.println("Object Detected by IR2!");
          sim800.println("ATD" + PHONE + ";");
          delay(20000);
        }
        
      } else {
        digitalWrite(led2, LOW);
        ir2_timer = 0;
      }
      
      ir3stat = digitalRead(ir3pin);
      if (ir3stat == LOW) {
        digitalWrite(led3, HIGH);
        if (ir3_timer == 0) {
          ir3_timer = millis();
        }
        if ((millis() - ir3_timer) > 20000) {
          Serial.println("Object Detected by IR3!");
          sim800.println("ATD" + PHONE + ";");
          delay(20000);
        }
        
      } else {
        digitalWrite(led3, LOW);
        ir3_timer = 0;
      }
      
      ir4stat = digitalRead(ir4pin);
      if (ir4stat == LOW) {
        digitalWrite(led4, HIGH);
        if (ir4_timer == 0) {
          ir4_timer = millis();
        }
        if ((millis() - ir4_timer) > 20000) {
          Serial.println("Object Detected by IR4!");
          sim800.println("ATD" + PHONE + ";");
          delay(20000);
        }
        
      } else {
        
        digitalWrite(led4, LOW);
        ir4_timer = 0;
      }
    }
  }
}
