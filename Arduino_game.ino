#define PIN_SWITCH D2

bool isServer;

void setup() {
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  isServer = (digitalRead(PIN_SWITCH) == LOW) ? true : false;
  if (isServer)
        setupGame();


}

void loop(){
    if (isServer)
        loopGame();
}
