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

  PciIoBBTestMain.h

Abstract:

  BB test main header file for Pci Io Protocol Interface.

--*/


#ifndef _EFI_PCI_IO_BBTEST_MAIN_H_
#define _EFI_PCI_IO_BBTEST_MAIN_H_


#include "Efi.h"
#include <IndustryStandard/Pci22.h>
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/PciIo.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)
#include "Guid.h"

#define PCIIO_TEST_REVISION 0x00010001


//
//TDS 4.1.1
//
EFI_STATUS
EFIAPI
PollMem_Func_Manual (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );
//
//internal help function.
//
EFI_STATUS
EFIAPI
PollMemCheckPoint (
  IN  EFI_PCI_IO_PROTOCOL                 *PciIo,
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_PCI_IO_PROTOCOL_WIDTH           PciIoWidth,
  IN  UINT8                               BarIndex,
  IN  UINT64                              AddressOffset,
  IN  UINT64                              Mask,
  IN  UINT64                              TargetValue,
  IN  UINT64                              AlternateValue
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
  IN EFI_HANDLE                  SupportHandle
  );


//
//TDS 4.1.3
//
EFI_STATUS
EFIAPI
PollIo_Func_Manual (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//internal function to check the PollIo Check Point.
//
EFI_STATUS
EFIAPI
PollIoCheckPoint (
  IN  EFI_PCI_IO_PROTOCOL                 *PciIo,
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_PCI_IO_PROTOCOL_WIDTH           PciIoWidth,
  IN  UINT8                               BarIndex,
  IN  UINT64                              AddressOffset,
  IN  UINT64                              Mask,
  IN  UINT64                              TargetValue,
  IN  UINT64                              AlternateValue
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.1.13
//
EFI_STATUS
EFIAPI
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.1.17
//
EFI_STATUS
EFIAPI
GetLocation_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.1.18
//
EFI_STATUS
EFIAPI
Attributes_Func (
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
GetBarAttributes_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.1.20
//
EFI_STATUS
EFIAPI
SetBarAttributes_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//conformance testing
//

//
//TDS 4.2.1
//
EFI_STATUS
EFIAPI
PollMem_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
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
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.2.11
//
EFI_STATUS
EFIAPI
Unmap_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.2.12
//
EFI_STATUS
EFIAPI
AllocateBuffer_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.2.13
//
EFI_STATUS
EFIAPI
FreeBuffer_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );


//
//TDS 4.2.14
//
EFI_STATUS
EFIAPI
GetLocation_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.2.15
//
EFI_STATUS
EFIAPI
Attributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );


//
//TDS 4.2.16
//
EFI_STATUS
EFIAPI
GetBarAttributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.2.17
//
EFI_STATUS
EFIAPI
SetBarAttributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );
//
//TDS 4.3.1
//
EFI_STATUS
EFIAPI
MapUnmap_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.3.2
//
EFI_STATUS
EFIAPI
AllocateBufferFreeBuffer_Stress (
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
Attributes_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  );

//
//TDS 4.3.4
//
EFI_STATUS
EFIAPI
GetAndSetBarAttributes_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
//entry point
//
EFI_STATUS
EFIAPI
InitializeBBTestPciIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

//
//unload function
//
EFI_STATUS
EFIAPI
BBTestPciIoUnload (
  IN EFI_HANDLE       ImageHandle
  );

#endif
