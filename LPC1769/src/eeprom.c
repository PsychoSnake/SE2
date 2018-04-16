#include "I2C.h"
#include "LPC17xx.h"

extern char Rdbuffer [I2C_BUFFER_SIZE];
extern char Wrbuffer [I2C_BUFFER_SIZE];
extern int WrLength;
extern int RdLength;
extern int RdIndex;
extern int state;

void EEPROM_Init(){
	I2C_Init();
}

int EEPROM_Write(char * buffer, int length){
	if(length > I2C_BUFFER_SIZE - 3)
		return -1; // buffer to big

	Wrbuffer[0] = 0xA << 4;
	Wrbuffer[1] = 0;
	Wrbuffer[2] = 0;

	for(int i = 3; i < length + 3; i++)
		Wrbuffer[i] = buffer[i - 3];

	WrLength = length + 3;

	I2C_Start();

	while(state == I2C_STARTED);
}

int EEPROM_Read(char buffer [64], int numberOfBytes){

	EEPROM_Write(0, 0);

	Wrbuffer[0] = ((0xA) << 4) | 1;
	RdLength = numberOfBytes;
	RdIndex = 0;

	I2C_Start();

	while(state == I2C_STARTED);

	for(int i = 0; i < numberOfBytes; i++)
		buffer[i] = Rdbuffer[i];

	RdLength = 0;

	return 0; //ok
}
