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

void RxDescriptorInit(){
	unsigned int * rxBase = (unsigned int *)RX_DESC_BASE;
	unsigned int rxBuf = (unsigned int)RX_BUF_BASE;
	unsigned int * rxControl = (unsigned int *)RX_DESC_BASE + 4;
	unsigned int * rxStatus = (unsigned int *)RX_STAT_BASE;
	unsigned int * rxCrc = (unsigned int *)RX_STAT_BASE + 4;

	for(int i = 0; i < NUM_RX_FRAG; i++){
		 *rxBase = rxBuf;
		 rxBase+=2;
		 rxBuf += ETH_FRAG_SIZE;

		 *rxControl = RCTRL_INT | (ETH_FRAG_SIZE - 1);
		 rxControl+=2;

		 *rxStatus = 0;
		 rxStatus+=2;

		 *rxStatus = 0;
		 rxCrc+=2;
	}


	  /* Set EMAC Receive Descriptor Registers. */
	  LPC_EMAC->RxDescriptor    = RX_DESC_BASE;
	  LPC_EMAC->RxStatus        = RX_STAT_BASE;
	  LPC_EMAC->RxDescriptorNumber = NUM_RX_FRAG-1;

	  /* Rx Descriptors Point to 0 */
	  LPC_EMAC->RxConsumeIndex  = 0;

}

void TxDescriptorInit(){
	unsigned int * txBase = (unsigned int *)TX_DESC_BASE;
	unsigned int txBuf = (unsigned int)TX_BUF_BASE;
	unsigned int * txControl = (unsigned int *)TX_DESC_BASE + 4;
	unsigned int * txStatus = (unsigned int *)TX_STAT_BASE;

	for(int i = 0; i < NUM_TX_FRAG; i++){
		 *txBase = txBuf;
		 txBase+=2;
		 txBuf += ETH_FRAG_SIZE;

		 *txControl = 0;
		 txControl+=2;

		 *txStatus = 0;
		 txStatus++;
	}

	 /* Set EMAC Transmit Descriptor Registers. */
	  LPC_EMAC->TxDescriptor    = TX_DESC_BASE;
	  LPC_EMAC->TxStatus        = TX_STAT_BASE;
	  LPC_EMAC->TxDescriptorNumber = NUM_TX_FRAG-1;

	  /* Tx Descriptors Point to 0 */
	  LPC_EMAC->TxProduceIndex  = 0;
}

void Ethernet_Init(){

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
	while(ReadFromPHY(BASIC_CONTROL_REGISTER)&PHY_RESET);

	WriteToPHY(AUTO_NEGOTIATION_ADVERTISEMENT_REGISTER, A_100BASE_TX_FULL_DUPLEX);
	WriteToPHY(BASIC_CONTROL_REGISTER, PHY_AUTO_NEGOTIATION_ENABLE);
	while(ReadFromPHY(BASIC_STATUS_REGISTER)&PHY_AUTO_NEGOTIATION_COMPLETE);

	//wait for link
	while(!(ReadFromPHY(BASIC_STATUS_REGISTER)&PHY_LINK_STATUS));

	int config = ReadFromPHY(BASIC_STATUS_REGISTER);

	if(config & (1<<12) & (1<<14))
		LPC_EMAC->MAC2 |= 1;
	else
		LPC_EMAC->MAC2 &= ~1;

	if(config & (1<<13 & (1<<14)))
		LPC_EMAC->SUPP |= A_100BASE;
	else
		LPC_EMAC->SUPP &= ~A_100BASE;

	//Configure MAC address
	LPC_EMAC->SA0 = MAC_STATION_ADDRESS_0;
	LPC_EMAC->SA1 = MAC_STATION_ADDRESS_1;
	LPC_EMAC->SA2 = MAC_STATION_ADDRESS_2;


	//Initialization the Rx descriptors
	RxDescriptorInit();
	//Initialization the Tx descriptors
	TxDescriptorInit();

	/* Receive Broadcast and Perfect Match Packets */
	LPC_EMAC->RxFilterCtrl = RFC_BROADCAST_EN | RFC_PERFECT_EN;

	/* Enable EMAC interrupts. */
	LPC_EMAC->IntEnable = INT_RX_DONE | INT_TX_DONE;

	/* Reset all interrupts */
	LPC_EMAC->IntClear  = 0xFFFF;

	/* Enable receive and transmit mode of MAC Ethernet core */
	LPC_EMAC->Command  |= (RX_ENABLE | TX_ENABLE);
	LPC_EMAC->MAC1     |= MAC1_RECEIVE_ENABLE;
}


