// POE Lab 3 - A Line Following Robot

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define leftSensor A5 // Left IR sensor
#define rightSensor A4 // Right IR sensor

byte input[256];
int leftValue;
int rightValue;

Adafruit_MotorShield ms = Adafruit_MotorShield();
Adafruit_DCMotor *m1 = ms.getMotor(1); // leftMotor
Adafruit_DCMotor *m2 = ms.getMotor(2); // rightMotor
volatile int mainSpeed = 100;
volatile int diffSpeed = 30;
volatile int irThreshhold = 950;

void setup() {
  // put your setup code here, to run once:
  ms.begin();
  m1->setSpeed(mainSpeed);
  m2->setSpeed(mainSpeed);
  m1->run(FORWARD);
  m2->run(FORWARD);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // read irSensor valye
  irSensorRead();

  if(leftValue < irThreshhold){
    m1->setSpeed(mainSpeed);
    m2->setSpeed(mainSpeed - diffSpeed);
  }
  else if(rightValue > irThreshhold){
    m1->setSpeed(mainSpeed - diffSpeed);
    m2->setSpeed(mainSpeed);
  }
  else{
    m1->setSpeed(mainSpeed);
    m2->setSpeed(mainSpeed);
  }
}

void irSensorRead()
{
  // irSensorRead reads the sensor 5 times and returns the average
  leftValue = 0;
  rightValue = 0;

  // read from the irSensors 5 times
  for (int i = 0; i < 5; i++)
  {
    leftValue += analogRead(leftSensor);
    rightValue += analogRead(rightSensor);
  }

  // divide the value of irValue by 5 to find the average
  leftValue = leftValue/5;
  rightValue = rightValue/5;
}

void serialEvent(){
  /*
   * This function reads bytes from serial at the end of each
   * loop if there are bytes to read
   */
  Serial.readBytes(input, 4); // read 4 bytes from serial
  mainSpeed = int(input[0]); // The values for the left motor should be between 0 - 255 (size of byte)
  diffSpeed = int(input[1]); // The values for the right motor should be between 0 - 255
  irThreshhold = int(input[2]*256+input[3]); // The values for the threshhold can be between 0 - 1023 so there need to be 2 bytes
}

