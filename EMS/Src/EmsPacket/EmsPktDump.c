/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
