#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
}

void loop() {

  // 0 → 180
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(10);
  }

  delay(500);

  // 180 → 0
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(10);
  }

  delay(500);
}