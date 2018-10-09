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
  
    EmsRivlVar.c
    
Abstract:

    Implementation of RIVL variable related functions

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"

STATIC RIVL_VARIABLE  *Variables = NULL;

RIVL_VARIABLE *
RivlVariableFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find RIVL variable accroding to name

Arguments:

  Name  - the name of variable

Returns:

  Return the pointer to RIVL variable

--*/
{
  RIVL_VARIABLE *VPointer;

  if (!Name) {
    return NULL;
  }

  VPointer = Variables;
  while (VPointer) {
    if (VPointer->Name && (0 == strcmp (Name, VPointer->Name))) {
      return VPointer;
    }

    VPointer = VPointer->Next;
  }

  return NULL;
}

VOID_P
RivlVariableRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove RIVL variable accroding to name

Arguments:

  Name  - The name of variable

Returns:

  None

--*/
{
  RIVL_VARIABLE *VPointer;

  RIVL_VARIABLE *destroy;

  if (Variables == NULL) {
    return ;
  }
  //
  // if the first node is to be deleted
  //
  if (0 == strcmp (Name, Variables->Name)) {
    destroy   = Variables;
    Variables = destroy->Next;
    RivlVariableDestroy (destroy);
    return ;
  }
  //
  // Find the variable
  //
  for (VPointer = Variables; VPointer && VPointer->Next; VPointer = VPointer->Next) {
    if (0 == strcmp (Name, VPointer->Next->Name)) {
      destroy         = VPointer->Next;
      VPointer->Next  = VPointer->Next->Next;
      break;
    }
  }
  //
  // Remove it from the chain by scope
  //
  for (VPointer = Variables; VPointer && VPointer != destroy; VPointer = VPointer->Next) {
    if (VPointer->NextByScope == destroy) {
      VPointer->NextByScope = destroy->NextByScope;
      break;
    }
  }

  RivlVariableDestroy (destroy);
  return ;
}

VOID_P
RivlVariableDestroy (
  RIVL_VARIABLE *VPointer
  )
/*++

Routine Description:

  Destroy a RIVL variable

Arguments:

  VPointer - The pointer to the RIVL variable

Returns:

  None

--*/
{
  UINT32  Index;
  UINT32  Num;

  if (!VPointer) {
    return ;
  }

  if (VPointer->InternalValue) {
    free (VPointer->InternalValue);
  }

  if (VPointer->Value) {
    Num = VPointer->IsArray ? VPointer->ArrayNum : VPointer->EType->MemberNum;
    for (Index = 0; Index < Num; Index++) {
      if (VPointer->Value[Index].Value) {
        free (VPointer->Value[Index].Value);
      }
    }

    free (VPointer->Value);
  }

  free (VPointer);
}

VOID_P
RivlVariableDestroyAll (
  VOID_P
  )
/*++

Routine Description:

  Destroy all the RIVL variables

Arguments:

  None

Returns:

  None

--*/
{
  RIVL_VARIABLE *Variable;
  Variable = Variables;
  while (Variable) {
    Variables = Variable->Next;
    RivlVariableDestroy (Variable);
    Variable = Variables;
  }
}

VOID_P
RivlVariableAdd (
  RIVL_VARIABLE *Var
  )
/*++

Routine Description:

  Add a new RIVL variable

Arguments:

  Var - The new RIVL variable to be added

Returns:

  None

--*/
{
  RIVL_VARIABLE *VPointer;
  if (Var == NULL) {
    return ;
  }

  if (Variables == NULL) {
    Variables = Var;
    Var->Next = NULL;
    return ;
  }
  //
  // Add to the tail  by scope
  //
  for (VPointer = Variables; VPointer; VPointer = VPointer->Next) {
    if ((VPointer->Scope == Var->Scope) && (NULL == VPointer->NextByScope)) {
      VPointer->NextByScope = Var;
      break;
    }
  }

  for (VPointer = Variables; VPointer->Next; VPointer = VPointer->Next)
    ;
  VPointer->Next    = Var;
  Var->Next         = NULL;
  Var->NextByScope  = NULL;

  return ;
}

RIVL_VARIABLE *
RivlVariableGetByScope (
  RIVL_SCOPE   *Scope
  )
/*++

Routine Description:

  Get RIVL variables accroding to scope

Arguments:

  Scope - Used to find RIVL variables

Returns:

  return the Pointer to RIVL variables

--*/
{
  RIVL_VARIABLE *VPointer;
  if (NULL == Scope) {
    return NULL;
  }

  for (VPointer = Variables; VPointer; VPointer = VPointer->Next) {
    if (VPointer->Scope == Scope) {
      return VPointer;
    }
  };
  return NULL;
}
