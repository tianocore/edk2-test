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
  
    EmsPktDump.c
    
Abstract:

    Implementation for packet dump TCL commands

--*/

#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsPktMain.h"
#include "EmsProtocols.h"
#include "EmsLogUtility.h"
#include "EmsLogCommand.h"
#include <time.h>

#define ISPRINT(c)  (c >= ' ' && c <= '~')

STATIC Tcl_CmdProc  TclDumpPacket;

VOID_P
DumpTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet dump related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None.

--*/
{
  //
  // Create Packet related TCL commands
  //
  Tcl_CreateCommand (
    Interp,
    "DumpPacket",
    TclDumpPacket,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  //
  // Link Packet related TCL variables
  //
}

static
INT32
TclDumpPacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DumpPacket" implementation routine

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
  PACKET_T  *PacketPointer;
  INT8      Buff[100];
  INT8      AscBuff[100];
  INT8      Str[100];
  INT8      Ch;
  UINT32    Index;
  UINT32    Line;

  LogCurrentCommand (Argc, Argv);

  if (Argc == 1) {
    Tcl_AppendResult (
      Interp,
      "DumpPacket PacketName",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };
  Name          = (INT8 *) Argv[1];
  PacketPointer = EmsPacketFindByName (Name);
  if (NULL == PacketPointer) {
    Tcl_AppendResult (
      Interp,
      "EMS: DumpPacket: Packet ",
      Name,
      " does not exist.",
      (INT8 *) NULL
      );
    return TCL_OK;
  }
  //
  // Packet name, time, ...
  //
#ifdef WIN32
  sprintf (
    Buff,
    "EMS: DumpPacket\nName:%s\n Len:%d",
    PacketPointer->Name,
    PacketPointer->DataLen
    );
  RecordMessage (
    EMS_VERBOSE_LEVEL_QUIET,
    "%a",
    Buff
    );
#else
  dtime = localtime (&PacketPointer->Time.tv_sec);
  strftime (Str, sizeof (Str), "%H:%M:%S", dtime);

  sprintf (
    Buff,
    "EMS: DumpPacket\nName:%s\nTime:%s %.6ld Len:%d",
    PacketPointer->Name,
    Str,
    (PacketPointer->Time).tv_usec,
    PacketPointer->DataLen
    );
  RecordMessage (
    EMS_VERBOSE_LEVEL_QUIET,
    "%a",
    Buff
    );
#endif

  for (Line = 0; Line < PacketPointer->DataLen / 16; Line++) {
    Buff[0]     = '\0';
    AscBuff[0]  = '\0';
    for (Index = Line * 16; Index < Line * 16 + 16; Index++) {
      sprintf (Str, "%02x ", PacketPointer->Data[Index]);
      sprintf (Buff, "%s%02x ", Buff, PacketPointer->Data[Index]);
      //
      //      strcat( buff, str);
      //
      Ch = ISPRINT (PacketPointer->Data[Index]) ? PacketPointer->Data[Index] : '.';
      sprintf (AscBuff, "%s%c", AscBuff, Ch);
    }

    strcat (Buff, AscBuff);
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "%a",
      Buff
      );
  }

  Buff[0]     = '\0';
  AscBuff[0]  = '\0';
  for (Index = Line * 16; Index < PacketPointer->DataLen; Index++) {
    sprintf (Str, "%02x ", PacketPointer->Data[Index]);
    strcat (Buff, Str);
    Ch = ISPRINT (PacketPointer->Data[Index]) ? PacketPointer->Data[Index] : '.';
    sprintf (AscBuff, "%s%c", AscBuff, Ch);
  }

  for (Index = strlen (Buff); Index < 48; Index++) {
    Buff[Index] = ' ';
  }

  Buff[Index] = '\0';
  strcat (Buff, AscBuff);
  RecordMessage (
    EMS_VERBOSE_LEVEL_QUIET,
    "%a",
    Buff
    );

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}
