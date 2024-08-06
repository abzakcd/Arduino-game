#define pinLed_R D1
#define pinLed_G D3
#define pinLed_B D4
#define pinBtn D7

int lastVal;
unsigned long lastPress;
unsigned long duration;
unsigned long lastDuration;

unsigned long pressDurations[10] = { 0 };
bool isImprove[10] = { false };
int pressIndex = 0;

void game_setup() {
  wifiClient_Setup();
  Serial.begin(9600);
  pinMode(pinLed_R, OUTPUT);
  pinMode(pinLed_G, OUTPUT);
  pinMode(pinLed_B, OUTPUT);
  pinMode(pinBtn, INPUT_PULLUP);
  LedOFF();
  lastVal = HIGH;
  lastPress = millis();
  lastDuration = GetData();
  if (lastDuration <= 0) SendData(6000000);  // במקרה והשרת ריק
}

void game_loop() {
  if (digitalRead(pinBtn) == LOW && lastVal == HIGH && (millis() - lastPress > 50)) {
    lastPress = millis();
    lastVal = LOW;
    Serial.println("start press");
  }
  if (digitalRead(pinBtn) == HIGH && lastVal == LOW) {
    lastVal = HIGH;
    duration = millis() - lastPress;
    Serial.println("end press");
    Serial.print("Duration: ");
    Serial.println(duration);

    pressDurations[pressIndex] = duration;
    isImprove[pressIndex] = duration < lastDuration;

    if (isImprove[pressIndex]) {
      SendData(duration);
      LightLed(0x5DE2E7);
    } else {
      LightLed(0xFE9900);
    }

    pressIndex = (pressIndex + 1) % 10;
    delay(200);
    lastDuration = GetData();
  }
}

void LightLed(long HexaColor) {
  int red = (HexaColor >> 16) & 0xFF;
  int green = (HexaColor >> 8) & 0xFF;
  int blue = HexaColor & 0xFF;

  analogWrite(pinLed_R, red);
  analogWrite(pinLed_G, green);
  analogWrite(pinLed_B, blue);
}

void LedOFF() {
  analogWrite(pinLed_R, 0);
  analogWrite(pinLed_G, 0);
  analogWrite(pinLed_B, 0);
}
