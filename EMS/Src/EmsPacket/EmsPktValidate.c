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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsPktValidate.c
    
Abstract:

    Implementation for packet validate TCL commands

--*/

#include "EmsPktValidate.h"
#include "EmsTypes.h"
#include "EmsProtocols.h"
#include "EmsPktPattern.h"
#include "EmsPktMain.h"
#include "EmsUtilityString.h"
#include "EmsLogUtility.h"
#include "EmsLogCommand.h"

STATIC Tcl_CmdProc  TclValidatePacket;

INT8                *ValidateResult;

VOID_P
ValidateTclInit (
  IN  Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet validation related TCL command initialization routine

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  //
  // Create Packet validation related TCL commands
  //
  Tcl_CreateCommand (
    Interp,
    "ValidatePacket",
    TclValidatePacket,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  //
  // Link Packet related TCL variables
  //
  Tcl_LinkVar (Interp, "EMS_RESULT", (INT8 *) &ValidateResult, TCL_LINK_STRING);
}

STATIC
INT32
TclValidatePacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "ValidatePacket" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  UINT32            Index;
  INT8              *Arg;
  INT8              *Name;
  INT8              *Type;
  INT8              *Pattern;
  PROTOCOL_ENTRY_T  *Protocol;
  PACKET_T          *Packet;
  FIELD_T           *Unpack;
  BOOLEAN           Result;
  UINT8             Log[4096];

  LogCurrentCommand (Argc, Argv);

  ValidateResult = "False";
  if (Argc != 5) {
    goto ErrorExit;
  };

  //
  // The first argument is packet name
  //
  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto ErrorExit;

  }

  Type = NULL;

  for (Index = 2; Index < (UINT32) Argc; Index++) {
    Arg = (INT8 *) Argv[Index];
    if (strcmp_i (Arg, "-t") == 0) {
      if (Index + 1 < (UINT32) Argc) {
        Type = (INT8 *) Argv[Index + 1];
        Index++;
      } else {
        goto ErrorExit;
      }
    } else {
      Pattern = Arg;
    }
  }

  if (NULL == Type) {
    goto ErrorExit;

  }

  Packet = EmsPacketFindByName (Name);

  if (NULL == Packet) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "Validatepacket: Cannot find Packet %a. %a:%d",
      Name,
      __FILE__,
      __LINE__
      );
    return TCL_OK;
  }
  //
  // Find protocol entry and unpack the packet
  //
  Protocol = GetProtocolByName (Type);
  if (NULL == Protocol) {
    Tcl_AppendResult (
      Interp,
      "The Protocol ",
      Type,
      " is not supported!",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }

  Unpack = Protocol->UnpackPacket (Packet->Data, Packet->DataLen);

  //
  // validate this packet
  //
  Result = Validate (Pattern, Unpack);

  if (TRUE == Result) {
    ValidateResult = "TRUE";
    EmsFieldDump (Log, Unpack);
    RecordMessage (EMS_VERBOSE_LEVEL_NOISY, "Packet %a : %a", Name, Log);
    Tcl_AppendResult (
      Interp,
      "0",
      (INT8 *) NULL
      );
  } else if (FALSE == Result) {
    EmsFieldDump (Log, Unpack);
    RecordMessage (EMS_VERBOSE_LEVEL_MINIMAL, "Packet %a : %a", Name, Log);
    ValidateResult = "FALSE";
    Tcl_AppendResult (
      Interp,
      "1",
      (INT8 *) NULL
      );
  } else {
    goto ErrorExit;
  }

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}
