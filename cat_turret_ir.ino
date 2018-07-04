#include <Servo.h>
#include <IRremote.h>

Servo servoLR;
Servo servoUD;
IRrecv irrecv(8);
decode_results results;
unsigned long lastPressed = 0;

int LRpos = 90;
int UDpos = 90;


void setup() {
  Serial.begin(9600);
  servoLR.attach(9);
  servoUD.attach(10);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  int UDposTemp = UDpos;
  int LRposTemp = LRpos;
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        unsigned long pressed = results.value;

        if (pressed == 0xFFFFFFFF){ //if button is held down, repeat
          pressed = lastPressed;
        }
       /* else { // this works great in theory but theres a lot of garbage signals to ignore
          lastPressed = pressed;
        } */
        
        switch(pressed){
          case 0xFF629D:
          lastPressed = 0xFF629D;
          UDposTemp = UDposTemp + 10;
          break;
          case 0xFFA857:
          lastPressed = 0xFFA857;
          UDposTemp = UDposTemp - 10;
          break;
          case 0xFFC23D:
          lastPressed =  0xFFC23D;
          LRposTemp = LRposTemp + 10;
          break;
          case 0xFF22DD:
          lastPressed = 0xFF22DD;
          LRposTemp = LRposTemp - 10;
          break;
        }
        irrecv.resume();
  }
  if (LRposTemp > 170){
    LRposTemp = 170;
  }
  if (UDposTemp > 170){
    UDposTemp = 170;
  }
  if (LRposTemp < 10){
    LRposTemp = 10;
  }
  if (UDposTemp < 10){
    UDposTemp = 10;
  }

  if (UDposTemp != UDpos){
    UDpos = UDposTemp;
    Serial.println(UDpos);
    servoUD.write(UDpos);
  }

  if (LRposTemp != LRpos){
    LRpos = LRposTemp;
    Serial.println(LRpos);
    servoLR.write(LRpos);
  }

  delay(15);
}
