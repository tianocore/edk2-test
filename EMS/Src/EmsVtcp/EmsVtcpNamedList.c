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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsVtcpNamedList.c
    
Abstract:

    

--*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EmsVtcpNamedList.h"

NL_NODE *
EmsNlCreateNode (
  IN CONST INT8      *Name,
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
{
  NL_NODE *Node;
  Node = (NL_NODE *) malloc (sizeof (NL_NODE));
  strcpy (Node->Name, Name);
  Node->Goods = Goods;
  Node->Next  = NULL;
  return Node;
}

NL_NODE *
EmsNlFindNodeByName (
  CONST INT8             *Name,
  NL_LIST                *List
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
{
  NL_NODE *Node;
  Node = *List;
  while (Node) {
    if (0 == strcmp (Name, Node->Name)) {
      break;
    }

    Node = Node->Next;
  }

  return Node;
}

VOID_P *
EmsNlFindGoodsByName (
  CONST INT8             *Name,
  NL_LIST                *List
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
{
  NL_NODE *Node;
  Node = EmsNlFindNodeByName (Name, List);
  if (NULL != Node) {
    return Node->Goods;
  }

  return Node;
}

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
{
  if (NULL == Node) {
    return ;
  }

  if (NULL != Node->Goods) {
    free (Node->Goods);
  }

  free (Node);
}

NL_NODE *
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
{
  NL_NODE *Node;

  NL_NODE *exact_node;

  Node = *List;
  if (NULL == Node) {
    return NULL;
  }

  if (0 == strcmp (Name, Node->Name)) {
    exact_node  = Node;
    *List       = Node->Next;
    return exact_node;
  }

  for (Node = *List; Node && Node->Next; Node = Node->Next) {
    if (0 == strcmp (Name, Node->Next->Name)) {
      exact_node  = Node->Next;
      Node->Next  = Node->Next->Next;
      return exact_node;
    }
  }

  return NULL;
}

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
{
  NL_NODE *NPointer;

  if (NULL == Node) {
    return ;
  }

  if (*List == Node) {
    *List = (*List)->Next;
    return ;
  }

  for (NPointer = *List; NPointer && NPointer->Next; NPointer = NPointer->Next) {
    if (NPointer->Next == Node) {
      NPointer->Next = NPointer->Next->Next;
      return ;
    }
  }
}

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
{
  NL_NODE *NPointer;
  if (NULL == Node) {
    return ;
  }

  if (*List == NULL) {
    *List       = Node;
    Node->Next  = NULL;
    return ;
  }

  for (NPointer = *List; NPointer->Next; NPointer = NPointer->Next)
    ;
  NPointer->Next  = Node;
  Node->Next      = NULL;
  return ;
}

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
{
  NL_NODE *Node;
  Node = EmsNlFindNodeByName (Name, List);
  if (NULL == Node) {
    Node = EmsNlCreateNode (Name, Goods);
    EmsNlAddNode (Node, List);
  } else {
    free (Goods);
  }

  Node->Goods = Goods;
}

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
{
  NL_NODE *NPointer;

  NL_NODE *NPointer1;

  NPointer = *List;
  while (NPointer) {
    NPointer1 = NPointer;
    NPointer  = NPointer->Next;
    EmsNlFreeNode (NPointer1);
  }

  *List = NULL;
}
