#ifndef _I2C_H_
#define _I2C_H_

#define I2C_IDLE              0
#define I2C_STARTED           1
#define I2C_RESTARTED         2
#define I2C_REPEATED_START    3
#define DATA_ACK              4
#define DATA_NACK             5
#define I2C_BUSY              6
#define I2C_NO_DATA           7
#define I2C_NACK_ON_ADDRESS   8
#define I2C_NACK_ON_DATA      9
#define I2C_ARBITRATION_LOST  10
#define I2C_TIME_OUT          11
#define I2C_OK                12


#define I2C_BUFFER_SIZE 	64 		/* max supported bytes by EEPROM */

#define I2CONSET_ENABLE 	(0x40)
#define I2C_CLOCK_HIGH 		50
#define I2C_CLOCK_LOW 		50

#define I2CONSET_I2EN       (0x1<<6)  /* I2C Control Set Register */
#define I2CONSET_AA         (0x1<<2)
#define I2CONSET_SI         (0x1<<3)
#define I2CONSET_STO        (0x1<<4)
#define I2CONSET_STA        (0x1<<5)

#define I2CONCLR_AAC        (0x1<<2)  /* I2C Control clear Register */
#define I2CONCLR_SIC        (0x1<<3)
#define I2CONCLR_STAC       (0x1<<5)
#define I2CONCLR_I2ENC      (0x1<<6)
#define I2CONCLR_STOP       (0x1<<4)



void I2C_Init();

void I2C_Start();

void I2C_End();

void I2C_send();

#endif
