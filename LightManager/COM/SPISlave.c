/*
 * SPISlave.c
 *
 * Created: 12/10/2017 11:42:34 PM
 *  Author: Nicholas
 */ 

#include <avr/io.h>
#include "SPISlave.h"

void SPIInitialize()
{
	//Set MISO to output, all others input
	DDRB = (1 << PB6);
	//Enable SPI in the control register
	SPCR = (1 << SPE);
}

unsigned char SPITransceive(unsigned char data)
{
	//Load data into the data register
	SPDR = data;

	//Wait until transmission is complete
	while(!(SPSR & (1 << SPIF)));

	//Return data register
	return SPDR;
}

unsigned char SPIReceive(void)
{
	//Wait until transmission is complete
	while(!(SPSR & (1 << SPIF)));

	//Return data register
	return SPDR;
}
void SPITransmit(unsigned char data)
{
	//Load data into data register
	SPDR = data;

	//Wait until transmission is complete
	while(!(SPSR & (1 << SPIF)));
}

unsigned char SPIPseudoReceive(unsigned char *data)
{
	//Check if transmission is complete.
	if(SPSR & (1 << SPIF))
	{
		//Set data
		*data = SPDR;
		//Success
		return 0x1;
	}

	//Failed
	return 0x0;
}

void SPIPseudoTransmit(unsigned char data)
{
	SPDR = data;
}