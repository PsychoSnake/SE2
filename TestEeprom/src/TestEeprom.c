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

    char * test = "Pramaara Escrita";

    printf("%d", sizeof(test));

    EEPROM_Write(test, 16);

    char read [16];


    EEPROM_Read(read, 16);

    printf("Read: %s", read);

    char * test2 = "SI";

    EEPROM_Write(test2, 2);


    EEPROM_Read(read, 2);


    printf("Read: %s", read);

    return 0 ;
}
