/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DiskIo2BBTestConformance.c

Abstract:

  Consistency Test Cases of Disk I/O2 Protocol

--*/


#include "DiskIo2BBTestMain.h"

STATIC BOOLEAN                         DiskIO2Finished;

STATIC
VOID
NotifyFunc (
  EFI_EVENT               Event,
  BOOLEAN                 *Finished
  )
{
  *Finished = TRUE;
  return ;
}


/**
 *  Entrypoint for EFI_DISK_IO2_PROTOCOL.ReadDiskEx() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//



EFI_STATUS
EFIAPI
BBTestReadDiskExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib=NULL;
  EFI_STATUS                            Status, StatusSync, StatusAsync;
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2=NULL;
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2=NULL;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT32                                MediaId;
  BOOLEAN                               RemovableMedia;
  BOOLEAN                               MediaPresent;
  BOOLEAN                               LogicalPartition;
  BOOLEAN                               ReadOnly;
  BOOLEAN                               WriteCaching;
  UINT32                                BlockSize;
  UINT32                                IoAlign;
  EFI_LBA                               LastBlock;
  UINT64                                LastOffset;
  UINTN                                 BufferSize;
  UINT8                                 *Buffer=NULL;
  UINTN                                 Index;
  UINT32                                NewMediaId;
  UINT64                                Offset;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath=NULL;
  CHAR16                                *DevicePathStr=NULL;
  EFI_DISK_IO2_TOKEN                    DiskIo2TokenSync;
  EFI_DISK_IO2_TOKEN                    DiskIo2TokenAsync;



  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
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

  DiskIo2 = (EFI_DISK_IO2_PROTOCOL *)ClientInterface;

  Status = LocateBlockIo2FromDiskIo2 (DiskIo2, &BlockIo2, StandardLib);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Locate Device path of the current DiskIo2 device
  // and save it into log for investigating
  //
  LocateDevicePathFromDiskIo2 (DiskIo2, &DevicePath, StandardLib);

  DevicePathStr = SctDevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
    DevicePathStr = NULL;
  }

  
  //
  // Initialize Disk IO2 ReadDiskEx token event
  //
  //
  // Sync Token Init
  //
  DiskIo2TokenSync.Event = NULL;
  DiskIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  //
  // Async Token Init
  //
  DiskIO2Finished = FALSE;
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) NotifyFunc,
                   &DiskIO2Finished,
                   &DiskIo2TokenAsync.Event
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat Read DiskEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    return Status;
  }
  DiskIo2TokenAsync.TransactionStatus = EFI_NOT_READY;

  //
  // Initialize variable
  //
  MediaId           = BlockIo2->Media->MediaId;
  RemovableMedia    = BlockIo2->Media->RemovableMedia;
  MediaPresent      = BlockIo2->Media->MediaPresent;
  LogicalPartition  = BlockIo2->Media->LogicalPartition;
  ReadOnly          = BlockIo2->Media->ReadOnly;
  WriteCaching      = BlockIo2->Media->WriteCaching;
  BlockSize         = BlockIo2->Media->BlockSize;
  IoAlign           = BlockIo2->Media->IoAlign;
  LastBlock         = BlockIo2->Media->LastBlock;



  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? \
                                MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = SctMultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = 1;
  }

  Buffer = NULL;

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->CloseEvent (DiskIo2TokenAsync.Event);

    return Status;
  }


  

  

  //
  // If the floppy is ejected without "map -r", after first readdiskex() or writediskex()
  // the DiskIo2 will be changed because of reinstall and the original DiskIo2 will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //

  //
  // Assertion Points 4.1.2.1
  // ReadDiskEx should not succeed to read from disk
  // When MedialId is not the id for the current media in the device  both in Sync & Async case
  //
  if (MediaPresent == TRUE) {
    for (Index = 0; Index < 5; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          NewMediaId = MediaId + 5;
          break;
        case 1:
          NewMediaId = MediaId + 1;
          break;
        case 2:
          NewMediaId = MediaId - 1;
          break;
        case 3:
          NewMediaId = MediaId - 5;
          break;
        case 4:
          NewMediaId = 0;
          break;
        default:
          NewMediaId = MediaId;
      }

      //
      // Verify test data
      //
      if (NewMediaId == MediaId) {
        continue;
      }

      //
      // Sync Call ReadDiskEx with false MediaID
      //
      StatusSync = DiskIo2->ReadDiskEx (
                         DiskIo2,
                         NewMediaId,
                         0,
                         &DiskIo2TokenSync,
                         BufferSize,
                         (VOID*)Buffer
                         );


      //
      // Async Call ReadDiskEx with false MediaID
      //
      StatusAsync = DiskIo2->ReadDiskEx (
                                DiskIo2,
                                NewMediaId,
                                0,
                                &DiskIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );
    
      if (StatusSync == EFI_MEDIA_CHANGED 
       && StatusAsync == EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
	  
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIo2ConformanceTestAssertionGuid001,
                     L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx -  Sync & Async Read disk with MediaId not being the id for the current media in the device",
                     L"%a:%d:Actual MediaID = %d, MediaID = %d, StatusSync=%r, StatusAsync=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     MediaId,
                     NewMediaId,
                     StatusSync,
                     StatusAsync
                     );
  
      if ((StatusSync == EFI_DEVICE_ERROR)|| (StatusAsync == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        gtBS->CloseEvent (DiskIo2TokenAsync.Event);
        return Status;
      }
    }
  }

  //
  // Assertion Point 4.1.2.2
  // ReadDiskEx should not succeed to read from device with invalid device addresses
  //
  if (MediaPresent == TRUE) {
    for (Index = 0; Index < 6; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          Offset = LastOffset + 1;
          break;
        case 1:
          Offset = LastOffset + 10;
          break;
        case 2:
          Offset = LastOffset - BufferSize + 1;
          break;
        case 3:
          Offset = LastOffset - BufferSize + 2;
          break;
        case 4:
          Offset = LastOffset - BufferSize + 3;
          break;
        case 5:
          Offset = LastOffset - BufferSize + 4;
          break;
        default:
          Offset = 0;
          break;
      }
  
      //
      // Verify test data
      //
      if (Offset + BufferSize <= LastOffset) {
        continue;
      }

      //
      // Sync Call ReadDiskEx with invalid Offset
      //
      StatusSync = DiskIo2->ReadDiskEx (
                         DiskIo2,
                         MediaId,
                         Offset,
                         &DiskIo2TokenSync,
                         BufferSize,
                         (VOID*)Buffer
                         );
  
      //
      // Async Call ReadDiskEx with invalid Offset
      //
      StatusAsync = DiskIo2->ReadDiskEx (
                                DiskIo2,
                                MediaId,
                                Offset,
                                &DiskIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );

  
      if ((StatusSync == EFI_INVALID_PARAMETER)&&(StatusAsync == EFI_INVALID_PARAMETER)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
	  
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIo2ConformanceTestAssertionGuid002,
                     L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Sync & Async Read disk with invalid Offset parameter",
                     L"%a:%d:BufferSize = %d, BlockSize = %d, Offset = 0x%lx, LastBlock = 0x%lx, StatusSync = %r,StatusAsync = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     BlockSize,
                     Offset,
                     LastBlock,
                     StatusSync,
                     StatusAsync
                     );

      if ((StatusSync == EFI_DEVICE_ERROR)|| (StatusAsync == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        gtBS->CloseEvent (DiskIo2TokenAsync.Event);
        return Status;
      }
    }
  }

  //
  // Assertion Point 4.1.2.3
  // ReadDiskEx should not succeed to read from device that with no media present in the device
  //
  if (MediaPresent == FALSE) {
    //
    // Sync Call ReadDiskEx with proper parameter
    //
    StatusSync = DiskIo2->ReadDiskEx (
                       DiskIo2,
                       MediaId,
                       0,
                       &DiskIo2TokenSync,
                       BufferSize,
                       (VOID*)Buffer
                       );
    //
    // Async Call ReadDiskEx with proper parameter
    //
    StatusAsync = DiskIo2->ReadDiskEx (
                             DiskIo2,
                             MediaId,
                             0,
                             &DiskIo2TokenAsync,
                             BufferSize,
                             (VOID*)Buffer
                             );




    if ((StatusSync == EFI_NO_MEDIA)&&(StatusAsync == EFI_NO_MEDIA)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
	
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDiskIo2ConformanceTestAssertionGuid003,
                   L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Sync & Async Read disk from device without media present in the device",
                   L"%a:%d:BufferSize = %d, StatusSync = %r ,StatusAsync = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   StatusSync,
                   StatusAsync
                   );
  }

  //
  // Close Disk IO2 ReadEx block Event
  //
  gtBS->CloseEvent (DiskIo2TokenAsync.Event);
  gtBS->FreePool (Buffer);

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_DISK_IO2_PROTOCOL.WriteDiskEx() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestWriteDiskExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib=NULL;
  EFI_STATUS                           Status,StatusSync,StatusAsync;
  EFI_DISK_IO2_PROTOCOL                *DiskIo2=NULL;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2=NULL;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               MediaId;
  BOOLEAN                              RemovableMedia;
  BOOLEAN                              MediaPresent;
  BOOLEAN                              LogicalPartition;
  BOOLEAN                              ReadOnly;
  BOOLEAN                              WriteCaching;
  UINT32                               BlockSize;
  UINT32                               IoAlign;
  EFI_LBA                              LastBlock;
  UINT64                               LastOffset;
  UINTN                                BufferSize;
  UINT8                                *Buffer=NULL;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath=NULL;
  CHAR16                               *DevicePathStr=NULL;
  UINTN                                Index;
  UINT32                               NewMediaId;
  UINT64                               Offset;
  EFI_DISK_IO2_TOKEN                   DiskIo2TokenSync;
  EFI_DISK_IO2_TOKEN                   DiskIo2TokenAsync;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
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

  DiskIo2 = (EFI_DISK_IO2_PROTOCOL *)ClientInterface;

  Status = LocateBlockIo2FromDiskIo2 (DiskIo2, &BlockIo2, StandardLib);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Locate Device path of the current DiskIo2 device
  // and save it into log for investigating
  //
  LocateDevicePathFromDiskIo2 (DiskIo2, &DevicePath, StandardLib);

  DevicePathStr = SctDevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
    DevicePathStr = NULL;
  }

  //
  // Initialize Disk IO2 WriteDiskEx token event
  //
  //
  // Sync Token Init
  //
  DiskIo2TokenSync.Event             = NULL;
  DiskIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  //
  // Async Token Init
  //
  DiskIO2Finished = FALSE;
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) NotifyFunc,
                   &DiskIO2Finished,
                   &DiskIo2TokenAsync.Event
                   );
  
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat Write DiskEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  DiskIo2TokenAsync.TransactionStatus = EFI_NOT_READY;

  //
  // Initialize variable
  //
  MediaId           = BlockIo2->Media->MediaId;
  RemovableMedia    = BlockIo2->Media->RemovableMedia;
  MediaPresent      = BlockIo2->Media->MediaPresent;
  LogicalPartition  = BlockIo2->Media->LogicalPartition;
  ReadOnly          = BlockIo2->Media->ReadOnly;
  WriteCaching      = BlockIo2->Media->WriteCaching;
  BlockSize         = BlockIo2->Media->BlockSize;
  IoAlign           = BlockIo2->Media->IoAlign;
  LastBlock         = BlockIo2->Media->LastBlock;

  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? \
                                MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = SctMultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = 1;
  }

  Buffer = NULL;



  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  

  //
  // If the floppy is ejected without "map -r", after first readdiskex() or writediskex()
  // the DiskIo2 will be changed because of reinstall and the original DiskIo2 will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //

  //
  // Assertion Points 4.2.2.1
  // WriteDiskEx should not succeed to write to disk
  // When MedialId is not the id for the current media in the device
  //
  if (MediaPresent == TRUE && ReadOnly == FALSE) {
    for (Index = 0; Index < 5; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          NewMediaId = MediaId + 5;
          break;
        case 1:
          NewMediaId = MediaId + 1;
          break;
        case 2:
          NewMediaId = MediaId - 1;
          break;
        case 3:
          NewMediaId = MediaId - 5;
          break;
        case 4:
          NewMediaId = 0;
          break;
        default:
          NewMediaId = MediaId;
      }

      //
      // Verify test data
      //
      if (NewMediaId == MediaId) {
        continue;
      }



      //
      // Sync Call WriteDiskEx with false MediaID
      //
      StatusSync = DiskIo2->WriteDiskEx (
                              DiskIo2,
                              NewMediaId,
                              0,
                              &DiskIo2TokenSync,
                              BufferSize,
                              (VOID*)Buffer
                              );
      //
      // Async Call WriteDiskEx with false MediaID
      //
      StatusAsync = DiskIo2->WriteDiskEx (
                               DiskIo2,
                               NewMediaId,
                               0,
                               &DiskIo2TokenAsync,
                               BufferSize,
                               (VOID*)Buffer
                               );

      if (StatusSync == EFI_MEDIA_CHANGED && StatusAsync == EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIo2ConformanceTestAssertionGuid004,
                     L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Sync & Async Write disk with MediaId not being the id for the current media in the device",
                     L"%a:%d:Actual MediaID = %d, MediaID = %d, StatusSync = %r,StatusSync = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     MediaId,
                     NewMediaId,
                     StatusSync,
                     StatusAsync
                     );
  
      if ((StatusSync == EFI_DEVICE_ERROR) || (StatusAsync == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        gtBS->CloseEvent (DiskIo2TokenAsync.Event);
        return Status;
      }
    }
  }

  //
  // Assertion Point 4.2.2.2
  // WriteDiskEx should not succeed to write to device with invalid device addresses
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    for (Index = 0; Index < 6; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          Offset = LastOffset + 1;
          break;
        case 1:
          Offset = LastOffset + 10;
          break;
        case 2:
          Offset = LastOffset - BufferSize + 1;
          break;
        case 3:
          Offset = LastOffset - BufferSize + 2;
          break;
        case 4:
          Offset = LastOffset - BufferSize + 3;
          break;
        case 5:
          Offset = LastOffset - BufferSize + 4;
          break;
        default:
          Offset = 0;
          break;
      }
  
      //
      // Verify test data
      //
      if (Offset + BufferSize <= LastOffset) {
        continue;
      }


      //
      // Sync Call WriteDiskEx with invalid Offset&BufferSize
      //
      StatusSync = DiskIo2->WriteDiskEx (
                               DiskIo2,
                               MediaId,
                               Offset,
                               &DiskIo2TokenSync,
                               BufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call WriteDiskEx with invalid Offset&BufferSize
      //
      StatusAsync = DiskIo2->WriteDiskEx (
                                DiskIo2,
                                MediaId,
                                Offset,
                                &DiskIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );

      if (StatusSync == EFI_INVALID_PARAMETER && StatusAsync == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIo2ConformanceTestAssertionGuid005,
                     L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Sync & Async Write disk with MediaId not being the id for the current media in the device",
                     L"%a:%d:BufferSize = %d, BlockSize = %d, Offset = 0x%lx, LastBlock = 0x%lx, StatusSync = %r,StatusAsync = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     BlockSize,
                     Offset,
                     LastBlock,
                     StatusSync,
                     StatusAsync
                     );
      if ( (StatusSync == EFI_DEVICE_ERROR) || (StatusAsync == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        gtBS->CloseEvent (DiskIo2TokenAsync.Event);
        return Status;
      }
    }
  }

  //
  // Assertion Point 4.2.2.3
  // WriteDiskEx should not succeed to write to a write-protected device
  //
  if ((MediaPresent == TRUE) && (ReadOnly == TRUE)) {
   
      //
      // Sync Call WriteDiskEx with proper parameter
      //
      StatusSync = DiskIo2->WriteDiskEx (
                              DiskIo2,
                              MediaId,
                              0,
                              &DiskIo2TokenSync,
                              BufferSize,
                              (VOID*)Buffer
                              );
      //                      
      // Async Call WriteDiskEx with proper parameter
      //
      StatusAsync = DiskIo2->WriteDiskEx (
                               DiskIo2,
                               MediaId,
                               0,
                               &DiskIo2TokenAsync,
                               BufferSize,
                               (VOID*)Buffer
                               );

      if (StatusSync == EFI_WRITE_PROTECTED && StatusAsync == EFI_WRITE_PROTECTED) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIo2ConformanceTestAssertionGuid006,
                     L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Sync & Async Write disk with MediaId not being the id for the current media in the device",
                     L"%a:%d:BufferSize=%d, StatusSync = %r,StatusAsync = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     StatusSync,
                     StatusAsync
                     );
  
      if ((StatusSync == EFI_DEVICE_ERROR) || (StatusAsync == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        gtBS->CloseEvent (DiskIo2TokenAsync.Event);
        return Status;
      }
    }

  
  //
  // Assertion Point 4.2.2.4
  // WriteDiskEx should not succeed to write to device that with no media present in the device
  //
  if (MediaPresent == FALSE)  {
    //
    // Sync Call WriteDiskEx with proper parameter
    //
    
    StatusSync = DiskIo2->WriteDiskEx (
                   DiskIo2,
                   MediaId,
                   0,
                   &DiskIo2TokenSync,
                   BufferSize,
                   (VOID*)Buffer
                   );
    //
    // Async Call WriteDiskEx with proper parameter
    //
    
    StatusAsync = DiskIo2->WriteDiskEx (
                    DiskIo2,
                    MediaId,
                    0,
                    &DiskIo2TokenAsync,
                    BufferSize,
                    (VOID*)Buffer
                    );

    if ((StatusSync == EFI_NO_MEDIA) && (StatusAsync == EFI_NO_MEDIA)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDiskIo2ConformanceTestAssertionGuid007,
                   L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx -Sync & Async Write disk to device without media present in the device",
                   L"%a:%d:BufferSize = %d, StatusSync = %r,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   StatusSync,
                   StatusAsync
                   );
    if ((StatusSync == EFI_DEVICE_ERROR) || (StatusAsync == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        gtBS->CloseEvent (DiskIo2TokenAsync.Event);
        return Status;
    }
  }
  
  //
  // Close Disk IO2 WriteEx block Event
  //
  gtBS->CloseEvent (DiskIo2TokenAsync.Event);

  gtBS->FreePool (Buffer);

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_DISK_IO2_PROTOCOL.FlushDiskEx() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.5
//
EFI_STATUS
EFIAPI
BBTestFlushDiskExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib=NULL;
  EFI_STATUS                           Status, StatusSync, StatusAsync;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2=NULL;
  EFI_DISK_IO2_PROTOCOL                *DiskIo2=NULL;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               MediaId;
  BOOLEAN                              RemovableMedia;
  BOOLEAN                              MediaPresent;
  BOOLEAN                              LogicalPartition;
  BOOLEAN                              ReadOnly;
  BOOLEAN                              WriteCaching;
  UINT32                               BlockSize;
  UINT32                               IoAlign;
  EFI_LBA                              LastBlock;

  EFI_DISK_IO2_TOKEN                   DiskIo2TokenSync;
  EFI_DISK_IO2_TOKEN                   DiskIo2TokenAsync;

  UINT64                               LastOffset;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath=NULL;
  CHAR16                               *DevicePathStr=NULL;
  UINTN                                Index;
  UINT32                               NewMediaId;
  UINT64                               Offset;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                    SupportHandle,
                    &gEfiStandardTestLibraryGuid,
                    (VOID **) &StandardLib
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
  
  DiskIo2 = (EFI_DISK_IO2_PROTOCOL *)ClientInterface;
     
  Status = LocateBlockIo2FromDiskIo2 (DiskIo2, &BlockIo2, StandardLib);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }
  
  //
  // Locate Device path of the current DiskIo2 device
  // and save it into log for investigating
  //
  LocateDevicePathFromDiskIo2 (DiskIo2, &DevicePath, StandardLib);
     
  DevicePathStr = SctDevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
    DevicePathStr = NULL;
  }
  
  //
  // Initialize Disk IO2 FlushDiskEx token event
  //
  //
  // Sync Token Init
  //
  DiskIo2TokenSync.Event = NULL;
  DiskIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  //
  // Async Token Init
  //
  DiskIO2Finished = FALSE;
  
  Status = gtBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  (EFI_EVENT_NOTIFY) NotifyFunc,
                  &DiskIO2Finished,
                  &DiskIo2TokenAsync.Event
                  );
  
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.CreateEvent - Creat Flush DiskEx Event",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
      return Status;
  }
  
  DiskIo2TokenAsync.TransactionStatus = EFI_NOT_READY;
     
  //
  // Initialize variable
  //
  MediaId          = BlockIo2->Media->MediaId;
  RemovableMedia   = BlockIo2->Media->RemovableMedia;
  MediaPresent     = BlockIo2->Media->MediaPresent;
  LogicalPartition = BlockIo2->Media->LogicalPartition;
  ReadOnly         = BlockIo2->Media->ReadOnly;
  WriteCaching     = BlockIo2->Media->WriteCaching;
  BlockSize        = BlockIo2->Media->BlockSize;
  IoAlign          = BlockIo2->Media->IoAlign;
  LastBlock        = BlockIo2->Media->LastBlock;
     
  LastOffset       = SctMultU64x32 (LastBlock+1, BlockSize);
     
  //
  // If the floppy is ejected without "map -r", after first readdiskex() or writediskex()
  // the DiskIo2 will be changed because of reinstall and the original DiskIo2 will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //
     
  //
  // Assertion Points 4.2.2.1
  // FlushDiskEx should not succeed to flush data to disk
  // When MedialId is not the id for the current media in the device
  //
  if ( (MediaPresent == TRUE) && (ReadOnly == FALSE) && (WriteCaching == TRUE)) {
    for (Index = 0; Index < 5; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          NewMediaId = MediaId + 5;
          break;
        case 1:
          NewMediaId = MediaId + 1;
          break;
        case 2:
          NewMediaId = MediaId - 1;
          break;
        case 3:
          NewMediaId = MediaId - 5;
          break;
      
        case 4:
          NewMediaId = 0;
          break;
        default:
          NewMediaId = MediaId;
      }
  
      //
      // Verify test data
      //
      if (NewMediaId == MediaId) {
        continue;
      }
            
            
            
      //
      // Sync Call FlushDiskEx with false MediaID
      //
      StatusSync = DiskIo2->FlushDiskEx (
                              DiskIo2,
                              NewMediaId,
                              0,
                              &DiskIo2TokenSync
                              );
      //
      // Async Call FlushDiskEx with false MediaID
      //
      StatusAsync = DiskIo2->FlushDiskEx (
                               DiskIo2,
                               NewMediaId,
                               0,
                               &DiskIo2TokenAsync
                               );
            
      if (StatusSync == EFI_MEDIA_CHANGED && StatusAsync == EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIo2ConformanceTestAssertionGuid008,
                     L"EFI_DISK_IO2_PROTOCOL.FlushDiskEx - Sync & Async Flush disk with MediaId not being the id for the current media in the device",
                     L"%a:%d:Actual MediaID = %d, MediaID = %d, StatusSync = %r,StatusAsync = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     MediaId,
                     NewMediaId,
                     StatusSync,
                     StatusAsync
                     );
      if ((StatusSync == EFI_DEVICE_ERROR) || (StatusAsync == EFI_DEVICE_ERROR)) {
        gtBS->CloseEvent (DiskIo2TokenAsync.Event);
        return Status;
      }
    }
  }
     
  //
  // Assertion Point 4.2.2.2
  // FlushDiskEx should not succeed to flush data to device with invalid device addresses
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (WriteCaching == TRUE)) {
    for (Index = 0; Index < 6; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          Offset = LastOffset + 1;
          break;
        case 1:
          Offset = LastOffset + 10;
          break;
        default:
          Offset = 0;
          break;
      }
    
      //
      // Verify test data
      //
      if (Offset <= LastOffset) {
        continue;
      }
  
  
      //
      // Sync Call FlushDiskEx with invalid Offset
      //
      StatusSync = DiskIo2->FlushDiskEx (
                              DiskIo2,
                              MediaId,
                              Offset,
                              &DiskIo2TokenSync
                              );
      //
      // Async Call FlushDiskEx with invalid Offset&BufferSize
      //
      StatusAsync = DiskIo2->FlushDiskEx (
                               DiskIo2,
                               MediaId,
                               Offset,
                               &DiskIo2TokenAsync  
                               );
            
      if (StatusSync == EFI_INVALID_PARAMETER && StatusAsync == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIo2ConformanceTestAssertionGuid009,
                     L"EFI_DISK_IO2_PROTOCOL.FlushDiskEx - Sync & Async Flush disk with MediaId not being the id for the current media in the device",
                     L"%a:%d:Offset = 0x%lx, StatusSync = %r,StatusSync = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Offset,
                     StatusSync,
                     StatusAsync
                     );
      if ((StatusSync == EFI_DEVICE_ERROR) || (StatusAsync == EFI_DEVICE_ERROR)) {
        gtBS->CloseEvent (DiskIo2TokenAsync.Event);
        return Status;
      }
    }
  }
       
  //
  // Assertion Point 4.2.2.3
  // FlushDiskEx should not succeed to flush to a write-protected device
  //
  if ((MediaPresent == TRUE) && (ReadOnly == TRUE) && (WriteCaching == TRUE)) {
   
    //
    // Sync Call FlushDiskEx with proper parameter
    //
    StatusSync = DiskIo2->FlushDiskEx (
                            DiskIo2,
                            MediaId,
                            0,
                            &DiskIo2TokenSync
                            );
    //
    // Async Call FlushDiskEx with proper parameter
    //
    StatusAsync = DiskIo2->FlushDiskEx (
                             DiskIo2,
                             MediaId,
                             0,
                             &DiskIo2TokenAsync
                             );
  
    if (StatusSync == EFI_WRITE_PROTECTED && StatusAsync == EFI_WRITE_PROTECTED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } 

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDiskIo2ConformanceTestAssertionGuid010,
                   L"EFI_DISK_IO2_PROTOCOL.FlushDiskEx - Sync & Async Flush disk with MediaId not being the id for the current media in the device",
                   L"%a:%d:StatusSync = %r,StatusSync = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   StatusSync,
                   StatusAsync
                   );
    if ((StatusSync == EFI_DEVICE_ERROR) || (StatusAsync == EFI_DEVICE_ERROR)) {
      gtBS->CloseEvent (DiskIo2TokenAsync.Event);
      return Status;
    }
  }

  //
  // Assertion Point 4.2.2.4
  // FlushDiskEx should not succeed to Flush to device that with no media present in the device
  //
  if (MediaPresent == FALSE) {
    //
    // Sync Call FlushDiskEx with proper parameter
    //
  
    StatusSync = DiskIo2->FlushDiskEx (
                            DiskIo2,
                            MediaId,
                            0,
                            &DiskIo2TokenSync
                            );
    //
    // Async Call FlushDiskEx with proper parameter
    //
  
    StatusAsync = DiskIo2->FlushDiskEx (
                            DiskIo2,
                            MediaId,
                            0,
                            &DiskIo2TokenAsync
                            );
	  
	if ((StatusSync == EFI_NO_MEDIA) && (StatusAsync == EFI_NO_MEDIA)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDiskIo2ConformanceTestAssertionGuid011,
                   L"EFI_DISK_IO2_PROTOCOL.FlushDiskEx -Sync & Async Flush disk to device without media present in the device",
                   L"%a:%d:StatusSync = %r,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   StatusSync,
                   StatusAsync
                   );
    if ( (StatusSync == EFI_DEVICE_ERROR) || (StatusAsync == EFI_DEVICE_ERROR)) {
      gtBS->CloseEvent (DiskIo2TokenAsync.Event);
      return Status;
    }
  }
  

  //
  // Close Disk IO2 FlushEx block Event
  //
  if (DiskIo2TokenAsync.Event != NULL) {
    gtBS->CloseEvent (DiskIo2TokenAsync.Event);
  }
  return EFI_SUCCESS;
} 
