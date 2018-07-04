#include <Servo.h>

#define xPin A1
#define yPin A0

Servo servoLR;
Servo servoUD;
int LRpos = 90;
int UDpos = 90;

int xPosition = 0;
int yPosition = 0;

void setup() {
  Serial.begin(9600);
  servoLR.attach(9);
  servoUD.attach(10);

  pinMode(yPin, INPUT);
  pinMode(xPin, INPUT);
}

void loop() {
  int UDposTemp = map(analogRead(xPin), 0, 1023, 170, 10);
  int LRposTemp = map(analogRead(yPin), 0, 1023, 10, 170);
  
  if (UDposTemp != UDpos){
    UDpos = UDposTemp;
    Serial.print("UD: ");
    Serial.println(UDpos);
    servoUD.write(UDpos);
  }

  if (LRposTemp != LRpos){
    LRpos = LRposTemp;
    Serial.print("LR: ");
    Serial.println(LRpos);
    servoLR.write(LRpos);
  }

  delay(100);
}
