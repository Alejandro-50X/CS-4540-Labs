// the pins the led and switches are connected to
const int LED1_PIN   = 6;   
const int SWITCH1_PIN = 10;  // switch for brightness up
const int SWITCH2_PIN = 8;   // for brightness down

// brightness settings
int brightnessLevel       = 0;    // starts at 0
const int BRIGHTNESS_STEP = 25;   // a 10% increase per press

// tracks for rapid press
const int  RAPID_PRESS_TARGET = 10;
const long RAPID_PRESS_GAP    = 600;

// keeps track of switch 1
bool lastSw1State          = HIGH;
int  sw1PressCount         = 0;
unsigned long sw1LastPress = 0;

// keeps track of switch 2
bool lastSw2State          = HIGH;
int  sw2PressCount         = 0;
unsigned long sw2LastPress = 0;

// debounce delay so there is no multiple presses for just one press
const long DEBOUNCE_DELAY    = 50;
unsigned long sw1DebounceTime = 0;
unsigned long sw2DebounceTime = 0;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(SWITCH1_PIN, INPUT);
  pinMode(SWITCH2_PIN, INPUT);

  analogWrite(LED1_PIN, brightnessLevel); // the brightness level starts at 0
}

void loop() {
  unsigned long now = millis(); // captures current time 
  bool sw1State = digitalRead(SWITCH1_PIN); // for the switch states high means off and low means on or preswsed
  bool sw2State = digitalRead(SWITCH2_PIN);

  // for switch 1 to keep brightness up
  // checking if the switch was unpressed and if it is now being pressed and that there was a delay since the last press
  if (lastSw1State == HIGH && sw1State == LOW && (now - sw1DebounceTime > DEBOUNCE_DELAY)) {
    sw1DebounceTime = now;

    // chechks if presses have been in the 600 ms time gap and if so add it to sw1presscount but if not then it will be treated as a reguler press
    if (now - sw1LastPress <= RAPID_PRESS_GAP) {
      sw1PressCount++;
    } else {
      sw1PressCount = 1;
    }
    sw1LastPress = now;

    //if we rapidly press 10 times it goes to maximum brightness otherwise we just increment by ten percent 
    if (sw1PressCount >= RAPID_PRESS_TARGET) {
      brightnessLevel = 255;  goes to max brightness
      sw1PressCount   = 0;
    } else {
      brightnessLevel = min(255, brightnessLevel + BRIGHTNESS_STEP);
    }

    analogWrite(LED1_PIN, brightnessLevel);
  }
  lastSw1State = sw1State;

  // for switch 2 to keep brightness down
  if (lastSw2State == HIGH && sw2State == LOW && (now - sw2DebounceTime > DEBOUNCE_DELAY)) {
    sw2DebounceTime = now;

    if (now - sw2LastPress <= RAPID_PRESS_GAP) {
      sw2PressCount++;
    } else {
      sw2PressCount = 1;
    }
    sw2LastPress = now;

    if (sw2PressCount >= RAPID_PRESS_TARGET) {
      brightnessLevel = 0;    // go to 0 which is off
      sw2PressCount   = 0;
    } else {
      brightnessLevel = max(0, brightnessLevel - BRIGHTNESS_STEP);
    }

    analogWrite(LED1_PIN, brightnessLevel);
  }
  lastSw2State = sw2State;
}