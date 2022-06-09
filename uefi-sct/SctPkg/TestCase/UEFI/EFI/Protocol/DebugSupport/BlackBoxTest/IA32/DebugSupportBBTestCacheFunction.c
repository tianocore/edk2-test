/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DebugSupportBBTestCacheFunction.c

Abstract:

  Interface Function Test Cases of Debug Support Protocol

--*/


#include "DebugSupportBBTestMain.h"

/**
 *  Entrypoint for EFI_DEBUG_SUPPORT_PROTOCOL.InvalidateInstructionCache() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.5
//
EFI_STATUS
EFIAPI
BBTestInvalidateInstructionCacheFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEBUG_SUPPORT_PROTOCOL           *DebugSupport;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT64                               Start;
  UINT64                               Length;
  UINTN                                MaxProcessorIndex;
  UINTN                                ProcessorIndex;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DebugSupport = (EFI_DEBUG_SUPPORT_PROTOCOL *)ClientInterface;

  if (DebugSupport->Isa != PlatformIsa) {
    return EFI_SUCCESS;
  }

  Status = DebugSupport->GetMaximumProcessorIndex (DebugSupport, &MaxProcessorIndex);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_DEBUG_SUPPORT_PROTOCOL.GetMaximumProcessorIndex",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (ProcessorIndex = 0; ProcessorIndex <= MaxProcessorIndex; ProcessorIndex++) {

    //
    // Assertion Point 3.5.2.1
    // Invoke InvalidateInstructionCache and verify interface correctness.
    //

    // The Physical base of the memory range to be invalidated.
    Start  = 0x0;

    // The minimum number of bytes in the processor's instruction cache to be invalidated.
    Length = 0x0;

    Status = DebugSupport->InvalidateInstructionCache (DebugSupport, ProcessorIndex, (VOID*)&Start, Length);

    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid015,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.InvalidateInstructionCache - Invoke this function and verify interface correctness",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  }

  return EFI_SUCCESS;
}

