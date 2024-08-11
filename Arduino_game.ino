#define buttonPin D2

bool serverMode;

void initialize() {
  pinMode(buttonPin, INPUT_PULLUP);
  setupGameMode();
}

void mainLoop() {
  serverMode = (digitalRead(buttonPin) == LOW) ? true : false;
  if (!serverMode) {
    turnOffLeds();
    gameModeLoop();
  } else if (serverMode) {
    setupPerformanceMode();
  } else handlePerformance();
}