/*
===============================================================================
 Name        : Test.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "core_cm3.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

#define LED_PIN_ID 1 << 22

int ms;


void Delay(uint32_t time){
	ms = 0;
	while( ms < time )
		__WFI();
}

void SysTick_Handler(void){
	ms++;
}

int main(void) {

	SystemCoreClockUpdate();
	LPC_GPIO0->FIODIR |= LED_PIN_ID;
	LPC_GPIO0->FIOCLR = LED_PIN_ID;

	if(SysTick_Config(SystemCoreClock / 1000)){
		printf("ERROR on SysTickConfig()");
		while(1){}
	}

    while(1){
    	LPC_GPIO0->FIOSET = LED_PIN_ID;
    	Delay(250);
    	LPC_GPIO0->FIOCLR = LED_PIN_ID;
    	Delay(250);
    }

    return 0 ;
}
