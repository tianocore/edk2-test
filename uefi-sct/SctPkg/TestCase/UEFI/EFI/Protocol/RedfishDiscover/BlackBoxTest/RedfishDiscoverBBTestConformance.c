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

  RedfishDiscoverBBTestConformance.c

Abstract:

  Conformance test cases for EFI_REDFISH_DISCOVER_PROTOCOL

  Covers invalid parameter handling for all four protocol functions
  per UEFI 2.8 (Mantis 1920) with clarifications from Mantis 1925
  and revised definitions from UEFI 2.8C (Mantis 2172).

--*/

#include "RedfishDiscoverBBTestMain.h"
#include "SctLib.h"

extern EFI_HANDLE mImageHandle;

EFI_STATUS
EFIAPI
BBTestGetNetworkInterfaceListConformanceTest (
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

  //
  // Checkpoint 1: GetNetworkInterfaceList() with NULL NumberOfNetworkInterfaces
  //
  NetworkInterfaces = NULL;
  Status = RedfishDiscover->GetNetworkInterfaceList (
                              RedfishDiscover,
                              mImageHandle,
                              NULL,
                              &NetworkInterfaces
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestConformanceAssertionGuid001,
                 L"REDFISH_DISCOVER.GetNetworkInterfaceList - NULL NumberOfNetworkInterfaces returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: GetNetworkInterfaceList() with NULL NetworkInterfaces
  //
  NumberOfNetworkInterfaces = 0;
  Status = RedfishDiscover->GetNetworkInterfaceList (
                              RedfishDiscover,
                              mImageHandle,
                              &NumberOfNetworkInterfaces,
                              NULL
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestConformanceAssertionGuid002,
                 L"REDFISH_DISCOVER.GetNetworkInterfaceList - NULL NetworkInterfaces returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3: GetNetworkInterfaceList() with NULL ImageHandle.
  // Per Mantis 2172, ImageHandle == NULL should return EFI_INVALID_PARAMETER.
  //
  NumberOfNetworkInterfaces = 0;
  NetworkInterfaces = NULL;
  Status = RedfishDiscover->GetNetworkInterfaceList (
                              RedfishDiscover,
                              NULL,
                              &NumberOfNetworkInterfaces,
                              &NetworkInterfaces
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestConformanceAssertionGuid007,
                 L"REDFISH_DISCOVER.GetNetworkInterfaceList - NULL ImageHandle returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestAcquireRedfishServiceConformanceTest (
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
  // Checkpoint 1: AcquireRedfishService() with NULL Token.
  // Per spec, Token == NULL should return EFI_INVALID_PARAMETER.
  //
  Status = RedfishDiscover->AcquireRedfishService (
                              RedfishDiscover,
                              mImageHandle,
                              NULL,
                              EFI_REDFISH_DISCOVER_HOST_INTERFACE,
                              NULL
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestConformanceAssertionGuid003,
                 L"REDFISH_DISCOVER.AcquireRedfishService - NULL Token returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: AcquireRedfishService() with Flags == 0.
  // Per spec, Flags == 0 should return EFI_INVALID_PARAMETER.
  //
  SctZeroMem (&Token, sizeof (EFI_REDFISH_DISCOVERED_TOKEN));
  Token.Signature = REDFISH_DISCOVER_TOKEN_SIGNATURE;
  Token.Timeout = 0;
  Token.Event = NULL;

  Status = RedfishDiscover->AcquireRedfishService (
                              RedfishDiscover,
                              mImageHandle,
                              NULL,
                              0,
                              &Token
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestConformanceAssertionGuid004,
                 L"REDFISH_DISCOVER.AcquireRedfishService - Flags == 0 returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3: AcquireRedfishService() with Flags == EFI_REDFISH_DISCOVER_VALIDATION only.
  // Per Mantis 2172, the VALIDATION bit is a modifier, not a discovery method.
  // (Flags & ~EFI_REDFISH_DISCOVER_VALIDATION) == 0 should return EFI_INVALID_PARAMETER.
  //
  SctZeroMem (&Token, sizeof (EFI_REDFISH_DISCOVERED_TOKEN));
  Token.Signature = REDFISH_DISCOVER_TOKEN_SIGNATURE;
  Token.Timeout = 0;
  Token.Event = NULL;

  Status = RedfishDiscover->AcquireRedfishService (
                              RedfishDiscover,
                              mImageHandle,
                              NULL,
                              EFI_REDFISH_DISCOVER_VALIDATION,
                              &Token
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestConformanceAssertionGuid006,
                 L"REDFISH_DISCOVER.AcquireRedfishService - VALIDATION-only Flags returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 4: AcquireRedfishService() with NULL ImageHandle.
  // Per Mantis 2172, ImageHandle == NULL should return EFI_INVALID_PARAMETER.
  //
  SctZeroMem (&Token, sizeof (EFI_REDFISH_DISCOVERED_TOKEN));
  Token.Signature = REDFISH_DISCOVER_TOKEN_SIGNATURE;
  Token.Timeout = 0;
  Token.Event = NULL;

  Status = RedfishDiscover->AcquireRedfishService (
                              RedfishDiscover,
                              NULL,
                              NULL,
                              EFI_REDFISH_DISCOVER_HOST_INTERFACE,
                              &Token
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestConformanceAssertionGuid008,
                 L"REDFISH_DISCOVER.AcquireRedfishService - NULL ImageHandle returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestReleaseRedfishServiceConformanceTest (
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
  // Checkpoint 1: ReleaseRedfishService() with NULL List
  //
  Status = RedfishDiscover->ReleaseRedfishService (RedfishDiscover, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRedfishDiscoverBBTestConformanceAssertionGuid005,
                 L"REDFISH_DISCOVER.ReleaseRedfishService - NULL List returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
