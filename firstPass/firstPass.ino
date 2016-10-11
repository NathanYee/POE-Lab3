// POE Lab 3 - A Line Following Robot

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define sensor1 A0 // Left IR sensor
#define sensor2 A1 // Right IR sensor

byte input[256];
int irVal1;
int irVal2;
int ir_threshold = 950;

Adafruit_MotorShield ms = Adafruit_MotorShield();
Adafruit_DCMotor *m1 = ms.getMotor(1);
Adafruit_DCMotor *m2 = ms.getMotor(2);
int m1_speed = 100;
int m2_speed = 100;

void setup() {
  // put your setup code here, to run once:
  ms.begin();
  m1->setSpeed(m1_speed);
  m2->setSpeed(m2_speed);
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // read irSensor valye
  irSensorRead();

  /*
   * FORWARD, BACKWARD, RELEASE
   * m1->run(FORWARD);
   * m2->run(FORWARD);
   */
  
  // print sensor vals
  Serial.println(irVal1);
  Serial.println(irVal2);
}

void irSensorRead()
{
  // irSensorRead reads the sensor 5 times and returns the average
  irVal1 = 0;
  irVal2 = 0;

  // read from the irSensor 5 times
  for (int i = 0; i < 5; i++)
  {
    irVal1 += analogRead(sensor1);
    irVal2 += analogRead(sensor2);
  }

  // divide the value of irValue by 5 to find the average
  irVal1 = irVal1/5;
  irVal2 = irVal2/5;
}

void serialEvent(){
  // read 1 byte from serial
  Serial.readBytes(input, 1);
  ir_threshold = input[0];
}

