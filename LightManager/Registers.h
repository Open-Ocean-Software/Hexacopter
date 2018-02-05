/*
 * Registers.h
 *
 * Created: 01/24/2018 2:10:13 PM
 *  Author: nichh
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <stdbool.h>

#include "Manager.h"

//////////////////////////////////////////////////////////////////////////
// REGISTER KEYS
//////////////////////////////////////////////////////////////////////////
#define REG_CONTROL 0x01
#define REG_PRESETS 0x02

#define REG_EMPHASISR 0x03
#define REG_EMPHASISG 0x04
#define REG_EMPHASISB 0x05
#define REG_SUPPORTR 0x06
#define REG_SUPPORTG 0x07
#define REG_SUPPORTB 0x08

#define REG_CAMFLDALPHA 0x09
#define REG_LANDFLDALPHA 0x0A
#define REG_CAMPTLSRALPHA 0x0B
#define REG_CAMLVLLSRALPHA 0x0C
#define REG_SCANLSRALPHA 0x0D

#define REG_STATNOTIFYR 0x0E
#define REG_STATNOTIFYG 0x0F
#define REG_STATNOTIFYB 0x10


//////////////////////////////////////////////////////////////////////////
// REGISTER DEFAULT VALUES
//////////////////////////////////////////////////////////////////////////
#define REG_DEFAULT_CONTROL 0xB9
#define REG_DEFAULT_PRESETS 0x00

#define REG_DEFAULT_EMPHASISR 0x00
#define REG_DEFAULT_EMPHASISG 0x00
#define REG_DEFAULT_EMPHASISB 0x00
#define REG_DEFAULT_SUPPORTR 0x00
#define REG_DEFAULT_SUPPORTG 0x00
#define REG_DEFAULT_SUPPORTB 0x00

#define REG_DEFAULT_CAMFLDALPHA 0x00
#define REG_DEFAULT_LANDFLDALPHA 0x00
#define REG_DEFAULT_CAMPTLSRALPHA 0x00
#define REG_DEFAULT_CAMLVLLSRALPHA 0x00
#define REG_DEFAULT_SCANLSRALPHA 0x00

#define REG_DEFAULT_STATNOTIFYR 0x00
#define REG_DEFAULT_STATNOTIFYG 0x00
#define REG_DEFAULT_STATNOTIFYB 0x00


//////////////////////////////////////////////////////////////////////////
// CONSTANTS
//////////////////////////////////////////////////////////////////////////
#define REGISTER_COUNT 16

#define READ_FILTER_VALUE 0x00
#define WRITE_FILTER_VALUE 0x80
#define READWRITE_FILTER 0x80

#define RES_INC_POWERSAVING 0.016384
#define RES_INC_LOW 0.004096
#define RES_INC_MEDIUM 0.001024
#define RES_INC_HIGH 0.000128


//////////////////////////////////////////////////////////////////////////
// REGISTER VALUE LABELS
//////////////////////////////////////////////////////////////////////////
#define REGVAL_CONTROL_ENABLE 0
#define REGVAL_CONTROL_ALLOFF 1
#define REGVAL_CONTROL_ALLON 2
#define REGVAL_CONTROL_ENABLESTRIPS 3
#define REGVAL_CONTROL_ENABLEUTILITIES 4
#define REGVAL_CONTROL_ENABLENOTIFY 5
#define REGVAL_CONTROL_LOWPWRMODE 6
#define REGVAL_CONTROL_RESETREG 7

#define REGVAL_PRESETS_ON 0
#define REGVAL_PRESETS_SPIN 1
#define REGVAL_PRESETS_BOUNCE 2
#define REGVAL_PRESETS_FLASH 3
#define REGVAL_PRESETS_CORRECTED 4
#define REGVAL_PRESETS_ALERT 5
#define REGVAL_PRESETS_WARNING 6
#define REGVAL_PRESETS_DANGER 7


//////////////////////////////////////////////////////////////////////////
// REGISTER EVENTS
//////////////////////////////////////////////////////////////////////////
 extern bool Enabled;
 extern bool AllOff;
 extern bool AllOn;
 extern bool EnableStrips;
 extern bool EnableUtilities;
 extern bool EnableNotify;
 extern bool LowPowerMode;
 
 
 void Altered_Control(uint8_t, unsigned char);
 void Altered_Presets(uint8_t, unsigned char);

 void Altered_Emphasis(uint8_t, unsigned char);
 void Altered_Support(uint8_t, unsigned char);

 void Altered_Floodlights(uint8_t, unsigned char);
 void Altered_Laser(uint8_t, unsigned char);

 void Altered_StatusNotify(uint8_t, unsigned char);



 

 //////////////////////////////////////////////////////////////////////////
 // REGISTER STRUCTURES
 //////////////////////////////////////////////////////////////////////////
 struct Register{
	 uint8_t Id;
	 unsigned char Value;
	 unsigned char DefaultValue;
	 void (*Callback)(uint8_t, unsigned char);
 };

 extern struct Register REGISTERS[REGISTER_COUNT];
 
 
 enum TimerResolutions{
	 PowerSaving,
	 Low,
	 Medium,
	 High
 };
 extern const enum TimerResolutions DefaultTimerResolution;
 extern enum TimerResolutions TimerResolution;
 
 extern double TimerOverflowIncrement;
 
 void SetTimerResolution(enum TimerResolutions);
 

#endif /* REGISTERS_H_ */