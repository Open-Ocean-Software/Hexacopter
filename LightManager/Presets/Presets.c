/*
 * Presets.c
 *
 * Created: 02/08/2018 9:15:26 PM
 *  Author: nichh
 */ 

#include "Presets/Presets.h"

void (*PRESETS)(double, uint8_t)[PRESET_COUNT] PROGMEM =
{
	&Preset_On,
	&Preset_Spin,
	&Preset_Bounce,
	&Preset_Flash,
	&Preset_Corrected,
	&Preset_Alert,
	&Preset_Warning,
	&Preset_Danger
};

void Preset_On(double t, uint8_t *resolved)
{
	static double starttime = -1.0;
	static uint8_t flag = 0x00;
	static unsigned char emphasissave[] = {0x00, 0x00, 0x00};
	static unsigned char supportsave[] = {0x00, 0x00, 0x00};
	
	if(starttime < 0)
	{
		emphasissave = {EmphasisR, EmphasisG, EmphasisB};
		supportsave = {SupportR, SupportG, SupportB};
		starttime = t;
	}
	else if(starttime >= PRESET_ON_DURATION)
	{
		ChangeEmphasisStrips(emphasissave[0], emphasissave[1], emphasissave[2]);
		ChangeSupportStrips(supportsave[0], supportsave[1], supportsave[2]);
		starttime = -1.0;
		flag = 0x00;
		*resolved = 0x01;
		return;
	}
	
	double time = t - starttime;
	
	if((int)(time / PRESET_ON_PERIOD) % 2 == 0 && flag == 0x00)
	{
		ChangeEmphasisStrips(0x00, 0x00, 0xFF);
		ChangeSupportStrips(0x00, 0x00, 0x00);
		flag = 0x01;
	}
	else if((int)(time / PRESET_ON_PERIOD) % 2 != 0 && flag == 0x01)
	{
		ChangeEmphasisStrips(0x00, 0x00, 0x00);
		ChangeSupportStrips(0x00, 0x00, 0x00);
		flag = 0x00;
	}
	
	*resolved = 0x00;
}

void Preset_Spin(double t, uint8_t *resolved)
{
	//TODO: Implement
}

void Preset_Bounce(double t, uint8_t *resolved)
{
	//TODO: Implement
}

void Preset_Flash(double t, uint8_t *resolved)
{
	//TODO: Implement
}

void Preset_Corrected(double t, uint8_t *resolved)
{
	//TODO: Implement
}

void Preset_Alert(double t, uint8_t *resolved)
{
	//TODO: Implement
}

void Preset_Warning(double t, uint8_t *resolved)
{
	//TODO: Implement
}

void Preset_Danger(double t, uint8_t *resolved)
{
	//TODO: Implement
}