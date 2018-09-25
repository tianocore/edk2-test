/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  lock.c

Abstract:

  Implements SCT_LOCK

--*/

#include "SctLibInternal.h"

/*++

Routine Description:

  Initialize a basic mutual exclusion lock.   Each lock
  provides mutual exclusion access at it's task priority
  level.  Since there is no-premption (at any TPL) or
  multiprocessor support, acquiring the lock only consists
  of raising to the locks TPL.

  Note on a debug build the lock is acquired and released
  to help ensure proper usage.

Arguments:

  Lock        - The SCT_LOCK structure to initialize

  Priority    - The task priority level of the lock


Returns:

  An initialized F Lock structure.

--*/
VOID
SctInitializeLock (
  IN OUT SCT_LOCK    *Lock,
  IN EFI_TPL      Priority
  )
{
  Lock->Tpl = Priority;
  Lock->OwnerTpl = 0;
  Lock->Lock = 0;
}

/*++

Routine Description:

  Raising to the task priority level of the mutual exclusion
  lock, and then acquires ownership of the lock.

Arguments:

  Lock        - The lock to acquire

Returns:

  Lock owned

--*/
VOID
SctAcquireLock (
  IN SCT_LOCK    *Lock
  )
{
  if (tBS) {
    if (tBS->RaiseTPL != NULL) {
      Lock->OwnerTpl = tBS->RaiseTPL (Lock->Tpl);
    }
  } else {
    // Unsupported
    ASSERT(0);
  }
  Lock->Lock += 1;
  ASSERT (Lock->Lock == 1);
}

/*++

Routine Description:

  Releases ownership of the mutual exclusion lock, and
  restores the previous task priority level.

Arguments:

  Lock        - The lock to release

Returns:

  Lock unowned

--*/
VOID
SctReleaseLock (
  IN SCT_LOCK    *Lock
  )
{
  EFI_TPL     Tpl;

  Tpl = Lock->OwnerTpl;
  ASSERT(Lock->Lock == 1);
  Lock->Lock -= 1;
  if (tBS) {
    if (tBS->RestoreTPL != NULL) {
      tBS->RestoreTPL (Tpl);
    }
  } else {
    // Unsupported
    ASSERT(0);
  }
}

EFI_STATUS
SctAcquireLockOrFail (
  IN SCT_LOCK  *Lock
  )
{
  if (Lock->Lock != 0) {
    //
    // Lock is already owned, so bail out
    //
    return EFI_ACCESS_DENIED;
  }

  if (tBS) {
    if (tBS->RestoreTPL != NULL) {
      Lock->OwnerTpl = tBS->RaiseTPL (Lock->Tpl);
    }
  } else {
    // Unsupported
    ASSERT(0);
  }

  Lock->Lock += 1;
  return EFI_SUCCESS;
}
