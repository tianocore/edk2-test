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

    DriverDiagnosticsBBTestConformance.c

Abstract:

    for EFI Driver Diagnostics Protocol's generic Conformance Test

--*/

#include "SctLib.h"
#include "DriverDiagnosticsBBTest.h"

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
  IN  EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics,
  OUT EFI_HANDLE                            *ValidControllerHandle
  );

STATIC
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
 *  @brief Entrypoint for RunDiagnostics() Conformance Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 7.2.1
//
EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics;

  //
  // init
  //
  DriverDiagnostics = (EFI_DRIVER_DIAGNOSTICS_PROTOCOL*)ClientInterface;

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
  // 7.2.1.2.1  Call RunDiagnostics() with invalid parameters.
  //
  BBTestRunDiagnosticsConformanceTestCheckpoint1 (StandardLib, DriverDiagnostics);

  //
  // 7.2.1.2.2  Call RunDiagnostics() with unsupported Language.
  //
  BBTestRunDiagnosticsConformanceTestCheckpoint2 (StandardLib, DriverDiagnostics);

  //
  // 7.2.1.2.3  Call RunDiagnostics() with unsupported ControllerHandle.
  //
  BBTestRunDiagnosticsConformanceTestCheckpoint3 (StandardLib, DriverDiagnostics);

  return EFI_SUCCESS;
}

/**
 *  @brief checkpoint3 for RunDiagnostic() Conformance Test
 *  @param StandardLib A pointer of the standard test library
 *  @param DriverConfig This a pointer of EFI_BB_TEST_PROTOCOL
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// 7.2.1.2.1  Call RunDiagnostic() with invalid parameters
//
EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  InvalidHandle;
  EFI_HANDLE                                  ValidControllerHandle;
  CHAR8                                       SupportedLanguage[3];
  EFI_GUID                                    *ErrorType;
  UINTN                                       BufferSize;
  CHAR16                                      *Buffer;

  //
  // Init
  //
  Buffer = NULL;

  //
  // retrieve the first supported language
  //
  gtBS->CopyMem (SupportedLanguage, DriverDiagnostics->SupportedLanguages, 3);

  //
  // with invalid ControllerHandle
  //
  CreateInvalidHandle (&InvalidHandle);
  if (NULL == InvalidHandle){
   StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not find invalid device handle",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_NOT_FOUND;
  }

  Status = DriverDiagnostics->RunDiagnostics (
                                DriverDiagnostics,
                                InvalidHandle,
                                NULL,
                                0,
                                SupportedLanguage,
                                &ErrorType,
                                &BufferSize,
                                &Buffer
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
                 L"EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics - RunDiagnostics() returns EFI_INVALID_PARAMETER with invalid ControllerHandle",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  ReleaseInvalidHandle (InvalidHandle);
  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
    Buffer = NULL;
  }

  //
  // retrieve a device handle that could be managed by the Driver Diagnostics Protocol
  //
  Status = FindMatchedDeviceHandle (DriverDiagnostics, &ValidControllerHandle);
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
  // with Language being NULL.
  //
  Status = DriverDiagnostics->RunDiagnostics (
                                DriverDiagnostics,
                                ValidControllerHandle,
                                NULL,
                                0,
                                NULL,
                                &ErrorType,
                                &BufferSize,
                                &Buffer
                                );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid003,
                 L"EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics - RunDiagnostics() returns EFI_INVALID_PARAMETER with Language being NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
    Buffer = NULL;
  }

  //
  // with ErrorType being NULL.
  //
  Status = DriverDiagnostics->RunDiagnostics (
                                DriverDiagnostics,
                                ValidControllerHandle,
                                NULL,
                                0,
                                SupportedLanguage,
                                NULL,
                                &BufferSize,
                                &Buffer
                                );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid004,
                 L"RunDiagnostics Conformance Test - Checkpoint1",
                 L"%a:%d:NULL ErrorType Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
    Buffer = NULL;
  }

  //
  // with BufferSize being NULL.
  //
  Status = DriverDiagnostics->RunDiagnostics (
                                DriverDiagnostics,
                                ValidControllerHandle,
                                NULL,
                                0,
                                SupportedLanguage,
                                &ErrorType,
                                NULL,
                                &Buffer
                                );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid005,
                 L"RunDiagnostics Conformance Test - Checkpoint1",
                 L"%a:%d:NULL BufferSize Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
    Buffer = NULL;
  }

  //
  // with Buffer being NULL.
  //
  Status = DriverDiagnostics->RunDiagnostics (
                                DriverDiagnostics,
                                ValidControllerHandle,
                                NULL,
                                0,
                                SupportedLanguage,
                                &ErrorType,
                                &BufferSize,
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
                 gConformanceTestAssertionGuid006,
                 L"RunDiagnostics Conformance Test - Checkpoint1",
                 L"%a:%d:NULL Buffer Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  @brief checkpoint3 for RunDiagnostic() Conformance Test
 *  @param StandardLib A pointer of the standard test library
 *  @param DriverConfig This a pointer of EFI_BB_TEST_PROTOCOL
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// 7.2.1.2.2  Call RunDiagnostic() with all unsupported languages
//
EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  ValidControllerHandle;
  UINTN                                       NextHandle = 0;
  CHAR8                                       UnsupportedLanguageCode[3];
  EFI_GUID                                    *ErrorType;
  UINTN                                       BufferSize;
  CHAR16                                      *Buffer = NULL;


  //
  // retrieve a device handle that could be managed by the Driver Diagnostics Protocol
  //
  Status = FindMatchedDeviceHandle (DriverDiagnostics, &ValidControllerHandle);
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
  // Try RunDiagnostics() with all unsupported languages
  //
  while(1){
    Status = SearchNextUnsupportedLanguageCode (
               DriverDiagnostics->SupportedLanguages,
               &NextHandle,
               UnsupportedLanguageCode
               );
    if(EFI_ERROR(Status)){
      if(0 == NextHandle){
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
      break ;
    }

    Status = DriverDiagnostics->RunDiagnostics (
                                  DriverDiagnostics,
                                  ValidControllerHandle,
                                  NULL,
                                  0,
                                  UnsupportedLanguageCode,
                                  &ErrorType,
                                  &BufferSize,
                                  &Buffer
                                  );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConformanceTestAssertionGuid007,
                   L"RunDiagnostics Conformance Test - Checkpoint2",
                   L"%a:%d: Unsupported Language Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
      Buffer = NULL ;
    }

  }

  return EFI_SUCCESS;
}

/**
 *  @brief checkpoint3 for RunDiagnostic() Conformance Test
 *  @param StandardLib A pointer of the standard test library
 *  @param DriverConfig This a pointer of EFI_BB_TEST_PROTOCOL
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// 7.2.1.2.3  Call RunDiagnostic() with unsupported controller
//
EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  DeviceHandle;
  CHAR8                                       SupportedLanguage[3];
  EFI_GUID                                    *ErrorType;
  UINTN                                       BufferSize;
  CHAR16                                      *Buffer;


  //
  // retrieve the first supported language
  //
  gtBS->CopyMem (SupportedLanguage, DriverDiagnostics->SupportedLanguages, 3);

  //
  // Create a virtual device handle
  //
  CreateDeviceHandle (&DeviceHandle);
  if (NULL == DeviceHandle){
   StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not find a virtual device handle",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_NOT_FOUND;
  }

  Status = DriverDiagnostics->RunDiagnostics (
                                DriverDiagnostics,
                                DeviceHandle,
                                NULL,
                                0,
                                SupportedLanguage,
                                &ErrorType,
                                &BufferSize,
                                &Buffer
                                );
  if (EFI_UNSUPPORTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid008,
                 L"RunDiagnostics Conformance Test - Checkpoint3",
                 L"%a:%d: Unsupported Controller Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // free resources
  //
  ReleaseDeviceHandle (DeviceHandle);
  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
    Buffer = NULL ;
  }

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

  Status = gtBS->InstallProtocolInterface(
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

/**
 *  @brief This function create an virtual device handle. To avoid memory leak,
 *         it is stronggly recommended to pare with ReleaseDeviceHandle.
 *  @see ReleaseInvalidHandle.
 */
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
    DeviceHandle = NULL;
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

/**
 *  @brief This function retrieves a device handle that could be managed by the Driver Config Protocol
 *  @return EFI_SUCCESS
 *  @return Execution Status
 */
STATIC
EFI_STATUS
FindMatchedDeviceHandle (
  IN  EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics,
  OUT EFI_HANDLE                            *ValidControllerHandle
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               NoHandles;
  EFI_HANDLE          *HandleBuffer;
  EFI_HANDLE          DriverDiagnosticsHandle = NULL;
  UINTN               ControllerHandleCount;
  EFI_HANDLE          *ControllerHandleBuffer;

  EFI_DRIVER_DIAGNOSTICS_PROTOCOL     *TestedDriverDiagnostics;

  //
  // locate all Driver Diagnostics protocol instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiDriverDiagnosticsProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the Driver Diagnostics protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiDriverDiagnosticsProtocolGuid,
                     (VOID **) &TestedDriverDiagnostics
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (TestedDriverDiagnostics == DriverDiagnostics) {
      DriverDiagnosticsHandle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (DriverDiagnosticsHandle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the DriverDiagnosticsHandle.
  //
  Status = SctGetManagedControllerHandles (
             DriverDiagnosticsHandle,
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

/**
 *  @brief This function caculates the total number of supported languages
 *  @param SupportedLanguges This a string indicating supported language codes
 *  @return the count of supported languages
 */
static
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


/**
 *  @brief This function caculates the number of supported languages
 *  @param SupportedLanguges This a string indicating supported languages
 *  @param NextHandle This a point indicating starting position in IsoLatin table
 *  @param UnsupportedLangugeCode This a string containing returned unsupported language code
 *  @return EFI_SUCESS
 *  @return EFI_NOT_FOUND
 */
STATIC
EFI_STATUS
SearchNextUnsupportedLanguageCode (
  IN OUT CHAR8         *SupportedLanguageCodeList,
  IN OUT UINTN         *NextHandle,
     OUT CHAR8         *UnsupportedLanguageCode
  )
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
      if (SctCompareMem (Pointer, IsoLatinTable[Indexi], 3) == 0) {
        break ;
      }
      Pointer += 3;
    }

    if(SupportedNumber == Indexj){
      *NextHandle = Indexi + 1;
      gtBS->CopyMem (UnsupportedLanguageCode, IsoLatinTable[Indexi], 3);
      return EFI_SUCCESS;
    }

  }

  return EFI_NOT_FOUND;
}
