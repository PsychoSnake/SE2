#include "storage.h"
#include "event.h"
#include "rtc.h"
#include "eeprom.h"

#define CONFIG_EVENT 21
#define PLAY_EVENT 10
#define CLOCK_RATE 1
#define TIMER_FREQUENCY 1
#define LED_PIN PIN_6

struct players_info players = {0,0,0,0,0,0};

void initialize();


int main(){
	initialize();
	unsigned int event;
	struct tm *dateTime;
	while(1){
		dateTime = TIME_GetDateTime();
		STORAGE_LoadGameResults(&players);
		UI_DrawIdleScreen(dateTime, &players);
		event = EVENT_GetIdleEvent();

		switch(event){
			case IDLE_CONFIG:
				CONFIG_StartConfiguration();
				break;
			case IDLE_PLAY:
				startGame(&players);
				break;
		}
	}
}

void initialize(){
	SystemCoreClockUpdate();
	//VPBDIV->VPB_RATE = 1;
	//MAM->MAMCR = 2;
	//LED_Init(LED_PIN, 0);
	EVENT_Init();
	TIME_Init(TIMER_FREQUENCY);
	UI_SetupLCD();
	EEPROM_Init();
}
