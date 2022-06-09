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
    ComponentName2BBTestFunction.c

Abstract:
    for EFI Driver Component Name2 Protocol's Function Test

--*/
#include "SctLib.h"
#include "ComponentName2BBTestMain.h"


/**
 *  @brief Entrypoint for GetDriverName() Func Test.
 *         1 checkpoint will be tested.
 *  @param This            A pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel       Test "thoroughness" control
 *  @param SupportHandle   A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
EFIAPI
BBTestGetDriverNameFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_COMPONENT_NAME2_PROTOCOL          *ComponentName;

  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  CHAR16                                *DevicePathStr;
  //
  // init
  //
  ComponentName = (EFI_COMPONENT_NAME2_PROTOCOL*)ClientInterface;

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

  //
  // Get Loaded Image Device Path of current EFI_COMPONENT_NAME2_PROTOCOL
  // And out put device path or device name
  //
  Status = LocateLoadedImageDevicePathFromComponentName2 (ComponentName, &DevicePath, StandardLib);
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

  BBTestGetDriverNameFuncTestCheckpoint1 (StandardLib, ComponentName);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for GetControllerName() Basic Test.
 *         2 checkpoints will be tested.
 *  @param This            A pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel       Test "thoroughness" control
 *  @param SupportHandle   A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
EFIAPI
BBTestGetControllerNameFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_COMPONENT_NAME2_PROTOCOL          *ComponentName;

  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  CHAR16                                *DevicePathStr;
  //
  // init
  //
  ComponentName = (EFI_COMPONENT_NAME2_PROTOCOL*)ClientInterface;

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

  //
  // Get Loaded Image Device Path of current EFI_COMPONENT_NAME2_PROTOCOL
  // And out put device path or device name
  //
  Status = LocateLoadedImageDevicePathFromComponentName2 (ComponentName, &DevicePath, StandardLib);
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

  BBTestGetControllerNameFuncTestCheckpoint1 (StandardLib, ComponentName);

  BBTestGetControllerNameFuncTestCheckpoint2 (StandardLib, ComponentName);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetDriverNameFuncTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
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
  CHAR16                                      *DriverName;
  UINTN                                       LangIndex;
  UINTN                                       Switch = 0;

  LangIndex   = 0;
  PoolAddress = NULL;
  SupportedLanguages = ComponentName->SupportedLanguages;
  if (SupportedLanguages == NULL)
  	return  EFI_UNSUPPORTED;

  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress = (CHAR8 *) SctAllocateZeroPool (StringLength + 1);
  if (PoolAddress == NULL)
    return  EFI_UNSUPPORTED;

  SupportedLanguagesBackup = PoolAddress;  	
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

  if (Switch == 0){//RFC3066
    while (*Language !='\0') {
  
      DriverName = NULL;
      Status = ComponentName->GetDriverName (
                                ComponentName,
                                Language,
                                &DriverName
                                );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gComponentName2BBTestFunctionAssertionGuid001,
                     L"COMPONENT_NAME2_PROTOCOL.GetDriverName - GetDriverName() returns EFI_SUCCESS with supported languange",
                     L"%a:%d: LangIndex - %d, Language - %a, DriverName - %s, Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     LangIndex,
                     Language,
                     (DriverName == NULL) ? L"(NULL)" : DriverName,
                     Status
                     );
  
      LangIndex++;
      Language = SctAsciiSplitStr (&SupportedLanguagesBackup, ';');
    }
  }else{//ISO639-2
    while (Lang[0] !='\0') {
  
      DriverName = NULL;
      Status = ComponentName->GetDriverName (
                                ComponentName,
                                Lang,
                                &DriverName
                                );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gComponentName2BBTestFunctionAssertionGuid001,
                     L"Please Use Native RFC3066 which is preferable in UEFI 2.X\n COMPONENT_NAME2_PROTOCOL.GetDriverName - GetDriverName() returns EFI_SUCCESS with supported languange",
                     L"%a:%d: LangIndex - %d, Language - %c%c%c, DriverName - %s, Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     LangIndex,
                     Lang[0],
                     Lang[1],
                     Lang[2],
                     (DriverName == NULL) ? L"(NULL)" : DriverName,
                     Status
                     );
  
      LangIndex++;
      SctAsciiStrnCpy (Lang, SupportedLanguagesBackup, 3);
      SupportedLanguagesBackup = SupportedLanguagesBackup + 3;
    }
  }
  
  gtBS->FreePool (PoolAddress);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetControllerNameFuncTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
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
  EFI_HANDLE                                  ComponentNameHandle = NULL;
  EFI_COMPONENT_NAME2_PROTOCOL                *TestedComponentName;
  UINTN                                       ControllerHandleCount;
  EFI_HANDLE                                  *ControllerHandleBuffer;
  UINTN                                          Switch = 0;

  //
  // locate all component name protocol instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiComponentName2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not locate component name2 protocol handles",
                   L"%a:%d: Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the component name protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiComponentName2ProtocolGuid,
                     (VOID **) &TestedComponentName
                     );
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (TestedComponentName == ComponentName) {
      ComponentNameHandle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (ComponentNameHandle == NULL) {
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
  // find controller handles managed by the component name handle.
  //
  Status = SctGetManagedControllerHandles (
             ComponentNameHandle,
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

  LangIndex   = 0;
  PoolAddress = NULL;
  SupportedLanguages = ComponentName->SupportedLanguages;
  if (SupportedLanguages == NULL){
    gtBS->FreePool (ControllerHandleBuffer);
    return EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress = (CHAR8 *) SctAllocateZeroPool (StringLength + 1);
  if (PoolAddress == NULL) {
    gtBS->FreePool (ControllerHandleBuffer);
    return  EFI_UNSUPPORTED;
  }
  
  SupportedLanguagesBackup = PoolAddress;
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
        Status = ComponentName->GetControllerName (
                                  ComponentName,
                                  ControllerHandleBuffer[Index],
                                  NULL,
                                  Language,
                                  &ControllerName
                                  );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else if (EFI_UNSUPPORTED == Status) {
          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gComponentName2BBTestFunctionAssertionGuid002,
                       L"COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_SUCCESS with supported language",
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
        Status = ComponentName->GetControllerName (
                                  ComponentName,
                                  ControllerHandleBuffer[Index],
                                  NULL,
                                  Lang,
                                  &ControllerName
                                  );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else if (EFI_UNSUPPORTED == Status) {
          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gComponentName2BBTestFunctionAssertionGuid002,
                       L"Please Use Native RFC3066 which is preferable in UEFI 2.X\nCOMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_SUCCESS with supported languange",
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
BBTestGetControllerNameFuncTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
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
  EFI_HANDLE                                  ComponentNameHandle = NULL;
  EFI_COMPONENT_NAME2_PROTOCOL                *TestedComponentName;
  UINTN                                       ControllerHandleCount;
  EFI_HANDLE                                  *ControllerHandleBuffer;
  UINTN                                       NumberOfChildren;
  EFI_HANDLE                                  *ChildControllerHandleBuffer;
  UINTN                                       ChildIndex;
  UINTN                                       Switch = 0;

  //HandleBuffer = NULL;
  //
  // locate all component name protocol instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiComponentName2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not locate component name2 protocol handles",
                   L"%a:%d: Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the component name protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiComponentName2ProtocolGuid,
                     (VOID **) &TestedComponentName
                     );
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (TestedComponentName == ComponentName) {
      ComponentNameHandle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (ComponentNameHandle == NULL) {
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
  // find controller handles managed by the component name handle.
  //
  Status = SctGetManagedControllerHandles (
             ComponentNameHandle,
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

  LangIndex   = 0;
  PoolAddress = NULL;
  SupportedLanguages = ComponentName->SupportedLanguages;
  if (SupportedLanguages == NULL){
    gtBS->FreePool (ControllerHandleBuffer);
    return  EFI_UNSUPPORTED;
  }	

  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress = (CHAR8 *) SctAllocateZeroPool (StringLength + 1);
  if (PoolAddress == NULL) {
    gtBS->FreePool (ControllerHandleBuffer);
    return  EFI_UNSUPPORTED;
  }
  
  SupportedLanguagesBackup = PoolAddress;
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
                   ComponentNameHandle,
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
          Status = ComponentName->GetControllerName (
                                    ComponentName,
                                    ControllerHandleBuffer[Index],
                                    ChildControllerHandleBuffer[ChildIndex],
                                    Language,
                                    &ControllerName
                                    );
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else if (EFI_UNSUPPORTED == Status) {
            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gComponentName2BBTestFunctionAssertionGuid003,
                         L"COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_SUCCESS support language",
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
                   ComponentNameHandle,
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
          Status = ComponentName->GetControllerName (
                                    ComponentName,
                                    ControllerHandleBuffer[Index],
                                    ChildControllerHandleBuffer[ChildIndex],
                                    Lang,
                                    &ControllerName
                                    );
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else if (EFI_UNSUPPORTED == Status) {
            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gComponentName2BBTestFunctionAssertionGuid003,
                         L"Please Use Native RFC3066 which is preferable in UEFI 2.X\nCOMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_SUCCESS support language",
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

