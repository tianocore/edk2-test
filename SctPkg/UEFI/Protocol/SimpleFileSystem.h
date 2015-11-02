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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  SimpleFileSystem.h

Abstract:

  EFI Simple File System Protocol and EFI_FILE Protocol
    (define according to the EFI Spec, version 1.10)

--*/

#ifndef _SIMPLE_FILE_SYSTEM_FOR_TEST_H
#define _SIMPLE_FILE_SYSTEM_FOR_TEST_H

//#define _SIMPLE_FILE_SYSTEM_H_
//#define _FILE_INFO_H_
//#define _FILE_SYSTEM_INFO_H_
//#define _FILE_SYSTEM_VOLUME_LABEL_INFO_H_

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
  { 0x964e5b22, 0x6459, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
typedef struct _EFI_FILE EFI_FILE;

typedef
EFI_STATUS
(EFIAPI *EFI_VOLUME_OPEN) (
  IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL    *This,
  OUT EFI_FILE                          **Root
  )
/*++

  Routine Description:
    Open the root directory on a volume.

  Arguments:
    This - Protocol instance pointer.
    Root - Returns an Open file handle for the root directory

  Returns:
    EFI_SUCCES           - The device was opened.
    EFI_UNSUPPORTED      - This volume does not suppor the file system.
    EFI_NO_MEDIA         - The device has no media.
    EFI_DEVICE_ERROR     - The device reported an error.
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_ACCESS_DENIED    - The service denied access to the file
    EFI_OUT_OF_RESOURCES - The volume was not opened due to lack of resources

--*/
;

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION   0x00010000
#define EFI_FILE_PROTOCOL_REVISION1 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000
#define EFI_FILE_PROTOCOL_REVISION EFI_FILE_PROTOCOL_REVISION2

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
  UINT64                  Revision;
  EFI_VOLUME_OPEN         OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;


typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN) (
  IN EFI_FILE                 *File,
  OUT EFI_FILE                **NewHandle,
  IN CHAR16                   *FileName,
  IN UINT64                   OpenMode,
  IN UINT64                   Attributes
  )
/*++

  Routine Description:
    Open the root directory on a volume.

  Arguments:
    File       - Protocol instance pointer.
    NewHandle  - Returns File Handle for FileName
    FileName   - Null terminated string. "\", ".", and ".." are supported
    OpenMode   - Open mode for file.
    Attributes - Only used for EFI_FILE_MODE_CREATE

  Returns:
    EFI_SUCCES           - The device was opened.
    EFI_NOT_FOUND        - The specified file could not be found on the device
    EFI_NO_MEDIA         - The device has no media.
    EFI_MEDIA_CHANGED    - The media has changed
    EFI_DEVICE_ERROR     - The device reported an error.
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_ACCESS_DENIED    - The service denied access to the file
    EFI_OUT_OF_RESOURCES - The volume was not opened due to lack of resources
    EFI_VOLUME_FULL      - The volume is full.

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

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_CLOSE) (
  IN EFI_FILE  *File
  )
/*++

  Routine Description:
    Close the file handle

  Arguments:
    File       - Protocol instance pointer.

  Returns:
    EFI_SUCCES - The device was opened.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_FILE_DELETE) (
  IN EFI_FILE  *File
  )
/*++

  Routine Description:
    Close and delete the file handle

  Arguments:
    File       - Protocol instance pointer.

  Returns:
    EFI_SUCCES              - The device was opened.
    EFI_WARN_DELETE_FAILURE - The handle was closed but the file was not
                              deleted

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ) (
  IN EFI_FILE                 *File,
  IN OUT UINTN                *BufferSize,
  OUT VOID                    *Buffer
  )
/*++

  Routine Description:
    Read data from the file.

  Arguments:
    File       - Protocol instance pointer.
    BufferSize - On input size of buffer, on output amount of data in
                 buffer.
    Buffer     - The buffer in which data is read.

  Returns:
    EFI_SUCCES           - Data was read.
    EFI_NO_MEDIA         - The device has no media
    EFI_DEVICE_ERROR     - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_BUFFER_TO_SMALL  - BufferSize is too small. BufferSize contains
                           required size

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE) (
  IN EFI_FILE                 *File,
  IN OUT UINTN                *BufferSize,
  IN VOID                     *Buffer
  )
/*++

  Routine Description:
    Write data from to the file.

  Arguments:
    File       - Protocol instance pointer.
    BufferSize - On input size of buffer, on output amount of data in buffer.
    Buffer     - The buffer in which data to write.

  Returns:
    EFI_SUCCES           - Data was written.
    EFI_UNSUPPORT        - Writes to Open directory are not supported
    EFI_NO_MEDIA         - The device has no media
    EFI_DEVICE_ERROR     - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED  - The device is write protected
    EFI_ACCESS_DENIED    - The file was open for read only
    EFI_VOLUME_FULL      - The volume is full

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_POSITION) (
  IN EFI_FILE                 *File,
  IN UINT64                   Position
  )
/*++

  Routine Description:
    Set a files current position

  Arguments:
    File     - Protocol instance pointer.
    Position - Byte possition from the start of the file

  Returns:
    EFI_SUCCES      - Data was written.
    EFI_UNSUPPORTED - Seek request for non-zero is not valid on open.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_POSITION) (
  IN EFI_FILE                 *File,
  OUT UINT64                  *Position
  )
/*++

  Routine Description:
    Get a files current position

  Arguments:
    File     - Protocol instance pointer.
    Position - Byte possition from the start of the file

  Returns:
    EFI_SUCCES      - Data was written.
    EFI_UNSUPPORTED - Seek request for non-zero is not valid on open.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_INFO) (
  IN EFI_FILE                 *File,
  IN EFI_GUID                 *InformationType,
  IN OUT UINTN                *BufferSize,
  OUT VOID                    *Buffer
  )
/*++

  Routine Description:
    Get information about a file

  Arguments:
    File            - Protocol instance pointer.
    InformationType - Type of info to return in Buffer
    BufferSize      - On input size of buffer, on output amount of data in
                      buffer.
    Buffer          - The buffer to return data.

  Returns:
    EFI_SUCCES           - Data was returned.
    EFI_UNSUPPORT        - InformationType is not supported
    EFI_NO_MEDIA         - The device has no media
    EFI_DEVICE_ERROR     - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED  - The device is write protected
    EFI_ACCESS_DENIED    - The file was open for read only
    EFI_BUFFER_TOO_SMALL - Buffer was too small, required size returned in
                           BufferSize
--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_INFO) (
  IN EFI_FILE                 *File,
  IN EFI_GUID                 *InformationType,
  IN UINTN                    BufferSize,
  IN VOID                     *Buffer
  )
/*++

  Routine Description:
    Set information about a file

  Arguments:
    File            - Protocol instance pointer.
    InformationType - Type of info in Buffer
    BufferSize      - Size of buffer.
    Buffer          - The data to write.

  Returns:
    EFI_SUCCES           - Data was returned.
    EFI_UNSUPPORT        - InformationType is not supported
    EFI_NO_MEDIA         - The device has no media
    EFI_DEVICE_ERROR     - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED  - The device is write protected
    EFI_ACCESS_DENIED    - The file was open for read only
--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH) (
  IN EFI_FILE  *File
  )
/*++

  Routine Description:
    Flush data back for the file handle

  Arguments:
    File  - Protocol instance pointer.

  Returns:
    EFI_SUCCES           - Data was written.
    EFI_UNSUPPORT        - Writes to Open directory are not supported
    EFI_NO_MEDIA         - The device has no media
    EFI_DEVICE_ERROR     - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED  - The device is write protected
    EFI_ACCESS_DENIED    - The file was open for read only
    EFI_VOLUME_FULL      - The volume is full

--*/
;

#if EFI_FILE_HANDLE_REVISION >= 0x00020000

#define FILEIOENTITY_SIGNATURE   EFI_SIGNATURE_32('f','i','o','2')

typedef struct {
  EFI_EVENT                Event;
  EFI_STATUS               Status;
  UINTN                    BufferSize;
  VOID                     *Buffer;
} EFI_FILE_IO_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN_EX) (
  IN EFI_FILE               *File,
  OUT EFI_FILE              **NewHandle,
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
(EFIAPI *EFI_FILE_READ_EX) (
  IN EFI_FILE                  *File,
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
(EFIAPI *EFI_FILE_WRITE_EX) (
  IN EFI_FILE                *File,
  IN OUT EFI_FILE_IO_TOKEN   *Token
)
/*++

  Routine Description:
    Write data from to the file.

  Arguments:
    File       - Protocol instance pointer.
    BufferSize - On input size of buffer, on output amount of data in buffer.
    Buffer     - The buffer in which data to write.

  Returns:
    EFI_SUCCES           - Data was written.
    EFI_UNSUPPORT        - Writes to Open directory are not supported
    EFI_NO_MEDIA         - The device has no media
    EFI_DEVICE_ERROR     - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED  - The device is write protected
    EFI_ACCESS_DENIED    - The file was open for read only
    EFI_VOLUME_FULL      - The volume is full

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH_EX) (
  IN EFI_FILE                *File,
  IN OUT EFI_FILE_IO_TOKEN   *Token
)
/*++

  Routine Description:
    Flush data back for the file handle

  Arguments:
    File  - Protocol instance pointer.

  Returns:
    EFI_SUCCES           - Data was written.
    EFI_UNSUPPORT        - Writes to Open directory are not supported
    EFI_NO_MEDIA         - The device has no media
    EFI_DEVICE_ERROR     - The device reported an error
    EFI_VOLUME_CORRUPTED - The file system structures are corrupted
    EFI_WRITE_PROTECTED  - The device is write protected
    EFI_ACCESS_DENIED    - The file was open for read only
    EFI_VOLUME_FULL      - The volume is full

--*/
;
#endif

#if EFI_FILE_HANDLE_REVISION >= 0x00020000
  #define EFI_FILE_HANDLE_REVISION         0x00020000

  struct _EFI_FILE {
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
  };
#else
  #define EFI_FILE_HANDLE_REVISION         0x00010000

  struct _EFI_FILE {
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
  };
#endif

typedef struct _EFI_FILE *EFI_FILE_HANDLE;

extern EFI_GUID gBlackBoxEfiSimpleFileSystemProtocolGuid;

#endif
