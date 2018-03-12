/**
* @file		led.h
* @brief	Contains the LED API.
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

#ifndef _LED_H_
#define _LED_H_

/** @defgroup LED LED 
 * @ingroup LED
 * This package provides the core capabilities such as on / off the LED in a LPC2106 port.
 * @{

/** @defgroup LED_Public_Functions LED Public Functions
 * @{
 */

/**
 * @brief	Initializes the LED API
 * @param	state	: State of the LED. The 0 indicate led off and 1 LED on.
 * @param	pinId 	: Id of the pin to use for the LED
 * @return	Nothing
 * @note	This function must be called prior to any other LED functions. The
 * LED will be started in the value passed in the parameter.
 */
void LED_Init(int pinId, int state);


/**
 * @brief	Get LED state. 
 * @return	status of LED. The 0 indicate led off and 1 LED on.
 */
int LED_GetState(void);

/**
 * @brief	Set LED state.
 * @param	state	: State of the LED. The 0 indicate led off and 1 LED on.
 * @return	Nothing
 */
void LED_SetState(int state);

/**
 * @}
 */


/**
 * @}
 */

#endif

