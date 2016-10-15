// POE Lab 3 - A Line Following Robot

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define leftSensor A2 // Left IR sensor
#define rightSensor A3 // Right IR sensor

byte input[256]; // Serial input buffer
volatile int leftValue = 0; // Left IR Value
volatile int rightValue = 0; // Right IR Value

Adafruit_MotorShield ms = Adafruit_MotorShield();
Adafruit_DCMotor *m1 = ms.getMotor(1); // leftMotor
Adafruit_DCMotor *m2 = ms.getMotor(2); // rightMotor
volatile int mainSpeed = 40; // The main speed for the motors
volatile int diffSpeed = 40; // The difference in speed based on the irThreshhold
volatile int irThreshhold = 800; // The threshhold for the floor vs the black tape

void setup(){
  ms.begin(); // Begins the motorshield
  m1->setSpeed(mainSpeed); // Sets the main speed for both of the motors
  m2->setSpeed(mainSpeed);
  m1->run(FORWARD); // Sets both of the motors to go forward
  m2->run(FORWARD);
  Serial.begin(9600); // Begins serial communication
}

void loop() {
  // read irSensor values
  irSensorRead();

  if(leftValue > irThreshhold){
    // If the left sensor hits the tape, turn off the right motor
    m1->setSpeed(mainSpeed);
    m2->setSpeed(mainSpeed - diffSpeed);
    Serial.print(mainSpeed);
    Serial.print(mainSpeed - diffSpeed);
  }
  else if(rightValue > irThreshhold){
    // If the right sensor hits the tape, turn off the left motor
    m1->setSpeed(mainSpeed - diffSpeed);
    m2->setSpeed(mainSpeed);
    Serial.print(mainSpeed - diffSpeed);
    Serial.print(mainSpeed);
  }
  else{
    // Charge forward!
    m1->setSpeed(mainSpeed);
    m2->setSpeed(mainSpeed);
    Serial.print(mainSpeed);
    Serial.print(mainSpeed);
  }
  
}

void irSensorRead()
{
  /*
   * irSensorRead reads the sensor 5 times and returns the average
   */

  // Reset the values
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

  Serial.print(leftValue);
  Serial.println(rightValue);
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

