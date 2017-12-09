#define ledpinbl 13
#define ledpinrt 15
#define ledpingn 12

void set_led(int iv_pin, int iv_val) {
  
//  switch (iv_val) {
//    case 0:
//      digitalWrite(iv_pin, LOW);
//      break;
//    case 255:
//      digitalWrite(iv_pin, HIGH);
//      break;
//    default:
      analogWrite(iv_pin, iv_val);
//      break;
//  }
  
}

void set_rgb(int iv_red, int iv_green, int iv_blue) {

  int lv_green = iv_green * 0.8;
  int lv_red = iv_red;
  int lv_blue = iv_blue;

  set_led(ledpingn, lv_green);
  set_led(ledpinrt, lv_red);
  set_led(ledpinbl, lv_blue);
}

void set_rgb(int iv_red, int iv_green, int iv_blue, int iv_LDRvalue) {

  int lv_green = iv_green * iv_LDRvalue / 1023;
  int lv_red = iv_red * iv_LDRvalue / 1023;
  int lv_blue = iv_blue * iv_LDRvalue / 1023;

  set_rgb(lv_red, lv_green, lv_blue);

}


