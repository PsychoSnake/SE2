/**
* @file		gpio.h
* @brief	Contains the GPIO API.
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

#ifndef _GPIO_H_
#define _GPIO_H_

/** @defgroup GPIO GPIO 
 * @ingroup GPIO
 * This package provides the core capabilities to set and clear pins from the processor and 
 * the means to do it like putting a pin to input or output direction
 * @{

/** @defgroup GPIO_Public_Functions GPIO Public Functions
 * @{
 */

/**
 * @brief	Sets the received pin into a specified direction
 * @param	pin	: The pin to change direction
 * @param	direction : The direction to be used by the pin (0 = INPUT; 1 = OUTPUT)
 * @return  Nothing
 * @note	This function must be called always before a read or write operation to a pin to change it's direction to the desired one
 */
void GPIO_SetIOPinDirection(int pin, int direction);

/**
 * @brief	Gets the received pin value to the received state
 * @param	pin	: The pin to get the value
 * @return  state of the pin
 */
int GPIO_GetIOPin(int pin);

/**
 * @brief	Sets the received pin OUTPUT value to the received state
 * @param	pin	: The pin to change OUTPUT value
 * @param	state : The desired state of the pin
 * @return  Nothing
 */
void GPIO_SetIOPin(int pin, int state);

/**
 * @brief	Sets the function to be used in a pin
 * @param	pin	: The pin to set the function
 * @param	funcId	: The function the pin will take
 * @return  Nothing
 */
void GPIO_SetPinFunction(int pin, int funcId);

/**
 * @}
 */


/**
 * @}
 */


#endif
