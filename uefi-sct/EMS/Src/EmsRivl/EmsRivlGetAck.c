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
  
    EmsRivlGetAck.c
    
Abstract:

    Implementation of RIVL GetAck(TCL command)

--*/

#include <stdlib.h>
#include "EmsRivlType.h"
#include "EmsRivlMain.h"
#include "EmsRpcMain.h"

INT32
TclGetAck (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetAck" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8    Message[MAX_MESSAGE_LEN];
  INT8    ErrorBuff[MAX_ERRBUFF_LEN];
  INT8    TempStr[10];
  INT32   Timeout;
  INT32   Length;
  BOOLEAN Pass;
  INT8    *Out;
  INT8    *Log;

  if (Argc > 1) {
    Timeout = atoi (Argv[1]);
  } else {
    Timeout = -1;
  }

  Timeout = -1;

  //
  // memset  (message, 0, MAX_MESSAGE_LEN);
  //
  Message[0]  = 0;
  Length      = RpcRecvMessage (Timeout, MAX_MESSAGE_LEN, Message);
  if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) /*||
      (false == Pass)*/ ) {
    sprintf (ErrorBuff, "GetAck failed!");
    goto ErrorExit;
  }
  //
  // Format of GetAck should be
  //      GetAck [timeout [Pass [Out [log]]]]
  //
  switch (Argc) {
  case 5:
    Tcl_SetVar (Interp, Argv[4], Log, TCL_GLOBAL_ONLY);

  case 4:
    Tcl_SetVar (Interp, Argv[3], Out, TCL_GLOBAL_ONLY);

  case 3:
    if (Pass == TRUE) {
      strcpy (TempStr, "true");
      Tcl_SetVar (Interp, Argv[2], TempStr, TCL_GLOBAL_ONLY);
    } else {
      strcpy (TempStr, "false");
      Tcl_SetVar (Interp, Argv[2], TempStr, TCL_GLOBAL_ONLY);
    }
    break;

  case 2:
    break;

  case 1:
    break;

  default:
    sprintf (ErrorBuff, "Contax of GetAck error");
    goto ErrorExit;
  }

  if (Pass != TRUE) {
    sprintf (ErrorBuff, "GetAck failed!");
    goto ErrorExit;
  }

  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);

  return TCL_ERROR;
}
