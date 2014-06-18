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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
/*
EFI_STATUS
BBTestCallBackFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ACCESS_PROTOCOL             *HIIConfigAccess
  );
*/

//
//Test Cases
//
/*
EFI_STATUS
BBTestUnitTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ACCESS_PROTOCOL        *HIIConfigAccess;
  EFI_STRING                            DevicePath = NULL;
  EFI_STRING    Request = NULL;
  EFI_STRING    Resp = NULL;
  EFI_STRING    MultiConfigAltResp = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=ft894&PATH=000acf&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff&GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=ft894&PATH=000acf&ALTCFG=0037&A000=abcd&B000=efef&GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=ft894&PATH=0104180035170b0fa0879341b266538c38af48ce000000007fff0400&A000=abcd&B000=efef&GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=ft894&PATH=0104180035170b0fa0879341b266538c38af48ce000000007fff0400&ALTCFG=0037&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff";;

  //
  // init
  //
  HIIConfigAccess = (EFI_HII_CONFIG_ACCESS_PROTOCOL*)ClientInterface;

  Request = (EFI_STRING) SctAllocateZeroPool (2 * SctStrLen (MultiConfigAltResp) + 2);
  if (Request == NULL)
  	return EFI_OUT_OF_RESOURCES;

  Resp = (EFI_STRING) SctAllocateZeroPool (2 * SctStrLen (MultiConfigAltResp) + 2);
  if (Resp == NULL) {
  	gtBS->FreePool (Request);
  	return EFI_OUT_OF_RESOURCES;
  }

  Status = GetDevicePath ( HIIConfigAccess, &DevicePath );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Resp);  
  	gtBS->FreePool (Request);
    return Status;
  }
  
  Status = GetCorrespondingRequest (MultiConfigAltResp, DevicePath, Request);

  Status = GetCorrespondingResp (MultiConfigAltResp, DevicePath, Resp);

  gtBS->FreePool (Request);
  gtBS->FreePool (Resp);
  gtBS->FreePool (DevicePath);

  return EFI_SUCCESS;
}
*/

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
                   &StandardLib
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
                   &StandardLib
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

/*
EFI_STATUS
BBTestCallBackFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_CONFIG_ACCESS_PROTOCOL        *HIIConfigAccess;
  
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
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  
  //
  //Call check points
  //
  BBTestCallBackFunctionTestCheckpoint1( StandardLib, HIIConfigAccess );
  
  return EFI_SUCCESS;
}
*/

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
      if (NULL == SctStrStr (MultiConfigAltResp, Results)) {
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
                 gHIIConfigAccessBBTestFunctionAssertionGuid001,
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

  UINTN                 Len = 0;
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

  if ( EFI_OUT_OF_RESOURCES == Status) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;  
  } else if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    if (Results != NULL) {
      gtBS->FreePool (Results);
    }
    return Status;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if ( (Results != NULL) && (NULL == SctStrStr (MultiConfigAltResp, Results)) ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigAccessBBTestFunctionAssertionGuid002,
                 L"HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig- ExtractConfig() returns EFI_SUCCESS with Request been NULL .",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );



  //
  // build <MultiConfigRequest> out of <MultiConfigAltResp> 
  //
  Len = SctStrLen (MultiConfigAltResp);
  Request = (EFI_STRING) SctAllocateZeroPool (2 * Len + 2);
  if (Request == NULL) {
    goto FUNC_EXIT;
  }
 

  Status = MultiAltRespToMultiReq (MultiConfigAltResp, Request);
  if (Status != EFI_SUCCESS) {
    goto FUNC_EXIT;
  }

  Status = HIIConfigRouting->ExtractConfig(
                               HIIConfigRouting,
                               Request,
                               &Progress,
                               &Results
                               );
  // 
  // Since ExtractConfig may not append <AltResp> at string tail.  
  // We check whether Results is a substring of MultiConfigAltResp from ExportConfig 
  //
  if (Status == EFI_SUCCESS && SctStrStr (MultiConfigAltResp, Results) != NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (EFI_OUT_OF_RESOURCES == Status){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigAccessBBTestFunctionAssertionGuid004,
                 L"HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig - ExtractConfig() Check if Results is in <MultiConfigAltResp> format.",
                 L"%a:%d:",
                 __FILE__,
                 (UINTN)__LINE__
                 );
   

FUNC_EXIT:

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

/*
EFI_STATUS
BBTestCallBackFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ACCESS_PROTOCOL             *HIIConfigAccess
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  
  EFI_BROWSER_ACTION                             *Action;
  EFI_QUESTION_ID                                QuestionId;
  UINT8                                          Type;
  EFI_IFR_TYPE_VALUE                             Value;
  EFI_BROWSER_ACTION_REQUEST                     ActionRequest;
  
  //init the paremeters
  Action=EFI_BROWSER_ACTION_REQUEST_CHANGING;
  QuestionId=0x1234;
  Type=EFI_IFR_TYPE_NUM_SIZE_8;
  
  
  //
  // Call CallBack  with valid parameters
  //
  Status = HIIConfigAccess->CallBack(
                 HIIConfigAccess,
                 Action,
                 QuestionId,
				 Type,
				 &Value,
				 &ActionRequest
                 );
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
	
	//check the output ActionRequest
  if ((EFI_BROWSER_ACTION_REQUEST_NONE || EFI_BROWSER_ACTION_REQUEST_RESET || EFI_BROWSER_ACTION_REQUEST_SUBMIT || EFI_BROWSER_ACTION_REQUEST_EXIT) != ActionRequest)
	AssertionType = EFI_TEST_ASSERTION_FAILED;
    
  }
  
 
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gHIIConfigAccessBBTestFunctionAssertionGuid003,
           L"HII_CONFIG_ACCESS_PROTOCOL.CallBack- CallBack() returns EFI_SUCCESS with valid parameters .",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );
  return EFI_SUCCESS;
} 
*/


