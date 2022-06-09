/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    UFSDeviceConfigConformance.c

Abstract:

    for EFI UFS Device Config Protocol's Conformance Test

--*/

#include "UFSDeviceConfigBBTestMain.h"

EFI_STATUS
EFIAPI
BBTestRwUfsDescriptorConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_UFS_DEVICE_CONFIG_PROTOCOL        *UFSDeviceConfig;
  EFI_TEST_ASSERTION                    AssertionType;
  
  UINT8                                 Descriptor;
  UINT32                                DescSize;  
  
  UFSDeviceConfig = (EFI_UFS_DEVICE_CONFIG_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  Status = UFSDeviceConfig->RwUfsDescriptor(UFSDeviceConfig, TRUE, 0, 0, 0, NULL, &DescSize);
  if (Status == EFI_INVALID_PARAMETER) 
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUFSDeviceConfigBBTestConfAssertionGuid001,
                 L"EFI_UFS_DEVICE_CONFIG_PROTOCOL.RwUfsDescriptor- RwUfsDescriptor() returns EFI_INVALID_PARAMETER when Descriptor is NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  Status = UFSDeviceConfig->RwUfsDescriptor(UFSDeviceConfig, TRUE, 0, 0, 0, &Descriptor, NULL);
  if (Status == EFI_INVALID_PARAMETER) 
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED; 

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUFSDeviceConfigBBTestConfAssertionGuid002,
                 L"EFI_UFS_DEVICE_CONFIG_PROTOCOL.RwUfsDescriptor- RwUfsDescriptor() returns EFI_INVALID_PARAMETER when DescSize is NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  


  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRwUfsFlagConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_UFS_DEVICE_CONFIG_PROTOCOL        *UFSDeviceConfig;
  EFI_TEST_ASSERTION                    AssertionType;
  
  UINT8                                 Flag;
  
  UFSDeviceConfig = (EFI_UFS_DEVICE_CONFIG_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  Status = UFSDeviceConfig->RwUfsFlag(UFSDeviceConfig, TRUE, 0, &Flag);
  if (Status == EFI_INVALID_PARAMETER) 
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUFSDeviceConfigBBTestConfAssertionGuid003,
                 L"EFI_UFS_DEVICE_CONFIG_PROTOCOL.RwUfsFlag- RwUfsFlag() returns EFI_INVALID_PARAMETER when FlagId is an invalid UFS flag ID.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  Status = UFSDeviceConfig->RwUfsFlag(UFSDeviceConfig, TRUE, 1, NULL);
  if (Status == EFI_INVALID_PARAMETER) 
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED; 

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUFSDeviceConfigBBTestConfAssertionGuid004,
                 L"EFI_UFS_DEVICE_CONFIG_PROTOCOL.RwUfsFlag- RwUfsFlag() returns EFI_INVALID_PARAMETER when Flag is NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
EFIAPI
BBTestRwUfsAttributeConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_UFS_DEVICE_CONFIG_PROTOCOL        *UFSDeviceConfig;
  EFI_TEST_ASSERTION                    AssertionType;
  
  UINT8                                 Attribute;
  UINT32                                AttrSize;  
  
  UFSDeviceConfig = (EFI_UFS_DEVICE_CONFIG_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = UFSDeviceConfig->RwUfsAttribute(UFSDeviceConfig, TRUE, 0, 0, 0, NULL, &AttrSize);
  if (Status == EFI_INVALID_PARAMETER) 
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUFSDeviceConfigBBTestConfAssertionGuid005,
                 L"EFI_UFS_DEVICE_CONFIG_PROTOCOL.RwUfsAttribute- RwUfsAttribute() returns EFI_INVALID_PARAMETER when Attribute is NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  Status = UFSDeviceConfig->RwUfsAttribute(UFSDeviceConfig, TRUE, 0, 0, 0, &Attribute, NULL);
  if (Status == EFI_INVALID_PARAMETER) 
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED; 

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUFSDeviceConfigBBTestConfAssertionGuid006,
                 L"EFI_UFS_DEVICE_CONFIG_PROTOCOL.RwUfsAttribute- RwUfsAttribute() returns EFI_INVALID_PARAMETER when AttrSize is NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );    
  
  return EFI_SUCCESS;
}
