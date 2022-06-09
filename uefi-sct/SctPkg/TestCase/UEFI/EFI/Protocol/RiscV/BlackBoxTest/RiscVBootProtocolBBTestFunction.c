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
    RiscVBootProtocolBBTestFunction.c

Abstract:
    for EFI Driver RISC-V Boot Protocol's function Test

--*/
#include "SctLib.h"
#include "RiscVBootProtocolBBTestMain.h"

EFI_STATUS
BBTestGetBootHartIdFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot;

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

  BBTestGetBootHartIdFunctionTestCheckpoint1 (StandardLib, RiscVBoot);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetBootHartIdFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot
  )
{
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN					hartid1 = 0xdead;
  UINTN					hartid2 = 0xbeef;


  //
  // with correct This and BoothartId pointers.
  //

  Status = RiscVBoot->GetBootHartId (
                        RiscVBoot,
                        &hartid1
                        );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGetBootHartIdBBTestFunctionAssertionGuid001,
                 L"RISCV_EFI_BOOT_PROTOCOL.GetBootHartId - GetBootHartId() returns EFI_SUCCESS with valid parameters.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // call again with correct This and BoothartId pointers to ensure hartid is not changed.
  //

  Status = RiscVBoot->GetBootHartId (
                        RiscVBoot,
                        &hartid2
                        );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (hartid1 != hartid2) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGetBootHartIdBBTestFunctionAssertionGuid002,
                 L"RISCV_EFI_BOOT_PROTOCOL.GetBootHartId - GetBootHartId() returned same hartid when called twice.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  return EFI_SUCCESS;

  }
