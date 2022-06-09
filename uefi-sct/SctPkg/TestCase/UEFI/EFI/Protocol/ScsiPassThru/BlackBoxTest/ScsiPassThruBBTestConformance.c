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

  ScsiPassThruBBTestConformance.c

Abstract:

  Conformance Test Cases of Scsi Pass Through Protocol

--*/


#include "SctLib.h"
#include "ScsiPassThruBBTestMain.h"

extern UINT8 EnterEvent;

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.GetNextDevice Conformance Test.
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
BBTestGetNextDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_PASS_THRU_PROTOCOL          *ScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               Target;
  UINT64                               Lun;
  UINT32                               NewTarget;
  UINT64                               NewLun;

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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.1.2.1
  // Call GetNextDevice() with invalid parameter.
  //
  NewTarget = 0xFFFFFFFF;

  //
  // Get First Device Target and Lun.
  //
  Status = ScsiPassThru->GetNextDevice (ScsiPassThru, &NewTarget, &NewLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_SCSI_PASS_THRU_PROTOCOL.GetNextDevice",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun(ScsiPassThru, &Target, &Lun);
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
  // Check point 1, call GetNextDevice with invalid Target.
  //
  Status = ScsiPassThru->GetNextDevice (ScsiPassThru, &Target, &NewLun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid002,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetNextDevice - call GetNextDevice with invalid Target.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 NewLun
                 );

  //
  // Check point 2, call GetNextDevice with invalid Lun.
  //
  Status = ScsiPassThru->GetNextDevice (ScsiPassThru, &NewTarget, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid003,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetNextDevice - call GetNextDevice with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 NewTarget,
                 Lun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.BuildDevicePath Conformance Test.
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
  EFI_SCSI_PASS_THRU_PROTOCOL          *ScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               Target;
  UINT64                               Lun;
  UINT32                               NewTarget;
  UINT64                               NewLun;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;

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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.2.2.1
  // Call BuildDevicePath() with invalid Target and invalid Lun.
  //
  NewTarget = 0xFFFFFFFF;
  Status = ScsiPassThru->GetNextDevice(ScsiPassThru, &NewTarget, &NewLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun(ScsiPassThru, &Target, &Lun);
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
  // Check point 1, call BuildDevicePath with invalid Target.
  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, Target, NewLun, &DevicePath);

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid004,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with invalid Target.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 NewLun
                 );

  //
  // Check point 2, call BuildDevicePath with invalid Lun.
  //
  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, NewTarget, Lun, &DevicePath);

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid005,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 NewTarget,
                 Lun
                 );

  //
  // Assertion Point 4.2.2.2
  // Call BuildDevicePath() with NULL DevicePath.
  //

  //
  // Get Present Target and Lun
  //
  Target = 0xFFFFFFFF;
  Status = GetPresentTargetLun(ScsiPassThru, &Target, &Lun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, Target, Lun, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid006,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with NULL DevicePath.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 Lun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.GetTargetLun Conformance Test.
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
  EFI_SCSI_PASS_THRU_PROTOCOL          *ScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               Target;
  UINT64                               Lun;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;

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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.3.2.1
  // Call GetTargetLun()with NULL DevicePath, NULL Target and NULL Lun.
  //
  Target = 0xFFFFFFFF;
  Status = GetPresentTargetLun(ScsiPassThru, &Target, &Lun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Get the valid Device Path Node.
  //
  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, Target, Lun, &DevicePath);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath",
                   L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Target,
                   Lun
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check Point 1. NULL Device Path.
  //
  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, NULL, &Target, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid007,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Device Path",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2. NULL Target.
  //
  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, DevicePath, NULL, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid008,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Target",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3. NULL Lun.
  //
  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, DevicePath, &Target, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid009,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Lun",
                 L"%a:%d:Status - %r",
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

  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, DevicePath, &Target, &Lun);

  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //Free the DevicePath.
  gtBS->FreePool (DevicePath);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid010,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with unsupported Device Path",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.ResetTarget Conformance Test.
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
BBTestResetTargetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_PASS_THRU_PROTOCOL          *ScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               Target;
  UINT64                               Lun;
  UINT32                               NewTarget;
  UINT64                               NewLun;

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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.4.2.1
  // Call ResetTarget() with invalid Target and invalid Lun.
  //
  NewTarget = 0xFFFFFFFF;
  Status = ScsiPassThru->GetNextDevice(ScsiPassThru, &NewTarget, &NewLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check point 1, call GetNextDevice with invalid Target.
  //

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun(ScsiPassThru, &Target, &Lun);
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
  
  Status = ScsiPassThru->ResetTarget (ScsiPassThru, Target, NewLun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid011,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.ResetTarget - call ResetTarget with invalid Target.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 NewLun
                 );

  //
  // Check point 2, call GetNextDevice with invalid Lun.
  //
  Status = ScsiPassThru->ResetTarget (ScsiPassThru, NewTarget, Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid012,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.ResetTarget - call ResetTarget with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 NewTarget,
                 Lun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.PassThru Conformance Test.
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
BBTestPassThruConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_SCSI_PASS_THRU_PROTOCOL            *ScsiPassThru;
  EFI_TEST_ASSERTION                     AssertionType;
  UINT32                                 Target;
  UINT64                                 Lun;
  EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET Packet;
  UINT8                                  Cdb[6];
  UINT8                                  *Data;
  EFI_EVENT                              Event;
  UINT32                                 InVaildTarget;
  UINT64                                 InVaildLun;

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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  Target = 0xFFFFFFFF;
  Status = GetPresentTargetLun(ScsiPassThru, &Target, &Lun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Initialize the Request Packet.
  //
  Data = (UINT8 *)SctAllocatePool (ScsiPassThru->Mode->IoAlign + 96);
  
  //
  // Assertion Point 4.5.2.1
  // Call PassThru() with too long TransferLength.
  //
  SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout = EfiScsiStallSeconds (2);
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  if((ScsiPassThru->Mode->IoAlign == 0)|| (ScsiPassThru->Mode->IoAlign == 1)){
    Packet.DataBuffer = (VOID *)Data;
  } else {
    Packet.DataBuffer = (VOID *)(((UINTN)Data + ScsiPassThru->Mode->IoAlign - 1) &
                                   ~(ScsiPassThru->Mode->IoAlign - 1));
  }
  Packet.TransferLength = 0xFFFFFFFF;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, Lun, &Packet, NULL);

  if ( (Status == EFI_BAD_BUFFER_SIZE) || (Status == EFI_SUCCESS) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid013,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with too long TransferLength",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld, The max length is %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 Lun,
                 Packet.TransferLength
                 );

  SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout = EfiScsiStallSeconds (2);
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  if((ScsiPassThru->Mode->IoAlign == 0)|| (ScsiPassThru->Mode->IoAlign == 1)){
    Packet.DataBuffer = (VOID *)Data;
  } else {
    Packet.DataBuffer = (VOID *)(((UINTN)Data + ScsiPassThru->Mode->IoAlign - 1) &
                                   ~(ScsiPassThru->Mode->IoAlign - 1));
  }
  Packet.TransferLength = 0xFFFFFFFF;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, Lun, &Packet, Event);

  if ( (Status == EFI_BAD_BUFFER_SIZE) || (Status == EFI_SUCCESS) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid014,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with too long TransferLength",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld, The max length is %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 Lun,
                 Packet.TransferLength
                 );
  
  //
  // Assertion Point 4.5.2.3
  // Call PassThru() with invalid parameter.
  //

  //
  // Get invalid Target and Lun
  //
  Status = GetInvalidTargetLun(ScsiPassThru, &InVaildTarget, &InVaildLun);
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
  // Check Point 1. Invalid Target
  SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout = EfiScsiStallSeconds (2);
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  if((ScsiPassThru->Mode->IoAlign == 0)|| (ScsiPassThru->Mode->IoAlign == 1)){
    Packet.DataBuffer = (VOID *)Data;
  } else {
    Packet.DataBuffer = (VOID *)(((UINTN)Data + ScsiPassThru->Mode->IoAlign - 1) &
                                   ~(ScsiPassThru->Mode->IoAlign - 1));
  }
  Packet.TransferLength = 96;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, InVaildTarget, Lun, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid016,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Target",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

		EnterEvent = 0;
  SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout = EfiScsiStallSeconds (2);
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  if((ScsiPassThru->Mode->IoAlign == 0)|| (ScsiPassThru->Mode->IoAlign == 1)){
    Packet.DataBuffer = (VOID *)Data;
  } else {
    Packet.DataBuffer = (VOID *)(((UINTN)Data + ScsiPassThru->Mode->IoAlign - 1) &
                                   ~(ScsiPassThru->Mode->IoAlign - 1));
  }
  Packet.TransferLength = 96;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, InVaildTarget, Lun, &Packet, Event);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid015,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Target",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2. Invalid Lun
  //
  SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)InVaildLun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout        = 0;
  Packet.Cdb            = Cdb;
  Packet.CdbLength      = 6;
  if((ScsiPassThru->Mode->IoAlign == 0)|| (ScsiPassThru->Mode->IoAlign == 1)){
    Packet.DataBuffer = (VOID *)Data;
  } else {
    Packet.DataBuffer = (VOID *)(((UINTN)Data + ScsiPassThru->Mode->IoAlign - 1) &
                                   ~(ScsiPassThru->Mode->IoAlign - 1));
  }
  Packet.TransferLength = 96;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, InVaildLun, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid017,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Lun",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  EnterEvent = 0;
  SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)InVaildLun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout        = 0;
  Packet.Cdb            = Cdb;
  Packet.CdbLength      = 6;
  if((ScsiPassThru->Mode->IoAlign == 0)|| (ScsiPassThru->Mode->IoAlign == 1)){
    Packet.DataBuffer = (VOID *)Data;
  } else {
    Packet.DataBuffer = (VOID *)(((UINTN)Data + ScsiPassThru->Mode->IoAlign - 1) &
                                   ~(ScsiPassThru->Mode->IoAlign - 1));
  }
  Packet.TransferLength = 96;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, InVaildLun, &Packet, Event);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid019,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Lun",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3. Invalid ScsiRequestPacket.
  //
  SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, Lun, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid018,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid ScsiRequestPacket",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  EnterEvent = 0;
  SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, Lun, &Packet, Event);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid020,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid ScsiRequestPacket",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  SctFreePool (Data);
  return EFI_SUCCESS;
}
