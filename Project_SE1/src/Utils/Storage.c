//
//struct Flash_Sector usedSector = FILLSECT(13);
//
//struct players_info emptyResults = {0,0,0,0,0,0};
//
//void STORAGE_StoreGameResults(struct players_info *players){
//  do{
//    FLASH_EraseSectors(13,13);
//    FLASH_PrepareSectors(13,13);
//    FLASH_WriteData((void*)usedSector.startAddr, players, 512);
//  }while(FLASH_VerifyData((void*)usedSector.startAddr, players, 512));
//}
//
//void STORAGE_ClearGameResults(){
//  do{
//    FLASH_EraseSectors(13,13);
//    FLASH_PrepareSectors(13,13);
//    FLASH_WriteData((void*) usedSector.startAddr, &emptyResults, 512);
//  }while(FLASH_VerifyData((void*)usedSector.startAddr, &emptyResults, 512));
//}
//
//void STORAGE_LoadGameResults(struct players_info *players){
//  *players = *(struct players_info*) usedSector.startAddr;
//}