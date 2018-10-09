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
  
    EmsRpcTarget.h
    
Abstract:

    Incude header files for RPC target functions

--*/

#ifndef _EMS_RPC_TARGET_H_
#define _EMS_RPC_TARGET_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct _TARGET_T {
  INT8              Mac[6];
  struct _TARGET_T  *Next;
} TARGET_T;

VOID_P
RpcTargetDumpAll (
  INT8        *Buff
  )
/*++

Routine Description:

  Dump all the targets

Arguments:

  Buff  - The Buffer to contain targets

Returns:

  None

--*/
;

VOID_P
RpcTargetAddByMac (
  INT8      *mac
  )
/*++

Routine Description:

  Add a target identified by MAC address

Arguments:

  Mac - The MAC address

Returns:

  None

--*/
;

TARGET_T  *
RpcTargetFindByMac (
  INT8            *mac
  )
/*++

Routine Description:

  Find the taget by MAC address

Arguments:

  Mac - MAC address

Returns:

  The target found

--*/
;

VOID_P
RpcTargetRemoveAll (
  VOID_P
  )
/*++

Routine Description:

  Remove all the target

Arguments:

  None.

Returns:

  None

--*/
;

#endif
