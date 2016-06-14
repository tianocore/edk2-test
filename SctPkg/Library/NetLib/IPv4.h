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

  IPv4.h

Abstract:

  Header file of IP v4 network stack.

--*/
#ifndef __EFI_IPV4_PACKET_HEADER_H
#define __EFI_IPV4_PACKET_HEADER_H

#include <Library/NetLib.h>

//
// transport layer protocol type
//
#define EFI_IP_PROTO_ICMP                0x01
#define EFI_IP_PROTO_IGMP                0x02
#define EFI_IP_PROTO_TCP                 0x06
#define EFI_IP_PROTO_UDP                 0x11
#define EFI_IP_PROTO_RAW                 0xff
//
// fragment flag masks
//
#define EFI_IP_FRAGMENT_RF               0x8000        /* reserved fragment flag */
#define EFI_IP_FRAGMENT_DF               0x4000        /* dont fragment flag */
#define EFI_IP_FRAGMENT_MF               0x2000        /* more fragments flag */
#define EFI_IP_FRAGMENT_OFFMASK          0x1fff        /* mask for fragmenting bits *///

//
// IP protocol address length
//
#define EFI_IP_VERSION                      4
#define EFI_IPv4_ADDRESS_LEN            4  //32bits, 4 bytes
#define EFI_IP_ADDRESS_LENGTH               EFI_IPv4_ADDRESS_LEN  

#define EFI_IP_MIN_HLEN                     0x5  //5 *32bits = 20 bytes
#define EFI_IP_MAX_HLEN                     0xf //15 *32bits = 60 bytes
#define EFI_IP_MAX_PLEN                     0xFFFF  //maximum 64K Bytes per packet

//
// ICMP message type
//
#define ICMP_TYPE_ECHO_REPLY                      0
#define ICMP_TYPE_DESTINATION_UNREACHABLE         3
#define ICMP_TYPE_SOURCE_QUENCH                   4
#define ICMP_TYPE_REDIRECT                        5
#define ICMP_TYPE_ECHO_REQUEST                    8
#define ICMP_TYPE_TIME_EXCEEDED                   11
#define ICMP_TYPE_PARAMETER_PROBLEM               12
#define ICMP_TYPE_TIMESTAMP_REQUEST               13
#define ICMP_TYPE_TIMESTAMP_REPLY                 14
#define ICMP_TYPE_INFORMATION_REQUEST             15
#define ICMP_TYPE_INFORMATION_REPLY               16
#define ICMP_TYPE_ADDRESS_MASK_REQUEST            17
#define ICMP_TYPE_ADDRESS_MASK_REPLY              18
#define ICMP_TYPE_MAXIMUM                         18
//
// ICMP message code
//
#define ICMP_CODE_NULL                            0

#define ICMP_CODE_UNREACH_NET                     0
#define ICMP_CODE_UNREACH_HOST                    1
#define ICMP_CODE_UNREACH_PROTOCOL                2
#define ICMP_CODE_UNREACH_PORT                    3
#define ICMP_CODE_UNREACH_NEED_FLAG               4
#define ICMP_CODE_UNREACH_SRC_FAIL                5

typedef union{
  UINT32           Addr[1];
  EFI_IPv4_ADDRESS v4;
}EFI_IP4_ADDRESS;

//
// Convert EFI_IPv4_ADDRESS to be EFI_IP4_ADDRESS
//
#define addr_cast(x) ((EFI_IP4_ADDRESS*)(x))

// 
// Convert EFI_IPv4_ADDRESS to be unsigned long value
//
#define ULADDR(x)    (addr_cast(x)->Addr[0])

//
// Convert a Unsigned Long into pointer to EFI_IPv4_ADDRESS.
//
#define V4ADDR(x)    (&addr_cast(x)->v4)

//
// Some useful IPv4 macros.
//
#define EFI_IP_HEADER_LEN(HdrPtr) \
  ((HdrPtr)->HeaderLength << 2)

#define EFI_IP_DATA_LEN(HdrPtr)   \
  (NTOHS((HdrPtr)->TotalLength) - EFI_IP_HEADER_LEN(HdrPtr))

#define EFI_IP_DATA_POINTER(HdrPtr)  \
  ( ((CHAR8*)(HdrPtr)) + EFI_IP_HEADER_LEN(HdrPtr) ) 

#define EFI_IP_FRAGMENT_OFFSET(HdrPtr)      ((HdrPtr)->FragmentOffset & EFI_IP_FRAGMENT_OFFMASK)
#define EFI_IP_MORE_FRAGMENTS(HdrPtr)       ((HdrPtr)->FlagmentOffset & EFI_IP_FRAGMENT_MF)
#define EFI_IP_DONT_FRAGMENT(HdrPtr)        ((HdrPtr)->FlagmentOffset & EFI_IP_FRAGMENT_DF)


//
//Determine the class of IP address from the first byte of address
//EFI_IP_ADDRESS  *x,*y:  pointer to IPv4 address in network byte order
//
#define  IP_IS_CLASSA(x)  ((addr_cast(x)->v4.Addr[0] & 0x80) == 0x00)  /* IP Class A address  */
#define  IP_IS_CLASSB(x)  ((addr_cast(x)->v4.Addr[0] & 0xc0) == 0x80)  /* IP Class B address  */
#define  IP_IS_CLASSC(x)  ((addr_cast(x)->v4.Addr[0] & 0xe0) == 0xc0)  /* IP Class C address  */
#define  IP_IS_CLASSD(x)  ((addr_cast(x)->v4.Addr[0] & 0xf0) == 0xe0)  /* IP Class D address  */
#define  IP_IS_CLASSE(x)  ((addr_cast(x)->v4.Addr[0] & 0xf8) == 0xf0)  /* IP Class E address  */

//
//determine if IP address (array of bytes in network order) is broadcast or multicast address
//
#define IP_ALLONE           (0xffffffff)
#define IP_ALLZERO          (0x00000000)
#define IP_IS_ALLONE(x)     ( addr_cast(x)->Addr[0] == IP_ALLONE ) /*IP address is 0xffffffff*/
#define IP_IS_ALLZERO(x)    ( addr_cast(x)->Addr[0] == IP_ALLZERO) /*IP address is 0x00000000*/

#define IP_ADDR_CMP(x,y)    ( addr_cast(x)->Addr[0] == addr_cast(y)->Addr[0] )
#define IP_ADDR_MASKCMP(x,y,netmask) ( (addr_cast(x)->Addr[0] & addr_cast(netmask)->Addr[0]) == (addr_cast(y)->Addr[0] & addr_cast(netmask)->Addr[0]) )
#define IP_ADDR_MASKICMP(dstaddr, dstnet, mask) ( (addr_cast(dstaddr)->Addr[0] & addr_cast(mask)->Addr[0]) == addr_cast(dstnet)->Addr[0] )

#define IS_INADDR_ANY(x)              IP_IS_ALLZERO(x)
#define IS_INADDR_UNICAST(x)          (IP_IS_CLASSC(x) || IP_IS_CLASSB(x) || IP_IS_CLASSA(x))
#define IS_INADDR_BROADCAST(x)        IP_IS_ALLONE(x)
#define IS_INADDR_MULTICAST(x)        IP_IS_CLASSD(x)
#define IS_INADDR_LOCALBCAST(x,mask)  ((~(addr_cast(x)->Addr[0]) & ~(addr_cast(mask)->Addr[0])) == 0)
    

#define IGMP_ALL_HOSTS            HTONL(0xE0000001)
#define IGMP_ALL_ROUTER           HTONL(0xE0000002)
#define IS_INADDR_LOCALMCAST(x)   ((addr_cast(x)->Addr[0] & HTONL(0xffffff00)) == HTONL(0xe0000000))

#define IP_COPY_ADDR(dst,src)   ( addr_cast(dst)->Addr[0] =  addr_cast(src)->Addr[0] )
#define IP_MASK_ADDR(dst,mask)  ( addr_cast(dst)->Addr[0] &= addr_cast(mask)->Addr[0] )
#define IP_ZERO_ADDR(x)         ( addr_cast(x)->Addr[0] = IP_ALLZERO )
#define IP_SET_BCAST_ADDR(x)    ( addr_cast(x)->Addr[0] = IP_ALLONE  )
#define IP_SET_ULADDR(x,laddr)  ( addr_cast(x)->Addr[0] = laddr )

#define RAW_IP_TO_EFI_IP(x)     ((EFI_IP4_ADDRESS*)(x))
#define EFI_IP_TO_RAW_IP(x)     (((x)->v4.Addr))

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//  Typical ethernet IPv4 packet layout:
//

//
//  +----- ----- ----- ----- ----- ----- ----- ----- -----+
//  | Media header  Destination MAC (6 bytes)             |
//  |               Source MAC (6 bytes)                  |
//  |               Protocol (2 bytes) [IP, ARP, etc]     |
//  +----- ----- ----- ----- ----- ----- ----- ----- -----+
//  | IPv4 header   HeaderLen (4 bits)                    |
//  |               Version (4 bits) [IPv4, IPv6]         |
//  |               TypeOfService (1 byte)                |
//  |               TotalLen (2 bytes)                    |
//  |               Identification (2 bytes)              |
//  |               FragmentOffset (2 bytes)              |
//  |               TimeToLive (1 byte)                   |
//  |               Protocol (1 byte)                     |
//  |               HeaderChecksum (2 bytes)              |
//  |               SourceIp (4 bytes)                    |
//  |               DestinationIp (4 bytes)               |
//  +----- ----- ----- ----- ----- ----- ----- ----- -----+
//  | IPv4 data                                           |
//  +----- ----- ----- ----- ----- ----- ----- ----- -----+
//

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
// Detailed information on IPv4 packet contents can be found in RFC 791.
// www.ietf.org
//
#ifndef __STRUCT_EFI_IP4_HEADER__
#define __STRUCT_EFI_IP4_HEADER__
#pragma pack(1)

typedef struct _EFI_IP4_HEADER {
  UINT8               HeaderLength:4;
  UINT8               Version:4;
//UINT8               VerHdrLen; //On little-endian platform, VersionHeader >> 4 is the version number.
  UINT8               TypeOfService;
  UINT16              TotalLength;
  UINT16              Identification;
  UINT16              Fragmentation;
  UINT8               TimeToLive;
  UINT8               Protocol;
  UINT16              Checksum;
  EFI_IPv4_ADDRESS    SourceAddress;
  EFI_IPv4_ADDRESS    DestinationAddress;
} EFI_IP4_HEADER;
#pragma pack()

#endif //__STRUCT_EFI_IP4_HEADER__

#pragma pack(1)
typedef struct  {
  UINT8                 Type;
  UINT8                 Code;
  UINT16                Checksum;
  union {
    struct {
      UINT16            Identifier;
      UINT16            SequenceNo;
    } echo;
    EFI_IPv4_ADDRESS    GatewayAddress;
    struct {
      UINT16            __unused;
      UINT16            MaxTransmitUnit;
    } frag;
    UINT32              Unused;
  } un;
} EFI_IP4_ICMP_HEADER;
#pragma pack()

//************************************************
//           EFI_UDP4_HEADER                     *
//************************************************
#pragma pack(1)
typedef struct {
  UINT16     SourcePortNum;
  UINT16     DestinationPortNum;
  UINT16     UdpLength;
  UINT16     UdpCheckSum;
} EFI_UDP4_HEADER;
#pragma pack()


#define EFI_UDP4_HEADER_SIZE  sizeof(EFI_UDP4_HEADER)

//
// 64 bits of Data Datagram in ICMP payload
//
#define ICMP_ERROR_PACKET_LENGTH  8
//
//  Length of ICMP data packet
//
#define MAX_ICMP_DATA_LENGTH      (sizeof(EFI_IP4_ICMP_HEADER) + (EFI_IP_MAX_HLEN << 2) + ICMP_ERROR_PACKET_LENGTH)
#define MIN_ICMP_DATA_LENGTH      (sizeof(EFI_IP4_ICMP_HEADER) + (EFI_IP_MIN_HLEN << 2) + ICMP_ERROR_PACKET_LENGTH)



/*
 *  Utilities of address comparison
 */
VOID  SetIpNetMask(
  IN EFI_IPv4_ADDRESS     *IpAddr,
  IN OUT EFI_IPv4_ADDRESS *NetMask);

BOOLEAN IpIsBcast(
  IN EFI_IPv4_ADDRESS *DestAddr,
  IN EFI_IPv4_ADDRESS *Netmask  OPTIONAL
  );

BOOLEAN IpIsDirectBcast(
  IN EFI_IPv4_ADDRESS *DestAddr,/*net byte order*/
  IN EFI_IPv4_ADDRESS *Netmask/*net byte order*/
  );

BOOLEAN IpIsSubnetMask(
  IN EFI_IPv4_ADDRESS * Mask
  );
/*
BOOLEAN MacIsBcast(
  IN ETHER_FRAME_HEADER*Packet);

VOID IpHdrNetToHost(
  IN OUT EFI_IP4_HEADER *IpHeader);

VOID IpHdrHostToNet(
  IN OUT EFI_IP4_HEADER *IpHeader);
*/

//
// Get the number of 1 in the binary form of Mask, e.g., IpNetPartLen(0x00ffffff ) == 24.
//
UINT8 IpNetPartLen(
  IN EFI_IPv4_ADDRESS* Mask
  );

#endif
