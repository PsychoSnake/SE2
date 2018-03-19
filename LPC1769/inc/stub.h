/**
* @file		stub.h
*
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

#ifndef _STUB_H_
#define _STUB_H_

/** @defgroup STUB STUB
 * @ingroup STUB
 * This package provides a function to be used for IAP
 * @{
 */

/** @defgroup STUB_Public_Functions STUB Public Functions
 * @{
 */

 /**
 * @brief	Enters thumb mode to execute a IAP command
 * @param	command: command to be executed and his parameters
 * @param	results: the result from the execute
 * @return  Nothing
 */
void iap_entry(unsigned int *command, unsigned int *results);

/**
 * @}
 */


/**
 * @}
 */

#endif
