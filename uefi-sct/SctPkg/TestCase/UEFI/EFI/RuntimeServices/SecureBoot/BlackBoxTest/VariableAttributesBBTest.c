/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright 2025, Arm Ltd.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  VariableAttributesTest.c

Abstract:
  Source file for Secure Boot Variable Attribute Black-Box Test - Conformance Test.

--*/

#include "SctLib.h"
#include "SecureBootBBTestMain.h"
#include "SecureBootBBTestSupport.h"

// Global variable attributes as defined in Table 14 in the UEFI spec
#define SECUREBOOT_ATTRIBUTES (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)
#define SETUPMODE_ATTRIBUTES (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)
#define PK_ATTRIBUTES (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                       EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
#define KEK_ATTRIBUTES (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                       EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
#define DB_ATTRIBUTES (EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
#define DBX_ATTRIBUTES (EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)

VARIABLE_DATA DefSecureBootVarArray[DEF_SECURE_VARS_NUM] = {
  {L"PKDefault",   (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS),
   EFI_TEST_SECUREBOOTVARIABLEATTRIBUTES_ASSERTION_009_GUID},
  {L"KEKDefault",  (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS),
   EFI_TEST_SECUREBOOTVARIABLEATTRIBUTES_ASSERTION_010_GUID},
  {L"dbDefault",   (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS),
   EFI_TEST_SECUREBOOTVARIABLEATTRIBUTES_ASSERTION_011_GUID},
  {L"dbxDefault",  (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS),
   EFI_TEST_SECUREBOOTVARIABLEATTRIBUTES_ASSERTION_012_GUID},
};

//
// Prototypes (external)
//

EFI_STATUS
VariableAttributesTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Functions
//

/**
 *  Entry point for Secure Boot Variable Attributes Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
VariableAttributesTest(
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_TEST_ASSERTION                  Result;
  EFI_RUNTIME_SERVICES                *RT;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  UINTN                               DataSize;
  UINT8                               Data[MAX_BUFFER_SIZE];
  UINT32                              Attributes;
  VOID                                *DataPtr;
  UINT32                              Index;

  //
  // Get test support library interfaces
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib,
             &LoggingLib
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - VariableAttributesBBTest: Failed to get test support protocol library",
      Status);
    return Status;
  }

  RT = (EFI_RUNTIME_SERVICES *)ClientInterface;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"VariableAttributesTest",
                  L"UEFI spec, Table 14"
                  );
  }

  //
  // Check if SecureBoot is enabled (Data[0] == 1)
  //
  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 L"SecureBoot",               // VariableName
                 &gEfiGlobalVariableGuid,     // VendorGuid
                 &Attributes,                 // Attributes
                 &DataSize,                   // DataSize
                 Data                         // Data
                 );

  if (EFI_ERROR(Status) || Data[0] != 1) {
    EFI_TEST_GENERIC_FAILURE(L"SecureBoot - VariableAttributesBBTest: SecureBoot not enabled",
      Status);
    return EFI_NOT_FOUND;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 EFI_TEST_ASSERTION_PASSED,
                 gSecureBootVariableAttributesBbTestAssertionGuid001,
                 L"SecureBoot - Verify SecureBoot is enabled ",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check if SetupMode is disabled (i.e., SetupMode == 0)
  //
  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 L"SetupMode",                // VariableName
                 &gEfiGlobalVariableGuid,     // VendorGuid
                 &Attributes,                 // Attributes
                 &DataSize,                   // DataSize
                 Data                         // Data
                 );

  if (EFI_ERROR(Status) || Data[0] != 0) {
    EFI_TEST_GENERIC_FAILURE(L"SecureBoot - VariableAttributesBBTest: SetupMode != 0", Status);
    return EFI_NOT_FOUND;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 EFI_TEST_ASSERTION_PASSED,
                 gSecureBootVariableAttributesBbTestAssertionGuid002,
                 L"SecureBoot - Verify SetupMode == 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Verify attributes of SecureBoot variable match expected value
  // (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)
  //
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"SecureBoot",               // VariableName
                 &gEfiGlobalVariableGuid,     // VendorGuid
                 &Attributes,                 // Attributes
                 &DataSize,                   // DataSize
                 NULL                         // Data
                 );

  if (Status == EFI_BUFFER_TOO_SMALL && Attributes == SECUREBOOT_ATTRIBUTES) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableAttributesBbTestAssertionGuid003,
                 L"SecureBoot - Verify SecureBoot variable attributes",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Attributes=0x%x, Expected=0x%x\n",
                 Attributes, SECUREBOOT_ATTRIBUTES
                 );

  //
  // Verify attributes of SetupMode variable match expected value
  // (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)
  //
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"SetupMode",                // VariableName
                 &gEfiGlobalVariableGuid,     // VendorGuid
                 &Attributes,                 // Attributes
                 &DataSize,                   // DataSize
                 NULL                         // Data
                 );

  if (Status == EFI_BUFFER_TOO_SMALL && Attributes == SETUPMODE_ATTRIBUTES) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableAttributesBbTestAssertionGuid004,
                 L"SecureBoot - Verify SetupMode variable attributes",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Attributes=0x%x, Expected=0x%x\n",
                 Attributes, SETUPMODE_ATTRIBUTES
                 );

  //
  // Verify attributes of Platform Key (PK) variable match expected value
  // (Non-volatile, boot + runtime access, time-based authenticated write)
  //
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"PK",                       // VariableName
                 &gEfiGlobalVariableGuid,     // VendorGuid
                 &Attributes,                 // Attributes
                 &DataSize,                   // DataSize
                 NULL                         // Data
                 );

  if (Status == EFI_BUFFER_TOO_SMALL && Attributes == PK_ATTRIBUTES) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableAttributesBbTestAssertionGuid005,
                 L"SecureBoot - Verify PK variable attributes",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Attributes=0x%x, Expected=0x%x\n",
                 Attributes, PK_ATTRIBUTES
                 );

  //
  // Verify attributes of Key Exchange Key (KEK) variable match expected value
  // (Non-volatile, boot + runtime access, time-based authenticated write)
  //
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"KEK",                      // VariableName
                 &gEfiGlobalVariableGuid,     // VendorGuid
                 &Attributes,                 // Attributes
                 &DataSize,                   // DataSize
                 NULL                         // Data
                 );

  if (Status == EFI_BUFFER_TOO_SMALL && Attributes == KEK_ATTRIBUTES) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableAttributesBbTestAssertionGuid006,
                 L"SecureBoot - Verify KEK variable attributes",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Attributes=0x%x, Expected=0x%x\n",
                 Attributes, KEK_ATTRIBUTES
                 );

  //
  // Verify that the 'db' (Allowed Signatures) variable includes expected attribute
  // (time-based authenticated write access)
  //
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"db",                          // VariableName
                 &gEfiImageSecurityDatabaseGuid, // VendorGuid
                 &Attributes,                    // Attributes
                 &DataSize,                      // DataSize
                 NULL                            // Data
                 );

  if (Status == EFI_BUFFER_TOO_SMALL && (Attributes & DB_ATTRIBUTES)) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableAttributesBbTestAssertionGuid007,
                 L"SecureBoot - Verify DB variable attributes",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Attributes=0x%x, Expected=0x%x\n",
                 Attributes, DB_ATTRIBUTES
                 );
  //
  // Verify that the 'dbx' (Forbidden Signatures) variable includes expected attribute
  // (time-based authenticated write access)
  //
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"dbx",                          // VariableName
                 &gEfiImageSecurityDatabaseGuid, // VendorGuid
                 &Attributes,                    // Attributes
                 &DataSize,                      // DataSize
                 NULL                            // Data
                 );

  if (Status == EFI_BUFFER_TOO_SMALL && (Attributes & DBX_ATTRIBUTES)) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableAttributesBbTestAssertionGuid008,
                 L"SecureBoot - Verify DBX variable attributes",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Attributes=0x%x, Expected=0x%x\n",
                 Attributes, DB_ATTRIBUTES
                 );

  //
  // Verify default Secure Boot variables (PKDefault, KEKDefault, dbDefault, dbxDefault)
  // Each variable should exist and have matching attribute values.
  //
  Result = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < DEF_SECURE_VARS_NUM; Index++) {
    // discover buffer size required
    DataSize = 0;
    DataPtr     = NULL;
    Status = gtRT->GetVariable (
                          DefSecureBootVarArray[Index].Name,
                          &gEfiGlobalVariableGuid,
                          &Attributes,
                          &DataSize,
                          DataPtr
                          );

    if (Status == EFI_BUFFER_TOO_SMALL) {
      gtBS->AllocatePool (
                  EfiBootServicesData,
                  DataSize,
                  (VOID **) &DataPtr
                  );

      Status = gtRT->GetVariable (
                          DefSecureBootVarArray[Index].Name,
                          &gEfiGlobalVariableGuid,
                          &Attributes,
                          &DataSize,
                          DataPtr
                          );
    }

    if (Status == EFI_SUCCESS) {
      // check the attributes
      if (Attributes != DefSecureBootVarArray[Index].Attributes) {
        Result   = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                    StandardLib,
                    EFI_VERBOSE_LEVEL_DEFAULT,
                    L"Variable Name: %s, Variable Attribute: 0x%08x, Expected Attribute: 0x%08x\n",
                    DefSecureBootVarArray[Index].Name,
                    Attributes,
                    DefSecureBootVarArray[Index].Attributes
                    );
      }
    } else {
      Result   = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                    StandardLib,
                    EFI_VERBOSE_LEVEL_DEFAULT,
                    L"Failed to fetch Variable = %s, Status = 0x%x\n",
                    DefSecureBootVarArray[Index].Name,
                    Status
                    );
    }

    // Record assertion
    StandardLib->RecordAssertion (
                  StandardLib,
                  Result,
                  DefSecureBootVarArray[Index].TestAssertionGuid,
                  L"BBSR Check Default SecureBoot Variable",
                  L"%s :%a:%d:Status - %r",
                  DefSecureBootVarArray[Index].Name,
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
    // reset the Result for next iteration
    Result = EFI_TEST_ASSERTION_PASSED;
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"VariableAttributesTest",
                  L"UEFI spec, Table 14"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
