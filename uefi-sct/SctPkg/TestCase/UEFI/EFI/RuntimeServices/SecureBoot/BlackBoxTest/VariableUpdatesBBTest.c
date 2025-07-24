/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright 2025, Arm LTD.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  VariableUpdatesTest.c

Abstract:
  Source file for Secure Boot Variable Updates Black-Box Test - Conformance Test.

--*/

#include "SctLib.h"
#include "SecureBootBBTestMain.h"
#include "SecureBootBBTestSupport.h"

#define KEK_ATTRIBUTES (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                       EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)

//
// Prototypes (external)
//

EFI_STATUS
VariableUpdatesTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Prototypes (internal)
//

EFI_STATUS
VariableUpdatesTestCheckpoint1 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  );

EFI_STATUS
VariableUpdatesTestCheckpoint2 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  );

EFI_STATUS
VariableUpdatesTestCheckpoint3 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  );

EFI_STATUS
VariableUpdatesTestCheckpoint4 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  );

//
// Functions
//

/**
 *  Entry point for Secure Boot Variable Updates Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
VariableUpdatesTest(
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_RUNTIME_SERVICES                *RT;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;

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
    return Status;
  }

  RT = (EFI_RUNTIME_SERVICES *)ClientInterface;

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  // invoke the cleanup routine to set KEK/db/dbx to known good values, 
  // including known timestamps
  Status = SecureBootVariableCleanup (RT, StandardLib, LoggingLib, ProfileLib);
  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - VariableUpdatesBBTest: SecureBootVariableCleanup() failed",
      Status);
    return Status;
  }

  Status = VariableUpdatesTestCheckpoint1 (RT, StandardLib, LoggingLib, ProfileLib);
  if (EFI_ERROR(Status)) {
    SecureBootVariableCleanup (RT, StandardLib, LoggingLib, ProfileLib);
    return Status;
  }
  Status = VariableUpdatesTestCheckpoint2 (RT, StandardLib, LoggingLib, ProfileLib);
  if (EFI_ERROR(Status)) {
    SecureBootVariableCleanup (RT, StandardLib, LoggingLib, ProfileLib);
    return Status;
  }
  Status = VariableUpdatesTestCheckpoint3 (RT, StandardLib, LoggingLib, ProfileLib);
  if (EFI_ERROR(Status)) {
    SecureBootVariableCleanup (RT, StandardLib, LoggingLib, ProfileLib);
    return Status;
  }

  VariableUpdatesTestCheckpoint4 (RT, StandardLib, LoggingLib, ProfileLib);
  if (EFI_ERROR(Status)) {
    SecureBootVariableCleanup (RT, StandardLib, LoggingLib, ProfileLib);
    return Status;
  }

  Status = SecureBootVariableCleanup (RT, StandardLib, LoggingLib, ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;

}

/**
 *  Verify that updates to KEK are signed (by PK)
 *
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ProfileLib     A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
VariableUpdatesTestCheckpoint1 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataSize;
  UINT8                 Data[MAX_BUFFER_SIZE];
  UINT32                Attributes;
  EFI_FILE_HANDLE       KeyFHandle;
  UINT32                KeyFileSize;
  CHAR16                *FileName;
  VOID                  *Buffer;
  UINTN                 BufferSize;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"VariableUpdatesTest",
                  L"UEFI spec, 8.2, 32.3, 32.4.1"
                  );
  }

  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 L"SecureBoot",               // VariableName
                 &gEfiGlobalVariableGuid,     // VendorGuid
                 &Attributes,                 // Attributes
                 &DataSize,                   // DataSize
                 Data                         // Data
                 );

  // if SecureBoot is not enabled, exit
  if (EFI_ERROR(Status) || Data[0] != 1) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - VariableUpdatesBBTest: SecureBoot not enabled",
      Status);
    return EFI_NOT_FOUND;
  }

  //
  // Test KEK update with unsigned signature list (4Kb in size), expect security violation
  //

  FileName = L"unsignedKeyUpdate.auth";
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned KEK update: OpenFileAndGetSize() failed for unsignedKeyUpdate.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned KEK update: Failed to allocate buffer for unsignedKeyUpdate.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned KEK update: Failed to read unsignedKeyUpdate.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"KEK",                    // VariableName
                     &gEfiGlobalVariableGuid,   // VendorGuid
                     KEK_ATTRIBUTES,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status == EFI_SECURITY_VIOLATION) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid001,
                 L"SecureBoot - Verify unsigned KEK update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);

  //
  // Test KEK update with properly signed data
  //

  FileName = L"KEKSigList1.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed KEK update: OpenFileAndGetSize() failed for KEKSigList1.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed KEK update: Failed to allocate buffer for KEKSigList1.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed KEK update: Failed to read KEKSigList1.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"KEK",                    // VariableName
                     &gEfiGlobalVariableGuid,   // VendorGuid
                     KEK_ATTRIBUTES,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid001,
                 L"SecureBoot - Verify signed KEK update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"VariableUpdatesTest",
                  L"UEFI spec, 8.2, 32.3, 32.4.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  Verify that updates to db are signed
 *
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ProfileLib     A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
VariableUpdatesTestCheckpoint2 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataSize;
  UINT32                Attributes;
  EFI_FILE_HANDLE       KeyFHandle;
  UINT32                KeyFileSize;
  CHAR16                *FileName;
  VOID                  *Buffer;
  UINTN                 BufferSize;
  UINT32                DBAttributes;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"VariableUpdatesTest",
                  L"UEFI spec, 8.2, 32.3, 32.4.1"
                  );
  }

  // get db variable attributes
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"db",                          // VariableName
                 &gEfiImageSecurityDatabaseGuid, // VendorGuid
                 &DBAttributes,                    // Attributes
                 &DataSize,                      // DataSize
                 NULL                            // Data
                 );


  //
  // Test db update with unsigned signature list (4Kb in size), expect security violation
  //

  FileName = L"unsignedKeyUpdate.auth";
  //
  // read the key data into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned db update: OpenFileAndGetSize() failed for unsignedKeyUpdate.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned db update: Failed to allocate buffer for unsignedKeyUpdate.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned db update: Failed to read unsignedKeyUpdate.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"db",                           // VariableName
                     &gEfiImageSecurityDatabaseGuid,  // Vendor GUID
                     DBAttributes,                   // Attributes
                     BufferSize,                      // DataSize
                     Buffer                           // Data
                     );

  if (Status == EFI_SECURITY_VIOLATION) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid003,
                 L"SecureBoot - Verify unsigned db update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Test db update with properly signed data
  //

  FileName = L"dbSigList1.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update: OpenFileAndGetSize() failed for dbSigList1.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update: Failed to allocate buffer for dbSigList1.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update: Failed to read dbSigList1.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"db",                    // VariableName
                     &gEfiImageSecurityDatabaseGuid,  // Vendor GUID
                     DBAttributes,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid004,
                 L"SecureBoot - Verify signed db update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Test db update with data signed by KEK
  //

  FileName = L"dbSigList2.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update: OpenFileAndGetSize() failed for dbSigList2.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update: Failed to allocate buffer for dbSigList2.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update: Failed to read dbSigList2.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"db",                    // VariableName
                     &gEfiImageSecurityDatabaseGuid,  // Vendor GUID
                     DBAttributes,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid005,
                 L"SecureBoot - Verify signed db update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Test db update with data signed by TestKEK2
  //

  FileName = L"dbSigList4.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update signed by TESTKEK2: OpenFileAndGetSize() failed for dbSigList4.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update signed by TESTKEK2: Failed to allocate buffer for dbSigList4.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed db update signed by TESTKEK2: Failed to read dbSigList4.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"db",                    // VariableName
                     &gEfiImageSecurityDatabaseGuid,  // Vendor GUID
                     DBAttributes,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid008,
                 L"SecureBoot - Verify signed db update data signed by TESTKEK2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);


  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"VariableUpdatesTest",
                  L"UEFI spec, 8.2, 32.3, 32.4.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  Verify that updates to dbx are signed
 *
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ProfileLib     A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
VariableUpdatesTestCheckpoint3 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataSize;
  UINT32                Attributes;
  EFI_FILE_HANDLE       KeyFHandle;
  UINT32                KeyFileSize;
  CHAR16                *FileName;
  VOID                  *Buffer;
  UINTN                 BufferSize;
  UINT32                DBXAttributes;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"VariableUpdatesTest",
                  L"UEFI spec, 8.2, 32.3, 32.4.1"
                  );
  }

  // get dbx variable attributes
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"dbx",                          // VariableName
                 &gEfiImageSecurityDatabaseGuid, // VendorGuid
                 &DBXAttributes,                    // Attributes
                 &DataSize,                      // DataSize
                 NULL                            // Data
                 );


  //
  // Test dbx update with unsigned signature list (4Kb in size), expect security violation
  //

  FileName = L"unsignedKeyUpdate.auth";

  //
  // read the key data into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned dbx update: OpenFileAndGetSize() failed for unsignedKeyUpdate.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned dbx update: Failed to allocate buffer for unsignedKeyUpdate.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify unsigned dbx update: Failed to read unsignedKeyUpdate.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"dbx",                           // VariableName
                     &gEfiImageSecurityDatabaseGuid,  // Vendor GUID
                     DBXAttributes,                   // Attributes
                     BufferSize,                      // DataSize
                     Buffer                           // Data
                     );

  if (Status == EFI_SECURITY_VIOLATION) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid006,
                 L"SecureBoot - Verify unsigned dbx update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);

  //
  // Test db update with properly signed data
  //

  FileName = L"dbSigList3.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed dbx update: OpenFileAndGetSize() failed for dbSigList3.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed dbx update: Failed to allocate buffer for dbSigList3.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed dbx update: Failed to read dbSigList3.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"dbx",                    // VariableName
                     &gEfiImageSecurityDatabaseGuid,  // Vendor GUID
                     DBXAttributes,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid007,
                 L"SecureBoot - Verify signed dbx update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"VariableUpdatesTest",
                  L"UEFI spec, 8.2, 32.3, 32.4.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  Verify that Append updates are valid
 *
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ProfileLib     A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
VariableUpdatesTestCheckpoint4 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataSize;
  UINT32                Attributes;
  EFI_FILE_HANDLE       KeyFHandle;
  UINT32                KeyFileSize;
  CHAR16                *FileName;
  VOID                  *Buffer;
  UINTN                 BufferSize;
  UINT32                DBAttributes;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"VariableUpdatesTest",
                  L"UEFI spec, 8.2, 32.3, 32.4.1"
                  );
  }

  // get db variable attributes
  DataSize = 0;
  Attributes = 0;
  Status = RT->GetVariable (
                 L"db",                          // VariableName
                 &gEfiImageSecurityDatabaseGuid, // VendorGuid
                 &DBAttributes,                    // Attributes
                 &DataSize,                      // DataSize
                 NULL                            // Data
                 );

  //
  //
  // Test KEK append update with properly signed data
  //

  FileName = L"KEKSigList3.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed KEK append update: OpenFileAndGetSize() failed for KEKSigList3.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed KEK append update: Failed to allocate buffer for KEKSigList3.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed KEK append update: Failed to read KEKSigList3.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"KEK",                    // VariableName
                     &gEfiGlobalVariableGuid,   // VendorGuid
                     KEK_ATTRIBUTES | EFI_VARIABLE_APPEND_WRITE,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid009,
                 L"SecureBoot - Verify signed KEK append update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);

  //
  // Test db append update with data Signed by TestKEK3
  //

  FileName = L"dbSigList5.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed DB append update: OpenFileAndGetSize() failed for dbSigList5.auth",
      Status);
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed DB append update: Failed to allocate buffer for dbSigList5.auth",
      Status);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    EFI_TEST_GENERIC_FAILURE(
      L"SecureBoot - Verify signed DB append update: Failed to read dbSigList5.auth",
      Status);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"db",                    // VariableName
                     &gEfiImageSecurityDatabaseGuid, // VendorGuid
                     DBAttributes | EFI_VARIABLE_APPEND_WRITE,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status == EFI_SUCCESS) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSecureBootVariableUpdatesBbTestAssertionGuid010,
                 L"SecureBoot - Verify signed DB append update",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);


  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"VariableUpdatesTest",
                  L"UEFI spec, 8.2, 32.3, 32.4.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
