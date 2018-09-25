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

  InitPlat.c

Abstract:

  Functions to make SAL and PAL proc calls

--*/

#include "Efi.h"
#include "EntsLibPlat.h"
#include "LibSalPal.h"

VOID
EntsInitializeLibPlatform (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:

  Initialize platform.

Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.

Returns:

  None.

--*/
{
  LibInitSalAndPalProc ();
}
