/*
 * Rendering.h
 *
 * Created: 02/03/2018 7:09:50 PM
 *  Author: nichh
 */ 


#ifndef RENDERING_H_
#define RENDERING_H_

#include <stdbool.h>

#include "Manager.h"

#define RENDER_EVENT_COUNT 8

extern bool CameraFloodlightOn;
extern bool LandingFloodlightOn;
extern bool CameraOrientLaserOn;
extern bool CameraLevelLaserOn;
extern bool ScanLaserOn;
extern bool StatusROn;
extern bool StatusGOn;
extern bool StatusBOn;

void Render_CameraFloodlight(int);
void Render_LandingFloodlight(int);

void Render_CameraOrientLaser(int);
void Render_CameraLevelLaser(int);
void Render_ScanLaser(int);

void Render_StatusR(int);
void Render_StatusG(int);
void Render_StatusB(int);

extern void (*RenderEvents[RENDER_EVENT_COUNT])(int);

#endif /* RENDERING_H_ */