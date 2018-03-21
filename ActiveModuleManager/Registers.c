/*
 * Registers.c
 *
 * Created: 02/08/2018 9:11:37 PM
 *  Author: nichh
 */ 

//////////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////////

#include "Registers.h"

//////////////////////////////////////////////////////////////////////////
// Extern Implementations
//////////////////////////////////////////////////////////////////////////

struct Register Registers[REGISTER_COUNT] = {
	{REG_CONTROL, 0x1D, 0x1D, &RegAlt_Control},
	{REG_PRESETS, 0x00, 0x00, &RegAlt_Presets},
	{REG_GIMBALX, 0x00, 0x00, &RegAlt_Gimbal},
	{REG_GIMBALY, 0x00, 0x00, &RegAlt_Gimbal},
	{REG_GIMBALZ, 0x00, 0x00, &RegAlt_Gimbal},
	{REG_LANDGEAR, 0x00, 0x00, &RegAlt_LandingGear},
	{REG_THERMSWVLX, 0x00, 0x00, &RegAlt_ThermalSwivel},
	{REG_THERMSWVLY, 0x00, 0x00, &RegAlt_ThermalSwivel},
	{REG_PIEZO, 0x00, 0x00, &RegAlt_PiezoBuzzer},
	{REG_PROJECTILES, 0x00, 0x00, &RegAlt_Projectiles},
	{REG_ACCESSORIES, 0x00, 0x00, &RegAlt_Accessories}
};

//////////////////////////////////////////////////////////////////////////
// System Controls
//////////////////////////////////////////////////////////////////////////

void InitializeRegisters(void)
{
	SPIInitialize();
}

void LoadDataFromFIFO(void)
{
	for(uint8_t i = 0; i < REGISTER_COUNT; i++) {
		//Wait for previous read to complete
		while(EECR & (1 << EEWE));
		//Set register address
		EEAR = (unsigned int)(EEPROM_BASE_REGISTER + i);
		//Triggers an EEPROM read
		EECR |= (1 << EERE);
		//Read data into register
		Registers[i].Value = EEDR;
	}
}

void UnloadDataToFIFO(void)
{
	for(uint8_t i = 0; i < REGISTER_COUNT; i++) {
		//Wait for previous write
		while(EECR & (1 << EEWE));
		//Set register address
		EEAR = (unsigned int)(EEPROM_BASE_REGISTER + i);
		//Set register data
		EEDR = (unsigned char)(Registers[i].Value);
		//Allows EEPROM write
		EECR |= (1 << EEMWE);
		//Starts EEPROM write
		EECR |= (1 << EEWE);
	}
}

struct Register *FindRegister(uint8_t id)
{
	for(uint8_t i = 0; i < REGISTER_COUNT; i++) {
		if(Registers[i].Id == id) {
			return &Registers[i];
		}
	}
}

void ChangeRegister(uint8_t id, unsigned char val)
{
	struct Register *reg = FindRegister(id);
	(*reg).Value = val;
	(*reg).Callback(id, val);
}

void HandleRegisters(void)
{
	static unsigned char regaddr = 0x00;
	unsigned char data;
	if(SPIPseudoReceive(&data)) {
		if(regaddr) {
			if(FindRegister(REG_CONTROL)->Value & (1 << REG_CONTROL_ENABLE) || regaddr == REG_CONTROL) {
				if((regaddr & READWRITE_FILTER_VALUE) == WRITE_FILTER_VALUE) {
					ChangeRegister(regaddr, data);
				}
			}
			regaddr = 0x00;
		}
		else {
			regaddr = data;
			if(FindRegister(REG_CONTROL)->Value & (1 << REG_CONTROL_ENABLE) && (regaddr & READWRITE_FILTER_VALUE) == READWRITE_FILTER_VALUE) {
				struct Register *regref = FindRegister(regaddr);
				SPIPseudoTransmit((*regref).Value);
				regaddr = 0x00;
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
// Register Alteration Functions
//////////////////////////////////////////////////////////////////////////

void RegAlt_Control(uint8_t ctrl, unsigned char cmd)
{
	if (cmd & REG_CONTROL_RESETALL) {
		for(uint8_t i = 0; i < REGISTER_COUNT; i++) {
			Registers[i].Value = Registers[i].DefaultValue;
			Registers[i].Callback(Registers[i].Id, Registers[i].DefaultValue);
		}
	}
	if (cmd & REG_CONTROL_ENABLENOTIFY == 0x0) {
		ToggleProjectileNotify(FLAGNONE);
		ToggleWinchNotify(FLAGNONE);
		ToggleLandingGearNotify(FLAGNONE);
	}
	if (cmd & REG_CONTROL_ENABLEPIEZO == 0x0) {
		TogglePiezo(FLAGNONE);
	}
	if (cmd & REG_CONTROL_ENABLEPROJ == 0x0) {
		ToggleLaunchRegister(FLAGNONE);
	}
	if (cmd & REG_CONTROL_LAUNCHNEXT == 0x0) {
		static unsigned char launchorder = -1;
		launchorder++;
		if (launchorder >= MAXPROJECTILES) {
			launchorder = -1;
			ToggleLaunchRegister(FLAGNONE);
		} else {
			ToggleLaunchRegister((1 << launchorder));
		}
	}
	if (cmd & REG_CONTROL_WINCHUP || cmd & REG_CONTROL_WINCHDOWN) {
		uint8_t winchval = 0x0;
		if (cmd & REG_CONTROL_WINCHUP) {
			winchval |= FLAG1;
		}
		if (cmd & REG_CONTROL_WINCHDOWN) {
			winchval |= FLAG0;
		}
		ToggleWinch(winchval);
	}
}

void RegAlt_Presets(uint8_t ctrl, unsigned char cmd)
{
	
}

void RegAlt_Gimbal(uint8_t ctrl, unsigned char cmd)
{
	
}

void RegAlt_LandingGear(uint8_t ctrl, unsigned char cmd)
{
	
}

void RegAlt_ThermalSwivel(uint8_t ctrl, unsigned char cmd)
{
	
}

void RegAlt_PiezoBuzzer(uint8_t ctrl, unsigned char cmd)
{
	
}

void RegAlt_Projectiles(uint8_t ctrl, unsigned char cmd)
{
	
}

void RegAlt_Accessories(uint8_t ctrl, unsigned char cmd)
{
	
}