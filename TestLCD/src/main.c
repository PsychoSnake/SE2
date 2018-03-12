#include "lcd.h"
#include "lab5.h"

int main(){

	SystemCoreClockUpdate();

	LCD_LowLevelInit();
	SPI_BeginTransfer(LCD_CS);
	LCD_Clear(0xFFF);
	LCD_WriteString("Benfica");
	LCD_Goto(2,1);
	LCD_WriteString("Benfica = Porto");
	SPI_EndTransfer(LCD_CS);
}
