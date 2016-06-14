/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
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

