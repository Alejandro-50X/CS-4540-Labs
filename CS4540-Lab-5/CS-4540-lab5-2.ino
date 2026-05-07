// pin numbers for the led and switch
const int LED1_PIN = 6;
const int LED2_PIN = 4;
const int SWITCH_PIN = 10;

const long BLINK_INTERVAL = 1000;
const long SHORT_PRESS_MAX = 400;   // under 400ms = short press
const long LONG_PRESS_MIN  = 800;   // over 800ms = long press
const long DOUBLE_PRESS_GAP = 400;   // max time gap between two clicks for double press
const long DISCO_INTERVAL = 150;   // disco blink speed

// different behavior modes
enum Mode { NORMAL, STOPLIGHT, DISCO, ALL_OFF };
Mode currentMode = NORMAL;

// led 1 blink 
unsigned long previousMillis1 = 0;
bool led1State = HIGH;

// disco mode
unsigned long discoMillis = 0;
bool discoState = HIGH;

// keeps track of the button state
bool lastButtonState = HIGH;
bool buttonState = HIGH;
unsigned long pressStart  = 0;
unsigned long lastReleaseTime = 0;
bool waitingForDouble = false;
unsigned long pendingAction = 0;   // timestamp of first click release
bool longPressHandled = false;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);

  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
}

// handles the different modes

void runNormal(unsigned long now) {
  // led 1 will blink on anf off for one second
  if (now - previousMillis1 >= BLINK_INTERVAL) {
    previousMillis1 = now;
    led1State = !led1State;
    digitalWrite(LED1_PIN, led1State);
  }
  // in normal mode led 2 will be off
  digitalWrite(LED2_PIN, LOW);
}

void runStoplight(unsigned long now) {
  // LED 1 stays ON, LED 2 stays ON (like a red/green stoplight pair)
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
}

void runDisco(unsigned long now) {
  // Both LEDs blink rapidly, alternating
  if (now - discoMillis >= DISCO_INTERVAL) {
    discoMillis = now;
    discoState = !discoState;
    digitalWrite(LED1_PIN, discoState);
    digitalWrite(LED2_PIN, !discoState); // opposite = alternating
  }
}

void runAllOff() {
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
}

// the button logic

void handleButton(unsigned long now) {
  buttonState = digitalRead(SWITCH_PIN);

  //the button was just pressed
  if (lastButtonState == HIGH && buttonState == LOW) {
    pressStart = now;
    longPressHandled = false;
  }

  // checks if they button is prseed and hold
  if (buttonState == LOW && !longPressHandled) {
    if (now - pressStart >= LONG_PRESS_MIN) {
      currentMode = ALL_OFF;
      longPressHandled = true;
      waitingForDouble = false; // cancel any pending double
    }
  }

  // the button was just released
  if (lastButtonState == LOW && buttonState == HIGH) {
    unsigned long pressDuration = now - pressStart;

    if (!longPressHandled && pressDuration < SHORT_PRESS_MAX) {
      // short press detected
      if (waitingForDouble && (now - pendingAction <= DOUBLE_PRESS_GAP)) {
        // confirms for double press
        currentMode = DISCO;
        waitingForDouble = false;
      } else {
        // first click and waits to see if there will be a second click
        waitingForDouble = true;
        pendingAction = now;
      }
    }
    lastReleaseTime = now;
  }

  // if you don't double press fast enough its treated as a single press
  if (waitingForDouble && (now - pendingAction > DOUBLE_PRESS_GAP)) {
    currentMode = STOPLIGHT;
    waitingForDouble = false;
  }

  lastButtonState = buttonState;
}

void loop() {
  unsigned long now = millis();

  handleButton(now);

  switch (currentMode) {
    case NORMAL: runNormal(now);   break;
    case STOPLIGHT: runStoplight(now); break;
    case DISCO: runDisco(now);    break;
    case ALL_OFF: runAllOff();      break;
  }
}