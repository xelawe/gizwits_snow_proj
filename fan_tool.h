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

  if ( gv_tempC > 30 ) {
    start_fan();
  } else {
    stop_fan();
  }

  if (gv_start_fan == true) {
    digitalWrite(motfanpin, HIGH);
   // client.publish(mqtt_pubt_fan, "1", true);
    gv_start_fan = false;
  }

  if (gv_stop_fan == true) {
    digitalWrite(motfanpin, LOW);
   // client.publish(mqtt_pubt_fan, "0", true);
    gv_stop_fan = false;
  }

}

