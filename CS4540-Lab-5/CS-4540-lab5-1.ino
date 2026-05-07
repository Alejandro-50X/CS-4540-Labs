// the pins for leds and the switch
const int LED1_PIN = 6;   // this is the blinking led
const int LED2_PIN = 4;   // this will be controlled 
const int SWITCH_PIN = 10; // Push switch

// the timing variables for the led
unsigned long previousMillis = 0;
const long INTERVAL = 1000; // 1 second interval
bool led1State = LOW;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  // the led on pin will blink on and off for 1 sec intervals
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
    led1State = !led1State; // toggles between the led satats
    digitalWrite(LED1_PIN, led1State);
  }

  // sees if the switch is pressed 
  int switchState = digitalRead(SWITCH_PIN);

  if (switchState == HIGH) {
    digitalWrite(LED2_PIN, HIGH); // if switch is pressed led is on
  } else {
    digitalWrite(LED2_PIN, LOW);  // if switch is not pressed led is off
  }
}