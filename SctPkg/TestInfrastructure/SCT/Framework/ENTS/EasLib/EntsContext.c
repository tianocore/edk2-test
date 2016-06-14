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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  EntsContext.c

Abstract:

  Driver to publish the Test Profile Library Protocol.

--*/
#include "Efi.h"
#include <Library/EntsLib.h>
#include "SctLib.h"

#define MAX_FILENAME_LEN                   128
#define MAX_RECORD_LEN                     512

typedef struct _EFI_PASSIVE_TEST_CONTEXT_RECORD {
  CHAR8                                            *Key;
  UINTN                                            Size;
  VOID                                             *Value;
  struct _EFI_PASSIVE_TEST_CONTEXT_RECORD          *Next;
}EFI_PASSIVE_TEST_CONTEXT_RECORD;

typedef struct _EFI_PASSIVE_TEST_CONTEXT {
  EFI_FILE_HANDLE                                  DirHandle;
  EFI_FILE_HANDLE                                  FileHandle;
  CHAR16                                           FileName[MAX_FILENAME_LEN];
  IN UINT64                                        Attributes;
}EFI_PASSIVE_TEST_CONTEXT;

STATIC
EFI_STATUS
ContextReopen (
  IN EFI_PASSIVE_TEST_CONTEXT                      *Context
  );

STATIC
EFI_STATUS
ContextOpen (
  IN EFI_DEVICE_PATH_PROTOCOL                      *DevicePath,
  IN CHAR16                                        *FileName,
  IN UINT64                                        Attributes,
  OUT EFI_PASSIVE_TEST_CONTEXT                     **Context
  );

STATIC
EFI_STATUS
DelRecord (
  IN EFI_PASSIVE_TEST_CONTEXT                      *Context,
  IN CHAR8                                         *Key
  );

STATIC
EFI_STATUS
ParseRecordLine (
  IN CHAR8                                 *LineBuf,
  IN OUT EFI_PASSIVE_TEST_CONTEXT_RECORD   *Record
  )
{
  CHAR8                                    *TmpStr;
  CHAR8                                    *KeyBuf;
  VOID                                     *ValueBuf;
  UINTN                                    ValueSize;

  TmpStr  = SctAsciiStrChr (LineBuf, '|');
  if (TmpStr == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *TmpStr = '\0';
  KeyBuf = (CHAR8 *)EntsAllocateZeroPool((TmpStr - LineBuf + 1));
  if (KeyBuf == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctAsciiStrCpy (KeyBuf, LineBuf);
  TmpStr++;
  EntsCopyMem(&ValueSize, TmpStr, sizeof(UINTN));
  ValueBuf = (VOID *)EntsAllocateZeroPool (ValueSize);
  if (ValueBuf == NULL) {
    EntsFreePool (KeyBuf);
    return EFI_OUT_OF_RESOURCES;
  }
  TmpStr += sizeof(UINTN) + 1;
  EntsCopyMem(ValueBuf, TmpStr, ValueSize);

  Record->Key   = KeyBuf;
  Record->Size  = ValueSize;
  Record->Value = ValueBuf;
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
ReadRecordsFromFile (
  IN EFI_PASSIVE_TEST_CONTEXT              *Context,
  OUT EFI_PASSIVE_TEST_CONTEXT_RECORD      **RecordListHead
  )
{
  EFI_STATUS                               Status;
  EFI_FILE_HANDLE                          FileHandle;
  CHAR8                                    Buffer[MAX_RECORD_LEN];
  UINTN                                    BufSize;
  EFI_PASSIVE_TEST_CONTEXT_RECORD          *Record;

  if (RecordListHead == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *RecordListHead = NULL;
  FileHandle       = Context->FileHandle;

  //
  // Read all the records from the file to initialize the record list
  //
  BufSize = MAX_RECORD_LEN;
  Status = FileHandle->Read (FileHandle, &BufSize, Buffer);
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Read file error - %r", Status));
    goto Error1;
  }
  while (BufSize != 0) {
    Record = (EFI_PASSIVE_TEST_CONTEXT_RECORD *)EntsAllocateZeroPool(sizeof(EFI_PASSIVE_TEST_CONTEXT_RECORD));
    if (Record == NULL) {
      goto Error1;
    }

    //
    // Process a line and insert the record into record list 
    //
    Status = ParseRecordLine(Buffer, Record);
    if (EFI_ERROR(Status)) {
      EntsFreePool(Record);
      EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Parse the record line fail - %r", Status));
      goto Error1;
    }

    Record->Next = *RecordListHead;
    *RecordListHead = Record;

#if 0
    for (BufPos = 0; BufPos < BufSize; BufPos++) {
      if (Buffer[BufPos] == '\n') {
        //
        // Make the LineBuf as a string (end with '\0')
        //
        LineBuf[LinePos++] = '\0';

        Record = (EFI_PASSIVE_TEST_CONTEXT_RECORD *)EntsAllocateZeroPool(sizeof(EFI_PASSIVE_TEST_CONTEXT_RECORD));
        if (Record == NULL) {
          goto Error1;
        }
        //
        // Process a line and insert the record into record list 
        //
        Status  = ParseRecordLine(LineBuf, LinePos,  Record);
        if (EFI_ERROR(Status)) {
          EntsFreePool(Record);
          EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Parse the record line %s fail - %r", LineBuf, Status));
          goto Error1;
        }
        Record->Next = *RecordListHead;
		*RecordListHead = Record;

        LinePos = 0;
        continue;
      }
      LineBuf[LinePos++] = Buffer[BufPos];
    }
#endif
    //
    // Read a new buffer
    //
    BufSize = MAX_RECORD_LEN;
    Status = FileHandle->Read (FileHandle, &BufSize, Buffer);
    if (EFI_ERROR(Status)) {
      EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Read file error - %r", Status));
      goto Error1;
    }
  }

  return EFI_SUCCESS;
Error1:
  //
  // Free the record list and return
  //
  while(*RecordListHead != NULL) {
    Record = *RecordListHead;
	*RecordListHead = (*RecordListHead)->Next;
    EntsFreePool(Record->Key);
	EntsFreePool(Record->Value);
	EntsFreePool(Record);
  }
  return Status;
}

STATIC
EFI_STATUS
WriteRecordsToFile(
  IN EFI_PASSIVE_TEST_CONTEXT              *Context,
  IN EFI_PASSIVE_TEST_CONTEXT_RECORD       *RecordListHead
  )
{
  EFI_STATUS                               Status;
  EFI_FILE_HANDLE                          FileHandle;
  EFI_PASSIVE_TEST_CONTEXT_RECORD          *Record;
  CHAR8                                    Buffer[MAX_RECORD_LEN];
  UINTN                                    BufSize;
  UINTN                                    Index;

  //
  // Delete the old file and create a new one to throw away old records
  //
  Status = ContextReopen(Context);
  if (EFI_ERROR(Status)) {
  	return Status;
  }

  if (RecordListHead == NULL) {
    return EFI_SUCCESS;
  }

  FileHandle = Context->FileHandle;

  for (Record = RecordListHead; Record != NULL; Record = Record->Next) {
    SctAsciiStrCpy (Buffer, Record->Key);
    Index = SctAsciiStrLen (Record->Key);
    Buffer[Index++] = '|';
    EntsCopyMem(Buffer + Index, &Record->Size, sizeof(UINTN));
    Index += sizeof(UINTN);
	Buffer[Index++] = '|';
	EntsCopyMem(Buffer + Index, Record->Value, MAX_RECORD_LEN - Index);
    BufSize = MAX_RECORD_LEN;
    Status = FileHandle->Write(FileHandle, &BufSize, Buffer);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  return FileHandle->Flush(FileHandle);
}

STATIC
EFI_STATUS
SetRecord (
  IN EFI_PASSIVE_TEST_CONTEXT               *Context,
  IN CHAR8                                  *Key,
  IN UINTN                                  RecordSize,
  IN VOID                                   *RecordValue
  )
{
  EFI_STATUS                                Status;
  EFI_PASSIVE_TEST_CONTEXT_RECORD           *RecordListHead;
  EFI_PASSIVE_TEST_CONTEXT_RECORD           *Record;
  CHAR8                                     *KeyBuf;
  VOID                                      *ValueBuf;

  Status = ReadRecordsFromFile(Context, &RecordListHead);
  if (EFI_ERROR(Status)) {
  	return Status;
  }

  for (Record = RecordListHead; Record != NULL; Record = Record->Next) {
  	if (SctAsciiStrCmp (Key, Record->Key) == 0) {
      break;
    }
  }

  //
  // Create a new record if does not found otherwise replease the
  // value with new one and then inset the record list
  //
  if (Record == NULL) {
    Record = (EFI_PASSIVE_TEST_CONTEXT_RECORD *)EntsAllocateZeroPool(sizeof(EFI_PASSIVE_TEST_CONTEXT_RECORD));
    if (Record == NULL ) {
      Status = EFI_OUT_OF_RESOURCES;
      goto FreeAndReturn;
    }
    KeyBuf = (CHAR8 *)EntsAllocateZeroPool (SctAsciiStrLen (Key) + 1);
    if (KeyBuf == NULL) {
      EntsFreePool(Record);
      Status = EFI_OUT_OF_RESOURCES;
      goto FreeAndReturn;
    }
    ValueBuf = (CHAR8 *)EntsAllocateZeroPool (RecordSize);
    if (ValueBuf == NULL) {
      EntsFreePool(Record);
      EntsFreePool(KeyBuf);
      Status = EFI_OUT_OF_RESOURCES;
      goto FreeAndReturn;
    }
    SctAsciiStrCpy (KeyBuf, Key);
	EntsCopyMem(ValueBuf, RecordValue, RecordSize);
    Record->Key    = KeyBuf;
    Record->Size   = RecordSize;
	Record->Value  = ValueBuf;
    Record->Next   = RecordListHead;
    RecordListHead = Record;
  } else {
    ValueBuf = (VOID *)EntsAllocateZeroPool (RecordSize);
    if (ValueBuf == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto FreeAndReturn;
    }
    EntsFreePool(Record->Value);
	EntsCopyMem(ValueBuf, RecordValue, RecordSize);
	Record->Value = ValueBuf;
	Record->Size  = RecordSize;
  }

  //
  // Write all the records to file
  //
  Status = WriteRecordsToFile(Context, RecordListHead);
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"WriteRecordsToFile fail - %r", Status));
  }
FreeAndReturn:
  //
  // Free the record list and return
  //
  while(RecordListHead != NULL) {
    Record = RecordListHead;
	RecordListHead = RecordListHead->Next;
    EntsFreePool(Record->Key);
	EntsFreePool(Record->Value);
	EntsFreePool(Record);
  }
  return Status;
}

STATIC
EFI_STATUS
GetRecord (
  IN EFI_PASSIVE_TEST_CONTEXT               *Context,
  IN CHAR8                                  *Key,
  IN UINTN                                  *BufSize,
  OUT VOID                                  *RecordBuf
  )
{
  EFI_STATUS                                Status;
  EFI_PASSIVE_TEST_CONTEXT_RECORD           *RecordListHead;
  EFI_PASSIVE_TEST_CONTEXT_RECORD           *Record;

  Status = ReadRecordsFromFile(Context, &RecordListHead);
  if (EFI_ERROR(Status)) {
  	return Status;
  }

  //
  // Search the record with key in the record line of the contextcontainer. Notes:
  // the records in the list are same as the ones in file
  //
  for (Record = RecordListHead; Record != NULL; Record = Record->Next) {
    if (SctAsciiStrCmp (Record->Key, Key) == 0) {
      break;
    }
  }

  if (Record == NULL) {
    Status = EFI_NOT_FOUND;
    goto FreeAndReturn;
  }

  if (*BufSize > Record->Size) {
    *BufSize = Record->Size;
  }
  EntsCopyMem(RecordBuf, Record->Value, *BufSize);
  Status = EFI_SUCCESS;

FreeAndReturn:
  //
  // Free the record list and return
  //
  while(RecordListHead != NULL) {
    Record = RecordListHead;
	RecordListHead = RecordListHead->Next;
    EntsFreePool(Record->Key);
	EntsFreePool(Record->Value);
	EntsFreePool(Record);
  }
  return Status;
}

STATIC
EFI_STATUS
DelRecord (
  IN EFI_PASSIVE_TEST_CONTEXT                      *Context,
  IN CHAR8                                         *Key
  )
{
  EFI_STATUS                                       Status;
  EFI_PASSIVE_TEST_CONTEXT_RECORD                  *RecordListHead;
  EFI_PASSIVE_TEST_CONTEXT_RECORD                  *Record;
  EFI_PASSIVE_TEST_CONTEXT_RECORD                  *Tmp;

  Status = ReadRecordsFromFile(Context, &RecordListHead);
  if (EFI_ERROR(Status)) {
  	return Status;
  }

  if (RecordListHead == NULL) {
    return EFI_NOT_FOUND;
  } else {
    if (SctAsciiStrCmp (Key, RecordListHead->Key) == 0) {
      Record = RecordListHead;
	  RecordListHead = RecordListHead->Next;
    } else {
      for (Record = RecordListHead; Record->Next != NULL; Record = Record->Next) {
        if (SctAsciiStrCmp (Key, Record->Next->Key) == 0) {
          break;
        }
      }
      if(Record->Next == NULL) {
        Status = EFI_NOT_FOUND;
        goto FreeAndReturn;
      } else {
        Tmp = Record->Next;
        Record->Next = Record->Next->Next;
        EntsFreePool(Tmp->Key);
        EntsFreePool(Tmp->Value);
        EntsFreePool(Tmp);
      }
    }
  }

  //
  // Write the remain records to file
  //
  Status = WriteRecordsToFile(Context, RecordListHead);
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_WARNING, L"WriteRecordsToFile fail - %r", Status));
  }
FreeAndReturn:
  //
  // Free the record list and return
  //
  while(RecordListHead != NULL) {
    Record = RecordListHead;
	RecordListHead = RecordListHead->Next;
    EntsFreePool(Record->Key);
	EntsFreePool(Record->Value);
	EntsFreePool(Record);
  }
  return Status;
}

STATIC
EFI_STATUS
ContextReopen (
  IN EFI_PASSIVE_TEST_CONTEXT                      *Context
  )
{
  EFI_STATUS                                       Status;

  Status = Context->FileHandle->Close(Context->FileHandle);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = Context->DirHandle->Open (
                                 Context->DirHandle,
                                 &Context->FileHandle,
                                 Context->FileName,
                                 Context->Attributes,
                                 0
                                 );
  if (EFI_ERROR(Status)) {
    Context->FileHandle = NULL;
    return Status;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
ContextOpen (
  IN EFI_DEVICE_PATH_PROTOCOL                      *DevicePath,
  IN CHAR16                                        *FileName,
  IN UINT64                                        Attributes,
  OUT EFI_PASSIVE_TEST_CONTEXT                     **Context
  )
{
  EFI_STATUS                                       Status;
  EFI_HANDLE                                       DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL                  *Vol;
  EFI_FILE_HANDLE                                  RootDir;
  EFI_FILE_HANDLE                                  FileHandle;

  //
  // Check the parameter
  //
  if (Context == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *Context = (EFI_PASSIVE_TEST_CONTEXT *)EntsAllocateZeroPool(sizeof(EFI_PASSIVE_TEST_CONTEXT));
  if (*Context == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Open the file if not exist create a new
  //
  Status = gntBS->LocateDevicePath (
                    &gEfiSimpleFileSystemProtocolGuid,
                    &DevicePath,
                    &DeviceHandle
                    );
  if (EFI_ERROR(Status)) {
    goto ContextOpenError;
  }

  Status = gntBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiSimpleFileSystemProtocolGuid,
                    (VOID *)&Vol
                    );
  if (EFI_ERROR(Status)) {
    goto ContextOpenError;
  }

  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    goto ContextOpenError;
  }

  Status = RootDir->Open (
                      RootDir,
                      &FileHandle,
                      FileName,
                      Attributes,
                      0
                      );
  if (EFI_ERROR(Status)) {
    RootDir->Close(RootDir);
    goto ContextOpenError;
  }

  (*Context)->DirHandle    = RootDir;
  (*Context)->FileHandle   = FileHandle;
  EntsStrCpy((*Context)->FileName, FileName);
  (*Context)->Attributes   = Attributes;

  return EFI_SUCCESS;
ContextOpenError:
  EntsFreePool(*Context);
  return Status;
}

STATIC
VOID
ContextClose (
  IN EFI_PASSIVE_TEST_CONTEXT                      *Context
  )
{
  if (Context == NULL) {
    return ;
  }

  if (Context->FileHandle != NULL) {
    Context->FileHandle->Close(Context->FileHandle);
  }

  if (Context->DirHandle != NULL) {
    Context->DirHandle->Close(Context->DirHandle);
  }

  EntsFreePool(Context);

  return ;
}

EFI_STATUS
PassiveTestContextCreate (
  IN EFI_DEVICE_PATH_PROTOCOL                      *DevicePath,
  IN CHAR16                                        *FileName
  )
{
  EFI_STATUS                                       Status;
  EFI_HANDLE                                       DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL                  *Vol;
  EFI_FILE_HANDLE                                  FileHandle;
  EFI_FILE_HANDLE                                  RootDir;

  //
  // Check the parameter
  //
  if ((DevicePath == NULL) || (FileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  if (EntsStrLen(FileName) > MAX_FILENAME_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Open the file if not exist create a new
  //
  Status = gntBS->LocateDevicePath (
                    &gEfiSimpleFileSystemProtocolGuid,
                    &DevicePath,
                    &DeviceHandle
                    );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gntBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiSimpleFileSystemProtocolGuid,
                    (VOID *)&Vol
                    );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Delete it first if the file exist
  //
  Status = RootDir->Open (
                      RootDir,
                      &FileHandle,
                      FileName,
                      EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                      0
                      );
  if (!EFI_ERROR(Status)) {
    FileHandle->Delete(FileHandle);
  }

  //
  // Create a new file
  //
  Status = RootDir->Open (
                      RootDir,
                      &FileHandle,
                      FileName,
                      EFI_FILE_MODE_CREATE|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR(Status)) {
    RootDir->Close(RootDir);
    return Status;
  }

  //
  // Close the file and return
  //
  FileHandle->Close (FileHandle);
  RootDir->Close (RootDir);
  return EFI_SUCCESS;
}

EFI_STATUS
PassiveTestContextDelete (
  IN EFI_DEVICE_PATH_PROTOCOL                      *DevicePath,
  IN CHAR16                                        *FileName
  )
{
  EFI_STATUS                                       Status;
  EFI_HANDLE                                       DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL                  *Vol;
  EFI_FILE_HANDLE                                  FileHandle;
  EFI_FILE_HANDLE                                  RootDir;

  //
  // Check the parameter
  //
  if ((DevicePath == NULL) || (FileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  if (EntsStrLen(FileName) > MAX_FILENAME_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Open the file if not exist create a new
  //
  Status = gntBS->LocateDevicePath (
                    &gEfiSimpleFileSystemProtocolGuid,
                    &DevicePath,
                    &DeviceHandle
                    );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gntBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiSimpleFileSystemProtocolGuid,
                    (VOID *)&Vol
                    );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = RootDir->Open (
                      RootDir,
                      &FileHandle,
                      FileName,
                      EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR(Status)) {
    RootDir->Close(RootDir);
    return Status;
  }

  FileHandle->Delete(FileHandle);
  RootDir->Close(RootDir);
  return EFI_SUCCESS;
}

EFI_STATUS
SetContextRecord (
  IN EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN CHAR16                                    *FileName,
  IN CHAR16                                    *Key,
  IN UINTN                                     Size,
  IN VOID                                      *Value
  )
{
  EFI_STATUS                                   Status;
  EFI_PASSIVE_TEST_CONTEXT                     *Context;
  CHAR8                                        AsciiKey[MAX_RECORD_LEN];

  //
  // Check the pararmeters.
  //
  if ((Key == NULL) || (DevicePath == NULL) || (FileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  if ((Size != 0) && (Value == NULL)) {
  	return EFI_INVALID_PARAMETER; 
  }
  if (EntsStrLen(FileName) > MAX_FILENAME_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  Unicode2Ascii(AsciiKey, Key);
  if (SctAsciiStrLen (AsciiKey) + Size + 1 > MAX_RECORD_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  if (SctAsciiStrChr (AsciiKey, '=') != NULL) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"The KEY of record can not contain ="));
    return EFI_INVALID_PARAMETER;
  }

  //
  // Open the file
  //
  Status = ContextOpen (
             DevicePath, 
             FileName, 
             EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
             &Context
             );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_WARNING, L"SetContextRecord: ContextOpen %s Fail - %r", FileName, Status));
    return Status;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"SetContextRecord: ContextOpen %s Success", FileName));

  //
  // Record string.
  //
  if (Size != 0) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"Do SetRecord"));
    Status = SetRecord(
               Context,
               AsciiKey,
               Size,
               Value
               );
    if(EFI_ERROR(Status)) {
      EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"SetContextRecord: SetRecord Key:%s Value:%s - %r", Key, Value, Status));
    }
  } else {
    EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"Do DelRecord"));
    Status = DelRecord(
               Context, 
               AsciiKey
               );
    if(EFI_ERROR(Status)) {
      EFI_ENTS_DEBUG((EFI_ENTS_D_WARNING, L"SetContextRecord: DelRecord Key:%s - %r", Key, Status));
    }
  }

  ContextClose(Context);
  return Status;
}

EFI_STATUS
GetContextRecord (
  IN EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN CHAR16                                    *FileName,
  IN CHAR16                                    *Key,
  IN UINTN                                     *BufSize, 
  OUT VOID                                     *RecordBuf
  )
{
  EFI_STATUS                                   Status;
  EFI_PASSIVE_TEST_CONTEXT                     *Context;
  CHAR8                                        AsciiKey[MAX_RECORD_LEN];

  if ((DevicePath == NULL) || (FileName == NULL) || 
      (Key == NULL) || (RecordBuf == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  if (EntsStrLen(FileName) > MAX_FILENAME_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  Unicode2Ascii(AsciiKey, Key);

  //
  // Open the file
  //
  Status = ContextOpen (
             DevicePath, 
             FileName, 
             EFI_FILE_MODE_READ,
             &Context
             );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_WARNING, L"GetContextRecord: ContextOpen %s Fail - %r", FileName, Status));
    return Status;
  }

  Status = GetRecord(
             Context,
             AsciiKey,
             BufSize,
             RecordBuf
             );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_WARNING, L"GetContextRecord: GetRecord Key:%s - %r", Key, Status));
    ContextClose(Context);
	return Status;
  }

  ContextClose(Context);
  return EFI_SUCCESS;
}
