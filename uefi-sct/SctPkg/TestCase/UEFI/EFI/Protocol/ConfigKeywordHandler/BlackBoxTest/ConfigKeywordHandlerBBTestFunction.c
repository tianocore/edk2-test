/** @file

  Copyright 2016 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    ConfigKeywordHandlerBBTestFunction.c

Abstract:

    for EFI Driver Config Keyword Handler Protocol's Function Test

--*/

#include "ConfigKeywordHandlerBBTestMain.h"

extern CONST EFI_STRING FullStr;
extern EFI_HANDLE       mImageHandle;

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTest (
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
  EFI_STRING                             Results = NULL;  
  EFI_STRING                             Progress = NULL;
  UINT32                                 ProgressErr = 0;

  EFI_STRING    KeywordString1     = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&VALUE=01&NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=ChipsetSATAPortDisable:1&VALUE=01";
  EFI_STRING    ValidPartOfString1 = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&VALUE=01&NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400";

  EFI_STRING    KeywordString2       = L"PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable";
  EFI_STRING    RespOfKeywordString2 = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&VALUE=00";

  EFI_STRING    KeywordString3          = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&VALUE=00&NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=ChipsetSATAPortEnable:1&VALUE=01";
  EFI_STRING    RequestOfKeywordString3 = L"PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=ChipsetSATAPortEnable:1";

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

  Status = ConfigKeywordHandler->SetData (ConfigKeywordHandler, KeywordString1, &Progress, &ProgressErr);
  if (EFI_NOT_FOUND != Status || ProgressErr != KEYWORD_HANDLER_KEYWORD_NOT_FOUND || Progress != KeywordString1 + SctStrLen(ValidPartOfString1))
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  else
  	AssertionType = EFI_TEST_ASSERTION_PASSED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestFunctionAssertionGuid001 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.SetData - SetData() returns EFI_NOT_FOUND when an element of the KeywordString was not found and Progress points to the most recent '&' before the first failing string element.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, KeywordString2, &Progress, &ProgressErr, &Results);
  if (Status == EFI_SUCCESS && Progress == KeywordString2 + SctStrLen(KeywordString2) && ProgressErr == KEYWORD_HANDLER_NO_ERROR && 0 == SctStrCmp(RespOfKeywordString2, Results))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestFunctionAssertionGuid002 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.SetData - SetData() the system storage associated with earlier keywords is not modified when an EFI_NOT_FOUND error is generated during processing the second or later keyword element.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  if (Results) {
    SctFreePool (Results);
    Results = NULL;
  }

  Status = ConfigKeywordHandler->SetData (ConfigKeywordHandler, KeywordString3, &Progress, &ProgressErr);
  if (Status == EFI_SUCCESS && Progress == KeywordString3 + SctStrLen(KeywordString3) && ProgressErr == KEYWORD_HANDLER_NO_ERROR)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;  

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestFunctionAssertionGuid003 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.SetData - SetData() should be successful and with correct behavior and Progress points to the request string's NULL terminator.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, RequestOfKeywordString3, &Progress, &ProgressErr, &Results);
  if (Status == EFI_SUCCESS && Progress == RequestOfKeywordString3 + SctStrLen(RequestOfKeywordString3) && ProgressErr == KEYWORD_HANDLER_NO_ERROR && 0 != SctStrStr(FullStr, Results))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestFunctionAssertionGuid004 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.SetData - SetData() should save the data correctly.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Results) {
    SctFreePool (Results);
    Results = NULL;
  }

  Status = gtBS->UnloadImage (ImageHandle);

  return Status;
}


EFI_STATUS
EFIAPI
BBTestGetDataFunctionTest (
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
  EFI_STRING                             Results     = NULL;
  EFI_STRING                             Progress    = NULL;
  UINT32                                 ProgressErr = 0;
  
  EFI_STRING                             Results1 = NULL;
  EFI_STRING                             Results2 = NULL;
  EFI_STRING                             KeywordString1 = L"PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable";
  EFI_STRING                             KeywordString2 = L"KEYWORD=iSCSIBootEnable";


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

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, NULL, NULL, &Progress, &ProgressErr, &Results);
  if (Status != EFI_SUCCESS || ProgressErr != KEYWORD_HANDLER_NO_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestFunctionAssertionGuid005 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_SUCCESS when KeywordString and NameSpaceId are NULL.",
                 L"%a:%d: Status - %r, ProgressErr - %x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ProgressErr
                 );
  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    if (NULL != SctStrStr (Results, FullStr))
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigKeywordHandlerBBTestFunctionAssertionGuid006 ,
                   L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - The preinstalled Str should be included in the Results outputted from the GetData().",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  }

  if (Results) {
    SctFreePool(Results);
    Results = NULL;
  }

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, L"NAMESPACE=x-UEFI-ns&", NULL, &Progress, &ProgressErr, &Results);
  if (Status != EFI_SUCCESS || ProgressErr != KEYWORD_HANDLER_NO_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestFunctionAssertionGuid007 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_SUCCESS when KeywordString is NULL and NameSpaceId is one vaild expression.",
                 L"%a:%d: Status - %r, ProgressErr - %x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ProgressErr
                 );

  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    if (NULL != SctStrStr (Results, FullStr))
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigKeywordHandlerBBTestFunctionAssertionGuid008 ,
                   L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - The preinstalled Str should be in the Results outputted from the GetData().",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  }

  if (Results) {
    SctFreePool(Results);
    Results = NULL;
  }

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, L"NAMESPACE=x-UEFI-ns&", KeywordString1, &Progress, &ProgressErr, &Results1);
  if (Status != EFI_SUCCESS || ProgressErr != KEYWORD_HANDLER_NO_ERROR || Progress != KeywordString1 + SctStrLen(KeywordString1)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestFunctionAssertionGuid009 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_SUCCESS when KeywordString is the vaild expression(with PathHdr) and NameSpaceId is one vaild expression.",
                 L"%a:%d: Status - %r, ProgressErr - %x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ProgressErr
                 );

  Status = ConfigKeywordHandler->GetData (ConfigKeywordHandler, L"NAMESPACE=x-UEFI-ns&", KeywordString2, &Progress, &ProgressErr, &Results2);
  if (Status != EFI_SUCCESS || ProgressErr != KEYWORD_HANDLER_NO_ERROR || Progress != KeywordString2 + SctStrLen(KeywordString2)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigKeywordHandlerBBTestFunctionAssertionGuid010 ,
                 L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - GetData() returns EFI_SUCCESS when KeywordString is the vaild expression(without PathHdr) and NameSpaceId is one vaild expression.",
                 L"%a:%d: Status - %r, ProgressErr - %x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ProgressErr
                 );

  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    if (NULL != SctStrStr (Results2, Results1))
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigKeywordHandlerBBTestFunctionAssertionGuid011 ,
                   L"CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData - The Results outputted with PathHdr should be included in the Results outputted without PathHdr.",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );  
  }

  if (Results1) {
    SctFreePool(Results1);
    Results1 = NULL;
  }

  if (Results2) {
    SctFreePool(Results2);
    Results2 = NULL;
  }

  Status = gtBS->UnloadImage (ImageHandle);
  
  return Status;  
}
