/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  (C) Copyright 2016 Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    RegularExpressionBBTestConformance.c

Abstract:

    for EFI Driver Regular Expression Protocol's Conformance Test

--*/

#include "RegularExpressionBBTest.h"

#define UNSUPPORTED_SYNTAX_TYPE_GUID    \
  { 0x4d78ffd2, 0xceaa, 0x4b53, {0x98, 0x68, 0xb0, 0x57, 0x6f, 0xfc, 0x88, 0x9d }}

EFI_GUID UnsupportedSyntaxTypeGuid = UNSUPPORTED_SYNTAX_TYPE_GUID;

//
// Test Data for all other types of Regular Expression Syantax Types.
//
MATCHSTRING_TEST_DATA_FIELD           MatchStringSampleTestData[] ={
  { L"Match", L"Match a specific string", TRUE, 1 },
};

/**
 *  @brief Entrypoint for GetInfo() Conformance Test.
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression;

  //
  // init
  //
  RegularExpression = (EFI_REGULAR_EXPRESSION_PROTOCOL*)ClientInterface;
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  //  Call GetInfo() with invalid RegExSyntaxTypeList.
  //
  BBTestGetInfoConformanceTestCheckpoint1 (StandardLib, RegularExpression);
  
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for MatchString() Conformance Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
EFIAPI
BBTestMatchStringConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression;
  
  //
  // init
  //
  RegularExpression = (EFI_REGULAR_EXPRESSION_PROTOCOL*)ClientInterface;
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  //  Call MatchString() with invalid parameters.
  //
  BBTestMatchStringConformanceTestCheckpoint1 (StandardLib, RegularExpression);
  
  //
  //  Call MatchString() with unsupported SyntaxType.
  //
  BBTestMatchStringConformanceTestCheckpoint2 (StandardLib, RegularExpression);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  )
{
  EFI_STATUS                               Status;
  EFI_TEST_ASSERTION                       AssertionType;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList = NULL;
  UINTN                                    SyntaxTypeListSize;
  
  SyntaxTypeListSize = 0;
  //
  // REGULAR_EXPRESSION_PROTOCOL.GetInfo with SyntaxTypeListSize too small to hold the result.
  //
  Status = RegularExpression->GetInfo (
                                RegularExpression,
                                &SyntaxTypeListSize,
                                RegExSyntaxTypeList
                              );
  if (    (Status == EFI_UNSUPPORTED)
       || (Status == EFI_DEVICE_ERROR))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() is not supported or EFI_DEVICE_ERROR.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    return Status;
  }
  
  if (    (EFI_BUFFER_TOO_SMALL == Status)
       && (SyntaxTypeListSize % sizeof(EFI_REGEX_SYNTAX_TYPE) == 0)
       && (SyntaxTypeListSize != 0))
  {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegExConformanceTestAssertionGuid001,
                 L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() returns EFI_BUFFER_TOO_SMALL when SyntaxTypeListSize too small to hold the result.",
                 L"%a:%d: Status - %r, SyntaxTypeListSize - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 SyntaxTypeListSize
               );
  
  //
  // REGULAR_EXPRESSION_PROTOCOL.GetInfo() with SyntaxTypeListSize = NULL.
  //  
  Status = RegularExpression->GetInfo (
                                RegularExpression,
                                NULL,
                                RegExSyntaxTypeList
                              );
  if (    (Status == EFI_UNSUPPORTED)
       || (Status == EFI_DEVICE_ERROR))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() is not supported or EFI_DEVICE_ERROR",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    return Status;
  }
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegExConformanceTestAssertionGuid002,
                 L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() returns EFI_INVALID_PARAMETER when SyntaxTypeListSize is NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
               );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestMatchStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  )
{
  EFI_STATUS                               Status;
  EFI_TEST_ASSERTION                       AssertionType;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList1 = NULL;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList2;
  UINTN                                    SyntaxTypeListSize = 0;
  BOOLEAN                                  Result;
  UINTN                                    CapturesCount;
  
  //
  //Call GetInfo() to get SyntaxTypeListSize and then call again to get supported SyntaxTypes.
  //
  Status = RegularExpression->GetInfo (
                                RegularExpression,
                                &SyntaxTypeListSize,
                                RegExSyntaxTypeList1
                              );
  if (    (Status == EFI_UNSUPPORTED)
       || (Status == EFI_DEVICE_ERROR))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() is not supported or EFI_DEVICE_ERROR.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    return Status;
  }
  
  if (    (EFI_BUFFER_TOO_SMALL != Status)
       || (SyntaxTypeListSize % sizeof(EFI_REGEX_SYNTAX_TYPE) != 0)
       || (SyntaxTypeListSize == 0))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get the correct SyntaxTypeListSize.",
                   L"%a:%d: Status - %r, SyntaxTypeListSize - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   SyntaxTypeListSize
                 );
    return Status;
  }
  
  //
  //Allocate buffer with obtained size SyntaxTypeListSize for holding RegExSyntaxTypeList.
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   SyntaxTypeListSize,
                   (VOID **) &RegExSyntaxTypeList2
                 );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Allocate Pool failure.",
                   L"%a:%d: Status - %r.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    return Status;
  }
  
  //
  //Call GetInfo() to get the supported SyntaxTypes. This will be used in MatchString() tests below.
  //
  Status = RegularExpression->GetInfo (
                                RegularExpression,
                                &SyntaxTypeListSize,
                                RegExSyntaxTypeList2
                              );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get the valid SyntaxTypes.",
                   L"%a:%d: Status - %r.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    gtBS->FreePool (RegExSyntaxTypeList2);
    return Status;
  }
  
  //
  //REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_INVALID_PARAMETER when String is NULL.
  //
  Status = RegularExpression->MatchString (
                                RegularExpression,
                                NULL,
                                MatchStringSampleTestData[0].Pattern,
                                RegExSyntaxTypeList2,
                                &Result,
                                NULL,
                                &CapturesCount
                              );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegExConformanceTestAssertionGuid003,
                 L"REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_INVALID_PARAMETER when String is NULL.",
                 L"%a:%d: Status - %r.",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
               );
  
  //
  //REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_INVALID_PARAMETER when Pattern is NULL.
  //
  Status = RegularExpression->MatchString (
                                RegularExpression,
                                MatchStringSampleTestData[0].String,
                                NULL,
                                RegExSyntaxTypeList2,
                                &Result,
                                NULL,
                                &CapturesCount
                              );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegExConformanceTestAssertionGuid004,
                 L"REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_INVALID_PARAMETER when Pattern is NULL.",
                 L"%a:%d: Status - %r.",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
               );
  
  //
  //REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_INVALID_PARAMETER when Result is NULL.
  //
  Status = RegularExpression->MatchString (
                                RegularExpression,
                                MatchStringSampleTestData[0].String,
                                MatchStringSampleTestData[0].Pattern,
                                RegExSyntaxTypeList2,
                                NULL,
                                NULL,
                                &CapturesCount
                              );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegExConformanceTestAssertionGuid005,
                 L"REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_INVALID_PARAMETER when Result is NULL.",
                 L"%a:%d: Status - %r.",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
               );
  
  //
  //REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_INVALID_PARAMETER when CapturesCount is NULL
  //
  Status = RegularExpression->MatchString (
                                RegularExpression,
                                MatchStringSampleTestData[0].String,
                                MatchStringSampleTestData[0].Pattern,
                                RegExSyntaxTypeList2,
                                &Result,
                                NULL,
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
                 gRegExConformanceTestAssertionGuid006,
                 L"REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_INVALID_PARAMETER when CapturesCount is NULL.",
                 L"%a:%d: Status - %r.",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
               );
  
  gtBS->FreePool (RegExSyntaxTypeList2);
  return EFI_SUCCESS;
}

//
//REGULAR_EXPRESSION_PROTOCOL.MatchString() with unsupported SyntaxType should return EFI_UNSUPPORTED.
//
EFI_STATUS
EFIAPI
BBTestMatchStringConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  )
{
  EFI_STATUS                    Status;
  EFI_TEST_ASSERTION            AssertionType;
  BOOLEAN                       Result;
  UINTN                         CapturesCount;
  
  Status = RegularExpression->MatchString (
                                RegularExpression,
                                MatchStringSampleTestData[0].String,
                                MatchStringSampleTestData[0].Pattern,
                                &UnsupportedSyntaxTypeGuid,
                                &Result,
                                NULL,
                                &CapturesCount
                              );
  if (EFI_UNSUPPORTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegExConformanceTestAssertionGuid007,
                 L"REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_UNSUPPORTED with unsupported SyntaxType.",
                 L"%a:%d: Status - %r.",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
               );
  
  return EFI_SUCCESS;
}
