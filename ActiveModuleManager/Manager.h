/*
 * Manager.h
 *
 * Created: 02/08/2018 9:13:07 PM
 *  Author: nichh
 */ 


#ifndef MANAGER_H_
#define MANAGER_H_

#include "PinLabels.h"


#define PULSE_MODULE_COUNT 3
#define DEFAULTDUTYFREQUENCY 60
#define MINDUTYFREQUENCY 4
#define MAXDUTYFREQUENCY 500
unsigned int DutyCyclePeriod = 0; //Must be more than 4Hz and less than 500Hz.  Default is 60Hz

struct PulseRegister
{
	enum RegisterId RID;
	unsigned char RegisterNumber;
	unsigned char Alpha;
	unsigned char DutyCycle;
	
	struct PulseRegisterSave Save;
};
struct PulseRegisterSave
{
	unsigned char Alpha;
	unsigned char DutyCycle;
};

enum RegisterId
{
	RIDB,
	RIDC,
	RIDD
};

enum StaticModuleFlag
{
	FLAGNONE = 0x00,
	FLAG0 = 0x01,
	FLAG1 = 0x02,
	FLAG2 = 0x04,
	FLAG3 = 0x08,
	FLAG4 = 0x10,
	FLAG5 = 0x20,
	FLAG6 = 0x40,
	FLAG7 = 0x80,
	FLAGALL = 0xFF
};

extern struct PulseRegister PulseModules[3]


void InitializeManager(void);

struct PulseRegister *FindPulseModule(enum RegisterId, unsigned char);
void ChangePulseRegister(enum RegisterId, unsigned char, unsigned char);
unsigned char ConvertAlphaToDuty(unsigned char);

void ToggleGimbal(unsigned char, unsigned char, unsigned char);
void ToggleThermalSwivel(unsigned char, unsigned char);
void ToggleLandingGear(unsigned char);
void TogglePiezo(unsigned char);

void ToggleWinch(uint8_t);
void ToggleProjectileNotify(uint8_t);
void ToggleWinchNotify(uint8_t);
void ToggleLandingGearNotify(uint8_t);

void ToggleLaunchRegister(uint8_t);
void ToggleAccessoryRegister(uint8_t);

void HandlePulseRegisters(double);



#endif /* MANAGER_H_ */