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
#ifndef _IPF_IO_ACCESS_H
#define _IPF_IO_ACCESS_H

#include "SctLib.h"

#include <PiPei.h>
#include <Ppi/CpuIo.h>

//#define VIRT_TO_PHYS_OFFSET       (0x10000000000)  //1T, 1024G.
#define VIRT_TO_PHYS_OFFSET         (0x10000000000000)

//
// If System I/O space is enabled via MMIO on IPF, the macro should be initialized by platform.
// Here is a sample address.
//
#define IPF_IOBLK_ADDR                (0x0ffffc000000)

//
// IO block addr is at ((1 << 44) - (64*ONE_MB)), make sure it is unsigned
//	
#define PORT_AND_IO_BASE_TO_MEM(_Port) \
    (((_Port) & 0xffffffffffff0000) | (((_Port) & 0xfffc) << 10) | ((_Port) & 0x0fff))



typedef union {
  VOID            *Void;
  UINT8           *Buffer;
  UINT8 VOLATILE  *Uint8;
  UINT16 VOLATILE *Uint16;
  UINT32 VOLATILE *Uint32;
  UINT64 VOLATILE *Uint64;
  UINT8           *Array[8];  // Only used for moving data
  UINT64          Value;
} VOLATILE_POINTER;

typedef union {
  UINT8 VOLATILE  Uint8;
  UINT16 VOLATILE Uint16;
  UINT32 VOLATILE Uint32;
  UINT64 VOLATILE Uint64;
  UINT8           Array[8];   // Only used for moving data
} DATA_SIZE;


#endif
