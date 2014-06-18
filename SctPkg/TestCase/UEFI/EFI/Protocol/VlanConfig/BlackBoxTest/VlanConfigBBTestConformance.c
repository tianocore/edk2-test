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
    VlanConfigBBTestConformance.c

Abstract:
    for EFI Driver Vlan Config Protocol's conformance Test

--*/
#include "SctLib.h"
#include "VlanConfigBBTestMain.h"


EFI_STATUS
BBTestSetConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
BBTestSetConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
BBTestFindConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
BBTestFindConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );

EFI_STATUS
BBTestFindConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );

EFI_STATUS
BBTestFindConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
BBTestRemoveConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
BBTestRemoveConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
  
//
//Test Cases
//
EFI_STATUS
BBTestSetConformanceTest (
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
  BBTestSetConformanceTestCheckpoint1( StandardLib, VlanConfig );
  
  BBTestSetConformanceTestCheckpoint2( StandardLib, VlanConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestFindConformanceTest (
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
  BBTestFindConformanceTestCheckpoint1( StandardLib, VlanConfig );
  
  BBTestFindConformanceTestCheckpoint2( StandardLib, VlanConfig );
  
  BBTestFindConformanceTestCheckpoint3( StandardLib, VlanConfig );

  BBTestFindConformanceTestCheckpoint4( StandardLib, VlanConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestRemoveConformanceTest (
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
  BBTestRemoveConformanceTestCheckpoint1( StandardLib, VlanConfig );
  
  BBTestRemoveConformanceTestCheckpoint2( StandardLib, VlanConfig );
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
BBTestSetConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  UINT16                VlanId;
  UINT8                 Priority;

  VlanId = 4095;
  Priority = 0;
  
  //
  // Call Set with an invalid VlanId (>4094) 
  //
  Status = VlanConfig->Set(
                         VlanConfig,
                         4095,
                         0
                         );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestConformanceAssertionGuid001,
                 L"VLAN_CONFIG_PROTOCOL.Set - Set() returns EFI_INVALID_PARAMETER with an invalid VlanId (>4094).",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT16                VlanId;

  VlanId = 0;
  
  //
  // Call Set with an invalid Priority (>7) It is a temp point here
  //
  Status = VlanConfig->Set(
                         VlanConfig,
                         VlanId,
                         9
                         );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestConformanceAssertionGuid002,
                 L"VLAN_CONFIG_PROTOCOL.Set - Set() returns EFI_INVALID_PARAMETER with an invalid Priority (>7).",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestFindConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  UINT16                VlanId;
  UINT16                NumberOfVlan;
  EFI_VLAN_FIND_DATA    *Entries;

  VlanId = 4095;
  
  //
  // Call Find with an invalid VlanId (>4094) 
  //
  Status = VlanConfig->Find(
                         VlanConfig,
                         &VlanId,
                         &NumberOfVlan,
                         &Entries
                         );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestConformanceAssertionGuid003,
                 L"VLAN_CONFIG_PROTOCOL.Find - Find() returns EFI_INVALID_PARAMETER with an invalid VlanId (>4094).",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestFindConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_VLAN_FIND_DATA    *Entries;
  
  //
  // Call Find with an NULL NumberOfVlan 
  //
  Status = VlanConfig->Find(
                         VlanConfig,
                         NULL,
                         NULL,
                         &Entries
                         );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestConformanceAssertionGuid004,
                 L"VLAN_CONFIG_PROTOCOL.Find - Find() returns EFI_INVALID_PARAMETER with an NULL NumberOfVlan.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestFindConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  UINT16                NumberOfVlan;
  
  //
  // Call Find with an NULL Entries 
  //
  Status = VlanConfig->Find(
                         VlanConfig,
                         NULL,
                         &NumberOfVlan,
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
                 gVlanConfigBBTestConformanceAssertionGuid005,
                 L"VLAN_CONFIG_PROTOCOL.Find - Find() returns EFI_INVALID_PARAMETER with an NULL Entries.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestFindConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  UINT16                NumberOfVlan;
  UINT16                VlanId;
  EFI_STATUS            Status1;
  
  Status1 = GetAValidVlanId ( VlanConfig, &VlanId );
  if ( Status1 == EFI_NOT_FOUND ) {
    VlanId = 0;
    Status = VlanConfig->Set( VlanConfig, VlanId, 0);
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
  }

  
  //
  // Call Find with an NULL Entries 
  //
  Status = VlanConfig->Find(
                         VlanConfig,
                         &VlanId,
                         &NumberOfVlan,
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
                 gVlanConfigBBTestConformanceAssertionGuid006,
                 L"VLAN_CONFIG_PROTOCOL.Find - Find() returns EFI_INVALID_PARAMETER with an NULL Entries.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( Status1 == EFI_NOT_FOUND ) {
    VlanConfig->Remove( VlanConfig, VlanId );
  }

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestRemoveConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  UINT16                VlanId;

  VlanId = 4095;
  
  //
  // Call Remove with an Invalid VlanId(>4094)
  //
  Status = VlanConfig->Remove(
                         VlanConfig,
                         VlanId
                         );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestConformanceAssertionGuid007,
                 L"VLAN_CONFIG_PROTOCOL.Remove - Remove() returns EFI_INVALID_PARAMETER with an Invalid VlanId(>4094).",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestRemoveConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  UINT16                VlanId;
  
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
  // Call Remove with an Invalid VlanId(it is not configed)
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
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gVlanConfigBBTestConformanceAssertionGuid008,
                 L"VLAN_CONFIG_PROTOCOL.Remove - Remove() returns EFI_NOT_FOUND with an Invalid VlanId(it is not configed.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
