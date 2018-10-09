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
  
    EmsProtocols.c
    
Abstract:

    Implementation for protocol related common functions

--*/

#include <EmsUtilityString.h>

#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsProtoIgmp.h"
#include "EmsProtoArp.h"
#include "EmsProtoUdp.h"
#include "EmsProtoIcmp.h"
#include "EmsProtoDhcp.h"
#include "EmsProtoTcp.h"
#include "EmsProtoIPv6.h"

PROTOCOL_ENTRY_T  *Protocols[] = {
  &EthProtocol,
  &IpProtocol,
  &IgmpProtocol,
  &ArpProtocol,
  &UdpProtocol,
  &IcmpProtocol,
  &DhcpProtocol,
  &TcpProtocol,
  &IPv6Protocol,
  NULL
};

PROTOCOL_ENTRY_T *
GetProtocolByName (
  IN INT8 *Name
  )
/*++

Routine Description:

  Get the protocol entry by specified name

Arguments:

  Name  - Protocl name

Returns:

  The protocol entry or NULL.

--*/
{
  UINT32  Index;

  for (Index = 0; Protocols[Index]; Index++) {
    if (0 == strcmp_i (Protocols[Index]->Name, Name)) {
      return Protocols[Index];
    }
  }

  return NULL;
}

VOID_P
EmsFieldDump (
  IN OUT  INT8     *Buff,
  IN      FIELD_T  *Fields
  )
/*++

Routine Description:

  Dump the field information into a specified buffer.

Arguments:

  Buff    - The buffer for the fields
  Fields  - The pointer to the fields

Returns:

  None

--*/
{
  UINT32  Index;
  INT8    Log[100];
  Buff[0] = '\0';
  for (Index = 0; Fields[Index].Name; Index++) {
    strcat (Buff, Fields[Index].Name);
    switch (Fields[Index].Type) {
    case OCTET1:
      sprintf (Log, "=0x%02x ", *(UINT8 *) Fields[Index].Value);
      break;

    case OCTET2:
      sprintf (Log, "=0x%04x ", *(UINT16 *) Fields[Index].Value);
      break;

    case OCTET4:
      sprintf (Log, "=0x%08x ", *(UINT32 *) Fields[Index].Value);
      break;

    case IPADDR:
      Log[0] = '=';
      Ipv4ToAsciiString (&Log[1], *(UINT32 *) Fields[Index].Value);
      break;

	case IPV6ADDR:
      Log[0] = '=';
      Ipv6ToAsciiString (&Log[1], (EMS_IPV6_ADDR*)Fields[Index].Value);
      break;  

    case MACADDR:
      Log[0] = '=';
      MacToAsciiString (&Log[1], ((UINT8 *) Fields[Index].Value));
      break;

    case STRING:
      Log[0] = '=';
      sprintf (Log, "=%s ", *((UINT8 **) Fields[Index].Value));
      break;

    default:
      sprintf (Log, " ");
      break;
    }

    strcat (Buff, Log);
  }

  return ;
}
