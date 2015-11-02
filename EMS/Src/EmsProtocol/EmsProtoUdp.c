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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsProtoUdp.c
    
Abstract:

    Implementation for functions for protocol UDP

--*/

#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsPktCreate.h"
#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsProtoIpv6.h"
#include "EmsProtoUdp.h"
#include "EmsUtilityString.h"

STATIC
libnet_t          *
UdpCreatePacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T           *
UdpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

STATIC 
UINT16
Udp6CalCheckSum(
  IN EMS_IPV6_ADDR localIPv6,
  IN EMS_IPV6_ADDR remoteIPv6,
  IN BOOLEAN payloadok,
  IN UINT32 udplen,
  IN libnet_t      *l,
  IN libnet_ptag_t udptag
);

PROTOCOL_ENTRY_T  UdpProtocol = {
  "UDP",            /* name */
  UdpCreatePacket,  /* Create packet routine */
  UdpUnpackPacket,  /* Unpacket routine */
  NULL              /* UDP TCL initialzation routine*/
};

STATIC UINT16     UdpSrcPort;
STATIC UINT16     UdpDstPort;
STATIC UINT16     UdpLength;
STATIC UINT16     UdpChecksum;
STATIC UINT16     IPver;
STATIC PAYLOAD_T  UdpPayload = { NULL, 0 };

#define DEFAULT_CHECKSUM  0x00

STATIC BOOLEAN    SrcPortOk;
STATIC BOOLEAN    DstPortOk;
STATIC BOOLEAN    LengthOk;
STATIC BOOLEAN    ChecksumOk;
STATIC BOOLEAN    PayloadOk;
STATIC BOOLEAN    IPverOK;

#define DEFAULT_SRC_PORT  0x00

FIELD_T           UdpField[] = {
  /* name         type         value           Mandatory Isset?*/
  {
    "Udp_sp",
    OCTET2,
    &UdpSrcPort,
    FALSE,
    &SrcPortOk
  },
  {
    "Udp_dp",
    OCTET2,
    &UdpDstPort,
    TRUE,
    &DstPortOk
  },
  {
    "Udp_len",
    OCTET2,
    &UdpLength,
    FALSE,
    &LengthOk
  },
  {
    "Udp_sum",
    OCTET2,
    &UdpChecksum,
    FALSE,
    &ChecksumOk
  },
  {
    "Udp_payload",
    PAYLOAD,
    &UdpPayload,
    FALSE,
    &PayloadOk
  },
  {
    "IP_ver",
    OCTET1,
    &IPver,
    FALSE,
    &IPverOK
  },
  {
    NULL
  }
};

STATIC
libnet_t *
UdpCreatePacket (
  INT32 Argc,
  INT8  *Argv[]
  )
/*++

Routine Description:

  Create an UDP packet

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  NULL if error occurs
  The pointer to a libnet_t type's object

--*/
{
  libnet_t      *l;
  libnet_ptag_t Tag;
  UINT32        Index;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  UINT32        Len;
  EMS_STATUS    Status;
  UINT16        CheckSum;
  libnet_ptag_t Tag2;
  //
  // Initialize all the local variables
  //
  for (Index = 0; UdpField[Index].Name; Index++) {
    *UdpField[Index].IsOk = FALSE;
    Status                = GetValueByName (&UdpField[Index], Argc, Argv);
    if (IsError (Status)) {
      return NULL;
    }
  }
  //
  //  Initialize the libnet
  //
  l = libnet_init (
        LIBNET_LINK,
        /* injection type */EmsInterface,
        /* network interface */ErrBuf /* errbuf */
        );
  if (NULL == l) {
    return NULL;
  }

  Len = LIBNET_UDP_H;
  Len += PayloadOk ? UdpPayload.Len : 0;

  Tag = libnet_build_udp (
          SrcPortOk ? UdpSrcPort : DEFAULT_SRC_PORT,
          UdpDstPort,
          Len,
          ChecksumOk ? UdpChecksum : DEFAULT_CHECKSUM,
          PayloadOk ? UdpPayload.Payload : NULL,
          PayloadOk ? UdpPayload.Len : 0,
          l,
          0
          );
  if (-1 == Tag) {
    return NULL;
  }

  /*
  * Build IP packet
  */
  if(IPverOK && IPver==0x06) {
    if(!ChecksumOk) {
      Len = LIBNET_UDP_H;
      Len += PayloadOk ? UdpPayload.Len : 0;

      CheckSum = Udp6CalCheckSum(
                   LocalIPv6,
                   RemoteIPv6,
                   PayloadOk,
                   Len,
                   l,
                   Tag
                   );
      Tag2 = Tag;

      Tag = libnet_build_udp (
              SrcPortOk ? UdpSrcPort : DEFAULT_SRC_PORT,
              UdpDstPort,
              Len,
              CheckSum,
              PayloadOk ? UdpPayload.Payload : NULL,
              PayloadOk ? UdpPayload.Len : 0,
              l,
              Tag2
              );
    }

    Len = LIBNET_UDP_H;
    Len += PayloadOk ? UdpPayload.Len : 0;

    /* Build IPv6 Packet
    * @param tc traffic class
    * @param fl flow label
    * @param len total length of the IP packet
    * @param nh next header
    * @param hl hop limit
    * @param src source IPv6 address
    * @param dst destination IPv6 address
    * @param payload optional payload or NULL
    * @param payload_s payload length or 0
    * @param l pointer to a libnet context
    * @param ptag protocol tag to modify an existing header, 0 to build a new one
    * @return protocol tag value on success, -1 on error
    */

    Tag = libnet_build_ipv6 (
          /* Traffic Class*/0,
          /* flow label */0,
          /* total length of the IP packet */Len,		//QUESTION: Only Indicate Payload Len Instead Of Packet Len In IPv6
          /* nh next header */0x11,
          /* hl hop limit*/0xff,
          /* src source IPv6 address */EmsIPv6htons(LocalIPv6),
          /* dst destination IPv6 address*/EmsIPv6htons(RemoteIPv6),
          /* payload optiona payload or NULL*/ NULL,
          /* payload_s payload length or 0 */0,
          /* l pointer to a libnet context */l,
          /* ptay, 0 to build a new one */0
          );
    if (-1 == Tag) {
      return NULL;
    }

    Tag = libnet_build_ethernet (
          RemoteEthaddr,
          /* ethernet destination */LocalEthaddr,
          /* ethernet source */0x86dd,
          /* protocol type */NULL,
          /* payload */0,
          /* payload size */l,
          /* libnet handle */0  /* libnet id */
          );
    if (-1 == Tag) {
      return NULL;
    }
  } else {
    Len = LIBNET_IPV4_H + LIBNET_UDP_H;
    Len += PayloadOk ? UdpPayload.Len : 0;

    Tag = libnet_build_ipv4 (
            Len,    //QUESTION: Indicate Packet Len Instead Of Payload Len In IPv4
            0,
            /* TOS */GetIpId (),
            /* IP ID */0,
            /* IP Frag */0x40,
            /* TTL */IPPROTO_UDP,
            /* protocol */0,
            /* checksum */htonl (LocalIp),
            htonl (RemoteIp),
            NULL,
            /* payload */0,
            /* payload size */l,
            0
            );
    if (-1 == Tag) {
      return NULL;
    }

    Tag = libnet_build_ethernet (
            RemoteEthaddr,
            LocalEthaddr,
            ETHERTYPE_IP,
            NULL,
            0,
            l,
            0
            );
    if (-1 == Tag) {
      return NULL;
    }
  }
 
  return l;
}

STATIC
FIELD_T *
UdpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack an UDP packet

Arguments:

  Packet  - The packet should be unpacked
  Length  - The size of the packet

Returns:

  NULL if error occurs
  The pointer to a FIELD_T type's object if successfully

--*/
{
  UDP_HEADER  *Header;
  UINT32      PayloadLen;

  /*++
  Parse IP header
  --*/
  ETH_HEADER *EthHeader;
  UINT32     SzIPHeader;

  EthHeader = (ETH_HEADER *) Packet;
  if( EthHeader->Type == 0x0008 ) {
    SzIPHeader = sizeof (IP_HEADER);        //IPv4 header
  } else if ( EthHeader->Type == 0xdd86 ){  //IPv6 header (Serial next headers is not supported)
    SzIPHeader = sizeof (IPV6_HEADER);
  } else {
    return NULL;                            //wrong IP header
  }
  
  //if (Length < (sizeof (UDP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
  if (Length < (sizeof (UDP_HEADER) + SzIPHeader + sizeof (ETH_HEADER))) {
    return NULL;
  }
  
  //Header      = (UDP_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
  Header      = (UDP_HEADER *) (Packet + sizeof (ETH_HEADER) + SzIPHeader);

  UdpSrcPort  = ntohs (Header->UdpSrcPort); 
  UdpDstPort  = ntohs (Header->UdpDstPort);
  UdpLength   = ntohs (Header->UdpLength);
  UdpChecksum = ntohs (Header->UdpChecksum);

  if (NULL != UdpPayload.Payload) {
    free (UdpPayload.Payload);
    UdpPayload.Payload  = NULL;
    UdpPayload.Len      = 0;
  }

//  PayloadLen = Length - sizeof (UDP_HEADER) - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
  PayloadLen = Length - sizeof (UDP_HEADER) - SzIPHeader - sizeof (ETH_HEADER);
  if (PayloadLen) {
    UdpPayload.Payload = malloc (PayloadLen);
    //memcpy (UdpPayload.Payload, Packet + sizeof (UDP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
    memcpy (UdpPayload.Payload, Packet + sizeof (UDP_HEADER) + SzIPHeader + sizeof (ETH_HEADER), PayloadLen);
    UdpPayload.Len = PayloadLen;
  }

  return UdpField;
}

STATIC 
UINT16
Udp6CalCheckSum(
  IN EMS_IPV6_ADDR localIPv6,
  IN EMS_IPV6_ADDR remoteIPv6,
  IN BOOLEAN payloadok,
  IN UINT32 udplen,
  IN libnet_t      *l,
  IN libnet_ptag_t udptag
)
/*++

Routine Description:

  Calculate CheckSum for UDP over IPv6

Arguments:

  EMS_IPV6_ADDR    localIPv6:  Local IPv6 Address for pesudo header
  EMS_IPV6_ADDR    remoteIPv6: Remote IPv6-Address for pesudo header
  libnet_t         *l:         Current libnet context
  IN BOOLEAN       payloadok:  Whether contains payload
  IN BOOLEAN       optionsok:  Whether contains options
  IN libnet_ptag_t udptag:     Tag for UDP header

Returns:

  UINT16           checksum:   16bit checksum

--*/
{
  UINT32 Sum = 0;
  UINT32 BlockSum;
  UINT32 Offset = 0;

  u_int8_t *   CheckSumBuf;
  u_int32_t    CheckSumBufSz;

  //sum for pesudo header
  BlockSum = EmsCalPHeaderSum16(
               localIPv6,
               remoteIPv6,
               0x11,
               udplen
               );
  Sum += BlockSum;

  //Sum for UDP Packet

  CheckSumBuf = libnet_getpbuf(l, udptag);
  CheckSumBufSz = libnet_getpbuf_size(l, udptag);

  BlockSum = EmsCalBufSum16(
               Offset,
               CheckSumBuf,
               CheckSumBufSz
               );
  Sum += BlockSum;
  Offset += CheckSumBufSz;

  return (EmsCalCheckSum16( Sum ));
};
