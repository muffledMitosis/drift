#ifndef SIM808_H
#define SIM808_H

#include <Arduino.h>
#include <limits.h>

#include "./utils.h"

#define RUN_ERR(run, err) if(!run) err
#define SEND_AT(at, exp, err) RUN_ERR(this->sendCommand(at, exp), DEBUG_OUT(err))

enum SIMERR
{
	NONE = 1,
	NO_CONNECT = INT_MIN,
	INTERNAL
};

struct SIM808StatusDto
{
	bool gpsFix, up, gps, bt, gsm = false;
};

class SIM808
{
private:
	HardwareSerial *sDev;
	SIMERR errorState;
	String errorString;
	SIM808StatusDto *sysStat;

	bool sendCommand(const char* command, const char* expectedResp, unsigned long timeout);
	String getResp(const char* command, unsigned long timeout);

public:
	SIM808(HardwareSerial *serialDevice);

	void init();
	void initGPS();

	SIMERR getErr();
	String getErrString();
	SIM808StatusDto* getSysStatPtr();
	String getGPSInfo();

	~SIM808();
};

#endif