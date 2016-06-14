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

  CombinationTest.c

Abstract:

  for Image Boot Services' Combination Test

--*/

#include "SctLib.h"
#include "Misc.h"

/**
 *  @brief
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
BBTestImageServicesCombinationTest1 (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                              Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_DEVICE_PATH_PROTOCOL                *FilePath;
  EFI_HANDLE                              ImageHandle;
  EFI_EVENT                               EventArray[10];
  EFI_GUID                                *ProtGuidArray[10];
  IMAGE_TEST_NOTIFY_CONTEXT               NotifyContextArray[10];
  UINTN                                   Index;
  CHAR16                                  *ExitData;
  UINTN                                   ExitDataSize;

  UINTN                                   Numbers;

  //
  // Init
  //
  StandardLib = NULL;
  ImageHandle = NULL;
  ExitData = NULL;
  FilePath = NULL;

  gtBS->SetMem (EventArray, 10 * sizeof (EFI_EVENT), 0);
  gtBS->SetMem (NotifyContextArray, 10 * sizeof (IMAGE_TEST_NOTIFY_CONTEXT), 0);

  ProtGuidArray[0] = &mImageTestNoInterfaceProtocol1Guid;
  ProtGuidArray[1] = &mImageTestNoInterfaceProtocol2Guid;
  ProtGuidArray[2] = &mImageTestNoInterfaceProtocol3Guid;
  ProtGuidArray[3] = &mImageTestNoInterfaceProtocol4Guid;
  ProtGuidArray[4] = &mImageTestNoInterfaceProtocol5Guid;
  ProtGuidArray[5] = &mImageTestNoInterfaceProtocol6Guid;
  ProtGuidArray[6] = &mImageTestNoInterfaceProtocol7Guid;
  ProtGuidArray[7] = &mImageTestNoInterfaceProtocol8Guid;
  ProtGuidArray[8] = &mImageTestNoInterfaceProtocol9Guid;
  ProtGuidArray[9] = &mImageTestNoInterfaceProtocol10Guid;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestCheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             COMBINATION_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    gtBS->FreePool (FilePath);
    return Status;
  }

  for (Index = 0; Index < 10; Index++) {
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     ImageTestNotifyFunctionForCombinationTest1,
                     NotifyContextArray,
                     &EventArray[Index]
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
  }

  for (Index = 0; Index < 10; Index++) {
    Status = gtBS->RegisterProtocolNotify (
                     ProtGuidArray[Index],
                     EventArray[Index],
                     &NotifyContextArray[Index].Registration
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
  }
  //
  // load the image
  //
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   FilePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gCombinationTestAssertionGuid001,
                 L"BS.ImageTest - CombinationTest1",
                 L"%a:%d:LoadImage Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  //
  // start the image
  //
  Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gCombinationTestAssertionGuid002,
                 L"BS.ImageTest - CombinationTest1",
                 L"%a:%d:StartImage Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // check the events signal
  // each event should be signaled exactly once
  //
  for (Index = 0; Index < 10; Index++) {
    if (1 == NotifyContextArray[Index].NotifyTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gCombinationTestAssertionGuid003,
                   L"BS.ImageTest - CombinationTest1",
                   L"%a:%d:Index - %d, NotifyTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index,
                   NotifyContextArray[Index].NotifyTimes
                   );
  }

Done:

  if (ImageHandle != NULL) {
    gtBS->UnloadImage (ImageHandle);
  }

  if (ExitData != NULL) {
    gtBS->FreePool (ExitData);
  }

  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  for (Index = 0; Index < 10; Index++) {
    if (EventArray[Index] != NULL) {
      gtBS->CloseEvent (EventArray[Index]);
    }
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestCheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return EFI_SUCCESS;
}