/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    HIIStringBBTestFunction.c

Abstract:
    for EFI Driver HII String Protocol's function Test

--*/

#include "HIIStringBBTestMain.h"

extern UINT8 mPackageList1[];

EFI_STATUS
EFIAPI
BBTestNewStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestGetStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestSetStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestGetLanguagesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );

EFI_STATUS
EFIAPI
BBTestGetSecondaryLanguagesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );

//
//Test Cases
//
EFI_STATUS
EFIAPI
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
                   (VOID **) &StandardLib
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
EFIAPI
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
                   (VOID **) &StandardLib
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
EFIAPI
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
                   (VOID **) &StandardLib
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
EFIAPI
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
                   (VOID **) &StandardLib
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
EFIAPI
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
                   (VOID **) &StandardLib
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
