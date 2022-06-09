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

  PciRootBridgeIoBBTestMain.h

Abstract:

  BB test main head file for Pci Root Bridge Io Protocol

--*/



#ifndef _PCI_ROOT_BRIDGE_IO_BBTEST_MAIN_H_
#define _PCI_ROOT_BRIDGE_IO_BBTEST_MAIN_H_


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/PciRootBridgeIo.h>

#include "Guid.h"
#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define EXAMPLE_TEST_REVISION 0x00010001

//
//TDS 4.1.1
//
EFI_STATUS
EFIAPI
PollMem_Func_Manual (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

EFI_STATUS
EFIAPI
PollMemCheckPoint (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo,
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH RootBridgeIoWidth,
  IN  UINT64                                Address,
  IN  UINT64                                Mask,
  IN  UINT64                                TargetValue,
  IN  UINT64                                AlternateValue
  );

//
//TDS 4.1.2
//
EFI_STATUS
EFIAPI
PollMem_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.2.3
//
EFI_STATUS
EFIAPI
PollIo_Func_Manual (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

EFI_STATUS
EFIAPI
PollIoCheckPoint (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo,
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH RootBridgeIoWidth,
  IN  UINT64                                Address,
  IN  UINT64                                Mask,
  IN  UINT64                                TargetValue,
  IN  UINT64                                AlternateValue
  );

//
//TDS 4.1.4
//
EFI_STATUS
EFIAPI
PollIo_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.5
//
EFI_STATUS
EFIAPI
MemRead_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.6
//
EFI_STATUS
EFIAPI
MemWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.7
//
EFI_STATUS
EFIAPI
IoRead_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.8
//
EFI_STATUS
EFIAPI
IoWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.9
//
EFI_STATUS
EFIAPI
PciRead_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.10
//
EFI_STATUS
EFIAPI
PciWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.11
//
EFI_STATUS
EFIAPI
CopyMem_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.12
//
EFI_STATUS
EFIAPI
Map_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.13
//
EFI_STATUS
Unmap_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.1.14
//
EFI_STATUS
EFIAPI
AllocateBuffer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.15
//
EFI_STATUS
EFIAPI
FreeBuffer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );



//
//TDS 4.1.16
//
EFI_STATUS
EFIAPI
Flush_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                SupportHandle
  );

//
//TDS 4.1.17
//
EFI_STATUS
EFIAPI
GetAttributes_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.1.18
//
EFI_STATUS
EFIAPI
SetAttributes_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );
//
//TDS 4.1.19
//
EFI_STATUS
EFIAPI
Configuration_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.1
//
EFI_STATUS
EFIAPI
PollMem_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.2
//
EFI_STATUS
EFIAPI
PollIo_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.3
//
EFI_STATUS
EFIAPI
MemRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.4
//
EFI_STATUS
EFIAPI
MemWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.5
//
EFI_STATUS
EFIAPI
IoRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.6
//
EFI_STATUS
EFIAPI
IoWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.7
//
EFI_STATUS
EFIAPI
PciRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.8
//
EFI_STATUS
EFIAPI
PciWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.9
//
EFI_STATUS
EFIAPI
CopyMem_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.10
//
EFI_STATUS
EFIAPI
Map_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
//TDS 4.2.11
//
EFI_STATUS
EFIAPI
AllocateBuffer_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
//TDS 4.2.12
//
EFI_STATUS
EFIAPI
GetAttributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
//TDS 4.2.13
//
EFI_STATUS
EFIAPI
SetAttributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.3.1
//
EFI_STATUS
EFIAPI
SetAttributes_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
InitializeBBTestPciRootBridgeIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestPciRootBridgeIoUnload (
  IN EFI_HANDLE       ImageHandle
  );

#endif
