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

  guid.c

Abstract:

  Misc EFI support functions

--*/

#include "lib.h"

//
// Additional Known guids
//

#define SHELL_INTERFACE_PROTOCOL \
  { 0x47c7b223, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define ENVIRONMENT_VARIABLE_ID  \
  { 0x47c7b224, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define DEVICE_PATH_MAPPING_ID  \
  { 0x47c7b225, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define PROTOCOL_ID_ID  \
  { 0x47c7b226, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define ALIAS_ID  \
  { 0x47c7b227, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

static EFI_GUID ShellInterfaceProtocol = SHELL_INTERFACE_PROTOCOL;
static EFI_GUID SEnvId                 = ENVIRONMENT_VARIABLE_ID;
static EFI_GUID SMapId                 = DEVICE_PATH_MAPPING_ID;
static EFI_GUID SProtId                = PROTOCOL_ID_ID;
static EFI_GUID SAliasId               = ALIAS_ID;

struct {
  EFI_GUID        *Guid;
  CHAR16          *GuidName;
} KnownGuids[] = {
  &tNullGuid,                  L"G0",
  &tEfiGlobalVariable,         L"Efi",

  &gtEfiVariableStoreProtocolGuid,     L"varstore",
  &gtEfiDevicePathProtocolGuid,        L"dpath",
  &gtEfiLoadedImageProtocolGuid,       L"image",
  &gtEfiSimpleTextInProtocolGuid,      L"txtin",
  &gtEfiSimpleTextOutProtocolGuid,     L"txtout",
  &gtEfiBlockIoProtocolGuid,           L"blkio",
  &gtEfiDiskIoProtocolGuid,            L"diskio",
  &gtEfiSimpleFileSystemProtocolGuid,  L"fs",
  &gtEfiLoadFileProtocolGuid,          L"load",
  &gtEfiDeviceIoProtocolGuid,          L"DevIo",

  &tGenericFileInfo,                   L"GenFileInfo",
  &gtEfiFileSystemInfoGuid,            L"FileSysInfo",

  &gtEfiUnicodeCollationProtocolGuid,  L"UnicodeCollation",
  &gtEfiSerialIoProtocolGuid,          L"serialio",
  &gtEfiSimpleNetworkProtocolGuid,     L"net",
  &gtEfiNetworkInterfaceIdentifierProtocolGuid,    L"nii",
  &gtEfiPxeBaseCodeProtocolGuid,       L"pxebc",
  &gtEfiPxeCallbackProtocolGuid,       L"pxecb",

  &tPcAnsiProtocol,            L"PcAnsi",
  &tVt100Protocol,             L"Vt100",
  &gtEfiUnknownDeviceGuid,             L"Unknown Device",

  &gtEfiPartTypeSystemPartitionGuid,    L"ESP",
  &gtEfiPartTypeLegacyMbrGuid,          L"GPT MBR",

  &ShellInterfaceProtocol,    L"ShellInt",
  &SEnvId,                    L"SEnv",
  &SProtId,                   L"ShellProtId",
  &SMapId,                    L"ShellDevPathMap",
  &SAliasId,                  L"ShellAlias",

  NULL
};

EFI_LIST_ENTRY          GuidList;


INTN
CompareGuid(
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
  = 0     if Guid1 == Guid2

--*/
{
  INT32       *g1, *g2, r;

  //
  // Compare 32 bits at a time
  //

  g1 = (INT32 *) Guid1;
  g2 = (INT32 *) Guid2;

  r  = g1[0] - g2[0];
  r |= g1[1] - g2[1];
  r |= g1[2] - g2[2];
  r |= g1[3] - g2[3];

  return r;
}


VOID
GuidToString (
  OUT CHAR16      *Buffer,
  IN EFI_GUID     *Guid
  )
/*++

Routine Description:

  Converts Guid to a string

Arguments:

  Buffer      - On return, a pointer to the buffer which contains the string.
  Guid        - guid to compare

Returns:
  none

--*/
{

  UINTN           Index;

  //
  // Else, (for now) use additional internal function for mapping guids
  //
  for (Index=0; KnownGuids[Index].Guid; Index++) {
    if (CompareGuid(Guid, KnownGuids[Index].Guid) == 0) {
      SPrint (Buffer, 0, KnownGuids[Index].GuidName);
      return ;
    }
  }

  //
  // Else dump it
  //
  SPrint (Buffer, 0, L"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        Guid->Data1,
        Guid->Data2,
        Guid->Data3,
        Guid->Data4[0],
        Guid->Data4[1],
        Guid->Data4[2],
        Guid->Data4[3],
        Guid->Data4[4],
        Guid->Data4[5],
        Guid->Data4[6],
        Guid->Data4[7]
        );
}
