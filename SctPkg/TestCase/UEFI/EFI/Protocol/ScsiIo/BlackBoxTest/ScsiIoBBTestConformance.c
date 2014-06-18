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

  ScsiIoBBTestConformance.c

Abstract:

  Conformance Test Cases of Scsi Io Protocol

--*/


#include "SctLib.h"
#include "ScsiIoBBTestMain.h"

extern UINT8 EnterEvent;
/**
 *  Entrypoint for EFI_SCSI_IO_PROTOCOL.GetNextDevice Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2.1
//
EFI_STATUS
BBTestGetDeviceTypeConformanceAutoTest (
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
                   &StandardLib
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

  ScsiIo = (EFI_SCSI_IO_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.2.1.2.1
  // GetDeviceType should return EFI_INVALID_PARAMETER with DeviceType set NULL
  //
  Status = ScsiIo->GetDeviceType (ScsiIo, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestConformanceAssertionGuid001,
                 L"EFI_SCSI_IO_PROTOCOL.GetDeviceType - Perform conformance test on the GetDeviceType service.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_SCSI_IO_PROTOCOL.GetDeviceLocation Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2.2
//
EFI_STATUS
BBTestGetDeviceLocationConformanceAutoTest (
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
                   &StandardLib
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

  ScsiIo = (EFI_SCSI_IO_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.2.2.2.1
  // GetDeviceLocation should return EFI_INVALID_PARAMETER with Target set NULL
  //
  Status = ScsiIo->GetDeviceLocation (ScsiIo, NULL, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestConformanceAssertionGuid002,
                 L"EFI_SCSI_IO_PROTOCOL.GetDeviceLocation - Perform conformance test on the GetDeviceLocation service",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Assertion Point 3.2.2.2.2
  // GetDeviceLocation should return EFI_INVALID_PARAMETER with Lun set NULL
  //
  TargetAddr = &Target[0];
  Status = ScsiIo->GetDeviceLocation (ScsiIo, (UINT8 **)&TargetAddr, NULL);
  
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestConformanceAssertionGuid003,
                 L"EFI_SCSI_IO_PROTOCOL.GetDeviceLocation - Perform conformance test on the GetDeviceLocation service",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_IO_PROTOCOL.PassThru Conformance Test.
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
BBTestExecuteScsiCommandConformanceAutoTest (
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
                   &StandardLib
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

  ScsiIo = (EFI_SCSI_IO_PROTOCOL *)ClientInterface;
  Data = SctAllocatePool (ScsiIo->IoAlign + 96);

  //
  // Assertion Point 3.2.3.2.1
  // Call ExecuteScsiCommand() with too long InTransferLength.
  //
  
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet, sizeof (EFI_SCSI_IO_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ScsiIo->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = 0x00;
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if((ScsiIo->IoAlign == 0) || (ScsiIo->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ScsiIo->IoAlign - 1) &
		                  ~((UINTN)(ScsiIo->IoAlign - 1)));
  }
  Packet.InTransferLength  = 0xFFFFFFFF;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_SCSI_IO_DATA_DIRECTION_READ;
  
  Status = ScsiIo->ExecuteScsiCommand (ScsiIo, &Packet, NULL);

  if ( (Status == EFI_BAD_BUFFER_SIZE) || (Status == EFI_SUCCESS) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestConformanceAssertionGuid004,
                 L"EFI_SCSI_IO_PROTOCOL.ExecuteScsiCommand - Call ExecuteScsiCommand() with with too long InTransferLength",
                 L"%a:%d:Status - %r, The max length is %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Packet.InTransferLength
                 );
  
  //
  // Create Event
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   NotifyFunction,
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
  
  SctZeroMem (&Packet, sizeof (EFI_SCSI_IO_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb, 6);
  SctZeroMem (Data, ScsiIo->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = 0x00;
  Cdb[4] = 96;

  Packet.Timeout           = EfiScsiStallSeconds (2);
  Packet.Cdb               = Cdb;
  Packet.CdbLength         = 6;
  if((ScsiIo->IoAlign == 0) || (ScsiIo->IoAlign == 1)){
    Packet.InDataBuffer = Data;
  } else {
    Packet.InDataBuffer = (VOID *)(((UINTN)Data + ScsiIo->IoAlign - 1) &
		                  ~((UINTN)(ScsiIo->IoAlign - 1)));
  }
  Packet.InTransferLength  = 0xFFFFFFFF;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.DataDirection     = EFI_SCSI_IO_DATA_DIRECTION_READ;
  
  Status = ScsiIo->ExecuteScsiCommand (ScsiIo, &Packet, Event);

  if ( (Status == EFI_BAD_BUFFER_SIZE) || (Status == EFI_SUCCESS) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestConformanceAssertionGuid006,
                 L"EFI_SCSI_IO_PROTOCOL.ExecuteScsiCommand - Call ExecuteScsiCommand() with with too long InTransferLength",
                 L"%a:%d:Status - %r, The max length is %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Packet.InTransferLength
                 );

  //
  // Assertion Point 3.2.3.2.2
  // Call ExecuteScsiCommand() with invalid parameter.
  //
  
  //
  // Check Point 1. Invalid ScsiRequestPacket.
  //
  SctZeroMem (&Packet, sizeof (EFI_SCSI_IO_SCSI_REQUEST_PACKET));

  Status = ScsiIo->ExecuteScsiCommand (ScsiIo, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestConformanceAssertionGuid005,
                 L"EFI_SCSI_IO_PROTOCOL.ExecuteScsiCommand - Call ExecuteScsiCommand() with invalid ScsiRequestPacket",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  EnterEvent = 0;

  SctZeroMem (&Packet, sizeof (EFI_SCSI_IO_SCSI_REQUEST_PACKET));

  Status = ScsiIo->ExecuteScsiCommand (ScsiIo, &Packet, Event);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiIoBBTestConformanceAssertionGuid007,
                 L"EFI_SCSI_IO_PROTOCOL.ExecuteScsiCommand - Call ExecuteScsiCommand() with invalid ScsiRequestPacket",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Close the event
  Status = gtBS->CloseEvent (Event);
  if (EFI_ERROR(Status)) {
    return EFI_UNSUPPORTED;
  }

  SctFreePool (Data);

  return EFI_SUCCESS;
}
