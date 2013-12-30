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

  EfiTestUtilityLib.h

Abstract:

EFI Test Utility library functions

--*/

#ifndef _EFI_TEST_UTILITY_LIB_H_
#define _EFI_TEST_UTILITY_LIB_H_

//
// Disabling bitfield type checking warnings.
//
#ifndef __GNUC__
#pragma warning ( disable : 4214 )
#endif

#include "efipart.h"
#include "efilibplat.h"
#include "LinkedList.h"
#include "pci22.h"
#include "LibSmbios.h"
#include "EfiUi.h"
#include "Intload.h"
#include "AdapterDebug.h"
#include "EfiPerf.h"
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)
#include EFI_PROTOCOL_DEFINITION (FileInfo)
#include EFI_PROTOCOL_DEFINITION (FileSystemInfo)
#include EFI_PROTOCOL_DEFINITION (FileSystemVolumeLabelInfo)
#include EFI_PROTOCOL_DEFINITION (BlockIo)
#include EFI_PROTOCOL_DEFINITION (DeviceIo)
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
#include "TianoHii.h"
#else
#include EFI_PROTOCOL_DEFINITION (Hii)
#endif
//
// Public read-only data in the EFI library
//

extern EFI_SYSTEM_TABLE         *tST;
extern EFI_BOOT_SERVICES        *tBS;
extern EFI_RUNTIME_SERVICES     *tRT;

extern EFI_GUID gtEfiDevicePathProtocolGuid;
extern EFI_GUID gtEfiLoadedImageProtocolGuid;
extern EFI_GUID gtEfiSimpleTextInProtocolGuid;
extern EFI_GUID gtEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gtEfiBlockIoProtocolGuid;
extern EFI_GUID gtEfiDiskIoProtocolGuid;
extern EFI_GUID gtEfiSimpleFileSystemProtocolGuid;
extern EFI_GUID gtEfiLoadFileProtocolGuid;
extern EFI_GUID gtEfiDeviceIoProtocolGuid;
extern EFI_GUID gtEfiVariableStoreProtocolGuid;
extern EFI_GUID gtEfiLegacyBootProtocolGuid;
extern EFI_GUID gtEfiUnicodeCollationProtocolGuid;
extern EFI_GUID gtEfiSerialIoProtocolGuid;
extern EFI_GUID gtEfiVgaClassProtocolGuid;
extern EFI_GUID tTextOutSpliterProtocol;
extern EFI_GUID tErrorOutSpliterProtocol;
extern EFI_GUID tTextInSpliterProtocol;
extern EFI_GUID gtEfiSimpleNetworkProtocolGuid;
extern EFI_GUID gtEfiPxeBaseCodeProtocolGuid;
extern EFI_GUID gtEfiPxeCallbackProtocolGuid;
extern EFI_GUID gtEfiNetworkInterfaceIdentifierProtocolGuid;
extern EFI_GUID tUiProtocol;
extern EFI_GUID gtEfiInternalShellProtocolGuid;

extern EFI_GUID tEfiGlobalVariable;
extern EFI_GUID tGenericFileInfo;
extern EFI_GUID gtEfiFileSystemInfoGuid;
extern EFI_GUID gtEfiFileSystemVolumeLabelInfoGuid;
extern EFI_GUID tPcAnsiProtocol;
extern EFI_GUID tVt100Protocol;
extern EFI_GUID tNullGuid;
extern EFI_GUID gtEfiUnknownDeviceGuid;

extern EFI_GUID gtEfiPartTypeSystemPartitionGuid;
extern EFI_GUID gtEfiPartTypeLegacyMbrGuid;

extern EFI_GUID gtEfiMpsTableGuid;
extern EFI_GUID gtEfiAcpiTableGuid;
extern EFI_GUID gtEfiAcpi20TableGuid;
extern EFI_GUID gtEfiSMBIOSTableGuid;
extern EFI_GUID gtEfiSalSystemTableGuid;

//
// EFI Variable strings
//
#define LOAD_OPTION_ACTIVE          0x00000001

#define VarLanguageCodes            L"LangCodes"
#define VarLanguage                 L"Lang"
#define VarTimeout                  L"Timeout"
#define VarConsoleInp               L"ConIn"
#define VarConsoleOut               L"ConOut"
#define VarErrorOut                 L"ErrOut"
#define VarBootOption               L"Boot%04x"
#define VarBootOrder                L"BootOrder"
#define VarBootNext                 L"BootNext"
#define VarBootCurrent              L"BootCurrent"
#define VarDriverOption             L"Driver%04x"
#define VarDriverOrder              L"DriverOrder"
#define VarConsoleInpDev            L"ConInDev"
#define VarConsoleOutDev            L"ConOutDev"
#define VarErrorOutDev              L"ErrOutDev"

#define LanguageCodeEnglish         "eng"

extern EFI_DEVICE_PATH_PROTOCOL     *RootDevicePath ;
extern EFI_DEVICE_PATH_PROTOCOL     EndDevicePath[];
extern EFI_DEVICE_PATH_PROTOCOL     EndInstanceDevicePath[];

//
// Other public data in the EFI library
//

extern EFI_MEMORY_TYPE              PoolAllocationType;

//
// Prototypes
//

VOID
InitializeLib (
  IN EFI_HANDLE                     ImageHandle,
  IN EFI_SYSTEM_TABLE               *SystemTable
  );

VOID
InitializeUnicodeSupport (
  CHAR8                             *LangCode
  );

VOID
EFIDebugVariable (
  VOID
  );

VOID
SetCrc (
  IN OUT EFI_TABLE_HEADER           *Hdr
  );

VOID
SetCrcAltSize (
  IN UINTN                          Size,
  IN OUT EFI_TABLE_HEADER           *Hdr
  );

BOOLEAN
CheckCrc (
  IN UINTN                          MaxSize,
  IN OUT EFI_TABLE_HEADER           *Hdr
  );

BOOLEAN
CheckCrcAltSize (
  IN UINTN                          MaxSize,
  IN UINTN                          Size,
  IN OUT EFI_TABLE_HEADER           *Hdr
  );

UINT32
CalculateCrc (
  UINT8 *pt,
  UINTN Size
  );

VOID
ZeroMem (
  IN VOID                           *Buffer,
  IN UINTN                          Size
  );

VOID
SetMem (
  IN VOID                           *Buffer,
  IN UINTN                          Size,
  IN UINT8                          Value
  );

VOID
CopyMem (
  IN VOID                           *Dest,
  IN VOID                           *Src,
  IN UINTN                          len
  );

INTN
CompareMem (
  IN VOID                           *Dest,
  IN VOID                           *Src,
  IN UINTN                          len
  );

INTN
StrCmp (
  IN CHAR16                         *s1,
  IN CHAR16                         *s2
  );

INTN
StrnCmp (
  IN CHAR16                         *s1,
  IN CHAR16                         *s2,
  IN UINTN                          len
  );

INTN
StriCmp (
  IN CHAR16                         *s1,
  IN CHAR16                         *s2
  );

VOID
StrLwr (
  IN CHAR16                         *Str
  );

VOID
StrUpr (
  IN CHAR16                         *Str
  );

VOID
StrCpy (
  IN CHAR16                         *Dest,
  IN CHAR16                         *Src
  );

VOID
StrnCpy (
  OUT CHAR16                   *Dst,
  IN  CHAR16                   *Src,
  IN  UINTN                    Length
  );

VOID
StrTrim (
  IN OUT CHAR16                     *str,
  IN     CHAR16                     c
  );

VOID
StrCat (
  IN CHAR16                         *Dest,
  IN CHAR16                         *Src
  );

CHAR16 *
StrChr (
  IN  CHAR16  *Str,
  IN  CHAR16  c
  );

CHAR8 *
StrChrAscii (
  IN  CHAR8  *Str,
  IN  CHAR8  c
  );

UINTN
StrLen (
  IN CHAR16                         *s1
  );

UINTN
StrSize (
  IN CHAR16                         *s1
  );

CHAR16 *
StrDuplicate (
  IN CHAR16                         *Src
  );

UINTN
strlena (
  IN CHAR8                          *s1
  );

UINTN
strcmpa (
  IN CHAR8                          *s1,
  IN CHAR8                          *s2
  );

UINTN
strncmpa (
  IN CHAR8                          *s1,
  IN CHAR8                          *s2,
  IN UINTN                          len
  );

UINTN
xtoi (
  CHAR16                            *str
  );

UINTN
Atoi (
  CHAR16                            *str
  );

UINTN
StrToUInt (
  IN  CHAR16       *Str
  );

VOID
StrToUInt64 (
  IN  CHAR16       *Str,
  OUT UINT64       *Result
  );

VOID
StrToAscii (
  IN CHAR16 *Str,
  IN CHAR8  *AsciiStr
  );

CHAR16 *
SplitStr (
  IN OUT CHAR16 **List,
  IN     CHAR16 Separator
  );

CHAR8 *
SplitStrAscii (
  IN OUT CHAR8 **List,
  IN     CHAR8 Separator
  );

VOID
StrToIPv4Addr (
  IN OUT CHAR16           **Str,
  OUT    EFI_IPv4_ADDRESS *IPv4Addr
  );

VOID
StrToIPv6Addr (
  IN OUT CHAR16           **Str,
  OUT    EFI_IPv6_ADDRESS *IPv6Addr
  );

BOOLEAN
MetaMatch (
  IN CHAR16                         *String,
  IN CHAR16                         *Pattern
  );

BOOLEAN
MetaiMatch (
  IN CHAR16                         *String,
  IN CHAR16                         *Pattern
  );

UINT64
LShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  );

UINT64
RShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  );

UINT64
MultU64x32 (
  IN UINT64                         Multiplicand,
  IN UINTN                          Multiplier
  );

UINT64
DivU64x32 (
  IN UINT64                         Dividend,
  IN UINTN                          Divisor,
  OUT UINTN                         *Remainder OPTIONAL
  );

VOID
InitializeLock (
  IN OUT FLOCK                      *Lock,
  IN EFI_TPL                        Priority
  );

VOID
AcquireLock (
  IN FLOCK                          *Lock
  );

VOID
ReleaseLock (
  IN FLOCK                          *Lock
  );

UINTN
Print (
  IN CHAR16                         *fmt,
  ...
  );

UINTN
SPrint (
  OUT CHAR16                        *Str,
  IN UINTN                          StrSize,
  IN CHAR16                         *fmt,
  ...
  );

UINTN
VSPrint (
  OUT CHAR16                        *Str,
  IN UINTN                          StrSize,
  IN CHAR16                         *fmt,
  IN VA_LIST                        vargs
  );

VOID
ValueToString (
  IN CHAR16                         *Buffer,
  IN BOOLEAN                        Comma,
  IN INT64                          v
  );

VOID
TimeToString (
  OUT CHAR16                        *Buffer,
  IN EFI_TIME                       *Time
  );

VOID
GuidToString (
  OUT CHAR16                        *Buffer,
  IN EFI_GUID                       *Guid
  );

INTN
CompareGuid(
  IN EFI_GUID                       *Guid1,
  IN EFI_GUID                       *Guid2
  );

VOID *
AllocatePool (
  IN UINTN                          Size
  );

VOID *
AllocateCopyPool (
  IN  UINTN                         AllocationSize,
  IN  VOID                          *Buffer
  );

VOID *
AllocateZeroPool (
  IN UINTN                          Size
  );

VOID *
ReallocatePool (
  IN VOID                           *OldPool,
  IN UINTN                          OldSize,
  IN UINTN                          NewSize
  );

VOID
FreePool (
  IN VOID                           *p
  );

VOID
Output (
  IN CHAR16                         *Str
  );

VOID
Input (
  IN CHAR16                         *Prompt OPTIONAL,
  OUT CHAR16                        *InStr,
  IN UINTN                          StrLen
  );

VOID
IInput (
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL   *ConOut,
  IN EFI_SIMPLE_TEXT_IN_PROTOCOL    *ConIn,
  IN CHAR16                         *Prompt OPTIONAL,
  OUT CHAR16                        *InStr,
  IN UINTN                          StrLen
  );

CHAR16 *
PoolPrint (
  IN CHAR16                         *fmt,
  ...
  );

typedef struct {
  CHAR16                            *str;
  UINTN                             len;
  UINTN                             maxlen;
} POOL_PRINT;

CHAR16 *
CatPrint (
  IN OUT POOL_PRINT                 *Str,
  IN CHAR16                         *fmt,
  ...
  );

UINTN
PrintToken (
  IN UINT16                         Token,
  IN EFI_HII_HANDLE                 Handle,
  ...
  );

UINTN
PrintAt (
  IN UINTN                          Column,
  IN UINTN                          Row,
  IN CHAR16                         *fmt,
  ...
  );

UINTN
IPrint (
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL   *Out,
  IN CHAR16                         *fmt,
  ...
  );

UINTN
IPrintAt (
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL   *Out,
  IN UINTN                          Column,
  IN UINTN                          Row,
  IN CHAR16                         *fmt,
  ...
  );

UINTN
APrint (
  IN CHAR8                          *fmt,
  ...
  );

VOID
ValueToHex (
  IN CHAR16                         *Buffer,
  IN UINT64                         v
  );

VOID
StatusToString (
  OUT CHAR16                        *Buffer,
  EFI_STATUS                        Status
  );

VOID
DumpHex (
  IN UINTN                          Indent,
  IN UINTN                          Offset,
  IN UINTN                          DataSize,
  IN VOID                           *UserData
  );

BOOLEAN
GrowBuffer(
  IN OUT EFI_STATUS                 *Status,
  IN OUT VOID                       **Buffer,
  IN UINTN                          BufferSize
  );

EFI_MEMORY_DESCRIPTOR *
LibMemoryMap (
  OUT UINTN                         *NoEntries,
  OUT UINTN                         *MapKey,
  OUT UINTN                         *DescriptorSize,
  OUT UINT32                        *DescriptorVersion
  );

VOID *
LibGetVariable (
  IN CHAR16                         *Name,
  IN EFI_GUID                       *VendorGuid
  );

VOID *
LibGetVariableAndSize (
  IN CHAR16                         *Name,
  IN EFI_GUID                       *VendorGuid,
  OUT UINTN                         *VarSize
  );

EFI_STATUS
LibDeleteVariable (
  IN CHAR16                         *VarName,
  IN EFI_GUID                       *VarGuid
  );

EFI_STATUS
LibInsertToTailOfBootOrder (
  IN  UINT16                        BootOption,
  IN  BOOLEAN                       OnlyInsertIfEmpty
  );

EFI_STATUS
LibLocateProtocol (
  IN  EFI_GUID                      *ProtocolGuid,
  OUT VOID                          **Interface
  );

EFI_STATUS
LibLocateHandle (
  IN EFI_LOCATE_SEARCH_TYPE         SearchType,
  IN EFI_GUID                       *Protocol OPTIONAL,
  IN VOID                           *SearchKey OPTIONAL,
  IN OUT UINTN                      *NoHandles,
  OUT EFI_HANDLE                    **Buffer
  );

EFI_STATUS
LibLocateHandleByDiskSignature (
  IN UINT8                          MBRType,
  IN UINT8                          SignatureType,
  IN VOID                           *Signature,
  IN OUT UINTN                      *NoHandles,
  OUT EFI_HANDLE                    **Buffer
  );

EFI_STATUS
LibInstallProtocolInterfaces (
  IN OUT EFI_HANDLE                 *Handle,
  ...
  );

VOID
LibUninstallProtocolInterfaces (
  IN EFI_HANDLE                     Handle,
  ...
  );

EFI_STATUS
LibReinstallProtocolInterfaces (
  IN OUT EFI_HANDLE                 *Handle,
  ...
  );

EFI_EVENT
LibCreateProtocolNotifyEvent (
  IN EFI_GUID                       *ProtocolGuid,
  IN EFI_TPL                        NotifyTpl,
  IN EFI_EVENT_NOTIFY               NotifyFunction,
  IN VOID                           *NotifyContext,
  OUT VOID                          *Registration
  );

EFI_STATUS
WaitForSingleEvent (
  IN EFI_EVENT                      Event,
  IN UINT64                         Timeout OPTIONAL
  );

VOID
WaitForEventWithTimeout (
  IN  EFI_EVENT                     Event,
  IN  UINTN                         Timeout,
  IN  UINTN                         Row,
  IN  UINTN                         Column,
  IN  CHAR16                        *String,
  IN  EFI_INPUT_KEY                 TimeoutKey,
  OUT EFI_INPUT_KEY                 *Key
  );

EFI_FILE_HANDLE
LibOpenRoot (
  IN EFI_HANDLE                     DeviceHandle
  );

EFI_FILE_INFO *
LibFileInfo (
  IN EFI_FILE_HANDLE                FHand
  );

EFI_FILE_SYSTEM_INFO *
LibFileSystemInfo (
  IN EFI_FILE_HANDLE                FHand
  );

EFI_FILE_SYSTEM_VOLUME_LABEL_INFO *
LibFileSystemVolumeLabelInfo (
  IN EFI_FILE_HANDLE                FHand
  );

BOOLEAN
ValidMBR(
  IN  MASTER_BOOT_RECORD            *Mbr,
  IN  EFI_BLOCK_IO_PROTOCOL         *BlkIo
  );

BOOLEAN
LibMatchDevicePaths (
  IN  EFI_DEVICE_PATH_PROTOCOL      *Multi,
  IN  EFI_DEVICE_PATH_PROTOCOL      *Single
  );

EFI_DEVICE_PATH_PROTOCOL *
LibDuplicateDevicePathInstance (
  IN EFI_DEVICE_PATH_PROTOCOL       *DevPath
  );

EFI_DEVICE_PATH_PROTOCOL *
DevicePathFromHandle (
  IN EFI_HANDLE                     Handle
  );

UINT16 *
DevicePathStrFromProtocol (
  IN VOID        *Protocol,
  IN EFI_GUID    *Guid
  );

EFI_DEVICE_PATH_PROTOCOL *
DevicePathInstance (
  IN OUT EFI_DEVICE_PATH_PROTOCOL   **DevicePath,
  OUT UINTN                         *Size
  );

UINTN
DevicePathInstanceCount (
  IN EFI_DEVICE_PATH_PROTOCOL       *DevicePath
  );

EFI_DEVICE_PATH_PROTOCOL *
AppendDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL       *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL       *Src2
  );

EFI_DEVICE_PATH_PROTOCOL *
AppendDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL       *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL       *Src2
  );

EFI_DEVICE_PATH_PROTOCOL*
AppendDevicePathInstance (
  IN EFI_DEVICE_PATH_PROTOCOL       *Src,
  IN EFI_DEVICE_PATH_PROTOCOL       *Instance
  );

EFI_DEVICE_PATH_PROTOCOL *
FileDevicePath (
  IN EFI_HANDLE                     Device  OPTIONAL,
  IN CHAR16                         *FileName
  );

UINTN
DevicePathSize (
  IN EFI_DEVICE_PATH_PROTOCOL       *DevPath
  );

EFI_DEVICE_PATH_PROTOCOL *
DuplicateDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL       *DevPath
  );

EFI_DEVICE_PATH_PROTOCOL *
UnpackDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL       *DevPath
  );

EFI_STATUS
LibDevicePathToInterface (
  IN EFI_GUID                       *Protocol,
  IN EFI_DEVICE_PATH_PROTOCOL       *FilePath,
  OUT VOID                          **Interface
  );

CHAR16 *
DevicePathToStr (
  EFI_DEVICE_PATH_PROTOCOL          *DevPath
  );

//
//added by kevin for test cases.
//
EFI_STATUS
GetFilePathByName (
  IN CHAR16                       *Name,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **FilePath
  );

//
// BugBug: I need my own include files
//
typedef struct {
  UINT8                             Register;
  UINT8                             Function;
  UINT8                             Device;
  UINT8                             Bus;
  UINT32                            Reserved;
} EFI_ADDRESS;

typedef union {
  UINT64                            Address;
  EFI_ADDRESS                       EfiAddress;
} EFI_PCI_ADDRESS_UNION;


EFI_STATUS
PciFindDeviceClass (
  IN OUT EFI_PCI_ADDRESS_UNION      *Address,
  IN UINT8                          BaseClass,
  IN UINT8                          SubClass
  );

EFI_STATUS
PciFindDevice (
  IN OUT EFI_PCI_ADDRESS_UNION      *DeviceAddress,
  IN UINT16                         VendorId,
  IN UINT16                         DeviceId,
  IN OUT PCI_TYPE00                 *Pci
  );

//
// SIMPLE_READ_FILE object used to access files
//

typedef VOID                        *SIMPLE_READ_FILE;

EFI_STATUS
OpenSimpleReadFile (
  IN BOOLEAN                        BootPolicy,
  IN VOID                           *SourceBuffer   OPTIONAL,
  IN UINTN                          SourceSize,
  IN OUT EFI_DEVICE_PATH_PROTOCOL   **FilePath,
  OUT EFI_HANDLE                    *DeviceHandle,
  OUT SIMPLE_READ_FILE              *SimpleReadHandle
  );

EFI_STATUS
ReadSimpleReadFile (
  IN SIMPLE_READ_FILE               SimpleReadHandle,
  IN UINTN                          Offset,
  IN OUT UINTN                      *ReadSize,
  OUT VOID                          *Buffer
  );

VOID
CloseSimpleReadFile (
  IN SIMPLE_READ_FILE               SimpleReadHandle
  );

UINT8
DecimaltoBCD(
  IN  UINT8                         DecValue
  );

UINT8
BCDtoDecimal(
  IN  UINT8                         BcdValue
  );

EFI_STATUS
LibGetSystemConfigurationTable(
  IN EFI_GUID                       *TableGuid,
  IN OUT VOID                       **Table
  );

BOOLEAN
LibIsValidTextGraphics (
  IN  CHAR16                        Graphic,
  OUT CHAR8                         *PcAnsi,    OPTIONAL
  OUT CHAR8                         *Ascii      OPTIONAL
  );

BOOLEAN
IsValidAscii (
  IN  CHAR16                        Ascii
  );

BOOLEAN
IsValidEfiCntlChar (
  IN  CHAR16                        c
  );

CHAR16 *
LibGetUiString (
  IN  EFI_HANDLE                    Handle,
  IN  UI_STRING_TYPE                StringType,
  IN  ISO_639_2                     *LangCode,
  IN  BOOLEAN                       ReturnDevicePathStrOnMismatch
  );

#define EFI_HANDLE_TYPE_UNKNOWN                      0x000
#define EFI_HANDLE_TYPE_IMAGE_HANDLE                 0x001
#define EFI_HANDLE_TYPE_DRIVER_BINDING_HANDLE        0x002
#define EFI_HANDLE_TYPE_DEVICE_DRIVER                0x004
#define EFI_HANDLE_TYPE_BUS_DRIVER                   0x008
#define EFI_HANDLE_TYPE_DRIVER_CONFIGURATION_HANDLE  0x010
#define EFI_HANDLE_TYPE_DRIVER_DIAGNOSTICS_HANDLE    0x020
#define EFI_HANDLE_TYPE_COMPONENT_NAME_HANDLE        0x040
#define EFI_HANDLE_TYPE_DEVICE_HANDLE                0x080
#define EFI_HANDLE_TYPE_PARENT_HANDLE                0x100
#define EFI_HANDLE_TYPE_CONTROLLER_HANDLE            0x200
#define EFI_HANDLE_TYPE_CHILD_HANDLE                 0x400

EFI_STATUS
LibScanHandleDatabase (
  EFI_HANDLE  DriverBindingHandle,       OPTIONAL
  UINT32      *DriverBindingHandleIndex, OPTIONAL
  EFI_HANDLE  ControllerHandle,          OPTIONAL
  UINT32      *ControllerHandleIndex,    OPTIONAL
  UINTN       *HandleCount,
  EFI_HANDLE  **HandleBuffer,
  UINT32      **HandleType
  );

EFI_STATUS
LibGetManagingDriverBindingHandles (
  EFI_HANDLE  ControllerHandle,
  UINTN       *DriverBindingHandleCount,
  EFI_HANDLE  **DriverBindingHandleBuffer
  );

EFI_STATUS
LibGetParentControllerHandles (
  EFI_HANDLE  ControllerHandle,
  UINTN       *ParentControllerHandleCount,
  EFI_HANDLE  **ParentControllerHandleBuffer
  );

EFI_STATUS
LibGetManagedChildControllerHandles (
  EFI_HANDLE  DriverBindingHandle,
  EFI_HANDLE  ControllerHandle,
  UINTN       *ChildControllerHandleCount,
  EFI_HANDLE  **ChildControllerHandleBuffer
  );

EFI_STATUS
LibGetManagedControllerHandles (
  EFI_HANDLE  DriverBindingHandle,
  UINTN       *ControllerHandleCount,
  EFI_HANDLE  **ControllerHandleBuffer
  );

EFI_STATUS
LibGetChildControllerHandles (
  EFI_HANDLE  ControllerHandle,
  UINTN       *HandleCount,
  EFI_HANDLE  **HandleBuffer
  );

CHAR8*
LibGetSmbiosString (
  IN  SMBIOS_STRUCTURE_POINTER      *Smbios,
  IN  UINT16                        StringNumber
  );

EFI_STATUS
LibGetSmbiosSystemGuidAndSerialNumber (
  IN  EFI_GUID                      *SystemGuid,
  OUT CHAR8                         **SystemSerialNumber
  );

EFI_STATUS
EfiDebugAssertInit (
  VOID
  );

EFI_STATUS
LibGetFreePages (
  IN UINT64 *NoFreePages
  );

EFI_STATUS
StallForKey (
  IN UINTN             Seconds,
  OUT EFI_INPUT_KEY    *Key
  );

#endif
