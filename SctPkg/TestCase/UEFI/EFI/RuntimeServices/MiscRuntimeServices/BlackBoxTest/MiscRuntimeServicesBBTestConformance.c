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

  MiscRuntimeServicesBBTestFunction.c

Abstract:

  Interface Test Cases of Miscellaneous Runtime Services

--*/

#include "SctLib.h"
#include "MiscRuntimeServicesBBTestMain.h"

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)

EFI_STATUS
BBTestUpdateCapsuleConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                           Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                *AllocatedBuffer;
  EFI_CAPSULE_HEADER                  *CapsuleHeaderArray[2];

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

  if (FALSE == CheckBBTestCanRunAndRecordAssertion (
                  StandardLib, 
                  L"RT.UpdateCapsule_Conf- UpdateCapsule_Conf it's not Supported in EFI",
                  __FILE__,
                  (UINTN)__LINE__
                  )) {
    return EFI_SUCCESS;
  }

  AllocatedBuffer = (UINT8 *)SctAllocatePool (sizeof(EFI_CAPSULE_HEADER));
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"RT.UpdateCapsule_conf - Allocate pages for EFI_CAPSULE_HEADER",
                   L"%a:%d,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_PERSIST_ACROSS_RESET;


  // When CapsuleCount is 0, the return status code should be EFI_INVALID_PARAMETER
  Status = gtRT->UpdateCapsule(
  	             CapsuleHeaderArray,
  	             0, // invaild
  	             (EFI_PHYSICAL_ADDRESS ) 0
  	             );
  if (Status == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid001,
                 L"RT.UpdateCapsule - invoke UpdateCapsule with invalid CapsuleCount - 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
                
  //
  // when the flag is CAPSULE_FLAGS_PERSIST_ACROSS_RESET, ScatterGatherList can't be NULL.
  //

  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_PERSIST_ACROSS_RESET | CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE;

  Status = gtRT->UpdateCapsule(
  	             CapsuleHeaderArray,
  	             1,
  	             (EFI_PHYSICAL_ADDRESS ) 0
  	             );
  if (Status == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid002,
                 L"RT.UpdateCapsule - invoke UpdateCapsule with invalid ScatterGatherList",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );


  //
  // A capsule which has the CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE flag must have
  // CAPSULE_FLAGS_PERSIST_ACROSS_RESET set in its header as well.
  //
  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE;

  Status = gtRT->UpdateCapsule(
  	             CapsuleHeaderArray,
  	             1,
  	             (EFI_PHYSICAL_ADDRESS ) 0
  	             );
  if (Status == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid003,
                 L"RT.UpdateCapsule - invoke UpdateCapsule with invalid Flags",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // A capsule which has the CAPSULE_FLAGS_INITIATE_RESET Flag must have 
  // CAPSULE_FLAGS_PERSIST_ACROSS_RESET set in its header as well.
  //
  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_INITIATE_RESET;

  Status = gtRT->UpdateCapsule(
  	             CapsuleHeaderArray,
  	             1,
  	             (EFI_PHYSICAL_ADDRESS ) 0
  	             );
  if (Status == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid005,
                 L"RT.UpdateCapsule - invoke UpdateCapsule with invalid Flags",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  SctFreePool (AllocatedBuffer);
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestQueryCapsuleCapabilitiesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                           Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                *AllocatedBuffer;
  EFI_CAPSULE_HEADER                  *CapsuleHeaderArray[2];
  EFI_RESET_TYPE                       ResetType;

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

  if (FALSE == CheckBBTestCanRunAndRecordAssertion(
                  StandardLib, 
                  L"RT.QueryCapsuleCapabilities_Conf - QueryCapsuleCapabilities_Conf it's not Supported in EFI",
                  __FILE__,
                  (UINTN)__LINE__
                  )) {
    return EFI_SUCCESS;
  }

  AllocatedBuffer = (UINT8 *)SctAllocatePool (sizeof(EFI_CAPSULE_HEADER));
  if (AllocatedBuffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"RT.QueryCapsuleCapabilities_Conf - Allocate zero pool for EFI_CAPSULE_HEADER",
                   L"%a:%d,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
// When the flag is CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE and CAPSULE_FLAGS_PERSIST_ACROSS_RESET, platform will ignore the CapsuleGuid   
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_PERSIST_ACROSS_RESET | CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE;

  Status = gtRT->QueryCapsuleCapabilities(
  	               CapsuleHeaderArray, 
  	               1, 
  	               NULL, //invalid
  	               &ResetType);
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid004,
                 L"RT.QueryCapsuleCapabilities - invoke QueryCapsuleCapabilities with invalid MaxiumCapsuleSize",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  SctFreePool (AllocatedBuffer);
  return EFI_SUCCESS;
}

#endif
