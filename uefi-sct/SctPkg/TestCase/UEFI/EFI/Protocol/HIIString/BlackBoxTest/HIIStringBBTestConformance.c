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
    HIIStringBBTestConformance.c

Abstract:
    for EFI Driver HII String Protocol's conformance Test

--*/

#include "HIIStringBBTestMain.h"

extern UINT8 mPackageList1[];

#ifndef EFI_INVALID_LANGUAGE
#define EFI_INVALID_LANGUAGE      EFIERR (32)   //should be removed and get from EDK definition
#endif

EFI_STATUS
EFIAPI
BBTestNewStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestGetStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestGetStringConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestGetStringConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestGetStringConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestSetStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );
  
EFI_STATUS
EFIAPI
BBTestGetLanguagesConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );

EFI_STATUS
EFIAPI
BBTestGetSecondaryLanguagesConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  );

//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestNewStringConformanceTest (
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
  BBTestNewStringConformanceTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
EFIAPI
BBTestGetStringConformanceTest (
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
  BBTestGetStringConformanceTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  BBTestGetStringConformanceTestCheckpoint2( StandardLib, HIIDatabase, HIIString );
  
  BBTestGetStringConformanceTestCheckpoint3( StandardLib, HIIDatabase, HIIString );
  
  BBTestGetStringConformanceTestCheckpoint4( StandardLib, HIIDatabase, HIIString );
  
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
EFIAPI
BBTestSetStringConformanceTest (
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
  BBTestSetStringConformanceTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
EFIAPI
BBTestGetLanguagesConformanceTest (
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
  BBTestGetLanguagesConformanceTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetSecondaryLanguagesConformanceTest (
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
  BBTestGetSecondaryLanguagesConformanceTestCheckpoint1( StandardLib, HIIDatabase, HIIString );
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestNewStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  CHAR8                          *Language;
  CHAR16                         *LanguageName; 
  EFI_STRING                     String;
  EFI_STRING_ID                  StringId;
 
  //
  // Init the Language and String
  //
  Language = "en-US";
  LanguageName = L"English(United States)";
  String = L"This is a new String!";
  
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
  // Call NewString with StringId been NULL
  //
  Status = HIIString->NewString (
                        HIIString,
                        Handle,
                        NULL,
                        Language,
                        LanguageName,
                        String,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid001,
                 L"HII_STRING_PROTOCOL.NewString - NewString() returns EFI_INVALID_PARAMETER with StringId been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call NewString with Language been NULL
  //
  Status = HIIString->NewString (
                        HIIString,
                        Handle,
                        &StringId,
                        NULL,
                        LanguageName,
                        String,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid002,
                 L"HII_STRING_PROTOCOL.NewString - NewString() returns EFI_INVALID_PARAMETER with Language been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call NewString with String been NULL
  //
  Status = HIIString->NewString (
                        HIIString,
                        Handle,
                        &StringId,
                        Language,
                        LanguageName,
                        NULL,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid003,
                 L"HII_STRING_PROTOCOL.NewString - NewString() returns EFI_INVALID_PARAMETER with String been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call NewString with PackageList been NULL
  //
  Status = HIIString->NewString (
                        HIIString,
                        NULL,
                        &StringId,
                        Language,
                        LanguageName,
                        String,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid004,
                 L"HII_STRING_PROTOCOL.NewString - NewString() returns EFI_INVALID_PARAMETER with PackageList been NULL.",
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
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  CHAR8                          *Language;
  CHAR16                         *LanguageName;
  EFI_STRING_ID                  StringId;
  EFI_STRING                     String;
  UINTN                          StringSize;
  
  //
  // Init Language, StringId, String, StringSize
  //
  Language = "en-US";
  String = L"This is a new String!";
  LanguageName = L"English(United States)";
  StringSize = 60;
   
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
  // Add a String to the PackageList
  //
  Status = HIIString->NewString (
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
  // Call GetString with StringId been invalid
  //
  Status = HIIString->GetString (
                        HIIString,
                        Language,
                        Handle,
                        StringId+1,
                        String,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid005,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_NOT_FOUND with StringId been invalid.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetString with PackageList is not in the Database 
  //
  Status = HIIString->GetString (
                        HIIString,
                        Language,
                        (EFI_HANDLE)((UINT8*)(Handle) + 8),
                        StringId,
                        String,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid026,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_NOT_FOUND with PackageList is not in the Database.",
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
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetStringConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  CHAR8                          *Language;
  CHAR16                         *LanguageName;
  EFI_STRING_ID                  StringId;
  EFI_STRING                     String;
  EFI_STRING                     OutString;
  UINTN                          StringSize, ActuStringSize;

  //
  // Init Language, StringId, String and StringSize
  //
  Language = "en-US";
  String = L"This is a new string!";
  LanguageName = L"English(United States)";
  StringSize = 8;
  ActuStringSize = 44;
  OutString = (EFI_STRING)SctAllocateZeroPool ( StringSize );
  
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
    gtBS->FreePool ( OutString );
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
    gtBS->FreePool ( OutString );
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    return Status;
  }
  
  //
  // Call GetString with StringSize indicates the String is too small
  //
  Status = HIIString->GetString (
                        HIIString,
                        Language,
                        Handle,
                        StringId,
                        OutString,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_BUFFER_TOO_SMALL != Status || StringSize != ActuStringSize ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid006,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_BUFFER_TOO_SMALL with StringSize indicates the String is too small.",
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
  // Release the resource of OutString
  //
  gtBS->FreePool ( OutString );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetStringConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  CHAR8                          *Language, *InvalidLanguage1, *InvalidLanguage2, *InvalidLanguage3;
  CHAR16                         *LanguageName;
  EFI_STRING_ID                  StringId;
  EFI_STRING                     String;
  EFI_STRING                     OutString;
  UINTN                          StringSize;

  //
  // Init Language, StringId, String and StringSize
  //
  Language = "en-US";
  InvalidLanguage1 = "zh-Hans";
  InvalidLanguage2 = "en";
  InvalidLanguage3 = "en-US-CA";
  String = L"This is a new string!";
  LanguageName = L"English(United States)";
  StringSize = 64;
  
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
  
  OutString = (EFI_STRING)SctAllocateZeroPool ( StringSize );
  
  //
  // Call GetString with string is not in the specified Language
  //
  Status = HIIString->GetString (
                        HIIString,
                        InvalidLanguage1,
                        Handle,
                        StringId,
                        OutString,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_INVALID_LANGUAGE != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid007,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_INVALID_LANGUAGE with string is not in the specified Language.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetString with string is not in the specified Language
  //
  Status = HIIString->GetString (
                        HIIString,
                        InvalidLanguage2,
                        Handle,
                        StringId,
                        OutString,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_INVALID_LANGUAGE != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid007,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_INVALID_LANGUAGE with string is not in the specified Language.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetString with string is not in the specified Language
  //
  Status = HIIString->GetString (
                        HIIString,
                        InvalidLanguage3,
                        Handle,
                        StringId,
                        OutString,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_INVALID_LANGUAGE != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid007,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_INVALID_LANGUAGE with string is not in the specified Language.",
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
  // Release the resource of OutString
  //
  gtBS->FreePool ( OutString );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetStringConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  CHAR8                          *Language;
  CHAR16                         *LanguageName;
  EFI_STRING_ID                  StringId;
  EFI_STRING                     String;
  EFI_STRING                     OutString;
  UINTN                          StringSize;
 
  //
  // Init Language, StringId, String and StringSize
  //
  Language = "en-US";
  String = L"This is a new string!";
  LanguageName = L"English(United States)";
  StringSize = 64;
  OutString = (EFI_STRING)SctAllocateZeroPool ( StringSize );
  
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
    gtBS->FreePool ( OutString );
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
    gtBS->FreePool ( OutString );
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    return Status;
  }
  
  //
  // Call GetString with Language been NULL
  //
  Status = HIIString->GetString (
                        HIIString,
                        NULL,
                        Handle,
                        StringId,
                        OutString,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid008,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_INVALID_PARAMETER with Language been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetString with String been NULL
  //
  Status = HIIString->GetString (
                        HIIString,
                        Language,
                        Handle,
                        StringId,
                        NULL,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid009,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_INVALID_PARAMETER with String been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetString with StringSize been NULL
  //
  Status = HIIString->GetString (
                        HIIString,
                        Language,
                        Handle,
                        StringId,
                        OutString,
                        NULL,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid010,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_INVALID_PARAMETER with StringSize been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetString with PackageList been NULL
  //
  Status = HIIString->GetString (
                        HIIString,
                        Language,
                        NULL,
                        StringId,
                        OutString,
                        &StringSize,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid011,
                 L"HII_STRING_PROTOCOL.GetString - GetString() returns EFI_INVALID_PARAMETER with PackageList been NULL.",
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
  // Release the resource of OutString
  //
  gtBS->FreePool ( OutString );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
  CHAR8                          *Language;
  CHAR16                         *LanguageName;
  EFI_STRING_ID                  StringId, InvalidStringId;
  EFI_STRING                     String;
  EFI_STRING                     NewSetString;

  //
  // Init Language, StringId, String
  //
  InvalidStringId = 0xFF;
  Language = "en-US";
  String = L"This is a new string!";
  NewSetString = L"The new reset string!";
  LanguageName = L"English(United States)";
  
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
  // Call SetString with StringId been invalid
  //
  Status = HIIString->SetString (
                        HIIString,
                        Handle,
                        InvalidStringId,
                        Language,
                        NewSetString,
                        NULL
                        );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid012,
                 L"HII_STRING_PROTOCOL.SetString - SetString() returns EFI_NOT_FOUND with StringId been invalid.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call SetString with Language been NULL
  //
  Status = HIIString->SetString (
                        HIIString,
                        Handle,
                        StringId,
                        NULL,
                        NewSetString,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid013,
                 L"HII_STRING_PROTOCOL.SetString - SetString() returns EFI_INVALID_PARAMETER with Language been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call SetString with String been NULL
  //
  Status = HIIString->SetString (
                        HIIString,
                        Handle,
                        StringId,
                        Language,
                        NULL,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid014,
                 L"HII_STRING_PROTOCOL.SetString - SetString() returns EFI_INVALID_PARAMETER with String been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call SetString with PackageList is not in the Database
  //
  Status = HIIString->SetString (
                        HIIString,
                        (EFI_HANDLE)((UINT8*)(Handle) + 8),
                        StringId,
                        Language,
                        NewSetString,
                        NULL
                        );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid027,
                 L"HII_STRING_PROTOCOL.SetString - SetString() returns EFI_NOT_FOUND with PackageList is not in the Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call SetString with PackageList been NULL
  //
  Status = HIIString->SetString (
                        HIIString,
                        NULL,
                        StringId,
                        Language,
                        NewSetString,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid015,
                 L"HII_STRING_PROTOCOL.SetString - SetString() returns EFI_INVALID_PARAMETER with PackageList been NULL.",
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

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetLanguagesConformanceTestCheckpoint1 (
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
  // Init Language and LanguagesSize
  //
  LanguagesSize = 512;
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
    gtBS->FreePool ( Languages );
    return Status;
  }
  
  //
  // Call GetLanguages with Languages been NULL
  //
  Status = HIIString->GetLanguages (
                        HIIString,
                        Handle,
                        NULL,
                        &LanguagesSize
                        );
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid016,
                 L"HII_STRING_PROTOCOL.GetLanguages - GetLanguages() returns EFI_INVALID_PARAMETER with Languages been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetLanguages with LanguagesSize been NULL
  //
  Status = HIIString->GetLanguages (
                        HIIString,
                        Handle,
                        Languages,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid017,
                 L"HII_STRING_PROTOCOL.GetLanguages - GetLanguages() returns EFI_INVALID_PARAMETER with LanguagesSize been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetLanguages with PackageList is not in the Database
  //
  Status = HIIString->GetLanguages (
                        HIIString,
                        (EFI_HANDLE)((UINT8*)(Handle) + 8),
                        Languages,
                        &LanguagesSize
                        );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid028,
                 L"HII_STRING_PROTOCOL.GetLanguages - GetLanguages() returns EFI_NOT_FOUND with PackageList is not in the Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetLanguages with PackageList been NULL
  //
  Status = HIIString->GetLanguages (
                        HIIString,
                        NULL,
                        Languages,
                        &LanguagesSize
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid018,
                 L"HII_STRING_PROTOCOL.GetLanguages - GetLanguages() returns EFI_INVALID_PARAMETER with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool ( Languages );
  LanguagesSize = 2;
  Languages = (CHAR8*)SctAllocateZeroPool ( LanguagesSize );
  
  //
  // Call GetLanguages with LanguagesSize indicates the Languages is too small
  //
  Status = HIIString->GetLanguages (
                        HIIString,
                        Handle,
                        Languages,
                        &LanguagesSize
                        );
  
  if ( EFI_BUFFER_TOO_SMALL != Status || LanguagesSize != 14 ) { 
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid019,
                 L"HII_STRING_PROTOCOL.GetLanguages - GetLanguages() returns EFI_BUFFER_TOO_SMALL with LanguagesSize indicates the Languages is too small.",
                 L"%a:%d: Status - %r, LanguagesSize - %d, Expected LanguagesSize - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 LanguagesSize,
                 14
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
  gtBS->FreePool (Languages);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetSecondaryLanguagesConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString
  )
{

  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  
//  CHAR8                          *FirstLanguage;
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
  // Call GetSecondaryLanguages with FirstLanguages been NULL
  //
  Status = HIIString->GetSecondaryLanguages (
                        HIIString,
                        Handle,
                        NULL,
                        SecondLanguages,
                        &SecondLanguagesSize
                        );
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid020,
                 L"HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages() returns EFI_INVALID_PARAMETER with FirstLanguage been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetSecondaryLanguages with SecondLanguages been NULL
  //
  Status = HIIString->GetSecondaryLanguages (
                        HIIString,
                        Handle,
                        "en-US",
                        NULL,
                        &SecondLanguagesSize
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid021,
                 L"HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages() returns EFI_INVALID_PARAMETER with SecondLanguages been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetSecondaryLanguages with SecondLanguagesSize been NULL
  //
  Status = HIIString->GetSecondaryLanguages (
                        HIIString,
                        Handle,
                        "en-US",
                        SecondLanguages,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid022,
                 L"HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages() returns EFI_INVALID_PARAMETER with SecondLanguagesSize been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetSecondaryLanguages with PackageList is not in the Database
  //
  Status = HIIString->GetSecondaryLanguages (
                        HIIString,
                        (EFI_HANDLE)((UINT8*)(Handle) + 8),
                        "en-US",
                        SecondLanguages,
                        &SecondLanguagesSize
                        );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid029,
                 L"HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages() returns EFI_NOT_FOUND with PackageList is not in the Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetSecondaryLanguages with PackageList been NULL
  //
  Status = HIIString->GetSecondaryLanguages (
                        HIIString,
                        NULL,
                        "en-US",
                        SecondLanguages,
                        &SecondLanguagesSize
                        );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid023,
                 L"HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages() returns EFI_INVALID_PARAMETER with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetSecondaryLanguages with FirstLanguage is not present in the PackageList.
  //
  Status = HIIString->GetSecondaryLanguages (
                        HIIString,
                        Handle,
                        "fr-Latn-CA",
                        SecondLanguages,
                        &SecondLanguagesSize
                        );
  
  if ( EFI_INVALID_LANGUAGE != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid024,
                 L"HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages() returns EFI_INVALID_LANGUAGE with FirstLanguage is not present in the PackageList.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Init the SecondLanguagesSize and SecondLanguages again
  //
  SecondLanguagesSize = 0;
  
  //
  // Call GetSecondaryLanguages with SecondLanguagesSize indicates the SecondLanguages is too small
  //
  Status = HIIString->GetSecondaryLanguages (
                        HIIString,
                        Handle,
                        "en-US",
                        SecondLanguages,
                        &SecondLanguagesSize
                        );
  
  if ( EFI_BUFFER_TOO_SMALL != Status || SecondLanguagesSize != 8 ) {//BUGBUG:  SecondLanguagesSize is not 0x14 !!
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIStringBBTestConformanceAssertionGuid025,
                 L"HII_STRING_PROTOCOL.GetLanguages - GetSecondaryLanguages() returns EFI_BUFFER_TOO_SMALL with SecondLanguagesSize indicates the SecondLanguages is too small.",
                 L"%a:%d: Status - %r, SecondaryLanguagesSize - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 SecondLanguagesSize
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
