/*++
  The material contained herein is not a license, either
  expressly or impliedly, to any intellectual property owned
  or controlled by any of the authors or developers of this
  material or to any contribution thereto. The material
  contained herein is provided on an "AS IS" basis and, to the
  maximum extent permitted by applicable law, this information
  is provided AS IS AND WITH ALL FAULTS, and the authors and
  developers of this material hereby disclaim all other
  warranties and conditions, either express, implied or
  statutory, including, but not limited to, any (if any)
  implied warranties, duties or conditions of merchantability,
  of fitness for a particular purpose, of accuracy or
  completeness of responses, of results, of workmanlike
  effort, of lack of viruses and of lack of negligence, all
  with regard to this material and any contribution thereto.
  Designers must not rely on the absence or characteristics of
  any features or instructions marked "reserved" or
  "undefined." The Unified EFI Forum, Inc. reserves any
  features or instructions so marked for future definition and
  shall have no responsibility whatsoever for conflicts or
  incompatibilities arising from future changes to them. ALSO,
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY
  CONTRIBUTION THERETO.

  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF
  THE POSSIBILITY OF SUCH DAMAGES.

  Copyright 2006 - 2012 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.

--*/

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

  Status = tBS->AllocatePool (PoolAllocationType, Size, &p);
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
  tBS->AllocatePool (PoolAllocationType, AllocationSize, &Memory);
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
