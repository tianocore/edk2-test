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

#include "SctLibInternal.h"

UINT64
SctLShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  )
{
  return Operand << Count;
}

UINT64
SctRShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  )
{
  return Operand >> Count;
}

UINT64
SctMultU64x32 (
  IN UINT64                         Multiplicand,
  IN UINTN                          Multiplier
  )
{
  return Multiplicand * Multiplier;
}

UINT64
SctDivU64x32 (
  IN UINT64                         Dividend,
  IN UINTN                          Divisor,
  OUT UINTN                         *Remainder OPTIONAL
  )
{
  if (Remainder != NULL) {
    *Remainder = Dividend % Divisor;
  }
  return Dividend / Divisor;
}
