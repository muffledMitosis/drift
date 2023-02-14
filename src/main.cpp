#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "./utils.h"

#include "./SIM808.h"

#define SERVICE_UUID          "6f14048f-e286-406a-bb2e-75eaf121fca8"
#define CHARACTERISTIC_UUID   "b1b67348-22a8-490a-ad22-f841c0d8582b"

BLEServer *bleServer;
BLEService *bleService;
BLECharacteristic *bleCharac;

SIM808 *sim808;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 4,5); // RX, TX

  BLEDevice::init("Drift");

  bleServer = BLEDevice::createServer();
  bleService = bleServer->createService(SERVICE_UUID);
  bleCharac = bleService->createCharacteristic(
                            CHARACTERISTIC_UUID,
                            BLECharacteristic::PROPERTY_READ |
                            BLECharacteristic::PROPERTY_WRITE
                          );

  bleCharac->setValue("Drift says hello");
  bleService->start();

  BLEAdvertising *bleAdv = BLEDevice::getAdvertising();
  bleAdv->addServiceUUID(SERVICE_UUID);
  bleAdv->setScanResponse(true);
  bleAdv->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  bleAdv->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  sim808 = new SIM808(&Serial1);

  sim808->init();
  sim808->initGPS();
}

void loop()
{
  Serial.println(sim808->getGPSInfo());
  delay(1000);
}