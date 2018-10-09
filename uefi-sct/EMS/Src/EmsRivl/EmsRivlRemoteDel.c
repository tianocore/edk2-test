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
  
    EmsRivlRemoteDel.c
    
Abstract:

    Implementation of RIVL type/func/variable delete 

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"
#include "EmsRivlUtil.h"
#include "EmsRivlType.h"
#include "EmsRpcMain.h"
#include "EmsRivlTclVar.h"
#include "EmsRivlFunc.h"

INT32
TclRemoteDelType (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DelType" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  INT8  Message[MAX_MESSAGE_LEN];
  INT8  *Name;
  INT32 Length;

  Name = NULL;
  //
  // Check argument count, should be 1
  //
  if ((Argc != 1) && (Argc != 2)) {
    sprintf (ErrorBuff, "EMS_DELTYPE : Syntax Error!");
    goto ErrorExit;
  }
  //
  // Check if the type exist?
  //
  if (Argc == 2) {
    Name = (INT8 *) Argv[1];
    if (NULL == RivlTypeFindByName (Name)) {
      sprintf (
        ErrorBuff,
        "EMS_DELTYPE : Type %s not defined!",
        Name
        );
      goto ErrorExit;
    }
  }
  //
  // Build Message and Send it to EAS
  //
  memset (Message, 0, MAX_MESSAGE_LEN);
  Message[0] = '\0';
  strcat (Message, "RIVL_DELTYPE");
  if (Name) {
    strcat (Message, " ");
    strcat (Message, Argv[1]);
  }

  Length = strlen (Message);
  RpcSendMessage (Length, Message);
  Message[0]  = 0;
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);

  //
  // Local Delete Type
  //
  if (Name) {
    RivlTypeRemoveByName (Name);
  } else {
    RivlTypeDestroyAll ();
  }

  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclRemoteDelVar (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DelVar" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{

  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  INT8  Message[MAX_MESSAGE_LEN];
  INT8  *Name;
  INT32 Length;

  Name = NULL;
  //
  // Check argument count, should be 1
  //
  if ((Argc != 1) && (Argc != 2)) {
    sprintf (ErrorBuff, "EMS_DELTYPE : Syntax Error!");
    goto ErrorExit;
  }
  //
  // Check if the variable exist?
  //
  if (Argc == 2) {
    Name = (INT8 *) Argv[1];
    if (NULL == RivlVariableFindByName (Name)) {
      sprintf (ErrorBuff, "EMS_DELVAR : Variable %s not defined!", Name);
      goto ErrorExit;
    }
  }
  //
  // Build Message and Send it to EAS
  //
  Message[0] = '\0';
  strcat (Message, "RIVL_DELVAR");
  if (Argc == 2) {
    strcat (Message, " ");
    strcat (Message, Argv[1]);
  }

  Length = strlen (Message);
  RpcSendMessage (Length, Message);
  Message[0]  = '\0';
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);
  //
  // rivl_msg_send;
  //
  // Local Delete variable and its relative TCL variable
  //
  if (Name) {
    RivlVariableRemoveByName (Name);
    RivlRemoveTclVarsByName (Interp, (INT8 *) Name);
  } else {
    RivlVariableDestroyAll ();
    RivlRemoveTclVarsAll (Interp);
  }

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclRemoteDelFunc (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DelFunc" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  INT8  *Name;

  Name = NULL;
  //
  // Check argument count, should be 1
  //
  if ((Argc != 1) && (Argc != 2)) {
    sprintf (ErrorBuff, "EMS_DELTYPE : Syntax Error!");
    goto ErrorExit;
  }
  //
  // Check if the variable exist?
  //
  if (Argc == 2) {
    Name = (INT8 *) Argv[1];
    if (NULL == RivlFunctionFindByName (Name)) {
      sprintf (ErrorBuff, "EMS_DELTYPE : Variable %s not defined!", Name);
      goto ErrorExit;
    }
  }
  //
  // Local Delete variable and its relative TCL variable
  //
  if (Name) {
    RivlFunctionRemoveByName (Name);
  } else {
    RivlFunctionRemoveAll ();
  }

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
