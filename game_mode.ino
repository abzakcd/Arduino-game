#define PIN_LED_R D1
#define PIN_LED_G D3
#define PIN_LED_B D4
#define PIN_BTN D7

int lastButtonState;
unsigned long lastPressTime;
unsigned long pressDuration;
unsigned long lastPressDuration;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
  turnOffLed();
  lastButtonState = HIGH;
  lastPressTime = millis();
}

void loop() {
  lastPressDuration = getData();
  if (lastPressDuration <= 0) {
    sendData(6000000);
  }
  
  int buttonState = digitalRead(PIN_BTN);

  if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastPressTime > 50)) {
    lastPressTime = millis();
    lastButtonState = LOW;
    Serial.println("start press");
  }
  
  if (buttonState == HIGH && lastButtonState == LOW) {
    lastButtonState = HIGH;
    pressDuration = millis() - lastPressTime;
    Serial.println("end press");
    Serial.print("Duration: ");
    Serial.println(pressDuration);
  }
}

void lightLed(long hexaColor) {
  // Set the LED to a specific color based on the hexadecimal color value
  int red = (hexaColor >> 16) & 0xFF;
  int green = (hexaColor >> 8) & 0xFF;
  int blue = hexaColor & 0xFF;

  analogWrite(PIN_LED_R, red);
  analogWrite(PIN_LED_G, green);
  analogWrite(PIN_LED_B, blue);
}

void turnOffLed() {
  // Turn off all LEDs
  analogWrite(PIN_LED_R, 0);
  analogWrite(PIN_LED_G, 0);
  analogWrite(PIN_LED_B, 0);
}
