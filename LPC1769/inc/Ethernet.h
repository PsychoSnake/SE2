#define ETHERNET_ENABLE_POWER_CLOCK 1<<30

#define RECEIVE_ENABLE 1

#define FULL_DUPLEX 1
#define CRC_ENABLE 1<<4
#define PAD_CRC_ENABLE 1<<5
#define VLAN_PAD_ENABLE 1<<6
#define AUTO_DETECT_PAD_ENABLE 1<<7

#define MAXIMUM_FRAME_LENGTH 0x600

#define RETRANSMISSION_MAXIMUM 0xF
#define COLLISION_WINDOW 0x37

#define NON_BACK_TO_BACK_INTER_PACKET_GAP_PART1 0xC
#define NON_BACK_TO_BACK_INTER_PACKET_GAP_PART2 0x12

#define ENABLE_RMI 1<<9
#define DISABLE_PASS_RUN_FRAME 1<<6


#define PHY_RESET 1<<15
#define PHY_AUTO_NEGOTIATION_ENABLE 1<<12
#define PHY_AUTO_NEGOTIATION_COMPLETE 1<<5
#define PHY_LINK_STATUS 1<<2
#define PHY_DEF_ADR 1<<8

#define MCMD_READ 1
#define MIND_BUSY 1
#define MII_RD_TOUT 100000
#define MII_WR_TOUT 100000

#define A_100BASE 1<<8
#define A_100BASE_TX_FULL_DUPLEX 1<<8


#define UIP_ETHADDR0 0x0
#define	UIP_ETHADDR1 0x0
#define	UIP_ETHADDR2 0x0
#define	UIP_ETHADDR3 0x0
#define	UIP_ETHADDR4 0x0
#define	UIP_ETHADDR5 0x0

#define BASIC_CONTROL_REGISTER 0
#define BASIC_STATUS_REGISTER 1
#define AUTO_NEGOTIATION_ADVERTISEMENT_REGISTER 4


#define RFC_BROADCAST_EN 1<<1
#define RFC_PERFECT_EN 1<<5

#define INT_RX_DONE 1<<3
#define INT_TX_DONE 1<<7

#define TX_ENABLE 1<<1
#define RX_ENABLE 1

#define MAC1_RECEIVE_ENABLE 1

/* EMAC Memory Buffer configuration for 16K Ethernet RAM. */
#define NUM_RX_FRAG 4 /* Num.of RX Fragments 4*1536= 6.0kB */
#define NUM_TX_FRAG 2 /* Num.of TX Fragments 3*1536= 4.6kB */
#define ETH_FRAG_SIZE 1536 /* Packet Fragment size 1536 Bytes */
#define ETH_MAX_FLEN 1536 /* Max. Ethernet Frame Size */

/* EMAC variables located in AHB SRAM bank 1 */
#define RX_DESC_BASE 0x2007c000
#define RX_STAT_BASE (RX_DESC_BASE + NUM_RX_FRAG*8)
#define TX_DESC_BASE (RX_STAT_BASE + NUM_RX_FRAG*8)
#define TX_STAT_BASE (TX_DESC_BASE + NUM_TX_FRAG*8)
#define RX_BUF_BASE (TX_STAT_BASE + NUM_TX_FRAG*4)
#define TX_BUF_BASE (RX_BUF_BASE + NUM_RX_FRAG*ETH_FRAG_SIZE)

/* MAC Configuration Register 1 */
#define MAC1_RESET_TX         		 0x00000100  /* Reset TX Logic                    */
#define MAC1_RESET_MCS_TX     		 0x00000200  /* Reset MAC TX Control Sublayer     */
#define MAC1_RESET_RX         		 0x00000400  /* Reset RX Logic                    */
#define MAC1_RESET_MCS_RX     		 0x00000800  /* Reset MAC RX Control Sublayer     */
#define MAC1_SIMULATION_RESET        0x00004000  /* Simulation Reset                  */
#define MAC1_SOFT_RESET       		 0x00008000  /* Soft Reset MAC                    */
#define MAC1_PASS_ALL_RECEIVE_FRAMES 1<<1

#define COMMAND_REGISTER_RESET       0x00000008  /* Reset Host Registers              */
#define COMMAND_TX_RESET           	 0x00000010  /* Reset Transmit Datapath           */
#define COMMAND_RX_RESET           	 0x00000020  /* Reset Receive Datapath            */
#define CR_FULL_DUP         		 0x00000400  /* Full Duplex                       */

/* RX Descriptor Control Word */
#define RCTRL_INT           0x80000000  /* Generate RxDone Interrupt         */

#define RX_CONTROL_SIZE_MASK 0x7FF

/* Back-to-Back Inter-Packet-Gap Register */
#define IPGT_FULL_DUP       0x00000015  /* Recommended value for Full Duplex */
#define IPGT_HALF_DUP       0x00000012  /* Recommended value for Half Duplex */



void Ethernet_Init();
int Ethernet_ReceiveFrame(char * buffer);
void Ethernet_WriteFrame(char * buffer, int length);

