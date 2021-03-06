/*
 ===============================================================================
 Name        : TestEthernet.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

#include "uip.h"
#include "uip_arp.h"
#include "Ethernet.h"
#include <Timer.h>
//#include "tapdev.h"
#define CLOCK_SECOND 1000

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

/*---------------------------------------------------------------------------*/
int main(void) {
	int i;
	uip_ipaddr_t ipaddr;
	unsigned int periodic_timer, arp_timer;

	TIMER0_Init(1);
	periodic_timer = TIMER0_GetValue();
	arp_timer = TIMER0_GetValue();

	Ethernet_Init();
	//tapdev_init();

	uip_init();

	//foram alterados os ips
	uip_ipaddr(ipaddr, 10, 10, 3, 172);
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, 10, 10, 7, 254);
	uip_setdraddr(ipaddr);
	uip_ipaddr(ipaddr, 255, 255, 248, 0);
	uip_setnetmask(ipaddr);

	//httpd_init();

	/*  telnetd_init();*/

	/*  hello_world_init();*/

	/*  {
	 u8_t mac[6] = {1,2,3,4,5,6};
	 dhcpc_init(&mac, 6);
	 }*/

	/*uip_ipaddr(ipaddr, 127,0,0,1);
	 smtp_configure("localhost", ipaddr);
	 SMTP_SEND("adam@sics.se", NULL, "uip-testing@example.com",
	 "Testing SMTP from uIP",
	 "Test message sent by uIP\r\n");*/

	webclient_init();
	resolv_init();

	char * host = "93.184.216.34";
	char * file = "/";
	short port = 8080;

	if(!webclient_get(host, port, file))
		while(1);

	while (1) {
		uip_len = Ethernet_ReceiveFrame(uip_buf);
		if (uip_len > 0) {
			if (BUF->type == htons(UIP_ETHTYPE_IP)) {
				uip_arp_ipin();
				uip_input();
				/* If the above function invocation resulted in data that
				 should be sent out on the network, the global variable
				 uip_len is set to a value > 0. */
				if (uip_len > 0) {
					uip_arp_out();
					Ethernet_WriteFrame(uip_buf, uip_len);
				}
			} else if (BUF->type == htons(UIP_ETHTYPE_ARP)) {
				uip_arp_arpin();
				/* If the above function invocation resulted in data that
				 should be sent out on the network, the global variable
				 uip_len is set to a value > 0. */
				if (uip_len > 0) {
					Ethernet_WriteFrame(uip_buf, uip_len);
				}
			}

		} else if (TIMER0_Elapse(periodic_timer) > CLOCK_SECOND / 2) {
			periodic_timer = TIMER0_GetValue();
			for (i = 0; i < UIP_CONNS; i++) {
				uip_periodic(i);
				/* If the above function invocation resulted in data that
				 should be sent out on the network, the global variable
				 uip_len is set to a value > 0. */
				if (uip_len > 0) {
					uip_arp_out();
					Ethernet_WriteFrame(uip_buf, uip_len);
				}
			}

#if UIP_UDP
			for(i = 0; i < UIP_UDP_CONNS; i++) {
				uip_udp_periodic(i);
				/* If the above function invocation resulted in data that
				 should be sent out on the network, the global variable
				 uip_len is set to a value > 0. */
				if(uip_len > 0) {
					uip_arp_out();
					Ethernet_WriteFrame(uip_buf, uip_len);
				}
			}
#endif /* UIP_UDP */

			/* Call the ARP timer function every 10 seconds. */
			if (TIMER0_Elapse(arp_timer) > CLOCK_SECOND * 10) {
				arp_timer = TIMER0_GetValue();
				uip_arp_timer();
			}
		}
	}
	return 0;
}
/*---------------------------------------------------------------------------*/
void uip_log(char *m) {
	printf("uIP log message: %s\n", m);
}
void resolv_found(char *name, u16_t *ipaddr) {
	u16_t *ipaddr2;

	if (ipaddr == NULL) {
		printf("Host '%s' not found.\n", name);
	} else {
		printf("Found name '%s' = %d.%d.%d.%d\n", name, htons(ipaddr[0]) >> 8,
				htons(ipaddr[0]) & 0xff, htons(ipaddr[1]) >> 8,
				htons(ipaddr[1]) & 0xff);
		/*    webclient_get("www.sics.se", 80, "/~adam/uip");*/
	}
}
#ifdef __DHCPC_H__
void
dhcpc_configured(const struct dhcpc_state *s)
{
	uip_sethostaddr(s->ipaddr);
	uip_setnetmask(s->netmask);
	uip_setdraddr(s->default_router);
	resolv_conf(s->dnsaddr);
}
#endif /* __DHCPC_H__ */
void smtp_done(unsigned char code) {
	printf("SMTP done with code %d\n", code);
}
void webclient_closed(void) {
	printf("Webclient: connection closed\n");
}
void webclient_aborted(void) {
	printf("Webclient: connection aborted\n");
}
void webclient_timedout(void) {
	printf("Webclient: connection timed out\n");
}
extern void *uip_sappdata;
extern short uip_slen;
void webclient_connected(void) {
	printf("Webclient: Connection called.\n");
}
void webclient_datahandler(char *data, u16_t len) {
	printf("Webclient: got %d bytes of data, and data: %s.\n", len , data);
}
/*---------------------------------------------------------------------------*/

