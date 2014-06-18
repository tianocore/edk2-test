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
    VlanConfigBBTestFunction.c

Abstract:
    for EFI Driver Vlan Config Protocol's function Test

--*/
#include "SctLib.h"
#include "VlanConfigBBTestMain.h"

EFI_STATUS
BBTestSetFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
BBTestFindFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );

EFI_STATUS
BBTestFindFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
BBTestRemoveFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
//
//Test Cases
//
EFI_STATUS
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
                   &StandardLib
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
                   &StandardLib
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
                   &StandardLib
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

