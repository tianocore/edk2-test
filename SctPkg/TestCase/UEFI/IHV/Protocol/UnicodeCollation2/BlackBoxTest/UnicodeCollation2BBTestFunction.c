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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  UnicodeCollation2BBTestFunction.c

Abstract:

  Interface Function Test Cases of Unicode Collation2 Protocol

--*/


#include "SctLib.h"
#include "UnicodeCollation2BBTestMain.h"


/**
 *  Entrypoint for EFI_UNICODE_COLLATOIN2_PROTOCOL.StriColl() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.1
//
EFI_STATUS
BBTestStriCollFunctionAutoTest (
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
  INTN                                 Result;
  EFI_TEST_ASSERTION                   AssertionType;

  //
  // Test Data
  //
  STRICOLL_TEST_DATA_FIELD             TestData[] ={
     {
       L"",
       L"",
       STRING_COMPARE_EQUAL
     },
     {
       L"\x01\x02\x11\x12\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5Ax61\x62\x7D\x7E",
       L"\x01\x02\x11\x12\x21\x22\x31\x32\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7Ax61\x62\x7D\x7E",
       STRING_COMPARE_EQUAL
     },
     {
       L"\x01\x02\x11\x12\x21\x22\x31\x32\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7Ax61\x62\x7D\x7E",
       L"\x01\x02\x11\x12\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5Ax61\x62\x7D\x7E",
       STRING_COMPARE_EQUAL
     },
     {
       L"\x01\x02\x11\x12\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x61\x62\x7D\x7E",
       L"\x01\x02\x11\x12\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x61\x62\x7D\x7D",
       STRING_COMPARE_MORE
     },
     {
       L"\x01\x02\x11\x12\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x61\x62\x7D\x7E",
       L"\x01\x02\x11\x12\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x61\x62\x7D\x7F",
       STRING_COMPARE_LESS
     },
     {
       L"\x01",
       L"",
       STRING_COMPARE_MORE
     },
     {
       L"",
       L"\x01\x02",
       STRING_COMPARE_LESS
     },
  };



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
  for (Index = 0; Index < sizeof (TestData) / sizeof (STRICOLL_TEST_DATA_FIELD); Index++) {
    //
    // For each test data, test the StriColl functionality.
    //
    Result = UnicodeCollation->StriColl (
                                 UnicodeCollation,
                                 TestData[Index].S1,
                                 TestData[Index].S2
                                 );

    if ((Result < 0) && (TestData[Index].Result < 0) ||
            (Result == 0) && (TestData[Index].Result == 0) ||
            (Result > 0) && (TestData[Index].Result > 0)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid001,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StriColl - Verification of StriColl interface",
                   L"%a:%d: S1='%s', S2='%s', Result=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestData[Index].S1,
                   TestData[Index].S2,
                   Result
                   );
  };

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_UNICODE_COLLATOIN_PROTOCOL.MetaiMatch() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.2
//
EFI_STATUS
BBTestMetaiMatchFunctionAutoTest (
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
  BOOLEAN                              Result;
  EFI_TEST_ASSERTION                   AssertionType;

  //
  // Test Data
  //
  METAIMATCH_TEST_DATA_FIELD           TestData[] ={
     {L"", L"\x30\x50zz\x40\x20", FALSE},
     {L"\x30\x50*\x40\x20", L"", FALSE},
     {L"", L"", TRUE},
     {L"\x30\x50*\x40\x20", L"\x30\x50zz\x40\x20", TRUE},
     {L"\x30\x50*\x40\x20", L"\x30\x50\x30\x20", FALSE},

     {L"\x30\x50?\x40\x20", L"\x30\x50H\x40\x20", TRUE},
     {L"\x30\x50?\x40\x20", L"\x30\x50\x40\x20", FALSE},

     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50Z\x40\x20", TRUE},
     {L"\x30\x50[abcdZyxw!)(@#*]\x40\x20", L"\x30\x50Z\x40\x20", TRUE},
     {L"\x30\x50[abcdZyxw!)(@#*]\x40\x20", L"\x30\x50z\x40\x20", TRUE},
     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50z\x40\x20", TRUE},
     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50W\x40\x20", TRUE},
     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50w\x40\x20", TRUE},
     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50@\x40\x20", TRUE},
     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50*\x40\x20", TRUE},
     {L"\x30\x50[abcdzyxw!)(@#*?]\x40\x20", L"\x30\x50?\x40\x20", TRUE},
     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50g\x40\x20", FALSE},
     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50q\x40\x20", FALSE},
     {L"\x30\x50[abcdzyxw!)(@#*]\x40\x20", L"\x30\x50W\x40\x20", TRUE},

//
// Index = 19
//
     {L"[a-z]", L"b", TRUE},
     {L"[a-z]", L"B", TRUE},
     {L"[bcd]", L"B", TRUE},
     {L"\x30\x50[R-Z]\x40\x20", L"\x30\x50r\x40\x20", TRUE},
     {L"\x30\x50[R-Z]\x40\x20", L"\x30\x50R\x40\x20", TRUE},
     {L"\x30\x50[R-Z]\x40\x20", L"\x30\x50Z\x40\x20", TRUE},
     {L"\x30\x50[R-Z]\x40\x20", L"\x30\x50z\x40\x20", TRUE},
     {L"\x30\x50[R-Z]\x40\x20", L"\x30\x50Y\x40\x20", TRUE},
     {L"\x30\x50[R-Z]\x40\x20", L"\x30\x50s\x40\x20", TRUE},
     {L"\x30\x50[R-Z]\x40\x20", L"\x30\x50k\x40\x20", FALSE},
     {L"\x30\x50[R-Z]\x40\x20", L"\x30\x50K\x40\x20", FALSE},


//
// Index = 30
//

     {L"\x30\x50[\x20-\x25]\x40\x20", L"\x30\x50\x20\x40\x20", TRUE},
     {L"\x30\x50[\x20-\x25]\x40\x20", L"\x30\x50\x25\x40\x20", TRUE},
     {L"\x30\x50[\x20-\x25]\x40\x20", L"\x30\x50\x22\x40\x20", TRUE},
     {L"\x30\x50[\x20-\x25]\x40\x20", L"\x30\x50\x10\x40\x20", FALSE},

  };



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
  for (Index = 0; Index < sizeof (TestData) / sizeof (METAIMATCH_TEST_DATA_FIELD); Index ++) {
    //
    // For each test data, test the MetaiMatch functionality.
    //
    Result = UnicodeCollation->MetaiMatch (
                                 UnicodeCollation,
                                 TestData[Index].String,
                                 TestData[Index].Pattern
                                 );

    if (Result == TestData[Index].Result) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid002,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.MetaiMatch - Verification of MetaiMatch interface",
                   L"%a:%d: Index = %d, String='%s', Pattern='%s', Result=%d, Expected Result=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index,
                   TestData[Index].String,
                   TestData[Index].Pattern,
                   Result,
                   TestData[Index].Result
                   );
  };

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_UNICODE_COLLATOIN2_PROTOCOL.StrLwr () Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.3
//
EFI_STATUS
BBTestStrLwrFunctionAutoTest (
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

  EFI_TEST_ASSERTION                   AssertionType;

  //
  // Test Data
  //
  CHAR16                               *TestData[] ={
                                             L"\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5Ax61\x62\x7D\x7E",
                                             L"\x30\x50[abcdzyxw!)(@#*]\x40\x20\x30\x50\ab\x40\x20",
                                             L"\x30\x50[A-D]\x40\x20\x30\x50f\x40\x20",
                                             L"",
                                             L".."//NULL
                                        };

  CHAR16                               TestDataSav[MAX_SIZE_OF_STRING + 1];



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
  for (Index = 0; Index < sizeof (TestData) / sizeof (CHAR16*); Index++) {
    //
    // Backup current test data
    //
    CopyUnicodeString (TestDataSav, TestData[Index]);

    //
    // For each test data, test the StrLwr functionality.
    //
    UnicodeCollation->StrLwr (UnicodeCollation, TestData[Index]);

    if (CheckStrLwr (TestDataSav, TestData[Index])) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid003,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrLwr - Verification of StrLwr interface",
                   L"%a:%d: Original=%s -- ToLower=%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestDataSav,
                   TestData[Index]
                   );


    CopyUnicodeString (TestDataSav, TestData[Index]);
    UnicodeCollation->StrUpr (UnicodeCollation, TestData[Index]);
    UnicodeCollation->StrLwr (UnicodeCollation, TestData[Index]);

    if (CheckStrEql (TestDataSav, TestData[Index])) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid004,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrLwr - Verification of StrLwr interface",
                   L"%a:%d: Original=%s -- ToLower=%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestDataSav,
                   TestData[Index]
                   );
  };

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_UNICODE_COLLATOIN2_PROTOCOL.StrUpr () Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.4
//
EFI_STATUS
BBTestStrUprFunctionAutoTest (
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

  EFI_TEST_ASSERTION                   AssertionType;

  //
  // Test Data
  //
  CHAR16                               *TestData[] ={
                                             L"\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5Ax61\x62\x7D\x7E",
                                             L"\x30\x50[abcdzyxw!)(@#*]\x40\x20\x30\x50\ab\x40\x20",
                                             L"\x30\x50[A-D]\x40\x20\x30\x50f\x40\x20",
                                             L""
                                        };

  CHAR16                               TestDataSav[MAX_SIZE_OF_STRING + 1];



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
  for (Index = 0; Index < sizeof (TestData) / sizeof (CHAR16*); Index++) {
    //
    // Backup current test data
    //
    CopyUnicodeString (TestDataSav, TestData[Index]);

    //
    // For each test data, test the StrUpr functionality.
    //
    UnicodeCollation->StrUpr (UnicodeCollation, TestData[Index]);

    if (CheckStrUpr (TestDataSav, TestData[Index])) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid005,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrUpr - Verification of StrUpr interface",
                   L"%a:%d: Original=%s-- ToUpper=%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestDataSav,
                   TestData[Index]
                   );

    CopyUnicodeString (TestDataSav, TestData[Index]);
    UnicodeCollation->StrLwr (UnicodeCollation, TestData[Index]);
    UnicodeCollation->StrUpr (UnicodeCollation, TestData[Index]);

    if (CheckStrEql (TestDataSav, TestData[Index])) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid006,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrUpr - Verification of StrUpr interface",
                   L"%a:%d: Original=%s -- ToUpper=%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestDataSav,
                   TestData[Index]
                   );
  };

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_UNICODE_COLLATOIN_PROTOCOL.FatToStr() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.5
//
EFI_STATUS
BBTestFatToStrFunctionAutoTest (
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
  UINTN                                FatSize;

  EFI_TEST_ASSERTION                   AssertionType;

  //
  // Test Data
  //
  CHAR8                                *TestData[] ={
                                             "filename.c",
                                             "longfilename.c",
                                             "\x10\x11\x20\x22\x50\x51\x61\x62",
                                        };


  CHAR16                               Result[MAX_SIZE_OF_STRING + 1];


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

  for (Index = 0; Index < sizeof (TestData) / sizeof (CHAR8*); Index++) {
    //
    // For each test data, test the FatToStr functionality.
    //

    //
    // FatSize reflect length of TestData[Index] correctly
    //
    FatSize = GetStrLen8 (TestData[Index]);
    UnicodeCollation->FatToStr (
                        UnicodeCollation,
                        FatSize,
                        TestData[Index],
                        Result
                        );

    if (CheckFatToStr (TestData[Index], FatSize, Result) == TRUE) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid007,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.FatToStr - Verification of FatToStr interface",
                   L"%a:%d: Fat='%s', FatToStr='%s', FatSize=%d, StrSize=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestData[Index],
                   Result,
                   FatSize,
                   GetStrLen16 (Result)
                   );

    //
    // FatSize is larger then length of TestData[Index]
    //
    FatSize = GetStrLen8 (TestData[Index]) + 2;
    if (FatSize >= 0 || FatSize <= MAX_SIZE_OF_STRING) {
      UnicodeCollation->FatToStr (
                          UnicodeCollation,
                          FatSize,
                          TestData[Index],
                          Result
                          );

      if (CheckFatToStr (TestData[Index], FatSize, Result) == TRUE) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gUnicodeCollationFunctionTestAssertionGuid008,
                     L"EFI_UNICODE_COLLATION_PROTOCOL.FatToStr - Verification of FatToStr interface",
                     L"%a:%d: Fat='%s', FatToStr='%s', FatSize=%d, StrSize=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     TestData[Index],
                     Result,
                     FatSize,
                     GetStrLen16 (Result)
                     );
    }

    //
    // FatSize is less then length of TestData[Index]
    //
    FatSize = GetStrLen8 (TestData[Index]) - 2;
    if (FatSize >= 0 || FatSize <= MAX_SIZE_OF_STRING) {
      UnicodeCollation->FatToStr (
                          UnicodeCollation,
                          FatSize,
                          TestData[Index],
                          Result
                          );

      if (CheckFatToStr (TestData[Index], FatSize, Result) == TRUE) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gUnicodeCollationFunctionTestAssertionGuid009,
                     L"EFI_UNICODE_COLLATION_PROTOCOL.FatToStr - Verification of FatToStr interface",
                     L"%a:%d: Fat='%s', FatToStr='%s', FatSize=%d, StrSize=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     TestData[Index],
                     Result,
                     FatSize,
                     GetStrLen16 (Result)
                     );
    }
  };

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_UNICODE_COLLATOIN_PROTOCOL.StrToFat() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.6
//
EFI_STATUS
BBTestStrToFatFunctionAutoTest (
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
  UINTN                                SubIndex;
  UINTN                                FatSize;

  EFI_TEST_ASSERTION                   AssertionType;

  //
  // Test Data
  //
  CHAR16                               *TestData[] ={
                                             L"longfilename.c",
                                             L"\x40\x50[]-\x20\x30",
                                             L"\x40\x50.\x20\x30",
                                             L"\x40\x50 \x20\x30",
                                             L"\x40\x50\x1234\x20\x30",
                                             L"\x40\x50\x1234\x20\x30",
                                             L"filename.c",
                                             L"longfilename.c"
                                        };


  CHAR8                                 Result[MAX_SIZE_OF_STRING + 1];
  CHAR16                                UnicodeBuf[MAX_SIZE_OF_STRING + 1];

  BOOLEAN                               IsLongFileName;

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

  for (Index = 0; Index < sizeof (TestData) / sizeof (CHAR16*); Index++) {
    //
    // For each test data, test the StrToFat functionality.
    //
    for (SubIndex = 0; SubIndex < MAX_SIZE_OF_STRING; SubIndex++) {
      Result[SubIndex] = 'x';
    }
    Result[MAX_SIZE_OF_STRING] = 0;

    //
    // FatSize is equal to the length of TestData[Index]
    //
    FatSize = GetStrLen16 (TestData[Index]);
    IsLongFileName = UnicodeCollation->StrToFat (
                                         UnicodeCollation,
                                         TestData[Index],
                                         FatSize,
                                         Result
                                         );

    if (CheckStrToFat (TestData[Index], FatSize, Result, IsLongFileName) == TRUE &&
          IsLongFileName == CheckLongFileName (TestData[Index], FatSize)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Change Char8 to Char16 for record log
    //
    UnicodeCollation->FatToStr (
                        UnicodeCollation,
                        FatSize,
                        Result,
                        UnicodeBuf
                        );


    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid010,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrToFat - Verification of StrToFat interface",
                   L"%a:%d: Str='%s', StrSize=%d, Parameter FatSize=%d, Fat='%s', Return Fat Length= %d, LongFileNmae=%d, Expected=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestData[Index],
                   GetStrLen16 (TestData[Index]),
                   FatSize,
                   UnicodeBuf,
                   GetStrLen8 (Result),
                   IsLongFileName,
                   CheckLongFileName (TestData[Index], FatSize)
                   );

    //
    // FatSize is larger than the length of TestData[Index]
    //
    FatSize = GetStrLen16 (TestData[Index]) + 2;
    IsLongFileName = UnicodeCollation->StrToFat (
                                         UnicodeCollation,
                                         TestData[Index],
                                         FatSize,
                                         Result
                                         );

    if (CheckStrToFat (TestData[Index], FatSize, Result, IsLongFileName) == TRUE &&
          IsLongFileName == CheckLongFileName (TestData[Index], FatSize)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Change Char8 to Char16 for record log
    //
    UnicodeCollation->FatToStr (
                        UnicodeCollation,
                        FatSize,
                        Result,
                        UnicodeBuf
                        );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid011,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrToFat - Verification of StrToFat interface",
                   L"%a:%d: Str='%s', StrSize=%d, Parameter FatSize=%d, Fat='%s', Return Fat Length= %d, LongFileNmae=%d, Expected=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestData[Index],
                   GetStrLen16 (TestData[Index]),
                   FatSize,
                   UnicodeBuf,
                   GetStrLen8 (Result),
                   IsLongFileName,
                   CheckLongFileName (TestData[Index], FatSize)
                   );

    //
    // FatSize is smaller than the length of TestData[Index]
    //
    FatSize = GetStrLen16 (TestData[Index]) - 2;

    IsLongFileName = UnicodeCollation->StrToFat (
                                         UnicodeCollation,
                                         TestData[Index],
                                         FatSize,
                                         Result
                                         );

    if (CheckStrToFat (TestData[Index], FatSize, Result, IsLongFileName) == TRUE &&
          IsLongFileName == CheckLongFileName (TestData[Index], FatSize)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Change Char8 to Char16 for record log
    //
    UnicodeCollation->FatToStr (
                        UnicodeCollation,
                        FatSize,
                        Result,
                        UnicodeBuf
                        );
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid012,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrToFat - Verification of StrToFat interface",
                   L"%a:%d: Str='%s', StrSize=%d, Parameter FatSize=%d, Fat='%s', Return Fat Length= %d, ConversionFail=%d, Expected=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TestData[Index],
                   GetStrLen16 (TestData[Index]),
                   FatSize,
                   UnicodeBuf,
                   GetStrLen8 (Result),
                   IsLongFileName,
                   CheckLongFileName (TestData[Index], FatSize)
                   );
  };

  return EFI_SUCCESS;
}
