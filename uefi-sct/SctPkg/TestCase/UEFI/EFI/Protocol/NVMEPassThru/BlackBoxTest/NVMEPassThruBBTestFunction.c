/** @file

  Copyright 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    NVMEPassThruBBTestFunction.c

Abstract:

    for EFI Driver NVME PassThru Protocol's Function Test

--*/

#include "NVMEPassThruBBTestMain.h"

extern UINT8 EnterEvent;

EFI_STATUS
EFIAPI
BBTestGetNextNamespaceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *NVMEPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT32                                NameSpaceId;

  NVMEPassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL*)ClientInterface;
  

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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  NameSpaceId  = 0xFFFFFFFF;

  while(!EFI_ERROR(Status )) {
    Status = NVMEPassThru->GetNextNamespace (NVMEPassThru, &NameSpaceId);
    if (!EFI_ERROR(Status )) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"Next valid namespace ID on NVM Express controller: %x\n",
                     NameSpaceId
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
                 gNVMEPassThruBBTestFunctionAssertionGuid001,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.GetNextNamespace - Invoke GetNextNamespace() and verify interface correctness within test case",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestBuildDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *NVMEPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT32                                InNameSpaceId;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;

  NVMEPassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL*)ClientInterface;
  

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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );   
    return Status;
  }

  InNameSpaceId  = 0xFFFFFFFF;
  Status = NVMEPassThru->GetNextNamespace (NVMEPassThru, &InNameSpaceId);
  if (Status == EFI_SUCCESS) {
    DevicePath = NULL;
    Status = NVMEPassThru->BuildDevicePath (NVMEPassThru, InNameSpaceId, &DevicePath);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (((NVME_NAMESPACE_DEVICE_PATH *)DevicePath)->NamespaceId != InNameSpaceId)
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else if (Status == EFI_OUT_OF_RESOURCES) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gNVMEPassThruBBTestFunctionAssertionGuid002,
                   L"EFI_NVME_PASS_THRU_PROTOCOL.BuildDevicePath - Invoke BuildDevicePath() and verify interface correctness within test case",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (DevicePath != NULL)
      SctFreePool(DevicePath);
  }

  return EFI_SUCCESS;
} 


EFI_STATUS
EFIAPI
BBTestGetNamespaceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *NVMEPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT32                                InNameSpaceId;
  UINT32                                OutNameSpaceId;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;

  NVMEPassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL*)ClientInterface;
  

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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );   
    return Status;
  }

  InNameSpaceId  = 0xFFFFFFFF;
  Status = NVMEPassThru->GetNextNamespace (NVMEPassThru, &InNameSpaceId);
  if (Status == EFI_SUCCESS) {
    DevicePath = NULL;
    Status = NVMEPassThru->BuildDevicePath (NVMEPassThru, InNameSpaceId, &DevicePath);
    if (Status == EFI_SUCCESS) {
      Status = NVMEPassThru->GetNamespace (NVMEPassThru, DevicePath, &OutNameSpaceId);
      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if (InNameSpaceId != OutNameSpaceId || ((NVME_NAMESPACE_DEVICE_PATH *)DevicePath)->NamespaceId != OutNameSpaceId)
          AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gNVMEPassThruBBTestFunctionAssertionGuid003,
                     L"EFI_NVME_PASS_THRU_PROTOCOL.GetNamespace - Invoke GetNamespace() and verify interface correctness within test case",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    }

    if (DevicePath != NULL)
      SctFreePool(DevicePath);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestPassThruFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL        *StandardLib;
  EFI_STATUS                                Status;
  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL        *NVMEPassThru;
  EFI_TEST_ASSERTION                        AssertionType;
  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET  Packet;
  EFI_NVM_EXPRESS_COMMAND                   NvmeCmd;
  EFI_NVM_EXPRESS_COMPLETION                NvmeCompletion;
  EFI_EVENT                                 Event;
  NVME_ADMIN_NAMESPACE_DATA                 *NamespaceData;  
  
  NVMEPassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL*)ClientInterface;

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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );   
    return Status;
  }

  if (NVMEPassThru->Mode->Attributes & (EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL | EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gNVMEPassThruBBTestFunctionAssertionGuid004,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.Mode - neither EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL nor EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL set is an illegal configuration",
                 L"%a:%d:Attributes - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 NVMEPassThru->Mode->Attributes
                 );

  if (AssertionType == EFI_TEST_ASSERTION_FAILED)
    return EFI_SUCCESS;


  if ((NVMEPassThru->Mode->IoAlign != 0) && ((NVMEPassThru->Mode->IoAlign & (NVMEPassThru->Mode->IoAlign - 1)) != 0)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gNVMEPassThruBBTestFunctionAssertionGuid005,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.Mode - IoAlign should be the power of 2",
                 L"%a:%d:IoAlign - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 NVMEPassThru->Mode->IoAlign
                 );


  if (NVMEPassThru->Mode->Attributes & EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM) {

    NamespaceData = AllocateAlignedPool (EfiBootServicesData, sizeof(NVME_ADMIN_NAMESPACE_DATA), NVMEPassThru->Mode->IoAlign);
    if(NamespaceData == NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocateAlignedPool - Allocate Aligned Pool for testing",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     EFI_UNSUPPORTED
                     );
      return EFI_UNSUPPORTED; 
    }
  	
    SctZeroMem (&Packet, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
    SctZeroMem (&NvmeCmd, sizeof(EFI_NVM_EXPRESS_COMMAND));
    SctZeroMem (&NvmeCompletion, sizeof(EFI_NVM_EXPRESS_COMPLETION));


    Packet.NvmeCmd = &NvmeCmd;
    Packet.NvmeCompletion = &NvmeCompletion;

    Packet.CommandTimeout = NVME_GENERIC_TIMEOUT;
    Packet.TransferBuffer = NamespaceData;
    Packet.TransferLength = sizeof (NVME_ADMIN_NAMESPACE_DATA);;
    Packet.MetadataBuffer = NULL;
    Packet.MetadataLength = 0;
    Packet.QueueType = NVME_ADMIN_QUEUE;  

    NvmeCmd.Cdw0.Opcode = 0x06;  //Identify
    NvmeCmd.Flags = CDW10_VALID;
    NvmeCmd.Nsid = 0;
    NvmeCmd.Cdw10 = 1;  

    Status = NVMEPassThru->PassThru (NVMEPassThru, 0, &Packet, NULL);
    if (Status == EFI_SUCCESS)
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gNVMEPassThruBBTestFunctionAssertionGuid006,
                   L"EFI_NVME_PASS_THRU_PROTOCOL.PassThru - PassThru return EFI_SUCCESS with the valid Identify Command",
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
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return EFI_SUCCESS;
    }

    EnterEvent = 0;    

    SctZeroMem (&Packet, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
    SctZeroMem (&NvmeCmd, sizeof(EFI_NVM_EXPRESS_COMMAND));
    SctZeroMem (&NvmeCompletion, sizeof(EFI_NVM_EXPRESS_COMPLETION));


    Packet.NvmeCmd = &NvmeCmd;
    Packet.NvmeCompletion = &NvmeCompletion;

    Packet.CommandTimeout = NVME_GENERIC_TIMEOUT;
    Packet.TransferBuffer = NamespaceData;
    Packet.TransferLength = sizeof (NVME_ADMIN_NAMESPACE_DATA);;
    Packet.MetadataBuffer = NULL;
    Packet.MetadataLength = 0;
    Packet.QueueType = NVME_ADMIN_QUEUE;  

    NvmeCmd.Cdw0.Opcode = 0x06;  //Identify
    NvmeCmd.Flags = CDW10_VALID;
    NvmeCmd.Nsid = 0;
    NvmeCmd.Cdw10 = 1;  

    Status = NVMEPassThru->PassThru (NVMEPassThru, 0, &Packet, Event);
    
    if (NVMEPassThru->Mode->Attributes & EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_NONBLOCKIO) {
      gtBS->Stall (5*1000*1000);
      if (Status == EFI_SUCCESS && EnterEvent == 1)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

    } else {
      if (Status == EFI_SUCCESS && EnterEvent == 0)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Status == EFI_NOT_READY || Status == EFI_DEVICE_ERROR || Status == EFI_TIMEOUT) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
      if (EnterEvent == 1) {//Event should NOT be triggered if return not ready.
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gNVMEPassThruBBTestFunctionAssertionGuid007,
                   L"EFI_NVME_PASS_THRU_PROTOCOL.PassThru - PassThru return EFI_SUCCESS with the valid Get Feature Command",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    

    gtBS->CloseEvent (Event);

    Status = FreeAlignedPool(NamespaceData);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"FreeAlignedPool - Free Aligned Pool for testing",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     ); 
      return Status; 
    }

  }
  
  return EFI_SUCCESS;
}
