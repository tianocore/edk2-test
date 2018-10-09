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
  
    EmsProtoIgmp.c
    
Abstract:

    Implementation for functions for protocol IGMP

--*/

#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsPktCreate.h"
#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIgmp.h"
#include "EmsUtilityString.h"

STATIC
libnet_t          *
IgmpCreatePacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T           *
IgmpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

PROTOCOL_ENTRY_T  IgmpProtocol = {
  "IGMP",           /* name */
  IgmpCreatePacket, /* Create packet routine */
  IgmpUnpackPacket, /* Unpacket routine */
  NULL              /* IP TCL initialzation routine*/
};

#define ALL_HOST    0xe0000001
#define ALL_ROUTER  0xe0000002

STATIC BOOLEAN    TypeOk;
STATIC BOOLEAN    MasResTimeOk;
STATIC BOOLEAN    ChecksumOk;
STATIC BOOLEAN    IpOk;
STATIC BOOLEAN    PayloadOk;
STATIC BOOLEAN    IgmpSrcOk;
STATIC BOOLEAN    IgmpDstOk;

STATIC UINT8      IgmpType;
STATIC UINT8      MaxResTime;
STATIC UINT16     IgmpChecksum;
STATIC UINT32     IgmpIp;
STATIC PAYLOAD_T  IgmpPayload = { NULL, 0 };
STATIC UINT32     IgmpSrc;
STATIC UINT32     IgmpDst;

STATIC UINT8      DefaultMaxRestTime  = 0;
STATIC UINT8      DefaultChecksum     = 0;
STATIC UINT32     DefaultIgmpDest     = ALL_HOST;

STATIC UINT8      IgmpRemoteEth[6];

FIELD_T           IgmpField[] = {
  /* name            type       value            M      IsSet?*/
  {
    "Igmp_type",
    OCTET1,
    &IgmpType,
    TRUE,
    &TypeOk
  },
  {
    "Igmp_MaxResTime",
    OCTET1,
    &MaxResTime,
    FALSE,
    &MasResTimeOk
  },
  {
    "Igmp_sum",
    OCTET2,
    &IgmpChecksum,
    FALSE,
    &ChecksumOk
  },
  {
    "Igmp_ip",
    IPADDR,
    &IgmpIp,
    TRUE,
    &IpOk
  },
  {
    "Igmp_payload",
    PAYLOAD,
    &IgmpPayload,
    FALSE,
    &PayloadOk
  },
  {
    "Igmp_srcip",
    IPADDR,
    &IgmpSrc,
    FALSE,
    &IgmpSrcOk
  },
  {
    "Igmp_destip",
    IPADDR,
    &IgmpDst,
    FALSE,
    &IgmpDstOk
  },
  {
    NULL
  }
};

STATIC
libnet_t *
IgmpCreatePacket (
  INT32 Argc,
  INT8  *Argv[]
  )
/*++

Routine Description:

  Create an IGMP packet

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  The pointer to a libnet_t data structure if create successfully
  otherwise NULL

--*/
{
  libnet_t      *l;
  libnet_ptag_t Tag;
  UINT32        Index;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  UINT32        Len;
  EMS_STATUS    Status;
  //
  // Initialize all the local variables
  //
  for (Index = 0; IgmpField[Index].Name; Index++) {
    *IgmpField[Index].IsOk  = FALSE;
    Status                  = GetValueByName (&IgmpField[Index], Argc, Argv);
    if (IsError (Status)) {
      return NULL;
    }
  }

  /*
  *  Initialize the libnet
  */
  l = libnet_init (
        LIBNET_LINK,
        /* injection type */EmsInterface,
        /* network interface */ErrBuf /* errbuf */
        );

  if (NULL == l) {
  }

  Tag = libnet_build_igmp (
          IgmpType,
          MasResTimeOk ? MaxResTime : DefaultMaxRestTime,
          ChecksumOk ? IgmpChecksum : DefaultChecksum,
          htonl (IgmpIp),
          PayloadOk ? IgmpPayload.Payload : NULL,
          PayloadOk ? IgmpPayload.Len : 0,
          l,
          0
          );

  if (-1 == Tag) {
    return NULL;
  }

  Len = LIBNET_IPV4_H + LIBNET_IGMP_H;
  Len += PayloadOk ? IgmpPayload.Len : 0;

  Tag = libnet_build_ipv4 (
          Len,
          /* length */0,
          /* TOS */GetIpId (),
          /* IP ID */0,
          /* IP Frag */1,
          /* TTL */IPPROTO_IGMP,
          /* protocol */0,
          /* checksum */IgmpSrcOk ? htonl (IgmpSrc) : htonl (LocalIp),
          /*source IP */IgmpDstOk ? htonl (IgmpDst) : htonl (DefaultIgmpDest),
          /* destination IP */NULL,
          /* payload */0,
          /* payload size */l,
          /* libnet handle */0
          );
  if (-1 == Tag) {
    return NULL;
  }
  //
  // Calculate remote ethernet address from destip.
  //
  IgmpDst           = IgmpDstOk ? IgmpDst : DefaultIgmpDest;
  IgmpRemoteEth[0]  = 0x01;
  IgmpRemoteEth[1]  = 0x00;
  IgmpRemoteEth[2]  = 0x5e;
  IgmpRemoteEth[3]  = (IgmpDst >> 16) & 0x7f;
  IgmpRemoteEth[4]  = (IgmpDst >> 8) & 0xff;
  IgmpRemoteEth[5]  = IgmpDst & 0xff;

  Tag = libnet_build_ethernet (
          IgmpRemoteEth,
          /* ethernet destination */LocalEthaddr,
          /* ethernet source */ETHERTYPE_IP,
          /* protocol type */NULL,
          /* payload */0,
          /* payload size */l,
          /* libnet handle */0
          );  /* libnet id */
  if (-1 == Tag) {
    return NULL;
  }

  return l;

}

STATIC
FIELD_T *
IgmpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack an IGMP packet

Arguments:

  Packet  - The packet should be unpacked
  Length  - The length of the packet

Returns:

  NULL if error occur
  The pointer to an FIELD_T type's object

--*/
{
  IGMP_HEADER *Header;
  UINT32      PayloadLen;

  if (Length < (sizeof (IGMP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
    return NULL;
  }

  Header        = (IGMP_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));

  IgmpType      = Header->IgmpType;
  MaxResTime    = Header->IgmpCode;
  IgmpChecksum  = ntohs (Header->IgmpSum);
  IgmpIp        = ntohl (Header->IgmpGroup);

  if (NULL != IgmpPayload.Payload) {
    free (IgmpPayload.Payload);
    IgmpPayload.Payload = NULL;
    IgmpPayload.Len     = 0;
  }

  PayloadLen = Length - sizeof (IGMP_HEADER) - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
  if (PayloadLen) {
    IgmpPayload.Payload = malloc (PayloadLen);
    memcpy (
      IgmpPayload.Payload,
      Packet + sizeof (IGMP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER),
      PayloadLen
      );
    IgmpPayload.Len = PayloadLen;
  }

  return IgmpField;
}
