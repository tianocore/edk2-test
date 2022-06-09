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
    VlanConfigBBTestFunction.c

Abstract:
    for EFI Driver Vlan Config Protocol's function Test

--*/
#include "SctLib.h"
#include "VlanConfigBBTestMain.h"

EFI_STATUS
EFIAPI
BBTestSetFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
EFIAPI
BBTestFindFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );

EFI_STATUS
EFIAPI
BBTestFindFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
EFIAPI
BBTestRemoveFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestSetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_VLAN_CONFIG_PROTOCOL              *VlanConfig;

  //
  // init
  //
  VlanConfig = (EFI_VLAN_CONFIG_PROTOCOL*)ClientInterface;

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
  BBTestSetFunctionTestCheckpoint1( StandardLib, VlanConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFindFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_VLAN_CONFIG_PROTOCOL              *VlanConfig;

  //
  // init
  //
  VlanConfig = (EFI_VLAN_CONFIG_PROTOCOL*)ClientInterface;

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
  BBTestFindFunctionTestCheckpoint1( StandardLib, VlanConfig );

  BBTestFindFunctionTestCheckpoint2( StandardLib, VlanConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRemoveFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_VLAN_CONFIG_PROTOCOL              *VlanConfig;

  //
  // init
  //
  VlanConfig = (EFI_VLAN_CONFIG_PROTOCOL*)ClientInterface;

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
  BBTestRemoveFunctionTestCheckpoint1( StandardLib, VlanConfig );
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestSetFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                NumberOfVlan;
  UINT16                VlanId;
  EFI_VLAN_FIND_DATA    *Entries;
  UINT8                 Priority1;
  UINT8                 Priority2;

  Priority1 = 1;
  Priority2 = 2;
  Entries = NULL;
  
  Status = GetAnInvalidVlanId ( VlanConfig, &VlanId );
  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Set a new VlanId fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;    
  }
  
  //
  // Call Set to config a priotity
  //
  Status = VlanConfig->Set(
                         VlanConfig,
                         VlanId,
                         Priority1
                         );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid001,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Set - Set() returns EFI_SUCCESS with valid VlanId/Priority.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( AssertionType == EFI_TEST_ASSERTION_FAILED )
    return Status;
  
  //
  // Call Find to check the Priority
  //
  Status = VlanConfig->Find(
                         VlanConfig,
                         &VlanId,
                         &NumberOfVlan,
                         &Entries
                         );
  
  if ( Status != EFI_SUCCESS || NumberOfVlan != 1 || Entries == NULL || \
  	   Entries->Priority != Priority1 || Entries->VlanId != VlanId ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid002,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Set - Set() returns EFI_SUCCESS with valid VlanId/Priority.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( Entries != NULL ) {
    gtBS->FreePool (Entries);
    Entries = NULL;
  }

  if ( AssertionType == EFI_TEST_ASSERTION_FAILED ) {
    Status = VlanConfig->Remove( VlanConfig, VlanId );
    return Status;
  }

  //
  // Call Set to config a new priotity
  //
  Status = VlanConfig->Set(
                         VlanConfig,
                         VlanId,
                         Priority2
                         );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid003,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Set - Set() returns EFI_SUCCESS with valid VlanId/Priority.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( AssertionType == EFI_TEST_ASSERTION_FAILED )
    return Status;
  
  //
  // Call Find to check the Priority
  //
  Status = VlanConfig->Find(
                         VlanConfig,
                         &VlanId,
                         &NumberOfVlan,
                         &Entries
                         );

  if ( Status != EFI_SUCCESS || NumberOfVlan != 1 || Entries == NULL || \
       Entries->Priority != Priority2 || Entries->VlanId != VlanId ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid004,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Set - Set() returns EFI_SUCCESS with valid VlanId/Priority.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  
  if ( Entries != NULL ) {
    gtBS->FreePool (Entries);
  }

  Status = VlanConfig->Remove(
                         VlanConfig,
                         VlanId
                         );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFindFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                NumberOfVlan;
  EFI_VLAN_FIND_DATA    *Entries;

  Entries = NULL;

  Status = VlanConfig->Find(
                         VlanConfig,
                         NULL,
                         &NumberOfVlan,
                         &Entries
                         );
  
  if ( EFI_SUCCESS == Status && NumberOfVlan > 0 && Entries != NULL ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ( EFI_NOT_FOUND == Status && NumberOfVlan == 0 && Entries == NULL ){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid005,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Find - Find() returns EFI_SUCCESS / EFI_NOT_FOUND.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( Entries != NULL ) {
    gtBS->FreePool (Entries);
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFindFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                NumberOfVlan;
  UINT16                VlanId;
  EFI_VLAN_FIND_DATA    *Entries;
  UINT8                 Priority;

  Priority = 1;
  Entries = NULL;
  
  Status = GetAnInvalidVlanId ( VlanConfig, &VlanId );
  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Set a new VlanId fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;    
  }
  
  //
  // Call Set to config a priotity
  //
  Status = VlanConfig->Set(
                         VlanConfig,
                         VlanId,
                         Priority
                         );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Set - Set() returns EFI_SUCCESS with valid VlanId/Priority.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if ( AssertionType == EFI_TEST_ASSERTION_FAILED )
    return Status;
  
  //
  // Call Find to check the Priority
  //
  Status = VlanConfig->Find(
                         VlanConfig,
                         &VlanId,
                         &NumberOfVlan,
                         &Entries
                         );
  if ( Status != EFI_SUCCESS || NumberOfVlan != 1 || Entries == NULL || \
       Entries->Priority != Priority || Entries->VlanId != VlanId ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid006,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Find - Find() returns EFI_SUCCESS and check with valid Entries/NumberOfVlan.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( Entries != NULL ) {
    gtBS->FreePool (Entries);
    Entries = NULL;
  }

  if ( AssertionType == EFI_TEST_ASSERTION_FAILED ) {
    Status = VlanConfig->Remove( VlanConfig, VlanId );
    return Status;
  }

  //
  // Call Remove to delete the VlanId 
  //
  Status = VlanConfig->Remove(
                         VlanConfig,
                         VlanId
                         );
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Remove - Remove() returns EFI_SUCCESS with valid VlanId.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if ( AssertionType == EFI_TEST_ASSERTION_FAILED )
    return Status;
  
  //
  // Call Find to check the Priority
  //
  Status = VlanConfig->Find(
                         VlanConfig,
                         &VlanId,
                         &NumberOfVlan,
                         &Entries
                         );
  if ( Status != EFI_NOT_FOUND || NumberOfVlan != 0 || Entries != NULL ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid007,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Find - Find() returns EFI_NOT_FOUND with valid VlanId/NumberOfVlan/Entries.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRemoveFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                VlanId;
  EFI_VLAN_FIND_DATA    *Entries;
  UINT8                 Priority;

  Priority = 1;
  Entries = NULL;
  
  Status = GetAnInvalidVlanId ( VlanConfig, &VlanId );
  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Set a new VlanId fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;    
  }
  
  //
  // Call Set to config a priority
  //
  Status = VlanConfig->Set(
                         VlanConfig,
                         VlanId,
                         Priority
                         );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Set - Set() returns EFI_SUCCESS with valid VlanId/Priority.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if ( AssertionType == EFI_TEST_ASSERTION_FAILED )
    return Status;

  //
  // Call Remove to remove the same VlanId
  //
  Status = VlanConfig->Remove(
                         VlanConfig,
                         VlanId
                         );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid008,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Remove - Remove() returns EFI_SUCCESS with valid VlanId.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if ( AssertionType != EFI_TEST_ASSERTION_PASSED )
    return Status;

  //
  // Call Remove to remove the same VlanId again
  //
  Status = VlanConfig->Remove(
                         VlanConfig,
                         VlanId
                         );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestFunctionAssertionGuid009,
                 L"EFI_VLAN_CONFIG_PROTOCOL.Remove - Remove() returns EFI_NOT_FOUND with valid VlanId.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  return EFI_SUCCESS;
}

