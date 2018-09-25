/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2011 - 2012 ARM Ltd. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

/*++

Module Name:

  Debug.h

--*/

#ifndef _IA32_IO_ACCESS_H
#define _IA32_IO_ACCESS_H

#include "SCRTDriver.h"

#define IA32_MAX_IO_ADDRESS   0xFFFF

#define IA32API


typedef union {
  UINT8  VOLATILE  *buf;
  UINT8  VOLATILE  *ui8;
  UINT16 VOLATILE  *ui16;
  UINT32 VOLATILE  *ui32;
  UINT64 VOLATILE  *ui64;
  UINTN  VOLATILE  ui;
} PTR;

// This address is assuming a pure PC architecture. Not required?
#define   VIRT_TO_PHYS_OFFSET            (0x80000000)     //2G



#endif
