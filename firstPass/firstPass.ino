// POE Lab 3 - A Line Following Robot

const int irSensor = 0; // ir sensor pin
int irValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // read irSensor valye
  irSensorRead();
  
  // print serial value
  Serial.println(irValue);
}

void irSensorRead()
{
  // irSensorRead reads the sensor 5 times and returns the average

  // reset value of irValue
  irValue = 0;

  // read from the irSensor 5 times
  for (int i = 0; i < 5; i++)
  {
    irValue += analogRead(irSensor);
  }

  // divide the value of irValue by 5 to find the average

  irValue = irValue / 5;
}
