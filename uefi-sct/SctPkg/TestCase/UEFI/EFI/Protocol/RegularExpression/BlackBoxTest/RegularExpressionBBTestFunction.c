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

    RegularExpressionBBTestFunction.c

Abstract:

    for EFI Driver Regular Expression Protocol's Basic Test

--*/

#include "RegularExpressionBBTest.h"

//
// EFI Regular Expression Syntax Type Definitions
//
#define EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED_GUID \
{ 0x5F05B20F, 0x4A56, 0xC231, {0xFA, 0x0B, 0xA7, 0xB1, 0xF1, 0x10, 0x04, 0x1D }}

#define EFI_REGEX_SYNTAX_TYPE_PERL_GUID \
{ 0x63E60A51, 0x497D, 0xD427, {0xC4, 0xA5, 0xB8, 0xAB, 0xDC, 0x3A, 0xAE, 0xB6 }}

#define EFI_REGEX_SYNTAX_TYPE_ECMA_262_GUID \
{ 0x9A473A4A, 0x4CEB, 0xB95A, {0x41, 0x5E, 0x5B, 0xA0, 0xBC, 0x63, 0x9B, 0x2E }}

EFI_GUID SyntaxTypes[3] = {
  EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED_GUID,
  EFI_REGEX_SYNTAX_TYPE_PERL_GUID,
  EFI_REGEX_SYNTAX_TYPE_ECMA_262_GUID
  };

//
// Unicode Test Data for POSIX Regular Expression Syantax Type.
//
MATCHSTRING_TEST_DATA_FIELD          MatchStringPosixTestData[] = {
  { L".", L"Match everything", TRUE, 1 },
  { L"a{3}", L"xxcaadeaaaxx", TRUE, 1 },
  { L"b[aeiou]t", L"boot", FALSE, 0 },
  { L"(^.+(capture))(.+$)", L"Three capture groups", TRUE, 4 },
  { L"(a[[:digit:]]b)", L"a0b", TRUE, 2 },
  { L"^([[:alnum:]])+$", L"abc123DEF456", TRUE, 2 },
  { L"a[[:digit:]]b", L"acb", FALSE, 0 },
  { L"^0x([[:xdigit:]]+)$", L"0x123FF", TRUE, 2 },
  { L"^[[:digit:]]+$", L"123abc", FALSE, 0 },
  { L"[[:blank:]]([[:upper:]]{8})[[:space:]]", L"REGULAR EXPRESSION PROTOCOL TEST", TRUE, 2 },
};
EFI_REGEX_CAPTURE  MatchStringPosixTestCaptures[10][4] = {
  {{ L"M", 1}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"aaa", 3}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"", 0}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"Three capture groups", 20}, { L"Three capture", 13}, { L"capture", 7}, { L" groups", 7}},
  {{ L"a0b", 3}, { L"a0b", 3}, { L"", 0}, { L"", 0}},
  {{ L"abc123DEF456", 12}, { L"6", 1}, { L"", 0}, { L"", 0}},
  {{ L"", 0}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"0x123FF", 7}, { L"123FF", 5}, { L"", 0}, { L"", 0}},
  {{ L"", 0}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L" PROTOCOL ", 10}, { L"PROTOCOL", 8}, { L"", 0}, { L"", 0}},
};

//
// Unicode Test Data for Perl Regular Expression Syantax Type.
//
MATCHSTRING_TEST_DATA_FIELD           MatchStringPerlTestData[] = {
  { L".", L"Match everything", TRUE, 1 },
  { L"\\btest(er|ing|ed|s)?\\b", L"that tested test is testing the tester's tests", TRUE, 2 },
  { L"b([aeiou])t", L"bitter lemon better lemon", TRUE, 2 },
  { L"b[aeiou]t", L"boot", FALSE, 0 },
  { L"\\b(\\S)(\\S)(\\S*)\\b", L"Matches words with at least 2 characters", TRUE, 4 },
  { L"^((1?[0-9]{1,2}|2[0-4][0-9]|25[0-5])\\.){3}(1?[0-9]{1,2}|2[0-4][0-9]|25[0-5])$", L"192.168.1.100", TRUE, 4 },
  { L"^((1?[0-9]{1,2}|2[0-4][0-9]|25[0-5])\\.){3}(1?[0-9]{1,2}|2[0-4][0-9]|25[0-5])$", L"192.168.1.500", FALSE, 0 },
  { L"^iqn\\.[0-9]{4}-[0-9]{2}\\.[^:]+(:.*)?$", L"iqn.1991-05.com.domainname:systemname-123", TRUE, 2 },
  { L"^([0-9a-fA-F]{0,4}:){2,7}(:|[0-9a-fA-F]{1,4})$", L"2001:0db8:0000:0042:0000:8a2e:0370:7334", TRUE, 3 },
  { L"^([0-9a-fA-F]{0,4}:){2,7}(:|[0-9a-fA-F]{1,4})$", L"10.0.1.1", FALSE, 0 },
};
EFI_REGEX_CAPTURE  MatchStringPerlTestCaptures[10][4] = {
  {{ L"M", 1}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"tested", 6}, { L"ed", 2}, { L"", 0}, { L"", 0}},
  {{ L"bit", 3}, { L"i", 1}, { L"", 0}, { L"", 0}},
  {{ L"", 0}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"Matches", 7}, { L"M", 1}, { L"a", 1}, { L"tches", 5}},
  {{ L"192.168.1.100", 13}, { L"1.", 2}, { L"1", 1}, { L"100", 3}},
  {{ L"", 0}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"iqn.1991-05.com.domainname:systemname-123", 41}, { L":systemname-123", 15}, { L"", 0}, { L"", 0}},
  {{ L"2001:0db8:0000:0042:0000:8a2e:0370:7334", 39}, { L"0370:", 5}, { L"7334", 4}, { L"", 0}},
  {{ L"", 0}, { L"", 0}, { L"", 0}, { L"", 0}},
};

//
// Unicode Test Data for Ecma Regular Expression Syantax Type.
//
MATCHSTRING_TEST_DATA_FIELD  MatchStringEcmaTestData[] ={
  { L"\\b(\\S)(\\S)(\\S*)\\b", L"This regex matches words with at least 2 characters", TRUE, 4 },
  { L"(^.+(capture))(.+$)", L"Three capture groups", TRUE, 4 },
  { L"b[aeiou]t", L"boot", FALSE, 0 },
  { L"^abcdef$", L"abcdefgh", FALSE, 0 },
};
EFI_REGEX_CAPTURE  MatchStringEcmaTestCaptures[4][4] = {
  {{ L"This", 4}, { L"T", 1}, { L"h", 1}, { L"is", 2}},
  {{ L"Three capture groups", 20}, { L"Three capture", 13}, { L"capture", 7}, { L" groups", 7}},
  {{ L"", 1}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"", 1}, { L"", 0}, { L"", 0}, { L"", 0}},
};

//
// Test Data for all other types of Regular Expression Syantax Types.
//
MATCHSTRING_TEST_DATA_FIELD  MatchStringGenericTestData[] ={
  { L"Protocol", L"Regular Expression Protocol Test", TRUE, 1 },
  { L"Protocol", L"Regular Expression Test", FALSE, 0 },
};
EFI_REGEX_CAPTURE  MatchStringGenericTestCaptures[2][4] = {
  {{ L"Protocol", 8}, { L"", 0}, { L"", 0}, { L"", 0}},
  {{ L"", 1}, { L"", 0}, { L"", 0}, { L"", 0}},
};


/**
 *  @brief Entrypoint for GetInfo() Function Test.
 *         1 checkpoint will be tested.
 *  @param This A pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
EFIAPI
BBTestRegExGetInfoFunctionTest (
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
  //  Call GetInfo() with valid parameters.
  //
  BBTestRegExGetInfoFunctionTestCheckpoint1 (StandardLib, RegularExpression);
  
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for MatchString() Function Test.
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
EFI_STATUS
EFIAPI
BBTestMatchStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression;
  EFI_STATUS                            Status;
  
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
  //  Call MatchString() with supported SyntaxTypes.
  //
  BBTestMatchStringFunctionTestCheckpoint1 (StandardLib, RegularExpression);
  
  //
  //  Call MatchString() with NULL SyntaxType.
  //
  BBTestMatchStringFunctionTestCheckpoint2 (StandardLib, RegularExpression);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRegExGetInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  )
{
  EFI_STATUS                               Status;
  EFI_TEST_ASSERTION                       AssertionType;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList1 = NULL;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList2;
  UINTN                                    SyntaxTypeListSize = 0;
  UINTN                                    InputListSize = 0;
  
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
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() is not supported or EFI_DEVICE_ERROR.",
                   L"%a:%d: Status - %r.",
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
                   L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() did not return EFI_BUFFER_TOO_SMALL or ListSize wrong.",
                   L"%a:%d: Status - %r, SyntaxTypeListSize - %d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   SyntaxTypeListSize
                 );
    return Status;
  }
  
  //Allocate buffer with obtained size SyntaxTypeListSize for holding RegExSyntaxTypes.
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
  
  InputListSize = SyntaxTypeListSize;
  
  Status = RegularExpression->GetInfo (
                                RegularExpression,
                                &SyntaxTypeListSize,
                                RegExSyntaxTypeList2
                              );
  if (    (EFI_SUCCESS == Status)
       && (SyntaxTypeListSize % sizeof(EFI_REGEX_SYNTAX_TYPE) == 0)
       && (SyntaxTypeListSize == InputListSize))
  {
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (    (Status == EFI_UNSUPPORTED)
              || (Status == EFI_DEVICE_ERROR))
  {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegExFunctionTestAssertionGuid001,
                 L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() returns EFI_SUCCESS with valid parameters.",
                 L"%a:%d: Status - %r, SyntaxTypeListSize - %d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 SyntaxTypeListSize
               );
  
  gtBS->FreePool (RegExSyntaxTypeList2);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestMatchStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  )
{
  EFI_STATUS                               Status;
  EFI_STATUS                               FreePoolStatus1;
  EFI_STATUS                               FreePoolStatus2;
  EFI_TEST_ASSERTION                       AssertionType;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList1 = NULL;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList2;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList3;
  MATCHSTRING_TEST_DATA_FIELD              *MatchStringTestData = NULL;
  EFI_REGEX_CAPTURE                        *Captures;
  EFI_REGEX_CAPTURE                        (*ExpectedCaptures)[4];
  UINTN                                    SyntaxTypeListSize = 0;
  UINTN                                    CapturesCount = 0;
  UINTN                                    TestDataSize = 0;
  UINTN                                    CaptureMatchResult;
  UINTN                                    IndexI;
  UINTN                                    IndexJ;
  UINTN                                    IndexK;
  BOOLEAN                                  Result = FALSE;

  //Call REGULAR_EXPRESSION_PROTOCOL.GetInfo() to get actual SyntaxTypeListSize
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
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() is not supported or EFI_DEVICE_ERROR.",
                   L"%a:%d: Status - %r.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    return Status;
  }
  if (    (Status != EFI_BUFFER_TOO_SMALL )
       || ((SyntaxTypeListSize % sizeof(EFI_REGEX_SYNTAX_TYPE)) != 0)
       || (SyntaxTypeListSize == 0))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"Can't get the RegExSyntaxTypeListSize.",
                   L"%a:%d: Status - %r.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
   return Status;
  }
  
  //
  //Allocate a list buffer for holding RegExSyntaxTypes.
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
  //Test MatchString() for all supported syntax types with Unicode test data.
  //
  
  RegExSyntaxTypeList3 = RegExSyntaxTypeList2;
  for (IndexI = 0; IndexI < (SyntaxTypeListSize / sizeof(EFI_REGEX_SYNTAX_TYPE)); IndexI++) {
    if (SctCompareGuid(RegExSyntaxTypeList3, &SyntaxTypes[0]) == 0) {
      MatchStringTestData = MatchStringPosixTestData;
      ExpectedCaptures = (EFI_REGEX_CAPTURE (*)[4])&MatchStringPosixTestCaptures;
      TestDataSize = sizeof(MatchStringPosixTestData) / sizeof(MATCHSTRING_TEST_DATA_FIELD);
    
    } else if (SctCompareGuid(RegExSyntaxTypeList3, &SyntaxTypes[1]) == 0) {
      MatchStringTestData = MatchStringPerlTestData;
      ExpectedCaptures = (EFI_REGEX_CAPTURE (*)[4])&MatchStringPerlTestCaptures;
      TestDataSize = sizeof(MatchStringPerlTestData) / sizeof(MATCHSTRING_TEST_DATA_FIELD);
    
    } else if (SctCompareGuid(RegExSyntaxTypeList3, &SyntaxTypes[2]) == 0) {
      MatchStringTestData = MatchStringEcmaTestData;
      ExpectedCaptures = (EFI_REGEX_CAPTURE (*)[4])&MatchStringEcmaTestCaptures;
      TestDataSize = sizeof(MatchStringEcmaTestData) / sizeof(MATCHSTRING_TEST_DATA_FIELD);
    
    } else {
      MatchStringTestData = MatchStringGenericTestData;
      ExpectedCaptures = (EFI_REGEX_CAPTURE (*)[4])&MatchStringGenericTestCaptures;
      TestDataSize = sizeof(MatchStringGenericTestData) / sizeof(MATCHSTRING_TEST_DATA_FIELD);
    }
    for (IndexJ = 0; IndexJ < TestDataSize; IndexJ++) {
      FreePoolStatus1 = EFI_SUCCESS;
      FreePoolStatus2 = EFI_SUCCESS;    	
      AssertionType      = EFI_TEST_ASSERTION_PASSED;
      CaptureMatchResult = 1;
      Status = RegularExpression->MatchString (
                                    RegularExpression,
                                    MatchStringTestData[IndexJ].String,
                                    MatchStringTestData[IndexJ].Pattern,
                                    RegExSyntaxTypeList3,
                                    &Result,
                                    &Captures,
                                    &CapturesCount
                                  );
      if (    (Result == MatchStringTestData[IndexJ].Result)
           && (Status == EFI_SUCCESS))
      {
        if (Result == 1) {  //If successful match, compare the captures.
          if (CapturesCount == MatchStringTestData[IndexJ].CapturesCount) {
            for (IndexK = 0; IndexK < CapturesCount; IndexK++) {
              CaptureMatchResult = SctCompareMem (
                                     (CHAR16 *)Captures[IndexK].CapturePtr,
                                     (CHAR16 *)ExpectedCaptures[IndexJ][IndexK].CapturePtr,
                                     ExpectedCaptures[IndexJ][IndexK].Length
                                   );
              if (    (CaptureMatchResult != 0)
                   || (Captures[IndexK].Length != ExpectedCaptures[IndexJ][IndexK].Length))
              {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
                CaptureMatchResult = 0;
                break;
              }

              FreePoolStatus1 = gtBS->FreePool ((CHAR16 *)Captures[IndexK].CapturePtr);
              if (EFI_ERROR (FreePoolStatus1)) { //If unable to free the CapturePtr, mark test as FAIL.
                AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
            }
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            CaptureMatchResult = 2;
          }
          FreePoolStatus2 = gtBS->FreePool (Captures);
          if (EFI_ERROR (FreePoolStatus2)) { //If unable to free the Captures, mark test as FAIL.
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else { //If the string doesn't match, there's no captures returned. Hence initialize the status to EFI_SUCCESS
          FreePoolStatus1 = EFI_SUCCESS;
          FreePoolStatus2 = EFI_SUCCESS;
        }
      } else if (    (Status == EFI_NOT_READY)
                  || (Status == EFI_DEVICE_ERROR))
      {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (    (FreePoolStatus1 == EFI_SUCCESS)
           && (FreePoolStatus2 == EFI_SUCCESS))
      {
        StandardLib->RecordAssertion (
                      StandardLib,
                      AssertionType,
                      gRegExFunctionTestAssertionGuid002,
                      L"REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_SUCCESS with Unicode String and Pattern.",
                      L"%a:%d: '%s'=~'%s', Status: %r, Result=%d Expected=%d, CaptureCount=%d Expected=%d, SyntaxType: %g.",
                      __FILE__,
                      (UINTN)__LINE__,
                      MatchStringTestData[IndexJ].Pattern,
                      MatchStringTestData[IndexJ].String,
                      Status,
                      Result,
                      MatchStringTestData[IndexJ].Result,
                      CapturesCount,
                      MatchStringTestData[IndexJ].CapturesCount,
                      *RegExSyntaxTypeList3
                    );
       } else { //If unable to free the Captures or CapturePtr, mark test as FAIL.
           StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gRegExFunctionTestAssertionGuid002,
                       L"REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_SUCCESS with Unicode String and Pattern.",
                       L"%a:%d: Unable to free Captures or CapturePtr.",
                       __FILE__,
                       (UINTN)__LINE__
                     );
       }
    }
    RegExSyntaxTypeList3 += 1;
  }
  gtBS->FreePool (RegExSyntaxTypeList2);
  return EFI_SUCCESS;
}

//
//REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_SUCCESS with default SyntaxType.
EFI_STATUS
EFIAPI
BBTestMatchStringFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  )
{
  EFI_STATUS                               Status1;
  EFI_STATUS                               Status2;
  EFI_TEST_ASSERTION                       AssertionType;
  BOOLEAN                                  Result1;
  BOOLEAN                                  Result2;
  UINTN                                    CapturesCount1;
  UINTN                                    CapturesCount2;
  UINTN                                    SyntaxTypeListSize = 0;
  EFI_REGEX_CAPTURE                        *Captures1;
  EFI_REGEX_CAPTURE                        *Captures2;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList1 = NULL;
  EFI_REGEX_SYNTAX_TYPE                    *RegExSyntaxTypeList2;
  
  //
  //Call REGULAR_EXPRESSION_PROTOCOL.GetInfo() to get supported SyntaxTypes.
  //
  Status1 = RegularExpression->GetInfo (
                                RegularExpression,
                                &SyntaxTypeListSize,
                                RegExSyntaxTypeList1
                              );
  if (    (Status1 == EFI_UNSUPPORTED)
       || (Status1 == EFI_DEVICE_ERROR))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"REGULAR_EXPRESSION_PROTOCOL.GetInfo() is not supported or EFI_DEVICE_ERROR.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                 );
    return Status1;
  }
  if (    (EFI_BUFFER_TOO_SMALL != Status1)
       || (SyntaxTypeListSize % sizeof(EFI_REGEX_SYNTAX_TYPE) != 0)
       || (SyntaxTypeListSize == 0))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get the valid SyntaxTypeListSize.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                 );
   return Status1;
  }
  
  //
  //Allocate buffer for holding RegExSyntaxTypeList and call GetInfo() to get SyntaxTypes.
  //
  Status1 = gtBS->AllocatePool (
                   EfiBootServicesData,
                   SyntaxTypeListSize,
                   (VOID **)&RegExSyntaxTypeList2
                 );
  if (EFI_ERROR (Status1)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Allocate Pool failure.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                 );
    return Status1;
  }
  
  Status1 = RegularExpression->GetInfo (
                                RegularExpression,
                                &SyntaxTypeListSize,
                                RegExSyntaxTypeList2
                              );
  if (EFI_ERROR (Status1)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get the valid SyntaxTypes.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                 );
    gtBS->FreePool (RegExSyntaxTypeList2);
    return Status1;
  }

  //
  //Call MatchString with RegExSyntaxTypeList=NULL.
  //  
  Status1 = RegularExpression->MatchString (
                                RegularExpression,
                                MatchStringGenericTestData[0].String,
                                MatchStringGenericTestData[0].Pattern,
                                NULL,
                                &Result1,
                                &Captures1,
                                &CapturesCount1
                              );
  
  //
  //Call MatchString with RegExSyntaxTypeList = First syntax type from the supported types.
  //  
  Status2 = RegularExpression->MatchString (
                                RegularExpression,
                                MatchStringGenericTestData[0].String,
                                MatchStringGenericTestData[0].Pattern,
                                RegExSyntaxTypeList2,
                                &Result2,
                                &Captures2,
                                &CapturesCount2
                              );

  if (    (Result1 == MatchStringGenericTestData[0].Result)
       && (Result2 == Result1)
       && (CapturesCount1 == MatchStringGenericTestData[0].CapturesCount)
       && (CapturesCount2 == CapturesCount1)
       && (Status1 == EFI_SUCCESS)
       && (Status2 == EFI_SUCCESS))
  {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (    (Status1 == EFI_NOT_READY)
              || (Status2 == EFI_NOT_READY)
              || (Status1 == EFI_DEVICE_ERROR)
              || (Status2 == EFI_DEVICE_ERROR))
  {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegExFunctionTestAssertionGuid003,
                 L"REGULAR_EXPRESSION_PROTOCOL.MatchString() returns EFI_SUCCESS with default SyntaxType.",
                 L"%a:%d: '%s'=~'%s', Status: %r, Result=%d Expected=%d, CaptureCount=%d Expected=%d, SyntaxType: %g.",
                 __FILE__,
                 (UINTN)__LINE__,
                 MatchStringGenericTestData[0].Pattern,
                 MatchStringGenericTestData[0].String,
                 Status1,
                 Result1,
                 MatchStringGenericTestData[0].Result,
                 CapturesCount1,
                 MatchStringGenericTestData[0].CapturesCount,
                 *RegExSyntaxTypeList2
               );
  
  gtBS->FreePool (RegExSyntaxTypeList2);
  return EFI_SUCCESS;
}

