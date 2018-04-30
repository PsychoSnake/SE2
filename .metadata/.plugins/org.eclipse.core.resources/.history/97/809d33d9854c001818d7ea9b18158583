#include "LPC17xx.h"
#include "Ethernet.h"

int length;
char buffer [ETH_FRAG_SIZE];

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

	LPC_EMAC->MCFG |= 1<<15;
	LPC_EMAC->MCFG &=~(1<<15);

	LPC_EMAC->MCFG|= (1<<2) | (1<<3) | (1<<4) | (1<<5);

	/* Reset all EMAC internal modules. */
    LPC_EMAC->MAC1 = MAC1_RESET_TX | MAC1_RESET_MCS_TX | MAC1_RESET_RX | MAC1_RESET_MCS_RX |
	             MAC1_SIMULATION_RESET | MAC1_SOFT_RESET;
  	LPC_EMAC->Command = COMMAND_REGISTER_RESET | COMMAND_TX_RESET | COMMAND_RX_RESET;

	LPC_EMAC->MAC1 = MAC1_PASS_ALL_RECEIVE_FRAMES;
	LPC_EMAC->MAC2 = CRC_ENABLE | PAD_CRC_ENABLE | VLAN_PAD_ENABLE | AUTO_DETECT_PAD_ENABLE;

	LPC_EMAC->MAXF = MAXIMUM_FRAME_LENGTH;

	LPC_EMAC->CLRT =  RETRANSMISSION_MAXIMUM | COLLISION_WINDOW;

	LPC_EMAC->IPGR = NON_BACK_TO_BACK_INTER_PACKET_GAP_PART1 | NON_BACK_TO_BACK_INTER_PACKET_GAP_PART2;

	LPC_EMAC->Command = ENABLE_RMI | DISABLE_PASS_RUN_FRAME;



	//Reset PHY and wait to finish
	WriteToPHY(BASIC_CONTROL_REGISTER, PHY_RESET);

	int b = ReadFromPHY(2);

	int a = ReadFromPHY(BASIC_CONTROL_REGISTER);
	while(a&PHY_RESET){
		a = ReadFromPHY(BASIC_CONTROL_REGISTER);
	}

	WriteToPHY(AUTO_NEGOTIATION_ADVERTISEMENT_REGISTER, A_100BASE_TX_FULL_DUPLEX);
	WriteToPHY(BASIC_CONTROL_REGISTER, PHY_AUTO_NEGOTIATION_ENABLE);

	while(((ReadFromPHY(BASIC_STATUS_REGISTER))&PHY_AUTO_NEGOTIATION_COMPLETE) == 0);

	int config = ReadFromPHY(BASIC_STATUS_REGISTER);

	if(config & ((1<<12) | (1<<14)))
		LPC_EMAC->MAC2 |= 1;
	else
		LPC_EMAC->MAC2 &= ~1;

	if(config & ((1<<13) | (1<<14)))
		LPC_EMAC->SUPP |= A_100BASE;
	else
		LPC_EMAC->SUPP &= ~A_100BASE;

	//Configure MAC address
	LPC_EMAC->SA0 = MAC_STATION_ADDRESS_0;
	LPC_EMAC->SA1 = MAC_STATION_ADDRESS_1;
	LPC_EMAC->SA2 = MAC_STATION_ADDRESS_2;

	//wait for link
	while(!(ReadFromPHY(BASIC_STATUS_REGISTER)&PHY_LINK_STATUS));

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


int ReceiveFrame(){
	int idx = LPC_EMAC->RxConsumeIndex;
	if(idx != LPC_EMAC->RxProduceIndex){
		char * pointer =  LPC_EMAC->RxDescriptor[idx*2];
		int size = LPC_EMAC->RxDescriptor[idx*2 + 1] & RX_CONTROL_SIZE_MASK;

		for(int i = 0; i < size; i++)
			buffer[i] = pointer[i];

		if(++idx > LPC_EMAC->RxDescriptorNumber)
			idx = 0;


		LPC_EMAC->RxConsumeIndex = idx;

		length = size;

		return size;
	}
	else return 0;
}

void WriteFrame(){
	int idx = LPC_EMAC->TxProduceIndex;
	char * pointer = LPC_EMAC->TxDescriptor[idx*2];

	for(int i = 0; i < length; i++)
		pointer[i] = buffer[i];

	LPC_EMAC->TxDescriptor[idx*2 + 1] = length | (1 << 30) | (1<<31);

	if(++idx > LPC_EMAC->TxDescriptorNumber)
		idx = 0;
	LPC_EMAC->TxProduceIndex = idx;
}



