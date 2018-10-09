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
  
    EmsRivlFunc.c
    
Abstract:

    Implementation of RIVL function related Functions

--*/

#include "EmsRivlMain.h"
#include "EmsRivlFunc.h"
#include "stdlib.h"

STATIC RIVL_FUNCTION  *Functions = NULL;

RIVL_FUNCTION *
RivlFunctionFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find a Rivl function type's variable accroding to name

Arguments:

  Name  - 

Returns:

  return the found variable

--*/
{
  RIVL_FUNCTION *FPointer;
  FPointer = Functions;
  while (FPointer) {
    if (0 == strcmp (Name, FPointer->Name)) {
      break;
    }

    FPointer = FPointer->Next;
  }

  return FPointer;
}

BOOLEAN
FunctionExist (
  INT8 *Name
  )
/*++

Routine Description:

  Check whether the Rivl function type's variable is exist

Arguments:

  Name  - The name of the Rivl function

Returns:

  TRUE or FALSE

--*/
{
  return RivlFunctionFindByName (Name) ? TRUE : FALSE;
}

VOID_P
RivlFunctionRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove a Rivl function type's variable accroding to name

Arguments:

  Name  - The name of the function

Returns:

  None

--*/
{
  RIVL_FUNCTION *FPointer;

  if (Functions == NULL) {
    return ;
  }

  if (strcmp (Name, Functions->Name)) {
    Functions = Functions->Next;
    return ;
  }

  for (FPointer = Functions; FPointer && FPointer->Next; FPointer = FPointer->Next) {
    if (0 == strcmp (Name, FPointer->Next->Name)) {
      FPointer->Next = FPointer->Next->Next;
      return ;
    }
  }
}

VOID_P
RivlFunctionDestroy (
  RIVL_FUNCTION *Func
  )
/*++

Routine Description:

  Destroy a Rivl function

Arguments:

  Func  - The pointer to a Rivl function

Returns:

  None

--*/
{
  if (Func) {
    free (Func);
  }
}

VOID_P
RivlFunctionAdd (
  RIVL_FUNCTION *Func
  )
/*++

Routine Description:

  Add a new Rivl function

Arguments:

  Func  - The pointer to a Rivl function

Returns:

  None

--*/
{
  RIVL_FUNCTION *FPointer;
  if (Func == NULL) {
    return ;
  }

  if (Functions == NULL) {
    Functions   = Func;
    Func->Next  = NULL;
    return ;
  }

  for (FPointer = Functions; FPointer->Next; FPointer = FPointer->Next)
    ;
  FPointer->Next  = Func;
  Func->Next      = NULL;
  return ;
}

VOID_P
RivlFunctionRemoveAll (
  VOID_P
  )
/*++

Routine Description:

  Remove all the Rivl functions

Arguments:

  None

Returns:

  None

--*/
{
  RIVL_FUNCTION *FPointer;

  //
  // remove header of the list
  //
  while (FPointer = Functions) {
    Functions = FPointer->Next;
    RivlFunctionDestroy (FPointer);
  }
}
