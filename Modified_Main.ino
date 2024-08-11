
#define modeSwitchPin D2

bool isInServerMode;
int initializationCounter = 0;

void initialSetup() {
  pinMode(modeSwitchPin, INPUT_PULLUP);
  configureGameMode();
}

void primaryLoop() {
  isInServerMode = (digitalRead(modeSwitchPin) == LOW);
  if (!isInServerMode) {
    deactivateAllLeds();
    executeGameModeLoop();
  } else if (isInServerMode && initializationCounter == 0) {
    initializePerformanceServer();
    initializationCounter++;
  } else {
    managePerformanceServer();
  }
}
