#include "spi.h"
#include "gpio.h"
#include "LPC17xx.h"

void SPI_Init(int frequency, int bitData){
	LPC_PINCON->PINSEL0 |= (1 << 31 | 1 << 30);
	LPC_PINCON->PINSEL1 |= (1 << 5 | 1 << 4);
    LPC_SPI->SPCR = 0x24 | (1 << 3) | (1 << 4) | bitData << 8;
	int possibleFreq = SystemCoreClock / frequency;
	if(possibleFreq < 8)
		possibleFreq = 8;
	else
		if(possibleFreq % 2 != 0)
			possibleFreq += 1;
	LPC_SPI->SPCCR = possibleFreq;
	unsigned char dummy;
	dummy = LPC_SPI->SPSR;
}

void SPI_BeginTransfer(int csBitId){
	GPIO_SetIOPin( csBitId, 0);
}

void SPI_EndTransfer(int csBitId){
	GPIO_SetIOPin( csBitId, 1);
}

void SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int lenght){
	int i;
	for (i = 0; i < lenght; i++) {
		LPC_SPI->SPDR = *txBuffer++; 	// load SPI transmiter register
		while (!(LPC_SPI->SPSR)); 	// wait for transmission to complete
		*rxBuffer++ = LPC_SPI->SPDR; 	// read data from SPI data register
	}
	return i;
}
