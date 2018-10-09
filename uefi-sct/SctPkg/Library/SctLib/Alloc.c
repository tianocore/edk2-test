/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2016, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/


#include "SctLibInternal.h"

extern EFI_MEMORY_TYPE              PoolAllocationType;

/*++

Routine Description:
  Allocates pool memory.

Arguments:
  Size                 - Size in bytes of the pool being requested.

Returns:

  EFI_SUCEESS          - The requested number of bytes were allocated.

  EFI_OUT_OF_RESOURCES - The pool requested could not be allocated.

--*/
VOID *
SctAllocatePool (
  IN UINTN                Size
  )
{
  EFI_STATUS              Status;
  VOID                    *p;

  Status = tBS->AllocatePool (PoolAllocationType, Size, (VOID **) &p);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "AllocatePool: out of pool  %x\n", Status));
    p = NULL;
  }
  return p;
}

VOID *
SctAllocateCopyPool (
  IN  UINTN   AllocationSize,
  IN  VOID    *Buffer
  )
{
  VOID  *Memory;

  Memory = NULL;
  tBS->AllocatePool (PoolAllocationType, AllocationSize, (VOID **) &Memory);
  if (Memory != NULL) {
    tBS->CopyMem (Memory, Buffer, AllocationSize);
  }

  return Memory;
}

/*++

Routine Description:
  Allocates pool memory and initializes the memory to zeros.

Arguments:
  Size                 - Size in bytes of the pool being requested.

Returns:

  EFI_SUCEESS          - The requested number of bytes were allocated.

  EFI_OUT_OF_RESOURCES - The pool requested could not be allocated.

--*/
VOID *
SctAllocateZeroPool (
  IN UINTN                Size
  )
{
  VOID                    *p;

  p = SctAllocatePool (Size);
  if (p) {
    SctZeroMem (p, Size);
  }

  return p;
}


/*++

Routine Description:
  Adjusts the size of a previously allocated buffer.

Arguments:
  OldPool               - A pointer to the buffer whose size is being adjusted.
  OldSize               - The size of the current buffer.
  NewSize               - The size of the new buffer.

Returns:

  EFI_SUCEESS           - The requested number of bytes were allocated.

  EFI_OUT_OF_RESOURCES  - The pool requested could not be allocated.

  EFI_INVALID_PARAMETER - The buffer was invalid.

--*/
VOID *
SctReallocatePool (
  IN VOID                 *OldPool,
  IN UINTN                OldSize,
  IN UINTN                NewSize
  )
{
  VOID                    *NewPool;

  NewPool = NULL;
  if (NewSize) {
    NewPool = SctAllocatePool (NewSize);
  }

  if (OldPool) {
    if (NewPool) {
      tBS->CopyMem (NewPool, OldPool, OldSize < NewSize ? OldSize : NewSize);
    }
    SctFreePool (OldPool);
  }

  return NewPool;
}


/*++

Routine Description:
  Releases a previously allocated buffer.

Arguments:
  Buffer                - A pointer to the buffer to free.

Returns:

  EFI_SUCEESS           - The requested number of bytes were allocated.

  EFI_INVALID_PARAMETER - The buffer was invalid.

--*/
VOID
SctFreePool (
  IN VOID                 *Buffer
  )
{
  tBS->FreePool (Buffer);
}
