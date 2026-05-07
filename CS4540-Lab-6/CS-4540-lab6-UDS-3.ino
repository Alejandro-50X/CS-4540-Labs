const int trigPin = 8;
const int echoPin = 9;

const int leds[]  = {2, 3, 4, 5, 6};
const int numLeds = 5;

// distance range
#define MIN_DIST 10    // cm — all LEDs off below this
#define MAX_DIST 100   // cm — all LEDs on at this and above

// thresholds evenly spread between 10cm and 100cm in 18cm steps
// LED 1 on at 10cm, LED 2 at 28cm, LED 3 at 46cm, LED 4 at 64cm, LED 5 at 82cm
const int thresholds[] = {10, 28, 46, 64, 82};

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

  // below minimum all LEDs off
  if (cm < MIN_DIST) {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], LOW);
    }
  }
  // above maximum all LEDs on
  else if (cm >= MAX_DIST) {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }
  // in range light up LEDs based on thresholds
  else {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], cm >= thresholds[i] ? HIGH : LOW);
    }
  }

  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println("cm");

  delay(100);
}