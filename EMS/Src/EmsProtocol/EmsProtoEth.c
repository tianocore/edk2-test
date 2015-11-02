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
  
    EmsProtoEth.c
    
Abstract:

    Implementation for functions for protocol ETHERNET

--*/

#include "EmsTypes.h"
#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsPktCreate.h"
#include "EmsUtilityString.h"
#include "EmsLogCommand.h"

STATIC
libnet_t            *
EthCreatePacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T             *
EthUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

STATIC Tcl_CmdProc  TclConfigEth;

STATIC
VOID_P
EthTclInit (
  IN Tcl_Interp *Interp
  );

UINT8               LocalEthaddr[6];
UINT8               RemoteEthaddr[6];

STATIC UINT8        EthDst[6];
STATIC UINT8        EthSrc[6];
STATIC UINT16       EthType;
STATIC PAYLOAD_T    EthPld = { NULL, 0 };

STATIC BOOLEAN      DstOk;
STATIC BOOLEAN      SrcOk;
STATIC BOOLEAN      TypeOk;
STATIC BOOLEAN      PldOk;

/* Ethernet Protocol Entry*/
PROTOCOL_ENTRY_T    EthProtocol = {
  "ETH",            /* name */
  EthCreatePacket,  /* Create packet routine */
  EthUnpackPacket,  /* Unpacket routine */
  EthTclInit        /* ETH TCL initialzation routine*/
};

FIELD_T             EthField[] = {
  /* name        type          value     Mandatory    Isset */
  {
    "Eth_dst",
    MACADDR,
    EthDst,
    FALSE,
    &DstOk
  },
  {
    "Eth_src",
    MACADDR,
    EthSrc,
    FALSE,
    &SrcOk
  },
  {
    "Eth_type",
    OCTET2,
    &EthType,
    FALSE,
    &TypeOk
  },
  {
    "Eth_payload",
    PAYLOAD,
    &EthPld,
    FALSE,
    &PldOk
  },
  {
    NULL
  }
};

STATIC
libnet_t *
EthCreatePacket (
  INT32   Argc,
  INT8    *Argv[]
  )
/*++

Routine Description:

  Create an ethernet packet

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  The pointer to the libnet

--*/
{
  libnet_t      *l;
  libnet_ptag_t Tag;
  INT32         Index;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  EMS_STATUS    Status;

  /*
 * Initialize all the local variables
 */
  for (Index = 0; EthField[Index].Name; Index++) {
    *(EthField[Index].IsOk) = FALSE;
    Status                  = GetValueByName (&EthField[Index], Argc, Argv);
    if (IsError (Status)) {
      return NULL;
    }
  }

  /*
  *  Initialize the libnet
  */
  l = libnet_init (
        LIBNET_LINK,
        /* injection type */EmsInterface,
        /* network interface */ErrBuf /* errbuf */
        );

  if (NULL == l) {
    return NULL;
  }

  Tag = libnet_build_ethernet (
          DstOk ? EthDst : RemoteEthaddr,
          /* ethernet destination */SrcOk ? EthSrc : LocalEthaddr,
          /* ethernet source */TypeOk ? EthType : ETHERTYPE_IP,
          /* protocol type */PldOk ? EthPld.Payload : NULL,
          /* payload */PldOk ? EthPld.Len : 0,
          /* payload size */l,
          /* libnet handle */0  /* libnet id */
          );
  if (-1 == Tag) {
    return NULL;
  } else {
    return l;
  }
}

STATIC
FIELD_T *
EthUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack an Ethernet packet

Arguments:

  Packet  - The packet should be unpacked
  Length  - The size of the packet

Returns:

  The pointer to the EthField

--*/
{
  ETH_HEADER  *Header;
  UINT32      PayloadLen;

  if (Length < sizeof (ETH_HEADER)) {
    return NULL;
  }

  Header = (ETH_HEADER *) Packet;
  memcpy (EthDst, Header->Dst, 6);
  memcpy (EthSrc, Header->Src, 6);
  EthType = ntohs (Header->Type);

  if (NULL != EthPld.Payload) {
    free (EthPld.Payload);
    EthPld.Payload  = NULL;
    EthPld.Len      = 0;
  }

  PayloadLen = Length - sizeof (ETH_HEADER);
  if (PayloadLen) {
    EthPld.Payload = malloc (PayloadLen);
    memcpy (EthPld.Payload, Packet + sizeof (ETH_HEADER), PayloadLen);
    EthPld.Len = PayloadLen;
  }

  return EthField;
}

VOID_P
EthTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS Ethernet related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  //
  // Create Packet related TCL commands
  //
  Tcl_CreateCommand (
    Interp,
    "LocalEther",
    TclConfigEth,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  Tcl_CreateCommand (
    Interp,
    "RemoteEther",
    TclConfigEth,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  //
  // Link Packet related TCL variables
  //
}

STATIC
INT32
TclConfigEth (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "LocalEther" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  *Arg;
  UINT8 Addr[6];
  UINT8 *Addr1;
  INT8  Buff[25];

  LogCurrentCommand (Argc, Argv);
  if (Argc > 2) {
    goto WrongArg;
  };

  if (Argc == 1) {
    if (0 == strcmp_i ((INT8 *) Argv[0], "localether")) {
      Addr1 = &LocalEthaddr[0];
    } else {
      Addr1 = &RemoteEthaddr[0];
    }

    sprintf (
      Buff,
      "%x:%x:%x:%x:%x:%x",
      Addr1[0],
      Addr1[1],
      Addr1[2],
      Addr1[3],
      Addr1[4],
      Addr1[5]
      );
    Tcl_AppendResult (Interp, Buff, (INT8 *) NULL);
    return TCL_OK;
  }

  Arg = (INT8 *) Argv[1];
  if (AsciiStringToMac (Arg, Addr) <= 0) {
    goto WrongArg;
  };

  if (0 == strcmp_i ((INT8 *) Argv[0], "localether")) {
    memcpy (LocalEthaddr, Addr, 6);
  } else {
    memcpy (RemoteEthaddr, Addr, 6);
  }

  return TCL_OK;
WrongArg:
  /* Say somethine here */
  return TCL_ERROR;
}
