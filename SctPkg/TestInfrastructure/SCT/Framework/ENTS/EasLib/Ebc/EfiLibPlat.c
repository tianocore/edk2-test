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

  EfiLibPlat.c

Abstract:

  Math routines for compatibility with native EFI library routines.

--*/

#include "Efi.h"
#include "EntsLibPlat.h"

UINT64
SctRShiftU64 (
  IN UINT64   Operand,
  IN UINTN    Count
  )
{
  return Operand >> Count;
}

UINT64
SctDivU64x32 (
  IN UINT64   Dividend,
  IN UINTN    Divisor,
  OUT UINTN   *Remainder OPTIONAL
  )
{
  ASSERT (Divisor != 0);

  //
  // Have to compute twice if remainder. No support for
  // divide-with-remainder in VM.
  //
  if (Remainder != NULL) {
    *Remainder = Dividend % Divisor;
  }

  return Dividend / Divisor;
}

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
  //
  // No platform-specific initializations
  //
}
