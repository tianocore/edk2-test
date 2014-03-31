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
                                                                  
    Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
     
  --*/
  /*++
  
  Module Name:
  
    SimpleFileSystemExProtocol.h
  
  Abstract:
  
    EFI Simple File System Protocol and EFI_FILE Protocol
      (define according to the EFI Spec, version 1.10)
  
  --*/
  
#ifndef _SIMPLE_FILE_SYSTEMEX_FOR_TEST_H
#define _SIMPLE_FILE_SYSTEMEX_FOR_TEST_H

#include "Efi.h"
#include "EfiCommonLib.h"
//#include "EfiTestUtilityLib.h"
#include "EfiTestLib.h"
#include "Guid.h" 
#include "LinkedList.h"
#include "Lock.h"


#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION 0x00010000
#define EFI_FILE_PROTOCOL_REVISION1 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000
#define EFI_FILE_PROTOCOL_REVISION EFI_FILE_PROTOCOL_REVISION2
  


  //#define _SIMPLE_FILE_SYSTEM_H_
  //#define _FILE_INFO_H_
  //#define _FILE_SYSTEM_INFO_H_
  //#define _FILE_SYSTEM_VOLUME_LABEL_INFO_H_
  
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
    { 0x964e5b22, 0x6459, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define MAX_STRING_LENGTH         266

#define TPL_ARRAY_SIZE 2

#define EFI_INITIALIZE_LOCK_VARIABLE(Tpl) {Tpl,0,0}

extern EFI_TPL TplArray [TPL_ARRAY_SIZE];

extern EFI_EVENT              TimerEvent;




EFI_FORWARD_DECLARATION (EFI_SIMPLE_FILE_SYSTEM_PROTOCOL);
EFI_FORWARD_DECLARATION (EFI_FILE_PROTOCOL);
  
typedef
EFI_STATUS
(EFIAPI *EFI_VOLUME_OPEN) (
  IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL    *This,
  OUT EFI_FILE_PROTOCOL                 **Root
  );
/*++
  
   Routine Description:
      Open the root directory on a volume.
  
    Arguments:
      This - Protocol instance pointer.
      Root - Returns an Open file handle for the root directory
  
    Returns:
      EFI_SUCCES                     - The device was opened.
      EFI_UNSUPPORTED           - This volume does not suppor the file system.
      EFI_NO_MEDIA                 - The device has no media.
      EFI_DEVICE_ERROR          - The device reported an error.
      EFI_VOLUME_CORRUPTED - The file system structures are corrupted
      EFI_ACCESS_DENIED        - The service denied access to the file
      EFI_OUT_OF_RESOURCES - The volume was not opened due to lack of resources
  
--*/
  
  
typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
  UINT64                  Revision;
  EFI_VOLUME_OPEN         OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;


typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN) (
  IN EFI_FILE_PROTOCOL        *File,
  OUT EFI_FILE_PROTOCOL       **NewHandle,
  IN CHAR16                   *FileName,
  IN UINT64                   OpenMode,
  IN UINT64                   Attributes
  )
/*++

  Routine Description:
    Open the root directory on a volume.

  Arguments:
    File             - Protocol instance pointer.
    NewHandle  - Returns File Handle for FileName
    FileName     - Null terminated string. "\", ".", and ".." are supported
    OpenMode   - Open mode for file.
    Attributes    - Only used for EFI_FILE_MODE_CREATE

  Returns:
    EFI_SUCCES                     - The device was opened.
    EFI_NOT_FOUND               - The specified file could not be found on the device
    EFI_NO_MEDIA                 - The device has no media.
    EFI_MEDIA_CHANGED       - The media has changed
    EFI_DEVICE_ERROR          - The device reported an error.
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_ACCESS_DENIED        - The service denied access to the file
    EFI_OUT_OF_RESOURCES - The volume was not opened due to lack of resources
    EFI_VOLUME_FULL            - The volume is full.

--*/
;

// Open modes
#define EFI_FILE_MODE_READ      0x0000000000000001
#define EFI_FILE_MODE_WRITE     0x0000000000000002
#define EFI_FILE_MODE_CREATE    0x8000000000000000

// File attributes
#define EFI_FILE_READ_ONLY      0x0000000000000001
#define EFI_FILE_HIDDEN         0x0000000000000002
#define EFI_FILE_SYSTEM         0x0000000000000004
#define EFI_FILE_RESERVED       0x0000000000000008
#define EFI_FILE_DIRECTORY      0x0000000000000010
#define EFI_FILE_ARCHIVE        0x0000000000000020
#define EFI_FILE_VALID_ATTR     0x0000000000000037

#define OPEN_R_W_MODE       (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE)
#define CREATE_FILE_MODE    (OPEN_R_W_MODE | EFI_FILE_MODE_CREATE)


#define FILEIOENTITY_SIGNATURE   EFI_SIGNATURE_32('f','i','o','2')


typedef struct {
  EFI_EVENT                Event;
  EFI_STATUS               Status;
  UINTN                    BufferSize;
  VOID                     *Buffer;
} EFI_FILE_IO_TOKEN;



/*++

  Arguments:
    Event       - If Event is NULL, then blocking I/O is performed
    Status      - Defines whether or not the signaled event encountered an error
    BufferSize - For OpenEx():  Not Used, ignored
                       For ReadEx():  On input, the size of the Buffer. On output, the amount of data returned in Buffer. In both cases, the size is measured in bytes.
                       For WriteEx(): On input, the size of the Buffer. On output, the amount of data actually written. In both cases, the size is measured in bytes.
                       For FlushEx(): Not used, ignored
    Buffer       - For OpenEx():  Not Used, ignored
                    - For ReadEx():  The buffer into which the data is read.
                    - For WriteEx(): The buffer of data to write.
                    - For FlushEx(): Not Used, ignored
--*/



typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN_EX) (
  IN EFI_FILE_PROTOCOL      *File,
  OUT EFI_FILE_PROTOCOL     **NewHandle,
  IN CHAR16                 *FileName,
  IN UINT64                 OpenMode,
  IN UINT64                 Attributes,
  IN OUT EFI_FILE_IO_TOKEN  *Token
  )
/*++

  Routine Description:
    Opens a new file relative to the source directorys location

  Arguments:
    File             - Protocol instance pointer.
    NewHandle  - Returns File Handle for FileName
    FileName     - Null terminated string. "\", ".", and ".." are supported
    OpenMode   - Open mode for file.
    Attributes    - Only used for EFI_FILE_MODE_CREATE
    Token          - A pointer to the token associated with the transaction

  Returns:
    EFI_SUCCES                     - The device was opened.
    EFI_NOT_FOUND               - The specified file could not be found on the device
    EFI_NO_MEDIA                 - The device has no media.
    EFI_MEDIA_CHANGED       - The media has changed
    EFI_DEVICE_ERROR          - The device reported an error.
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_ACCESS_DENIED        - The service denied access to the file
    EFI_OUT_OF_RESOURCES - The volume was not opened due to lack of resources
    EFI_VOLUME_FULL            - The volume is full.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_FILE_CLOSE) (
  IN EFI_FILE_PROTOCOL  *File
  )
/*++

  Routine Description:
    Close the file handle

  Arguments:
    File              - Protocol instance pointer.

  Returns:
    EFI_SUCCES - The device was opened.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_FILE_DELETE) (
  IN EFI_FILE_PROTOCOL  *File
  )
/*++

  Routine Description:
    Close and delete the file handle

  Arguments:
    File       - Protocol instance pointer.

  Returns:
    EFI_SUCCES                         - The device was opened.
    EFI_WARN_DELETE_FAILURE - The handle was closed but the file was not deleted

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ) (
  IN EFI_FILE_PROTOCOL        *File,
  IN OUT UINTN                *BufferSize,
  OUT VOID                    *Buffer
  )
/*++

  Routine Description:
    Read data from the file.

  Arguments:
    File            - Protocol instance pointer.
    BufferSize  - On input size of buffer, on output amount of data in buffer.
    Buffer        - The buffer in which data is read.

  Returns:
    EFI_SUCCES                     - Data was read.
    EFI_NO_MEDIA                 - The device has no media
    EFI_DEVICE_ERROR          - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_BUFFER_TO_SMALL    - BufferSize is too small. BufferSize contains required size

--*/

;
typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ_EX) (
  IN EFI_FILE_PROTOCOL         *File,
  IN OUT EFI_FILE_IO_TOKEN     *Token
);
/*++

  Routine Description:
    Read data from the file.

  Arguments:
    File         - Protocol instance pointer.
    Token      - A pointer to the token associated with the transaction. 

  Returns:
    EFI_SUCCES                     - Data was read.
    EFI_NO_MEDIA                 - The device has no media
    EFI_DEVICE_ERROR          - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_BUFFER_TO_SMALL    - BufferSize is too small. BufferSize contains required size

--*/




typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE) (
  IN EFI_FILE_PROTOCOL        *File,
  IN OUT UINTN                *BufferSize,
  IN VOID                     *Buffer
  )
/*++

  Routine Description:
    Write data from to the file.

  Arguments:
    File         - Protocol instance pointer.
    Token      - A pointer to the token associated with the transaction. 


  Returns:
    EFI_SUCCES                     - Data was written.
    EFI_UNSUPPORT               - Writes to Open directory are not supported
    EFI_NO_MEDIA                 - The device has no media
    EFI_DEVICE_ERROR          - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED    - The device is write protected
    EFI_ACCESS_DENIED        - The file was open for read only
    EFI_VOLUME_FULL            - The volume is full

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE_EX) (
  IN EFI_FILE_PROTOCOL       *File,
  IN OUT EFI_FILE_IO_TOKEN   *Token
)
/*++

  Routine Description:
    Write data from to the file.

  Arguments:
    File           - Protocol instance pointer.
    BufferSize - On input size of buffer, on output amount of data in buffer.
    Buffer       - The buffer in which data to write.

  Returns:
    EFI_SUCCES                     - Data was written.
    EFI_UNSUPPORT               - Writes to Open directory are not supported
    EFI_NO_MEDIA                 - The device has no media
    EFI_DEVICE_ERROR          - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED    - The device is write protected
    EFI_ACCESS_DENIED        - The file was open for read only
    EFI_VOLUME_FULL            - The volume is full

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_POSITION) (
  IN EFI_FILE_PROTOCOL        *File,
  IN UINT64                   Position
  )
/*++

  Routine Description:
    Set a files current position

  Arguments:
    File       - Protocol instance pointer.
    Position - Byte possition from the start of the file

  Returns:
    EFI_SUCCES          - Data was written.
    EFI_UNSUPPORTED - Seek request for non-zero is not valid on open.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_POSITION) (
  IN EFI_FILE_PROTOCOL        *File,
  OUT UINT64                  *Position
  )
/*++

  Routine Description:
    Get a files current position

  Arguments:
    File       - Protocol instance pointer.
    Position - Byte possition from the start of the file

  Returns:
    EFI_SUCCES          - Data was written.
    EFI_UNSUPPORTED - Seek request for non-zero is not valid on open.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_INFO) (
  IN EFI_FILE_PROTOCOL        *File,
  IN EFI_GUID                 *InformationType,
  IN OUT UINTN                *BufferSize,
  OUT VOID                    *Buffer
  )
/*++

  Routine Description:
    Get information about a file

  Arguments:
    File                    - Protocol instance pointer.
    InformationType - Type of info to return in Buffer
    BufferSize          - On input size of buffer, on output amount of data in buffer.
    Buffer                - The buffer to return data.

  Returns:
    EFI_SUCCES                     - Data was returned.
    EFI_UNSUPPORT               - InformationType is not supported
    EFI_NO_MEDIA                 - The device has no media
    EFI_DEVICE_ERROR          - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED    - The device is write protected
    EFI_ACCESS_DENIED        - The file was open for read only
    EFI_BUFFER_TOO_SMALL  - Buffer was too small, required size returned in BufferSize
--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_INFO) (
  IN EFI_FILE_PROTOCOL        *File,
  IN EFI_GUID                 *InformationType,
  IN UINTN                    BufferSize,
  IN VOID                     *Buffer
  )
/*++

  Routine Description:
    Set information about a file

  Arguments:
    File                    - Protocol instance pointer.
    InformationType - Type of info in Buffer
    BufferSize          - Size of buffer.
    Buffer                - The data to write.

  Returns:
    EFI_SUCCES                     - Data was returned.
    EFI_UNSUPPORT               - InformationType is not supported
    EFI_NO_MEDIA                 - The device has no media
    EFI_DEVICE_ERROR          - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED    - The device is write protected
    EFI_ACCESS_DENIED        - The file was open for read only
--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH) (
  IN EFI_FILE_PROTOCOL  *File
  )
/*++

  Routine Description:
    Flush data back for the file handle

  Arguments:
    File  - Protocol instance pointer.

  Returns:
    EFI_SUCCES                     - Data was written.
    EFI_UNSUPPORT               - Writes to Open directory are not supported
    EFI_NO_MEDIA                 - The device has no media
    EFI_DEVICE_ERROR          - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED     - The device is write protected
    EFI_ACCESS_DENIED        - The file was open for read only
    EFI_VOLUME_FULL            - The volume is full

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH_EX) (
  IN EFI_FILE_PROTOCOL       *File,
  IN OUT EFI_FILE_IO_TOKEN   *Token
)
/*++

  Routine Description:
    Flush data back for the file handle

  Arguments:
    File  - Protocol instance pointer.

  Returns:
    EFI_SUCCES                     - Data was written.
    EFI_UNSUPPORT               - Writes to Open directory are not supported
    EFI_NO_MEDIA                 - The device has no media
    EFI_DEVICE_ERROR          - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED     - The device is write protected
    EFI_ACCESS_DENIED        - The file was open for read only
    EFI_VOLUME_FULL            - The volume is full

--*/
;



#define EFI_FILE_HANDLE_REVISION         0x00020000
typedef struct _EFI_FILE_PROTOCOL {
  UINT64                  Revision;
  EFI_FILE_OPEN           Open;
  EFI_FILE_CLOSE          Close;
  EFI_FILE_DELETE         Delete;
  EFI_FILE_READ           Read;
  EFI_FILE_WRITE          Write;
  EFI_FILE_GET_POSITION   GetPosition;
  EFI_FILE_SET_POSITION   SetPosition;
  EFI_FILE_GET_INFO       GetInfo;
  EFI_FILE_SET_INFO       SetInfo;
  EFI_FILE_FLUSH          Flush;
  EFI_FILE_OPEN_EX        OpenEx;
  EFI_FILE_READ_EX        ReadEx;
  EFI_FILE_WRITE_EX       WriteEx;
  EFI_FILE_FLUSH_EX       FlushEx;
}EFI_FILE_PROTOCOL;
struct _EFI_FILE_PROTOCOL *EFI_FILE_PROTOCOL_HANDLE;


//
// File information types
//

#define EFI_FILE_INFO_ID   \
  { 0x9576e92, 0x6d3f, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

typedef struct {
  UINT64                  Size;
  UINT64                  FileSize;
  UINT64                  PhysicalSize;
  EFI_TIME                CreateTime;
  EFI_TIME                LastAccessTime;
  EFI_TIME                ModificationTime;
  UINT64                  Attribute;
  CHAR16                  FileName[1];
} EFI_FILE_INFO;

//
// The FileName field of the EFI_FILE_INFO data structure is variable length.
// Whenever code needs to know the size of the EFI_FILE_INFO data structure, it needs to
// be the size of the data structure without the FileName field.  The following macro
// computes this size correctly no matter how big the FileName array is declared.
// This is required to make the EFI_FILE_INFO data structure ANSI compilant.
//
#define SIZE_OF_EFI_FILE_INFO EFI_FIELD_OFFSET(EFI_FILE_INFO,FileName)

#define EFI_FILE_SYSTEM_INFO_ID  \
  { 0x9576e93, 0x6d3f, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

typedef struct {
  UINT64                  Size;
  BOOLEAN                 ReadOnly;
  UINT64                  VolumeSize;
  UINT64                  FreeSpace;
  UINT32                  BlockSize;
  CHAR16                  VolumeLabel[1];
} EFI_FILE_SYSTEM_INFO;

//
// The VolumeLabel field of the EFI_FILE_SYSTEM_INFO data structure is variable length.
// Whenever code needs to know the size of the EFI_FILE_SYSTEM_INFO data structure, it needs
// to be the size of the data structure without the VolumeLable field.  The following macro
// computes this size correctly no matter how big the VolumeLable array is declared.
// This is required to make the EFI_FILE_SYSTEM_INFO data structure ANSI compilant.
//
#define SIZE_OF_EFI_FILE_SYSTEM_INFO EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO,VolumeLabel)

#define EFI_FILE_SYSTEM_VOLUME_LABEL_INFO_ID \
  { 0xDB47D7D3,0xFE81, 0x11d3, 0x9A, 0x35, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }

typedef struct {
  CHAR16                  VolumeLabel[1];
} EFI_FILE_SYSTEM_VOLUME_LABEL_INFO;


//
// 
//
typedef struct {
  UINTN                             Signature;
  EFI_FILE_PROTOCOL                 *FileIo;
  EFI_FILE_IO_TOKEN               	FileIoToken;
  EFI_TPL                           Tpl;
  UINT64                            SetPosition;
  UINT64                            PositionAfterRead;
  UINTN                             ReadLength;
  EFI_LIST_ENTRY                    ListEntry;     
  EFI_STATUS                        StatusAsync;
  EFI_TEST_ASSERTION                AssertionType;
} FileIo_Task;

//
// record every  SimpleFileSystem Async Read Directory call status
//
typedef struct {
  UINTN                             Signature;
  EFI_FILE_PROTOCOL                 *FileIo;
  EFI_FILE_IO_TOKEN               	FileIoToken;
  EFI_TPL                           Tpl;
  UINTN                             Index;
  EFI_LIST_ENTRY                    ListEntry;     
  EFI_STATUS                        StatusAsync;
  EFI_TEST_ASSERTION                AssertionType;
} FileIoDir_Task;


#define SIZE_OF_EFI_FILE_SYSTEM_VOLUME_LABEL_INFO EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_VOLUME_LABEL_INFO,VolumeLabel)

extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;

extern EFI_GUID gEfiFileInfoGuid;
extern EFI_GUID gEfiFileInfoIdGuid;
extern EFI_GUID gEfiFileSystemVolumeLabelInfoIdGuid;




UINTN
Print (
  IN CHAR16                         *fmt,
  ...
  );




#endif

