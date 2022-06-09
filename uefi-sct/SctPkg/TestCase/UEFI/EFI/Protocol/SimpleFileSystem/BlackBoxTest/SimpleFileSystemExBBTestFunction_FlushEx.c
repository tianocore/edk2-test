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
    SimpleFileSystemExTestFunction_FlushEx.c

Abstract:
    for EFI Simple File System Protocol and EFI_FILE Protocol's Function Test

--*/


#define EFI_FILE_HANDLE_REVISION 0x00020000

#include "SimpleFileSystemBBTest.h"

//
//
//
typedef struct {
  UINTN                 Signature;
  EFI_FILE              *FileIo;
  EFI_FILE_IO_TOKEN     FileIoToken;
  EFI_TPL               Tpl;
  SCT_LIST_ENTRY        ListEntry;     
  EFI_STATUS            StatusAsync;
  EFI_TEST_ASSERTION    AssertionType;
} FileIoFlush_Task;

//
//CheckPoints
//
EFI_STATUS
EFIAPI
BBTestFlushExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestFlushExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestFlushExBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestFlushExBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
InternalGetInfoFileIo2 (
  EFI_FILE             *FileHandle,
  VOID                 **InfoBuffer,
  UINTN                *BufferSize,
  EFI_GUID             *InfoId
  );

EFI_STATUS
InternalSetFileSizeFileIo2 (
  EFI_FILE             *FileHandle,
  UINT64               FileSize
  );

//
// Async Flush File Queue
//
SCT_LIST_ENTRY  AsyncFlushFileExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncFlushFileExecuteListHead);
SCT_LIST_ENTRY  AsyncFlushFileFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncFlushFileFinishListHead);
SCT_LIST_ENTRY  AsyncFlushFileFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncFlushFileFailListHead);

//
// Async Flush File lock
//
SCT_LOCK  gAsyncFlushFileQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);


//
// Async Flush Dir Queue
//
SCT_LIST_ENTRY  AsyncFlushDirExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncFlushDirExecuteListHead);
SCT_LIST_ENTRY  AsyncFlushDirFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncFlushDirFinishListHead);
SCT_LIST_ENTRY  AsyncFlushDirFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncFlushDirFailListHead);

//
// Async Flush Dir lock
//
SCT_LOCK  gAsyncFlushDirQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);



//
//Async Flush File NotifyFunc
//
VOID
EFIAPI FileIoFlushFileNotifyFunc (
  IN  EFI_EVENT    Event,
  IN  VOID         *Context
  )
{
  FileIoFlush_Task    *FileIoEntity;
  
  FileIoEntity = (FileIoFlush_Task *)Context;

  //
  // Remove entity from FlushFileExecuteListHead &  add entity to FlushFileFinishListHead
  // All FileIoFlushFile Notify function run at Call Back level only once, So no locks required
  //
  SctAcquireLock (&gAsyncFlushFileQueueLock);
  SctRemoveEntryList(&FileIoEntity->ListEntry);
  SctInsertTailList(&AsyncFlushFileFinishListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncFlushFileQueueLock);
}


/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.FlushEx() function abstraction interface
 *  @param FileIo  a pointer to File Io to be tested.
 *  @param Tpl the Tpl level
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncFlushFileData (
  IN EFI_FILE             *FileIo,
  IN EFI_TPL              Tpl
)
{

  EFI_STATUS          Status;
  FileIoFlush_Task    *FileIoEntity;
  EFI_TPL             OldTpl;

  ASSERT(FileIo != NULL);

  FileIoEntity = NULL;
  
  //
  // Allocate memory for one FileIoFlushFileEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoFlush_Task), 
                   (VOID **) &FileIoEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   FileIoFlushFileNotifyFunc,
                   FileIoEntity,
                   &FileIoEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(FileIoEntity);
    return Status;
  }

  FileIoEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoEntity->FileIo                 = FileIo;
  FileIoEntity->Tpl                    = Tpl;
  FileIoEntity->FileIoToken.Status     = EFI_NOT_READY;

  SctAcquireLock (&gAsyncFlushFileQueueLock);
  SctInsertTailList(&AsyncFlushFileExecuteListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncFlushFileQueueLock);
  
  //
  // Async FlushEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  Status = FileIo->FlushEx (
                     FileIoEntity->FileIo,
                     &FileIoEntity->FileIoToken
                     );
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    SctAcquireLock (&gAsyncFlushFileQueueLock);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctInsertTailList(&AsyncFlushFileFailListHead, &FileIoEntity->ListEntry);    
    SctReleaseLock (&gAsyncFlushFileQueueLock);
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return Status;
}

//
//Async Flush Dir NotifyFunc
//
VOID
EFIAPI FileIoFlushDirNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIoFlush_Task    *FileIoEntity;
  
  FileIoEntity = (FileIoFlush_Task *)Context;

  //
  // Remove entity from FlushDirExecuteListHead &  add entity to FlushDirFinishListHead
  // All FileIoFlushDir Notify function run at Call Back level only once, So no locks required
  //
  SctAcquireLock (&gAsyncFlushDirQueueLock);
  SctRemoveEntryList(&FileIoEntity->ListEntry);
  SctInsertTailList(&AsyncFlushDirFinishListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncFlushDirQueueLock);
}


/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.FlushEx() function abstraction interface
 *  @param FileIo  a pointer to File Io to be tested.
 *  @param Buffer a pointer to Write data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncFlushDirData (
  IN EFI_FILE                          *FileIo,
  IN EFI_TPL                           Tpl
)
{

  EFI_STATUS                         Status;
  FileIoFlush_Task                   *FileIoEntity = NULL;
  EFI_TPL                            OldTpl;

  ASSERT(FileIo != NULL);
  
  //
  // Allocate memory for one FileIoFlushDirEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoFlush_Task), 
                   (VOID **) &FileIoEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   FileIoFlushDirNotifyFunc,
                   FileIoEntity,
                   &FileIoEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(FileIoEntity);
    FileIoEntity = NULL;
    return Status;
  }

  FileIoEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoEntity->FileIo                 = FileIo;
  FileIoEntity->Tpl                    = Tpl;
  FileIoEntity->FileIoToken.Status     = EFI_NOT_READY;

  SctAcquireLock (&gAsyncFlushDirQueueLock);
  SctInsertTailList(&AsyncFlushDirExecuteListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncFlushDirQueueLock);
  
  //
  // Async FlushEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  Status = FileIo->FlushEx (
                     FileIoEntity->FileIo,
                     &FileIoEntity->FileIoToken
                     );
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    SctAcquireLock (&gAsyncFlushDirQueueLock);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctInsertTailList(&AsyncFlushDirFailListHead, &FileIoEntity->ListEntry);    
    SctReleaseLock (&gAsyncFlushDirQueueLock);
    FileIoEntity->StatusAsync        = Status;
    return Status;
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return Status;
}



/**
 *  @brief For FlushEx() basic test
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.15
//
EFI_STATUS
EFIAPI
BBTestFlushExBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem;

  //
  // init
  //
  SimpleFileSystem = (EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 5.1.15.2.1  Async FlushEx() a normal file.
  //
  BBTestFlushExBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.1.15.2.2  Sync FlushEx() a normal file.
  //
  BBTestFlushExBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);
  


  //
  // 5.1.15.2.3  Async FlushEx() a directory.
  //
  BBTestFlushExBasicTestCheckpoint3 (StandardLib, SimpleFileSystem);

  //
  // 5.1.15.2.4  Sync FlushEx() a directory.
  //
  BBTestFlushExBasicTestCheckpoint4 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestFlushExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS           Status;
  EFI_FILE             *Root;
  UINTN                TplIndex;
  CHAR16               FileName[100];
  EFI_FILE             *FileHandle;
  UINT8                *Buffer;
  UINTN                BufferSize;
  UINTN                IndexI;
  UINTN                WaitIndex;
  SCT_LIST_ENTRY       *ListEntry;
  FileIoFlush_Task     *FileIoEntity;

  Root         = NULL;
  FileHandle   = NULL;
  Buffer       = NULL;
  ListEntry    = NULL;
  FileIoEntity = NULL;

  //
  // init
  //
  SctStrCpy (FileName, L"BBTestFlushExBasicTestCheckpoint1_File");

  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"OpenVolume fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  if (Root->Revision != EFI_FILE_PROTOCOL_REVISION2) {
    Root->Close(Root);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Async File IO is not supported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // allocate buffer for write
  //
  BufferSize = 200;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
    return Status;
  }

  //
  // create the file
  //
  Status = Root->Open (Root, &FileHandle, FileName, CREATE_FILE_MODE, 0);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool(Buffer);
    Root->Close(Root);    
    return Status;
  }

  //
  // set the Buffer content 
  //
  gtBS->SetMem (Buffer, BufferSize, 0x31);

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
 
    //
    // reset file size
    //
    Status = InternalSetFileSizeFileIo2 (FileHandle, 0);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file position fail",
                     L"%a:%d: Status - %r, filesize - 0",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
    //
    // write data to the file
    //
    BufferSize = 200;
    Status = FileHandle->Write (FileHandle, &BufferSize, Buffer);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Write to file fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
  
    Status = FileIoAsyncFlushFileData(
               FileHandle,
               TplArray[TplIndex]
               );
  }
    
  
  SctPrint (L" ================== Async FlushEx call finshed ================== \n\n");
  
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  SctPrint (L"Wait maximumly 120s for all Async Write events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
    
  SctAcquireLock (&gAsyncFlushFileQueueLock);
  while (!SctIsListEmpty(&AsyncFlushFileExecuteListHead) && IndexI < 120) {
    SctReleaseLock (&gAsyncFlushFileQueueLock);
    
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    SctPrint (L".");
    SctAcquireLock (&gAsyncFlushFileQueueLock);
  }
  SctReleaseLock (&gAsyncFlushFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  SctPrint (L"\n");

  //
  // clear all File IO events from gFlushFileFinishQueue 
  // Here no logs should be wrote to this file device to keep data intact
  //
  SctAcquireLock (&gAsyncFlushFileQueueLock);
    if (!SctIsListEmpty(&AsyncFlushFileFinishListHead)) {
      for(ListEntry = SctGetFirstNode(&AsyncFlushFileFinishListHead); ; ListEntry = SctGetNextNode(&AsyncFlushFileFinishListHead, ListEntry)) {
        FileIoEntity = CR(ListEntry, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
        SctReleaseLock (&gAsyncFlushFileQueueLock);

        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        //
        // Check & record every File Io execution entity status 
        //
        if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
            && FileIoEntity->StatusAsync == EFI_SUCCESS) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
        SctAcquireLock (&gAsyncFlushFileQueueLock);
        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&AsyncFlushFileFinishListHead, ListEntry)) {
           break;
        } 

      }
    }
  SctReleaseLock (&gAsyncFlushFileQueueLock);
    
  //
  // Record All Finished Flush case results
  //
  SctAcquireLock (&gAsyncFlushFileQueueLock);
  while (!SctIsListEmpty(&AsyncFlushFileFinishListHead)) {
    FileIoEntity = CR(AsyncFlushFileFinishListHead.ForwardLink, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctReleaseLock (&gAsyncFlushFileQueueLock);

    FileHandle = FileIoEntity->FileIo;

    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid017,
                   L"FlushEx() Basic Test - checkpoint1----Async",
                   L"%a:%d: Tpl - %d,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
      
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    SctAcquireLock (&gAsyncFlushFileQueueLock);
  }
  SctReleaseLock (&gAsyncFlushFileQueueLock);

  //
  // If FlushFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  SctAcquireLock (&gAsyncFlushFileQueueLock);
  while(!SctIsListEmpty(&AsyncFlushFileFailListHead)) {
    FileIoEntity = CR(AsyncFlushFileFailListHead.ForwardLink, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctReleaseLock (&gAsyncFlushFileQueueLock);

    FileHandle = FileIoEntity->FileIo;

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid018,
                   L"FlushEx() Basic Test - checkpoint1---Async",
                   L"%a:%d:Tpl - %d,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);     

     gtBS->FreePool(FileIoEntity);
     SctAcquireLock (&gAsyncFlushFileQueueLock);
  }
  SctReleaseLock (&gAsyncFlushFileQueueLock);
    
  //
  // If FlushFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  SctAcquireLock (&gAsyncFlushFileQueueLock);
  if (!SctIsListEmpty(&AsyncFlushFileExecuteListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncFlushFileExecuteListHead); ; ListEntry = SctGetNextNode(&AsyncFlushFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncFlushFileQueueLock);


      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid019,
                     L"FlushEx() Basic Test - checkpoint1----Async",
                     L"%a:%d:Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl
                     );

      SctAcquireLock (&gAsyncFlushFileQueueLock);
      if (SctIsNodeAtEnd(&AsyncFlushFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  SctReleaseLock (&gAsyncFlushFileQueueLock);

  FileHandle->Delete(FileHandle);
  FileHandle = NULL;
  gtBS->FreePool(Buffer);
  Root->Close(Root);  
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
BBTestFlushExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  UINT8                     *Buffer;
  UINTN                     BufferSize;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;

  Root       = NULL;
  FileHandle = NULL;
  Buffer     = NULL;
  //
  // init
  //
  SctStrCpy (FileName, L"BBTestFlushExBasicTestCheckpoint2_File");
  
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;
  
  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"OpenVolume fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  if (Root->Revision != EFI_FILE_PROTOCOL_REVISION2) {
    Root->Close(Root);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Async File IO is not supported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }


  //
  // allocate buffer for write
  //
  BufferSize = 200;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
	return Status;
  }	

  //
  // set the Buffer content 
  //
  gtBS->SetMem (Buffer, BufferSize, 0x31);  

  //
  // create the file
  //
  Status = Root->Open (Root, &FileHandle, FileName, CREATE_FILE_MODE, 0);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer);
    Root->Close(Root);   
    return Status;
  }


  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
 
    //
    // reset file size
    //
    Status = InternalSetFileSizeFileIo2 (FileHandle, 0);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file position fail",
                     L"%a:%d: Status - %r, filesize - 0",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
    //
    // write data to the file
    //
    BufferSize = 200;
    Status = FileHandle->Write (FileHandle, &BufferSize, Buffer);

    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Write to file fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
    
    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = FileHandle->FlushEx(
               FileHandle,
               &FileIoTokenSync
               );
    gtBS->RestoreTPL (OldTpl);
    
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    //
    // Check & record every File Io execution entity status 
    //
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } 
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid020,
                   L"FlushEx() Basic Test - checkpoint2----Sync",
                   L"%a:%d: Tpl - %d,Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[TplIndex],
                   Status
                   );  
  }
  
  FileHandle->Delete(FileHandle);
  FileHandle = NULL;
  gtBS->FreePool(Buffer);
  Root->Close(Root); 

  return Status;
}
  
  
EFI_STATUS
EFIAPI
BBTestFlushExBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    DirName[100];
  CHAR16                    FileName[TPL_ARRAY_SIZE][100];
  EFI_FILE                  *DirHandle;
  EFI_FILE                  *FileHandle[TPL_ARRAY_SIZE];
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  SCT_LIST_ENTRY            *ListEntry;
  FileIoFlush_Task          *FileIoEntity;

  Root          = NULL;
  DirHandle     = NULL;
  FileHandle[0] = NULL;
  FileHandle[1] = NULL;
  ListEntry     = NULL;
  FileIoEntity  = NULL;
  //
  // init
  //
  SctStrCpy (DirName, L"BBTestFlushExBasicTestCheckpoint3_Dir");
  SctStrCpy (FileName[0], L"BBTestFlushExBasicTestCheckpoint3_File_0");
  SctStrCpy (FileName[1], L"BBTestFlushExBasicTestCheckpoint3_File_1");

  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"OpenVolume fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

    
  if (Root->Revision != EFI_FILE_PROTOCOL_REVISION2) {
    Root->Close(Root);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Async File IO is not supported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }
  
  //
  // create the Dir
  //
  Status = Root->Open (Root, &DirHandle, DirName, CREATE_FILE_MODE, EFI_FILE_DIRECTORY);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create dir fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
    return Status;
  }

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
    //
    // create the file
    //
    Status = Root->Open (DirHandle, &FileHandle[TplIndex], FileName[TplIndex], CREATE_FILE_MODE, 0);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Create file fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
   
    Status = FileIoAsyncFlushDirData(
               DirHandle,
               TplArray[TplIndex]
               );
    
  }
    
  SctPrint (L" ================== Async FlushEx call finshed ================== \n\n");

  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  SctPrint (L"Wait maximumly 120s for all Async Write events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
    
  SctAcquireLock (&gAsyncFlushDirQueueLock);
  while (!SctIsListEmpty(&AsyncFlushDirExecuteListHead) && IndexI < 120) {
    SctReleaseLock (&gAsyncFlushDirQueueLock);
    
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    SctPrint (L".");
    SctAcquireLock (&gAsyncFlushDirQueueLock);
  }
  SctReleaseLock (&gAsyncFlushDirQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  SctPrint (L"\n");
 
  //
  // clear all File IO events from gFlushDirFinishQueue 
  // Here no logs should be wrote to this file device to keep data intact
  //
  SctAcquireLock (&gAsyncFlushDirQueueLock);
    if (!SctIsListEmpty(&AsyncFlushDirFinishListHead)) {
      for(ListEntry = SctGetFirstNode(&AsyncFlushDirFinishListHead); ; ListEntry = SctGetNextNode(&AsyncFlushDirFinishListHead, ListEntry)) {
        FileIoEntity = CR(ListEntry, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
        SctReleaseLock (&gAsyncFlushDirQueueLock);

        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        //
        // Check & record every File Io execution entity status 
        //
        if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
            && FileIoEntity->StatusAsync == EFI_SUCCESS) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
        SctAcquireLock (&gAsyncFlushDirQueueLock);
        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&AsyncFlushDirFinishListHead, ListEntry)) {
          break;
        } 
      }
    }
  SctReleaseLock (&gAsyncFlushDirQueueLock);
    
  //
  // Record All Finished Flush case results
  //
  SctAcquireLock (&gAsyncFlushDirQueueLock);
  while (!SctIsListEmpty(&AsyncFlushDirFinishListHead)) {
    FileIoEntity = CR(AsyncFlushDirFinishListHead.ForwardLink, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctReleaseLock (&gAsyncFlushDirQueueLock);
	
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid021,
                   L"FlushEx() Basic Test - checkpoint3----Async",
                   L"%a:%d: Tpl - %d,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
      
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    
    gtBS->FreePool(FileIoEntity);
    SctAcquireLock (&gAsyncFlushDirQueueLock);
  }
  SctReleaseLock (&gAsyncFlushDirQueueLock);
  

  //
  // If FlushDirFailListHead is not empty, which means some Async Calls are wrong 
  //
  SctAcquireLock (&gAsyncFlushDirQueueLock);
  while(!SctIsListEmpty(&AsyncFlushDirFailListHead)) {
    FileIoEntity = CR(AsyncFlushDirFailListHead.ForwardLink, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctReleaseLock (&gAsyncFlushDirQueueLock);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid022,
                   L"FlushEx() Basic Test - checkpoint3---Async",
                   L"%a:%d:Tpl - %d,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
   
     gtBS->FreePool(FileIoEntity);
       
     SctAcquireLock (&gAsyncFlushDirQueueLock);
  }
  SctReleaseLock (&gAsyncFlushDirQueueLock);
    
  //
  // If FlushDirExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  SctAcquireLock (&gAsyncFlushDirQueueLock);
  if (!SctIsListEmpty(&AsyncFlushDirExecuteListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncFlushDirExecuteListHead); ; ListEntry = SctGetNextNode(&AsyncFlushDirExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncFlushDirQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid023,
                     L"FlushEx() Basic Test - checkpoint3----Async",
                     L"%a:%d:Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl
                     );

      SctAcquireLock (&gAsyncFlushDirQueueLock);
      if (SctIsNodeAtEnd(&AsyncFlushDirExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  SctReleaseLock (&gAsyncFlushDirQueueLock);

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
  	if (FileHandle[TplIndex] != NULL)
      FileHandle[TplIndex]->Delete(FileHandle[TplIndex]);
    FileHandle[TplIndex] = NULL;
  }
  
  if (DirHandle != NULL)
  	DirHandle->Delete(DirHandle);
  
  Root->Close(Root);    
  return EFI_SUCCESS;
}




EFI_STATUS
EFIAPI
BBTestFlushExBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    DirName[100];
  CHAR16                    FileName[100];
  EFI_FILE                  *DirHandle;
  EFI_FILE                  *FileHandle;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;

  Root       = NULL;
  DirHandle  = NULL;
  FileHandle = NULL;
  
  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"OpenVolume fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  if (Root->Revision != EFI_FILE_PROTOCOL_REVISION2) {
    Root->Close(Root);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Async File IO is not supported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }
  //
  // init
  //
  SctStrCpy (DirName, L"BBTestFlushExBasicTestCheckpoint4_Dir");
  SctStrCpy (FileName, L"BBTestFlushExBasicTestCheckpoint4_File");
  
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  //
  // create the Dir
  //
  Status = Root->Open (Root, &DirHandle, DirName, CREATE_FILE_MODE, EFI_FILE_DIRECTORY);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create dir fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);

    return Status;
  }

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
    //
    // create the file
    //
    Status = Root->Open (Root, &FileHandle, FileName, CREATE_FILE_MODE, 0);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Create file fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      if (DirHandle != NULL){
         DirHandle->Delete(DirHandle);
         DirHandle = NULL;
      }
      
      Root->Close(Root);

      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = DirHandle->FlushEx(
               DirHandle,
               &FileIoTokenSync
               );
    gtBS->RestoreTPL (OldTpl);
    
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    //
    // Check & record every File Io execution entity status 
    //
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } 
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid024,
                   L"FlushEx() Basic Test - checkpoint4----Sync",
                   L"%a:%d: Tpl - %d,Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[TplIndex],
                   Status
                   ); 
  
    if (FileHandle != NULL){
      FileHandle->Delete(FileHandle);
      FileHandle = NULL;
    }   
  }
  
  if (DirHandle != NULL){
    DirHandle->Delete(DirHandle);
    DirHandle = NULL;
  }

  Root->Close(Root);

  return Status;
}


