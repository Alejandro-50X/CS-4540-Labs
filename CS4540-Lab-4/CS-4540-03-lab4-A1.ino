//sample switch code
const int buttonPin = 10;
const int ledPinNum = 13;
int buttonState = 0;

void setup() {
   pinMode(ledPinNum, OUTPUT);
   pinMode(buttonPin, INPUT);
}
void loop() {
   buttonState = digitalRead(buttonPin);
   if (buttonState == HIGH) {
   digitalWrite(ledPinNum, HIGH);
   } else {
   digitalWrite(ledPinNum, LOW);
   }
}