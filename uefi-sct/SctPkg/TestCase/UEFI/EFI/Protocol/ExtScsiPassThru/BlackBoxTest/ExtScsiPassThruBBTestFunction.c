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

  ExtScsiPassThruBBTestFunction.c

Abstract:

  Interface Function Test Cases of Extended Scsi Pass Through Protocol

--*/


#include "SctLib.h"
#include "ExtScsiPassThruBBTestMain.h"

extern UINT8 EnterEvent;

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestGetNextTargetLunFunctionAutoTest (
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
  CHAR16                               Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                StringLength;
  UINT8                                *TargetAddr;  
  UINT64                               Lun;

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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.2.1
  // Retrieve the list of legal Target IDs and LUNs for SCSI devices on a SCSI channel.
  //
  TargetAddr = &Target[0];
  SctSetMem (Target, TARGET_MAX_BYTES, 0xFF);    
  
  Status = EFI_SUCCESS;
  while (!EFI_ERROR(Status)) {
    BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
    Status = ExtScsiPassThru->GetNextTargetLun (ExtScsiPassThru, (UINT8 **)&TargetAddr, &Lun);
    if (!EFI_ERROR(Status )) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"SCSI device: Target - %s, Lun - 0x%lX\n",
                     Target2,
                     Lun
                     );
    }
  }

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestFunctionAssertionGuid001,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun - Invoke GetNextTargetLun() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestBuildDevicePathFunctionAutoTest (
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
  CHAR16                               Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                StringLength;
  UINT8                                *TargetAddr;
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

  if ( EFI_ERROR(Status) ) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.2.2.1
  // Call BuildDevicePath().
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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	return EFI_UNSUPPORTED;
  }
  
  Status = ExtScsiPassThru->BuildDevicePath (ExtScsiPassThru, TargetAddr, Lun, &DevicePath);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    gtBS->FreePool (DevicePath);
  }

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestFunctionAssertionGuid002,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - Invoke BuildDevicePath() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.3
//
EFI_STATUS
EFIAPI
BBTestGetTargetLunFunctionAutoTest (
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
  CHAR16                               NewTarget2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                NewStringLength;


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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  StringLength = 2 * TARGET_MAX_BYTES + 1;
  NewStringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.3.2.1
  // Call GetTargetLun().
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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	return EFI_UNSUPPORTED;
  }
  

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
  //
  // Get the valid Device Path Node.
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

  NewTargetAddr = &NewTarget[0];
  Status = ExtScsiPassThru->GetTargetLun (ExtScsiPassThru, DevicePath, (UINT8 **)&NewTargetAddr, &NewLun);

  BufToUHexString(NewTarget2, &NewStringLength, NewTarget, TARGET_MAX_BYTES);

  //Free the DevicePath.
  gtBS->FreePool (DevicePath);

  if ((!EFI_ERROR(Status)) && 
      (0 == SctCompareMem (NewTargetAddr, TargetAddr, TARGET_MAX_BYTES)) && 
      (NewLun == Lun)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestFunctionAssertionGuid003,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX, NewTarget - %s, NewLun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun,
                 NewTarget2,
                 NewLun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetChannel Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.4
//
EFI_STATUS
EFIAPI
BBTestResetChannelFunctionAutoTest (
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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.4.2.1
  // Call ResetChannel().
  //
  Status = ExtScsiPassThru->ResetChannel (ExtScsiPassThru);

  if (Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestFunctionAssertionGuid004,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetChannel - Invoke ResetChannel() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetTargetLun Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.5
//
EFI_STATUS
EFIAPI
BBTestResetTargetLunFunctionAutoTest (
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

  if ( EFI_ERROR(Status) ) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.5.2.1
  // Call ResetTargetLun().
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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	return EFI_UNSUPPORTED;
  }

  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);

  Status = ExtScsiPassThru->ResetTargetLun (ExtScsiPassThru, TargetAddr, Lun);

  if (Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestFunctionAssertionGuid005,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetTargetLun - Invoke ResetTargetLun() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTarget Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.6
//
EFI_STATUS
EFIAPI
BBTestGetNextTargetFunctionAutoTest (
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

  if ( EFI_ERROR(Status) ) {
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

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.6.2.1
  // Retrieve the list of legal Target IDs for SCSI devices on a SCSI channel.
  //
  TargetAddr = &Target[0];
  SctSetMem (Target, TARGET_MAX_BYTES, 0xFF);
  
  Status = EFI_SUCCESS;
  while (!EFI_ERROR(Status)) {
    Status = ExtScsiPassThru->GetNextTarget (ExtScsiPassThru, (UINT8 **)&TargetAddr);
    if (!EFI_ERROR(Status)) {
	  BufToUHexString (Target2, &StringLength, Target, TARGET_MAX_BYTES);
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"SCSI device: Target - %s\n",
                     Target2
                     );
    }
  }

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestFunctionAssertionGuid006,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTarget - Invoke GetNextTarget() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

//
// TDS 3.7
//
EFI_STATUS
EFIAPI
BBTestPassThruFunctionAutoTest (
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
  UINT64                                     Lun;
  EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET Packet;
  UINT8                                      Cdb[6];
  UINT8                                      *Data;
  EFI_EVENT                                  Event;
  CHAR16                                     Target2[2 * TARGET_MAX_BYTES + 1];
  UINTN                                      StringLength;

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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  StringLength = 2 * TARGET_MAX_BYTES + 1;

  ExtScsiPassThru = (EFI_EXT_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  Data = SctAllocateZeroPool (ExtScsiPassThru->Mode->IoAlign + 96);
  
  //
  // Get valid Target and Lun
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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	return EFI_UNSUPPORTED;
  }
  //
  // Assertion Point 3.7.2.1
  // Call PassThru() with NULL Event.
  //
  BufToUHexString(Target2, &StringLength, Target, TARGET_MAX_BYTES);

  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet,sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
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
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ExtScsiPassThru->Mode->IoAlign - 1)& 
		                  ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 96;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, Lun, &Packet, NULL);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestFunctionAssertionGuid007,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with NULL Event",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX, InTransferLen - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target2,
                 Lun,
                 Packet.InTransferLength
                 );

  //
  // Assertion Point 3.7.2.2
  // Call PassThru() with Event.
  //

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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  EnterEvent = 0;

  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet,sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb,6);
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
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ExtScsiPassThru->Mode->IoAlign - 1)& 
		                  ~((UINTN)(ExtScsiPassThru->Mode->IoAlign - 1)));
  }
  Packet.InTransferLength  = 96;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_EXT_SCSI_DATA_DIRECTION_READ;

  Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, Lun, &Packet, Event);

  if (!(ExtScsiPassThru->Mode->Attributes & EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_NONBLOCKIO)) {
    if (!EFI_ERROR(Status) && (EnterEvent == 0)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    gtBS->Stall(EfiScsiStallSeconds (3));
    if (!EFI_ERROR(Status) && (EnterEvent == 1)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gExtScsiPassThruBBTestFunctionAssertionGuid008,
                 L"EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with Event",
                 L"%a:%d:Status - %r, Target - %s, Lun - 0x%lX, InTransferLen - %d\n",
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

  SctFreePool (Data);

  return EFI_SUCCESS;
}


