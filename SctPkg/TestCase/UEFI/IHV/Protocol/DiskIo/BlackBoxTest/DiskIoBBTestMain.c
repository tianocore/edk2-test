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

  DiskIoBBTestMain.c

Abstract:

  Test Driver of Disk I/O Protocol

--*/

#include "SctLib.h"
#include "DiskIoBBTestMain.h"

EFI_EVENT              TimerEvent;

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  DISK_IO_PROTOCOL_TEST_REVISION,
  IHV_DISK_IO_PROTOCOL_GUID,
  L"Disk I/O Protocol Test",
  L"UEFI Disk I/O Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    DISK_IO_PROTOCOL_READDISK_CONFORMANCE_AUTO_GUID,
    L"ReadDisk_Conf",
    L"Perform auto consistency checkes on the ReadDisk interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadDiskConformanceAutoTest
  },
  //
  // Function test section
  //
  {
    DISK_IO_PROTOCOL_READDISK_FUNCTION_AUTO_GUID,
    L"ReadDisk_Func",
    L"Invoke ReadDisk and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadDiskFunctionAutoTest
  },

  //
  // Combination test section
  //
#ifdef EFI_TEST_EXHAUSTIVE
  {
    DISK_IO_PROTOCOL_WRITEDISK_CONFORMANCE_AUTO_GUID,
    L"WriteDisk_Conf",
    L"Perform auto consistency checkes on the WriteDisk interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteDiskConformanceAutoTest
  },
  {
    DISK_IO_PROTOCOL_WRITEDISK_FUNCTION_AUTO_GUID,
    L"WriteDisk_Func",
    L"Invoke WriteDisk and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteDiskFunctionAutoTest
  },
  {
    DISK_IO_PROTOCOL_READDISK_STRESS_AUTO_GUID,
    L"ReadDisk_Stress",
    L"Perform stress test on ReadDisk",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadDiskStressAutoTest
  },
  {
    DISK_IO_PROTOCOL_WRITEDISK_STRESS_AUTO_GUID,
    L"WriteDisk_Stress",
    L"Perform stress test on WriteDisk",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteDiskStressAutoTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestDiskIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Disk I/O Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestDiskIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status;

  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);


  Status = gtBS->CreateEvent(EVT_TIMER, 0, NULL, NULL, &TimerEvent);
  ASSERT_EFI_ERROR(Status);

  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestDiskIoProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestDiskIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;
  Status = gtBS->CloseEvent(TimerEvent);
  ASSERT_EFI_ERROR(Status);

  Status = EfiUninstallAndFreeIHVBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

/**
 *  assistant function to verify two buffer
 *  @param  Buffer1 first buffer
 *  @param  Buffer2 second buffer
 *  @param  BufferSize size of the buffer
 *  @return Count of the different byte of two buffers
*/
UINTN
VerifyBuffer(
  IN UINT8           *Buffer1,
  IN UINT8           *Buffer2,
  IN UINTN           BufferSize
  )
{
  UINTN              Loop,Count;
  Count = 0;
  for (Loop = 0; Loop < BufferSize; Loop++) {
    if (Buffer1[Loop] != Buffer2[Loop]) {
      Count++;
    }
  }

  return Count;
}

/**
 *  assistant function to locate DevicePath Protocol from DiskIo Protocol
 *  @param  DiskIo protocol interface
 *  @param  BlockIo protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateBlockIoFromDiskIo(
  IN EFI_DISK_IO_PROTOCOL                 *DiskIo,
  IN EFI_BLOCK_IO_PROTOCOL                **BlockIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles,Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_DISK_IO_PROTOCOL                    *OtherDiskIo;

  //
  // Locate the Handle that the DiskIo interface is bound to
  //
  Status = gtBS->LocateHandleBuffer(
                   ByProtocol,
                   &gBlackBoxEfiDiskIoProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (NoHandles <= 0) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Device Error",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_DEVICE_ERROR;
  }

  //
  // Find the exact handle that DiskIo bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol(
                       HandleBuffer[Index],
                       &gBlackBoxEfiDiskIoProtocolGuid,
                       &OtherDiskIo
                       );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - HandleProtocol",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      if (HandleBuffer != NULL) {
        gtBS->FreePool (HandleBuffer);
      }
      return Status;
    }
    if (OtherDiskIo == DiskIo) {
      break;
    }
  }

  //
  // Locate the BlockIo Protocol bound to DiskIo Protocol
  //
  if (Index >= NoHandles) {
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }
    //
    // No Handle Found!!
    //
    return EFI_DEVICE_ERROR;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gBlackBoxEfiBlockIoProtocolGuid,
                   BlockIo
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - HandleProtocol",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }
    return Status;
  }

  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  return EFI_SUCCESS;
}


/**
 *  assistant function to locate DevicePath Protocol from DiskIo Protocol
 *  @param  DiskIo protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromDiskIo(
  IN EFI_DISK_IO_PROTOCOL                 *DiskIo,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles,Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_DISK_IO_PROTOCOL                    *OtherDiskIo;

  //
  // Locate the Handle that the DiskIo interface is bound to
  //
  Status = gtBS->LocateHandleBuffer(
                   ByProtocol,
                   &gBlackBoxEfiDiskIoProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (NoHandles <= 0) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Device Error",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_DEVICE_ERROR;
  }

  //
  // Find the exact handle that DiskIo bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol(
                       HandleBuffer[Index],
                       &gBlackBoxEfiDiskIoProtocolGuid,
                       &OtherDiskIo
                       );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - HandleProtocol",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      if (HandleBuffer != NULL) {
        gtBS->FreePool (HandleBuffer);
      }
      return Status;
      }
    if (OtherDiskIo == DiskIo) {
      break;
    }
  }

  //
  // Locate the DevicePath Protocol bound to DiskIo Protocol
  //
  if (Index >= NoHandles) {
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }
    //
    // No Handle Found!!
    //
    return EFI_DEVICE_ERROR;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gEfiDevicePathProtocolGuid,
                   DevicePath
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - HandleProtocol",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }
    return Status;
  }


  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  return EFI_SUCCESS;
}
