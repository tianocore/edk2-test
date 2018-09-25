/** @file

  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
  { &tNullGuid, L"G0" },
  { &tEfiGlobalVariable, L"Efi" },

  { &gtEfiVariableStoreProtocolGuid, L"varstore"},
  { &gtEfiDevicePathProtocolGuid, L"dpath"},
  { &gtEfiLoadedImageProtocolGuid, L"image"},
  { &gtEfiSimpleTextInProtocolGuid, L"txtin"},
  { &gtEfiSimpleTextOutProtocolGuid, L"txtout"},
  { &gtEfiBlockIoProtocolGuid, L"blkio"},
  { &gtEfiDiskIoProtocolGuid, L"diskio"},
  { &gtEfiSimpleFileSystemProtocolGuid, L"fs"},
  { &gtEfiLoadFileProtocolGuid, L"load"},
  { &gtEfiDeviceIoProtocolGuid, L"DevIo"},

  { &tGenericFileInfo, L"GenFileInfo"},
  { &gtEfiFileSystemInfoGuid, L"FileSysInfo"},

  { &gtEfiUnicodeCollationProtocolGuid, L"UnicodeCollation"},
  { &gtEfiSerialIoProtocolGuid, L"serialio"},
  { &gtEfiSimpleNetworkProtocolGuid, L"net"},
  { &gtEfiNetworkInterfaceIdentifierProtocolGuid, L"nii"},
  { &gtEfiPxeBaseCodeProtocolGuid, L"pxebc"},
  { &gtEfiPxeCallbackProtocolGuid, L"pxecb"},

  { &tPcAnsiProtocol, L"PcAnsi"},
  { &tVt100Protocol, L"Vt100"},
  { &gtEfiUnknownDeviceGuid, L"Unknown Device"},

  { &gtEfiPartTypeSystemPartitionGuid, L"ESP"},
  { &gtEfiPartTypeLegacyMbrGuid, L"GPT MBR"},
 
  { &ShellInterfaceProtocol, L"ShellInt"},
  { &SEnvId, L"SEnv"},
  { &SProtId, L"ShellProtId"},
  { &SMapId, L"ShellDevPathMap"},
  { &SAliasId, L"ShellAlias"},

  { NULL, NULL }
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

