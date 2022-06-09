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

    NVMEPassThruBBTestConformance.c

Abstract:

    for EFI Driver NVME PassThru Protocol's Conformance Test

--*/

#include "NVMEPassThruBBTestMain.h"

EFI_STATUS
EFIAPI
BBTestGetNextNamespaceConformanceTest (
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
  UINT32                                LastNameSpaceId;

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
  LastNameSpaceId = 0xFFFFFFFF;

  while(!EFI_ERROR(Status )) {
    Status = NVMEPassThru->GetNextNamespace (NVMEPassThru, &NameSpaceId);
    if (!EFI_ERROR(Status )) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"Next valid namespace ID on NVM Express controller: %x\n",
                     NameSpaceId
                     );
      LastNameSpaceId = NameSpaceId;
    }
  }

  if (Status == EFI_NOT_FOUND && LastNameSpaceId != 0xFFFFFFFF) {
    LastNameSpaceId++;
    Status = NVMEPassThru->GetNextNamespace (NVMEPassThru, &LastNameSpaceId);
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gNVMEPassThruBBTestConformanceAssertionGuid001,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.GetNextNamespace - call GetNextNamespace() with invalid NameSpaceId, the status should be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  }



  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestBuildDevicePathConformanceTest (
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
  UINT32                                LastNameSpaceId;
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

  NameSpaceId  = 0xFFFFFFFF;
  LastNameSpaceId = 0xFFFFFFFF;
  
  while(!EFI_ERROR(Status )) {
    Status = NVMEPassThru->GetNextNamespace (NVMEPassThru, &NameSpaceId);
    if (!EFI_ERROR(Status )) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"Next valid namespace ID on NVM Express controller: %x\n",
                     NameSpaceId
                     );
      LastNameSpaceId = NameSpaceId;
    }
  }

  if (Status == EFI_NOT_FOUND  && LastNameSpaceId != 0xFFFFFFFF) {
    Status = NVMEPassThru->BuildDevicePath (NVMEPassThru, LastNameSpaceId, NULL);
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gNVMEPassThruBBTestConformanceAssertionGuid002,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath() with NULL DevicePath, the status should be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

    LastNameSpaceId++;
    Status = NVMEPassThru->BuildDevicePath (NVMEPassThru, LastNameSpaceId, &DevicePath);
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gNVMEPassThruBBTestConformanceAssertionGuid003,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath() with invalid NameSpaceId, the status should be EFI_NOT_FOUND",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNamespaceConformanceTest (
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
  DevicePath = NULL;
  Status = NVMEPassThru->GetNextNamespace (NVMEPassThru, &InNameSpaceId);
  if (Status == EFI_SUCCESS) {
    Status = NVMEPassThru->BuildDevicePath (NVMEPassThru, InNameSpaceId, &DevicePath);
    if (Status == EFI_SUCCESS) {
      Status = NVMEPassThru->GetNamespace (NVMEPassThru, DevicePath, NULL);
      if (Status == EFI_INVALID_PARAMETER)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gNVMEPassThruBBTestConformanceAssertionGuid004,
                     L"EFI_NVME_PASS_THRU_PROTOCOL.GetNameSpace - call GetNameSpace() with NULL NamespaceId, the status should be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      Status = NVMEPassThru->GetNamespace (NVMEPassThru, NULL, &InNameSpaceId);
      if (Status == EFI_INVALID_PARAMETER)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gNVMEPassThruBBTestConformanceAssertionGuid005,
                     L"EFI_NVME_PASS_THRU_PROTOCOL.GetNameSpace - call GetNameSpace() with NULL DevicePath, the status should be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      //
      // Set the Device Path to End Device Path.
      //
      DevicePath->Type    = 0x7F;
      DevicePath->SubType = 0xFF;
      Status = NVMEPassThru->GetNamespace (NVMEPassThru, DevicePath, &InNameSpaceId);
      if (Status == EFI_UNSUPPORTED)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gNVMEPassThruBBTestConformanceAssertionGuid006,
                     L"EFI_NVME_PASS_THRU_PROTOCOL.GetNameSpace - call GetNameSpace() with unsupportted device path node, the status should be EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );      

      //
      // restore to the NVME Device Path Node
      //
      DevicePath->Type    = 0x03;
      DevicePath->SubType = 0x17;            

      ((NVME_NAMESPACE_DEVICE_PATH *)DevicePath)->NamespaceId = 0xFFFFFFFF;
      
      Status = NVMEPassThru->GetNamespace (NVMEPassThru, DevicePath, &InNameSpaceId);
      if (Status == EFI_NOT_FOUND)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gNVMEPassThruBBTestConformanceAssertionGuid007,
                     L"EFI_NVME_PASS_THRU_PROTOCOL.GetNameSpace - call GetNameSpace(), but translation from DevicePath to namespace ID failed",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );    

    }
  }

  if (DevicePath != NULL)
    SctFreePool(DevicePath);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestPassThruConformanceTest (
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
  Packet.TransferLength = sizeof (NVME_ADMIN_NAMESPACE_DATA);
  Packet.MetadataBuffer = NULL;
  Packet.MetadataLength = 0;
  Packet.QueueType = NVME_ADMIN_QUEUE;

  NvmeCmd.Cdw0.Opcode = 0x06;  //Identify 
  NvmeCmd.Flags = CDW10_VALID;
  NvmeCmd.Nsid = 0;
  NvmeCmd.Cdw10 = 1;
  
  if (NVMEPassThru->Mode->IoAlign != 0 && NVMEPassThru->Mode->IoAlign != 1) {
    Packet.TransferBuffer = (VOID *)((UINTN)NamespaceData + 1);
    Status = NVMEPassThru->PassThru (NVMEPassThru, 0, &Packet, NULL);
    if (Status == EFI_INVALID_PARAMETER)
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gNVMEPassThruBBTestConformanceAssertionGuid008,
                   L"EFI_NVME_PASS_THRU_PROTOCOL.PassThru - TransferBuffer does not meet the alignment requirement specified by the IoAlign field of the EFI_NVM_EXPRESS_PASS_THRU_MODE",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Packet.TransferBuffer = NamespaceData;
  }

  Packet.QueueType = NVME_ADMIN_QUEUE + 2;

  Status = NVMEPassThru->PassThru (NVMEPassThru, 0, &Packet, NULL);
  if (Status == EFI_INVALID_PARAMETER)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gNVMEPassThruBBTestConformanceAssertionGuid009,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.PassThru - QueueType is not 0 (Admin Submission Queue) or 1 (I/O Submission Queue), then EFI_INVALID_PARAMETER is returned",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

/*
  It depends on the device's implementation to ignore the Flag/value pair or not 
  We remove this checkpoints here.
  
  Packet.QueueType = NVME_ADMIN_QUEUE;
  NvmeCmd.Flags = CDW10_VALID | CDW11_VALID;    // CDW11_VALID
  NvmeCmd.Cdw11 = 0x23;

  Status = NVMEPassThru->PassThru (NVMEPassThru, 0, &Packet, NULL);
  if (Status == EFI_INVALID_PARAMETER || Status == EFI_DEVICE_ERROR)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gNVMEPassThruBBTestConformanceAssertionGuid010,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.PassThru - only CDW10 is valid for the identify command",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
*/

/*
  It is difficult to get the controller's Cap.Mpsmin even we get the Mdts from the 77th bytes from the TransferBuffer
  we remove this checkpoint here.

  NvmeCmd.Flags = CDW10_VALID;
  Packet.TransferLength = sizeof (NVME_ADMIN_NAMESPACE_DATA) + 10;


  Status = NVMEPassThru->PassThru (NVMEPassThru, 0, &Packet, NULL);
  if (Status == EFI_BAD_BUFFER_SIZE && Packet.TransferLength == sizeof (NVME_ADMIN_NAMESPACE_DATA))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gNVMEPassThruBBTestConformanceAssertionGuid011,
                 L"EFI_NVME_PASS_THRU_PROTOCOL.PassThru - TransferLength is too big to be transferred in a single command",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
 */ 

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
  
  return EFI_SUCCESS;
}
