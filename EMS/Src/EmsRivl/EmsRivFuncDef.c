/** @file
 
  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsRivFuncDef.c
    
Abstract:

    Implementation of RIVL function declaration

--*/

#include "stdlib.h"
#include "EmsRivlType.h"
#include "EmsRivlFunc.h"
#include "EmsRivlUtil.h"
#include "EmsRivlMain.h"

#define MAX_MEMBER_NUM  100

INT32
TclFuncDef (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Func" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          *Name;
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  UINT32        ArgNum;
  INT8          Type[MAX_STRING_LEN];
  UINT32        Index;
  UINT32        Len;
  UINT32        Pos;
  INT8          Line[MAX_STRING_LEN];

  RIVL_FUNCTION *TempFunction;

  TempFunction = NULL;
  LogCurrentCommand (Argc, Argv);

  //
  // Parse argument
  //
  if (Argc != 3) {
    sprintf (ErrorBuff, "%s: Syntax error.\n", Argv[0]);
    goto ErrorExit;
  }

  Name = (INT8 *) Argv[1];
  if (strlen (Name) >= MAX_FUNTIONNAME_LEN) {
    sprintf (ErrorBuff, "%s: Function Name is too long.\n", Argv[0]);
    goto ErrorExit;
  }
  //
  // Check if this type has existed. If yes, give a warning and return
  //
  if (FunctionExist (Name)) {
    sprintf (ErrorBuff, "%s: Function '%s' redefined.\n", Argv[0], Name);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    goto ErrorExit;
  }

  TempFunction = (RIVL_FUNCTION *) malloc (sizeof (RIVL_FUNCTION));

  strcpy (TempFunction->Name, Name);

  Len     = strlen (Argv[2]);
  Pos     = 0;
  ArgNum  = 0;
  while (Pos != Len) {
    Pos = GetNextLine ((INT8 *) Argv[2], Pos, Line);
    if ('\0' == *Line) {
      continue;
    }

    StripString (Line, Type);
    if (!((RivlInternalTypeFindByName (Type)) || (RivlTypeFindByName (Type)))) {
      sprintf (ErrorBuff, "%s: Type '%s' doesn't exist.\n", Argv[0], Type);
      Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
      goto ErrorExit;
    }

    TempFunction->arg_type[ArgNum] = _strdup (Type);
    ArgNum++;
    if (ArgNum == MAX_ARG_NUM) {
      sprintf (ErrorBuff, "%s: Function '%s' has too many argumems.\n", Argv[0], Name);
      Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
      goto ErrorExit;
    }
  }

  TempFunction->Argc = ArgNum;
  RivlFunctionAdd (TempFunction);

  Tcl_CreateCommand (
    TestCaseInterp,
    Name,
    TclFuncDeclare,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  return TCL_OK;

ErrorExit:
  if (TempFunction) {
    for (Index = 0; Index < ArgNum; Index++) {
      free (TempFunction->arg_type[Index]);
    }

    free (TempFunction);
  }

  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
