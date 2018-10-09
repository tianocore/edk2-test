/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
  IPv4.c

Abstract:

--*/

#include "IPv4.h"

BOOLEAN
IpIsBcast (
  EFI_IPv4_ADDRESS *DestAddr,
  EFI_IPv4_ADDRESS *Netmask
  )
/*++

Routine Description:

  Check address is broadcast address.

Arguments:

  DestAddr  - Destination address in net byte order.
  Netmask   - Network mask in net byte order.

Returns:

  TURE      - Is broadcast address.
  FALSE     - Not broadcast address.

--*/
{
  if (IP_IS_ALLONE (DestAddr)) {
    return TRUE;
  }

  if (Netmask) {
    if ((addr_cast (DestAddr)->Addr[0] &~(addr_cast (Netmask)->Addr[0])) ==
          (0xffffffff &~(addr_cast (Netmask)->Addr[0]))
          ) {
      return TRUE;
    }
  }

  return FALSE;
}

BOOLEAN
IpIsDirectBcast (
  EFI_IPv4_ADDRESS *DestAddr,
  EFI_IPv4_ADDRESS *Netmask
  )
/*++

Routine Description:

  Check address is direct broadcast address.

Arguments:

  DestAddr  - Destination address in net byte order.
  Netmask   - Network mask in net byte order.

Returns:

  TURE      - Is direct broadcast address.
  FALSE     - Not direct broadcast address.

--*/
{
  if ((addr_cast (DestAddr)->Addr[0] &~(addr_cast (Netmask)->Addr[0])) == (0xffffffff &~(addr_cast (Netmask)->Addr[0]))) {
    return TRUE;

  }

  return FALSE;
}

VOID
SetIpNetMask (
  IN EFI_IPv4_ADDRESS     *IpAddr,
  IN OUT EFI_IPv4_ADDRESS *NetMask
  )
/*++

Routine Description:

  Set network mask.

Arguments:

  IpAddr  - Ip address to be set.
  NetMask - Network mask.

Returns:

  None.

--*/
{
  if (IP_IS_CLASSC (IpAddr)) {
    addr_cast (NetMask)->Addr[0] = 0x00ffffff;
  } else if (IP_IS_CLASSB (IpAddr)) {
    addr_cast (NetMask)->Addr[0] = 0x0000ffff;
  } else if (IP_IS_CLASSA (IpAddr)) {
    addr_cast (NetMask)->Addr[0] = 0x000000ff;
  } else if (IP_IS_CLASSD (IpAddr)) {
    addr_cast (NetMask)->Addr[0] = 0xffffffff;
  } else {
    addr_cast (NetMask)->Addr[0] = 0xffffffff;
  }
}

UINT8
IpNetPartLen (
  EFI_IPv4_ADDRESS*Mask
  )
{
  UINT8   Len;
  UINT32  Addr;
  Len   = 0;
  Addr  = addr_cast (Mask)->Addr[0];

  while (Addr) {
    Len++;
    Addr >>= 1;
  }

  return Len;
}

BOOLEAN
IpIsSubnetMask (
  IN EFI_IPv4_ADDRESS *Mask
  )
{
  //
  // Addr must have following format, e.g., 0x00ffffff
  //
  UINT32  Addr;
  UINTN   Count;

  Addr  = ULADDR (Mask);
  Count = 0;

  Addr  = NTOHL (Addr);

  if (Addr == 0xffffffff) {
    return FALSE;

  }

  while ((Addr = (Addr << 1)) != 0) {
    Count++;
  }

  Addr = (0xffffffff >> Count);

  return (BOOLEAN) ((Addr | NTOHL (ULADDR (Mask))) == 0xffffffff);
}
