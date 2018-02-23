/*
 * PinLabels.h
 *
 * Created: 02/08/2018 9:13:17 PM
 *  Author: nichh
 */ 


#ifndef PINLABELS_H_
#define PINLABELS_H_

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL //16MHz Clock Speed
#endif


//////////////////////////////////////////////////////////////////////////
// Servo Register
//////////////////////////////////////////////////////////////////////////
#define SERVOREG DDRC

#define SERVOPORT PORTC

#define GIMBALX PC1
#define GIMBALY PC2
#define GIMBALZ PC3

#define THERMSWIVELX PC4
#define THERMSWIVELY PC5

#define LANDINGGEAR PC0

//////////////////////////////////////////////////////////////////////////
// Winch
//////////////////////////////////////////////////////////////////////////
#define WINCHREG DDRD

#define WINCHPORT PORTD

#define WINCHINT PD1

#define WINCHPOS PD2
#define WINCHNEG PD3


//////////////////////////////////////////////////////////////////////////
// Notify
//////////////////////////////////////////////////////////////////////////
#define NOTIFYREG DDRD

#define NOTIFYPORT PORTD

#define PROJLAUNCHNOTIFY PD4
#define WINCHACTIVENOTIFY PD5
#define LANDINGGEARACTIVENOTIFY PD6

#define PIEZOBUZZER PD7

//////////////////////////////////////////////////////////////////////////
// Shift Registers
//////////////////////////////////////////////////////////////////////////
#define SHIFTREGSETREG DDRB
#define SHIFTREGDATAREG DDRD

#define SHIFTREGSETPORT PORTB
#define SHIFTREGDATAPORT PORTD

#define SHIFTREGDATA PD0
#define PROJSHIFTREGSET PB0
#define ACCESSORYSHIFTREGSET PB1



#endif /* PINLABELS_H_ */