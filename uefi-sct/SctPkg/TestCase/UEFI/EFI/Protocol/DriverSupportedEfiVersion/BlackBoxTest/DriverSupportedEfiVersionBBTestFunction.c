/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2015, Byosoft Corporation. All rights reserved.<BR>
  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DriverSupportedEfiVersionBBTestFunction.c

Abstract:

  Interface Function Test Cases of Efi Driver Support Efi Version Protocol

--*/


#include "SctLib.h"
#include "DriverSupportedEfiVersionBBTestMain.h"


/**
 *  Entrypoint for EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.Length Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
EFIAPI
BBTestLengthParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL       *DriverSupportedEfiVersion;

  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                                         EfiVersionProtocolLength;
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DriverSupportedEfiVersion = (EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL *)ClientInterface;
  EfiVersionProtocolLength =sizeof( EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL);
  
  if(DriverSupportedEfiVersion->Length ==EfiVersionProtocolLength){
        AssertionType = EFI_TEST_ASSERTION_PASSED;
  }else{
        AssertionType = EFI_TEST_ASSERTION_FAILED;
   }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDriverSupportedEfiVersionTestAssertionGuid001,
                 L"EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.Length,compare with length of EfiVersionProtocol",
                 L"%a:%d: Length = %d, EfiVersionProtocolLength = %d, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 DriverSupportedEfiVersion->Length,
                 EfiVersionProtocolLength,
                 EFI_SUCCESS
                 );
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.FirmwareVersion Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
EFIAPI
BBTestFirmwareVersionParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL       *DriverSupportedEfiVersion;

  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                                        S1,S2;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  DriverSupportedEfiVersion = (EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL *)ClientInterface;
  S1 = DriverSupportedEfiVersion->FirmwareVersion;
  S2 = EFI_2_50_SYSTEM_TABLE_REVISION;
  
  if (S1 == S2) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if ( S1 == EFI_2_40_SYSTEM_TABLE_REVISION ||
      S1 == EFI_2_31_SYSTEM_TABLE_REVISION ||
      S1 == EFI_2_30_SYSTEM_TABLE_REVISION ||
      S1 == EFI_2_20_SYSTEM_TABLE_REVISION ||
      S1 == EFI_2_10_SYSTEM_TABLE_REVISION ||
      S1 == EFI_2_00_SYSTEM_TABLE_REVISION ||
      S1 == EFI_1_10_SYSTEM_TABLE_REVISION ||
      S1 == EFI_1_02_SYSTEM_TABLE_REVISION ) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
      StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDriverSupportedEfiVersionTestAssertionGuid002,
                 L"EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.FirmwareVersion,compare with system table revision",
                 L"%a:%d: FirmwareVersion = %r, FirmwareRevision = %r, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 S1,
                 S2,
                 EFI_SUCCESS
                 );
      return EFI_INCOMPATIBLE_VERSION;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDriverSupportedEfiVersionTestAssertionGuid002,
                 L"EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.FirmwareVersion,compare with system table revision",
                 L"%a:%d: FirmwareVersion = %r, FirmwareRevision = %r, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 S1,
                 S2,
                 EFI_SUCCESS
                 );
  return EFI_SUCCESS;
}
