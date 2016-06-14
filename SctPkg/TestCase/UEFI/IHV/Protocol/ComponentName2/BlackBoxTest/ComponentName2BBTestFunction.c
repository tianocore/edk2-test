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
BBTestGetDriverNameFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName;

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
                   &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
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
BBTestGetControllerNameFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName;

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
                   &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  BBTestGetControllerNameFuncTestCheckpoint1 (StandardLib, ComponentName);

  BBTestGetControllerNameFuncTestCheckpoint2 (StandardLib, ComponentName);

  return EFI_SUCCESS;
}

EFI_STATUS
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
                     &TestedComponentName
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
                     &TestedComponentName
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
                         L"%a:%d: Language - %c%c%c, ControllerIndex - %d, ChildIndex - %d, ControllerName - %s, Status - %r",
		                 __FILE__,
                         (UINTN)__LINE__,
                         Lang,
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

