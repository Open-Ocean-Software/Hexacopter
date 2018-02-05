/*
 * Rendering.c
 *
 * Created: 02/03/2018 7:08:41 PM
 *  Author: nichh
 */ 

#include "Rendering.h"

bool CameraFloodlightOn = false;
bool LandingFloodlightOn = false;
bool CameraOrientLaserOn = false;
bool CameraLevelLaserOn = false;
bool ScanLaserOn = false;
bool StatusROn = false;
bool StatusGOn = false;
bool StatusBOn = false;

void (*RenderEvents[RENDER_EVENT_COUNT])(int) =
{
	&Render_CameraFloodlight,
	&Render_LandingFloodlight,
	&Render_CameraOrientLaser,
	&Render_CameraLevelLaser,
	&Render_ScanLaser,
	&Render_StatusR,
	&Render_StatusG,
	&Render_StatusB
};


void Render_CameraFloodlight(int ms)
{
	if(ms <= CameraFloodlightDutyCycle && CameraFloodlightOn == false)
	{
		FLOODLIGHTPORT |= (1 << CAMFLOODLIGHTS);
		CameraFloodlightOn = true;
	}
	else if(ms > CameraFloodlightDutyCycle && CameraFloodlightOn == true)
	{
		FLOODLIGHTPORT &= ~(1 << CAMFLOODLIGHTS);
		CameraFloodlightOn = false;
	}
}
void Render_LandingFloodlight(int ms)
{
	if(ms <= LandingFloodlightDutyCycle && LandingFloodlightOn == false)
	{
		FLOODLIGHTPORT |= (1 << LANDFLOODLIGHTS);
		LandingFloodlightOn = true;
	}
	else if(ms > LandingFloodlightDutyCycle && LandingFloodlightOn == true)
	{
		FLOODLIGHTPORT &= ~(1 << LANDFLOODLIGHTS);
		LandingFloodlightOn = false;
	}
}


void Render_CameraOrientLaser(int ms)
{
	if(ms <= CameraOrientLaserDutyCycle && CameraOrientLaserOn == false)
	{
		LASERPORT |= (1 << CAMORIENTLASER);
		CameraOrientLaserOn = true;
	}
	else if(ms > CameraOrientLaserDutyCycle && CameraOrientLaserOn == true)
	{
		LASERPORT &= ~(1 << CAMORIENTLASER);
		CameraOrientLaserOn = false;
	}
}
void Render_CameraLevelLaser(int ms)
{
	if(ms <= CameraLevelLaserDutyCycle && CameraLevelLaserOn == false)
	{
		LASERPORT |= (1 << CAMLEVELLASER);
		CameraLevelLaserOn = true;
	}
	else if(ms > CameraLevelLaserDutyCycle && CameraLevelLaserOn == true)
	{
		LASERPORT &= ~(1 << CAMLEVELLASER);
		CameraLevelLaserOn = false;
	}
}
void Render_ScanLaser(int ms)
{
	if(ms <= ScanLaserDutyCycle && ScanLaserOn == false)
	{
		LASERPORT |= (1 << SCANLASER);
		ScanLaserOn = true;
	}
	else if(ms > ScanLaserDutyCycle && ScanLaserOn == true)
	{
		LASERPORT &= ~(1 << SCANLASER);
		ScanLaserOn = false;
	}
}


void Render_StatusR(int ms)
{
	if(ms <= StatusRDutyCycle && StatusROn == false)
	{
		STATUSNOTIFYPORT |= (1 << STATUSNOTIFYR);
		StatusROn = true;
	}
	else if(ms > StatusRDutyCycle && StatusROn == true)
	{
		STATUSNOTIFYPORT &= ~(1 << STATUSNOTIFYR);
		StatusROn = false;
	}
}
void Render_StatusG(int ms)
{
	if(ms <= StatusGDutyCycle && StatusGOn == false)
	{
		STATUSNOTIFYPORT |= (1 << STATUSNOTIFYG);
		StatusGOn = true;
	}
	else if(ms > StatusGDutyCycle && StatusGOn == true)
	{
		STATUSNOTIFYPORT &= ~(1 << STATUSNOTIFYG);
		StatusGOn = false;
	}
}
void Render_StatusB(int ms)
{
	if(ms <= StatusBDutyCycle && StatusBOn == false)
	{
		STATUSNOTIFYPORT |= (1 << STATUSNOTIFYB);
		StatusGOn = true;
	}
	else if(ms > StatusBDutyCycle && StatusBOn == true)
	{
		STATUSNOTIFYPORT &= ~(1 << STATUSNOTIFYB);
		StatusBOn = false;
	}
}