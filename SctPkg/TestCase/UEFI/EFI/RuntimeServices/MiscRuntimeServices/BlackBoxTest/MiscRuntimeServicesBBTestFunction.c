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

  MiscRuntimeServicesBBTestFunction.c

Abstract:

  Interface Test Cases of Miscellaneous Runtime Services

--*/

#include "SctLib.h"
#include "MiscRuntimeServicesBBTestMain.h"

/**
 *  Entrypoint for gtRT->ResetSystem() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
BBTestResetSystemInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  UINT8                                Buffer[1024];
  RESET_DATA                           *ResetData;
  UINTN                                Size;

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
  // Get the Recovery Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   &RecoveryLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle recovery library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Read reset record
  //
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &Size,
                          Buffer
                          );
  ResetData = (RESET_DATA *)Buffer;
  if (EFI_ERROR(Status) || (Size < sizeof(RESET_DATA))) {
    //
    // Step 1
    //
  } else if (ResetData->Step == 1) {
    //
    // Step 2
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto ResetSystemStep2;
    }
  } else if (ResetData->Step == 2) {
    //
    // Step 3
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto ResetSystemStep3;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.1.2.1  ResetSystem must succeed when ResetType is EfiResetCold
    //
    ResetData->Step = 1;
    ResetData->TplIndex = Index;
    Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            sizeof (RESET_DATA),
                            Buffer
                            );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"TestRecoveryLib - WriteResetRecord",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

    //
    // Print out some information to avoid the user thought it is an error
    //
    SctPrint (L"System will cold reset after 1 second...");
    gtBS->Stall (1000000);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtRT->ResetSystem (
            EfiResetCold,
            EFI_SUCCESS,
            0,
            NULL
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_FAILED;

ResetSystemStep2:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscRuntimeServicesInterfaceTestAssertionGuid001: \
                   (Index == 1? \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid001: \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid002),
                   L"RT.ResetSystem - EfiResetCold",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // 4.1.2.2  ResetSystem must succeed when ResetType is EfiResetWarm
    //
    ResetData->Step = 2;
    ResetData->TplIndex = Index;
    Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            sizeof (RESET_DATA),
                            Buffer
                            );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"TestRecoveryLib - WriteResetRecord",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

    //
    // Print out some information to avoid the user thought it is an error
    //
    SctPrint (L"System will warm reset after 1 second...");
    gtBS->Stall (1000000);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtRT->ResetSystem (
            EfiResetWarm,
            EFI_SUCCESS,
            0,
            NULL
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_FAILED;

ResetSystemStep3:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscRuntimeServicesInterfaceTestAssertionGuid002: \
                   (Index == 1? \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid003: \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid004),
                   L"RT.ResetSystem - EfiResetWarm",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtRT->ResetSystem() Manual Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
BBTestResetSystemManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  UINT8                                Buffer[1024];
  RESET_DATA                           *ResetData;
  UINTN                                Size;

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
  // Get the Recovery Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   &RecoveryLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle recovery library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Read reset record
  //
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &Size,
                          Buffer
                          );
  ResetData = (RESET_DATA *)Buffer;
  if (EFI_ERROR(Status) || (Size < sizeof(RESET_DATA))) {
    //
    // Step 1
    //
  } else if (ResetData->Step == 1) {
    //
    // Step 2
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto ManualTestStep2;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.2.2.1  ResetSystem must succeed when ResetType is EfiResetShutdown
    //
    ResetData->Step = 1;
    ResetData->TplIndex = Index;
    Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            sizeof (RESET_DATA),
                            Buffer
                            );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"TestRecoveryLib - WriteResetRecord",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

    //
    // Print out some information to avoid the user thought it is an error.
    //
    // And the stall a second is required to make sure the recovery data has
    // been written into the storage device.
    //
    SctPrint (L"System will shut down (or cold reset) after 1 second...");
    gtBS->Stall (1000000);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtRT->ResetSystem (
            EfiResetShutdown,
            EFI_SUCCESS,
            0,
            NULL
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_FAILED;

ManualTestStep2:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscRuntimeServicesCombinationTestAssertionGuid006: \
                   (Index == 1? \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid005: \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid006),
                   L"RT.ResetSystem - EfiResetShutdown",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  return EFI_SUCCESS;
}

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)

EFI_STATUS
BBTestQueryCapsuleCapabilitiesTest (
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
  UINT64                               MaxCapsuleSize;
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
                  L"RT.QueryCapsuleCapabilities_Func - QueryCapsuleCapabilities_Func it's not Supported in EFI",
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
                   L"RT.QueryCapsuleCapabilities - Allocate zero pool for EFI_CAPSULE_HEADER",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_OUT_OF_RESOURCES;
  }

  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) AllocatedBuffer;
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);

// When the flag is CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE and CAPSULE_FLAGS_PERSIST_ACROSS_RESET, platform will ignore the CapsuleGuid 
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_PERSIST_ACROSS_RESET|CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE;
  Status = gtRT->QueryCapsuleCapabilities (CapsuleHeaderArray, 1, &MaxCapsuleSize, &ResetType);
  if (EFI_ERROR(Status) && (Status != EFI_UNSUPPORTED)) {
  	AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestFunctionAssertionGuid007,
                 L"RT.QueryCapsuleCapabilities - invoke QueryCapsuleCapabilities with CAPSULE_FLAGS_PERSIST_ACROSS_RESET flag set in EFI_CAPSULE_HEADER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

//
// Spec say: when the flag is none, but what meaning is none. remove this checkpoint
//
/*
  CapsuleHeaderArray[0]->Flags = 0;
  Status = gtRT->QueryCapsuleCapabilities (CapsuleHeaderArray, 1, &MaxCapsuleSize, &ResetType);

  if (EFI_ERROR(Status) && (Status != EFI_UNSUPPORTED)) {
  	AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestFunctionAssertionGuid008,
                 L"RT.QueryCapsuleCapabilities - invoke QueryCapsuleCapabilities without CAPSULE_FLAGS_PERSIST_ACROSS_RESET flag set in EFI_CAPSULE_HEADER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
*/
  SctFreePool (AllocatedBuffer);
  return EFI_SUCCESS;
}

#endif
