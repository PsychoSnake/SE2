/**
* @file		spi.h
* @brief	Contains the SPI API.
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

#ifndef _SPI_H_
#define _SPI_H_

/** @defgroup SPI SPI
 * @ingroup SPI
 * This package provides an API to use the SPI
 * @{
 */

/** @defgroup SPI_Public_Functions SPI Public Functions
 * @{
 */

 /**
 * @brief	Initializes the SPI controller configuring the pins, send baud rate and number of data bits
 * @param	frequency: baud rate for sending messages
 * @param	bitData: number of data bits
 * @return  Nothing
 * @note	MUST be called before any other SPI function
 */
void SPI_Init(int frequency, int bitData);

 /**
 * @brief	Initiates a transfer by activating the slave device chip select 
 * @param	csBitId: chip select identifier
 * @return  Nothing
 */
void SPI_BeginTransfer(int csBitId);

 /**
 * @brief	Ends a transfer by deactivating the slave device chip select 
 * @param	csBitId: chip select identifier
 * @return  Nothing
 */
void SPI_EndTransfer(int csBitId);

 /**
 * @brief	Makes a transfer
 * @param	txBuffer: information to send
 * @param	rxBuffer: value read from the device
 * @param	lenght: number of shorts to send
 * @return  Nothing
 */
void SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int lenght);

/**
 * @}
 */


/**
 * @}
 */

#endif
