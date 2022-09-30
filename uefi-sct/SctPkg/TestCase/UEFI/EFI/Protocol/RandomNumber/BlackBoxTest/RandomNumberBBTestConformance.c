/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2014 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    RandomNumberBBTestConformance.c

Abstract:

    for EFI Driver Random Number Protocol's Conformance Test

--*/

#include "RandomNumberBBTest.h"

#define UNSUPPORTED_ALGO_GUID    \
  { 0x628fcfba, 0xc74b, 0x4038, {0x91, 0x5a, 0x01, 0x1a, 0xb9, 0x0f, 0x67, 0x35 }}

EFI_GUID UnsupportedAlgoGuid = UNSUPPORTED_ALGO_GUID;

/**
 *  @brief Entrypoint for GetInfo() Conformance Test.
 *         1 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestGetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_RNG_PROTOCOL                      *RandomNumber;

  //
  // init
  //
  RandomNumber = (EFI_RNG_PROTOCOL*)ClientInterface;

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
  //  Call GetInfo() with invalid RNGAlgorithmList.
  //
  BBTestGetInfoConformanceTestCheckpoint1 (StandardLib, RandomNumber);


  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for GetRNG() Conformance Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
BBTestGetRNGConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_RNG_PROTOCOL                      *RandomNumber;

  //
  // init
  //
  RandomNumber = (EFI_RNG_PROTOCOL*)ClientInterface;

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
  //  Call GetRNG() with invalid parameters.
  //
  BBTestGetRNGConformanceTestCheckpoint1 (StandardLib, RandomNumber);

  //
  //  Call GetRNG() with unsupported Algo.
  //
  BBTestGetRNGConformanceTestCheckpoint2 (StandardLib, RandomNumber);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_RNG_ALGORITHM                           RNGAlgorithmList;
  UINTN                                       RNGAlgorithmListSize;

  RNGAlgorithmListSize = 10;

  //
  // with RNGAlgorithmListSize being small.
  //
  Status = RandomNumber->GetInfo (
                           RandomNumber,
                           &RNGAlgorithmListSize,
                           &RNGAlgorithmList
                           );

  if (Status == EFI_UNSUPPORTED || Status == EFI_DEVICE_ERROR) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gConformanceTestAssertionGuid001,
                   L"RANDOM_NUMBER_PROTOCOL.GetInfo - GetInfo() is not supported or EFI_DEVICE_ERROR",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (EFI_BUFFER_TOO_SMALL == Status && RNGAlgorithmListSize &&
      RNGAlgorithmListSize % sizeof(EFI_RNG_ALGORITHM) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid001,
                 L"RANDOM_NUMBER_PROTOCOL.GetInfo - GetInfo() returns EFI_BUFFER_TOO_SMALL with small RNGAlgorithmListSize and returns valid size",
                 L"%a:%d: Status - %r, RNGAlgorithmListSize - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RNGAlgorithmListSize
                 );


  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetRNGConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_RNG_ALGORITHM                           RNGAlgorithmList1;
  EFI_RNG_ALGORITHM                           *RNGAlgorithmList2;
  UINTN                                       RNGAlgorithmListSize;
  UINTN                                       RNGValueLength;                   
  UINT8                                       RNGValue[10];
 
  RNGValueLength       = 10;
  RNGAlgorithmListSize = 10;

  //
  // with RNGAlgorithmListSize being small.
  //
  Status = RandomNumber->GetInfo (
                           RandomNumber,
                           &RNGAlgorithmListSize,
                           &RNGAlgorithmList1
                           );
  if (Status == EFI_UNSUPPORTED || Status == EFI_DEVICE_ERROR) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"RANDOM_NAME_PROTOCOL.GetInfo - GetInfo() is not supported or EFI_DEVICE_ERROR",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (EFI_BUFFER_TOO_SMALL != Status || RNGAlgorithmListSize % sizeof(EFI_RNG_ALGORITHM) != 0 || RNGAlgorithmListSize == 0) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Could not return the correct RNGAlgorithmListSize",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   RNGAlgorithmListSize,
                   (VOID **)&RNGAlgorithmList2
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Allocate Pool failure",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = RandomNumber->GetInfo (
                           RandomNumber,
                           &RNGAlgorithmListSize,
                           RNGAlgorithmList2
                           );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get the valid Algos",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );    
    gtBS->FreePool (RNGAlgorithmList2);
    return Status;
  }

  Status = RandomNumber->GetRNG (
                           RandomNumber,
                           RNGAlgorithmList2,
                           0,
                           RNGValue
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
    
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid002,
                 L"RANDOM_NAME_PROTOCOL.GetRNG - GetRNG() returns EFI_INVALID_PARAMETER when RNGValueLength is 0",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = RandomNumber->GetRNG (
                           RandomNumber,
                           RNGAlgorithmList2,
                           RNGValueLength,
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
                 gConformanceTestAssertionGuid003,
                 L"RANDOM_NAME_PROTOCOL.GetRNG - GetRNG() returns EFI_INVALID_PARAMETER when RNGValue is NULL",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (RNGAlgorithmList2);

  Status = RandomNumber->GetRNG (
                           RandomNumber,
                           NULL,
                           0,
                           RNGValue
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
    
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid004,
                 L"RANDOM_NAME_PROTOCOL.GetRNG - GetRNG() returns EFI_INVALID_PARAMETER when RNGValueLength is 0",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = RandomNumber->GetRNG (
                           RandomNumber,
                           RNGAlgorithmList2,
                           RNGValueLength,
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
                 gConformanceTestAssertionGuid005,
                 L"RANDOM_NAME_PROTOCOL.GetRNG - GetRNG() returns EFI_INVALID_PARAMETER when RNGValue is NULL",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetRNGConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 RNGValueLength;                   
  UINT8                 RNGValue[10];

  RNGValueLength = 10;

  Status = RandomNumber->GetRNG (
                           RandomNumber,
                           &UnsupportedAlgoGuid,
                           RNGValueLength,
                           RNGValue
                           );
  if (EFI_UNSUPPORTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid006,
                 L"RANDOM_NUMBER_PROTOCOL.GetRNG - GetRNG() returns EFI_UNSUPPORTED with unsupported Algo",
                 L"%a:%d:, Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

