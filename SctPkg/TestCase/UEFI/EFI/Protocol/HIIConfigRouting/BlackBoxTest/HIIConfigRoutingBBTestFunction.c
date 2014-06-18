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
    HIIConfigRoutingBBTestFunction.c

Abstract:
    for EFI Driver HII Config Routing Protocol's Function Test

--*/

#include "HIIConfigRoutingBBTestMain.h"

EFI_STATUS
BBTestExtractConfigFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestExportConfigFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestRouteConfigFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestBlockToConfigFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestConfigToBlockFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

EFI_STATUS
BBTestGetAltCfgFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  );

/*
EFI_STATUS
BBTestUnitAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS            Status;
  UINTN                 Len;
  EFI_STRING            MultiAltResp;
  EFI_STRING            MultiRequest = NULL;
  EFI_STRING            MultiResp = NULL;
  EFI_STRING            Request = NULL;
  EFI_STRING            Resp = NULL;

  //MultiAltResp = L"GUID=970EB94AA0D449f7B980BDAA47D42528&NAME=ft894&PATH=0acf&A000=ABCD&B000=EFGH&GUID=970EB94AA0D449f7B980BDAA47D42528&NAME=ft894&PATH=0acf&ALTCFG=0037&OFFSET=3&WIDTH=4&VALUE=AABBCCDD&OFFSET=1&WIDTH=2&VALUE=EEFF";
  //MultiAltResp = L"GUID=970EB94AA0D449f7B980BDAA47D42527&NAME=ft894&PATH=0acf&OFFSET=3&WIDTH=4&VALUE=AABBCCDD&OFFSET=1&WIDTH=2&VALUE=EEFF&GUID=970EB94AA0D449f7B980BDAA47D42527&NAME=ft894&PATH=0acf&ALTCFG=0037&A000=ABCD&B000=EFGH";
  //MultiAltResp = L"GUID=970EB94AA0D449f7B980BDAA47D42528&NAME=ft894&PATH=0acf&A000=ABCD&B000=EFGH&GUID=970EB94AA0D449f7B980BDAA47D42528&NAME=ft894&PATH=0acf&ALTCFG=0037&OFFSET=3&WIDTH=4&VALUE=AABBCCDD&OFFSET=1&WIDTH=2&VALUE=EEFF&GUID=970EB94AA0D449f7B980BDAA47D42527&NAME=ft894&PATH=0acf&OFFSET=3&WIDTH=4&VALUE=AABBCCDD&OFFSET=1&WIDTH=2&VALUE=EEFF&GUID=970EB94AA0D449f7B980BDAA47D42527&NAME=ft894&PATH=0acf&ALTCFG=0037&A000=ABCD&B000=EFGH";
  MultiAltResp = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000acf&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff&GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000acf&ALTCFG=0037&A000=abcd&B000=efef&GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0039&PATH=000acf&A000=abcd&B000=efef&GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0039&PATH=000acf&ALTCFG=0037&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff";
  Len = SctStrLen (MultiAltResp);

  MultiRequest = (EFI_STRING) SctAllocateZeroPool ( 2 * Len + 2);
  if (MultiRequest == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  MultiResp = (EFI_STRING) SctAllocateZeroPool ( 2 * Len + 2);
  if (MultiResp == NULL) {
  	SctFreePool (MultiRequest);
    return EFI_OUT_OF_RESOURCES;
  }  

  Request = (EFI_STRING) SctAllocateZeroPool ( 2 * Len + 2);
  if (Request == NULL) {
  	SctFreePool (MultiRequest);
    SctFreePool (MultiResp);
    return EFI_OUT_OF_RESOURCES;
  }  

  Resp = (EFI_STRING) SctAllocateZeroPool ( 2 * Len + 2);
  if (Resp == NULL) {
  	SctFreePool (MultiRequest);
  	SctFreePool (MultiResp);
    SctFreePool (Request);
    return EFI_OUT_OF_RESOURCES;
  }  

  // <MultiConfigAltResp> to <MultiConfigRequest>
  Status = MultiAltRespToMultiReq (MultiAltResp, MultiRequest);
  
  // <MultiConfigAltResp> to <MultiConfigResp>
  Status = MultiAltRespToMultiResp (MultiAltResp, MultiResp);

  // <MultiConfigAltResp> to <ConfigReq>
  Status = MultiAltRespToReq (MultiAltResp, Request);

  // <MultiConfigAltResp> to <ConfigResp>
  Status = MultiAltRespToResp (MultiAltResp, Resp);  

  SctFreePool (MultiRequest);
  SctFreePool (MultiResp);
  SctFreePool (Request);
  SctFreePool (Resp);
  
  return Status;
}
*/

EFI_STATUS
BBTestExtractConfigFunctionAutoTest (
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
  BBTestExtractConfigFunctionTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestExportConfigFunctionAutoTest (
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
  BBTestExportConfigFunctionTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestRouteConfigFunctionAutoTest (
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
  BBTestRouteConfigFunctionTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestBlockToConfigFunctionAutoTest (
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
  BBTestBlockToConfigFunctionTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestConfigToBlockFunctionAutoTest (
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
  BBTestConfigToBlockFunctionTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetAltCfgFunctionAutoTest (
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
  BBTestGetAltCfgFunctionTestCheckpoint1( StandardLib, HIIConfigRouting );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestExtractConfigFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_TEST_ASSERTION    AssertionType;
  EFI_STATUS            Status;
  UINTN                 Len = 0;
  EFI_STRING            MultiConfigAltResp = NULL;
  EFI_STRING            Request = NULL;
  EFI_STRING            Progress = NULL;
  EFI_STRING            Results = NULL;

  Status = HIIConfigRouting->ExportConfig(
                              HIIConfigRouting,
                              &MultiConfigAltResp
                              );

  if ( EFI_SUCCESS != Status ) {
    return Status;
  }
  
  Len = SctStrLen (MultiConfigAltResp);

  Request = (EFI_STRING) SctAllocateZeroPool (2 * Len + 2);
  if (Request == NULL) {
    goto FUNC_EXIT;
  }
  
  //
  // <MultiConfigAltResp> to <MultiConfigRequest>
  //
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
//  if ( (EFI_SUCCESS == Status) && (Progress == Request + SctStrLen (Request)) && (0 == SctStrCmp (Results, Resp)) ) {
  if ( (EFI_SUCCESS == Status) && (Progress == Request + SctStrLen (Request)) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid001,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() returns EFI_SUCCESS with no NULL Results.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // 
  // Since ExtractConfig may not append <AltResp> at string tail.  
  // We check whether Results is a substring of MultiConfigAltResp from ExportConfig 
  //
  if (Status == EFI_SUCCESS && (SctStrStr (MultiConfigAltResp, Results) != NULL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (EFI_OUT_OF_RESOURCES == Status){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid011,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig - ExtractConfig() Check if Results is in <MultiConfigAltResp> format.",
                 L"%a:%d:",
                 __FILE__,
                 (UINTN)__LINE__
                 );

FUNC_EXIT:

  if (Request != NULL) {
    gtBS->FreePool (Request);
  }

  if (MultiConfigAltResp != NULL) {
    gtBS->FreePool (MultiConfigAltResp);
  }

  if (Results != NULL) {
    gtBS->FreePool (Results);
  }

  return EFI_SUCCESS;

}


EFI_STATUS
BBTestExportConfigFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_TEST_ASSERTION    AssertionType;
  EFI_STATUS            Status, StatusConvert;
  UINTN                 Len = 0;
  EFI_STRING            MultiConfigAltResp = NULL;
  EFI_STRING            Request = NULL;

  Status = HIIConfigRouting->ExportConfig(
                               HIIConfigRouting,
                               &MultiConfigAltResp
                               );


  if (EFI_SUCCESS == Status) {
    Len = SctStrLen (MultiConfigAltResp);
  
    Request = (EFI_STRING) SctAllocateZeroPool (2 * Len + 2);
    if (Request == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    
    //
    // <MultiConfigAltResp> to <MultiConfigRequest>
    //
    StatusConvert = MultiAltRespToMultiReq (MultiConfigAltResp, Request);

    gtBS->FreePool (Request);
  }
  
  if ( EFI_SUCCESS == Status ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid002,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ExportConfig - ExportConfig() returns EFI_SUCCESS with no NULL Results.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  if (NULL != MultiConfigAltResp) {
    gtBS->FreePool (MultiConfigAltResp);
  }
  
  return EFI_SUCCESS;

}

EFI_STATUS
BBTestRouteConfigFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_TEST_ASSERTION     AssertionType;
  EFI_STATUS             Status;
  EFI_STRING             Resp1 = NULL;
  EFI_STRING             Resp2 = NULL;
  EFI_STRING             Progress = NULL;
  UINTN                  Len = 0;

  Status = HIIConfigRouting->ExportConfig(
                               HIIConfigRouting,
                               &Resp1
                               );

  if ( EFI_SUCCESS != Status ) {
    return EFI_OUT_OF_RESOURCES;
  }
  
  Len = SctStrLen (Resp1);

  Resp2 = (EFI_STRING) SctAllocateZeroPool (2 * Len + 2);
  if (Resp2 == NULL) {
    gtBS->FreePool (Resp1);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // <MultiConfigAltResp> to <MultiConfigResp>
  //
  Status = MultiAltRespToMultiResp (Resp1, Resp2);
  if (Status != EFI_SUCCESS) {
    gtBS->FreePool (Resp1);
    gtBS->FreePool (Resp2);  
    return EFI_UNSUPPORTED;
  }

  Status = HIIConfigRouting->RouteConfig(
                               HIIConfigRouting,
                               Resp2,
                               &Progress
                               );

  if ( (EFI_SUCCESS == Status) && (Progress == Resp2 + SctStrLen (Resp2)) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid003,
                 L"HII_CONFIG_ROUTING_PROTOCOL.RouteConfig - RouteConfig() returns EFI_SUCCESS with valid input.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Resp1);
  gtBS->FreePool (Resp2);
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestBlockToConfigFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{

  EFI_TEST_ASSERTION    AssertionType;
  EFI_STATUS            Status;
  EFI_STRING            Req;
  EFI_STRING            Config = NULL;
  EFI_STRING            Progress = NULL; 
  UINT8                 Block[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  UINTN                 BlockSize = 6;

  Req = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000acf&OFFSET=3&WIDTH=1&OFFSET=0&WIDTH=2";

  Status = HIIConfigRouting->BlockToConfig(
                               HIIConfigRouting,
                               Req,
                               Block,
                               BlockSize,
                               &Config,
                               &Progress
                               );

  if ( EFI_SUCCESS == Status ) {
    if ((Progress != (Req + SctStrLen (Req))) || 
        (NULL == SctStrStr (Config, L"OFFSET=3&WIDTH=1&VALUE=03")) ||
        (NULL == SctStrStr (Config, L"OFFSET=0&WIDTH=2&VALUE=0100")) ){
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      gtBS->FreePool (Config);
    }
  } else if ( (EFI_OUT_OF_RESOURCES == Status) && (Progress == Req) ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid004,
                 L"HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig() returns EFI_SUCCESS with valid input.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestConfigToBlockFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{

  EFI_TEST_ASSERTION    AssertionType;
  EFI_STATUS            Status;
  EFI_STRING            Resp;
  EFI_STRING            Progress = NULL; 
  UINT8                 Block[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  UINTN                 BlockSize = 6;

  Resp = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000acf&OFFSET=3&WIDTH=1&VALUE=7&OFFSET=0&WIDTH=2&VALUE=aa55";

  Status = HIIConfigRouting->ConfigToBlock(
                               HIIConfigRouting,
                               Resp,
                               Block,
                               &BlockSize,
                               &Progress
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if ((Block[0] != 0x55) || (Block[1] != 0xAA) || (Block[2] != 0x02) ||
        (Block[3] != 0x07) || (Block[4] != 0x04) || (Block[5] != 0x05) || (BlockSize != 3) ||(Progress != (Resp + SctStrLen (Resp))))
      AssertionType = EFI_TEST_ASSERTION_FAILED;
     else
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ( (EFI_OUT_OF_RESOURCES == Status) && (Progress == Resp) ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid005,
                 L"HII_CONFIG_ROUTING_PROTOCOL.ConfigToBlock - ConfigToBlock() returns EFI_SUCCESS with valid input.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetAltCfgFunctionTestCheckpoint1 ( 
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_CONFIG_ROUTING_PROTOCOL            *HIIConfigRouting
  )
{
  EFI_TEST_ASSERTION          AssertionType;
  EFI_STATUS                  Status;
  EFI_STRING                  ConfigAltResp;
  EFI_GUID                    Guid1 = { 0x4ab90e97, 0xd4a0, 0xf749, 0xb9, 0x80, 0xbd, 0xaa, 0x47, 0xd4, 0x25, 0x27};
  EFI_GUID                    Guid2 = { 0x4ab90e97, 0xd4a0, 0xf749, 0xb9, 0x80, 0xbd, 0xaa, 0x47, 0xd4, 0x25, 0x28};
  EFI_STRING                  NameDomain1 = L"jin9"; //L"006a0069006e0039";
  EFI_STRING                  NameDomain2 = L"jin8"; //L"006a0069006e0038";
  UINT16                      AltCfgId1 = EFI_HII_DEFAULT_CLASS_STANDARD;
  UINT16                      AltCfgId2 = EFI_HII_DEFAULT_CLASS_MANUFACTURING;
  EFI_STRING                  CfgResp = NULL;

  ConfigAltResp = L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=1122&GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&ALTCFG=0000&a000=abcd&b000=efef&GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0038&PATH=000acf&ALTCFG=0001&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff";
  // GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff
  //&GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&ALTCFG=0037&a000=abcd&b000=efef
  //&GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0038&PATH=000acf&a000=abcd&b000=efef
  //&GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0038&PATH=000acf&ALTCFG=0038&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff

  // Check All are NULL, except AltcfgId
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               NULL,
                               NULL,
                               NULL,
                               &AltCfgId1,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&a000=abcd&b000=efef")){
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    
    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }

  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid006,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid AltcfgId1.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check Guid1
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               &Guid1,
                               NULL,
                               NULL,
                               &AltCfgId1,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&a000=abcd&b000=efef")){
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    
    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid007,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid Guid1 and AltcfgId1.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check NameDomain1
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               NULL,
                               NameDomain1,
                               NULL,
                               &AltCfgId1,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&a000=abcd&b000=efef")) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid008,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid Name1 and AltcfgId1.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check NameDomain1 and Guid1
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               &Guid1,
                               NameDomain1,
                               NULL,
                               &AltCfgId1,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&a000=abcd&b000=efef")) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid009,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid Guid1, Name1, and AltCfgId1.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check NameDomain1 and Guid1, with AltCfgId is NULL
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               &Guid1,
                               NameDomain1,
                               NULL,
                               NULL,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=1122")) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    
    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid010,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid Guid1 and Name1.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check NameDomain1 only
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               NULL,
                               NameDomain1,
                               NULL,
                               NULL,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42527&NAME=006a0069006e0039&PATH=000ace&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=1122")) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    
    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid012,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid Name1.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  

  /****************************************************************************************/
  //
  // Check All are NULL, except AltcfgId
  // current setting will be returned
  //
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               NULL,
                               NULL,
                               NULL,
                               &AltCfgId2,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0038&PATH=000acf&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff")) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid006,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid AltcfgId2.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check Guid2
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               &Guid2,
                               NULL,
                               NULL,
                               &AltCfgId2,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0038&PATH=000acf&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff")){
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid007,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid Guid2 and AltcfgId2.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check NameDomain2
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               NULL,
                               NameDomain2,
                               NULL,
                               &AltCfgId2,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0038&PATH=000acf&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff")) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid008,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid Name2 and AltcfgId2.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check NameDomain2 and Guid2
  Status = HIIConfigRouting->GetAltCfg(
                               HIIConfigRouting,
                               ConfigAltResp,
                               &Guid2,
                               NameDomain2,
                               NULL,
                               &AltCfgId2,
                               &CfgResp
                               );
  
  if ( EFI_SUCCESS == Status ) {
    if (0 != SctStrCmp (CfgResp, L"GUID=970eb94aa0d449f7b980bdaa47d42528&NAME=006a0069006e0038&PATH=000acf&OFFSET=3&WIDTH=4&VALUE=aabbccdd&OFFSET=1&WIDTH=2&VALUE=eeff")) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if (CfgResp != NULL) {
      gtBS->FreePool (CfgResp);
      CfgResp = NULL;
    }
  } else if ( EFI_OUT_OF_RESOURCES == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIConfigRoutingBBTestFunctionAssertionGuid009,
                 L"HII_CONFIG_ROUTING_PROTOCOL.GetAltCfg - GetAltCfg() returns EFI_SUCCESS with valid Guid2, Name2 and AltcfgId2.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}
