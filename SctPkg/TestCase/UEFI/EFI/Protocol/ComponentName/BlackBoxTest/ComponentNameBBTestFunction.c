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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

    ComponentNameBBTestFunction.c

Abstract:

    for EFI Driver Component Name Protocol's Basic Test

--*/

#include "SctLib.h"
#include "ComponentNameBBTest.h"

/**
 *  @brief Entrypoint for GetDriverName() Basic Test.
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 9.2.1
//
EFI_STATUS
BBTestGetDriverNameBasicTest (
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
                   &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 9.2.1.2.1  GetDriverName() returns its driver name
  // in every supported language.
  //
  BBTestGetDriverNameBasicTestCheckpoint1 (StandardLib, ComponentName);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for GetControllerName() Basic Test.
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 9.2.2
//
EFI_STATUS
BBTestGetControllerNameBasicTest (
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
                   &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 9.2.2.2.1  Retrieve the name of a controller
  // which is managed by a device driver.
  //
  BBTestGetControllerNameBasicTestCheckpoint1 (StandardLib, ComponentName);

  //
  // 9.2.2.2.2  Retrieve the name of a controller
  // which is managed by a bus driver.
  //
  BBTestGetControllerNameBasicTestCheckpoint2 (StandardLib, ComponentName);


  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetDriverNameBasicTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  CHAR8                                       *Language;
  CHAR16                                      *DriverName;
  UINTN                                       LangIndex;

  LangIndex = 0;
  Language = ComponentName->SupportedLanguages;
  while (*Language != 0) {

    DriverName = NULL;
    Status = ComponentName->GetDriverName (
                              ComponentName,
                              Language,
                              &DriverName
                              );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBasicTestAssertionGuid001,
                   L"COMPONENT_NAME_PROTOCOL.GetDriverName - GetDriverName() returns EFI_SUCCESS with supported languange",
                   L"%a:%d: LangIndex - %d, Language - %c%c%c, DriverName - %s, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   LangIndex,
                   Language[0],
                   Language[1],
                   Language[2],
                   (DriverName == NULL) ? L"(NULL)" : DriverName,
                   Status
                   );

    LangIndex++;
    Language += 3;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetControllerNameBasicTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  CHAR8                                       *Language;
  UINTN                                       LangIndex;
  UINTN                                       NoHandles;
  EFI_HANDLE                                  *HandleBuffer;
  UINTN                                       SuccessCount;
  CHAR16                                      *ControllerName;
  UINTN                                       Index;
  EFI_HANDLE                                  ComponentNameHandle = NULL;
  EFI_COMPONENT_NAME_PROTOCOL                 *TestedComponentName;
  UINTN                                       ControllerHandleCount;
  EFI_HANDLE                                  *ControllerHandleBuffer;

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
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not locate component name protocol handles",
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
                     &gBlackBoxEfiComponentNameProtocolGuid,
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
                   L"Could not find the component name protocol handle - NO",
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

  LangIndex = 0;
  Language = ComponentName->SupportedLanguages;
  while (*Language != 0) {

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
      } else {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBasicTestAssertionGuid002,
                     L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_SUCCESS with supported language",
                     L"%a:%d: Language - %c%c%c, ControllerHandleIndex - %d, ControllerName - %s, Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Language[0],
                     Language[1],
                     Language[2],
                     Index,
                     (ControllerName == NULL) ? L"(NULL)" : ControllerName,
                     Status
                     );
    }

    LangIndex++;
    Language += 3;
  }

  gtBS->FreePool (ControllerHandleBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetControllerNameBasicTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  CHAR8                                       *Language;
  UINTN                                       LangIndex;
  UINTN                                       NoHandles;
  EFI_HANDLE                                  *HandleBuffer;
  UINTN                                       Index;
  CHAR16                                      *ControllerName;
  EFI_HANDLE                                  ComponentNameHandle = NULL;
  EFI_COMPONENT_NAME_PROTOCOL                 *TestedComponentName;
  UINTN                                       ControllerHandleCount;
  EFI_HANDLE                                  *ControllerHandleBuffer;
  UINTN                                       NumberOfChildren;
  EFI_HANDLE                                  *ChildControllerHandleBuffer;
  UINTN                                       ChildIndex;

  HandleBuffer = NULL;
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
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Could not locate component name protocol handles",
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
                     &gBlackBoxEfiComponentNameProtocolGuid,
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
                   L"Could not find the component name protocol handle - NO",
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

  LangIndex = 0;
  Language = ComponentName->SupportedLanguages;
  while (*Language != 0) {

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
        } else {
          AssertionType = EFI_TEST_ASSERTION_WARNING;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gBasicTestAssertionGuid003,
                       L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_SUCCESS support language",
                       L"%a:%d: Language - %c%c%c, ControllerIndex - %d, ChildIndex - %d, ControllerName - %s, Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Language[0],
                       Language[1],
                       Language[2],
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
    Language += 3;
  }

  gtBS->FreePool (ControllerHandleBuffer);

  return EFI_SUCCESS;
}
