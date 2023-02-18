#ifndef BLESUBSYS_H
#define BLESUBSYS_H

#include <Arduino.h>

#define SERVICE_UUID          "6f14048f-e286-406a-bb2e-75eaf121fca8"
#define CHARACTERISTIC_UUID   "b1b67348-22a8-490a-ad22-f841c0d8582b"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

class BLESubsys
{
private:
	BLEServer *bleServer;
	BLEService *bleService;
	BLECharacteristic *bleCharac;
	BLEAdvertising *bleAdv;
public:
	BLESubsys(const char* name);
	~BLESubsys();
};

#endif