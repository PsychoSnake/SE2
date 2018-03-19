#include "flash.h"
#include "stub.h"

unsigned int FLASH_PrepareSectors(unsigned int startSector, unsigned int endSector);

/* Apaga o conteúdo de um sector, ou de múltiplos sectores, da FLASH. Para apagar
apenas um sector, deve usar-se o mesmo número de sector para os dois parâmetros. */
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector){
	unsigned int iap_command[5], iap_result[3];
	iap_result[0] = FLASH_PrepareSectors(startSector, endSector);
	if (iap_result[0] == IAP_CMD_SUCESS) {
		iap_command[0] = 52; /* Erase sectors command */
		iap_command[1] = startSector;
		iap_command[2] = endSector;
		iap_command[3] = 14745;
		iap_entry(iap_command, iap_result);
	}
	return iap_result[0];
}

/* Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes, no
endereço da FLASH referenciado por dstAddr. */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size){
	unsigned int iap_command[5], iap_result[3];
	iap_command[0] = 51; /* Write in FLASH from RAM command */
	iap_command[1] = dstAddr;
	iap_command[2] = srcAddr;
	iap_command[3] = size;
	iap_command[4] = 14745;
	iap_entry(iap_command, iap_result);
	return iap_result[0];
}

/* Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes, no
endereço da FLASH referenciado por dstAddr. */
unsigned int FLASH_PrepareSectors(unsigned int startSector, unsigned int endSector){
	unsigned int iap_command[5], iap_result[3];
	iap_command[0] = 50; /* Prepare sectors command */
	iap_command[1] = startSector;
	iap_command[2] = endSector;
	iap_entry(iap_command, iap_result);
	return iap_result[0];
}

/* Compara o conteúdo do bloco de dados referenciado por srcAddr, de dimensão size
bytes, com o conteúdo do bloco de dados referenciado por dstAddr. */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size){
	unsigned int iap_command[5], iap_result[3];
	iap_command[0] = 56; /* Compare Addrs command */
	iap_command[1] = (unsigned int) dstAddr;
	iap_command[2] = (unsigned int) srcAddr;
	iap_command[3] = size;
	iap_entry(iap_command, iap_result);
	return iap_result[0];
}
