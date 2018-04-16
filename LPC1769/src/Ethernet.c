#include "LPC17xx.h"
#include "Ethernet.h"

unsigned short ReadFromPHY (unsigned char reg)
{
	unsigned int loop;
	// Set up address to access in MII Mgmt Address Register
	LPC_EMAC->MADR = PHY_DEF_ADR | reg;
	// Trigger a PHY read via MII Mgmt Command Register
	LPC_EMAC->MCMD = MCMD_READ;
	// Loop read from PHY completes
	for (loop = 0; loop < MII_RD_TOUT; loop++) {
		if ((LPC_EMAC->MIND & MIND_BUSY) == 0) {
			break;
		}
	}
	LPC_EMAC->MCMD = 0; // Cancel read
	// Returned value is in MII Mgmt Read Data Register
	return (LPC_EMAC->MRDD);
}

void WriteToPHY (int reg, int writeval){
	unsigned int loop;

	// Set up address to access in MII Mgmt Address Register
	LPC_EMAC->MADR = PHY_DEF_ADR | reg;
	// Write value into MII Mgmt Write Data Register
	LPC_EMAC->MWTD = writeval;
	// Loop write to PHY completes
	for (loop = 0; loop < MII_WR_TOUT; loop++) {
		if ((LPC_EMAC->MIND & MIND_BUSY) == 0) {
			break;
		}
	}
}

Ethernet_Init(){

	LPC_SC->PCONP |= ETHERNET_ENABLE_POWER_CLOCK;

	LPC_PINCON->PINSEL2 |= 1 | (1<<2) | (1<<8) | (1<<16) | (1<<18) | (1<<20) | (1<<28) | (1<<30);
	LPC_PINCON->PINSEL3 |= 1 | (1<<2);

	LPC_EMAC->MAC1 |= PASS_ALL_RECEIVE_FRAMES;
	LPC_EMAC->MAC2 |= CRC_ENABLE | PAD_CRC_ENABLE | VLAN_PAD_ENABLE | AUTO_DETECT_PAD_ENABLE;

	LPC_EMAC->MAXF = MAXIMUM_FRAME_LENGTH;

	LPC_EMAC->CLRT |=  RETRANSMISSION_MAXIMUM | COLLISION_WINDOW;

	LPC_EMAC->IPGR |= NON_BACK_TO_BACK_INTER_PACKET_GAP_PART1 | NON_BACK_TO_BACK_INTER_PACKET_GAP_PART2;

	LPC_EMAC->Command = ENABLE_RMI | DISABLE_PASS_RUN_FRAME;

	//Reset PHY and wait to finish
	WriteToPHY(BASIC_CONTROL_REGISTER, PHY_RESET);
	while(ReadFromPHY(CONTROL_REGISTER)&PHY_RESET);

	WriteToPHY(AUTO_NEGOTIATION_ADVERTISEMENT_REGISTER, A_100BASE_TX_FULL_DUPLEX);
	WriteToPHY(BASIC_CONTROL_REGISTER, PHY_AUTO_NEGOTIATION_ENABLE);
	while(ReadFromPHY(BASIC_STATUS_REGISTER)&PHY_AUTO_NEGOTIATION_COMPLETE);

	//wait for link
	while(!(ReadFromPHY(BASIC_STATUS_REGISTER)&PHY_LINK_STATUS));











}
