// the pins that will be connected to the leds
const int LED_PINS[] = {2, 3, 4, 5, 6};
const int NUM_LEDS = 5; // number of leds
const int SW_RIGHT_PIN = 9; // switch for right accerlation
const int SW_LEFT_PIN = 10;  // for left accleration
const int SW_RESET_PIN = 11;// resets the led to the center

// Speed settings for how fast the light is moving
const long SPEED_MAX = 80; // maximum speed
const long SPEED_MIN = 1000; // our slowest speed
const long SPEED_STEP = 80;  // the difference in how much the switches will change the speed
const long SPEED_STOPPED = 0;  // for no movement

// sequencer state
int  currentLED = 2;  // start at the center led which is pin 4
int  direction = 0; // 0 = stopped, 1 = right, -1 = left
long stepDelay = 0; // current delay between steps 
unsigned long lastStepTime = 0;

// switch debounce
const long DEBOUNCE_DELAY = 50;
bool lastSwRightState = HIGH;
bool lastSwLeftState  = HIGH;
bool lastSwResetState = HIGH;
unsigned long swRightDebounce = 0;
unsigned long swLeftDebounce  = 0;
unsigned long swResetDebounce = 0;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(SW_RIGHT_PIN, INPUT_PULLUP);
  pinMode(SW_LEFT_PIN,  INPUT_PULLUP);
  pinMode(SW_RESET_PIN, INPUT_PULLUP);

  lightLED(currentLED);
}

// turn off all leds then light only the given index
void lightLED(int index) {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  digitalWrite(LED_PINS[index], HIGH);
}

void loop() {
  unsigned long now = millis();

  bool swRightState = digitalRead(SW_RIGHT_PIN);
  bool swLeftState  = digitalRead(SW_LEFT_PIN);
  bool swResetState = digitalRead(SW_RESET_PIN);

  // for the switch to the right 
  // check if this is a proper press
  if (lastSwRightState == HIGH && swRightState == LOW &&
      (now - swRightDebounce > DEBOUNCE_DELAY)) {
    swRightDebounce = now;

    direction = 1;

    if (stepDelay == 0) {
      stepDelay = SPEED_MIN;      // Kick off from stopped
    } else {
      stepDelay = max(SPEED_MAX, stepDelay - SPEED_STEP); // Speed up, cap at max
    }
  }
  lastSwRightState = swRightState;

  // for the switch to the left 
  if (lastSwLeftState == HIGH && swLeftState == LOW &&
      (now - swLeftDebounce > DEBOUNCE_DELAY)) {
    swLeftDebounce = now;

    direction = -1;

    if (stepDelay == 0) {
      stepDelay = SPEED_MIN;   // kick off from stopped
    } else {
      stepDelay = max(SPEED_MAX, stepDelay - SPEED_STEP); // speed up, cap at max
    }
  }
  lastSwLeftState = swLeftState;

  // for the switch reset go back to center and stop moving
  if (lastSwResetState == HIGH && swResetState == LOW &&
      (now - swResetDebounce > DEBOUNCE_DELAY)) {
    swResetDebounce = now;

    currentLED = 2;   // center LED
    direction  = 0;
    stepDelay  = 0;
    lightLED(currentLED);
  }
  lastSwResetState = swResetState;

  // advance the sequencer
  if (direction != 0 && stepDelay > 0 && (now - lastStepTime >= stepDelay)) {
    lastStepTime = now;

    int nextLED = currentLED + direction;

    // reverse the driection when hitting an edge
    if (nextLED < 0) {
      direction = 1;
      nextLED   = 1;
    } else if (nextLED >= NUM_LEDS) {
      direction = -1;
      nextLED   = NUM_LEDS - 2;
    }

    currentLED = nextLED;
    lightLED(currentLED);
  }
}