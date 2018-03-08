/*
 * Registers.h
 *
 * Created: 02/08/2018 9:11:52 PM
 *  Author: nichh
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

//////////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////////

#include "COM/SPISlave.h"

//////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// System
#define REGISTER_COUNT
#define READ_FILTER_VALUE 0x00
#define WRITE_FILTER_VALUE 0x80
#define READWRITE_FILTER_VALUE 0x80

//////////////////////////////////////////////////////////////////////////
// Register Id's
#define REG_CONTROL 0x01
#define REG_PRESETS 0x02

#define REG_GIMBALX 0x03
#define REG_GIMBALY 0x04
#define REG_GIMBALZ 0x05
#define REG_LANDGEAR 0x06
#define REG_THERMSWVLX 0x07
#define REG_THERMSWVLY 0x08
#define REG_PIEZO 0x09

#define REG_PROJECTILES 0x0A
#define REG_ACCESSORIES 0x0B

//////////////////////////////////////////////////////////////////////////
// Register Value Positions
#define REG_CONTROL_ENABLE (1 << 0)
#define REG_CONTROL_RESETALL (1 << 1)
#define REG_CONTROL_ENABLENOTIFY (1 << 2)
#define REG_CONTROL_ENABLEPIEZO (1 << 3)
#define REG_CONTROL_ENABLEPROJ (1 << 4)
#define REG_CONTROL_LAUNCHNEXT (1 << 5)
#define REG_CONTROL_WINCHUP (1 << 6)
#define REG_CONTROL_WINCHDOWN (1 << 7)

#define REG_PRESETS_ACKNOWLEDGE 0x00
#define REG_PRESETS_CORRECTED 0x01
#define REG_PRESETS_READY 0x02
#define REG_PRESETS_BEEP 0x03
#define REG_RESETS_CRASH 0x04
#define REG_PRESETS_WARNING 0x05
#define REG_PRESETS_SIREN 0x06
#define REG_PRESETS_ERROR 0x07

//////////////////////////////////////////////////////////////////////////
// Externals
//////////////////////////////////////////////////////////////////////////

/**
 * A container storing all registers implemented on the system.
 */
extern struct Register Registers[REGISTER_COUNT];

//////////////////////////////////////////////////////////////////////////
// Data Structures
//////////////////////////////////////////////////////////////////////////

/**
 * A protocol data storage container.
 */
struct Register{
	uint8_t Id;
	unsigned char Value;
	unsigned char DefaultValue;
	void (*Callback)(uint8_t, unsigned char);
};

//////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////

//Load/Unload (from fifo)

#endif /* REGISTERS_H_ */