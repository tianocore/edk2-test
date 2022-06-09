/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MiscBootServicesBBTestConformance.c

Abstract:

  Consistency Test Cases of Miscellaneous Boot Services

--*/

#include "SctLib.h"
#include "MiscBootServicesBBTestMain.h"

/**
 *  Entrypoint for gtBS->SetWatchdogTimer() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestSetWatchdogTimerConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->GetNextMonotonicCount() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestGetNextMonotonicCountConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;

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
  // 3.2.2.1  GetNextMonotonicCount should not succeed when Count is NULL
  //
  Status = gtBS->GetNextMonotonicCount (
                   NULL  // invalid
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscBootServicesConsistencyTestAssertionGuid004,
                 L"BS.GetNextMonotonicCount - Count is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->InstallConfigurationTable() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.3
//
EFI_STATUS
EFIAPI
BBTestInstallConfigurationTableConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;

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
  // 3.3.2.1  InstallConfigurationTable should not succeed when the Guid is NULL
  //
  Status = gtBS->InstallConfigurationTable (
                   NULL,  // invalid
                   NULL
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscBootServicesConsistencyTestAssertionGuid005,
                 L"BS.InstallConfigurationTable - Guid is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.3.2.2  InstallConfigurationTable  should not succeed when the Guid is
  //          not present in the System Table and Table is NULL
  //
  Status = gtBS->InstallConfigurationTable (
                   &gMiscBootServicesTestTableGuid,
                   NULL
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscBootServicesConsistencyTestAssertionGuid006,
                 L"BS.InstallConfigurationTable - Guid is not present",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->CalculateCrc32() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.4
//
EFI_STATUS
EFIAPI
BBTestCalculateCrc32ConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                Data[1];
  UINTN                                DataSize;
  UINT32                               Crc32;

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
  // 3.4.2.1  CalculateCrc32 should not succeed when the Data is NULL
  //
  DataSize = sizeof(Data);
  Status = gtBS->CalculateCrc32 (
                   NULL,     // Data
                   DataSize,
                   &Crc32
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscBootServicesConsistencyTestAssertionGuid007,
                 L"BS.CalculateCrc32 - Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.4.2.2  CalculateCrc32 should not succeed when the Crc32 is NULL
  //
  DataSize = sizeof(Data);
  Status = gtBS->CalculateCrc32 (
                   Data,
                   DataSize,
                   NULL         // &Crc32
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscBootServicesConsistencyTestAssertionGuid008,
                 L"BS.CalculateCrc32 - Crc32 is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.4.2.3  CalculateCrc32 should not succeed when the DataSize is 0
  //
  DataSize = sizeof(Data);
  Status = gtBS->CalculateCrc32 (
                   Data,
                   0,           // DataSize
                   &Crc32
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscBootServicesConsistencyTestAssertionGuid009,
                 L"BS.CalculateCrc32 - DataSize is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

