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
  
    EmsRpcTarget.c
    
Abstract:

    Implementation of RPC target related Functions

--*/

#include "EmsTypes.h"
#include "EmsMain.h"
#include "EmsUtilityString.h"
#include "EmsRpcTarget.h"

STATIC TARGET_T *Targets = NULL;

VOID_P
RpcTargetAddByMac (
  INT8      *Mac
  )
/*++

Routine Description:

  Add a target identified by MAC address

Arguments:

  Mac - The MAC address

Returns:

  None

--*/
{
  TARGET_T  *Node;
  TARGET_T  *TargetPointer;

  if (Mac == NULL) {
    return ;

  }

  Node = malloc (sizeof (TARGET_T));
  if (Node == NULL) {
    return ;
  }

  memcpy (Node->Mac, Mac, 6);

  if (Targets == NULL) {
    Targets     = Node;
    Node->Next  = NULL;
    return ;
  }

  for (TargetPointer = Targets; TargetPointer->Next; TargetPointer = TargetPointer->Next)
    ;

  TargetPointer->Next = Node;
  Node->Next          = NULL;
  return ;
}

TARGET_T *
RpcTargetFindByMac (
  INT8            *Mac
  )
/*++

Routine Description:

  Find the taget by MAC address

Arguments:

  Mac - MAC address

Returns:

  The target found

--*/
{
  TARGET_T  *TargetPointer;

  TargetPointer = Targets;
  while (TargetPointer) {
    if (0 == memcmp (Mac, TargetPointer->Mac, 6)) {
      break;
    }

    TargetPointer = TargetPointer->Next;
  }

  return TargetPointer;
}

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
{
  TARGET_T  *TargetPointer;

  TARGET_T  *TargetPointer1;

  //
  // remove header of the list
  //
  TargetPointer = Targets;
  while (TargetPointer != NULL) {
    TargetPointer1 = TargetPointer->Next;
    free (TargetPointer);
    TargetPointer = TargetPointer1;
  }

  Targets = NULL;
}
//
// dump all Targets to buffer
//
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
{
  TARGET_T  *TargetPointer;
  INT8      Str[18];

  TargetPointer = Targets;
  if (NULL == TargetPointer) {
    return ;
  }

  Buff[0] = '\0';
  while (TargetPointer) {
    MacToAsciiString (Str, TargetPointer->Mac);
    strcat (Buff, Str);
    TargetPointer = TargetPointer->Next;
  }
}
