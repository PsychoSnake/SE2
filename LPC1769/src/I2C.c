#include "LPC17xx.h"
#include "I2C.h"

int
char I2C_Buffer [I2C_BUFFER_SIZE];
static int I2C_Idx;


void I2C_Init(){
	LPC_SC->PCONP |= 1 << 19;

	LPC_SC->PCLKSEL1 |= 1 << 6;

	LPC_PINCON->PINSEL0 |= 1 | 1<<1 | 1<<2 | 1<<3;
	LPC_PINCON->PINMODE0 &= ~((1)|(1<<2));
	LPC_PINCON->PINMODE0 |= 1 << 1 | 1 << 3;
	LPC_PINCON->PINMODE_OD0 |= 1 | 1 << 1;

	LPC_I2C1->I2SCLH = I2C_CLOCK_HIGH;
	LPC_I2C1->I2SCLL = I2C_CLOCK_LOW;

	LPC_I2C1->I2CONCLR = I2CONCLR_AAC | I2CONCLR_I2ENC | I2CONCLR_SIC | I2CONCLR_STAC;

	NVIC_EnableIRQ(I2C2_IRQn);

	LPC_I2C1->I2CONSET = I2CONSET_ENABLE;
}

void I2C_Start(char address){
	I2C_Idx = 0;
	LPC_I2C1->I2DAT = address;


}

void I2C_End();





