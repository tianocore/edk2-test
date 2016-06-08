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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
                   L"RANDOM_NAME_PROTOCOL.GetInfo - GetInfo() is not supported or EFI_DEVICE_ERROR",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (EFI_BUFFER_TOO_SMALL == Status && RNGAlgorithmListSize % sizeof(EFI_RNG_ALGORITHM) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConformanceTestAssertionGuid001,
                 L"RANDOM_NAME_PROTOCOL.GetInfo - GetInfo() returns EFI_BUFFER_TOO_SMALL with small RNGAlgorithmListSize and returns valid size",
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

