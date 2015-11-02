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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    HIIStringBBTestFunction.c

Abstract:
    for EFI Driver HII String Protocol's function Test

--*/

#include "HIIStringBBTestMain.h"

extern UINT8 mPackageList1[];

EFI_STATUS
BBTestNewStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
BBTestGetStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
BBTestSetStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
BBTestGetLanguagesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );

EFI_STATUS
BBTestGetSecondaryLanguagesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );

//
//Test Cases
//
EFI_STATUS
BBTestNewStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_STRING_PROTOCOL               *HIIString;
  
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIString = (EFI_HII_STRING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  Status = GetHIIDatabaseInterface( &HIIDatabase );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestNewStringFunctionTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
BBTestGetStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_STRING_PROTOCOL               *HIIString;
  
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIString = (EFI_HII_STRING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface( &HIIDatabase );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetStringFunctionTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
BBTestSetStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_STRING_PROTOCOL               *HIIString;
  
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIString = (EFI_HII_STRING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface( &HIIDatabase );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestSetStringFunctionTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
BBTestGetLanguagesFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_STRING_PROTOCOL               *HIIString;
  
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIString = (EFI_HII_STRING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface( &HIIDatabase );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetLanguagesFunctionTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetSecondaryLanguagesFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_STRING_PROTOCOL               *HIIString;
  
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIString = (EFI_HII_STRING_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface( &HIIDatabase );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetSecondaryLanguagesFunctionTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}

//
//Check Points
//
EFI_STATUS
BBTestNewStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  EFI_STRING_ID                  StringId;
  CHAR8                          *Language;
  CHAR16                         *LanguageName;
  EFI_STRING                     String;
  EFI_STRING                     OutString;
  UINTN                          StringSize, ActuStringSize;

  //
  // Init the Language, String, StringSize;
  //
  Language = "en-US";
  String = L"This is a new string!";
  LanguageName = L"English(United States)";
  StringSize = 64;
  ActuStringSize = 44;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
  return Status;
  }
  
  //
  // Call NewString with valid parameters
  //
  Status = HIIString->NewString(
                        HIIString,
                        Handle,
                        &StringId,
                        Language,
                        LanguageName,
                        String,
                        NULL
                        );
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }


  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestFunctionAssertionGuid001,
                 L"HII_STRING_PROTOCOL.NewString - NewString() returns EFI_SUCCESS with valid parameters and result checked.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( EFI_SUCCESS == Status) {
	//
    // Allocate the OutString
    //
    OutString = (EFI_STRING)SctAllocateZeroPool ( StringSize );
    
    //
    // Call GetString to check
    //
    Status = HIIString->GetString(
                          HIIString,
                          Language,
                          Handle,
                          StringId,
                          OutString,
                          &StringSize,
                          NULL
                          );
    if ( EFI_ERROR(Status) ) {
      gtBS->FreePool ( OutString );
      Status = HIIDatabase->RemovePackageList (
                              HIIDatabase,
                              Handle
                              );
      return Status;
    }
    //
    // Check the output String
    //
    if ( SctCompareMem ( OutString, String, ActuStringSize ) != 0 )
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    gtBS->FreePool ( OutString );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIStringBBTestFunctionAssertionGuid002,
                   L"HII_STRING_PROTOCOL.NewString - output the string and compare with the original string.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  EFI_STRING_ID                  StringId;
  CHAR8                          *Language;
  CHAR8                          *Language1;
  CHAR16                         *LanguageName;
  EFI_STRING                     String;
  EFI_STRING                     GetString;
  UINTN                          StringSize, ActuStringSize;

  //
  // Init the Language, String, StringSize;
  //
  Language = "en-US";
  Language1 = "en-us";
  String = L"This is a new string!";
  LanguageName = L"English(United States)";
  StringSize = 64;
  ActuStringSize = 44;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Call NewString with valid parameters
  //
  Status = HIIString->NewString(
                        HIIString,
                        Handle,
                        &StringId,
                        Language,
                        LanguageName,
                        String,
                        NULL
                        );
  if ( EFI_ERROR(Status) ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    return Status;
  }

  GetString = (EFI_STRING)SctAllocateZeroPool ( StringSize );
  
  //
  // Call GetString to with valid parameters
  //
  Status = HIIString->GetString(
                        HIIString,
                        Language1,
                        Handle,
                        StringId,
                        GetString,
                        &StringSize,
                        NULL
                        );
  
//  if ( EFI_SUCCESS != Status || SctCompareMem ( GetString, String, ActuStringSize ) != 0 || StringSize != ActuStringSize ) {
  if ( EFI_SUCCESS != Status || SctCompareMem ( GetString, String, ActuStringSize ) != 0 ) {  	
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestFunctionAssertionGuid003,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_SUCCESS with valid parameters and the result checked.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );

  //
  // Release the resource of GetString
  //
  gtBS->FreePool ( GetString );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  EFI_STRING_ID                  StringId;
  CHAR8                          *Language;
  CHAR16                         *LanguageName;
  EFI_STRING                     String;
  EFI_STRING                     SetNewString;
  EFI_STRING                     OutString;
  UINTN                          StringSize, ActuStringSize;

  //
  // Init the Language, StringId, String and StringSize;
  //
  Language = "en-US";
  String = L"This is a new string!";
  LanguageName = L"English(United States)";
  SetNewString = L"Reset the new string!";
  StringSize = 64;
  ActuStringSize = 44;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
  return Status;
  }
  
  //
  // Call NewString with valid parameters
  //
  Status = HIIString->NewString(
                        HIIString,
                        Handle,
                        &StringId,
                        Language,
                        LanguageName,
                        String,
                        NULL
                        );
  if ( EFI_ERROR(Status) ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    return Status;
  }
  
  //
  // Call SetString with valid parameters
  //
  Status = HIIString->SetString(
                        HIIString,
                        Handle,
                        StringId,
                        Language,
                        SetNewString,
                        NULL
                        );
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestFunctionAssertionGuid004,
                 L"HII_STRING_PROTOCOL.SetString - SetString() returns EFI_SUCCESS with valid parameters and result checked.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( EFI_SUCCESS == Status ) {
    //
    // Allocate the OutString
    //
    OutString = (EFI_STRING)SctAllocateZeroPool ( StringSize );
    
    //
    // Call GetString to check
    //
    Status = HIIString->GetString(
                          HIIString,
                          Language,
                          Handle,
                          StringId,
                          OutString,
                          &StringSize,
                          NULL
                          );
    if ( EFI_ERROR(Status) ) {
      gtBS->FreePool ( OutString );
      Status = HIIDatabase->RemovePackageList (
                              HIIDatabase,
                              Handle
                              );
      return Status;
    }
    //
    // Check the output String
    //
    if ( SctCompareMem ( OutString, SetNewString, ActuStringSize ) != 0 )
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    gtBS->FreePool ( OutString );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIStringBBTestFunctionAssertionGuid005,
                   L"HII_STRING_PROTOCOL.SetString - output the string and compare with the reset string.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetLanguagesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  CHAR8                          *Languages;
  UINTN                          LanguagesSize;

  //
  // Init the Languages and LanguagesSize;
  //
  LanguagesSize = 128;
  Languages = (CHAR8*)SctAllocateZeroPool ( LanguagesSize );
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    //
    // Release the resource of Languages
    //
    gtBS->FreePool ( Languages );
    return Status;
  }
  
  //
  // Call GetLanguages to with valid parameters
  //
  Status = HIIString->GetLanguages(
                        HIIString,
                        Handle,
                        Languages,
                        &LanguagesSize
                        );
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    //
    // Check the output Languages
    //

  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestFunctionAssertionGuid006,
                 L"HII_STRING_PROTOCOL.GetLanguages - GetLanguages() returns EFI_SUCCESS with valid parameters.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  //
  // Release the resource of Languages
  //
  gtBS->FreePool ( Languages );

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetSecondaryLanguagesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{

  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  CHAR8                          *SecondLanguages;
  UINTN                          SecondLanguagesSize;

  //
  // Init Language and LanguagesSize
  //
  SecondLanguagesSize = 512;
  SecondLanguages = (CHAR8*)SctAllocateZeroPool ( SecondLanguagesSize );
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool ( SecondLanguages );
    return Status;
  }
  
  //
  // Call GetSecondaryLanguages with SecondLanguagesSize indicates the SecondLanguages is large enough
  //
  Status = HIIString->GetSecondaryLanguages (
                        HIIString,
                        Handle,
                        "en-US",
                        SecondLanguages,
                        &SecondLanguagesSize
                        );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestFunctionAssertionGuid007,
                 L"HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages() returns EFI_SUCCESS with SecondLanguagesSize is large enough.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  
  //
  // Release the resource of Languages
  //
  gtBS->FreePool ( SecondLanguages );

  return EFI_SUCCESS;

}
