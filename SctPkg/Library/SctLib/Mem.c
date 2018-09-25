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

#include "SctLib.h"

/*++

Routine Description:
  Fills a buffer with zeros.

Arguments:
  Buffer                - A pointer to the buffer to fill with zeros.

  Size                  - Number of bytes to zero in the buffer.

Returns:

  None

--*/
VOID
SctZeroMem (
  IN VOID     *Buffer,
  IN UINTN    Size
  )
{
  INT8        *pt;

  pt = Buffer;
  while (Size--) {
    *(pt++) = 0;
  }
}

/*++

Routine Description:
  Fills a buffer with a value.

Arguments:
  Buffer                - A pointer to the buffer to free.

  Size                  - The number of bytes in the buffer to fill.

  Value                 - The value to fill Buffer with.

Returns:

  Buffer

--*/
VOID *
SctSetMem (
  IN VOID     *Buffer,
  IN UINTN    Size,
  IN UINT8    Value
  )
{
  INT8        *pt;

  pt = Buffer;
  while (Size--) {
    *(pt++) = Value;
  }
  return Buffer;
}

/*++

Routine Description:
  Copies the contents of one buffer to another.

Arguments:
  Dest                - A pointer to the buffer to copy to

  Src                 - A pointer to the buffer to copy from.

  len                 - The number of bytes to copy.

Returns:

  None

--*/
VOID
SctCopyMem (
  IN VOID     *Dest,
  IN CONST VOID     *Src,
  IN UINTN    len
  )
{
        CHAR8 *d;
  CONST CHAR8 *s;

  d = Dest;
  s = Src;
  while (len--) {
    *(d++) = *(s++);
  }
}

/*++

Routine Description:
  Compares the contents of one buffer to another.

Arguments:
  Dest                - A pointer to the buffer to compare

  Src                 - A pointer to the buffer to compare

  len                 - The number of bytes to compare

Returns:

  0                   - Dest is identical to Src for len bytes.
  !=0                 - Dest is not identical to Src for len bytes.

--*/
INTN
SctCompareMem (
  IN VOID     *Dest,
  IN VOID     *Src,
  IN UINTN    len
  )
{
  CHAR8    *d, *s;

  d = Dest;
  s = Src;
  while (len--) {
    if (*d != *s) {
      return *d - *s;
    }

    d += 1;
    s += 1;
  }

  return 0;
}
