/*
 * Registers.c
 *
 * Created: 01/29/2018 12:08:53 AM
 *  Author: Nicholas
 */

#include "Registers.h"
 
 
bool Enabled = true;
bool AllOff = false;
bool AllOn = false;
bool EnableStrips = true;
bool EnableUtilities = true;
bool EnableNotify = true;
bool LowPowerMode = false;

const enum TimerResolutions DefaultTimerResolution = Low;
enum TimerResolutions TimerResolution = Low;

double TimerOverflowIncrement = 0;
 
struct Register REGISTERS[REGISTER_COUNT] =
{
	{ REG_CONTROL, REG_DEFAULT_CONTROL, REG_DEFAULT_CONTROL, &Altered_Control },
	{ REG_PRESETS, REG_DEFAULT_PRESETS, REG_DEFAULT_PRESETS, &Altered_Presets },
	{ REG_EMPHASISR, REG_DEFAULT_EMPHASISR, REG_DEFAULT_EMPHASISR, &Altered_Emphasis },
	{ REG_EMPHASISG, REG_DEFAULT_EMPHASISG, REG_DEFAULT_EMPHASISG, &Altered_Emphasis },
	{ REG_EMPHASISB, REG_DEFAULT_EMPHASISB, REG_DEFAULT_EMPHASISB, &Altered_Emphasis },
	{ REG_SUPPORTR, REG_DEFAULT_SUPPORTR, REG_DEFAULT_SUPPORTR, &Altered_Support },
	{ REG_SUPPORTG, REG_DEFAULT_SUPPORTG, REG_DEFAULT_SUPPORTG, &Altered_Support },
	{ REG_SUPPORTB, REG_DEFAULT_SUPPORTB, REG_DEFAULT_SUPPORTB, &Altered_Support },
	{ REG_CAMFLDALPHA, REG_DEFAULT_CAMFLDALPHA, REG_DEFAULT_CAMFLDALPHA, &Altered_Floodlights },
	{ REG_LANDFLDALPHA, REG_DEFAULT_LANDFLDALPHA, REG_DEFAULT_LANDFLDALPHA, &Altered_Floodlights },
	{ REG_CAMPTLSRALPHA, REG_DEFAULT_CAMPTLSRALPHA, REG_DEFAULT_CAMPTLSRALPHA, &Altered_Laser },
	{ REG_CAMLVLLSRALPHA, REG_DEFAULT_CAMLVLLSRALPHA, REG_DEFAULT_CAMLVLLSRALPHA, &Altered_Laser },
	{ REG_SCANLSRALPHA, REG_DEFAULT_SCANLSRALPHA, REG_DEFAULT_SCANLSRALPHA, &Altered_Laser },
	{ REG_STATNOTIFYR, REG_DEFAULT_STATNOTIFYR, REG_DEFAULT_STATNOTIFYR, &Altered_StatusNotify },
	{ REG_STATNOTIFYG, REG_DEFAULT_STATNOTIFYG, REG_DEFAULT_STATNOTIFYG, &Altered_StatusNotify },
	{ REG_STATNOTIFYB, REG_DEFAULT_STATNOTIFYB, REG_DEFAULT_STATNOTIFYB, &Altered_StatusNotify }
};
 
 
 void Altered_Control(uint8_t id, unsigned char value)
 {
	 
	 static bool utilitiessaved = false;
	 static unsigned char floodlightsdc[2] = { 0x00, 0x00 };
	 static unsigned char lasersdc[3] = { 0x00, 0x00, 0x00 };
	 if(utilitiessaved == false)
	 {
		 floodlightsdc[0] = CameraFloodlight;
		 floodlightsdc[1] = LandingFloodlight;
		 lasersdc[0] = CameraOrientLaser;
		 lasersdc[1] = CameraLevelLaser;
		 lasersdc[2] = ScanLaser;
	 }
	 
	 static bool stripssaved = false;
	 static unsigned char emphasisrgb[3] = { 0x00, 0x00, 0x00 };
	 static unsigned char supportrgb[3] = { 0x00, 0x00, 0x00 };
	 if(stripssaved == false)
	 {
		 emphasisrgb[0] = EmphasisR;
		 emphasisrgb[1] = EmphasisG;
		 emphasisrgb[2] = EmphasisB;
		 supportrgb[0] = SupportR;
		 supportrgb[1] = SupportG;
		 supportrgb[2] = SupportB;
	 }
	 
	 static bool statussaved = false;
	 static unsigned char statusrgb[3] = { 0x00, 0x00, 0x00 };
	 if(statussaved == false)
	 {
		 statusrgb[0] = StatusR;
		 statusrgb[1] = StatusG;
		 statusrgb[2] = StatusB;
	 }
	 
	 
	 if((value & (1 << REGVAL_CONTROL_ENABLE)) == (1 << REGVAL_CONTROL_ENABLE))
	 {
		 if(Enabled == false)
		 {
			 Enabled = true;
			 stripssaved = false;
		 }
		 
		 if((value & (1 << REGVAL_CONTROL_ENABLESTRIPS)) == (1 << REGVAL_CONTROL_ENABLESTRIPS) && EnableStrips == false)
		 {
			EnableStrips = true;

			ChangeEmphasisStrips(emphasisrgb[0], emphasisrgb[1], emphasisrgb[2]);
			ChangeSupportStrips(supportrgb[0], supportrgb[1], supportrgb[2]);

			stripssaved = false;
		 }
		 else if((value & (1 << REGVAL_CONTROL_ENABLESTRIPS)) != (1 << REGVAL_CONTROL_ENABLESTRIPS) && EnableStrips == true)
		 {
			EnableStrips = false;

			ChangeEmphasisStrips(0x00, 0x00, 0x00);
			ChangeSupportStrips(0x00, 0x00, 0x00);
			
			stripssaved = true;
		 }

		 if((value & (1 << REGVAL_CONTROL_ENABLEUTILITIES)) == (1 << REGVAL_CONTROL_ENABLEUTILITIES) && EnableUtilities == false)
		 {
			EnableUtilities = true;

			ToggleCameraFloodlight(floodlightsdc[0]);
			ToggleLandingFloodlights(floodlightsdc[1]);
			ToggleCameraOrientLaser(lasersdc[0]);
			ToggleCameraLevelLaser(lasersdc[1]);
			ToggleScanLaser(lasersdc[2]);

			utilitiessaved = false;
		 }
		 else if((value & (1 << REGVAL_CONTROL_ENABLEUTILITIES)) != (1 << REGVAL_CONTROL_ENABLEUTILITIES) && EnableUtilities == true)
		 {
			EnableUtilities = false;

			ToggleCameraFloodlight(0x00);
			ToggleLandingFloodlights(0x00);
			ToggleCameraOrientLaser(0x00);
			ToggleCameraLevelLaser(0x00);
			ToggleScanLaser(0x00);

			utilitiessaved = true;
		 }

		 if((value & (1 << REGVAL_CONTROL_ENABLENOTIFY)) == (1 << REGVAL_CONTROL_ENABLENOTIFY) && EnableNotify == false)
		 {
			EnableNotify = true;

			ChangeStatusNotify(statusrgb[0], statusrgb[1], statusrgb[2]);

			statussaved = false;
		 }
		 else if((value & (1 << REGVAL_CONTROL_ENABLENOTIFY)) != (1 << REGVAL_CONTROL_ENABLENOTIFY) && EnableNotify == true)
		 {
			EnableNotify = false;

			ChangeStatusNotify(0x00, 0x00, 0x00);

			statussaved = true;
		 }
		 
		 
		 if((value & (1 << REGVAL_CONTROL_ALLOFF)) == (1 << REGVAL_CONTROL_ALLOFF) && AllOff == false)
		 {
			 AllOff = true;

			 ToggleCameraFloodlight(0x00);
			 ToggleLandingFloodlights(0x00);
			 ToggleCameraOrientLaser(0x00);
			 ToggleCameraLevelLaser(0x00);
			 ToggleScanLaser(0x00);
			 ChangeEmphasisStrips(0x00, 0x00, 0x00);
			 ChangeSupportStrips(0x00, 0x00, 0x00);
			 ChangeStatusNotify(0x00, 0x00, 0x00);

			 utilitiessaved = true;
			 stripssaved = true;
			 statussaved = true;
		 }
		 else
		 {
			AllOff = false;
		 }

		 if((value & (1 << REGVAL_CONTROL_ALLON)) == (1 << REGVAL_CONTROL_ALLON) && AllOn == false && AllOff == false)
		 {
			 AllOn = true;

			 ToggleCameraFloodlight(0xFF);
			 ToggleLandingFloodlights(0xFF);
			 ToggleCameraOrientLaser(0xFF);
			 ToggleCameraLevelLaser(0xFF);
			 ToggleScanLaser(0xFF);
			 ChangeEmphasisStrips(0xFF, 0xFF, 0xFF);
			 ChangeSupportStrips(0xFF, 0xFF, 0xFF);
			 ChangeStatusNotify(0xFF, 0xFF, 0xFF);

			 utilitiessaved = true;
			 stripssaved = true;
			 statussaved = true;
		 }
		 else
		 {
			AllOn = false;
		 }

		 if(AllOff == false && AllOn == false)
		 {
			 ToggleCameraFloodlight(floodlightsdc[0]);
			 ToggleLandingFloodlights(floodlightsdc[1]);
			 ToggleCameraOrientLaser(lasersdc[0]);
			 ToggleCameraLevelLaser(lasersdc[1]);
			 ToggleScanLaser(lasersdc[2]);
			 ChangeEmphasisStrips(emphasisrgb[0], emphasisrgb[1], emphasisrgb[2]);
			 ChangeSupportStrips(supportrgb[0], supportrgb[1], supportrgb[2]);
			 ChangeStatusNotify(statusrgb[0], statusrgb[1], statusrgb[2]);
			 
			 if(EnableUtilities == true)
			 {
				utilitiessaved = false;
			 }
			 if(EnableStrips == true)
			 {
				stripssaved = false;
			 }
			 if(EnableNotify == true)
			 {
				statussaved = false;
			 }
		 }


		 if((value & (1 << REGVAL_CONTROL_LOWPWRMODE)) == (1 << REGVAL_CONTROL_LOWPWRMODE) && LowPowerMode == false)
		 {
			LowPowerMode = true;
			SetTimerResolution(PowerSaving);
		 }
		 else if((value & (1 << REGVAL_CONTROL_LOWPWRMODE)) != (1 << REGVAL_CONTROL_LOWPWRMODE) && LowPowerMode == true)
		 {
			LowPowerMode = false;
			SetTimerResolution(DefaultTimerResolution);
		 }


		 if((value & (1 << REGVAL_CONTROL_RESETREG)) == (1 << REGVAL_CONTROL_RESETREG))
		 {
			for(int i = 0; i < REGISTER_COUNT; i++)
			{
				REGISTERS[i].Value = REGISTERS[i].DefaultValue;
			}
		 }
	 }
	 else
	 {
		 Enabled = false;

		 ChangeEmphasisStrips(0, 0, 0);
		 ChangeSupportStrips(0, 0, 0);
		 stripssaved = true;
	 }
 }
 void Altered_Presets(uint8_t id, unsigned char value)
 {
	//TODO: implement presets
 }


 void Altered_Emphasis(uint8_t id, unsigned char value)
 {
	if(id == REG_EMPHASISR)
	{
		ChangeEmphasisStrips(value, EmphasisG, EmphasisB);
	}
	else if(id == REG_EMPHASISG)
	{
		ChangeEmphasisStrips(EmphasisR, value, EmphasisB);
	}
	else if(id == REG_EMPHASISB)
	{
		ChangeEmphasisStrips(EmphasisR, EmphasisG, value);
	}
 }
 void Altered_Support(uint8_t id, unsigned char value)
 {
	if(id == REG_SUPPORTR)
	{
		ChangeSupportStrips(value, SupportG, SupportB);
	}
	else if(id == REG_SUPPORTG)
	{
		ChangeSupportStrips(SupportR, value, SupportB);
	}
	else if(id == REG_SUPPORTB)
	{
		ChangeSupportStrips(SupportR, SupportG, value);
	}
 }


 void Altered_Floodlights(uint8_t id, unsigned char value)
 {
	if(id == REG_CAMFLDALPHA)
	{
		ToggleCameraFloodlight(value);
	}
	else if(id == REG_LANDFLDALPHA)
	{
		ToggleLandingFloodlights(value);
	}
 }
 void Altered_Laser(uint8_t id, unsigned char value)
 {
	if(id == REG_CAMPTLSRALPHA)
	{
		ToggleCameraOrientLaser(value);
	}
	else if(id == REG_CAMLVLLSRALPHA)
	{
		ToggleCameraLevelLaser(value);
	}
	else if(id == REG_SCANLSRALPHA)
	{
		ToggleScanLaser(value);
	}
 }


 void Altered_StatusNotify(uint8_t id, unsigned char value)
 {
	if(id == REG_STATNOTIFYR)
	{
		ChangeStatusNotify(value, StatusG, StatusB);
	}
	else if(id == REG_STATNOTIFYG)
	{
		ChangeStatusNotify(StatusR, value, StatusB);
	}
	else if(id == REG_STATNOTIFYB)
	{
		ChangeStatusNotify(StatusR, StatusG, value);
	}
 }







void SetTimerResolution(enum TimerResolutions res)
{
	if(TimerResolution == res)
	{
		return;
	}
	TimerResolution = res;
	
	if(res == PowerSaving)
	{
		//F_CPU / 1024
		//TCCR0 => 101
		TCCR0 &= ~(1 << CS01);
		TCCR0 |= (1 << CS02) | (1 << CS00);
		TimerOverflowIncrement = RES_INC_POWERSAVING;
	}
	else if(res == Low)
	{
		//F_CPU / 256
		//TCCR0 => 100
		TCCR0 &= ~((1 << CS01) | (1 << CS00));
		TCCR0 |= (1 << CS02);
		TimerOverflowIncrement = RES_INC_LOW;
	}
	else if(res == Medium)
	{
		//F_CPU / 64
		//TCCR0 => 011
		TCCR0 &= ~(1 << CS02);
		TCCR0 |= (1 << CS01) | (1 << CS00);
		TimerOverflowIncrement = RES_INC_MEDIUM;
	}
	else if(res == High)
	{
		//F_CPU / 8
		//TCCR0 => 010
		TCCR0 &= ~((1 << CS02) | (1 << CS00));
		TCCR0 |= (1 << CS01);
		TimerOverflowIncrement = RES_INC_HIGH;
	}
	else
	{
		SetTimerResolution(DefaultTimerResolution);
	}
}