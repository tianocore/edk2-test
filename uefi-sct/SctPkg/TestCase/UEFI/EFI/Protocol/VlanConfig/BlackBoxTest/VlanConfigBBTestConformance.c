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
    VlanConfigBBTestConformance.c

Abstract:
    for EFI Driver Vlan Config Protocol's conformance Test

--*/
#include "SctLib.h"
#include "VlanConfigBBTestMain.h"


EFI_STATUS
EFIAPI
BBTestSetConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
EFIAPI
BBTestSetConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
EFIAPI
BBTestFindConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
EFIAPI
BBTestFindConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );

EFI_STATUS
EFIAPI
BBTestFindConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );

EFI_STATUS
EFIAPI
BBTestFindConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
EFIAPI
BBTestRemoveConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
EFI_STATUS
EFIAPI
BBTestRemoveConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
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
                   (VOID **) &StandardLib
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
EFIAPI
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
                   (VOID **) &StandardLib
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
EFIAPI
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
                   (VOID **) &StandardLib
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
