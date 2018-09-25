/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SctDebug.h

Abstract:

  This file provides the debug macro definitions for SCT.

--*/

#ifndef _EFI_SCT_DEBUG_H_
#define _EFI_SCT_DEBUG_H_

//
// Definitions
//

#define EFI_SCT_D_ERROR           0x01
#define EFI_SCT_D_DEBUG           0x02
#define EFI_SCT_D_TRACE           0x04

#define EFI_SCT_D_MASK            \
  (EFI_SCT_D_ERROR | EFI_SCT_D_DEBUG)

//
// Construction and destruction services
//

EFI_STATUS
InitializeDebugServices (
  VOID
  );

EFI_STATUS
FreeDebugServices (
  VOID
  );

//
// EFI_SCT_DEBUG worker function
//

VOID
EfiSctDebug (
  IN UINTN              Level,
  IN CHAR16             *Format,
  ...
  );

#ifdef EFI_DEBUG
  #define EFI_SCT_DEBUG(a)    EfiSctDebug a
#else
  #define EFI_SCT_DEBUG(a)
#endif

#endif
