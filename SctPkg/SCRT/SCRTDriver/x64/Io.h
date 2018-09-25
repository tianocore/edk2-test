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

  Io.h

--*/
#ifndef _X64_IO_ACCESS_H
#define _X64_IO_ACCESS_H

#include "SctLib.h"

#include <PiPei.h>
#include <Ppi/CpuIo.h>

#define VIRT_TO_PHYS_OFFSET       (0x800000000)    //32G

#define X64_MAX_IO_ADDRESS   0xFFFF

#ifdef __GNUC__
#define X64API __attribute__((cdecl))
#else
#define X64API __cdecl
#endif

typedef union {
  UINT8  VOLATILE  *buf;
  UINT8  VOLATILE  *ui8;
  UINT16 VOLATILE  *ui16;
  UINT32 VOLATILE  *ui32;
  UINT64 VOLATILE  *ui64;
  UINTN  VOLATILE  ui;
} PTR;


UINT8
X64API
CpuIoRead8 (
  IN  UINT16  Port
  )
;


UINT16
X64API
CpuIoRead16 (
  IN  UINT16  Port
  )
;

UINT32
X64API
CpuIoRead32 (
  IN  UINT16  Port
  )
;

VOID
X64API
CpuIoWrite8 (
  IN  UINT16  Port,
  IN  UINT32  Data
  )
;

VOID
X64API
CpuIoWrite16 (
  IN  UINT16  Port,
  IN  UINT32  Data
  )
;

VOID
X64API
CpuIoWrite32 (
  IN  UINT16  Port,
  IN  UINT32  Data
  )
;

#endif

