#define motrotpin 14

Ticker ticker_rot;

boolean gv_start_rot = false;
boolean gv_stop_rot = true;

void start_rot() {
  gv_start_rot = true;
}

void stop_rot() {
  gv_stop_rot = true;
}

void init_rot() {
  pinMode(motrotpin, OUTPUT);

  digitalWrite(motrotpin, HIGH);
  delay(3000);
  digitalWrite(motrotpin, LOW);
}

void check_rot() {
  if (gv_start_rot == true) {
    ticker_rot.detach();
    digitalWrite(motrotpin, HIGH);
    gv_start_rot = false;
    int lv_timeRun = random(1, 4);
    lv_timeRun = ( lv_timeRun * 1000 ) + 300;
    ticker_rot.attach_ms(lv_timeRun, stop_rot);
  }

  if (gv_stop_rot == true) {
    ticker_rot.detach();
    digitalWrite(motrotpin, LOW);
    gv_stop_rot = false;
    int lv_timeWait = random(15, 45);
    ticker_rot.attach(lv_timeWait, start_rot);
  }
}
