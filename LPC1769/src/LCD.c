#include <Timer.h>
#include "lcd.h"
#include "gpio.h"
#include "lab5.h"
#include "LPC17xx.h"

#define FRONT_COLOR 0
#define BACK_COLOR 0xFFF

extern const unsigned char font8x16[97][16];

static unsigned int nRows;
static unsigned int nCols;
static unsigned int nBytes;

static unsigned int currentRow = 1;
static unsigned int maxRow;
static unsigned int currentCol = 1;
static unsigned int maxCol;

/**
 * @brief	Initilize LCD.
 * @return	Nothing
 */
void LCD_Init(void) {

	SPI_BeginTransfer(LCD_CS);

	LCD_Command(DISCTL); 	// display control

	LCD_Data(0x0C);
	LCD_Data(0x20);
	LCD_Data(0x0C);

	LCD_Command(COMSCN); 	// common scanning direction
	LCD_Data(0x01);

	LCD_Command(OSCON); 	// internal oscialltor on

	LCD_Command(SLPOUT); 	// sleep out

	LCD_Command(PWRCTR); 	// power ctrl
	LCD_Data(0x0F); 		//everything on, no external reference resistors

	LCD_Command(0xA7); 		// invert display

	LCD_Command(DATCTL); 	// data control
	LCD_Data(0x00); 		// 3 correct for normal sin7
	LCD_Data(0x00); 		// normal RGB arrangement
	LCD_Data(0x04); 		// 16-bit Grayscale Type A

	LCD_Command(VOLCTR); 	// electronic volume, this is the contrast/brightness
	LCD_Data(0x27); 		// volume (contrast) setting - fine tuning, original
	LCD_Data(0x03); 		// internal resistor ratio - coarse adjustment

	TIMER0_Init(1);
	int time = TIMER0_GetValue();
	while(TIMER0_Elapse(time) < 400);

	LCD_Command(DISON); 	// display on

	SPI_EndTransfer(LCD_CS);
}


void LCD_LowLevelInit(){
	unsigned char *pFont = (unsigned char *) font8x16;
	nCols = *pFont;
	maxCol = LCD_WIDTH / nCols;
	nRows = *(pFont + 1);
	maxRow = LCD_HEIGHT / nRows;
	nBytes = *(pFont + 2);
	GPIO_SetIOPin(LCD_CS,1);
	GPIO_SetIOPin(LCD_RST,0);

	TIMER0_Init(1);
	int time = TIMER0_GetValue();
	while(TIMER0_Elapse(time) < 400);

	GPIO_SetIOPin(LCD_RST,1);
	SPI_Init(SystemCoreClock / 8, 9);
	LCD_Init();
}

void LCD_Command(int command){
	unsigned short rxBuffer[1];
	command &= 0xFF;
	unsigned short send = command;
	SPI_Transfer(&send, rxBuffer, 1);
}

void LCD_Data(int data){
	unsigned short rxBuffer[1];
	data |= (1 << 8);
	unsigned short send = data;
	SPI_Transfer(&send, rxBuffer, 1);
}

void incrementCursor(){
	if((currentCol += nCols) > LCD_WIDTH){
		currentCol = 1;
		currentRow += nRows;
	}
}

void LCDSetPixel(int x, int y, int color) {

	LCD_Command(PASET);
	LCD_Data(LCD_HEIGHT - x);
	LCD_Data(LCD_HEIGHT);

	LCD_Command(CASET);
	LCD_Data(LCD_WIDTH - y);
	LCD_Data(LCD_WIDTH - y);

  // Now illuminate the pixel (2nd pixel will be ignored)
  LCD_Command(RAMWR);
  LCD_Data((color >> 4) & 0xFF);
  LCD_Data(((color & 0xF) << 4) | ((color >> 8) & 0xF));
  LCD_Data(color & 0xFF);
}

void LCD_WriteChar(char ch){
	int i, colIndex;
	unsigned char pixelRow;
	unsigned int pixel1, pixel2, convertedRow, convertedCol;
	unsigned char *pFont;
	unsigned char *pChar;

	pFont = (unsigned char *) font8x16;

	convertedRow = currentRow * nRows;
	convertedCol = currentCol * nCols;

	LCD_Command(PASET);
	LCD_Data(LCD_HEIGHT - (currentRow + nRows - 1));
	LCD_Data(LCD_HEIGHT - (currentRow));

	LCD_Command(CASET);
	//LCD_Data(LCD_WIDTH - (convertedCol + nCols - 1));
	LCD_Data(LCD_WIDTH - (currentCol + nCols - 1));
	LCD_Data(LCD_WIDTH - (currentCol));

	LCD_Command(RAMWR);
	incrementCursor();

	pChar = pFont + (nBytes * (ch - 0x1F)) + nBytes - 1;

	for (i = 0; i < nBytes; i++) {
		pixelRow = *pChar--;
		for (colIndex = 0; colIndex < nCols / 2; colIndex++) {
			pixel1 = ((pixelRow & 0x1) != 0) ? FRONT_COLOR : BACK_COLOR;
			pixelRow >>= 1;
			pixel2 = ((pixelRow & 0x1) != 0) ? FRONT_COLOR : BACK_COLOR;
			pixelRow >>= 1;
			LCD_Data((pixel1 >> 4) & 0xFF);
			LCD_Data(((pixel1 & 0xF) << 4) | ((pixel2 >> 8) & 0xF));
			LCD_Data(pixel2 & 0xFF);
		}
	}
}

void LCD_WriteString(char *str){
	char aux;
	while( (aux = *str) != '\0'){
		LCD_WriteChar(aux);
		str++;
	}
}

void LCD_Goto(int x, int y){
	currentRow = x;
	currentCol = y;
}

void LCD_Clear(int color){
	int i; // loop counter

  // Row address set
  LCD_Command(PASET);
  LCD_Data(0);
  LCD_Data(131);

  // Column address set
  LCD_Command(CASET);
  LCD_Data(0);
  LCD_Data(131);

  LCD_Command(RAMWR);

  for(i = 0; i < ((131 * 131) / 2); i++) {
    LCD_Data((color >> 4) & 0xFF);
    LCD_Data(((color & 0xF) << 4) | ((color >> 8) & 0xF));
    LCD_Data(color & 0xFF);
  }

}
