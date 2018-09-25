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

  RivlCall.h

Abstract:

  Remote Interface Validation Language Call definitions

--*/

#ifndef __RIVL_CALL_H__
#define __RIVL_CALL_H__

#define ENTS_STACK_NUM  12

typedef struct {
  UINTN Number;
  UINTN *StackTop;
  UINTN *StackBottom;
  VOID  *FuncAddr;
  UINTN CallingType;
  UINTN Status;
  UINTN Stack[ENTS_STACK_NUM];
} RIVL_CALL_FRAME;

UINTN
RivlCall (
  VOID  *FuncAddr,
  UINTN CallingType,
  UINTN Number,
  UINTN *StackTop,
  UINTN *StackBottom
  )
/*++

Routine Description:

  Remote Interface verification calling.

Arguments:

  FuncAddr    - Remote calling function address.
  CallingType - Calling type.
  Number      - Calling number.
  StackTop    - Top stack.
  StackBottom - Bottom stack.

Returns:

  

--*/
;

#endif // __RIVL_CALL_H__
