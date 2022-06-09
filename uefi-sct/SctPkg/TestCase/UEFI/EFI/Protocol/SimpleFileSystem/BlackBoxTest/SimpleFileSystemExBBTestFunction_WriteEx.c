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
    SimpleFileSystemExTestFunction_WriteEx.c

Abstract:
    For EFI Simple File System Protocol and EFI_FILE Protocol's Function Test

--*/


#define EFI_FILE_HANDLE_REVISION 0x00020000

#include "SimpleFileSystemBBTest.h"

//
//
//
typedef struct {
  UINTN                             Signature;
  EFI_FILE                          *FileIo;
  EFI_FILE_IO_TOKEN               	FileIoToken;
  EFI_TPL                           Tpl;
  UINT64                            SetPosition;
  UINT64                            PositionAfterWrite;
  UINTN                             WriteLength;
  SCT_LIST_ENTRY                    ListEntry;     
  EFI_STATUS                        StatusAsync;
  EFI_TEST_ASSERTION                AssertionType;
} FileIoWrite_Task;

EFI_STATUS
InternalGetInfoFileIo2 (
  EFI_FILE               *FileHandle,
  VOID                   **InfoBuffer,
  UINTN                  *BufferSize,
  EFI_GUID               *InfoId
  );

EFI_STATUS
InternalSetFileSizeFileIo2 (
  EFI_FILE               *FileHandle,
  UINT64                 FileSize
  );


//
//CheckPoint 
//

EFI_STATUS
EFIAPI
BBTestWriteExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestWriteExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestWriteExBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestWriteExBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// Async Write File Queue
//
SCT_LIST_ENTRY  AsyncWriteExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteExecuteListHead);
SCT_LIST_ENTRY  AsyncWriteFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteFinishListHead);
SCT_LIST_ENTRY  AsyncWriteFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteFailListHead);

//
// Async Write File lock
//
SCT_LOCK  gAsyncWriteQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);

//
// Async Write Multi Files Queue
//
SCT_LIST_ENTRY  AsyncWriteMultiExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteMultiExecuteListHead);
SCT_LIST_ENTRY  AsyncWriteMultiFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteMultiFinishListHead);
SCT_LIST_ENTRY  AsyncWriteMultiFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteMultiFailListHead);

//
// Async Write Multi Files lock
//
SCT_LOCK  gAsyncWriteMultiQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);


//
//Async Write One File NotifyFunc
//
EFI_STATUS
EFIAPI FileIoWriteOneFileNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIoWrite_Task    *FileIoEntity;
  EFI_STATUS          Status;
  
  FileIoEntity = (FileIoWrite_Task *)Context;
  //
  // returned BufferSize equals ReadLength
  //
  Status = FileIoEntity->FileIo->GetPosition (
                                   FileIoEntity->FileIo,
                                   &FileIoEntity->PositionAfterWrite
                                   );
  
  if (EFI_ERROR (Status)) {
    return Status;
  } 

  //
  // Remove entity from WriteExecuteListHead &  add entity to WriteFinishListHead
  // All FileIoWriteOneFile Notify function run at Call Back level only once, So no locks required
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  SctRemoveEntryList(&FileIoEntity->ListEntry);
  SctInsertTailList(&AsyncWriteFinishListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncWriteQueueLock);

  return EFI_SUCCESS;
}

/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.WriteEx() function abstraction interface
 *  @param FileIo  a pointer to File Io to be tested.
 *  @param Tpl the Tpl level
 *  @param SetPosition the Starting Position to write.
 *  @param WriteLength the Write length.
 *  @param Buffer a pointer to Write data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncWriteOneFile(
  IN EFI_FILE                          *FileIo,
  IN EFI_TPL                           Tpl,
  IN UINT64                            SetPosition,
  IN UINTN                             WriteLength,
  OUT UINT8                            *Buffer
)
{

  EFI_STATUS                         Status;
  FileIoWrite_Task                   *FileIoEntity = NULL;
  EFI_TPL                            OldTpl;

  ASSERT(FileIo != NULL);
  
  //
  // Allocate memory for one FileIoWriteOneFileEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoWrite_Task), 
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
                   (EFI_EVENT_NOTIFY) FileIoWriteOneFileNotifyFunc,
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
  FileIoEntity->FileIoToken.Buffer     = (UINT8 *)Buffer;
  FileIoEntity->FileIoToken.BufferSize = WriteLength;
  FileIoEntity->SetPosition            = SetPosition;
  FileIoEntity->WriteLength            = WriteLength;
  
  Status = FileIoEntity->FileIo->SetPosition (FileIoEntity->FileIo, SetPosition);
  if (EFI_ERROR (Status)) {
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    return Status;
  }

  SctAcquireLock (&gAsyncWriteQueueLock);
  SctInsertTailList(&AsyncWriteExecuteListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncWriteQueueLock);
  
  //
  // Async WriteEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  Status = FileIo->WriteEx (
                     FileIoEntity->FileIo,
                     &FileIoEntity->FileIoToken
                     );
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    SctAcquireLock (&gAsyncWriteQueueLock);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctInsertTailList(&AsyncWriteFailListHead, &FileIoEntity->ListEntry);    
    SctReleaseLock (&gAsyncWriteQueueLock);
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return EFI_SUCCESS;
}



//
//Async Write Multi Files NotifyFunc
//
EFI_STATUS
EFIAPI FileIoWriteMultiFilesNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIoWrite_Task    *FileIoEntity;
  EFI_STATUS          Status;
  FileIoEntity = (FileIoWrite_Task *)Context;

  //
  // returned BufferSize equals ReadLength
  //
  Status = FileIoEntity->FileIo->GetPosition (
                                   FileIoEntity->FileIo,
                                   &FileIoEntity->PositionAfterWrite
                                   );
  
  if (EFI_ERROR (Status)) {
    return Status;
  } 

  //
  // Remove entity from WriteMultiExecuteListHead &  add entity to WriteMultiFinishListHead
  // All FileIoWriteMultiFiles Notify function run at Call Back level only once, So no locks required
  //
  SctAcquireLock (&gAsyncWriteMultiQueueLock);
  SctRemoveEntryList(&FileIoEntity->ListEntry);
  SctInsertTailList(&AsyncWriteMultiFinishListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncWriteMultiQueueLock);
  return EFI_SUCCESS;
}

/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.WriteEx() function abstraction interface
 *  @param FileIo  a pointer to File Io to be tested.
 *  @param SetPosition the Starting Position to write.
 *  @param WriteLength the Write length.
 *  @param Buffer a pointer to Write data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncWriteMultiFiles (
  IN EFI_FILE                          *FileIo,
  IN UINT64                            SetPosition,
  IN UINTN                             WriteLength,
  OUT UINT8                            *Buffer
)
{

  EFI_STATUS                         Status;
  FileIoWrite_Task                   *FileIoEntity = NULL;

  ASSERT(FileIo != NULL);
  
  //
  // Allocate memory for one FileIoWriteMultiFilesEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoWrite_Task), 
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
                   (EFI_EVENT_NOTIFY) FileIoWriteMultiFilesNotifyFunc,
                   FileIoEntity,
                   &FileIoEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(FileIoEntity);
    return Status;
  }

  FileIoEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoEntity->FileIo                 = FileIo;
  FileIoEntity->FileIoToken.Status     = EFI_NOT_READY;
  FileIoEntity->FileIoToken.Buffer     = (UINT8 *)Buffer;
  FileIoEntity->FileIoToken.BufferSize = WriteLength;
  FileIoEntity->WriteLength            = WriteLength;
  FileIoEntity->SetPosition            = SetPosition;
  
  Status = FileIoEntity->FileIo->SetPosition (FileIoEntity->FileIo, SetPosition);
  if (EFI_ERROR (Status)) {
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    return Status;
  }

  SctAcquireLock (&gAsyncWriteMultiQueueLock);
  SctInsertTailList(&AsyncWriteMultiExecuteListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncWriteMultiQueueLock);
  
  //
  // Async WriteEx Call
  //
  Status = FileIo->WriteEx (
                     FileIoEntity->FileIo,
                     &FileIoEntity->FileIoToken
                     );
  
  if (EFI_ERROR (Status)) {
    SctAcquireLock (&gAsyncWriteMultiQueueLock);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctInsertTailList(&AsyncWriteMultiFailListHead, &FileIoEntity->ListEntry);    
    SctReleaseLock (&gAsyncWriteMultiQueueLock);
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return EFI_SUCCESS;
}


/**
 *  @brief For WriteEx() basic test
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
 
//
// TDS 5.1.14
//
EFI_STATUS
EFIAPI
BBTestWriteExBasicTest (
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
  // 5.1.14.2.1 Async Call WriteEx() to write data into a normal file.
  //
  BBTestWriteExBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.1.14.2.2 Sync Call WriteEx() to write data into a normal file.
  //
  BBTestWriteExBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);

  //
  // 5.1.14.2.3 Async Call WriteEx() to write data into multi files.
  //
  BBTestWriteExBasicTestCheckpoint3 (StandardLib, SimpleFileSystem);

  //
  // 5.1.14.2.4 Sync Call WriteEx() to write data into multi files.
  //
  BBTestWriteExBasicTestCheckpoint4 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestWriteExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  UINT64                    FileSize;
  UINT8                     *Buffer;
  UINTN                     BufferSize;
  UINT64                    SetPosition[9] = {0, 50, 75, 100, 150, 175, 200, 250, 300};
  UINTN                     WriteLength[9] = {50, 25, 25, 50, 25, 25, 50, 50, 50};
  UINT8                     WriteContent[9] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
  UINTN                     PositionIndex;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  SCT_LIST_ENTRY            *ListEntry;
  FileIoWrite_Task          *FileIoEntity;
  UINT8                     BufferRead[100];

  Root         = NULL;
  Buffer       = NULL;
  BufferSize   = 300;
  ListEntry    = NULL;
  FileIoEntity = NULL;
  FileHandle   = NULL;
  FileSize     = 200;
  
  SctStrCpy (FileName, L"BBTestWriteExBasicTestCheckpoint1_File");

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
    Root->Close(Root);    
    return Status;
  }

  //
  // enlarge file by setting file size
  //
  Status = InternalSetFileSizeFileIo2 (FileHandle, FileSize);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"set file size fail",
                   L"%a:%d: Status - %r, filesize - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   (UINTN)FileSize
                   );

    if (FileHandle != NULL){
      FileHandle->Delete(FileHandle);
      FileHandle = NULL;
    }
    Root->Close(Root);
    return Status;
  }

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    for (PositionIndex = 0; PositionIndex < 9; PositionIndex++) {
      //
      // allocate buffer for write
      //
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
        continue;
      }
      //
      // set the Buffer content 
      //
      gtBS->SetMem (Buffer, BufferSize, WriteContent[PositionIndex]);

      //
      // write data to the file
      //
      Status = FileIoAsyncWriteOneFile(
                 FileHandle,
                 TplArray[TplIndex],
                 SetPosition[PositionIndex],
                 WriteLength[PositionIndex],
                 Buffer
                 );

	  if (EFI_ERROR(Status)) {
        gtBS->FreePool (Buffer);
	  }
    }
  }
  
  SctPrint (L" ================== Async WriteEx call finshed ================== \n\n");

  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  SctPrint (L"Wait maximumly 120s for all Async Write events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
    
  SctAcquireLock (&gAsyncWriteQueueLock);
  while (!SctIsListEmpty(&AsyncWriteExecuteListHead) && IndexI < 120) {
    SctReleaseLock (&gAsyncWriteQueueLock);
    
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    SctPrint (L".");
    SctAcquireLock (&gAsyncWriteQueueLock);
  }
  SctReleaseLock (&gAsyncWriteQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  SctPrint (L"\n");
 
  //
  // clear all File IO events from gWriteFinishQueue 
  // gWriteFinshQueue is handled first since we use File IO Write to do Write buffer validation 
  // Here no logs should be wrote to this file device to keep data intact
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  if (!SctIsListEmpty(&AsyncWriteFinishListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncWriteFinishListHead); ; ListEntry = SctGetNextNode(&AsyncWriteFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoWrite_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncWriteQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS && FileIoEntity->StatusAsync == EFI_SUCCESS) {
	  	
        FileHandle = FileIoEntity->FileIo;
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // file position is updated
        //
        if (FileIoEntity->PositionAfterWrite == (FileIoEntity->SetPosition + FileIoEntity->WriteLength)) {
          //
          // check write content
          //           
          Status = FileHandle->SetPosition (FileHandle, FileIoEntity->SetPosition);
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file position fail",
                           L"%a:%d: Status - %r, postion - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           FileIoEntity->SetPosition
                           );
            continue;
          }
            
          Status = FileHandle->Read (FileHandle, &FileIoEntity->WriteLength, BufferRead);  
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"Read file  fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            continue;
          }
            
          for (Index = 0; Index < FileIoEntity->WriteLength; Index++) {
            if (FileIoEntity->SetPosition == 0) {
              if (BufferRead[Index] != 0x31) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
            } else if (FileIoEntity->SetPosition == 50) {
              if (BufferRead[Index] != 0x32) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
            } else if (FileIoEntity->SetPosition == 75) {
              if (BufferRead[Index] != 0x33) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
            } else if (FileIoEntity->SetPosition == 100) {
              if (BufferRead[Index] != 0x34) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
            } else if (FileIoEntity->SetPosition == 150) {
              if (BufferRead[Index] != 0x35) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }               
            } else if (FileIoEntity->SetPosition == 175) {
              if (BufferRead[Index] != 0x36) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }               
            } else if (FileIoEntity->SetPosition == 200) {
              if (BufferRead[Index] != 0x37) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }               
            } else if (FileIoEntity->SetPosition == 250) {
              if (BufferRead[Index] != 0x38) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }               
            } else {
              if (BufferRead[Index] != 0x39) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }               
            }
          }
        }else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
		}
      }else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
	  }
      SctAcquireLock (&gAsyncWriteQueueLock);
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&AsyncWriteFinishListHead, ListEntry)) {
         break;
      }
    }
  }
  SctReleaseLock (&gAsyncWriteQueueLock);
  
  //
  // Record All Finished Write case results
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  while (!SctIsListEmpty(&AsyncWriteFinishListHead)) {
    FileIoEntity = CR(AsyncWriteFinishListHead.ForwardLink, FileIoWrite_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctReleaseLock (&gAsyncWriteQueueLock);

    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid009,
                   L"WriteEx() Basic Test - checkpoint1----Async",
                   L"%a:%d: WriteLength - %d, Expected - %d, position before Write - %d, position after Write - %d, Tpl - %d, StatusAsync = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->FileIoToken.BufferSize,
                   FileIoEntity->WriteLength,
                   (UINTN)FileIoEntity->SetPosition,
                   FileIoEntity->PositionAfterWrite,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
    
    if (FileIoEntity->FileIoToken.Buffer != NULL) {         
      Status = gtBS->FreePool (FileIoEntity->FileIoToken.Buffer);
      FileIoEntity->FileIoToken.Buffer = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    SctAcquireLock (&gAsyncWriteQueueLock);
  }
  SctReleaseLock (&gAsyncWriteQueueLock);

  //
  // If WriteFailListHead is not empty, which means some Async Calls are wrong 
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  while(!SctIsListEmpty(&AsyncWriteFailListHead)) {
    FileIoEntity = CR(AsyncWriteFailListHead.ForwardLink, FileIoWrite_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctReleaseLock (&gAsyncWriteQueueLock);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid010,
                   L"WriteEx() Basic Test - checkpoint1---Async",
                   L"%a:%d: WriteLength - %d, position before write - %d, Tpl - %d, StatusAsync = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->FileIoToken.BufferSize,
                   (UINTN)FileIoEntity->SetPosition,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
     //
     // Free  Buffer
     //
     if (FileIoEntity->FileIoToken.Buffer != NULL) {
       Status =gtBS->FreePool (FileIoEntity->FileIoToken.Buffer);
       FileIoEntity->FileIoToken.Buffer = NULL;
     }
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
     gtBS->FreePool(FileIoEntity);
       
     SctAcquireLock (&gAsyncWriteQueueLock);
  }
  SctReleaseLock (&gAsyncWriteQueueLock);  
  
  //
  // If WriteExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  if (!SctIsListEmpty(&AsyncWriteExecuteListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncWriteExecuteListHead); ; ListEntry = SctGetNextNode(&AsyncWriteExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoWrite_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncWriteQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid011,
                     L"WriteEx() Basic Test - checkpoint1----Async",
                     L"%a:%d: WriteLength - %d, position before read - %d, Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->FileIoToken.BufferSize,
                     (UINTN)FileIoEntity->SetPosition,
                     FileIoEntity->Tpl
                     );

      SctAcquireLock (&gAsyncWriteQueueLock);
      if (SctIsNodeAtEnd(&AsyncWriteExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  SctReleaseLock (&gAsyncWriteQueueLock);

  FileHandle->Delete(FileHandle);  
  Root->Close(Root);
  return EFI_SUCCESS;
}

//
//CheckPoint2 --------Sync WriteEx
//
EFI_STATUS
EFIAPI
BBTestWriteExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                WriteExStatus;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  UINT64                    FileSize;
  UINT8                     BufferWrite[200];
  UINT8                     BufferRead[200];
  UINTN                     BufferSize;
  UINT64                    SetPosition[9] = {0, 0, 0, 100, 100, 100, 200, 200, 300};
  UINT8                     WriteContent;
  UINT64                    PositionAfterWrite;
  UINTN                     WriteLength[9] = {50, 75, 100, 50, 75, 100, 0, 100, 1};
  UINTN                     PositionIndex;
  UINTN                     Index;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_INFO             *FileInfo;
  UINTN                     InfoSize;

  
  Root         = NULL;
  FileHandle   = NULL;
  FileInfo     = NULL;
  FileSize     = 200;
  BufferSize   = 200;
  WriteContent = 0x31;
  SctStrCpy (FileName, L"BBTestWriteExBasicTestCheckpoint2_File");

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
    Root->Close(Root);
    return Status;
  }

  //
  // enlarge file by setting file size
  //
  Status = InternalSetFileSizeFileIo2 (FileHandle, FileSize);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"set file size fail",
                   L"%a:%d: Status - %r, filesize - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   (UINTN)FileSize
                   );
  
    if (FileHandle != NULL){
      FileHandle->Delete(FileHandle);
      FileHandle = NULL;
    }
    
    Root->Close(Root);
    return Status;
  }


  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    for (PositionIndex = 0; PositionIndex < 9; PositionIndex++) {
      //
      // reset file size
      //
      Status = InternalSetFileSizeFileIo2 (FileHandle, FileSize);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"set file position fail",
                       L"%a:%d: Status - %r, filesize - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINTN)FileSize
                       );
        continue;
      }

      Status = FileHandle->SetPosition (FileHandle, SetPosition[PositionIndex]);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"set file position fail",
                       L"%a:%d: Status - %r, setpostion - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       SetPosition[PositionIndex]
                       );
        continue;
      }
	  
      //
      // set the Buffer content 
      //
      gtBS->SetMem (BufferWrite, BufferSize, WriteContent);

      PositionAfterWrite = 0;

      //
      // Sync Token Init
      //
      FileIoTokenSync.Event      = NULL;
      FileIoTokenSync.Status     = EFI_NOT_READY;
      FileIoTokenSync.BufferSize = WriteLength[PositionIndex];
      FileIoTokenSync.Buffer     = BufferWrite;

      OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
      
      WriteExStatus = FileHandle->WriteEx (
                                    FileHandle,
                                    &FileIoTokenSync
                                    );
      
      gtBS->RestoreTPL (OldTpl);

      AssertionType = EFI_TEST_ASSERTION_PASSED;
      
      //
      // Check & record  
      // 
      if (Status == EFI_SUCCESS) {
        //
        // returned BufferSize equals ReadLength
        //
        if (FileIoTokenSync.BufferSize == WriteLength[PositionIndex]) {

          Status = FileHandle->GetPosition (FileHandle, &PositionAfterWrite);
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"get file position fail",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
            continue;
          }   
          
          //
          // file position is updated
          //
          if (PositionAfterWrite == (SetPosition[PositionIndex] + WriteLength[PositionIndex])){
            //
            // file size grows
            //
            FileInfo = NULL;
            Status = InternalGetInfoFileIo2 (FileHandle, (VOID **) &FileInfo, &InfoSize, &gBlackBoxEfiFileInfoGuid);
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"Get file info fail",
                             L"%a:%d: Status - %r, postion - %d",
                              __FILE__,
                             (UINTN)__LINE__,
                             Status,
                             SetPosition[PositionIndex]
                             );
              continue;
            }
            
            //
            // exceed original file size
            //
            if (((PositionAfterWrite >= FileSize) && (FileInfo->FileSize == PositionAfterWrite)) || 
              ((PositionAfterWrite < FileSize) && (FileInfo->FileSize == FileSize))) {
              //
              // check read content
              //         
              Status = FileHandle->SetPosition (FileHandle, SetPosition[PositionIndex]);
              if (EFI_ERROR (Status)) {
                StandardLib->RecordAssertion (
                               StandardLib,
                               EFI_TEST_ASSERTION_FAILED,
                               gTestGenericFailureGuid,
                               L"set file position fail",
                               L"%a:%d: Status - %r, postion - %d",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status,
                               SetPosition[PositionIndex]
                               );
                continue;
              }

              Status = FileHandle->Read (FileHandle, &WriteLength[PositionIndex], BufferRead);
              if (EFI_ERROR (Status)) {
                StandardLib->RecordAssertion (
                               StandardLib,
                               EFI_TEST_ASSERTION_FAILED,
                               gTestGenericFailureGuid,
                               L"Read file position fail",
                               L"%a:%d: Status - %r",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status
                               );
                continue;
              }
              
              for (Index = 0; Index < WriteLength[PositionIndex]; Index++) {
                if (BufferRead[Index] != 0x31) {
                  AssertionType = EFI_TEST_ASSERTION_FAILED;
                  break;
                }
              }
            }
          }
        }    else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid012,
                     L"WriteEx() Basic Test - checkpoint2---Sync",
                     L"%a:%d: WriteLength - %d, Expected - %d, Position Before Write - %d, Position After Write - %d, Filesize - %d, Tpl - %d, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoTokenSync.BufferSize,
                     WriteLength[PositionIndex],
                     SetPosition[PositionIndex],
                     PositionAfterWrite,
                     FileInfo->FileSize,             
                     TplArray[TplIndex],
                     WriteExStatus
                     );
	  
      if (FileInfo != NULL){
        gtBS->FreePool (FileInfo);
        FileInfo = NULL;
      }
    }
  }
     
  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
    FileHandle = NULL;
  }

  Root->Close(Root);

  return Status;
}


//
//checkpoint3 ----Async Write Multi Files
//
EFI_STATUS
EFIAPI
BBTestWriteExBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  CHAR16                    FileName[3][100];
  EFI_FILE                  *FileHandle[3];
  UINT64                    FileSize;
  UINT8                     *Buffer[3];
  UINTN                     BufferSize;
  UINT64                    SetPosition[3] = {0, 100, 200};
  UINTN                     WriteLength[3] = {50, 100, 100};
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  SCT_LIST_ENTRY            *ListEntry;
  FileIoWrite_Task          *FileIoEntity;
  UINT8                     BufferRead[200];
  EFI_FILE_INFO             *FileInfo;
  UINTN                     InfoSize;

  Root         = NULL;
  ListEntry    = NULL;
  FileIoEntity = NULL;
  FileInfo     = NULL;
  FileSize     = 200;
  BufferSize   = 300;
  SctStrCpy (FileName[0], L"BBTestWriteExBasicTestCheckpoint3_File1");
  SctStrCpy (FileName[1], L"BBTestWriteExBasicTestCheckpoint3_File2");
  SctStrCpy (FileName[2], L"BBTestWriteExBasicTestCheckpoint3_File3");
  
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
  // create the file
  //
  for (Index = 0; Index < 3; Index++){
  	FileHandle[Index] = NULL;
    Status = Root->Open (Root, &FileHandle[Index], FileName[Index], CREATE_FILE_MODE, 0);
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
      for (IndexI = 0; IndexI < Index; IndexI++) {
        if (FileHandle[IndexI] != NULL) {
          FileHandle[IndexI]->Delete(FileHandle[IndexI]);
        }
	  }
      Root->Close(Root);
      return Status;
    }
  }
  
  //
  // enlarge file by setting file size
  //
  for (Index = 0; Index < 3; Index++){
    Status = InternalSetFileSizeFileIo2 (FileHandle[Index], FileSize);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file size fail",
                     L"%a:%d: Status - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (UINTN)Index
                     );

      for (IndexI = 0; IndexI < 3; IndexI++){
        if (FileHandle[IndexI] != NULL){
          FileHandle[IndexI]->Delete(FileHandle[IndexI]);
        }
      }
      Root->Close(Root);

      return Status;
    }
  }

  for (Index = 0; Index < 3; Index++) {
    //
    // allocate buffer for write
    //
    Buffer[Index] = NULL;
    Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer[Index]);
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
      for (IndexI = 0; IndexI < Index; IndexI++) {
        if (Buffer[IndexI] != NULL) {
          gtBS->FreePool(Buffer[IndexI]);
        }
	  }
      for (IndexI = 0; IndexI < 3; IndexI++){
        if (FileHandle[IndexI] != NULL){
          FileHandle[IndexI]->Delete(FileHandle[IndexI]);
        }
      }
      Root->Close(Root);
      return Status;
    }

	//
    // set the Buffer content 
    //
    gtBS->SetMem (Buffer[Index], BufferSize, 0x31);
  }

  for (Index = 0; Index < 3; Index++) { 
	//
    // write data to the file
    //
    Status = FileIoAsyncWriteMultiFiles(
               FileHandle[Index],
               SetPosition[Index],
               WriteLength[Index],
               Buffer[Index]
               );

    if (EFI_ERROR(Status)) {
      gtBS->FreePool(Buffer[Index]);
      FileHandle[Index]->Delete(FileHandle[Index]);
    }
  }
  
  SctPrint (L" ================== Async WriteEx call finshed ================== \n\n");
  
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  SctPrint (L"Wait maximumly 120s for all Async Write events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  SctAcquireLock (&gAsyncWriteMultiQueueLock);
  while (!SctIsListEmpty(&AsyncWriteMultiExecuteListHead) && IndexI < 120) {
    SctReleaseLock (&gAsyncWriteMultiQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    SctPrint (L".");
    SctAcquireLock (&gAsyncWriteMultiQueueLock);
  }
  SctReleaseLock (&gAsyncWriteMultiQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  SctPrint (L"\n");
 
  //
  // clear all File IO events from gWriteFinishQueue 
  // gWriteFinshQueue is handled first since we use File IO Write to do Write buffer validation 
  // Here no logs should be wrote to this file device to keep data intact
  //
  SctAcquireLock (&gAsyncWriteMultiQueueLock);
  if (!SctIsListEmpty(&AsyncWriteMultiFinishListHead)) {
    for (ListEntry = SctGetFirstNode(&AsyncWriteMultiFinishListHead); ; ListEntry = SctGetNextNode(&AsyncWriteMultiFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoWrite_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncWriteMultiQueueLock);

      FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;;
      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS && FileIoEntity->StatusAsync == EFI_SUCCESS) {

        if (FileIoEntity->FileIoToken.BufferSize == FileIoEntity->WriteLength) {
          //
          // file position is updated
          //
          if (FileIoEntity->PositionAfterWrite == (FileIoEntity->SetPosition + FileIoEntity->WriteLength)) {
            //
            // file size grows
            //
            FileInfo = NULL;
            Status = InternalGetInfoFileIo2 (FileIoEntity->FileIo, (VOID **) &FileInfo, &InfoSize, &gBlackBoxEfiFileInfoGuid);
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"Get file info fail",
                             L"%a:%d: Status - %r, postion - %d",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status,
                             FileIoEntity->SetPosition
                             );
              continue;
            }
              
            //
            // exceed original file size
            //
            if ((((FileIoEntity->SetPosition + FileIoEntity->WriteLength) < FileSize) && (FileInfo->FileSize == FileSize)) || 
              (((FileIoEntity->SetPosition + FileIoEntity->WriteLength) >= FileSize) && (FileInfo->FileSize == FileIoEntity->PositionAfterWrite))) {
             
              //
              // check read content
              // 
              Status = FileIoEntity->FileIo->SetPosition (FileIoEntity->FileIo, FileIoEntity->SetPosition);
              if (EFI_ERROR (Status)) {
                StandardLib->RecordAssertion (
                               StandardLib,
                               EFI_TEST_ASSERTION_FAILED,
                               gTestGenericFailureGuid,
                               L"set file position fail",
                               L"%a:%d: Status - %r, postion - %d",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status,
                               FileIoEntity->SetPosition
                               );
                continue;
              }
			  
              Status = FileIoEntity->FileIo->Read (FileIoEntity->FileIo, &FileIoEntity->WriteLength, BufferRead);
              if (EFI_ERROR (Status)) {
                StandardLib->RecordAssertion (
                               StandardLib,
                               EFI_TEST_ASSERTION_FAILED,
                               gTestGenericFailureGuid,
                               L"Read file position fail",
                               L"%a:%d: Status - %r",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status
                               );
                continue;
              }
                
              for (Index = 0; Index < FileIoEntity->WriteLength; Index++) {
                if (BufferRead[Index] != 0x31) {
                  FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                  break;
                }
              }
            } else {
              FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            
            if (FileInfo != NULL){
              gtBS->FreePool (FileInfo);  
              FileInfo = NULL;
            } 
			
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      SctAcquireLock (&gAsyncWriteMultiQueueLock);
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&AsyncWriteMultiFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  SctReleaseLock (&gAsyncWriteMultiQueueLock);
    
  //
  // Record All Finished Write case results
  //
  SctAcquireLock (&gAsyncWriteMultiQueueLock);
  while (!SctIsListEmpty(&AsyncWriteMultiFinishListHead)) {
    FileIoEntity = CR(AsyncWriteMultiFinishListHead.ForwardLink, FileIoWrite_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctReleaseLock (&gAsyncWriteMultiQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid013,
                   L"WriteEx() Basic Test - checkpoint3----Async",
                   L"%a:%d: WriteLength - %d, Expected - %d, position before Write - %d, position after Write - %d, StatusAsync = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->FileIoToken.BufferSize,
                   FileIoEntity->WriteLength,
                   (UINTN)FileIoEntity->SetPosition,
                   FileIoEntity->PositionAfterWrite,
                   FileIoEntity->StatusAsync
                   );
        
    if (FileIoEntity->FileIoToken.Buffer != NULL) {         
      Status = gtBS->FreePool (FileIoEntity->FileIoToken.Buffer);
      FileIoEntity->FileIoToken.Buffer = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    SctAcquireLock (&gAsyncWriteMultiQueueLock);
  }
  SctReleaseLock (&gAsyncWriteMultiQueueLock);


  //
  // If WriteMultiFailListHead is not empty, which means some Async Calls are wrong 
  //
  SctAcquireLock (&gAsyncWriteMultiQueueLock);
  while(!SctIsListEmpty(&AsyncWriteMultiFailListHead)) {
    FileIoEntity = CR(AsyncWriteMultiFailListHead.ForwardLink, FileIoWrite_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctReleaseLock (&gAsyncWriteMultiQueueLock);
        
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid014,
                   L"WriteEx() Basic Test - checkpoint3---Async",
                   L"%a:%d: WriteLength - %d, Expected - %d, position before write - %d,StatusAsync = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->FileIoToken.BufferSize,
                   FileIoEntity->WriteLength,
                   (UINTN)FileIoEntity->SetPosition,
                   FileIoEntity->StatusAsync
                   );
    //
    // Free  Buffer
    //
    if (FileIoEntity->FileIoToken.Buffer != NULL) {
      Status =gtBS->FreePool (FileIoEntity->FileIoToken.Buffer);
      FileIoEntity->FileIoToken.Buffer = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
         
    SctAcquireLock (&gAsyncWriteMultiQueueLock);
  }
  SctReleaseLock (&gAsyncWriteMultiQueueLock);
      
    
  //
  // If WriteMultiExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  SctAcquireLock (&gAsyncWriteMultiQueueLock);
  if (!SctIsListEmpty(&AsyncWriteMultiExecuteListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncWriteMultiExecuteListHead); ; ListEntry = SctGetNextNode(&AsyncWriteMultiExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoWrite_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncWriteMultiQueueLock);
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid015,
                     L"WriteEx() Basic Test - checkpoint3----Async",
                     L"%a:%d: BufferSize - %d, Expected - %d, position before read - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->FileIoToken.BufferSize,
                     FileIoEntity->WriteLength,
                     (UINTN)FileIoEntity->SetPosition
                     );

      SctAcquireLock (&gAsyncWriteMultiQueueLock);
      if (SctIsNodeAtEnd(&AsyncWriteMultiExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  SctReleaseLock (&gAsyncWriteMultiQueueLock);
     
  for (Index = 0; Index < 3; Index++){
    if ( FileHandle[Index] != NULL){
      FileHandle[Index]->Delete(FileHandle[Index]);
      FileHandle[Index] = NULL;
    }
  }
  
  Root->Close(Root);
    
  return EFI_SUCCESS;
}


//
//CheckPoint4 --------Sync WriteEx Multi Files
//
EFI_STATUS
EFIAPI
BBTestWriteExBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                WriteStatus;
  EFI_FILE                  *Root;
  CHAR16                    FileName[3][100];
  EFI_FILE                  *FileHandle[3];
  UINT64                    FileSize;
  UINTN                     BufferSize;
  UINT64                    SetPosition[3] = {0, 100, 200};
  UINTN                     WriteLength[3] = {50, 100, 100};
  UINT64                    PositionAfterWrite;
  UINTN                     Index;
  UINTN                     IndexI;
  UINT8                     BufferWrite[200];  
  UINT8                     BufferRead[200];
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_INFO             *FileInfo;
  UINTN                     InfoSize;

  Root               = NULL;
  FileInfo           = NULL;
  FileSize           = 200;
  BufferSize         = 200;
  PositionAfterWrite = 0;

  SctStrCpy (FileName[0], L"BBTestWriteExBasicTestCheckpoint4_File1");
  SctStrCpy (FileName[1], L"BBTestWriteExBasicTestCheckpoint4_File2");
  SctStrCpy (FileName[2], L"BBTestWriteExBasicTestCheckpoint4_File3");
  
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
  // create the file
  //
  for (Index = 0; Index < 3; Index++){
  	FileHandle[Index] = NULL;
    Status = Root->Open (Root, &FileHandle[Index], FileName[Index], CREATE_FILE_MODE, 0);
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
      for (IndexI = 0; IndexI < Index; IndexI++){
        if (FileHandle[IndexI] != NULL){
          FileHandle[IndexI]->Delete(FileHandle[IndexI]);
          FileHandle[IndexI] = NULL;
        }
      }
      
      Root->Close(Root);
      return Status;
    }
  }
  //
  // enlarge file by setting file size
  //
  for (Index = 0; Index < 3; Index++){
    Status = InternalSetFileSizeFileIo2 (FileHandle[Index], FileSize);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file size fail",
                     L"%a:%d: Status - %r, filesize - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (UINTN)FileSize
                     );
    
      for (IndexI = 0; IndexI < 3; IndexI++){
        if (FileHandle[IndexI] != NULL){
          FileHandle[IndexI]->Delete(FileHandle[IndexI]);
          FileHandle[IndexI] = NULL;
        }
      }
     
      Root->Close(Root);

      return Status;
    }
  }
  
  for (Index = 0; Index < 3; Index++) {
    //
    // set the Buffer content 
    //
    gtBS->SetMem (BufferWrite, BufferSize, 0x31);
    
    //
    // reset file size
    //
    Status = InternalSetFileSizeFileIo2 (FileHandle[Index], FileSize);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file position fail",
                     L"%a:%d: Status - %r, filesize - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (UINTN)FileSize
                     );
      continue;
    }

    Status = FileHandle[Index]->SetPosition (FileHandle[Index], SetPosition[Index]);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file position fail",
                     L"%a:%d: Status - %r, setpostion - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     SetPosition[Index]
                     );
      continue;
    }

    //
    // Sync Token Init
    //
    FileIoTokenSync.Event      = NULL;
    FileIoTokenSync.Status     = EFI_NOT_READY;
    FileIoTokenSync.BufferSize = WriteLength[Index];
    FileIoTokenSync.Buffer     = BufferWrite;
    
    WriteStatus = FileHandle[Index]->WriteEx (
                                       FileHandle[Index],
                                       &FileIoTokenSync
                                       );

    AssertionType = EFI_TEST_ASSERTION_PASSED;

    //
    // Check & record  
    // 
    if (Status == EFI_SUCCESS) {
      //
      // returned BufferSize equals ReadLength
      //
      if (FileIoTokenSync.BufferSize == WriteLength[Index]) {

        Status = FileHandle[Index]->GetPosition (FileHandle[Index], &PositionAfterWrite);

        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"get file position fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
          continue;
        }   
        
        //
        // file position is updated
        //
        if (PositionAfterWrite == (SetPosition[Index] + WriteLength[Index])) {
          //
          // file size grows
          //
          FileInfo = NULL;
          Status = InternalGetInfoFileIo2 (FileHandle[Index], (VOID **) &FileInfo, &InfoSize, &gBlackBoxEfiFileInfoGuid);
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"Get file info fail",
                           L"%a:%d: Status - %r, postion - %d",
                            __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           SetPosition[Index]
                           );
            continue;
          }
          
          //
          // exceed original file size
          //
          if ((((SetPosition[Index] + WriteLength[Index]) < FileSize) && FileInfo->FileSize == FileSize) || 
            (((SetPosition[Index] + WriteLength[Index]) >= FileSize) && (FileInfo->FileSize == PositionAfterWrite))) {
            //
            // check read content
            //
            Status = FileHandle[Index]->SetPosition (FileHandle[Index], SetPosition[Index]);
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"set file position fail",
                             L"%a:%d: Status - %r, postion - %d",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status,
                             SetPosition[Index]
                             );
              continue;
            }

            Status = FileHandle[Index]->Read (FileHandle[Index], &WriteLength[Index], BufferRead);
            if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"Read file position fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
              continue;
            }
            
            for (IndexI = 0; IndexI < WriteLength[IndexI]; IndexI++) {
              if (BufferRead[IndexI] != 0x31) {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
            }
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
		  }
          if (FileInfo != NULL){
            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
          }
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid016,
                   L"WriteEx() Basic Test - checkpoint4---Sync",
                   L"%a:%d: WriteLength - %d, Expected - %d, position before write - %d, position after write - %d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoTokenSync.BufferSize,
                   WriteLength[Index],
                   SetPosition[Index],
                   PositionAfterWrite,
                   WriteStatus
                   );


  }
   
  for (Index = 0; Index < 3; Index++){   
    if (FileHandle[Index] != NULL) {
      FileHandle[Index]->Delete (FileHandle[Index]);
      FileHandle[Index] = NULL;
    }
  }
  Root->Close(Root);
  return Status;
 }


EFI_STATUS
InternalGetInfoFileIo2 (
  EFI_FILE               *FileHandle,
  VOID                   **InfoBuffer,
  UINTN                  *BufferSize,
  EFI_GUID               *InfoId
  )
{
  UINT8         *Buffer = NULL;
  EFI_STATUS    Status = EFI_SUCCESS;

  *InfoBuffer = NULL;

  *BufferSize = 1;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   *BufferSize,
                   (VOID**)&Buffer
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = FileHandle->GetInfo (
                         FileHandle,
                         InfoId,
                         BufferSize,
                         (VOID*)Buffer
                         );
  if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
    goto Done;
  }

  if (Status == EFI_BUFFER_TOO_SMALL) {

    gtBS->FreePool ((VOID*)Buffer);
    Buffer = NULL;
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     *BufferSize,
                     (VOID**)&Buffer
                     );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = FileHandle->GetInfo (
                           FileHandle,
                           InfoId,
                           BufferSize,
                           (VOID*)Buffer
                           );
  }

Done:
  if (EFI_ERROR(Status)) {
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
      Buffer = NULL;
    }
  }

  *InfoBuffer = Buffer;
  return Status;
}


EFI_STATUS
InternalSetFileSizeFileIo2 (
  EFI_FILE               *FileHandle,
  UINT64                 FileSize
  )
{
  EFI_FILE_INFO *InfoBuffer;
  UINTN         BufferSize;
  EFI_STATUS    Status;

  Status = InternalGetInfoFileIo2 (FileHandle, (VOID **) &InfoBuffer, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  InfoBuffer->FileSize = FileSize;
  Status = FileHandle->SetInfo (FileHandle, &gBlackBoxEfiFileInfoGuid, BufferSize, InfoBuffer);

  gtBS->FreePool (InfoBuffer);

  return Status;
}




