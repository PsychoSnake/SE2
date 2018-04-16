/*
===============================================================================
 Name        : TestEeprom.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "eeprom.h"

#include <stdio.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

	EEPROM_Init();
	/*
	char test [12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	*/

	char test [7] = {0};
	while(1){
		EEPROM_Read(test, 3);
		test[0]=0;
	}

/*	char read [3];

	EEPROM_Read(read, 3);

	printf("Read: %s", read);

	char * test2 = "SE";

	EEPROM_Write(test2, 3);

	EEPROM_Read(read, 3);

	printf("Read: %s", read);*/

	return 0 ;
}
