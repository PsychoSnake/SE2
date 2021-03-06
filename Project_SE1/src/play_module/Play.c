#include "storage.h"
#include "rtc.h"
#include "UI.h"
#include "time.h"
#include "stdio.h"

int checkWin(char grid[6]) {
	if (grid[0] == grid[1] && grid[1] == grid[2])
		return 1;

	else if (grid[3] == grid[4] && grid[4] == grid[5])
		return 1;

	else if (grid[6] == grid[7] && grid[7] == grid[8])
		return 1;

	else if (grid[0] == grid[3] && grid[3] == grid[6])
		return 1;

	else if (grid[1] == grid[4] && grid[4] == grid[7])
		return 1;

	else if (grid[2] == grid[5] && grid[5] == grid[8])
		return 1;

	else if (grid[0] == grid[4] && grid[4] == grid[8])
		return 1;

	else if (grid[2] == grid[4] && grid[4] == grid[6])
		return 1;

	else if (grid[0] != '1' && grid[1] != '2' && grid[2] != '3'
			&& grid[3] != '4' && grid[4] != '5' && grid[5] != '6'
			&& grid[6] != '7' && grid[7] != '8' && grid[8] != '9')
		return 0;
	else
		return -1;
}

void incrementResults(int gameState, int player, struct players_info *players) {
	switch (gameState) {
	case 0:
		players->player_one_draws += 1;
		players->player_two_draws += 1;
		break;
	case 1:
		if (player == 1) {
			players->player_one_victories += 1;
			players->player_two_defeats += 1;
		} else {
			players->player_two_victories += 1;
			players->player_one_defeats += 1;
		}
		break;
	}
	STORAGE_StoreGameResults(players);
}

void startGame(struct players_info *players) {
	char grid[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int event, player = 1, isValidPlay = 1, x, y, gameState;
	char mark;
	struct tm * dateTime = TIME_GetDateTime();
	UI_AddMessage(UI_ClearScreen, NULL);
	UI_AddMessage(UI_DrawGameGrid, dateTime);
	while (1) {
		player = player % 2 != 0 ? 1 : 2;
		char aux[2] = {player, 0};
		if (isValidPlay){
			UI_AddMessage(UI_DrawPlayerTurn, aux);
		}
		else {
			aux[1] = 1;
			UI_AddMessage(UI_DrawPlayerTurn, aux);
		}
		event = EVENT_GetEvent();

		mark = (player == 1) ? 'X' : 'O';

		if (event == 1 && grid[0] == '1') {
			isValidPlay = 1;
			x = 40;
			y = 25;
			grid[0] = mark;
		} else if (event == 2 && grid[1] == '2') {
			isValidPlay = 2;
			x = 40;
			y = 65;
			grid[1] = mark;
		} else if (event == 3 && grid[2] == '3') {
			isValidPlay = 3;
			x = 40;
			y = 105;
			grid[2] = mark;
		} else if (event == 4 && grid[3] == '4') {
			isValidPlay = 4;
			x = 70;
			y = 25;
			grid[3] = mark;
		} else if (event == 5 && grid[4] == '5') {
			isValidPlay = 5;
			x = 70;
			y = 65;
			grid[4] = mark;
		} else if (event == 6 && grid[5] == '6') {
			isValidPlay = 6;
			x = 70;
			y = 105;
			grid[5] = mark;
		} else if (event == 7 && grid[6] == '7') {
			isValidPlay = 7;
			x = 105;
			y = 25;
			grid[6] = mark;
		} else if (event == 8 && grid[7] == '8') {
			isValidPlay = 8;
			x = 105;
			y = 65;
			grid[7] = mark;
		} else if (event == 9 && grid[8] == '9') {
			isValidPlay = 9;
			x = 105;
			y = 105;
			grid[8] = mark;
		} else {
			isValidPlay = 0;
		}

		if (isValidPlay) {
			int params[3] = {mark, x, y};
			UI_AddMessage(UI_Write, params);
		}

		if ((gameState = checkWin(grid)) != -1)
			break;

		if (isValidPlay)
			player++;
	}

	TIME_Wait(1000);
	int params[2] = {gameState, player};
	UI_AddMessage(UI_PlayResultScreen, params);
	TIME_Wait(2000);
	incrementResults(gameState, player, players);
	UI_AddMessage(UI_ClearScreen, NULL);
}
