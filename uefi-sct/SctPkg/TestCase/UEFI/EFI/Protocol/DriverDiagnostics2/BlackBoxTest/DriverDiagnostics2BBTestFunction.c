/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    DriverDiagnostics2BBTestFunction.c

Abstract:
    for EFI Driver Diagnostics2 Protocol's generic Function Test

--*/

#include "SctLib.h"
#include "DriverDiagnostics2BBTest.h"

EFI_STATUS
EFIAPI
BBTestRunDiagnosticsFuncTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  );

EFI_STATUS
EFIAPI
BBTestRunDiagnosticsFuncTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  );


/**
 *  @brief Entrypoint for RunDiagnostics() Function Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
EFIAPI
BBTestRunDiagnosticsFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2;

  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  CHAR16                                *DevicePathStr;

  //
  // init
  //
  DriverDiagnostics2 = (EFI_DRIVER_DIAGNOSTICS2_PROTOCOL*)ClientInterface;

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
  // Get Loaded Image Device Path of current EFI_DRIVER_DIAGNOSTICS2_PROTOCOL
  // And out put device path or device name
  //
  Status = LocateLoadedImageDevicePathFromDriverDiagnostisc2 (DriverDiagnostics2, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = NULL;
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Device Path: %s\r\n",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status))
        return Status;
      DevicePathStr=NULL;
    }     
  }

  //
  // 7.2.1.2.1  Call RunDiagnostics() with valid ControllerHandle
  //
  BBTestRunDiagnosticsFuncTestCheckpoint1 (StandardLib, DriverDiagnostics2);

  //
  // 7.2.1.2.2  Call RunDiagnostics() with valid ChildHandle.
  //
  BBTestRunDiagnosticsFuncTestCheckpoint2 (StandardLib, DriverDiagnostics2);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRunDiagnosticsFuncTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  CHAR8                                       *Language = NULL;
  CHAR8                                       Lang[4];
  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *SupportedLanguagesBackup;
  CHAR8                                       *PoolAddress;
  UINTN                                        StringLength;
  UINTN                                       LangIndex;
  UINTN                                       NoHandles;
  EFI_HANDLE                                  *HandleBuffer;
  UINTN                                       SuccessCount;
  CHAR16                                      *ControllerName;
  UINTN                                       Index;
  EFI_HANDLE                                  DriverDiagnostics2Handle = NULL;
  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL            *TestedDriverDiagnostics2 = NULL;
  UINTN                                       ControllerHandleCount;
  EFI_HANDLE                                  *ControllerHandleBuffer;
  UINTN                                       Switch = 0;

  EFI_GUID                                    *ErrorType;
  UINTN                                       BufferSize;
  CHAR16                                      *Buffer;
  //
  // locate all component name protocol instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not locate Driver Diagnostics2 protocol handles",
                   L"%a:%d: Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the Driver Diagnostics Protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
                     (VOID **) &TestedDriverDiagnostics2
                     );
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (TestedDriverDiagnostics2 == DriverDiagnostics2) {
      DriverDiagnostics2Handle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (DriverDiagnostics2Handle == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not find the Driver Diagnostics protocol handle - NO",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the Driver Diagnostics handle.
  //
  Status = SctGetManagedControllerHandles (
             DriverDiagnostics2Handle,
             &ControllerHandleCount,
             &ControllerHandleBuffer
             );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not get managed controller handle",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  LangIndex = 0;
  SupportedLanguages = DriverDiagnostics2->SupportedLanguages;
  if (SupportedLanguages == NULL){
    gtBS->FreePool (ControllerHandleBuffer);
    return EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress = (CHAR8 *) SctAllocatePool (StringLength + 1);
  SupportedLanguagesBackup = PoolAddress;
  if (SupportedLanguagesBackup ==NULL){
    gtBS->FreePool (ControllerHandleBuffer);
    return  EFI_UNSUPPORTED;
  }
  SctAsciiStrCpy (SupportedLanguagesBackup, SupportedLanguages);

  if ((SctAsciiStrChr (SupportedLanguagesBackup, '-') == NULL) &&
  	(SctAsciiStrChr (SupportedLanguagesBackup, ';') == NULL) && 
  	(SctAsciiStrLen (SupportedLanguagesBackup) >= 3)){
  //ISO639-2, Which belongs to EFI1.1  
    SctAsciiStrnCpy (Lang, SupportedLanguagesBackup, 3);
    SupportedLanguagesBackup = SupportedLanguagesBackup + 3;
    Switch = 1;	
  }else{
  //RFC3066
    Language = SctAsciiSplitStr(&SupportedLanguagesBackup, ';');
  }
  
 if (Switch == 0){
    while (*Language !='\0') {
  
      SuccessCount = 0;
      for (Index = 0; Index < ControllerHandleCount; Index++) {
  
        ControllerName = NULL;

        Status = DriverDiagnostics2->RunDiagnostics (
                                      DriverDiagnostics2,
                                      ControllerHandleBuffer[Index],
                                      NULL,
                                      0,
                                      Language,
                                      &ErrorType,
                                      &BufferSize,
                                      &Buffer
                                      );

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else if (EFI_UNSUPPORTED == Status) {
          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else if (EFI_NOT_READY == Status) {
          Status = DriverDiagnostics2->RunDiagnostics (
                                      DriverDiagnostics2,
                                      ControllerHandleBuffer[Index],
                                      NULL,
                                      3,
                                      Language,
                                      &ErrorType,
                                      &BufferSize,
                                      &Buffer
                                      );
		  if (EFI_SUCCESS == Status) {
		  	AssertionType = EFI_TEST_ASSERTION_PASSED;
		  } else if (EFI_ACCESS_DENIED == Status) {
            AssertionType = EFI_TEST_ASSERTION_WARNING;
		  } else {
		  	AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
		} else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gFunctionAssertionGuid001,
                       L"EFI_DRIVER_DIAGNOSTICS2_PROTOCOL.RunDiagnostics - RunDiagnostics() returns EFI_SUCCESS with supported language",
                       L"%a:%d: Language - %a, ControllerHandleIndex - %d, ControllerName - %s, Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Language,
                       Index,
                       (ControllerName == NULL) ? L"(NULL)" : ControllerName,
                       Status
                       );
      }
  
      LangIndex++;
      Language = SctAsciiSplitStr (&SupportedLanguagesBackup, ';');
    }
  }else{
    while (Lang[0] !='\0') {

      SuccessCount = 0;
      for (Index = 0; Index < ControllerHandleCount; Index++) {
  
        ControllerName = NULL;
        Status = DriverDiagnostics2->RunDiagnostics (
                                      DriverDiagnostics2,
                                      ControllerHandleBuffer[Index],
                                      NULL,
                                      0,
                                      Lang,
                                      &ErrorType,
                                      &BufferSize,
                                      &Buffer
                                      );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else if (EFI_UNSUPPORTED == Status) {
          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else if (EFI_NOT_READY == Status) {
          Status = DriverDiagnostics2->RunDiagnostics (
                                      DriverDiagnostics2,
                                      ControllerHandleBuffer[Index],
                                      NULL,
                                      3,
                                      Language,
                                      &ErrorType,
                                      &BufferSize,
                                      &Buffer
                                      );
		  if (EFI_SUCCESS == Status) {
		  	AssertionType = EFI_TEST_ASSERTION_PASSED;
		  } else if (EFI_ACCESS_DENIED == Status) {
            AssertionType = EFI_TEST_ASSERTION_WARNING;
		  } else {
		  	AssertionType = EFI_TEST_ASSERTION_FAILED;
          }		  
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gFunctionAssertionGuid001,
                       L"Please Use Native RFC3066 which is preferable in UEFI 2.X\nEFI_DRIVER_DIAGNOSTICS2_PROTOCOL.RunDiagnostics - RunDiagnostics() returns EFI_SUCCESS with supported languange",
                       L"%a:%d: LangIndex - %d, Language - %c%c%c, ControllerName - %s, Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       LangIndex,
                       Lang[0],
                       Lang[1],
                       Lang[2],
                       (ControllerName == NULL) ? L"(NULL)" : ControllerName,
                       Status
                       );
      }

      LangIndex++;
      SctAsciiStrnCpy (Lang, SupportedLanguagesBackup, 3);
      SupportedLanguagesBackup = SupportedLanguagesBackup + 3;
    }
  }

  gtBS->FreePool (ControllerHandleBuffer);
  gtBS->FreePool (PoolAddress);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRunDiagnosticsFuncTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  CHAR8                                       *Language = NULL;
  CHAR8                                       Lang[4];
  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *SupportedLanguagesBackup;
  CHAR8                                       *PoolAddress;
  UINTN                                        StringLength;
  UINTN                                       LangIndex;
  UINTN                                       NoHandles;
  EFI_HANDLE                                  *HandleBuffer;
  UINTN                                       Index;
  CHAR16                                      *ControllerName;
  EFI_HANDLE                                  DriverDiagnostics2Handle = NULL;
  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL            *TestedDriverDiagnostics2 = NULL;
  UINTN                                       ControllerHandleCount;
  EFI_HANDLE                                  *ControllerHandleBuffer;
  UINTN                                       NumberOfChildren;
  EFI_HANDLE                                  *ChildControllerHandleBuffer;
  UINTN                                       ChildIndex;
  UINTN                                       Switch = 0;
  
  EFI_GUID                                    *ErrorType;
  UINTN                                       BufferSize;
  CHAR16                                      *Buffer;
  //HandleBuffer = NULL;
  //
  // locate all Driver Diagnostics Protocol instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not locate Driver Diagnostics protocol handles",
                   L"%a:%d: Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the Driver Diagnostics Protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
                     (VOID **) &TestedDriverDiagnostics2
                     );
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (TestedDriverDiagnostics2 == DriverDiagnostics2) {
      DriverDiagnostics2Handle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (DriverDiagnostics2Handle == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not find the component name2 protocol handle - NO",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the Driver Diagnostics handle.
  //
  Status = SctGetManagedControllerHandles (
             DriverDiagnostics2Handle,
             &ControllerHandleCount,
             &ControllerHandleBuffer
             );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not get managed controller handle",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  LangIndex = 0;
  SupportedLanguages = DriverDiagnostics2->SupportedLanguages;
  if (SupportedLanguages == NULL){
    gtBS->FreePool (ControllerHandleBuffer);
    return  EFI_UNSUPPORTED;
  }	

  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress = (CHAR8 *) SctAllocatePool (StringLength + 1);
  SupportedLanguagesBackup = PoolAddress;
  if (SupportedLanguagesBackup == NULL){
    gtBS->FreePool (ControllerHandleBuffer);
    return  EFI_UNSUPPORTED;
  }	
  SctAsciiStrCpy (SupportedLanguagesBackup, SupportedLanguages);

  if ((SctAsciiStrChr (SupportedLanguagesBackup, '-') == NULL) &&
  	(SctAsciiStrChr (SupportedLanguagesBackup, ';') == NULL) && 
  	(SctAsciiStrLen (SupportedLanguagesBackup) >= 3)){
  //ISO639-2, Which belongs to EFI1.1  
    SctAsciiStrnCpy (Lang, SupportedLanguagesBackup, 3);
    SupportedLanguagesBackup = SupportedLanguagesBackup + 3;
    Switch = 1;	
  }else{
  //RFC3066
    Language = SctAsciiSplitStr(&SupportedLanguagesBackup, ';');
  }
  
  if (Switch == 0){
  
    while (*Language != '\0') {
  
      for (Index = 0; Index < ControllerHandleCount; Index++) {
  
        ChildControllerHandleBuffer = NULL;
  
        Status = SctGetManagedChildControllerHandles (
                   DriverDiagnostics2Handle,
                   ControllerHandleBuffer[Index],
                   &NumberOfChildren,
                   &ChildControllerHandleBuffer
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_WARNING,
                         gTestGenericFailureGuid,
                         L"Could not get managed child controller handle",
                         L"%a:%d",
                         __FILE__,
                         (UINTN)__LINE__
                         );
          continue;
        }
  
        for (ChildIndex = 0; ChildIndex < NumberOfChildren; ChildIndex++) {
  
          ControllerName = NULL;
          Status = DriverDiagnostics2->RunDiagnostics (
                                        DriverDiagnostics2,
                                        ControllerHandleBuffer[Index],
                                        ChildControllerHandleBuffer[ChildIndex],
                                        0,
                                        Language,
                                        &ErrorType,
                                        &BufferSize,
                                        &Buffer
                                        );
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else if ( (EFI_UNSUPPORTED == Status) || (EFI_DEVICE_ERROR == Status) || (EFI_ACCESS_DENIED == Status) ) {
            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else if (EFI_NOT_READY == Status) {
            Status = DriverDiagnostics2->RunDiagnostics (
                                      DriverDiagnostics2,
                                      ControllerHandleBuffer[Index],
                                      ChildControllerHandleBuffer[ChildIndex],
                                      3,
                                      Language,
                                      &ErrorType,
                                      &BufferSize,
                                      &Buffer
                                      );
		    if (EFI_SUCCESS == Status) {
		  	  AssertionType = EFI_TEST_ASSERTION_PASSED;
		    } else if (EFI_ACCESS_DENIED == Status || EFI_DEVICE_ERROR == Status) {
              AssertionType = EFI_TEST_ASSERTION_WARNING;
		    } else {
		  	  AssertionType = EFI_TEST_ASSERTION_FAILED;
            }				
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gFunctionAssertionGuid002,
                         L"EFI_DRIVER_DIAGNOSTICS2_PROTOCOL.RunDiagnostics - RunDiagnostics() returns EFI_SUCCESS with supported language",
                         L"%a:%d: Language - %a, ControllerIndex - %d, ChildIndex - %d, ControllerName - %s, Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Language,
                         Index,
                         ChildIndex,
                         (ControllerName == NULL) ? L"(NULL)" : ControllerName,
                         Status
                         );
        }
  
        if (ChildControllerHandleBuffer != NULL) {
          gtBS->FreePool (ChildControllerHandleBuffer);
        }
      }
  
      LangIndex++;
      Language = SctAsciiSplitStr (&SupportedLanguagesBackup, ';');
    }
  }else {
    while (Lang[0] !='\0') {

      for (Index = 0; Index < ControllerHandleCount; Index++) {
  
        ChildControllerHandleBuffer = NULL;
  
        Status = SctGetManagedChildControllerHandles (
                   DriverDiagnostics2Handle,
                   ControllerHandleBuffer[Index],
                   &NumberOfChildren,
                   &ChildControllerHandleBuffer
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_WARNING,
                         gTestGenericFailureGuid,
                         L"Could not get managed child controller handle",
                         L"%a:%d",
                         __FILE__,
                         (UINTN)__LINE__
                         );
          continue;
        }

        for (ChildIndex = 0; ChildIndex < NumberOfChildren; ChildIndex++) {
  
          ControllerName = NULL;
          Status = DriverDiagnostics2->RunDiagnostics (
                                        DriverDiagnostics2,
                                        ControllerHandleBuffer[Index],
                                        ChildControllerHandleBuffer[ChildIndex],
                                        0,
                                        Lang,
                                        &ErrorType,
                                        &BufferSize,
                                        &Buffer
                                        );	
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else if ( (EFI_UNSUPPORTED == Status) || (EFI_DEVICE_ERROR == Status) || (EFI_ACCESS_DENIED == Status) ) {
            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else if (EFI_NOT_READY == Status) {
            Status = DriverDiagnostics2->RunDiagnostics (
                                      DriverDiagnostics2,
                                      ControllerHandleBuffer[Index],
                                      ChildControllerHandleBuffer[ChildIndex],
                                      3,
                                      Language,
                                      &ErrorType,
                                      &BufferSize,
                                      &Buffer
                                      );
		    if (EFI_SUCCESS == Status) {
		  	  AssertionType = EFI_TEST_ASSERTION_PASSED;
		    } else if (EFI_ACCESS_DENIED == Status || EFI_DEVICE_ERROR == Status) {
              AssertionType = EFI_TEST_ASSERTION_WARNING;
		    } else {
		  	  AssertionType = EFI_TEST_ASSERTION_FAILED;
            }			
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gFunctionAssertionGuid002,
                         L"Please Use Native RFC3066 which is preferable in UEFI 2.X\nEFI_DRIVER_DIAGNOSTICS2_PROTOCOL.RunDiagnostics - RunDiagnostics() returns EFI_SUCCESS with supported language",
                         L"%a:%d: Language - %c%c%c%c, ControllerIndex - %d, ChildIndex - %d, ControllerName - %s, Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Lang[0],Lang[1],Lang[2],Lang[3],
                         Index,
                         ChildIndex,
                         (ControllerName == NULL) ? L"(NULL)" : ControllerName,
                         Status
                         );
        }
  
        if (ChildControllerHandleBuffer != NULL) {
          gtBS->FreePool (ChildControllerHandleBuffer);
        }	
      	}
      LangIndex++;
      SctAsciiStrnCpy (Lang, SupportedLanguagesBackup, 3);
      SupportedLanguagesBackup = SupportedLanguagesBackup + 3;
    }
  }

  gtBS->FreePool (ControllerHandleBuffer);
  gtBS->FreePool (PoolAddress);

  return EFI_SUCCESS;
}

