/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   

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

#include "SctLib.h"

#include <PiPei.h>
#include <Ppi/CpuIo.h>

#define IA32_MAX_IO_ADDRESS   0xFFFF

#ifdef __GNUC__
#define IA32API __attribute__((cdecl))
#else
#define IA32API __cdecl
#endif


typedef union {
  UINT8  VOLATILE  *buf;
  UINT8  VOLATILE  *ui8;
  UINT16 VOLATILE  *ui16;
  UINT32 VOLATILE  *ui32;
  UINT64 VOLATILE  *ui64;
  UINTN  VOLATILE  ui;
} PTR;

#define   VIRT_TO_PHYS_OFFSET            (0x80000000)     //2G

UINT8
IA32API
CpuIoRead8 (
  IN  UINT16  Port
  )
;


UINT16
IA32API
CpuIoRead16 (
  IN  UINT16  Port
  )
;

UINT32
IA32API
CpuIoRead32 (
  IN  UINT16  Port
  )
;

VOID
IA32API
CpuIoWrite8 (
  IN  UINT16  Port,
  IN  UINT32  Data
  )
;

VOID
IA32API
CpuIoWrite16 (
  IN  UINT16  Port,
  IN  UINT32  Data
  )
;

VOID
IA32API
CpuIoWrite32 (
  IN  UINT16  Port,
  IN  UINT32  Data
  )
;

#endif
