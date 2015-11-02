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

  MiscBootServicesBBTestFunction.c

Abstract:

  Interface Test Cases of Misellaneous Boot Services

--*/

#include "SctLib.h"
#include "MiscBootServicesBBTestMain.h"

/**
 *  Entrypoint for gtBS->SetWatchdogTimer() Interface Test.
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
BBTestSetWatchdogTimerInterfaceTest (
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
                   (VOID **) &StandardLib
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
                   (VOID **) &RecoveryLib
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
  ResetData = (RESET_DATA *)&Buffer;
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
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      goto SetWatchdogTimerStep2;
    }
  } else if (ResetData->Step == 2) {
    //
    // Step 3
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto SetWatchdogTimerStep3;
    }
  } else if (ResetData->Step == 3) {
    //
    // Step 4
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      goto SetWatchdogTimerStep4;
    }
  } else if (ResetData->Step == 4) {
    //
    // Step 5
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto SetWatchdogTimerStep5;
    }
  } else if (ResetData->Step == 5) {
    //
    // Step 6
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      goto SetWatchdogTimerStep6;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.1.2.1  SetWatchdogTimer must succeed when enable the watchdog timer.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     5,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_UNSUPPORTED) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"BS.SetWatchdogTimer - Unsupported",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return EFI_SUCCESS;
    }
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMiscBootServicesInterfaceTestAssertionGuid001: \
                     (Index == 1? \
                      gMiscBootServicesBBTestFunctionAssertionGuid001: \
                      gMiscBootServicesBBTestFunctionAssertionGuid002),
                     L"BS.SetWatchdogTimer - enable watchdog timer",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }
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
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    gtBS->Stall (
            3500000
            );

    //
    // Disable WatchdogTimer
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     0,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_PASSED,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid001: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid001: \
                    gMiscBootServicesBBTestFunctionAssertionGuid002),
                   L"BS.SetWatchdogTimer - enable watchdog timer",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_SUCCESS,
                   TplArray[Index]
                   );
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMiscBootServicesInterfaceTestAssertionGuid009: \
                     (Index == 1? \
                      gMiscBootServicesBBTestFunctionAssertionGuid017: \
                      gMiscBootServicesBBTestFunctionAssertionGuid018),
                     L"BS.SetWatchdogTimer - disable watchdog timer",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

SetWatchdogTimerStep2:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid002: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid003: \
                    gMiscBootServicesBBTestFunctionAssertionGuid004),
                   L"BS.SetWatchdogTimer - should not reset after 3.5s",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );
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
    // SetWatchdogTimer again
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                         5,
                         0x10000,
                         0,
                         NULL
                         );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid001: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid001: \
                    gMiscBootServicesBBTestFunctionAssertionGuid002),
                   L"BS.SetWatchdogTimer - enable watchdog timer",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
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
    AssertionType = EFI_TEST_ASSERTION_FAILED;

    SctPrint (L"System will reset after 6.5 second...");
    gtBS->Stall (
            6500000
            );

SetWatchdogTimerStep3:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid003: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid005: \
                    gMiscBootServicesBBTestFunctionAssertionGuid006),
                   L"BS.SetWatchdogTimer - should reset after 6.5s",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // 4.1.2.2  SetWatchdogTimer must succeed when change the Timeout.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     5,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid004: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid007: \
                    gMiscBootServicesBBTestFunctionAssertionGuid008),
                   L"BS.SetWatchdogTimer - enable watchdog timer",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     10,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMiscBootServicesInterfaceTestAssertionGuid005: \
                     (Index == 1? \
                      gMiscBootServicesBBTestFunctionAssertionGuid009: \
                      gMiscBootServicesBBTestFunctionAssertionGuid010),
                     L"BS.SetWatchdogTimer - change watchdog timer",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }
    ResetData->Step = 3;
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
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    gtBS->Stall (
            8500000
            );

    //
    // Disable WatchdogTimer
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     0,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_PASSED,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid005: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid009: \
                    gMiscBootServicesBBTestFunctionAssertionGuid010),
                   L"BS.SetWatchdogTimer - change watchdog timer",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_SUCCESS,
                   TplArray[Index]
                   );
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMiscBootServicesInterfaceTestAssertionGuid009: \
                     (Index == 1? \
                      gMiscBootServicesBBTestFunctionAssertionGuid017: \
                      gMiscBootServicesBBTestFunctionAssertionGuid018),
                     L"BS.SetWatchdogTimer - disable watchdog timer",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

SetWatchdogTimerStep4:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid006: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid011: \
                    gMiscBootServicesBBTestFunctionAssertionGuid012),
                   L"BS.SetWatchdogTimer - should not reset after 8.5s",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    ResetData->Step = 4;
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
    // SetWatchdogTimer again
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     10,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid001: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid001: \
                    gMiscBootServicesBBTestFunctionAssertionGuid002),
                   L"BS.SetWatchdogTimer - enable watchdog timer",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
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
    AssertionType = EFI_TEST_ASSERTION_FAILED;

    SctPrint (L"System will reset after 11.5 second...");
    gtBS->Stall (
            11500000
            );

SetWatchdogTimerStep5:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid007: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid013: \
                    gMiscBootServicesBBTestFunctionAssertionGuid014),
                   L"BS.SetWatchdogTimer - should reset after 11.5s",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            0,
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
    // 4.1.2.3  SetWatchdogTimer must succeed when disable the watchdog timer.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     5,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid008: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid015: \
                    gMiscBootServicesBBTestFunctionAssertionGuid016),
                   L"BS.SetWatchdogTimer - enable watchdog timer",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     0,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid009: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid017: \
                    gMiscBootServicesBBTestFunctionAssertionGuid018),
                   L"BS.SetWatchdogTimer - disable watchdog timer",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->SetWatchdogTimer (
                     0,
                     0x10000,
                     0,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid010: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid019: \
                    gMiscBootServicesBBTestFunctionAssertionGuid020),
                   L"BS.SetWatchdogTimer - disable watchdog timer again",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    ResetData->Step = 5;
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
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    gtBS->Stall (
            6000000
            );

SetWatchdogTimerStep6:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesBBTestFunctionAssertionGuid085: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid086: \
                    gMiscBootServicesBBTestFunctionAssertionGuid087),
                   L"BS.SetWatchdogTimer - should not reset after 6s",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );


  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->Stall() Interface Test.
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
BBTestStallInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  EFI_TIME                             StartTime;
  EFI_TIME                             EndTime;
  UINT32                               SecondsElapsed;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE + 1; Index++) {
    //
    // 4.2.2.1  Stall must succeed.
    //
    gtRT->GetTime (&StartTime, NULL);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->Stall (
                     10000000
                     );
    gtBS->RestoreTPL (OldTpl);
    gtRT->GetTime (&EndTime, NULL);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid011: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid021: \
                    gMiscBootServicesBBTestFunctionAssertionGuid022),
                   L"BS.Stall - 10 seconds",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    SecondsElapsed = GetSecondsElapsed (&StartTime, &EndTime);
    if ((SecondsElapsed <= 10 + MAX_SECOND_MARGIN) &&
         (SecondsElapsed >= 10 - MAX_SECOND_MARGIN)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid012: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid023: \
                    gMiscBootServicesBBTestFunctionAssertionGuid024),
                   L"BS.Stall - Verify Duration",
                   L"%a:%d:TPL - %d, Start - %t:%d, End - %t:%d, Seconds - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index],
                   &StartTime,
                   StartTime.Second,
                   &EndTime,
                   EndTime.Second,
                   SecondsElapsed
                   );

  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->CopyMem() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3
//
EFI_STATUS
BBTestCopyMemInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  UINT8                                *Buffer;
  EFI_PHYSICAL_ADDRESS                 BufferAddress;
  UINT8                                *Src;
  UINT8                                *Dest;

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
  // Allocate buffer
  //
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   EfiBootServicesData,
                   1,
                   &BufferAddress
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePages - 1 page EfiBootServicesData",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  Buffer = (UINT8*)(UINTN)BufferAddress;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.3.2.1  CopyMem must succeed with valid parameters when Source
    //          and Destination are not overlapped.
    //
    Dest = Buffer + 50;
    SetTestMem (Dest, 50, 2);
    Src = Buffer;
    SetTestMem (Src, 50, 1);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->CopyMem (
            (VOID *)Dest,
            (VOID *)Src,
            50
            );
    gtBS->RestoreTPL (OldTpl);
    Status = CheckTestMem (Dest, 50, 1);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid013: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid025: \
                    gMiscBootServicesBBTestFunctionAssertionGuid026),
                   L"BS.CopyMem - not overlapped",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // 4.3.2.2  CopyMem must succeed with valid parameters when Source
    //          and Destination are overlapped.
    //

    //
    // the whole Source and Destination are overlapped.
    //
    Dest = Buffer;
    SetTestMem (Dest, 50, 2);
    Src = Buffer;
    SetTestMem (Src, 50, 1);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->CopyMem (
            (VOID *)Dest,
            (VOID *)Src,
            50
            );
    gtBS->RestoreTPL (OldTpl);
    Status = CheckTestMem (Dest, 50, 1);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid014: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid027: \
                    gMiscBootServicesBBTestFunctionAssertionGuid028),
                   L"BS.CopyMem - full overlapped",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // the top half of Source and the bottom half of Destination are overlapped.
    //
    Dest = Buffer;
    SetTestMem (Dest, 50, 2);
    Src = Buffer + 25;
    SetTestMem (Src, 25, 1);
    SetTestMem (Src + 25, 25, 3);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->CopyMem (
            (VOID *)Dest,
            (VOID *)Src,
            50
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    Status = CheckTestMem (Dest, 25, 1);
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    Status = CheckTestMem (Dest + 25, 25, 3);
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid015: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid029: \
                    gMiscBootServicesBBTestFunctionAssertionGuid030),
                   L"BS.CopyMem - top src part overlapped",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // the top of Source and the bottom of Destination are overlapped and
    // there is only 1 byte left which is not overlapped.
    //
    Dest = Buffer;
    SetTestMem (Dest, 50, 2);
    Src = Buffer + 1;
    SetTestMem (Src, 1, 1);
    SetTestMem (Src + 1, 49, 3);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->CopyMem (
            (VOID *)Dest,
            (VOID *)Src,
            50
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    Status = CheckTestMem (Dest, 1, 1);
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    Status = CheckTestMem (Dest + 1, 49, 3);
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid016: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid031: \
                    gMiscBootServicesBBTestFunctionAssertionGuid032),
                   L"BS.CopyMem - top src overlapped 1 byte left",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // the bottom half of Source and the top half of Destination are overlapped.
    //
    Dest = Buffer + 25;
    SetTestMem (Dest, 50, 2);
    Src = Buffer;
    SetTestMem (Src, 25, 1);
    SetTestMem (Src + 25, 25, 3);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->CopyMem (
            (VOID *)Dest,
            (VOID *)Src,
            50
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    Status = CheckTestMem (Dest, 25, 1);
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    Status = CheckTestMem (Dest + 25, 25, 3);
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid017: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid033: \
                    gMiscBootServicesBBTestFunctionAssertionGuid034),
                   L"BS.CopyMem - bottom src part overlapped",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // the bottom of Source and the top of Destination are overlapped and
    // there is only 1 byte left which is not overlapped.
    //
    Dest = Buffer + 1;
    SetTestMem (Dest, 50, 2);
    Src = Buffer;
    SetTestMem (Src, 1, 1);
    SetTestMem (Src + 1, 49, 3);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->CopyMem (
            (VOID *)Dest,
            (VOID *)Src,
            50
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    Status = CheckTestMem (Dest, 1, 1);
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    Status = CheckTestMem (Dest + 1, 49, 3);
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid018: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid035: \
                    gMiscBootServicesBBTestFunctionAssertionGuid036),
                   L"BS.CopyMem - bottom src overlapped 1 byte left",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // 4.3.2.3  CopyMem must succeed when Length is 0.
    //
    Dest = Buffer;
    SetTestMem (Dest, 50, 2);
    Src = Buffer + 50;
    SetTestMem (Src, 50, 1);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->CopyMem (
            (VOID *)Dest,
            (VOID *)Src,
            0
            );
    gtBS->RestoreTPL (OldTpl);
    Status = CheckTestMem (Dest, 50, 2);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid019: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid037: \
                    gMiscBootServicesBBTestFunctionAssertionGuid038),
                   L"BS.CopyMem - Length is 0",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // 4.3.2.4  CopyMem must succeed with valid parameters when Source
    //          and Destination are not 4-byte aligned.
    //

    // covered by implementation of 4.3.2.3

  }

  //
  // Free the buffer
  //

  Status = gtBS->FreePages (
                   BufferAddress,
                   1
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePages - 1 page",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->SetMem() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.4
//
EFI_STATUS
BBTestSetMemInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  UINT8                                *Buffer;
  EFI_PHYSICAL_ADDRESS                 BufferAddress;
  UINT8                                *Dest;

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
  // Allocate buffer
  //
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   EfiBootServicesData,
                   1,
                   &BufferAddress
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePages - 1 page EfiBootServicesData",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  Buffer = (UINT8*)(UINTN)BufferAddress;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.4.2.1  SetMem must succeed with valid parameters.
    //
    Dest = Buffer;
    SetTestMem (Dest, 128, 1);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->SetMem (
            (VOID *)Dest,
            128,
            2
            );
    gtBS->RestoreTPL (OldTpl);
    Status = CheckTestMem (Dest, 128, 2);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid020: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid039: \
                    gMiscBootServicesBBTestFunctionAssertionGuid040),
                   L"BS.SetMem - valid parameters",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // 4.4.2.2  SetMem must succeed when Size is 0.
    //
    Dest = Buffer;
    SetTestMem (Dest, 128, 1);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->SetMem (
            (VOID *)Dest,
            0,
            2
            );
    gtBS->RestoreTPL (OldTpl);
    Status = CheckTestMem (Dest, 128, 1);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid021: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid041: \
                    gMiscBootServicesBBTestFunctionAssertionGuid042),
                   L"BS.SetMem - Size is 0",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // 4.4.2.3  SetMem must succeed when Buffer is not 4-byte aligned.
    //
    Dest = Buffer + 1;
    SetTestMem (Dest, 129, 1);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtBS->SetMem (
            (VOID *)Dest,
            129,
            2
            );
    gtBS->RestoreTPL (OldTpl);
    Status = CheckTestMem (Dest, 129, 2);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid022: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid043: \
                    gMiscBootServicesBBTestFunctionAssertionGuid044),
                   L"BS.SetMem - Buffer is not 4-byte aligned",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

  }

  //
  // Free the buffer
  //
  Status = gtBS->FreePages (
                   BufferAddress,
                   1
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePages - 1 page",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->GetNextMonotonicCount() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.5
//
EFI_STATUS
BBTestGetNextMonotonicCountInterfaceTest (
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
  UINT64                               Count;
  UINT64                               Count2;
  UINT8                                Buffer[1024];
  RESET_DATA                           *ResetData;
  UINTN                                Size;

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
  // Get the Recovery Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   (VOID **) &RecoveryLib
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
  ResetData = (RESET_DATA *)&Buffer;
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
      Count = ResetData->Count;
      goto GetNextMonotonicCountStep2;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.5.2.1  GetNextMonotonicCount must succeed with valid parameters.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetNextMonotonicCount (
                     &Count
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid023: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid045: \
                    gMiscBootServicesBBTestFunctionAssertionGuid046),
                   L"BS.GetNextMonotonicCount - get current count",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetNextMonotonicCount (
                     &Count2
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid024: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid047: \
                    gMiscBootServicesBBTestFunctionAssertionGuid048),
                   L"BS.GetNextMonotonicCount - get count again",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (Count2 == Count + 1) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid025: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid049: \
                    gMiscBootServicesBBTestFunctionAssertionGuid050),
                   L"BS.GetNextMonotonicCount - Count + 1 == Count2",
                   L"%a:%d:Count - %lx, Count2 - %lx, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Count,
                   Count2,
                   TplArray[Index]
                   );

    //
    // 4.5.2.2  GetNextMonotonicCount after reset.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetNextMonotonicCount (
                     &Count
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid026: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid051: \
                    gMiscBootServicesBBTestFunctionAssertionGuid052),
                   L"BS.GetNextMonotonicCount - get current count",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    //  save the high 32 bit and reset system
    //
    ResetData->Step     = 1;
    ResetData->TplIndex = Index;
    ResetData->Count    = Count;
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

    gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);

GetNextMonotonicCountStep2:

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetNextMonotonicCount (
                     &Count2
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid027: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid053: \
                    gMiscBootServicesBBTestFunctionAssertionGuid054),
                   L"BS.GetNextMonotonicCount - get count after reset",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    if (SctRShiftU64 (Count2, 32) == SctRShiftU64 (Count, 32) + 1) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid029: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid057: \
                    gMiscBootServicesBBTestFunctionAssertionGuid058),
                   L"BS.GetNextMonotonicCount - high 32 bit increase by 1",
                   L"%a:%d:Count - %lx, Count2 - %lx, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Count,
                   Count2,
                   TplArray[Index]
                   );

  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->InstallConfigurationTable() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.6
//
EFI_STATUS
BBTestInstallConfigurationTableInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  UINTN                                Index2;
  EFI_TPL                              OldTpl;
  UINTN                                TestTable;
  UINTN                                TestTable2;
  UINT32                               Crc32;
  UINT32                               OldCrc32;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.6.2.1  InstallConfigurationTable must succeed with valid parameters
    //          to install a configuration table.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->InstallConfigurationTable (
                     &gMiscBootServicesTestTableGuid,
                     (VOID*)&TestTable
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid030: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid059: \
                    gMiscBootServicesBBTestFunctionAssertionGuid060),
                   L"BS.InstallConfiguratoinTable - install Test Table",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
    for (Index2 = 0; Index2 < gtST->NumberOfTableEntries; Index2++) {
      if (SctCompareGuid (&gMiscBootServicesTestTableGuid,
                       &(gtST->ConfigurationTable[Index2].VendorGuid)) == 0) {
        if (gtST->ConfigurationTable[Index2].VendorTable == (VOID*)&TestTable) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
          break;
        }
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid031: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid061: \
                    gMiscBootServicesBBTestFunctionAssertionGuid062),
                   L"BS.InstallConfiguratoinTable - Test Table Exist",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    OldCrc32 = gtST->Hdr.CRC32;
    gtST->Hdr.CRC32 = 0;
    Status = gtBS->CalculateCrc32 (
                     (UINT8 *)gtST,
                     gtST->Hdr.HeaderSize,
                     &Crc32
                     );
    gtST->Hdr.CRC32 = OldCrc32;
    if (OldCrc32 == Crc32) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid032: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid063: \
                    gMiscBootServicesBBTestFunctionAssertionGuid064),
                   L"BS.InstallConfiguratoinTable - System Table CRC32 Value",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    Status = CheckMemoryType (
               (EFI_PHYSICAL_ADDRESS)(UINTN)(gtST->ConfigurationTable),
               gtST->NumberOfTableEntries * sizeof(EFI_CONFIGURATION_TABLE),
               EfiRuntimeServicesData
               );
    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid033: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid065: \
                    gMiscBootServicesBBTestFunctionAssertionGuid066),
                   L"BS.InstallConfiguratoinTable - EfiRuntimeServicesData",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // 4.6.2.2  InstallConfigurationTable must succeed with valid parameters
    //          to change a configuration table.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->InstallConfigurationTable (
                     &gMiscBootServicesTestTableGuid,
                     (VOID*)&TestTable2
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid034: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid067: \
                    gMiscBootServicesBBTestFunctionAssertionGuid068),
                   L"BS.InstallConfiguratoinTable - change Test Table",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
    for (Index2 = 0; Index2 < gtST->NumberOfTableEntries; Index2++) {
      if (SctCompareGuid (&gMiscBootServicesTestTableGuid,
                       &(gtST->ConfigurationTable[Index2].VendorGuid)) == 0) {
        if (gtST->ConfigurationTable[Index2].VendorTable == (VOID*)&TestTable2) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
          break;
        }
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid035: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid069: \
                    gMiscBootServicesBBTestFunctionAssertionGuid070),
                   L"BS.InstallConfiguratoinTable - Changed Test Table Exist",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    OldCrc32 = gtST->Hdr.CRC32;
    gtST->Hdr.CRC32 = 0;
    Status = gtBS->CalculateCrc32 (
                     (UINT8 *)gtST,
                     gtST->Hdr.HeaderSize,
                     &Crc32
                     );
    gtST->Hdr.CRC32 = OldCrc32;
    if (OldCrc32 == Crc32) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid036: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid071: \
                    gMiscBootServicesBBTestFunctionAssertionGuid072),
                   L"BS.InstallConfiguratoinTable - System Table CRC32 Value",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    Status = CheckMemoryType (
               (EFI_PHYSICAL_ADDRESS)(UINTN)(gtST->ConfigurationTable),
               gtST->NumberOfTableEntries * sizeof(EFI_CONFIGURATION_TABLE),
               EfiRuntimeServicesData
               );
    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid037: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid073: \
                    gMiscBootServicesBBTestFunctionAssertionGuid074),
                   L"BS.InstallConfiguratoinTable - EfiRuntimeServicesData",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // 4.6.2.3  InstallConfigurationTable must succeed with valid parameters
    //          to remove a configuration table.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->InstallConfigurationTable (
                     &gMiscBootServicesTestTableGuid,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid038: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid075: \
                    gMiscBootServicesBBTestFunctionAssertionGuid076),
                   L"BS.InstallConfiguratoinTable - remove Test Table",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (Index2 = 0; Index2 < gtST->NumberOfTableEntries; Index2++) {
      if (SctCompareGuid (&gMiscBootServicesTestTableGuid,
                       &(gtST->ConfigurationTable[Index2].VendorGuid)) == 0) {
        if (gtST->ConfigurationTable[Index2].VendorTable == (VOID*)&TestTable2) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid039: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid077: \
                    gMiscBootServicesBBTestFunctionAssertionGuid078),
                   L"BS.InstallConfiguratoinTable - Test Table Removed",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    OldCrc32 = gtST->Hdr.CRC32;
    gtST->Hdr.CRC32 = 0;
    Status = gtBS->CalculateCrc32 (
                     (UINT8 *)gtST,
                     gtST->Hdr.HeaderSize,
                     &Crc32
                     );
    gtST->Hdr.CRC32 = OldCrc32;
    if (OldCrc32 == Crc32) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid040: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid079: \
                    gMiscBootServicesBBTestFunctionAssertionGuid080),
                   L"BS.InstallConfiguratoinTable - System Table CRC32 Value",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    Status = CheckMemoryType (
               (EFI_PHYSICAL_ADDRESS)(UINTN)(gtST->ConfigurationTable),
               gtST->NumberOfTableEntries * sizeof(EFI_CONFIGURATION_TABLE),
               EfiRuntimeServicesData
               );
    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid041: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid081: \
                    gMiscBootServicesBBTestFunctionAssertionGuid082),
                   L"BS.InstallConfiguratoinTable - EfiRuntimeServicesData",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->CalculateCrc32() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.7
//
EFI_STATUS
BBTestCalculateCrc32InterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  UINT32                               Crc32;
  UINT32                               StdCrc32;
  UINT32                               OldCrc32;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.7.2.1  CalculateCrc32 must succeed with valid parameters to
    //          calculate the CRC32 value of system table.
    //
    OldCrc32 = gtST->Hdr.CRC32;
    gtST->Hdr.CRC32 = 0;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CalculateCrc32 (
                     (UINT8 *)gtST,
                     gtST->Hdr.HeaderSize,
                     &Crc32
                     );
    gtBS->RestoreTPL (OldTpl);
    SctCalculateCrc32 (
                     (UINT8 *)gtST,
                     gtST->Hdr.HeaderSize,
                     &StdCrc32
                     );
    gtST->Hdr.CRC32 = OldCrc32;
    if (StdCrc32 == Crc32) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscBootServicesInterfaceTestAssertionGuid042: \
                   (Index == 1? \
                    gMiscBootServicesBBTestFunctionAssertionGuid083: \
                    gMiscBootServicesBBTestFunctionAssertionGuid084),
                   L"BS.CalculateCrc32 - CRC32 Value should be correct",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  }

  return EFI_SUCCESS;
}

