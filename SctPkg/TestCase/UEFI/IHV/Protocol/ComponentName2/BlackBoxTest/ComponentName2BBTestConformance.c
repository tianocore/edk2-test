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
    ComponentName2BBTestConformance.c

Abstract:
    for EFI Driver Component Name2 Protocol's Conformance Test

--*/

#include "SctLib.h"
#include "ComponentName2BBTestMain.h"

//
// some private functions declaration
//
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
  IN  EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName,
  OUT EFI_HANDLE                            *ValidControllerHandle
  );

STATIC
EFI_STATUS
FindMatchedBusHandle (
  IN  EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName,
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


/**
 *  @brief Entrypoint for GetDriverName() Conformance Test.
 *         2 checkpoints will be tested.
 *  @param This            A pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel       Test "thoroughness" control
 *  @param SupportHandle   A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
BBTestGetDriverNameConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_COMPONENT_NAME2_PROTOCOL          *ComponentName;

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
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BBTestGetDriverNameConformanceTestCheckpoint1 (StandardLib, ComponentName);

  BBTestGetDriverNameConformanceTestCheckpoint2 (StandardLib, ComponentName);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for GetControllerName() Conformance Test.
 *         3 checkpoints will be tested.
 *  @param This            A pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel       Test "thoroughness" control
 *  @param SupportHandle   A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
BBTestGetControllerNameConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_COMPONENT_NAME2_PROTOCOL          *ComponentName;

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
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BBTestGetControllerNameConformanceTestCheckpoint1 (StandardLib, ComponentName);

  BBTestGetControllerNameConformanceTestCheckpoint2 (StandardLib, ComponentName);

  BBTestGetControllerNameConformanceTestCheckpoint3 (StandardLib, ComponentName);

//  BBTestGetControllerNameConformanceTestCheckpoint4 (StandardLib, ComponentName);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetDriverNameConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL          *ComponentName
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
  UINTN                                        Switch = 0;

  //
  // retrieve the first supported language
  //
  SupportedLanguages = ComponentName->SupportedLanguages;
  if (SupportedLanguages == NULL){
    return  EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress  = NULL;
  PoolAddress  = (CHAR8 *) SctAllocateZeroPool (StringLength + 1);
  if (PoolAddress == NULL){
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
  
  if ((Switch == 0 && *Language == '\0') || (Switch == 1 && Lang[0] == '\0')){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get SupportedLanguages",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (PoolAddress);
    return EFI_UNSUPPORTED;
  }
  //
  // with Language being NULL.
  //
  Status = ComponentName->GetDriverName (
                            ComponentName,
                            NULL,
                            &DriverName
                            );
  if (EFI_INVALID_PARAMETER == Status  || EFI_UNSUPPORTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gComponentName2BBTestConformanceAssertionGuid001,
                 L"COMPONENT_NAME2_PROTOCOL.GetDriverName - GetDriverName() returns EFI_INVALID_PARAMETER with NULL Language",
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
                            (Switch == 0) ?  Language : Lang,
                            NULL
                            );
  if (EFI_INVALID_PARAMETER == Status || EFI_UNSUPPORTED == Status) {
    AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gComponentName2BBTestConformanceAssertionGuid002,
                 L"COMPONENT_NAME2_PROTOCOL.GetDriverName - GetDriverName() returns EFI_INVALID_PARAMETER with NULL DriverName",
                 L"%a:%d: Status - %r, %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 (Switch == 0) ? L"NULL" :  L"Please Use Native RFC3066 which is preferable in UEFI 2.X"
                 );
  
  
  gtBS->FreePool (PoolAddress);
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetDriverNameConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL          *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *UnsupportedLanguageCode = "enus";
  CHAR16                                      *DriverName;
  UINTN                                       StringLength;
  CHAR8                                       *PoolAddress;
  CHAR8                                       *SupportedLanguagesBackup;
  UINTN                                       Switch = 0;
  CHAR8                                       Lang[4];
  CHAR8                                       *Language = NULL;
  CHAR8                                       *CandidateCode[7] = {"en-US", "da-DE", "fr-FR", "zh-CN", "ja", "ko-KP", "es-ES" }; 
  CHAR8                                       Sign[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  UINTN                                       Index;

  SupportedLanguages = ComponentName->SupportedLanguages;
  if (SupportedLanguages == NULL){
    return  EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress  = NULL;
  PoolAddress  = (CHAR8 *) SctAllocateZeroPool (StringLength + 1);
  if (PoolAddress == NULL){
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
    while (*Language != '\0'){
      for (Index = 0; Index < 7; Index ++){
        if (SctAsciiStrnCmp (Language, CandidateCode[Index], 2) == 0){
          Sign[Index] = 1;
        }
      }
      Language = SctAsciiSplitStr (&SupportedLanguagesBackup, ';');
    }
  } else {
     while (Lang[0] != '\0'){
      for (Index = 0; Index < 7; Index ++){
        if (SctAsciiStrnCmp (Lang, CandidateCode[Index], 2) == 0){
          Sign[Index] = 1;
        }
      }
      SctAsciiStrnCpy (Lang, SupportedLanguagesBackup, 3);
      SupportedLanguagesBackup = SupportedLanguagesBackup + 3;
    } 
  }

  for (Index = 0; Index < 7; Index ++){
    if (Sign[Index] == 0){
      Sign[7] = 1;
      Status = ComponentName->GetDriverName (
		                     ComponentName,
                             CandidateCode[Index],
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
                   gComponentName2BBTestConformanceAssertionGuid003,
                   L"COMPONENT_NAME_PROTOCOL.GetDriverName - GetDriverName() returns EFI_UNSUPPORTED with unsupported language",
                   L"%a:%d: Language - %a, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   CandidateCode[Index],
                   Status
                   );
      break;		
    }
  }
  //
  // with unsupported Language.
  //
  if (Sign[7] == 0){
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
				   gComponentName2BBTestConformanceAssertionGuid003,
				   L"COMPONENT_NAME_PROTOCOL.GetDriverName - GetDriverName() returns EFI_UNSUPPORTED with unsupported language",
				   L"%a:%d: Language - %a, Status - %r",
				   __FILE__,
				   (UINTN)__LINE__,
				   UnsupportedLanguageCode,
				   Status
				   );
  }

  gtBS->FreePool (PoolAddress);
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetControllerNameConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL          *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  ValidControllerHandle;
  CHAR8                                       *Language = NULL;
  CHAR8                                       Lang[4];
  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *SupportedLanguagesBackup;
  CHAR8                                       *PoolAddress;
  UINTN                                        StringLength;
  CHAR16                                      *ControllerName;
  UINTN                                        Switch = 0;

  //
  // retrieve the first supported language
  //
  SupportedLanguages = ComponentName->SupportedLanguages;
  if (SupportedLanguages == NULL){
    return  EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress  = NULL;
  PoolAddress  = (CHAR8 *) SctAllocateZeroPool (StringLength + 1);
  if (PoolAddress == NULL){
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
  
  if ((Switch == 0 && *Language == '\0') || (Switch == 1 && Lang[0] == '\0')) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get SupportedLanguages",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (PoolAddress);
    return EFI_UNSUPPORTED;
  }


  //
  // with a NULL ControllerHandle
  //
  Status = ComponentName->GetControllerName (
                            ComponentName,
                            NULL,
                            NULL,
                            (Switch == 0) ? Language : Lang,
                            &ControllerName
                            );
  if (EFI_INVALID_PARAMETER == Status || EFI_UNSUPPORTED == Status) {
    AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gComponentName2BBTestConformanceAssertionGuid004,
                 L"COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_INVALID_PARAMETER with a NULL ControllerHandle",
                 L"%a:%d: Language - %a, Status - %r, %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 (Switch == 0) ? Language : Lang,
                 Status,
                 (Switch == 0) ? L"NULL" : L"Please Use Native RFC3066 which is preferable in UEFI 2.X"
                 );
  

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
    gtBS->FreePool (PoolAddress);
    return EFI_NOT_FOUND;
  }

  //
  // with ControllerName being NULL
  //
  Status = ComponentName->GetControllerName (
                            ComponentName,
                            ValidControllerHandle,
                            NULL,
                            (Switch == 0) ? Language : Lang,
                            NULL
                            );
  if (EFI_INVALID_PARAMETER == Status || EFI_UNSUPPORTED == Status) {
    AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gComponentName2BBTestConformanceAssertionGuid006,
                 L"COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_INVALID_PARAMETER with NULL ControllerName",
                 L"%a:%d: Status - %r, %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 (Switch == 0) ? L"NULL" :  L"Please Use Native RFC3066 which is preferable in UEFI 2.X"
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
  if (EFI_INVALID_PARAMETER == Status || EFI_UNSUPPORTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gComponentName2BBTestConformanceAssertionGuid007,
                 L"COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_INVALID_PARAMETER with NULL Language",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (PoolAddress);
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetControllerNameConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL          *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  CHAR8                                       *UnsupportedLanguageCode = "enus";
  CHAR16                                      *ControllerName;
  EFI_HANDLE                                  ValidControllerHandle;
  UINTN                                       StringLength;
  CHAR8                                       *PoolAddress;
  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *SupportedLanguagesBackup;
  UINTN                                       Switch = 0;
  CHAR8                                       Lang[4];
  CHAR8                                       *Language = NULL;
  CHAR8                                       *CandidateCode[7] = {"en-US", "da-DE", "fr-FR", "zh-CN", "ja", "ko-KP", "es-ES" }; 
  CHAR8                                       Sign[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  UINTN                                       Index;

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

  SupportedLanguages = ComponentName->SupportedLanguages;
  if (SupportedLanguages == NULL){
    return  EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress  = NULL;
  PoolAddress  = (CHAR8 *) SctAllocateZeroPool (StringLength + 1);
  if (PoolAddress == NULL){
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
    while (*Language != '\0'){
      for (Index = 0; Index < 7; Index ++){
        if (SctAsciiStrnCmp (Language, CandidateCode[Index], 2) == 0){
          Sign[Index] = 1;
        }
      }
      Language = SctAsciiSplitStr (&SupportedLanguagesBackup, ';');
    }
  } else {
     while (Lang[0] != '\0'){
      for (Index = 0; Index < 7; Index ++){
        if (SctAsciiStrnCmp (Lang, CandidateCode[Index], 2) == 0){
          Sign[Index] = 1;
        }
      }
      SctAsciiStrnCpy (Lang, SupportedLanguagesBackup, 3);
      SupportedLanguagesBackup = SupportedLanguagesBackup + 3;
    } 
  }

  for (Index = 0; Index < 7; Index ++){
    if (Sign[Index] == 0){
      Sign[7] = 1;
      Status = ComponentName->GetControllerName (
		                          ComponentName,
		                          ValidControllerHandle,
		                          NULL,
                                  CandidateCode[Index],
                                  &ControllerName
                                  );
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gComponentName2BBTestConformanceAssertionGuid008,
                   L"COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with unsupported language",
                   L"%a:%d: Language - %a, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   CandidateCode[Index],
                   Status
                   );
      break;		
    }
  }
  
  if (Sign[7] == 1){
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
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gComponentName2BBTestConformanceAssertionGuid008,
                   L"COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with unsupported language",
                   L"%a:%d: Language - %a, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   UnsupportedLanguageCode,
                   Status
                   );
  }
  
  gtBS->FreePool (PoolAddress);
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetControllerNameConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  DeviceHandle;
  EFI_HANDLE                                  ValidBusHandle;
  CHAR16                                      *ControllerName;
  CHAR8                                       *Language = NULL;
  CHAR8                                       Lang[4];
  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *SupportedLanguagesBackup;
  CHAR8                                       *PoolAddress;
  UINTN                                        StringLength;
  UINTN                                        Switch = 0;

  //
  // retrieve the first supported language
  //
  SupportedLanguages = ComponentName->SupportedLanguages;

  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress  = NULL;
  PoolAddress  = (CHAR8 *) SctAllocateZeroPool (StringLength + 1);
  if (PoolAddress == NULL){
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
  
  if ((Switch == 0 && *Language == '\0') || (Switch == 1 && Lang[0] == '\0')) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can get SupportedLanguage",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (PoolAddress);
    return EFI_UNSUPPORTED;
  }

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
                              (Switch == 0) ? Language : Lang,
                              &ControllerName
                              );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gComponentName2BBTestConformanceAssertionGuid009,
                   L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with irrelevant ControllerHandle",
                   L"%a:%d: Status - %r, %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   (Switch == 0) ? L"NULL" :  L"Please Use Native RFC3066 which is preferable in UEFI 2.X"
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
                                (Switch == 0) ? Language : Lang,
                                &ControllerName
                                );
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gComponentName2BBTestConformanceAssertionGuid010,
                     L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with irrelevant ChildHandle",
                     L"%a:%d: Status - %r, %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (Switch == 0) ? L"NULL" :  L"Please Use Native RFC3066 which is preferable in UEFI 2.X"
                     );

      ReleaseDeviceHandle (DeviceHandle);
    }
  }

  //
  //Remove this checkpoint after TDS Review
  //
/*  
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
                  __LINE__
                  );
    gtBS->FreePool (PoolAddress);
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
                              Language,
                              &ControllerName
                              );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gComponentName2BBTestConformanceAssertionGuid011,
                   L"COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName() returns EFI_UNSUPPORTED with device handle and not-NULL ChildHandle",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    ReleaseInvalidHandle (InvalidHandle);
  }
*/

  gtBS->FreePool (PoolAddress);
  return EFI_SUCCESS;
}

/*
EFI_STATUS
BBTestGetControllerNameConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  )
{
  EFI_STATUS                                  Status;
  UINTN                                       NoHandles;
  EFI_HANDLE                                  *HandleBuffer;
  UINTN                                       Index1, Index2;
  CHAR8                                       *Language;
  CHAR8                                       *SupportedLanguages;
  CHAR16                                      *ControllerName;
  EFI_TEST_ASSERTION                          AssertionType;

  Index1    = 0;
  Index2    = 0;
  NoHandles = 0;

  //
  // retrieve the first supported language
  //
  SupportedLanguages = ComponentName->SupportedLanguages;
  Language = SctAsciiSplitStr (&SupportedLanguages, ';');
  if (Language == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can get SupportedLanguage",
                   L"%a:%d:",
                   __FILE__,
                   __LINE__
                   );
    return EFI_UNSUPPORTED;
  }

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
                    __LINE__,
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
                               Language,
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
                  gComponentName2BBTestConformanceAssertionGuid012,
                  L"EFI_COMPONENT_NAME2_PROTOCOL.GetControllerName - Go through each of the handles",
                  L"%a:%d, Status - %r, Index1 - %d, NoHandles - %d",
                  __FILE__,
                  __LINE__,
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
                                 Language,
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
                  gComponentName2BBTestConformanceAssertionGuid013,
                  L"EFI_COMPONENT_NAME_PROTOCOL.GetControllerName - Go through each of the handles and child handles",
                  L"%a:%d, Status - %r, Index1 - %d, Index2 - %d, NoHandles - %d",
                  __FILE__,
                  __LINE__,
                  Status,
                  Index1,
                  Index2,
                  NoHandles
                  );

  gtBS->FreePool (HandleBuffer);
  return EFI_SUCCESS;
}
*/
//
// private functions
//

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
  IN  EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName,
  OUT EFI_HANDLE                            *ValidControllerHandle
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               NoHandles;
  EFI_HANDLE          *HandleBuffer;
  EFI_HANDLE          ComponentName2Handle = NULL;
  UINTN               ControllerHandleCount;
  EFI_HANDLE          *ControllerHandleBuffer;

  EFI_COMPONENT_NAME2_PROTOCOL           *TestedComponentName;

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
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the component name2 protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiComponentName2ProtocolGuid,
                     &TestedComponentName
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (TestedComponentName == ComponentName) {
      ComponentName2Handle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (ComponentName2Handle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the component name handle.
  //
  Status = SctGetManagedControllerHandles (
             ComponentName2Handle,
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
  IN  EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName,
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
  EFI_HANDLE          ComponentName2Handle = NULL;
  UINTN               ControllerHandleCount;
  EFI_HANDLE          *ControllerHandleBuffer;
  UINTN               NumberOfChildren;
  EFI_HANDLE          *ChildControllerHandleBuffer;

  EFI_COMPONENT_NAME2_PROTOCOL           *TestedComponentName;

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
                     &gBlackBoxEfiComponentName2ProtocolGuid,
                     &TestedComponentName
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (TestedComponentName == ComponentName) {
      ComponentName2Handle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (ComponentName2Handle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the component name handle.
  //
  Status = SctGetManagedControllerHandles (
             ComponentName2Handle,
             &ControllerHandleCount,
             &ControllerHandleBuffer
             );
  if (EFI_ERROR(Status) || (ControllerHandleCount == 0)) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < ControllerHandleCount; Index++) {
    ChildControllerHandleBuffer = NULL;

    Status = SctGetManagedChildControllerHandles (
               ComponentName2Handle,
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

