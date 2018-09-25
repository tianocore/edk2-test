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
  
    EmsRivlNameScope.c
    
Abstract:

    Implementation of RIVL Name Space

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"
#include "EmsRivlEndian.h"
#include "EmsRivlUtil.h"
#include "EmsRpcMain.h"
#include "EmsRivlTclVar.h"
#include "EmsThread.h"

RIVL_SCOPE  *RivlScopes[SCOPE_STACK_DEPTH];
UINT32      ScopeDepth = 0;

INT32
TclBeginScope (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "BeginScope" implementation routine 

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];

  LogCurrentCommand (Argc, Argv);

  if (Argc != 2) {
    sprintf (ErrorBuff, "%s", "BeginScope: BeginScope scopename");
    goto ErrorExit;
  };

  if (strlen (Argv[1]) >= MAX_SCOPENAME_LEN) {
    sprintf (ErrorBuff, "BeginScope: scopename \"%s\" is too long", Argv[1]);
    goto ErrorExit;
  }

  ScopeDepth++;

  RivlScopes[ScopeDepth] = (RIVL_SCOPE *) calloc (1, sizeof (RIVL_SCOPE));
  strcpy (RivlScopes[ScopeDepth]->Name, Argv[1]);

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (
    Interp,
    ErrorBuff,
    (INT8 *) NULL
    );
  return TCL_ERROR;
}

INT32
TclEndScope (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EndScope" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  INT8          Message[MAX_MESSAGE_LEN];
  INT8          *Name;
  RIVL_VARIABLE *Header;
  RIVL_VARIABLE *Var;
  INT32         Length;

  LogCurrentCommand (Argc, Argv);

  if (Argc != 2) {
    sprintf (ErrorBuff, "%s", "EndScope: EndScope scopename");
    goto ErrorExit;
  };

  if (ScopeDepth == 0) {
    sprintf (ErrorBuff, "EndScope: None scopename \"%s\" defined", Argv[1]);
    goto ErrorExit;
  }

  if (strcmp (Argv[1], RivlScopes[ScopeDepth]->Name)) {
    sprintf (
      ErrorBuff,
      "EndScope: scopename \"%s\" does not match current scopename \"%s\"",
      Argv[1],
      RivlScopes[ScopeDepth - 1]->Name
      );
    goto ErrorExit;
  }

  Header = RivlVariableGetByScope (RivlScopes[ScopeDepth]);

  for (Var = Header; Var; Var = Var->NextByScope) {
    //
    // Build Message and Send it to EAS
    //
    Message[0] = '\0';
    strcat (Message, "RIVL_DELVAR");
    if (Argc == 2) {
      strcat (Message, " ");
      strcat (Message, Var->Name);
    }

    Length = strlen (Message);
    RpcSendMessage (Length, Message);
    memset (Message, 0, MAX_MESSAGE_LEN);
    Length = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);
  }

  for (Var = Header; Var;) {
    Name  = _strdup (Var->Name);
    Var   = Var->NextByScope;
    //
    // Local Delete variable and its relative TCL variable
    //
    RivlVariableRemoveByName (Name);
    RivlRemoveTclVarsByName (Interp, Name);
    free (Name);

  }

  free (RivlScopes[ScopeDepth]);
  RivlScopes[ScopeDepth] = NULL;
  ScopeDepth--;
  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (
    Interp,
    ErrorBuff,
    (INT8 *) NULL
    );
  return TCL_ERROR;
}

VOID
EmsClearLocalScope(
  VOID
  )
/*++

Routine Description:

  Clear all local scope

Arguments:

  None

Returns:

  None

--*/
{
  while(ScopeDepth > 0)
  {
    free (RivlScopes[ScopeDepth]);
    RivlScopes[ScopeDepth] = NULL;
    ScopeDepth--;
  }
}
