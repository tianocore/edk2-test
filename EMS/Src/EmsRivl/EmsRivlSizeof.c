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
  
    EmsRivlSizeof.c
    
Abstract:

    Implementation of RIVL TCL command Sizeof

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "EmsRivlType.h"
#include "EmsRivlUtil.h"

BOOLEAN
GetSizeofFromName (
  INT8        *TypeName,
  UINT32      *Len
  );

INT32
TclSizeof (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Sizeof" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8    ResultBuff[256];
  UINT32  Len;

  if (Argc != 2) {
    sprintf (ResultBuff, "%s : Format error - Arg missing!", Argv[0]);
    goto ErrorExit;
  }

  if (FALSE == GetSizeofFromName ((INT8 *) Argv[1], &Len)) {
    sprintf (ResultBuff, "%s : get sizeof (%s) failed!", Argv[0], Argv[1]);
    goto ErrorExit;
  }

  sprintf (ResultBuff, "%d", Len);
  Tcl_AppendResult (Interp, ResultBuff, (INT8 *) NULL);

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ResultBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

BOOLEAN
GetSizeofFromName (
  INT8        *Name,
  UINT32      *Len
  )
/*++

Routine Description:

  Set the size of the variable accroding to name

Arguments:

  Name  - The variable name
  Len   - Return size of variable

Returns:

  TRUE or FALSE

--*/
{
  INTERNAL_TYPE *IType;
  RIVL_TYPE     *EType;
  RIVL_VARIABLE *Variable;

  Variable = RivlVariableFindByName (Name);
  if (Variable) {
    if (Variable->Internal) {
      *Len = Variable->IType->Size * Variable->ArrayNum;
    } else {
      *Len = Variable->EType->Size * Variable->ArrayNum;
    }

    return TRUE;
  }
  //
  // Internal type
  //
  IType = RivlInternalTypeFindByName (Name);
  if (IType) {
    *Len = IType->Size;
    return TRUE;
  }
  //
  // External type
  //
  EType = RivlTypeFindByName (Name);
  if (EType) {
    *Len = EType->Size;
    return TRUE;
  }

  return FALSE;
}
