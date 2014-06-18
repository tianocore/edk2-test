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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/

/*++

Module Name:
    SimpleFileSystemExTestFunction_OpenEx.c

Abstract:
    for EFI Simple File System Protocol and EFI_FILE Protocol's Function Test

--*/


#include "SimpleFileSystemBBTest.h"

#define VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE    8   // zero-based
#define ALL_ATTRIBUTES_COUNT_FOR_CREATE                16

#define MAX_NUMBER_OF_FILE_NAME   1000
#define MAX_STRING_LENGTH         266

//
//
//
typedef struct {
  UINTN                             Signature;
  EFI_FILE_PROTOCOL                 *FileIo;
  EFI_FILE_IO_TOKEN                 FileIoToken;
  EFI_TPL                           Tpl;
  CHAR16                            *Name;
  UINT64                            OpenMode;
  EFI_LIST_ENTRY                    ListEntry;     
  EFI_STATUS                        StatusAsync;
  EFI_TEST_ASSERTION                AssertionType;
} FileIoOpenFile_Task;


//----------------------------------//
//
//  This macro is used for a sub-set test (to save time)
//
#define FILE_SYSTEM_SIMPLE_TEST 1
//
//---------------------------------//

CHAR16 ValidFileBaseNameFileIo2[][30] = {
                              L"u",
                              L"h_jsf77",
                              L"sf_h+8~a",
                              L"was09=$iw",
                              L"a2~isudfoi01f98w7r7%01'-f@a",
                              L"!123",
                              L"wx#12`A;--0B",
                              L"[abc123]][()]"
                              };
CHAR16 ValidExtensionNameFileIo2[][15]={L"", L"1", L"u2", L"sf_", L"0404", L"g_=fs+lkd11", L"Aa [b"};

UINT64 ValidAttributesForCreateFileIo2[] = {
  0,
  EFI_FILE_HIDDEN,
  EFI_FILE_SYSTEM,
  EFI_FILE_ARCHIVE,
  EFI_FILE_HIDDEN | EFI_FILE_SYSTEM,
  EFI_FILE_HIDDEN | EFI_FILE_ARCHIVE,
  EFI_FILE_SYSTEM | EFI_FILE_ARCHIVE,
  EFI_FILE_HIDDEN | EFI_FILE_SYSTEM | EFI_FILE_ARCHIVE,
  //
  // below are for directory
  //
  EFI_FILE_DIRECTORY,
  EFI_FILE_DIRECTORY | EFI_FILE_HIDDEN,
  EFI_FILE_DIRECTORY | EFI_FILE_SYSTEM,
  EFI_FILE_DIRECTORY | EFI_FILE_ARCHIVE,
  EFI_FILE_DIRECTORY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM,
  EFI_FILE_DIRECTORY | EFI_FILE_HIDDEN | EFI_FILE_ARCHIVE,
  EFI_FILE_DIRECTORY | EFI_FILE_SYSTEM | EFI_FILE_ARCHIVE,
  EFI_FILE_DIRECTORY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM | EFI_FILE_ARCHIVE
  };


//
// Async Open File Queue
//
EFI_LIST_ENTRY  AsyncOpenFileExecuteListHead = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenFileExecuteListHead);
EFI_LIST_ENTRY  AsyncOpenFileFinishListHead  = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenFileFinishListHead);
EFI_LIST_ENTRY  AsyncOpenFileFailListHead    = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenFileFailListHead);

//
// Async Open File lock
//
FLOCK  gAsyncOpenFileQueueLock = EFI_INITIALIZE_LOCK_VARIABLE (EFI_TPL_CALLBACK);

//
// Async Open Dir Queue
//
EFI_LIST_ENTRY  AsyncOpenDirExecuteListHead = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenDirExecuteListHead);
EFI_LIST_ENTRY  AsyncOpenDirFinishListHead  = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenDirFinishListHead);
EFI_LIST_ENTRY  AsyncOpenDirFailListHead    = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenDirFailListHead);



//
// Sync Create File Queue for Async Open 
//
EFI_LIST_ENTRY  SyncCreateFileListHead = INITIALIZE_LIST_HEAD_VARIABLE(SyncCreateFileListHead);

//
// Async Open Existing File Queue
//
EFI_LIST_ENTRY  AsyncOpenExistingFileExecuteListHead = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenExistingFileExecuteListHead);
EFI_LIST_ENTRY  AsyncOpenExistingFileFinishListHead  = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenExistingFileFinishListHead);
EFI_LIST_ENTRY  AsyncOpenExistingFileFailListHead    = INITIALIZE_LIST_HEAD_VARIABLE(AsyncOpenExistingFileFailListHead);

//
// Async Open File lock
//
FLOCK  gAsyncOpenExistingFileQueueLock = EFI_INITIALIZE_LOCK_VARIABLE (EFI_TPL_CALLBACK);

//
// some private functions declaration
//
EFI_STATUS
ComposeFileNameArrayFileIo2 (
  CHAR16        **PureFileNameArray,
  UINT32        *NameCount
  );


EFI_STATUS
InternalGetInfoFileIo2 (
  EFI_FILE_PROTOCOL      *FileHandle,
  VOID                   **InfoBuffer,
  UINTN                  *BufferSize,
  EFI_GUID               *InfoId
  );

//
//Checkpoints 
//

EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test1_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test1_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test2_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test2_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test3_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test3_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test4_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test4_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test5_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );



EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test5_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test1_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test1_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test2_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test2_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test3_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test3_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test4_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test4_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test5_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );


EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test5_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

EFI_STATUS
BBTestOpenExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );



//
//Async Open File NotifyFunc
//
VOID
EFIAPI FileIoOpenFileNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIoOpenFile_Task    *FileIoEntity;
  
  FileIoEntity = (FileIoOpenFile_Task *)Context;

  //
  // Remove entity from OpenFileExecuteListHead &  add entity to OpenFileFinishListHead
  // All FileIoOpenFile Notify function run at Call Back level only once, So no locks required
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  RemoveEntryList(&FileIoEntity->ListEntry);
  InsertTailList(&AsyncOpenFileFinishListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncOpenFileQueueLock);
}

/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.OpenEx() function abstraction interface
 *  @param Root  a pointer to File Io to be tested.
 *  @param Tpl the Tpl level
 *  @param PureStrPointer point to the filename
 *  @param Attribute the file attribute
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncOpenFile (
  IN EFI_FILE_PROTOCOL                 *Root,
  IN EFI_TPL                           Tpl,
  IN CHAR16                            *PureStrPointer,
  IN UINT64                            Attribute
)
{

  EFI_STATUS                         Status;
  FileIoOpenFile_Task                *FileIoEntity;
  EFI_TPL                            OldTpl;

  ASSERT(Root != NULL);
  FileIoEntity = NULL;

  //
  // Allocate memory for one FileIoOpenFileEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoOpenFile_Task), 
                   &FileIoEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gtBS->SetMem (FileIoEntity, sizeof(FileIoOpenFile_Task), 0x0);
  
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   FileIoOpenFileNotifyFunc,
                   FileIoEntity,
                   &FileIoEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(FileIoEntity);
    return Status;
  }

  FileIoEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoEntity->Tpl                    = Tpl;
  FileIoEntity->FileIoToken.Status     = EFI_NOT_READY;
  FileIoEntity->Name                   = PureStrPointer;


  AcquireLock(&gAsyncOpenFileQueueLock);
  InsertTailList(&AsyncOpenFileExecuteListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // Async OpenEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  
  Status = Root->OpenEx (
                   Root,
                   &FileIoEntity->FileIo,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   Attribute,
                   &FileIoEntity->FileIoToken
                   );
  
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    AcquireLock(&gAsyncOpenFileQueueLock);
    RemoveEntryList(&FileIoEntity->ListEntry);
    InsertTailList(&AsyncOpenFileFailListHead, &FileIoEntity->ListEntry);    
    ReleaseLock(&gAsyncOpenFileQueueLock);
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return EFI_SUCCESS;
}

//
//Async Open Dir NotifyFunc
//
VOID
EFIAPI FileIoOpenDirNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIoOpenFile_Task    *FileIoEntity;
  
  FileIoEntity = (FileIoOpenFile_Task *)Context;

  //
  // Remove entity from OpenDirExecuteListHead &  add entity to OpenDirFinishListHead
  // All FileIoOpenDir Notify function run at Call Back level only once, So no locks required
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  RemoveEntryList(&FileIoEntity->ListEntry);
  InsertTailList(&AsyncOpenDirFinishListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncOpenFileQueueLock);
}


/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.OpenEx() function abstraction interface
 *  @param Root  a pointer to File Io to be tested.
 *  @param Tpl the Tpl level
 *  @param PureStrPointer point to the filename
 *  @param StrPointer point to the dirname
 *  @param DirAttribute the Dir attribute
 *  @param FileAttribute the file attribute
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncOpenDir (
  IN EFI_FILE_PROTOCOL                 *Root,
  IN EFI_TPL                           Tpl,
  IN CHAR16                            *PureStrPointer,
  IN CHAR16                            *StrPointer,
  IN UINT64                            DirAttribute,
  IN UINT64                            FileAttribute
)
{

  EFI_STATUS                         Status;
  FileIoOpenFile_Task                *FileIoOpenFileEntity;
  FileIoOpenFile_Task                *FileIoOpenDirEntity;
  EFI_TPL                            OldTpl;

  ASSERT(Root != NULL);
  FileIoOpenDirEntity  = NULL;
  FileIoOpenFileEntity = NULL;
  //
  // Allocate memory for one FileIoOpenFileEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoOpenFile_Task), 
                   &FileIoOpenFileEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Allocate memory for one FileIoOpenDirEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoOpenFile_Task), 
                   &FileIoOpenDirEntity);
  if (EFI_ERROR (Status)) {
    
    if (FileIoOpenFileEntity != NULL)
      gtBS->FreePool(FileIoOpenFileEntity);
    
    return Status;
  }
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   FileIoOpenDirNotifyFunc,
                   FileIoOpenDirEntity,
                   &FileIoOpenDirEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    
    if (FileIoOpenFileEntity != NULL){
      gtBS->FreePool(FileIoOpenFileEntity);
      FileIoOpenFileEntity = NULL;
    }
    if (FileIoOpenDirEntity != NULL){
      gtBS->FreePool(FileIoOpenDirEntity);
      FileIoOpenDirEntity = NULL;
    }
    
    return Status;
  }

  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   FileIoOpenFileNotifyFunc,
                   FileIoOpenFileEntity,
                   &FileIoOpenFileEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    if (FileIoOpenFileEntity != NULL){
      gtBS->FreePool(FileIoOpenFileEntity);
      FileIoOpenFileEntity = NULL;
    }
    if (FileIoOpenDirEntity != NULL){
      gtBS->FreePool(FileIoOpenDirEntity);
      FileIoOpenDirEntity = NULL;
    }
    gtBS->CloseEvent(FileIoOpenDirEntity->FileIoToken.Event);
    return Status;
  }

  FileIoOpenDirEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoOpenDirEntity->Tpl                    = Tpl;
  FileIoOpenDirEntity->FileIoToken.Status     = EFI_NOT_READY;
  FileIoOpenDirEntity->Name                   = PureStrPointer;

  FileIoOpenFileEntity->Signature             = FILEIOENTITY_SIGNATURE;
  FileIoOpenFileEntity->Tpl                   = Tpl;
  FileIoOpenFileEntity->FileIoToken.Status    = EFI_NOT_READY;
  FileIoOpenFileEntity->Name                  = StrPointer;

  AcquireLock(&gAsyncOpenFileQueueLock);
  InsertTailList(&AsyncOpenDirExecuteListHead, &FileIoOpenDirEntity->ListEntry);
  ReleaseLock(&gAsyncOpenFileQueueLock);

  AcquireLock(&gAsyncOpenFileQueueLock);
  InsertTailList(&AsyncOpenFileExecuteListHead, &FileIoOpenFileEntity->ListEntry);
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // Async OpenEx Call---Open Dir
  //
  OldTpl = gtBS->RaiseTPL (FileIoOpenDirEntity->Tpl);
  
  Status = Root->OpenEx (
                   Root,
                   &FileIoOpenDirEntity->FileIo,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   DirAttribute,
                   &FileIoOpenDirEntity->FileIoToken
                   );
  
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    AcquireLock(&gAsyncOpenFileQueueLock);
    RemoveEntryList(&FileIoOpenDirEntity->ListEntry);
    InsertTailList(&AsyncOpenDirFailListHead, &FileIoOpenDirEntity->ListEntry);    
    ReleaseLock(&gAsyncOpenFileQueueLock);
    FileIoOpenDirEntity->StatusAsync        = Status;
    return Status;
  }
  //
  // Record Execution Info to File IO Dir Entity 
  //
  FileIoOpenDirEntity->StatusAsync = Status;

  //
  // Async OpenEx Call---Open File
  //
  OldTpl = gtBS->RaiseTPL (FileIoOpenFileEntity->Tpl);
  
  Status = Root->OpenEx (
                   Root,
                   &FileIoOpenFileEntity->FileIo,
                   StrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   FileAttribute,
                   &FileIoOpenFileEntity->FileIoToken
                   );
  
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    AcquireLock(&gAsyncOpenFileQueueLock);
    RemoveEntryList(&FileIoOpenFileEntity->ListEntry);
    InsertTailList(&AsyncOpenFileFailListHead, &FileIoOpenFileEntity->ListEntry);    
    ReleaseLock(&gAsyncOpenFileQueueLock);
    FileIoOpenFileEntity->StatusAsync = Status;
    return Status;
  }
  //
  // Record Execution Info to File IO  Open File Entity 
  //
  FileIoOpenFileEntity->StatusAsync = Status;

  return Status;
}

/**
 *  @brief For OpenEx() basic test
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.12
//
EFI_STATUS
BBTestOpenExBasicTest (
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
                   &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 5.1.12.2.1  Call OpenEx() to create new files(directories)
  // with valid file names and valid attributes.
  //
  BBTestOpenExBasicTestCheckpoint1 (StandardLib, SimpleFileSystem, FALSE);

  //
  // 5.1.12.2.2  Call OpenEx() to Open existing files with all valid OpenMode.
  //
  //BBTestOpenExBasicTestCheckpoint2 (StandardLib, SimpleFileSystem, FALSE);

  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  )
{
  EFI_STATUS                Status;
  EFI_FILE_PROTOCOL         *Root = NULL;
  CHAR16                    *PureFileNameArray;
  UINT32                    Count;

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
    
    if (Root != NULL){
      Root->Close(Root);
      Root = NULL;
    }
    
    return EFI_UNSUPPORTED;
  }

  Status = ComposeFileNameArrayFileIo2 (&PureFileNameArray, &Count);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ComposeFileNameArray fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    if (Root != NULL){
      Root->Close(Root);
      Root = NULL;
    }
    
    return Status;
  }

  //
  // Test 1: one directory level
  // Source: Root
  // FileName: pure file name (no other nodes)
  //
  Status = BBTestOpenExBasicTestCheckpoint1_Test1_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = BBTestOpenExBasicTestCheckpoint1_Test1_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }


  //
  // Test 2: 2 directory levels
  // Source: Root
  // FileName: file name with directory node (subdir\filename)
  //
  Status = BBTestOpenExBasicTestCheckpoint1_Test2_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  


  Status = BBTestOpenExBasicTestCheckpoint1_Test2_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Test 3: 2 directory levels
  // Source: Sub directory
  // FileName: pure file name
  //
  Status = BBTestOpenExBasicTestCheckpoint1_Test3_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }


  Status = BBTestOpenExBasicTestCheckpoint1_Test3_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Test 4: 3 directory levels (subdir1\subdir2\filename)
  // Source: level 1 directory (subdir1)
  // FileName: file name with directory node (subdir2\filename)
  //
  Status = BBTestOpenExBasicTestCheckpoint1_Test4_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }


  Status = BBTestOpenExBasicTestCheckpoint1_Test4_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Test 5: 3 directory levels
  // Source: level 2 directory (subdir2)
  // FileName: file name with directory node (\subdir1\subdir2\filename)
  //
  Status = BBTestOpenExBasicTestCheckpoint1_Test5_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );

  Status = BBTestOpenExBasicTestCheckpoint1_Test5_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );


Done:
  if (PureFileNameArray != NULL) {
    gtBS->FreePool (PureFileNameArray);
    PureFileNameArray = NULL;
  }

  if (Root != NULL){
    Root->Close(Root);
    Root = NULL;
  }

  return Status;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test1_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  EFI_STATUS                Status;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  UINTN                     FileNameIndex;
  CHAR16                    *PureStrPointer;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;

  ListEntry    = NULL;
  FileIoEntity = NULL;

  if (IsStress) {
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  PureStrPointer = PureFileNameArray;
  
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) { 
    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++) {
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
        for (FileNameIndex = 0; FileNameIndex < 5; FileNameIndex++, PureStrPointer += MAX_STRING_LENGTH){
          Status = FileIoAsyncOpenFile(
                     Root,
                     TplArray[Index],
                     PureStrPointer,
                     ValidAttributesForCreateFileIo2[AttributesIndex]
                     );
        }
      }
    }
  }
  Print (L" ================== Async OpenEx call finshed ================== \n\n");
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    Print (L".");
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    

  //
  // clear all File IO events from gOpenFileFinishQueue 
  // gOpenFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS && FileIoEntity->StatusAsync == EFI_SUCCESS) {           
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else if((EFI_MEDIA_CHANGED == FileIoEntity->StatusAsync) ||
        (EFI_WRITE_PROTECTED == FileIoEntity->StatusAsync) || 
        (EFI_VOLUME_FULL == FileIoEntity->StatusAsync)) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_WARNING;  
          
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
       
      AcquireLock(&gAsyncOpenFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);

  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid025,
                   L"OpenEx() Basic Test - checkpoint1 ---Test1---Async",
                   L"%a:%d: Tpl - %d,Status - %r, Token Status - %r, File Name - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->FileIoToken.Status,
                   FileIoEntity->Name
                   );
    
    if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // If OpenFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while(!IsListEmpty(&AsyncOpenFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid026,
                   L"OpenEx() Basic Test - checkpoint1 ---Test1--Async",
                   L"%a:%d: Tpl - %d,Status - %r, File Name - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->Name
                   );
    //
    // Delete FileHandle
    //
    if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
       
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // If OpenFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid027,
                     L"OpenEx() Basic Test - checkpoint1 ----Test1----Async",
                     L"%a:%d: FileIoEntity->Tpl, Status - %r, File Name - %",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test1_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  EFI_STATUS                Status;
  UINTN                     Index;
  CHAR16                    *PureStrPointer;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_TPL                   OldTpl; 
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  if (IsStress) {
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  PureStrPointer = PureFileNameArray;
  
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) { 
    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++, PureStrPointer += MAX_STRING_LENGTH) {
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
        //
        // Async OpenEx Call
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        FileHandle = NULL;
        Status = Root->OpenEx (
                         Root,
                         &FileHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreateFileIo2[AttributesIndex],
                         &FileIoTokenSync
                         );
        gtBS->RestoreTPL (OldTpl);
        //
        // Check & record  status 
        //
        if (Status == EFI_SUCCESS) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else if ((EFI_MEDIA_CHANGED == Status) ||
          (EFI_WRITE_PROTECTED == Status) ||
          (EFI_VOLUME_FULL == Status)) {
          AssertionType = EFI_TEST_ASSERTION_WARNING;  
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid028,
                       L"OpenEx() Basic Test - checkpoint1 ---Test1---Sync",
                       L"%a:%d: Tpl - %d, Status - %r, FileName - %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       Status,
                       PureStrPointer
                       );

        if (FileHandle != NULL) {         
          FileHandle->Delete (FileHandle);
        }
      }
    }
  }

  return EFI_SUCCESS;
}

        
EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test2_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  UINT32                    DirAttributesIndex;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  CHAR16                    *FileNameArray, *StrPointer, *PureStrPointer;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  UINTN                     FileNameIndex;
  UINTN                     FileNameLength;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  UINT32                    MaxFileName;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoOpenFileEntity;
  FileIoOpenFile_Task       *FileIoOpenDirEntity;

  ListEntry            = NULL;
  FileIoOpenFileEntity = NULL;
  FileIoOpenDirEntity  = NULL;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  
  gtBS->SetMem (FileNameArray, ArraySize * sizeof (CHAR16), 0);

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  
  MaxFileName = FixedNameCount + TPL_ARRAY_SIZE + MaxNameIndex + MaxDirAttributesIndex + MaxAttributesIndex;
  
  for (Loop = 0; Loop < MaxFileName; Loop++) {
    
    EfiStrCpy (StrPointer, PureStrPointer);
    FileNameLength = EfiStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    EfiStrCat (StrPointer, PureStrPointer);

    PureStrPointer += MAX_STRING_LENGTH;
    StrPointer += MAX_STRING_LENGTH;
  }
  
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
            DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {
         
        AttributesIndex = DirAttributesIndex - VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
        
        for (FileNameIndex = 0; FileNameIndex < 5; FileNameIndex++, StrPointer += MAX_STRING_LENGTH, PureStrPointer += MAX_STRING_LENGTH){

          Status = FileIoAsyncOpenDir(
                     Root,
                     TplArray[Index],
                     PureStrPointer,
                     StrPointer,
                     ValidAttributesForCreateFileIo2[DirAttributesIndex],
                     ValidAttributesForCreateFileIo2[AttributesIndex]
                     );
        }
      }
    }
  }
  Print (L" ================== Async OpenEx call finshed ================== \n\n");
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
        
  AcquireLock(&gAsyncOpenFileQueueLock);
  
  while (!IsListEmpty(&AsyncOpenFileExecuteListHead) 
         && !IsListEmpty(&AsyncOpenDirExecuteListHead) 
         && IndexI < 120) {
    ReleaseLock(&gAsyncOpenFileQueueLock);
        
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    Print (L".");
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
    
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    
  
  //
  // clear all File IO events from gOpenDirFinishQueue 
  // gOpenDirQueue is handled first since we use File IO openex to do open dir. 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenDirFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenDirFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenDirFinishListHead, ListEntry)) {
      FileIoOpenDirEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoOpenDirEntity->FileIoToken.Status == EFI_SUCCESS &&
        FileIoOpenDirEntity->StatusAsync == EFI_SUCCESS) {
        FileIoOpenDirEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else if((EFI_MEDIA_CHANGED == FileIoOpenDirEntity->StatusAsync) ||
         (EFI_WRITE_PROTECTED == FileIoOpenDirEntity->StatusAsync) ||
         (EFI_VOLUME_FULL == FileIoOpenDirEntity->StatusAsync)) {
        FileIoOpenDirEntity->AssertionType = EFI_TEST_ASSERTION_WARNING;  
      } else {
        FileIoOpenDirEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
         
      AcquireLock(&gAsyncOpenFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenDirFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // clear all File IO events from gOpenFileFinishQueue 
  // gOpenDirQueue is handled first since we use File IO openex to do open dir. 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenFileFinishListHead, ListEntry)) {
      FileIoOpenFileEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);
      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoOpenFileEntity->FileIoToken.Status == EFI_SUCCESS &&
        FileIoOpenFileEntity->StatusAsync == EFI_SUCCESS) {
        FileIoOpenFileEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else if((EFI_MEDIA_CHANGED == FileIoOpenFileEntity->StatusAsync) ||
        (EFI_WRITE_PROTECTED == FileIoOpenFileEntity->StatusAsync) ||
        (EFI_VOLUME_FULL == FileIoOpenFileEntity->StatusAsync)) {
        FileIoOpenFileEntity->AssertionType = EFI_TEST_ASSERTION_WARNING; 
      } else {
        FileIoOpenFileEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
         
      AcquireLock(&gAsyncOpenFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // Record All Finished Open File case results
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    FileIoOpenFileEntity = CR(AsyncOpenFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoOpenFileEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoOpenFileEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid030,
                   L"OpenEx() Basic Test - checkpoint1 ---Test2---Async---Open File",
                   L"%a:%d:Tpl - %d, create file Status - %r, Token Status - %r, file name - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoOpenFileEntity->Tpl,
                   FileIoOpenFileEntity->StatusAsync,
                   FileIoOpenFileEntity->FileIoToken.Status,
                   FileIoOpenFileEntity->Name
                   );
        
    if (FileIoOpenFileEntity->FileIo != NULL) {         
      FileIoOpenFileEntity->FileIo->Delete (FileIoOpenFileEntity->FileIo);
      FileIoOpenFileEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoOpenFileEntity->FileIoToken.Event);
    
    if (FileIoOpenFileEntity != NULL) {
      gtBS->FreePool(FileIoOpenFileEntity);
      FileIoOpenFileEntity = NULL;
    }
    
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);

  //
  // Record All Finished Open Dir case results
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenDirFinishListHead)) {
    FileIoOpenDirEntity = CR(AsyncOpenDirFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoOpenDirEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
     
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoOpenDirEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid029,
                   L"OpenEx() Basic Test - checkpoint1 ---Test2---Async---Open Dir",
                   L"%a:%d:Tpl -  %d, create directory Status - %r, Token Status - %r, dir name - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoOpenDirEntity->Tpl,
                   FileIoOpenDirEntity->StatusAsync,
                   FileIoOpenDirEntity->FileIoToken.Status,
                   FileIoOpenDirEntity->Name
                   );

    if (FileIoOpenDirEntity->FileIo != NULL) {         
      FileIoOpenDirEntity->FileIo->Delete (FileIoOpenDirEntity->FileIo);
      FileIoOpenDirEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoOpenDirEntity->FileIoToken.Event);
    
    if (FileIoOpenDirEntity != NULL) {
      gtBS->FreePool(FileIoOpenDirEntity); 
      FileIoOpenDirEntity = NULL;
    }
    
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // If OpenFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while(!IsListEmpty(&AsyncOpenFileFailListHead)) {
    FileIoOpenFileEntity = CR(AsyncOpenFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoOpenFileEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
        
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid032,
                   L"OpenEx() Basic Test - checkpoint1 ---Test2---Async ---Open File",
                   L"%a:%d:Tpl - %d, create file Status - %r, file name - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoOpenFileEntity->Tpl,
                   FileIoOpenFileEntity->StatusAsync,
                   FileIoOpenFileEntity->Name
                   );

    gtBS->CloseEvent(FileIoOpenFileEntity->FileIoToken.Event);

    if (FileIoOpenFileEntity != NULL) {
      gtBS->FreePool(FileIoOpenFileEntity);
      FileIoOpenFileEntity = NULL;
    }    
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // If OpenDirFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while(!IsListEmpty(&AsyncOpenDirFailListHead)) {
    FileIoOpenDirEntity = CR(AsyncOpenDirFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoOpenDirEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
        
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid031,
                   L"OpenEx() Basic Test - checkpoint1 ---Test2---Async---Open Dir",
                   L"%a:%d:Tpl -  %d, create directory Status - %r, dir name - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoOpenDirEntity->Tpl,
                   FileIoOpenDirEntity->StatusAsync,
                   FileIoOpenDirEntity->Name
                   );

    gtBS->CloseEvent(FileIoOpenDirEntity->FileIoToken.Event);
    
    if (FileIoOpenDirEntity){
      gtBS->FreePool(FileIoOpenDirEntity);
      FileIoOpenDirEntity = NULL;
    }    
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
    
  //
  // If OpenFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenFileExecuteListHead, ListEntry)) {
      FileIoOpenFileEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid034,
                     L"OpenEx() Basic Test - checkpoint1 ---Test2---Async --- Open File",
                     L"%a:%d:Tpl - %d, create file Status - %r, file name - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoOpenFileEntity->Tpl,
                     FileIoOpenFileEntity->StatusAsync,
                     FileIoOpenFileEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  //
  // If OpenDirExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenDirExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenDirExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenDirExecuteListHead, ListEntry)) {
      FileIoOpenDirEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid033,
                     L"OpenEx() Basic Test - checkpoint1 ---Test2---Async ---Open Dir",
                     L"%a:%d:Tpl -  %d, create directory Status - %r, dir name - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoOpenDirEntity->Tpl,
                     FileIoOpenDirEntity->StatusAsync,
                     FileIoOpenDirEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenDirExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);

  if (FileNameArray){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test2_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_PROTOCOL         *DirHandle;
  UINT32                    DirAttributesIndex;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  CHAR16                    *FileNameArray, *StrPointer, *PureStrPointer;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     FileNameLength;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  UINT32                    MaxFileName;
  EFI_FILE_IO_TOKEN         FileIoFileTokenSync;
  EFI_FILE_IO_TOKEN         FileIoDirTokenSync;

  //
  // Sync Token Init
  //
  FileIoFileTokenSync.Event      = NULL;
  FileIoFileTokenSync.Status     = EFI_NOT_READY;
  FileIoDirTokenSync.Event       = NULL;
  FileIoDirTokenSync.Status      = EFI_NOT_READY;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  gtBS->SetMem (FileNameArray, ArraySize * sizeof (CHAR16), 0);

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;

  MaxFileName = FixedNameCount + TPL_ARRAY_SIZE + MaxNameIndex + MaxDirAttributesIndex + MaxAttributesIndex;
  for (Loop = 0; Loop < MaxFileName; Loop++) {
    EfiStrCpy (StrPointer, PureStrPointer);
    FileNameLength = EfiStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    EfiStrCat (StrPointer, PureStrPointer);

    PureStrPointer += MAX_STRING_LENGTH;
    StrPointer += MAX_STRING_LENGTH;
  }
  
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (NameIndex = 0; NameIndex < MaxNameIndex;
         StrPointer += MAX_STRING_LENGTH, PureStrPointer += MAX_STRING_LENGTH, NameIndex++) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
            DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {
        AttributesIndex = DirAttributesIndex - VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;

        DirHandle = NULL;

        //
        // create sub directory first
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);

        Status = Root->OpenEx (
                         Root,
                         &DirHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreateFileIo2[DirAttributesIndex],
                         &FileIoDirTokenSync
                         );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid035,
                       L"OpenEx() Basic Test - checkpoint1---Test2---Sync Create Dir",
                       L"%a:%d: create directory Status - %r, dir name - %s,Tpl - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       PureStrPointer,
                       TplArray[Index]
                      );

        if (EFI_ERROR (Status)) {
          goto Done;
        }
        //
        // create file under the created directory
        //
        FileHandle = NULL;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = Root->OpenEx (
                         Root,
                         &FileHandle,
                         StrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreateFileIo2[AttributesIndex],
                         &FileIoFileTokenSync
                         );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }


        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid036,
                       L"Open() Basic Test - checkpoint1 ---Test2--Sync Open File",
                       L"%a:%d: create file Status - %r, FileName - %s, Tpl - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       StrPointer,
                       TplArray[Index]
                      );

        if (FileHandle != NULL) {
          FileHandle->Delete (FileHandle);
          FileHandle = NULL;
        } 

        if (DirHandle != NULL) {
          Status = DirHandle->Delete (DirHandle);
          DirHandle = NULL;
        }
        
        if (EFI_ERROR (Status)) {
          goto Done;
        }
      }
    }
  }

Done:
  if (FileNameArray){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test3_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE_PROTOCOL         *DirHandle;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  EFI_STATUS                Status;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  UINTN                     FileNameIndex;
  CHAR16                    *PureStrPointer;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;

  ListEntry    = NULL;
  FileIoEntity = NULL;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  PureStrPointer = PureFileNameArray;

  DirHandle = NULL;
  
  //
  // create sub directory first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint1---Test3 --Async---Open Dir ",
                 L"%a:%d: create directory Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                );
  
  if (EFI_ERROR (Status)) {
    if (Root != NULL){
      Root->Close(Root);
      Root = NULL;
    }
    return Status;
  }
   
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {

      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;AttributesIndex++) {
              
        for (FileNameIndex = 0;FileNameIndex < 5;FileNameIndex++,PureStrPointer += MAX_STRING_LENGTH){

          Status = FileIoAsyncOpenFile(
                     DirHandle,
                     TplArray[Index],
                     PureStrPointer,
                     ValidAttributesForCreateFileIo2[AttributesIndex]
                     );
        }
      }
    } 
  }   
  Print (L" ================== Async OpenEx call finshed ================== \n\n");
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    Print (L".");
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    
 
  //
  // clear all File IO events from gOpenFileFinishQueue 
  // gOpenFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
          && FileIoEntity->StatusAsync == EFI_SUCCESS) {
          
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else if ((EFI_MEDIA_CHANGED == FileIoEntity->StatusAsync)
                 || (EFI_WRITE_PROTECTED == FileIoEntity->StatusAsync)
                 || (EFI_VOLUME_FULL == FileIoEntity->StatusAsync)) {
  
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_WARNING;  
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      AcquireLock(&gAsyncOpenFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid037,
                   L"OpenEx() Basic Test - checkpoint1 ---Async ----Test3----Open File ",
                   L"%a:%d: Tpl - %d, Status - %r, Token Status - %r, FileName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->FileIoToken.Status,
                   FileIoEntity->Name
                   );
    
    if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    
    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
    
    
  //
  // If OpenFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while(!IsListEmpty(&AsyncOpenFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid038,
                   L"OpenEx() Basic Test - checkpoint1 ---Async----Test3",
                   L"%a:%d: Tpl - %d, Status - %r, FileName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->Name
                   );

     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

     if (FileIoEntity != NULL){
       gtBS->FreePool(FileIoEntity);
       FileIoEntity = NULL;
     }
       
     AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
      
    
  //
  // If OpenFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid039,
                     L"OpenEx() Basic Test - checkpoint1 ---Async",
                     L"%a:%d: FileIoEntity->Tpl,Status - %r,FileName - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  if (DirHandle != NULL) {
    Status = DirHandle->Delete (DirHandle);
    DirHandle = NULL;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test3_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_PROTOCOL         *DirHandle;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    FileNameIndex;
  EFI_STATUS                Status;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  CHAR16                    *PureStrPointer;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  PureStrPointer = PureFileNameArray;

  DirHandle = NULL;
  
  //
  // create sub directory first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint1---Test3---Sync Open Dir",
                 L"%a:%d: create directory Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                );
  
  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {

      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;AttributesIndex++) {
              
        for (FileNameIndex = 0;FileNameIndex < 5;FileNameIndex++,PureStrPointer += MAX_STRING_LENGTH){
          //
          // create file under the created directory
          // source is DirHandle
          //
          FileHandle = NULL;

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = DirHandle->OpenEx (
                                DirHandle,
                                &FileHandle,
                                PureStrPointer,
                                EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                ValidAttributesForCreateFileIo2[AttributesIndex],
                                &FileIoTokenSync                                
                                );
          gtBS->RestoreTPL (OldTpl);

          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;

          } else if ((EFI_MEDIA_CHANGED == Status)
                    || (EFI_WRITE_PROTECTED == Status)
                    || (EFI_VOLUME_FULL == Status)) {

            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gSimpleFileSystemExBBTestFunctionAssertionGuid040,
                         L"OpenEx() Basic Test - checkpoint1---Test3---Sync ---Open File",
                         L"%a:%d: create file Status - %r, FileName - %s,Tpl - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         PureStrPointer,
                         TplArray[Index]
                         );

          if (FileHandle != NULL) {
            FileHandle->Delete (FileHandle);
          }
        }
      }
    }
  }

  if (DirHandle != NULL) {
    Status = DirHandle->Delete (DirHandle);
    DirHandle = NULL;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test4_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE_PROTOCOL         *DirHandle1;
  EFI_FILE_PROTOCOL         *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    FileNameIndex;
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     FileNameLength;
  CHAR16                    *StrPointer, *PureStrPointer,*PureStrPointer1;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;

  FileIoEntity = NULL;
  ListEntry    = NULL;  

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  
  for (Loop = 0; Loop < 10; Loop++) {
    EfiStrCpy (StrPointer, PureStrPointer);
    FileNameLength = EfiStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);
    StrPointer += MAX_STRING_LENGTH;
  }
  
  DirHandle1 = NULL;
  DirHandle2 = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle1,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint1 -- Test4 -- Async---Open Dir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  
  //
  // create sub directory 2
  //
  Status = DirHandle1->Open (
                         DirHandle1,
                         &DirHandle2,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         EFI_FILE_DIRECTORY
                         );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint1 -- Test4 -- Async---Open Dir",
                 L"%a:%d: create directory 2 Status - %r, dirname - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                );
  if (EFI_ERROR (Status)) {
    if (DirHandle1 != NULL) {
       DirHandle1->Delete (DirHandle1);
       DirHandle1 = NULL;
    }

    if (FileNameArray){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
  }
   
  StrPointer = FileNameArray;
   
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++) {

      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;AttributesIndex++) {

        for (FileNameIndex = 0;FileNameIndex < 5; StrPointer += MAX_STRING_LENGTH,FileNameIndex++){

          Status = FileIoAsyncOpenFile(
                     DirHandle1,
                     TplArray[Index],
                     StrPointer,
                     ValidAttributesForCreateFileIo2[AttributesIndex]
                     );
        }
      }
    }
  }
  
  Print (L" ================== Async OpenEx call finshed ================== \n\n");
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
    
    Print (L".");
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    
    
  //
  // clear all File IO events from gOpenFileFinishQueue 
  // gOpenFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);
      
      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
          && FileIoEntity->StatusAsync == EFI_SUCCESS) {
          
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else if ((EFI_MEDIA_CHANGED == FileIoEntity->StatusAsync)
                || (EFI_WRITE_PROTECTED == FileIoEntity->StatusAsync)
                || (EFI_VOLUME_FULL == FileIoEntity->StatusAsync)) {
    
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_WARNING;  
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      AcquireLock(&gAsyncOpenFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
    
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid041,
                   L"OpenEx() Basic Test - checkpoint1 ---Test4 ---- Async --- Open File",
                   L"%a:%d: Tpl - %d, Status - %r, Token Status - %r, FileName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->FileIoToken.Status,
                   FileIoEntity->Name
                   );
    
    if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
      
      
  //
  // If OpenFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while(!IsListEmpty(&AsyncOpenFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid042,
                   L"OpenEx() Basic Test - checkpoint1 ---Async----Test4 ----Open File",
                   L"%a:%d: Tpl - %d,Status - %r,FileName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->Name
                   );
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
     gtBS->FreePool(FileIoEntity);
       
     AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
        
      
  //
  // If OpenFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid043,
                     L"OpenEx() Basic Test - checkpoint1 ---Async -- Test4----Open File",
                     L"%a:%d: FileIoEntity->Tpl,Status - %r,FileName - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
    
  if (DirHandle2 != NULL) {
    Status = DirHandle2->Delete (DirHandle2);
    DirHandle2 = NULL;
  }
  if (DirHandle1 != NULL) {
    Status = DirHandle1->Delete (DirHandle1);
    DirHandle1 = NULL;
  }

  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  return EFI_SUCCESS;
}
        
        
EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test4_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_PROTOCOL         *DirHandle1;
  EFI_FILE_PROTOCOL         *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    FileNameIndex;
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     FileNameLength;
  CHAR16                    *StrPointer, *PureStrPointer, *PureStrPointer1;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;
  
  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  
  for (Loop = 0; Loop < 10; Loop++) {
    EfiStrCpy (StrPointer, PureStrPointer);
    FileNameLength = EfiStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);
    StrPointer += MAX_STRING_LENGTH;
  }
  
  DirHandle1 = NULL;
  DirHandle2 = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle1,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint1 -- Test4 -- Sync -- Open Dir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    if (FileNameArray){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
  }
  
  //
  // create sub directory 2
  //
  Status = DirHandle1->Open (
                         DirHandle1,
                         &DirHandle2,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         EFI_FILE_DIRECTORY
                         );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint1 -- Test4 -- Sync -- Open Dir",
                 L"%a:%d: create directory 2 Status - %r, dirname - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                );
  if (EFI_ERROR (Status)) {
    if (DirHandle1 != NULL) {
       Status = DirHandle1->Delete (DirHandle1);
       DirHandle1 = NULL;
    }

    if (FileNameArray != NULL){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
  }
  
  StrPointer = FileNameArray;
   
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++) {

      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
	  	
        for (FileNameIndex = 0;FileNameIndex < 5; StrPointer += MAX_STRING_LENGTH,FileNameIndex++){
          //
          // create file under the created directory
          //
          FileHandle = NULL;

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = DirHandle1->OpenEx (
                                 DirHandle1,
                                 &FileHandle,
                                 StrPointer,
                                 EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                 ValidAttributesForCreateFileIo2[AttributesIndex],
                                 &FileIoTokenSync
                                 );
          gtBS->RestoreTPL (OldTpl);

          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;

          } else if ((EFI_MEDIA_CHANGED == Status)
                    || (EFI_WRITE_PROTECTED == Status)
                    || (EFI_VOLUME_FULL == Status)) {

            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          StandardLib->RecordAssertion (
                        StandardLib,
                        AssertionType,
                        gSimpleFileSystemExBBTestFunctionAssertionGuid044,
                        L"OpenEx() Basic Test - checkpoint1---Test4 --- Sync",
                        L"%a:%d: create file Status - %r, FileName - %s, Tpl - %d",
                        __FILE__,
                        (UINTN)__LINE__,
                        Status,
                        StrPointer,
                        TplArray[Index]
                        );

          if (FileHandle != NULL) {
            FileHandle->Delete (FileHandle);
          } 
        }
      }
    } 
  }

  if (DirHandle2 != NULL) {
    Status = DirHandle2->Delete (DirHandle2);
    DirHandle2 = NULL;
  }
  if (DirHandle1 != NULL) {
    Status = DirHandle1->Delete (DirHandle1);
    DirHandle1 = NULL;
  }

  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test5_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE_PROTOCOL         *DirHandle1;
  EFI_FILE_PROTOCOL         *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    FileNameIndex;
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     FileNameLength;
  CHAR16                    *StrPointer, *PureStrPointer, *PureStrPointer1 ;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;

  ListEntry    = NULL;
  FileIoEntity = NULL;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }

  //
  // prepare file name "\" + subdir1 + "\" + subdir2 + "\" + filename
  //
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  for (Loop = 0; Loop < 10; Loop++) {

    //
    // "\"
    //
    StrPointer[0] = '\\';
    StrPointer[1] = 0;

    //
    // "\" + subdir1
    //
    EfiStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\"
    //
    FileNameLength = EfiStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2
    //
    EfiStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\" + subdir2 + "\"
    //
    FileNameLength = EfiStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2 + "\" + filename
    //
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);

    StrPointer += MAX_STRING_LENGTH;
    
  }
  
  DirHandle1 = NULL;
  DirHandle2 = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle1,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );

  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"Open() Basic Test - checkpoint1 -- Test5 -- Async -- Open Dir",
                 L"%a:%d: create directory 1 Status - %r, DirName - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    
    if (FileNameArray != NULL){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
  }
  
  //
  // create sub directory 2
  //
  Status = DirHandle1->Open (
                         DirHandle1,
                         &DirHandle2,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         EFI_FILE_DIRECTORY
                         );

  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint1 -- Test5 -- Async --- Open Dir",
                 L"%a:%d: create directory 2 Status - %r, DirName - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  if (EFI_ERROR (Status)) {
    if (DirHandle1 != NULL){
      DirHandle1->Delete (DirHandle1);
      DirHandle1 = NULL;
    }
    if (FileNameArray){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
  }

  StrPointer = FileNameArray;
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;AttributesIndex++) {
        for (FileNameIndex = 0;FileNameIndex < 5;StrPointer += MAX_STRING_LENGTH, FileNameIndex++){
          Status = FileIoAsyncOpenFile(
                     DirHandle2,
                     TplArray[Index],
                     StrPointer,
                     ValidAttributesForCreateFileIo2[AttributesIndex]
                     );
        }
      }
    }    
  }      
  Print (L" ================== Async OpenEx call finshed ================== \n\n");
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
    
    Print (L".");
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    
    
  //
  // clear all File IO events from gOpenFileFinishQueue 
  // gOpenFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
          && FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else if((EFI_MEDIA_CHANGED == FileIoEntity->StatusAsync)
                || (EFI_WRITE_PROTECTED == FileIoEntity->StatusAsync)
                || (EFI_VOLUME_FULL == FileIoEntity->StatusAsync)) {
    
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_WARNING;  
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      AcquireLock(&gAsyncOpenFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
    
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while (!IsListEmpty(&AsyncOpenFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid045,
                   L"OpenEx() Basic Test - checkpoint1 ---Test5 ---- Async---Open File",
                   L"%a:%d: Tpl - %d, Status - %r, Token Status - %r, FileName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->FileIoToken.Status,
                   FileIoEntity->Name
                   );
    
    if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL) {
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
    AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
      
      
  //
  // If OpenFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  while(!IsListEmpty(&AsyncOpenFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid046,
                   L"OpenEx() Basic Test - checkpoint1 ---Async----Test5---Open File",
                   L"%a:%d: Tpl - %d,Status - %r,FileName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->Name
                   );

    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }

     AcquireLock(&gAsyncOpenFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);
        
      
  //
  // If OpenFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenFileQueueLock);
  if (!IsListEmpty(&AsyncOpenFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid047,
                     L"OpenEx() Basic Test - checkpoint1 ---Async -- Test5---Open File",
                     L"%a:%d: FileIoEntity->Tpl,Status - %r,FileName - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenFileQueueLock);

  if (DirHandle2 != NULL) {
    Status = DirHandle2->Delete (DirHandle2);
    DirHandle2 = NULL;
  }

  if (DirHandle1 != NULL) {
    Status = DirHandle1->Delete (DirHandle1);
    DirHandle1 = NULL;
  }

  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray= NULL;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestOpenExBasicTestCheckpoint1_Test5_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_PROTOCOL         *DirHandle1;
  EFI_FILE_PROTOCOL         *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    FileNameIndex; 
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     FileNameLength;
  CHAR16                    *StrPointer, *PureStrPointer, *PureStrPointer1;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;
  
  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  
  //
  // prepare file name "\" + subdir1 + "\" + subdir2 + "\" + filename
  //
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  for (Loop = 0; Loop < 5; Loop++) {

    //
    // "\"
    //
    StrPointer[0] = '\\';
    StrPointer[1] = 0;

    //
    // "\" + subdir1
    //
    EfiStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\"
    //
    FileNameLength = EfiStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2
    //
    EfiStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\" + subdir2 + "\"
    //
    FileNameLength = EfiStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2 + "\" + filename
    //
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);

    StrPointer += MAX_STRING_LENGTH;
    
  }
  
  DirHandle1 = NULL;
  DirHandle2 = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle1,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );

  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"Open() Basic Test - checkpoint1 -- Test5 -- Sync---Open Dir",
                 L"%a:%d: create directory 1 Status - %r, DirName - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    if (FileNameArray != NULL){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
  }
  
  //
  // create sub directory 2
  //
  Status = DirHandle1->Open (
                         DirHandle1,
                         &DirHandle2,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         EFI_FILE_DIRECTORY
                         );

  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint1 -- Test5 -- Sync ---Open Dir",
                 L"%a:%d: create directory 2 Status - %r, DirName - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  if (EFI_ERROR (Status)) {
    if (DirHandle1 != NULL){
      DirHandle1->Delete (DirHandle1);
      DirHandle1 = NULL;
    }
    if (FileNameArray != NULL){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
  }
  
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    StrPointer = FileNameArray;
    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) { 
      
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;
            AttributesIndex++) {
        for (FileNameIndex = 0;FileNameIndex <5; StrPointer += MAX_STRING_LENGTH, FileNameIndex++){
          //
          // create file under the created directory
          //
          FileHandle = NULL;
          
          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = DirHandle2->OpenEx (
                                 DirHandle2,
                                 &FileHandle,
                                 StrPointer,
                                 EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                 ValidAttributesForCreateFileIo2[AttributesIndex],
                                 &FileIoTokenSync
                                 );
          gtBS->RestoreTPL (OldTpl);
          
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          
          } else if ((EFI_MEDIA_CHANGED == Status)
                    || (EFI_WRITE_PROTECTED == Status)
                    || (EFI_VOLUME_FULL == Status)) {
          
            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gSimpleFileSystemExBBTestFunctionAssertionGuid048,
                         L"OpenEx() Basic Test - checkpoint1 -- Test5 -- Sync---Open File",
                         L"%a:%d: create file Status - %r, FileName - %s, Tpl - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         StrPointer,
                         TplArray[Index]
                         );
          
          
          if (FileHandle != NULL){
            FileHandle->Delete (FileHandle);    
          }
        }  
      }
    }
  }
  if (DirHandle2 != NULL) {
    Status = DirHandle2->Delete (DirHandle2);
    DirHandle2 = NULL;
  }

  if (DirHandle1 != NULL) {
    Status = DirHandle1->Delete (DirHandle1);
    DirHandle1 = NULL;
  }

  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }

  return EFI_SUCCESS;
}

//
//Async OpenExisting File NotifyFunc
//
VOID
EFIAPI FileIoOpenExistingFileNotifyFunc  (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIoOpenFile_Task    *FileIoEntity;
  
  FileIoEntity = (FileIoOpenFile_Task *)Context;

  //
  // Remove entity from OpenExistingFileExecuteListHead &  add entity to OpenExistingFileFinishListHead
  // All FileIoOpenExistingFile Notify function run at Call Back level only once, So no locks required
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  RemoveEntryList(&FileIoEntity->ListEntry);
  InsertTailList(&AsyncOpenExistingFileFinishListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
}

/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.OpenEx() function abstraction interface
 *  @param Root  a pointer to File Io to be tested.
 *  @param Tpl the Tpl level
 *  @param PureStrPointer point to the filename
 *  @param Attribute the file attribute
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncOpenExistingFile (
  IN EFI_FILE_PROTOCOL                 *Root,
  IN EFI_TPL                           Tpl,
  IN CHAR16                            *PureStrPointer,
  IN UINT64                            Attribute,
  IN UINT64                            OpenMode
)
{
  
  EFI_STATUS                         Status;
  FileIoOpenFile_Task                *FileIoEntity = NULL;
  EFI_TPL                            OldTpl;

  ASSERT(Root != NULL);
  //
  // Allocate memory for one FileIoOpenFileEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoOpenFile_Task), 
                   &FileIoEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gtBS->SetMem (FileIoEntity, sizeof(FileIoOpenFile_Task), 0x0);
  
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   FileIoOpenExistingFileNotifyFunc ,
                   FileIoEntity,
                   &FileIoEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
    return Status;
  }

  FileIoEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoEntity->Tpl                    = Tpl;
  FileIoEntity->FileIoToken.Status     = EFI_NOT_READY;
  FileIoEntity->Name                   = PureStrPointer;
  FileIoEntity->OpenMode               = OpenMode;

  
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  InsertTailList(&AsyncOpenExistingFileExecuteListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  //
  // Async OpenEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  
  Status = Root->OpenEx (
             Root,
             &FileIoEntity->FileIo,
             PureStrPointer,
             OpenMode,
             Attribute,
             &FileIoEntity->FileIoToken
             );
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
    RemoveEntryList(&FileIoEntity->ListEntry);
    InsertTailList(&AsyncOpenExistingFileFailListHead, &FileIoEntity->ListEntry);    
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return Status;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  )
{
  EFI_STATUS                Status;
  EFI_FILE_PROTOCOL         *Root = NULL;
  CHAR16                    *PureFileNameArray;
  UINT32                    Count;

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
  // compose pure file name array
  //
  Status = ComposeFileNameArrayFileIo2 (&PureFileNameArray, &Count);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ComposeFileNameArray fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
    return Status;
  }

  //
  // Test 1: one directory level
  // Source: Root
  // FileName: pure file name (no other nodes)
  //
  Status = BBTestOpenExBasicTestCheckpoint2_Test1_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = BBTestOpenExBasicTestCheckpoint2_Test1_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Test 2: 2 directory levels
  // Source: Root
  // FileName: file name with directory node (subdir\filename)
  //
  Status = BBTestOpenExBasicTestCheckpoint2_Test2_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  
  Status = BBTestOpenExBasicTestCheckpoint2_Test2_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }


  //
  // Test 3: 2 directory levels
  // Source: Sub directory
  // FileName: pure file name
  //
  Status = BBTestOpenExBasicTestCheckpoint2_Test3_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }


  Status = BBTestOpenExBasicTestCheckpoint2_Test3_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }


  //
  // Test 4: 3 directory levels (subdir1\subdir2\filename)
  // Source: level 1 directory (subdir1)
  // FileName: file name with directory node (subdir2\filename)
  //
  Status = BBTestOpenExBasicTestCheckpoint2_Test4_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = BBTestOpenExBasicTestCheckpoint2_Test4_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Test 5: 3 directory levels
  // Source: level 2 directory (subdir2)
  // FileName: file name with directory node (\subdir1\subdir2\filename)
  //
  Status = BBTestOpenExBasicTestCheckpoint2_Test5_Async (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }


  Status = BBTestOpenExBasicTestCheckpoint2_Test5_Sync (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

Done:
  if (PureFileNameArray != NULL) {
    gtBS->FreePool (PureFileNameArray);
    PureFileNameArray = NULL;
  }

  if (Root != NULL){
    Root->Close(Root);
    Root = NULL;
  }

  return Status;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test1_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;

  ListEntry    = NULL;
  FileIoEntity = NULL;

  if (IsStress) {
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  PureStrPointer = PureFileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++) {

      //
      // create file only (do not create directory)
      //
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {

        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, PureStrPointer += MAX_STRING_LENGTH) {
 
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"Allocate Pool fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL) {
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
            return Status;
          } 

          gtBS->SetMem (CreateFileEntity, sizeof(FileIoOpenFile_Task), 0x0);
		  
          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          CreateFileEntity->Name               = PureStrPointer; 
          CreateFileEntity->Tpl                = TplArray[Index];
          CreateFileEntity->OpenMode           = OpenMode[OpenIndex];
          
          Status = Root->OpenEx (
                           Root,
                           &CreateFileEntity->FileIo,
                           PureStrPointer,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                           ValidAttributesForCreateFileIo2[AttributesIndex],
                           &CreateFileEntity->FileIoToken
                           );
          
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
		  
            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }

		  //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);

          //
          // enlarge file size
          //
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }

            return Status;
          }

          FileInfo->FileSize = 1;

          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
			
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }

			return Status;
          }

          if (FileInfo != NULL){
            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  Print (L" ================ Start to do Async OpenFile call ================ \n\n");

  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    FileIoAsyncOpenExistingFile (
      Root,
      FileIoEntity->Tpl,
      FileIoEntity->Name,
      0,
      FileIoEntity->OpenMode
      ); 
    
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  Print (L" ================== Async OpenExisting File call finshed ================== \n\n"); 
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
    
    Print (L".");
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");     
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
          && FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)&& (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {      
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      }else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid049,
                   L"OpenEx() Basic Test - checkpoint2 ---Test1 ---- Async -- Open File",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );

    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
      Root->Open (
              Root,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
    } else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  //
  // If OpenExistingFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while(!IsListEmpty(&AsyncOpenExistingFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid050,
                   L"OpenEx() Basic Test - checkpoint2 ---Test1 ---- Async --- Open File",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );

    Root->Open (
            Root,
            &FileIoEntity->FileIo,
            FileIoEntity->Name,
            EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
            0
            ); 
    FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;   
    }  
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
          
        
  //
  // If OpenExistingFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid051,
                     L"OpenEx() Basic Test - checkpoint2 ---Test1 ---- Async---OpenFile",
                     L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->OpenMode,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test1_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINTN                     Index;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_TPL                   OldTpl;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
 
  ListEntry    = NULL;
  FileIoEntity = NULL;

  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  if (IsStress) {
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  PureStrPointer = PureFileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {

      //
      // create file only (do not create directory)
      //
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {

        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, PureStrPointer += MAX_STRING_LENGTH) {

          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"Allocate Pool fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);		  	
            return Status;
          } 

          gtBS->SetMem (CreateFileEntity, sizeof(FileIoOpenFile_Task), 0x0);
		  
          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          CreateFileEntity->Name               = PureStrPointer; 
          CreateFileEntity->Tpl                = TplArray[Index];
          CreateFileEntity->OpenMode           = OpenMode[OpenIndex];
          
          Status = Root->OpenEx (
                           Root,
                           &CreateFileEntity->FileIo,
                           PureStrPointer,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                           ValidAttributesForCreateFileIo2[AttributesIndex],
                           &CreateFileEntity->FileIoToken
                           );
          
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }

          //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);

          //
          // enlarge file size
          //
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }

            return Status;
          }

          FileInfo->FileSize = 1;

          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }

	        return Status;
          }
		  
          if (FileInfo != NULL){
            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
   
  Print (L" ================ Start to do Sync OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {  
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Sync OpenEx Call
      //
      OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  
      Status = Root->OpenEx (
                       Root,
                       &FileIoEntity->FileIo,
                       FileIoEntity->Name,
                       FileIoEntity->OpenMode,
                       0,
                       &FileIoTokenSync
                       );
      gtBS->RestoreTPL (OldTpl);
      
      FileIoEntity->StatusAsync = Status;
      //
      // Last list node handled
      //
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&SyncCreateFileListHead,ListEntry)) {
        break;
      }
    } 
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  Print (L" ================== Sync OpenExisting File call finshed ================== \n\n");
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);  
      //
      // Check & record every File Io execution entity status 
      //
      if ( FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;	  	
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      }else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);  

  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);   
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);  
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid052,
                   L"OpenEx() Basic Test - checkpoint2 ---Test1 ---- Sync",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      Root->Open (
              Root,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
    } else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }

    AcquireLock(&gAsyncOpenExistingFileQueueLock);	
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test2_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  EFI_FILE_PROTOCOL         *DirHandle;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  UINTN                     InfoBufferSize;
  UINTN                     FileNameLength;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer,*PureStrPointer1,*StrPointer;
  CHAR16                    *FileNameArray;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxNameIndex;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;
  EFI_TEST_ASSERTION        AssertionType;

  ListEntry    = NULL;
  FileIoEntity = NULL;
  
  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }
  
  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;
  
  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;

  for (Loop = 0; Loop < 10; Loop++) {
    EfiStrCpy (StrPointer, PureStrPointer);
    FileNameLength = EfiStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);
    StrPointer += MAX_STRING_LENGTH;
  }
  
  DirHandle = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test2 -- Async  -- Open Dir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
    return Status;
  }
  
  StrPointer = FileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {
      
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
        //
        // create file only (do not create directory)
        //
        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, StrPointer += MAX_STRING_LENGTH) {
        
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (DirHandle != NULL) {
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (FileNameArray != NULL) {
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
			
            return Status;
          } 

          gtBS->SetMem (CreateFileEntity, sizeof(FileIoOpenFile_Task), 0x0);

          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          CreateFileEntity->Name               = StrPointer; 
          CreateFileEntity->Tpl                = TplArray[Index];
          CreateFileEntity->OpenMode           = OpenMode[OpenIndex];

          Status = Root->OpenEx (
                           Root,
                           &CreateFileEntity->FileIo,
                           StrPointer,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                           ValidAttributesForCreateFileIo2[AttributesIndex],
                           &CreateFileEntity->FileIoToken
                           );

          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r,DirName - %s,FileName- %s",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           PureStrPointer,
                           StrPointer
                           );
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (DirHandle != NULL) {
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (FileNameArray != NULL) {
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            if (CreateFileEntity != NULL) {
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }
		  
          //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);
		  
          //
          // enlarge file size
          //
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            if (DirHandle != NULL) {
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (FileNameArray != NULL) {
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
			return Status;
          }
        
          FileInfo->FileSize = 1;
        
          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
			
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            if (DirHandle != NULL) {
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (FileNameArray != NULL) {
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
			return Status;
          }
  
          if (FileInfo != NULL){
            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  Print (L" ================ Start to do Async OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    Status = FileIoAsyncOpenExistingFile (
                      Root,
                      FileIoEntity->Tpl,
                      FileIoEntity->Name,
                      0,
                      FileIoEntity->OpenMode
                      ); 
    
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);  
     
  Print (L" ================== Async OpenExisting File call finshed ================== \n\n");
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
    
    Print (L".");
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    
    
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
          && FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)
              && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid053,
                   L"OpenEx() Basic Test - checkpoint2 ---Test2---- Async -- Open File",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      Root->Open (
              Root,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      
    }else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
        
        
  //
  // If OpenExistingFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while(!IsListEmpty(&AsyncOpenExistingFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid054,
                   L"OpenEx() Basic Test - checkpoint2 ---Test2 ---- Async ---Open File",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
     
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

     if (FileIoEntity != NULL){
       gtBS->FreePool(FileIoEntity);
       FileIoEntity = NULL;
     }
       
     AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
          
        
  //
  // If OpenExistingFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid055,
                     L"OpenEx() Basic Test - checkpoint2 ---Test2---- Async---OpenFile",
                     L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->OpenMode,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  if (DirHandle != NULL){
    DirHandle->Delete(DirHandle);
    DirHandle = NULL;
  }

  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test2_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  EFI_FILE_PROTOCOL         *DirHandle;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     InfoBufferSize;
  UINTN                     FileNameLength;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer,*PureStrPointer1,*StrPointer;
  CHAR16                    *FileNameArray;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxNameIndex;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_TPL                   OldTpl;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;

  ListEntry    = NULL;
  FileIoEntity = NULL;
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }
  
  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;
  
  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  
  
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;

  for (Loop = 0; Loop < 10; Loop++) {
    EfiStrCpy (StrPointer, PureStrPointer);
    FileNameLength = EfiStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);
    StrPointer += MAX_STRING_LENGTH;
  }
  
  DirHandle = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test2 -- Sync---OpenDir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
	return Status;
  }
  
  StrPointer = FileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++) {
      
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
        //
        // create file only (do not create directory)
        //
        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, StrPointer += MAX_STRING_LENGTH) {
        
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
            if (DirHandle != NULL) {
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (FileNameArray != NULL) {
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
			
            return Status;
          } 

          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;                  
          CreateFileEntity->Name        = StrPointer; 
          CreateFileEntity->Tpl         = TplArray[Index];
          CreateFileEntity->OpenMode    = OpenMode[OpenIndex];
          Status = Root->OpenEx (
                           Root,
                           &CreateFileEntity->FileIo,
                           StrPointer,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                           ValidAttributesForCreateFileIo2[AttributesIndex],
                           &CreateFileEntity->FileIoToken
                           );
      
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
            if (DirHandle != NULL){
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (FileNameArray != NULL) {
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }

          //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);

          //
          // enlarge file size
          //
        
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
        
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            if (DirHandle != NULL) {
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (FileNameArray != NULL) {
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
			return Status;
          }
        
          FileInfo->FileSize = 1;
        
          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            if (DirHandle != NULL) {
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (FileNameArray != NULL) {
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
			return Status;
          }

          if (FileInfo != NULL){
            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
   
  Print (L" ================ Start to do Sync OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {      
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Sync OpenEx Call
      //
      OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  
      Status = Root->OpenEx (
                 Root,
                 &FileIoEntity->FileIo,
                 FileIoEntity->Name,
                 FileIoEntity->OpenMode,
                 0,
                 &FileIoTokenSync
                 );
      gtBS->RestoreTPL (OldTpl);
      
      FileIoEntity->StatusAsync = Status;
      //
      // Last list node handled
      //
      
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&SyncCreateFileListHead,ListEntry)) {
        break;
      }
    } 
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  Print (L" ================== Sync OpenExisting File call finshed ================== \n\n");  
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)
              && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      // Last list node handled
      //
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);     
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid056,
                   L"OpenEx() Basic Test - checkpoint2 ---Test2---- Sync --- OpenFile",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      Root->Open (
              Root,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
    } else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock); 


  if (DirHandle != NULL){
    DirHandle->Delete(DirHandle);
    DirHandle = NULL;
  }

  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test3_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  EFI_FILE_PROTOCOL         *DirHandle;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    MaxDirAttributesIndex;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_TEST_ASSERTION        AssertionType;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;

  ListEntry    = NULL;
  FileIoEntity = NULL;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }
  
  DirHandle = NULL;
  PureStrPointer = PureFileNameArray;
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test3 -- Async ---Open Dir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++) {

      //
      // create file only (do not create directory)
      //
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {

        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, PureStrPointer += MAX_STRING_LENGTH) {
 
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (DirHandle != NULL) {
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            return Status;
          }
		  
          gtBS->SetMem (CreateFileEntity, sizeof(FileIoOpenFile_Task), 0x0);

          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          CreateFileEntity->Name               = PureStrPointer; 
          CreateFileEntity->Tpl                = TplArray[Index];
          CreateFileEntity->OpenMode           = OpenMode[OpenIndex]; 
            
          Status = DirHandle->OpenEx (
                                DirHandle,
                                &CreateFileEntity->FileIo,
                                PureStrPointer,
                                EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                ValidAttributesForCreateFileIo2[AttributesIndex],
                                &CreateFileEntity->FileIoToken
                                );
          
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (DirHandle != NULL){
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }

		  //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);

          //
          // enlarge file size
          //
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }

          FileInfo->FileSize = 1;

          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }

          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  Print (L" ================ Start to do Async OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    Status = FileIoAsyncOpenExistingFile (
                    DirHandle,
                    FileIoEntity->Tpl,
                    FileIoEntity->Name,
                    0,
                    FileIoEntity->OpenMode
                    );
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);  
  Print (L" ================== Async OpenExisting File call finshed ================== \n\n"); 

  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
    
    Print (L".");
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    
    
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
          && FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)
              && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid057,
                   L"OpenEx() Basic Test - checkpoint2 ---Test3 ---- Async----OpenFile",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      DirHandle->Open (
              DirHandle,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      
    }else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  //
  // If OpenExistingFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while(!IsListEmpty(&AsyncOpenExistingFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid058,
                   L"OpenEx() Basic Test - checkpoint2 ---Test3 ---- Async----Open File",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
     
     if (FileIoEntity != NULL){
       gtBS->FreePool(FileIoEntity);
       FileIoEntity = NULL;
     }

     AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
          
  //
  // If OpenExistingFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid059,
                     L"OpenEx() Basic Test - checkpoint2 ---Test3 ---- Async",
                     L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->OpenMode,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  if (DirHandle != NULL) {
    DirHandle->Delete (DirHandle);
    DirHandle = NULL;
  }
  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test3_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  EFI_FILE_PROTOCOL         *DirHandle;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    MaxDirAttributesIndex;
  UINTN                     Index;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_TEST_ASSERTION        AssertionType;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;
  EFI_TPL                   OldTpl;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;

  ListEntry    = NULL;
  FileIoEntity = NULL;
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }
  
  DirHandle = NULL;
  PureStrPointer = PureFileNameArray;
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test3 -- Sync -- Open Dir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );

  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {

      //
      // create file only (do not create directory)
      //
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {

        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, PureStrPointer += MAX_STRING_LENGTH) {
 
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (DirHandle != NULL){
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            return Status;
          }

          gtBS->SetMem (CreateFileEntity, sizeof(FileIoOpenFile_Task), 0x0);

          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          CreateFileEntity->Name               = PureStrPointer; 
          CreateFileEntity->Tpl                = TplArray[Index];
          CreateFileEntity->OpenMode           = OpenMode[OpenIndex];
          
          Status = DirHandle->OpenEx (
                                DirHandle,
                                &CreateFileEntity->FileIo,
                                PureStrPointer,
                                EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                ValidAttributesForCreateFileIo2[AttributesIndex],
                                &CreateFileEntity->FileIoToken
                                );
          
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

			if (DirHandle != NULL){
              DirHandle->Delete(DirHandle);
              DirHandle = NULL;
            }
            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }

		  //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);

          //
          // enlarge file size
          //
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
			return Status;
          }

          FileInfo->FileSize = 1;

          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);
            
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  Print (L" ================ Start to do Sync OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);   
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      //
      // Sync OpenEx Call
      //
      OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  
      Status = DirHandle->OpenEx (
                 DirHandle,
                 &FileIoEntity->FileIo,
                 FileIoEntity->Name,
                 FileIoEntity->OpenMode,
                 0,
                 &FileIoTokenSync
                 );
      gtBS->RestoreTPL (OldTpl);
      
      FileIoEntity->StatusAsync = Status;
  
      //
      // Last list node handled
      //
      AcquireLock(&gAsyncOpenExistingFileQueueLock); 
      if (IsNodeAtEnd(&SyncCreateFileListHead,ListEntry)) {
        break;
      }
    }  
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  Print (L" ================== Sync OpenExisting File call finshed ================== \n\n");  
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock); 
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if ( FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)
              && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // Last list node handled
      //
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);   

  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid060,
                   L"OpenEx() Basic Test - checkpoint2 ---Test3 ---- Sync -- Open File",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      DirHandle->Open (
              DirHandle,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      
    } else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
    
    AcquireLock(&gAsyncOpenExistingFileQueueLock);  
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  if (DirHandle != NULL) {
    DirHandle->Delete (DirHandle);
    DirHandle = NULL;
  }
  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test4_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  EFI_FILE_PROTOCOL         *DirHandle1;
  EFI_FILE_PROTOCOL         *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  UINTN                     InfoBufferSize;
  UINTN                     FileNameLength;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer,*PureStrPointer1,*StrPointer;
  CHAR16                    *FileNameArray;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxNameIndex;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;
  EFI_TEST_ASSERTION        AssertionType;

  ListEntry    = NULL;
  FileIoEntity = NULL;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }
  
  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;
  
  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  
  for (Loop = 0; Loop < 10; Loop++) {
    EfiStrCpy (StrPointer, PureStrPointer);
    FileNameLength = EfiStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);
    StrPointer += MAX_STRING_LENGTH;
  }
  
  DirHandle1 = NULL;
  DirHandle2 = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle1,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test4 -- Async---Open Dir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
    return Status;
  }
  
  //
  // create sub directory 2
  //
  Status = DirHandle1->Open (
                         DirHandle1,
                         &DirHandle2,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         EFI_FILE_DIRECTORY
                         );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test4 -- Async ---Open Dir",
                 L"%a:%d: create directory 2 Status - %r, dirname - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                );
  if (EFI_ERROR (Status)) {
    if (DirHandle1 != NULL) {
       DirHandle1->Delete (DirHandle1);
    }
    if (FileNameArray != NULL){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
    return EFI_SUCCESS;
  }
  
  StrPointer = FileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {
      
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
        //
        // create file only (do not create directory)
        //
        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, StrPointer += MAX_STRING_LENGTH) {
        
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);            

            if (DirHandle2 != NULL) {
              DirHandle2->Delete (DirHandle2);
              DirHandle2 = NULL;
            } 
            if (DirHandle1 != NULL) {
              DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }  
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            return Status;
          } 
        
          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          CreateFileEntity->Name        = StrPointer; 
          CreateFileEntity->Tpl         = TplArray[Index];
          CreateFileEntity->OpenMode    = OpenMode[OpenIndex];
          
          Status = DirHandle1->OpenEx (
                                 DirHandle1,
                                 &CreateFileEntity->FileIo,
                                 StrPointer,
                                 EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                 ValidAttributesForCreateFileIo2[AttributesIndex],
                                 &CreateFileEntity->FileIoToken
                                 );
          
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            if (DirHandle2 != NULL) {
              DirHandle2->Delete (DirHandle2);
              DirHandle2 = NULL;
            } 
            if (DirHandle1 != NULL) {
              DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }  
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }

            return Status;
          }

          //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);        

          //
          // enlarge file size
          //
        
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (DirHandle2 != NULL) {
              DirHandle2->Delete (DirHandle2);
              DirHandle2 = NULL;
            } 
            if (DirHandle1 != NULL) {
              DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }  
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }

            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }

            return Status;
          }
        
          FileInfo->FileSize = 1;
        
          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);

            if (DirHandle2 != NULL) {
              DirHandle2->Delete (DirHandle2);
              DirHandle2 = NULL;
            } 
            if (DirHandle1 != NULL) {
              DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }  
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }            
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }
        
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
   
  Print (L" ================ Start to do Async OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    Status = FileIoAsyncOpenExistingFile (
                    DirHandle1,
                    FileIoEntity->Tpl,
                    FileIoEntity->Name,
                    0,
                    FileIoEntity->OpenMode
                    );

    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);  
  Print (L" ================== Async OpenExisting File call finshed ================== \n\n"); 
 
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
    
    Print (L".");
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    
    
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
          && FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)
              && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid061,
                   L"OpenEx() Basic Test - checkpoint2 ---Test4---- Async",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      DirHandle1->Open (
              DirHandle1,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      
    }else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
        
        
  //
  // If OpenExistingFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while(!IsListEmpty(&AsyncOpenExistingFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid062,
                   L"OpenEx() Basic Test - checkpoint2 ---Test4 ---- Async --Open File",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

     if (FileIoEntity != NULL){
       gtBS->FreePool(FileIoEntity);
       FileIoEntity = NULL;
     }
     AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
          
        
  //
  // If OpenExistingFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid063,
                     L"OpenEx() Basic Test - checkpoint2 ---Test4---- Async --Open File",
                     L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->OpenMode,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  if (DirHandle2 != NULL){
    DirHandle2->Delete(DirHandle2);
    DirHandle2 = NULL;
  }

  if (DirHandle1 != NULL){
   DirHandle1->Delete(DirHandle1);
   DirHandle1 = NULL;
  }
  
  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test4_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  EFI_FILE_PROTOCOL         *DirHandle1;
  EFI_FILE_PROTOCOL         *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     InfoBufferSize;
  UINTN                     FileNameLength;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer,*PureStrPointer1,*StrPointer;
  CHAR16                    *FileNameArray;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxNameIndex;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_TPL                   OldTpl;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;

  ListEntry    = NULL;
  FileIoEntity = NULL;
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }
  
  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;
  
  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;

  for (Loop = 0; Loop < 10; Loop++) {
    EfiStrCpy (StrPointer, PureStrPointer);
    FileNameLength = EfiStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);
    StrPointer += MAX_STRING_LENGTH;
  }
  
  DirHandle1 = NULL;
  DirHandle2 = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle1,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test4 -- Sync -- OpenDir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
	return Status;
  }
  
  //
  // create sub directory 2
  //
  Status = DirHandle1->Open (
                         DirHandle1,
                         &DirHandle2,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         EFI_FILE_DIRECTORY
                         );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test4 -- Sync -- Open Dir",
                 L"%a:%d: create directory 2 Status - %r, dirname - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                );
  if (EFI_ERROR (Status)) {
    if (DirHandle1 != NULL) {
       Status = DirHandle1->Delete (DirHandle1);
       DirHandle1 = NULL;
    }
    if (FileNameArray != NULL){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
    return Status;
  }
  
  StrPointer = FileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {
      
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
        //
        // create file only (do not create directory)
        //
        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, StrPointer += MAX_STRING_LENGTH) {
        
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);    

            if (DirHandle1 != NULL){
              DirHandle1->Delete(DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle2 != NULL){
              DirHandle2->Delete(DirHandle2);
              DirHandle2 = NULL;
            }
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            return Status;
          } 
        
          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          
          Status = DirHandle1->OpenEx (
                                 DirHandle1,
                                 &CreateFileEntity->FileIo,
                                 StrPointer,
                                 EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                 ValidAttributesForCreateFileIo2[AttributesIndex],
                                 &CreateFileEntity->FileIoToken
                                 );
          
          CreateFileEntity->Name        = StrPointer; 
          CreateFileEntity->StatusAsync = Status;
          CreateFileEntity->Tpl         = TplArray[Index];
          CreateFileEntity->OpenMode    = OpenMode[OpenIndex];
          
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);    

            if (DirHandle1 != NULL){
              DirHandle1->Delete(DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle2 != NULL){
              DirHandle2->Delete(DirHandle2);
              DirHandle2 = NULL;
            }
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }

          //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);        

          //
          // enlarge file size
          //
        
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);    

            if (DirHandle1 != NULL){
              DirHandle1->Delete(DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle2 != NULL){
              DirHandle2->Delete(DirHandle2);
              DirHandle2 = NULL;
            }
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }        
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status; 
          }
        
          FileInfo->FileSize = 1;
        
          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);    

            if (DirHandle1 != NULL){
              DirHandle1->Delete(DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle2 != NULL){
              DirHandle2->Delete(DirHandle2);
              DirHandle2 = NULL;
            }
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }
        
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  Print (L" ================ Start to do Sync OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);     
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      //
      // Sync OpenEx Call
      //
      OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  
      Status = DirHandle1->OpenEx (
                 DirHandle1,
                 &FileIoEntity->FileIo,
                 FileIoEntity->Name,
                 FileIoEntity->OpenMode,
                 0,
                 &FileIoTokenSync
                 );
      gtBS->RestoreTPL (OldTpl);
      
      FileIoEntity->StatusAsync = Status;
  
      //
      // Last list node handled
      //
      AcquireLock(&gAsyncOpenExistingFileQueueLock); 
      if (IsNodeAtEnd(&SyncCreateFileListHead,ListEntry)) {
        break;
      }
    } 
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  Print (L" ================== Sync OpenExisting File call finshed ================== \n\n");   
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)
              && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      // Last list node handled
      //
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);

  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid064,
                   L"OpenEx() Basic Test - checkpoint2 ---Test4---- Sync ---Open File",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      DirHandle1->Open (
              DirHandle1,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      
    }else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
  }

  if (DirHandle2 != NULL){
    DirHandle2->Delete(DirHandle2);
    DirHandle2 = NULL;
  }

  if (DirHandle1 != NULL){
    DirHandle1->Delete(DirHandle1);
    DirHandle1 = NULL;
  }

  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test5_Async (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  EFI_FILE_PROTOCOL         *DirHandle1;
  EFI_FILE_PROTOCOL         *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  UINTN                     InfoBufferSize;
  UINTN                     FileNameLength;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer,*PureStrPointer1,*StrPointer;
  CHAR16                    *FileNameArray;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxNameIndex;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;
  EFI_TEST_ASSERTION        AssertionType;

  ListEntry    = NULL;
  FileIoEntity = NULL;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }
  
  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;
  
  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  
  //
  // prepare file name "\" + subdir1 + "\" + subdir2 + "\" + filename
  //
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;


  for (Loop = 0; Loop < 10; Loop++) {

    //
    // "\"
    //
    StrPointer[0] = '\\';
    StrPointer[1] = 0;

    //
    // "\" + subdir1
    //
    EfiStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\"
    //
    FileNameLength = EfiStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2
    //
    EfiStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\" + subdir2 + "\"
    //
    FileNameLength = EfiStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2 + "\" + filename
    //
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);

    StrPointer += MAX_STRING_LENGTH;
    
  }


  
  DirHandle1 = NULL;
  DirHandle2 = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle1,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test5 -- Async ----Open Dir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
    return Status;
  }
  
  //
  // create sub directory 2
  //
  Status = DirHandle1->Open (
                         DirHandle1,
                         &DirHandle2,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         EFI_FILE_DIRECTORY
                         );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test5 -- Async --OpenDir",
                 L"%a:%d: create directory 2 Status - %r, dirname - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                );
  if (EFI_ERROR (Status)) {
    if (DirHandle1 != NULL) {
       Status = DirHandle1->Delete (DirHandle1);
    }
    if (FileNameArray != NULL){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
    return Status;
  }
  
  StrPointer = FileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {
      
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
        //
        // create file only (do not create directory)
        //
        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, StrPointer += MAX_STRING_LENGTH) {
        
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
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

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);   

            if (DirHandle2 != NULL) {
              Status = DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle1 != NULL) {
              Status = DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            return Status;
          } 
        
          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          
          Status = DirHandle2->OpenEx (
                                 DirHandle2,
                                 &CreateFileEntity->FileIo,
                                 StrPointer,
                                 EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                 ValidAttributesForCreateFileIo2[AttributesIndex],
                                 &CreateFileEntity->FileIoToken
                                 );
          
          CreateFileEntity->Name        = StrPointer; 
          CreateFileEntity->StatusAsync = Status;
          CreateFileEntity->Tpl         = TplArray[Index];
          CreateFileEntity->OpenMode    = OpenMode[OpenIndex];
          
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);   

            if (DirHandle2 != NULL) {
              Status = DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle1 != NULL) {
              Status = DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }

          //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);        

          //
          // enlarge file size
          //        
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);   

            if (DirHandle2 != NULL) {
              Status = DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle1 != NULL) {
              Status = DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
		
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }
        
          FileInfo->FileSize = 1;
        
          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock);   

            if (DirHandle2 != NULL) {
              Status = DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle1 != NULL) {
              Status = DirHandle1->Delete (DirHandle1);
              DirHandle1 = NULL;
            }
            if (FileNameArray != NULL){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
   
  Print (L" ================ Start to do Async OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    Status = FileIoAsyncOpenExistingFile (
                    DirHandle2,
                    FileIoEntity->Tpl,
                    FileIoEntity->Name,
                    0,
                    FileIoEntity->OpenMode
                    );


    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock); 

  Print (L" ================== Async OpenExisting File call finshed ================== \n\n"); 
  
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Open events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
      
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
    
    Print (L".");
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");    
    
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileFinishListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
          && FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)
              && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      } else {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&AsyncOpenExistingFileFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&AsyncOpenExistingFileFinishListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFinishListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid065,
                   L"OpenEx() Basic Test - checkpoint2 ---Test5---- Async---OpenFile",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode
                   );
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      DirHandle2->Open (
              DirHandle2,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      
    } else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
         
  //
  // If OpenExistingFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while(!IsListEmpty(&AsyncOpenExistingFileFailListHead)) {
    FileIoEntity = CR(AsyncOpenExistingFileFailListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid066,
                   L"OpenEx() Basic Test - checkpoint2 ---Test5 ---- Async -- OpenFile",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   );
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

     gtBS->FreePool(FileIoEntity);
       
     AcquireLock(&gAsyncOpenExistingFileQueueLock);
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
          
        
  //
  // If OpenExistingFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&AsyncOpenExistingFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncOpenExistingFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid067,
                     L"OpenEx() Basic Test - checkpoint2 ---Test5---- Async----OpenFile",
                     L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync,
                     FileIoEntity->OpenMode,
                     FileIoEntity->Name
                     );
  
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&AsyncOpenExistingFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
  
  if (DirHandle2 != NULL){
    DirHandle2->Delete(DirHandle2);
    DirHandle2 = NULL;
  }
  if (DirHandle1 != NULL){
    DirHandle1->Delete(DirHandle1);
    DirHandle1 = NULL;
  }
  if (FileNameArray != NULL){
    gtBS->FreePool (FileNameArray);
    FileNameArray =NULL;
  }
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExBasicTestCheckpoint2_Test5_Sync (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE_PROTOCOL                     *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{ 
  EFI_FILE_PROTOCOL         *DirHandle1;
  EFI_FILE_PROTOCOL         *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     InfoBufferSize;
  UINTN                     FileNameLength;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer,*PureStrPointer1,*StrPointer;
  CHAR16                    *FileNameArray;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxNameIndex;
  FileIoOpenFile_Task       *CreateFileEntity;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoOpenFile_Task       *FileIoEntity;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_TPL                   OldTpl;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;

  ListEntry    = NULL;
  FileIoEntity = NULL;
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }
  
  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  
  //
  // prepare file name "\" + subdir1 + "\" + subdir2 + "\" + filename
  //
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;

  for (Loop = 0; Loop < 10; Loop++) {

    //
    // "\"
    //
    StrPointer[0] = '\\';
    StrPointer[1] = 0;

    //
    // "\" + subdir1
    //
    EfiStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\"
    //
    FileNameLength = EfiStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2
    //
    EfiStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\" + subdir2 + "\"
    //
    FileNameLength = EfiStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2 + "\" + filename
    //
    PureStrPointer1 = PureStrPointer + Loop * MAX_STRING_LENGTH; 
    EfiStrCat (StrPointer, PureStrPointer1);

    StrPointer += MAX_STRING_LENGTH;
    
  }

  DirHandle1 = NULL;
  DirHandle2 = NULL;
  
  //
  // create sub directory 1 first
  //
  Status = Root->Open (
                   Root,
                   &DirHandle1,
                   PureStrPointer,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test5 -- Sync---OpenDir",
                 L"%a:%d: create directory 1 Status - %r, dir name - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                 );
  
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
    return Status;	
  }
  
  //
  // create sub directory 2
  //
  Status = DirHandle1->Open (
                         DirHandle1,
                         &DirHandle2,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         EFI_FILE_DIRECTORY
                         );
  
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  } else if ((EFI_MEDIA_CHANGED == Status)
            || (EFI_WRITE_PROTECTED == Status)
            || (EFI_VOLUME_FULL == Status)) {
  
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"OpenEx() Basic Test - checkpoint2 -- Test5 -- Sync ---Open Dir",
                 L"%a:%d: create directory 2 Status - %r, dirname - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PureStrPointer
                );
  if (EFI_ERROR (Status)) {
    if (DirHandle1 != NULL) {
       Status = DirHandle1->Delete (DirHandle1);
    }
    if (FileNameArray != NULL){
      gtBS->FreePool (FileNameArray);
      FileNameArray = NULL;
    }
    return Status;
  }
  
  StrPointer = FileNameArray;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    for (NameIndex = 0; NameIndex < MaxNameIndex;NameIndex++) {
      
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {
        //
        // create file only (do not create directory)
        //
        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++, StrPointer += MAX_STRING_LENGTH) {
        
          FileInfo = NULL;
          //
          // Allocate memory for one CreateFileEntity
          //
          Status = gtBS->AllocatePool(
                           EfiBootServicesData, 
                           sizeof(FileIoOpenFile_Task), 
                           &CreateFileEntity
                           );
          if (EFI_ERROR(Status)) {
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

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock); 

            if (DirHandle1 != NULL){
              DirHandle1->Delete(DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle2 != NULL){
              DirHandle2->Delete(DirHandle2);
              DirHandle2 = NULL;
            }
            if (FileNameArray){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            return Status;
          } 
        
          //
          // create file
          //
          CreateFileEntity->FileIoToken.Event  = NULL;
          CreateFileEntity->FileIoToken.Status = EFI_NOT_READY;
          CreateFileEntity->Name        = StrPointer; 
          CreateFileEntity->Tpl         = TplArray[Index];
          CreateFileEntity->OpenMode    = OpenMode[OpenIndex];
          
          Status = DirHandle2->OpenEx (
                                 DirHandle2,
                                 &CreateFileEntity->FileIo,
                                 StrPointer,
                                 EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                 ValidAttributesForCreateFileIo2[AttributesIndex],
                                 &CreateFileEntity->FileIoToken
                                 );
               
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock); 

            if (DirHandle1 != NULL){
              DirHandle1->Delete(DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle2 != NULL){
              DirHandle2->Delete(DirHandle2);
              DirHandle2 = NULL;
            }
            if (FileNameArray){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            if (CreateFileEntity != NULL){
              gtBS->FreePool(CreateFileEntity);
              CreateFileEntity = NULL;
            }
            return Status;
          }

          //
          // Add CreateFileEntity to SyncReadDataList
          //
          InsertTailList(&SyncCreateFileListHead, &CreateFileEntity->ListEntry);        

          //
          // enlarge file size
          //
          Status = InternalGetInfoFileIo2 (
                     CreateFileEntity->FileIo,
                     &FileInfo,
                     &InfoBufferSize,
                     &gEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock); 

            if (DirHandle1 != NULL){
              DirHandle1->Delete(DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle2 != NULL){
              DirHandle2->Delete(DirHandle2);
              DirHandle2 = NULL;
            }
            if (FileNameArray){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }
        
          FileInfo->FileSize = 1;
        
          Status = CreateFileEntity->FileIo->SetInfo (
                                               CreateFileEntity->FileIo,
                                               &gEfiFileInfoGuid,
                                               InfoBufferSize,
                                               FileInfo
                                               );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );

            AcquireLock(&gAsyncOpenExistingFileQueueLock);
            while (!IsListEmpty(&SyncCreateFileListHead)) {
              FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
              RemoveEntryList(&FileIoEntity->ListEntry);
              ReleaseLock(&gAsyncOpenExistingFileQueueLock);
			
              FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);

              if (FileIoEntity != NULL){
                gtBS->FreePool(FileIoEntity);
                FileIoEntity = NULL;
              }
              AcquireLock(&gAsyncOpenExistingFileQueueLock);
            }
            ReleaseLock(&gAsyncOpenExistingFileQueueLock); 

            if (DirHandle1 != NULL){
              DirHandle1->Delete(DirHandle1);
              DirHandle1 = NULL;
            }
            if (DirHandle2 != NULL){
              DirHandle2->Delete(DirHandle2);
              DirHandle2 = NULL;
            }
            if (FileNameArray){
              gtBS->FreePool (FileNameArray);
              FileNameArray = NULL;
            }            
            if (FileInfo != NULL){
              gtBS->FreePool(FileInfo);
              FileInfo = NULL;
            }
            return Status;
          }
         
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
        }
      }
    }
  }

  //
  // Close File in the SyncCreateFileListHead
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
	  
      FileIoEntity->FileIo->Close (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
        
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      //
      // Last list node handled
      //
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }    
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);
   
  Print (L" ================ Start to do Sync OpenFile call ================ \n\n");
  // 
  // do Asyn Open File call basing on read data result 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      //
      // Sync OpenEx Call
      //
      OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  
      Status = DirHandle2->OpenEx (
                 DirHandle2,
                 &FileIoEntity->FileIo,
                 FileIoEntity->Name,
                 FileIoEntity->OpenMode,
                 0,
                 &FileIoTokenSync
                 );
      gtBS->RestoreTPL (OldTpl);
      FileIoEntity->StatusAsync = Status;
      //
      // Last list node handled
      //
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&SyncCreateFileListHead,ListEntry)) {
        break;
      }
    }  
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);  

  Print (L" ================== Sync OpenExisting File call finshed ================== \n\n"); 
  //
  // clear all File IO events from gOpenExistingFileFinishQueue 
  // gOpenExistingFileQueue is handled first since we use File IO openex to do open file 
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  if (!IsListEmpty(&SyncCreateFileListHead)) {
    for(ListEntry = GetFirstNode(&SyncCreateFileListHead); ; ListEntry = GetNextNode(&SyncCreateFileListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncOpenExistingFileQueueLock);  

      //
      // Check & record every File Io execution entity status 
      //
      if (FileIoEntity->StatusAsync == EFI_SUCCESS) {
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Retrieve file info again
        //
        Status = InternalGetInfoFileIo2 (
                   FileIoEntity->FileIo,
                   &FileInfo,
                   &InfoBufferSize,
                   &gEfiFileInfoGuid
                   );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file info fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (FileInfo != NULL){
            gtBS->FreePool(FileInfo);
            FileInfo = NULL;
          }
          continue;
        }
        
        //
        // OpenMode is Create/Read/Write:
        // Create for an existing file will open the existing file
        //
        if (FileInfo->FileSize == 1) {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          continue;
        }
        //
        // Write / SetInfo to the file
        //
        Temp = 0;
        TempSize = sizeof (UINT8);
        
        WriteStatus = FileIoEntity->FileIo->Write (
                                              FileIoEntity->FileIo,
                                              &TempSize,
                                              &Temp
                                              );
        
        Status = FileIoEntity->FileIo->SetInfo (
                                         FileIoEntity->FileIo,
                                         &gEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
        //
        // OpenMode is Read
        //
        if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ) {
          if ((EFI_ACCESS_DENIED == WriteStatus)
              && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } else {
          if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            continue;
          }
        } 
        
        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
        }
      } else { 
        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // Last list node handled
      //
      AcquireLock(&gAsyncOpenExistingFileQueueLock);
      if (IsNodeAtEnd(&SyncCreateFileListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncOpenExistingFileQueueLock);    
  //
  // Record All Finished Open case results
  //
  AcquireLock(&gAsyncOpenExistingFileQueueLock);
  while (!IsListEmpty(&SyncCreateFileListHead)) {
    FileIoEntity = CR(SyncCreateFileListHead.ForwardLink, FileIoOpenFile_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncOpenExistingFileQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid068,
                   L"OpenEx() Basic Test - checkpoint2 ---Test5---- Sync---OpenFile",
                   L"%a:%d: Tpl - %d,Status - %r,OpenMode-0x%lx,FileName -- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync,
                   FileIoEntity->OpenMode,
                   FileIoEntity->Name
                   ); 
    if (FileIoEntity->OpenMode == EFI_FILE_MODE_READ){
      DirHandle2->Open (
              DirHandle2,
              &FileIoEntity->FileIo,
              FileIoEntity->Name,
              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
              0
              ); 
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      
    }else if (FileIoEntity->FileIo != NULL) {         
      FileIoEntity->FileIo->Delete (FileIoEntity->FileIo);
      FileIoEntity->FileIo = NULL;
    }
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);

    if (FileIoEntity != NULL){
      gtBS->FreePool(FileIoEntity);
      FileIoEntity = NULL;
    }
  }

  if (DirHandle2 != NULL){
    DirHandle2->Delete(DirHandle2);
    DirHandle2 = NULL;
  }

  if (DirHandle1 != NULL){
    DirHandle1->Delete(DirHandle1);
    DirHandle1 = NULL;
  }
  if (FileNameArray){
    gtBS->FreePool (FileNameArray);
    FileNameArray = NULL;
  }
  return EFI_SUCCESS;
}



EFI_STATUS
ComposeFileNameArrayFileIo2 (
  CHAR16        **PureFileNameArray,
  UINT32        *NameCount
  )
{
  UINTN                     ArraySize;
  CHAR16                    *NameArray;
  CHAR16                    *StrPointer;
  UINT32                    Count;
  UINT8                     FileBaseNameLength;
  UINT8                     ExtensionNameLength;
  UINT8                     FileBaseNameNum;
  UINT8                     ExtensionNameNum;
  CHAR16                    TempChar;
  UINT8                     TempIndex;
  UINT8                     Loop;
  EFI_STATUS                Status;

  *PureFileNameArray = NULL;
  *NameCount = 0;

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // compose pure file name array
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&NameArray
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gtBS->SetMem (NameArray, ArraySize * sizeof (CHAR16), 0);

  Count = 0;
  StrPointer = NameArray;
  for (FileBaseNameNum = sizeof (ValidFileBaseNameFileIo2) / sizeof (*ValidFileBaseNameFileIo2);
        FileBaseNameNum > 0; FileBaseNameNum --) {

    FileBaseNameLength = sizeof (ValidFileBaseNameFileIo2[FileBaseNameNum - 1]);

    for (ExtensionNameNum = sizeof (ValidExtensionNameFileIo2) / sizeof (*ValidExtensionNameFileIo2);
          ExtensionNameNum > 0; ExtensionNameNum --){

      ExtensionNameLength = sizeof (ValidExtensionNameFileIo2[ExtensionNameNum - 1]);
      TempIndex = 0;

      for (Loop = 0; Loop < FileBaseNameLength; Loop++){
        TempChar = ValidFileBaseNameFileIo2[FileBaseNameNum - 1][Loop];
        if (TempChar == 0){
          TempIndex = Loop;
          break;
        }
        StrPointer[Loop] = TempChar;
      }

      if (ExtensionNameNum != 1){
        StrPointer[TempIndex++] = (L'.');
      }

      for (Loop = 0; Loop < ExtensionNameLength; Loop++) {
        TempChar = ValidExtensionNameFileIo2[ExtensionNameNum - 1][Loop];
        if (TempChar == 0){
          break;
        }
        StrPointer[Loop + TempIndex] = TempChar;
      }

      StrPointer[Loop + TempIndex] = 0;

      Count++;

      if (Count > MAX_NUMBER_OF_FILE_NAME) {
        break;
      }

      StrPointer += MAX_STRING_LENGTH;
    }
  }

  *PureFileNameArray = NameArray;

#ifdef FILE_SYSTEM_SIMPLE_TEST
  *NameCount = 1;
#else
  *NameCount = Count;
#endif

  return EFI_SUCCESS;
}



