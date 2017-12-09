const char* mqtt_pubt_addr = "ATSH28/SNOWPROJ/SENS/1/addr";
const char* mqtt_pubt_temp = "ATSH28/SNOWPROJ/TEMP/1/value";

Ticker ticker_mqtt;
volatile boolean gv_tick_mqtt = true;

void pub_addr( DeviceAddress iv_addr ) {

  char buffer[10];
  for (uint8_t i = 0; i < 8; i++)
  {
    dtostrf(iv_addr[i], 0, 1, buffer);
    client.publish(mqtt_pubt_addr, buffer, false);
  }
}

void pub_temp( float iv_temp ) {

  char buffer[10];
  dtostrf(iv_temp, 0, 1, buffer);
  client.publish(mqtt_pubt_temp, buffer, true);
}

void tick_mqtt(){
  gv_tick_mqtt = true;
}

void init_mqtt_l(const char* iv_clientname){
  init_mqtt(iv_clientname);

  ticker_mqtt.attach(60, tick_mqtt);
}

void check_mqtt_l(){
  check_mqtt();

    if (gv_tick_mqtt == true ){
        //pub_addr( insideThermometer);
    pub_temp( gv_tempC );
    gv_tick_mqtt = false;
  }
}

