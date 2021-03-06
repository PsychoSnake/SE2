/**
* @file		lcd.h
* @brief	Contains the LCD API.
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

#ifndef _LCD_H_
#define _LCD_H_

/** @defgroup LCD LCD
 * @ingroup LCD
 * This package provides an API to use the LCD module MOD-LCD6610
 * @{
 */

/** @addtogroup LCD_Constants LCD Constants
 *
 * @{
 */
#define LCD_HEIGHT 132 				/*!< LCD Height */
#define LCD_WIDTH 132				/*!< LCD Width */
#define LCD_CS  ( 1 << 16 )		/*!< PIN used for the LCD chip select */
#define LCD_RST ( 1 << 17 )		/*!< PIN used for the LCD reset */

/**
* @}
*/

/** @addtogroup LCD_Colors LCD COLORS
 *
 * @{
 */

#define COLOR_BLACK 0
#define COLOR_BLUE  0x00F
#define COLOR_GREEN 0x0F0
#define COLOR_RED   0xF00
#define COLOR_WHITE 0xFFF

/**
* @}
*/

/** @defgroup LCD_Public_Functions LCD Public Functions
 * @{
 */

 /**
 * @brief	Initializes LCD and also SPI
 * @return  Nothing
 * @note	MUST be called before any other LCD function
 */
void LCD_LowLevelInit();

 /**
 * @brief	Writes a character on the current cursor position
 * @param	ch: character to be written
 * @return  Nothing
 */
void LCD_WriteChar(char ch);

 /**
 * @brief	Writes a string on the current cursor position
 * @param	str: string to be written
 * @return  Nothing
 */
void LCD_WriteString(char *str);

 /**
 * @brief	Paints a pixel on a specific coordinate of the LCD
 * @param	x: line axis
 * @param	y: collunm axis
 * @param	color: color to paint the pixel
 * @return  Nothing
 */
void LCDSetPixel(int x, int y, int color);

 /**
 * @brief	Points the cursor to a given coordinate
 * @param	x: line axis
 * @param	y: collunm axis
 * @return  Nothing
 */
void LCD_Goto(int x, int y);

 /**
 * @brief	Clears the screen with the given color
 * @param	color: color to paint the screen
 * @return  Nothing
 */
void LCD_Clear(int color);

/**
 * @}
 */


/**
 * @}
 */

#endif
