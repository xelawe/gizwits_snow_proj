#define motfanpin 5


boolean gv_start_fan = false;
boolean gv_stop_fan = true;

void start_fan() {
  gv_start_fan = true;
}

void stop_fan() {
  gv_stop_fan = true;
}

void init_fan() {
  pinMode(motfanpin, OUTPUT);

  digitalWrite(motfanpin, HIGH);
  delay(3000);
  digitalWrite(motfanpin, LOW);

}

void check_fan() {

  if ( gv_tempC > 26 ) {
    start_fan();
  } else {
    stop_fan();
  }

  if (gv_start_rot == true) {
    //ticker_rot.detach();
    digitalWrite(motfanpin, HIGH);
    gv_start_fan = false;
    //int lv_timeRun = random(1, 4);
    //ticker_rot.attach(lv_timeRun, stop_rot);
  }

  if (gv_stop_rot == true) {
    //ticker_rot.detach();
    digitalWrite(motfanpin, LOW);
    gv_stop_rot = false;
    //int lv_timeWait = random(15, 45);
    //ticker_rot.attach(lv_timeWait, start_rot);
  }

}

