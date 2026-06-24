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

  RestExBBTestFunction.c

Abstract:

  Function test cases for EFI_REST_EX_PROTOCOL

  Covers all seven protocol functions per UEFI 2.8 (Mantis 1834) with
  clarifications from Mantis 1879 and AsyncSendReceive updates from
  Mantis 1924.

--*/

#include "RestExBBTestMain.h"
#include "SctLib.h"

EFI_STATUS
EFIAPI
BBTestGetServiceFunctionTest (
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
  EFI_REST_EX_SERVICE_INFO              *ServiceInfo;
  EFI_REST_EX_SERVICE_INFO_V_1_0        *InfoV10;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ServiceInfo = NULL;

  //
  // Checkpoint 1: GetService() returns EFI_SUCCESS with valid info.
  // Per Mantis 1879, GetService() is the only function that must work
  // even before Configure() is called.
  //
  Status = RestEx->GetService (RestEx, &ServiceInfo);

  if (Status == EFI_SUCCESS && ServiceInfo != NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestFunctionAssertionGuid001,
                 L"REST_EX.GetService - GetService() returns valid EFI_REST_EX_SERVICE_INFO",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2: Validate service type is within known range
  //
  if (Status == EFI_SUCCESS && ServiceInfo != NULL) {
    InfoV10 = &ServiceInfo->EfiRestExServiceInfoV10;

    if (InfoV10->RestServiceType >= EfiRestExServiceUnspecific &&
        InfoV10->RestServiceType < EfiRestExServiceTypeMax) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gRestExBBTestFunctionAssertionGuid002,
                   L"REST_EX.GetService - Service type is valid",
                   L"%a:%d: RestServiceType - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   InfoV10->RestServiceType
                   );

    gtBS->FreePool (ServiceInfo);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestConfigureFunctionTest (
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
  // Checkpoint 1: Configure() with NULL to reset to unconfigured state.
  // Per spec, this puts the instance back to unconfigured and should succeed.
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
                 gRestExBBTestFunctionAssertionGuid004,
                 L"REST_EX.Configure - Configure() with NULL resets to unconfigured",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetModeDataFunctionTest (
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

  ConfigData = NULL;

  //
  // Checkpoint 1: GetModeData() returns configuration data.
  // Per Mantis 1879, returns EFI_NOT_READY if Configure() has not been
  // called, EFI_SUCCESS if configured, or EFI_UNSUPPORTED.
  //
  Status = RestEx->GetModeData (RestEx, &ConfigData);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_NOT_READY || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestFunctionAssertionGuid005,
                 L"REST_EX.GetModeData - GetModeData() returns configuration data",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Status == EFI_SUCCESS && ConfigData != NULL) {
    gtBS->FreePool (ConfigData);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSendReceiveFunctionTest (
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
  EFI_HTTP_REQUEST_DATA                 RequestData;

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
  // Checkpoint 1: SendReceive() with a basic GET request.
  // A REST service endpoint may not be available in the test environment,
  // so EFI_DEVICE_ERROR, EFI_NOT_READY, and EFI_TIMEOUT are treated as
  // warnings rather than failures.
  //
  SctZeroMem (&RequestMessage, sizeof (EFI_HTTP_MESSAGE));
  SctZeroMem (&ResponseMessage, sizeof (EFI_HTTP_MESSAGE));
  SctZeroMem (&RequestData, sizeof (EFI_HTTP_REQUEST_DATA));

  RequestData.Method = HttpMethodGet;
  RequestData.Url    = L"/";

  RequestMessage.Data.Request = &RequestData;
  RequestMessage.HeaderCount  = 0;
  RequestMessage.Headers      = NULL;
  RequestMessage.BodyLength   = 0;
  RequestMessage.Body         = NULL;

  Status = RestEx->SendReceive (RestEx, &RequestMessage, &ResponseMessage);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_NOT_READY ||
             Status == EFI_DEVICE_ERROR ||
             Status == EFI_TIMEOUT) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestFunctionAssertionGuid006,
                 L"REST_EX.SendReceive - SendReceive() basic GET request",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetServiceTimeFunctionTest (
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

  SctZeroMem (&Time, sizeof (EFI_TIME));

  //
  // Checkpoint 1: GetServiceTime() returns time or EFI_UNSUPPORTED.
  // Per spec, this is optional. EFI_UNSUPPORTED must be returned if
  // the service type is EfiRestExServiceUnspecific.
  // Per Mantis 1879, returns EFI_NOT_READY if not configured.
  //
  Status = RestEx->GetServiceTime (RestEx, &Time);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED ||
             Status == EFI_NOT_READY ||
             Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestFunctionAssertionGuid007,
                 L"REST_EX.GetServiceTime - GetServiceTime() returns valid time or EFI_UNSUPPORTED",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestAyncSendReceiveFunctionTest (
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
  EFI_HTTP_MESSAGE                      RequestMessage;
  EFI_HTTP_REQUEST_DATA                 RequestData;
  EFI_REST_EX_TOKEN                     TimeoutToken;
  EFI_HTTP_MESSAGE                      TimeoutReqMsg;
  EFI_HTTP_REQUEST_DATA                 TimeoutReqData;
  UINTN                                 TimeoutMs;
  EFI_REST_EX_TOKEN                     CancelToken;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (&Token, sizeof (EFI_REST_EX_TOKEN));
  SctZeroMem (&RequestMessage, sizeof (EFI_HTTP_MESSAGE));
  SctZeroMem (&RequestData, sizeof (EFI_HTTP_REQUEST_DATA));

  RequestData.Method = HttpMethodGet;
  RequestData.Url    = L"/";

  RequestMessage.Data.Request = &RequestData;
  RequestMessage.HeaderCount  = 0;
  RequestMessage.Headers      = NULL;
  RequestMessage.BodyLength   = 0;
  RequestMessage.Body         = NULL;

  //
  // Checkpoint 1: AyncSendReceive() with valid parameters and no timeout.
  // EFI_UNSUPPORTED is acceptable if the driver does not support async.
  // EFI_NOT_READY is acceptable if not yet configured (Mantis 1879).
  //
  Status = RestEx->AyncSendReceive (RestEx, &RequestMessage, &Token, NULL);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED ||
             Status == EFI_NOT_READY ||
             Status == EFI_DEVICE_ERROR ||
             Status == EFI_TIMEOUT) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestFunctionAssertionGuid008,
                 L"REST_EX.AyncSendReceive - AyncSendReceive() establishes async request",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2 (Mantis 1924): AyncSendReceive() with TimeOutInMilliSeconds.
  // Per UEFI 2.8, a non-NULL TimeOutInMilliSeconds specifies the duration
  // after which the driver should signal EFI_TIMEOUT via the token if no
  // response has been received. A very short timeout is used here to
  // exercise the timeout path.
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

  TimeoutMs = 1;

  Status = RestEx->AyncSendReceive (RestEx, &TimeoutReqMsg, &TimeoutToken, &TimeoutMs);

  if (Status == EFI_SUCCESS || Status == EFI_TIMEOUT) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED ||
             Status == EFI_NOT_READY ||
             Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestFunctionAssertionGuid010,
                 L"REST_EX.AyncSendReceive - AyncSendReceive() with TimeOutInMilliSeconds (Mantis 1924)",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3 (Mantis 1924): AyncSendReceive() cancellation via NULL
  // RequestMessage. Per UEFI 2.8, setting RequestMessage to NULL cancels
  // the previous asynchronous request associated with the RestExToken
  // and must return EFI_ABORTED.
  //
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
                 gRestExBBTestFunctionAssertionGuid011,
                 L"REST_EX.AyncSendReceive - NULL RequestMessage cancels previous request, returns EFI_ABORTED (Mantis 1924)",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestEventServiceFunctionTest (
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
  EFI_HTTP_MESSAGE                      RequestMessage;
  EFI_HTTP_REQUEST_DATA                 RequestData;

  RestEx = (EFI_REST_EX_PROTOCOL *)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (&Token, sizeof (EFI_REST_EX_TOKEN));
  SctZeroMem (&RequestMessage, sizeof (EFI_HTTP_MESSAGE));
  SctZeroMem (&RequestData, sizeof (EFI_HTTP_REQUEST_DATA));

  RequestData.Method = HttpMethodGet;
  RequestData.Url    = L"/";

  RequestMessage.Data.Request = &RequestData;
  RequestMessage.HeaderCount  = 0;
  RequestMessage.Headers      = NULL;
  RequestMessage.BodyLength   = 0;
  RequestMessage.Body         = NULL;

  //
  // Checkpoint 1: EventService() with valid parameters.
  // EFI_UNSUPPORTED is acceptable if the driver does not support events.
  // EFI_NOT_READY is acceptable if not yet configured (Mantis 1879).
  //
  Status = RestEx->EventService (RestEx, &RequestMessage, &Token);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_UNSUPPORTED ||
             Status == EFI_NOT_READY ||
             Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRestExBBTestFunctionAssertionGuid009,
                 L"REST_EX.EventService - EventService() establishes event subscription",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
