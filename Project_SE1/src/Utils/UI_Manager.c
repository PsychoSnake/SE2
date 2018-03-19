#include "LPC17xx.h"
#include "lcd.h"
#include "rtc.h"
#include "storage.h"

#define BEGIN_GRID 1
#define END_GRID 16

char* itoa(int valToConvert, int maxUnits, char *buf){
    int value = valToConvert;
    buf[maxUnits] = '\0';

    int i;

    for(i = maxUnits - 1; i >= 0 ; --i, value /= 10){
			if(!value)
				buf[i] = '0';
			else
        buf[i] = "0123456789"[value % 10];
		}

    return buf;

}

void UI_SetupLCD(){
	LCD_LowLevelInit();
	SPI_BeginTransfer(LCD_CS);
	LCD_Clear(COLOR_WHITE);
	SPI_EndTransfer(LCD_CS);
}

void UI_DrawGameGrid(struct tm *dateTime){
	int i;
	SPI_BeginTransfer(LCD_CS);
  char str[10];
	LCD_Goto(1,5);

  LCD_WriteString(itoa(dateTime->tm_mday, 2, str));
	LCD_WriteChar('/');

  LCD_WriteString(itoa(dateTime->tm_mon, 2, str));

  LCD_WriteChar('/');
	LCD_WriteString(itoa(dateTime->tm_year, 4, str));

  LCD_WriteChar('|');

	LCD_WriteString(itoa(dateTime->tm_hour, 2, str));

	LCD_WriteChar(':');

	LCD_WriteString(itoa(dateTime->tm_min, 2, str));

  for(i=11; i <= 121; i++)
    LCDSetPixel(61,i,COLOR_BLACK); // horizontal
  for(i=11; i <= 121; i++)
    LCDSetPixel(91,i,COLOR_BLACK); // horizontal
  for(i=31; i <= 121; i++)
    LCDSetPixel(i,50,COLOR_BLACK); // vertical
  for(i=31; i <= 121; i++)
    LCDSetPixel(i,90,COLOR_BLACK); // vertical

	SPI_EndTransfer(LCD_CS);
}


void UI_DrawConfigClock(struct tm *dateTime, int ind){
	char str[10];
  SPI_BeginTransfer(LCD_CS);
  LCD_Goto(1,5);
  switch (ind) {
    case 0:
      LCD_WriteString("Pick Hour");
      break;
    case 1:
      LCD_WriteString("Pick minutes");
      break;
  }
  LCD_Goto(20,5);
  LCD_WriteString(itoa(dateTime->tm_hour, 2, str));
  LCD_WriteChar('h');
  LCD_WriteChar(':');
  LCD_WriteString(itoa(dateTime->tm_min, 2, str));
  LCD_WriteChar('m');

  SPI_EndTransfer(LCD_CS);
}


void UI_DrawConfigDate(struct tm *dateTime, int ind){
  char str[10];
  SPI_BeginTransfer(LCD_CS);
  LCD_Goto(1,5);
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
  LCD_Goto(20,5);
  LCD_WriteString(itoa(dateTime->tm_mday, 2, str));
  LCD_WriteChar('/');
  LCD_WriteString(itoa(dateTime->tm_mon, 2, str));
  LCD_WriteChar('/');
  LCD_WriteString(itoa(dateTime->tm_year, 4, str));

  SPI_EndTransfer(LCD_CS);
}

void UI_DrawConfigDeleteResults(){
  SPI_BeginTransfer(LCD_CS);
  LCD_Goto(1,5);
  LCD_WriteString("Delete Results?");
  LCD_Goto(20,5);
  LCD_WriteString("*:Confirm");
  LCD_Goto(40,5);
  LCD_WriteString("#:Cancel");
}

void UI_DrawMainConfigScreen(){
  SPI_BeginTransfer(LCD_CS);
  LCD_Goto(1,5);
  LCD_WriteString("Commands:");
  LCD_Goto(20,5);
  LCD_WriteString("1:ConfigClock");
  LCD_Goto(40,5);
  LCD_WriteString("2:ConfigDate");
  LCD_Goto(60,5);
  LCD_WriteString("3:DeleteResults");
  LCD_Goto(80,5);
  LCD_WriteString("*:Exit And Save");
  SPI_EndTransfer(LCD_CS);
}

void printTime(struct tm *dateTime){
	char str[10];
	LCD_Goto(1,5);
	LCD_WriteString("Time:");

	LCD_WriteString(itoa(dateTime->tm_hour, 2, str));
  LCD_WriteChar('h');

	LCD_WriteChar(':');

	LCD_WriteString(itoa(dateTime->tm_min, 2, str));
  LCD_WriteChar('m');
}

void printDate(struct tm *dateTime){
	char str[10];
	LCD_Goto(20,5);
	LCD_WriteString("Date:");

  LCD_WriteString(itoa(dateTime->tm_mday, 2, str));
	LCD_WriteChar('/');

  LCD_WriteString(itoa(dateTime->tm_mon, 2, str));

  LCD_WriteChar('/');
	LCD_WriteString(itoa(dateTime->tm_year, 4, str));
}

void printPlayerResults(struct players_info *players){
	char str[10];

	LCD_Goto(50,5);
	LCD_WriteString("Win|Draw|Defeat");

	LCD_Goto(70,5);
	LCD_WriteString("P1:");
	LCD_WriteString(itoa(players->player_one_victories, 2, str));
	LCD_WriteChar('|');
	LCD_WriteString(itoa(players->player_one_draws, 2, str));
	LCD_WriteChar('|');
	LCD_WriteString(itoa(players->player_one_defeats, 2, str));

	LCD_Goto(90,5);
	LCD_WriteString("P2:");
	LCD_WriteString(itoa(players->player_two_victories, 2, str));
	LCD_WriteChar('|');
	LCD_WriteString(itoa(players->player_two_draws, 2, str));
	LCD_WriteChar('|');
	LCD_WriteString(itoa(players->player_two_defeats, 2, str));
}

void UI_DrawIdleScreen(struct tm *dateTime, struct players_info *players){
	SPI_BeginTransfer(LCD_CS);
	printTime(dateTime);
	printDate(dateTime);
	printPlayerResults(players);
	SPI_EndTransfer(LCD_CS);
}

void UI_ClearScreen(){
  SPI_BeginTransfer(LCD_CS);
  LCD_Clear(COLOR_WHITE);
  SPI_EndTransfer(LCD_CS);
}

void UI_PlayResultScreen(int state, int player){
  SPI_BeginTransfer(LCD_CS);
  LCD_Clear(COLOR_WHITE);
  LCD_Goto(50,5);
  switch (state) {
    case 0:
      LCD_WriteString("End in draw");
      break;
    case 1:
      LCD_WriteString("Player ");
      LCD_WriteChar(player == 1? '1' : '2');
      LCD_WriteString(" won");
      LCD_Goto(70,5);
      LCD_WriteString("CONGRATULATIONS");
      break;
  }
  SPI_EndTransfer(LCD_CS);
}

void UI_DrawPlayerTurn(player, invalidPlay){
  char *str;
  int time;
  SPI_BeginTransfer(LCD_CS);

  if(invalidPlay){
    str = "Invalid play ";
    LCD_Goto(20,15);
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
  LCD_Goto(20,15);
  LCD_WriteString(str);
  SPI_EndTransfer(LCD_CS);
}

void UI_Write(char c, int x, int y){
  SPI_BeginTransfer(LCD_CS);
  LCD_Goto(x,y);
  LCD_WriteChar(c);
  SPI_EndTransfer(LCD_CS);
}
