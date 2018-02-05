/*
 * Manager.h
 *
 * Created: 12/13/2017 1:58:21 PM
 *  Author: nichh
 */ 


#ifndef MANAGER_H_
#define MANAGER_H_

#include "PinLabels.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>


#define DEFAULTDUTYFREQUENCY 60
#define MINDUTYFREQUENCY 4
#define MAXDUTYFREQUENCY 500

#define SHIFTREGSETDELAY 5




extern unsigned int DutyCyclePeriod; //Must be more than 4Hz and less than 500Hz.  Default is 60Hz

extern unsigned char CameraFloodlight;
extern unsigned char LandingFloodlight;
extern unsigned char CameraFloodlightDutyCycle;
extern unsigned char LandingFloodlightDutyCycle;

extern unsigned char CameraOrientLaser;
extern unsigned char CameraLevelLaser;
extern unsigned char ScanLaser;
extern unsigned char CameraOrientLaserDutyCycle;
extern unsigned char CameraLevelLaserDutyCycle;
extern unsigned char ScanLaserDutyCycle;

extern unsigned char EmphasisR;
extern unsigned char EmphasisG;
extern unsigned char EmphasisB;
extern unsigned char SupportR;
extern unsigned char SupportG;
extern unsigned char SupportB;

extern unsigned char StatusR;
extern unsigned char StatusG;
extern unsigned char StatusB;
extern unsigned char StatusRDutyCycle;
extern unsigned char StatusGDutyCycle;
extern unsigned char StatusBDutyCycle;


void InitializeManager(void);

void ToggleCameraFloodlight(unsigned char);
void ToggleLandingFloodlights(unsigned char);

void ToggleCameraOrientLaser(unsigned char);
void ToggleCameraLevelLaser(unsigned char);
void ToggleScanLaser(unsigned char);

void ChangeEmphasisStrips(unsigned char, unsigned char, unsigned char);
void ChangeSupportStrips(unsigned char, unsigned char, unsigned char);

void ChangeStatusNotify(unsigned char, unsigned char, unsigned char);

void ShiftRegCommitData(unsigned char, unsigned char);

unsigned char ConvertAlphaToDuty(unsigned char);

#endif /* MANAGER_H_ */