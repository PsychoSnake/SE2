/**
* @file		ui.h
* @brief	Contains the UI API.
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

#ifndef _UI_H_
#define _UI_H_

#include "lcd.h"
#include "storage.h"

/** @defgroup UI UI
 * @ingroup UI
 * This package provides an API to do more specific operations involving the LCD
 * @{
 */

/** @defgroup UI_Public_Functions UI Public Functions
 * @{
 */

 /**
 * @brief	Initializes all visual related periferics
 * @return  Nothing
 * @note	MUST be called before any other UI function
 */
void UI_SetupLCD();

 /**
 * @brief	Draws the grid where the players will play
 * @param	dateTime: current time and date
 * @return  Nothing
 */
void UI_DrawGameGrid(struct tm *dateTime);

 /**
 * @brief	Draws the main screen
 * @param	dateTime: current time and date
 * @param	players: current game results
 * @return  Nothing
 */
void UI_DrawIdleScreen(void *params);

 /**
 * @brief	Draws the configuration screen
 * @return  Nothing
 */
void UI_DrawMainConfigScreen(void *params);

 /**
 * @brief	Draws the screen where the user will set the clock
 * @param	dateTime: current time and date
 * @param	ind: the element that is being edited (0->hour ; 1->minutes)
 * @return  Nothing
 */
void UI_DrawConfigClock(void *params);

 /**
 * @brief	Draws the screen where the user will set the date
 * @param	dateTime: current time and date
 * @param	ind: the element that is being edited (0->day ; 1->month ; 2->year)
 * @return  Nothing
 */
void UI_DrawConfigDate(void *params);

 /**
 * @brief	Draws the screen where the user confirms the game results deletion
 * @return  Nothing
 */
void UI_DrawConfigDeleteResults(void *params);

 /**
 * @brief	Draws the result screen of the game
 * @param	state: the state of the end game (0->draw ; 1->win)
 * @param	player: the player related to the end game in case of the win
 * @return  Nothing
 */
void UI_PlayResultScreen(void *params);

 /**
 * @brief	Clears the screen
 * @return  Nothing
 */
void UI_ClearScreen(void *params);

void UI_Write(void *params);

void UI_DrawPlayerTurn(void *params);

void UI_Init();

void UI_AddMessage(void* function, void* params);

/**
 * @}
 */


/**
 * @}
 */

#endif
