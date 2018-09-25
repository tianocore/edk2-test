/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  TimerInterrupt.c

Abstract:
  Ia32 Source file for Mask/Unmask TimerInterrupt.

--*/

#include "Usb2HcTest.h"

VOID MaskTimerInterrupt()
/*++

Routine Description:

  Mask timer interrupt

Arguments:

  None

Returns:

  VOID

--*/
{
  __asm mov al, 0x0ff
  __asm out 0x21, al

  return;
}

VOID UnmaskTimerInterrupt()
/*++

Routine Description:

  Unmask timer interrupt

Arguments:

  None

Returns:

  VOID

--*/
{
  __asm mov al, 0x0fe
  __asm out 0x21, al

  return;
}