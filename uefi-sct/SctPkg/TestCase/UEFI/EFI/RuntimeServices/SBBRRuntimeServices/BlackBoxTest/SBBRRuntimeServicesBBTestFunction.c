/*++
  The material contained herein is not a license, either
  expressly or impliedly, to any intellectual property owned
  or controlled by any of the authors or developers of this
  material or to any contribution thereto. The material
  contained herein is provided on an "AS IS" basis and, to the
  maximum extent permitted by applicable law, this information
  is provided AS IS AND WITH ALL FAULTS, and the authors and
  developers of this material hereby disclaim all other
  warranties and conditions, either express, implied or
  statutory, including, but not limited to, any (if any)
  implied warranties, duties or conditions of merchantability,
  of fitness for a particular purpose, of accuracy or
  completeness of responses, of results, of workmanlike
  effort, of lack of viruses and of lack of negligence, all
  with regard to this material and any contribution thereto.
  Designers must not rely on the absence or characteristics of
  any features or instructions marked "reserved" or
  "undefined." The Unified EFI Forum, Inc. reserves any
  features or instructions so marked for future definition and
  shall have no responsibility whatsoever for conflicts or
  incompatibilities arising from future changes to them. ALSO,
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY
  CONTRIBUTION THERETO.

  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF
  THE POSSIBILITY OF SUCH DAMAGES.

  Copyright 2006 - 2016 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2016, ARM Corporation. All rights reserved.<BR>

--*/
/*++

Module Name:

  SBBRRuntimeServicesBBTestFunction.c

Abstract:

  Test cases for SBBRRuntimeServices.

--*/
#include "Guid.h"
#include "SctLib.h"
#include "SBBRRuntimeServicesBBTestMain.h"
#include "SBBRRuntimeServicesBBTestFunction.h"




/**
 *  Entrypoint for Runtime Services Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
BBTestRuntimeServices (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_TEST_ASSERTION                  AssertionType;
  UINT32              CRC32;
  UINT32              LocalCRC32;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Check the EFI Runtime Services Table
  //
  CRC32 = gtRT->Hdr.CRC32;
  gtRT->Hdr.CRC32 = 0;

  LocalCRC32 = 0;
  Status = SctCalculateCrc32 ((UINT8 *)gtRT, gtRT->Hdr.HeaderSize, &LocalCRC32);
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    if ((gtRT->Hdr.Signature             == EFI_RUNTIME_SERVICES_SIGNATURE) &&
        (gtRT->Hdr.Revision              >= 0x00020000                    ) &&
        (gtRT->Hdr.Reserved              == 0x00000000                    ) &&
        (gtRT->GetTime                   != NULL                          ) &&
        (gtRT->SetTime                   != NULL                          ) &&
        (gtRT->GetWakeupTime             != NULL                          ) &&
        (gtRT->SetWakeupTime             != NULL                          ) &&
        (gtRT->SetVirtualAddressMap      != NULL                          ) &&
        (gtRT->ConvertPointer            != NULL                          ) &&
        (gtRT->GetVariable               != NULL                          ) &&
        (gtRT->GetNextVariableName       != NULL                          ) &&
        (gtRT->SetVariable               != NULL                          ) &&
        (gtRT->GetNextHighMonotonicCount != NULL                          ) &&
        (gtRT->ResetSystem               != NULL                          ) &&
        (gtRT->QueryVariableInfo         != NULL                          ) &&
        (gtRT->QueryCapsuleCapabilities  != NULL                          ) &&
        (gtRT->UpdateCapsule             != NULL                          ) &&
        (LocalCRC32                      == CRC32                         )) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    gtRT->Hdr.CRC32 = CRC32;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSBBRRuntimeServicesAssertion001Guid,
                 L"UEFI Compliant - EFI Runtime Services Table must be implemented",
                 L"%a:%d:Signature - %lX, Expected - %lX",
                 __FILE__,
                 (UINTN)__LINE__,
                 gtRT->Hdr.Signature,
                 EFI_RUNTIME_SERVICES_SIGNATURE
                 );

  //
  // Record the entire EFI Runtime Services Table
  //
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  Hdr.Signature             : %lX\n"
                 L"  Hdr.Revision              : %X\n"
                 L"  Hdr.HeaderSize            : %X\n"
                 L"  Hdr.CRC32                 : %X\n"
                 L"  Hdr.Reserved              : %X\n",
                 gtRT->Hdr.Signature,
                 gtRT->Hdr.Revision,
                 gtRT->Hdr.HeaderSize,
                 gtRT->Hdr.CRC32,
                 gtRT->Hdr.Reserved
                 );


  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  GetTime                   : %X\n"
                 L"  SetTime                   : %X\n"
                 L"  GetWakeupTime             : %X\n"
                 L"  SetWakeupTime             : %X\n"
                 L"  SetVirtualAddressMap      : %X\n"
                 L"  ConvertPointer            : %X\n"
                 L"  GetVariable               : %X\n"
                 L"  GetNextVariableName       : %X\n"
                 L"  SetVariable               : %X\n"
                 L"  GetNextHighMonotonicCount : %X\n"
                 L"  ResetSystem               : %X\n"
                 L"  QueryVariableInfo         : %X\n"
                 L"  QueryCapsuleCapabilities  : %X\n"
                 L"  UpdateCapsule             : %X\n",
                 gtRT->GetTime,
                 gtRT->SetTime,
                 gtRT->GetWakeupTime,
                 gtRT->SetWakeupTime,
                 gtRT->SetVirtualAddressMap,
                 gtRT->ConvertPointer,
                 gtRT->GetVariable,
                 gtRT->GetNextVariableName,
                 gtRT->SetVariable,
                 gtRT->GetNextHighMonotonicCount,
                 gtRT->ResetSystem,
                 gtRT->QueryVariableInfo,
                 gtRT->QueryCapsuleCapabilities,
                 gtRT->UpdateCapsule
                 );

  //
  // Done
  //

  //
  // Function calls like above are used to record test results.
  // The actual return value of this function is used to tell
  // the framework whether the tests completed successfully or
  // if there was some fault in the test itself.  For example, not
  // being able to allocate a buffer because the system is out of
  // memory would return an error, but a test case failing because
  // a register being checked does not contain the right value
  // would return EFI_SUCCESS.
  //

  return EFI_SUCCESS;
}
