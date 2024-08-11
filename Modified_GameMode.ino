
#define redLed D1
#define greenLed D3
#define blueLed D4
#define actionButton D7

int previousButtonState;
unsigned long lastButtonPressTime;
unsigned long currentPressDuration;
unsigned long previousBestDuration;

unsigned long pressDurationsLog[10] = { 0 };
bool improvementStatus[10] = { false };
int logIndex = 0;

void configureGameMode() {
  establishWiFiConnection();
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(actionButton, INPUT_PULLUP);
  deactivateAllLeds();
  previousButtonState = HIGH;
  lastButtonPressTime = millis();
  previousBestDuration = retrieveDataFromServer();
  if (previousBestDuration <= 0) {
    uploadDataToServer(6000000);  // במקרה והשרת ריק
  }
}

void executeGameModeLoop() {
  if (digitalRead(actionButton) == LOW && previousButtonState == HIGH && (millis() - lastButtonPressTime > 50)) {
    lastButtonPressTime = millis();
    previousButtonState = LOW;
    Serial.println("Button Press Initiated");
  }
  if (digitalRead(actionButton) == HIGH && previousButtonState == LOW) {
    previousButtonState = HIGH;
    currentPressDuration = millis() - lastButtonPressTime;
    Serial.println("Button Press Ended");
    Serial.print("Press Duration: ");
    Serial.println(currentPressDuration);

    pressDurationsLog[logIndex] = currentPressDuration;
    improvementStatus[logIndex] = currentPressDuration < previousBestDuration;

    if (improvementStatus[logIndex]) {
      uploadDataToServer(currentPressDuration);
      illuminateLed(0x5DE2E7);  // צבע כחול
    } else {
      illuminateLed(0xFE9900);  // צבע כתום
    }

    logIndex = (logIndex + 1) % 10;
    delay(200);
    previousBestDuration = retrieveDataFromServer();
  }
}

void illuminateLed(long hexColor) {
  int redIntensity = (hexColor >> 16) & 0xFF;
  int greenIntensity = (hexColor >> 8) & 0xFF;
  int blueIntensity = hexColor & 0xFF;

  analogWrite(redLed, redIntensity);
  analogWrite(greenLed, greenIntensity);
  analogWrite(blueLed, blueIntensity);
}

void deactivateAllLeds() {
  analogWrite(redLed, 0);
  analogWrite(greenLed, 0);
  analogWrite(blueLed, 0);
}
