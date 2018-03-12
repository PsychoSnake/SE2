#include "LPC17xx.h"

int layoutTest[] = {5,6,7,8,9,10,11,12,14,15,16,17,18};

int main(){
	SystemCoreClockUpdate();
		LPC_GPIO0->FIODIR |= 1<<22;
		LPC_GPIO0->FIOCLR = 1<<22;

		if(SysTick_Config(SystemCoreClock / 1000)){
			printf("ERROR on SysTickConfig()");
			while(1){}
		}

	int i;
	int key;
	while(1){
		key = KEYPAD_Read();
		for(i = 0; i < key; i++){
			printf("1111");
		}

	}
}
