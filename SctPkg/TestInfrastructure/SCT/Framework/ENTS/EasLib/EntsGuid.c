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

  EntsGuid.c

Abstract:

  Ents GUID implementations.

--*/
#include "Efi.h"
#include <Library/EntsLib.h>

#define SHELL_INTERFACE_PROTOCOL \
  { \
    0x47c7b223, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
  }

#define ENVIRONMENT_VARIABLE_ID \
  { \
    0x47c7b224, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
  }

#define DEVICE_PATH_MAPPING_ID \
  { \
    0x47c7b225, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
  }

#define PROTOCOL_ID_ID \
  { \
    0x47c7b226, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
  }

#define ALIAS_ID \
  { \
    0x47c7b227, 0xc42a, 0x11d2, { 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
  }

static EFI_GUID ShellInterfaceProtocol  = SHELL_INTERFACE_PROTOCOL;
static EFI_GUID SEnvId                  = ENVIRONMENT_VARIABLE_ID;
static EFI_GUID SMapId                  = DEVICE_PATH_MAPPING_ID;
static EFI_GUID SProtId                 = PROTOCOL_ID_ID;
static EFI_GUID SAliasId                = ALIAS_ID;

struct {
  EFI_GUID  *Guid;
  CHAR16    *GuidName;
}
EntsKnownGuids[] = {
  &tNullGuid,
  L"G0",
  &tEfiGlobalVariable,
  L"Efi",

  &gtEfiVariableStoreProtocolGuid,
  L"varstore",
  &gtEfiDevicePathProtocolGuid,
  L"dpath",
  &gtEfiLoadedImageProtocolGuid,
  L"image",
  &gtEfiSimpleTextInProtocolGuid,
  L"txtin",
  &gtEfiSimpleTextOutProtocolGuid,
  L"txtout",
  &gtEfiBlockIoProtocolGuid,
  L"blkio",
  &gtEfiDiskIoProtocolGuid,
  L"diskio",
  &gtEfiSimpleFileSystemProtocolGuid,
  L"fs",
  &gtEfiLoadFileProtocolGuid,
  L"load",
  &gtEfiDeviceIoProtocolGuid,
  L"DevIo",

  &tGenericFileInfo,
  L"GenFileInfo",
  &gtEfiFileSystemInfoGuid,
  L"FileSysInfo",

  &gtEfiUnicodeCollationProtocolGuid,
  L"UnicodeCollation",
  &gtEfiSerialIoProtocolGuid,
  L"serialio",
  &gtEfiSimpleNetworkProtocolGuid,
  L"net",
  &gtEfiNetworkInterfaceIdentifierProtocolGuid,
  L"nii",
  &gtEfiPxeBaseCodeProtocolGuid,
  L"pxebc",
  &gtEfiPxeCallbackProtocolGuid,
  L"pxecb",

  &tPcAnsiProtocol,
  L"PcAnsi",
  &tVt100Protocol,
  L"Vt100",
  &gtEfiUnknownDeviceGuid,
  L"Unknown Device",

  &gtEfiPartTypeSystemPartitionGuid,
  L"ESP",
  &gtEfiPartTypeLegacyMbrGuid,
  L"GPT MBR",

  &ShellInterfaceProtocol,
  L"ShellInt",
  &SEnvId,
  L"SEnv",
  &SProtId,
  L"ShellProtId",
  &SMapId,
  L"ShellDevPathMap",
  &SAliasId,
  L"ShellAlias",

  NULL
};

INTN
EntsCompareGuid (
  IN EFI_GUID     *Guid1,
  IN EFI_GUID     *Guid2
  )
/*++

Routine Description:

  Compares to GUIDs

Arguments:

  Guid1       - guid to compare
  Guid2       - guid to compare

Returns:
  0           - if Guid1 == Guid2

--*/
{
  INT32 *g1;

  INT32 *g2;

  INT32 r;

  //
  // Compare 32 bits at a time
  //
  g1  = (INT32 *) Guid1;
  g2  = (INT32 *) Guid2;

  r   = g1[0] - g2[0];
  r |= g1[1] - g2[1];
  r |= g1[2] - g2[2];
  r |= g1[3] - g2[3];

  return r;
}

VOID
EntsGuidToString (
  OUT CHAR16      *Buffer,
  IN EFI_GUID     *Guid
  )
/*++

Routine Description:

  Convert a GUID to a string.

--*/
{
  UINT32  Index;
  UINT32  BufferIndex;
  UINT32  DataIndex;
  UINT32  Len;
  
  if ((Guid == NULL) || (Buffer == NULL)) {
    return ;
  }

  BufferIndex = 0;

  //
  // Convert Guid->Data1
  //
  Len = sizeof(UINT32)*2;
  for (Index = 0; Index < Len; Index++) {
    Buffer[BufferIndex]  = 0;
    Buffer[BufferIndex] = (CHAR16)((Guid->Data1 & (0xf0000000>>(4 * Index)))>>(4 * (Len - Index - 1)));
    if (Buffer[BufferIndex] < 0x0A) {
       Buffer[BufferIndex] += (CHAR16)(L'0');
    } else {
       Buffer[BufferIndex] = (CHAR16)((L'A') + (Buffer[BufferIndex] - 0x0A));
    }
    BufferIndex ++;
  }

  Buffer[BufferIndex++] = L'-';
  
  //
  // Convert Guid->Data2
  //
  Len = sizeof(UINT16)*2;
  for (Index = 0; Index < Len; Index++) {
    Buffer[BufferIndex]  = 0;
    Buffer[BufferIndex] = (CHAR16)((Guid->Data2 & (0xf000>>(4 * Index)))>>(4 * (Len - Index - 1)));
    if (Buffer[BufferIndex] < 0x0A) {
       Buffer[BufferIndex] += (CHAR16)(L'0');
    } else {
       Buffer[BufferIndex] = (CHAR16)((L'A') + (Buffer[BufferIndex] - 0x0A));
    }
    BufferIndex ++;
  }

  Buffer[BufferIndex++] = L'-';
  
  //
  // Convert Guid->Data3
  //
  Len = sizeof(UINT16)*2;
  for (Index = 0; Index < Len; Index++) {
    Buffer[BufferIndex]  = 0;
    Buffer[BufferIndex] = (CHAR16)((Guid->Data3 & (0xf000>>(4 * Index)))>>(4 * (Len - Index - 1)));
    if (Buffer[BufferIndex] < 0x0A) {
       Buffer[BufferIndex] += (CHAR16)(L'0');
    } else {
       Buffer[BufferIndex] = (CHAR16)((L'A') + (Buffer[BufferIndex] - 0x0A));
    }
    BufferIndex ++;
  }

  Buffer[BufferIndex++] = L'-';
  
  //
  // Convert Guid->Data4[x]
  //
  Len = sizeof(UINT8)*2;
  for (DataIndex = 0; DataIndex < 8; DataIndex++) {
     for (Index = 0; Index < Len; Index++) {
        Buffer[BufferIndex]  = 0;
        Buffer[BufferIndex] = (CHAR16)((Guid->Data4[DataIndex] & (0xf0>>(4 * Index)))>>(4 * (Len - Index - 1)));
        if (Buffer[BufferIndex] < 0x0A) {
           Buffer[BufferIndex] += (CHAR16)(L'0');
        } else {
       Buffer[BufferIndex] = (CHAR16)((L'A') + (Buffer[BufferIndex] - 0x0A));
        }
        BufferIndex ++;
     }

     if (DataIndex == 1) {
       Buffer[BufferIndex++] = L'-';
     }
  }

  Buffer[BufferIndex] = 0;
  
  return;
}

