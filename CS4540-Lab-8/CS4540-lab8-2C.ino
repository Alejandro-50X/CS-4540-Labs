#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
}

void loop() {

  myServo.write(180);
  delay(150);  // very short

  myServo.write(0);
  delay(150);
}