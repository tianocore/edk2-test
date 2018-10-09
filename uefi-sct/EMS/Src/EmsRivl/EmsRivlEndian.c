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
  
    EmsRivlEndian.c
    
Abstract:

    Implementation of RIVL endian related functions

--*/

#include "EmsRivlMain.h"
#include "EmsRivlEndian.h"

BOOLEAN RivlLittleEndian = TRUE;

UINT64  Lak;

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
{
  UINT16  M;
  UINT8   *B;
  B = (UINT8 *) &N;
  if (RivlLittleEndian) {
    M = (UINT16) (B[0] << 8 | B[1]);
  } else {
    M = N;
  }

  return M;
}

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
{
  UINT32  M;
  UINT8   *B;
  B = (UINT8 *) &N;

  if (RivlLittleEndian) {
    M = (UINT32) (B[0] << 24 | B[1] << 16 | B[2] << 8 | B[3]);
  } else {
    M = N;
  }

  return M;
}

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
{
  union {
    UINT64  N;
    UINT8   B[8];
  } U;

  UINT8 T;
  U.N = N;

  if (RivlLittleEndian) {

    T       = U.B[0];
    U.B[0]  = U.B[7];
    U.B[7]  = T;

    T       = U.B[1];
    U.B[1]  = U.B[6];
    U.B[6]  = T;

    T       = U.B[2];
    U.B[2]  = U.B[5];
    U.B[5]  = T;

    T       = U.B[3];
    U.B[3]  = U.B[4];
    U.B[4]  = T;
  }

  return U.N;
}
