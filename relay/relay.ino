const int relayPin =  3;
int relayState;
void setup() {
  pinMode(relayPin, OUTPUT);
}


void loop() {
  
   if (relayState == LOW) {
      relayState = HIGH;
    } else {
      relayState = LOW;
    }
 
  digitalWrite(relayPin, relayState);
delay(1000);
}
