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
                                                                
  Copyright (c) 2013 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

    RandomNumberBBTestFunction.c

Abstract:

    for EFI Driver Random Number Protocol's Basic Test

--*/

#include "RandomNumberBBTest.h"

//
// EFI RNG Algorithm Definitions
//
#define EFI_RNG_ALGORITHM_SP800_90_HASH_256_GUID \
{0xa7af67cb, 0x603b, 0x4d42, 0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96}

#define EFI_RNG_ALGORITHM_SP800_90_HMAC_256_GUID \
{0xc5149b43, 0xae85, 0x4f53, 0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7}

#define EFI_RNG_ALGORITHM_SP800_90_CTR_256_GUID \
{0x44f0de6e, 0x4d8c, 0x4045, 0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e}

#define EFI_RNG_ALGORITHM_X9_31_3DES_GUID \
{0x63c4785a, 0xca34, 0x4012, 0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46}

#define EFI_RNG_ALGORITHM_X9_31_AES_GUID \
{0xacd03321, 0x777e, 0x4d3d, 0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9}

#define EFI_RNG_ALGORITHM_RAW \
{0xe43176d7, 0xb6e8, 0x4827, 0xb7, 0x84, 0x7f, 0xfd, 0xc4, 0xb6, 0x85, 0x61}


EFI_GUID Algos[6] = {
    EFI_RNG_ALGORITHM_SP800_90_HASH_256_GUID, 
    EFI_RNG_ALGORITHM_SP800_90_HMAC_256_GUID, 
    EFI_RNG_ALGORITHM_SP800_90_CTR_256_GUID,
    EFI_RNG_ALGORITHM_X9_31_3DES_GUID, 
    EFI_RNG_ALGORITHM_X9_31_AES_GUID, 
    EFI_RNG_ALGORITHM_RAW
    };


/**
 *  @brief Entrypoint for GetInfo() Function Test.
 *         1 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestGetInfoFunctionTest (
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
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //  Call GetInfo() with valid parameters.
  //
  BBTestGetInfoFunctionTestCheckpoint1 (StandardLib, RandomNumber);


  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for GetRNG() Function Test.
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
BBTestGetRNGFunctionTest (
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
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //  Call GetRNG() with supported Algo.
  //
  BBTestGetRNGFunctionTestCheckpoint1 (StandardLib, RandomNumber);

  //
  //  Call GetRNG() with NULL Algos.
  //
  BBTestGetRNGFunctionTestCheckpoint2 (StandardLib, RandomNumber);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_RNG_ALGORITHM                           RNGAlgorithmList1;
  UINTN                                       RNGAlgorithmListSize;
  EFI_RNG_ALGORITHM                           *RNGAlgorithmList2;
  EFI_RNG_ALGORITHM                           *RNGAlgorithmList3;
  UINTN                                       IndexI;
  UINTN                                       IndexJ;

  RNGAlgorithmListSize = 0;

  Status = RandomNumber->GetInfo (
                           RandomNumber,
                           &RNGAlgorithmListSize,
                           &RNGAlgorithmList1
                           );

  if (Status == EFI_UNSUPPORTED || Status == EFI_DEVICE_ERROR) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gFunctionTestAssertionGuid001,
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


  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (EFI_DEVICE_ERROR == Status) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gFunctionTestAssertionGuid002,
                 L"RANDOM_NAME_PROTOCOL.GetInfo - GetInfo() returns EFI_SUCCESS with valid parameters",
                 L"%a:%d: Status - %r, RNGAlgorithmListSize - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RNGAlgorithmListSize
                 );

  RNGAlgorithmList3 = RNGAlgorithmList2;
  for (IndexI = 0; IndexI < RNGAlgorithmListSize/sizeof(EFI_RNG_ALGORITHM); IndexI++) {
  	
    AssertionType = EFI_TEST_ASSERTION_FAILED;
	for (IndexJ = 0; IndexJ < 6; IndexJ++) {
      if (SctCompareGuid (RNGAlgorithmList3, &Algos[IndexJ]) == 0) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        break;
      } 
	}

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gFunctionTestAssertionGuid003,
                   L"RANDOM_NAME_PROTOCOL.GetInfo - GetInfo() should returns valid algo",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );    

    RNGAlgorithmList3 += 1;
  }

  gtBS->FreePool (RNGAlgorithmList2);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetRNGFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_RNG_ALGORITHM                           RNGAlgorithmList1;
  EFI_RNG_ALGORITHM                           *RNGAlgorithmList2;
  EFI_RNG_ALGORITHM                           *RNGAlgorithmList3;
  UINTN                                       RNGAlgorithmListSize;
  UINTN                                       RNGValueLength;                   
  UINT8                                       RNGValue[256];
  UINTN                                       Index;
 
  RNGValueLength       = 256;
  RNGAlgorithmListSize = 0;

  Status = RandomNumber->GetInfo (
                           RandomNumber,
                           &RNGAlgorithmListSize,
                           &RNGAlgorithmList1
                           );

  if (Status == EFI_UNSUPPORTED || Status == EFI_DEVICE_ERROR) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
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

  RNGAlgorithmList3 = RNGAlgorithmList2;
  AssertionType     = EFI_TEST_ASSERTION_PASSED;  
  for (Index = 0; Index < RNGAlgorithmListSize/sizeof(EFI_RNG_ALGORITHM); Index++) {
    Status = RandomNumber->GetRNG (
                             RandomNumber,
                             RNGAlgorithmList3,
                             RNGValueLength,
                             RNGValue
  	                         );

    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else if (Status == EFI_NOT_READY || Status == EFI_DEVICE_ERROR) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
	
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gFunctionTestAssertionGuid004,
                   L"RANDOM_NAME_PROTOCOL.GetRNG - GetRNG() should returns EFI_SUCCESS with valid parameters",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    RNGAlgorithmList3 += 1;
  }

  gtBS->FreePool (RNGAlgorithmList2);
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetRNGFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 RNGValueLength;                   
  UINT8                 RNGValue[256];

  RNGValueLength = 256;

  Status = RandomNumber->GetRNG (
                           RandomNumber,
                           NULL,
                           RNGValueLength,
                           RNGValue
                           );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (Status == EFI_NOT_READY || Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gFunctionTestAssertionGuid005,
                 L"RANDOM_NUMBER_PROTOCOL.GetRNG - GetRNG() returns EFI_SUCCESS with default Algo",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

