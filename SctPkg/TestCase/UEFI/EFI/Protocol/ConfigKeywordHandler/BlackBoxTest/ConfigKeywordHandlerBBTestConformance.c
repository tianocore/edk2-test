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
                                                                
  Copyright 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

    ConfigKeywordHandlerBBTestConformance.c

Abstract:

    for EFI Driver Config Keyword Handler Protocol's Conformance Test

--*/

#include "ConfigKeywordHandlerBBTestMain.h"

extern EFI_HANDLE       mImageHandle;

EFI_STATUS
BBTestSetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_DEVICE_PATH_PROTOCOL               *FilePath;
  EFI_HANDLE                             ImageHandle;
  EFI_STATUS                             Status;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL    *ConfigKeywordHandler = NULL;
  EFI_STRING                             Progress = NULL;
  UINT32                                 ProgressErr = 0;

  EFI_STRING    KeywordString1      = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnableUefiSct&VALUE=00";
  EFI_STRING    KeywordString2      = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD12=iSCSIBootEnable&VALUE=00";
  EFI_STRING    ValidPartOfString12 = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400";  

  EFI_STRING    ROKeywordString            = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=ChipsetSATAPortEnable:2&VALUE=01";
  EFI_STRING    ValidPartOfROKeywordString = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400";

  ConfigKeywordHandler = (EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL*)ClientInterface;
  if (ConfigKeywordHandler == NULL)
  	return EFI_UNSUPPORTED;

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
  // Get the Profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = LoadedImageTestComposeSimpleFilePath (
              StandardLib,
              ProfileLib,
              mImageHandle,
              DRIVER_SAMPLE_NAME,
              &FilePath
              );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"LoadedImageTestComposeSimpleFilePath - compose driver files",
                   L"%a:%d:Status1:%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    
    return EFI_DEVICE_ERROR;
  }

  ImageHandle = NULL;
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   FilePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LoadImage()",
                   L"%a:%d:Status :%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  Status = gtBS->StartImage (ImageHandle, NULL, NULL);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.StartImage()",
                   L"%a:%d: Status: %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  Status = ConfigKeywordHandler->SetData (ConfigKeywordHandler, NULL, &Progress, &ProgressErr);
  if (EFI_INVALID_PARAMETER != Status)
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  else
  	AssertionType = EFI_TEST_ASSERTION_PASSED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid001 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.SetData - SetData() returns EFI_INVALID_PARAMETER when KeywordString is NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = ConfigKeywordHandler->SetData (ConfigKeywordHandler, KeywordString2, &Progress, &ProgressErr);
  if (EFI_INVALID_PARAMETER != Status || ProgressErr != KEYWORD_HANDLER_MALFORMED_STRING || Progress != KeywordString2 + SctStrLen(ValidPartOfString12))
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  else
  	AssertionType = EFI_TEST_ASSERTION_PASSED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid002 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.SetData - SetData() returns EFI_INVALID_PARAMETER when Parsing of the KeywordString resulted in an error and Progress points to the most recent '&' before the first failing string element.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = ConfigKeywordHandler->SetData (ConfigKeywordHandler, KeywordString1, &Progress, &ProgressErr);
  if (EFI_NOT_FOUND != Status || ProgressErr != KEYWORD_HANDLER_KEYWORD_NOT_FOUND || Progress != KeywordString1 + SctStrLen(ValidPartOfString12))
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  else
  	AssertionType = EFI_TEST_ASSERTION_PASSED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid003 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.SetData - SetData() returns EFI_NOT_FOUND when An element of the KeywordString was not found and Progress points to the most recent '&' before the first failing string element.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = ConfigKeywordHandler->SetData (ConfigKeywordHandler, ROKeywordString, &Progress, &ProgressErr);
  if (EFI_ACCESS_DENIED != Status || ProgressErr != KEYWORD_HANDLER_ACCESS_NOT_PERMITTED || Progress != ROKeywordString + SctStrLen(ValidPartOfROKeywordString))
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  else
  	AssertionType = EFI_TEST_ASSERTION_PASSED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid004 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.SetData - SetData() returns EFI_ACCESS_DENIED when the ReadOnly element is writen and Progress points to the most recent '&' before the first failing string element.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->UnloadImage (ImageHandle);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_DEVICE_PATH_PROTOCOL               *FilePath;
  EFI_HANDLE                             ImageHandle;
  EFI_STATUS                             Status, Status1, Status2, Status3;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL    *ConfigKeywordHandler = NULL;
  EFI_STRING                             Results = NULL;
  EFI_STRING                             Progress = NULL;
  UINT32                                 ProgressErr = 0;

  EFI_STRING    NameSpaceId         = L"NAMESPACE=x-UEFI-uefisct&";
  EFI_STRING    KeywordString1      = L"PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnableUefiSct";
  EFI_STRING    KeywordString2      = L"PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD12=iSCSIBootEnable";
  EFI_STRING    ValidPartOfString12 = L"PATH=01041400f4274aa000df424db55239511302113d7fff0400";  

  EFI_STRING    KeywordString3     = L"PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=ChipsetSATAPortDisable:1&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=ChipsetSATAPortEnable:2";
  EFI_STRING    ValidPartOfString3 = L"PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&PATH=01041400f4274aa000df424db55239511302113d7fff0400";
  EFI_STRING    ResultsOfString3   = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&VALUE=00";

  ConfigKeywordHandler = (EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL*)ClientInterface;
  if (ConfigKeywordHandler == NULL)
  	return EFI_UNSUPPORTED;

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
  // Get the Profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = LoadedImageTestComposeSimpleFilePath (
              StandardLib,
              ProfileLib,
              mImageHandle,
              DRIVER_SAMPLE_NAME,
              &FilePath
              );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"LoadedImageTestComposeSimpleFilePath - compose driver files",
                   L"%a:%d:Status1:%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    
    return EFI_DEVICE_ERROR;
  }

  ImageHandle = NULL;
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   FilePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LoadImage()",
                   L"%a:%d:Status :%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  Status = gtBS->StartImage (ImageHandle, NULL, NULL);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.StartImage()",
                   L"%a:%d: Status: %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  Status1 = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, NULL, NULL, &ProgressErr, &Results);
  Status2 = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, NULL, &Progress, NULL, &Results);
  Status3 = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, NULL, &Progress, &ProgressErr, NULL);
  if (Status1 != EFI_INVALID_PARAMETER || Status2 != EFI_INVALID_PARAMETER || Status3 != EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid005 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER when Progress, ProgressErr, or Resuts is NULL.",
                 L"%a:%d: Status1 - %r, Status2 - %r, Status3 - %r, expected - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1,
                 Status2,
                 Status3,
                 EFI_INVALID_PARAMETER
                 );

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, KeywordString2, &Progress, &ProgressErr, &Results);
  if (Status != EFI_INVALID_PARAMETER || ProgressErr != KEYWORD_HANDLER_MALFORMED_STRING || Progress != KeywordString2 + SctStrLen(ValidPartOfString12)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid006 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER when Parsing of the KeywordString resulted in an error and Progress points to the most recent '&' before the first failing string element.",
                 L"%a:%d: Status - %r, ProgressErr -%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ProgressErr
                 );

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, KeywordString1, &Progress, &ProgressErr, &Results);
  if (Status != EFI_NOT_FOUND || ProgressErr != KEYWORD_HANDLER_KEYWORD_NOT_FOUND || Progress != KeywordString1 + SctStrLen(ValidPartOfString12)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid007 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_NOT_FOUND when An element of the KeywordString was not found and Progress points to the most recent '&' before the first failing string element.",
                 L"%a:%d: Status - %r, ProgressErr -%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ProgressErr
                 );
  
  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NameSpaceId, NULL, &Progress, &ProgressErr, &Results);
  if (Status != EFI_NOT_FOUND || ProgressErr != KEYWORD_HANDLER_NAMESPACE_ID_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid008 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_NOT_FOUND when the NamespaceId specified was not found.",
                 L"%a:%d: Status - %r, ProgressErr -%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ProgressErr
                 );

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, KeywordString3, &Progress, &ProgressErr, &Results);
  if (Status != EFI_NOT_FOUND || ProgressErr != KEYWORD_HANDLER_KEYWORD_NOT_FOUND || Progress != KeywordString3 + SctStrLen(ValidPartOfString3)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestConformanceAssertionGuid009 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_NOT_FOUND when An element of the KeywordString was not found and Progress points to the most recent '&' before the first failing string element.",
                 L"%a:%d: Status - %r, ProgressErr -%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ProgressErr
                 );
  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    if (0 == SctStrnCmp (Results, ResultsOfString3, SctStrLen(ResultsOfString3)))
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigKeywordHandlerBBTestConformanceAssertionGuid010 ,
                   L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns Results string contains values returned for all keywords processed prior to the keyword generating the error.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  }
  if (Results != NULL)
    SctFreePool (Results);

  gtBS->UnloadImage (ImageHandle);

  return EFI_SUCCESS;  
}

