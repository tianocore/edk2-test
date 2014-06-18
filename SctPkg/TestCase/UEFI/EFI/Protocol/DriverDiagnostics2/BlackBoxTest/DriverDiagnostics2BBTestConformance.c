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
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    DriverDiagnostics2BBTestConformance.c

Abstract:
    for EFI Driver Diagnostics2 Protocol's generic Conformance Test

--*/

#include "SctLib.h"
#include "DriverDiagnostics2BBTest.h"

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
  IN  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2,
  OUT EFI_HANDLE                            *ValidControllerHandle
  );

STATIC
EFI_STATUS
FindMatchedBusHandle (
  IN  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2,
  OUT EFI_HANDLE                            *ValidBusHandle
  );

//
// global variables
//
EFI_GUID mTestNoInterfaceProtocol1Guid = TEST_NO_INTERFACE_PROTOCOL_1_GUID;
EFI_GUID mTestNoInterfaceProtocol2Guid = TEST_NO_INTERFACE_PROTOCOL_2_GUID;


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

EFI_STATUS
BBTestRunDiagnosticsConformanceTest (
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
  // 7.2.1.2.1  Call RunDiagnostics() with invalid parameters.
  //
  BBTestRunDiagnosticsConformanceTestCheckpoint1 (StandardLib, DriverDiagnostics2);

  //
  // 7.2.1.2.2  Call RunDiagnostics() with unsupported Language.
  //
  BBTestRunDiagnosticsConformanceTestCheckpoint2 (StandardLib, DriverDiagnostics2);

  //
  // 7.2.1.2.3  Call RunDiagnostics() with unsupported ControllerHandle.
  //
  BBTestRunDiagnosticsConformanceTestCheckpoint3 (StandardLib, DriverDiagnostics2);

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
BBTestRunDiagnosticsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  ValidControllerHandle;
  EFI_GUID                                    *ErrorType;
  UINTN                                       BufferSize;
  CHAR16                                      *Buffer;

  CHAR8                                       *Language = NULL;            //Language for RFC3066
  CHAR8                                       Lang[4];                     //Language for ISO639-2
  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *SupportedLanguagesBackup;
  CHAR8                                       *PoolAddress;
  UINTN                                        StringLength;
  UINTN                                        Switch = 0;
  //
  // Init
  //
  Buffer = NULL;

  //
  // retrieve the first supported language
  //
  SupportedLanguages = DriverDiagnostics2->SupportedLanguages;
  if (SupportedLanguages == NULL){
    return  EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress = (CHAR8 *) SctAllocatePool (StringLength + 1);
  SupportedLanguagesBackup = PoolAddress;
  if (SupportedLanguagesBackup ==NULL){
    return  EFI_UNSUPPORTED;
  }	
  SctAsciiStrCpy (SupportedLanguagesBackup, SupportedLanguages);

  if ((SctAsciiStrChr (SupportedLanguagesBackup, '-') == NULL) &&
  	(SctAsciiStrChr (SupportedLanguagesBackup, ';') == NULL) && 
  	(SctAsciiStrLen (SupportedLanguagesBackup) >= 3)){
  //ISO639-2, it belongs to EFI1.1  
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
  // with NULL ControllerHandle
  //
  Status = DriverDiagnostics2->RunDiagnostics (
                                DriverDiagnostics2,
                                NULL,
                                NULL,
                                0,
                                (Switch == 0) ?  Language : Lang,
                                &ErrorType,
                                &BufferSize,
                                &Buffer
                                );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid001,
                 L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() returns EFI_INVALID_PARAMETER with NULL ControllerHandle",
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
  // retrieve a device handle that could be managed by the Driver Diagnostics Protocol
  //
  Status = FindMatchedDeviceHandle (DriverDiagnostics2, &ValidControllerHandle);
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
  Status = DriverDiagnostics2->RunDiagnostics (
                                DriverDiagnostics2,
                                ValidControllerHandle,
                                NULL,
                                0,
                                NULL,
                                &ErrorType,
                                &BufferSize,
                                &Buffer
                                );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid003,
                 L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() returns EFI_INVALID_PARAMETER with Language being NULL",
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
  Status = DriverDiagnostics2->RunDiagnostics (
                                DriverDiagnostics2,
                                ValidControllerHandle,
                                NULL,
                                0,
                                (Switch == 0) ?  Language : Lang,
                                NULL,
                                &BufferSize,
                                &Buffer
                                );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid004,
                 L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() return EFI_INVALID_PARAMETER with ErrorType being NULL",
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
  Status = DriverDiagnostics2->RunDiagnostics (
                                DriverDiagnostics2,
                                ValidControllerHandle,
                                NULL,
                                0,
                                (Switch == 0) ?  Language : Lang,
                                &ErrorType,
                                NULL,
                                &Buffer
                                );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid005,
                 L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() return EFI_INVALID_PARAMETER with BufferSize being NULL",
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
  Status = DriverDiagnostics2->RunDiagnostics (
                                DriverDiagnostics2,
                                ValidControllerHandle,
                                NULL,
                                0,
                                (Switch == 0) ?  Language : Lang,
                                &ErrorType,
                                &BufferSize,
                                NULL
                                );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid006,
                 L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() return EFI_INVALID_PARAMETER with Buffer being NULL",
                 L"%a:%d:NULL Buffer Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (PoolAddress);
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
BBTestRunDiagnosticsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  ValidControllerHandle;
  EFI_GUID                                    *ErrorType;
  UINTN                                       BufferSize;
  CHAR16                                      *Buffer = NULL;

  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *UnsupportedLanguageCode = "enus";
  UINTN                                       StringLength;
  CHAR8                                       *PoolAddress;
  CHAR8                                       *SupportedLanguagesBackup;
  UINTN                                       Switch = 0;
  CHAR8                                       Lang[4];
  CHAR8                                       *Language = NULL;
  CHAR8                                       *CandidateCode[7] = {"en-US", "da-DE", "fr-FR", "zh-CN", "ja", "ko-KP", "es-ES" }; 
  CHAR8                                       Sign[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  UINTN                                       Index;

  //
  // retrieve a device handle that could be managed by the Driver Diagnostics Protocol
  //
  Status = FindMatchedDeviceHandle (DriverDiagnostics2, &ValidControllerHandle);
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

  SupportedLanguages = DriverDiagnostics2->SupportedLanguages;
  if (SupportedLanguages == NULL){
    return  EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress = (CHAR8 *) SctAllocatePool (StringLength + 1);
  SupportedLanguagesBackup = PoolAddress;
  if (SupportedLanguagesBackup ==NULL){
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
      Status = DriverDiagnostics2->RunDiagnostics (
                                    DriverDiagnostics2,
                                    ValidControllerHandle,
                                    NULL,
                                    0,
                                    CandidateCode[Index],
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
                   L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() return EFI_UNSUPPORTED with unsupported language",
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
    Status = DriverDiagnostics2->RunDiagnostics (
                                  DriverDiagnostics2,
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
                    L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() return EFI_UNSUPPORTED with unsupported language",
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
BBTestRunDiagnosticsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  DeviceHandle;
  EFI_HANDLE                                  ValidBusHandle;
  EFI_GUID                                    *ErrorType;
  UINTN                                       BufferSize;
  CHAR16                                      *Buffer;

  CHAR8                                       *Language = NULL;            //Language for RFC3066
  CHAR8                                       Lang[4];                     //Language for ISO639-2
  CHAR8                                       *SupportedLanguages;
  CHAR8                                       *SupportedLanguagesBackup;
  CHAR8                                       *PoolAddress;
  UINTN                                        StringLength;
  UINTN                                        Switch = 0;
  //
  // Init
  //
  Buffer = NULL;

  //
  // retrieve the first supported language
  //
  SupportedLanguages = DriverDiagnostics2->SupportedLanguages;
  if (SupportedLanguages == NULL){
    return  EFI_UNSUPPORTED;
  }
  
  StringLength = SctAsciiStrLen (SupportedLanguages);
  PoolAddress = (CHAR8 *) SctAllocatePool (StringLength + 1);
  SupportedLanguagesBackup = PoolAddress;
  if (SupportedLanguagesBackup ==NULL){
    return  EFI_UNSUPPORTED;
  }	
  SctAsciiStrCpy (SupportedLanguagesBackup, SupportedLanguages);

  if ((SctAsciiStrChr (SupportedLanguagesBackup, '-') == NULL) &&
  	(SctAsciiStrChr (SupportedLanguagesBackup, ';') == NULL) && 
  	(SctAsciiStrLen (SupportedLanguagesBackup) >= 3)){
  //ISO639-2, it belongs to EFI1.1  
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
  // Create a virtual device handle
  //
  CreateDeviceHandle (&DeviceHandle);
  if (DeviceHandle != NULL) {
    //
    // Input this DeviceHandle as the ControllerHandle input
    // for the RunDiagnostics().
    //
    Status = DriverDiagnostics2->RunDiagnostics (
                                  DriverDiagnostics2,
                                  DeviceHandle,
                                  NULL,
                                  0,
                                  (Switch == 0) ?  Language : Lang,
                                  &ErrorType,
                                  &BufferSize,
                                  &Buffer
                                  );

    if (EFI_UNSUPPORTED == Status) {
      AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConformanceTestAssertionGuid008,
                   L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() return EFI_UNSUPPORTED with virtual device handle",
                   L"%a:%d: Status - %r, %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   (Switch == 0) ? L"NULL" :  L"Please Use Native RFC3066 which is preferable in UEFI 2.X"
                   );

    //
    // retrieve a bus handle that could be managed by the Component Name Protocol
    //
    Status = FindMatchedBusHandle (DriverDiagnostics2, &ValidBusHandle);
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
      Status = DriverDiagnostics2->RunDiagnostics (
                                     DriverDiagnostics2,
                                     ValidBusHandle,
                                     DeviceHandle,
                                     0,
                                     (Switch == 0) ?  Language : Lang,
                                     &ErrorType,
                                     &BufferSize,
                                     &Buffer
                                     );
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = ((Switch == 0) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_WARNING);
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gConformanceTestAssertionGuid009,
                     L"EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics - RunDiagnostics() return EFI_UNSUPPORTED with virtual child handle",
                     L"%a:%d: Status - %r, %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (Switch == 0) ? L"NULL" :  L"Please Use Native RFC3066 which is preferable in UEFI 2.X"
                     );

      ReleaseDeviceHandle (DeviceHandle);
    }
  }


  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
    Buffer = NULL ;
  }

  gtBS->FreePool (PoolAddress);
  return EFI_SUCCESS;
}

//
// private functions
//

/**
 *  @brief This function create an virtual device handle. To avoid memory leak,
 *         it is stronggly recommended to pare with ReleaseDeviceHandle.
 *  @see ReleaseDeviceHandle.
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
  IN  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2,
  OUT EFI_HANDLE                            *ValidControllerHandle
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               NoHandles;
  EFI_HANDLE          *HandleBuffer;
  EFI_HANDLE          DriverDiagnostics2Handle = NULL;
  UINTN               ControllerHandleCount;
  EFI_HANDLE          *ControllerHandleBuffer;

  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL     *TestedDriverDiagnostics2 = NULL;

  //
  // locate all Driver Diagnostics protocol instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the Driver Diagnostics2 protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
                     &TestedDriverDiagnostics2
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (TestedDriverDiagnostics2 == DriverDiagnostics2) {
      DriverDiagnostics2Handle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (DriverDiagnostics2Handle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the DriverDiagnostics2Handle.
  //
  Status = SctGetManagedControllerHandles (
             DriverDiagnostics2Handle,
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
  IN  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2,
  OUT EFI_HANDLE                            *ValidBusHandle
  )
/*
  The method is: locate all bus handles, and feed in until finding the first handle.
*/
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               NoHandles;
  EFI_HANDLE          *HandleBuffer;
  EFI_HANDLE          DriverDiagnostics2Handle = NULL;
  UINTN               ControllerHandleCount;
  EFI_HANDLE          *ControllerHandleBuffer;
  UINTN               NumberOfChildren;
  EFI_HANDLE          *ChildControllerHandleBuffer;

  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL           *TestedDriverDiagnostics2 = NULL;

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
                     &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
                     &TestedDriverDiagnostics2
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (TestedDriverDiagnostics2 == DriverDiagnostics2) {
      DriverDiagnostics2Handle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (DriverDiagnostics2Handle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the component name handle.
  //
  Status = SctGetManagedControllerHandles (
             DriverDiagnostics2Handle,
             &ControllerHandleCount,
             &ControllerHandleBuffer
             );
  if (EFI_ERROR(Status) || (ControllerHandleCount == 0)) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < ControllerHandleCount; Index++) {
    ChildControllerHandleBuffer = NULL;

    Status = SctGetManagedChildControllerHandles (
               DriverDiagnostics2Handle,
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

