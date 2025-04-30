/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2023, Arm Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  TCGMemoryOverwriteRequestBBTestFunction.c

Abstract:

  Function Test Cases for the TCG MOR and MORLOCK EFI variables that are defined
  in TCG Platform Reset Attack Mitigation v1.10 Section 4 (UEFI Interface)

--*/

#include "SctLib.h"
#include "TCGMemoryOverwriteRequestBBTestMain.h"

#define RECOVER_BUFFER_SIZE         2048

#define TCG_MOR_VARIABLE_ATTRIBUTES  (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)

#define CONTROL_PLATFORM_RESET_TEST 1

#define CONTROL_SET_VARIABLE_TEST   2

#define LOCK_SET_VARIABLE_TEST      3

#define LOCK_UNLOCKED_STATE_TEST    4

#define LOCK_NO_KEY_STATE_TEST      5

#define LOCK_WITH_KEY_STATE_TEST    6


/**
 *  Entry point for TCG Platform Reset Attack Mitigation MemoryOverwrite EFI Variables Function Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Test cases ran Successfully, may still contain errors in assertions.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
BBTestTCGMemoryOverwriteRequestFunctionTest (
  IN EFI_BB_TEST_PROTOCOL              *This,
  IN VOID                              *ClientInterface,
  IN EFI_TEST_LEVEL                    TestLevel,
  IN EFI_HANDLE                        SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_STATUS                           Status;
  RESET_DATA                           *ResetData;
  UINT8                                Buffer[RECOVER_BUFFER_SIZE];
  UINTN                                Size;

  ResetData = (RESET_DATA *)Buffer;

  BOOLEAN                              CheckpointStepMatched = FALSE;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->OpenProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  (VOID **) &StandardLib,
                  gImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                  );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Recovery Library Interface
  //
  Status = gtBS->OpenProtocol (
                  SupportHandle,
                  &gEfiTestRecoveryLibraryGuid,
                  (VOID **) &RecoveryLib,
                  gImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.OpenProtocol - Handle recovery library",
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

  //
  // if ResetRecord has not been written to yet, or EFI_ERROR from reading reset record, start the test from beginning
  //
  if (EFI_ERROR(Status) || Size < sizeof(RESET_DATA)) {
    ResetData->Step = 0;
    Status = TCGMemoryOverwriteRequestPlatformResetCheck (StandardLib, RecoveryLib, ResetData);
    //
    // In the event that the MOR/MORLOCK variables do not exist in accordance to spec,
    // or the WriteResetRecord returns EFI_ERROR, test ends prematurely
    //
    if(EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Once TCGMemoryOverwriteRequestPlatformResetCheck has been invoked and ResetRecord written
  // check ResetData->CheckpointStep for next test
  //
  if (ResetData->CheckpointStep == CONTROL_PLATFORM_RESET_TEST) {
    //
    // Test Checkpoint CONTROL_PLATFORM_RESET_TEST
    //
    Status = TCGMemoryOverwriteRequestPlatformResetCheck (StandardLib, RecoveryLib, ResetData);
    if(EFI_ERROR(Status)) {
      return Status;
    }
    CheckpointStepMatched = TRUE;
  }
  if (ResetData->CheckpointStep == CONTROL_SET_VARIABLE_TEST) {
    //
    // Test Checkpoint CONTROL_SET_VARIABLE_TEST
    //
    Status = TCGMemoryOverwriteRequestControlSetVariable (StandardLib, RecoveryLib, ResetData);
    if(EFI_ERROR(Status)) {
      return Status;
    }
    CheckpointStepMatched = TRUE;
  }
  if (ResetData->CheckpointStep == LOCK_SET_VARIABLE_TEST) {
    //
    // Test Checkpoint LOCK_SET_VARIABLE_TEST
    //
    Status = TCGMemoryOverwriteRequestControlLockSetVariable (StandardLib, RecoveryLib, ResetData);
    if(EFI_ERROR(Status)) {
      return Status;
    }
    CheckpointStepMatched = TRUE;
  }
  if (ResetData->CheckpointStep == LOCK_UNLOCKED_STATE_TEST) {
    //
    // Test Checkpoint LOCK_UNLOCKED_STATE_TEST
    //
    Status = TCGMemoryOverwriteRequestControlLockUnlockedState (StandardLib, RecoveryLib, ResetData);
    if(EFI_ERROR(Status)) {
      return Status;
    }
    CheckpointStepMatched = TRUE;
  }
  if (ResetData->CheckpointStep == LOCK_NO_KEY_STATE_TEST) {
    //
    // Test Checkpoint LOCK_NO_KEY_STATE_TEST
    //
    Status = TCGMemoryOverwriteRequestControlLockLockedNoKeyState (StandardLib, RecoveryLib, ResetData);
    if(EFI_ERROR(Status)) {
      return Status;
    }
    CheckpointStepMatched = TRUE;
  }
  if (ResetData->CheckpointStep == LOCK_WITH_KEY_STATE_TEST) {
    //
    // Test Checkpoint LOCK_WITH_KEY_STATE_TEST
    //
    Status = TCGMemoryOverwriteRequestControlLockLockedWithKeyState (StandardLib, RecoveryLib, ResetData);
    if(EFI_ERROR(Status)) {
      return Status;
    }
    CheckpointStepMatched = TRUE;
  }

  if (!CheckpointStepMatched) {
    return EFI_INVALID_PARAMETER; // incase of invalid CheckpointStep, return EFI_INVALID_PARAMETER
  }

  //
  // After all Checkpoints have run successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Check MOR & MORLOCK EFI variables are correctly created by platform
 *  Initially setting MOR bit 0 is then cleared upon platform reset
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param RecoveryLib    A pointer to EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
TCGMemoryOverwriteRequestPlatformResetCheck (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   Result;
  UINTN                                DataSize;
  UINT8                                MemoryOverwriteRequestControlData;
  UINT8                                MemoryOverwriteRequestControlLockData;
  UINT32                               Attributes;

  //
  // Check Step to see which part of test remains to be executed
  //
  switch (ResetData->Step) {
    case 0:
      goto INITIAL_RESET;
    case 1:
      goto MOR_VARIABLE_CHECK;
    case 2:
      goto MOR_BIT_CLEAR_ON_RESET;
    default:
      return EFI_INVALID_PARAMETER;
  }

INITIAL_RESET:
  //
  // Perform initial plaform reset
  //
  ResetData->Step = 1;
  ResetData->CheckpointStep = CONTROL_PLATFORM_RESET_TEST;

  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  SctPrint (L"System will cold reset after 1 second and test will be resumed after reboot.");
  Status = gtBS->Stall(1000000);
  if (EFI_ERROR(Status)) {
      // Handle stall error
      SctPrint(L"Error: Failed to stall the system.\n");
      return Status;
  }
  gtRT->ResetSystem (
                  EfiResetCold,
                  EFI_SUCCESS,
                  0,
                  NULL
                  );
  SctPrint(L"Error: Failed to perform a cold reset.\n");
  return EFI_DEVICE_ERROR;

MOR_VARIABLE_CHECK:
  //
  // Post system reset, Check if the MOR variable is correctly created by platform
  //

  // Write reset record before the second reset (MOR_BIT_CLEAR_ON_RESET)
  ResetData->Step = 2;
  ResetData->CheckpointStep = CONTROL_PLATFORM_RESET_TEST;

  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  //
  // GetVariable and check if the DataSize and Attributes are as expected
  //
  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (EFI_ERROR (Status) || (DataSize != 1) || (Attributes != TCG_MOR_VARIABLE_ATTRIBUTES)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid001,
                  L"MemoryOverwriteRequestControl - Validate that the MOR Variable is created by the platform in accordance with TCG Spec",
                  L"%a:%d:Status - %r, DataSize - %d, Attributes - %x",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status,
                  (UINTN)DataSize,
                  (UINTN)Attributes
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Set MemoryOverwriteRequestControlData bit 0 and verify the platform clears bit 0 upon system reset
  // MOR bit 0 indicates to platform firmware that system memory must be wiped during platform initialization
  //
  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlData |= MOR_BIT_HIGH << MOR_CLEAR_MEMORY_BIT_OFFSET;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  Attributes,                           // Attributes
                  DataSize,                             // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  }else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid002,
                  L"MemoryOverwriteRequestControl - SetVariable() with MOR bit 0 set high returns EFI_SUCCESS",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Cold reset system again for step 2
  SctPrint (L"System will cold reset after 1 second and test will be resumed after reboot.");
  Status = gtBS->Stall(1000000);
  if (EFI_ERROR(Status)) {
      // Handle stall error
      SctPrint(L"Error: Failed to stall the system.\n");
      return Status;
  }
  gtRT->ResetSystem (
                  EfiResetCold,
                  EFI_SUCCESS,
                  0,
                  NULL
                  );
  SctPrint(L"Error: Failed to perform a cold reset.\n");
  return EFI_DEVICE_ERROR;

MOR_BIT_CLEAR_ON_RESET:
  //
  // Clear Step count and increment checkpoint for next test
  //

  ResetData->Step = 0;
  ResetData->CheckpointStep = CONTROL_SET_VARIABLE_TEST;

  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  //
  // Check if the platform has cleared the set MOR bit 0 on reset
  //
  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (EFI_ERROR (Status) || (MOR_CLEAR_MEMORY_VALUE (MemoryOverwriteRequestControlData) != MOR_BIT_LOW)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid003,
                  L"MemoryOverwriteRequestControl - Validate that MOR bit 0 is cleared after a cold reset when the bit 0 is initially set",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Verify MemoryOverwriteRequestControlLock is created as defined in the TCG Platform Reset Attack Mitigation spec
  //
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED) ||
      (DataSize != 1) || (Attributes != TCG_MOR_VARIABLE_ATTRIBUTES)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid004,
                  L"MemoryOverwriteRequestControlLock - Validate that MORLOCK is created by the platform in accordance with the TCG Spec",
                  L"%a:%d:Status - %r, DataSize - %d, Attributes - %x",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status,
                  (UINTN)DataSize,
                  (UINTN)Attributes
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}


/**
 *  MemoryOverwriteRequestControl EFI variable SetVariable() requests with a single invalid parameter
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param RecoveryLib    A pointer to EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
TCGMemoryOverwriteRequestControlSetVariable (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   Result;
  UINTN                                DataSize;
  UINT8                                MemoryOverwriteRequestControlData;
  UINT8                                MemoryOverwriteRequestControlDataCached;
  UINT32                               Attributes;

  //
  // Write reset record to initiate checkpoint LOCK_SET_VARIABLE_TEST after these assertions are complete
  //
  ResetData->Step = 0;
  ResetData->CheckpointStep = LOCK_SET_VARIABLE_TEST;

  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  //
  // MOR SetVariable() with invalid Attributes = NV + BS returns EFI_INVALID_PARAMETER and value is unchanged
  // SetVariable() with MOR bit 0 set and invalid Attributes = NV + BS
  //
  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // caching variable for later comparison with the second GetVariable() value
  MemoryOverwriteRequestControlDataCached = MemoryOverwriteRequestControlData;

  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
  MemoryOverwriteRequestControlData |= MOR_BIT_HIGH << MOR_CLEAR_MEMORY_BIT_OFFSET;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  Attributes,                           // Attributes
                  DataSize,                             // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid005,
                  L"MemoryOverwriteRequestControl - SetVariable() returns EFI_INVALID_PARAMETER with invalid Attributes = (NV+BS)",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  // verifying that the MOR variable has not been modified with SetVariable()
  if (MemoryOverwriteRequestControlDataCached == MemoryOverwriteRequestControlData) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid006,
                  L"MemoryOverwriteRequestControl - SetVariable() with invalid Attributes = (NV+BS), variable value remains unchanged",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  return EFI_SUCCESS;
}


/**
 *  MemoryOverwriteRequestControlLock SetVariable() with different variations
 *  of only a single invalid parameter being passed, with the rest parameters being valid
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param RecoveryLib    A pointer to EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ResetData      A pointer to the ResetData buffer which is used throughout the
 *                        test
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
TCGMemoryOverwriteRequestControlLockSetVariable (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   Result;
  UINTN                                DataSize;
  UINT8                                MemoryOverwriteRequestControlLockData;
  UINT32                               Attributes;

  //
  // Check Step to see which part of test remains to be executed
  //
  switch (ResetData->Step) {
    case 0:
      goto INITIAL_RESET;
    case 1:
      goto MORLOCK_SET_VARIABLE;
    default:
      return EFI_INVALID_PARAMETER;
  }

INITIAL_RESET:
  //
  // Reset MORLOCK variable by performing a cold reset
  //

  ResetData->Step = 1;
  ResetData->CheckpointStep = LOCK_SET_VARIABLE_TEST;

  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  SctPrint (L"System will cold reset after 1 second and test will be resumed after reboot.");
  Status = gtBS->Stall(1000000);
  if (EFI_ERROR(Status)) {
      // Handle stall error
      SctPrint(L"Error: Failed to stall the system.\n");
      return Status;
  }
  gtRT->ResetSystem (
                  EfiResetCold,
                  EFI_SUCCESS,
                  0,
                  NULL
                  );
  SctPrint(L"Error: Failed to perform a cold reset.\n");
  return EFI_DEVICE_ERROR;

MORLOCK_SET_VARIABLE:
  //
  // reset step count and Update Checkpoint to LOCK_UNLOCKED_STATE_TEST
  //

  ResetData->Step = 0;
  ResetData->CheckpointStep = LOCK_UNLOCKED_STATE_TEST;

  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  // MORLOCK SetVariable() to locked-without-key with valid GUID, variable name, Data, and DataSize
  // except for invalid Attributes value = 0
  // verify SetVariable() returns EFI_WRITE_PROTECTED and GetVariable() returns a Data Value = 0
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = 0;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_LOCKED_WITHOUT_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_WRITE_PROTECTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid007,
                  L"MemoryOverwriteRequestControlLock - SetVariable() returns EFI_WRITE_PROTECTED with invalid Attributes = 0",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // change Attributes to valid before GetVariable() to check that MORLOCK value is still 0x00 or unlocked
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  // Check that MORLOCK remains unlocked after previous operation
  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid008,
                  L"MemoryOverwriteRequestControlLock - SetVariable() with invalid Attributes = 0, lock value remains unlocked",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // MORLOCK SetVariable() to locked-without-key with valid GUID, variable name, Data, and Attributes
  // except for invalid DataSize = 0
  // verify SetVariable() returns EFI_WRITE_PROTECTED and GetVariable() returns a Data Value = 0
  DataSize = 0;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_LOCKED_WITHOUT_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_WRITE_PROTECTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid009,
                  L"MemoryOverwriteRequestControlLock - SetVariable() returns EFI_WRITE_PROTECTED with DataSize = 0",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // change DataSize to a valid value before GetVariable()
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  // Check that MORLOCK remains unlocked after previous operation
  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid010,
                  L"MemoryOverwriteRequestControlLock - SetVariable() with DataSize = 0, lock value remains unlocked",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // MORLOCK SetVariable() to locked-without-key with valid GUID,
  // variable name, DataSize, and Attributes, except for Data = NULL
  // verify SetVariable() returns EFI_INVALID_PARAMETER and GetVariable() returns a Data Value = 0
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  NULL                                         // Data
                  );
  if (Status == EFI_WRITE_PROTECTED || EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid011,
                  L"MemoryOverwriteRequestControlLock - SetVariable() with Data parameter as NULL returns either EFI_WRITE_PROTECTED or EFI_INVALID_PARAMETER",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // Check that MORLOCK remains unlocked after previous operation
  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid012,
                  L"MemoryOverwriteRequestControlLock - SetVariable() with Data as NULL, lock value remains unlocked",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // MORLOCK SetVariable() to lock-without-key with valid GUID, variable name, Data, and DataSize
  // except for invalid Attributes != NV+BS+RT, this test will use invalid Attributes = NV + BS
  // verify SetVariable() returns EFI_INVALID_PARAMETER and GetVariable() returns a Data Value = 0
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_LOCKED_WITHOUT_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid013,
                  L"MemoryOverwriteRequestControlLock - SetVariable() with invalid attributes = (NV+BS) returns EFI_INVALID_PARAMETER",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // change attributes value to valid NV+BS+RT for GetVariable()
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  // Check that MORLOCK remains unlocked after previous operation
  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid014,
                  L"MemoryOverwriteRequestControlLock - SetVariable() with invalid attributes = (NV+BS), lock value remains unlocked",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // MORLOCK SetVariable() to locked-without-key with valid GUID, variable name, Data, and Attributes
  // except for invalid DataSize != 1 && != 8, this test will use invalid DataSize = 5
  // verify SetVariable() returns EFI_INVALID_PARAMETER and GetVariable() returns a Data Value = 0
  DataSize = 5;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_LOCKED_WITHOUT_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid015,
                  L"MemoryOverwriteRequestControlLock - SetVariable() with DataSize = 5 returns EFI_INVALID_PARAMETER",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  // change datasize to valid value for GetVariable
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  // Check that MORLOCK remains unlocked after previous operation
  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid016,
                  L"MemoryOverwriteRequestControlLock - SetVariable() with DataSize = 5, lock value remains unlocked",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  return EFI_SUCCESS;
}


/**
 *  MemoryOverwriteRequestControlLock in unlocked state test
 *  When unlocked, the lock should stay unlocked when passed a valid value of 0x00
 *
 *  When passed an invalid Data value != 0x00 or != 0x01, such as 0x02,
 *  the lock must stay unlocked and return EFI_INVALID_PARAMETER
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param RecoveryLib    A pointer to EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ResetData      A pointer to the ResetData Buffer which is used throughout
 *                        the test
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
TCGMemoryOverwriteRequestControlLockUnlockedState (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   Result;
  UINTN                                DataSize;
  UINT8                                MemoryOverwriteRequestControlLockData;
  UINT32                               Attributes;

  //
  // Check Step to see which part of test remains to be executed
  //
  switch (ResetData->Step) {
    case 0:
      goto INITIAL_RESET;
    case 1:
      goto MORLOCK_UNLOCKED_STATE;
    default:
      return EFI_INVALID_PARAMETER;
  }

INITIAL_RESET:
  //
  // Reset MORLOCK variable by performing a cold reset
  //

  ResetData->Step = 1;
  ResetData->CheckpointStep = LOCK_UNLOCKED_STATE_TEST;
  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  SctPrint (L"System will cold reset after 1 second and test will be resumed after reboot.");
  Status = gtBS->Stall(1000000);
  if (EFI_ERROR(Status)) {
      // Handle stall error
      SctPrint(L"Error: Failed to stall the system.\n");
      return Status;
  }
  gtRT->ResetSystem (
                  EfiResetCold,
                  EFI_SUCCESS,
                  0,
                  NULL
                  );
  SctPrint(L"Error: Failed to perform a cold reset.\n");
  return EFI_DEVICE_ERROR;

MORLOCK_UNLOCKED_STATE:
  //
  // Testing MORLOCK scenarios when the Variable is in the unlocked state
  //

  ResetData->Step = 0;
  ResetData->CheckpointStep = LOCK_NO_KEY_STATE_TEST;
  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  //
  // Setting MORLOCK to unlocked when already in unlocked state should return EFI_SUCCESS
  // and the MORLOCK value should still be = 0x00 or unlocked
  //
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_UNLOCKED;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid017,
                  L"MemoryOverwriteRequestControlLock - Setting to unlocked when already unlocked should return EFI_SUCCESS",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid018,
                  L"MemoryOverwriteRequestControlLock - Lock value remains unlocked",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Setting MORLOCK with an invalid Data parameter != 0x01 should return EFI_INVALID_PARAMETER
  // and the MORLOCK value should still be = 0x00
  //
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = 0x02;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid019,
                  L"MemoryOverwriteRequestControlLock - Invalid Data = 0x02 returns EFI_INVALID_PARAMETER",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid020,
                  L"MemoryOverwriteRequestControlLock - Lock value remains unlocked",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  return EFI_SUCCESS;
}


/**
 *  MemoryOverwriteRequestControlLock in locked-without-key state test
 *  When unlocked, a valid SetVariable() with Data value 0x01 must return EFI_SUCCESS
 *  and the lock value must be 0x01, value cannot change till the system is cold reset
 *
 *  When locked-without-key, SetVariable() with Data = 0x01, 0x00, or 0x11111111 (key)
 *  must return EFI_ACCESS_DENIED and value must still equal 0x01
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param RecoveryLib    A pointer to EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ResetData      A pointer to the ResetData Buffer which is used throughout
 *                        the test
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
TCGMemoryOverwriteRequestControlLockLockedNoKeyState (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   Result;
  UINTN                                DataSize;
  UINTN                                MemoryOverwriteControlLockKeyValue;
  UINT8                                MemoryOverwriteRequestControlLockData;
  UINT8                                MemoryOverwriteRequestControlData;
  UINT8                                MemoryOverwriteRequestControlDataCached;
  UINT32                               Attributes;

  //
  // Check Step to see which part of test remains to be executed
  //
  switch (ResetData->Step) {
    case 0:
      goto INITIAL_RESET;
    case 1:
      goto MORLOCK_LOCKED_STATE;
    default:
      return EFI_INVALID_PARAMETER;
  }

INITIAL_RESET:
  //
  // Reset MORLOCK variable by performing a cold reset
  //
  ResetData->Step = 1;
  ResetData->CheckpointStep = LOCK_NO_KEY_STATE_TEST;

  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  SctPrint (L"System will cold reset after 1 second and test will be resumed after reboot.");
  Status = gtBS->Stall(1000000);
  if (EFI_ERROR(Status)) {
      // Handle stall error
      SctPrint(L"Error: Failed to stall the system.\n");
      return Status;
  }
  gtRT->ResetSystem (
                  EfiResetCold,
                  EFI_SUCCESS,
                  0,
                  NULL
                  );
  SctPrint(L"Error: Failed to perform a cold reset.\n");
  return EFI_DEVICE_ERROR;

MORLOCK_LOCKED_STATE:
  //change checkpoint to next function
  ResetData->Step = 0;
  ResetData->CheckpointStep = LOCK_WITH_KEY_STATE_TEST;

  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  //
  // After Cold Reset, MORLOCK SetVariable() with value 0x01 must return EFI_SUCCESS
  // and MORLOCK GetVariable() value must now be MOR_LOCK_DATA_LOCKED_WITHOUT_KEY
  //
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_LOCKED_WITHOUT_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid021,
                  L"MemoryOverwriteRequestControlLock - Setting to locked-without-key when unlocked returns EFI_SUCCESS",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITHOUT_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid022,
                  L"MemoryOverwriteRequestControlLock - Lock state is now locked-without-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Once locked-without-key, MORLOCK SetVariable() with value 0x00 must return EFI_ACCESS_DENIED
  // and MORLOCK GetVariable() value must still be 0x01
  //
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_UNLOCKED;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid023,
                  L"MemoryOverwriteRequestControlLock - Setting to unlocked when locked-without-key returns EFI_ACCESS_DENIED",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITHOUT_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid024,
                  L"MemoryOverwriteRequestControlLock - Lock state is still locked-without-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Once locked-without-key, MORLOCK SetVariable() with value 0x01 must return EFI_ACCESS_DENIED
  // and MORLOCK GetVariable() value must still be 0x01
  //
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_LOCKED_WITHOUT_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid025,
                  L"MemoryOverwriteRequestControlLock - Setting to locked-without-key when already locked-without-key returns EFI_ACCESS_DENIED",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITHOUT_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid026,
                  L"MemoryOverwriteRequestControlLock - Lock state is still locked-without-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Once locked-without-key, MORLOCK SetVariable() with 8 byte key = 0x11111111 must return EFI_ACCESS_DENIED
  // and MORLOCK GetVariable() value must still be 0x01
  //
  DataSize = MOR_LOCK_WITH_KEY_SIZE;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteControlLockKeyValue = MOR_LOCK_TEST_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteControlLockKeyValue          // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid027,
                  L"MemoryOverwriteRequestControlLock - Setting to locked-with-key when locked-without-key returns EFI_ACCESS_DENIED",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITHOUT_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid028,
                  L"MemoryOverwriteRequestControlLock - Lock state is still locked-without-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Once locked-without-key, MOR SetVariable() call to set MOR bit 0 must return EFI_ACCESS_DENIED
  // and MOR value must not change
  //
  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  // getting current MOR bit 0 value that will be used to check that the variable is unchanged
  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // caching MOR and then setting bit 0
  MemoryOverwriteRequestControlDataCached = MemoryOverwriteRequestControlData;
  MemoryOverwriteRequestControlData |= MOR_BIT_HIGH << MOR_CLEAR_MEMORY_BIT_OFFSET;

  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;


  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  Attributes,                           // Attributes
                  DataSize,                             // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid029,
                  L"MemoryOverwriteRequestControl - SetVariable() returns EFI_ACCESS_DENIED when MORLOCK is locked-without-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );

  // verifying that the variable has not been modified with SetVariable(), proving that MORLOCK acts as a lock
  if (MemoryOverwriteRequestControlDataCached == MemoryOverwriteRequestControlData) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid030,
                  L"MemoryOverwriteRequestControl - When locked-without-key, MOR bit 0 remains unchanged after an attempt to set it",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Once locked-without-key, MOR cannot be deleted
  // SetVariable() call to set MOR with DataSize = 0 must return EFI_ACCESS_DENIED
  // MemoryOverwriteControlData is a don't care in this case
  DataSize = 0;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  Attributes,                           // Attributes
                  DataSize,                             // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (Status == EFI_ACCESS_DENIED || EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid031,
                  L"MemoryOverwriteRequestControl - When MORLOCK is locked-without-key, an attempt to delete the MOR variable must return either EFI_ACCESS_DENIED or EFI_INVALID_PARAMETER",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  return EFI_SUCCESS;
}


/**
 *  MemoryOverwriteRequestControlLock in locked-with-key state test
 *  When unlocked, a valid SetVariable() with an 8 byte key must return EFI_SUCCESS
 *  and the lock value must be 0x02 (MOR_LOCK_DATA_LOCKED_WITH_KEY), in order to
 *  unlock, the same 8 byte key must be passed.
 *
 *  When locked with an 8 byte key, SetVariable() with the same 8 byte key
 *  must return EFI_SUCCESS and the Lock value must be 0x00 or MOR_LOCK_DATA_UNLOCKED.
 *
 *  When locked with an 8 byte Key, SetVariable() with DataSize != 8 and
 *  Data = 0x01 (MOR_LOCK_DATA_LOCKED_WITHOUT_KEY) or 0x00 (MOR_LOCK_DATA_UNLOCKED)
 *  must return EFI_ACCESS_DENIED
 *  and value must still equal to 0x02 (MOR_LOCK_DATA_LOCKED_WITH_KEY).
 *
 *  When locked with an 8 byte Key, SetVariable() with 8 byte key != key used to set
 *  the lock, in this case 0x11111111 (MOR_LOCK_TEST_KEY), must return EFI_ACCESS_DENIED
 *  and lock value must be updated to 0x01 (MOR_LOCK_DATA_LOCKED_WITHOUT_KEY)
 *  to prevent dictonary attack.
 *
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param RecoveryLib    A pointer to EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ResetData      A pointer to the ResetData Buffer which is used throughout
 *                        the test
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
TCGMemoryOverwriteRequestControlLockLockedWithKeyState (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   Result;
  UINTN                                DataSize;
  UINT8                                MemoryOverwriteRequestControlLockData;
  UINTN                                MemoryOverwriteControlLockKeyValue;
  UINT8                                MemoryOverwriteRequestControlData;
  UINT8                                MemoryOverwriteRequestControlDataCached;
  UINT32                               Attributes;

  //
  // Check Step to see which part of test remains to be executed
  //
  switch (ResetData->Step) {
    case 0:
      goto INITIAL_RESET;
    case 1:
      goto MORLOCK_LOCKED_KEY_STATE;
    default:
      return EFI_INVALID_PARAMETER;
  }

INITIAL_RESET:
  //
  // Reset MORLOCK variable by performing a cold reset
  //

  ResetData->Step = 1;
  ResetData->CheckpointStep = LOCK_WITH_KEY_STATE_TEST;
  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  sizeof (RESET_DATA),
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"TestRecoveryLib - WriteResetRecord",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    return Status;
  }

  SctPrint (L"System will cold reset after 1 second and test will be resumed after reboot.");
  Status = gtBS->Stall(1000000);
  if (EFI_ERROR(Status)) {
      // Handle stall error
      SctPrint(L"Error: Failed to stall the system.\n");
      return Status;
  }
  gtRT->ResetSystem (
                  EfiResetCold,
                  EFI_SUCCESS,
                  0,
                  NULL
                  );
  SctPrint(L"Error: Failed to perform a cold reset.\n");
  return EFI_DEVICE_ERROR;

MORLOCK_LOCKED_KEY_STATE:
  //
  // MORLOCK Reboot system to clear lock, and invoke SetVariable() with valid 8 byte key
  // In this case = 0x11111111, must return EFI_SUCCESS and GetVariable() value must = 0x02
  //

  DataSize = MOR_LOCK_WITH_KEY_SIZE;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteControlLockKeyValue = MOR_LOCK_TEST_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteControlLockKeyValue          // Data
                  );
  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid032,
                  L"MemoryOverwriteRequestControlLock - Setting to locked-with-key using key value = 0x11111111 when unlocked returns EFI_SUCCESS",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITH_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid033,
                  L"MemoryOverwriteRequestControlLock - Lock state is now locked-with-key with key value = 0x11111111",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Currently locked-with-key, invoke SetVariable() with the same valid 8 byte key used to lock
  // In this case = 0x11111111, must return EFI_SUCCESS and GetVariable() value must = 0x00
  //
  DataSize = MOR_LOCK_WITH_KEY_SIZE;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteControlLockKeyValue = MOR_LOCK_TEST_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteControlLockKeyValue          // Data
                  );
  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid034,
                  L"MemoryOverwriteRequestControlLock - Unlocking the lock using key value = 0x11111111 when locked with the same key returns EFI_SUCCESS",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_UNLOCKED)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid035,
                  L"MemoryOverwriteRequestControlLock - Lock state is now unlocked",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Lock with same 8 byte key again, verify EFI_SUCCESS is returned
  // unlock attempt: invoke SetVariable() with the same valid 8 byte
  // key used to lock = 0x11111111, but with invalid DataSize = 1
  // must return EFI_ACCESS_DENIED and GetVariable() value must remain = 0x02
  //
  DataSize = MOR_LOCK_WITH_KEY_SIZE;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteControlLockKeyValue = MOR_LOCK_TEST_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteControlLockKeyValue          // Data
                  );
  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid036,
                  L"MemoryOverwriteRequestControlLock - Setting to locked-with-key using key value = 0x11111111 when unlocked returns EFI_SUCCESS",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = MOR_LOCK_NO_KEY_SIZE; // invalid datasize = 1
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteControlLockKeyValue = MOR_LOCK_TEST_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteControlLockKeyValue          // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid037,
                  L"MemoryOverwriteRequestControlLock - Attempting to unlock by passing an invalid DataSize returns EFI_ACCESS_DENIED",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITH_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid038,
                  L"MemoryOverwriteRequestControlLock - Lock state is still locked-with-key with key value = 0x11111111",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // invoke MORLOCK SetVariable() with Data value = 0x00 to change to unlocked
  // must return EFI_ACCESS_DENIED and GetVariable() value must still = 0x02
  //
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_UNLOCKED;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid039,
                  L"MemoryOverwriteRequestControlLock - Setting to unlocked when locked-with-key returns EFI_ACCESS_DENIED",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITH_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid040,
                  L"MemoryOverwriteRequestControlLock - Lock state is still locked-with-key with key value = 0x11111111",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // invoke MORLOCK SetVariable() with Data value = 0x01 to change to locked-without-key
  // must return EFI_ACCESS_DENIED and GetVariable() value must still = 0x02
  //
  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteRequestControlLockData = MOR_LOCK_DATA_LOCKED_WITHOUT_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid041,
                  L"MemoryOverwriteRequestControlLock - Setting to locked-without-key when locked-with-key returns EFI_ACCESS_DENIED",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITH_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid042,
                  L"MemoryOverwriteRequestControlLock - Lock state is still locked-with-key with key value = 0x11111111",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Once locked-with-key, MOR SetVariable() call to set MOR bit 0 must return EFI_ACCESS_DENIED
  // and MOR value must not change
  //
  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  // getting current MOR value that will be used to check that the variable is unchanged
  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // caching MOR and setting the bit 0
  MemoryOverwriteRequestControlDataCached = MemoryOverwriteRequestControlData;
  MemoryOverwriteRequestControlData |= MOR_BIT_HIGH << MOR_CLEAR_MEMORY_BIT_OFFSET;

  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  Attributes,                           // Attributes
                  DataSize,                             // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid043,
                  L"MemoryOverwriteRequestControl - SetVariable() returns EFI_ACCESS_DENIED when MORLOCK is locked-with-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );

  // verifying that the variable has not been modified with SetVariable()
  if (MemoryOverwriteRequestControlDataCached == MemoryOverwriteRequestControlData) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid044,
                  L"MemoryOverwriteRequestControl - After SetVariable(), MOR value remains unchanged when MORLOCK is locked-with-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Once locked-with-key, MOR cannot be deleted
  // SetVariable() call to set MOR with DataSize = 0 must return EFI_ACCESS_DENIED
  // MemoryOverwriteControlData is a don't care in this case
  DataSize = 0;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  Attributes,                           // Attributes
                  DataSize,                             // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (Status == EFI_ACCESS_DENIED || EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid045,
                  L"MemoryOverwriteRequestControl - When MORLOCK is locked-with-key, an attempt to delete the MOR variable must return either EFI_ACCESS_DENIED or EFI_INVALID_PARAMETER",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // When locked-with-key, in this case key = 0x11111111,
  // SetVariable() with an invalid 8 byte key != 0x11111111, must return EFI_ACCESS_DENIED
  // and lock must be updated to Locked without key (Data value = 0x01) to prevent dictonary attack
  // The invalid key to be used to attempt unlock is = 0x22222222
  //
  DataSize = MOR_LOCK_WITH_KEY_SIZE;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteControlLockKeyValue = MOR_LOCK_INVALID_TEST_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteControlLockKeyValue          // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid046,
                  L"MemoryOverwriteRequestControlLock - Unlocking lock with invalid key != 0x11111111 returns EFI_ACCESS_DENIED",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITHOUT_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid047,
                  L"MemoryOverwriteRequestControlLock - Lock state is now locked-without-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // MORLOCK has been updated to locked-without-key (Data value = 0x01) to prevent dictonary attack
  // Now check to see if the lock can still be unlocked with the initial key used to set to lock-with-key state
  // The key to be used to attempt unlock is = 0x11111111
  //
  DataSize = MOR_LOCK_WITH_KEY_SIZE;
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  MemoryOverwriteControlLockKeyValue = MOR_LOCK_TEST_KEY;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  Attributes,                                  // Attributes
                  DataSize,                                    // DataSize
                  &MemoryOverwriteControlLockKeyValue          // Data
                  );
  if (Status == EFI_ACCESS_DENIED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid048,
                  L"MemoryOverwriteRequestControlLock - Attempt to unlock after dictionary attack mitigation returns EFI_ACCESS_DENIED",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  DataSize = sizeof(MemoryOverwriteRequestControlLockData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControlLock",        // VariableName
                  &gEfiMemoryOverwriteRequestControlLockGuid,  // VendorGuid
                  &Attributes,                                 // Attributes
                  &DataSize,                                   // DataSize
                  &MemoryOverwriteRequestControlLockData       // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlLockData != MOR_LOCK_DATA_LOCKED_WITHOUT_KEY)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTCGMemoryOverwriteRequestTestFunctionAssertionGuid049,
                  L"MemoryOverwriteRequestControlLock - Lock state is still locked-without-key",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  return EFI_SUCCESS;
}
