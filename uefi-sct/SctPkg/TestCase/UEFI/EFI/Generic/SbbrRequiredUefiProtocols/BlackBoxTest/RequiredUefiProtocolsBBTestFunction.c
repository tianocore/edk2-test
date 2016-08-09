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

  Copyright (c) 2016, ARM Corporation. All rights reserved.

--*/
/*++

Module Name:

  RequiredUefiProtocolsBBTestFunction.c

Abstract:

  Test case function definitions for RequiredUefiProtocols.

--*/

#include "RequiredUefiProtocolsBBTestMain.h"
#include "RequiredUefiProtocolsBBTestFunction.h"
#include "SctLib.h"
#include "Guid.h"

/**
 *  Entrypoint for MediaIoProtocols Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
BBTestMediaIoProtocolsTest (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_HANDLE                          *HandleBuffer;
  UINTN                               NumberOfHandles;
  SBBR_REQUIRED_PROTOCOL             Protocol[] = {
                                        {EFI_LOAD_FILE_PROTOCOL_GUID, L"EFI_LOAD_FILE_PROTOCOL"},
                                        {EFI_LOAD_FILE2_PROTOCOL_GUID, L"EFI_LOAD_FILE2_PROTOCOL"},
                                        {gEfiNullGuid, 0}
                                      };
  UINT32                              i;

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
  // Looking for Protocols
  //
  i = 0;
  while (SctCompareGuid (&Protocol[i].guid, &gEfiNullGuid) != 0){
    Status = gBS->LocateHandleBuffer (
                ByProtocol,
                &Protocol[i].guid,
                NULL,
                &NumberOfHandles,
                &HandleBuffer
                );

    if ((Status == EFI_NOT_FOUND) && (NumberOfHandles == 0)){
      // Protocol not found
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gRequiredUefiProtocolsAssertion001Guid,
                  L"MediaIoProtocols",
                  L"%a:%d:%s Not Found",
                  __FILE__,
                  __LINE__,
                  Protocol[i].name
                  );
    }
    else {
      // Protocol found
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_PASSED,
                  gRequiredUefiProtocolsAssertion001Guid,
                  L"MediaIoProtocols",
                  L"%a:%d:%s Found",
                  __FILE__,
                  __LINE__,
                  Protocol[i].name
                  );
    }

    i++;
  }

  return EFI_SUCCESS;
}
