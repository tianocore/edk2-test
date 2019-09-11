/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2019,Microchip Technology Inc.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:
    HIIConfigAccessBBTestFunction.c

Abstract:
    for EFI Driver HII Configuration Access Protocol's function Test

--*/

#include "HIIConfigAccessBBTestMain.h"


EFI_STATUS
BBTestExtractConfigFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting,
  IN EFI_HII_CONFIG_ACCESS_PROTOCOL             *HIIConfigAccess
  );

EFI_STATUS
BBTestExtractConfigFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting,
  IN EFI_HII_CONFIG_ACCESS_PROTOCOL             *HIIConfigAccess
  );

EFI_STATUS
BBTestRouteConfigFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting,
  IN EFI_HII_CONFIG_ACCESS_PROTOCOL             *HIIConfigAccess
  );

//
//Test Cases
//

EFI_STATUS
BBTestExtractConfigFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ACCESS_PROTOCOL        *HIIConfigAccess;
  EFI_HII_CONFIG_ROUTING_PROTOCOL       *HIIConfigRouting;

  //
  // init
  //
  HIIConfigAccess = (EFI_HII_CONFIG_ACCESS_PROTOCOL*)ClientInterface;

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

  //
  // Get the Config Routing Protocol Interface
  //
  Status = GetHIIConfigRoutingInterface( &HIIConfigRouting );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestExtractConfigFunctionTestCheckpoint1( StandardLib, HIIConfigRouting, HIIConfigAccess );
  BBTestExtractConfigFunctionTestCheckpoint2( StandardLib, HIIConfigRouting, HIIConfigAccess );

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestRouteConfigFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ACCESS_PROTOCOL        *HIIConfigAccess;
  EFI_HII_CONFIG_ROUTING_PROTOCOL       *HIIConfigRouting;

  //
  // init
  //
  HIIConfigAccess = (EFI_HII_CONFIG_ACCESS_PROTOCOL*)ClientInterface;

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

  //
  // Get the Config Routing Protocol Interface
  //
  Status = GetHIIConfigRoutingInterface( &HIIConfigRouting );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestRouteConfigFunctionTestCheckpoint1( StandardLib, HIIConfigRouting, HIIConfigAccess );

  return EFI_SUCCESS;
}

//
//Check Points
//
EFI_STATUS
BBTestExtractConfigFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting,
  IN EFI_HII_CONFIG_ACCESS_PROTOCOL             *HIIConfigAccess
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_STRING            Request = NULL;
  EFI_STRING            ConfigHdr = NULL;
  EFI_STRING            Progress = NULL;
  EFI_STRING            Results = NULL;
  EFI_STRING            MultiConfigAltResp = NULL;
  EFI_STRING            DevicePath = NULL;


  //init the Request
  Status = HIIConfigRouting->ExportConfig(
                               HIIConfigRouting,
                               &MultiConfigAltResp
                               );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = GetDevicePath ( HIIConfigAccess, &DevicePath );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (MultiConfigAltResp);
    return Status;
  }

  Request = (EFI_STRING) SctAllocateZeroPool ( 2 * SctStrLen (MultiConfigAltResp) + 2 );
  if (Request == NULL) {
    gtBS->FreePool (MultiConfigAltResp);
    gtBS->FreePool (DevicePath);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = GetCorrespondingRequest (MultiConfigAltResp, DevicePath, Request);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (MultiConfigAltResp);
    gtBS->FreePool (DevicePath);
    gtBS->FreePool (Request);
    return Status;
  }

  //
  // Call ExtractConfig with valid parameters
  //
  Status = HIIConfigAccess->ExtractConfig(
                  HIIConfigAccess,
                  Request,
                  &Progress,
                  &Results
                  );

  if ( (EFI_SUCCESS == Status) && (Progress == (Request + SctStrLen (Request))) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (Results == NULL) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      gtBS->FreePool (Results);
    }
  } else if (EFI_OUT_OF_RESOURCES == Status) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigAccessBBTestFunctionAssertionGuid001,
                 L"HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig- ExtractConfig() returns EFI_SUCCESS and vaild Results with valid parameters .",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Change the Request to ConfigHdr
  //
  ConfigHdr = Request;
  while (*Request) {
    if (*Request == L'&') {
      if (SctStrnCmp (Request, L"&NAME=", 6) == 0) {
        Request = Request + 6;
      } else if (SctStrnCmp (Request, L"&PATH=", 6) == 0) {
        Request = Request + 6;
      } else {
        *Request = 0;
      }
    } else {
      Request++;
    }
  }
  Request = ConfigHdr;

  //
  // Call ExtractConfig when Request is ConfigHdr
  //
  Progress = NULL;
  Results = NULL;
  Status = HIIConfigAccess->ExtractConfig(
                  HIIConfigAccess,
                  Request,
                  &Progress,
                  &Results
                  );

  if ( (EFI_SUCCESS == Status) && (Progress == (Request + SctStrLen (Request))) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (Results == NULL) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      if (NULL == SctStrStr (Results, Request)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      gtBS->FreePool (Results);
    }
  } else if (EFI_OUT_OF_RESOURCES == Status) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigAccessBBTestFunctionAssertionGuid002,
                 L"HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig- ExtractConfig() returns EFI_SUCCESS and vaild Results with valid parameters .",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (MultiConfigAltResp);
  gtBS->FreePool (DevicePath);
  gtBS->FreePool (Request);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestExtractConfigFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting,
  IN EFI_HII_CONFIG_ACCESS_PROTOCOL             *HIIConfigAccess
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_STRING            Request = NULL;
  EFI_STRING            Progress = NULL;
  EFI_STRING            Results = NULL;
  EFI_STRING            MultiConfigAltResp = NULL;


  //init the Request
  Status = HIIConfigRouting->ExportConfig(
                               HIIConfigRouting,
                               &MultiConfigAltResp
                               );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Call ExtractConfig with valid parameters
  //
  Status = HIIConfigAccess->ExtractConfig(
                  HIIConfigAccess,
                  NULL,
                  &Progress,
                  &Results
                  );

  if (EFI_OUT_OF_RESOURCES == Status) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else if ((EFI_NOT_FOUND == Status) && (Progress == NULL) && (Results == NULL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    if (Results != NULL) {
      gtBS->FreePool (Results);
    }
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (Results == NULL) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigAccessBBTestFunctionAssertionGuid003,
                 L"HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig- ExtractConfig() returns EFI_SUCCESS or EFI_NOT_FOUND with Request been NULL .",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  if ( NULL != MultiConfigAltResp ){
    gtBS->FreePool (MultiConfigAltResp);
  }

  if ( NULL !=Results ) {
    gtBS->FreePool (Results);
  }

  if (NULL != Request) {
    gtBS->FreePool (Request);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestRouteConfigFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting,
  IN EFI_HII_CONFIG_ACCESS_PROTOCOL             *HIIConfigAccess
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_STRING            Resp = NULL;
  EFI_STRING            Progress = NULL;
  EFI_STRING            MultiConfigAltResp = NULL;
  EFI_STRING            DevicePath = NULL;

  //init the Request
  Status = HIIConfigRouting->ExportConfig(
                               HIIConfigRouting,
                               &MultiConfigAltResp
                               );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = GetDevicePath ( HIIConfigAccess, &DevicePath );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (MultiConfigAltResp);
    return Status;
  }

  Resp = (EFI_STRING) SctAllocateZeroPool ( 2 * SctStrLen (MultiConfigAltResp) + 2 );
  if (Resp == NULL) {
    gtBS->FreePool (MultiConfigAltResp);
    gtBS->FreePool (DevicePath);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = GetCorrespondingResp (MultiConfigAltResp, DevicePath, Resp);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (MultiConfigAltResp);
    gtBS->FreePool (DevicePath);
    gtBS->FreePool (Resp);
    return Status;
  }

  //
  // Call RouteConfig with valid parameters
  //
  Status = HIIConfigAccess->RouteConfig(
                 HIIConfigAccess,
                 Resp,
                 &Progress
                 );
  if ( (EFI_SUCCESS == Status) && (Progress == Resp + SctStrLen (Resp)) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ( EFI_OUT_OF_RESOURCES == Status ) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gHIIConfigAccessBBTestFunctionAssertionGuid003,
           L"HII_CONFIG_ACCESS_PROTOCOL.RouteConfig- RouteConfig() returns EFI_SUCCESS with valid parameters .",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  gtBS->FreePool (MultiConfigAltResp);
  gtBS->FreePool (DevicePath);
  gtBS->FreePool (Resp);

  return EFI_SUCCESS;
}
