#define Switch_pin D2

bool IamServer;
int cnt = 0;

void setup() {
  pinMode(Switch_pin, INPUT_PULLUP);
  game_setup();
}

void loop() {
  IamServer = (digitalRead(Switch_pin) == LOW) ? true : false;
  if (!IamServer) {
    LedOFF();
    game_loop();
  } else if (IamServer && cnt == 0) {
    performance_setup();
    cnt++;
  } else performance_loop();
}
