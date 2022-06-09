/** @file

  Copyright (c) 2022, Ventana Micro Systems Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:
    RiscVBootProtocolBBTestConformance.c

Abstract:
    for EFI Driver RISC-V Boot Protocol's Conformance Test

--*/
#include "SctLib.h"
#include "RiscVBootProtocolBBTestMain.h"


EFI_STATUS
BBTestGetBootHartIdConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  RISCV_EFI_BOOT_PROTOCOL          		*RiscVBoot;

  //
  // init
  //
  RiscVBoot = (RISCV_EFI_BOOT_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BBTestGetBootHartIdConformanceTestCheckpoint1 (StandardLib, RiscVBoot);

  BBTestGetBootHartIdConformanceTestCheckpoint2 (StandardLib, RiscVBoot);

  BBTestGetBootHartIdConformanceTestCheckpoint3 (StandardLib, RiscVBoot);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetBootHartIdConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINTN                                       hartid;

  //
  // with "This" pointer being NULL.
  //
  Status = RiscVBoot->GetBootHartId (
                        NULL,
                        &hartid
                        );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGetBootHartIdBBTestConformanceAssertionGuid001,
                 L"RISCV_EFI_BOOT_PROTOCOL - GetBootHartId() returns EFI_INVALID_PARAMETER with This pointer as NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetBootHartIdConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINTN                                       hartid;
  RISCV_EFI_BOOT_PROTOCOL                     protocol;

  //
  // with "This" pointer being some thing other than located protocol.
  //
  Status = RiscVBoot->GetBootHartId (
                        &protocol,
                        &hartid
                        );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGetBootHartIdBBTestConformanceAssertionGuid001,
                 L"RISCV_EFI_BOOT_PROTOCOL - GetBootHartId() returns EFI_INVALID_PARAMETER with invalid This pointer.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetBootHartIdConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;

  //
  // with BootHartId as NULL pointer.
  //
  Status = RiscVBoot->GetBootHartId (
                        RiscVBoot,
                        NULL
                        );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGetBootHartIdBBTestConformanceAssertionGuid001,
                 L"RISCV_EFI_BOOT_PROTOCOL - GetBootHartId() returns EFI_INVALID_PARAMETER with NULL BootHartId pointer.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
