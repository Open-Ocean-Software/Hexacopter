/*
 * Main.h
 *
 * Created: 01/22/2018 9:42:24 PM
 *  Author: Nicholas
 */ 


#ifndef MAIN_H_
#define MAIN_H_


 #include <avr/io.h>
 #include <stdbool.h>


 #include "COM/SPISlave.h"

 #include "Rendering.h"
 #include "Registers.h"
 

 extern volatile double SystemMS;

 void UpdateLights(double);

 unsigned char GetRegisterValue(uint8_t);
 void SetRegisterValue(uint8_t, unsigned char);


#endif /* MAIN_H_ */