/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
EFIAPI
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