/*
 * Manager.c
 *
 * Created: 02/08/2018 9:13:29 PM
 *  Author: nichh
 */ 
#include "Manager.h"

struct PulseRegister PulseModules[3] = {
	{RIDC, GIMBALX, 0x00, 0, {0x00, 0}},
	{RIDC, GIMBALY, 0x00, 0, {0x00, 0}},
	{RIDC, GIMBALZ, 0x00, 0, {0x00, 0}},
	{RIDC, THERMSWIVELX, 0x00, 0, {0x00, 0}},
	{RIDC, THERMSWIVELY, 0x00, 0, {0x00, 0}},
	{RIDC, LANDINGGEAR, 0x00, 0, {0x00, 0}},
	{RIDD, PIEZOBUZZER, 0x00, 0, {0x00, 0}}
};

void InitializeManager(void)
{
	uint8_t servos = (1 << GIMBALX) | (1 << GIMBALY) | (1 << GIMBALZ) | (1 << LANDINGGEAR) | (1 << THERMSWIVELX) | (1 << THERMSWIVELY);
	//Enable servos pins for output
	SERVOREG |= servos;
	//Turn off all servo pins
	SERVOPORT &= ~servos;
	
	uint8_t winch = (1 << WINCHPOS) | (1 << WINCHNEG);
	//Enable winch pins for output
	WINCHREG |= winch;
	//Turn off winch pins
	WINCHPORT &= ~winch;
	
	winch = (1 << WINCHINT);
	//Enable winch interrupt for input
	WINCHREG &= ~winch;
	
	uint8_t notify = (1 << PROJLAUNCHNOTIFY) | (1 << WINCHACTIVENOTIFY) | (1 << LANDINGGEARACTIVENOTIFY) | (1 << PIEZOBUZZER);
	//Enable notify pins for output
	NOTIFYREG |= notify;
	//Turn off all notify pins
	NOTIFYPORT &= ~notify;
	
	uint8_t shiftregset = (1 << PROJSHIFTREGSET) | (1 << ACCESSORYSHIFTREGSET);
	//Enable shift register set pins for output
	SHIFTREGSETREG |= shiftregset;
	//Turn off all shift register set pins
	SHIFTREGSETPORT &= ~shiftregset;
	
	uint8_t shiftregdata = (1 << SHIFTREGDATA);
	//Enable shift register data pins for output
	SHIFTREGDATAREG |= shiftregdata;
	//Turn off all shift register data pins
	SHIFTREGDATAPORT &= ~shiftregdata;
	
	//Set initial duty cycle period
	DutyCyclePeriod = (unsigned int)(1.0f / ((float)DEFAULTDUTYFREQUENCY) * 1000.0f);
}



struct PulseRegister *FindPulseModule(enum RegisterId rid, unsigned char num)
{
	for(uint8_t i = 0; i < PULSE_MODULE_COUNT; i++)
	{
		if(PulseModules[i].RID == rid && PulseModules[i].RegisterNumber == num)
		{
			return &PulseModules[i];
		}
	}
}

void ChangePulseRegister(enum RegisterId rid, unsigned char num, unsigned char val)
{
	struct PulseRegister *reg = FindPulseModule(rid, num);
	(*reg).Save.Alpha = (*reg).Alpha;
	(*reg).Save.DutyCycle = (*reg).DutyCycle;
	(*reg).Alpha = val;
	(*reg).DutyCycle = ConvertAlphaToDuty(val);
}

unsigned char ConvertAlphaToDuty(unsigned char alpha)
{
	return (unsigned char)(((float)alpha / 255.0f) * (float)DutyCyclePeriod);
}



void ToggleGimbal(unsigned char x, unsigned char y, unsigned char z)
{
	ChangePulseRegister(RIDC, GIMBALX, x);
	ChangePulseRegister(RIDC, GIMBALY, y);
	ChangePulseRegister(RIDC, GIMBALZ, z);
}

void ToggleThermalSwivel(unsigned char x, unsigned char y)
{
	ChangePulseRegister(RIDC, THERMSWIVELX, x);
	ChangePulseRegister(RIDC, THERMSWIVELY, y);
}

void ToggleLandingGear(unsigned char a)
{
	ChangePulseRegister(RIDC, LANDINGGEAR, a);
}

void TogglePiezo(unsigned char a)
{
	ChangePulseRegister(RIDD, PIEZOBUZZER, a);
}

void ToggleWinch(uint8_t flagval)
{
	if((flagval & FLAG0) == FLAG0)
	{
		WINCHPORT |= WINCHPOS;
	}
	else
	{
		WINCHPORT &= ~WINCHPOS;
	}
	
	if((flagval & FLAG1) == FLAG1)
	{
		WINCHPORT |= WINCHNEG;
	}
	else
	{
		WINCHPORT &= ~WINCHNEG;
	}
}


void ToggleProjectileNotify(uint8_t flagval)
{
	if((flagval & FLAG0) == FLAG0)
	{
		NOTIFYPORT |= PROJLAUNCHNOTIFY;
	}
	else
	{
		NOTIFYPORT &= ~PROJLAUNCHNOTIFY;
	}
}

void ToggleWinchNotify(uint8_t flagval)
{
	if((flagval & FLAG0) == FLAG0)
	{
		NOTIFYPORT |= WINCHACTIVENOTIFY;
	}
	else
	{
		NOTIFYPORT &= ~WINCHACTIVENOTIFY;	
	}
}

void ToggleLandingGearNotify(uint8_t flagval)
{
	if((flagval & FLAG0) == FLAG0)
	{
		NOTIFYPORT |= LANDINGGEARACTIVENOTIFY;
	}
	else
	{
		NOTIFYPORT &= ~LANDINGGEARACTIVENOTIFY;
	}
}


void ToggleLaunchRegister(uint8_t flagval)
{
	
}

void ToggleAccessoryRegister(uint8_t flagval)
{
	
}


void HandlePulseRegisters(double elapsedtime)
{
	
}