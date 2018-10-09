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
  
    EmsRivlDump.c
    
Abstract:

    Implementation of RIVL variable dump routine

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"

INT32
TclDumpVar (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DumpVar" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  INT8          *Name;
  RIVL_VARIABLE *Variable;
  UINT32        Index;

  if (Argc != 2) {
    sprintf (
      ErrorBuff,
      "%s : Syntax error!",
      Argv[0]
      );
  }

  Name      = (INT8 *) Argv[1];

  Variable  = RivlVariableFindByName (Name);

  if (NULL == Variable) {
    sprintf (
      ErrorBuff,
      "%s : Variable %s is undefined!",
      Argv[0],
      Name
      );
    goto ErrorExit;
  }

  if (Variable->Internal) {
    //
    // Internal type variable
    //
    sprintf (
      ErrorBuff,
      "Type  : %s \nArray: %s Value : %s \n",
      Variable->IType->Name,
      Variable->IsArray ? "Yes" : "No",
      ((Variable->InternalValue) != NULL) ? (INT8 *) Variable->InternalValue : "NULL"
      );
    goto End;
  } else {
    //
    // External type variable
    //
    if (Variable->IsArray) {
      for (Index = 0; Index < Variable->ArrayNum; Index++) {
        sprintf (
          ErrorBuff,
          "Name: %s Value: %s\n",
          Variable->Value[Index].Name,
          Variable->Value[Index].Value ? Variable->Value[Index].Value : "NULL"
          );
        Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
      }
    } else {
      for (Index = 0; Index < Variable->EType->MemberNum; Index++) {
        sprintf (
          ErrorBuff,
          "Name: %s Value: %s\n",
          Variable->Value[Index].Name,
          Variable->Value[Index].Value ? Variable->Value[Index].Value : "NULL"
          );
        Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
      }
    }

    return TCL_OK;

  }

End:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
