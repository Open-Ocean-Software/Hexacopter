/*
 * Manager.h
 *
 * Created: 02/08/2018 9:13:07 PM
 *  Author: nichh
 */ 


#ifndef MANAGER_H_
#define MANAGER_H_

//////////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////////
#include <avr/interrupt.h>

#include "PinLabels.h"

//////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////
#define PULSE_MODULE_COUNT 7		//The total count of the PulseModules array

#define DEFAULTDUTYFREQUENCY 60		//The original Duty Cycle Frequency or the inverse of DutyCyclePeriod (Hz) - Note: assigned in function Initialize
#define MINDUTYFREQUENCY 4			//The absolute minimum Duty Cycle Frequency (Hz)
#define MAXDUTYFREQUENCY 500		//The absolute maxumum Duty Cycle Frequency (Hz)

#define SHIFTREG_TRANSPERIOD 3		//The transition period for setting each bit in the shift register (ms)

//////////////////////////////////////////////////////////////////////////
// Externals
//////////////////////////////////////////////////////////////////////////
/**
 * The duty cycle resolution of all pulse width related modules.
 */
extern unsigned int DutyCyclePeriod; //Must be more than 4Hz and less than 500Hz.  Default is 60Hz as set in Initialize.

/**
 * Contains all pulse width modules.
 */
extern struct PulseRegister PulseModules[PULSE_MODULE_COUNT];

//////////////////////////////////////////////////////////////////////////
// Data Structures
//////////////////////////////////////////////////////////////////////////
/**
 * A pulse-width-controlled module's data container.
 */
struct PulseRegister
{
	enum RegisterId RID;
	unsigned char RegisterNumber;
	unsigned char Alpha;
	unsigned char DutyCycle;
	uint8_t IsOn;
	
	struct PulseRegisterSave Save;
};

/**
 * A pulse-width-controlled module's backup data container.
 */
struct PulseRegisterSave
{
	unsigned char Alpha;
	unsigned char DutyCycle;
};

/**
 * All registers available as outputs on the Atmega.
 */
enum RegisterId
{
	RIDB,
	RIDC,
	RIDD
};

/**
 * Flags available to compare against flagged arguments.
 */
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


//////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// System Controls

/*!
 * Sets up all of the necessary registers and variables used in the manager.
 */
void InitializeManager(void);

/*!
 * Handles the activity of the pulse registers based on system time.
 * @param double: Total elapsed system time.
 */
void HandlePulseRegisters(double);

/*!
 * Changes the register value of the pulse module.
 * @param enum RegisterId: The register the module can be found on.
 * @param unsigned char: The pin number the module can be found on.
 * @param uint8_t: Flags ([0]: Port Active)
 * @see HandlePulseRegisters
 */
void ActivatePulseRegister(enum RegisterId, unsigned char, uint8_t);

/*!
 * Gets a pulse-width module from the registered collection.
 * @param enum RegisterId: The register the module can be found on.
 * @param unsigned char: The pin number the module can be found on.
 * @see PulseModules
 * @return struct PulseRegister: The corresponding pulse register.
 */
struct PulseRegister *FindPulseModule(enum RegisterId, unsigned char);
/*!
 * Gives the corresponding pulse register the specified alpha.
 * @param enum RegisterId: The register the module can be found on.
 * @param unsigned char: The pin number the module can be found on.
 * @param unsigned char: The new alpha value.
 * @see PulseModules
 * @see PulseRegister.Alpha
 */
void ChangePulseRegister(enum RegisterId, unsigned char, unsigned char);
/*!
 * Converts the alpha value to the duty cycle period based on the DutyCyclePeriod.
 * @param unsigned char: The alpha value to be converted.
 * @see DutyCyclePeriod
 * @return unsigned char: The duty cycle period.
 */
unsigned char ConvertAlphaToDuty(unsigned char);

//////////////////////////////////////////////////////////////////////////
// Pulse Width Modulated Controls

/*!
 * Changes the pulse width values of the gimbal's servos.
 * @param unsigned char: X Alpha.
 * @param unsigned char: Y Alpha.
 * @param unsigned char: Z Alpha.
 */
void ToggleGimbal(unsigned char, unsigned char, unsigned char);
/*!
 * Changes the pulse width values of the thermal swivel's servos.
 * @param unsigned char: X Alpha.
 * @param unsigned char: Y Alpha.
 */
void ToggleThermalSwivel(unsigned char, unsigned char);
/*!
 * Changes the pulse width value of the landing gear's servos.
 * @param unsigned char: Alpha.
 */
void ToggleLandingGear(unsigned char);
/*!
 * Changes the pulse width value of the piezo buzzer.
 * @param unsigned char: Alpha.
 */
void TogglePiezo(unsigned char);

//////////////////////////////////////////////////////////////////////////
// Digital Controls

/*!
 * Changes the state of the winch's motors.
 * @param uint8_t: Flags ([0]: Positive; [1]: Negative)
 */
void ToggleWinch(uint8_t);
/*!
 * Changes the state of the projectile launching notification LED.
 * @param uint8_t: Flags ([0]: On)
 */
void ToggleProjectileNotify(uint8_t);
/*!
 * Changes the state of the winch notification LED.
 * @param uint8_t: Flags ([0]: On)
 */
void ToggleWinchNotify(uint8_t);
/*!
 * Changes the state of the landing gear notification LED.
 * @param uint8_t: Flags([0]: On)
 */
void ToggleLandingGearNotify(uint8_t);

//////////////////////////////////////////////////////////////////////////
// Shift Register Controls

/*!
 * Changes the state value of the projectile launch shift register.
 * @param uint8_t: Flags([0-7]: Activate Projectile 0 to 7)
 */
void ToggleLaunchRegister(uint8_t);
/*!
 * Changes the state value of the accessory activity shift register.
 * @param uint8_t: Flags([0-7]: Activate Accessory 0 to 7)
 */
void ToggleAccessoryRegister(uint8_t);


#endif /* MANAGER_H_ */