/*
 * Copyright (c) 2001, Adam Dunkels.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Adam Dunkels.
 * 4. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.  
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: tapdev.h,v 1.1 2002/01/10 06:22:56 adam Exp $
 *
 */

#ifndef __TAPDEV_H__
#define __TAPDEV_H__

#define UIP_ETHADDR0    0x02  /**< The first octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR1    0x01  /**< The second octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR2    0x04  /**< The third octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR3    0x03  /**< The fourth octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR4    0x06  /**< The fifth octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR5    0x05  /**< The sixth octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */


void tapdev_init(void);
unsigned int tapdev_read(void *pPacket);
void tapdev_send(void *pPacket, unsigned int size);

#endif /* __TAPDEV_H__ */
