#define serdebug
#ifdef serdebug
#define DebugPrint(...) {  Serial.print(__VA_ARGS__); }
#define DebugPrintln(...) {  Serial.println(__VA_ARGS__); }
#else
#define DebugPrint(...) { }
#define DebugPrintln(...) { }
#endif

#include "cy_wifi.h"
#include "cy_ota.h"
#include "cy_mqtt.h"
#include <Ticker.h>
#include "ds1820_tool.h"
#include "mqtt_tool.h"
#include "rot_tool.h"
#include "fan_tool.h"

#define btnpin 4
#define ledpinbl 13
#define ledpinrt 15
#define ledpingn 12
#define LDRPin (A0)

int LDRValue;


void set_rgb(int iv_red, int iv_green, int iv_blue, int iv_LDRvalue) {

  int lv_green = iv_green * iv_LDRvalue / 1023;
  int lv_red = iv_red * iv_LDRvalue / 1023;
  int lv_blue = iv_blue * iv_LDRvalue / 1023;

  set_rgb(lv_red, lv_green, lv_blue);

}

void set_rgb(int iv_red, int iv_green, int iv_blue) {

  int lv_green = iv_green * 0.8;
  int lv_red = iv_red;
  int lv_blue = iv_blue;

  analogWrite(ledpinrt, lv_red);
  analogWrite(ledpingn, lv_green);
  analogWrite(ledpinbl, lv_blue);
}

void setup() {
  // put your setup code here, to run once:

#ifdef serdebug
  Serial.begin(115200);
#endif

  DebugPrintln("\n" + String(__DATE__) + ", " + String(__TIME__) + " " + String(__FILE__));

  set_rgb(255, 255, 255);
  delay(500);

  wifi_init("GizSnowPr");
  delay(500);

  init_ota("GizSnowPr");

  init_mqtt_l("GizSnowPr");
  init_ds1820();
  delay(500);

  check_ds1820();
  check_mqtt_l();

  init_fan();
  init_rot();

  set_rgb(0, 0, 0);

}

void loop() {
  // put your main code here, to run repeatedly:

  check_ota();

  check_ds1820();

  LDRValue = analogRead(LDRPin);

  check_fan();
  check_rot();

  check_mqtt_l();

  delay(100);

}
