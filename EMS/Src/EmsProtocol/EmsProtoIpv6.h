/** @file
 
  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsProtoIpv6.h
    
Abstract:

    Incude header files for protocol IP

--*/

#ifndef __EMS_IPV6_H__
#define __EMS_IPV6_H__

#include "EmsTclInit.h"
#include "EmsTypes.h"
#include "EmsProtocols.h"

extern PROTOCOL_ENTRY_T        IPv6Protocol;
extern EMS_IPV6_ADDR           LocalIPv6;
extern EMS_IPV6_ADDR           RemoteIPv6;


typedef struct _IPV6_HEADER {
  UINT32   IPV6First32;
  //IPv6Ver: 4, /* Version */
  //IPv6TC : 8,        /* Traffic Class*/
  //IPv6FL : 20;       /* Flow Label */               
  UINT16  IPv6PldLen; /* Payload Length */
  UINT8   IPv6NH;     /* Next Header */
  UINT8   IPv6HL;     /* Hop Limit */
  EMS_IPV6_ADDR  IPv6Src;    /* source ip address */
  EMS_IPV6_ADDR  IPv6Dst;    /* destination ip address */
} IPV6_HEADER;

EMS_IPV6_ADDR
EmsIPv6htons(
  EMS_IPV6_ADDR hostIPv6
)
/*++

Routine Description:

 This function takes a IPv6 Address
 in host byte order and returns a IPv6 Address
 in network byte order used in TCP/IP networks

Arguments:

  EMS_IPV6_ADDR hostIpv6 : The IPV6 Address in host byte order

Returns:

  Return the IP Id

--*/
;
EMS_IPV6_ADDR
EmsIPv6ntohs (
  EMS_IPV6_ADDR netIPv6
)
/*++

Routine Description:

 This function takes a IPv6 Address
 in TCP/IP networks and returns a IPv6 Address
 in network byte order used in host byte order 

Arguments:

  EMS_IPV6_ADDR netIpv6 : The IPV6 Address n TCP/IP networks

Returns:

  Return the EMS_IPV6_ADDR in  TCP/IP networks

--*/
;

UINT32
EmsCalPHeaderSum16(
  IN EMS_IPV6_ADDR localIPv6,
  IN EMS_IPV6_ADDR remoteIPv6,
  IN UINT8 nh,
  IN UINT32 len
)
/*++		

Routine Description:				

 This function calculate the sum for
 Pesudo IPv6 Header.

Arguments:

  EMS_IPV6_ADDR localIPv6     : The local IPV6 Address in host byte order
  EMS_IPV6_ADDR remoetIPv6 : The remote IPV6 Address in host byte order 
  UINT8 nh			           : Flag for next header
  UINT32 len				    : Length of TCP/UDP payload
  
Returns:

  UINT32 sum			           : 32bit sum 

--*/
;

UINT32 
EmsCalBufSum16(
  IN UINT32 offset,
  IN u_int8_t *payload,
  IN UINT32 len
)
/*++		

Routine Description:				

 This function calculate the sum for
 a buffer. If the buffer starts with odd
 byte, extra calcualtion will be done

Arguments:

  UINT32 offset			    : Offset of the start byte
  UINT8 *payload			    : Buffer pointer
  UINT32 len				    : Buffer length
  
Returns:

  UINT32 sum			           : 32bit sum

--*/
;

UINT16
EmsCalCheckSum16(
  IN UINT32 sum
)
/*++		

Routine Description:				

 This function generate 16bit checksum from
 32bit sum

Arguments:

  UINT32 sum   			    : 32bit sum
  
Returns:

  UINT16 checksum			           : 16bit checksum

--*/
;

#endif

