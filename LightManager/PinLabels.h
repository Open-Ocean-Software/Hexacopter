/*
 * PinLabels.h
 *
 * Created: 12/11/2017 9:46:17 AM
 *  Author: nichh
 */ 


#ifndef PINLABELS_H_
#define PINLABELS_H_

#include <avr/io.h>



#ifndef F_CPU
#define F_CPU 16000000UL //16MHz Clock Speed
#endif


//////////////////////////////////////////////////////////////////////////
//Floodlights
//////////////////////////////////////////////////////////////////////////
#define FLOODLIGHTREG DDRD

#define FLOODLIGHTPORT PORTD

#define CAMFLOODLIGHTS PD0
#define LANDFLOODLIGHTS PD1

//////////////////////////////////////////////////////////////////////////
//Lasers
//////////////////////////////////////////////////////////////////////////
#define LASERREG DDRD

#define LASERPORT PORTD

#define CAMORIENTLASER PD2
#define CAMLEVELLASER PD3
#define SCANLASER PD4

//////////////////////////////////////////////////////////////////////////
//Shift Registers
//////////////////////////////////////////////////////////////////////////
#define SHIFTREGDATAREG DDRB
#define SHIFTREGSELECTREG DDRC

#define SHIFTREGDATAPORT PORTB
#define SHIFTREGSELECTPORT PORTC

#define SR_DATA PB0
#define SRS_EMPHASISR PC0
#define SRS_EMPHASISG PC1
#define SRS_EMPHASISB PC2
#define SRS_SUPPORTR PC3
#define SRS_SUPPORTG PC4
#define SRS_SUPPORTB PC5

//////////////////////////////////////////////////////////////////////////
//Status
//////////////////////////////////////////////////////////////////////////
#define STATUSNOTIFYREG DDRD

#define STATUSNOTIFYPORT PORTD

#define STATUSNOTIFYR PD5
#define STATUSNOTIFYG PD6
#define STATUSNOTIFYB PD7


#endif /* PINLABELS_H_ */