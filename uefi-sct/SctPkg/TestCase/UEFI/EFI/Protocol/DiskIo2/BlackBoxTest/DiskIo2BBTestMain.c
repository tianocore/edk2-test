/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DiskIo2BBTestMain.c

Abstract:

  Test Driver of Disk I/O2 Protocol

--*/

#include "DiskIo2BBTestMain.h"

EFI_EVENT              TimerEvent;

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  DISK_IO2_PROTOCOL_TEST_REVISION,
  EFI_DISK_IO2_PROTOCOL_GUID,
  L"Disk I/O2 Protocol Test",
  L"UEFI Disk I/O2 Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID///
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
	//
    // Conformance test section
	//
  {
    DISK_IO2_PROTOCOL_READDISKEX_CONFORMANCE_AUTO_GUID,
    L"ReadDiskEx_Conf",
    L"Perform auto consistency checkes on the ReadDiskEx interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadDiskExConformanceAutoTest
  },
  
  {
    DISK_IO2_PROTOCOL_FLUSHDISKEX_CONFORMANCE_AUTO_GUID,
    L"FlushDiskEx_Conf",
    L"Perform auto consistency checkes on the FulshDiskEx interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFlushDiskExConformanceAutoTest
  },

  //
  // Function test section
  //
  {
    DISK_IO2_PROTOCOL_CANCEL_FUNCTION_AUTO_GUID,
    L"Cancel_Func",
    L"Invoke Cancel and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCancelFunctionAutoTest
  },

  {
    DISK_IO2_PROTOCOL_READDISKEX_FUNCTION_AUTO_GUID,
    L"ReadDiskEx_Func",
    L"Invoke ReadDiskEx and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadDiskExFunctionAutoTest
  },
 
  {
	DISK_IO2_PROTOCOL_FLUSHDISKEX_FUNCTION_AUTO_GUID,
	L"FlushDiskEx_Func",
	L"Invoke FlushDiskEx and verify interface correctness within test case",
	EFI_TEST_LEVEL_DEFAULT,
	gSupportProtocolGuid1,
	EFI_TEST_CASE_AUTO,
	BBTestFlushDiskExFunctionAutoTest
  },

  {
    DISK_IO2_PROTOCOL_WRITEDISKEX_CONFORMANCE_AUTO_GUID,
    L"WriteDiskEx_Conf",
    L"Perform auto consistency checkes on the WriteDiskEx interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteDiskExConformanceAutoTest
  },
  {
    DISK_IO2_PROTOCOL_WRITEDISKEX_FUNCTION_AUTO_GUID,
    L"WriteDiskEx_Func",
    L"Invoke WriteDiskEx and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteDiskExFunctionAutoTest
  },
  
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestDiskIo2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

/**
 *  Disk I/O2 Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestDiskIo2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status;

  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);


  Status = gtBS->CreateEvent (EVT_TIMER, 0, (EFI_EVENT_NOTIFY) NULL, NULL, &TimerEvent);
  ASSERT_EFI_ERROR(Status);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestDiskIo2ProtocolUnload,
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
BBTestDiskIo2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;
  Status = gtBS->CloseEvent(TimerEvent);
  ASSERT_EFI_ERROR(Status);

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}


/**
 *  assistant function to locate DevicePath Protocol from DiskIo2 Protocol
 *  @param  DiskIo2 protocol interface
 *  @param  BlockIo2 protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/

EFI_STATUS
LocateBlockIo2FromDiskIo2(
  IN EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  IN EFI_BLOCK_IO2_PROTOCOL                **BlockIo2,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  )
{
  EFI_STATUS                               Status;

  UINTN                                    NoHandles,Index;
  EFI_HANDLE                               *HandleBuffer;
  EFI_DISK_IO2_PROTOCOL                    *OtherDiskIo2;

  //
  // Locate the Handle that the DiskIo2 interface is bound to
  //
  Status = gtBS->LocateHandleBuffer(
                   ByProtocol,
                   &gBlackBoxEfiDiskIo2ProtocolGuid,
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
  // Find the exact handle that DiskIo2 bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol(
                       HandleBuffer[Index],
                       &gBlackBoxEfiDiskIo2ProtocolGuid,
                       (VOID **) &OtherDiskIo2
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
    if (OtherDiskIo2 == DiskIo2) {
      break;
    }
  }

  //
  // Locate the BlockIo2 Protocol bound to DiskIo2 Protocol
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
                   &gBlackBoxEfiBlockIo2ProtocolGuid,
                   (VOID **) BlockIo2
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
 *  assistant function to locate DevicePath Protocol from DiskIo2 Protocol
 *  @param  DiskIo2 protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromDiskIo2(
  IN EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                               Status;

  UINTN                                    NoHandles,Index;
  EFI_HANDLE                               *HandleBuffer;
  EFI_DISK_IO2_PROTOCOL                    *OtherDiskIo2;

  //
  // Locate the Handle that the DiskIo2 interface is bound to
  //
  Status = gtBS->LocateHandleBuffer(
                   ByProtocol,
                   &gBlackBoxEfiDiskIo2ProtocolGuid,
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
  // Find the exact handle that DiskIo2 bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol(
                       HandleBuffer[Index],
                       &gBlackBoxEfiDiskIo2ProtocolGuid,
                       (VOID **) &OtherDiskIo2
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
    if (OtherDiskIo2 == DiskIo2) {
      break;
    }
  }

  //
  // Locate the DevicePath Protocol bound to DiskIo2 Protocol
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
                   (VOID **) DevicePath
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
