#include "./BLE.h"

#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>


BLESubsys::BLESubsys(const char* name)
{
  BLEDevice::init(name);

  this->bleServer = BLEDevice::createServer();
  this->bleService = bleServer->createService(SERVICE_UUID);
  this->bleCharac = bleService->createCharacteristic(
                            CHARACTERISTIC_UUID,
                            BLECharacteristic::PROPERTY_READ |
                            BLECharacteristic::PROPERTY_WRITE
                          );

  this->bleCharac->setValue("Drift says hello");
  this->bleService->start();

  this->bleAdv = BLEDevice::getAdvertising();
  this->bleAdv->addServiceUUID(SERVICE_UUID);
  this->bleAdv->setScanResponse(true);
  this->bleAdv->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  this->bleAdv->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

BLESubsys::~BLESubsys()
{
}
