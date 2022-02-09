/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2021 - 2023, Arm Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

    TCG2BBTestConformance.c

Abstract:

    for EFI Driver TCG2 Protocol's Basic Test

--*/

#include "TCG2ProtocolBBTest.h"

#define offsetof(st, m) __builtin_offsetof(st, m)

/**
 *  @brief Entrypoint for GetCapability() Function Test.
 *         4 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestGetCapabilityConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TCG2_PROTOCOL                     *TCG2;

  //
  // init
  //
  TCG2 = (EFI_TCG2_PROTOCOL*)ClientInterface;

  // Ensure Protocol not NULL
  if (TCG2 == NULL)
    return EFI_UNSUPPORTED;

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

  // Test Using NULL BootCapability Pointer
  BBTestGetCapabilityConformanceTestCheckpoint1 (StandardLib, TCG2);

  // Test for validating fields of struct returned by GetCapability()
  BBTestGetCapabilityConformanceTestCheckpoint2 (StandardLib, TCG2);

  // Test Using Capability struct with struct size less than 1.0 size
  BBTestGetCapabilityConformanceTestCheckpoint3 (StandardLib, TCG2);

  // Test Using Capability struct with struct size equal to 1.0 size
  BBTestGetCapabilityConformanceTestCheckpoint4 (StandardLib, TCG2);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for GetActivePcrBanks() Function Test.
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestGetActivePcrBanksConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TCG2_PROTOCOL                     *TCG2;

  //
  // init
  //
  TCG2 = (EFI_TCG2_PROTOCOL*)ClientInterface;

  // Ensure Protocol not NULL
  if (TCG2 == NULL)
    return EFI_UNSUPPORTED;

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

  // Test with invalid (NULL) bitmap
  BBTestGetActivePcrBanksConformanceTestCheckpoint1 (StandardLib, TCG2);

  // Test with valid bitmap
  BBTestGetActivePcrBanksConformanceTestCheckpoint2 (StandardLib, TCG2);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for HashLogExtendEvent() Function Test.
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestHashLogExtendEventConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TCG2_PROTOCOL                     *TCG2;
  //
  // init
  //
  TCG2 = (EFI_TCG2_PROTOCOL*)ClientInterface;

  // Ensure Protocol not NULL
  if (TCG2 == NULL)
    return EFI_UNSUPPORTED;

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

  // Test HashLogExtendEvent with invalid arguments
  BBTestHashLogExtendEventConformanceTestCheckpoint1 (StandardLib, TCG2);

  // Test HashLogExtendEvent with valid arguments
  BBTestHashLogExtendEventConformanceTestCheckpoint2 (StandardLib, TCG2);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  EFI_TCG2_BOOT_SERVICE_CAPABILITY *BootServiceCapPtr = NULL;

  Status = TCG2->GetCapability (
                           TCG2,
                           BootServiceCapPtr);

  // Ensure GetCapability returns Invalid Parameter when passing in NULL pointer
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid001,
                 L"TCG2_PROTOCOL.GetCapability - GetCapability() returns EFI_INVALID_PARAMETER with NULL pointer Capability Struct Passed in",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  CHAR8                                 StructureVersionMajor;
  CHAR8                                 StructureVersionMinor;
  CHAR8                                 ProtocolVersionMajor;
  CHAR8                                 ProtocolVersionMinor;
  EFI_TCG2_BOOT_SERVICE_CAPABILITY      BootServiceCap;

  BootServiceCap.Size = sizeof(EFI_TCG2_BOOT_SERVICE_CAPABILITY);

  Status = TCG2->GetCapability (
                           TCG2,
                           &BootServiceCap);

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: GetCapability should return EFI_SUCCESS"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StructureVersionMajor = BootServiceCap.StructureVersion.Major;
  StructureVersionMinor = BootServiceCap.StructureVersion.Minor;

  // TCG EFI Protocol spec 6.4.4 #4
  if ((StructureVersionMajor != 1) | (StructureVersionMinor != 1)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: GetCapability should have StructureVersion 1.1, reported value = %d.%d",
                     StructureVersionMajor,
                     StructureVersionMinor
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  ProtocolVersionMajor = BootServiceCap.ProtocolVersion.Major;
  ProtocolVersionMinor = BootServiceCap.ProtocolVersion.Minor;

  // TCG EFI Protocol spec 6.4.4 #4
  if ((ProtocolVersionMajor != 1) | (ProtocolVersionMinor != 1)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: GetCapability should have ProtocolVersion 1.1, reported value = %d.%d",
                     ProtocolVersionMajor,
                     ProtocolVersionMinor
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (!(BootServiceCap.HashAlgorithmBitmap & EFI_TCG2_BOOT_HASH_ALG_SHA256)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: unexpected hash algorithms reported = %x",
                     BootServiceCap.HashAlgorithmBitmap
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (!(BootServiceCap.SupportedEventLogs &  EFI_TCG2_EVENT_LOG_FORMAT_TCG_2)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: GetCapability must support TCG2 event log format"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  for (int i = 0; i < sizeof(BootServiceCap.ActivePcrBanks); i++) {
    if (((BootServiceCap.ActivePcrBanks & (1u << i)) != 0) &&
        ((BootServiceCap.HashAlgorithmBitmap & (1u << i)) == 0)) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: ActivePcrBanks is not a subset of HashAlgorithmBitmap. Reported ActivePcrBanks:0x%x HashAlgorithmBitmap=0x%x",
                     BootServiceCap.ActivePcrBanks,
                     BootServiceCap.HashAlgorithmBitmap
                     );
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  if (BootServiceCap.NumberOfPcrBanks < 1 ) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: expect at least 1 PCR bank"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify that ActivePcrBanks includes SHA256, SHA384, or SHA512
  EFI_TCG2_EVENT_ALGORITHM_BITMAP HashBitMapAlgos =  EFI_TCG2_BOOT_HASH_ALG_SHA256 | EFI_TCG2_BOOT_HASH_ALG_SHA384 | EFI_TCG2_BOOT_HASH_ALG_SHA512;

  if (!(BootServiceCap.ActivePcrBanks & HashBitMapAlgos)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: ActivePcrBanks doesn't includes SHA256, SHA384, or SHA512",
                     BootServiceCap.ActivePcrBanks
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid002,
                 L"TCG2_PROTOCOL.GetCapability - GetCapability() populates all elements of EFI_TCG_BOOT_SERVICE_CAPABILITY",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  EFI_TCG2_BOOT_SERVICE_CAPABILITY      BootServiceCap;

  // set size to be value less than 1.0 or 1.1 struct
  BootServiceCap.Size = 4;

  Status = TCG2->GetCapability (
                           TCG2,
                           &BootServiceCap);

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  if (Status != EFI_BUFFER_TOO_SMALL && BootServiceCap.Size != sizeof(EFI_TCG2_BOOT_SERVICE_CAPABILITY)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: Did not return Status == EFI_BUFFER_TOO_SMALL and Size == sizeof(EFI_TCG2_BOOT_SERVICE_CAPABILITY)"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid003,
                 L"TCG2_PROTOCOL.GetCapability() - GetCapability() handling of input struct size less than the size of EFI_TCG2_BOOT_SERVICE_CAPABILITY up to and including the ManufacturerID field",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  EFI_TCG2_BOOT_SERVICE_CAPABILITY      BootServiceCap;

  // set size of struct to be up to and including the ManufacturerID
  // (this acts like a client with a 1.0 version of the struct)
  BootServiceCap.Size = offsetof(EFI_TCG2_BOOT_SERVICE_CAPABILITY, NumberOfPcrBanks);

  Status = TCG2->GetCapability (
                           TCG2,
                           &BootServiceCap);

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: 1.0 Compatibility. GetCapability should return EFI_SUCCESS"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify returned Size equals the size of EFI_TCG2_BOOT_SERVICE_CAPABILITY up to and including the ManufacturerID field.
  if (BootServiceCap.Size != offsetof(EFI_TCG2_BOOT_SERVICE_CAPABILITY, NumberOfPcrBanks)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapability Test: Did not return Size == EFI_TCG2_BOOT_SERVICE_CAPABILITY up to and including the ManufacturerID field"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid004,
                 L"TCG2_PROTOCOL.GetCapability - GetCapability() backwards compatibility check for 1.0 version of EFI_TCG_BOOT_SERVICE_CAPABILITY",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetActivePcrBanksConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;

  EFI_TCG2_EVENT_ALGORITHM_BITMAP *ActivePcrBanks = NULL;
  Status = TCG2->GetActivePcrBanks (
                           TCG2,
                           ActivePcrBanks);

  // Ensure GetActivePcrBanks returns Invalid Parameter when passing in NULL pointer
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid005,
                 L"TCG2_PROTOCOL.GetActivePcrBanks - GetActivePcrBanks() returns EFI_INVALID_PARAMETER with NULL pointer Passed in",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetActivePcrBanksConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  EFI_TCG2_EVENT_ALGORITHM_BITMAP ActivePcrBanks;
  EFI_TCG2_BOOT_SERVICE_CAPABILITY      BootServiceCap;

  Status = TCG2->GetActivePcrBanks (
                           TCG2,
                           &ActivePcrBanks);

  // Ensure GetActivePcrBanks returns EFI_SUCCESS
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetActivePcrBanks Test: GetActivePcrBanks should return EFI_SUCCESS"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  EFI_TCG2_EVENT_ALGORITHM_BITMAP BitMapAlgos =  EFI_TCG2_BOOT_HASH_ALG_SHA256 | EFI_TCG2_BOOT_HASH_ALG_SHA384 | EFI_TCG2_BOOT_HASH_ALG_SHA512;

  // Ensure ActivePcrBanks has SHA256/384/512 in its Bitmap
  if (!(ActivePcrBanks & BitMapAlgos)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetActivePcrBanks Test: GetActivePcrBanks should have SHA256/384/512 Algorithm in its Bitmap. ActivePcrBanks = %x",
                     ActivePcrBanks
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  BootServiceCap.Size = sizeof(EFI_TCG2_BOOT_SERVICE_CAPABILITY);

  Status = TCG2->GetCapability (
                           TCG2,
                           &BootServiceCap);

  // Ensure ActivePcrBanks is the same returned as GetCapability()
  if (ActivePcrBanks != BootServiceCap.ActivePcrBanks) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetActivePcrBanks Test:Returned ActivePcrBanks should match the one returned by GetCapability()"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid006,
                 L"TCG2_PROTOCOL.GetActivePcrBanks - GetActivePcrBanks should return with EFI_SUCCESS and have SHA256/384/512 Algoritms in its Bitmap",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  UINT64                                Flags = 0;
  EFI_PHYSICAL_ADDRESS                  DataToHash;
  UINT64                                DataToHashLen;
  EFI_TCG2_EVENT                        *EfiTcgEvent;
  const CHAR8                           *EventData = "TCG2 Protocol Test";
  const CHAR8                           *Str = "The quick brown fox jumps over the lazy dog";
  UINT32                                EfiTcgEventSize = sizeof(EFI_TCG2_EVENT) + SctAsciiStrLen(EventData);

  DataToHash =  (EFI_PHYSICAL_ADDRESS)Str;
  DataToHashLen = SctAsciiStrLen(Str);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   EfiTcgEventSize,
                   (VOID **)&EfiTcgEvent
                   );

  EfiTcgEvent->Header.HeaderSize = sizeof(EFI_TCG2_EVENT_HEADER);
  EfiTcgEvent->Header.HeaderVersion = 1;
  EfiTcgEvent->Header.EventType = EV_POST_CODE;
  EfiTcgEvent->Header.PCRIndex = 16;
  EfiTcgEvent->Size = EfiTcgEvent->Header.HeaderSize + SctAsciiStrLen(EventData);

  // Ensure HashLogExtendEvent returns Invalid Parameter when passing in NULL DataToHash pointer
  // EFI Protocol Spec Section 6.6.5 #1
  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           (EFI_PHYSICAL_ADDRESS)NULL,
                           0,
                           EfiTcgEvent);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid007,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - Test with NULL DataToHash Pointer should return EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Ensure HashLogExtendEvent returns Invalid Parameter when passing in NULL EfiTcgEvent pointer
  // EFI Protocol Spec Section 6.6.5 #1
  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           NULL);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
   } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
   }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid008,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - Test with NULL EfiTcgEvent Pointer should return EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Ensure HashLogExtendEvent returns Invalid Parameter when passed in EventSize < HeaderSize + sizeof(UINT32)
  // EFI Protocol Spec Section 6.6.5 #2
  EfiTcgEvent->Size = EfiTcgEvent->Header.HeaderSize + sizeof(UINT32) - 1;

  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           EfiTcgEvent);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid009,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - Test with Event.Size < Event.Header.HeaderSize + sizeof(UINT32) should return EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Ensure HashLogExtendEvent returns Invalid Parameter when passing in PCR Index > 23
  // EFI Protocol Spec Section 6.6.5 #3
  EfiTcgEvent->Header.PCRIndex = 24;
  EfiTcgEvent->Size = EfiTcgEvent->Header.HeaderSize + SctAsciiStrLen(EventData);

  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           EfiTcgEvent);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid010,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - Test with PCRIndex > 23 should return  EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TCG2_EVENT                        *EfiTcgEvent;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  UINT64                                Flags = 0;
  EFI_PHYSICAL_ADDRESS                  DataToHash;
  UINT64                                DataToHashLen;
  const CHAR8                           *Str = "The quick brown fox jumps over the lazy dog";
  const CHAR8                           *EventData = "TCG2 Protocol Test";
  UINT32 EfiTcgEventSize = sizeof(EFI_TCG2_EVENT) + SctAsciiStrLen(EventData);

  DataToHash = (EFI_PHYSICAL_ADDRESS)Str;
  DataToHashLen = SctAsciiStrLen(Str);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   EfiTcgEventSize,
                   (VOID **)&EfiTcgEvent
                   );

  EfiTcgEvent->Header.HeaderSize = sizeof(EFI_TCG2_EVENT_HEADER);
  EfiTcgEvent->Header.HeaderVersion = 1;
  EfiTcgEvent->Header.EventType = EV_POST_CODE;
  EfiTcgEvent->Header.PCRIndex = 16;
  EfiTcgEvent->Size = EfiTcgEvent->Header.HeaderSize + SctAsciiStrLen(EventData);

  // Perform HashLogExtendEvent over test buffer to PCR 16
  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           EfiTcgEvent);

  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid011,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - HashLogExtendEvent() Test: HashLogExtendEvent should return EFI_SUCCESS",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Test with valid Parameters but with Flags = PE_COFF_IMAGE
  // EFI Protocol Spec Section 6.6.5 #4
  Flags = PE_COFF_IMAGE;

  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           EfiTcgEvent);

  if (Status != EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid012,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - HashLogExtendEvent() Test Handling of PE_COFF_IMAGE flag",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (EfiTcgEvent);

  return EFI_SUCCESS;
}
