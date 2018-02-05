/*
 * SPISlave.h
 *
 * Created: 12/10/2017 11:42:48 PM
 *  Author: Nicholas
 */ 


#ifndef SPISLAVE_H_
#define SPISLAVE_H_


void SPIInitialize(void);

unsigned char SPIReceive(void);
void SPITransmit(unsigned char);
unsigned char SPITransceive(unsigned char);

unsigned char SPIPseudoReceive(unsigned char *);
void SPIPseudoTransmit(unsigned char);

#endif /* SPISLAVE_H_ */