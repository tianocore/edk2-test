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
UnloadVlanConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
