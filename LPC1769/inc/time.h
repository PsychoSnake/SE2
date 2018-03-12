/**
* @file		time.h
* @brief	Contains the TIME API.
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

#ifndef _TIME_H_
#define _TIME_H_

/** @defgroup TIME TIME
 * @ingroup TIME
 * This package provides an API to use the TIMER and RTC
 * @{
 */

/** @defgroup TIME_Public_Functions TIME Public Functions
 * @{
 */

/**
 * @brief	Initializes the TIMER0 and RTC
 * @param	timerFreq: frequency to be used for the timer
 * @return  Nothing
 * @note	MUST be called before any other function
 */
void TIME_Init(unsigned int timerFreq);

/**
 * @brief	Gets the current value on the RTC
 * @return  struct with the value gotten from the RTC
 */
struct tm *TIME_GetDateTime();

/**
 * @brief	Sets the RTC with the given struct
 * @param	setDate: value to be set
 * @return  Nothing
 */
void TIME_SetDateTime(struct tm *setDate);

/**
 * @brief	Waits a specific amount of time
 * @param	waitTime: time to wait
 * @return  Nothing
 */
void TIME_Wait(int waitTime);

/**
 * @}
 */


/**
 * @}
 */

#endif
