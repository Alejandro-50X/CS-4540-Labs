// rotary encoder pins
#define inputCLK 10
#define inputDT   9
#define inputSW   8   // encoder push button which connects to ground when pressed

// leds in sequence order which is left to right visually
const int leds[]  = {2, 3, 4, 5, 6};
const int numLeds = 5;

// sequencer state
int  currentLed  = 2;  // start on middle LED which is pin 4 at index 2
bool goingRight  = true;    // current chase direction

//acceleration state
float velocity      = 0.0;// steps per second — negative = left, positive = right
float acceleration  = 0.5; // how much each encoder tick adds to velocity
long  lastStepTime  = 0; // micros of last led step
long  stepInterval  = 0;// microseconds between the led steps

// encoder state
int  currentStateCLK;
int  previousStateCLK;
bool lastSWState    = HIGH;


// convert velocity to a step interval in microseconds.
// velocity is in "LED steps per second". Zero or near-zero = stopped.
long velocityToInterval(float vel) {
  float absVel = abs(vel);
  if (absVel < 0.05) return 0;          // effectively stopped
  return (long)(1000000.0 / absVel);    // microseconds per step
}

void lightOnlyIndex(int idx) {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], i == idx ? HIGH : LOW);
  }
}

void setup() {
  pinMode(inputCLK, INPUT);
  pinMode(inputDT,  INPUT);
  pinMode(inputSW,  INPUT_PULLUP);   // pressed = LOW

  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }

  Serial.begin(9600);

  previousStateCLK = digitalRead(inputCLK);

  // start with middle LED lit, everything stopped
  lightOnlyIndex(currentLed);
  lastStepTime = micros();
}

void loop() {

  //Read encoder rotation
  currentStateCLK = digitalRead(inputCLK);

  if (currentStateCLK != previousStateCLK) {
    if (digitalRead(inputDT) != currentStateCLK) {
      // CCW tick which accelerate left which means it decreases velocity
      velocity -= acceleration;
    } else {
      // CW tick accelerate right which increase velocity
      velocity += acceleration;
    }

    // clamp velocity so it doesn't grow forever
    velocity = constrain(velocity, -20.0, 20.0);

    stepInterval = velocityToInterval(velocity);

    Serial.print("Velocity: ");
    Serial.print(velocity);
    Serial.print("  Interval(us): ");
    Serial.println(stepInterval);
  }
  previousStateCLK = currentStateCLK;

  // read encoder button — reset to center / stopped 
  bool swState = digitalRead(inputSW);
  if (swState == LOW && lastSWState == HIGH) {   // fresh press
    velocity = 0.0;
    stepInterval = 0;
    currentLed = 2;  // back to middle (pin 4)
    lightOnlyIndex(currentLed);
    Serial.println("RESET");
  }
  lastSWState = swState;

  //advance sequencer based on current velocity
  if (stepInterval > 0) {
    long now = micros();
    if (now - lastStepTime >= stepInterval) {
      lastStepTime = now;

      // determine direction from sign of velocity
      int dir = (velocity > 0) ? 1 : -1;
      int next = currentLed + dir;

      // bounce off the ends — reverse velocity direction
      if (next < 0 || next >= numLeds) {
        velocity = -velocity; // reverse
        stepInterval = velocityToInterval(velocity);
        next = currentLed + (velocity > 0 ? 1 : -1);
        next = constrain(next, 0, numLeds - 1);
      }

      currentLed = next;
      lightOnlyIndex(currentLed);
    }
  }
}