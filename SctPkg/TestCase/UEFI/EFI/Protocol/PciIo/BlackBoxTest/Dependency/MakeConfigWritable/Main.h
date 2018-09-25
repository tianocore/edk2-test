/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Main.h

Abstract:

  main header file for make pci configuraiton space writable

--*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include "SctLib.h"

//
//entry point.
//

EFI_STATUS
EFIAPI
MakeConfigWritableEntryPoint (
  IN EFI_HANDLE                      ImageHandle,
  IN EFI_SYSTEM_TABLE                *SystemTable
  );

//
//function in MakeConfigWritable.c
//
EFI_STATUS
MakeConfigWritable (
 IN PCIDev  *Dev
 );


UINT8
ReadCardState (
  IN  PCIDev          *Device
  );

BOOLEAN
InitializeCard (
  IN  PCIDev          *Dev
  );

EFI_STATUS
WriteMaskBytes (
  IN PCIDev           *Device
  );

BOOLEAN
InitializeCardFunction (
  IN  PCIDev          *Device,
  IN  UINT8           FuncNum
  );

//
//function in search.c
//
EFI_STATUS
FindTestCard (
  IN PCIDev        **Dev
  );

EFI_STATUS
FoundTestCardUnderRB (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo,
  IN PCIDev                          **TestDev
  );

EFI_STATUS
AllocateNewDevice (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *RootBridgeIo,
  IN PCIDev                            **TestDev,
  IN UINT8                             Bus,
  IN UINT8                             Dev,
  IN UINT8                             Func
  );

//
//function in basefunc.c
//
UINT8
ReadConfigByte (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  );

UINT16
ReadConfigWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  );

UINT32
ReadConfigDWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  );

VOID
WriteConfigByte (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT8                             Value
  );

VOID
WriteConfigWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT16                            Value
  );

VOID
WriteConfigDWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT32                            Value
  );

#endif
