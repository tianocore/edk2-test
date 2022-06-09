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

  DecompressBBTestMain.h

Abstract:

  BB test main header file for Decompress protocol

--*/

#ifndef _DECOMPRESSTEST_H
#define _DECOMPRESSTEST_H

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Decompress.h>
#include "Guid.h"

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define EXAMPLE_TEST_REVISION 0x00010000

//
//TDS 4.1.1
//
EFI_STATUS
EFIAPI
GetInfo_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.1.2
//
EFI_STATUS
EFIAPI
Decompress_Func (
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
GetInfo_Conf (
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
Decompress_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
InitializeDecompressProtocolBBTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
DecompressProtocolBBTestUnload (
  IN EFI_HANDLE       ImageHandle
  );

#endif
