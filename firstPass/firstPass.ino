// POE Lab 3 - A Line Following Robot

const int irSensor = 0; // ir sensor pin
byte input[256];
int irValue;
int ir_threshold = 950;

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
  Serial.println(ir_threshold);
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

  irValue = irValue/5;
}

void serialEvent(){
  // read 1 byte from serial
  Serial.readBytes(input, 1);
  ir_threshold = input[0];
}

