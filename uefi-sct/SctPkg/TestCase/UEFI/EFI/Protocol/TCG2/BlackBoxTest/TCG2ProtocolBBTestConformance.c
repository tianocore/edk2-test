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
#include <Base.h>

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
 *         4 checkpoints will be tested.
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

  // Test GetEventLog using invalid EventLog Format
  BBTestGetEventLogConformanceTestCheckpoint1 (StandardLib, TCG2);

  // Test GetEventLog using valid EventLog Format
  BBTestGetEventLogConformanceTestCheckpoint2 (StandardLib, TCG2);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for SubmitCommand() Function Test.
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestSubmitCommandConformanceTest (
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

  // Test GetRandom TPM Command
  BBTestSubmitCommandConformanceTestCheckpoint1 (StandardLib, TCG2);

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
  BootServiceCap.Size = OFFSET_OF(EFI_TCG2_BOOT_SERVICE_CAPABILITY, NumberOfPcrBanks);

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
  if (BootServiceCap.Size != OFFSET_OF(EFI_TCG2_BOOT_SERVICE_CAPABILITY, NumberOfPcrBanks)) {
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

#define EFI_TCG2_INVALID_EVENT_LOG_FORMAT 0x20

EFI_STATUS
BBTestGetEventLogConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  EFI_TCG2_EVENT_LOG_FORMAT             EventLogFormat;
  EFI_PHYSICAL_ADDRESS                  EventLogLocation;
  EFI_PHYSICAL_ADDRESS                  EventLogLastEntry;
  BOOLEAN                               EventLogTruncated;

  // Ensure Get EventLog returns Invalid Parameter when passed invalid format
  EventLogFormat = EFI_TCG2_INVALID_EVENT_LOG_FORMAT;

  Status = TCG2->GetEventLog (
                           TCG2,
                           EventLogFormat,
                           &EventLogLocation,
                           &EventLogLastEntry,
                           &EventLogTruncated);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid013,
                 L"TCG2_PROTOCOL.GetEventLog - GetEventLog() should return EFI_INVALID_PARAMETER when passed in invalid EventLog Format",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetEventLogConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  EFI_TCG2_EVENT_LOG_FORMAT             EventLogFormat;
  EFI_PHYSICAL_ADDRESS                  EventLogLocation;
  EFI_PHYSICAL_ADDRESS                  EventLogLastEntry;
  BOOLEAN                               EventLogTruncated;
  TCG_PCR_EVENT                         *EventLogHeader;
  TCG_EfiSpecIDEventStruct              *EventLogHeaderSpecEvent;
  TCG_PCR_EVENT2                        *LastEvent;
  // signature as defined in the EFI protocol spec: "Spec ID Event03"
  UINT8 signature[] = {0x53, 0x70, 0x65, 0x63, 0x20, 0x49, 0x44, 0x20, 0x45, 0x76, 0x65, 0x6e, 0x74, 0x30, 0x33, 0x00};

  EventLogFormat = EFI_TCG2_EVENT_LOG_FORMAT_TCG_2;

  // Call GetEventLog with valid EventLogFormat
  Status = TCG2->GetEventLog (
                           TCG2,
                           EventLogFormat,
                           &EventLogLocation,
                           &EventLogLastEntry,
                           &EventLogTruncated);

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  // Verify GetEventLog returns EFI_SUCCESS
  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: GetEventLog should return EFI_SUCCESS with valid EventLogFormat, Status = %r",
                     Status
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;

  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid014,
                 L"TCG2_PROTOCOL.GetEventLog - GetEventLog() should return EFI_SUCCESS",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // If GetEventLog doesn't return EFI_SUCCESS abort test
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  EventLogHeader = (TCG_PCR_EVENT *) EventLogLocation;
  EventLogHeaderSpecEvent = (TCG_EfiSpecIDEventStruct *) EventLogHeader->Event;

  AssertionType = EFI_TEST_ASSERTION_PASSED;


  // Verify valid eventlog header is returned
  // Verify EventLogHeader PCR index == 0
  if (EventLogHeader->PCRIndex != 0) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: EventLogHeader should have PCR index == 0"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify EventLogHeader event type = EV_NO_ACTION
  if (EventLogHeader->EventType != EV_NO_ACTION) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: EventLogHeader should be EventType == EV_NO_ACTION"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify EventLog Signature
  Status = SctCompareMem(EventLogHeaderSpecEvent->signature, signature, sizeof(signature));

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: EventLogHeader Signature did not match \'Spec ID Event03\'"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid015,
                 L"TCG2_PROTOCOL.GetEventLog - GetEventLog() should return correct EventLogHeader",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Verify that the event log created by HashLogExtendEvent in the
  // BBTestHashLogExtendEventConformanceTestCheckpoint2 function
  // is actually in Eventlog
  LastEvent = (TCG_PCR_EVENT2 *) EventLogLastEntry;
  Status = EFI_SUCCESS;

  // Verify Last Event PCR = 16
  if (LastEvent->PCRIndex != 16) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: PCR Index of Last event should be 16"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify last event type = EV_POST_CODE
  if (LastEvent->EventType != EV_POST_CODE) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: PCR Index of last event should be type EV_POST_CODE"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid016,
                 L"TCG2_PROTOCOL.GetEventLog - verify that event log has expected entry from previous HashLogExtendEvent",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

//  Expected SHA256 Hash of the string "The quick brown fox jumps over the lazy dog"
UINT8 Tpm2HashOut[32] = {0xd7,0xa8,0xfb,0xb3,0x07,0xd7,0x80,0x94,0x69,0xca,0x9a,0xbc,0xb0,0x08,0x2e,0x4f, \
0x8d,0x56,0x51,0xe4,0x6d,0x3c,0xdb,0x76,0x2d,0x02,0xd0,0xbf,0x37,0xc9,0xe5,0x92};

EFI_STATUS
BBTestSubmitCommandConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  TPM2_HASH_RESPONSE                    CommandResponse;
  TPM2_HASH_COMMAND                     CommandInput;
  CHAR8 *Str ="The quick brown fox jumps over the lazy dog";

  // Build TPM2 Hash command to hash test string
  CommandInput.Tag = SctSwapBytes16(ST_NO_SESSIONS);
  CommandInput.CommandSize = SctSwapBytes32(sizeof(TPM2_HASH_COMMAND));
  CommandInput.CommandCode = SctSwapBytes32(TPM_CC_Hash);
  CommandInput.data.size = SctSwapBytes16(SctAsciiStrLen(Str));
  SctAsciiStrCpy((CHAR8 *)CommandInput.data.buffer, Str);
  CommandInput.hashAlg = SctSwapBytes16(TPM_ALG_SHA256);
  CommandInput.hierarchy = SctSwapBytes32(TPM_RH_NULL);

  // allocate buffer for response
  SctZeroMem(&CommandResponse, sizeof(TPM2_HASH_RESPONSE));

  Status = TCG2->SubmitCommand (
                           TCG2,
                           sizeof(TPM2_HASH_COMMAND),
                           (UINT8 *)&CommandInput,
                           sizeof(TPM2_HASH_RESPONSE),
                           (UINT8 *)&CommandResponse);


  AssertionType = EFI_TEST_ASSERTION_PASSED;

  // Verify SubmitCommand returns EFI_SUCCESS
  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol SubmitCommand Test: SubmitCommand should return EFI_SUCCESS, Status = %r",
                     Status
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify SubmitCommand returns correct Response Tag
  if (SctSwapBytes16(CommandResponse.Tag) != ST_NO_SESSIONS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol SubmitCommand Test: SubmitCommand should return ST_NO_SESSIONS response Tag"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify SubmitCommand returns correct Response Code
  if (SctSwapBytes32(CommandResponse.ResponseCode) != TPM_RC_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol SubmitCommand Test: SubmitCommand should return Correct ResponseCode, ResponseCode = %x",
                     SctSwapBytes32(CommandResponse.ResponseCode)
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }


  // Verify SubmitCommand returns correct Response Size
  if (SctSwapBytes32(CommandResponse.ResponseSize) != sizeof(TPM2_HASH_RESPONSE)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol SubmitCommand Test: SubmitCommand should return Correct ResponseSize, Size = %x",
                     SctSwapBytes32(CommandResponse.ResponseSize)
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Check that the size of the buffer returned is size of SHA256 hash
  if (SctSwapBytes16(CommandResponse.data.size) != 32) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol SubmitCommand Test: SubmitCommand should return correct size digest for SHA256, Size = %x",
                     SctSwapBytes16(CommandResponse.data.size)
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Ensure Hash returned matches expected response for input
  if (0 != SctCompareMem(Tpm2HashOut, CommandResponse.data.digest, SHA256_LENGTH) ) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nTCG2 Protocol SubmitCommand Test: SubmitCommand should return expected Hash for data that was hashed."
                   );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid017,
                 L"EFI_TCG2_PROTOCOL. SubmitComand() - SubmitCommand() shall populate the response buffer and return with a status of EFI_SUCCESS when valid command parameters are passed in.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
