/**
* @file		rtc.h
* @brief	Contains the RTC API.
*     		It is intended to be used in ISO C conforming development
*     		environments and checks for this insofar as it is possible
*     		to do so.
* @author	Tiago Lopes
*
* Copyright(C) 2015, Tiago Lopes
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

#ifndef _RTC_H_
#define _RTC_H_

struct tm {
	int tm_sec; /*!< Offset: 0x00 seconds */
  	int tm_min; /*!< Offset: 0x04 minutes */
	int tm_hour; /*!< Offset: 0x08 hours */
	int tm_wday; /*!< Offset: 0x0c Memory Accelerator Module Control Register */
	int tm_mday; /*!< Offset: 0x10 Memory Accelerator Module Control Register */
	int tm_yday; /*!< Offset: 0x14 Memory Accelerator Module Control Register */
	int	tm_mon; /*!< Offset: 0x18 Memory Accelerator Module Control Register */
	int tm_year; /*!< Offset: 0x1c Memory Accelerator Module Control Register */
};

/** @defgroup RTC RTC
 * @ingroup RTC
 * This package provides an API to use the RTC
 * @{
 */

 /** @defgroup RTC_Public_Functions RTC Public Functions
 * @{
 */

 /**
 * @brief	Initializes RTC
 * @param	dateTime: the initial time for the RTC 
 * @return  Nothing
 * @note	MUST be called before any other RTC function
 */
void RTC_Init(struct tm *dateTime);

 /**
 * @brief	Returns in a struct tm the current value of the RTC
 * @param	dateTime: struct to store the current time
 * @return  Nothing
 */
void RTC_GetValue(struct tm *dateTime);

 /**
 * @brief	Updates RTC with the given parameter
 * @param	dateTime: struct to store update RTC
 * @return  Nothing
 */
void RTC_SetValue(struct tm *dateTime);

/**
 * @}
 */


/**
 * @}
 */

#endif
