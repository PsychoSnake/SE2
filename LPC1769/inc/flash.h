/**
* @file		flash.h
* @brief	Contains the IAP API.
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

#ifndef _FLASH_H_
#define _FLASH_H_

#include "lpc2106.h"

/** @defgroup FLASH FLASH
 * @ingroup FLASH
 * This package provides the capabilty to write and read from the Flash using IAP.
 * @{
 */


/** @addtogroup Flash_Struct Flash Sector Struct
 *
 * @{
 */
struct Flash_Sector{
	uint32_t startAddr; /*!< Flash sector start address */
	uint32_t endAddr; 	/*!< Flash sector end address */
};
/**
* @}
*/

/**
 * Defines a Flash_Sector struct for the sector number received
 */
#define FILLSECT(v) { ((v) * 1024*8) , ((v) * 1024*8) + (1024 * 8) - 1}

/**
 * IAP command success result
 */
#define IAP_CMD_SUCESS 0

/** @defgroup FLASH_Public_Functions FLASH Public Functions
 * @{
 */

 /**
 * @brief	Prepares sectors for a write operation
 * @param	startSector: The beginning sector
 * @param	endSector: The end sector
 * @return  The result of the command executed
 * @note	If needed to prepare only one sector, both parameters must be equal
 */
unsigned int FLASH_PrepareSectors(unsigned int startSector, unsigned int endSector);

/**
 * @brief	Erases a sector or multiple depending on the parameters passed
 * @param	startSector: The sector to start erase
 * @param	endSector: The sector where the erase ends
 * @return  The result of the command executed
 * @note	If needed to delete only one sector, both parameters must be equal
 */
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector);

/**
 * @brief	Writes a block of data in the Flash from data in Ram
 * @param	dstAddr: The address of Flash to write to
 * @param	srcAddr: The address of Ram to read
 * @param	size: Amount of bytes to be written. Value MUST be one of these {512, 1024, 4096}
 * @return  The result of the command executed
 */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);

/**
 * @brief	Compares a block of data from Flash and Ram
 * @param	dstAddr: The address of Flash. MUST be word aligned
 * @param	srcAddr: The address of Ram. MUST be word aligned
 * @param	size: Amount of bytes to be compared. MUST be multiple of 4
 * @return  The result of the command executed
 */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);

/**
 * @}
 */


/**
 * @}
 */

#endif
