// AquaBus Library
// Copyright (C) 2017
//
// This software is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0
// International License.
//
// You can redistribute and/or modify this software for non-commerical purposes under the terms
// of the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// This software is provided "as is" without express or implied warranty.

// Debug related definitions
//#define DEBUG
#ifdef DEBUG
	#include <SoftwareSerial.h>
	extern SoftwareSerial Serial2; // 6 is RX, 7 is TX
  #define DEBUG_LOG(string) Serial2.print(string)
  #define DEBUG_LOG_LN(string) Serial2.println(string)
#else
  #define DEBUG_LOG(string)
  #define DEBUG_LOG_LN(string)
#endif
#define DEBUG_LOG_FREE_RAM() DEBUG_LOG(F("Free RAM: ")); DEBUG_LOG_LN(FreeRam())


// Include header files
#include "PM1.h"

AB_PM1_DATA_RESPONSE_FRAME PM1::PM1DataResponseFrame = {};
AB_PM1_INIT_RESPONSE_FRAME PM1::PM1InitResponseFrame = {};
AB_PM1_EEPROM_RESPONSE_FRAME PM1::EEPROMResponseFrame = {};

//ctor
PM1::PM1(unsigned short serial):AquaBusDev(APEX_MODULE_PM1, serial, 0x01, 0x07)
{
  ModuleStatus.ProbeRangeOriginal = eeprom_read_byte(3);
	ModuleStatus.pH_DOProbeOffset = eeprom_read_word(4);
	ModuleStatus.TempProbeOffset = eeprom_read_word(6);
	ModuleStatus.ORPProbeOffset = eeprom_read_word(8);
	ModuleStatus.pH_DOProbeScale = eeprom_read_word(10);
	ModuleStatus.TempProbeScale = eeprom_read_word(12);
	ModuleStatus.ORPProbeScale = eeprom_read_word(14);
	ModuleStatus.Unknown_3 = eeprom_read_word(16);
	ModuleStatus.Unknown_4 = eeprom_read_word(18);
	
}
// Function called to process recieved data
void PM1::processData(byte deviceABAddr, byte* data, unsigned short length)
{
  byte requestType = (((AB_PM1_REQUEST_PACKET*)data)->RequestType);
  
  switch (requestType)
  {
  	case 1: //init
  		PM1InitResponseFrame.response.FunctionCode = (((AB_PM1_REQUEST_PACKET*)data)->FunctionCode);
		  PM1InitResponseFrame.response.RequestType = (((AB_PM1_REQUEST_PACKET*)data)->RequestType);
		  PM1InitResponseFrame.response.ProbeRangeOriginal = ModuleStatus.ProbeRangeOriginal;
			PM1InitResponseFrame.response.pH_DOProbeOffset = ModuleStatus.pH_DOProbeOffset;
			PM1InitResponseFrame.response.TempProbeOffset = ModuleStatus.TempProbeOffset;
			PM1InitResponseFrame.response.ORPProbeOffset = ModuleStatus.ORPProbeOffset;
			PM1InitResponseFrame.response.pH_DOProbeScale = ModuleStatus.pH_DOProbeScale;
			PM1InitResponseFrame.response.TempProbeScale = ModuleStatus.TempProbeScale;
			PM1InitResponseFrame.response.ORPProbeScale = ModuleStatus.ORPProbeScale;
			PM1InitResponseFrame.response.Unknown_3 = ModuleStatus.Unknown_3;
			PM1InitResponseFrame.response.Unknown_4 = ModuleStatus.Unknown_4;
			 // Send the response
		  sendData(deviceABAddr, (byte*)(&PM1InitResponseFrame.response), sizeof(AB_PM1_INIT_RESPONSE_PACKET));
		  break;
  	case 2: //calibrate
  		PM1InitResponseFrame.response.FunctionCode = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->FunctionCode;
		  PM1InitResponseFrame.response.RequestType = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->RequestType;
		  PM1InitResponseFrame.response.ProbeRangeOriginal = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ProbeRangeOriginal;
			PM1InitResponseFrame.response.pH_DOProbeOffset = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->pH_DOProbeOffset;
			PM1InitResponseFrame.response.TempProbeOffset = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->TempProbeOffset;
			PM1InitResponseFrame.response.ORPProbeOffset = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ORPProbeOffset;
			PM1InitResponseFrame.response.pH_DOProbeScale = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->pH_DOProbeScale;
			PM1InitResponseFrame.response.TempProbeScale = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->TempProbeScale;
			PM1InitResponseFrame.response.ORPProbeScale = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ORPProbeScale;
			PM1InitResponseFrame.response.Unknown_3 = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->Unknown_3;
			PM1InitResponseFrame.response.Unknown_4 = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->Unknown_4;
			 // Send the response
		  sendData(deviceABAddr, (byte*)(&PM1InitResponseFrame.response), sizeof(AB_PM1_INIT_RESPONSE_PACKET));
		  
		  eeprom_update_byte(3, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ProbeRangeOriginal);
		  eeprom_update_word(4, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->pH_DOProbeOffset);
		  eeprom_update_word(6, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->TempProbeOffset);
		  eeprom_update_word(8, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ORPProbeOffset);
		  eeprom_update_word(10, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->pH_DOProbeScale);
		  eeprom_update_word(12, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->TempProbeScale);
		  eeprom_update_word(14, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ORPProbeScale);
		  eeprom_update_word(16, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->Unknown_3);
		  eeprom_update_word(18, ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->Unknown_4);
  		
  		ModuleStatus.ProbeRangeOriginal = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ProbeRangeOriginal;
			ModuleStatus.pH_DOProbeOffset = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->pH_DOProbeOffset;
			ModuleStatus.TempProbeOffset = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->TempProbeOffset;
			ModuleStatus.ORPProbeOffset = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ORPProbeOffset;
			ModuleStatus.pH_DOProbeScale = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->pH_DOProbeScale;
			ModuleStatus.TempProbeScale = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->TempProbeScale;
			ModuleStatus.ORPProbeScale = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->ORPProbeScale;
			ModuleStatus.Unknown_3 = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->Unknown_3;
			ModuleStatus.Unknown_4 = ((AB_PM1_CALIBRATE_REQUEST_PACKET*)data)->Unknown_4;
  		
  		break;
  	case 3: //get data
  		PM1DataResponseFrame.response.FunctionCode = (((AB_PM1_REQUEST_PACKET*)data)->FunctionCode);
		  PM1DataResponseFrame.response.RequestType = (((AB_PM1_REQUEST_PACKET*)data)->RequestType);
		  PM1DataResponseFrame.response.ProbeRangeOriginal = ModuleStatus.ProbeRangeOriginal;
			PM1DataResponseFrame.response.pH_DOReading = 0x348A;
			PM1DataResponseFrame.response.TempReading = 0x2244;
			PM1DataResponseFrame.response.ORPReading = 0x4018;
			PM1DataResponseFrame.response.SwitchState = 2;
			 // Send the response
  		sendData(deviceABAddr, (byte*)(&PM1DataResponseFrame.response), sizeof(AB_PM1_DATA_RESPONSE_PACKET));
  		break;
  	default:
  		break;
  }
}

void PM1::processEEPROMRequest(byte deviceABAddr, byte* data, unsigned short length)
{
	int index = 0;
	
	DEBUG_LOG_LN("processEEPROMRequest");
	switch(((AB_EEPROM_GET_SET_REQUEST_PACKET*)data)->RequestType)
	{
		case 1://GET
			DEBUG_LOG_LN("processEEPROMRequest 1");
			//not quite sure what this is for yet
			//Apex expects two bytes of eeprom back
			break;
		case 2://SET
			DEBUG_LOG_LN("processEEPROMRequest 2");
			//on abdelete Apex tells us to clear ApexSerial from eeprom
			//data->location should be byte 1 of eeprom
			//data->length should be 2 bytes
			//this matches our internal eeprom format
			for (int i = ((AB_EEPROM_GET_SET_REQUEST_PACKET*)data)->Location; i < ((AB_EEPROM_GET_SET_REQUEST_PACKET*)data)->Length; i++)
			{
				eeprom_update_byte(i, ((AB_EEPROM_GET_SET_REQUEST_PACKET*)data)->data[index]);
				index++;
			}
			break;
		default:
			DEBUG_LOG_LN("processEEPROMRequest default");
			break;
	}
	
	EEPROMResponseFrame.response.funcCode = (((AB_EEPROM_GET_SET_REQUEST_PACKET*)data)->funcCode);
	EEPROMResponseFrame.response.RequestType = (((AB_EEPROM_GET_SET_REQUEST_PACKET*)data)->RequestType);
	EEPROMResponseFrame.response.unknown_1 = 0;
	EEPROMResponseFrame.response.unknown_2 = 0;
	EEPROMResponseFrame.response.unknown_3 = 0;
	EEPROMResponseFrame.response.unknown_4 = 0;
	
	
	sendData(deviceABAddr, (byte*)(&EEPROMResponseFrame.response), sizeof(AB_EEPROM_GET_SET_RESPONSE_PACKET));
}