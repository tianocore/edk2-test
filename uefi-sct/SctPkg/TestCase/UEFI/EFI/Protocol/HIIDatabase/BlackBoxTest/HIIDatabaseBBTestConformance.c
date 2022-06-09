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
    HIIDatabaseBBTestConformance.c

Abstract:
    for EFI Driver HII Database Protocol's conformance Test

--*/

#include "HIIDatabaseBBTestMain.h"

extern UINT8 mPackageList1[];
extern UINT8 mPackageList2[];
extern EFI_GUID mPackageGuid;
extern EFI_GUID mKBLayoutGuid11;
extern EFI_GUID mKBLayoutGuid21;
extern EFI_GUID mKBLayoutGuid22;

#define PackageListLength    512

#define PackageList1ActualLength    398


EFI_GUID mTestNoInterfaceProtocol2Guid = TEST_NO_INTERFACE_PROTOCOL_2_GUID;

STATIC
VOID
CreateDeviceHandle (
  OUT EFI_HANDLE  *DeviceHandle
  );

STATIC
VOID
ReleaseDeviceHandle (
  IN EFI_HANDLE    DeviceHandle
  );

EFI_STATUS
EFIAPI
BBTestNewPackageListConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestNewPackageListConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestRemovePackageListConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestRemovePackageListConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
EFIAPI
BBTestRemovePackageListConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestUpdatePackageListConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestUpdatePackageListConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestUpdatePackageListConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestUpdatePackageListConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestRegisterPackageNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestRegisterPackageNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestRegisterPackageNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
EFIAPI
BBTestSetKeyboardLayoutConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
EFIAPI
BBTestSetKeyboardLayoutConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestNewPackageListConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestNewPackageListConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestNewPackageListConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRemovePackageListConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestRemovePackageListConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestRemovePackageListConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  BBTestRemovePackageListConformanceTestCheckpoint3( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUpdatePackageListConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestUpdatePackageListConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestUpdatePackageListConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  BBTestUpdatePackageListConformanceTestCheckpoint3( StandardLib, HIIDatabase );
  
  BBTestUpdatePackageListConformanceTestCheckpoint4( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestListPackageListsConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestListPackageListsConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  BBTestListPackageListsConformanceTestCheckpoint3( StandardLib, HIIDatabase );
  
  BBTestListPackageListsConformanceTestCheckpoint4( StandardLib, HIIDatabase );
  
  BBTestListPackageListsConformanceTestCheckpoint5( StandardLib, HIIDatabase );
  
  BBTestListPackageListsConformanceTestCheckpoint6( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestExportPackageListsConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestExportPackageListsConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  BBTestExportPackageListsConformanceTestCheckpoint3( StandardLib, HIIDatabase );
  
  BBTestExportPackageListsConformanceTestCheckpoint4( StandardLib, HIIDatabase );
  
  BBTestExportPackageListsConformanceTestCheckpoint5( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterPackageNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestRegisterPackageNotifyConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestRegisterPackageNotifyConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  BBTestRegisterPackageNotifyConformanceTestCheckpoint3( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestUnregisterPackageNotifyConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestUnregisterPackageNotifyConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  BBTestUnregisterPackageNotifyConformanceTestCheckpoint3( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestFindKeyboardLayoutsConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestFindKeyboardLayoutsConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  BBTestFindKeyboardLayoutsConformanceTestCheckpoint3( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestGetKeyboardLayoutConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestGetKeyboardLayoutConformanceTestCheckpoint2( StandardLib, HIIDatabase );

  BBTestGetKeyboardLayoutConformanceTestCheckpoint3( StandardLib, HIIDatabase );
  
  BBTestGetKeyboardLayoutConformanceTestCheckpoint4( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetKeyboardLayoutConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestSetKeyboardLayoutConformanceTestCheckpoint1( StandardLib, HIIDatabase );
  
  BBTestSetKeyboardLayoutConformanceTestCheckpoint2( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIDatabase = (EFI_HII_DATABASE_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestGetPackageListHandleConformanceTestCheckpoint1 ( StandardLib, HIIDatabase );
  
  BBTestGetPackageListHandleConformanceTestCheckpoint2 ( StandardLib, HIIDatabase );
  
  BBTestGetPackageListHandleConformanceTestCheckpoint3 ( StandardLib, HIIDatabase );
  
  BBTestGetPackageListHandleConformanceTestCheckpoint4 ( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestNewPackageListConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_HANDLE        Handle;

  //
  // Call NewPackageList with PackageList set to be NULL
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          NULL,
                          NULL,
                          &Handle
                          );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid001,
                 L"HII_DATABASE_PROTOCOL.NewPackageList - NewPackageList() returns EFI_INVALID_PARAMETER with PackageList being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestNewPackageListConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Call NewPackageList with Handle set to be NULL
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          NULL
                          );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid002,
                 L"HII_DATABASE_PROTOCOL.NewPackageList - NewPackageList() returns EFI_INVALID_PARAMETER with Handle being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRemovePackageListConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  //
  // Call RemovePackageList with Handle set to be NULL
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          NULL
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid003,
                 L"HII_DATABASE_PROTOCOL.RemovePackageList - RemovePackageList() returns EFI_NOT_FOUND with Handle being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRemovePackageListConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the new PackageList to the database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
    }
  
  //
  // Remove the PackageList associated with Handle
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Call RemovePackageList with Handle has already been removed once
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid004,
                 L"HII_DATABASE_PROTOCOL.RemovePackageList - RemovePackageList() returns EFI_NOT_FOUND with Handle has already been removed once.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRemovePackageListConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  EFI_HII_HANDLE                 InvalidHandle;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the new PackageList to the database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
    }
  
  //
  // Create a invalid Handle 
  //
  InvalidHandle = (EFI_HII_HANDLE)((UINT8*)Handle + 8);
  
  //
  // Call RemovePackageList with the invalid Handle
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          InvalidHandle
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid005,
                 L"HII_DATABASE_PROTOCOL.RemovePackageList - RemovePackageList() returns EFI_NOT_FOUND with an invalid Handle.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList associated with Handle
  //
  Status = HIIDatabase->RemovePackageList(
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
BBTestUpdatePackageListConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *UpdatePackageList;

  UpdatePackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Call UpdatePackageList with Handle set to be NULL
  //
  Status = HIIDatabase->UpdatePackageList(
                          HIIDatabase,
                          NULL,
                          UpdatePackageList
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid006,
                 L"HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList() returns EFI_NOT_FOUND with Handle being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUpdatePackageListConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_PACKAGE_LIST_HEADER    *UpdatePackageList;
  EFI_HII_HANDLE                 Handle;

  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  UpdatePackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList2;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Remove the package list associated with Handle from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Call UpdatePackageList with Handle has already been removed from the HII database
  //
  Status = HIIDatabase->UpdatePackageList(
                          HIIDatabase,
                          Handle,
                          UpdatePackageList
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid007,
                 L"HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList() returns EFI_NOT_FOUND with Handle has already been removed before.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUpdatePackageListConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_PACKAGE_LIST_HEADER    *UpdatePackageList;
  EFI_HII_HANDLE                 Handle;
  EFI_HII_HANDLE                 InvalidHandle;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  UpdatePackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList2;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Create an invalid handle
  //
  InvalidHandle = (EFI_HII_HANDLE)((UINT8*)(Handle) + 8);
  
  //
  // Call UpdatePackageList with the invalid handle
  //
  Status = HIIDatabase->UpdatePackageList(
                          HIIDatabase,
                          InvalidHandle,
                          UpdatePackageList
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid008,
                 L"HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList() returns EFI_NOT_FOUND with an invalid handle.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the package list associated with Handle from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
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
BBTestUpdatePackageListConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Call UpdatePackageList with PackageList set to be NULL
  //
  Status = HIIDatabase->UpdatePackageList(
                          HIIDatabase,
                          Handle,
                          NULL
                          );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid009,
                 L"HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList() returns EFI_INVALID_PARAMETER with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the package list associated with Handle from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
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
BBTestListPackageListsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                 PackageType;
  UINTN                 HandleBufferLength;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;

  PackageType = EFI_HII_PACKAGE_STRINGS;
  HandleBufferLength = 128 * sizeof(EFI_HII_HANDLE);
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Call ListPackageLists with Handle set to be NULL
  //
  Status = HIIDatabase->ListPackageLists(
                          HIIDatabase,
                          PackageType,
                          NULL,
                          &HandleBufferLength,
                          NULL
                          );
  //
  // Check if the HandleBufferLength is too small
  //
  if ( EFI_BUFFER_TOO_SMALL == Status ) {
    Status = HIIDatabase->ListPackageLists(
                            HIIDatabase,
                            PackageType,
                            NULL,
                            &HandleBufferLength,
                            NULL
                            );
  }

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid010,
                 L"HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists() returns EFI_INVALID_PARAMETER with Handle being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the package list associated with Handle from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
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
BBTestListPackageListsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINT8                 PackageType;
  EFI_HII_HANDLE        *HandleBuffer;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;

  PackageType = EFI_HII_PACKAGE_STRINGS;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Allocate the mem for Handle
  //
  HandleBuffer = (EFI_HII_HANDLE*) SctAllocateZeroPool ( 10 * sizeof(EFI_HII_HANDLE) );
  
  //
  // Call ListPackageLists with HandleBufferLength set to be NULL
  //
  Status = HIIDatabase->ListPackageLists(
                          HIIDatabase,
                          PackageType,
                          NULL,
                          NULL,
                          HandleBuffer
                          );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid011,
                 L"HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists() returns EFI_INVALID_PARAMETER with HandleBufferLength being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Release the resource of Handle
  //
  gtBS->FreePool ( HandleBuffer );
  
  //
  // Remove the package list associated with Handle from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
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
BBTestListPackageListsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                 PackageType;
  EFI_GUID              PackageGuid;
  EFI_HII_HANDLE        *Handle;
  UINTN                 HandleBufferLength;


  //
  // Init the PackageGuid
  //
  PackageType = EFI_HII_PACKAGE_TYPE_GUID;
  PackageGuid = mTestNoInterfaceProtocol2Guid;
  HandleBufferLength = 10 * sizeof( EFI_HII_HANDLE);
  
  //
  // Allocate the mem for Handle
  //
  Handle = (EFI_HII_HANDLE*) SctAllocateZeroPool ( HandleBufferLength );
  
  //
  // Call ListPackageLists with no mathching handles were found
  //
  Status = HIIDatabase->ListPackageLists(
                          HIIDatabase,
                          PackageType,
                          &PackageGuid,
                          &HandleBufferLength,
                          Handle
                          );
  //
  // Check if the HandleBufferLength is too small
  //
  if ( EFI_BUFFER_TOO_SMALL == Status ) {
    gtBS->FreePool ( Handle );
    Handle = (EFI_HII_HANDLE*) SctAllocateZeroPool ( HandleBufferLength );
    Status = HIIDatabase->ListPackageLists(
                            HIIDatabase,
                            PackageType,
                            &PackageGuid,
                            &HandleBufferLength,
                            Handle
                            );
  }

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid012,
                 L"HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists() returns EFI_NOT_FOUND when no matching handles were found.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Release the resource of Handle
  //
  gtBS->FreePool ( Handle );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                          PackageType;
  EFI_GUID                       PackageGuid;
  EFI_HII_HANDLE                 *Handle;
  UINTN                          HandleBufferLength;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList1, *PackageList2;
  EFI_HII_HANDLE                 PackageListHandle1, PackageListHandle2;

  PackageList1 = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  PackageList2 = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList2;
  //
  // Add the PackageList1 and PackageList2 to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList1,
                          NULL,
                          &PackageListHandle1
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList2,
                          NULL,
                          &PackageListHandle2
                          );
  if ( EFI_ERROR(Status) ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            PackageListHandle1
                            );
    return Status;
  }
  
  //
  // Init the PackageGuid
  //
  PackageType = EFI_HII_PACKAGE_TYPE_GUID;
  PackageGuid = mPackageGuid;
  HandleBufferLength = 1 * sizeof(EFI_HII_HANDLE);
  
  //
  // Allocate the mem for Handle
  //
  Handle = (EFI_HII_HANDLE*) SctAllocateZeroPool ( HandleBufferLength );
  
  //
  // Call ListPackageLists with HandleBufferLength indicates the buffer is too small
  //
  Status = HIIDatabase->ListPackageLists(
                          HIIDatabase,
                          PackageType,
                          &PackageGuid,
                          &HandleBufferLength,
                          Handle
                          );

  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid013,
                 L"HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists() returns EFI_BUFFER_TOO_SMALL when the HandleBufferLength indicates the buffer is too small.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
           
  if ( 2 * sizeof(EFI_HII_HANDLE) != HandleBufferLength ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid014,
                 L"HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists() returns EFI_BUFFER_TOO_SMALL when the HandleBufferLength indicates the buffer is too small and return the needed buffer length.",
                 L"%a:%d: Status - %r NeededLength - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HandleBufferLength
                 );

  //
  // Release the resource of Handle
  //
  gtBS->FreePool ( Handle );
  
  //
  // Remove the PackageLists from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          PackageListHandle1
                          );
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          PackageListHandle2
                          );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                 PackageType;
  EFI_GUID              PackageGuid;
  UINTN                 HandleBufferLength;
  EFI_HII_HANDLE        *Handle;


  //
  // Init the PackageGuid
  //
  PackageType = EFI_HII_PACKAGE_STRINGS;
  PackageGuid = mPackageGuid;
  HandleBufferLength = 10 * sizeof(EFI_HII_HANDLE);
  
  //
  // Allocate the mem for Handle
  //
  Handle = (EFI_HII_HANDLE*) SctAllocateZeroPool ( HandleBufferLength );
  
  //
  // Call ListPackageLists with PackageType is not Guid and PackageGuid is not NULL
  //
  Status = HIIDatabase->ListPackageLists(
                          HIIDatabase,
                          PackageType,
                          &PackageGuid,
                          &HandleBufferLength,
                          Handle
                          );
  //
  // Check if the HandleBufferLength is too small
  //
  if ( EFI_BUFFER_TOO_SMALL == Status ) {
    gtBS->FreePool ( Handle );
    Handle = (EFI_HII_HANDLE*) SctAllocateZeroPool ( HandleBufferLength );
    Status = HIIDatabase->ListPackageLists(
                            HIIDatabase,
                            PackageType,
                            &PackageGuid,
                            &HandleBufferLength,
                            Handle
                            );
  }

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid015,
                 L"HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists() returns EFI_INVALID_PARAMETER with PackageType is not Guid and PackageGuid is not NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Release the resource of Handle
  //
  gtBS->FreePool ( Handle );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTestCheckpoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                 PackageType;
  UINTN                 HandleBufferLength;
  EFI_HII_HANDLE        *Handle;


  //
  // Init the PackageGuid
  //
  PackageType = EFI_HII_PACKAGE_TYPE_GUID;
  HandleBufferLength = 10 * sizeof(EFI_HII_HANDLE);
  
  //
  // Allocate the mem for Handle
  //
  Handle = (EFI_HII_HANDLE*) SctAllocatePool ( HandleBufferLength );
  
  //
  // Call ListPackageLists with PackageType is EFI_HII_DATABASE_TYPE_GUID and PackageGuid is NULL
  //
  Status = HIIDatabase->ListPackageLists(
                          HIIDatabase,
                          PackageType,
                          NULL,
                          &HandleBufferLength,
                          Handle
                          );
  //
  // Check if the HandleBufferLength is too small
  //
  if ( EFI_BUFFER_TOO_SMALL == Status ) {
    gtBS->FreePool ( Handle );
    Handle = (EFI_HII_HANDLE*) SctAllocatePool ( HandleBufferLength );
    Status = HIIDatabase->ListPackageLists(
                            HIIDatabase,
                            PackageType,
                            NULL,
                            &HandleBufferLength,
                            Handle
                            );
  }

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid016,
                 L"HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists() returns EFI_INVALID_PARAMETER with PackageType is EFI_HII_DATABASE_TYPE_GUID and PackageGuid is  NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Release the resource of Handle
  //
  gtBS->FreePool ( Handle );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *Buffer;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  //
  // Allocate the mem for Buffer
  //
  Buffer = (EFI_HII_PACKAGE_LIST_HEADER*) SctAllocateZeroPool ( 1024 );
  
  //
  // Call ExportPackageLists with BufferSize set to be NULL
  //
  Status = HIIDatabase->ExportPackageLists(
                          HIIDatabase,
                          Handle,
                          NULL,
                          Buffer
                          );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid017,
                 L"HII_DATABASE_PROTOCOL.ExportPackageLists - ExportPackageLists() returns EFI_INVALID_PARAMETER with BufferSize being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Free the Buffer
  //
  gtBS->FreePool ( Buffer );
  
  //
  // Remvoe the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  UINTN                          BufferSize;


  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  BufferSize = 1024;
  
  //
  // Call ExportPackageLists with Buffer set to be NULL
  //
  Status = HIIDatabase->ExportPackageLists(
                          HIIDatabase,
                          Handle,
                          &BufferSize,
                          NULL
                          );
  //
  // Check if the BufferSize is too small
  //
  if ( EFI_BUFFER_TOO_SMALL == Status ) {
    Status = HIIDatabase->ExportPackageLists(
                            HIIDatabase,
                            Handle,
                            &BufferSize,
                            NULL
                            );
  }

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid018,
                 L"HII_DATABASE_PROTOCOL.ExportPackageLists - ExportPackageLists() returns EFI_INVALID_PARAMETER with Buffer being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Remvoe the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  UINTN                          BufferSize;
  EFI_HII_PACKAGE_LIST_HEADER    *Buffer;


  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  //
  // Init the NeededBufferSize
  //
  BufferSize = 10;
  
  //
  // Allocate the mem for Buffer
  //
  Buffer = (EFI_HII_PACKAGE_LIST_HEADER*) SctAllocateZeroPool ( BufferSize );
  
  //
  // Call ExportPackageLists with BufferSize indicates the Buffer is too small
  //
  Status = HIIDatabase->ExportPackageLists(
                          HIIDatabase,
                          Handle,
                          &BufferSize,
                          Buffer
                          );
  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid019,
                 L"HII_DATABASE_PROTOCOL.ExportPackageLists - ExportPackageLists() returns EFI_BUFFER_TOO_SMALL with BufferSize indicates the buffer is too small.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Remvoe the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  
  //
  // Free the Buffer
  //
  gtBS->FreePool ( Buffer );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  UINTN                          BufferSize;
  EFI_HII_PACKAGE_LIST_HEADER    *Buffer;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  
 
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  //
  // Remove the PackageList associated with Handle
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Allocate the mem for Buffer
  //
  BufferSize = PackageListLength;
  Buffer = (EFI_HII_PACKAGE_LIST_HEADER*) SctAllocateZeroPool ( BufferSize );
  if ( NULL == Buffer ){
    return Status;
  }
  
  //
  // Call ExportPackageLists with  Handle has been  already removed once
  //
  Status = HIIDatabase->ExportPackageLists(
                          HIIDatabase,
                          Handle,
                          &BufferSize,
                          Buffer
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid021,
                 L"HII_DATABASE_PROTOCOL.ExportPackageLists - ExportPackageLists() returns EFI_NOT_FOUND with handle has been already removed once.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Free the Buffer
  //
  gtBS->FreePool ( Buffer );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle,InvalidHandle;
  UINTN                          BufferSize;
  EFI_HII_PACKAGE_LIST_HEADER    *Buffer;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  //
  // Allocate the mem for Buffer
  //
  BufferSize = PackageListLength;
  Buffer = (EFI_HII_PACKAGE_LIST_HEADER*) SctAllocateZeroPool ( BufferSize );
  if ( NULL == Buffer ){
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    return Status;
  }
  
   //
  // Create a invalid Handle 
  //
  InvalidHandle = (EFI_HII_HANDLE)((UINT8*)Handle + 8);
  
  //
  // Call ExportPackageLists with the invalid handle 
  //
  Status = HIIDatabase->ExportPackageLists(
                          HIIDatabase,
                          InvalidHandle,
                          &BufferSize,
                          Buffer
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid022,
                 L"HII_DATABASE_PROTOCOL.ExportPackageLists - ExportPackageLists() returns EFI_NOT_FOUND with the invalid handle.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Free the Buffer
  //
  gtBS->FreePool ( Buffer );
  
  //
  // Remove the PackageList associated with Handle
  //
  Status = HIIDatabase->RemovePackageList(
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
BBTestRegisterPackageNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                           PackageType;
  EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType[] = {
                                    EFI_HII_DATABASE_NOTIFY_NEW_PACK,
                                    EFI_HII_DATABASE_NOTIFY_REMOVE_PACK,
                                    EFI_HII_DATABASE_NOTIFY_EXPORT_PACK,
                                    EFI_HII_DATABASE_NOTIFY_ADD_PACK,
                                    0
                                    };
  UINTN                            Index;


  PackageType = EFI_HII_PACKAGE_STRINGS;

  //
  // Call RegisterPackageNotify with NotifyHandle set to be NULL
  //
  for( Index=0; NotifyType[Index]; Index++ ) {
    Status = HIIDatabase->RegisterPackageNotify(
                            HIIDatabase,
                            PackageType,
                            NULL,
                            DoNothingPackageNotifyFn,
                            NotifyType[Index],
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
                   gHIIDatabaseBBTestConformanceAssertionGuid023,
                   L"HII_DATABASE_PROTOCOL.RegisterPackageNotify - RegisterPackageNotify() returns EFI_INVALID_PARAMETER with NotifyHandle been NULL.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterPackageNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                           PackageType;
  EFI_GUID                        PackageGuid;
  EFI_HANDLE                      NotifyHandle;
  EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType[] = {
                                    EFI_HII_DATABASE_NOTIFY_NEW_PACK,
                                    EFI_HII_DATABASE_NOTIFY_REMOVE_PACK,
                                    EFI_HII_DATABASE_NOTIFY_EXPORT_PACK,
                                    EFI_HII_DATABASE_NOTIFY_ADD_PACK,
                                    0
                                    };
  UINTN                            Index;


  //
  //Init the PacakageGuid
  //
  PackageType = EFI_HII_PACKAGE_STRINGS;
  PackageGuid = mPackageGuid;
  
  //
  // Call RegisterPackageNotify with PackageType is not Guid and PackageGuid not been NULL
  //
  for( Index=0; NotifyType[Index]; Index++ ) {
    Status = HIIDatabase->RegisterPackageNotify(
                            HIIDatabase,
                            PackageType,
                            &PackageGuid,
                            DoNothingPackageNotifyFn,
                            NotifyType[Index],
                            &NotifyHandle
                            );

    if ( EFI_INVALID_PARAMETER != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIDatabaseBBTestConformanceAssertionGuid024,
                   L"HII_DATABASE_PROTOCOL.RegisterPackageNotify - RegisterPackageNotify() returns EFI_INVALID_PARAMETER with PackageType is not Guid and PackageGuid not been NULL.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterPackageNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                           PackageType;
  EFI_HANDLE                      NotifyHandle;
  EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType[] = {
                                    EFI_HII_DATABASE_NOTIFY_NEW_PACK,
                                    EFI_HII_DATABASE_NOTIFY_REMOVE_PACK,
                                    EFI_HII_DATABASE_NOTIFY_EXPORT_PACK,
                                    EFI_HII_DATABASE_NOTIFY_ADD_PACK,
                                    0
                                    };
  UINTN                            Index;


  //
  //Init the PacakageGuid
  //
  PackageType = EFI_HII_PACKAGE_TYPE_GUID;
 
  
  //
  //Call RegisterPackageNotify with PackageType is EFI_HII_PACKAGE_TYPE_GUID and PackageGuid been NULL
  //
  for( Index=0; NotifyType[Index]; Index++ ) {
    Status = HIIDatabase->RegisterPackageNotify(
                            HIIDatabase,
                            PackageType,
                            NULL,
                            DoNothingPackageNotifyFn,
                            NotifyType[Index],
                            &NotifyHandle
                            );

    if ( EFI_INVALID_PARAMETER != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIDatabaseBBTestConformanceAssertionGuid025,
                   L"HII_DATABASE_PROTOCOL.RegisterPackageNotify - RegisterPackageNotify() returns EFI_INVALID_PARAMETER with PackageType is EFI_HII_PACKAGE_TYPE_GUID and PackageGuid been NULL.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                           PackageType;
  EFI_HANDLE                      NotifyHandle;
  EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType[] = {
                                    EFI_HII_DATABASE_NOTIFY_NEW_PACK,
                                    EFI_HII_DATABASE_NOTIFY_REMOVE_PACK,
                                    EFI_HII_DATABASE_NOTIFY_EXPORT_PACK,
                                    EFI_HII_DATABASE_NOTIFY_ADD_PACK,
                                    0
                                    };
  UINTN                            Index;

  PackageType = EFI_HII_PACKAGE_STRINGS;

  for( Index=0; NotifyType[Index]; Index++ ) {
    //
    // register a notify function
    //
    Status = HIIDatabase->RegisterPackageNotify(
                            HIIDatabase,
                            PackageType,
                            NULL,
                            DoNothingPackageNotifyFn,
                            NotifyType[Index],
                            &NotifyHandle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    
    //
    // Unregister the notify function
    //
    Status = HIIDatabase->UnregisterPackageNotify(
                            HIIDatabase,
                            NotifyHandle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }

    //
    // Call UnregisterPackageNotify with the NotifyHandle has been removed already
    //
    Status = HIIDatabase->UnregisterPackageNotify(
                            HIIDatabase,
                            NotifyHandle
                            );

    if ( EFI_NOT_FOUND != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIDatabaseBBTestConformanceAssertionGuid026,
                   L"HII_DATABASE_PROTOCOL.UnregisterPackageNotify - UnregisterPackageNotify() returns EFI_NOT_FOUND with the NotifyHandle has been removed already.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                           PackageType;
  EFI_HANDLE                      NotifyHandle;
  EFI_HANDLE                      InvalidNotifyHandle;
  EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType[] = {
                                    EFI_HII_DATABASE_NOTIFY_NEW_PACK,
                                    EFI_HII_DATABASE_NOTIFY_REMOVE_PACK,
                                    EFI_HII_DATABASE_NOTIFY_EXPORT_PACK,
                                    EFI_HII_DATABASE_NOTIFY_ADD_PACK,
                                    0
                                    };
  UINTN                            Index;


  PackageType = EFI_HII_PACKAGE_STRINGS;

  for( Index=0; NotifyType[Index]; Index++ ) {
    //
    // register a notify function
    //
    Status = HIIDatabase->RegisterPackageNotify(
                            HIIDatabase,
                            PackageType,
                            NULL,
                            DoNothingPackageNotifyFn,
                            NotifyType[Index],
                            &NotifyHandle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    
    InvalidNotifyHandle = (EFI_HANDLE)((UINT8*)(NotifyHandle) + 8);

    //
    // Call UnregisterPackageNotify with the invalid NotifyHandle
    //
    Status = HIIDatabase->UnregisterPackageNotify(
                            HIIDatabase,
                            InvalidNotifyHandle
                            );

    if ( EFI_NOT_FOUND != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIDatabaseBBTestConformanceAssertionGuid027,
                   L"HII_DATABASE_PROTOCOL.UnregisterPackageNotify - UnregisterPackageNotify() returns EFI_NOT_FOUND with an invalid NotifyHandle.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    // Unregister the notify function
    //
    Status = HIIDatabase->UnregisterPackageNotify(
                            HIIDatabase,
                            NotifyHandle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }

  }

    

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                           PackageType;
  EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType[] = {
                                    EFI_HII_DATABASE_NOTIFY_NEW_PACK,
                                    EFI_HII_DATABASE_NOTIFY_REMOVE_PACK,
                                    EFI_HII_DATABASE_NOTIFY_EXPORT_PACK,
                                    EFI_HII_DATABASE_NOTIFY_ADD_PACK,
                                    0
                                    };
  UINTN                            Index;
  PackageType = EFI_HII_PACKAGE_STRINGS;

  for( Index=0; NotifyType[Index]; Index++ ) {
    //
    // Call UnregisterPackageNotify with NotifyHandle been NULL
    //
    Status = HIIDatabase->UnregisterPackageNotify(
                            HIIDatabase,
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
                   gHIIDatabaseBBTestConformanceAssertionGuid028,
                   L"HII_DATABASE_PROTOCOL.UnregisterPackageNotify - UnregisterPackageNotify() returns EFI_NOT_FOUND with NotifyHandle been NULL.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_GUID              KeyGuidBuffer;

  //
  // Call FindKeyboardLayouts with KeyGuidBufferLength been NULL
  //
  Status = HIIDatabase->FindKeyboardLayouts(
                          HIIDatabase,
                          NULL,
                          &KeyGuidBuffer
                          );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid029,
                 L"HII_DATABASE_PROTOCOL.FindKeyboardLayouts - FindKeyboardLayouts() returns EFI_INVALID_PARAMETER with KeyGuidBufferLength been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                KeyGuidBufferLength;

  KeyGuidBufferLength = 10 * sizeof(EFI_GUID);
  
  //
  // Call FindKeyboardLayouts with KeyGuidBuffer been NULL
  //
  Status = HIIDatabase->FindKeyboardLayouts(
                          HIIDatabase,
                          &KeyGuidBufferLength,
                          NULL
                          );
  //
  // Check if the KeyGuidBufferLength is too small
  //
  if ( EFI_BUFFER_TOO_SMALL == Status ) {
    Status = HIIDatabase->FindKeyboardLayouts(
                            HIIDatabase,
                            &KeyGuidBufferLength,
                            NULL
                            );
  }
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid030,
                 L"HII_DATABASE_PROTOCOL.FindKeyboardLayouts - FindKeyboardLayouts() returns EFI_INVALID_PARAMETER with KeyGuidBuffer been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                KeyGuidBufferLength;
  EFI_GUID              *KeyGuidBuffer;

  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Call NewPackageList to add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  if ( EFI_SUCCESS != Status) { 
    return Status;
  } 

  //
  // Init the KeyGuidBufferLength been too small
  //
  KeyGuidBufferLength = 1 * sizeof(EFI_GUID);

  KeyGuidBuffer = (EFI_GUID*) SctAllocateZeroPool ( KeyGuidBufferLength );
  
  //
  // Call FindKeyboardLayouts with KeyGuidBufferLength indicates the buffer is too small
  //
  Status = HIIDatabase->FindKeyboardLayouts(
                          HIIDatabase,
                          &KeyGuidBufferLength,
                          KeyGuidBuffer
                          );
  
  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid031,
                 L"HII_DATABASE_PROTOCOL.FindKeyboardLayouts - FindKeyboardLayouts() returns EFI_BUFFER_TOO_SMALL with KeyGuidBufferLength indicates the buffer is too small.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  
  gtBS->FreePool ( KeyGuidBuffer );

  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR (Status) )
  	return Status;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_KEYBOARD_LAYOUT    KeyboardLayout;

  //
  // Call GetKeyboardLayout with KeyboardLayoutLength been NULL
  //
  Status = HIIDatabase->GetKeyboardLayout(
                          HIIDatabase,
                          NULL,
                          NULL,
                          &KeyboardLayout
                          );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid032,
                 L"HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout() returns EFI_INVALID_PARAMETER with KeyboardLayoutLength been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                KeyboardLayoutLength;
  
  KeyboardLayoutLength = 1024 * 32;

  //
  // Call GetKeyboardLayout with KeyboardLayout been NULL
  //
  Status = HIIDatabase->GetKeyboardLayout(
                          HIIDatabase,
                          NULL,
                          &KeyboardLayoutLength,
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
                 gHIIDatabaseBBTestConformanceAssertionGuid033,
                 L"HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout() returns EFI_INVALID_PARAMETER with KeyboardLayout been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                     KeyboardLayoutLength;
  EFI_HII_KEYBOARD_LAYOUT    *KeyboardLayout;

  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;

  UINT16                     LayoutLength = 0x5d;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Call NewPackageList to add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  if ( EFI_SUCCESS != Status ) { 
    return Status;
  } 
  

  //
  // Init the KeyGuidBufferLength and KeyGuidBuffer
  //
  KeyboardLayoutLength = 32;
  KeyboardLayout = (EFI_HII_KEYBOARD_LAYOUT*) SctAllocateZeroPool ( KeyboardLayoutLength );
  //
  // Call GetKeyboardLayout
  //
  Status = HIIDatabase->GetKeyboardLayout(
                          HIIDatabase,
                          &mKBLayoutGuid11,
                          &KeyboardLayoutLength,
                          KeyboardLayout
                          );
  //
  // Check if the buffer too small
  //
  if ( EFI_BUFFER_TOO_SMALL != Status || KeyboardLayoutLength != LayoutLength ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid034,
                 L"HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout() returns EFI_BUFFER_TOO_SMALL with KeyboardLayoutLength not enough.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool ( KeyboardLayout );

  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR (Status) )
  	return Status;
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                     KeyboardLayoutLength;
  EFI_HII_KEYBOARD_LAYOUT    *KeyboardLayout;

  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;


  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
    
  //
  // Call NewPackageList to add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  if ( EFI_SUCCESS != Status ) { 
    return Status;
  } 
  
  //
  // Init the KeyGuidBufferLength and KeyGuidBuffer
  //
  KeyboardLayoutLength = 1024 * 32;
  KeyboardLayout = (EFI_HII_KEYBOARD_LAYOUT*) SctAllocateZeroPool ( KeyboardLayoutLength );
  //
  // Call GetKeyboardLayout with the requested keyboard layout not found
  //
  Status = HIIDatabase->GetKeyboardLayout(
                          HIIDatabase,
                          &mKBLayoutGuid21,
                          &KeyboardLayoutLength,
                          KeyboardLayout
                          );
 
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid035,
                 L"HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout() returns EFI_NOT_FOUND  with the requested keyboard layout not found.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool ( KeyboardLayout );

  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR (Status) )
  	return Status;
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetKeyboardLayoutConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  //
  // Call SetKeyboardLayout with KeyGuid been NULL
  //
  Status = HIIDatabase->SetKeyboardLayout(
                          HIIDatabase,
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
                 gHIIDatabaseBBTestConformanceAssertionGuid036,
                 L"HII_DATABASE_PROTOCOL.SetKeyboardLayout - SetKeyboardLayout() returns EFI_INVALID_PARAMETER with KeyGuid set to be NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetKeyboardLayoutConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;

  

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  //
  // Call NewPackageList to add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  
  if ( EFI_SUCCESS != Status ) { 
    return Status;
  } 
  
  //
  // Call SetKeyboardLayout with the referenced  keyboard layout not found
  //
  Status = HIIDatabase->SetKeyboardLayout(
                          HIIDatabase,
                          &mKBLayoutGuid22
                          );

  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid037,
                 L"HII_DATABASE_PROTOCOL.SetKeyboardLayout - SetKeyboardLayout() returns EFI_NOT_FOUND with the referenced  keyboard layout not found.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR (Status) )
  	return Status;
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 PackageListHandle;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;

  //
  // Add the PackageList to the HII database
  //
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &PackageListHandle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Call GetPackageListHandle with DriverHandle set to be NULL
  //
  Status = HIIDatabase->GetPackageListHandle(
                          HIIDatabase,
                          PackageListHandle,
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
                 gHIIDatabaseBBTestConformanceAssertionGuid038 ,
                 L"HII_DATABASE_PROTOCOL.GetPackageListHandle - GetPackageListHandle() returns EFI_INVALID_PARAMETER with DriverHandle set to be NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          PackageListHandle
                          );

  //
  // Release the resource of DriverHandle
  //

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HANDLE                     DriverHandle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 PackageListHandle;
  EFI_HANDLE                     GetDriverHandle;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;

  CreateDeviceHandle (&DriverHandle);
  
  if (DriverHandle != NULL) {
    //
    // Add the PackageList to the HII database
    //
    Status = HIIDatabase->NewPackageList(
                            HIIDatabase,
                            PackageList,
                            DriverHandle,
                            &PackageListHandle
                            );
    if ( EFI_ERROR(Status) ) {
      // 
      // Release the resource of DriverHandle
      //
      ReleaseDeviceHandle (DriverHandle);
      return Status;
    }
  
    //
    // Remove the PackageList from the HII database
    //
    Status = HIIDatabase->RemovePackageList(
                            HIIDatabase,
                            PackageListHandle
                            );
    if ( EFI_ERROR(Status) ) {
      //
      // Release the resource of DriverHandle
      //
      ReleaseDeviceHandle (DriverHandle);
      return Status;
    }

    //
    // Call GetPackageListHandle with PackageListHandle has been removed already
    //
    Status = HIIDatabase->GetPackageListHandle(
                            HIIDatabase,
                            PackageListHandle,
                            &GetDriverHandle
                            );
  
    if ( EFI_INVALID_PARAMETER != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIDatabaseBBTestConformanceAssertionGuid039 ,
                   L"HII_DATABASE_PROTOCOL.GetPackageListHandle - GetPackageListHandle() returns EFI_INVALID_PARAMETER with PackageListHandle has been removed already.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    //
    // Release the resource of DriverHandle
    //
    ReleaseDeviceHandle (DriverHandle);
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HANDLE                     DriverHandle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 PackageListHandle;
  EFI_HANDLE                     GetDriverHandle;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;

  CreateDeviceHandle (&DriverHandle);
  
  if (DriverHandle != NULL) {
    //
    // Add the PackageList to the HII database
    //
    Status = HIIDatabase->NewPackageList(
                            HIIDatabase,
                            PackageList,
                            DriverHandle,
                            &PackageListHandle
                            );
    if ( EFI_ERROR(Status) ) {
      // 
      // Release the resource of DriverHandle
      //
      ReleaseDeviceHandle (DriverHandle);
      return Status;
    }
  
    //
    // Remove the PackageList from the HII database
    //
    Status = HIIDatabase->RemovePackageList(
                            HIIDatabase,
                            PackageListHandle
                            );
    if ( EFI_ERROR(Status) ) {
      //
      // Release the resource of DriverHandle
      //
      ReleaseDeviceHandle (DriverHandle);
      return Status;
    }

    //
    // Call GetPackageListHandle with an invalid PackageListHandle
    //
    Status = HIIDatabase->GetPackageListHandle(
                            HIIDatabase,
                            (EFI_HII_HANDLE)((UINT8*)(&PackageListHandle) + 8),
                            &GetDriverHandle
                            );
  
    if ( EFI_INVALID_PARAMETER != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIDatabaseBBTestConformanceAssertionGuid040 ,
                   L"HII_DATABASE_PROTOCOL.GetPackageListHandle - GetPackageListHandle() returns EFI_INVALID_PARAMETER with PackageListHandle has been removed already.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    //
    // Release the resource of DriverHandle
    //
    ReleaseDeviceHandle (DriverHandle);
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HANDLE            DriverHandle;

  //
  // Call GetPackageListHandle with PackageListHandle set to be NULL
  //
  Status = HIIDatabase->GetPackageListHandle(
                          HIIDatabase,
                          NULL,
                          &DriverHandle
                          );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestConformanceAssertionGuid041 ,
                 L"HII_DATABASE_PROTOCOL.GetPackageListHandle - GetPackageListHandle() returns EFI_INVALID_PARAMETER with PackageListHandle set to be NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

STATIC
VOID
CreateDeviceHandle (
  OUT EFI_HANDLE  *DeviceHandle
  )
{
  EFI_HANDLE                  Handle = NULL;
  EFI_STATUS                  Status;

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    *DeviceHandle = NULL;
  } else {
    *DeviceHandle = Handle;
  }
}

STATIC
VOID
ReleaseDeviceHandle (
  IN EFI_HANDLE    DeviceHandle
  )
{
  if (DeviceHandle == NULL) {
    return;
  }

  gtBS->UninstallProtocolInterface (DeviceHandle, &mTestNoInterfaceProtocol2Guid, NULL);
}
