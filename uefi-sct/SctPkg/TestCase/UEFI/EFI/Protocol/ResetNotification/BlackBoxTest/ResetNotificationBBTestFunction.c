/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    ResetNotificationFunction.c

Abstract:

    for EFI Driver Reset Notification Protocol's Function Test

--*/

#include "ResetNotificationBBTestMain.h"

extern UINT8 EnterEvent;

EFI_STATUS
EFIAPI
BBTestRegisterResetNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL    *RecoveryLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_RESET_NOTIFICATION_PROTOCOL       *ResetNotification;
  UINTN                                 RecoveryDataSize;
  UINT8                                 *RecoveryData;
  UINTN                                 DataSize;
  UINT32                                Attributes1;
  UINT8                                 Data[MAX_BUFFER_SIZE];
  UINTN                                 Index;

  ResetNotification = (EFI_RESET_NOTIFICATION_PROTOCOL*)ClientInterface;

  //
  // Get test support library interfaces
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &RecoveryLib,
             &LoggingLib
             );
  
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"TestSupportLibrary - StandardLib, RecoveryLib, LoggingLib failure",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Allocate memory for recovery data
  //
  Status = gtBS->AllocatePool (
                   EfiLoaderData,
                   1024,
                   (VOID **)&RecoveryData
                   );
  if (EFI_ERROR(Status)) {
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"BBTestRegisterResetNotifyFunctionTest",
                    L"Cannot allocate memory for recovery data"
                    );
    }

    return Status;
  }

  //
  // Read reset record
  //
  RecoveryDataSize = 1024;
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &RecoveryDataSize,
                          RecoveryData
                          );
  if (!EFI_ERROR(Status) && (RecoveryDataSize > 0)) {
    switch (RecoveryData[0]) {
    case 1:
      goto step2;
    default:
      goto step3;
    }
  }
  
  Status = ResetNotification->RegisterResetNotify (ResetNotification, TestOnReset);
  if (EFI_SUCCESS == Status)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gResetNotificationBBTestFunctionAssertionGuid001,
                 L"EFI_RESET_NOTIFICATION_PROTOCOL.RegisterResetNotify - call RegisterResetNotify() with correct parameters, the status should be EFI_SUCCESS",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  Status = ResetNotification->RegisterResetNotify (ResetNotification, TestOnReset);
  if (EFI_ALREADY_STARTED == Status)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gResetNotificationBBTestFunctionAssertionGuid002,
                 L"EFI_RESET_NOTIFICATION_PROTOCOL.RegisterResetNotify - call RegisterResetNotify() with registered ResetFunction, the status should be EFI_ALREADY_STARTED",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Write reset record
  //
  RecoveryData[0] = 1;
  RecoveryLib->WriteResetRecord (RecoveryLib, 1, RecoveryData);

  //
  // Print out some information to avoid the user thought it is an error
  //
  SctPrint (L"System will cold reset after 1 second...");
  gtBS->Stall (1000000);

  gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);  


step2:
  RecoveryLib->WriteResetRecord (RecoveryLib, 0, NULL);

  DataSize = MAX_BUFFER_SIZE;
  Status = gtRT->GetVariable (
                     VariableName,                // VariableName
                     &gTestVendorGuid,           // VendorGuid
                     &Attributes1,                 // Attributes
                     &DataSize,                   // DataSize
                     Data                         // Data
                     );

  //
  // Check results
  //
  if ((Status == EFI_SUCCESS) && (Attributes == Attributes1) && (DataSize == 10)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;

    //
    // Delete the variable (restore environment)
    //
    Status = gtRT->SetVariable (
                     VariableName,                // VariableName
                     &gTestVendorGuid,           // VendorGuid
                     Attributes,                  // Attributes
                     0,                           // DataSize
                     Data                         // Data
                     );    


    for (Index = 0; Index < 10; Index++) {
      if (Data[Index] != (UINT8)Index) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gResetNotificationBBTestFunctionAssertionGuid003,
                 L"EFI_RESET_NOTIFICATION_PROTOCOL.RegisterResetNotify - The registered ResetFunction is called before ResetSystem",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  
step3:

	 gtBS->FreePool (RecoveryData);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterResetNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL    *RecoveryLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_RESET_NOTIFICATION_PROTOCOL       *ResetNotification;
  UINTN                                 RecoveryDataSize;
  UINT8                                 *RecoveryData;
  UINTN                                 DataSize;
  UINT32                                Attributes1;
  UINT8                                 Data[MAX_BUFFER_SIZE];

  ResetNotification = (EFI_RESET_NOTIFICATION_PROTOCOL*)ClientInterface;

  //
  // Get test support library interfaces
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &RecoveryLib,
             &LoggingLib
             );
  
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"TestSupportLibrary - StandardLib, RecoveryLib, LoggingLib failure",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Allocate memory for recovery data
  //
  Status = gtBS->AllocatePool (
                   EfiLoaderData,
                   1024,
                   (VOID **)&RecoveryData
                   );
  if (EFI_ERROR(Status)) {
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"BBTestRegisterResetNotifyFunctionTest",
                    L"Cannot allocate memory for recovery data"
                    );
    }

    return Status;
  }

  //
  // Read reset record
  //
  RecoveryDataSize = 1024;
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &RecoveryDataSize,
                          RecoveryData
                          );
  if (!EFI_ERROR(Status) && (RecoveryDataSize > 0)) {
    switch (RecoveryData[0]) {
    case 1:
      goto step2;
    default:
      goto step3;
    }
  }

  Status = ResetNotification->UnregisterResetNotify (ResetNotification, TestOnReset);
  if (EFI_INVALID_PARAMETER == Status)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gResetNotificationBBTestFunctionAssertionGuid004,
                 L"EFI_RESET_NOTIFICATION_PROTOCOL.UnregisterResetNotify - call UnregisterResetNotify() with unregistered ResetFunction, the status should be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = ResetNotification->RegisterResetNotify (ResetNotification, TestOnReset);
  if (EFI_SUCCESS != Status) {
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_RESET_NOTIFICATION_PROTOCOL.RegisterResetNotify - call RegisterResetNotify() with unregistered ResetFunction fail",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
    return Status;
  }

  Status = ResetNotification->UnregisterResetNotify (ResetNotification, TestOnReset);
  if (EFI_SUCCESS == Status)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gResetNotificationBBTestFunctionAssertionGuid005,
                 L"EFI_RESET_NOTIFICATION_PROTOCOL.UnregisterResetNotify - call UnregisterResetNotify() with registered ResetFunction, the status should be EFI_SUCCESS",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Write reset record
  //
  RecoveryData[0] = 1;
  RecoveryLib->WriteResetRecord (RecoveryLib, 1, RecoveryData);

  //
  // Print out some information to avoid the user thought it is an error
  //
  SctPrint (L"System will cold reset after 1 second...");
  gtBS->Stall (1000000);

  gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);  


step2:
  RecoveryLib->WriteResetRecord (RecoveryLib, 0, NULL);

  DataSize = MAX_BUFFER_SIZE;
  Status = gtRT->GetVariable (
                     VariableName,                // VariableName
                     &gTestVendorGuid,            // VendorGuid
                     &Attributes1,                // Attributes
                     &DataSize,                   // DataSize
                     Data                         // Data
                     );

  if (Status == EFI_NOT_FOUND)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else 
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gResetNotificationBBTestFunctionAssertionGuid006,
                 L"EFI_RESET_NOTIFICATION_PROTOCOL.UnregisterResetNotify - The unregistered ResetFunction should not be called before ResetSystem",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  
step3:

	 gtBS->FreePool (RecoveryData);

  return EFI_SUCCESS;
}

