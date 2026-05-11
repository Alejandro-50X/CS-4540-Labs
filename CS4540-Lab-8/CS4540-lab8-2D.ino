#include <Servo.h>

Servo myServo;

const int defaultPos = 90;   // center position

void setup() {
  Serial.begin(9600);
  myServo.attach(9);

  randomSeed(analogRead(0)); // seed randomness

  myServo.write(defaultPos); // start centered
  delay(1000);
}

void loop() {

  // generate random movement between -30 and +30 degrees
  int offset = random(-30, 31);

  int newPos = defaultPos + offset;

  // constrain to valid range
  newPos = constrain(newPos, 0, 180);

  Serial.print("Moving to: ");
  Serial.println(newPos);

  myServo.write(newPos);
  delay(800);

  // return to default
  Serial.println("Returning to default (90)");

  myServo.write(defaultPos);
  delay(1200);

}