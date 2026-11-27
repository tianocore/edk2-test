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

  RestExBBTestConformance.c

Abstract:

  Conformance test cases for EFI_REST_EX_PROTOCOL

  Covers all seven protocol functions per UEFI 2.8 (Mantis 1834) with
  clarifications from Mantis 1879: all functions except GetService() must
  return EFI_NOT_READY when Configure() has not been called.
  Includes AsyncSendReceive updates from Mantis 1924: cancellation via
  NULL RequestMessage and timeout handling.

--*/

#include "RestExBBTestMain.h"
#include "SctLib.h"

EFI_STATUS
EFIAPI
BBTestGetServiceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REST_EX_PROTOCOL                  *RestEx;
  EFI_TEST_ASSERTION                    AssertionType;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checkpoint 1: Call GetService() with NULL RestExServiceInfo
  //
  Status = RestEx->GetService (RestEx, NULL);

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
                 gRestExBBTestConformanceAssertionGuid001,
                 L"REST_EX.GetService - GetService() with NULL RestExServiceInfo returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetModeDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REST_EX_PROTOCOL                  *RestEx;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_REST_EX_CONFIG_DATA               ConfigData;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checkpoint 1: Call GetModeData() with NULL RestExConfigData
  //
  Status = RestEx->GetModeData (RestEx, NULL);

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
                 gRestExBBTestConformanceAssertionGuid002,
                 L"REST_EX.GetModeData - GetModeData() with NULL RestExConfigData returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: Call GetModeData() before Configure().
  // Per Mantis 1879, all functions except GetService() must return
  // EFI_NOT_READY when Configure() has not been called.
  // First reset to unconfigured state, then call with valid output pointer.
  //
  RestEx->Configure (RestEx, NULL);

  ConfigData = NULL;
  Status = RestEx->GetModeData (RestEx, &ConfigData);

  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED || Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid003,
                 L"REST_EX.GetModeData - GetModeData() before Configure() returns EFI_NOT_READY",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestConfigureConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REST_EX_PROTOCOL                  *RestEx;
  EFI_TEST_ASSERTION                    AssertionType;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checkpoint 1: Configure() with NULL resets to unconfigured state.
  // Per spec, this should succeed or return EFI_UNSUPPORTED.
  //
  Status = RestEx->Configure (RestEx, NULL);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid004,
                 L"REST_EX.Configure - Configure() with NULL RestExConfigData resets to unconfigured",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSendReceiveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REST_EX_PROTOCOL                  *RestEx;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_HTTP_MESSAGE                      RequestMessage;
  EFI_HTTP_MESSAGE                      ResponseMessage;
  EFI_HTTP_REQUEST_DATA                 ReqData;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (&RequestMessage, sizeof (EFI_HTTP_MESSAGE));
  SctZeroMem (&ResponseMessage, sizeof (EFI_HTTP_MESSAGE));

  //
  // Checkpoint 1: SendReceive() with NULL RequestMessage
  //
  Status = RestEx->SendReceive (RestEx, NULL, &ResponseMessage);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED || Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid005,
                 L"REST_EX.SendReceive - SendReceive() with NULL RequestMessage returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: SendReceive() with NULL ResponseMessage
  //
  Status = RestEx->SendReceive (RestEx, &RequestMessage, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED || Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid006,
                 L"REST_EX.SendReceive - SendReceive() with NULL ResponseMessage returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3: SendReceive() before Configure() returns EFI_NOT_READY.
  // Per Mantis 1879, all functions except GetService() must return
  // EFI_NOT_READY when not yet configured.
  //
  RestEx->Configure (RestEx, NULL);

  SctZeroMem (&RequestMessage, sizeof (EFI_HTTP_MESSAGE));
  SctZeroMem (&ResponseMessage, sizeof (EFI_HTTP_MESSAGE));

  SctZeroMem (&ReqData, sizeof (EFI_HTTP_REQUEST_DATA));
  ReqData.Method = HttpMethodGet;
  ReqData.Url    = L"/";
  RequestMessage.Data.Request = &ReqData;

  Status = RestEx->SendReceive (RestEx, &RequestMessage, &ResponseMessage);

  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED || Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid013,
                 L"REST_EX.SendReceive - SendReceive() before Configure() returns EFI_NOT_READY",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestAyncSendReceiveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REST_EX_PROTOCOL                  *RestEx;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_REST_EX_TOKEN                     Token;
  EFI_REST_EX_TOKEN                     CancelToken;
  EFI_REST_EX_TOKEN                     TimeoutToken;
  EFI_HTTP_MESSAGE                      TimeoutReqMsg;
  EFI_HTTP_REQUEST_DATA                 TimeoutReqData;
  UINTN                                 ZeroTimeout;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checkpoint 1: AyncSendReceive() with NULL RestExToken
  //
  Status = RestEx->AyncSendReceive (RestEx, NULL, NULL, NULL);

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
                 gRestExBBTestConformanceAssertionGuid007,
                 L"REST_EX.AyncSendReceive - AyncSendReceive() with NULL RestExToken returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: AyncSendReceive() before Configure() returns EFI_NOT_READY.
  // Per Mantis 1879, all functions except GetService() must return
  // EFI_NOT_READY when not yet configured.
  //
  RestEx->Configure (RestEx, NULL);

  SctZeroMem (&Token, sizeof (EFI_REST_EX_TOKEN));

  Status = RestEx->AyncSendReceive (RestEx, NULL, &Token, NULL);

  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED || Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid008,
                 L"REST_EX.AyncSendReceive - AyncSendReceive() before Configure() returns EFI_NOT_READY",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3 (Mantis 1924): AyncSendReceive() with NULL RequestMessage
  // and a valid RestExToken should cancel any outstanding async request
  // and return EFI_ABORTED. When no previous request exists, EFI_NOT_FOUND
  // or EFI_UNSUPPORTED are acceptable.
  //
  // Must configure first — per Mantis 1879, unconfigured returns EFI_NOT_READY,
  // which would mask the cancellation behavior under test.
  //
  {
    EFI_REST_EX_HTTP_CONFIG_DATA  HttpConfigData;
    SctZeroMem (&HttpConfigData, sizeof (HttpConfigData));
    RestEx->Configure (RestEx, (EFI_REST_EX_CONFIG_DATA)&HttpConfigData);
  }

  SctZeroMem (&CancelToken, sizeof (EFI_REST_EX_TOKEN));

  Status = RestEx->AyncSendReceive (RestEx, NULL, &CancelToken, NULL);

  if (Status == EFI_ABORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED ||
             Status == EFI_NOT_READY ||
             Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid014,
                 L"REST_EX.AyncSendReceive - NULL RequestMessage cancels async request, returns EFI_ABORTED (Mantis 1924)",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 4 (Mantis 1924): AyncSendReceive() with a zero-value
  // TimeOutInMilliSeconds. Per the revised spec, the driver should signal
  // the token with EFI_TIMEOUT when the timeout expires. With a zero
  // timeout, the function itself should return EFI_TIMEOUT.
  //
  SctZeroMem (&TimeoutToken, sizeof (EFI_REST_EX_TOKEN));
  SctZeroMem (&TimeoutReqMsg, sizeof (EFI_HTTP_MESSAGE));
  SctZeroMem (&TimeoutReqData, sizeof (EFI_HTTP_REQUEST_DATA));

  TimeoutReqData.Method = HttpMethodGet;
  TimeoutReqData.Url    = L"/";
  TimeoutReqMsg.Data.Request = &TimeoutReqData;
  TimeoutReqMsg.HeaderCount  = 0;
  TimeoutReqMsg.Headers      = NULL;
  TimeoutReqMsg.BodyLength   = 0;
  TimeoutReqMsg.Body         = NULL;

  ZeroTimeout = 0;

  Status = RestEx->AyncSendReceive (RestEx, &TimeoutReqMsg, &TimeoutToken, &ZeroTimeout);

  if (Status == EFI_TIMEOUT) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED ||
             Status == EFI_NOT_READY ||
             Status == EFI_SUCCESS ||
             Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid015,
                 L"REST_EX.AyncSendReceive - zero TimeOutInMilliSeconds returns EFI_TIMEOUT (Mantis 1924)",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetServiceTimeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REST_EX_PROTOCOL                  *RestEx;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_TIME                              Time;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checkpoint 1: GetServiceTime() with NULL Time pointer
  //
  Status = RestEx->GetServiceTime (RestEx, NULL);

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
                 gRestExBBTestConformanceAssertionGuid009,
                 L"REST_EX.GetServiceTime - GetServiceTime() with NULL Time returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: GetServiceTime() before Configure() returns EFI_NOT_READY.
  // Per spec and Mantis 1879, must return EFI_NOT_READY if not configured.
  //
  RestEx->Configure (RestEx, NULL);

  SctZeroMem (&Time, sizeof (EFI_TIME));

  Status = RestEx->GetServiceTime (RestEx, &Time);

  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED || Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid010,
                 L"REST_EX.GetServiceTime - GetServiceTime() before Configure() returns EFI_NOT_READY",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestEventServiceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REST_EX_PROTOCOL                  *RestEx;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_REST_EX_TOKEN                     Token;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checkpoint 1: EventService() with NULL RestExToken
  //
  Status = RestEx->EventService (RestEx, NULL, NULL);

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
                 gRestExBBTestConformanceAssertionGuid011,
                 L"REST_EX.EventService - EventService() with NULL RestExToken returns EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: EventService() before Configure() returns EFI_NOT_READY.
  // Per Mantis 1879, all functions except GetService() must return
  // EFI_NOT_READY when not yet configured.
  //
  RestEx->Configure (RestEx, NULL);

  SctZeroMem (&Token, sizeof (EFI_REST_EX_TOKEN));

  Status = RestEx->EventService (RestEx, NULL, &Token);

  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED || Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestConformanceAssertionGuid012,
                 L"REST_EX.EventService - EventService() before Configure() returns EFI_NOT_READY",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
