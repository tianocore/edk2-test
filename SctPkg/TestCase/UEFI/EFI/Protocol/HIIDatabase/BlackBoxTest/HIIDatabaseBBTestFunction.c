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
    HIIDatabaseBBTestFunction.c

Abstract:
    for EFI Driver HII Database Protocol's function Test

--*/

#include "HIIDatabaseBBTestMain.h"

extern UINT8 mPackageList1[];
extern UINT8 mPackageList2[];
extern EFI_GUID mPackageGuid;
extern EFI_GUID mKBLayoutGuid11;
extern EFI_GUID mKBLayoutGuid12;

#define PackageList1Length    512
#define PackageList2Length    512

#define ActuPackageList1Length    322 //342
#define ActuPackageList2Length    254


//EFI_GUID mTestNoInterfaceProtocol2Guid = TEST_NO_INTERFACE_PROTOCOL_2_GUID;

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
BBTestNewPackageListFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
BBTestRemovePackageListFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
BBTestUpdatePackageListFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
BBTestListPackageListsFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
BBTestExportPackageListsFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
BBTestExportPackageListsFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );
  
EFI_STATUS
BBTestFindKeyboardLayoutsFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
BBTestGetKeyboardLayoutFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
BBTestSetKeyboardLayoutFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

EFI_STATUS
BBTestGetPackageListHandleFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  );

//
//Test Cases
//
EFI_STATUS
BBTestNewPackageListFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestNewPackageListFunctionTestCheckpoint1( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestRemovePackageListFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestRemovePackageListFunctionTestCheckpoint1( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestUpdatePackageListFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestUpdatePackageListFunctionTestCheckpoint1( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestListPackageListsFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestListPackageListsFunctionTestCheckpoint1( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestExportPackageListsFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestExportPackageListsFunctionTestCheckpoint1( StandardLib, HIIDatabase );

  BBTestExportPackageListsFunctionTestCheckpoint2( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestRegisterPackageNotifyFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestUnregisterPackageNotifyFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestFindKeyboardLayoutsFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestFindKeyboardLayoutsFunctionTestCheckpoint1( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetKeyboardLayoutFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetKeyboardLayoutFunctionTestCheckpoint1( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetKeyboardLayoutFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestSetKeyboardLayoutFunctionTestCheckpoint1( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetPackageListHandleFunctionTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetPackageListHandleFunctionTestCheckpoint1 ( StandardLib, HIIDatabase );
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
BBTestNewPackageListFunctionTestCheckpoint1 (
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
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid001,
                 L"HII_DATABASE_PROTOCOL.NewPackageList - NewPackageList() returns EFI_SUCCESS with valid inputs.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Remove the PackageList frome the HII database
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
BBTestRemovePackageListFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  
  UINTN                           BufferSize;
  EFI_HII_PACKAGE_LIST_HEADER     *Buffer;

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
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid002,
                 L"HII_DATABASE_PROTOCOL.RemovePackageList - RemovePackageList() returns EFI_SUCCESS with valid inputs.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Call ExportPackageList to Check the PackageList has been removed
  //
  BufferSize = PackageList1Length;
  Buffer = (EFI_HII_PACKAGE_LIST_HEADER*) SctAllocateZeroPool ( BufferSize );
  
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
                 gHIIDatabaseBBTestFunctionAssertionGuid003 ,
                 L"HII_DATABASE_PROTOCOL.RemovePackageList - ExportPackageLists() returns EFI_NOT_FOUND when RemovePackageList work.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Release the Buffer and resource of DriverHandle
  //
  gtBS->FreePool ( Buffer );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestUpdatePackageListFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList, *UpdatePackageList;
  EFI_HII_HANDLE                 Handle;
  
//  UINTN                           BufferSize;
//  EFI_HII_PACKAGE_LIST_HEADER     *Buffer;
  
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
  // Call UpdatePackageList Update the PackageList in the HII database
  //
  Status = HIIDatabase->UpdatePackageList(
                          HIIDatabase,
                          Handle,
                          UpdatePackageList
                          );
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid004,
                 L"HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList() returns EFI_SUCCESS with valid inputs.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  if ( AssertionType == EFI_TEST_ASSERTION_FAILED ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    return Status;
  }

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestListPackageListsFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList, *UpdatePackageList;
  EFI_HII_HANDLE                 Handle, UpdateHandle;
  
  UINT8                    PackageType;
  EFI_GUID                 PackageGuid;
  UINTN                    HandleBufferLength, ReturnLength;
  EFI_HII_HANDLE           *HandleBuffer;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;
  UpdatePackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList2;
  //
  // Add the PackageList and UpdatePackageList to the HII database
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
  
  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          UpdatePackageList,
                          NULL,
                          &UpdateHandle
                          );
  if ( EFI_ERROR(Status) ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    return Status;
  }
  
  //
  // Call ListPackageLists to retrieve two PackageLists just been installed
  //
  PackageType = EFI_HII_PACKAGE_TYPE_GUID;
  PackageGuid = mPackageGuid;
  ReturnLength = 2 * sizeof(EFI_HII_HANDLE);
  HandleBufferLength = 5 * sizeof(EFI_HII_HANDLE);
  HandleBuffer = (EFI_HII_HANDLE*) SctAllocateZeroPool (HandleBufferLength);
  Status = HIIDatabase->ListPackageLists(
                          HIIDatabase,
                          PackageType,
                          &PackageGuid,
                          &HandleBufferLength,
                          HandleBuffer
                          );
  
  if ( EFI_SUCCESS != Status || HandleBufferLength != ReturnLength ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid005 ,
                 L"HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists() returns EFI_SUCCESS with valid inputs and return length checked.",
                 L"%a:%d: Status - %r ReturnLength - %d HandleBufferLength - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ReturnLength,
                 HandleBufferLength
                 );
  

  //
  // Remove the PackageList and UpdatePackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          UpdateHandle
                          );

  //
  // Release the Buffer and resource of DriverHandle and UpdateDriverHandle
  //
  gtBS->FreePool ( HandleBuffer );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestExportPackageListsFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  
  UINTN                           BufferSize;
  EFI_HII_PACKAGE_LIST_HEADER     *Buffer;

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
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Export the PackageList and compare the result
  //
  BufferSize = PackageList1Length;
  Buffer = (EFI_HII_PACKAGE_LIST_HEADER*) SctAllocateZeroPool ( BufferSize );
  
  Status = HIIDatabase->ExportPackageLists(
                          HIIDatabase,
                          Handle,
                          &BufferSize,
                          Buffer
                          );

  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    //
    // Compare the result
    //
//    if ( BufferSize != ActuPackageList1Length )
//	  AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid006,
                 L"HII_DATABASE_PROTOCOL.ExportPackageLists - ExportPackageLists() returns EFI_SUCCESS with valid inputs and result checked.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Remove the PackageList frome the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  
  //
  // Release Buffer and the resource of DriverHandle
  //
  gtBS->FreePool ( Buffer );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestExportPackageListsFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  
  UINTN                           BufferSize;
  EFI_HII_PACKAGE_LIST_HEADER     *Buffer;

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
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Export the PackageList and compare the result
  //
  BufferSize = PackageList1Length;
  Buffer = (EFI_HII_PACKAGE_LIST_HEADER*) SctAllocateZeroPool ( BufferSize );
  
  Status = HIIDatabase->ExportPackageLists(
                          HIIDatabase,
                          NULL,
                          &BufferSize,
                          Buffer
                          );

  if ( EFI_SUCCESS == Status ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if (EFI_BUFFER_TOO_SMALL == Status && BufferSize > PackageList1Length) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    //
    // Compare the result
    //
//    if ( BufferSize != ActuPackageList1Length )
//	  AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (EFI_BUFFER_TOO_SMALL == Status) {
    gtBS->FreePool ( Buffer );
    Buffer = (EFI_HII_PACKAGE_LIST_HEADER*) SctAllocateZeroPool ( BufferSize );
    Status = HIIDatabase->ExportPackageLists(
                            HIIDatabase,
                            NULL,
                            &BufferSize,
                            Buffer
                            );
    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
      
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid012,
                 L"HII_DATABASE_PROTOCOL.ExportPackageLists - ExportPackageLists() returns EFI_SUCCESS or EFI_BUFFER_TOO_SMALL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Remove the PackageList frome the HII database
  //
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  
  //
  // Release Buffer and the resource of DriverHandle
  //
  gtBS->FreePool ( Buffer );

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestFindKeyboardLayoutsFunctionTestCheckpoint1 (
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
  
  if ( EFI_SUCCESS != Status ) { 
    return Status;
  } 

  //
  // Init the KeyGuidBufferLength and KeyGuidBuffer
  //
  KeyGuidBufferLength = 10 * sizeof(EFI_GUID);
  KeyGuidBuffer = (EFI_GUID*) SctAllocateZeroPool ( KeyGuidBufferLength );
  //
  // Call FindKeyboardLayouts
  //
  Status = HIIDatabase->FindKeyboardLayouts(
                          HIIDatabase,
                          &KeyGuidBufferLength,
                          KeyGuidBuffer
                          );
  //
  // Check if the buffer too small
  //
  if ( EFI_BUFFER_TOO_SMALL == Status )
  {
    gtBS->FreePool ( KeyGuidBuffer );
    KeyGuidBuffer = (EFI_GUID*) SctAllocateZeroPool ( KeyGuidBufferLength );
    Status = HIIDatabase->FindKeyboardLayouts(
                            HIIDatabase,
                            &KeyGuidBufferLength,
                            KeyGuidBuffer
                            );
  }

  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid007,
                 L"HII_DATABASE_PROTOCOL.FindKeyboardLayouts - FindKeyboardLayouts() returns EFI_SUCCESS with valid inputs.",
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
BBTestGetKeyboardLayoutFunctionTestCheckpoint1 (
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

//  UINT16                         LayoutLength = 0x37;

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
  if ( EFI_BUFFER_TOO_SMALL == Status ){
    gtBS->FreePool ( KeyboardLayout );
    KeyboardLayout = (EFI_HII_KEYBOARD_LAYOUT*) SctAllocateZeroPool ( KeyboardLayoutLength );
    Status = HIIDatabase->GetKeyboardLayout(
                            HIIDatabase,
                            NULL,
                            &KeyboardLayoutLength,
                            KeyboardLayout
                            );
  }

//  if ( EFI_SUCCESS != Status || KeyboardLayoutLength != LayoutLength ) {
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid008,
                 L"HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout() returns EFI_SUCCESS with valid inputs.",
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
BBTestSetKeyboardLayoutFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  UINT16                         KeyboardLayoutLength;
  EFI_HII_KEYBOARD_LAYOUT        *KeyboardLayout;
 

  //
  // retrieve current keyboard layout 
  //
  KeyboardLayoutLength = 1024 * 32;
  KeyboardLayout = (EFI_HII_KEYBOARD_LAYOUT*) SctAllocateZeroPool ( KeyboardLayoutLength );
  if (KeyboardLayout == NULL)
    return EFI_UNSUPPORTED;
  
  Status = HIIDatabase->GetKeyboardLayout(
                          HIIDatabase,
                          NULL,
                          &KeyboardLayoutLength,
                          KeyboardLayout
                          );
  if ( Status == EFI_NOT_FOUND ) {
    gtBS->FreePool ( KeyboardLayout );
	return EFI_UNSUPPORTED;
  }
  
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
    gtBS->FreePool ( KeyboardLayout );
    return Status;
  } 
  
  //
  // Call SetKeyboardLayout
  //
  Status = HIIDatabase->SetKeyboardLayout(
                          HIIDatabase,
                          &mKBLayoutGuid12
                          );

  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIDatabaseBBTestFunctionAssertionGuid009,
                 L"HII_DATABASE_PROTOCOL.SetKeyboardLayout - SetKeyboardLayout() returns EFI_SUCCESS with valid inputs.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  if ( EFI_SUCCESS == Status ) {
    Status = HIIDatabase->SetKeyboardLayout(
                            HIIDatabase,
                            (EFI_GUID *)((UINT8 *)KeyboardLayout + 2)
                            );
    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIDatabaseBBTestFunctionAssertionGuid010,
                   L"HII_DATABASE_PROTOCOL.SetKeyboardLayout - SetKeyboardLayout() returns EFI_SUCCESS with valid inputs.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  
  Status = HIIDatabase->RemovePackageList(
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR (Status) )
  	return Status;
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetPackageListHandleFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HANDLE                     DriverHandle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_HII_HANDLE                 Handle;
  EFI_HANDLE                     RetrieveDriverHandle;
  
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
                            &Handle
                            );
    if ( EFI_ERROR(Status) ) {
      ReleaseDeviceHandle (DriverHandle);
      return Status;
    }
  
    //
    // Call GetPackageListHandle
    //
    Status = HIIDatabase->GetPackageListHandle(
                            HIIDatabase,
                            Handle,
                            &RetrieveDriverHandle
                            );
  
    if ( EFI_SUCCESS != Status || DriverHandle != RetrieveDriverHandle ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIDatabaseBBTestFunctionAssertionGuid011 ,
                   L"HII_DATABASE_PROTOCOL.GetPackageListHandle - GetPackageListHandle() returns EFI_SUCCESS with valid inputs and get the correct result.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   __LINE__,
  				 Status
                   );

    ReleaseDeviceHandle (DriverHandle);

	Status = HIIDatabase->RemovePackageList(
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR (Status) )
  	  return Status;
  }

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
