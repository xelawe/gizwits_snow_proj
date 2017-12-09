#define motfanpin 5


boolean gv_start_fan = false;
boolean gv_stop_fan = true;

void start_fan() {
  gv_start_fan = true;
}

void stop_fan() {
  gv_stop_fan = true;
}

void init_fan(){
    pinMode(motfanpin, OUTPUT);
    
  digitalWrite(motfanpin, HIGH);
  delay(3000);
  digitalWrite(motfanpin, LOW);

}

