/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AtaPassThruBBTestMain.c

Abstract:

  Test Driver of ATA Pass Through Protocol

--*/

#include "SctLib.h"
#include "AtaPassThruBBTestMain.h"

UINT8    EnterEvent;
//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  ATA_PASS_THRU_PROTOCOL_TEST_REVISION,
  EFI_ATA_PASS_THRU_PROTOCOL_GUID,
  L"Ata Pass Through Protocol Test",
  L"UEFI Ata Pass Through Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    ATA_PASS_THRU_PROTOCOL_GET_NEXT_PORT_FUNCTION_AUTO_GUID,
    L"GetNextPort_Func",
    L"Invoke GetNextPort() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextPortFunctionAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID,
    L"BuildDevicePath_Func",
    L"Invoke BuildDevicePath() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathFunctionAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_GET_DEVICE_FUNCTION_AUTO_GUID,
    L"GetDevice_Func",
    L"Invoke GetDevice() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDeviceFunctionAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_RESET_PORT_FUNCTION_AUTO_GUID,
    L"ResetPort_Func",
    L"Invoke ResetPort() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO |EFI_TEST_CASE_RESET_REQUIRED,
    BBTestResetPortFunctionAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_RESET_DEVICE_FUNCTION_AUTO_GUID,
    L"ResetDevice_Func",
    L"Invoke ResetDevice() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO |EFI_TEST_CASE_RESET_REQUIRED,
    BBTestResetDeviceFunctionAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_FUNCTION_AUTO_GUID,
    L"GetNextDevice_Func",
    L"Invoke GetNextDevice() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextDeviceFunctionAutoTest
  },
  
  {
    ATA_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID,
    L"PassThru_Func",
    L"Invoke PassThru() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruFunctionAutoTest
  },
  
  {
    ATA_PASS_THRU_PROTOCOL_MODE_CONFORMANCE_AUTO_GUID,
    L"Mode_Conf",
    L"Test whether Mode conforms to spec",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestModeConformanceAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_GET_NEXT_PORT_CONFORMANCE_AUTO_GUID,
    L"GetNextPort_Conf",
    L"Test whether GetNextPort() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextPortConformanceAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID,
    L"BuildDevicePath_Conf",
    L"Test whether BuildDevicePath() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathConformanceAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_GET_DEVICE_CONFORMANCE_AUTO_GUID,
    L"GetDevice_Conf",
    L"Test whether GetDevice() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDeviceConformanceAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_RESET_DEVICE_CONFORMANCE_AUTO_GUID,
    L"ResetDevice_Conf",
    L"Test whether ResetDevice() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO |EFI_TEST_CASE_RESET_REQUIRED,
    BBTestResetDeviceConformanceAutoTest
  },

  {
    ATA_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_CONFORMANCE_AUTO_GUID,
    L"GetNextDevice_Conf",
    L"Test whether GetNextDevice() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextDeviceConformanceAutoTest
  },	
  
  {
    ATA_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID,
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
EFIAPI
BBTestAtaPassThruProtocolUnload (
  IN EFI_HANDLE    ImageHandle
  );


/**
 *  Scsi Pass Through Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestAtaPassThru (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);


  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestAtaPassThruProtocolUnload,
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
BBTestAtaPassThruProtocolUnload (
  IN EFI_HANDLE    ImageHandle
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
  EFI_EVENT    Event,
  VOID         *Context
  )
{
  EnterEvent = 1;
  return;
}

/**
 *  Function scan all legal Port, find the max of them, 
 *  and add 1 to the max, get the invalid
 *  @param a pointer of EFI_ATA_PASS_THRU_PROTOCOL.
 *  @param a pointer of Port.
 *  @return EFI_SUCCESS if get the invalid Port successfully.
 */
EFI_STATUS
GetInvalidPort(
  IN    EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  OUT   UINT16                        *InvalidPort
)
{
  EFI_STATUS    Status;
  UINT16        Port;

  Port         = 0xFFFF;  
  *InvalidPort = 0;
  
  Status = AtaPassThru->GetNextPort (AtaPassThru, &Port);
  if (EFI_ERROR(Status)) {
    return EFI_UNSUPPORTED;
  }

  *InvalidPort = Port;
  while (!EFI_ERROR(Status)) { 
    Status = AtaPassThru->GetNextPort (AtaPassThru, &Port);

    if (!EFI_ERROR(Status )) {
	  
      if (Port > *InvalidPort){
        *InvalidPort = Port;
      }
      
    }
  }

  if (Status == EFI_NOT_FOUND) {
    if (*InvalidPort == 0xFFFF){
      return EFI_UNSUPPORTED;
    }
    *InvalidPort += 32;	

    return EFI_SUCCESS;	
  }

  return EFI_UNSUPPORTED;
}

/**
 *  Function scan all legal Port
 *  @param a pointer of EFI_ATA_PASS_THRU_PROTOCOL.
 *  @param a pointer of Port.
 *  @return EFI_SUCCESS if get the invalid Port successfully.
 */
EFI_STATUS
GetValidPort(
  IN    EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  OUT   UINT16                        *Port
)
{
  EFI_STATUS    Status;
  
  *Port  = 0xFFFF;  
  Status = EFI_SUCCESS;
  while (!EFI_ERROR(Status)) { 
    Status = AtaPassThru->GetNextPort (AtaPassThru, Port);

    if (!EFI_ERROR(Status )) {
	  break;
    }
  }

  return Status;
}

/**
 *  Function scan all legal PortMultiplierPort, find the max of them, 
 *  and add 1 to the max, get the invalid
 *  @param a pointer of EFI_ATA_PASS_THRU_PROTOCOL.
 *  @param a pointer of Port.
 *  @return EFI_SUCCESS if get the invalid Port successfully.
 */
EFI_STATUS
GetInvalidPortMultiplierPort(
  IN    EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  IN    UINT16                        Port,
  OUT   UINT16                        *InvalidPortMultiplierPort
)
{
  EFI_STATUS    Status;
  UINT16        Device;

  Device                     = 0xFFFF;  
  *InvalidPortMultiplierPort = 0;

  Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &Device);
  if (EFI_ERROR(Status)) {
    return EFI_UNSUPPORTED;
  }

  *InvalidPortMultiplierPort = Device;
  while (!EFI_ERROR(Status)) { 
    Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &Device);

    if (!EFI_ERROR(Status)) {
	  
      if (Device > *InvalidPortMultiplierPort){
        *InvalidPortMultiplierPort = Device;
      }
      
    }
  }

  if (Status == EFI_NOT_FOUND) {
    if (*InvalidPortMultiplierPort == 0xFFFF){
	  return EFI_UNSUPPORTED;
    }

    *InvalidPortMultiplierPort += 16;	

    return EFI_SUCCESS;	
  }

  return EFI_UNSUPPORTED;
}

/**
 *  Function check return status
 *  @param AtaStatus.
 *  @return TRUE if identify device successfully.
 */
BOOLEAN
NormalOutput(
  IN    UINT8    AtaStatus
)
{
  if ((AtaStatus & 0xE9) == 0x40){
    return TRUE;
  }
  return FALSE;
}
/**
 *  Function probe all legal port, find valid PortMultiplierPort
 *  which point to the present device on port
 *  @param a pointer of EFI_ATA_PASS_THRU_PROTOCOL.
 *  @param a pointer of Port.
 *  @param a pointer of PortMultiplierPort.
 *  @return EFI_SUCCESS if get the valid device successfully.
 */
 EFI_STATUS
GetPresentDevice(
  IN       EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  IN OUT   UINT16                        *Port,
  IN OUT   UINT16                        *PortMultiplierPort,
     OUT   UINT8* AtaStatus
)
{
  EFI_ATA_PASS_THRU_COMMAND_PACKET    Packet;
  EFI_ATA_COMMAND_BLOCK               Acb;
  EFI_ATA_STATUS_BLOCK                *Asb;
  VOID*                               InData;
  EFI_STATUS                          Status;
  UINT16                              BackupPort;
  UINT16                              BackupPortMultiplierPort;
  BOOLEAN                             BackupAvailable;

  BackupAvailable          = FALSE;
  BackupPort               = 0xFFFF;
  BackupPortMultiplierPort = 0xFFFF;
  *AtaStatus               = 0;

  Asb    = NULL;
  InData = NULL;
  Asb    = SctAllocateZeroPool (AtaPassThru->Mode->IoAlign + sizeof(EFI_ATA_STATUS_BLOCK));
  InData = SctAllocateZeroPool (AtaPassThru->Mode->IoAlign + 512);
  if ((Asb == NULL) || (InData == NULL)){
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }
  //
  // Initialize ACB.
  //
  SctZeroMem (&Acb, sizeof (EFI_ATA_COMMAND_BLOCK));
  Acb.AtaCommand = 0xEC;
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet,sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
    
  if ((AtaPassThru->Mode->IoAlign == 0) || (AtaPassThru->Mode->IoAlign == 1)){
    Packet.Asb          = Asb;
    Packet.InDataBuffer = InData;
  } else {
    Packet.Asb          = (VOID *)(((UINTN)Asb + AtaPassThru->Mode->IoAlign - 1)& 
    		                  ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
    Packet.InDataBuffer = (VOID *)(((UINTN)InData + AtaPassThru->Mode->IoAlign - 1)& 
    		                  ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
  }  
   
  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 512;
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;
  
  while (!EFI_ERROR(Status = AtaPassThru->GetNextPort (AtaPassThru, Port))) { 
    while (!EFI_ERROR(Status = AtaPassThru->GetNextDevice (AtaPassThru, *Port, PortMultiplierPort))) {
      Acb.AtaDeviceHead = (UINT8)((UINT8)(*PortMultiplierPort) << 4);
    
      Status = AtaPassThru->PassThru (AtaPassThru, *Port, *PortMultiplierPort, &Packet, NULL);
      if (Status == EFI_SUCCESS){
        if (NormalOutput((Packet.Asb)->AtaStatus)) {
          goto Done;
        }
        BackupAvailable          = TRUE;
        BackupPort               = *Port;
        BackupPortMultiplierPort = *PortMultiplierPort;
        *AtaStatus               = (Packet.Asb)->AtaStatus;
      }
    }

  }

Done:
  if (Asb != NULL) {
    SctFreePool (Asb);
  }
  if (InData != NULL) {
    SctFreePool (InData);
  }

  if (BackupAvailable) {
    *Port               = BackupPort;
    *PortMultiplierPort = BackupPortMultiplierPort;
    return EFI_SUCCESS;
  }
  
  return Status;
}
