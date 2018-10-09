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
  
    EmsRivlEndian.h
    
Abstract:

    Incude header files for RIVL endian related functions

--*/

#ifndef _RIVL_ENDIAN_H_
#define _RIVL_ENDIAN_H_

UINT16
RivlSwap16 (
  UINT16  N
  )
/*++

Routine Description:

  Swap the bytes of a INT16

Arguments:

  N - The number should be swapped

Returns:

  The result

--*/
;

UINT32
RivlSwap32 (
  UINT32  N
  )
/*++

Routine Description:

  Swap the bytes of a INT32

Arguments:

  N - The number should be swapped

Returns:

  The result

--*/
;

UINT64
RivlSwap64 (
  UINT64  N
  )
/*++

Routine Description:

  Swap the bytes of a INT64

Arguments:

  N - The number should be swapped

Returns:

  The result

--*/
;

#endif
