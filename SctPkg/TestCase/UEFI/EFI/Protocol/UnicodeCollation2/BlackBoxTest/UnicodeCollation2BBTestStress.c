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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  UnicodeCollationBBTestStress.c

Abstract:

  Extensive Test Cases of Unicode Collation Protocol

--*/


#include "SctLib.h"
#include "UnicodeCollation2BBTestMain.h"


/**
 *  Entrypoint for EFI_UNICODE_COLLATOIN_PROTOCOL Stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.1
//
EFI_STATUS
BBTestStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_UNICODE_COLLATION2_PROTOCOL       *UnicodeCollation;

  UINTN                                Index;
  INTN                                 IResult;
  BOOLEAN                              BResult;
  EFI_TEST_ASSERTION                   AssertionType;

  CHAR16                               *S1;
  CHAR16                               *S2;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  UnicodeCollation = (EFI_UNICODE_COLLATION2_PROTOCOL *)ClientInterface;

  //
  // Allocate buffer for test data
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, sizeof (CHAR16) * (MAX_SIZE_OF_STRESS_STRING + 1), (VOID **)&S1);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, sizeof (CHAR16) * (MAX_SIZE_OF_STRESS_STRING + 1), (VOID *)&S2);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto FreeBuffer;
  }

  //
  // Assertion Points 4.2.1.2.1
  // Stress test of StriColl()
  //

  //
  // Initialize test data
  //
  for (Index = 0; Index < MAX_SIZE_OF_STRESS_STRING; Index++) {
    S1[Index] = (CHAR16)(Index + 1);
    S2[Index] = S1[Index];
  }
  S1[MAX_SIZE_OF_STRESS_STRING] = 0;
  S2[MAX_SIZE_OF_STRESS_STRING] = S1[MAX_SIZE_OF_STRESS_STRING];

  //
  // Call StriColl() with same large-length Unicode string S1 & S2
  //
  IResult = UnicodeCollation->StriColl (
                                UnicodeCollation,
                                S1,
                                S2
                                );

  if (IResult == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnicodeCollationCombinationTestAssertionGuid001,
                 L"EFI_UNICODE_COLLATION_PROTOCOL.StriColl - Stress verification of StriColl interface with same Unicode strings",
                 L"%a:%d,String Length = %d, Result = %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 MAX_SIZE_OF_STRESS_STRING,
                 IResult
                 );

  //
  // Call StriColl() with different large-length Unicode string S1 & S2
  //
  S2[MAX_SIZE_OF_STRESS_STRING - 1] = (CHAR16)(S1[MAX_SIZE_OF_STRESS_STRING - 1] - 1);

  IResult = UnicodeCollation->StriColl (
                                UnicodeCollation,
                                S1,
                                S2
                                );

  if (IResult == (S1[MAX_SIZE_OF_STRESS_STRING - 1] - S2[MAX_SIZE_OF_STRESS_STRING - 1])) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnicodeCollationCombinationTestAssertionGuid002,
                 L"EFI_UNICODE_COLLATION_PROTOCOL.StriColl - Stress verification of StriColl interface with two different string",
                 L"%a:%d: String Length = %d, Result = %d, Expected = %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 MAX_SIZE_OF_STRESS_STRING,
                 IResult,
                 S1[MAX_SIZE_OF_STRESS_STRING - 1] - S2[MAX_SIZE_OF_STRESS_STRING - 1]
                 );

  //
  // Assertion Point 4.2.1.2.2
  // Stress test of MetaiMatch()
  //
  for (Index = 0; Index < MAX_SIZE_OF_STRESS_STRING; Index++) {
    S1[Index] = 'a';
  }
  S1[MAX_SIZE_OF_STRESS_STRING] = 0;
  S1[MAX_SIZE_OF_STRESS_STRING - 1] = 'b';
  S1[0] = 'c';

  BResult = UnicodeCollation->MetaiMatch (
                                UnicodeCollation,
                                S1,
                                L"c*b"
                                );


  if (BResult == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnicodeCollationCombinationTestAssertionGuid003,
                 L"EFI_UNICODE_COLLATION_PROTOCOL.MetaiMatch - Stress verification of MetaiMatch interface with Unicode strings matching pattern",
                 L"%a:%d: String Length = %d, Result = %d,Pattern = '%s'",
                 __FILE__,
                 (UINTN)__LINE__,
                 MAX_SIZE_OF_STRESS_STRING,
                 BResult,
                 L"c*b"
                 );

  BResult = UnicodeCollation->MetaiMatch (
                                UnicodeCollation,
                                S1,
                                L"c*c"
                                );

  if (BResult == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnicodeCollationCombinationTestAssertionGuid004,
                 L"EFI_UNICODE_COLLATION_PROTOCOL.MetaiMatch - Stress verification of MetaiMatch interface with Unicode strings matching pattern",
                 L"%a:%d: String Length = %d, Result = %d,Pattern = '%s'",
                 __FILE__,
                 (UINTN)__LINE__,
                 MAX_SIZE_OF_STRESS_STRING,
                 BResult,
                 L"c*c"
                 );

  //
  // Assertion Point 4.2.1.2.3
  // Stress test of SctStrLwr ()
  //

  //
  // Initialize S1 & S2 as same Unicode string
  //
  for (Index = 0; Index < MAX_SIZE_OF_STRESS_STRING; Index++) {
    S2[Index] = S1[Index];
  }
  S1[MAX_SIZE_OF_STRESS_STRING] = 0;
  S2[MAX_SIZE_OF_STRESS_STRING] = S1[MAX_SIZE_OF_STRESS_STRING];

  UnicodeCollation->StrLwr (UnicodeCollation, S1);

  if (CheckStrLwr (S2, S1) == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnicodeCollationCombinationTestAssertionGuid005,
                 L"EFI_UNICODE_COLLATION_PROTOCOL.StrLwr -Stress verification of StrLwr interface",
                 L"%a:%d: Stress verification of StrLwr interface",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  //
  // Assertion Point 4.2.1.2.4
  // Stress test of SctStrUpr ()
  //

  //
  // Initialize S1 & S2 as same Unicode string
  //
  for (Index = 0; Index < MAX_SIZE_OF_STRESS_STRING; Index++) {
    S2[Index] = S1[Index];
  }
  S1[MAX_SIZE_OF_STRESS_STRING] = 0;
  S2[MAX_SIZE_OF_STRESS_STRING] = S1[MAX_SIZE_OF_STRESS_STRING];


  UnicodeCollation->StrUpr (UnicodeCollation, S1);

  if (CheckStrUpr (S2, S1) == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnicodeCollationCombinationTestAssertionGuid006,
                 L"EFI_UNICODE_COLLATION_PROTOCOL.StrUpr -Stress verification of StrUpr interface",
                 L"%a:%d: tress verification of StrUpr interface ",
                 __FILE__,
                 (UINTN)__LINE__
                 );

FreeBuffer:
  if (S1 != NULL) {
    Status = gtBS->FreePool (S1);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.FreePool - Free pool",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }
  }

  if (S2 != NULL) {
    Status = gtBS->FreePool (S2);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.FreePool - Free pool",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }
  }

  return EFI_SUCCESS;
}
