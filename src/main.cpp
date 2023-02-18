#include <Arduino.h>

#include "./utils.h"
#include "./SIM808.h"
#include "./BLE.h"


SIM808 *sim808;
BLESubsys *ble;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 4,5); // RX, TX

  sim808 = new SIM808(&Serial1);
  ble = new BLESubsys("Drift");

  sim808->init();
  sim808->initGPS();
}

void loop()
{
  Serial.println(sim808->getGPSInfo());
  delay(1000);
}