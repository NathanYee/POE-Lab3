// POE Lab 3 - Reading both of the sensors to see the difference between the floor and black tape

#define leftSensor A5 // Left IR sensor
#define rightSensor A4 // Right IR sensor
volatile int leftValue = 0;
volatile int rightValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // read irSensor value
  irSensorRead();  
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

  Serial.print(leftValue);
  Serial.println(rightValue);
}
