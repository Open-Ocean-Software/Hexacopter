/*
 * Manager.c
 *
 * Created: 12/13/2017 1:58:07 PM
 *  Author: nichh
 */ 
#include "Manager.h"


unsigned int DutyCyclePeriod = 0; //Must be more than 4Hz and less than 500Hz.  Default is 60Hz

unsigned char CameraFloodlight = 0;
unsigned char LandingFloodlight = 0;
unsigned char CameraFloodlightDutyCycle = 0;
unsigned char LandingFloodlightDutyCycle = 0;

unsigned char CameraOrientLaser = 0;
unsigned char CameraLevelLaser = 0;
unsigned char ScanLaser = 0;
unsigned char CameraOrientLaserDutyCycle = 0;
unsigned char CameraLevelLaserDutyCycle = 0;
unsigned char ScanLaserDutyCycle = 0;

unsigned char EmphasisR = 0x00;
unsigned char EmphasisG = 0x00;
unsigned char EmphasisB = 0x00;
unsigned char SupportR = 0x00;
unsigned char SupportG = 0x00;
unsigned char SupportB = 0x00;

unsigned char StatusR = 0;
unsigned char StatusG = 0;
unsigned char StatusB = 0;
unsigned char StatusRDutyCycle = 0;
unsigned char StatusGDutyCycle = 0;
unsigned char StatusBDutyCycle = 0;


void InitializeManager(void)
{
	unsigned char floodlights = (1 << CAMFLOODLIGHTS) | (1 << LANDFLOODLIGHTS);
	//Enable the floodlights for output
	FLOODLIGHTREG |= floodlights;
	//Turn off all floodlights
	FLOODLIGHTPORT &= ~floodlights;
	
	unsigned char lasers = (1 << CAMORIENTLASER) | (1 << CAMLEVELLASER) | (1 << SCANLASER);
	//Enable the lasers for output
	LASERREG |= lasers;
	//Turn off all lasers
	LASERPORT &= ~lasers;
	
	unsigned char dataline = (1 << SR_DATA);
	unsigned char selectlines = (1 << SRS_EMPHASISR) | (1 << SRS_EMPHASISG) | (1 << SRS_EMPHASISB) | (1 << SRS_SUPPORTR) | (1 << SRS_SUPPORTG) | (1 << SRS_SUPPORTB);
	//Enable the shift registers for output
	SHIFTREGDATAREG |= dataline;
	SHIFTREGSELECTREG |= selectlines;
	//Turn off shift register lines
	SHIFTREGDATAPORT &= ~dataline;
	SHIFTREGSELECTPORT &= ~selectlines;
	
	unsigned char statusnotify = (1 << STATUSNOTIFYR) | (1 << STATUSNOTIFYG) | (1 << STATUSNOTIFYB);
	//Enable the status notify LED for output
	STATUSNOTIFYREG |= statusnotify;
	//Turn off status notify
	STATUSNOTIFYPORT &= ~statusnotify;
	
	//Set initial duty cycle period
	DutyCyclePeriod = (unsigned int)(1.0f / ((float)DEFAULTDUTYFREQUENCY) * 1000.0f);
}

void ToggleCameraFloodlight(unsigned char alpha)
{
	CameraFloodlight = alpha;
	CameraFloodlightDutyCycle = ConvertAlphaToDuty(alpha);
}
void ToggleLandingFloodlights(unsigned char alpha)
{
	LandingFloodlight = alpha;
	LandingFloodlightDutyCycle = ConvertAlphaToDuty(alpha);
}

void ToggleCameraOrientLaser(unsigned char alpha)
{
	CameraOrientLaser = alpha;
	CameraOrientLaserDutyCycle = ConvertAlphaToDuty(alpha);
}
void ToggleCameraLevelLaser(unsigned char alpha)
{
	CameraLevelLaser = alpha;
	CameraLevelLaserDutyCycle = ConvertAlphaToDuty(alpha);
}
void ToggleScanLaser(unsigned char alpha)
{
	ScanLaser = alpha;
	ScanLaserDutyCycle = ConvertAlphaToDuty(alpha);
}

void ChangeEmphasisStrips(unsigned char r, unsigned char g, unsigned char b)
{
	EmphasisR = r;
	EmphasisG = g;
	EmphasisB = b;
	
	ShiftRegCommitData(r, SRS_EMPHASISR);
	_delay_ms(SHIFTREGSETDELAY);
	ShiftRegCommitData(g, SRS_EMPHASISG);
	_delay_ms(SHIFTREGSETDELAY);
	ShiftRegCommitData(b, SRS_EMPHASISB);
	_delay_ms(SHIFTREGSETDELAY);
}
void ChangeSupportStrips(unsigned char r, unsigned char g, unsigned char b)
{
	SupportR = r;
	SupportG = g;
	SupportB = b;
	
	ShiftRegCommitData(r, SRS_SUPPORTR);
	_delay_ms(SHIFTREGSETDELAY);
	ShiftRegCommitData(g, SRS_SUPPORTG);
	_delay_ms(SHIFTREGSETDELAY);
	ShiftRegCommitData(b, SRS_SUPPORTB);
	_delay_ms(SHIFTREGSETDELAY);
}

void ChangeStatusNotify(unsigned char r, unsigned char g, unsigned char b)
{
	StatusR = r;
	StatusG = g;
	StatusB = b;
	
	StatusRDutyCycle = ConvertAlphaToDuty(r);
	StatusGDutyCycle = ConvertAlphaToDuty(g);
	StatusBDutyCycle = ConvertAlphaToDuty(b);
}

void ShiftRegCommitData(unsigned char alpha, unsigned char select)
{
	SHIFTREGSELECTPORT |= (1 << select);
	for(int i = 0; i < 8; i++)
	{
		if((alpha & (1 << i)) == (1 << i))
		{
			SHIFTREGDATAPORT |= (1 << SR_DATA);
		}
		else
		{
			SHIFTREGDATAPORT &= ~(1 << SR_DATA);
		}
		_delay_ms(SHIFTREGSETDELAY);
	}
	SHIFTREGSELECTPORT &= ~(1 << select);
}

/*
 * Converts a brightness ratio to a duty cycle based on the current duty cycle period.
 */
unsigned char ConvertAlphaToDuty(unsigned char alpha)
{
	return (unsigned char)(((float)alpha / 255.0f) * (float)DutyCyclePeriod);
}