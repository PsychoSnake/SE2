/**
* @file		event.h
* @brief	Contains the EVENT API.
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

#ifndef _EVENT_H_
#define _EVENT_H_

/** @defgroup EVENT EVENT
 * @ingroup EVENT
 * This package provides the capabilty to receive events from the KeyPad.
 * @{
 */


/** @addtogroup IDLE_BUTTONS IDLE BUTTONS FUNCTIONS
 *
 * @{
 */
#define IDLE_NOTHING 0 	/*!< Do Nothing */
#define IDLE_CONFIG 21 	/*!< Go into configuration mode */
#define IDLE_PLAY 10 	/*!< Go into play mode */
/**
* @}
*/

/** @addtogroup CONFIG_BUTTONS CONFIG BUTTONS FUNCTIONS
 *
 * @{
 */
#define CONFIG_CLOCK 1 					/*!< Configure clock screen */
#define CONFIG_DATE 2					/*!< Configure date screen */
#define CONFIG_GAME_RESULTS 3 			/*!< Delete game results screen */
#define CONFIG_DATETIME_NEXT 11			/*!< Step to next state on date or clock configuration screen */
#define CONFIG_GAME_RESULTS_DELETE 10	/*!< Confirm delete of previous game results */
#define CONFIG_GAME_RESULTS_EXIT 11		/*!< Cancel game results deletion */
#define CONFIG_EXIT 10					/*!< Exit configuration mode back to idle mode */
/**
* @}
*/

/** @defgroup EVENT_Public_Functions EVENT Public Functions
 * @{
 */

 /**
 * @brief	Initializes KeyPad
 * @return  Nothing
 * @note	MUST be called before any other EVENT function
 */
void EVENT_Init();

 /**
 * @brief	Gets an IDLE mode event. Does not block thread waiting for key
 * @return  The key pressed. In the case for the configuration mode key it is used the TIMER to know if its available entry
 */
int EVENT_GetIdleEvent();

 /**
 * @brief	Gets any mode event besides IDLE. Blocks thread until a valid key is received
 * @return  The key pressed
 */
int EVENT_GetEvent();

/**
 * @}
 */

/**
* @}
*/

#endif
