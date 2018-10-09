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
  
    EmsRivlExec.c
    
Abstract:

    Implementation of RIVL TCL command Exec 
    Exec: request the remote target execute an application, 

--*/

#include "EmsRivlMain.h"
#include "EmsRpcMain.h"
#include "EmsLogUtility.h"
#include "EmsEftp.h"

INT32
TclExec (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Exec" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8    ErrorBuff[MAX_ERRBUFF_LEN];
  INT8    Message[MAX_MESSAGE_LEN];
  INT32   Length;
  BOOLEAN Pass;
  INT8    *Out;
  INT8    *Log;

  if (Argc != 2) {
    sprintf (ErrorBuff, "Exec: Syntax Error!");
    goto WrongArg;
  }

  Message[0] = '\0';
  strcat (Message, "TEST_EXEC ");
  strcat (Message, (INT8 *) Argv[1]);

  Length = strlen (Message);

  RpcSendMessage (Length, Message);

  Message[0]  = 0;
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);

  if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) || (FALSE == Pass)) {
    sprintf (ErrorBuff, "EAS: Exec \"%s\" Error!", (INT8 *) Argv[1]);
    goto ErrorExit;
  }
  //
  // Should not happen
  //
  if (Log == NULL) {
    goto ErrorExit;
  }
  //
  // The Format of ACK is     _ACK_ P/F _LOG_
  //
  RecordMessage (
    EMS_VERBOSE_LEVEL_DEFAULT,
    "Execute <%a>:\n%a%a\n",
    (INT8 *) Argv[1],
    Out,
    strstr (Log,
    "Status")
    );

  sprintf (ErrorBuff, "%s", strstr (Log, "Status"));
  Tcl_AppendResult (Interp, ErrorBuff, NULL);
  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "Exec:  Exec TargetName CmdLine");

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclGetFile (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetFile" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8    ErrorBuff[MAX_ERRBUFF_LEN];
  INT8    Message[MAX_MESSAGE_LEN];
  INT32   Length;
  BOOLEAN Pass;
  INT8    *Out;
  INT8    *Log;

  if (Argc != 2) {
    sprintf (ErrorBuff, "Exec: Syntax Error!");
    goto WrongArg;
  }

  Message[0] = '\0';
  strcat (Message, "GET_FILE ");
  strcat (Message, (INT8 *) Argv[1]);

  Length = strlen (Message);

  RpcSendMessage (Length, Message);

  Message[0]  = 0;
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);

  if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) || (FALSE == Pass)) {
    sprintf (ErrorBuff, "EAS: Exec \"%s\" Error!", (INT8 *) Argv[1]);
    goto ErrorExit;
  }
  //
  // Should not happen
  //
  if (Log == NULL) {
    goto ErrorExit;
  }
  //
  // The Format of ACK is     _ACK_ P/F _LOG_
  //
  RecordMessage (
    EMS_VERBOSE_LEVEL_DEFAULT,
    "Execute <%a>:\n%a%a\n",
    (INT8 *) Argv[1],
    Out,
    strstr (Log,
    "Status")
    );

  sprintf (ErrorBuff, "%s", strstr (Log, "Status"));
  Tcl_AppendResult (Interp, ErrorBuff, NULL);
  return TCL_OK;
WrongArg:
  sprintf (ErrorBuff, "Exec:  Exec TargetName CmdLine");
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclPutFile (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "PutFile" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8           ErrorBuff[MAX_ERRBUFF_LEN];
  INT8           Message[MAX_MESSAGE_LEN];
  INT32          Length;
  BOOLEAN        Pass;
  INT8           *Out;
  INT8           *Log;
  EmsEftpRequest *Req = NULL;

  if (Argc != 2) {
    sprintf (ErrorBuff, "Exec: Syntax Error!");
    goto WrongArg;
  }

  Message[0] = '\0';
  strcat (Message, "PUT_FILE ");
  strcat (Message, (INT8 *) Argv[1]);

  Req = EmsEftpRegisterRequest();

  Length = strlen (Message);

  RpcSendMessage (Length, Message);

  Message[0]  = 0;
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);

  if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) || (FALSE == Pass)) {
    sprintf (ErrorBuff, "EAS: Exec \"%s\" Error!", (INT8 *) Argv[1]);
    goto ErrorExit;
  }
  //
  // Should not happen
  //
  if (Log == NULL) {
    goto ErrorExit;
  }
  //
  // The Format of ACK is     _ACK_ P/F _LOG_
  //
  RecordMessage (
    EMS_VERBOSE_LEVEL_DEFAULT,
    "Execute <%a>:\n%a%a\n",
    (INT8 *) Argv[1],
    Out,
    strstr (Log,
    "Status")
    );

  EmsEftpRequestWait(Req);

  sprintf (ErrorBuff, "%s", strstr (Log, "Status"));
  Tcl_AppendResult (Interp, ErrorBuff, NULL);
  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "Exec:  Exec TargetName CmdLine");

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
