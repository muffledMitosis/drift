#include <Arduino.h>


#include "./SIM808.h"
#include "./utils.h"

SIM808::SIM808(HardwareSerial* serialDevice)
{
	this->sDev = serialDevice;
	this->sysStat = new SIM808StatusDto();
}

bool SIM808::sendCommand(const char* command, const char* expectedResp, unsigned long timeout = 5000)
{
	this->sDev->println(command);

	unsigned long startTime = millis();
	while((millis() - startTime) < timeout)
	{
		if(this->sDev->available())
		{
			String resp = this->sDev->readString();
			if(resp.indexOf(expectedResp) != -1)
			{
				return true;
			}
		}
	}
	return false;
}

String SIM808::getResp(const char* command, unsigned long timeout = 5000)
{
	this->sDev->println(command);

	unsigned long startTime = millis();
	while((millis() - startTime) < timeout)
	{
		if(this->sDev->available())
		{
			return this->sDev->readString();
		}
	}
	return "";
}

void SIM808::init()
{
	DEBUG_OUT("Initializing SIM808");

	SEND_AT("AT", "OK", "AT Error");
	SEND_AT("AT+CFUN=4", "OK", "Could not set phone func to min");
	SEND_AT("AT+CIPMUX=0", "OK", "Error disabling IP connections");
	SEND_AT("AT+CIPSHUT", "SHUT OK", "Error closing TCP/IP Connections");
	SEND_AT("AT+CIICR", "OK", "Could not disable automatic network registration");
	// SEND_AT("AT+CCLK=\"00/00/0000,00:00:00+00\"", "OK", "Could not s");
	// SEND_AT("AT+CSCLK=0", "OK", "Could not disable clock adjustment");
	SEND_AT("AT+CIPRXGET=1", "OK", "Could not enable URC for data reception");
	SEND_AT("AT+CREG=0", "OK", "Could not disable network registration URC");
	SEND_AT("AT+BTPOWER=0", "OK", "Could not power off bluetooth");

	DEBUG_OUT("SIM808 Initialization Complete");
}

void SIM808::initGPS()
{
	DEBUG_OUT("Initializing GPS");

	SEND_AT("AT+CGPSPWR=1", "OK", "Error powering on GPS");
	SEND_AT("AT+CGPSRST=1", "OK", "Could not reset GPS");

	DEBUG_OUT("GPS Initialization Complete");
}

String SIM808::getGPSInfo()
{
	return this->getResp("AT+CGPSINF=0");
}

SIMERR SIM808::getErr()
{
	return this->errorState;
}

String SIM808::getErrString()
{
	return this->errorString;
}

SIM808StatusDto* SIM808::getSysStatPtr()
{
	return this->sysStat;
}

SIM808::~SIM808()
{
}
