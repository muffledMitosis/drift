#include "./BLE.h"

#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

BLEServ::BLEServ(BLEServer* server, const char* UUID)
{
  this->ptr = server->createService(UUID);
}

BLESubsys::BLESubsys(const char *name)
{
  BLEDevice::init(name);

  this->bleServer = BLEDevice::createServer();
  this->bleService = bleServer->createService(SERVICE_UUID);
  this->bleCharac = bleService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  this->bleCharac->setValue("Drift says hello");
  this->bleService->start();

  this->_conn_cont_serv = new BLEServ(this->bleServer, SERVICE_UUID_CONN_CONT);
  this->_gps_stat_serv = new BLEServ(this->bleServer, SERVICE_UUID_GPS_STAT);
  this->_pos_stat_serv = new BLEServ(this->bleServer, SERVICE_UUID_POSITION_STAT);

  this->bleAdv = BLEDevice::getAdvertising();
  this->bleAdv->addServiceUUID(SERVICE_UUID);
  this->bleAdv->setScanResponse(true);
  this->bleAdv->setMinPreferred(0x06); // functions that help with iPhone connections issue
  this->bleAdv->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

BLESubsys::~BLESubsys()
{
}

_BLESubsystem::_BLESubsystem() {}

_BLESubsystem::~_BLESubsystem() {}

void _BLESubsystem::begin(const char *deviceName)
{
  BLEDevice::init(deviceName);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(this);

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(this);

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}