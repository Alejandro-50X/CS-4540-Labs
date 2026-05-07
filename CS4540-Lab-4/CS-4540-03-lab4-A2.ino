const int buttonPin = 10;
const int ledPinNum = 13;

int buttonState = 0;
int lastButtonState = 0;
int pressCount = 0;
int releaseCount = 0;

void setup() {
  pinMode(ledPinNum, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println(" Switch Bounce Counter Started ");
  Serial.println("Press the button to begin...");
  Serial.println("-------------------------------------");
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // if the button state has changed then run it if not then don't do anything
  if (buttonState != lastButtonState) {

    // the switch has just been pressed
    if (buttonState == HIGH) {
      
      pressCount++;
      digitalWrite(ledPinNum, HIGH);
      Serial.print("Pin 10 Status: HIGH  | Button PRESSED  | Press count: ");
      Serial.println(pressCount);

    } else {
      // the switch has just been released
      releaseCount++;
      digitalWrite(ledPinNum, LOW);
      Serial.print("Pin 10 Status: LOW   | Button RELEASED | Release count: ");
      Serial.println(releaseCount);
    }

    // update the button state for the next time it runs
    lastButtonState = buttonState;
  }
}