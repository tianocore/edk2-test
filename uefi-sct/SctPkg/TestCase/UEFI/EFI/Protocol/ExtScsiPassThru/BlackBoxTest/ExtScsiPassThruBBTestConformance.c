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

  ExtScsiPassThruBBTestConformance.c

Abstract:

  Conformance Test Cases of Extended Scsi Pass Through Protocol

--*/


#include "SctLib.h"
#include "ExtScsiPassThruBBTestMain.h"

extern UINT8 EnterEvent;
/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestGetNextTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_EXT_SCSI_PASS_THRU_PROTOCOL      *ExtScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                Target[TARGET_MAX_BYTES];
  UINT8                                *TargetAddr;
  UINT64                               Lun;
  UINT8                                NewTarget[TARGET_MAX_BYTES];
  UINT8                                *NewTargetAddr;
  UINT64                               NewLun;
  CHAR16                               Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                StringLength;
  UINT8								   InvalidTarget[TARGET_MAX_BYTES];
  UINT64                               InvalidLun;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun (ExtScsiPassThru, InvalidTarget, &InvalidLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid Target and Lun fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Assertion Point 4.1.2.1
  // Call GetNextTargetLun() with invalid parameter.
  //
  NewTargetAddr = &NewTarget[0];
  SctSetMem (NewTarget, TARGET_MAX_BYTES, 0xFF);
  //
  // Get First legal Device Target and Lun.
  //
  Status = ExtScsiPassThru->GetNextTargetLun (ExtScsiPassThru, (UINT8 **)&NewTargetAddr, &NewLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check point 1, call GetNextTargetLun with invalid Target.
  //
  TargetAddr = &Target[0];
  SctCopyMem (Target, InvalidTarget, TARGET_MAX_BYTES);
  Lun    = NewLun;

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  Status = ExtScsiPassThru->GetNextTargetLun (ExtScsiPassThru, (UINT8 **)&TargetAddr, &Lun);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid001,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun - call GetNextTargetLun with invalid Target.",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 NewLun
                 );

  //
  // Check point 2, call GetNextTargetLun with invalid Lun.
  //
  SctCopyMem (Target, NewTarget, TARGET_MAX_BYTES);
  Lun = InvalidLun;

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  Status = ExtScsiPassThru->GetNextTargetLun (ExtScsiPassThru, (UINT8 **)&TargetAddr, &Lun);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid002,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun - call GetNextTargetLun with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 InvalidLun
                 );
  
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestBuildDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_EXT_SCSI_PASS_THRU_PROTOCOL      *ExtScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                Target[TARGET_MAX_BYTES];
  UINT8                                *TargetAddr;
  UINT64                               Lun;
  UINT8                                NewTarget[TARGET_MAX_BYTES];
  UINT8                                *NewTargetAddr;
  UINT64                               NewLun;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                StringLength;
  UINT8								   InvalidTarget[TARGET_MAX_BYTES];
  UINT64                               InvalidLun;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun (ExtScsiPassThru, InvalidTarget, &InvalidLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid Target and Lun fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Assertion Point 4.2.2.1
  // Call BuildDevicePath() with invalid Target and invalid Lun.
  //
  NewTargetAddr = &NewTarget[0];
  SctSetMem (NewTarget, TARGET_MAX_BYTES, 0xFF);  
  Status = ExtScsiPassThru->GetNextTargetLun (ExtScsiPassThru, (UINT8 **)&NewTargetAddr, &NewLun);
  if (Status != EFI_SUCCESS){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get legal Target and Lun fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Check point 1, call BuildDevicePath with invalid Target.
  //
  TargetAddr = &Target[0];
  //SctSetMem (Target, TARGET_MAX_BYTES, 0xFE);
  SctCopyMem (Target, InvalidTarget, TARGET_MAX_BYTES);
  Lun = NewLun;

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  
  Status = ExtScsiPassThru->BuildDevicePath (ExtScsiPassThru, TargetAddr, Lun, &DevicePath);
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid003,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with invalid Target.",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 NewLun
                 );

  //
  // Check point 2, call BuildDevicePath with invalid Lun.
  //
  SctCopyMem (Target, NewTarget, TARGET_MAX_BYTES);
  Lun = InvalidLun;

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  
  Status = ExtScsiPassThru->BuildDevicePath (ExtScsiPassThru, TargetAddr, Lun, &DevicePath);

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid004,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 InvalidLun
                 );

  //
  // Assertion Point 4.2.2.2
  // Call BuildDevicePath() with NULL DevicePath.
  //
  NewTargetAddr = &NewTarget[0];
  SctSetMem (NewTarget, TARGET_MAX_BYTES, 0xFF);  
  
  Status =GetPresentTargetLun(ExtScsiPassThru, NewTargetAddr, &NewLun);
  if (Status != EFI_SUCCESS){
  	StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get present device on SCSI channel",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	return EFI_UNSUPPORTED;
  }

  BufToUHexString (Target2, &StringLength, NewTarget, TARGET_MAX_BYTES);
  
  Status = ExtScsiPassThru->BuildDevicePath (ExtScsiPassThru, NewTargetAddr, NewLun, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid005,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with NULL DevicePath.",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 NewLun
                 );
  
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestGetTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_EXT_SCSI_PASS_THRU_PROTOCOL      *ExtScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                Target[TARGET_MAX_BYTES];
  UINT8                                *TargetAddr;
  UINT64                               Lun;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                StringLength;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.3.2.1
  // Call GetTargetLun()with NULL DevicePath, NULL Target and NULL Lun.
  //
  TargetAddr = &Target[0];
  SctSetMem (Target, TARGET_MAX_BYTES, 0xFF);    
  Status =GetPresentTargetLun(ExtScsiPassThru, TargetAddr, &Lun);
  if (Status != EFI_SUCCESS){
  	StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get present device on SCSI channel",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	return EFI_UNSUPPORTED;
  }

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);

  //
  // Get the present Device Path Node.
  //
  Status = ExtScsiPassThru->BuildDevicePath (ExtScsiPassThru, TargetAddr, Lun, &DevicePath);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath",
                   L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Target2,
                   Lun
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check Point 1. NULL Device Path.
  //
  Status = ExtScsiPassThru->GetTargetLun (ExtScsiPassThru, NULL, (UINT8 **)&TargetAddr, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid006,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Device Path",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2. NULL Target.
  //
  Status = ExtScsiPassThru->GetTargetLun (ExtScsiPassThru, DevicePath, NULL, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid007,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Target",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3. NULL Lun.
  //
  Status = ExtScsiPassThru->GetTargetLun (ExtScsiPassThru, DevicePath, (UINT8 **)&TargetAddr, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid008,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Lun",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Assertion Point 4.3.2.2
  // Call GetTargetLun()with unsupported DevicePath.
  //

  //
  // Set the Device Path to Non Scsi Device Path.
  //
  DevicePath->Type    = 5;
  DevicePath->SubType = 1;

  Status = ExtScsiPassThru->GetTargetLun (ExtScsiPassThru, DevicePath, (UINT8 **)&TargetAddr, &Lun);

  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid009,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with unsupported Device Path",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //Free the DevicePath.
  SctFreePool (DevicePath);
  
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetTargetLun Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.4
//
EFI_STATUS
EFIAPI
BBTestResetTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_EXT_SCSI_PASS_THRU_PROTOCOL      *ExtScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                Target[TARGET_MAX_BYTES];
  UINT8                                *TargetAddr;
  UINT64                               Lun;
  UINT8                                NewTarget[TARGET_MAX_BYTES];
  UINT8                                *NewTargetAddr;
  UINT64                               NewLun;
  CHAR16                               Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                StringLength;
  UINT8								   InvalidTarget[TARGET_MAX_BYTES];
  UINT64                               InvalidLun;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun (ExtScsiPassThru, InvalidTarget, &InvalidLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid Target and Lun fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Assertion Point 4.4.2.1
  // Call ResetTargetLun() with invalid Target and invalid Lun.
  //

  //
  // Get present Target and Lun
  //  
  NewTargetAddr = &NewTarget[0];
  SctSetMem (NewTarget, TARGET_MAX_BYTES, 0xFF);  
  Status =GetPresentTargetLun(ExtScsiPassThru, NewTargetAddr, &NewLun);
  if (Status != EFI_SUCCESS){
  	StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get present device on SCSI channel",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	return EFI_UNSUPPORTED;
  }
  

  //
  // Check point 1, call ResetTargetLun with invalid Target.
  //
  TargetAddr = &Target[0];
  //SctSetMem (Target, TARGET_MAX_BYTES, 0xFE);
  SctCopyMem (Target, InvalidTarget, TARGET_MAX_BYTES);
  Lun = NewLun;

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  
  Status = ExtScsiPassThru->ResetTargetLun (ExtScsiPassThru, TargetAddr, Lun);

  if ( (Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid010,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetTargetLun - call ResetTargetLun with invalid Target.",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 NewLun
                 );

  //
  // Check point 2, call ResetTargetLun with invalid Lun.
  //
  SctCopyMem (Target, NewTarget, TARGET_MAX_BYTES);  
  Lun = InvalidLun;

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  
  Status = ExtScsiPassThru->ResetTargetLun (ExtScsiPassThru, TargetAddr, Lun);

  if ( (Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid011,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetTargetLun - call ResetTargetLun with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 InvalidLun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTarget Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.5
//
EFI_STATUS
EFIAPI
BBTestGetNextTargetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_EXT_SCSI_PASS_THRU_PROTOCOL      *ExtScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                Target[TARGET_MAX_BYTES];
  UINT8                                *TargetAddr;
  UINT8                                NewTarget[TARGET_MAX_BYTES];
  UINT8                                *NewTargetAddr;
  CHAR16                               Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                StringLength;
  UINT8								   InvalidTarget[TARGET_MAX_BYTES];
  UINT64                               InvalidLun;
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun (ExtScsiPassThru, InvalidTarget, &InvalidLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid Target and Lun fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  //
  // Assertion Point 4.5.2.1
  // Call GetNextTargetLun() with invalid parameter.
  //
  NewTargetAddr = &NewTarget[0];
  SctSetMem (NewTarget, TARGET_MAX_BYTES, 0xFF);  

  //
  // Get First Device Target.
  //
  Status = ExtScsiPassThru->GetNextTarget (ExtScsiPassThru, (UINT8 **)&NewTargetAddr);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTarget",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check point 1, call GetNextTarget with invalid Target.
  //
  TargetAddr = &Target[0];
  SctCopyMem (Target, InvalidTarget, TARGET_MAX_BYTES);

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  
  Status = ExtScsiPassThru->GetNextTarget (ExtScsiPassThru, (UINT8 **)&TargetAddr);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid012,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTarget - call GetNextTarget with invalid Target.",
                 L"%a:%d:Status - %r, Target - %s\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

//
// TDS 4.6
//
EFI_STATUS
EFIAPI
BBTestPassThruConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib;
  EFI_STATUS                                 Status;
  EFI_EXT_SCSI_PASS_THRU_PROTOCOL            *ExtScsiPassThru;
  EFI_TEST_ASSERTION                         AssertionType;
  UINT8                                      Target[TARGET_MAX_BYTES];
  UINT8                                      *TargetAddr;
  UINT8                                      NewTarget[TARGET_MAX_BYTES];  
  UINT8                                      *NewTargetAddr;
  UINT64                                     Lun;
  UINT64                                     NewLun;
  EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET Packet;
  UINT8                                      Cdb[6];
  UINT8                                      *Data;
  EFI_EVENT                                  Event;
  CHAR16                                     Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                      StringLength;
  UINT8								         InvalidTarget[TARGET_MAX_BYTES];
  UINT64                                     InvalidLun;
  UINT8                                      *Data1;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun (ExtScsiPassThru, InvalidTarget, &InvalidLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid Target and Lun fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Data = SctAllocateZeroPool (ExtScsiPassThru->Mode->IoAlign + 96);

  //
  // Get present Target and Lun
  //
  TargetAddr = &Target[0];
  SctSetMem (Target, TARGET_MAX_BYTES, 0xFF);    
  Status =GetPresentTargetLun(ExtScsiPassThru, TargetAddr, &Lun);
  if (Status != EFI_SUCCESS){
  	StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get present device on SCSI channel",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	return EFI_UNSUPPORTED;
  }
/*
  //
  // Assertion Point 4.6.2.1
  // Call PassThru() with too long InTransferLength.
  //

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ExtScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if ((ExtScsiPassThru->Mode->IoAlign == 0) || (ExtScsiPassThru->Mode->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ExtScsiPassThru->Mode->IoAlign - 1) &
                          ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 0xFFFFFFFF;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, Lun, &Packet, NULL);

  if ( (Status == EFI_BAD_BUFFER_SIZE) || (Status == EFI_SUCCESS) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid013,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with too long InTransferLength",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX, The max length is %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun,
                 Packet.InTransferLength
                 );
*/
  //
  // Assertion Point 4.6.2.3
  // Call PassThru() with invalid parameter.
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ExtScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if ((ExtScsiPassThru->Mode->IoAlign == 0) || (ExtScsiPassThru->Mode->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ExtScsiPassThru->Mode->IoAlign - 1) &
                          ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 96;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  //
  // Check Point 1. Invalid Target
  //
  NewTargetAddr = &NewTarget[0];
  //SctSetMem (NewTarget, TARGET_MAX_BYTES, 0xFE);
  SctCopyMem (NewTarget, InvalidTarget, TARGET_MAX_BYTES);

  BufToUHexString (Target2, &StringLength, NewTarget, TARGET_MAX_BYTES);
  
  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, NewTargetAddr, Lun, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid014,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Target",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun
                 );

  //
  // Check Point 2. Invalid Lun
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ExtScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)InvalidLun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if ((ExtScsiPassThru->Mode->IoAlign == 0) || (ExtScsiPassThru->Mode->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ExtScsiPassThru->Mode->IoAlign - 1) &
                          ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 96;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  NewLun = InvalidLun;
  
  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, NewLun, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid015,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Lun",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 InvalidLun
                 );

  //
  // Check Point 3. Invalid ScsiRequestPacket.
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, Lun, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid016,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid ScsiRequestPacket",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Create Event
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) NotifyFunction,
                   NULL,
                   &Event
                   );
  
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  EnterEvent = 0;
/*
  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ExtScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if ((ExtScsiPassThru->Mode->IoAlign == 0) || (ExtScsiPassThru->Mode->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ExtScsiPassThru->Mode->IoAlign - 1) &
                          ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 0xFFFFFFFF;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, Lun, &Packet, Event);

  if ( (Status == EFI_BAD_BUFFER_SIZE) || (Status == EFI_SUCCESS) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid017,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with too long InTransferLength",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX, The max length is %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun,
                 Packet.InTransferLength
                 );
*/
  //
  // Assertion Point 4.6.2.3
  // Call PassThru() with invalid parameter.
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ExtScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if ((ExtScsiPassThru->Mode->IoAlign == 0) || (ExtScsiPassThru->Mode->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ExtScsiPassThru->Mode->IoAlign - 1) &
                          ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 96;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  //
  // Check Point 1. Invalid Target
  //
  NewTargetAddr = &NewTarget[0];
  //SctSetMem (NewTarget, TARGET_MAX_BYTES, 0xFE);
  SctCopyMem (NewTarget, InvalidTarget, TARGET_MAX_BYTES);

  BufToUHexString (Target2, &StringLength, NewTarget, TARGET_MAX_BYTES);
  
  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, NewTargetAddr, Lun, &Packet, Event);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid018,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Target",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun
                 );

  //
  // Check Point 2. Invalid Lun
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ExtScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)InvalidLun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if ((ExtScsiPassThru->Mode->IoAlign == 0) || (ExtScsiPassThru->Mode->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ExtScsiPassThru->Mode->IoAlign - 1) &
                          ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 96;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  NewLun = InvalidLun;

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, NewLun, &Packet, Event);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid019,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Lun",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 InvalidLun
                 );

  //
  // Check Point 3. Invalid ScsiRequestPacket.
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, Lun, &Packet, Event);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid020,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid ScsiRequestPacket",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //Free Date
  SctFreePool(Data);

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);

  Data1 = NULL;
  Data1 = SctAllocateZeroPool ((UINTN)ExtScsiPassThru->Mode->IoAlign + 0xFFFFFFFF);
  if (NULL == Data1)
  	return EFI_OUT_OF_RESOURCES;
  
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data1, ExtScsiPassThru->Mode->IoAlign + 0xFFFFFFFF);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if ((ExtScsiPassThru->Mode->IoAlign == 0) || (ExtScsiPassThru->Mode->IoAlign == 1)){
    Packet.InDataBuffer = Data1;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data1 + ExtScsiPassThru->Mode->IoAlign - 1) &
                          ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 0xFFFFFFFF;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, Lun, &Packet, Event);

  if ( (Status == EFI_BAD_BUFFER_SIZE) || (Status == EFI_SUCCESS) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid017,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with too long InTransferLength",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX, The max length is %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun,
                 Packet.InTransferLength
                 );

  // Close the event
  Status = gtBS->CloseEvent (Event);
  if (EFI_ERROR(Status)) {
    return EFI_UNSUPPORTED;
  }


  //
  // Assertion Point 4.6.2.1
  // Call PassThru() with too long InTransferLength.
  //

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet, sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data1, ExtScsiPassThru->Mode->IoAlign + 0xFFFFFFFF);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if ((ExtScsiPassThru->Mode->IoAlign == 0) || (ExtScsiPassThru->Mode->IoAlign == 1)){
    Packet.InDataBuffer = Data1;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data1 + ExtScsiPassThru->Mode->IoAlign - 1) &
                          ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 0xFFFFFFFF;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, Lun, &Packet, NULL);

  if ( (Status == EFI_BAD_BUFFER_SIZE) || (Status == EFI_SUCCESS) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestConformanceAssertionGuid013,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with too long InTransferLength",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX, The max length is %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun,
                 Packet.InTransferLength
                 );



  SctFreePool(Data1);
  
  return EFI_SUCCESS;
}
