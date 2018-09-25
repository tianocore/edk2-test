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
  
    EmsProtoIcmp.c
    
Abstract:

    Implementation for functions for protocol ICMP

--*/

#include "EmsTypes.h"
#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsProtocols.h"
#include "EmsProtoIcmp.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsPktCreate.h"
#include "EmsUtilityString.h"

#define DEF_CHKSUM  0
#define DEF_ID      0
#define DEF_SEQ     0

STATIC
libnet_t          *
IcmpCreatepacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T           *
IcmpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

STATIC UINT8      IcmpType;
STATIC UINT8      IcmpCode;
STATIC UINT16     IcmpChksum;
STATIC UINT16     IcmpId;
STATIC UINT16     IcmpSeq;
STATIC UINT32     IcmpMask;
STATIC UINT16     IcmpOrigLen;
STATIC UINT8      IcmpOrigTos;
STATIC UINT16     IcmpOrigId;
STATIC UINT16     IcmpOrigFrag;
STATIC UINT8      IcmpOrigTtl;
STATIC UINT8      IcmpOrigProt;
STATIC UINT16     IcmpOrigCheck;
STATIC UINT32     IcmpOrigSrc;
STATIC UINT32     IcmpOrigDst;
STATIC UINT32     IcmpGateway;
STATIC n_time     IcmpOTime;
STATIC n_time     IcmpRTime;
STATIC n_time     IcmpTTime;
STATIC PAYLOAD_T  IcmpPayload;

STATIC BOOLEAN    TypeOk;
STATIC BOOLEAN    CodeOk;
STATIC BOOLEAN    ChksumOk;
STATIC BOOLEAN    IdOk;
STATIC BOOLEAN    SeqOk;
STATIC BOOLEAN    MaskOk;
STATIC BOOLEAN    OrigLenOk;
STATIC BOOLEAN    OrigTosOk;
STATIC BOOLEAN    OrigIdOk;
STATIC BOOLEAN    OrigFragOk;
STATIC BOOLEAN    OrigTtlOk;
STATIC BOOLEAN    OrigProtOk;
STATIC BOOLEAN    OrigCheckOk;
STATIC BOOLEAN    OrigSrcOk;
STATIC BOOLEAN    OrigDstOk;
STATIC BOOLEAN    GatewayOk;
STATIC BOOLEAN    OTimeOk;
STATIC BOOLEAN    RTimeOk;
STATIC BOOLEAN    TTimeOk;
STATIC BOOLEAN    PayloadOk;

//
// Internet Control Message Protocol Entry
//
PROTOCOL_ENTRY_T  IcmpProtocol = {
  "ICMP",           // name
  IcmpCreatepacket, // Create packet routine
  IcmpUnpackPacket, // Unpacket routine
  NULL              // ICMP TCL initialzation routine
};

FIELD_T           IcmpEchoField[] = {
  //
  // name            type       value             Mandatory  Isset
  //
  {
    "Icmp_type",
    OCTET1,
    &IcmpType,
    TRUE,
    &TypeOk
  },
  {
    "Icmp_code",
    OCTET1,
    &IcmpCode,
    TRUE,
    &CodeOk
  },
  {
    "Icmp_chksum",
    OCTET2,
    &IcmpChksum,
    FALSE,
    &ChksumOk
  },
  {
    "Icmp_id",
    OCTET2,
    &IcmpId,
    FALSE,
    &IdOk
  },
  {
    "Icmp_seq",
    OCTET2,
    &IcmpSeq,
    FALSE,
    &SeqOk
  },
  {
    "Icmp_payload",
    PAYLOAD,
    &IcmpPayload,
    FALSE,
    &PayloadOk
  },
  {
    NULL
  }
};

FIELD_T           IcmpAddressMaskField[] = {
  //
  // name            type       value             Mandatory  Isset
  //
  {
    "Icmp_type",
    OCTET1,
    &IcmpType,
    TRUE,
    &TypeOk
  },
  {
    "Icmp_code",
    OCTET1,
    &IcmpCode,
    TRUE,
    &CodeOk
  },
  {
    "Icmp_chksum",
    OCTET2,
    &IcmpChksum,
    FALSE,
    &ChksumOk
  },
  {
    "Icmp_id",
    OCTET2,
    &IcmpId,
    FALSE,
    &IdOk
  },
  {
    "Icmp_seq",
    OCTET2,
    &IcmpSeq,
    FALSE,
    &SeqOk
  },
  {
    "Icmp_mask",
    IPADDR,
    &IcmpMask,
    TRUE,
    &MaskOk
  },
  {
    "Icmp_payload",
    PAYLOAD,
    &IcmpPayload,
    FALSE,
    &PayloadOk
  },
  {
    NULL
  }
};

FIELD_T           IcmpDestUnreachField[] = {
  //
  // name            type       value             Mandatory  Isset
  //
  {
    "Icmp_type",
    OCTET1,
    &IcmpType,
    TRUE,
    &TypeOk
  },
  {
    "Icmp_code",
    OCTET1,
    &IcmpCode,
    TRUE,
    &CodeOk
  },
  {
    "Icmp_chksum",
    OCTET2,
    &IcmpChksum,
    FALSE,
    &ChksumOk
  },
  {
    "Icmp_orig_len",
    OCTET2,
    &IcmpOrigLen,
    TRUE,
    &OrigLenOk
  },
  {
    "Icmp_orig_tos",
    OCTET1,
    &IcmpOrigTos,
    TRUE,
    &OrigTosOk
  },
  {
    "Icmp_orig_id",
    OCTET2,
    &IcmpOrigId,
    TRUE,
    &OrigIdOk
  },
  {
    "Icmp_orig_frag",
    OCTET2,
    &IcmpOrigFrag,
    TRUE,
    &OrigFragOk
  },
  {
    "Icmp_orig_ttl",
    OCTET1,
    &IcmpOrigTtl,
    TRUE,
    &OrigTtlOk
  },
  {
    "Icmp_orig_prot",
    OCTET1,
    &IcmpOrigProt,
    TRUE,
    &OrigProtOk
  },
  {
    "Icmp_orig_check",
    OCTET2,
    &IcmpOrigCheck,
    TRUE,
    &OrigCheckOk
  },
  {
    "Icmp_orig_src",
    IPADDR,
    &IcmpOrigSrc,
    TRUE,
    &OrigSrcOk
  },
  {
    "Icmp_orig_dst",
    IPADDR,
    &IcmpOrigDst,
    TRUE,
    &OrigDstOk
  },
  {
    "Icmp_payload",
    PAYLOAD,
    &IcmpPayload,
    FALSE,
    &PayloadOk
  },
  {
    NULL
  }
};

FIELD_T           IcmpRedirectField[] = {
  //
  // name            type       value             Mandatory  Isset
  //
  {
    "Icmp_type",
    OCTET1,
    &IcmpType,
    TRUE,
    &TypeOk
  },
  {
    "Icmp_code",
    OCTET1,
    &IcmpCode,
    TRUE,
    &CodeOk
  },
  {
    "Icmp_chksum",
    OCTET2,
    &IcmpChksum,
    FALSE,
    &ChksumOk
  },
  {
    "Icmp_gateway",
    IPADDR,
    &IcmpGateway,
    TRUE,
    &GatewayOk
  },
  {
    "Icmp_orig_len",
    OCTET2,
    &IcmpOrigLen,
    TRUE,
    &OrigLenOk
  },
  {
    "Icmp_orig_tos",
    OCTET1,
    &IcmpOrigTos,
    TRUE,
    &OrigTosOk
  },
  {
    "Icmp_orig_id",
    OCTET2,
    &IcmpOrigId,
    TRUE,
    &OrigIdOk
  },
  {
    "Icmp_orig_frag",
    OCTET2,
    &IcmpOrigFrag,
    TRUE,
    &OrigFragOk
  },
  {
    "Icmp_orig_ttl",
    OCTET1,
    &IcmpOrigTtl,
    TRUE,
    &OrigTtlOk
  },
  {
    "Icmp_orig_prot",
    OCTET1,
    &IcmpOrigProt,
    TRUE,
    &OrigProtOk
  },
  {
    "Icmp_orig_check",
    OCTET2,
    &IcmpOrigCheck,
    TRUE,
    &OrigCheckOk
  },
  {
    "Icmp_orig_src",
    IPADDR,
    &IcmpOrigSrc,
    TRUE,
    &OrigSrcOk
  },
  {
    "Icmp_orig_dst",
    IPADDR,
    &IcmpOrigDst,
    TRUE,
    &OrigDstOk
  },
  {
    "Icmp_payload",
    PAYLOAD,
    &IcmpPayload,
    FALSE,
    &PayloadOk
  },
  {
    NULL
  }
};

FIELD_T           IcmpTimeExceededField[] = {
  //
  // name            type       value             Mandatory  Isset
  //
  {
    "Icmp_type",
    OCTET1,
    &IcmpType,
    TRUE,
    &TypeOk
  },
  {
    "Icmp_code",
    OCTET1,
    &IcmpCode,
    TRUE,
    &CodeOk
  },
  {
    "Icmp_chksum",
    OCTET2,
    &IcmpChksum,
    FALSE,
    &ChksumOk
  },
  {
    "Icmp_orig_len",
    OCTET2,
    &IcmpOrigLen,
    TRUE,
    &OrigLenOk
  },
  {
    "Icmp_orig_tos",
    OCTET1,
    &IcmpOrigTos,
    TRUE,
    &OrigTosOk
  },
  {
    "Icmp_orig_id",
    OCTET2,
    &IcmpOrigId,
    TRUE,
    &OrigIdOk
  },
  {
    "Icmp_orig_frag",
    OCTET2,
    &IcmpOrigFrag,
    TRUE,
    &OrigFragOk
  },
  {
    "Icmp_orig_ttl",
    OCTET1,
    &IcmpOrigTtl,
    TRUE,
    &OrigTtlOk
  },
  {
    "Icmp_orig_prot",
    OCTET1,
    &IcmpOrigProt,
    TRUE,
    &OrigProtOk
  },
  {
    "Icmp_orig_check",
    OCTET2,
    &IcmpOrigCheck,
    TRUE,
    &OrigCheckOk
  },
  {
    "Icmp_orig_src",
    IPADDR,
    &IcmpOrigSrc,
    TRUE,
    &OrigSrcOk
  },
  {
    "Icmp_orig_dst",
    IPADDR,
    &IcmpOrigDst,
    TRUE,
    &OrigDstOk
  },
  {
    "Icmp_payload",
    PAYLOAD,
    &IcmpPayload,
    FALSE,
    &PayloadOk
  },
  {
    NULL
  }
};

FIELD_T           IcmpTimestampField[] = {
  //
  // name            type       value             Mandatory  Isset
  //
  {
    "Icmp_type",
    OCTET1,
    &IcmpType,
    TRUE,
    &TypeOk
  },
  {
    "Icmp_code",
    OCTET1,
    &IcmpCode,
    TRUE,
    &CodeOk
  },
  {
    "Icmp_chksum",
    OCTET2,
    &IcmpChksum,
    FALSE,
    &ChksumOk
  },
  {
    "Icmp_id",
    OCTET2,
    &IcmpId,
    FALSE,
    &IdOk
  },
  {
    "Icmp_seq",
    OCTET2,
    &IcmpSeq,
    FALSE,
    &SeqOk
  },
  {
    "Icmp_otime",
    OCTET4,
    &IcmpOTime,
    TRUE,
    &OTimeOk
  },
  {
    "Icmp_rtime",
    OCTET4,
    &IcmpRTime,
    TRUE,
    &RTimeOk
  },
  {
    "Icmp_ttime",
    OCTET4,
    &IcmpTTime,
    TRUE,
    &TTimeOk
  },
  {
    "Icmp_payload",
    PAYLOAD,
    &IcmpPayload,
    FALSE,
    &PayloadOk
  },
  {
    NULL
  }
};

STATIC
libnet_t *
IcmpCreatepacket (
  INT32   Argc,
  INT8    *Argv[]
  )
/*++

Routine Description:

  Create an ICMP packet

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  The pointer to the libnet

--*/
{
  libnet_t      *l;
  libnet_ptag_t Tag;
  INT32         Index;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  EMS_STATUS    Status;
  UINT32        Len;
  FIELD_T       *IcmpField;

  //
  // Initialize all the local variables
  //
  Status = GetValueByName (&IcmpEchoField[0], Argc, Argv);
  if (IsError (Status)) {
    return NULL;
  }

  switch (IcmpType) {
  case ICMP_TYPE_ECHO_REQUEST:
  case ICMP_TYPE_ECHO_REPLY:
    IcmpField = IcmpEchoField;
    break;

  case ICMP_TYPE_ADDRESS_MASK_REQUEST:
  case ICMP_TYPE_ADDRESS_MASK_REPLY:
    IcmpField = IcmpAddressMaskField;
    break;

  case ICMP_TYPE_DEST_UNREACHABLE:
    IcmpField = IcmpDestUnreachField;
    break;

  case ICMP_TYPE_REDIRECT:
    IcmpField = IcmpRedirectField;
    break;

  case ICMP_TYPE_TIME_EXCEEDED:
    IcmpField = IcmpTimeExceededField;
    break;

  case ICMP_TYPE_TIMESTAMP_REQUEST:
  case ICMP_TYPE_TIMESTAMP_REPLY:
    IcmpField = IcmpTimestampField;
    break;

  default:
    return NULL;
  }

  for (Index = 0; IcmpField[Index].Name; Index++) {
    *IcmpField[Index].IsOk  = FALSE;
    Status                  = GetValueByName (&IcmpField[Index], Argc, Argv);
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

  switch (IcmpType) {
  //
  // Build ARP packet
  //
  case ICMP_TYPE_ECHO_REQUEST:
  case ICMP_TYPE_ECHO_REPLY:
    Tag = libnet_build_icmpv4_echo (
            IcmpType,                                   // ICMP type
            IcmpCode,                                   // ICMP code
            ChksumOk ? htons (IcmpChksum) : DEF_CHKSUM, // ICMP checksum
            IdOk ? htons (IcmpId) : DEF_ID,             // ICMP ECHO identifier
            SeqOk ? htons (IcmpSeq) : DEF_SEQ,          // ICMP ECHO sequence number
            PayloadOk ? IcmpPayload.Payload : NULL,     // payload
            PayloadOk ? IcmpPayload.Len : 0,            // payload size
            l,                                          // libnet handle
            0         // libnet id
            );
    break;

  case ICMP_TYPE_ADDRESS_MASK_REQUEST:
  case ICMP_TYPE_ADDRESS_MASK_REPLY:
    Tag = libnet_build_icmpv4_mask (
            IcmpType, // ICMP type
            IcmpCode, // ICMP code
            ChksumOk ? htons (IcmpChksum) : DEF_CHKSUM, // ICMP checksum
            IdOk ? IcmpId : DEF_ID,                     // ICMP MASK identifier
            SeqOk ? IcmpSeq : DEF_SEQ,                  // ICMP MASK sequence number
            IcmpMask,                                   // ICMP MASK mask
            PayloadOk ? IcmpPayload.Payload : NULL,     // payload
            PayloadOk ? IcmpPayload.Len : 0,            // payload size
            l,                                          // libnet handle
            0         // libnet id
            );
    break;

  case ICMP_TYPE_DEST_UNREACHABLE:
    Tag = libnet_build_icmpv4_unreach (
            IcmpType, // ICMP type
            IcmpCode, // ICMP code
            ChksumOk ? htons (IcmpChksum) : DEF_CHKSUM, // ICMP checksum
            //IcmpOrigLen, 
            // ICMP UNREACH original length 
            // IcmpOrigTos, 
            // ICMP UNREACH original type of service 
            // IcmpOrigId,
            // ICMP UNREACH original identification 
            // IcmpOrigFrag,
            // ICMP UNREACH original fragment 
            // IcmpOrigTtl, 
            // ICMP UNREACH original time to live 
            // IcmpOrigProt, 
            // ICMP UNREACH original protocol 
            // htons(IcmpOrigCheck),
            // ICMP UNREACH original check 
            // htonl(IcmpOrigSrc),
            // ICMP UNREACH original source 
            // htonl(IcmpOrigDst),
            // ICMP UNREACH original destination
            PayloadOk ? IcmpPayload.Payload : NULL,     // payload
            PayloadOk ? IcmpPayload.Len : 0,            // payload size
            l,                                          // libnet handle
            0                                           // libnet id
            );
    break;

  case ICMP_TYPE_REDIRECT:
    Tag = libnet_build_icmpv4_redirect (
            IcmpType,                                   // ICMP type
            IcmpCode,                                   // ICMP code
            ChksumOk ? htons (IcmpChksum) : DEF_CHKSUM, // ICMP checksum
            htonl (IcmpGateway),                        // ICMP REDIRECT gateway
            //IcmpOrigLen,
            //ICMP REDIRECT original length 
            //IcmpOrigTos,
            //ICMP REDIRECT original type of service 
            //IcmpOrigId,
            //ICMP REDIRECT original identification 
            //IcmpOrigFrag, 
            //ICMP REDIRECT original fragment 
            //IcmpOrigTtl,
            //ICMP REDIRECT original time to live 
            //IcmpOrigProt
            //ICMP REDIRECT original protocol 
            //htons(IcmpOrigCheck),
            //ICMP REDIRECT original check 
            //htonl(IcmpOrigSrc)
            //ICMP REDIRECT original source 
            //htonl(IcmpOrigDst)
            //ICMP REDIRECT original destination
            PayloadOk ? IcmpPayload.Payload : NULL,     // payload
            PayloadOk ? IcmpPayload.Len : 0,            // payload size
            l,                                          // libnet handle
            0                                           // libnet id
            );
    break;

  case ICMP_TYPE_TIME_EXCEEDED:
    Tag = libnet_build_icmpv4_timeexceed (
            IcmpType,                                   // ICMP type
            IcmpCode,                                   // ICMP code
            ChksumOk ? htons (IcmpChksum) : DEF_CHKSUM, // ICMP checksum
            //IcmpOrigLen
            //ICMP TIMEEXCEED original length 
            //IcmpOrigTos
            //ICMP TIMEEXCEED original type of service 
            //IcmpOrigId
            //ICMP TIMEEXCEED original identification 
            //IcmpOrigFrag
            //ICMP TIMEEXCEED original fragment 
            //IcmpOrigTtl
            //ICMP TIMEEXCEED original time to live 
            //IcmpOrigProt
            //ICMP TIMEEXCEED original protocol 
            //htons(IcmpOrigCheck)
            //ICMP TIMEEXCEED original check 
            //htonl(IcmpOrigSrc)
            //ICMP TIMEEXCEED original source 
            //htonl(IcmpOrigDst)
            //ICMP TIMEEXCEED original destination
            PayloadOk ? IcmpPayload.Payload : NULL,     // payload
            PayloadOk ? IcmpPayload.Len : 0,            // payload size
            l,                                          // libnet handle
            0                                           // libnet id
            );
    break;

  case ICMP_TYPE_TIMESTAMP_REQUEST:
  case ICMP_TYPE_TIMESTAMP_REPLY:
    Tag = libnet_build_icmpv4_timestamp (
            IcmpType,                                   // ICMP type
            IcmpCode,                                   // ICMP code
            ChksumOk ? htons (IcmpChksum) : DEF_CHKSUM, // ICMP checksum
            IdOk ? IcmpId : DEF_ID,                     // ICMP TIMESTAMP identifier
            SeqOk ? IcmpSeq : DEF_SEQ,                  // ICMP TIMESTAMP sequence number
            IcmpOTime,                                  // ICMP TIMESTAMP originate timestamp
            IcmpRTime,                                  // ICMP TIMESTAMP receive timestamp
            IcmpTTime,                                  // ICMP TIMESTAMP transmit timestamp
            PayloadOk ? IcmpPayload.Payload : NULL,     // payload
            PayloadOk ? IcmpPayload.Len : 0,            // payload size
            l,                                          // libnet handle
            0 // libnet id
            );
    break;

  default:
    Tag = -1;
    break;
  }

  if (-1 == Tag) {
    return NULL;
  }

  Len = LIBNET_IPV4_H;
  switch (IcmpType) {
  case ICMP_TYPE_ECHO_REQUEST:
  case ICMP_TYPE_ECHO_REPLY:
    //
    // len += sizeof(icmp_echo_header);
    //
    Len += 8;
    break;

  case ICMP_TYPE_ADDRESS_MASK_REQUEST:
  case ICMP_TYPE_ADDRESS_MASK_REPLY:
    //
    // len += sizeof(icmp_address_mask_header);
    //
    Len += 12;
    break;

  case ICMP_TYPE_DEST_UNREACHABLE:
    //
    // len += sizeof(icmp_dest_unreach_header);
    //
    Len += 8;
    break;

  case ICMP_TYPE_REDIRECT:
    //
    // len += sizeof(icmp_redirect_header);
    //
    Len += 8;
    break;

  case ICMP_TYPE_TIME_EXCEEDED:
    Len += sizeof (ICMP_TIME_EXCEEDED_HEADER);
    break;

  case ICMP_TYPE_TIMESTAMP_REQUEST:
  case ICMP_TYPE_TIMESTAMP_REPLY:
    //
    // len += sizeof(icmp_timestamp_header);
    //
    Len += 20;
    break;

  default:
    break;
  }

  Len += PayloadOk ? IcmpPayload.Len : 0;

  Tag = libnet_build_ipv4 (
          Len,              // length
          0,                // TOS
          GetIpId (),       // IP ID
          0,                // IP Frag
          1,                // TTL
          IPPROTO_ICMP,     // protocol
          0,                // checksum
          htonl (LocalIp),  // source
          htonl (RemoteIp), // destination
          NULL,             // payload
          0,                // payload size
          l,                // libnet handle
          0                 // libnet id
          );
  if (-1 == Tag) {
    return NULL;
  }

  Tag = libnet_build_ethernet (
          RemoteEthaddr,    // ethernet destination
          LocalEthaddr,     // ehternet source
          ETHERTYPE_IP,     // protocol type
          NULL,             // payload
          0,                // payload size
          l,                // libnet handle
          0                 // libnet id
          );
  if (-1 == Tag) {
    return NULL;
  }

  return l;
}

STATIC
FIELD_T *
IcmpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack an ICMP packet

Arguments:

  Packet  - The packet should be unpacked
  Length  - The size of the packet

Returns:

  NULL or The pointer to the FIELD_T

--*/
{
  UINT8                     *Type;
  UINT32                    PayloadLen;
  UINT32                    IcmpHeaderLen;
  ICMP_ECHO_HEADER          *EchoHdr;
  ICMP_ADDRESS_MASK_HEADER  *AddrMaskHdr;
  ICMP_DEST_UNREACH_HEADER  *DestUnreachHdr;
  ICMP_REDIRECT_HEADER      *RedirectHdr;
  ICMP_TIME_EXCEEDED_HEADER *TimeExceedHdr;
  ICMP_TIMESTAMP_HEADER     *TimestampHdr;

  if (Length < (sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
    return NULL;
  }

  if (NULL != IcmpPayload.Payload) {
    free (IcmpPayload.Payload);
    IcmpPayload.Payload = NULL;
    IcmpPayload.Len     = 0;
  }

  Type      = (UINT8 *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
  IcmpType  = *Type;

  switch (IcmpType) {
  case ICMP_TYPE_ECHO_REQUEST:
  case ICMP_TYPE_ECHO_REPLY:
    IcmpHeaderLen = sizeof (ICMP_ECHO_HEADER);
    EchoHdr       = (ICMP_ECHO_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
    if (Length < (IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
      return NULL;
    }

    IcmpType    = EchoHdr->Type;
    IcmpCode    = EchoHdr->Code;
    IcmpChksum  = ntohs (EchoHdr->ChhkSum);
    IcmpId      = ntohs (EchoHdr->Id);
    IcmpSeq     = ntohs (EchoHdr->Seq);

    PayloadLen  = Length - IcmpHeaderLen - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
    if (PayloadLen) {
      IcmpPayload.Payload = malloc (PayloadLen);
      memcpy (IcmpPayload.Payload, Packet + IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
      IcmpPayload.Len = PayloadLen;
    }

    return IcmpEchoField;

  case ICMP_TYPE_ADDRESS_MASK_REQUEST:
  case ICMP_TYPE_ADDRESS_MASK_REPLY:
    IcmpHeaderLen = sizeof (ICMP_ADDRESS_MASK_HEADER);
    AddrMaskHdr   = (ICMP_ADDRESS_MASK_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
    if (Length < (IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
      return NULL;
    }

    IcmpType    = AddrMaskHdr->Type;
    IcmpCode    = AddrMaskHdr->Code;
    IcmpChksum  = ntohs (AddrMaskHdr->ChhkSum);
    IcmpId      = ntohs (AddrMaskHdr->Id);
    IcmpSeq     = ntohs (AddrMaskHdr->Seq);
    IcmpMask    = ntohl (AddrMaskHdr->Mask);

    PayloadLen  = Length - IcmpHeaderLen - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
    if (PayloadLen) {
      IcmpPayload.Payload = malloc (PayloadLen);
      memcpy (IcmpPayload.Payload, Packet + IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
      IcmpPayload.Len = PayloadLen;
    }

    return IcmpAddressMaskField;

  case ICMP_TYPE_DEST_UNREACHABLE:
    IcmpHeaderLen   = sizeof (ICMP_DEST_UNREACH_HEADER);
    DestUnreachHdr  = (ICMP_DEST_UNREACH_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
    if (Length < (IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
      return NULL;
    }

    IcmpType      = DestUnreachHdr->Type;
    IcmpCode      = DestUnreachHdr->Code;
    IcmpChksum    = ntohs (DestUnreachHdr->ChhkSum);
    IcmpOrigLen   = ntohs (DestUnreachHdr->OrigLen);
    IcmpOrigTos   = DestUnreachHdr->OrigTos;
    IcmpOrigId    = ntohs (DestUnreachHdr->OrigId);
    IcmpOrigFrag  = ntohs (DestUnreachHdr->OrigFrag);
    IcmpOrigTtl   = DestUnreachHdr->OrigTtl;
    IcmpOrigProt  = DestUnreachHdr->OrigProt;
    IcmpOrigCheck = ntohs (DestUnreachHdr->OrigCheck);
    IcmpOrigSrc   = ntohl (DestUnreachHdr->OrigSrc);
    IcmpOrigDst   = ntohl (DestUnreachHdr->OrigDst);

    PayloadLen    = Length - IcmpHeaderLen - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
    if (PayloadLen) {
      IcmpPayload.Payload = malloc (PayloadLen);
      memcpy (IcmpPayload.Payload, Packet + IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
      IcmpPayload.Len = PayloadLen;
    }

    return IcmpDestUnreachField;

  case ICMP_TYPE_REDIRECT:
    IcmpHeaderLen = sizeof (ICMP_REDIRECT_HEADER);
    RedirectHdr   = (ICMP_REDIRECT_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
    if (Length < (IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
      return NULL;
    }

    IcmpType      = RedirectHdr->Type;
    IcmpCode      = RedirectHdr->Code;
    IcmpChksum    = ntohs (RedirectHdr->ChhkSum);
    IcmpGateway   = ntohl (RedirectHdr->GateWay);
    IcmpOrigLen   = ntohs (RedirectHdr->OrigLen);
    IcmpOrigTos   = RedirectHdr->OrigTos;
    IcmpOrigId    = ntohs (RedirectHdr->OrigId);
    IcmpOrigFrag  = ntohs (RedirectHdr->OrigFrag);
    IcmpOrigTtl   = RedirectHdr->OrigTtl;
    IcmpOrigProt  = RedirectHdr->OrigProt;
    IcmpOrigCheck = ntohs (RedirectHdr->OrigCheck);
    IcmpOrigSrc   = ntohl (RedirectHdr->OrigSrc);
    IcmpOrigDst   = ntohl (RedirectHdr->OrigDst);

    PayloadLen    = Length - IcmpHeaderLen - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
    if (PayloadLen) {
      IcmpPayload.Payload = malloc (PayloadLen);
      memcpy (IcmpPayload.Payload, Packet + IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
      IcmpPayload.Len = PayloadLen;
    }

    return IcmpRedirectField;

  case ICMP_TYPE_TIME_EXCEEDED:
    IcmpHeaderLen = sizeof (ICMP_TIME_EXCEEDED_HEADER);
    TimeExceedHdr = (ICMP_TIME_EXCEEDED_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
    if (Length < (IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
      return NULL;
    }

    IcmpType      = TimeExceedHdr->Type;
    IcmpCode      = TimeExceedHdr->Code;
    IcmpChksum    = ntohs (TimeExceedHdr->ChhkSum);
    IcmpOrigLen   = ntohs (TimeExceedHdr->OrigLen);
    IcmpOrigTos   = TimeExceedHdr->OrigTos;
    IcmpOrigId    = ntohs (TimeExceedHdr->OrigId);
    IcmpOrigFrag  = ntohs (TimeExceedHdr->OrigFrag);
    IcmpOrigTtl   = TimeExceedHdr->OrigTtl;
    IcmpOrigProt  = TimeExceedHdr->OrigProt;
    IcmpOrigCheck = ntohs (TimeExceedHdr->OrigCheck);
    IcmpOrigSrc   = ntohl (TimeExceedHdr->OrigSrc);
    IcmpOrigDst   = ntohl (TimeExceedHdr->OrigDst);

    PayloadLen    = Length - IcmpHeaderLen - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
    if (PayloadLen) {
      IcmpPayload.Payload = malloc (PayloadLen);
      memcpy (IcmpPayload.Payload, Packet + IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
      IcmpPayload.Len = PayloadLen;
    }

    return IcmpTimeExceededField;

  case ICMP_TYPE_TIMESTAMP_REQUEST:
  case ICMP_TYPE_TIMESTAMP_REPLY:
    IcmpHeaderLen = sizeof (ICMP_TIMESTAMP_HEADER);
    TimestampHdr  = (ICMP_TIMESTAMP_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
    if (Length < (IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
      return NULL;
    }

    IcmpType    = TimestampHdr->Type;
    IcmpCode    = TimestampHdr->Code;
    IcmpChksum  = ntohs (TimestampHdr->ChhkSum);
    IcmpId      = ntohs (TimestampHdr->Id);
    IcmpSeq     = ntohs (TimestampHdr->Seq);
    IcmpOTime   = ntohl (TimestampHdr->OTime);
    IcmpRTime   = ntohl (TimestampHdr->RTime);
    IcmpTTime   = ntohl (TimestampHdr->TTime);

    PayloadLen  = Length - IcmpHeaderLen - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
    if (PayloadLen) {
      IcmpPayload.Payload = malloc (PayloadLen);
      memcpy (IcmpPayload.Payload, Packet + IcmpHeaderLen + sizeof (IP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
      IcmpPayload.Len = PayloadLen;
    }

    return IcmpTimestampField;

  default:
    return NULL;
  }
}
