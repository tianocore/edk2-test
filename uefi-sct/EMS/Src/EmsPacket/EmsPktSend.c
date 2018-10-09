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
  
    EmsPktSend.c
    
Abstract:

    

--*/

#include "EmsTclInit.h"
#include "EmsNet.h"
#include "EmsPktSend.h"
#include "EmsUtilityString.h"
#include "EmsLogCommand.h"

STATIC Tcl_CmdProc  TclSendPacket;

VOID_P
SendTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet sending related TCL initialization routine.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  //
  // Create TCL commands here
  //
  Tcl_CreateCommand (
    Interp,
    "SendPacket",
    TclSendPacket,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

}

STATIC
INT32
TclSendPacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "SendPacket" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8      *Name;
  libnet_t  *l;
  INT32     Repeat;
  INT32     Count;
  INT32     Index;
  INT8      Result[100];

  LogCurrentCommand (Argc, Argv);
  //
  // sendpacket packetname
  //
  if ((Argc != 2) && (Argc != 4)) {
    goto FormatWrong;
  }

  Repeat  = 1;

  Name    = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto FormatWrong;
  }

  if (4 == Argc) {
    if (0 != strcmp_i ((INT8 *) Argv[2], "-c")) {
      goto FormatWrong;
    }

    if ((AsciiStringToUint32 ((INT8 *) Argv[3], &Repeat) <= 0) || (0 == Repeat)) {
      goto FormatWrong;
    }
  }

  l = libnet_cq_find_by_label (Name);
  if (NULL == l) {
    goto NoSuchPacket;
  }

  Count = 0;
  for (Index = 0; Index < Repeat; Index++) {
    if (-1 == libnet_write (l)) {
      continue;
    };
    Count++;
  }

  sprintf (Result, "%d", Count);
  //
  //  Tcl_AppendResult(interp, result, (char *) NULL);
  //
  return TCL_OK;

FormatWrong:
  //
  //  Tcl_AppendResult(interp, "SendPacket: SendPacket packetname [-c repeat] \n", (char *) NULL);
  //
  return TCL_ERROR;

NoSuchPacket:
  //
  //  Tcl_AppendResult(interp, "SendPacket: The specified packet not found \n", (char *) NULL);
  //
  return TCL_ERROR;
}
