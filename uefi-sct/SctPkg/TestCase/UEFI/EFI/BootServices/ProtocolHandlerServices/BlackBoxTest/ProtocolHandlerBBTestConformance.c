/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ProtocolHandlerBBTestConformance.c

Abstract:

  for Protocol Handler Boot Services' Consistency Test

--*/

#include "SctLib.h"
#include "Misc.h"

/**
 *  @brief Entrypoint for gtBS->InstallProtocolInterface() Consistency Test.
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
BBTestInstallProtocolInterfaceConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_HANDLE                           Handle;
  EFI_INTERFACE_TYPE                   InvalidInterfaceType;
  TEST_PROTOCOL_1                      TestProtocol1Instance;
  EFI_HANDLE                           InvalidHandle;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           *HandlePtr[2];
  UINTN                                Index;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }



  //
  // Checkpoint 1:
  // 3.1.2.1    InstallProtocolInterface should not succeed
  // with an invalid interface type
  //
  Handle = NULL;
  InvalidInterfaceType = ~EFI_NATIVE_INTERFACE;
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   InvalidInterfaceType,
                   &TestProtocol1Instance
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mTestProtocol1Guid,
            &TestProtocol1Instance
            );
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid001,
                 L"BS.InstallProtocolInterface - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // Checkpoint 2:
  // 3.1.2.2    InstallProtocolInterface should not succeed upon a spurious handle
  //
  CreateInvalidHandle (&InvalidHandle);
  HandlePtr[0] = NULL;
  HandlePtr[1] = &InvalidHandle;
  for (Index = 0; Index < 2; Index++) {
    Status = gtBS->InstallProtocolInterface (
                     HandlePtr[Index],
                     &mTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &TestProtocol1Instance
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
                   L"BS.InstallProtocolInterface - ConsistencyTestCheckpoint2",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  ReleaseInvalidHandle (InvalidHandle);


  //
  // Checkpoint 3:
  // 3.1.2.3    InstallProtocolInterface should not succeed when install
  // the same protocol to the same handle multiple times.
  //
  Handle = NULL;
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &TestProtocol1Instance
                   );
  if (!EFI_ERROR (Status)) {

#ifndef EFI_DEBUG
    //
    // install the protocol again
    //
    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &TestProtocol1Instance
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid003,
                   L"BS.InstallProtocolInterface - ConsistencyTestCheckpoint3",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
#endif
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mTestProtocol1Guid,
            &TestProtocol1Instance
            );
  }

  //
  // Checkpoint 4:
  // 3.1.2.4    InstallProtocolInterface should not succeed
  // if Protocol is NULL
  //
  Handle = NULL;
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   NULL,
                   EFI_NATIVE_INTERFACE,
                   &TestProtocol1Instance
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestConformanceAssertionGuid001,
                 L"BS.InstallProtocolInterface - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
               );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->UninstallProtocolInterface() Consistency Test.
 *         3 check points will be tested.
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
BBTestUninstallProtocolInterfaceConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_HANDLE                           Handle;
  EFI_HANDLE                           InvalidHandle;
  TEST_PROTOCOL_1                      TestProtocol1Instance;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           HandleBuffer[2];
  UINTN                                Index;

  UINTN                               Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Install a protocol for uninstall test use.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.2.2.1    UninstallProtocolInterface should not succeed with a NULL GUID
  //
  Status = gtBS->UninstallProtocolInterface (
                   Handle,
                   NULL,
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
                 gConsistencyTestAssertionGuid004,
                 L"BS.UninstallProtocolInterface - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2:
  // 3.2.2.2    UninstallProtocolInterface should not succeed
  // upon a spurious handle
  //
  CreateInvalidHandle (&InvalidHandle);
  HandleBuffer[0] = NULL;
  HandleBuffer[1] = InvalidHandle;
  for (Index = 0; Index < 2; Index++) {
    Status = gtBS->UninstallProtocolInterface (
                     HandleBuffer[Index],
                     &mTestNoInterfaceProtocol1Guid,
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
                   L"BS.UninstallProtocolInterface - ConsistencyTestCheckpoint2",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  ReleaseInvalidHandle (InvalidHandle);

  //
  // Checkpoint 3:
  // 3.2.2.3    UninstallProtocolInterface should not succeed
  // upon a non-existed protocol
  //
  // TestNoInterfaceProtocol1 was previously installed onto the handle.
  // Here, TestProtocol1 does not exist.
  //
  Status = gtBS->UninstallProtocolInterface (
                   Handle,
                   &mTestProtocol1Guid,
                   &TestProtocol1Instance
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid006,
                 L"BS.UninstallProtocolInterface - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 4:
  // 3.2.2.3    3.2.2.4  UninstallProtocolInterface should not succeed
  // upon an invalid interface
  //
  Status = gtBS->UninstallProtocolInterface (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   &TestProtocol1Instance    // invalid
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestConformanceAssertionGuid003,
                 L"BS.UninstallProtocolInterface - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
          NULL
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->ReinstallProtocolInterface() Consistency Test.
 *         4 check points will be tested.
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
BBTestReinstallProtocolInterfaceConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_HANDLE                           Handle;
  TEST_PROTOCOL_1                      OldTestProtocol1Instance;
  TEST_PROTOCOL_1                      NewTestProtocol1Instance;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           InvalidHandle;
  EFI_HANDLE                           HandleBuffer[2];
  UINTN                                Index;

  UINTN                               Numbers;

  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&OldTestProtocol1Instance);
  InitializeTestProtocol1 (&NewTestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Install a protocol for reinstall test use.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &OldTestProtocol1Instance
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.3.2.1    ReinstallProtocolInterface should not succeed with a NULL GUID
  //
  Status = gtBS->ReinstallProtocolInterface (
                   Handle,
                   NULL,
                   NULL,
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
                 gConsistencyTestAssertionGuid007,
                 L"BS.ReinstallProtocolInterface - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2:
  // 3.3.2.2    ReinstallProtocolInterface should not succeed
  // with spurious old protocol interface.
  //
  // the old protocol interface does not point to the protocol interface
  // installed upon current handle.
  //
  Status = gtBS->ReinstallProtocolInterface (
                   Handle,
                   &mTestProtocol1Guid,
                   &NewTestProtocol1Instance,
                   &NewTestProtocol1Instance
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid008,
                 L"BS.ReinstallProtocolInterface - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3:
  // 3.3.2.3    ReinstallProtocolInterface should not succeed
  // with current non-exist protocol
  //
  // TestProtocol1 is installed on the handle, while TestNoInterfaceProtocol is
  // not on the handle.
  //
  Status = gtBS->ReinstallProtocolInterface (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid010,
                 L"BS.ReinstallProtocolInterface - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 4:
  // 3.2.2.2    ReinstallProtocolInterface should not succeed
  // upon a spurious handle
  //
  CreateInvalidHandle (&InvalidHandle);
  HandleBuffer[0] = NULL;
  HandleBuffer[1] = InvalidHandle;
  for (Index = 0; Index < 2; Index++) {
    Status = gtBS->ReinstallProtocolInterface (
                     HandleBuffer[Index],
                     &mTestProtocol1Guid,
                     &OldTestProtocol1Instance,
                     &NewTestProtocol1Instance
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestConformanceAssertionGuid002,
                   L"BS.ReinstallProtocolInterface - ConsistencyTestCheckpoint4",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  ReleaseInvalidHandle (InvalidHandle);

  //
  // Restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestProtocol1Guid,
          &OldTestProtocol1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestProtocol1Guid,
          &NewTestProtocol1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestProtocol1Guid,
          NULL
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->RegisterProtocolNotify() Consistency Test.
 *         3 check points will be tested.
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
BBTestRegisterProtocolNotifyConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_EVENT                             Event;
  VOID                                  *Registration;
  EFI_TEST_ASSERTION                   AssertionType;

  UINTN                                 Numbers;

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Create Event. ## destroy before leave
  //
  Status = gtBS->CreateEvent (EVT_NOTIFY_WAIT, TPL_CALLBACK, TestNotifyFunction0, NULL, &Event);
  if (EFI_ERROR(Status)) {
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
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.4.2.1    RegisterProtocolNotify should not succeed with a NULL GUID
  //
  Status = gtBS->RegisterProtocolNotify (
                   NULL,
                   Event,
                   &Registration
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid011,
                 L"BS.RegisterProtocolNotify - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2:
  // 3.4.2.2    RegisterProtocolNotify should not succeed with a NULL event
  //
  // the old protocol interface does not point to the protocol interface
  // installed upon current handle.
  //
  Status = gtBS->RegisterProtocolNotify (
                   &mTestProtocol1Guid,
                   NULL,
                   &Registration
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid012,
                 L"BS.RegisterProtocolNotify - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3:
  // 3.4.2.3    RegisterProtocolNotify should not succeed
  // with a NULL registration
  //
  Status = gtBS->RegisterProtocolNotify (
                   &mTestProtocol1Guid,
                   Event,
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
                 gConsistencyTestAssertionGuid013,
                 L"BS.RegisterProtocolNotify - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Restore environment
  //
  gtBS->CloseEvent (Event);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->InstallMultipleProtocolInterfaces() Consistency Test.
 *         2 check points will be tested.
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
BBTestInstallMultipleProtocolInterfacesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            LocateStatus1;
  EFI_STATUS                            LocateStatus2;
  EFI_HANDLE                            Handle1;
  EFI_HANDLE                            Handle2;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath1;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath2;
  UINT8                                 *NoInstance;
  EFI_HANDLE                            InvalidHandle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  TEST_PROTOCOL_2                       TestProtocol2Instance;
  TEST_PROTOCOL_1                       *TestProtocol1;
  TEST_PROTOCOL_2                       *TestProtocol2;
  EFI_TEST_ASSERTION                   AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle1 = NULL;
  Handle2 = NULL;
  NoInstance = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);
  InitializeTestProtocol2 (&TestProtocol2Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Create 2 identical vendor device paths  ## destroy before leave
  //
  CreateVendorDevicePath (&DevicePath1, mVendorDevicePath1Guid);
  CreateVendorDevicePath (&DevicePath2, mVendorDevicePath1Guid);

  //
  // Checkpoint 0:
  // InstallMultipleProtocolInterfaces should not succeed
  // with an NULL Handle
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   NULL,
                   &mTestNoInterfaceProtocol1Guid, NULL,
                   &gEfiDevicePathProtocolGuid, DevicePath2,
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
                 gProtocolHandlerBBTestConformanceAssertionGuid008,
                 L"BS.InstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Install a vendor device path onto a new handle. ## destroy before leave
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle1,
                   &gEfiDevicePathProtocolGuid,
                   EFI_NATIVE_INTERFACE,
                   DevicePath1
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }


  //
  // Checkpoint 1:
  // 3.5.2.1    InstallMultipleProtocolInterfaces should not succeed
  // with an existed device path protocol instance
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle2,
                   &mTestNoInterfaceProtocol1Guid, NULL,
                   &gEfiDevicePathProtocolGuid, DevicePath2,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_ALREADY_STARTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid014,
                 L"BS.InstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (Handle2 != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle2,
            &gEfiDevicePathProtocolGuid,
            DevicePath2
            );
    Handle2 = NULL;
  }
  //
  // step 2: check whether the TestNoInterfaceProtocol is actually installed
  //
  Status = gtBS->LocateProtocol (
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   (VOID **) &NoInstance
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid015,
                 L"BS.InstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (Handle2 != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle2,
            &mTestNoInterfaceProtocol1Guid,
            NULL
            );
  }
  Handle2 = NULL;

  //
  // Checkpoint 2:
  // 3.5.2.2    InstallMultipleProtocolInterfaces should not succeed
  // upon a spurious handle
  //
  CreateInvalidHandle (&InvalidHandle);
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &InvalidHandle,
                   &mTestProtocol1Guid, &TestProtocol1Instance,
                   &mTestProtocol2Guid, &TestProtocol2Instance,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid016,
                 L"BS.InstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // step 2: check whether TestProtocol1 & TestProtocol2 are present
  //
  LocateStatus1 = gtBS->LocateProtocol (
                          &mTestProtocol1Guid,
                          NULL,
                          (VOID **) &TestProtocol1
                          );
  LocateStatus2 = gtBS->LocateProtocol (
                          &mTestProtocol2Guid,
                          NULL,
                          (VOID **) &TestProtocol2
                          );
  if (LocateStatus1 == EFI_NOT_FOUND && LocateStatus2 == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    //
    // uninstall the protocols
    //
    gtBS->UninstallProtocolInterface (
            InvalidHandle,
            &mTestProtocol1Guid,
            &TestProtocol1Instance
            );
    gtBS->UninstallProtocolInterface (
            InvalidHandle,
            &mTestProtocol2Guid,
            &TestProtocol2Instance
            );
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid017,
                 L"BS.InstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint2",
                 L"%a:%d:LocateStatus1 - %r, LocateStatus2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 LocateStatus1,
                 LocateStatus2
                 );
  ReleaseInvalidHandle (InvalidHandle);

  //
  // Checkpoint 3:
  // 3.5.2.3  InstallMultipleProtocolInterfaces should not succeed
  // when install the same protocol to the same handle multiple times.
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle2,
                   &mTestProtocol1Guid, &TestProtocol1Instance,
                   NULL
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterface - build environment 3",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle2,
                   &mTestProtocol2Guid, &TestProtocol2Instance,
                   &mTestProtocol1Guid, &TestProtocol1Instance,
                   NULL
                   );

  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestConformanceAssertionGuid004,
                 L"BS.InstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // step 2: check whether TestProtocol1 & TestProtocol2 are present
  //
  LocateStatus1 = gtBS->LocateProtocol (
                    &mTestProtocol1Guid,
                    NULL,
                    (VOID **) &TestProtocol1
                    );
  LocateStatus2 = gtBS->LocateProtocol (
                    &mTestProtocol2Guid,
                    NULL,
                    (VOID **) &TestProtocol2
                    );
  if (LocateStatus1 == EFI_SUCCESS && LocateStatus2 == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestConformanceAssertionGuid005,
                 L"BS.InstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint3",
                 L"%a:%d:LocateStatus1 - %r, LocateStatus2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 LocateStatus1,
                 LocateStatus2
                 );

  //
  // uninstall the Protocols
  //
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mTestProtocol1Guid,
          &TestProtocol1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mTestProtocol2Guid,
          &TestProtocol2Instance
          );

  Status = EFI_SUCCESS;
Done:
  //
  // Restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle1,
          &gEfiDevicePathProtocolGuid,
          DevicePath1
          );
  FreeVendorDevicePath (DevicePath1);
  FreeVendorDevicePath (DevicePath2);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

/**
 *  @brief Entrypoint for gtBS->UninstallMultipleProtocolInterfaces() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.6
//
EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1;
  EFI_STATUS                            Status2;
  EFI_HANDLE                            Handle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  TEST_PROTOCOL_2                       TestProtocol2Instance;
  TEST_PROTOCOL_1                       *TestProtocol1;
  TEST_PROTOCOL_2                       *TestProtocol2;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);
  InitializeTestProtocol2 (&TestProtocol2Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Install TestProtocol1 & TestProtocol2 onto a new handle.
  // ## destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid, &TestProtocol1Instance,
                   &mTestProtocol2Guid, &TestProtocol2Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.6.2.1    UninstallMultipleProtocolInterfaces should not succeed
  // with a non-exist protocol instance
  //
  Status = gtBS->UninstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid, &TestProtocol1Instance,
                   &mTestProtocol2Guid, &TestProtocol2Instance,
                   &mTestNoInterfaceProtocol1Guid, NULL,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid018,
                 L"BS.UninstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // step 2: check whether TestProtocol1 & TestProtocol2 are not uninstalled
  //
  Status1 = gtBS->LocateProtocol (
                    &mTestProtocol1Guid,
                    NULL,
                    (VOID**)&TestProtocol1
                    );
  Status2 = gtBS->LocateProtocol (
                    &mTestProtocol2Guid,
                    NULL,
                    (VOID**)&TestProtocol2
                    );
  if (Status1 == EFI_SUCCESS && Status2 == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid019,
                 L"BS.UninstallMultipleProtocolInterfaces - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status1 - %r, Status2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1,
                 Status2
                 );
  //
  // Restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestProtocol1Guid,
          &TestProtocol1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestProtocol2Guid,
          &TestProtocol2Instance
          );


  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->LocateHandle () Consistency Test.
 *         6 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.7
//
EFI_STATUS
EFIAPI
BBTestLocateHandleConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HANDLE                            Handle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  EFI_LOCATE_SEARCH_TYPE                InvalidSearchType;
  EFI_HANDLE                            HandleBuffer;
  UINTN                                 BufferSize;
  EFI_EVENT                             Event;
  EFI_TEST_ASSERTION                    AssertionType;
//  UINTN                                 *BufferSizePtr[2];
//  EFI_HANDLE                            *HandleBufferPtr[2];
//  UINTN                                 Index;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  Event = NULL;
  BufferSize = sizeof (EFI_HANDLE);
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Install TestProtocol1 onto a new handle. ##1 destroy before leave
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &TestProtocol1Instance
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.7.2.1    LocateHandle should not succeed with an invalid search type
  //
  InvalidSearchType = AllHandles + ByRegisterNotify + ByProtocol;
  Status = gtBS->LocateHandle (
                   InvalidSearchType,
                   &mTestProtocol1Guid,
                   NULL,
                   &BufferSize,
                   &HandleBuffer
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid020,
                 L"BS.LocateHandle - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

/*
  // BUG: NULL GUID cause ASSERT

  //
  // Checkpoint 2:
  // 3.7.2.2    LocateHandle should not succeed
  // with NULL protocol GUID when search ByProtocol
  //
  Status = gtBS->LocateHandle (
                   ByProtocol,
                   NULL,
                   NULL,
                   &BufferSize,
                   &HandleBuffer
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid021,
                 L"BS.LocateHandle - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
 */
  //
  // Checkpoint 3:
  // 3.7.2.3    LocateHandle should not succeed with
  // NULL SearchKey when search ByRegisterNotify
  //

  Status = gtBS->LocateHandle (
                   ByRegisterNotify,
                   NULL,
                   NULL,
                   &BufferSize,
                   &HandleBuffer
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid023,
                 L"BS.LocateHandle - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // Checkpoint 4:
  // 3.7.2.4    LocateHandle should not succeed
  // when search for a never installed protocol
  //
  Status = gtBS->LocateHandle (
                   ByProtocol,
                   &mTestProtocol2Guid,
                   NULL,
                   &BufferSize,
                   &HandleBuffer
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid024,
                 L"BS.LocateHandle - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 5:
  // 3.7.2.5    LocateHandle should not succeed
  // when handle buffer is not large enough
  //

  //
  // BufferSize = 0
  //
  BufferSize = 0;
  Status = gtBS->LocateHandle (
                   ByProtocol,
                   &mTestProtocol1Guid,
                   NULL,
                   &BufferSize,
                   &HandleBuffer
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid025,
                 L"BS.LocateHandle - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // step 2: check whether the buffer size is updated to the correct size
  //
  // this time, there is only one TestProtocol1 instance in the system
  //
  if (BufferSize == sizeof (EFI_HANDLE)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid026,
                 L"BS.LocateHandle - ConsistencyTestCheckpoint5",
                 L"%a:%d:ExpectedBufferSize - %d, BufferSize - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 sizeof (EFI_HANDLE),
                 BufferSize
                 );

  //
  // BufferSize = expected buffer size - 1
  //
  BufferSize = sizeof (EFI_HANDLE) - 1;
  Status = gtBS->LocateHandle (
                   ByProtocol,
                   &mTestProtocol1Guid,
                   NULL,
                   &BufferSize,
                   &HandleBuffer
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestConformanceAssertionGuid006,
                 L"BS.LocateHandle - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // step 2: check whether the buffer size is updated to the correct size
  //
  // this time, there is only one TestProtocol1 instance in the system
  //
  if (BufferSize == sizeof (EFI_HANDLE)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestConformanceAssertionGuid007,
                 L"BS.LocateHandle - ConsistencyTestCheckpoint5",
                 L"%a:%d:ExpectedBufferSize - %d, BufferSize - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 sizeof (EFI_HANDLE),
                 BufferSize
                 );

/*
  // BUG: NULL Buffer, NULL BufferSize cause assert

  //
  // Checkpoint 6:
  // 3.7.2.6    LocateHandle should not succeed when handle buffer or
  // BufferSize is NULL
  //
  BufferSize = sizeof (EFI_HANDLE);
  HandleBufferPtr[0] = NULL;
  HandleBufferPtr[1] = &HandleBuffer;
  BufferSizePtr[0] = &BufferSize;
  BufferSizePtr[1] = NULL;
  for (Index = 0; Index < 2; Index++) {
    Status = gtBS->LocateHandle (
                     ByProtocol,
                     &mTestProtocol1Guid,
                     NULL,
                     BufferSizePtr[Index],
                     HandleBufferPtr[Index]
                     );
    //
    // step 1: check return status
    //
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid027,
                   L"BS.LocateHandle - ConsistencyTestCheckpoint6",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }
*/
  //
  // Restore environment
  //
  gtBS->UninstallProtocolInterface (Handle, &mTestProtocol1Guid, &TestProtocol1Instance);


  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}


/**
 *  @brief Entrypoint for gtBS->LocateHandleBuffer() Consistency Test.
 *         3 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.8
//
EFI_STATUS
EFIAPI
BBTestLocateHandleBufferConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1;
  EFI_STATUS                            Status2;
  EFI_HANDLE                            Handle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  EFI_LOCATE_SEARCH_TYPE                InvalidSearchType;
  EFI_HANDLE                            *HandleBuffer;
  UINTN                                 NoHandles;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  NoHandles = 1;
  HandleBuffer = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Install TestProtocol1 onto a new handle. ##1 destroy before leave
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &TestProtocol1Instance
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.8.2.1    LocateHandleBuffer should not succeed with an invalid search type
  //
  InvalidSearchType = AllHandles + ByRegisterNotify + ByProtocol;
  Status = gtBS->LocateHandleBuffer (
                   InvalidSearchType,
                   &mTestProtocol1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid028,
                 L"BS.LocateHandleBuffer - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }

  //
  // Checkpoint 2:
  // 3.8.2.2    LocateHandleBuffer should not succeed
  // when search for a never installed protocol
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mTestProtocol2Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid029,
                 L"BS.LocateHandleBuffer - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }

  //
  // Checkpoint 3:
  // 3.8.2.3    LocateHandleBuffer should not succeed
  // when Buffer is NULL or NoHandles is NULL
  //

  Status1 = gtBS->LocateHandleBuffer (
                    ByProtocol,
                    &mTestProtocol1Guid,
                    NULL,
                    NULL,
                    &HandleBuffer
                    );
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }
  Status2 = gtBS->LocateHandleBuffer (
                    ByProtocol,
                    &mTestProtocol1Guid,
                    NULL,
                    &NoHandles,
                    NULL
                    );
  //
  // step 1: check return status
  //
  if (Status1 == EFI_INVALID_PARAMETER && Status2 == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid030,
                 L"BS.LocateHandleBuffer - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }

  //
  // Restore environment
  //
  gtBS->UninstallProtocolInterface (Handle, &mTestProtocol1Guid, &TestProtocol1Instance);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->HandleProtocol() Consistency Test.
 *         4 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.9
//
EFI_STATUS
EFIAPI
BBTestHandleProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HANDLE                            Handle;
  EFI_HANDLE                            InvalidHandle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  TEST_PROTOCOL_1                       *TestProtocol1;
  TEST_PROTOCOL_2                       *TestProtocol2;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_HANDLE                            HandleBuffer[2];
  UINTN                                 Index;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Install TestProtocol1 onto a new handle. ##1 destroy before leave
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &TestProtocol1Instance
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }


  //
  // Checkpoint 1:
  // 3.9.2.1    HandleProtocol should not succeed with invalid handle
  //
  CreateInvalidHandle (&InvalidHandle);
  HandleBuffer[0] = NULL;
  HandleBuffer[1] = InvalidHandle;
  for (Index = 0; Index < 2; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &mTestProtocol1Guid,
                     (VOID **) &TestProtocol1
                     );
    //
    // step 1: check return status
    //
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid031,
                   L"BS.HandleProtocol - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  ReleaseInvalidHandle (InvalidHandle);

  //
  // Checkpoint 2:
  // 3.9.2.2    HandleProtocol should not succeed with NULL protocol GUID
  //
  Status = gtBS->HandleProtocol (
                   Handle,
                   NULL,
                   (VOID **) &TestProtocol1
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid032,
                 L"BS.HandleProtocol - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Checkpoint 3:
  // 3.9.2.3    HandleProtocol should not succeed with NULL interface.
  //

  Status = gtBS->HandleProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid033,
                 L"BS.HandleProtocol - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 4:
  // 3.9.2.4    HandleProtocol should not succeed
  // with a protocol GUID that was never installed on the handle
  //
  Status = gtBS->HandleProtocol (
                   Handle,
                   &mTestProtocol2Guid,
                   (VOID **) &TestProtocol2
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid034,
                 L"BS.HandleProtocol - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Restore environment
  //
  gtBS->UninstallProtocolInterface (Handle, &mTestProtocol1Guid, &TestProtocol1Instance);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->LocateProtocol () Consistency Test.
 *         3 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.10
//
EFI_STATUS
EFIAPI
BBTestLocateProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HANDLE                            Handle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  TEST_PROTOCOL_2                       TestProtocol2Instance;
  TEST_PROTOCOL_2                       *TestProtocol2;
  EFI_EVENT                             Event;
  VOID                                  *Registration;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  Event = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);
  InitializeTestProtocol2 (&TestProtocol2Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Install TestProtocol1 onto a new handle. ##1 destroy before leave
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &TestProtocol1Instance
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }


  //
  // Checkpoint 1:
  // 3.10.2.1   LocateProtocol should not succeed with NULL interface
  //
  Status = gtBS->LocateProtocol (
                   &mTestProtocol1Guid,
                   NULL,
                   (VOID **) NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid035,
                 L"BS.LocateProtocol - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Add a checkpoint from the 1559
  // If Protocol is NULL, then EFI_INVALID_PARAMETER is returned
  //
  Status = gtBS->LocateProtocol (
                   NULL,
                   NULL,
                   (VOID **) &TestProtocol2
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid009,
                 L"BS.LocateProtocol - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2:
  // 3.10.2.2   LocateProtocol should not succeed
  // with a protocol GUID that was never installed
  //
  Status = gtBS->LocateProtocol (
                   &mTestProtocol2Guid,
                   NULL,
                   (VOID **) &TestProtocol2
                   );
  //
  // step 1: check return status
  //
  if ((Status == EFI_NOT_FOUND) && (TestProtocol2 == NULL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid036,
                 L"BS.LocateProtocol - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Checkpoint 3:
  // 3.10.2.3   LocateProtocol should not succeed
  // when there is no new protocol instance installed for the same Registration.
  //

  //
  // Create Event. ##2 destroy before leave
  //
  Status = gtBS->CreateEvent (EVT_NOTIFY_WAIT, TPL_CALLBACK, TestNotifyFunction0, NULL, &Event);
  if (EFI_ERROR(Status)) {
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

  Status = gtBS->RegisterProtocolNotify (
                   &mTestProtocol2Guid,
                   Event,
                   &Registration
                   );
  if (EFI_ERROR(Status)) {
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

  Status = gtBS->LocateProtocol (
                   &mTestProtocol2Guid,
                   Registration,
                   (VOID **) &TestProtocol2
                   );
  //
  // step 1: check return status
  //
  if ((Status == EFI_NOT_FOUND) && (TestProtocol2 == NULL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid037,
                 L"BS.LocateProtocol - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = EFI_SUCCESS;

Done:
  //
  // Restore environment
  //
  gtBS->UninstallProtocolInterface (Handle, &mTestProtocol1Guid, &TestProtocol1Instance);
  if (Event != NULL) {
    gtBS->CloseEvent (Event);
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

/**
 *  @brief Entrypoint for gtBS->LocateDevicePath() Consistency Test.
 *         4 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.11
//
EFI_STATUS
EFIAPI
BBTestLocateDevicePathConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HANDLE                            Handle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  EFI_EVENT                             Event;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath1;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath2;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath3;
  EFI_HANDLE                            Handle2;
  EFI_HANDLE                            Handle3;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;

  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  Handle2 = NULL;
  Event = NULL;
  DevicePath1 = NULL;
  DevicePath2 = NULL;
  DevicePath3 = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Create vendor device paths. ##1 destroy before leave
  //
  CreateVendorDevicePath (&DevicePath1, mVendorDevicePath1Guid);
  CreateVendorDevicePath (&DevicePath2, mVendorDevicePath2Guid);

  //
  // Install TestProtocol1 & vendor device path1 onto a new handle.
  // ##2 destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid,
                   &TestProtocol1Instance,
                   &gEfiDevicePathProtocolGuid,
                   DevicePath1,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // Install vendor device path2 onto a new handle.
  // ##3 destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle2,
                   &gEfiDevicePathProtocolGuid,
                   DevicePath2,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  // BUG: NULL GUID cause assert (only for EFI1.1)

  //
  // Checkpoint 1:
  // 3.11.2.1   LocateDevicePath should not succeed with NULL protocol GUID
  //
  DevicePath3 = DevicePath1;
  Status = gtBS->LocateDevicePath (
                   NULL,
                   &DevicePath3,
                   &Handle3
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid038,
                 L"BS.LocateDevicePath - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );


  //
  // Checkpoint 2:
  // 3.11.2.2   LocateDevicePath should not succeed with NULL device path
  //
  DevicePath3 = NULL;
  Status = gtBS->LocateDevicePath (
                   &mTestProtocol1Guid,
                   &DevicePath3,
                   &Handle3
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid039,
                 L"BS.LocateDevicePath - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3:
  // 3.11.2.3   If DevicePath is a multi-instance device path, the function will operate on the first instance
  //
  DevicePath3 = SctAppendDevicePath (DevicePath1, DevicePath2);
  Status = gtBS->LocateDevicePath (
                   &mTestProtocol1Guid,
                   &DevicePath3,
                   &Handle3
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid040,
                 L"BS.LocateDevicePath - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Checkpoint 4:
  // 3.11.2.4   LocateDevicePath should not succeed
  // searching for a handle with a never installed protocol
  //
  // There is no TestProtocol2 installed on the handle that has vendor device path2.
  //
  DevicePath3 = DevicePath2;
  Status = gtBS->LocateDevicePath (
                   &mTestProtocol2Guid,
                   &DevicePath3,
                   &Handle3
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid041,
                 L"BS.LocateDevicePath - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 5:
  // 3.11.2.5   LocateDevicePath should not succeed
  // searching for a handle with a never installed protocol with a NULL input device
  //
  // There is no TestProtocol2 installed on the handle that has vendor device path2.
  //
  DevicePath3 = DevicePath2;
  Status = gtBS->LocateDevicePath (
                   &mTestProtocol2Guid,
                   &DevicePath3,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid071,
                 L"BS.LocateDevicePath - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 6:
  // 3.11.2.6   LocateDevicePath should not succeed with NULL device path input
  //
  Status = gtBS->LocateDevicePath (
                   &mTestProtocol1Guid,
                   NULL,
                   &Handle3
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid072,
                 L"BS.LocateDevicePath - ConsistencyTestCheckpoint6",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  

  //
  // Checkpoint 7:
  // 3.11.2.7   LocateDevicePath should not succeed with NULL device and protocol is already installed
  //
  DevicePath3 = DevicePath1;
  Status = gtBS->LocateDevicePath (
                   &mTestProtocol1Guid,
                   &DevicePath3,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid073,
                 L"BS.LocateDevicePath - ConsistencyTestCheckpoint7",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

Done:
  //
  // Restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestProtocol1Guid, &TestProtocol1Instance,
          &gEfiDevicePathProtocolGuid, DevicePath1,
          NULL
          );
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle2,
          &gEfiDevicePathProtocolGuid, DevicePath2,
          NULL
          );
  FreeVendorDevicePath (DevicePath1);
  FreeVendorDevicePath (DevicePath2);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->ProtocolsPerHandle() Consistency Test.
 *         3 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.12
//
EFI_STATUS
EFIAPI
BBTestProtocolsPerHandleConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1;
  EFI_STATUS                            Status2;
  EFI_HANDLE                            Handle;
  EFI_HANDLE                            InvalidHandle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  TEST_PROTOCOL_2                       TestProtocol2Instance;
  EFI_GUID                              **ProtocolGuidArray;
  UINTN                                 ProtocolBufferCount;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  ProtocolGuidArray = NULL;
  ProtocolBufferCount = 0;
  InitializeTestProtocol1 (&TestProtocol1Instance);
  InitializeTestProtocol2 (&TestProtocol2Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Install TestProtocol1 & TestProtocol2 onto a new handle.
  // ##1 destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid,
                   &TestProtocol1Instance,
                   &mTestProtocol2Guid,
                   &TestProtocol2Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }


  //
  // Checkpoint 1:
  // 3.12.2.1   ProtocolsPerHandle should not succeed
  // with invalid handle or NULL handle
  //
  CreateInvalidHandle (&InvalidHandle);
  Status1 = gtBS->ProtocolsPerHandle (
                    InvalidHandle,
                    &ProtocolGuidArray,
                    &ProtocolBufferCount
                    );
  ReleaseInvalidHandle (InvalidHandle);
  Status2 = gtBS->ProtocolsPerHandle (
                    NULL,
                    &ProtocolGuidArray,
                    &ProtocolBufferCount
                    );
  //
  // step 1: check return status
  //
  if (Status1 == EFI_INVALID_PARAMETER && Status2 == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid042,
                 L"BS.ProtocolsPerHandle - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status1 - %r, Status2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1,
                 Status2
                 );

  //
  // Checkpoint 2:
  // 3.12.2.2   ProtocolsPerHandle should not succeed with NULL protocol buffer
  //
  Status = gtBS->ProtocolsPerHandle (
                   Handle,
                   NULL,
                   &ProtocolBufferCount
                   );

  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid043,
                 L"BS.ProtocolsPerHandle - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Checkpoint 3:
  // 3.12.2.3   ProtocolsPerHandle should not succeed with buffer count being NULL
  //

  Status = gtBS->ProtocolsPerHandle (
                   Handle,
                   &ProtocolGuidArray,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid044,
                 L"BS.ProtocolsPerHandle - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestProtocol1Guid, &TestProtocol1Instance,
          &mTestProtocol2Guid, &TestProtocol2Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->OpenProtocol() Consistency Test.
 *         6 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.13
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_HANDLE                            Handle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  TEST_PROTOCOL_1                       *TestProtocol1;
  TEST_PROTOCOL_2                       *TestProtocol2;
  UINT32                                InvalidAttributes;
  EFI_HANDLE                            InvalidHandle;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Install TestProtocol1 onto a new handle.
  // ##1 destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid,
                   &TestProtocol1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.13.2.1   OpenProtocol should not succeed with invalid handle
  //
  CreateInvalidHandle (&InvalidHandle);
  Status = gtBS->OpenProtocol (
                   InvalidHandle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                   );
  ReleaseInvalidHandle (InvalidHandle);

  Status1 = gtBS->OpenProtocol (
                    NULL,
                    &mTestProtocol1Guid,
                    (VOID **) &TestProtocol1,
                    mImageHandle,
                    NULL,
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                    );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER && Status1 == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid045,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2:
  // 3.13.2.2   OpenProtocol should not succeed with NULL protocol GUID
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   NULL,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid046,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3:
  // 3.13.2.3   OpenProtocol should not succeed
  // with NULL interface when Attributes is not TEST_PROTOCOL
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) NULL,
                   mImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_GET_PROTOCOL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid047,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 4:
  // 3.13.2.4   OpenProtocol should not succeed with invalid Attributes
  //
  InvalidAttributes = EFI_OPEN_PROTOCOL_GET_PROTOCOL | EFI_OPEN_PROTOCOL_TEST_PROTOCOL;
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   NULL,
                   InvalidAttributes
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid048,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 5:
  // 3.13.2.5   OpenProtocol should not succeed with invalid combination of
  // Handle, Attributes, ControllerHandle and AgentHandle
  // see below 1) ~ 9)
  //

  CreateInvalidHandle (&InvalidHandle);

  // 1) Attributes is BY_CHILD_CONTROLLER
  //    and AgentHandle is not a valid EFI_HANDLE.
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   InvalidHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                   );
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          InvalidHandle,
          NULL
          );

  Status1 = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   NULL,
                   NULL,
                   EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                   );
  
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          NULL,
          NULL
          );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER && Status1 == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid049,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 2) Attributes is BY_DRIVER and AgentHandle is not a valid EFI_HANDLE.
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   InvalidHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_BY_DRIVER
                   );
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          InvalidHandle,
          NULL
          );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid050,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // 3) Attributes is BY_DRIVER | EXCLUSIVE
  //    and AgentHandle is not a valid EFI_HANDLE.
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   InvalidHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                   );
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          InvalidHandle,
          NULL
          );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid051,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 4) Attributes is EXCLUSIVE and AgentHandle is not a valid EFI_HANDLE
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   InvalidHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_EXCLUSIVE
                   );
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          InvalidHandle,
          NULL
          );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid052,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 5) Attributes is BY_CHILD_CONTROLLER
  //    and ControllerHandle is not a valid EFI_HANDLE
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   InvalidHandle,
                   EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                   );
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          mImageHandle,
          InvalidHandle
          );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid053,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 6) Attributes is BY_DRIVER and ControllerHandle is not a valid EFI_HANDLE
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   InvalidHandle,
                   EFI_OPEN_PROTOCOL_BY_DRIVER
                   );
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          mImageHandle,
          InvalidHandle
          );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid054,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 7) Attributes is BY_DRIVER | EXCLUSIVE
  //    and ControllerHandle is not a valid EFI_HANDLE
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   InvalidHandle,
                   EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                   );
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          mImageHandle,
          InvalidHandle
          );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid055,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 8) Attributes is BY_CHILD_CONTROLLER
  //    and Handle is identical to ControllerHandle
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   Handle,
                   EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                   );
  gtBS->CloseProtocol (
          Handle,
          &mTestProtocol1Guid,
          mImageHandle,
          Handle
          );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid056,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  ReleaseInvalidHandle (InvalidHandle);


  //
  // Checkpoint 6:
  // 3.13.2.6   OpenProtocol should not succeed
  // with a protocol GUID that was never installed on the handle
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol2Guid,
                   (VOID **) &TestProtocol2,
                   mImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_GET_PROTOCOL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid058,
                 L"BS.OpenProtocol - ConsistencyTestCheckpoint6",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestProtocol1Guid, &TestProtocol1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->CloseProtocol() Consistency Test.
 *         6 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.14
//
EFI_STATUS
EFIAPI
BBTestCloseProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_HANDLE                            Handle;
  EFI_HANDLE                            InvalidHandle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  TEST_PROTOCOL_1                       *TestProtocol1;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Install TestProtocol1 onto a new handle.
  // ##1 destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid,
                   &TestProtocol1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }


  //
  // Checkpoint 1:
  // 3.14.2.1   CloseProtocol should not succeed with invalid Handle
  //

  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_GET_PROTOCOL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.OpenProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  CreateInvalidHandle (&InvalidHandle);

  Status = gtBS->CloseProtocol (
                   InvalidHandle,
                   &mTestProtocol1Guid,
                   mImageHandle,
                   NULL
                   );
  ReleaseInvalidHandle (InvalidHandle);

  Status1 = gtBS->CloseProtocol (
                    NULL,
                    &mTestProtocol1Guid,
                    mImageHandle,
                    NULL
                    );

  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER && Status1 == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid059,
                 L"BS.CloseProtocol - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  gtBS->CloseProtocol (Handle, &mTestProtocol1Guid, mImageHandle, NULL);


  //
  // Checkpoint 2:
  // 3.14.2.2   CloseProtocol should not succeed with invalid AgentHandle
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_GET_PROTOCOL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.OpenProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  CreateInvalidHandle (&InvalidHandle);

  Status = gtBS->CloseProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   InvalidHandle,
                   NULL
                   );
  ReleaseInvalidHandle (InvalidHandle);

  Status1 = gtBS->CloseProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   NULL,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER && Status1 == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid060,
                 L"BS.CloseProtocol - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  gtBS->CloseProtocol (Handle, &mTestProtocol1Guid, mImageHandle, NULL);


  //
  // Checkpoint 3:
  // 3.14.2.3   CloseProtocol should not succeed with invalid ControllerHandle
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   Handle,
                   EFI_OPEN_PROTOCOL_GET_PROTOCOL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.OpenProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  CreateInvalidHandle (&InvalidHandle);

  Status = gtBS->CloseProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   mImageHandle,
                   InvalidHandle
                   );
  ReleaseInvalidHandle (InvalidHandle);
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid061,
                 L"BS.CloseProtocol - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  gtBS->CloseProtocol (Handle, &mTestProtocol1Guid, mImageHandle, Handle);

  //
  // Checkpoint 4:
  // 3.14.2.4   CloseProtocol should not succeed with NULL protocol GUID
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_GET_PROTOCOL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.OpenProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  Status = gtBS->CloseProtocol (
                   Handle,
                   NULL,
                   mImageHandle,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid062,
                 L"BS.CloseProtocol - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  gtBS->CloseProtocol (Handle, &mTestProtocol1Guid, mImageHandle, NULL);

  //
  // Checkpoint 5:
  // 3.14.2.5   CloseProtocol should not succeed
  // when Handle does not support the protocol
  //
  Status = gtBS->OpenProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   (VOID **) &TestProtocol1,
                   mImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_GET_PROTOCOL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.OpenProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  Status = gtBS->CloseProtocol (
                   Handle,
                   &mTestProtocol2Guid,
                   mImageHandle,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid063,
                 L"BS.CloseProtocol - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  gtBS->CloseProtocol (Handle, &mTestProtocol1Guid, mImageHandle, NULL);

  //
  // Checkpoint 6:
  // 3.14.2.6   CloseProtocol should not succeed when the protocol is not opened.
  //
  Status = gtBS->CloseProtocol (
                   Handle,
                   &mTestProtocol1Guid,
                   mImageHandle,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid064,
                 L"BS.CloseProtocol - ConsistencyTestCheckpoint6",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = EFI_SUCCESS;

Done:
  //
  // Restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestProtocol1Guid, &TestProtocol1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}


/**
 *  @brief Entrypoint for gtBS->OpenProtocolInformation() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.15
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInformationConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HANDLE                            Handle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY   *EntryBuffer;
  UINTN                                 EntryCount;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  EntryBuffer = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Install TestProtocol1 onto a new handle.
  // ##1 destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid,
                   &TestProtocol1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }


  //
  // Checkpoint 1:
  // 3.15.2.1   OpenProtocolInformation should not succeed
  // when Handle does not support the protocol
  //

  Status = gtBS->OpenProtocolInformation (
                   Handle,
                   &mTestProtocol2Guid,
                   &EntryBuffer,
                   &EntryCount
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid065,
                 L"BS.OpenProtocolInformation - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EntryBuffer != NULL) {
    gtBS->FreePool (EntryBuffer);
  }

  //
  // Restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestProtocol1Guid, &TestProtocol1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->ConnectController() Consistency Test.
 *         2 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.16
//
EFI_STATUS
EFIAPI
BBTestConnectControllerConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_HANDLE                            Handle;
  EFI_HANDLE                            InvalidHandle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 Index;
  BOOLEAN                               Recursive[2];

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Install TestProtocol1 onto a new handle.
  // ##1 destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid,
                   &TestProtocol1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }


  //
  // Checkpoint 1:
  // 3.16.2.1   ConnectController should not succeed
  // with invalid ControllerHandle
  //

  CreateInvalidHandle (&InvalidHandle);

  Status = gtBS->ConnectController (
                   InvalidHandle,
                   NULL,
                   NULL,
                   FALSE
                   );
  ReleaseInvalidHandle (InvalidHandle);

  Status1 = gtBS->ConnectController (
                    NULL,
                    NULL,
                    NULL,
                    FALSE
                    );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER && Status1 == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid066,
                 L"BS.ConnectController - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2:
  // 3.16.2.2   ConnectController should not succeed
  // when no drivers is associated with the ControllerHandle
  //
  Recursive[0] = TRUE;
  Recursive[1] = FALSE;
  for (Index = 0; Index < 2; Index++) {
    Status = gtBS->ConnectController (
                     Handle,
                     NULL,
                     NULL,
                     Recursive[Index]
                     );
    //
    // step 1: check return status
    //
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid067,
                   L"BS.ConnectController - ConsistencyTestCheckpoint2",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestProtocol1Guid, &TestProtocol1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->DisconnectController() Consistency Test.
 *         3 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.17
//
EFI_STATUS
EFIAPI
BBTestDisconnectControllerConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_HANDLE                            Handle;
  EFI_HANDLE                            InvalidHandle;
  TEST_PROTOCOL_1                       TestProtocol1Instance;
  EFI_TEST_ASSERTION                    AssertionType;

  UINTN                                 Numbers;
  //
  // Init
  //
  StandardLib = NULL;
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);

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

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // Install TestProtocol1 onto a new handle.
  // ##1 destroy before leave
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestProtocol1Guid,
                   &TestProtocol1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // ##2 destroy before leave
  //
  CreateInvalidHandle (&InvalidHandle);

  //
  // Checkpoint 1:
  // 3.17.2.1   DisconnectController should not succeed
  // with invalid ControllerHandle
  //
  Status = gtBS->DisconnectController (
                   InvalidHandle,
                   NULL,
                   NULL
                   );

  Status1 = gtBS->DisconnectController (
                    NULL,
                    NULL,
                    NULL
                    );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER && Status1 == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid068,
                 L"BS.DisconnectController - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2:
  // 3.17.2.2   DisconnectController should not succeed
  // with invalid DriverImageHandle
  //
  Status = gtBS->DisconnectController (
                   Handle,
                   InvalidHandle,
                   NULL
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid069,
                 L"BS.DisconnectController - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 3:
  // 3.17.2.3   DisconnectController should not succeed with invalid ChildHandle
  //
  Status = gtBS->DisconnectController (
                   Handle,
                   NULL,
                   InvalidHandle
                   );
  //
  // step 1: check return status
  //
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid070,
                 L"BS.DisconnectController - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Restore environment
  //
  ReleaseInvalidHandle (InvalidHandle);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestProtocol1Guid, &TestProtocol1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}
