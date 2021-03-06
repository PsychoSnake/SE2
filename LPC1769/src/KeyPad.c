#include <Timer.h>
#include "LPC17xx.h"
#include "gpio.h"

#define L0 (1 << 9)
#define L1 (1 << 8)
#define L2 (1 << 7)
#define L3 (1 << 6)
#define C0 (1 << 23)
#define C1 (1 << 24)
#define C2 (1 << 25)

#define KEYPAD_OUTPUT_MASK_LENGTH 4
#define COLLUNM_SHIFT 23

int *keyPad_Layout;
int collumnVal;
int lineVal;
int keyPad_Output_Mask_Set[] = { L1|L2|L3, L0|L2|L3, L0|L1|L3, L0|L1|L2 };
int keyPad_Output_Mask_Clr[] = { L0,L1,L2,L3 };

void KEYPAD_Init(int layout[12]){
	keyPad_Layout = layout;
	GPIO_SetIOPinDirection( L0|L1|L2|L3, 1);
	GPIO_SetIOPin(L0|L1|L2|L3, 1);
	GPIO_SetIOPinDirection( C0|C1|C2, 0);
}

int KEYPAD_Hit(void){
	int i;
	collumnVal = 15;
	for(i = 0; i < KEYPAD_OUTPUT_MASK_LENGTH; i++){
		GPIO_SetIOPin(keyPad_Output_Mask_Set[i], 1);
		GPIO_SetIOPin(keyPad_Output_Mask_Clr[i], 0);
		if(( collumnVal = ( GPIO_GetIOPin(C0|C1|C2) >> COLLUNM_SHIFT ) ) < 7){
			lineVal = i;
			return 1;
		}
	}
	return 0;
}

int KEYPAD_Read(void){
		while(KEYPAD_Hit() == 0){
		}
	return keyPad_Layout[convertToKey()];
}

int convertToKey(){
	if(collumnVal == 2){
		return 12;
	}
	int value = lineVal * 3 + ( ( ~collumnVal & 7 ) >> 1) ; // 3 * 3 + (5 >> 1)
	int p = keyPad_Layout[value];
	return value;
}
