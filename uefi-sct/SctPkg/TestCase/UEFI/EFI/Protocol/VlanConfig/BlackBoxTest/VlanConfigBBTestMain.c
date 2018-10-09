/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  VlanConfigBBTestMain.c

Abstract:

  Test Driver of Vlan Config Protocol

--*/

#include "SctLib.h"
#include "VlanConfigBBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_VLAN_CONFIG_PROTOCOL_TEST_REVISION,
  EFI_VLAN_CONFIG_PROTOCOL_GUID,
  L"VLAN Config Protocol Test",
  L"UEFI VLAN Config Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101,
    L"SetFunction",
    L"Function auto test for Vlan Config Protocol Set().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetFunctionTest
  },
  {
    EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102,
    L"FindFunction",
    L"Function auto test for Vlan Config Protocol Find().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestFindFunctionTest
  },
  {
    EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103,
    L"RemoveFunction",
    L"Function auto test for Vlan Config Protocol Remove().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRemoveFunctionTest
  },
  
  {
    EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0201,
    L"SetConformance",
    L"Conformance auto test for Vlan Config Protocol Set().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetConformanceTest
  },
  {
    EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0202,
    L"FindConformance",
    L"Conformance auto test for Vlan Config Protocol Find().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestFindConformanceTest
  },
  {
    EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0203,
    L"RemoveConformance",
    L"Conformance auto test for Vlan Config Protocol Remove().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRemoveConformanceTest
  },
  
  0
};

//
// Get a valid VlanId
//
EFI_STATUS
GetAValidVlanId (
  EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig,
  UINT16                                     *VlanId
  ) 
{
  EFI_STATUS            Status;
  UINT16                NumberOfVlan;
  EFI_VLAN_FIND_DATA    *Entries;

  Entries = NULL;

  Status = VlanConfig->Find (
                         VlanConfig,
                         NULL,
                         &NumberOfVlan,
                         &Entries
                         );
  if ( EFI_SUCCESS == Status && NumberOfVlan > 0 && Entries != NULL ) {
    *VlanId = Entries->VlanId;
    Status = EFI_SUCCESS;
  } else if ( EFI_NOT_FOUND == Status ) {
    Status = EFI_NOT_FOUND;
  } else {
    return Status;
  }

  if (  Entries != NULL )
    gtBS->FreePool ( Entries );

  return Status;
}

//
// Get a Invalid VlanId
//
EFI_STATUS
GetAnInvalidVlanId (
  EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig,
  UINT16                                     *VlanId
  ) 
{
  EFI_STATUS            Status;
  UINT16                NumberOfVlan;
  EFI_VLAN_FIND_DATA    *Entries;

  UINT16  Id;
  UINT16  Number;
  UINT8   IsValid;

  Entries = NULL;
  IsValid = 0;

  Status = VlanConfig->Find (
                         VlanConfig,
                         NULL,
                         &NumberOfVlan,
                         &Entries
                         );
  
  if ( EFI_SUCCESS == Status && NumberOfVlan > 0 && Entries != NULL ) {
    for ( Id = 0; Id < 4095; Id++ ) {
      IsValid = 0;
      for ( Number = 0; Number < NumberOfVlan; Number++ ) {
        Entries++;
        if ( Id == Entries->VlanId ) {
          IsValid = 1;
          break;
        }  
      }
      if ( IsValid == 0)
        break;
    }
    if ( IsValid == 0 ) {
      *VlanId = Id;
      Status = EFI_SUCCESS;
    } else {
      Status = EFI_NOT_FOUND;
    }
  } else if ( EFI_NOT_FOUND == Status ){
    *VlanId = 0;
    Status = EFI_SUCCESS;
  } else {
    return Status;
  }

  if (  Entries != NULL )
    gtBS->FreePool ( Entries );

  return Status;
}

//
//
//

EFI_STATUS
EFIAPI
InitializeVlanConfigBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadVlanConfigBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadVlanConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
