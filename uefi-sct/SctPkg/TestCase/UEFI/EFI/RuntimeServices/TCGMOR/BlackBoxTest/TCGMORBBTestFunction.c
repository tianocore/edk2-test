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

  TCGMORBBTestFunction.c

Abstract:

  Function Test Cases for the TCG MOR and MORLock EFI Variables

--*/
#include "SctLib.h"
#include "TCGMORBBTestMain.h"

#define RECOVER_BUFFER_SIZE  2048

#define TCG_MOR_VARIABLE_ATTRIBUTES 0x00000007


/**
 *  Entry point for TCGMOR Function Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
BBTestTCGMORFunctionTest (
  IN EFI_BB_TEST_PROTOCOL              *This,
  IN VOID                              *ClientInterface,
  IN EFI_TEST_LEVEL                    TestLevel,
  IN EFI_HANDLE                        SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_STATUS                           Status;

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
  // TCGMOR EFI Variable and Platform Reset Checks
  //
  Status = TCGMORPlatformResetCheck (StandardLib, RecoveryLib);

  //
  // TCGMOR test for SetVariable() with Invalid Parameters
  //
  Status = TCGMORSetVariable (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  MOR & MORLock EFI variables are correctly created by platform
 *  Initially setting MOR bit0 is then cleared upon platform reset
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param RecoveryLib    A pointer to EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
TCGMORPlatformResetCheck (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   Result;
  UINTN                                DataSize;
  UINTN                                MemoryOverwriteRequestControlData;
  UINTN                                MemoryOverwriteRequestControlLockData;
  UINT32                               Attributes;
  RESET_DATA                           *ResetData;
  UINT8                                Buffer[RECOVER_BUFFER_SIZE];
  UINTN                                Size;

  ResetData = (RESET_DATA *)Buffer;
  //
  // Read reset record
  //
  Status = RecoveryLib->ReadResetRecord (
                  RecoveryLib,
                  &Size,
                  Buffer
                  );
  if (EFI_ERROR(Status) || (Size < sizeof(RESET_DATA))) {
    goto INITIAL_RESET;
  } else if (ResetData->Step == 1) {
    goto MOR_VARIABLE_CHECK;
  } else if (ResetData->Step == 2) {
    goto MOR_BIT_CLEAR_ON_RESET;

  return EFI_LOAD_ERROR;
  }


INITIAL_RESET:
  //
  // Perform initial plaform reset
  //
  ResetData->Step = 1;
  ResetData->TplIndex = 0;
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
  SctPrint (L"System will cold reset after 1 second...");
  gtBS->Stall (1000000);
  gtRT->ResetSystem (
                  EfiResetCold,
                  EFI_SUCCESS,
                  0,
                  NULL
                  );


MOR_VARIABLE_CHECK:
  //
  // Post system reset, Check if the MOR EFI var is correctly created by platform
  //

  // Write reset record before the second reset (MOR_BIT_CLEAR_ON_RESET)
  ResetData->Step = 2;
  ResetData->TplIndex = 0;
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

  // GetVariable and check if the DataSize and Attributes are as expected
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
                  gTcgMorTestFunctionAssertionGuid001,
                  L"MemoryOverwriteRequestControl - Validate that the MOR Variable is created by the platform in accordance with Tcg Spec",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Set MemoryOverwriteRequestControlData bit0 and verify the platform clears Bit0 upon system reset
  //
  MemoryOverwriteRequestControlData |= 1<<0;

  Status = gtRT->SetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  Attributes,                           // Attributes
                  DataSize,                             // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (EFI_ERROR (Status) || !(MemoryOverwriteRequestControlData & 1<<0)) {
    SctPrint (L"Unable to set MemoryOverwriteAction_BitValue Bit0!");
    return Status;
  }

  // Cold reset system again for step 2
  SctPrint (L"System will cold reset after 1 second and test will be resumed after reboot.");
  gtBS->Stall (1000000);
  gtRT->ResetSystem (
                  EfiResetCold,
                  EFI_SUCCESS,
                  0,
                  NULL
                  );


MOR_BIT_CLEAR_ON_RESET:
  //
  // Check if the platform has cleared the set MOR bit0 on reset
  //
  Status = RecoveryLib->WriteResetRecord (
                  RecoveryLib,
                  0,
                  (UINT8*)ResetData
                  );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  DataSize = sizeof(MemoryOverwriteRequestControlData);
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;

  Status = gtRT->GetVariable (
                  L"MemoryOverwriteRequestControl",     // VariableName
                  &gEfiMemoryOverwriteControlDataGuid,  // VendorGuid
                  &Attributes,                          // Attributes
                  &DataSize,                            // DataSize
                  &MemoryOverwriteRequestControlData    // Data
                  );
  if (EFI_ERROR (Status) || (MemoryOverwriteRequestControlData & 1<<0)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTcgMorTestFunctionAssertionGuid002,
                  L"MemoryOverwriteRequestControl - Validate that MOR bit0 is cleared after a cold reset when the bit0 is initially set",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Verify MemoryOverwriteRequestControlLock is created as defined in Tcg spec
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
  if (EFI_ERROR (Status) || ((MemoryOverwriteRequestControlLockData & 0xFF) != 0x00) || 
      (DataSize != 1) || (Attributes != TCG_MOR_VARIABLE_ATTRIBUTES)) {
    Result = EFI_TEST_ASSERTION_FAILED;
  } else {
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTcgMorTestFunctionAssertionGuid003,
                  L"MemoryOverwriteRequestControlLock - Validate that MORLock Variable is created by the platform in accordance with Tcg Spec",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}


/**
 *  MOR EFI variable SetVariable() requests with invalid parameters
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param RecoveryLib    A pointer to EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
TCGMORSetVariable (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   Result;
  UINTN                                DataSize;
  UINTN                                MemoryOverwriteRequestControlData;
  UINTN                                MemoryOverwriteRequestControlDataCached;
  UINT32                               Attributes;

  //
  //MOR SetVariable() with invalid DataSize == 0 returns EFI_INVALID_PARAMETER and value is unchanged
  //
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  DataSize = sizeof(MemoryOverwriteRequestControlData);
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

  // caching variable and setting the bit0
  // SetVar with changed value and invalid DataSize == 0
  MemoryOverwriteRequestControlDataCached = MemoryOverwriteRequestControlData;
  MemoryOverwriteRequestControlData |= 1<<0;
  DataSize = 0;

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

  DataSize = sizeof(MemoryOverwriteRequestControlData);

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

  // verifying that the variable has not been modified with SetVar
  if ((MemoryOverwriteRequestControlDataCached & 0xFF) == (MemoryOverwriteRequestControlData & 0xFF)) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTcgMorTestFunctionAssertionGuid004,
                  L"MemoryOverwriteRequestControl - SetVariable() with DataSize == 0 returns EFI_INVALID_PARAMETER, variable remains unchanged",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }


  //
  //MOR SetVariable() with invalid Attributes == NV returns EFI_INVALID_PARAMETER and value is unchanged
  //
  Attributes = TCG_MOR_VARIABLE_ATTRIBUTES;
  DataSize = sizeof(MemoryOverwriteRequestControlData);
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

  // caching variable and setting the bit0
  // SetVar with changed value and invalid attributes = NV
  MemoryOverwriteRequestControlDataCached = MemoryOverwriteRequestControlData;
  MemoryOverwriteRequestControlData |= 1<<0;
  Attributes = EFI_VARIABLE_NON_VOLATILE;

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

  // verifying that the variable has not been modified with SetVar
  if (MemoryOverwriteRequestControlDataCached == MemoryOverwriteRequestControlData) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  gTcgMorTestFunctionAssertionGuid005,
                  L"MemoryOverwriteRequestControl - SetVariable() with Attributes == NV returns EFI_INVALID_PARAMETER, variable remains unchanged",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}
