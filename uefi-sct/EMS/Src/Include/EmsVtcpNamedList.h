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
  
    EmsVtcpNamedList.h
    
Abstract:

    Data definition for Vtcp

--*/

#ifndef __EMS_NAMED_LIST_H__
#define __EMS_NAMED_LIST_H__

#include "EmsTypes.h"

#define MAX_NAMED_LIST_NAME_LEN 32
typedef struct _NL_NODE {
  INT8            Name[MAX_NAMED_LIST_NAME_LEN];
  VOID_P          *Goods;
  struct _NL_NODE *Next;
} NL_NODE;

typedef NL_NODE *NL_LIST;

NL_NODE         *
EmsNlCreateNode (
  IN CONST INT8     *Name,
  VOID_P             *Goods
  )
/*++

Routine Description:

  Create a TCP name list node

Arguments:

  Name  - The name string
  Goods - The goods

Returns:

  Return the new node

--*/
;

NL_NODE         *
EmsNlFindNodeByName (
  CONST INT8       *Name,
  NL_LIST          *List
  )
/*++

Routine Description:

  Find a name list node by name

Arguments:

  Name  - The name string
  List  - The name list

Returns:

  Return the name list node found

--*/
;

VOID_P          *
EmsNlFindGoodsByName (
  CONST INT8       *Name,
  NL_LIST          *List
  )
/*++

Routine Description:

  find a goods by name

Arguments:

  Name  - The name string
  List  - The name list

Returns:

  None

--*/
;

VOID_P
EmsNlFreeNode (
  NL_NODE         *Node
  )
/*++

Routine Description:

  Free a name list node

Arguments:

  Node  - The name list node

Returns:

  None

--*/
;

NL_NODE         *
EmsNlRemoveNodeByName (
  CONST INT8      *Name,
  NL_LIST         *List
  )
/*++

Routine Description:

  Remove a name node by name

Arguments:

  Name  - The name string
  List  - The name list

Returns:

  return the name node

--*/
;

VOID_P
EmsNlRemoveNode (
  NL_NODE         *Node,
  NL_LIST         *List
  )
/*++

Routine Description:

  Remove a name list node

Arguments:

  Node  - The name list node
  List  - The name list

Returns:

  None

--*/
;

VOID_P
EmsNlAddNode (
  NL_NODE         *Node,
  NL_LIST         *List
  )
/*++

Routine Description:

  add a name list node

Arguments:

  Node  - The name list node
  List  - The name list

Returns:

  None

--*/
;

VOID_P
EmsNlAddGoods (
  IN CONST INT8 *Name,
  VOID_P            *Goods,
  NL_LIST           *List
  )
/*++

Routine Description:

  Add a goods to name list

Arguments:

  Name  - The name string
  Goods - The goods
  List  - The name list

Returns:

  None

--*/
;

VOID_P
EmsNlDestroyList (
  NL_LIST         *List
  )
/*++

Routine Description:

  Destroy the name list

Arguments:

  List  - The name list to be destroy

Returns:

  None

--*/
;

#endif
