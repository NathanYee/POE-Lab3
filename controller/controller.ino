void loop() {
  // read irSensor values
  irSensorRead();

  if(leftValue > irThreshhold){
    // If the left sensor hits the tape, turn off the right motor
    m1->setSpeed(mainSpeed);
    m2->setSpeed(mainSpeed - diffSpeed);
    Serial.println(mainSpeed);
    Serial.println(mainSpeed - diffSpeed);
  }
  else if(rightValue > irThreshhold){
    // If the right sensor hits the tape, turn off the left motor
    m1->setSpeed(mainSpeed - diffSpeed);
    m2->setSpeed(mainSpeed);
    Serial.println(mainSpeed - diffSpeed);
    Serial.println(mainSpeed);
  }
  else{
    // Charge forward!
    m1->setSpeed(mainSpeed);
    m2->setSpeed(mainSpeed);
    Serial.println(mainSpeed);
    Serial.println(mainSpeed);
  }
  
}
