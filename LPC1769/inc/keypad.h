/**
* @file		keypad.h
* @brief	Contains the KeyPad API.
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

#ifndef _KEYPAD_H_
#define _KEYPAD_H_

/** @defgroup KEYPAD KEYPAD 
 * @ingroup KEYPAD
 * This package provides the core capabilities to read from a KeyPad more specific, a KeyPad 4x4.
 * @{

/** @defgroup KEYPAD_Public_Functions KEYPAD Public Functions
 * @{
 */

/**
 * @brief	Initializes the KeyPad
 * @param	layout: The layout used for the KeyPad
 * @return  Nothing
 * @note	This function must be called prior to any other KeyPad functions. The
 * keys will have the specified layout value.
 */
void KEYPAD_Init(int layout[12]);

/* Devolve 1 se existe alguma tecla pressionada e 0 no caso contrário. Não é
bloqueante. */

/**
 * @brief	Checks if a key was pressed on the KeyPad. It's non blocking.
 * @return  Nothing
 */
int KEYPAD_Hit(void);

/* Devolve o código da tecla pressionada. É bloqueante. */
/**
 * @brief	Reads the key pressed from the KeyPad. It stays blocked until there is a pressed key.
 * @return  the corresponding value for the pressed key
 */
int KEYPAD_Read(void);

/**
 * @}
 */


/**
 * @}
 */

#endif
