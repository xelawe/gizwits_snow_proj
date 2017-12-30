#define motfanpin 5


boolean gv_start_fan = false;
boolean gv_stop_fan = true;
boolean gv_fan_started = false;

void start_fan() {
  if ( gv_fan_started == false ) {
    gv_start_fan = true;
  }
}

void stop_fan() {
  if ( gv_fan_started != false ) {
    gv_stop_fan = true;
  }
}

void init_fan() {
  pinMode(motfanpin, OUTPUT);

  digitalWrite(motfanpin, HIGH);
  delay(3000);
  digitalWrite(motfanpin, LOW);

}

void check_fan() {

  if ( gv_tempC > 28 ) {
    start_fan();
  } else if ( gv_tempC < 24 ) {
    stop_fan();
  }

  if (gv_start_fan == true) {
    digitalWrite(motfanpin, HIGH);
    client.publish(mqtt_pubt_fan, "1", true);
    gv_fan_started = true;
    gv_start_fan = false;
  }

  if (gv_stop_fan == true) {
    digitalWrite(motfanpin, LOW);
    client.publish(mqtt_pubt_fan, "0", true);
    gv_fan_started = false;
    gv_stop_fan = false;
  }

}

