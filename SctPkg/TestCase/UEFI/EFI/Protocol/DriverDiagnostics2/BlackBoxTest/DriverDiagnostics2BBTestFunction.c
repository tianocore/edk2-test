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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010-2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    DriverDiagnostics2BBTestFunction.c

Abstract:
    for EFI Driver Diagnostics2 Protocol's generic Function Test

--*/

#include "SctLib.h"
#include "DriverDiagnostics2BBTest.h"

EFI_STATUS
BBTestRunDiagnosticsFuncTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  );

EFI_STATUS
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
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
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
                     &TestedDriverDiagnostics2
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
                     &TestedDriverDiagnostics2
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

