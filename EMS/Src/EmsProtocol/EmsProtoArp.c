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
  
    EmsProtoArp.c
    
Abstract:

    Implementation for functions for protocol ARP

--*/

#include "EmsTypes.h"
#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsProtocols.h"
#include "EmsProtoArp.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsPktCreate.h"
#include "EmsUtilityString.h"

STATIC
libnet_t          *
ArpCreatePacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T           *
ArpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

STATIC UINT16     ArpHrdType;
STATIC UINT16     ArpProType;
STATIC UINT8      ArpHrdLen;
STATIC UINT8      ArpProLen;
STATIC UINT16     ArpOper;
STATIC UINT8      ArpSndHa[6];
STATIC UINT8      ArpSndPa[4];
STATIC UINT8      ArpTgtHa[6];
STATIC UINT8      ArpTgtPa[4];
STATIC PAYLOAD_T  ArpPayload;

STATIC BOOLEAN    HrdTypeOk;
STATIC BOOLEAN    ProTypeOk;
STATIC BOOLEAN    hrdLenOk;
STATIC BOOLEAN    ProLenOk;
STATIC BOOLEAN    OperOk;
STATIC BOOLEAN    SndHaOk;
STATIC BOOLEAN    SndPaOk;
STATIC BOOLEAN    TgtHaOk;
STATIC BOOLEAN    TgtPaOk;
STATIC BOOLEAN    PayloadOk;

//
// Address Resolution Protocol Entry
//
PROTOCOL_ENTRY_T  ArpProtocol = {
  "ARP",            // name
  ArpCreatePacket,  // Create packet routine
  ArpUnpackPacket,  // Unpacket routine
  NULL              // ARP TCL initialzation routine
};

FIELD_T           ArpField[] = {
  //
  // name         type       value          Mandatory  Isset
  //
  {
    "Arp_hrd",
    OCTET2,
    &ArpHrdType,
    FALSE,
    &HrdTypeOk
  },
  {
    "Arp_pro",
    OCTET2,
    &ArpProType,
    FALSE,
    &ProTypeOk
  },
  {
    "Arp_hln",
    OCTET1,
    &ArpHrdLen,
    FALSE,
    &hrdLenOk
  },
  {
    "Arp_pln",
    OCTET1,
    &ArpProLen,
    FALSE,
    &ProLenOk
  },
  {
    "Arp_op",
    OCTET2,
    &ArpOper,
    TRUE,
    &OperOk
  },
  {
    "Arp_sha",
    MACADDR,
    ArpSndHa,
    FALSE,
    &SndHaOk
  },
  {
    "Arp_spa",
    IPADDR,
    ArpSndPa,
    FALSE,
    &SndPaOk
  },
  {
    "Arp_tha",
    MACADDR,
    ArpTgtHa,
    FALSE,
    &TgtHaOk
  },
  {
    "Arp_tpa",
    IPADDR,
    ArpTgtPa,
    FALSE,
    &TgtPaOk
  },
  {
    "Arp_payload",
    PAYLOAD,
    &ArpPayload,
    FALSE,
    &PayloadOk
  },
  {
    NULL
  }
};

STATIC
libnet_t *
ArpCreatePacket (
  INT32   Argc,
  INT8    *Argv[]
  )
/*++

Routine Description:

  Create a ARP packet

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  Return the pointer to libnet_t type's object

--*/
{
  libnet_t      *l;
  libnet_ptag_t Tag;
  INT32         Index;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  EMS_STATUS    Status;
  UINT32        RealLocalIp;
  UINT32        RealRemoteIp;
  UINT8         Temp;
  UINT8         BCastMac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  //
  // Initialize all the local variables
  //
  for (Index = 0; ArpField[Index].Name; Index++) {
    *ArpField[Index].IsOk = FALSE;
    Status                = GetValueByName (&ArpField[Index], Argc, Argv);
    if (IsError (Status)) {
      return NULL;
    }
  }
  //
  // htonl
  //
  RealLocalIp   = htonl (LocalIp);
  RealRemoteIp  = htonl (RemoteIp);
  Temp          = ArpSndPa[0];
  ArpSndPa[0]   = ArpSndPa[3];
  ArpSndPa[3]   = Temp;
  Temp          = ArpSndPa[1];
  ArpSndPa[1]   = ArpSndPa[2];
  ArpSndPa[2]   = Temp;
  Temp          = ArpTgtPa[0];
  ArpTgtPa[0]   = ArpTgtPa[3];
  ArpTgtPa[3]   = Temp;
  Temp          = ArpTgtPa[1];
  ArpTgtPa[1]   = ArpTgtPa[2];
  ArpTgtPa[2]   = Temp;

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
  //
  // Build ARP packet
  //
  Tag = libnet_build_arp (
          HrdTypeOk ? ArpHrdType : DEF_HTYPE,           // hardware type
          ProTypeOk ? ArpProType : DEF_PTYPE,           // protocol type
          hrdLenOk ? ArpHrdLen : DEF_HLEN,              // hardware length
          ProLenOk ? ArpProLen : DEF_PLEN,              // protocol length
          ArpOper,                                      // operation
          SndHaOk ? ArpSndHa : LocalEthaddr,            // sender hardware address
          SndPaOk ? ArpSndPa : (UINT8 *) &RealLocalIp,  // sender protocol address
          TgtHaOk ? ArpTgtHa : RemoteEthaddr,           // target hardware address
          TgtPaOk ? ArpTgtPa : (UINT8 *) &RealRemoteIp, // target protocol address
          PayloadOk ? ArpPayload.Payload : NULL,        // payload
          PayloadOk ? ArpPayload.Len : 0,               // payload size
          l,              // libnet handle
          0               // libnet id
          );
  if (-1 == Tag) {
    return NULL;
  }

  Tag = libnet_build_ethernet (
          (ArpOper == 0x0001) ? BCastMac : RemoteEthaddr,  // if send a arp request packet use broadcast else use unicast
          LocalEthaddr,   // ehternet source
          ETHERTYPE_ARP,  // protocol type
          NULL,           // payload
          0,              // payload size
          l,              // libnet handle
          0               // libnet id
          );
  if (-1 == Tag) {
    return NULL;
  }

  return l;
}

STATIC
FIELD_T *
ArpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack a ARP packet

Arguments:

  Packet  - The pointer to packet
  Length  - The size of the packet

Returns:

  The pointer to the ArpField

--*/
{
  ARP_HEADER  *h;
  UINT32      PayloadLen;
  UINT8       Temp;

  if (Length < (sizeof (ARP_HEADER) + sizeof (ETH_HEADER))) {
    return NULL;
  }

  h           = (ARP_HEADER *) (Packet + sizeof (ETH_HEADER));

  ArpHrdType  = ntohs (h->HType);
  ArpProType  = ntohs (h->PType);
  ArpHrdLen   = h->HLen;
  ArpProLen   = h->PLen;
  ArpOper     = ntohs (h->Oper);
  memcpy (ArpSndHa, h->Sha, 6);
  memcpy (ArpSndPa, h->Spa, 4);
  memcpy (ArpTgtHa, h->Tha, 6);
  memcpy (ArpTgtPa, h->Tpa, 4);
  Temp        = ArpSndPa[0];
  ArpSndPa[0] = ArpSndPa[3];
  ArpSndPa[3] = Temp;
  Temp        = ArpSndPa[1];
  ArpSndPa[1] = ArpSndPa[2];
  ArpSndPa[2] = Temp;
  Temp        = ArpTgtPa[0];
  ArpTgtPa[0] = ArpTgtPa[3];
  ArpTgtPa[3] = Temp;
  Temp        = ArpTgtPa[1];
  ArpTgtPa[1] = ArpTgtPa[2];
  ArpTgtPa[2] = Temp;

  if (NULL != ArpPayload.Payload) {
    free (ArpPayload.Payload);
    ArpPayload.Payload  = NULL;
    ArpPayload.Len      = 0;
  }

  PayloadLen = Length - sizeof (ARP_HEADER) - sizeof (ETH_HEADER);
  if (PayloadLen) {
    ArpPayload.Payload = malloc (PayloadLen);
    memcpy (ArpPayload.Payload, Packet + sizeof (ARP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
    ArpPayload.Len = PayloadLen;
  }

  return ArpField;
}
