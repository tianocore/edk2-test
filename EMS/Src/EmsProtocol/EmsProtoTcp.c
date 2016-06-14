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
  
    EmsProtoTcp.c
    
Abstract:

    Implementation for functions for protocol TCP

--*/

#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsPktCreate.h"
#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsProtoIpv6.h"
#include "EmsProtoTcp.h"
#include "EmsUtilityString.h"

STATIC
libnet_t          *
TcpCreatePacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T           *
TcpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

STATIC 
UINT16
Tcp6CalCheckSum(
  IN EMS_IPV6_ADDR localIPv6,
  IN EMS_IPV6_ADDR remoteIPv6,
  IN BOOLEAN payloadok,
  IN BOOLEAN optionsok,
  IN UINT32 tcplen,
  IN libnet_t      *l,
  IN libnet_ptag_t tcptag
  );

PROTOCOL_ENTRY_T  TcpProtocol = {
  "TCP",            /* name */
  TcpCreatePacket,  /* Create packet routine */
  TcpUnpackPacket,  /* Unpacket routine */
  NULL              /* TCP TCL initialzation routine*/
};

STATIC UINT16     TcpSrcPort;
STATIC UINT16     TcpDstPort;
STATIC UINT32     TcpSeq;
STATIC UINT32     TcpAck;
STATIC UINT8      TcpDataOffset;
STATIC UINT8      TcpCtrlFlag;
STATIC UINT16     TcpWinSize;
STATIC UINT16     TcpChecksum;
STATIC UINT16     TcpUrgent;
STATIC PAYLOAD_T  TcpOptions  = { NULL, 0 };
STATIC PAYLOAD_T  TcpPayload  = { NULL, 0 };
STATIC UINT8      IPver;

#define DEFAULT_SEQ_NUM   0x00
#define DEFAULT_ACK_NUM   0x00
#define DEFAULT_SRC_PORT  0x00
#define DEFAULT_CTRL_FLAG 0x00
#define DEFAULT_WIN_SIZE  0x400
#define DEFAULT_CHECKSUM  0x00
#define DEFAULT_URGENT    0x00

STATIC BOOLEAN    SrcPortOk;
STATIC BOOLEAN    DstPortOk;
STATIC BOOLEAN    SeqOk;
STATIC BOOLEAN    AckOk;
STATIC BOOLEAN    DataOffsetOk;
STATIC BOOLEAN    CtrlFlagOk;
STATIC BOOLEAN    WinSizeOk;
STATIC BOOLEAN    ChecksumOk;
STATIC BOOLEAN    UrgentOk;
STATIC BOOLEAN    OptionsOk;
STATIC BOOLEAN    PayloadOk;
STATIC BOOLEAN    IPverOK;

FIELD_T           TcpField[] = {
  /* name         type         value           Mandatory Isset?*/
  {
    "Tcp_sp",
    OCTET2,
    &TcpSrcPort,
    FALSE,
    &SrcPortOk
  },
  {
    "Tcp_dp",
    OCTET2,
    &TcpDstPort,
    TRUE,
    &DstPortOk
  },
  {
    "Tcp_seq",
    OCTET4,
    &TcpSeq,
    FALSE,
    &SeqOk
  },
  {
    "Tcp_ack",
    OCTET4,
    &TcpAck,
    FALSE,
    &AckOk
  },
  {
    "Tcp_offset",
    OCTET1,
    &TcpDataOffset,
    FALSE,
    &DataOffsetOk
  },
  {
    "Tcp_control",
    OCTET1,
    &TcpCtrlFlag,
    FALSE,
    &CtrlFlagOk
  },
  {
    "Tcp_win",
    OCTET2,
    &TcpWinSize,
    FALSE,
    &WinSizeOk
  },
  {
    "Tcp_sum",
    OCTET2,
    &TcpChecksum,
    FALSE,
    &ChecksumOk
  },
  {
    "Tcp_urg",
    OCTET2,
    &TcpUrgent,
    FALSE,
    &UrgentOk
  },
  {
    "Tcp_options",
    PAYLOAD,
    &TcpOptions,
    FALSE,
    &OptionsOk
  },
  {
    "Tcp_payload",
    PAYLOAD,
    &TcpPayload,
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
TcpCreatePacket (
  INT32 Argc,
  INT8  *Argv[]
  )
/*++

Routine Description:

  Create a TCP packet

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  NULL if error occurs
  The pointer to a libnet_t type's object if successfully

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
  for (Index = 0; TcpField[Index].Name; Index++) {
    *TcpField[Index].IsOk = FALSE;
    Status                = GetValueByName (&TcpField[Index], Argc, Argv);
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

  /*
   * Build TCP options
   */
  Tag = libnet_build_tcp_options (
          OptionsOk ? TcpOptions.Payload : NULL,
          OptionsOk ? TcpOptions.Len : 0,
          l,
          0
          );

  if (-1 == Tag) {
    return NULL;
  }

  /*
  * Build TCP packet
  */
  Len = LIBNET_TCP_H;
  Len += PayloadOk ? TcpPayload.Len : 0;

  Tag = libnet_build_tcp (
          SrcPortOk ? TcpSrcPort : DEFAULT_SRC_PORT,
          TcpDstPort,
          SeqOk ? TcpSeq : DEFAULT_SEQ_NUM,
          AckOk ? TcpAck : DEFAULT_ACK_NUM,
          CtrlFlagOk ? TcpCtrlFlag : DEFAULT_CTRL_FLAG,
          WinSizeOk ? TcpWinSize : DEFAULT_WIN_SIZE,
          ChecksumOk ? TcpChecksum : DEFAULT_CHECKSUM,
          TcpUrgent ? TcpUrgent : DEFAULT_URGENT,
          Len,
          PayloadOk ? TcpPayload.Payload : NULL,
          PayloadOk ? TcpPayload.Len : 0,
          l,
          0
          );

  if (-1 == Tag) {
    return NULL;
  }

  
  if(IPverOK && IPver==0x06) {
    if(!ChecksumOk) {

      Len = LIBNET_TCP_H;
      Len += PayloadOk ? TcpPayload.Len : 0;
      Len += OptionsOk ? TcpOptions.Len : 0;

      CheckSum = Tcp6CalCheckSum(
                   LocalIPv6,
                   RemoteIPv6,
                   PayloadOk,
                   OptionsOk,
                   Len,
                   l,
                   Tag
                   );
      Tag2 = Tag;

      Tag = libnet_build_tcp (
                   SrcPortOk ? TcpSrcPort : DEFAULT_SRC_PORT,
                   TcpDstPort,
                   SeqOk ? TcpSeq : DEFAULT_SEQ_NUM,
                   AckOk ? TcpAck : DEFAULT_ACK_NUM,
                   CtrlFlagOk ? TcpCtrlFlag : DEFAULT_CTRL_FLAG,
                   WinSizeOk ? TcpWinSize : DEFAULT_WIN_SIZE,
                   CheckSum,
                   TcpUrgent ? TcpUrgent : DEFAULT_URGENT,
                   Len,
                   PayloadOk ? TcpPayload.Payload : NULL,
                   PayloadOk ? TcpPayload.Len : 0,
                   l,
                   Tag2
                   );
    }

    Len = LIBNET_TCP_H;
    Len += PayloadOk ? TcpPayload.Len : 0;
    Len += OptionsOk ? TcpOptions.Len :0;

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
          /* total length of the IP packet */Len,
          /* nh next header */0x06,
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
  }
  else
  {
    Len = LIBNET_IPV4_H + LIBNET_TCP_H;
    Len += PayloadOk ? TcpPayload.Len : 0;
    Len += OptionsOk ? TcpOptions.Len :0;

    Tag = libnet_build_ipv4 (
          Len,
          0,
          /* TOS */GetIpId (),
          /* IP ID */0,
          /* IP Frag */0x40,
          /* TTL */IPPROTO_TCP,
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
TcpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack a TCP packet

Arguments:

  Packet  - The packet should be unpacked
  Length  - The size of the packet

Returns:

  NULL if error occurs
  The pointer to a FIELD_t type's object if successfully

--*/
{
  TCP_HEADER  *Header;
  UINT32      PayloadLen;
  UINT32      OptionsLen;

  /*++
  Parse IP header
  --*/
  ETH_HEADER  *EthHeader;
  UINT32      SzIPHeader;
  
  EthHeader = (ETH_HEADER *) Packet;
  if( EthHeader->Type == 0x0008 ) {
    SzIPHeader = sizeof (IP_HEADER);  //IPv4 header
  } else if ( EthHeader->Type == 0xdd86 ){//IPv6 header (Serial next headers is not supported)
    SzIPHeader = sizeof (IPV6_HEADER);
  } else {
    return NULL;//wrong IP header
  }
  
  //if (Length < (sizeof (TCP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
  if (Length < (sizeof (TCP_HEADER) + SzIPHeader + sizeof (ETH_HEADER))) {
    return NULL;
  }

  //Header        = (TCP_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
  Header        = (TCP_HEADER *) (Packet + sizeof (ETH_HEADER) + SzIPHeader);

  TcpSrcPort    = ntohs (Header->TcpSrcPort);
  TcpDstPort    = ntohs (Header->TcpDstPort);
  TcpSeq        = ntohl (Header->TcpSeq);
  TcpAck        = ntohl (Header->TcpAck);
  TcpDataOffset = (Header->TcpDataOffset >> 4) & 0x0F;
  TcpCtrlFlag   = Header->TcpCtrlFlag;
  TcpWinSize    = ntohs (Header->TcpWinSize);
  TcpChecksum   = ntohs (Header->TcpChecksum);
  TcpUrgent     = ntohs (Header->TcpUrgent);

  if (NULL != TcpPayload.Payload) {
    free (TcpPayload.Payload);
    TcpPayload.Payload  = NULL;
    TcpPayload.Len      = 0;
  }

  if (NULL != TcpOptions.Payload) {
    free (TcpOptions.Payload);
    TcpOptions.Payload  = NULL;
    TcpOptions.Len      = 0;
  }

  /*
   * data offset is 4 bits width.
   */
  if (TcpDataOffset < 5 || TcpDataOffset > 15) {
    OptionsLen = 0;
  } else {
    OptionsLen = TcpDataOffset * 4 - LIBNET_TCP_H;
  }

  if (OptionsLen) {
    TcpOptions.Payload = malloc (OptionsLen);
//    memcpy (
//      TcpOptions.Payload,
//      Packet + sizeof (TCP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER),
//      OptionsLen
//      );
    memcpy (
      TcpOptions.Payload,
      Packet + sizeof (TCP_HEADER) + SzIPHeader + sizeof (ETH_HEADER),
      OptionsLen
      );

    TcpOptions.Len = OptionsLen;
  }

  //PayloadLen = Length - OptionsLen - sizeof (TCP_HEADER) - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
  PayloadLen = Length - OptionsLen - sizeof (TCP_HEADER) - SzIPHeader - sizeof (ETH_HEADER);
  if (PayloadLen) {
    TcpPayload.Payload = malloc (PayloadLen);
    //memcpy (
    //  TcpPayload.Payload,
    //  Packet + OptionsLen + sizeof (TCP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER),
    //  PayloadLen
    //  );
    memcpy (
      TcpPayload.Payload,
      Packet + OptionsLen + sizeof (TCP_HEADER) + SzIPHeader + sizeof (ETH_HEADER),
      PayloadLen
      );
    TcpPayload.Len = PayloadLen;
  }

  return TcpField;
}

STATIC 
UINT16
Tcp6CalCheckSum(
  IN EMS_IPV6_ADDR localIPv6,
  IN EMS_IPV6_ADDR remoteIPv6,
  IN BOOLEAN payloadok,
  IN BOOLEAN optionsok,
  IN UINT32 tcplen,
  IN libnet_t      *l,
  IN libnet_ptag_t tcptag
)
/*++

Routine Description:

  Calculate CheckSum for TCP over IPv6

Arguments:

  EMS_IPV6_ADDR    localIPv6    :Local IPv6 Address for pesudo header
  EMS_IPV6_ADDR    remoteIPv6   :Remote IPv6-Address for pesudo header
  libnet_t         *l           :Current libnet context
  IN BOOLEAN       payloadok    :Whether contains payload
  IN BOOLEAN       optionsok    :Whether contains options
  IN UINT32        tcplen       :Length of TCP packet
  IN libnet_ptag_t tcptag       :Tag for TCP header

Returns:

  UINT16           checksum     :16bit checksum

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
               0x06,
               tcplen
               );
  Sum += BlockSum;

  //Sum for TCP header
  CheckSumBuf = libnet_getpbuf(l, tcptag);
  CheckSumBufSz = libnet_getpbuf_size(l, tcptag);

  BlockSum = EmsCalBufSum16(
               Offset,
               CheckSumBuf,
               CheckSumBufSz
               );
  Sum += BlockSum;
  Offset += CheckSumBufSz;

  //Sum for TCP option
  if(optionsok) {
    CheckSumBuf = libnet_getpbuf(l, tcptag-1);
    CheckSumBufSz = libnet_getpbuf_size(l, tcptag-1);

    BlockSum = EmsCalBufSum16(
                 Offset,
                 CheckSumBuf,
                 CheckSumBufSz
                 );
    Sum += BlockSum;
    Offset += CheckSumBufSz;
  }

  //Sum for TCP payload
  if(payloadok) {
    CheckSumBuf = libnet_getpbuf(l, tcptag+1);
    CheckSumBufSz = libnet_getpbuf_size(l, tcptag+1);

    BlockSum = EmsCalBufSum16(
                 Offset,
                 CheckSumBuf,
                 CheckSumBufSz
                 );
  Sum += BlockSum;
  Offset += CheckSumBufSz;
  }

  return (EmsCalCheckSum16( Sum ));
};
