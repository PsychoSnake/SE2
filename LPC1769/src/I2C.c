#include "LPC17xx.h"
#include "I2C.h"

char Rdbuffer [I2C_BUFFER_SIZE];
char Wrbuffer [I2C_BUFFER_SIZE];
int WrLength;
int RdLength;
int state;
static int WrIndex;
int RdIndex;

void I2C1_IRQHandler(void)
{
  uint8_t StatValue;

  StatValue = LPC_I2C1->I2STAT;
  switch ( StatValue )
  {
	case 0x08:			/* A Start condition is issued. */
	WrIndex = 0;
	RdIndex = 0;
	LPC_I2C1->I2DAT = Wrbuffer[WrIndex++];
	LPC_I2C1->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;

	case 0x10:			/* A repeated started is issued */
	RdIndex = 0;
	/* Send SLA with R bit set, */
	LPC_I2C1->I2DAT = Wrbuffer[WrIndex++];
	LPC_I2C1->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;

	case 0x18:			/* Regardless, it's a ACK */
	if ( WrLength == 1 )
	{
		LPC_I2C1->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
		state = I2C_NO_DATA;
	}
	else
	{
		LPC_I2C1->I2CONCLR = I2CONCLR_STOP | I2CONCLR_STAC;
		LPC_I2C1->I2DAT = Wrbuffer[WrIndex++];
	}
	LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
	break;

	case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
	if ( WrIndex < WrLength )
	{
	  LPC_I2C1->I2DAT = Wrbuffer[WrIndex++]; /* this should be the last one */
	}
	else
	{
	  if ( RdLength != 0 )
	  {
		LPC_I2C1->I2CONSET = I2CONSET_STA;	/* Set Repeated-start flag */
	  }
	  else
	  {
		LPC_I2C1->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
		state = I2C_OK;
	  }
	}
	LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
	break;

	case 0x30:
	LPC_I2C1->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
	state = I2C_NACK_ON_DATA;
	LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
	break;

	case 0x40:	/* Master Receive, SLA_R has been sent */
	if ( (RdIndex + 1) < RdLength )
	{
	  /* Will go to State 0x50 */
	  LPC_I2C1->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  /* Will go to State 0x58 */
	  LPC_I2C1->I2CONCLR = I2CONCLR_AAC;	/* assert NACK after data is received */
	}
	LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
	break;

	case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
	Rdbuffer[RdIndex++] = LPC_I2C1->I2DAT;
	if ( (RdIndex + 1) < RdLength )
	{
	  LPC_I2C1->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  LPC_I2C1->I2CONCLR = I2CONCLR_AAC;	/* assert NACK on last byte */
	}
	LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
	break;

	case 0x58:
	Rdbuffer[RdIndex++] = LPC_I2C1->I2DAT;
	state = I2C_OK;
	LPC_I2C1->I2CONSET = I2CONSET_STO;	/* Set Stop flag */
	LPC_I2C1->I2CONCLR = I2CONCLR_SIC;	/* Clear SI flag */
	break;

	case 0x20:		/* regardless, it's a NACK */
	case 0x48:
	LPC_I2C1->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
	state = I2C_NACK_ON_ADDRESS;
	LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
	break;

	case 0x38:		/* Arbitration lost, in this example, we don't
					deal with multiple master situation */
	default:
	state = I2C_ARBITRATION_LOST;
	LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
	break;
  }
  return;
}


void I2C_Init(){
	LPC_SC->PCONP |= 1 << 19;

	LPC_PINCON->PINSEL0 |= 1 | 1<<1 | 1<<2 | 1<<3;
	LPC_PINCON->PINMODE0 &= ~((1)|(1<<2)|(1<<3)|(1<<4));
	LPC_PINCON->PINMODE0 |= 1 << 1 | 1 << 3;
	LPC_PINCON->PINMODE_OD0 |= 1 | (1 << 1);

	LPC_I2C1->I2SCLH = I2C_CLOCK_HIGH;
	LPC_I2C1->I2SCLL = I2C_CLOCK_LOW;

	LPC_I2C1->I2CONCLR = I2CONCLR_AAC | I2CONCLR_I2ENC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_STOP;

	NVIC_EnableIRQ(I2C1_IRQn);

	LPC_I2C1->I2CONSET = I2CONSET_ENABLE;

}

void I2C_Start(){

	  LPC_I2C1->I2CONSET = I2CONSET_STA;

	  state = I2C_STARTED;
}

void I2C_End();





