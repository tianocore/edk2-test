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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  StorageSecurityCommandBBTestConformance.c

Abstract:

  Consistency Test Cases of Storage Security Command Protocol

--*/


#include "SctLib.h"
#include "StorageSecurityCommandBBTestMain.h"

/**
 *  Entrypoint for EFI_STORAGE_SECURITY_COMMAND_PROTOCOL.ReceiveData() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 
//
EFI_STATUS
BBTestReceiveDataConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL            *StandardLib = NULL;
  EFI_STATUS                                    Status;
  EFI_STORAGE_SECURITY_COMMAND_PROTOCOL         *StorageSecurityCommand = NULL;
  EFI_STORAGE_SECURITY_COMMAND_PROTOCOL         *StorageSecurityTemp = NULL;
  EFI_BLOCK_IO_PROTOCOL                         *BlockIo = NULL;
  EFI_DEVICE_PATH_PROTOCOL                      *DevicePath = NULL;
  EFI_DEVICE_PATH_PROTOCOL                      *DevPathNode = NULL;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL              *DevicePathToText = NULL;
  EFI_STRING                                    DevicePathNodeStr = NULL;
  UINTN                                         Index;
  UINTN                                         NoHandles;
  EFI_HANDLE                                    *HandleBuffer = NULL;
  EFI_TEST_ASSERTION                            AssertionType;
  UINT8                                         *DataBuffer = NULL;
  UINTN                                         RcvDataSize;
  EFI_HANDLE                                    Handle = NULL; 
  BOOLEAN                                       IsAtaDevice = FALSE;

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

  StorageSecurityCommand = (EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *)ClientInterface;

  //
  // Locate Block IO protocol on same handler to get media info
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiStorageSecurityCommandProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  for (Index = 0; Index < NoHandles; Index++) {
     Status = gtBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gBlackBoxEfiStorageSecurityCommandProtocolGuid,
                      &StorageSecurityTemp
                      );
     if (Status == EFI_SUCCESS && StorageSecurityTemp == StorageSecurityCommand) {
       Status = gtBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gBlackBoxEfiBlockIoProtocolGuid,
                        &BlockIo
                        );
       Handle = HandleBuffer[Index];
       if (Status != EFI_SUCCESS) {
         StandardLib->RecordAssertion (
                        StandardLib,
                        EFI_TEST_ASSERTION_FAILED,
                        gTestGenericFailureGuid,
                        L"Can not Locate BlockIo Protocol on Current Handler",
                        L"%a:%d:",
                        __FILE__,
                        (UINTN)__LINE__
                        );
          goto EXIT;
      }
    }
 
  }


  //
  // both ATA8-ACS & SPC-4 security protocol payload are in 512 incremenet
  //
  DataBuffer = SctAllocateZeroPool (512);
  if (DataBuffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocateMemory - Allocate Memory Fail",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    goto EXIT;
  }
  
  if (BlockIo->Media->MediaPresent) {
    //
    // EFI_WARN_BUFFER_TOO_SMALL 
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &gEfiDevicePathProtocolGuid,
                     &DevicePath
                     );

    if (!EFI_ERROR(Status)) {
      Status = gtBS->LocateProtocol (
                       &gBlackBoxEfiDevicePathToTextProtocolGuid,
                       NULL,
                       &DevicePathToText
                       );
      if (!EFI_ERROR(Status)) {
        //
        // Search for Ata device Node in devicepath
        //
        DevPathNode = DevicePath;
        while (!SctIsDevicePathEnd(DevPathNode)) {
          DevicePathNodeStr = DevicePathToText->ConvertDeviceNodeToText (
                                                  DevPathNode,
                                                  FALSE,
                                                  FALSE
                                                  );
          if ((DevicePathNodeStr != NULL) && ((SctStrStr (DevicePathNodeStr, L"Ata(") != NULL) || (SctStrStr (DevicePathNodeStr, L"Sata(") != NULL))) {
            IsAtaDevice = TRUE;
            SctFreePool (DevicePathNodeStr);
            DevicePathNodeStr = NULL;
            break;
          }
          SctFreePool (DevicePathNodeStr);
          DevicePathNodeStr = NULL;

          DevPathNode = SctNextDevicePathNode(DevPathNode);
        }
      }
    }       

    //
    // According to TCG definition, when the Security Protocol field is set to 00h, and SP 
    // Specific is set to 0000h in a TRUSTED RECEIVE command, return security protocol
    // information. This Command is not associated with a security send command
    //
    Status = StorageSecurityCommand->ReceiveData (
                                       StorageSecurityCommand,
                                       BlockIo->Media->MediaId,
                                       100000000,                    // Timeout 10-sec
                                       0,                            // SecurityProtocol
                                       0,                            // SecurityProtocolSpecifcData
                                       10,                           // PayloadBufferSize,
                                       DataBuffer,                   // PayloadBuffer
                                       &RcvDataSize
                                       );
    //
    // for ATA8-ACS SecurityProtocol, 512 byte is a request
    //
    if (IsAtaDevice) {
      if((Status == EFI_DEVICE_ERROR) || (Status == EFI_WARN_BUFFER_TOO_SMALL)){
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if((!EFI_ERROR(Status)) || (Status == EFI_WARN_BUFFER_TOO_SMALL)){
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }

    if (IsAtaDevice) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gStorageSecurityCommandConformanceTestAssertionGuid001,
                     L"EFI_STORAGE_SECURITY_COMMAND.ReceiveData - TRUSTED RECEIVE to get Ata device basic information with limited data buffer",
                     L"%a:%d: Status: %r ExpectedStatus: %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EFI_DEVICE_ERROR
                     );
    } else {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gStorageSecurityCommandConformanceTestAssertionGuid001,
                     L"EFI_STORAGE_SECURITY_COMMAND.ReceiveData - TRUSTED RECEIVE to get Non-Ata device basic information with limited data buffer",
                     L"%a:%d: Status: %r ExpectedStatus: %r or %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EFI_WARN_BUFFER_TOO_SMALL,
                     EFI_SUCCESS
                     );
    }

    //
    // EFI_MEDIA_CHANGED
    //
    Status = StorageSecurityCommand->ReceiveData (
                                       StorageSecurityCommand,
                                       BlockIo->Media->MediaId + 1,
                                       100000000,                    // Timeout 10-sec
                                       0,                            // SecurityProtocol
                                       0,                            // SecurityProtocolSpecifcData
                                       512,                          // PayloadBufferSize,
                                       DataBuffer,                   // PayloadBuffer
                                       &RcvDataSize
                                       );
  
    if (Status == EFI_MEDIA_CHANGED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gStorageSecurityCommandConformanceTestAssertionGuid002,
                   L"EFI_STORAGE_SECURITY_COMMAND.ReceiveData - TRUSTED RECEIVE to get device basic information with invalid Media ID",
                   L"%a:%d: Status: %r ExpectedStatus: %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_MEDIA_CHANGED
                   );

    //
    // EFI_INVALID_PARAMETER
    //
    //
    // NULL PayloadBuffer
    // 
    Status = StorageSecurityCommand->ReceiveData (
                                       StorageSecurityCommand,
                                       BlockIo->Media->MediaId,
                                       100000000,                    // Timeout 10-sec
                                       0,                            // SecurityProtocol
                                       0,                            // SecurityProtocolSpecifcData
                                       512,                          // PayloadBufferSize,
                                       NULL,                         // PayloadBuffer
                                       &RcvDataSize
                                       );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gStorageSecurityCommandConformanceTestAssertionGuid003,
                   L"EFI_STORAGE_SECURITY_COMMAND.ReceiveData - TRUSTED RECEIVE to get device basic information with NULL Payload buffer",
                   L"%a:%d: Status: %r ExpectedStatus: %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER
                   );
    //
    // NULL PayloadTransferSize
    // 
    Status = StorageSecurityCommand->ReceiveData (
                                       StorageSecurityCommand,
                                       BlockIo->Media->MediaId,
                                       100000000,                    // Timeout 10-sec
                                       0,                            // SecurityProtocol
                                       0,                            // SecurityProtocolSpecifcData
                                       512,                          // PayloadBufferSize,
                                       DataBuffer,                   // PayloadBuffer
                                       NULL
                                       );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gStorageSecurityCommandConformanceTestAssertionGuid004,
                   L"EFI_STORAGE_SECURITY_COMMAND.ReceiveData - TRUSTED RECEIVE to get device basic information with NULL PayloadTransferSize",
                   L"%a:%d: Status: %r ExpectedStatus: %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER
                   );
    
  } else {
    //
    // EFI_NO_MEDIA
    // 
    Status = StorageSecurityCommand->ReceiveData (
                                       StorageSecurityCommand,
                                       BlockIo->Media->MediaId,
                                       100000000,                    // Timeout 10-sec
                                       0,                            // SecurityProtocol
                                       0,                            // SecurityProtocolSpecifcData
                                       512,                          // PayloadBufferSize,
                                       DataBuffer,                   // PayloadBuffer
                                       &RcvDataSize
                                       );
  
    if (Status == EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gStorageSecurityCommandConformanceTestAssertionGuid005,
                   L"EFI_STORAGE_SECURITY_COMMAND.ReceiveData - TRUSTED RECEIVE to get device basic information on a non-existing media",
                   L"%a:%d: Status: %r ExpectedStatus: %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_NO_MEDIA
                   );

  }

EXIT:  
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }
  
  if (DataBuffer != NULL) {
    gtBS->FreePool (DataBuffer);
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_STORAGE_SECURITY_COMMAND_PROTOCOL.SendData() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 
//
EFI_STATUS
BBTestSendDataConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{ 
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL            *StandardLib = NULL;
  EFI_STATUS                                    Status;
  EFI_STORAGE_SECURITY_COMMAND_PROTOCOL         *StorageSecurityCommand = NULL;
  EFI_STORAGE_SECURITY_COMMAND_PROTOCOL         *StorageSecurityTemp = NULL;
  EFI_BLOCK_IO_PROTOCOL                         *BlockIo = NULL;
  UINTN                                         Index;
  UINTN                                         NoHandles;
  EFI_HANDLE                                    *HandleBuffer = NULL;
  EFI_TEST_ASSERTION                            AssertionType;
  UINT8                                         *DataBuffer = NULL;
  UINTN                                         RcvDataSize;
  SUPPORTED_SECURITY_PROTOCOLS_PARAMETER_DATA   *Data = NULL; 
  UINTN                                         Len;
  BOOLEAN                                       TcgFlag = FALSE;
  BOOLEAN                                       IeeeFlag = FALSE;  


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

  StorageSecurityCommand = (EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *)ClientInterface;

  //
  // Locate Block IO protocol on same handler for test
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiStorageSecurityCommandProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  for (Index = 0; Index < NoHandles; Index++) {
     Status = gtBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gBlackBoxEfiStorageSecurityCommandProtocolGuid,
                      &StorageSecurityTemp
                      );
     if (Status == EFI_SUCCESS && StorageSecurityTemp == StorageSecurityCommand) {
       Status = gtBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gBlackBoxEfiBlockIoProtocolGuid,
                        &BlockIo
                        );
       if (Status != EFI_SUCCESS) {
         StandardLib->RecordAssertion (
                        StandardLib,
                        EFI_TEST_ASSERTION_FAILED,
                        gTestGenericFailureGuid,
                        L"Can not find BlockIo Protocol on Current Handler",
                        L"%a:%d:",
                        __FILE__,
                        (UINTN)__LINE__
                        );
         goto EXIT;
       }
       
    }
  }

  
  DataBuffer = SctAllocateZeroPool (512);
  if (DataBuffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocateMemory - Allocate Memory Fail",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    goto EXIT;
  }

  //
  // Get device capiblity 
  //
  Status = StorageSecurityCommand->ReceiveData (
                                     StorageSecurityCommand,
                                     BlockIo->Media->MediaId,
                                     100000000,                    // Timeout 10-sec
                                     0,                            // SecurityProtocol
                                     0,                            // SecurityProtocolSpecifcData
                                     512,                          // PayloadBufferSize,
                                     DataBuffer,                   // PayloadBuffer
                                     &RcvDataSize
                                     );
  
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }
  
  //
  // In returned data, the ListLength field indicates the total length, in bytes, 
  // of the supported security protocol list.
  //
  Data = (SUPPORTED_SECURITY_PROTOCOLS_PARAMETER_DATA*)DataBuffer;
  Len  = ROUNDUP512(sizeof (SUPPORTED_SECURITY_PROTOCOLS_PARAMETER_DATA) + \
                    (Data->SupportedSecurityListLength[0] << 8) +          \
                    (Data->SupportedSecurityListLength[1]));
  
  //
  // Free original buffer and allocate new buffer.
  //
  SctFreePool (DataBuffer);
  DataBuffer = NULL;
  DataBuffer = SctAllocateZeroPool (Len);
  if (DataBuffer == NULL) {
    StandardLib->RecordAssertion (
                    StandardLib,
                    EFI_TEST_ASSERTION_FAILED,
                    gTestGenericFailureGuid,
                    L"BS.AllocateMemory - Allocate Memory Fail",
                    L"%a:%d:",
                    __FILE__,
                    (UINTN)__LINE__
                    );
    goto EXIT;
  }
  
  //
  // Read full supported security protocol list from device.
  //
  Status = StorageSecurityCommand->ReceiveData (
                                     StorageSecurityCommand,
                                     BlockIo->Media->MediaId,
                                     100000000,                    // Timeout 10-sec
                                     0,                            // SecurityProtocol
                                     0,                            // SecurityProtocolSpecifcData
                                     Len,                          // PayloadBufferSize,
                                     DataBuffer,                   // PayloadBuffer
                                     &RcvDataSize
                                     );
  
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }
  
  Data = (SUPPORTED_SECURITY_PROTOCOLS_PARAMETER_DATA*)DataBuffer;
  Len  = (Data->SupportedSecurityListLength[0] << 8) + Data->SupportedSecurityListLength[1];

  //
  // Iterate full supported security protocol list to check if TCG or IEEE 1667 protocol
  // is supported.
  //
  for (Index = 0; Index < Len; Index++) {
    if (Data->SupportedSecurityProtocol[Index] == SECURITY_PROTOCOL_TCG) {
      //
      // Found a  TCG device.
      //
      TcgFlag = TRUE;
      DEBUG ((EFI_D_INFO, "This device is a TCG protocol device\n"));
      break;
    }

    if (Data->SupportedSecurityProtocol[Index] == SECURITY_PROTOCOL_IEEE1667) {
      //
      // Found a IEEE 1667 device.
      //
      IeeeFlag = TRUE;
      DEBUG ((EFI_D_INFO, "This device is a IEEE 1667 protocol device\n"));
      break;
    }    
  }


  //
  // Main test process 
  //
  if (TcgFlag) {
    if (BlockIo->Media->MediaPresent) {
      //
      // EFI_MEDIA_CHANGED
      //
      //
      // As long as TCG protocol is supported, send out a TPer Reset 
      // TCG command to the device via the TrustedSend command with a non-zero Transfer Length. 
      //
      Status = StorageSecurityCommand->SendData (
                                         StorageSecurityCommand,
                                         BlockIo->Media->MediaId + 1,
                                         100000000,                  // Timeout 10-sec
                                         SECURITY_PROTOCOL_TCG,      // SecurityProtocol
                                         0x0400,                     // SecurityProtocolSpecifcData
                                         Len,                        // PayloadBufferSize,
                                         DataBuffer                  // PayloadBuffer
                                         );
      if (Status == EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gStorageSecurityCommandConformanceTestAssertionGuid006,
                     L"EFI_STORAGE_SECURITY_COMMAND.SendData - TRUSTED SendData to send a command with invalid media ID",
                     L"%a:%d: Status: %r ExpectedStatus: %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EFI_MEDIA_CHANGED
                     );

      //
      // EFI_INVALID_PARAMETER
      //
      Status = StorageSecurityCommand->SendData (
                                         StorageSecurityCommand,
                                         BlockIo->Media->MediaId,
                                         100000000,                  // Timeout 10-sec
                                         SECURITY_PROTOCOL_TCG,      // SecurityProtocol
                                         0x0400,                     // SecurityProtocolSpecifcData
                                         Len,                        // PayloadBufferSize,
                                         NULL                        // PayloadBuffer
                                         );
      if (Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gStorageSecurityCommandConformanceTestAssertionGuid007,
                     L"EFI_STORAGE_SECURITY_COMMAND.SendData - TRUSTED SendData to send a command with null payload buffer",
                     L"%a:%d: Status: %r ExpectedStatus: %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EFI_INVALID_PARAMETER
                     );
    }else { 
      //
      // EFI_NO_MEDIA
      //
      //
      // As long as TCG protocol is supported, send out a TPer Reset 
      // TCG command to the device via the TrustedSend command with a non-zero Transfer Length. 
      //
      Status = StorageSecurityCommand->SendData (
                                         StorageSecurityCommand,
                                         BlockIo->Media->MediaId,
                                         100000000,                  // Timeout 10-sec
                                         SECURITY_PROTOCOL_TCG,      // SecurityProtocol
                                         0x0400,                     // SecurityProtocolSpecifcData
                                         Len,                        // PayloadBufferSize,
                                         DataBuffer                  // PayloadBuffer
                                         );
      if (Status == EFI_NO_MEDIA) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gStorageSecurityCommandConformanceTestAssertionGuid008,
                     L"EFI_STORAGE_SECURITY_COMMAND.SendData - TRUSTED SendData to send command to a device with no media",
                     L"%a:%d: Status: %r ExpectedStatus: %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EFI_NO_MEDIA
                     );

    }
  }
  
EXIT:
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  if (DataBuffer != NULL) {
    gtBS->FreePool (DataBuffer);
  }

  return EFI_SUCCESS;
}

