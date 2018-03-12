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