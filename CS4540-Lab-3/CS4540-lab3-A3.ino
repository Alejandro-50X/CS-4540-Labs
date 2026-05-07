
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  //long blink 
  delay(400);                       
  digitalWrite(LED_BUILTIN, LOW); 
  delay(400);                      
  digitalWrite(LED_BUILTIN, HIGH);  //long blink
  delay(400); 
  digitalWrite(LED_BUILTIN, LOW);   
  delay(400);
  digitalWrite(LED_BUILTIN, HIGH);  //long blink
  delay(400);
  digitalWrite(LED_BUILTIN, LOW);   
  delay(400); 
  digitalWrite(LED_BUILTIN, HIGH);  //long blink
  delay(400);                       
  digitalWrite(LED_BUILTIN, LOW);    
  delay(200);                      
  digitalWrite(LED_BUILTIN, HIGH);  //short blink
  delay(200); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);  //short blink
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);  //short blink
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000);
}