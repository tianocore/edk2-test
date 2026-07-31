/** @file

  Copyright 2006 - 2026 Unified EFI, Inc.<BR>
  Copyright (c) 2026, AMD Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  RedfishDiscoverBBTestFunction.c

Abstract:

  Function test cases for EFI_REDFISH_DISCOVER_PROTOCOL

  Covers all four protocol functions per UEFI 2.8 (Mantis 1920) with
  clarifications from Mantis 1925.

--*/

#include "RedfishDiscoverBBTestMain.h"
#include "SctLib.h"

extern EFI_HANDLE mImageHandle;

EFI_STATUS
EFIAPI
BBTestGetNetworkInterfaceListFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib;
  EFI_STATUS                                  Status;
  EFI_REDFISH_DISCOVER_PROTOCOL               *RedfishDiscover;
  EFI_TEST_ASSERTION                          AssertionType;
  UINTN                                       NumberOfNetworkInterfaces;
  EFI_REDFISH_DISCOVER_NETWORK_INTERFACE      *NetworkInterfaces;

  RedfishDiscover = (EFI_REDFISH_DISCOVER_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  NumberOfNetworkInterfaces = 0;
  NetworkInterfaces = NULL;

  //
  // Checkpoint 1: GetNetworkInterfaceList() with valid parameters.
  // Should return EFI_SUCCESS with a list of NICs capable of Redfish
  // discovery, or EFI_NOT_FOUND if no interfaces are available.
  //
  Status = RedfishDiscover->GetNetworkInterfaceList (
                              RedfishDiscover,
                              mImageHandle,
                              &NumberOfNetworkInterfaces,
                              &NetworkInterfaces
                              );

  if (Status == EFI_SUCCESS && NetworkInterfaces != NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_NOT_FOUND || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestFunctionAssertionGuid001,
                 L"REDFISH_DISCOVER.GetNetworkInterfaceList - returns valid interface list",
                 L"%a:%d: Status - %r, Count - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 NumberOfNetworkInterfaces
                 );

  //
  // Checkpoint 2: If successful, verify NumberOfNetworkInterfaces > 0.
  //
  if (Status == EFI_SUCCESS) {
    if (NumberOfNetworkInterfaces > 0 && NetworkInterfaces != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gRedfishDiscoverBBTestFunctionAssertionGuid002,
                   L"REDFISH_DISCOVER.GetNetworkInterfaceList - NumberOfNetworkInterfaces is consistent",
                   L"%a:%d: Count - %d, Pointer - 0x%p",
                   __FILE__,
                   (UINTN)__LINE__,
                   NumberOfNetworkInterfaces,
                   NetworkInterfaces
                   );

    gtBS->FreePool (NetworkInterfaces);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestAcquireRedfishServiceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib;
  EFI_STATUS                                  Status;
  EFI_REDFISH_DISCOVER_PROTOCOL               *RedfishDiscover;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_REDFISH_DISCOVERED_TOKEN                Token;

  RedfishDiscover = (EFI_REDFISH_DISCOVER_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checkpoint 1: AcquireRedfishService() synchronous discovery.
  // Set Timeout to 0 for synchronous mode. A real Redfish service may
  // not be present; EFI_NOT_FOUND and EFI_TIMEOUT are acceptable.
  //
  SctZeroMem (&Token, sizeof (EFI_REDFISH_DISCOVERED_TOKEN));
  Token.Signature = REDFISH_DISCOVER_TOKEN_SIGNATURE;
  Token.Timeout = 0;
  Token.Event = NULL;

  Status = RedfishDiscover->AcquireRedfishService (
                              RedfishDiscover,
                              mImageHandle,
                              NULL,
                              EFI_REDFISH_DISCOVER_HOST_INTERFACE,
                              &Token
                              );

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_NOT_FOUND ||
             Status == EFI_TIMEOUT ||
             Status == EFI_UNSUPPORTED ||
             Status == EFI_DEVICE_ERROR ||
             Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestFunctionAssertionGuid003,
                 L"REDFISH_DISCOVER.AcquireRedfishService - synchronous discovery via host interface",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Status == EFI_SUCCESS && Token.DiscoverList.NumberOfServiceFound > 0) {
    RedfishDiscover->ReleaseRedfishService (
                       RedfishDiscover,
                       &Token.DiscoverList
                       );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestAbortAndReleaseFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib;
  EFI_STATUS                                  Status;
  EFI_REDFISH_DISCOVER_PROTOCOL               *RedfishDiscover;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_REDFISH_DISCOVERED_LIST                 EmptyList;

  RedfishDiscover = (EFI_REDFISH_DISCOVER_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checkpoint 1: AbortAcquireRedfishService() with NULL target interface
  // (abort on all interfaces). When no discovery is in progress,
  // EFI_NOT_FOUND or EFI_UNSUPPORTED is acceptable.
  //
  Status = RedfishDiscover->AbortAcquireRedfishService (RedfishDiscover, NULL);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_NOT_FOUND || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestFunctionAssertionGuid004,
                 L"REDFISH_DISCOVER.AbortAcquireRedfishService - abort with NULL target",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: ReleaseRedfishService() with an empty list.
  // Per spec, the list was allocated by Acquire() — passing an empty
  // but non-NULL list should succeed or return a benign error.
  //
  SctZeroMem (&EmptyList, sizeof (EFI_REDFISH_DISCOVERED_LIST));

  Status = RedfishDiscover->ReleaseRedfishService (RedfishDiscover, &EmptyList);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_INVALID_PARAMETER || Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestFunctionAssertionGuid005,
                 L"REDFISH_DISCOVER.ReleaseRedfishService - release empty list",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
