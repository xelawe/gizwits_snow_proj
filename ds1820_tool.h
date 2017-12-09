// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress   insideThermometer = { 0x28, 0xFF, 0x50, 0xC4, 0x0, 0x17, 0x4, 0x9 }; //insideThermometer;


Ticker ticker_ds1820;

float gv_tempC;
volatile boolean gv_tick_ds1820 = true;


// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) DebugPrint("0");
    DebugPrint(deviceAddress[i], HEX);
  }
}


void tick_ds1820(){
  gv_tick_ds1820 = true;
}

/*
   Setup function. Here we do the basics
*/
void init_ds1820(void)
{

  DebugPrintln("Dallas Temperature IC Control Library Demo");

  // locate devices on the bus
  DebugPrint("Locating devices...");
  sensors.begin();
  DebugPrint("Found ");
  DebugPrint(sensors.getDeviceCount(), DEC);
  DebugPrintln(" devices.");

  // report parasite power requirements
  DebugPrint("Parasite power is: ");
  if (sensors.isParasitePowerMode()) {
    DebugPrintln("ON");
  }
  else DebugPrintln("OFF");

  // Method 1:
  // Search for devices on the bus and assign based on an index. Ideally,
  // you would do this to initially discover addresses on the bus and then
  // use those addresses and manually assign them (see above) once you know
  // the devices on your bus (and assuming they don't change).
  // if (!sensors.getAddress(insideThermometer, 0)) {
  //   DebugPrintln("Unable to find address for Device 0");
  // }

  // show the addresses we found on the bus
  DebugPrint("Device 0 Address: ");
  printAddress(insideThermometer);
  DebugPrintln();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);

  DebugPrint("Device 0 Resolution: ");
  DebugPrint(sensors.getResolution(insideThermometer), DEC);
  DebugPrintln();

  ticker_ds1820.attach(10, tick_ds1820);
}

// function to print the temperature for a device
void printTemperature()
{
  // method 2 - faster

  DebugPrint("Temp C: ");
  DebugPrint(gv_tempC);
  DebugPrint(" Temp F: ");
  DebugPrintln(DallasTemperature::toFahrenheit(gv_tempC)); // Converts tempC to Fahrenheit

}

/*
   Main function. It will request the tempC from the sensors and display on Serial.
*/
void get_ds1820(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  DebugPrint("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  DebugPrintln("DONE");

  gv_tempC = sensors.getTempC(insideThermometer);

  // It responds almost immediately. Let's print out the data
  printTemperature(); // Use a simple function to print out the data
}

void check_ds1820(){
  if (gv_tick_ds1820 == true ){
    get_ds1820();
    gv_tick_ds1820 = false;
  }
}

