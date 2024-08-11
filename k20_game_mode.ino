#define redLedPin D1
#define greenLedPin D3
#define blueLedPin D4
#define buttonPin D7

int previousState;
unsigned long lastButtonPressTime;
unsigned long pressDuration;
unsigned long previousPressDuration;

unsigned long pressDurationsArray[10] = { 0 };
bool improvementFlag[10] = { false };
int currentIndex = 0;

void setupGameMode() {
  setupWiFiClient();
  Serial.begin(9600);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  turnOffLeds();
  previousState = HIGH;
  lastButtonPressTime = millis();
  previousPressDuration = fetchData();
  if (previousPressDuration <= 0) sendDataToServer(60000);  

void gameModeLoop() {
  if (digitalRead(buttonPin) == LOW && previousState == HIGH && (millis() - lastButtonPressTime > 50)) {
    lastButtonPressTime = millis();
    previousState = LOW;
    Serial.println("Button Pressed");
  }
  if (digitalRead(buttonPin) == HIGH && previousState == LOW) {
    previousState = HIGH;
    pressDuration = millis() - lastButtonPressTime;
    Serial.println("Button Released");
    Serial.print("Duration: ");
    Serial.println(pressDuration);

    pressDurationsArray[currentIndex] = pressDuration;
    improvementFlag[currentIndex] = pressDuration < previousPressDuration;

    if (improvementFlag[currentIndex]) {
      sendDataToServer(pressDuration);
      activateLed(0x5DE2E7);
    } else {
      activateLed(0xFE9900);
    }

    currentIndex = (currentIndex + 1) % 10;
    delay(200);
    previousPressDuration = fetchData();
  }
}

void activateLed(long colorHex) {
  int redValue = (colorHex >> 16) & 0xFF;
  int greenValue = (colorHex >> 8) & 0xFF;
  int blueValue = colorHex & 0xFF;

  analogWrite(redLedPin, redValue);
  analogWrite(greenLedPin, greenValue);
  analogWrite(blueLedPin, blueValue);
}

void turnOffLeds() {
  analogWrite(redLedPin, 0);
  analogWrite(greenLedPin, 0);
  analogWrite(blueLedPin, 0);
}
