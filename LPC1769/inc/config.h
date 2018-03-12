/**
* @file		config.h
* @brief	Contains the Config API.
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

#ifndef _CONFIG_H_
#define _CONFIG_H_

/** @defgroup CONFIG CONFIG
 * @ingroup CONFIG
 * This package provides the functions to execute the configuration mode for the Tic-Tac-Toe game
 * @{
 */

 /** @defgroup CONFIG_Public_Functions CONFIG Public Functions
 * @{
 */

  /**
 * @brief	Enter in configuration mode
 * @return  Nothing
 */
void CONFIG_StartConfiguration();

/**
 * @}
 */

/**
* @}
*/

#endif
