// rotary encoder pins
#define inputCLK 10
#define inputDT 9
#define inputSW  8 // push to reset brightness to 0

// on a pwm pin
#define ledPin 5

// Brightness state
int brightness = 0; // 0-255
int stepSize = 5; // how much each encoder tick changes brightness

// encoder state
int  currentStateCLK;
int  previousStateCLK;
bool lastSWState = HIGH;

void setup() {
  pinMode(inputCLK, INPUT);
  pinMode(inputDT,  INPUT);
  pinMode(inputSW,  INPUT_PULLUP);
  pinMode(ledPin,   OUTPUT);

  Serial.begin(9600);
  previousStateCLK = digitalRead(inputCLK);

  analogWrite(ledPin, brightness);
}

void loop() {

  currentStateCLK = digitalRead(inputCLK);

  if (currentStateCLK != previousStateCLK) {

    if (digitalRead(inputDT) != currentStateCLK) {
      // CCW decrease brightness
      brightness -= stepSize;
    } else {
      // CW increase brightness
      brightness += stepSize;
    }

    // clamp between fully off and fully on
    brightness = constrain(brightness, 0, 255);

    // apply brightness to LED
    analogWrite(ledPin, brightness);

    Serial.print("Brightness: ");
    Serial.println(brightness);
  }
  previousStateCLK = currentStateCLK;

  //push button to reset brightness to off 
  bool swState = digitalRead(inputSW);
  if (swState == LOW && lastSWState == HIGH) {
    brightness = 0;
    analogWrite(ledPin, 0);
    Serial.println("RESET — brightness off");
  }
  lastSWState = swState;
}