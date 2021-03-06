#include "LPC17xx.h"
#include "lcd.h"
#include "rtc.h"
#include "storage.h"
#include "spi.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "semphr.h"

#define BEGIN_GRID 1
#define END_GRID 16

typedef struct UI_Messages {
	void (*functionToExecute)(void *params);
	void* arrayParams;
} UI_Messages;

static UI_Messages arrayMessages[5];
static int currentMessagePos;
static int currentInsertPos;
static int messagesLen;

static xSemaphoreHandle xSemaphore;

void UI_AddMessage(void* function, void* params) {
	xSemaphoreTake(xSemaphore, 3000);
	while (messagesLen > 4) {
		xSemaphoreGive(xSemaphore);
		vTaskDelay(500);
		xSemaphoreTake(xSemaphore, 3000);
	}
	++messagesLen;
	UI_Messages message = { function, params };
	arrayMessages[currentInsertPos++] = message;
	if (currentInsertPos > 4) {
		currentInsertPos = 0;
	}
	xSemaphoreGive(xSemaphore);
}

void UI_MainLoop() {
	while (1) {
		xSemaphoreTake(xSemaphore, 3000);
		if (messagesLen > 0) {
			UI_Messages messageToExecute = arrayMessages[currentMessagePos++];
			if (currentMessagePos > 4) {
				currentMessagePos = 0;
			}
			messagesLen--;
			messageToExecute.functionToExecute(messageToExecute.arrayParams);
		}
		xSemaphoreGive(xSemaphore);
	}
}

void setupLCD() {
	LCD_LowLevelInit();
	SPI_BeginTransfer(LCD_CS);
	LCD_Clear(COLOR_WHITE);
	SPI_EndTransfer(LCD_CS);
}

int UI_Init() {
	setupLCD();
	currentMessagePos = 0;
	currentInsertPos = 0;
	messagesLen = 0;
	xSemaphore = xSemaphoreCreateMutex();
	return xTaskCreate(UI_MainLoop, "ui-loop", configMINIMAL_STACK_SIZE, 0, 1,
			0);
}

char* itoa(int valToConvert, int maxUnits, char *buf) {
	int value = valToConvert;
	buf[maxUnits] = '\0';

	int i;

	for (i = maxUnits - 1; i >= 0; --i, value /= 10) {
		if (!value)
			buf[i] = '0';
		else
			buf[i] = "0123456789"[value % 10];
	}

	return buf;

}

void UI_DrawGameGrid(void *params) {
	struct tm *dateTime = (struct tm *) params;
	int i;
	SPI_BeginTransfer(LCD_CS);
	char str[10];
	LCD_Goto(1, 5);

	LCD_WriteString(itoa(dateTime->tm_mday, 2, str));
	LCD_WriteChar('/');

	LCD_WriteString(itoa(dateTime->tm_mon, 2, str));

	LCD_WriteChar('/');
	LCD_WriteString(itoa(dateTime->tm_year, 4, str));

	LCD_WriteChar('|');

	LCD_WriteString(itoa(dateTime->tm_hour, 2, str));

	LCD_WriteChar(':');

	LCD_WriteString(itoa(dateTime->tm_min, 2, str));

	for (i = 11; i <= 121; i++)
		LCDSetPixel(61, i, COLOR_BLACK); // horizontal
	for (i = 11; i <= 121; i++)
		LCDSetPixel(91, i, COLOR_BLACK); // horizontal
	for (i = 31; i <= 121; i++)
		LCDSetPixel(i, 50, COLOR_BLACK); // vertical
	for (i = 31; i <= 121; i++)
		LCDSetPixel(i, 90, COLOR_BLACK); // vertical

	SPI_EndTransfer(LCD_CS);
}

void UI_DrawConfigClock(void *params) {
	int *aux = params;
	struct tm *dateTime = (struct tm*) *aux;
	int ind = *(aux + 1);
	char str[10];
	SPI_BeginTransfer(LCD_CS);
	LCD_Goto(1, 5);
	switch (ind) {
	case 0:
		LCD_WriteString("Pick Hour");
		break;
	case 1:
		LCD_WriteString("Pick minutes");
		break;
	}
	LCD_Goto(20, 5);
	LCD_WriteString(itoa(dateTime->tm_hour, 2, str));
	LCD_WriteChar('h');
	LCD_WriteChar(':');
	LCD_WriteString(itoa(dateTime->tm_min, 2, str));
	LCD_WriteChar('m');

	SPI_EndTransfer(LCD_CS);
}

void UI_DrawConfigDate(void *params) {
	int *aux = params;
	struct tm *dateTime = (struct tm*) *aux;
	int ind = *(aux + 1);
	char str[10];
	SPI_BeginTransfer(LCD_CS);
	LCD_Goto(1, 5);
	switch (ind) {
	case 0:
		LCD_WriteString("Pick Day");
		break;
	case 1:
		LCD_WriteString("Pick Month");
		break;
	case 2:
		LCD_WriteString("Pick Year  ");
		break;
	}
	LCD_Goto(20, 5);
	LCD_WriteString(itoa(dateTime->tm_mday, 2, str));
	LCD_WriteChar('/');
	LCD_WriteString(itoa(dateTime->tm_mon, 2, str));
	LCD_WriteChar('/');
	LCD_WriteString(itoa(dateTime->tm_year, 4, str));

	SPI_EndTransfer(LCD_CS);
}

void UI_DrawConfigDeleteResults(void* params) {
	SPI_BeginTransfer(LCD_CS);
	LCD_Goto(1, 5);
	LCD_WriteString("Delete Results?");
	LCD_Goto(20, 5);
	LCD_WriteString("*:Confirm");
	LCD_Goto(40, 5);
	LCD_WriteString("#:Cancel");
}

void UI_DrawMainConfigScreen(void *params) {
	SPI_BeginTransfer(LCD_CS);
	LCD_Goto(1, 5);
	LCD_WriteString("Commands:");
	LCD_Goto(20, 5);
	LCD_WriteString("1:ConfigClock");
	LCD_Goto(40, 5);
	LCD_WriteString("2:ConfigDate");
	LCD_Goto(60, 5);
	LCD_WriteString("3:DeleteResults");
	LCD_Goto(80, 5);
	LCD_WriteString("*:Exit And Save");
	SPI_EndTransfer(LCD_CS);
}

void printTime(struct tm *dateTime) {
	char str[10];
	LCD_Goto(1, 5);
	LCD_WriteString("Time:");

	LCD_WriteString(itoa(dateTime->tm_hour, 2, str));
	LCD_WriteChar('h');

	LCD_WriteChar(':');

	LCD_WriteString(itoa(dateTime->tm_min, 2, str));
	LCD_WriteChar('m');
}

void printDate(struct tm *dateTime) {
	char str[10];
	LCD_Goto(20, 5);
	LCD_WriteString("Date:");

	LCD_WriteString(itoa(dateTime->tm_mday, 2, str));
	LCD_WriteChar('/');

	LCD_WriteString(itoa(dateTime->tm_mon, 2, str));

	LCD_WriteChar('/');
	LCD_WriteString(itoa(dateTime->tm_year, 4, str));
}

void printPlayerResults(struct players_info *players) {
	char str[10];

	LCD_Goto(50, 5);
	LCD_WriteString("Win|Draw|Defeat");

	LCD_Goto(70, 5);
	LCD_WriteString("P1:");
	LCD_WriteString(itoa(players->player_one_victories, 2, str));
	LCD_WriteChar('|');
	LCD_WriteString(itoa(players->player_one_draws, 2, str));
	LCD_WriteChar('|');
	LCD_WriteString(itoa(players->player_one_defeats, 2, str));

	LCD_Goto(90, 5);
	LCD_WriteString("P2:");
	LCD_WriteString(itoa(players->player_two_victories, 2, str));
	LCD_WriteChar('|');
	LCD_WriteString(itoa(players->player_two_draws, 2, str));
	LCD_WriteChar('|');
	LCD_WriteString(itoa(players->player_two_defeats, 2, str));
}

void UI_DrawIdleScreen(void *params) {
	int *aux = (int*) params;
	struct tm *dateTime = (struct tm*) *aux;
	struct players_info *players = (struct tm*) *(aux + 1);
	SPI_BeginTransfer(LCD_CS);
	printTime(dateTime);
	printDate(dateTime);
	printPlayerResults(players);
	SPI_EndTransfer(LCD_CS);
}

void UI_ClearScreen(void *params) {
	SPI_BeginTransfer(LCD_CS);
	LCD_Clear(COLOR_WHITE);
	SPI_EndTransfer(LCD_CS);
}

void UI_PlayResultScreen(void *params) {
	int *aux = (int*) params;
	int state = *aux, player = *(aux + 1);
	SPI_BeginTransfer(LCD_CS);
	LCD_Clear(COLOR_WHITE);
	LCD_Goto(50, 5);
	switch (state) {
	case 0:
		LCD_WriteString("End in draw");
		break;
	case 1:
		LCD_WriteString("Player ");
		LCD_WriteChar(player == 1 ? '1' : '2');
		LCD_WriteString(" won");
		LCD_Goto(70, 5);
		LCD_WriteString("CONGRATULATIONS");
		break;
	}
	SPI_EndTransfer(LCD_CS);
}

void UI_DrawPlayerTurn(void *params) {
	char *validParams = (char*) params;
	char player = validParams[0], invalidPlay = validParams[1];
	char *str;
	int time;
	SPI_BeginTransfer(LCD_CS);

	if (invalidPlay) {
		str = "Invalid play ";
		LCD_Goto(20, 15);
		LCD_WriteString(str);
		TIME_Wait(1000);
	}

	switch (player) {
	case 1:
		str = "Player 1 turn";
		break;
	case 2:
		str = "Player 2 turn";
		break;
	}
	LCD_Goto(20, 15);
	LCD_WriteString(str);
	SPI_EndTransfer(LCD_CS);
}

void UI_Write(void *params) {
	int *aux = (int*) params;
	char c = *aux, x = *(aux+1), y = *(aux+2);
	SPI_BeginTransfer(LCD_CS);
	LCD_Goto(x, y);
	LCD_WriteChar(c);
	SPI_EndTransfer(LCD_CS);
}
