#include <SPI.h>
#include <Wire.h>

// הגדרת קבועים ומשתנים
const int ledPin = 13; 
int buttonState = 0; 
void setup() {
  pinMode(ledPin, OUTPUT); 
  pinMode(2, INPUT); 
}

void loop() {
  buttonState = digitalRead(2); 

  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else { 
    digitalWrite(ledPin, LOW);
  }
}
