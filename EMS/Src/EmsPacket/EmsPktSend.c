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
