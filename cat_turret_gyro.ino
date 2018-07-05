// From https://maker.pro/arduino/tutorial/how-to-control-a-servo-with-an-arduino-and-mpu6050
// THANK YOU!!!

#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>   

Servo servoLR;
Servo servoUD;        
MPU6050 sensor ;
int16_t ax, ay, az ;
int16_t gx, gy, gz ;

int16_t lastUDPos;
int16_t lastLRPos;

void setup(){ 
  Wire.begin();
  Serial.begin(9600); 

  servoLR.attach(9);
  servoUD.attach(10);
  
  Serial.println("Initializing the sensor"); 
  sensor.initialize(); 
  Serial.println(sensor.testConnection() ? "Successfully Connected" : "Connection failed"); 
  delay(1000); 
  Serial.println("Taking Values from the sensor");
  delay(1000);
}

void loop(){ 
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = constrain(ax, -14000, 14000); //actual range is 17000, but we dont want to move our hands around that much
  ay = constrain(ay, -14000, 14000);
  int16_t newLRPos = map(ax, -14000, 14000, 10, 170);
  int16_t newUDPos = map(ay, -14000, 14000, 170, 10);
  int16_t actLRPos = (newLRPos * 0.1) + (lastLRPos * 0.9);
  int16_t actUDPos = (newUDPos * 0.1) + (lastUDPos * 0.9);
  lastLRPos = actLRPos;
  lastUDPos = actUDPos;
  servoLR.write(actLRPos); 
  servoUD.write(actUDPos);
  delay(10);
}
