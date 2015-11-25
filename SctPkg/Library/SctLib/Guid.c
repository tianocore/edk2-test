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
                                                                
  Copyright 2006 - 2015 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  guid.c

Abstract:

  Misc EFI support functions

--*/

#include "SctLibInternal.h"

#include EFI_GUID_DEFINITION (GlobalVariable)
#include EFI_GUID_DEFINITION (Gpt)

#include EFI_PROTOCOL_DEFINITION (BlockIo)
#include EFI_PROTOCOL_DEFINITION (DeviceIo)
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (DiskIo)
#if (EFI_SPECIFICATION_VERSION >= 0x00020028)
  #include <Protocol/NetworkInterfaceIdentifier.h>
#else
  #include EFI_PROTOCOL_DEFINITION (EfiNetworkInterfaceIdentifier)
#endif

#if (EFI_SPECIFICATION_VERSION >= 0x00020028)
  #include <Guid/FileInfo.h>
  #include <Guid/FileSystemInfo.h>
#else
  #include EFI_PROTOCOL_DEFINITION (FileInfo)
  #include EFI_PROTOCOL_DEFINITION (FileSystemInfo)
#endif
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (LoadFile)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCode)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCodeCallBack)
#include EFI_PROTOCOL_DEFINITION (SerialIo)
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)
#include EFI_PROTOCOL_DEFINITION (SimpleNetwork)
#include EFI_PROTOCOL_DEFINITION (SimpleTextIn)
#include EFI_PROTOCOL_DEFINITION (SimpleTextOut)
#include EFI_PROTOCOL_DEFINITION (UnicodeCollation)
#if (EFI_SPECIFICATION_VERSION < 0x00020028)
  #include EFI_PROTOCOL_DEFINITION (VariableStore)
#else
  EFI_GUID  gEfiVariableStoreProtocolGuid = EFI_VARIABLE_STORE_PROTOCOL_GUID;
#endif

EFI_GUID mEfiUnknownDeviceGuid = UNKNOWN_DEVICE_GUID;

STATIC EFI_GUID mNullGuid = { 0,0,0, { 0,0,0,0,0,0,0,0 }};

STATIC EFI_GUID mPcAnsiProtocol    = DEVICE_PATH_MESSAGING_PC_ANSI;
STATIC EFI_GUID mVt100Protocol     = DEVICE_PATH_MESSAGING_VT_100;
// STATIC EFI_GUID mVt100PlusProtocol = DEVICE_PATH_MESSAGING_VT_100_PLUS;
// STATIC EFI_GUID mVtUtf8Protocol    = DEVICE_PATH_MESSAGING_VT_UTF8;

//
// Additional Known guids
//

#define SHELL_INTERFACE_PROTOCOL \
  { 0x47c7b223, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

#define ENVIRONMENT_VARIABLE_ID  \
  { 0x47c7b224, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

#define DEVICE_PATH_MAPPING_ID  \
  { 0x47c7b225, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

#define PROTOCOL_ID_ID  \
  { 0x47c7b226, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

#define ALIAS_ID  \
  { 0x47c7b227, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

static EFI_GUID ShellInterfaceProtocol = SHELL_INTERFACE_PROTOCOL;
static EFI_GUID SEnvId                 = ENVIRONMENT_VARIABLE_ID;
static EFI_GUID SMapId                 = DEVICE_PATH_MAPPING_ID;
static EFI_GUID SProtId                = PROTOCOL_ID_ID;
static EFI_GUID SAliasId               = ALIAS_ID;

struct {
  EFI_GUID        *Guid;
  CHAR16          *GuidName;
} KnownGuids[] = {
  &mNullGuid,                  L"G0",
  &gEfiGlobalVariableGuid,         L"Efi",

  &gEfiVariableStoreProtocolGuid,     L"varstore",
  &gEfiDevicePathProtocolGuid,        L"dpath",
  &gEfiLoadedImageProtocolGuid,       L"image",
  &gEfiSimpleTextInProtocolGuid,      L"txtin",
  &gEfiSimpleTextOutProtocolGuid,     L"txtout",
  &gEfiBlockIoProtocolGuid,           L"blkio",
  &gEfiDiskIoProtocolGuid,            L"diskio",
  &gEfiSimpleFileSystemProtocolGuid,  L"fs",
  &gEfiLoadFileProtocolGuid,          L"load",
  &gEfiDeviceIoProtocolGuid,          L"DevIo",

  &gEfiFileInfoGuid,                   L"GenFileInfo",
  &gEfiFileSystemInfoGuid,            L"FileSysInfo",

  &gEfiUnicodeCollationProtocolGuid,  L"UnicodeCollation",
  &gEfiSerialIoProtocolGuid,          L"serialio",
  &gEfiSimpleNetworkProtocolGuid,     L"net",
  &gEfiNetworkInterfaceIdentifierProtocolGuid,    L"nii",
  &gEfiPxeBaseCodeProtocolGuid,       L"pxebc",
  &gEfiPxeBaseCodeCallbackProtocolGuid,       L"pxecb",

  &mPcAnsiProtocol,            L"PcAnsi",
  &mVt100Protocol,             L"Vt100",
  &mEfiUnknownDeviceGuid,             L"Unknown Device",

  &gEfiPartTypeSystemPartGuid,    L"ESP",
  &gEfiPartTypeLegacyMbrGuid,          L"GPT MBR",

  &ShellInterfaceProtocol,    L"ShellInt",
  &SEnvId,                    L"SEnv",
  &SProtId,                   L"ShellProtId",
  &SMapId,                    L"ShellDevPathMap",
  &SAliasId,                  L"ShellAlias",

  NULL
};

SCT_LIST_ENTRY          GuidList;

/*++

Routine Description:

  Converts Guid to a string

Arguments:

  Buffer      - On return, a pointer to the buffer which contains the string.
  Guid        - guid to compare

Returns:
  none

--*/
VOID
GuidToString (
  OUT CHAR16      *Buffer,
  IN EFI_GUID     *Guid
  )
{

  UINTN           Index;

  //
  // Else, (for now) use additional internal function for mapping guids
  //
  for (Index=0; KnownGuids[Index].Guid; Index++) {
    if (SctCompareGuid (Guid, KnownGuids[Index].Guid) == 0) {
      SctSPrint (Buffer, 0, KnownGuids[Index].GuidName);
      return ;
    }
  }

  //
  // Else dump it
  //
  SctSPrint (Buffer, 0, L"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        (UINTN)Guid->Data1,
        (UINTN)Guid->Data2,
        (UINTN)Guid->Data3,
        (UINTN)Guid->Data4[0],
        (UINTN)Guid->Data4[1],
        (UINTN)Guid->Data4[2],
        (UINTN)Guid->Data4[3],
        (UINTN)Guid->Data4[4],
        (UINTN)Guid->Data4[5],
        (UINTN)Guid->Data4[6],
        (UINTN)Guid->Data4[7]
        );
}
