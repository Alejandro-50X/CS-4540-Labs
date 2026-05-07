// rotary encoder inputs
#define inputCLK 10
#define inputDT 9

// led outputs in order from counterclockwise end to clockwise end
// turning clockwise moves the lit led from pin 6 toward pin 2
// turning counterclockwise moves the lit led from pin 2 toward pin 6
const int leds[] = {6, 5, 4, 3, 2};  // index 0=CCW end, index 4=CW end
const int numLeds = 5;

int ledIndex = 2;  // start in the middle (pin 4)
int currentStateCLK;
int previousStateCLK;
String encdir = "";

void setup() {
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);

  // set all led pins as outputs
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }

  Serial.begin(9600);
  previousStateCLK = digitalRead(inputCLK);

  // light up the starting led
  digitalWrite(leds[ledIndex], HIGH);
}

void loop() {
  currentStateCLK = digitalRead(inputCLK);

  if (currentStateCLK != previousStateCLK) {

    if (digitalRead(inputDT) != currentStateCLK) {
      // rotating counterclockwise
      // moves the index towrd zero which is pin 6 and stops it once it reaches there
      if (ledIndex > 0) {
        ledIndex--;
      }
      encdir = "CCW";

    } else {
      // rotating clockwise toward pin 2 and stops it there
      if (ledIndex < numLeds - 1) {
        ledIndex++;
      }
      encdir = "CW";
    }

    // turn off all leds then light only the current one
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], LOW);
    }
    digitalWrite(leds[ledIndex], HIGH);

    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" -- LED Index: ");
    Serial.print(ledIndex);
    Serial.print(" -- Pin: ");
    Serial.println(leds[ledIndex]);
  }

  previousStateCLK = currentStateCLK;
}