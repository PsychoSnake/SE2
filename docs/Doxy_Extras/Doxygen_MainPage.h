/*! \mainpage
 *
 * Important Schematics:
 * - \subpage Wiring "Wiring Schematic"
 * 
 * Brief Explanation of the Project development:
 * 
 * 	The project proposed in this semester for Embedded Systems 1 was the Tic-Tac-Toe. It was used the LPC2106 ARM7TDMI-S Microcontroller
 * 	with the HEADER BOARD Olimex LPC-H2106. It's needed peripherals were studied and developed APIs for use in the application.
 * 	Such peripherals are GPIO, TIMER0, SPI, RTC, IAP. For application use it was created an abstraction for these APIs to provide
 * 	easier use and better understanding(represented in the AppHierarchy Schematic). 
 * 	The application is divided into three modes:
 * 
 * 	IDLE -> It's the main mode. The systems starts in this mode and from this the other two modes can be accessed with specific actions.
 * 			Press * and # for two seconds to enter Configuration;
 * 			Press * to enter Play;
 * 
 * 	CONFIG -> In this mode the time and date from the RTC can be configured and also the game results can be cleared.
 * 			Press 1 to configure Time;
 * 			Press 2 to configure Date;
 * 			(For the above press # to continue to next parameter until the last one that exits the specific configuration)
 * 			Press 3 to delete Game Results;
 * 
 * 	PLAY -> In this mode the game is played using 0..9 keys.
 * 	
 * 	!!!NOTE!!! -> In the Application Fluxogram is better explained the actions and modes behaviours
 *
 */ 

/*! \page Wiring
 *
 * \htmlonly <style>div.image img[src="Wiring Diagram.png"]{width:750px;}</style> \endhtmlonly
 * 
 * \image html "Wiring Diagram.png" "Wiring done for the Periferics(KeyPad, LCD, EEPROM and Ethernet physical device)"
 *
 */