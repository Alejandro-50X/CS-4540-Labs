#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET  -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



// pins for the button and led
const int BTN_DOT = 2;
const int BTN_DASH = 3;
const int BTN_SLASH = 4;
const int BTN_CLEAR = 5;

// svaes the previous button states
// in this case High means not pressed and low means pressed, using active low
bool lastDot = HIGH;
bool lastDash = HIGH;
bool lastSlash = HIGH;
bool lastClear = HIGH;



// message accumulator
// stores dot, dash, and slash and keeps building up everytime we press
String message = "";

void setup() {
  // the inputs are the four buttoins that are set up
  pinMode(BTN_DOT, INPUT);
  pinMode(BTN_DASH, INPUT);
  pinMode(BTN_SLASH, INPUT);
  pinMode(BTN_CLEAR, INPUT);

 // it will generate the display voltage iternally instead of trying to handle it manually
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay(); //clears the display
  display.setTextSize(2); // text size
  display.setTextColor(WHITE); //text color
  display.setCursor(0, 0); // where the text will start being written
  display.println("Firing up!");
  display.display();
  delay(1500);  // show ready message for 1.5 seconds
}

void loop() {
  bool currentDot = digitalRead(BTN_DOT); // reads wheter it pressed or not
  bool currentDash = digitalRead(BTN_DASH); 
  bool currentSlash = digitalRead(BTN_SLASH); // slashes are supposed to rpresent spaces
  bool currentClear = digitalRead(BTN_CLEAR);

  // dot button which will trigger when it goes from high to low
  if (currentDot == LOW && lastDot == HIGH) {

    delay(20); // debounce to prevent multiple dots from appear in one press
    message += ".";
    delay(100); // delay was originally try to be the debounce but didn't work 
    showMessage(message);
    lastDot = HIGH; // for the debounce
    //fixed the debounce with the other buttons
  }

  // dash button which also triggers from high to low 
  // currentdash equaling low means that its being pressed right now and if the last is high that means it wasn't pressed 
  // so going fromn high to low
  if (currentDash == LOW && lastDash == HIGH) { 
    
    delay(20); // a 20 ms delay to try to prevent debounce but it can still happen if pressed rapidly multiple time
              // it creates a delay in whats being displayed on the screen
    message += "-";
    delay(100);
    showMessage(message);
  }

  // slash button which triggers from high to low
  if (currentSlash == LOW && lastSlash == HIGH) {
    
    delay(20); 
    message += "/";
    showMessage(message);
  }

  // when pressed this will clear the message of what we have added so far
  if (currentClear == LOW && lastClear == HIGH){
    
    delay(20);
    message = "";
    showMessage(message);
  }

  // if message gets longer than 40 characters then it will automatically be cleared 
  if (message.length() > 30) {
    message = "";
    showMessage(message);
  }

  // whats happening rignt now becomes the past whter you're pressing something or not
  //so current button reads from btn dot and after that last dot is set to currentdot
  lastDot = currentDot;
  lastDash = currentDash;
  lastSlash = currentSlash;
  lastClear = currentClear;
}

void showMessage(String msg) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Morse:");
  display.println(msg);
  display.display();
}