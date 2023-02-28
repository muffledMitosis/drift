#ifndef BLESUBSYS_H
#define BLESUBSYS_H

#include <Arduino.h>

#define SERVICE_UUID "6f14048f-e286-406a-bb2e-75eaf121fca8"
#define CHARACTERISTIC_UUID "b1b67348-22a8-490a-ad22-f841c0d8582b"

#define SERVICE_UUID_CONN_CONT 			"83c64e2f-ce87-447b-bc80-511ed3c7873d"
#define SERVICE_UUID_GPS_STAT 			"fc6588cd-a130-480e-9a52-5d6b55721184"
#define SERVICE_UUID_POSITION_STAT 	"2a2237f0-e21c-40cf-b39c-713f5bcba9c1"

#define UUID_CC_GPS_POW 						"e521f694-999b-499e-a511-5fb0068f5940"
#define UUID_CC_BL_POW 							"786dc9bc-92bb-4004-909a-0553b9b7e5c6"
#define UUID_CC_CELL_POW 						"52f95524-3d2a-4c2f-9616-417c7c2e60d8"
#define UUID_CC_WIFI_CONN 					"3f948d8e-fec0-4d1a-be5f-8e3e0e1aaf9b"

#define UUID_GS_FIX_TYPE 						"a0b77e36-83b5-4e3b-8e17-9a3f321a58c3"
#define UUID_GS_POLL_INT 						"5fdac4a6-9808-4dd1-8050-a6b7d000841c"

#define UUID_PS_COORD 							"4a767391-3e80-4b71-9f37-db0954710d7d"
#define UUID_PS_SPEED 							"a53213d1-ea5f-43fe-b1dd-c2803774d699"
#define UUID_PS_HEADING 						"6f68fbad-1072-4a71-b142-2a3a0a0a42d8"
#define UUID_PS_ALT 								"4b3b8b73-bc11-4a31-bc96-3c9b6c268af9"

#define BLE_CHARAC_RW BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

class BLEServ
{
private:
	BLEService *ptr;
	uint16_t UUID;

public:
	BLEServ(BLEServer *server, const char *UUID);
};

struct BLECharac
{
	BLECharacteristic *ptr;
	uint16_t UUID;
};

class BLESubsys
{
private:
	BLEServer *bleServer;
	BLEService *bleService;
	BLECharacteristic *bleCharac;
	BLEAdvertising *bleAdv;

	BLEServ *_conn_cont_serv;
	BLEServ *_gps_stat_serv;
	BLEServ *_pos_stat_serv;

public:
	BLESubsys(const char *name);
	~BLESubsys();
};

class _BLESubsystem
{
public:
	_BLESubsystem();

	void begin(const char *deviceName);

	virtual void onRead(BLECharacteristic *pCharacteristic) {}
	virtual void onWrite(BLECharacteristic *pCharacteristic) {}
	virtual void onConnect(BLEServer *pServer) {}
	virtual void onDisconnect(BLEServer *pServer) {}

	~_BLESubsystem();

private:
};

#endif