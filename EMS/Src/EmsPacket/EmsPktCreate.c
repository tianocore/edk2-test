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
  
    EmsPktCreate.c
    
Abstract:

    Implementation for packet create TCL commands

--*/

#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsPktCreate.h"
#include "EmsPktMain.h"
#include "EmsProtocols.h"
#include "EmsLogCommand.h"
#include <time.h>

STATIC Tcl_CmdProc  TclCreatePacket;
STATIC Tcl_CmdProc  TclDestroyPacket;
STATIC Tcl_CmdProc  TclDisplayPacket;

VOID_P
CreateTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet related TCL initialization.

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
    "CreatePacket",
    TclCreatePacket,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  Tcl_CreateCommand (
    Interp,
    "DestroyPacket",
    TclDestroyPacket,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  Tcl_CreateCommand (
    Interp,
    "DisplayPacket",
    TclDisplayPacket,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  //
  // Link Packet related TCL variables
  //
}

EMS_STATUS
GetValueByName (
  FIELD_T   *Field,
  INT32     Argc,
  INT8      *Argv[]
  )
/*++

Routine Description:

  Get value through name string.

Arguments:

  Field       - Field context.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  EMS_STATUS status code to indicate success or failure operation.

--*/
{
  INT32     Index;
  INT8      *Arg;
  INT32     Status;
  UINT32    Value;
  UINT8     Eth[6];
  PACKET_T  *PacketPointer;
  EMS_IPV6_ADDR Ipv6Value;

  for (Index = 0; Index < Argc; Index++) {
    Arg = Argv[Index];
    if (Arg[0] != '-') {
      continue;
    }

    if (strncmp_i (&Arg[1], Field->Name, strlen (Field->Name)) != 0) {
      continue;
    }

    if (Index + 1 == Argc) {
      return 0 - ERROR_NOVALUE; /*????*/
    }
    break;
  }

  if (Index == Argc) {
    /*
   * This field has not been configure in argumems
   */
    if (Field->Mandatory == TRUE) {
      return 0 - ERROR_LACKOFARG; /*But this field is mandatory*/
    }

    *(Field->IsOk) = FALSE;       /* This field has not been configured*/
    return NOERROR;
  }

  Arg = Argv[Index + 1];
  switch (Field->Type) {
  case OCTET1:
    Status = AsciiStringToUint32 (Arg, &Value);
    if (Status <= 0) {
      return 0 - ERROR_WRONGFORMAT;
    }

    * (UINT8 *) (Field->Value)  = (UINT8) Value;
    *(Field->IsOk)              = TRUE;
    return NOERROR;

  case OCTET2:
    Status = AsciiStringToUint32 (Arg, &Value);
    if (Status <= 0) {
      return 0 - ERROR_WRONGFORMAT;
    }

    * (UINT16 *) (Field->Value) = (UINT16) Value;
    *(Field->IsOk)              = TRUE;
    return NOERROR;

  case OCTET4:
    Status = AsciiStringToUint32 (Arg, &Value);
    if (Status <= 0) {
      return 0 - ERROR_WRONGFORMAT;
    }

    * (UINT32 *) (Field->Value) = (UINT32) Value;
    *(Field->IsOk)              = TRUE;
    return NOERROR;

  case IPADDR:
    Status = AsciiStringToIpv4 (Arg, &Value);
    if (Status <= 0) {
      return 0 - ERROR_WRONGFORMAT;
    }

    * (UINT32 *) (Field->Value) = (UINT32) Value;
    *(Field->IsOk)              = TRUE;
    return NOERROR;

  case MACADDR:
    Status = AsciiStringToMac (Arg, Eth);
    if (Status <= 0) {
      return 0 - ERROR_WRONGFORMAT;
    }

    memcpy (Field->Value, Eth, 6);
    *(Field->IsOk) = TRUE;
    return NOERROR;

  case PAYLOAD:
    //
    // Payloads is stored packet queue
    //
    PacketPointer = EmsPacketFindByName (Arg);
    if (NULL == PacketPointer) {
      return 0 - ERROR_WRONGFORMAT;
    }

    if (((PAYLOAD_T *) (Field->Value))->Payload) {
      free (((PAYLOAD_T *) (Field->Value))->Payload);
    }
    ((PAYLOAD_T *) (Field->Value))->Payload = malloc (PacketPointer->DataLen);
    memcpy (((PAYLOAD_T *) (Field->Value))->Payload, PacketPointer->Data, PacketPointer->DataLen);
    ((PAYLOAD_T *) (Field->Value))->Len = PacketPointer->DataLen;
    *(Field->IsOk)                      = TRUE;
    return NOERROR;

  case STRING:
    * (INT8 **) (Field->Value)  = _strdup (Arg);
    *(Field->IsOk)              = TRUE;
    return NOERROR;

  case IPV6ADDR:
    Status = AsciiStringToIpv6 (Arg, &Ipv6Value);
    if (Status <= 0) {
      return 0 - ERROR_WRONGFORMAT;
    }

    memcpy ((UINT8 *)(Field->Value), (UINT8 *)(&Ipv6Value), sizeof(Ipv6Value));
    *(Field->IsOk)              = TRUE;
    return NOERROR;

  default:
    return 0 - ERROR_INTERNAL;
  }
}

static
INT32
TclCreatePacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "CreatePacket" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT32             Index;

  INT8              *Arg;
  INT8              *Name;
  INT8              *Type;
  libnet_t          *l;
  PROTOCOL_ENTRY_T  *Proto;

  LogCurrentCommand (Argc, Argv);

  if (Argc < 4) {
    goto WrongArg;
  };

  //
  // The first argument is packet name
  //
  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto ErrorExit;

  }

  Type = NULL;
  for (Index = 2; Index < Argc; Index++) {
    Arg = (INT8 *) Argv[Index];
    if (strcmp (Arg, "-t") == 0) {
      if (Index + 1 < Argc) {
        Type = (INT8 *) Argv[Index + 1];
        break;
      } else {
        goto WrongArg;
      }
    }
  }

  if (NULL == Type) {
    goto WrongArg;

  }
  //
  // If there is a packet with same name, destroy it.
  //
  l = libnet_cq_find_by_label (Name);
  if (NULL != l) {
    libnet_cq_remove_by_label (Name);
    libnet_destroy (l);
  }
  //
  // Find protocol entry and create the packet
  //
  Proto = GetProtocolByName (Type);
  if (NULL == Proto) {
    Tcl_AppendResult (
      Interp,
      "Protocol ",
      Type,
      " is not supported",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (NULL == Proto->CreatePacket) {
    Tcl_AppendResult (
      Interp,
      "Have no 'CreatePacket; callback routine for Type ",
      Type,
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  l = Proto->CreatePacket (Argc, (INT8 **) Argv);

  if (NULL == l) {
    Tcl_AppendResult (
      Interp,
      "Create Packet fail!",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (libnet_cq_add (l, Name) == -1) {
    Tcl_AppendResult (Interp, l->err_buf, (INT8 *) NULL);
    goto ErrorExit;
  }

  return TCL_OK;

WrongArg:
  Tcl_AppendResult (
    Interp,
    "CreatePacket Name -t Type [Options ...]",
    (INT8 *) NULL
    );
  return TCL_ERROR;
ErrorExit:
  return TCL_ERROR;
}

static
INT32
TclDestroyPacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DestroyPacket" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT32     Index;
  INT8      *Arg;
  libnet_t  *l;
  PACKET_T  *PacketPointer;

  LogCurrentCommand (Argc, Argv);
  if (Argc < 2) {
    //
    // destroy all packets
    //
    libnet_cq_destroy ();
    EmsPacketQueueDestroy ();
    return TCL_OK;
  }

  for (Index = 1; Index < Argc; Index++) {
    Arg = (INT8 *) Argv[Index];
    l   = libnet_cq_find_by_label (Arg);
    if (l) {
      //
      // Use libnet_cq_remove_by_lable(arg) or libnet_cq_remove(l)?
      //
      libnet_cq_remove_by_label (Arg);
      libnet_destroy (l);
    }
  }

  for (Index = 1; Index < Argc; Index++) {
    Arg           = (INT8 *) Argv[Index];
    PacketPointer = EmsPacketFindByName (Arg);
    if (PacketPointer) {
      EmsPacketRemove (PacketPointer);
      EmsPacketDestroy (PacketPointer);
    }
  }

  return TCL_OK;
}

static
INT32
TclDisplayPacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DisplayPacket" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  libnet_t  *l;
  PACKET_T  *PacketPointer;
  INT8      Log[2506];

  LogCurrentCommand (Argc, Argv);

  Tcl_AppendResult (
    Interp,
    "Display all the Packet in system: \n",
    (INT8 *) NULL
    );

  for_each_context_in_cq (l) {
    Tcl_AppendResult (
      Interp,
      l->label,
      "\n",
      (INT8 *) NULL
      );
  }

  for (PacketPointer = PacketQueue; PacketPointer; PacketPointer = PacketPointer->Next) {
    EmsPacketDump (Log, PacketPointer);
    Tcl_AppendResult (
      Interp,
      Log,
      (INT8 *) NULL
      );
  }

  return TCL_OK;
}
