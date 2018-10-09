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
  
    EmsTclCleanup.c
    
Abstract:

  Implementation of EMS TCL cleanup function.

--*/

#include <windows.h>
#include "EmsTclCleanup.h"

STATIC EmsTclResMng *EmsTclResStack;
STATIC HANDLE       EmsTclResStackMutex;

VOID
EmsTclResStackPush (
  EmsTclResMng *Mng
  )
/*++

Routine Description:

  Push a EMS TCL resource into stack

Arguments:

  Mng - The structure for the EMS TCL resource management

Returns:

  None

--*/
{
  WaitForSingleObject (EmsTclResStackMutex, INFINITE);
  Mng->Next       = EmsTclResStack;
  EmsTclResStack  = Mng;
  ReleaseMutex (EmsTclResStackMutex);
}

VOID
EmsTclResStackPop (
  EmsTclResMng **Mng
  )
/*++

Routine Description:

  Pop a EMS TCL resource from stack

Arguments:

  Mng - The structure for the EMS TCL resource management

Returns:

  None

--*/
{
  *Mng            = EmsTclResStack;
  EmsTclResStack  = EmsTclResStack->Next;
  (*Mng)->Next    = NULL;
}

STATIC
BOOLEAN
EmsTclResStackIsEmpty (
  VOID
  )
/*++

Routine Description:

  Check whether the EMS TCL resouce stack is empty

Arguments:

  None

Returns:

  TRUE or FALSE

--*/
{
  BOOLEAN Result;
  Result = (EmsTclResStack == NULL) ? TRUE : FALSE;
  return Result;
}

STATIC
INT32
EmsTclResCleanup (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsTclResCleanup" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  EmsTclResMng  *Temp;
  Temp = NULL;
  WaitForSingleObject (EmsTclResStackMutex, INFINITE);
  while (!EmsTclResStackIsEmpty ()) {
    EmsTclResStackPop (&Temp);
    ReleaseMutex (EmsTclResStackMutex);
    (Temp->CleanupFunc) (Temp->Res);
    WaitForSingleObject (EmsTclResStackMutex, INFINITE);
  }

  ReleaseMutex (EmsTclResStackMutex);
  return TCL_OK;
}

VOID_P
ResTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS cleanup related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  EmsTclResStack      = NULL;
  EmsTclResStackMutex = CreateMutex (NULL, FALSE, NULL);

  Tcl_CreateCommand (
    Interp,
    "EmsTclResCleanup",
    EmsTclResCleanup,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
}
