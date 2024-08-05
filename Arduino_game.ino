#define PIN_SWITCH D2

bool isServer;

void setup() {
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  isServer = (digitalRead(PIN_SWITCH) == LOW) ? true : false;
  if (isServer)
    // performance_setup();
        setupGame();

  // else
  //   game_setup();
}

void loop(){
    if (isServer)
    // performance_loop();
        loopGame();

  // else
  //   game_loop();
}
