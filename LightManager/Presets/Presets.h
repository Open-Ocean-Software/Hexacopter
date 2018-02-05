/*
 * Presets.h
 *
 * Created: 01/31/2018 11:16:09 PM
 *  Author: Nicholas
 */ 


#ifndef PRESETS_H_
#define PRESETS_H_

#include <stdbool.h>

#define FLOODLIGHT_COUNT 2
#define LASER_COUNT 3
#define STATUSNOTIFY_COUNT 3

#define STRUT_COUNT 8

struct PresetState {
	bool EnableUtilityAlteration;
	
	unsigned char Floodlights[FLOODLIGHT_COUNT];
	unsigned char Lasers[LASER_COUNT];
	unsigned char StatusNotify[STATUSNOTIFY_COUNT];
	
	struct {
		bool R;
		bool G;
		bool B;
	} Emphasis;
	struct {
		bool R;
		bool G;
		bool B;
	} Support;
};

#endif /* PRESETS_H_ */