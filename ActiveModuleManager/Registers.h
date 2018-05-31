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
#include "Manager.h"

//////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// System
#define REGISTER_COUNT 11
#define READ_FILTER_VALUE 0x00
#define WRITE_FILTER_VALUE 0x80
#define READWRITE_FILTER_VALUE 0x80

#define EEPROM_BASE_REGISTER 0x01

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

//////////////////////////////////////////////////////////////////////////
// System Controls

/*!
 * Sets up the register functionality.
 */
void InitializeRegisters(void);

/*!
 * Loads saved register data from the microcontroller's FIFO.
 */
void LoadDataFromFIFO(void);

/*!
 * Saves latest register data to the microcontroller's FIFO.
 */
void UnloadDataToFIFO(void);

/*!
 * Finds the register matching an id.
 * @param uint8_t: The Id of the register
 * @see Registers
 * @return struct Register *: A reference to the register's structure
 */
struct Register *FindRegister(uint8_t);

/*!
 * Changes the register matching an id.
 * @param uint8_t: The Id of the register
 * @param unsigned char: The new value for the register
 * @see Registers
 */
void ChangeRegister(uint8_t, unsigned char);

/*!
 * Called to handle protocol changes in registers.
 */
void HandleRegisters(void);


//////////////////////////////////////////////////////////////////////////
// Register Alterations

/*!
 * Activated when the control register is changed.
 * @param uint8_t: The Register Id accessed.
 * @param unsigned char: The command sent.
 */
void RegAlt_Control(uint8_t, unsigned char);

/*!
 * Activated when the presets register is changed.
 * @param uint8_t: The Register Id accessed.
 * @param unsigned char: The command sent.
 */
void RegAlt_Presets(uint8_t, unsigned char);

/*!
 * Activated when the gimbal register is changed.
 * @param uint8_t: The Register Id accessed.
 * @param unsigned char: The command sent.
 */
void RegAlt_Gimbal(uint8_t, unsigned char);

/*!
 * Activated when the landing gear register is changed.
 * @param uint8_t: The Register Id accessed.
 * @param unsigned char: The command sent.
 */
void RegAlt_LandingGear(uint8_t, unsigned char);

/*!
 * Activated when the thermal swivel register is changed.
 * @param uint8_t: The Register Id accessed.
 * @param unsigned char: The command sent.
 */
void RegAlt_ThermalSwivel(uint8_t, unsigned char);

/*!
 * Activated when the piezo buzzer register is changed.
 * @param uint8_t: The Register Id accessed.
 * @param unsigned char: The command sent.
 */
void RegAlt_PiezoBuzzer(uint8_t, unsigned char);

/*!
 * Activated when the projectiles register is changed.
 * @param uint8_t: The Register Id accessed.
 * @param unsigned char: The command sent.
 */
void RegAlt_Projectiles(uint8_t, unsigned char);

/*!
 * Activated when the accessories register is changed.
 * @param uint8_t: The Register Id accessed.
 * @param unsigned char: The command sent.
 */
void RegAlt_Accessories(uint8_t, unsigned char);

#endif /* REGISTERS_H_ */