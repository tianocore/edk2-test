/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2014, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

#ifndef __SCTLIB_INTERNAL_H__
#define __SCTLIB_INTERNAL_H__

#include "SctLib.h"
#include "SctLibPlat.h"

#include EFI_PROTOCOL_DEFINITION (UnicodeCollation)

extern CONST CHAR8 mHex[];
extern EFI_UNICODE_COLLATION_PROTOCOL   *UnicodeInterface;
extern UINTN                            EfiDebugMask;

extern EFI_GUID                         mEfiUnknownDeviceGuid;

//
// Default pool allocation type
//
extern EFI_MEMORY_TYPE PoolAllocationType;

VOID
InitializeLibPlatform (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
    );

VOID
EfiDebugVariable (
  VOID
  );

EFI_STATUS
EfiDebugAssertInit (
  VOID
  );

VOID
StatusToString (
  OUT CHAR16          *Buffer,
  IN EFI_STATUS       Status
  );

VOID
GuidToString (
  OUT CHAR16      *Buffer,
  IN EFI_GUID     *Guid
  );

extern EFI_UNICODE_COLLATION_PROTOCOL FallbackUnicodeInterface;
#endif
