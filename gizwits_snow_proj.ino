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
#include "led_tool.h"
#include "ds1820_tool.h"
#include "mqtt_tool.h"
#include "rot_tool.h"
#include "fan_tool.h"

#define btnpin 4
#define LDRPin (A0)

int LDRValue;

void setup() {
  // put your setup code here, to run once:

#ifdef serdebug
  Serial.begin(115200);
#endif

  DebugPrintln("\n" + String(__DATE__) + ", " + String(__TIME__) + " " + String(__FILE__));

//  pinMode(ledpinbl, OUTPUT);
//  pinMode(ledpingn, OUTPUT);
//  pinMode(ledpinrt, OUTPUT);

  set_rgb(255, 255, 255);
  delay(500);

  wifi_init("GizSnowPr");
  delay(500);

  init_ota("GizSnowPr");

  init_mqtt_l("GizSnowPr");

  set_rgb(255, 0, 0);
  init_ds1820();
  delay(500);

  check_ds1820();
  check_mqtt_l();


  set_rgb(0, 0, 255);
  init_fan();
  set_rgb(0, 255, 0);
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
