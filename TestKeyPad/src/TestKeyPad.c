#include "LPC17xx.h"
#include "rtc.h"

int layoutTest[] = {5,6,7,8,9,10,11,12,14,15,16,17,18};

int main(){
	SystemCoreClockUpdate();
	TIMER0_Init(1);
	KEYPAD_Init(layoutTest);


	LPC_GPIO0->FIODIR |= 1<<22;
	LPC_GPIO0->FIOCLR = 1<<22;

	int i;
	int key;
	int time;
	while(1){
		key = KEYPAD_Read();
		time = TIMER0_GetValue();
		while(TIMER0_Elapse(time) < 5000);
		printf("1111");

	}
}
