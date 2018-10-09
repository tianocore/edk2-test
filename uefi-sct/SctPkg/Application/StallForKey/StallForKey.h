/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  StallForKey.h

Abstract:

  Waiting for a key input.

--*/

#ifndef _EFI_STALL_FOR_KEY_H_
#define _EFI_STALL_FOR_KEY_H_

//
// Includes
//

#include "SctLib.h"

//
// Global definitions
//

#define DEFAULT_WAIT_TIME         10        // 10 seconds

//
// Entry point
//

EFI_STATUS
EFIAPI
StallForKey (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

#endif
