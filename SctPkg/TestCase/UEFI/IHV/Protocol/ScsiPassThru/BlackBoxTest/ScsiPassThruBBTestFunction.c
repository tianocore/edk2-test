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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  ScsiPassThruBBTestFunction.c

Abstract:

  Interface Function Test Cases of Scsi Pass Through Protocol

--*/


#include "SctLib.h"
#include "ScsiPassThruBBTestMain.h"

extern UINT8 EnterEvent;

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.GetNextDevice Function Test.
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
BBTestGetNextDeviceFunctionAutoTest (
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

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.2.1
  // Retrieve the list of legal Target IDs and LUNs for SCSI devices on a SCSI channel.
  //
  Target = 0xFFFFFFFF;
  Status = EFI_SUCCESS;
  while (!EFI_ERROR(Status)) {
    Status = ScsiPassThru->GetNextDevice (ScsiPassThru, &Target, &Lun);
    if (!EFI_ERROR(Status )) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"SCSI device: Target - %d, Lun - %ld\n",
                     Target,
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
                 gScsiPassThruBBTestFunctionAssertionGuid001,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetNextDevice - Invoke GetNextDevice() and verify interface correctness within test case",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.BuildDevicePath Function Test.
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
BBTestBuildDevicePathFunctionAutoTest (
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
                   &StandardLib
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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.2.2.1
  // Call BuildDevicePath().
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

  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, Target, Lun, &DevicePath);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    gtBS->FreePool (DevicePath);
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestFunctionAssertionGuid002,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - Invoke BuildDevicePath() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 Lun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.GetTargetLun Function Test.
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
BBTestGetTargetLunFunctionAutoTest (
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
                   &StandardLib
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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.3.2.1
  // Call GetTargetLun().
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

  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, DevicePath, &NewTarget, &NewLun);

  //Free the DevicePath.
  gtBS->FreePool (DevicePath);

  if ((!EFI_ERROR(Status)) && (NewTarget == Target) && (NewLun == Lun)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestFunctionAssertionGuid003,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld, NewTarget - %d, NewLun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 Lun,
                 NewTarget,
                 NewLun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.ResetChannel Function Test.
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
BBTestResetChannelFunctionAutoTest (
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

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.4.2.1
  // Call ResetChannel().
  //
  Status = ScsiPassThru->ResetChannel (ScsiPassThru);

  if (Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestFunctionAssertionGuid004,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.ResetChannel - Invoke ResetChannel() and verify interface correctness within test case",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.ResetTarget Function Test.
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
BBTestResetTargetFunctionAutoTest (
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

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.5.2.1
  // Call ResetTarget().
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

  Status = ScsiPassThru->ResetTarget (ScsiPassThru, Target, Lun);

  if (Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestFunctionAssertionGuid005,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.ResetTarget - Invoke ResetTarget() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 Lun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.PassThru Function Test.
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
BBTestPassThruFunctionAutoTest (
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

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
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

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.6.2.1
  // Call PassThru() with NULL Event.
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
  // Initialize the Request Packet.
  //
  Data = (UINT8 *)SctAllocatePool (ScsiPassThru->Mode->IoAlign + 96);

  SctZeroMem (&Packet,sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb,6);
  SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout = EfiScsiStallSeconds (2);
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  if ((ScsiPassThru->Mode->IoAlign == 0) || (ScsiPassThru->Mode->IoAlign == 1)){
  	Packet.DataBuffer = (VOID *)Data;
  } else {
    Packet.DataBuffer = (VOID *)(((UINTN)Data + ScsiPassThru->Mode->IoAlign - 1) &
                                   ~(ScsiPassThru->Mode->IoAlign - 1));
  }
  Packet.TransferLength = 96;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, Lun, &Packet, NULL);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestFunctionAssertionGuid006,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with NULL Event",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld, TransferLen - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 Lun,
                 Packet.TransferLength
                 );

  //
  // Assertion Point 3.6.2.2
  // Call PassThru() with Event.
  //

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
                   L"%a:%d:Status - %r\n",
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
  SctZeroMem (&Packet,sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  SctZeroMem (Cdb,6);
  SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 96;

  Packet.Timeout = EfiScsiStallSeconds (2);
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  if ((ScsiPassThru->Mode->IoAlign == 0) || (ScsiPassThru->Mode->IoAlign == 1)){
  	Packet.DataBuffer = (VOID *)Data;
  } else {
    Packet.DataBuffer = (VOID *)(((UINTN)Data + ScsiPassThru->Mode->IoAlign - 1) &
                                   ~(ScsiPassThru->Mode->IoAlign - 1));
  }
  Packet.TransferLength = 96;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, Lun, &Packet, Event);

  if (!(ScsiPassThru->Mode->Attributes & EFI_SCSI_PASS_THRU_ATTRIBUTES_NONBLOCKIO)) {
    if (!EFI_ERROR(Status) && (EnterEvent == 0)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    //
    // wait for event being signaled.
    //
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
                 gScsiPassThruBBTestFunctionAssertionGuid007,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with Event",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Target,
                 Lun
                 );

  // Close the event
  Status = gtBS->CloseEvent (Event);
  if (EFI_ERROR(Status)) {
    return EFI_UNSUPPORTED;
  }

  SctFreePool (Data);

  return EFI_SUCCESS;
}


