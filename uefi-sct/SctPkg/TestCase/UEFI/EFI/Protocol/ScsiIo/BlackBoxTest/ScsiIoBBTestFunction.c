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

  ScsiIoBBTestFunction.c

Abstract:

  Interface Function Test Cases of Scsi Io Protocol

--*/


#include "SctLib.h"
#include "ScsiIoBBTestMain.h"

extern UINT8 EnterEvent;

/**
 *  Entrypoint for EFI_SCSI_IO_PROTOCOL.GetDeviceType Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1.1
//
EFI_STATUS
EFIAPI
BBTestGetDeviceTypeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_IO_PROTOCOL                 *ScsiIo;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                DeviceType;

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

  ScsiIo = (EFI_SCSI_IO_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.1.2.1
  // GetDeviceType should return EFI_SUCCESS with SCSI device correctly installed
  //
  Status = ScsiIo->GetDeviceType (ScsiIo, &DeviceType);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestFunctionAssertionGuid001,
                 L"EFI_SCSI_IO_PROTOCOL.GetDeviceType - Invoke GetDeviceType() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );       

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_IO_PROTOCOL.GetDeviceLocation Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1.2
//
EFI_STATUS
EFIAPI
BBTestGetDeviceLocationFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_IO_PROTOCOL                 *ScsiIo;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                Target[TARGET_MAX_BYTES];
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

  ScsiIo = (EFI_SCSI_IO_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.2.2.1
  // GetDeviceLocation should return EFI_SUCCESS after setting Target and Lun.
  //
  TargetAddr = &Target[0];
  Status = ScsiIo->GetDeviceLocation (ScsiIo, (UINT8 **)&TargetAddr, &Lun);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestFunctionAssertionGuid002,
                 L"EFI_SCSI_IO_PROTOCOL.GetDeviceLocation - Invoke GetDeviceLocation() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_IO_PROTOCOL.ResetBus Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1.3
//
EFI_STATUS
EFIAPI
BBTestResetBusFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_IO_PROTOCOL                 *ScsiIo;
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

  ScsiIo = (EFI_SCSI_IO_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.3.2.1
  // ResetBus() should return EFI_SUCCESS or EFI_UNSUPPORTED with SCSI device correctly installed.
  //
  Status = ScsiIo->ResetBus (ScsiIo);

  if (Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestFunctionAssertionGuid003,
                 L"EFI_SCSI_IO_PROTOCOL.ResetBus - Invoke ResetChannel() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_IO_PROTOCOL.ResetDevice Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1.4
//
EFI_STATUS
EFIAPI
BBTestResetDeviceFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_IO_PROTOCOL                 *ScsiIo;
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

  ScsiIo = (EFI_SCSI_IO_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.4.2.1
  // ResetDevice() should return EFI_SUCCESS or EFI_UNSUPPORTED with SCSI device correctly installed
  //
  Status = ScsiIo->ResetDevice (ScsiIo);

  if (Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestFunctionAssertionGuid004,
                 L"EFI_SCSI_IO_PROTOCOL.ResetDevice - Invoke ResetDevice() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_IO_PROTOCOL.PassThru Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

//
// TDS 3.1.5
//
EFI_STATUS
EFIAPI
BBTestExecuteScsiCommandFunctionAutoTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib;
  EFI_STATUS                                 Status;
  EFI_SCSI_IO_PROTOCOL                       *ScsiIo;
  EFI_TEST_ASSERTION                         AssertionType;
  EFI_SCSI_IO_SCSI_REQUEST_PACKET            Packet;
  UINT8                                      Cdb[6];
  UINT8                                      *Data;
  EFI_EVENT                                  Event;

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
  
  ScsiIo = (EFI_SCSI_IO_PROTOCOL *)ClientInterface;

  Data = (UINT8 *)SctAllocatePool (ScsiIo->IoAlign + 96);
  //
  // Assertion Point 3.1.5.2.1
  // Call ExecuteScsiCommand() with NULL Event.
  //
  
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet,sizeof (EFI_SCSI_IO_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb,6);
  SctZeroMem (Data,ScsiIo->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = 0x00;
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if((ScsiIo->IoAlign == 0) ||(ScsiIo->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ScsiIo->IoAlign - 1) &
                                   ~((UINTN)(ScsiIo->IoAlign - 1)));
  }
  Packet.InTransferLength  = 96;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_SCSI_IO_DATA_DIRECTION_READ;

  Status = ScsiIo->ExecuteScsiCommand (ScsiIo, &Packet, NULL);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestFunctionAssertionGuid005,
                 L"EFI_Scsi_IO_PROTOCOL.ExecuteScsiCommand - Call ExecuteScsiCommand() with NULL Event",
                 L"%a:%d:Status - %r, InTransferLen - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Packet.InTransferLength
                 );

  //
  // Assertion Point 3.1.5.2.2
  // Call ExecuteScsiCommand() with Event.
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
  SctZeroMem (&Packet,sizeof (EFI_SCSI_IO_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb,6);
  SctZeroMem (Data,ScsiIo->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = 0x00;
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if((ScsiIo->IoAlign == 0) ||(ScsiIo->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ScsiIo->IoAlign - 1) &
                                   ~((UINTN)(ScsiIo->IoAlign - 1)));
  }
  Packet.InTransferLength  = 96;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_SCSI_IO_DATA_DIRECTION_READ;

  Status = ScsiIo->ExecuteScsiCommand (ScsiIo, &Packet, Event);

  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestFunctionAssertionGuid006,
                 L"EFI_Scsi_IO_PROTOCOL.ExecuteScsiCommand - Call ExecuteScsiCommand() with Event",
                 L"%a:%d:Status - %r, InTransferLen - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
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

