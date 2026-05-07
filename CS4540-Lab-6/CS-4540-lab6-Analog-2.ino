// potentiometer and LED pins
#define potPin  A3   // analog input
#define ledPin  6    // must be a PWM pin for analog usage

int potValue    = 0;   // raw reading  0–1023
int brightness  = 0;   // mapped value 0–255

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the potentiometer to see if its fully left or fully right
  potValue = analogRead(potPin);

  // map the 0–1023 range to 0–255 for analogWrite
  brightness = map(potValue, 0, 1023, 0, 255);

  // apply brightness to LED
  analogWrite(ledPin, brightness);

  // print both values so you can monitor in serial
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Brightness: ");
  Serial.print(map(potValue, 0, 1023, 0, 100));  // show as 0-100%
  Serial.println("%");

  delay(50);   // small delay to smooth out serial output
}