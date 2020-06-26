const int REMOTE_IN = 3;
const int RELAY_OUT = 4;

bool vacuum_running = LOW;
bool remote_state = LOW;

unsigned long lastDebounceTime = 0;  // the last time a bluetooth signal has been received
unsigned long debounceDelay = 2000;    // the debounce time, can probably be reduced

void setup() {
  pinMode(REMOTE_IN, INPUT);
  pinMode(RELAY_OUT, OUTPUT);

  // ensure a defined state at bootup
  digitalWrite(RELAY_OUT, vacuum_running);
}

void loop() {
  // after the remote has been triggered, "wait" debounceDelay until reading again to avoid boucing
  if ((millis() - lastDebounceTime) < debounceDelay) {
    return;
  }
  remote_state = digitalRead(REMOTE_IN);
  if (remote_state == HIGH) {
    // reset the debouncing timer
    lastDebounceTime = millis();

    // toggle vacuum
    vacuum_running = !vacuum_running;
    digitalWrite(RELAY_OUT, vacuum_running);
  }

}
