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

  Port80.c

--*/

#include "SCRTDriver.h"


VOID
Port80 (
  UINT8 num
  )
/*++

Routine Description:

  Print a Hex number to I/O 80h

Arguments:

  num  - a Hex number

Returns:

  NONE
  
--*/  
{
   EfiIoWrite (EfiPeiCpuIoWidthUint8, 0x80, 1, &num);
}
