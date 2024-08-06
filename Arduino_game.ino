#define Switch_pin D2

bool IsServer;
int cnt = 0;

void setup() {
  pinMode(Switch_pin, INPUT_PULLUP);
  game_setup();
}

void loop() {
  IsServer = (digitalRead(Switch_pin) == LOW) ? true : false;
  if (!IsServer) {
    game_loop();
  } else if (IsServer && cnt == 0) {
    performance_setup();
    cnt++;
  } else performance_loop();
}
