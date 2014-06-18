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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  ExtScsiPassThruBBTestMain.c

Abstract:

  Test Driver of Extended Scsi Pass Through Protocol

--*/

#include "SctLib.h"
#include "ExtScsiPassThruBBTestMain.h"

UINT8 EnterEvent;
//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EXT_SCSI_PASS_THRU_PROTOCOL_TEST_REVISION,
  IHV_EXT_SCSI_PASS_THRU_PROTOCOL_GUID,
  L"Scsi Pass Through Protocol Test",
  L"UEFI Scsi Pass Through Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_LUN_FUNCTION_AUTO_GUID,
    L"GetNextTargetLun_Func",
    L"Invoke GetNextTargetLun() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextTargetLunFunctionAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID,
    L"BuildDevicePath_Func",
    L"Invoke BuildDevicePath() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathFunctionAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_FUNCTION_AUTO_GUID,
    L"GetTargetLun_Func",
    L"Invoke GetTargetLun() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetTargetLunFunctionAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_RESET_CHANNEL_FUNCTION_AUTO_GUID,
    L"ResetChannel_Func",
    L"Invoke ResetChannel() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetChannelFunctionAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_LUN_FUNCTION_AUTO_GUID,
    L"ResetTargetLun_Func",
    L"Invoke ResetTargetLun() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetTargetLunFunctionAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_FUNCTION_AUTO_GUID,
    L"GetNextTarget_Func",
    L"Invoke GetNextTarget() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextTargetFunctionAutoTest
  },
  
  {
    EXT_SCSI_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID,
    L"PassThru_Func",
    L"Invoke PassThru() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruFunctionAutoTest
  },
  
  {
    EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_LUN_CONFORMANCE_AUTO_GUID,
    L"GetNextTargetLun_Conf",
    L"Test whether GetNextTargetLun() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextTargetLunConformanceAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID,
    L"BuildDevicePath_Conf",
    L"Test whether BuildDevicePath() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathConformanceAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_CONFORMANCE_AUTO_GUID,
    L"GetTargetLun_Conf",
    L"Test whether GetTargetLun() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetTargetLunConformanceAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_LUN_CONFORMANCE_AUTO_GUID,
    L"ResetTargetLun_Conf",
    L"Test whether ResetTargetLun() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetTargetLunConformanceAutoTest
  },

  {
    EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_CONFORMANCE_AUTO_GUID,
    L"GetNextTarget_Conf",
    L"Test whether GetNextTarget() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextTargetConformanceAutoTest
  },	
  
  {
    EXT_SCSI_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID,
    L"PassThru_Conf",
    L"Test whether PassThru() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruConformanceAutoTest
  },
  
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestExtScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Scsi Pass Through Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestExtScsiPassThru (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);


  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestExtScsiPassThruProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestExtScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeIHVBBTestInterface (
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

EFI_STATUS
BufToUHexString (
  IN OUT CHAR16                    *Str,
  IN OUT UINTN                     *HexStringBufferLength,
  IN     UINT8                     *Buf,
  IN     UINTN                      Len
  )
{
  UINTN       Idx;
  UINT8       Byte;
  UINTN       StrLen;
  
  StrLen = Len * 2;
  if (StrLen > ((*HexStringBufferLength) - 1)) {
    *HexStringBufferLength = StrLen + 1;
    return EFI_BUFFER_TOO_SMALL;
  }

  *HexStringBufferLength = StrLen + 1;
  //
  // Ends the string.
  //
  Str[StrLen] = L'\0'; 

  for (Idx = 0; Idx < Len; Idx++) {

    Byte = Buf[Idx];
    Str[Idx * 2 + 1] = SctNibbleToHexChar (Byte);
    Str[Idx * 2] = SctNibbleToHexChar ((UINT8)(Byte >> 4));
  }

  return EFI_SUCCESS;
}

/**
 *  Function ransack all legal Target and Lun, find the max of them, 
 *  and add 1 to the max, get the invalid
 *  @param a pointer of EFI_EXT_SCSI_PASS_THRU_PROTOCOL.
 *  @param a pointer of Target.
 *  @param a pointer of Lun.
 *  @return EFI_SUCCESS if get the invalid Target and Lun successfully.
 */
EFI_STATUS
GetInvalidTargetLun(
  IN    EFI_EXT_SCSI_PASS_THRU_PROTOCOL  *ExtScsiPassThru,
  IN OUT   UINT8                         *TargetAddr,
  IN OUT   UINT64                        *Lun
)
{
  EFI_STATUS                  Status;
  INT8                        Index;
  UINT8                       MaxTarget[TARGET_MAX_BYTES];
  UINT64                      MaxLun = 0;
  UINT8                       Switch = 0;

  
  SctSetMem (MaxTarget, TARGET_MAX_BYTES, 0x00);
  SctSetMem (TargetAddr, TARGET_MAX_BYTES, 0xFF);    
  
  Status = EFI_SUCCESS;
  while (!EFI_ERROR(Status)) { 
    Status = ExtScsiPassThru->GetNextTargetLun (ExtScsiPassThru, (UINT8 **)&TargetAddr, Lun);

    if (!EFI_ERROR(Status )) {
      
      if (*Lun > MaxLun){
        MaxLun = *Lun;
      }
      //for (Index = 0; Index < TARGET_MAX_BYTES; Index++) {
      for( Index = TARGET_MAX_BYTES - 1; Index >= 0; Index--) {
        if (MaxTarget[Index] < TargetAddr[Index]) {
          Switch = 1;
          break;
        }
        if (MaxTarget[Index] > TargetAddr[Index]){
          break;
        }
      }
      if (Switch == 1) {
        Switch = 0;
        SctCopyMem (MaxTarget, TargetAddr, TARGET_MAX_BYTES);
      }
    }
  }

  if (Status == EFI_NOT_FOUND) {
    if (MaxLun == 0xFFFFFFFFFFFFFFFF)
      return EFI_UNSUPPORTED;

    *Lun = MaxLun + 1;

    for (Index = 0; Index < TARGET_MAX_BYTES; Index++) {
      if (MaxTarget[Index] == 0xFF) {
    
        if (Index == TARGET_MAX_BYTES - 1) {
          return EFI_UNSUPPORTED;
        }
        MaxTarget[Index] = 0x00;
      } else {
        MaxTarget[Index] = MaxTarget[Index] + 1;
        break;    
      }
    }

    SctCopyMem (TargetAddr, MaxTarget, TARGET_MAX_BYTES);	

    return EFI_SUCCESS;	
  }

  return EFI_UNSUPPORTED;
}


/**
 *  Function probe all legal Target and Lun, find valid Target and Lun
 *  which point to the present device on SCSI channel
 *  @param a pointer of EFI_EXT_SCSI_PASS_THRU_PROTOCOL.
 *  @param a pointer of Target.
 *  @param a pointer of Lun.
 *  @return EFI_SUCCESS if get the valid Target and Lun successfully.
 */
 EFI_STATUS
GetPresentTargetLun(
  IN    EFI_EXT_SCSI_PASS_THRU_PROTOCOL  *ExtScsiPassThru,
  IN OUT   UINT8                         *TargetAddr,
  IN OUT   UINT64                        *Lun
)
{
  EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET Packet;
  UINT8                                      Cdb[6];
  UINT8                                      *Data;
  EFI_STATUS                                 Status = EFI_NOT_FOUND;

  Data = SctAllocateZeroPool (ExtScsiPassThru->Mode->IoAlign + 96);
  
  while (EFI_NOT_FOUND != ExtScsiPassThru->GetNextTargetLun (ExtScsiPassThru, (UINT8 **)&TargetAddr, Lun)) { 
    //
    // Initialize the Request Packet.
    //
    SctZeroMem (&Packet,sizeof (EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
    SctZeroMem (Cdb, 6);
    SctZeroMem (Data, ExtScsiPassThru->Mode->IoAlign + 96);
    
    // Set to OP_INQUIRY.
    Cdb[0] = 0x12;
    Cdb[1] = (UINT8)(((UINT8)(*Lun) << 5) & 0xE0);
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
    
    Status = ExtScsiPassThru->PassThru (ExtScsiPassThru, TargetAddr, (*Lun), &Packet, NULL);

    if (Status == EFI_SUCCESS)
        break;
    
  }

  SctFreePool (Data);

  return Status;
}
