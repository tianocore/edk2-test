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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    HIIConfigRoutingBBTestConformance.c

Abstract:
    for EFI Driver HII Config Routing Protocol's Conformance Test

--*/

#include "HIIConfigRoutingBBTestMain.h"


EFI_STATUS
BBTestExtractConfigConformanceTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );
/*
EFI_STATUS
BBTestExtractConfigConformanceTestCheckpoint2 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );
*/
EFI_STATUS
BBTestExtractConfigConformanceTestCheckpoint3 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestExtractConfigConformanceTestCheckpoint4 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestExportConfigConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestRouteConfigConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestRouteConfigConformanceTestCheckpoint2( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestBlockToConfigConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestBlockToConfigConformanceTestCheckpoint2( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestBlockToConfigConformanceTestCheckpoint3( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestBlockToConfigConformanceTestCheckpoint4( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestConfigToBlockConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestConfigToBlockConformanceTestCheckpoint2( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestConfigToBlockConformanceTestCheckpoint3( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestConfigToBlockConformanceTestCheckpoint4( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestGetAltCfgConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestExtractConfigConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ROUTING_PROTOCOL       *HIIConfigRouting;

  //
  // init
  //
  HIIConfigRouting = (EFI_HII_CONFIG_ROUTING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestExtractConfigConformanceTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  //BBTestExtractConfigConformanceTestCheckpoint2( StandardLib, HIIConfigRouting );

  BBTestExtractConfigConformanceTestCheckpoint3( StandardLib, HIIConfigRouting );

  BBTestExtractConfigConformanceTestCheckpoint4( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestExportConfigConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ROUTING_PROTOCOL       *HIIConfigRouting;

  //
  // init
  //
  HIIConfigRouting = (EFI_HII_CONFIG_ROUTING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestExportConfigConformanceTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestRouteConfigConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ROUTING_PROTOCOL       *HIIConfigRouting;

  //
  // init
  //
  HIIConfigRouting = (EFI_HII_CONFIG_ROUTING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestRouteConfigConformanceTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  BBTestRouteConfigConformanceTestCheckpoint2( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestBlockToConfigConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ROUTING_PROTOCOL       *HIIConfigRouting;

  //
  // init
  //
  HIIConfigRouting = (EFI_HII_CONFIG_ROUTING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestBlockToConfigConformanceTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  BBTestBlockToConfigConformanceTestCheckpoint2( StandardLib, HIIConfigRouting );

  BBTestBlockToConfigConformanceTestCheckpoint3( StandardLib, HIIConfigRouting );

  BBTestBlockToConfigConformanceTestCheckpoint4( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestConfigToBlockConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ROUTING_PROTOCOL       *HIIConfigRouting;

  //
  // init
  //
  HIIConfigRouting = (EFI_HII_CONFIG_ROUTING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestConfigToBlockConformanceTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  BBTestConfigToBlockConformanceTestCheckpoint2( StandardLib, HIIConfigRouting );

  BBTestConfigToBlockConformanceTestCheckpoint3( StandardLib, HIIConfigRouting );

  BBTestConfigToBlockConformanceTestCheckpoint4( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetAltCfgConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ROUTING_PROTOCOL       *HIIConfigRouting;

  //
  // init
  //
  HIIConfigRouting = (EFI_HII_CONFIG_ROUTING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetAltCfgConformanceTestCheckpoint1( StandardLib, HIIConfigRouting );
  
//  BBTestConfigToBlockConformanceTestCheckpoint2( StandardLib, HIIConfigRouting );

//  BBTestConfigToBlockConformanceTestCheckpoint3( StandardLib, HIIConfigRouting );

//  BBTestConfigToBlockConformanceTestCheckpoint4( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

//
// Call ExtractConfig with Request or Progress being NULL, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestExtractConfigConformanceTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  EFI_STRING            Request;
  EFI_STRING            Progress;
  EFI_STRING            Results;
  EFI_TEST_ASSERTION    AssertionType;

  Progress = NULL;
  Results = NULL;

  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               NULL,
                               &Progress,
                               &Results
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid001,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_INVALID_PARAMETER with Request been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Request = L"GUID=970eb94aa0d449f7b980bdaa47d42526&NAME=006a0069006e0039&PATH=0acf&OFFSET=3&WIDTH=4";

  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               Request,
                               NULL,
                               &Results
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid002,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_INVALID_PARAMETER with Progress been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               Request,
                               &Progress,
                               NULL
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gHIIConfigRoutingBBTestConformanceAssertionGuid003,
           L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_INVALID_PARAMETER with Results been NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );
  
  return EFI_SUCCESS;

}

/*
//
// Call ExtractConfig with Illegal Syntax, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestExtractConfigConformanceTestCheckpoint2( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  EFI_STRING            Request;
  EFI_STRING            Progress;
  EFI_STRING            Results;
  EFI_TEST_ASSERTION    AssertionType;

  Request = L"GUID=970EB94AA0D449f7B980BDAA47D42527&NAME=006a0069006e0039&PATH=000acf&OFFSET=3&WIDTH=4";  //Guid should be the combination of <DecCh> | <HexAf>
  Progress = NULL;
  Results = NULL;
  
  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               Request,
                               &Progress,
                               &Results
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    if ( Progress != Request )
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    else
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid004,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_INVALID_PARAMETER with Illegal Syntax.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Request = L"GUID=970eb94aa0d449f7b980bdaa47d425278&NAME=006a0069006e0039&PATH=000acf&OFFSET=3&WIDTH=4";  //Guid should be <HexCh>32
  Progress = NULL;
  Results = NULL;
  
  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               Request,
                               &Progress,
                               &Results
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    if ( Progress != Request )
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    else
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid005,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_INVALID_PARAMETER with Illegal Syntax.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Request = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=0065in9&PATH=000acf&OFFSET=3&WIDTH=4";  //Name should be <HexCh>+
  Progress = NULL;
  Results = NULL;
  
  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               Request,
                               &Progress,
                               &Results
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    if ( (Progress[0] != L'&') &&(Progress[1] != L'N') )
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    else
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid006,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_INVALID_PARAMETER with Illegal Syntax.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

 
  return EFI_SUCCESS;
}
*/

//
// Call ExtractConfig with unknown driver, EFI_NOT_FOUND should be returned.
//
EFI_STATUS
BBTestExtractConfigConformanceTestCheckpoint3( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  EFI_STRING            Request;
  EFI_STRING            Progress;
  EFI_STRING            Results;
  EFI_TEST_ASSERTION    AssertionType;

  Request = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000acf&OFFSET=3&WIDTH=4";
  Progress = NULL;
  Results = NULL;

  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               Request,
                               &Progress,
                               &Results
                               );

  if ( EFI_NOT_FOUND != Status || Progress[0] != L'G') {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid007,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_NOT_FOUND with no know driver.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

//
// Call ExtractConfig with unknown name, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestExtractConfigConformanceTestCheckpoint4( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_TEST_ASSERTION    AssertionType;
  EFI_STATUS            Status;
  UINTN                 Len = 0;
  EFI_STRING            Resp = NULL;
  EFI_STRING            Request = NULL;
  EFI_STRING            Progress = NULL;
  EFI_STRING            Results = NULL;
  EFI_STRING            Pointer = NULL;

  Status = HIIConfigRouting->ExportConfig(
  	                           HIIConfigRouting,
  	                           &Resp
  	                           );

  if ( EFI_SUCCESS != Status )
  	return Status;

  Len = SctStrLen (Resp);

  Request = (EFI_STRING) SctAllocateZeroPool (2 * Len + 2);
  if (Request == NULL) {
  	gtBS->FreePool (Resp);
    return EFI_OUT_OF_RESOURCES;
  }
  
  //
  // <MultiConfigAltResp> to <MultiConfigRequest>
  //
  Status = MultiAltRespToMultiReq (Resp, Request);
  if (Status != EFI_SUCCESS) {
    gtBS->FreePool (Resp);
    gtBS->FreePool (Request);	
	return EFI_UNSUPPORTED;
  }
  
  Pointer = Request;
  while (*Pointer) {
  	Pointer++;
    if ( (*Pointer == L'&') && ( (SctStrnCmp (Pointer, L"&GUID=", 6) != 0) &&
      (SctStrnCmp (Pointer, L"&NAME=", 6) != 0) && (SctStrnCmp (Pointer, L"&PATH=", 6) != 0) ) ) {
      Pointer = Pointer + 1;
      (*Pointer)++;
      break;
	}	
  }
  
  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               Request,
                               &Progress,
                               &Results
                               );

  if ( (EFI_INVALID_PARAMETER != Status) || 
  	(Progress[0] != *(Pointer - 1) && Progress[0] != *Request)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid008,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_INVALID_PARAMETER with unknown name.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Resp);
  gtBS->FreePool (Request);
  
  return EFI_SUCCESS;
}

//
// Call ExportConfig with Results being NULL, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestExportConfigConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS             Status;
  EFI_TEST_ASSERTION     AssertionType;
  
  Status = HIIConfigRouting->ExportConfig(
                               HIIConfigRouting,
                               NULL
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid009,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExportConfig - ExportConfig() returns EFI_INVALID_PARAMETER with Results being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}


//
// Call RouteConfig with Configuration being NULL, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestRouteConfigConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  EFI_STRING            Progress;
  EFI_TEST_ASSERTION    AssertionType;

  Progress = NULL;
  
  Status = HIIConfigRouting->RouteConfig(
                               HIIConfigRouting,
                               NULL,
                               &Progress
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid010,
                 L"HII_CONFIG_ROUTING_PROTOCOL.RouteConfig - RouteConfig() returns EFI_INVALID_PARAMETER with Configuration being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}


//
// Call RouteConfig with no found target for the routing data, EFI_NOT_FOUND should be returned.
//
EFI_STATUS
BBTestRouteConfigConformanceTestCheckpoint2( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS             Status;
  EFI_STRING             Progress;
  EFI_STRING             Configuration;
  EFI_TEST_ASSERTION     AssertionType;

  Configuration = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000acf&OFFSET=2&WIDTH=4&VALUE=aa55&OFFSET=0&WIDTH=1&VALUE=55";
  Progress = NULL;
  
  Status = HIIConfigRouting->RouteConfig(
                               HIIConfigRouting,
                               Configuration,
                               &Progress
                               );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid011,
                 L"HII_CONFIG_ROUTING_PROTOCOL.RouteConfig - RouteConfig() returns EFI_NOT_FOUND with no found target for the routing data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

//
// Call BlockToConfig with ConfigRequest being NULL, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestBlockToConfigConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  UINT8                 Block[TESTBLOCKZISE];
  UINTN                 BlockSize;
  EFI_STRING            Config;
  EFI_STRING            Progress;
  EFI_TEST_ASSERTION    AssertionType;

  BlockSize = TESTBLOCKZISE;
  Config = NULL;
  Progress = NULL;
  
  Status = HIIConfigRouting->BlockToConfig(
                               HIIConfigRouting,
                               NULL,
                               Block,
                               BlockSize,
                               &Config, 
                               &Progress
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid012,
                 L"HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig() returns EFI_INVALID_PARAMETER with ConfigRequest being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

//
// Call BlockToConfig with Block being NULL, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestBlockToConfigConformanceTestCheckpoint2( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  EFI_STRING            ConfigRequest;
  UINTN                 BlockSize;
  EFI_STRING            Config;
  EFI_STRING            Progress;
  EFI_TEST_ASSERTION    AssertionType;

  BlockSize = TESTBLOCKZISE;
  Config = NULL;
  Progress = NULL;
  ConfigRequest =L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=928720&OFFSET=5&WIDTH=1&OFFSET=7&WIDTH=2&OFFSET=2&WIDTH=4&OFFSET=1&WIDTH=8";
 
  Status = HIIConfigRouting->BlockToConfig(
                               HIIConfigRouting,
                               ConfigRequest,
                               NULL,
                               BlockSize,
                               &Config, 
                               &Progress
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid013,
                 L"HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig() returns EFI_INVALID_PARAMETER with Block being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}


//
// Call BlockToConfig with ConfigRequest being not <BlockName> format, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestBlockToConfigConformanceTestCheckpoint3( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS    Status;
  EFI_STRING    ConfigRequest;
  UINT8         Block[TESTBLOCKZISE];
  UINTN         BlockSize;
  EFI_STRING    Config;
  EFI_STRING    Progress;

  EFI_TEST_ASSERTION    AssertionType;

  BlockSize = TESTBLOCKZISE;
  Config = NULL;
  Progress = NULL;

  ConfigRequest =L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=928720&OFFSET=5&WIDTH=1&OFFSET=7&WIDTH=2&a9";
  
  Status = HIIConfigRouting->BlockToConfig(
                               HIIConfigRouting,
                               ConfigRequest,
                               Block,
                               BlockSize,
                               &Config, 
                               &Progress
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    if ( (Progress[0] != L'&') || (Progress[1] != L'a') || (Progress[2] != L'9'))
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    else
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid014,
                 L"HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig() returns EFI_INVALID_PARAMETER with ConfigRequest being not <BlockName> format.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

//
// Call BlockToConfig with not large Block, EFI_DEVICE_ERROR should be returned.
//
EFI_STATUS
BBTestBlockToConfigConformanceTestCheckpoint4( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS    Status;
  EFI_STRING    ConfigRequest;
  UINTN         BlockSize;
  EFI_STRING    Config;
  EFI_STRING    Progress;

  EFI_TEST_ASSERTION    AssertionType;

  UINT8 Block[5] = {0x20, 0x30, 0xa6, 0x13, 0x53};
  BlockSize = 5;
  Config = NULL;
  Progress = NULL;
  
  ConfigRequest =L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=958720&OFFSET=5&WIDTH=1&OFFSET=7&WIDTH=2&OFFSET=2&WIDTH=4&OFFSET=1&WIDTH=8";
  
  Status = HIIConfigRouting->BlockToConfig(
                               HIIConfigRouting,
                               ConfigRequest,
                               Block,
                               BlockSize,
                               &Config, 
                               &Progress
                               );

  if ( EFI_DEVICE_ERROR != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid015,
                 L"HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig() returns EFI_DEVICE_ERROR with not large Block.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}


//
// Call ConfigToBlock with ConfigResp being NULL, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestConfigToBlockConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  UINT8                 Block[TESTBLOCKZISE];
  UINTN                 BlockSize;
  EFI_STRING            Progress;
  EFI_TEST_ASSERTION    AssertionType;

  BlockSize = TESTBLOCKZISE;
  Progress = NULL;
  
  Status = HIIConfigRouting->ConfigToBlock(
                               HIIConfigRouting,
                               NULL,
                               Block,
                               &BlockSize,
                               &Progress
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid016,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ConfigToBlock - ConfigToBlock() returns EFI_INVALID_PARAMETER with ConfigRequest being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

//
// Call ConfigToBlock with Block being NULL, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestConfigToBlockConformanceTestCheckpoint2( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  EFI_STRING            ConfigResp;
  UINTN                 BlockSize;
  EFI_STRING            Progress;
  EFI_TEST_ASSERTION    AssertionType;

  BlockSize = TESTBLOCKZISE;
  Progress = NULL;
  
  ConfigResp = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=928720&OFFSET=5&WIDTH=1&VALUE=57&OFFSET=7&WIDTH=2&VALUE=AA55&OFFSET=2&WIDTH=4&VALUE=77889900";
  
  Status = HIIConfigRouting->ConfigToBlock(
                               HIIConfigRouting,
                               ConfigResp,
                               NULL,
                               &BlockSize,
                               &Progress
                               );

  if ( (EFI_INVALID_PARAMETER) != Status  || (ConfigResp != Progress) ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid017,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ConfigToBlock - ConfigToBlock() returns EFI_INVALID_PARAMETER with Block being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

//
// Call BlockToConfig with ConfigRequest being not <BlockName> format, EFI_INVALID_PARAMETER should be returned.
//
EFI_STATUS
BBTestConfigToBlockConformanceTestCheckpoint3( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  EFI_STRING            ConfigResp;
  UINT8                 Block[TESTBLOCKZISE];
  UINTN                 BlockSize;
  EFI_STRING            Progress;
  EFI_TEST_ASSERTION    AssertionType;

  BlockSize = TESTBLOCKZISE;
  Progress = NULL;
  
  ConfigResp =L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=958720&OFFSET=5&WIDTH=1&VALUE=57&OFFSET=7&WIDTH=2&VALUE=AA55&a9=qin9";
  
  Status = HIIConfigRouting->ConfigToBlock(
                               HIIConfigRouting,
                               ConfigResp,
                               Block,
                               &BlockSize,
                               &Progress
                               );

  if ( (EFI_INVALID_PARAMETER != Status) || (SctStrnCmp (Progress, L"&a9=qin9", 8) != 0) || 
  	(Block[5] != 0x57) || (Block[7] != 0x55) || (Block[8] != 0xAA)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid018,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ConfigToBlock - ConfigToBlock() returns EFI_INVALID_PARAMETER with ConfigRequest being not <BlockName> format.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

//
// Call ConfigToBlock with Block being not large enough, EFI_DEVICE_ERROR should be returned.
//
EFI_STATUS
BBTestConfigToBlockConformanceTestCheckpoint4( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_STATUS            Status;
  EFI_STRING            ConfigResp;
  UINT8                 Block[TESTBLOCKZISE];
  UINTN                 BlockSize;
  EFI_STRING            Progress;
  EFI_TEST_ASSERTION    AssertionType;

  BlockSize = 5;
  Progress = NULL;

  ConfigResp = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=928720&OFFSET=5&WIDTH=1&VALUE=57&OFFSET=7&WIDTH=2&VALUE=AA55&OFFSET=2&WIDTH=4&VALUE=77889900";
  
  Status = HIIConfigRouting->ConfigToBlock(
                               HIIConfigRouting,
                               ConfigResp,
                               Block,
                               &BlockSize,
                               &Progress
                               );

  if ( EFI_BUFFER_TOO_SMALL != Status || BlockSize != 9) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid019,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ConfigToBlock - ConfigToBlock() returns EFI_BUFFER_TOO_SMALL with Block being not large enough.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetAltCfgConformanceTestCheckpoint1( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_TEST_ASSERTION          AssertionType;
  EFI_STATUS                  Status;
  EFI_STRING                  MultiAltResp;
  EFI_GUID                    Guid1 = { 0x4ab90e97, 0xd4a0, 0xf749, 0xb9, 0x80, 0xbd, 0xaa, 0x47, 0xd4, 0x25, 0x27};
  EFI_STRING                  NameDomain1 = L"006a0069006e0039";
  UINT16                      AltCfgId1 = EFI_HII_DEFAULT_CLASS_STANDARD;
  EFI_STRING                  AltCfgResp = NULL;

  MultiAltResp = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff&GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&ALTCFG=0000&A000=abcd&B000=efef&GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000acf&ALTCFG=0000&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff";


  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               NULL,
                               &Guid1,
                               NameDomain1,
                               NULL,
                               &AltCfgId1,
                               &AltCfgResp
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid020,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_INVALID_PARAMETER with ConfigResp being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               MultiAltResp,
                               &Guid1,
                               NameDomain1,
                               NULL,
                               &AltCfgId1,
                               NULL
                               );

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestConformanceAssertionGuid021,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_INVALID_PARAMETER with AltCfgResp being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  return EFI_SUCCESS;
}
