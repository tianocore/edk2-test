/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ImageBBTestConformance.c

Abstract:

  for Image Boot Services' Consistency Test

--*/

#include "SctLib.h"
#include "Misc.h"

#define TEST_VENDOR1_GUID                         \
  { 0xF6FAB04F, 0xACAF, 0x4af3, { 0xB9, 0xFA, 0xDC, 0xF9, 0x7F, 0xB4, 0x42, 0x6F } }

#define STATUS_BUFFER_SIZE   8
#define RECOVER_BUFFER_SIZE  1024

EFI_GUID gTestVendor1Guid = TEST_VENDOR1_GUID;

/**
 *  @brief Entrypoint for gtBS->LoadImage() Consistency Test.
 *         4 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestLoadImageConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           ParentImageHandle[3];
  CHAR16                               *FileName;
  EFI_DEVICE_PATH_PROTOCOL             *ValidFilePath;
  UINTN                                Index;
  EFI_HANDLE                           ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL             *IrrelevantFilePath;
  EFI_DEVICE_PATH_PROTOCOL             *NonExistentDevicePath;
  UINT8                                *SourceBuffer;
  UINTN                                SourceBufferSize;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;

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

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  FileName = APPLICATION_IMAGE_1_NAME;
  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             FileName,
             &ValidFilePath
             );
  if (EFI_ERROR(Status)) {
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
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.1.2.1  LoadImage should not succeed with an invalid ParentImageHandle
  //
  //
  // invalid handle could be: NULL; invalid handle; not a image handle
  //
  ParentImageHandle[0] = NULL;
  ImageTestCreateInvalidHandle (&ParentImageHandle[1]);
  ImageTestCreateNewHandle (&ParentImageHandle[2]);

  for (Index = 0; Index < 3; Index++) {

    Status = gtBS->LoadImage (
                     FALSE,
                     ParentImageHandle[Index],
                     ValidFilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid001,
                   L"BS.LoadImage - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  //
  // restore environment
  //
  ImageTestReleaseInvalidHandle (ParentImageHandle[1]);
  ImageTestReleaseNewHandle (ParentImageHandle[2]);

  //
  // Checkpoint 2:
  // 3.1.2.2  LoadImage should not succeed with NULL FilePath
  //
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   NULL,
                   NULL,
                   0,
                   &ImageHandle
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid002,
                 L"BS.LoadImage - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3:
  // 3.1.2.3  LoadImage should not succeed with an irrelevant FilePath
  //
  ImageTestLocateNonFilePath (&IrrelevantFilePath);
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   IrrelevantFilePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid003,
                 L"BS.LoadImage - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 4:
  // 3.1.2.4  LoadImage should not succeed with a non-existent FilePath
  //
  ImageTestCreateNonExistentDevicePath (&NonExistentDevicePath);
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   NonExistentDevicePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  gtBS->FreePool (NonExistentDevicePath);
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid004,
                 L"BS.LoadImage - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //Create a DevicePath that combined a Media DevicePath and Vendor Devicepath.
  //
  NonExistentDevicePath = NULL;

  ImageTestCreateCombinedNonExistentDevicePath (&NonExistentDevicePath);
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   NonExistentDevicePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  gtBS->FreePool (NonExistentDevicePath);
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid004,
                 L"BS.LoadImage - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // ASSERT in CoreLoadImage (Core\Image.c Line1231),
  // so comments this checkpoint out temporarily until it is fixed.
  //

  //
  // Checkpoint 5:
  // 3.1.2.5  LoadImage should not succeed with NULL ImageHandle
  //
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   ValidFilePath,
                   NULL,
                   0,
                   NULL
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid005,
                 L"BS.LoadImage - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 6:
  // 3.1.2.6  LoadImage with SourceSize as 0 it should return EFI_LOAD_ERROR.
  //
  SourceBuffer     = NULL;
  Status = ImageTestCopySimpleFileToMemory (
             StandardLib,
             mImageHandle,
             APPLICATION_IMAGE_1_NAME,
             &SourceBuffer,
             &SourceBufferSize
             );

  if (!EFI_ERROR(Status) && (SourceBuffer != NULL)) {

    SourceBufferSize = 0;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     NULL,
                     SourceBuffer,
                     SourceBufferSize,
                     &ImageHandle
                     );

    if (EFI_LOAD_ERROR == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid010,
                   L"BS.LoadImage - ConsistencyTestCheckpoint6",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    gtBS->FreePool (SourceBuffer);

  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestCopySimpleFileToMemory -Error.",
                   L"%a:%d:Status - %r, ImageName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   APPLICATION_IMAGE_1_NAME
                   );
  }

  gtBS->FreePool (ValidFilePath);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->StartImage() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestStartImageConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_HANDLE                           ImageHandle[3];
  UINTN                                ExitDataSize;
  CHAR16                               *ExitData;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;

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

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.2.2.1  StartImage should not succeed with an invalid ImageHandle
  //
  //
  // invalid handle could be: NULL; invalid handle; not a image handle
  //
  ImageHandle[0] = NULL;
  ImageTestCreateInvalidHandle (&ImageHandle[1]);
  ImageTestCreateNewHandle (&ImageHandle[2]);

  for (Index = 0; Index < 3; Index++) {

    Status = gtBS->StartImage (
                     ImageHandle[Index],
                     &ExitDataSize,
                     &ExitData
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid006,
                   L"BS.StartImage - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // restore environment
  //
  ImageTestReleaseInvalidHandle (ImageHandle[1]);
  ImageTestReleaseNewHandle (ImageHandle[2]);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

/**
 *  @brief Entrypoint for gtBS->UnloadImage() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.3
//
EFI_STATUS
EFIAPI
BBTestUnloadImageConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           ImageHandle[3];
  UINTN                                Index;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;

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

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.3.2.1  UnloadImage should not succeed with an invalid ImageHandle
  //
  //
  // invalid handle could be: NULL; invalid handle; not a image handle
  //
  ImageHandle[0] = NULL;
  ImageTestCreateInvalidHandle (&ImageHandle[1]);
  ImageTestCreateNewHandle (&ImageHandle[2]);

  for (Index = 0; Index < 3; Index++) {

    Status = gtBS->UnloadImage (
                     ImageHandle[Index]
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid007,
                   L"BS.UnloadImage - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  //
  // restore environment
  //
  ImageTestReleaseInvalidHandle (ImageHandle[1]);
  ImageTestReleaseNewHandle (ImageHandle[2]);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

/**
 *  @brief Entrypoint for gtBS->Exit() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.4
//
EFI_STATUS
EFIAPI
BBTestExitConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           ImageHandle[3];
  UINTN                                Index;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;

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

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.4.2.1  Exit should not succeed with an invalid ImageHandle
  //
  //
  // invalid handle could be: NULL; invalid handle; not a image handle
  //
  ImageHandle[0] = NULL;
  ImageTestCreateInvalidHandle (&ImageHandle[1]);
  ImageTestCreateNewHandle (&ImageHandle[2]);

  for (Index = 0; Index < 3; Index++) {

    Status = gtBS->Exit (
                     ImageHandle[Index],
                     EFI_SUCCESS,
                     0,
                     NULL
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid008,
                   L"BS.Exit - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  //
  // restore environment
  //
  ImageTestReleaseInvalidHandle (ImageHandle[1]);
  ImageTestReleaseNewHandle (ImageHandle[2]);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

/**
 *  @brief Entrypoint for gtBS->ExitBootServices() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.5
//
EFI_STATUS
EFIAPI
BBTestExitBootServicesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                MapKey;
  UINTN                                Size;
  UINTN                                Numbers;
  UINTN                                DataSize;
  RESET_DATA                           *ResetData;
  UINT8                                Data[STATUS_BUFFER_SIZE];
  UINT8                                Buffer[RECOVER_BUFFER_SIZE];
  EFI_STATUS                           ReturnStatus;

  //
  // Init
  //
  StandardLib = NULL;
  RecoveryLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   (VOID **) &RecoveryLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  ResetData = (RESET_DATA *)Buffer;

  //
  // Read reset record
  //
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &Size,
                          Buffer
                          );

  //
  // The workflow to check the recovery data
  //
  if (EFI_SUCCESS == Status) {
    //
    // To check the recovery data size
    //
    if (Size == sizeof(RESET_DATA)){
      //
      // To Check the recovery data
      //
      if (ResetData->Step == 1) {
        //
        // Step 1: find the valid recovery data, to retrive presaved status from variable
        //
        DataSize = STATUS_BUFFER_SIZE;
        Status   = gtRT->GetVariable (
                         L"ExitBootServicesTestVariable",    // VariableName
                         &gTestVendor1Guid,                  // VendorGuid
                         NULL,                               // Attributes
                         &DataSize,                          // DataSize
                         &ReturnStatus                       // Data
                         );

        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"GetVariable - Can't get the test variable - ExitBootServicesTestVariable",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
          return Status;
        }
        goto CheckResult;
      } else {
        //
        // It is invalid recovery data
        //
        return EFI_LOAD_ERROR;
      }
    } else {
      //
      // The size of recovery data is invalid
      //
      return EFI_LOAD_ERROR;
    }
  }

  //
  // Step 0: No recovery data is found.
  //

  //
  // Print out some information to avoid the user thought it is an error
  //
  SctPrint (L"System will cold reset after 2 second and test will be resumed after reboot.");
  gtBS->Stall (2000000);


  ResetData->Step = 1;
  ResetData->TplIndex = 0;
  Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            sizeof (RESET_DATA),
                            (UINT8*)ResetData
                            );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"TestRecoveryLib - WriteResetRecord",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }


  //
  // Checkpoint 1:
  // 3.5.2.1  ExitBootServices should not succeed with an invalid MapKey
  //
  //
  // the steps to make a invalid MapKey could be:
  //   1) call tBS->GetMemoryMap() to retrieve the correct MapKey
  //   2) add a randomn value to the correct MapKey.
  //
  Status = ImageTestRetrieveCurrentMapKey (&MapKey);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" BS.GetMemoryMap - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  MapKey += MapKey;

  ReturnStatus = gtBS->ExitBootServices (
                         mImageHandle,
                         MapKey
                         );
  if (ReturnStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  Status = gtRT->SetVariable (
                     L"ExitBootServicesTestVariable",                                                           // VariableName
                     &gTestVendor1Guid,                                                                         // VendorGuid
                     EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS, // Attributes
                     sizeof(EFI_STATUS),                        // DataSize
                     &ReturnStatus                              // Data
                     );

  //reset system
  gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);


CheckResult:

  if (ReturnStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid009,
                 L"BS.ExitBootServices - ConsistencyTestCheckpoint1",
                 L"%a:%d: the Status is - %r, expected status is %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnStatus,
                 EFI_INVALID_PARAMETER
                 );

  Status = gtRT->SetVariable (
                     L"ExitBootServicesTestVariable",                                                           // VariableName
                     &gTestVendor1Guid,                                                                         // VendorGuid
                     EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS, // Attributes
                     0,                               // DataSize
                     Data                             // Data
                     );

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

