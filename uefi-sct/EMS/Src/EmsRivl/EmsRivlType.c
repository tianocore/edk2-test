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
  
    EmsRivlType.c
    
Abstract:

    Implementation of RIVL type related functions

--*/

#include "EmsRivlMain.h"
#include "EmsRivlType.h"
#include "stdlib.h"

RIVL_TYPE *ExternalTypes = NULL;

RIVL_TYPE *
RivlTypeFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find RIVL variable's type accroding to name

Arguments:

  Name  - The type name

Returns:

  return the RIVL type found

--*/
{
  RIVL_TYPE *TPointer;
  TPointer = ExternalTypes;
  while (TPointer) {
    if (0 == strcmp (Name, TPointer->Name)) {
      break;
    }

    TPointer = TPointer->Next;
  }

  return TPointer;
}

BOOLEAN
IsExternalType (
  INT8 *Name
  )
/*++

Routine Description:

  Check whether the type is an external type

Arguments:

  Name  - The type name

Returns:

  TRUE or FALSE

--*/
{
  return RivlTypeFindByName (Name) ? TRUE : FALSE;
}

VOID_P
RivlTypeRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove RIVL type accroding to name

Arguments:

  Name  - The type name

Returns:

  None

--*/
{
  RIVL_TYPE *TPointer;

  RIVL_TYPE *DestroyPointer;

  if (ExternalTypes == NULL) {
    return ;
  }

  if (0 == strcmp (Name, ExternalTypes->Name)) {
    DestroyPointer  = ExternalTypes;
    ExternalTypes   = ExternalTypes->Next;
    RivlTypeDestroy (DestroyPointer);
    return ;
  }

  for (TPointer = ExternalTypes; TPointer && TPointer->Next; TPointer = TPointer->Next) {
    if (0 == strcmp (Name, TPointer->Next->Name)) {
      DestroyPointer  = TPointer->Next;
      TPointer->Next  = TPointer->Next->Next;
      RivlTypeDestroy (DestroyPointer);
      return ;
    }
  }
  //
  //  Tcl_DeleteCommand(tcl_interpreter, name);
  //
}

VOID_P
RivlTypeDestroy (
  RIVL_TYPE *Type
  )
/*++

Routine Description:

  Destroy a RIVL type

Arguments:

  Type  - The RIVL type to be destroied

Returns:

  None

--*/
{
  if (Type) {
    free (Type->Members);
    free (Type);
  }
}

VOID_P
RivlTypeDestroyAll (
  VOID_P
  )
/*++

Routine Description:

  Destroy all the RIVL types

Arguments:

  None

Returns:

  None

--*/
{
  RIVL_TYPE *TPointer;
  TPointer  = ExternalTypes;

  TPointer  = ExternalTypes;
  while (TPointer) {
    ExternalTypes = TPointer->Next;
    RivlTypeDestroy (TPointer);
    TPointer = ExternalTypes;
  }
}

VOID_P
RivlTypeAdd (
  RIVL_TYPE *Type
  )
/*++

Routine Description:

  Add a new RIVL type

Arguments:

  Type  - The RIVL type to be added

Returns:

  None

--*/
{
  RIVL_TYPE *TPointer;
  if (Type == NULL) {
    return ;
  }

  if (ExternalTypes == NULL) {
    ExternalTypes = Type;
    Type->Next    = NULL;
    return ;
  }

  for (TPointer = ExternalTypes; TPointer->Next; TPointer = TPointer->Next)
    ;
  TPointer->Next  = Type;
  Type->Next      = NULL;

  return ;
}
