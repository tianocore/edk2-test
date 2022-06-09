/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ScsiPassThruBBTestMain.c

Abstract:

  Test Driver of Scsi Pass Through Protocol

--*/

#include "SctLib.h"
#include "ScsiPassThruBBTestMain.h"

UINT8 EnterEvent;
//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SCSI_PASS_THRU_PROTOCOL_TEST_REVISION,
  EFI_SCSI_PASS_THRU_PROTOCOL_GUID,
  L"Scsi Pass Through Protocol Test",
  L"UEFI Scsi Pass Through Protocol Test"
};


EFI_GUID gSupportProtocolGuid[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SCSI_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_FUNCTION_AUTO_GUID,
    L"GetNextDevice_Func",
    L"Invoke GetNextDevice() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextDeviceFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID,
    L"BuildDevicePath_Func",
    L"Invoke BuildDevicePath() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_FUNCTION_AUTO_GUID,
    L"GetTargetLun_Func",
    L"Invoke GetTargetLun() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetTargetLunFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_RESET_CHANNEL_FUNCTION_AUTO_GUID,
    L"ResetChannel_Func",
    L"Invoke ResetChannel() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestResetChannelFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_FUNCTION_AUTO_GUID,
    L"ResetTarget_Func",
    L"Invoke ResetTarget() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestResetTargetFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID,
    L"PassThru_Func",
    L"Invoke PassThru() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_CONFORMANCE_AUTO_GUID,
    L"GetNextDevice_Conf",
    L"Test whether GetNextDevice() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextDeviceConformanceAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID,
    L"BuildDevicePath_Conf",
    L"Test whether BuildDevicePath() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathConformanceAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_CONFORMANCE_AUTO_GUID,
    L"GetTargetLun_Conf",
    L"Test whether GetTargetLun() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetTargetLunConformanceAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_CONFORMANCE_AUTO_GUID,
    L"ResetTarget_Conf",
    L"Test whether ResetTarget() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestResetTargetConformanceAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID,
    L"PassThru_Conf",
    L"Test whether PassThru() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruConformanceAutoTest
  },
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;



/**
 *  Scsi Pass Through Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestScsiPassThru (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);


  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestScsiPassThruProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
EFIAPI
BBTestScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

VOID
NotifyFunction (
  EFI_EVENT Event,
  VOID      *Context
  )
{
  EnterEvent = 1;
  return;
}

/**
 *  Function ransack all legal Target and Lun, find the max of them, 
 *  and add 1 to the max, get the invalid
 *  @param a pointer of EFI_SCSI_PASS_THRU_PROTOCOL.
 *  @param a pointer of Target.
 *  @param a pointer of Lun.
 *  @return EFI_SUCCESS if get the invalid Target and Lun successfully.
 */
EFI_STATUS
GetInvalidTargetLun(
  IN       EFI_SCSI_PASS_THRU_PROTOCOL   *ScsiPassThru,
  IN OUT   UINT32                        *Target,
  IN OUT   UINT64                        *Lun
)
{
  EFI_STATUS                  Status;
  UINT32                      MaxTarget = 0;
  UINT64                      MaxLun = 0;

  
  *Target = 0xFFFFFFFF;
  
  Status = EFI_SUCCESS;
  while (!EFI_ERROR(Status)) { 
    Status = ScsiPassThru->GetNextDevice (ScsiPassThru, Target, Lun);

	if (!EFI_ERROR(Status )) {
	  
      if (*Lun > MaxLun){
        MaxLun = *Lun;
      }
      if (*Target > MaxTarget){
        MaxTarget = *Target;
      }
    }
  }

  if (Status == EFI_NOT_FOUND) {
    if (MaxLun == 0xFFFFFFFFFFFFFFFE || MaxTarget == 0xFFFFFFFE)
	  return EFI_UNSUPPORTED;
	
    *Lun = MaxLun + 1;
	*Target = MaxTarget + 1;

    return EFI_SUCCESS;	
  }

  return EFI_UNSUPPORTED;
}
/**
 *  Function probe all legal Target and Lun, find valid Target and Lun
 *  which point to the present device on SCSI channel
 *  @param a pointer of EFI_SCSI_PASS_THRU_PROTOCOL.
 *  @param a pointer of Target.
 *  @param a pointer of Lun.
 *  @return EFI_SUCCESS if get the valid Target and Lun successfully.
 */
EFI_STATUS
GetPresentTargetLun(
  IN    EFI_SCSI_PASS_THRU_PROTOCOL  *ScsiPassThru,
  IN OUT   UINT32                        *Target,
  IN OUT   UINT64                        *Lun
)
{
  EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET Packet;
  UINT8                                  Cdb[6];
  UINT8                                  *Data;
  EFI_STATUS                             Status = EFI_SUCCESS;
  

  Data = (UINT8 *)SctAllocateZeroPool (ScsiPassThru->Mode->IoAlign + 96);
  
  while (EFI_NOT_FOUND != ScsiPassThru->GetNextDevice (ScsiPassThru, Target, Lun)) { 
  	//
    // Initialize the Request Packet.
    //
    SctZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
    SctZeroMem (Cdb, 6);
    SctZeroMem (Data, ScsiPassThru->Mode->IoAlign + 96);
  
    // Set to OP_INQUIRY.
    Cdb[0] = 0x12;
    Cdb[1] = (UINT8)(((UINT8)(*Lun) << 5) & 0xE0);
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
	
    Status = ScsiPassThru->PassThru (ScsiPassThru, *Target, *Lun, &Packet, NULL);

    if (Status == EFI_SUCCESS)
		break;
  }

  SctFreePool (Data);

  return Status;
}
