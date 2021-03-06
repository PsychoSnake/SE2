#include "stddef.h"
#include "LPC17xx.h"
#include "rtc.h"

void SetDateAndTime(struct tm *dateTime);

#define CT0_SEC_OFFSET 	0
#define CT0_MIN_OFFSET 	8
#define CT0_HOUR_OFFSET 16
#define CT0_DOW_OFFSET 	24
#define CT1_DOM_OFFSET 	0
#define CT1_MON_OFFSET 	8
#define CT1_YEAR_OFFSET 16
#define CT2_DAY_OFFSET 	0

#define CT0_SEC_MASK 		(0x1F  << CT0_SEC_OFFSET)  /*!< Seconds mask */
#define CT0_MIN_MASK 		(0x3F  << CT0_MIN_OFFSET)  /*!< Minutes mask */
#define CT0_HOUR_MASK 	(0x1F  << CT0_HOUR_OFFSET) /*!< Hours mask */
#define CT0_DOW_MASK 		(0x7   << CT0_DOW_OFFSET)  /*!< Days of Week mask */
#define CT1_DOM_MASK 		(0xF   << CT1_DOM_OFFSET)   /*!< Days of Month mask */
#define CT1_MON_MASK 		(0xF   << CT1_MON_OFFSET)  /*!< Month mask */
#define CT1_YEAR_MASK 	(0xFFF << CT1_YEAR_OFFSET) /*!< Year mask */
#define CT2_DAY_MASK 		(0xFFF << CT2_DAY_OFFSET)	 /*!< Day of Year mask */

void RTC_Init(struct tm *dateTime){
	LPC_RTC->CCR = 0x2; /* Disable time counters and reset CTC */
	//LPC_LPC_RTC->PREINT = (CLK / 32768) - 1; /* Set PREINT */
	//LPC_LPC_RTC->PREFRAC = CLK - ((LPC_RTC->PREINT + 1) * 32768); /* Set PREFRAC */
	LPC_RTC->ILR = 0x3; /* Clear interrupts */
	LPC_RTC->ILR = 0x0; /* Disable interrupts */
	LPC_RTC->CIIR = 0x0; /* CIIR disabled */
	LPC_RTC->AMR = 0xFF; /* Alarm disabled */
	if(dateTime != NULL)
		SetDateAndTime(dateTime);
	LPC_RTC->CCR = 0x1; /* Enable time counters and CTC */
}

void SetDateAndTime(struct tm *dateTime){
	LPC_RTC->SEC = dateTime->tm_sec;
	LPC_RTC->MIN = dateTime->tm_min;
	LPC_RTC->HOUR = dateTime->tm_hour;
	LPC_RTC->DOW = dateTime->tm_wday;
	LPC_RTC->DOM = dateTime->tm_mday;
	LPC_RTC->DOY = dateTime->tm_yday;
	LPC_RTC->MONTH = dateTime->tm_mon;
	LPC_RTC->YEAR = dateTime->tm_year;
}

void RTC_GetValue(struct tm *dateTime){
	uint32_t ct0 = LPC_RTC->CTIME0;
	uint32_t ct1 = LPC_RTC->CTIME1;
	uint32_t ct2 = LPC_RTC->CTIME2;
	dateTime->tm_sec  = (ct0 & CT0_SEC_MASK) >> CT0_SEC_OFFSET;
	dateTime->tm_min  = (ct0 & CT0_MIN_MASK) >> CT0_MIN_OFFSET;
	dateTime->tm_hour = (ct0 & CT0_HOUR_MASK) >> CT0_HOUR_OFFSET;
	dateTime->tm_wday = (ct0 & CT0_DOW_MASK) >> CT0_DOW_OFFSET;
	dateTime->tm_mday = (ct1 & CT1_DOM_MASK) >> CT1_DOM_OFFSET;
	dateTime->tm_mon  = (ct1 & CT1_MON_MASK) >> CT1_MON_OFFSET;
	dateTime->tm_year = (ct1 & CT1_YEAR_MASK) >> CT1_YEAR_OFFSET;
	dateTime->tm_yday = (ct2 & CT2_DAY_MASK) >> CT2_DAY_OFFSET;
}

void RTC_SetValue(struct tm *dateTime){
	LPC_RTC->SEC   = dateTime->tm_sec;
	LPC_RTC->MIN   = dateTime->tm_min;
	LPC_RTC->HOUR  = dateTime->tm_hour;
	LPC_RTC->DOW   = dateTime->tm_wday;
	LPC_RTC->DOM   = dateTime->tm_mday;
	LPC_RTC->DOY   = dateTime->tm_yday;
	LPC_RTC->MONTH = dateTime->tm_mon;
	LPC_RTC->YEAR  = dateTime->tm_year;
}
