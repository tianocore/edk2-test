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

  DriverBindingBBTestFunction.c

Abstract:

  for EFI Driver Binding Protocol's Function Test

--*/

#include "SctLib.h"
#include "DriverBindingBBTest.h"
#include "../../../../../../TestInfrastructure/SCT/Drivers/StandardTest/StandardTest.h"

CHAR16 *DashLine = L"------------------------------------------------------------\r\n";
#define IS_LEAP(y) (((((y) % 4) == 0) && (((y) % 100) != 0)) || (((y) % 400) == 0))

static const UINTN  MonthLengths[2][12] = {
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

static EFI_TIME Epoch = { .Year = 1970, .Month = 1, .Day = 1 };

#define MINS_PER_HOUR       60
#define HOURS_PER_DAY       24
#define SECS_PER_MIN        60
#define SECS_PER_HOUR       (SECS_PER_MIN * MINS_PER_HOUR)
#define SECS_PER_DAY        (SECS_PER_HOUR * HOURS_PER_DAY)
#define DAYS_PER_NYEAR      365
#define DAYS_PER_LYEAR      366

//
// Definitions
//

#define DRIVER_BINDING_EMPTY                                    0xFF

#define DRIVER_BINDING_SUPPORTED_INVOKE                         0x00
#define DRIVER_BINDING_SUPPORTED_RETURN_SUCCESS                 0x01
#define DRIVER_BINDING_SUPPORTED_RETURN_ALREADY_STARTED         0x02
#define DRIVER_BINDING_SUPPORTED_RETURN_ACCESS_DENIED           0x03
#define DRIVER_BINDING_SUPPORTED_RETURN_UNSUPPORTED             0x04

#define DRIVER_BINDING_START_INVOKE                             0x10
#define DRIVER_BINDING_START_RETURN_SUCCESS                     0x11
#define DRIVER_BINDING_START_RETURN_DEVICE_ERROR                0x12
#define DRIVER_BINDING_START_RETURN_OUT_OF_RESOURCES            0x13

#define DRIVER_BINDING_STOP_INVOKE                              0x20
#define DRIVER_BINDING_STOP_RETURN_SUCCESS                      0x21

typedef struct _DRIVER_BINDING_CHECK {
  UINT32                ID;
  EFI_GUID              Guid;
  EFI_TEST_ASSERTION    AssertionType;
  CHAR16                *Title;
} DRIVER_BINDING_CHECK;

DRIVER_BINDING_CHECK  mDriverBindingCheck[] = {
  {
    DRIVER_BINDING_SUPPORTED_INVOKE,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_001_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Supported() service gets called."
  },
  {
    DRIVER_BINDING_SUPPORTED_RETURN_SUCCESS,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_002_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Supported() service returns EFI_SUCCESS with supported handle."
  },
  {
    DRIVER_BINDING_SUPPORTED_RETURN_ALREADY_STARTED,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_003_GUID,
    EFI_TEST_ASSERTION_WARNING,
    L"Supported() service returns EFI_ALREADY_STARTED with managed handle."
  },
  {
    DRIVER_BINDING_SUPPORTED_RETURN_ACCESS_DENIED,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_004_GUID,
    EFI_TEST_ASSERTION_WARNING,
    L"Supported() service returns EFI_ACCESS_DENIED with managed handle by other."
  },
  {
    DRIVER_BINDING_SUPPORTED_RETURN_UNSUPPORTED,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_005_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Supported() service returns EFI_UNSUPPORTED with unsupported handle."
  },
  {
    DRIVER_BINDING_START_INVOKE,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_006_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Start() service gets called."
  },
  {
    DRIVER_BINDING_START_RETURN_SUCCESS,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_007_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Start() service returns EFI_SUCCESS with supported handle."
  },
  {
    DRIVER_BINDING_START_RETURN_DEVICE_ERROR,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_008_GUID,
    EFI_TEST_ASSERTION_WARNING,
    L"Start() service returns EFI_DEVICE_ERROR due to a device error."
  },
  {
    DRIVER_BINDING_START_RETURN_OUT_OF_RESOURCES,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_009_GUID,
    EFI_TEST_ASSERTION_WARNING,
    L"Start() service returns EFI_OUT_OF_RESOURCES due to resources limitation."
  },
  {
    DRIVER_BINDING_STOP_INVOKE,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_010_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Stop() service gets called."
  },
  {
    DRIVER_BINDING_STOP_RETURN_SUCCESS,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_011_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Stop() service returns EFI_SUCCESS with supported handle."
  },
  {
    DRIVER_BINDING_EMPTY
  }
};

EFI_DRIVER_BINDING_SUPPORTED  mOldDriverBindingSupported;
EFI_DRIVER_BINDING_START      mOldDriverBindingStart;
EFI_DRIVER_BINDING_STOP       mOldDriverBindingStop;

//
// Internal function declarations
//

EFI_STATUS
EFIAPI
ProxySupported (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
ProxyStart (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
ProxyStop (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN UINTN                                  NumberOfChildren,
  IN EFI_HANDLE                             * ChildHandleBuffer
  );

VOID
SetCheckResult (
  IN UINT32                                 ID,
  IN EFI_TEST_ASSERTION                     AssertionType
  );

STATIC
EFI_STATUS
EFIAPI
RecordAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_TEST_ASSERTION                     Type,
  IN EFI_GUID                               EventId,
  IN CHAR16                                 *Description,
  IN CHAR16                                 *Detail,
  ...
  );

VOID
EFIAPI
EndLogging (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_STATUS                             Status
  );

//
// External function implementations
//

EFI_STATUS
BBTestDriverBindingFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_STATUS                           Status;
  EFI_DRIVER_BINDING_PROTOCOL          *DriverBinding;
  UINTN                                Index;
  UINTN                                NoHandles;
  EFI_HANDLE                           *HandleBuffer;
  DRIVER_BINDING_CHECK                 *Check;
  EFI_DEVICE_PATH_PROTOCOL             *ProfileDevicePath;
  CHAR16                               *ProfileFilePath;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
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
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle test profile library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    return Status;
  }

  DriverBinding = (EFI_DRIVER_BINDING_PROTOCOL *)ClientInterface;

  //
  // Redirect the Driver Binding services to the proxy services
  //
  mOldDriverBindingSupported  = DriverBinding->Supported;
  mOldDriverBindingStart      = DriverBinding->Start;
  mOldDriverBindingStop       = DriverBinding->Stop;

  DriverBinding->Supported  = ProxySupported;
  DriverBinding->Start      = ProxyStart;
  DriverBinding->Stop       = ProxyStop;

  //
  // Disconnect all handles
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
/*  	
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - Locate all handles",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
*/
    DriverBinding->Supported  = mOldDriverBindingSupported;
    DriverBinding->Start      = mOldDriverBindingStart;
    DriverBinding->Stop       = mOldDriverBindingStop;

    return Status;
  }

  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &ProfileDevicePath,
                         &ProfileFilePath
                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiDevicePathProtocolGuid,
                    (VOID **) &DevicePath
                    );
    if (!EFI_ERROR (Status)) {
      if (SctMatchDevicePaths (ProfileDevicePath, DevicePath)) {
        continue;
      }
    }

    Status = gtBS->DisconnectController (
                    HandleBuffer[Index],
                    NULL,
                    NULL
                    );
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Connect all handles
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
/*
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - Locate all handles",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
*/
    DriverBinding->Supported  = mOldDriverBindingSupported;
    DriverBinding->Start      = mOldDriverBindingStart;
    DriverBinding->Stop       = mOldDriverBindingStop;

    return Status;
  }

  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->ConnectController (
                    HandleBuffer[Index],
                    NULL,
                    NULL,
                    TRUE
                    );
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Connect all handles again
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
/*
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - Locate all handles",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
*/
    DriverBinding->Supported  = mOldDriverBindingSupported;
    DriverBinding->Start      = mOldDriverBindingStart;
    DriverBinding->Stop       = mOldDriverBindingStop;

    return Status;
  }

  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->ConnectController (
                    HandleBuffer[Index],
                    NULL,
                    NULL,
                    TRUE
                    );
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Restore back the redirected Driver Binding services
  //
  DriverBinding->Supported  = mOldDriverBindingSupported;
  DriverBinding->Start      = mOldDriverBindingStart;
  DriverBinding->Stop       = mOldDriverBindingStop;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    return Status;
  }

  //
  // Record the test results
  //
  for (Check = mDriverBindingCheck; Check->ID != DRIVER_BINDING_EMPTY; Check++) {
    RecordAssertion(
                   StandardLib,
                   Check->AssertionType,
                   Check->Guid,
                   Check->Title,
                   L"%a:%d:CheckId - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Check->ID
                 );
	
  }

  EndLogging(StandardLib, Status);

  return EFI_SUCCESS;
}

//
// Internal function implementations
//

EFI_STATUS
EFIAPI
ProxySupported (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  )
{
  EFI_STATUS  Status;

  SetCheckResult (
    DRIVER_BINDING_SUPPORTED_INVOKE,
    EFI_TEST_ASSERTION_PASSED
    );

  Status = (* mOldDriverBindingSupported) (
             This,
             ControllerHandle,
             RemainingDevicePath
             );

  switch (Status) {
  case EFI_SUCCESS:
    SetCheckResult (
      DRIVER_BINDING_SUPPORTED_RETURN_SUCCESS,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_ALREADY_STARTED:
    SetCheckResult (
      DRIVER_BINDING_SUPPORTED_RETURN_ALREADY_STARTED,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_ACCESS_DENIED:
    SetCheckResult (
      DRIVER_BINDING_SUPPORTED_RETURN_ACCESS_DENIED,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_UNSUPPORTED:
    SetCheckResult (
      DRIVER_BINDING_SUPPORTED_RETURN_UNSUPPORTED,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  default:
    break;
  }

  return Status;
}

EFI_STATUS
EFIAPI
ProxyStart (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  )
{
  EFI_STATUS  Status;

  SetCheckResult (
    DRIVER_BINDING_START_INVOKE,
    EFI_TEST_ASSERTION_PASSED
    );

  Status = (* mOldDriverBindingStart) (
             This,
             ControllerHandle,
             RemainingDevicePath
             );

  switch (Status) {
  case EFI_SUCCESS:
    SetCheckResult (
      DRIVER_BINDING_START_RETURN_SUCCESS,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_DEVICE_ERROR:
    SetCheckResult (
      DRIVER_BINDING_START_RETURN_DEVICE_ERROR,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_OUT_OF_RESOURCES:
    SetCheckResult (
      DRIVER_BINDING_START_RETURN_OUT_OF_RESOURCES,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  default:
    break;
  }

  return Status;
}

EFI_STATUS
EFIAPI
ProxyStop (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN UINTN                                  NumberOfChildren,
  IN EFI_HANDLE                             * ChildHandleBuffer
  )
{
  EFI_STATUS  Status;

  SetCheckResult (
    DRIVER_BINDING_STOP_INVOKE,
    EFI_TEST_ASSERTION_PASSED
    );

  Status = (* mOldDriverBindingStop) (
             This,
             ControllerHandle,
             NumberOfChildren,
             ChildHandleBuffer
             );

  switch (Status) {
  case EFI_SUCCESS:
    SetCheckResult (
      DRIVER_BINDING_STOP_RETURN_SUCCESS,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  default:
    break;
  }

  return Status;
}

VOID
SetCheckResult (
  IN UINT32                                 ID,
  IN EFI_TEST_ASSERTION                     AssertionType
  )
{
  DRIVER_BINDING_CHECK  *Check;

  for (Check = mDriverBindingCheck; Check->ID != DRIVER_BINDING_EMPTY; Check++) {
    if (Check->ID == ID) {
      Check->AssertionType = AssertionType;
      break;
    }
  }
}

UINT32
SecondsElapsedFromBaseYear (
  IN UINT16             BaseYear,
  IN UINT16             Year,
  IN UINT8              Month,
  IN UINT8              Day,
  IN UINT8              Hour,
  IN UINT8              Minute,
  IN UINT8              Second
  )
{
  UINTN       Seconds;
  UINT32      LeapYear;
  INTN        Index;

  Seconds  = 0;
  for (Index = BaseYear; Index < Year; Index ++) {
    if (IS_LEAP(Index)) {
      Seconds += DAYS_PER_LYEAR * SECS_PER_DAY;
    } else {
      Seconds += DAYS_PER_NYEAR * SECS_PER_DAY;
    }
  }

  LeapYear = IS_LEAP(Year);
  for (Index = 0; Index < Month - 1; Index ++) {
    Seconds += MonthLengths[LeapYear][Index] * SECS_PER_DAY;
  }

  for (Index = 0; Index < Day - 1; Index ++) {
    Seconds += SECS_PER_DAY;
  }

  for (Index = 0; Index < Hour; Index ++) {
    Seconds += SECS_PER_HOUR;
  }

  for (Index = 0; Index < Minute; Index ++) {
    Seconds += SECS_PER_MIN;
  }

  return (UINT32) (Seconds + Second);
}

EFI_STATUS
MyUINTToStr (
  IN UINTN        Num,
  OUT CHAR16      *StringNum
)
{
  UINTN          CurrentNum;

  
  CurrentNum = Num % 10;
  Num = Num/10;
  
  StringNum[0] = (CHAR16)( L'0' + Num );
  StringNum[1] = (CHAR16)( L'0' + CurrentNum );
  StringNum[2] = '\0';
  
  return EFI_SUCCESS;
}


EFI_STATUS
WriteLogFile (
  IN STANDARD_TEST_PRIVATE_DATA   *Private,
  IN CHAR16                       *String,
  IN UINT8                        FileType
  )
{
  EFI_STATUS                        Status;
  EFI_DEVICE_PATH_PROTOCOL          *PreDevicePath;
  EFI_HANDLE                        DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_FILE_HANDLE                   RootDir;  
  EFI_FILE_HANDLE                   FileHandle;
  UINTN                             BufSize;

  Status     = EFI_SUCCESS;
  FileHandle = NULL;

  PreDevicePath = Private->SystemLogFile.DevicePath;

  //
  //  Determine device handle for fs protocol on specified device path
  //
  Status = gtBS->LocateDevicePath (
                   &gEfiSimpleFileSystemProtocolGuid,
                   &PreDevicePath,
                   &DeviceHandle
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  //  Determine volume for file system on device handle
  //
  Status = gtBS->HandleProtocol (
                   DeviceHandle,
                   &gEfiSimpleFileSystemProtocolGuid,
                   (VOID*)&Vol
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open volume for file system on device path
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Determine the existence of the file
  //
  switch (FileType) {
    case SYSTEMLOG:	
    Status = RootDir->Open (
                        RootDir,
                        &FileHandle,
                        Private->SystemLogFile.FileName,
                        EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                        0
                        );
    break;

    case CASELOG:
    Status = RootDir->Open (
                        RootDir,
                        &FileHandle,
                        Private->CaseLogFile.FileName,
                        EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                        0
                        );
    break;

    case SYSTEMKEY:	
    Status = RootDir->Open (
                        RootDir,
                        &FileHandle,
                        Private->SystemKeyFile.FileName,
                        EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                        0
                        );
    break;

    case CASEKEY:
    Status = RootDir->Open (
                        RootDir,
                        &FileHandle,
                        Private->CaseKeyFile.FileName,
                        EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                        0
                        );
    break;


	default:
	break;
  }

  if (FileHandle == NULL)
  	return Status;
 
  Status = FileHandle->SetPosition (FileHandle, (UINT64)-1);
  if (EFI_ERROR (Status)) {
    RootDir->Close (RootDir);
    return Status;
  }

  //
  // Write the String to the file
  //
  BufSize = SctStrLen(String) * 2;
  Status = FileHandle->Write (FileHandle, &BufSize, String);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = FileHandle->Flush (FileHandle);

  FileHandle->Close (FileHandle);

  return Status;
}



STATIC
EFI_STATUS
EFIAPI
RecordAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_TEST_ASSERTION                     Type,
  IN EFI_GUID                               EventId,
  IN CHAR16                                 *Description,
  IN CHAR16                                 *Detail,
  ...
  )
/*++

Routine Description:

  Records the test result.

Arguments:

  This          - Standard test library protocol instance.
  Type          - Test result.
  EventId       - GUID for the checkpoint.
  Description   - Simple description for the checkpoint.
  Detail        - Format string for the detail test information.

Returns:

  EFI_SUCCESS           - record the assertion successfully.
  EFI_BAD_BUFFER_SIZE   - the Description string is too long.
  EFI_INVALID_PARAMETER - invalid Type.

--*/
{
  EFI_STATUS                      Status;
  VA_LIST                         Marker;
  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  CHAR16                          AssertionType[10];
  STANDARD_TEST_PRIVATE_DATA      *Private;
  
  Private = STANDARD_TEST_PRIVATE_DATA_FROM_STSL (This);
  
  //
  // Check the parameter
  //
  if (SctStrLen (Description) + 14 > EFI_MAX_PRINT_BUFFER) {
    return EFI_BAD_BUFFER_SIZE;
  }

  //
  // Write log file detail data
  //
  switch (Type) {
  case EFI_TEST_ASSERTION_PASSED:
    SctStrCpy (AssertionType, L"PASS");
    Private->PassCount ++;
    break;
  case EFI_TEST_ASSERTION_WARNING:
    SctStrCpy (AssertionType, L"WARNING");
    Private->WarningCount ++;
    break;
  case EFI_TEST_ASSERTION_FAILED:
    SctStrCpy (AssertionType, L"FAILURE");
    Private->FailCount ++;
    break;
  default:
    return EFI_INVALID_PARAMETER;
    break;
  }

  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%s -- %s\n", Description, AssertionType);
  Status = WriteLogFile  (Private, Buffer, SYSTEMLOG);
  Status = WriteLogFile  (Private, Buffer, CASELOG);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%g\n", &EventId);
  Status = WriteLogFile  (Private, Buffer, SYSTEMLOG);
  Status = WriteLogFile  (Private, Buffer, CASELOG);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  VA_START(Marker, Detail);
  DBVSPrint (Buffer, EFI_MAX_PRINT_BUFFER, Detail, Marker);
  VA_END (Marker);

  if ( SctStrLen (Buffer) + 5 < EFI_MAX_PRINT_BUFFER ) {
    SctStrCat (Buffer, L"\r\n\r\n");
  }

  Status = WriteLogFile (Private, Buffer, SYSTEMLOG);
  Status = WriteLogFile (Private, Buffer, CASELOG);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Send assertion to remotion computer if the network 
  // record assertion utility installed.
  //
  // To disable the remotion assertion function in this case
  //NetRecordAssertion((NET_EFI_TEST_ASSERTION) Type, EventId, Buffer);
  
  //
  // write key file detail line
  //
  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%g:%s|%s:",
          &EventId, AssertionType, Description);
  Status = WriteLogFile (Private, Buffer, SYSTEMKEY);
  Status = WriteLogFile (Private, Buffer, CASEKEY);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  VA_START(Marker, Detail);
  DBVSPrint (Buffer, EFI_MAX_PRINT_BUFFER, Detail, Marker);
  VA_END (Marker);

  if ( SctStrLen (Buffer) + 3 < EFI_MAX_PRINT_BUFFER ) {
    SctStrCat (Buffer, L"\r\n");
  }

  Status = WriteLogFile (Private, Buffer, SYSTEMKEY);
  Status = WriteLogFile (Private, Buffer, CASEKEY);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return Status;
}

VOID
EFIAPI
EndLogging (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_STATUS                             Status
  )
{

  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  CHAR16                          Buffer1[EFI_MAX_PRINT_BUFFER];
  CHAR16                          Str[20];  
  STANDARD_TEST_PRIVATE_DATA      *Private;
  EFI_TIME                        CurrentTime;
  UINT32                          SecondsElapsed;
  UINT32                          DaysElapsed;
  UINT32                          HoursElapsed;
  UINT32                          MunitesElapsed;

  Private = STANDARD_TEST_PRIVATE_DATA_FROM_STSL (This);

  //
  // Write log file terminator data
  //
  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
          L"\nReturned Status Code: %r\n", Status);
  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);

  if ((Private->PassCount    > 0 ) &&
      (Private->WarningCount == 0) &&
      (Private->FailCount    == 0)) {
    DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
            L"\n%s: [PASSED]\n", Private->EntryName);
  } else if ((Private->PassCount    > 0 ) &&
             (Private->WarningCount > 0 ) &&
             (Private->FailCount    == 0)) {
    DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
            L"\n%s: [PASSED WITH WARNINGS]\n", Private->EntryName);
  } else if ((Private->PassCount    >= 0) &&
             (Private->WarningCount >= 0) &&
             (Private->FailCount    > 0 )) {
    DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
            L"\n%s: [FAILED]\n", Private->EntryName);
  } else {
    DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
            L"\n%s: [NOT SUPPORTED]\n", Private->EntryName);
  }


  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);  
  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"  Passes........... %d\n", Private->PassCount);

  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);  
  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"  Warnings......... %d\n", Private->WarningCount);

  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);  
  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"  Errors........... %d\n", Private->FailCount);

  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);

  //
  // ----------------------------------
  //
  WriteLogFile (Private, DashLine, SYSTEMLOG);
  WriteLogFile (Private, DashLine, CASELOG);

  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%s\n", Private->BiosId);

  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);  
  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Revision 0x%08x\n", Private->TestRevision);

  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);  
  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Test Entry Point GUID: %g\n", &Private->EntryId);

  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);

  //
  // ----------------------------------
  //
  WriteLogFile (Private, DashLine, SYSTEMLOG);
  WriteLogFile (Private, DashLine, CASELOG);

  if (gtRT->GetTime (&CurrentTime, NULL) != EFI_SUCCESS)
    CurrentTime = Epoch;
  DBSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Test Finished: %t\n", &CurrentTime);

  WriteLogFile (Private, Buffer, SYSTEMLOG);
  WriteLogFile (Private, Buffer, CASELOG);
  
  SecondsElapsed = SecondsElapsedFromBaseYear (
                     Private->StartTime.Year,
                     CurrentTime.Year,
                     CurrentTime.Month,
                     CurrentTime.Day,
                     CurrentTime.Hour,
                     CurrentTime.Minute,
                     CurrentTime.Second
                   ) -
                   SecondsElapsedFromBaseYear (
                     Private->StartTime.Year,
                     Private->StartTime.Year,
                     Private->StartTime.Month,
                     Private->StartTime.Day,
                     Private->StartTime.Hour,
                     Private->StartTime.Minute,
                     Private->StartTime.Second
                   );

  DaysElapsed     = SecondsElapsed / SECS_PER_DAY;
  SecondsElapsed -= DaysElapsed * SECS_PER_DAY;
  HoursElapsed    = SecondsElapsed / SECS_PER_HOUR;
  SecondsElapsed -= HoursElapsed * SECS_PER_HOUR;
  MunitesElapsed  = SecondsElapsed / SECS_PER_MIN;
  SecondsElapsed -= MunitesElapsed * SECS_PER_MIN;

  SctStrCpy (Buffer1, L"Elapsed Time: ");
  MyUINTToStr (DaysElapsed, Str);
  SctStrCat (Buffer1, Str);
  SctStrCat (Buffer1, L" Days ");
  MyUINTToStr (HoursElapsed, Str);
  SctStrCat (Buffer1, Str);
  SctStrCat (Buffer1, L":");
  MyUINTToStr (MunitesElapsed, Str);
  SctStrCat (Buffer1, Str);
  SctStrCat (Buffer1, L":");
  MyUINTToStr (SecondsElapsed, Str);
  SctStrCat (Buffer1, Str);
  SctStrCat (Buffer1, L"\n");

  WriteLogFile (Private, Buffer1, SYSTEMLOG);
  WriteLogFile (Private, Buffer1, CASELOG);
  WriteLogFile (Private, L"\r\n", SYSTEMLOG);
  WriteLogFile (Private, L"\r\n", CASELOG);


  //
  // ----------------------------------
  //
  WriteLogFile (Private, DashLine, SYSTEMLOG);
  WriteLogFile (Private, DashLine, CASELOG);

  //
  // Write key file terminator line
  //
  DBSPrint (
    Buffer, EFI_MAX_PRINT_BUFFER, L"|TERM|%04x|%02d-%02d-%04d|%02d:%02d:%02d|%d %02d:%02d:%02d\n",
    (UINT16)(Status & 0xFFFF),
    CurrentTime.Day,
    CurrentTime.Month,
    CurrentTime.Year,
    CurrentTime.Hour,
    CurrentTime.Minute,
    CurrentTime.Second,
    DaysElapsed,
    HoursElapsed,
    MunitesElapsed,
    SecondsElapsed
    );
  WriteLogFile (Private, Buffer, SYSTEMKEY);
  WriteLogFile (Private, Buffer, CASEKEY);  

  Private->BeginLogging   = FALSE;

}
