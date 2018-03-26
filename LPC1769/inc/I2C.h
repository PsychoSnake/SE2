#ifndef _I2C_H_
#define _I2C_H_

#define I2C_BUFFER_SIZE 	64 		/* max supported bytes by EEPROM */

#define I2CONSET_ENABLE 	(0x40)
#define I2C_CLOCK_HIGH 		125
#define I2C_CLOCK_LOW 		125

#define I2CONCLR_AAC        (1<<2)  /* I2C Control clear Register */
#define I2CONCLR_SIC        (1<<3)
#define I2CONCLR_STAC       (1<<5)
#define I2CONCLR_I2ENC      (1<<6)



void I2C_Init();

void I2C_Start();

void I2C_End();

void I2C_send();

#endif