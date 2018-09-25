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

  BaseFunc.h

Abstract:
  based Function to read and write Pci configuration.

--*/

#include "Common.h"
#include <UEFI/Protocol/PciIo.h>

/*
 *  Read a byte from configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @return a byte read out from the configuration space.
 */
UINT8
ReadConfigByte (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  )
{
  UINT64      FuncAddress;
  UINT8       Data;

  FuncAddress = 0x0;
  Data        = 0x0;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;

  RootBridgeIo->Pci.Read (RootBridgeIo, EfiPciIoWidthUint8, FuncAddress, 1, &Data);
  return Data;
}


/*
 *  Read a word from configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @return a word read out from the configuration space.
 */
UINT16
ReadConfigWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  )
{
  UINT64      FuncAddress;
  UINT16      Data;

  FuncAddress = 0x0;
  Data        = 0x0;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;

  RootBridgeIo->Pci.Read (RootBridgeIo, EfiPciIoWidthUint16, FuncAddress, 1, &Data);
  return Data;
}


/*
 *  Read Double word from configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @return a Dword read out from the configuration space.
 */
UINT32
ReadConfigDWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  )
{
  UINT64      FuncAddress;
  UINT32      Data;

  FuncAddress = 0x0;
  Data        = 0x0;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;

  RootBridgeIo->Pci.Read (RootBridgeIo, EfiPciIoWidthUint32, FuncAddress, 1, &Data);
  return Data;
}


/*
 *  write a byte into configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @param Value the value to be written.
 */
VOID
WriteConfigByte (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT8                             Value
  )
{
  UINT64                        FuncAddress;

  FuncAddress = 0x00;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;
  RootBridgeIo->Pci.Write (RootBridgeIo, EfiPciIoWidthUint8, FuncAddress, 1, &Value);
}


/*
 *  write a word into configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @param Value the value to be written.
 */
VOID
WriteConfigWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT16                             Value
  )
{
  UINT64                        FuncAddress;

  FuncAddress = 0x00;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;
  RootBridgeIo->Pci.Write (RootBridgeIo, EfiPciIoWidthUint16, FuncAddress, 1, &Value);
}

/*
 *  write double word into configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @param Value the value to be written.
 */
VOID
WriteConfigDWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT32                            Value
  )
{
  UINT64                        FuncAddress;

  FuncAddress = 0x00;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;
  RootBridgeIo->Pci.Write (RootBridgeIo, EfiPciIoWidthUint32, FuncAddress, 1, &Value);
}
