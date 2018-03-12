/**
* @file		timer.h
* @brief	Contains the TIMER API.
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

#ifndef _TIMER_H_
#define _TIMER_H_

/** @defgroup TIMER TIMER 
 * @ingroup TIMER
 * This package provides the core capabilities to count time using TIMER0 only with LPC2106.
 * @{

/** @defgroup TIMER_Public_Functions TIMER Public Functions
 * @{
 */

/**
 * @brief	Initializes the LED API
 * @param	frequency : Frequency used for the timer
 * @return	Nothing
 * @note	This function must be called prior to any other TIMER functions.
 */
void TIMER0_Init(unsigned int frequency);

/**
 * @brief	Get's the current ticks
 * @return	Nothing
 * @note	The ticks are based on the frequency given on the initialization
 */
unsigned int TIMER0_GetValue(void);

/**
 * @brief	Get's the difference between the current ticks and the received parameter
 * @param	lastRead : ticks read last time
 * @return	Nothing
 */
unsigned int TIMER0_Elapse(unsigned int lastRead);


/**
 * @}
 */


/**
 * @}
 */

#endif
