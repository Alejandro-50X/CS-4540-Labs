int red = 9;
int yellow = 8;
int green = 7;

void setup(){
  
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green,  OUTPUT);
  
}
void loop(){

   digitalWrite(green, HIGH);
  delay(15000);
  digitalWrite(green,  LOW);
    
    digitalWrite(yellow, HIGH);
  delay(5000);
    digitalWrite(yellow,  LOW);

    digitalWrite(red, HIGH);
  delay(15000);
    digitalWrite(red,  LOW);
  
}