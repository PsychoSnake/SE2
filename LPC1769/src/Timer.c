#include "LPC17xx.h"
#include "timer.h"

#define TIMER_ON 1
#define TIMER_OFF 2

void TIMER0_Init(unsigned int frequency){
	LPC_TIM0->TCR = TIMER_OFF;
	//LPC_PINVPBDIV->VPB_RATE = 1;
	LPC_TIM0->PR = ((SystemCoreClock / frequency) - 1) / 1000;
	LPC_TIM0->MCR = 0;
	LPC_TIM0->EMR = 0;
	LPC_TIM0->CTCR = 0;
	LPC_TIM0->TCR = TIMER_ON;
}

unsigned int TIMER0_GetValue(void){
	return LPC_TIM0->TC;
}

unsigned int TIMER0_Elapse(unsigned int lastRead){
	return LPC_TIM0->TC - lastRead;
}
