const int trigPin = 8;
const int echoPin = 9;

const int leds[]  = {2, 3, 4, 5, 6};
const int numLeds = 5;

// distance thresholds in cm for each LED
// LED 1 (pin2) on at 4cm, LED 2 at 8cm, LED 3 at 12cm, LED 4 at 16cm, LED 5 at 20cm
const int thresholds[] = {4, 8, 12, 16, 20};

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration / 29 / 2;
}

void loop() {
  long cm = getDistanceCM();

  // light up LEDs based on distance thresholds
  for (int i = 0; i < numLeds; i++) {
    if (cm >= thresholds[i]) {
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    }
  }

  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println("cm");

  delay(100);
}