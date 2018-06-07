#include "eeprom.h"
#include "storage.h"

void STORAGE_StoreGameResults(struct players_info *players){
	EEPROM_Write((char * )players, sizeof(struct players_info));
}

void STORAGE_ClearGameResults(){
	char clear [12] = {0};
	STORAGE_StoreGameResults((struct players_info * )clear);
}

void STORAGE_LoadGameResults(struct players_info *players){
	EEPROM_Read((char * )players, sizeof(struct players_info));
}
