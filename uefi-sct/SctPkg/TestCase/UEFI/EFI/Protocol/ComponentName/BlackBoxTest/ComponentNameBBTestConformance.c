/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    ComponentNameBBTestConformance.c

Abstract:

    for EFI Driver Component Name Protocol's Conformance Test

--*/

#include "SctLib.h"
#include "ComponentNameBBTest.h"

//
// some private functions declaration
//
STATIC
VOID
CreateInvalidHandle (
  OUT EFI_HANDLE  *InvalidHandle
  );

STATIC
VOID
ReleaseInvalidHandle (
  IN EFI_HANDLE    InvalidHandle
  );

STATIC
VOID
CreateDeviceHandle (
  OUT EFI_HANDLE  *DeviceHandle
  );

STATIC
VOID
ReleaseDeviceHandle (
  IN EFI_HANDLE    DeviceHandle
  );

STATIC
EFI_STATUS
FindMatchedDeviceHandle (
  IN  EFI_COMPONENT_NAME_PROTOCOL           *ComponentName,
  OUT EFI_HANDLE                            *ValidControllerHandle
  );

STATIC
EFI_STATUS
FindMatchedBusHandle (
  IN  EFI_COMPONENT_NAME_PROTOCOL           *ComponentName,
  OUT EFI_HANDLE                            *ValidBusHandle
  );

static
UINTN
GetNumberOfSupportedLanguages (
  OUT CHAR8         *SupportedLanguages
  );

STATIC
EFI_STATUS
SearchNextUnsupportedLanguageCode (
  IN OUT CHAR8         *SupportedLanguageCodeList,
  IN OUT UINTN         *NextHandle,
     OUT CHAR8         *UnsupportedLanguageCode
  );

//
// global variables
//
EFI_GUID mTestNoInterfaceProtocol1Guid = TEST_NO_INTERFACE_PROTOCOL_1_GUID;
EFI_GUID mTestNoInterfaceProtocol2Guid = TEST_NO_INTERFACE_PROTOCOL_2_GUID;

CHAR8     IsoLatinTable[][4] = {
            "eng",
            "chn"
};

/**
 *  @brief Entrypoint for GetDriverName() Conformance Test.
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 9.3.1
//
EFI_STATUS
EFIAPI
BBTestGetDriverNameConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_COMPONENT_NAME_PROTOCOL           *ComponentName;

  //
  // init
  //
  ComponentName = (EFI_COMPONENT_NAME_PROTOCOL*)ClientInterface;

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
  // 9.3.1.2.1  Call GetDriverName() with invalid parameters.
  //
  BBTestGetDriverNameConformanceTestCheckpoint1 (StandardLib, ComponentName);

  //
  // 9.3.1.2.2  Call GetDriverName() with unsupported Language.
  //
  BBTestGetDriverNameConformanceTestCheckpoint2 (StandardLib, ComponentName);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for GetControllerName() Conformance Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 9.3.2
//
EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_COMPONENT_NAME_PROTOCOL           *ComponentName;

  //
  // init
  //
  ComponentName = (EFI_COMPONENT_NAME_PROTOCOL*)ClientInterface;

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
  // 9.3.2.2.1  Call GetControllerName() with invalid parameters.
  //
  BBTestGetControllerNameConformanceTestCheckpoint1 (StandardLib, ComponentName);

  //
  // 9.3.2.2.2  Call GetControllerName() with unsupported Language.
  //
  BBTestGetControllerNameConformanceTestCheckpoint2 (StandardLib, ComponentName);

  //
  // 9.3.2.2.3  Call GetControllerName() with unsupported ControllerHandle
  // or ChildHandle.
  //
  BBTestGetControllerNameConformanceTestCheckpoint3 (StandardLib, ComponentName);

  BBTestGetControllerNameConformanceTestCheckpoint4 (StandardLib, ComponentName);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetDriverNameConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  CHAR8                                       SupportedLanguage[3];
  CHAR16                                      *DriverName;

  //
  // retrieve the first supported language
  //
  gtBS->CopyMem (SupportedLanguage, ComponentName->SupportedLanguages, 3);

  //
  // with Language being NULL.
  //
  Status = ComponentName->GetDriverName (
                            ComponentName,
                            NULL,
                            &DriverName
                            );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid001,
                 L"COMPONENT_NAME_PROTOCOL.GetDriverName - GetDriverName() returns EFI_INVALID_PARAMETER with NULL Language",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // with DriverName being NULL.
  //
  Status = ComponentName->GetDriverName (
                            ComponentName,
                            SupportedLanguage,
                            NULL
                            );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid002,
                 L"COMPONENT_NAME_PROTOCOL.GetDriverName - GetDriverName() returns EFI_INVALID_PARAMETER with NULL DriverName",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetDriverNameConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINTN                                       NextHandle = 0;
  CHAR8                                       UnsupportedLanguageCode[3];
  CHAR16                                      *DriverName;

  Status = SearchNextUnsupportedLanguageCode (
             ComponentName->SupportedLanguages,
             &NextHandle,
             UnsupportedLanguageCode
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not find unsupported language code",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_NOT_FOUND;
  }

  Status = ComponentName->GetDriverName (
                            ComponentName,
                            UnsupportedLanguageCode,
                            &DriverName
                            );
  if (EFI_UNSUPPORTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid003,
                 L"COMPONENT_NAME_PROTOCOL.GetDriverName - GetDriverName() returns EFI_UNSUPPORTED with unsupported language",
                 L"%a:%d: Language - %c%c%c, Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 UnsupportedLanguageCode[0],
                 UnsupportedLanguageCode[1],
                 UnsupportedLanguageCode[2],
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  InvalidHandle;
  EFI_HANDLE                                  ValidControllerHandle;
  EFI_HANDLE                                  ValidBusHandle;
  CHAR8                                       SupportedLanguage[3];
  CHAR16                                      *ControllerName;

  //
  // retrieve the first supported language
  //
  gtBS->CopyMem (SupportedLanguage, ComponentName->SupportedLanguages, 3);

  //
  // with invalid ControllerHandle
  //
  CreateInvalidHandle (&InvalidHandle);
  if (InvalidHandle != NULL) {
    Status = ComponentName->GetControllerName (
                              ComponentName,
                              InvalidHandle,
                              NULL,
                              SupportedLanguage,
                              &ControllerName
                              );
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConformanceTestAssertionGuid004,
                   L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_INVALID_PARAMETER with  invalid ControllerHandle",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    ReleaseInvalidHandle (InvalidHandle);
  }

  //
  // retrieve a bus handle that could be managed by the Component Name Protocol
  //
  Status = FindMatchedBusHandle (ComponentName, &ValidBusHandle);
  if (EFI_ERROR(Status)) {
   StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_WARNING,
                  gTestGenericFailureGuid,
                  L"Could not find matched bus handle",
                  L"%a:%d",
                  __FILE__,
                  (UINTN)__LINE__
                  );

  } else {

    //
    // with invalid ChildHandle
    //
    CreateInvalidHandle (&InvalidHandle);
    if (InvalidHandle != NULL) {
      Status = ComponentName->GetControllerName (
                                ComponentName,
                                ValidBusHandle,
                                InvalidHandle,
                                SupportedLanguage,
                                &ControllerName
                                );
      if (EFI_INVALID_PARAMETER == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gConformanceTestAssertionGuid005,
                     L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_INVALID_PARAMETER with invalid ChildHandle and non-device ControllerHandle",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      ReleaseInvalidHandle (InvalidHandle);
    }
  }

  //
  // retrieve a device handle that could be managed by the Component Name Protocol
  //
  Status = FindMatchedDeviceHandle (ComponentName, &ValidControllerHandle);
  if (EFI_ERROR(Status)) {
   StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_WARNING,
                  gTestGenericFailureGuid,
                  L"Could not find matched device handle",
                  L"%a:%d",
                  __FILE__,
                  (UINTN)__LINE__
                  );
    return EFI_NOT_FOUND;
  }

  //
  // with ControllerName being NULL
  //
  Status = ComponentName->GetControllerName (
                            ComponentName,
                            ValidControllerHandle,
                            NULL,
                            SupportedLanguage,
                            NULL
                            );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid006,
                 L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_INVALID_PARAMETER with NULL ControllerName",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // with Language being NULL
  //
  Status = ComponentName->GetControllerName (
                            ComponentName,
                            ValidControllerHandle,
                            NULL,
                            NULL,
                            &ControllerName
                            );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid007,
                 L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_INVALID_PARAMETER with NULL Language",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINTN                                       NextHandle = 0;
  CHAR8                                       UnsupportedLanguageCode[3];
  CHAR16                                      *ControllerName;
  EFI_HANDLE                                  ValidControllerHandle;

  Status = SearchNextUnsupportedLanguageCode (
             ComponentName->SupportedLanguages,
             &NextHandle,
             UnsupportedLanguageCode
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not find unsupported language code",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_NOT_FOUND;
  }

  //
  // retrieve a device handle that could be managed by the Component Name Protocol
  //
  Status = FindMatchedDeviceHandle (ComponentName, &ValidControllerHandle);
  if (EFI_ERROR(Status)) {
   StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_WARNING,
                  gTestGenericFailureGuid,
                  L"Could not find matched device handle",
                  L"%a:%d",
                  __FILE__,
                  (UINTN)__LINE__
                  );
    return EFI_NOT_FOUND;
  }

  Status = ComponentName->GetControllerName (
                            ComponentName,
                            ValidControllerHandle,
                            NULL,
                            UnsupportedLanguageCode,
                            &ControllerName
                            );
  if (EFI_UNSUPPORTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid008,
                 L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with unsupported language",
                 L"%a:%d: Language - %c%c%c, Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 UnsupportedLanguageCode[0],
                 UnsupportedLanguageCode[1],
                 UnsupportedLanguageCode[2],
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  DeviceHandle;
  EFI_HANDLE                                  ValidControllerHandle;
  EFI_HANDLE                                  ValidBusHandle;
  EFI_HANDLE                                  InvalidHandle;
  CHAR16                                      *ControllerName;
  CHAR8                                       SupportedLanguage[3];

  //
  // retrieve the first supported language
  //
  gtBS->CopyMem (SupportedLanguage, ComponentName->SupportedLanguages, 3);

  //
  // Create a virtual device handle
  //
  CreateDeviceHandle (&DeviceHandle);
  if (DeviceHandle != NULL) {
    //
    // Input this DeviceHandle as the ControllerHandle input
    // for the GetControllerName().
    //
    Status = ComponentName->GetControllerName (
                              ComponentName,
                              DeviceHandle,
                              NULL,
                              SupportedLanguage,
                              &ControllerName
                              );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConformanceTestAssertionGuid009,
                   L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with irrelevant ControllerHandle",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    // retrieve a bus handle that could be managed by the Component Name Protocol
    //
    Status = FindMatchedBusHandle (ComponentName, &ValidBusHandle);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"Could not find matched bus handle",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

    } else {

      //
      //  Input the device handle as the ChildHandle input
      //  for the GetControllerName()
      //
      Status = ComponentName->GetControllerName (
                                ComponentName,
                                ValidBusHandle,
                                DeviceHandle,
                                SupportedLanguage,
                                &ControllerName
                                );
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gConformanceTestAssertionGuid010,
                     L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with irrelevant ChildHandle",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      ReleaseDeviceHandle (DeviceHandle);
    }
  }

  //
  // retrieve a device handle that could be managed by the Component Name Protocol
  //
  Status = FindMatchedDeviceHandle (ComponentName, &ValidControllerHandle);
  if (EFI_ERROR(Status)) {
   StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_WARNING,
                  gTestGenericFailureGuid,
                  L"Could not find matched device handle",
                  L"%a:%d",
                  __FILE__,
                  (UINTN)__LINE__
                  );
    return EFI_NOT_FOUND;
  }

  //
  // with invalid ChildHandle
  //
  CreateInvalidHandle (&InvalidHandle);
  if (InvalidHandle != NULL) {
    Status = ComponentName->GetControllerName (
                              ComponentName,
                              ValidControllerHandle,
                              InvalidHandle,
                              SupportedLanguage,
                              &ControllerName
                              );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConformanceTestAssertionGuid011,
                   L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with device handle and not-NULL ChildHandle",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    ReleaseInvalidHandle (InvalidHandle);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  UINTN                                       NoHandles;
  EFI_HANDLE                                  *HandleBuffer;
  UINTN                                       Index1, Index2;
  CHAR8                                       SupportedLanguage[3];
  CHAR16                                      *ControllerName;
  EFI_TEST_ASSERTION                          AssertionType;

  Index1    = 0;
  Index2    = 0;
  NoHandles = 0;

  //
  // retrieve the first supported language
  //
  gtBS->CopyMem (SupportedLanguage, ComponentName->SupportedLanguages, 3);

  Status = gtBS->LocateHandleBuffer (
                 AllHandles,
                 NULL,
                 NULL,
                 &NoHandles,
                 &HandleBuffer
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                    StandardLib,
                    EFI_TEST_ASSERTION_WARNING,
                    gTestGenericFailureGuid,
                    L"Could not find any handle",
                    L"%a:%d, Status - %r",
                    __FILE__,
                    (UINTN)__LINE__,
                    Status
                    );
    return EFI_NOT_FOUND;
  }

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index1 = 0; Index1 < NoHandles; Index1++) {
    Status = ComponentName->GetControllerName (
                               ComponentName,
                               HandleBuffer[Index1],
                               NULL,
                               SupportedLanguage,
                               &ControllerName
                               );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
	  break;
    }
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gConformanceTestAssertionGuid012,
                  L"EFI_COMPONENT_NAME_PROTOCOL.GetControllerName - Go through each of the handles",
                  L"%a:%d, Status - %r, Index1 - %d, NoHandles - %d",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status,
                  Index1,
                  NoHandles
                  );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index1 = 0; Index1 < NoHandles; Index1++) {
  	for (Index2 = 0; Index2 < NoHandles; Index2++) {
      Status = ComponentName->GetControllerName (
                                 ComponentName,
                                 HandleBuffer[Index1],
                                 HandleBuffer[Index2],
                                 SupportedLanguage,
                                 &ControllerName
                                 );
      if (Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gConformanceTestAssertionGuid013,
                  L"EFI_COMPONENT_NAME_PROTOCOL.GetControllerName - Go through each of the handles and child handles",
                  L"%a:%d, Status - %r, Index1 - %d, Index2 - %d, NoHandles - %d",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status,
                  Index1,
                  Index2,
                  NoHandles
                  );

  gtBS->FreePool (HandleBuffer);
  return EFI_SUCCESS;
}

//
// private functions
//

/**
 *  @brief This function create an invalid handle. To avoid memory leak,
 *         it is stronggly recommended to pare with ReleaseInvalidHandle.
 *  @see ReleaseInvalidHandle.
 */
STATIC
VOID
CreateInvalidHandle (
  OUT EFI_HANDLE  *InvalidHandle
  )
{
  EFI_HANDLE                  Handle = NULL;
  EFI_STATUS                  Status;

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    *InvalidHandle = NULL;
  } else {
    //
    // When restore the environment, the valid handle should be
    // (EFI_HANDLE)((UINT8*)InvalidHandle + 8)
    //
    *InvalidHandle = (EFI_HANDLE)((UINT8*)Handle + 8);
  }
}

STATIC
VOID
ReleaseInvalidHandle (
  IN EFI_HANDLE    InvalidHandle
  )
{
  EFI_HANDLE              ValidHandle;

  if (InvalidHandle == NULL) {
    return;
  }

  ValidHandle = (EFI_HANDLE)((UINT8*)InvalidHandle - 8);

  gtBS->UninstallProtocolInterface (ValidHandle, &mTestNoInterfaceProtocol1Guid, NULL);
}

STATIC
VOID
CreateDeviceHandle (
  OUT EFI_HANDLE  *DeviceHandle
  )
{
  EFI_HANDLE                  Handle = NULL;
  EFI_STATUS                  Status;

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    *DeviceHandle = NULL;
  } else {
    *DeviceHandle = Handle;
  }
}

STATIC
VOID
ReleaseDeviceHandle (
  IN EFI_HANDLE    DeviceHandle
  )
{
  if (DeviceHandle == NULL) {
    return;
  }

  gtBS->UninstallProtocolInterface (DeviceHandle, &mTestNoInterfaceProtocol2Guid, NULL);
}

STATIC
EFI_STATUS
FindMatchedDeviceHandle (
  IN  EFI_COMPONENT_NAME_PROTOCOL           *ComponentName,
  OUT EFI_HANDLE                            *ValidControllerHandle
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               NoHandles;
  EFI_HANDLE          *HandleBuffer;
  EFI_HANDLE          ComponentNameHandle = NULL;
  UINTN               ControllerHandleCount;
  EFI_HANDLE          *ControllerHandleBuffer;

  EFI_COMPONENT_NAME_PROTOCOL           *TestedComponentName;

  //
  // locate all component name protocol instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiComponentNameProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the component name protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiComponentNameProtocolGuid,
                     (VOID **) &TestedComponentName
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (TestedComponentName == ComponentName) {
      ComponentNameHandle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (ComponentNameHandle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the component name handle.
  //
  Status = SctGetManagedControllerHandles (
             ComponentNameHandle,
             &ControllerHandleCount,
             &ControllerHandleBuffer
             );
  if (EFI_ERROR(Status) || (ControllerHandleCount == 0)) {
    return EFI_NOT_FOUND;
  }

  *ValidControllerHandle = ControllerHandleBuffer[0];

  gtBS->FreePool (ControllerHandleBuffer);

  return Status;
}

STATIC
EFI_STATUS
FindMatchedBusHandle (
  IN  EFI_COMPONENT_NAME_PROTOCOL           *ComponentName,
  OUT EFI_HANDLE                            *ValidBusHandle
  )
/*
  The method is: locate all bus handles, and feed in until finding the first handle
  that make the GetControllerName return EFI_SUCCESS.
*/
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               NoHandles;
  EFI_HANDLE          *HandleBuffer;
  EFI_HANDLE          ComponentNameHandle = NULL;
  UINTN               ControllerHandleCount;
  EFI_HANDLE          *ControllerHandleBuffer;
  UINTN               NumberOfChildren;
  EFI_HANDLE          *ChildControllerHandleBuffer;

  EFI_COMPONENT_NAME_PROTOCOL           *TestedComponentName;

  //
  // locate all component name protocol instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiComponentNameProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the component name protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiComponentNameProtocolGuid,
                     (VOID **) &TestedComponentName
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (TestedComponentName == ComponentName) {
      ComponentNameHandle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (ComponentNameHandle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the component name handle.
  //
  Status = SctGetManagedControllerHandles (
             ComponentNameHandle,
             &ControllerHandleCount,
             &ControllerHandleBuffer
             );
  if (EFI_ERROR(Status) || (ControllerHandleCount == 0)) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < ControllerHandleCount; Index++) {
    ChildControllerHandleBuffer = NULL;

    Status = SctGetManagedChildControllerHandles (
               ComponentNameHandle,
               ControllerHandleBuffer[Index],
               &NumberOfChildren,
               &ChildControllerHandleBuffer
               );
    if ((EFI_SUCCESS == Status) && (NumberOfChildren != 0)) {
      *ValidBusHandle = ControllerHandleBuffer[Index];
      gtBS->FreePool (ControllerHandleBuffer);
      gtBS->FreePool (ChildControllerHandleBuffer);
      return EFI_SUCCESS;
    }
  }

  gtBS->FreePool (ControllerHandleBuffer);

  return EFI_NOT_FOUND;
}

STATIC
UINTN
GetNumberOfSupportedLanguages (
  IN OUT CHAR8         *SupportedLanguages
  )
{
  UINTN         Count = 0;

  while (*SupportedLanguages != 0) {
    SupportedLanguages += 3;
    Count++;
  }

  return Count;
}

STATIC
EFI_STATUS
SearchNextUnsupportedLanguageCode (
  IN OUT CHAR8         *SupportedLanguageCodeList,
  IN OUT UINTN         *NextHandle,
     OUT CHAR8         *UnsupportedLanguageCode
  )
/*
  NextHandle maps with the Index in the IsoLatin table. The relation is:

    NextHandle = Index + 1.

  if NextHandle == 0, then the search begins from the start of the IsoLatin table.

  if NextHandle != 0, then the search begins from the Index (Index = NextHandle).

*/
{
  UINTN                 TableItem;
  UINTN                 StartIndex;
  UINTN                 SupportedNumber;
  CHAR8                 *Pointer;
  UINTN                 Indexi, Indexj;

  StartIndex = *NextHandle;

  TableItem = sizeof (IsoLatinTable) / sizeof (*IsoLatinTable);

  if (StartIndex >= TableItem) {
    return EFI_NOT_FOUND;
  }

  SupportedNumber = GetNumberOfSupportedLanguages (SupportedLanguageCodeList);

  for (Indexi = StartIndex; Indexi < TableItem; Indexi++) {

    Pointer = SupportedLanguageCodeList;

    for (Indexj = 0; Indexj < SupportedNumber; Indexj++) {

      if (SctCompareMem (Pointer, IsoLatinTable[Indexi], 3)) {
        *NextHandle = Indexi + 1;
        gtBS->CopyMem (UnsupportedLanguageCode, IsoLatinTable[Indexi], 3);
        return EFI_SUCCESS;
      }

      Pointer += 3;
    }
  }

  return EFI_NOT_FOUND;
}
