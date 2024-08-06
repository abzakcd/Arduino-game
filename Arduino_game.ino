#define Switch_pin D2

bool IsServer;
int cnt = 0;

void setup() {
  pinMode(Switch_pin, INPUT_PULLUP);
  setupgame();
}

void loop() {
  IsServer = (digitalRead(Switch_pin) == LOW) ? true : false;
  if (!IsServer) {
    LedOff();
    gameloop();
  } else if (IsServer && cnt == 0) {
    performancesetup();
    cnt++;
  } else performanceloop();
}