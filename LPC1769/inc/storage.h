/**
* @file		storage.h
* @brief	Contains the flash memory access API (specific of the app).
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

#ifndef _STORAGE_H_
#define _STORAGE_H_

/** @defgroup STORAGE STORAGE
 * @ingroup STORAGE
 * This package provides an API to use the flash memory (Sector 13 is used)
 * @{
 */

/** @addtogroup STORAGE_Player_Results STORAGE Players results struct
 *
 * @{
 */

struct players_info{
	unsigned short player_one_victories;
	unsigned short player_one_draws;
	unsigned short player_one_defeats;
	unsigned short player_two_victories;
	unsigned short player_two_draws;
	unsigned short player_two_defeats;
};
/**
* @}
*/

/** @defgroup STORAGE_Public_Functions STORAGE Public Functions
 * @{
 */

 /**
 * @brief	Stores the game results
 * @param	players: game results of both players
 * @return  Nothing
 */
void STORAGE_StoreGameResults(struct players_info *players);

 /**
 * @brief	Clears the game results
 * @return  Nothing
 */
void STORAGE_ClearGameResults();

 /**
 * @brief	Loads the game results
 * @param	players: pointer to store the flash memory load
 * @return  Nothing
 */
void STORAGE_LoadGameResults(struct players_info *players);

/**
 * @}
 */


/**
 * @}
 */

#endif
