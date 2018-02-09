/*
 * Presets.h
 *
 * Created: 01/31/2018 11:16:09 PM
 *  Author: Nicholas
 */ 


#ifndef PRESETS_H_
#define PRESETS_H_

#define PRESET_COUNT 8

void Preset_On(double, uint8_t);
void Preset_Spin(double, uint8_t);
void Preset_Bounce(double, uint8_t);
void Preset_Flash(double, uint8_t);
void Preset_Corrected(double, uint8_t);
void Preset_Alert(double, uint8_t);
void Preset_Warning(double, uint8_t);
void Preset_Danger(double, uint8_t);

extern void (*PRESETS)(double, uint8_t)[PRESET_COUNT];

#endif /* PRESETS_H_ */