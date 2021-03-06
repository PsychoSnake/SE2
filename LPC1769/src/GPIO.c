#include "LPC17xx.h"

#define INPUT 0
#define OUTPUT 1

void GPIO_SetIOPinDirection(int pin, int direction){
	if(direction == 1)
		LPC_GPIO0->FIODIR |= pin;
	else
		LPC_GPIO0->FIODIR |= ~pin;
}


void GPIO_SetIOPin(int pin, int state){
    GPIO_SetIOPinDirection(pin, OUTPUT);
    if(state == 0)
    	LPC_GPIO0->FIOCLR |= pin;
	else
		LPC_GPIO0->FIOSET |= pin;
}

int GPIO_GetIOPin(int pin){
	GPIO_SetIOPinDirection(pin, INPUT);
	return LPC_GPIO0->FIOPIN & pin;
}

void GPIO_SetPinFunction(int pin, int funcId){
	if(pin < 16)
		LPC_PINCON->PINSEL0 |= funcId;
	else
		LPC_PINCON->PINSEL1 |= funcId;
}
