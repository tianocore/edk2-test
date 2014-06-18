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

  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.

--*/

#ifndef __SCTLIB_H__
#define __SCTLIB_H__

#include "Efi.h"

#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)
#include EDK_PROTOCOL_DEFINITION (FileInfo)


//
// Allocation API
//

VOID *
SctAllocatePool (
  IN UINTN                          Size
  );

VOID *
SctAllocateCopyPool (
  IN  UINTN                         AllocationSize,
  IN  VOID                          *Buffer
  );

VOID *
SctAllocateZeroPool (
  IN UINTN                          Size
  );

VOID *
SctReallocatePool (
  IN VOID                           *OldPool,
  IN UINTN                          OldSize,
  IN UINTN                          NewSize
  );

VOID
SctFreePool (
  IN VOID                           *p
  );

//
// Console API
//

VOID
SctInput (
  IN CHAR16    *Prompt OPTIONAL,
  OUT CHAR16   *InStr,
  IN UINTN     StrLen
  );

EFI_STATUS
SctStallForKey (
  IN UINTN             Seconds,
  OUT EFI_INPUT_KEY    *Key
  );

//
// Device Path API
//
#ifndef END_DEVICE_PATH_LENGTH
  #define END_DEVICE_PATH_LENGTH               (sizeof (EFI_DEVICE_PATH_PROTOCOL))
#endif

#ifndef EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE
  #define EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE  0xff
#endif

#ifndef EFI_END_INSTANCE_DEVICE_PATH
  #define EFI_END_INSTANCE_DEVICE_PATH  0x01
#endif

#define SctDevicePathNodeLength(a)     ( ((a)->Length[0]) | ((a)->Length[1] << 8) )

#define SctNextDevicePathNode(a)  ((EFI_DEVICE_PATH_PROTOCOL *) (((UINT8 *) (a)) + SctDevicePathNodeLength (a)))

#define SctDevicePathType(a)  (((a)->Type) & 0x7f)
#define SctDevicePathSubType(a)  ((a)->SubType)
#define SctIsDevicePathEndType(a) (SctDevicePathType (a) == 0x7f)
#define SctIsDevicePathEndSubType(a)  ((a)->SubType == EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE)
#define SctIsDevicePathEnd(a) (SctIsDevicePathEndType (a) && SctIsDevicePathEndSubType (a))

UINT16
SctSetDevicePathNodeLength (
  IN OUT VOID  *Node,
  IN UINTN     Length
  );

VOID
SctSetDevicePathEndNode (
  OUT VOID  *Node
  );

EFI_DEVICE_PATH_PROTOCOL *
SctDevicePathInstance (
  IN OUT EFI_DEVICE_PATH_PROTOCOL   **DevicePath,
  OUT UINTN                         *Size
  );

EFI_DEVICE_PATH_PROTOCOL *
SctFileDevicePath (
  IN EFI_HANDLE                     Device  OPTIONAL,
  IN CHAR16                         *FileName
  );

EFI_DEVICE_PATH_PROTOCOL *
SctDevicePathFromHandle (
  IN EFI_HANDLE       Handle
  );

UINT16 *
SctDevicePathStrFromProtocol (
  IN VOID        *Protocol,
  IN EFI_GUID    *Guid
  );

EFI_DEVICE_PATH_PROTOCOL *
SctAppendDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL       *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL       *Src2
  );

EFI_DEVICE_PATH_PROTOCOL *
SctAppendDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL       *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL       *Src2
  );

UINTN
SctDevicePathSize (
  IN EFI_DEVICE_PATH_PROTOCOL       *DevPath
  );

EFI_DEVICE_PATH_PROTOCOL *
SctDuplicateDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL       *DevPath
  );

EFI_DEVICE_PATH_PROTOCOL *
SctUnpackDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL       *DevPath
  );

CHAR16 *
SctDevicePathToStr (
  EFI_DEVICE_PATH_PROTOCOL          *DevPath
  );

BOOLEAN
SctMatchDevicePaths (
  IN  EFI_DEVICE_PATH_PROTOCOL *Multi,
  IN  EFI_DEVICE_PATH_PROTOCOL *Single
  );

EFI_STATUS
SctDevicePathToInterface (
  IN EFI_GUID                   *Protocol,
  IN EFI_DEVICE_PATH_PROTOCOL   *FilePath,
  OUT VOID                      **Interface
  );

//
// Event API
//

EFI_STATUS
SctWaitForSingleEvent (
  IN EFI_EVENT        Event,
  IN UINT64           Timeout OPTIONAL
  );

//
// File API
//

EFI_STATUS
SctOpenFileByName (
  IN  CHAR16                            *FileName,
  OUT EFI_FILE_HANDLE                   *FileHandle,
  IN UINT64                             OpenMode,
  IN UINT64                             Attributes
  );

EFI_STATUS
SctCloseFile (
  IN EFI_FILE_HANDLE     FileHandle
  );

EFI_STATUS
SctReadFile (
  IN EFI_FILE_HANDLE      FileHandle,
  IN OUT UINTN            *ReadSize,
  OUT VOID                *Buffer
  );

EFI_STATUS
SctWriteFile (
  IN EFI_FILE_HANDLE    FileHandle,
  IN OUT UINTN          *BufferSize,
  OUT VOID              *Buffer
  );

EFI_STATUS
SctFlushFile (
  IN EFI_FILE_HANDLE FileHandle
  );

EFI_STATUS
SctGetFileInfo (
  IN  EFI_FILE_HANDLE      FileHandle,
  OUT EFI_FILE_INFO      **FileInfo
  );

EFI_FILE_HANDLE
SctOpenRoot (
  IN EFI_HANDLE                   DeviceHandle
  );

EFI_STATUS
SctCreateDirectory (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName
  );

EFI_STATUS
SctCreateFile (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName,
  OUT EFI_FILE_HANDLE             *Handle
  );

//
// Public read-only data in the EFI library
//

extern EFI_SYSTEM_TABLE         *tST;
extern EFI_BOOT_SERVICES        *tBS;
extern EFI_RUNTIME_SERVICES     *tRT;

//
// Init API
//
EFI_STATUS
SctInitializeLib (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
SctInitializeDriver (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

//
// List API
//

#define INITIALIZE_SCT_LIST_HEAD_VARIABLE(ListHead)  {&ListHead, &ListHead}

typedef struct _SCT_LIST_ENTRY {
  struct _SCT_LIST_ENTRY  *ForwardLink;
  struct _SCT_LIST_ENTRY  *BackLink;
} SCT_LIST_ENTRY;

VOID
SctInitializeListHead (
  SCT_LIST_ENTRY       *List
  );

SCT_LIST_ENTRY *
SctGetFirstNode (
  CONST SCT_LIST_ENTRY  *List
  );

SCT_LIST_ENTRY *
SctGetNextNode (
  CONST SCT_LIST_ENTRY  *List,
  CONST SCT_LIST_ENTRY  *Node
  );

BOOLEAN
SctIsListEmpty (
  CONST SCT_LIST_ENTRY  *List
  );

BOOLEAN
SctIsNull (
  CONST SCT_LIST_ENTRY  *List,
  CONST SCT_LIST_ENTRY  *Node
  );

VOID
SctRemoveEntryList (
  SCT_LIST_ENTRY  *Entry
  );

VOID
SctInsertTailList (
  SCT_LIST_ENTRY  *ListHead,
  SCT_LIST_ENTRY  *Entry
  );

VOID
SctInsertHeadList (
  SCT_LIST_ENTRY  *ListHead,
  SCT_LIST_ENTRY  *Entry
  );

BOOLEAN
SctIsNodeAtEnd (
  CONST SCT_LIST_ENTRY  *List,
  CONST SCT_LIST_ENTRY  *Node
  );

//
// Math API
//

UINT64
SctLShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  );

UINT64
SctRShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  );

UINT64
SctMultU64x32 (
  IN UINT64                         Multiplicand,
  IN UINTN                          Multiplier
  );

UINT64
SctDivU64x32 (
  IN UINT64                         Dividend,
  IN UINTN                          Divisor,
  OUT UINTN                         *Remainder OPTIONAL
  );

//
// Lock API
//

typedef struct {
    EFI_TPL     Tpl;
    EFI_TPL     OwnerTpl;
    UINTN       Lock;
} SCT_LOCK;

#define SCT_INITIALIZE_LOCK_VARIABLE(Tpl) {Tpl,0,0}

VOID
SctInitializeLock (
  IN OUT SCT_LOCK                   *Lock,
  IN EFI_TPL                        Priority
  );

VOID
SctAcquireLock (
  IN SCT_LOCK                       *Lock
  );

VOID
SctReleaseLock (
  IN SCT_LOCK                       *Lock
  );

EFI_STATUS
SctAcquireLockOrFail (
  IN SCT_LOCK  *Lock
  );

//
// Match API
//

BOOLEAN
SctMetaMatch (
  IN CHAR16                         *String,
  IN CHAR16                         *Pattern
  );

BOOLEAN
SctMetaiMatch (
  IN CHAR16                         *String,
  IN CHAR16                         *Pattern
  );

//
// Memory API
//

VOID
SctZeroMem (
  IN VOID                           *Buffer,
  IN UINTN                          Size
  );

VOID*
SctSetMem (
  IN VOID                           *Buffer,
  IN UINTN                          Size,
  IN UINT8                          Value
  );

VOID
SctCopyMem (
  IN VOID                           *Dest,
  IN CONST VOID                     *Src,
  IN UINTN                          len
  );

INTN
SctCompareMem (
  IN VOID                           *Dest,
  IN VOID                           *Src,
  IN UINTN                          len
  );

//
// Misc API
//

INTN
SctCompareGuid (
  IN EFI_GUID                       *Guid1,
  IN EFI_GUID                       *Guid2
  );

EFI_STATUS
SctCalculateCrc32 (
  IN     UINT8                          *Data,
  IN     UINTN                          DataSize,
  IN OUT UINT32                         *CrcOut
  );

BOOLEAN
SctGrowBuffer (
  IN OUT EFI_STATUS   *Status,
  IN OUT VOID         **Buffer,
  IN UINTN            BufferSize
  );

UINT16
SctSwapBytes16 (
  IN      UINT16                    Value
  );

UINT32
SctSwapBytes32 (
  IN      UINT32                    Value
  );

UINT16
SctWriteUnaligned16 (
  OUT UINT16                    *Buffer,
  IN  UINT16                    Value
  );

UINT32
SctWriteUnaligned32 (
  OUT UINT32                    *Buffer,
  IN  UINT32                    Value
  );

UINT64
SctReadTsc (
  VOID
  );

//
// Print API
//

typedef struct {
  CHAR16                            *str;
  UINTN                             len;
  UINTN                             maxlen;
} SCT_POOL_PRINT;

UINTN
SctPrintAt (
  IN UINTN                          Column,
  IN UINTN                          Row,
  IN CONST CHAR16                   *fmt,
  ...
  );

UINTN
SctPrint (
  IN CONST CHAR16                   *fmt,
  ...
  );

UINTN
SctAPrint (
  IN CHAR8                          *fmt,
  ...
  );

UINTN
SctSPrint (
  OUT CHAR16  *Str,
  IN UINTN    StrSize,
  IN CHAR16   *fmt,
  ...
  );

UINTN
SctASPrint (
  OUT CHAR8   *Str,
  IN UINTN    StrSize,
  IN CHAR8    *fmt,
  ...
  );

UINTN
SctVSPrint (
  OUT CHAR16                        *Str,
  IN UINTN                          StrSize,
  IN CONST CHAR16                   *fmt,
  IN VA_LIST                        vargs
  );

CHAR16 *
SctPoolPrint (
  IN CONST CHAR16                   *fmt,
  ...
  );

CHAR16 *
SctCatPrint (
    IN OUT SCT_POOL_PRINT   *Str,
    IN CONST CHAR16     *fmt,
    ...
    );

//
// Protocol & Handle API
//

#define SCT_HANDLE_TYPE_UNKNOWN                      0x000
#define SCT_HANDLE_TYPE_IMAGE_HANDLE                 0x001
#define SCT_HANDLE_TYPE_DRIVER_BINDING_HANDLE        0x002
#define SCT_HANDLE_TYPE_DEVICE_DRIVER                0x004
#define SCT_HANDLE_TYPE_BUS_DRIVER                   0x008
#define SCT_HANDLE_TYPE_DRIVER_CONFIGURATION_HANDLE  0x010
#define SCT_HANDLE_TYPE_DRIVER_DIAGNOSTICS_HANDLE    0x020
#define SCT_HANDLE_TYPE_COMPONENT_NAME_HANDLE        0x040
#define SCT_HANDLE_TYPE_DEVICE_HANDLE                0x080
#define SCT_HANDLE_TYPE_PARENT_HANDLE                0x100
#define SCT_HANDLE_TYPE_CONTROLLER_HANDLE            0x200
#define SCT_HANDLE_TYPE_CHILD_HANDLE                 0x400

EFI_STATUS
SctGetSystemConfigurationTable (
  IN EFI_GUID                       *TableGuid,
  IN OUT VOID                       **Table
  );

EFI_STATUS
SctLocateProtocol (
  IN  EFI_GUID    *ProtocolGuid,
  OUT VOID        **Interface
  );

EFI_STATUS
SctGetPeiProtocol (
  IN EFI_GUID      *ProtocolGuid,
  IN OUT VOID      **Interface
  );

EFI_STATUS
SctLocateHandle (
  IN EFI_LOCATE_SEARCH_TYPE       SearchType,
  IN EFI_GUID                     *Protocol OPTIONAL,
  IN VOID                         *SearchKey OPTIONAL,
  IN OUT UINTN                    *NoHandles,
  OUT EFI_HANDLE                  **Buffer
  );

EFI_STATUS
SctScanHandleDatabase (
  EFI_HANDLE  DriverBindingHandle,       OPTIONAL
  UINT32      *DriverBindingHandleIndex, OPTIONAL
  EFI_HANDLE  ControllerHandle,          OPTIONAL
  UINT32      *ControllerHandleIndex,    OPTIONAL
  UINTN       *HandleCount,
  EFI_HANDLE  **HandleBuffer,
  UINT32      **HandleType
  );

EFI_STATUS
SctGetManagedChildControllerHandles (
  EFI_HANDLE  DriverBindingHandle,
  EFI_HANDLE  ControllerHandle,
  UINTN       *ChildControllerHandleCount,
  EFI_HANDLE  **ChildControllerHandleBuffer
  );

EFI_STATUS
SctGetManagedControllerHandles (
  EFI_HANDLE  DriverBindingHandle,
  UINTN       *ControllerHandleCount,
  EFI_HANDLE  **ControllerHandleBuffer
  );

//
// Shell API
//

typedef VOID *SHELL_FILE_HANDLE;

typedef struct {
  SCT_LIST_ENTRY    Link;       ///< Linked list members.
  EFI_STATUS        Status;     ///< Status of opening the file.  Valid only if Handle != NULL.
  CONST CHAR16      *FullName;  ///< Fully qualified filename.
  CONST CHAR16      *FileName;  ///< name of this file.
  SHELL_FILE_HANDLE Handle;     ///< Handle for interacting with the opened file or NULL if closed.
  EFI_FILE_INFO     *Info;      ///< Pointer to the FileInfo struct for this file or NULL.
} EFI_SHELL_FILE_INFO;

EFI_STATUS
SctShellApplicationInit (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

EFI_STATUS
SctShellGetArguments (
  OUT UINTN           *Argc,
  OUT CHAR16          ***Argv
  );

EFI_STATUS
SctShellExecute (
  IN EFI_HANDLE       *ImageHandle,
  IN CHAR16           *CmdLine,
  IN BOOLEAN          Output,
  IN CHAR16           **EnvironmentVariables OPTIONAL,
  OUT EFI_STATUS      *Status OPTIONAL
  );

EFI_STATUS
SctShellMapToDevicePath (
  IN  CHAR16                    *Name,
  OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath
  );

EFI_STATUS
SctShellOpenFileMetaArg (
  IN CHAR16                     *Arg,
  IN UINT64                     OpenMode,
  IN OUT SCT_LIST_ENTRY         **ListHead
  );

EFI_STATUS
EFIAPI
SctShellCloseFileMetaArg (
  IN OUT SCT_LIST_ENTRY         **ListHead
  );

EFI_STATUS
SctShellFreeFileList (
  IN OUT SCT_LIST_ENTRY   *ListHead
  );

BOOLEAN
SctShellGetExecutionBreak (
  IN VOID
  );

EFI_STATUS
SctShellFilterNullArgs (
  VOID
  );

EFI_DEVICE_PATH_PROTOCOL *
SctShellGetDevicePathFromFilePath (
  IN CONST CHAR16   *Path
  );

CONST CHAR16*
EFIAPI
ShellGetCurrentDir (
  IN CHAR16                     * CONST DeviceName OPTIONAL
  );

EFI_STATUS
SctExpandRelativePath (
  IN CHAR16                       *RelativePath,
  OUT CHAR16                      **FileName
  );

EFI_STATUS
SctGetFilesystemDevicePath (
  IN CHAR16                      *FilePath,
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  OUT CHAR16                    **RemainingFilePath OPTIONAL
  );
//
// String API
//

#define LEFT_JUSTIFY  0x01
#define PREFIX_SIGN   0x02
#define PREFIX_BLANK  0x04
#define COMMA_TYPE    0x08
#define LONG_TYPE     0x10
#define PREFIX_ZERO   0x20

INTN
SctStrCmp (
  IN CONST CHAR16                   *s1,
  IN CONST CHAR16                   *s2
  );

INTN
SctStrnCmp (
  IN CONST CHAR16                   *s1,
  IN CONST CHAR16                   *s2,
  IN UINTN                          len
  );

INTN
SctStriCmp (
  IN CONST CHAR16                   *s1,
  IN CONST CHAR16                   *s2
  );

VOID
SctStrLwr (
  IN CHAR16                   *Str
  );

VOID
SctStrUpr (
  IN CHAR16                   *Str
  );

VOID
SctStrCpy (
  IN CHAR16                         *Dest,
  IN CONST CHAR16                   *Src
  );

VOID
SctStrnCpy (
  OUT CHAR16                   *Dst,
  IN  CONST CHAR16             *Src,
  IN  UINTN                    Length
  );

VOID
StrTrim (
  IN OUT CHAR16                     *str,
  IN     CHAR16                     c
  );

VOID
SctStrCat (
  IN CHAR16                         *Dest,
  IN CONST CHAR16                   *Src
  );

CHAR16 *
SctStrChr (
  IN  CHAR16  *Str,
  IN  CHAR16  c
  );

UINTN
SctStrLen (
  IN CONST CHAR16                   *s1
  );

UINTN
SctStrSize (
  IN CONST CHAR16                   *s1
  );

CHAR16 *
SctStrDuplicate (
  IN CONST CHAR16                   *Src
  );

CHAR16*
SctStrStr (
  IN  CONST CHAR16  *Str,
  IN  CONST CHAR16  *Pat
  );

CHAR8 *
SctAsciiStrDuplicate (
  CHAR8 CONST  *str
  );

CHAR8 *
EFIAPI
SctAsciiStrCpy (
  OUT     CHAR8                     *Destination,
  IN      CONST CHAR8               *Source
  );

CHAR8 *
SctAsciiStrnCpy (
  CHAR8       *dst,
  CHAR8       *src,
  UINTN       n
  );

UINTN
EFIAPI
SctAsciiStrLen (
  IN      CONST CHAR8               *String
  );

UINTN
SctAsciiStrSize (
  IN CONST CHAR8   *String
  );

INTN
SctAsciiStriCmp (
  IN CONST CHAR8       *s1,
  IN CONST CHAR8       *s2
  );

CHAR8 *
EFIAPI
SctAsciiStrCat (
  IN OUT CHAR8    *Destination,
  IN CONST CHAR8  *Source
  );

UINTN
SctAsciiStrCmp (
  IN CHAR8                          *s1,
  IN CHAR8                          *s2
  );

UINTN
SctAsciiStrnCmp (
  IN CHAR8                          *s1,
  IN CHAR8                          *s2,
  IN UINTN                          len
  );

CHAR8*
EFIAPI
SctAsciiStrChr (
  IN  CHAR8  *String,
  IN  CHAR8  c
  );

CHAR8*
EFIAPI
SctAsciiStrStr (
  IN  CHAR8  *String,
  IN  CHAR8  *StrCharSet
  );

UINTN
SctXtoi (
  CHAR16                            *str
  );

UINTN
SctAtoi (
  CHAR16                            *str
  );

UINTN
SctStrToUInt (
  IN  CHAR16       *Str
  );

VOID
SctStrToUInt64 (
  IN  CHAR16       *Str,
  OUT UINT64       *Result
  );

VOID
SctValueToHexStr (
  IN CHAR16      *Buffer,
  IN UINT64      v,
  IN UINTN       Flags,
  IN UINTN       Width
  );

VOID
SctStrToAscii (
  IN CHAR16 *Str,
  IN CHAR8  *AsciiStr
  );

CHAR16 *
SctSplitStr (
  IN OUT CHAR16 **List,
  IN     CHAR16 Separator
  );

CHAR8 *
SctAsciiSplitStr (
  IN OUT CHAR8 **List,
  IN     CHAR8 Separator
  );

VOID
SctStrToIPv4Addr (
  IN OUT CHAR16           **Str,
  OUT    EFI_IPv4_ADDRESS *IPv4Addr
  );

VOID
SctStrToIPv6Addr (
  IN OUT CHAR16           **Str,
  OUT    EFI_IPv6_ADDRESS *IPv6Addr
  );

VOID
SctValueToHexStr (
  IN CHAR16      *Buffer,
  IN UINT64      v,
  IN UINTN       Flags,
  IN UINTN       Width
  );

BOOLEAN
SctIsHexDigit (
  OUT UINT8      *Digit,
  IN  CHAR16      Char
  );

CHAR16
SctNibbleToHexChar (
  IN UINT8      Nibble
  );

EFI_STATUS
SctHexStringToBuf (
  IN OUT UINT8                     *Buf,
  IN OUT UINTN                    *Len,
  IN     CHAR16                    *Str,
  OUT    UINTN                     *ConvertedStrLen  OPTIONAL
  );

EFI_STATUS
SctBufToHexString (
  IN OUT CHAR16                    *Str,
  IN OUT UINTN                     *HexStringBufferLength,
  IN     UINT8                     *Buf,
  IN     UINTN                      Len
  );

UINTN
SctUnicodeToAscii (
  CHAR8       *s,
  CHAR16      *pwcs,
  UINTN       n
  );

UINTN
SctAsciiToUnicode (
  CHAR16      *pwcs,
  CHAR8       *s,
  UINTN       n
  );

VOID
SctStrTrim (
  IN OUT CHAR16   *str,
  IN     CHAR16   c
  );

//
// Unicode API
//

typedef struct {
  CHAR8   *Language;
  CHAR16  *UnicodeString;
} SCT_UNICODE_STRING_TABLE;

EFI_STATUS
SctLookupUnicodeString (
  IN  CHAR8                     *Language,
  IN  CHAR8                     *SupportedLanguages,
  IN  SCT_UNICODE_STRING_TABLE  *UnicodeStringTable,
  OUT CHAR16                    **UnicodeString
  );

//
// HOB API
//

VOID  *
SctGetHob (
  IN UINT16  Type,
  IN VOID    *HobStart
  );

UINTN
SctGetHobListSize (
  IN VOID  *HobStart
  );

UINT32
SctGetHobVersion (
  IN VOID  *HobStart
  );

EFI_STATUS
SctGetHobBootMode (
  IN  VOID           *HobStart,
  OUT EFI_BOOT_MODE  *BootMode
  );

EFI_STATUS
SctGetCpuHobInfo (
  IN  VOID   *HobStart,
  OUT UINT8  *SizeOfMemorySpace,
  OUT UINT8  *SizeOfIoSpace
  );

EFI_STATUS
SctGetDxeCoreHobInfo (
  IN  VOID                  *HobStart,
  OUT EFI_PHYSICAL_ADDRESS  *BaseAddress,
  OUT UINT64                *Length,
  OUT VOID                  **EntryPoint,
  OUT EFI_GUID              **FileName
  );

EFI_STATUS
SctGetNextFirmwareVolumeHob (
  IN OUT VOID                  **HobStart,
  OUT    EFI_PHYSICAL_ADDRESS  *BaseAddress,
  OUT    UINT64                *Length
  );

#if (PI_SPECIFICATION_VERSION >= 0x00010000)
EFI_STATUS
GetNextFirmwareVolume2Hob (
  IN OUT VOID                  **HobStart,
  OUT    EFI_PHYSICAL_ADDRESS  *BaseAddress,
  OUT    UINT64                *Length,
  OUT    EFI_GUID              *FileName
  );
#endif

EFI_STATUS
SctGetNextGuidHob (
  IN OUT VOID      **HobStart,
  IN     EFI_GUID  * Guid,
  OUT    VOID      **Buffer,
  OUT    UINTN     *BufferSize OPTIONAL
  );

EFI_STATUS
GetPalEntryHobInfo (
  IN  VOID                  *HobStart,
  OUT EFI_PHYSICAL_ADDRESS  *PalEntry
  );

EFI_STATUS
GetIoPortSpaceAddressHobInfo (
  IN  VOID                  *HobStart,
  OUT EFI_PHYSICAL_ADDRESS  *IoPortSpaceAddress
  );

//
// EFI Driver Model Helpers
//

EFI_STATUS
SctInstallAllDriverProtocols (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   * SystemTable,
  IN VOID* DriverBindingProtocol,
  IN EFI_HANDLE                         DriverBindingHandle,
  IN VOID* ComponentNameProtocol, OPTIONAL
  IN VOID* DriverConfigurationProtocol, OPTIONAL
  IN VOID* DriverDiagnosticsProtocol OPTIONAL
  );

EFI_STATUS
SctInstallAllDriverProtocols2 (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   * SystemTable,
  IN VOID* DriverBindingProtocol,
  IN EFI_HANDLE                         DriverBindingHandle,
  IN VOID* ComponentName2Protocol, OPTIONAL
  IN VOID* DriverConfiguration2Protocol, OPTIONAL
  IN VOID* DriverDiagnostics2Protocol OPTIONAL
  );

#endif
