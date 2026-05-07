// the pins in an array
const int LED_PINS[] = {2, 3, 4, 5, 6};
const int NUM_LEDS  = 5;
const int SW_UP_PIN = 9;  // count up
const int SW_DOWN_PIN = 10; // count down
const int SW_RESET_PIN = 11; // reset to 0

const int MAX_COUNT = 31;  // 5 bits = 0 to 31

// counter
int count = 0;

// debounce
const long DEBOUNCE_DELAY = 50;
bool lastSwUpState = HIGH;
bool lastSwDownState = HIGH;
bool lastSwResetState = HIGH;
unsigned long swUpDebounce = 0;
unsigned long swDownDebounce = 0;
unsigned long swResetDebounce = 0;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(SW_UP_PIN,    INPUT);
  pinMode(SW_DOWN_PIN,  INPUT);
  pinMode(SW_RESET_PIN, INPUT);

  displayCount(count);
}

// display the binary value of count across the LEDs
void displayCount(int value) {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], (value >> i) & 1 ? HIGH : LOW);
  }
}

void loop() {
  unsigned long now = millis();

  bool swUpState    = digitalRead(SW_UP_PIN);
  bool swDownState  = digitalRead(SW_DOWN_PIN);
  bool swResetState = digitalRead(SW_RESET_PIN);

  // for the switch that goes up once it reaches 31 it go back to zero
  if (lastSwUpState == HIGH && swUpState == LOW &&
      (now - swUpDebounce > DEBOUNCE_DELAY)) {
    swUpDebounce = now;

    count = (count >= MAX_COUNT) ? 0 : count + 1;
    displayCount(count);
  }
  lastSwUpState = swUpState;

  // switch down if it reaches zero it will go to 31
  if (lastSwDownState == HIGH && swDownState == LOW &&
      (now - swDownDebounce > DEBOUNCE_DELAY)) {
    swDownDebounce = now;

    count = (count <= 0) ? MAX_COUNT : count - 1;
    displayCount(count);
  }
  lastSwDownState = swDownState;

  // resets the count back to zero
  if (lastSwResetState == HIGH && swResetState == LOW &&
      (now - swResetDebounce > DEBOUNCE_DELAY)) {
    swResetDebounce = now;

    count = 0;
    displayCount(count);
  }
  lastSwResetState = swResetState;
}