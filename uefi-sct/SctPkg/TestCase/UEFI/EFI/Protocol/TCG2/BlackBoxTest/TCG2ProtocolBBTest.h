/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2021 - 2023, Arm Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:
    TCG2ProtocolBBTest.h

Abstract:
    head file of test driver of EFI TCG2 Protocol Test

--*/

#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/TCG2.h>
#include "Guid.h"

#define EFI_TCG2_TEST_REVISION 0x00010000

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Function Test
//
#define EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x39ff9c71, 0x4b41, 0x4e5b, {0xae, 0xd7, 0x87, 0xc7, 0x94, 0x18, 0x7d, 0x67} }

#define EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0x847f1ae0, 0xb429, 0x49f1, {0x9e, 0x0c, 0x8f, 0x43, 0xfb, 0x55, 0x34, 0x54} }

#define EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0103 \
 {0x907a7878, 0xb294, 0xf147, {0xe9, 0x0a, 0x65, 0x43, 0xab, 0x55, 0x76, 0x46} }

#define EV_POST_CODE 0x01

#define EFI_TCG2_EXTEND_ONLY 0x0000000000000001

#define PE_COFF_IMAGE 0x0000000000000010

EFI_STATUS
EFIAPI
BBTestTCG2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetActivePcrBanksConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetActivePcrBanksConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetCapabilityConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetActivePcrBanksConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestHashLogExtendEventConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

