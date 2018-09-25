/** @file
 
  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsVtcpMain.c
    
Abstract:

    

--*/

#include "EmsVtcpTcb.h"

#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsPktCreate.h"
#include "EmsProtocols.h"
#include "EmsUtilityString.h"
#include "EmsLogCommand.h"
#include "EmsVtcpNamedList.h"

#include "EmsLogUtility.h"

#include "EmsThread.h"

NL_LIST             VTcbList = NULL;

STATIC Tcl_CmdProc  TclVTcpCreateTcb;
STATIC Tcl_CmdProc  TclVTcpDestroyTcb;
STATIC Tcl_CmdProc  TclVTcpUpdateSendBuffer;
STATIC Tcl_CmdProc  TclVTcpSendPacket;
STATIC Tcl_CmdProc  TclVTcpRecvPacket;
STATIC Tcl_CmdProc  TclVTcpBuildOption;
STATIC Tcl_CmdProc  TclVTcpGetChecksum;

STATIC TCL_CMD_TBL  TclCmd[] = {
  {
    "CreateTcb",
    TclVTcpCreateTcb
  },
  {
    "DestroyTcb",
    TclVTcpDestroyTcb
  },
  {
    "SendTcpPacket",
    TclVTcpSendPacket
  },
  {
    "UpdateTcpSendBuffer",
    TclVTcpUpdateSendBuffer
  },
  {
    "ReceiveTcpPacket",
    TclVTcpRecvPacket
  },
  {
    "BuildTcpOptions",
    TclVTcpBuildOption
  },
  {
    "GetTcpChecksum",
    TclVTcpGetChecksum
  },
  {
    NULL,
    NULL
  }
};

VOID_P
VTcpTclInit (
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS TCP related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  INT32 Index;
  //
  // Create related TCL commands
  //
  for (Index = 0; TclCmd[Index].Cmd; Index++) {
    Tcl_CreateCommand (
      Interp,
      TclCmd[Index].Cmd,
      TclCmd[Index].Proc,
      (ClientData) NULL,
      (Tcl_CmdDeleteProc *) NULL
      );
  }
}

STATIC
INT32
TclVTcpCreateTcb (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "CreateTcb" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  CONST INT8    *Name;
  UINT32  LocalIp;
  UINT32  LocalPort;
  UINT32  RemoteIp;
  UINT32  RemotePort;
  VTCB    *Tcb;

  LogCurrentCommand (Argc, Argv);

  if (Argc != 6) {
    Tcl_AppendResult (
      Interp,
      "CreateTcb: CreateTcb <Name> <LocalIp> <LocalPort> <RemoteIp> <RemotePort>",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };
  Name = Argv[1];

  if (AsciiStringToIpv4 ((INT8 *) Argv[2], &LocalIp) <= 0) {
    Tcl_AppendResult (
      Interp,
      "CreateTcb: LocalIp is invalid",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (strlen (Argv[3]) != AsciiStringToUint32 ((INT8 *) Argv[3], &LocalPort)) {
    Tcl_AppendResult (
      Interp,
      "CreateTcb: LocalPort is invalid",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (AsciiStringToIpv4 ((INT8 *) Argv[4], &RemoteIp) <= 0) {
    Tcl_AppendResult (
      Interp,
      "CreateTcb: RemoteIp is invalid",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (strlen (Argv[5]) != AsciiStringToUint32 ((INT8 *) Argv[5], &RemotePort)) {
    Tcl_AppendResult (
      Interp,
      "CreateTcb: RemotePort is invalid",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  Tcb = EmsVTcbCreate (LocalIp, LocalPort, RemoteIp, RemotePort);
  if (NULL == Tcb) {
    Tcl_AppendResult (
      Interp,
      "CreateTcb: Fail to allocate memory",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (EmsVTcbInitSendBuff (Tcb)) {
    free (Tcb);
    Tcl_AppendResult (
      Interp,
      "CreateTcb: Fail to initialize send Buff",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  EmsNlAddGoods (Name, (VOID_P *) Tcb, &VTcbList);
  EmsVTcbCreateTcls (Interp, Name, Tcb);

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

VOID
EmsVTcpDestroyAllTcb(
  VOID
  )
/*++

Routine Description:

  Destroy all virtual TCP

Arguments:

  None

Returns:

  None

--*/
{
  VTCB    *Tcb;
  NL_NODE *Node;

  while(VTcbList)
  {
    Node     = VTcbList;
    VTcbList = VTcbList->Next;

    Tcb      = (VTCB *)(Node->Goods);
    EmsVTcbDestroyTcls(EmsThreadSelf()->Interp, Node->Name);
    libnet_cq_remove(Tcb->SendBuff);
    libnet_destroy(Tcb->SendBuff);
    if(Tcb->Capturer->Packet)
    {
      PacketFreePacket(Tcb->Capturer->Packet);
      Tcb->Capturer->Packet = NULL;
    }
    pcap_close(Tcb->Capturer);
    EmsNlFreeNode(Node);
    VTcbList = NULL;
  }
}

STATIC
INT32
TclVTcpDestroyTcb (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DestroyTcb" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  VTCB    *Tcb;
  NL_NODE *Node;
  NL_NODE *Node1;

  LogCurrentCommand (Argc, Argv);

  if (Argc > 2) {
    Tcl_AppendResult (
      Interp,
      "DestroyTcb: DestroyTcb [Name]",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  if (Argc == 1) {

    Node = VTcbList;
    while (Node) {
      Node1 = Node;
      Node  = Node->Next;

      Tcb   = (VTCB *) (Node1->Goods);

      EmsVTcbDestroyTcls (Interp, Node1->Name);
      libnet_cq_remove(Tcb->SendBuff);
      libnet_destroy (Tcb->SendBuff);
      if (Tcb->Capturer->Packet) {
        PacketFreePacket (Tcb->Capturer->Packet);
        Tcb->Capturer->Packet = NULL;
      }

      pcap_close (Tcb->Capturer);

      EmsNlFreeNode (Node1);
    }

    VTcbList = NULL;

  } else {
    Node = EmsNlRemoveNodeByName (Argv[1], &VTcbList);
    if (NULL == Node) {
      Tcl_AppendResult (
        Interp,
        "DestroyTcb: No such TCB",
        (INT8 *) NULL
        );
      goto ErrorExit;
    }

    EmsVTcbDestroyTcls (Interp, Argv[1]);
    Tcb = (VTCB *) (Node->Goods);
    libnet_cq_remove(Tcb->SendBuff);
    libnet_destroy (Tcb->SendBuff);
    if (Tcb->Capturer->Packet) {
      PacketFreePacket (Tcb->Capturer->Packet);
      Tcb->Capturer->Packet = NULL;
    }

    pcap_close (Tcb->Capturer);

    EmsNlFreeNode (Node);
  }

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclVTcpSendPacket (
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
  VTCB  *Tcb;

  LogCurrentCommand (Argc, Argv);

  if (Argc != 2) {
    Tcl_AppendResult (
      Interp,
      "SendTcpPacket: SendTcpPacket [Name]",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  Tcb = EmsNlFindGoodsByName (Argv[1], &VTcbList);
  if (NULL == Tcb) {
    Tcl_AppendResult (
      Interp,
      "SendTcpPacket: No such TCB",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (EmsVTcbSend (Tcb) < 0) {
    Tcl_AppendResult (
      Interp,
      "SendTcpPacket: Fail to send",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclVTcpUpdateSendBuffer (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "UpdateTcpSendBuffer" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  CONST INT8      *Name;
  VTCB      *Tcb;
  UINT32    Index;
  UINT32    Seq;
  UINT32    Ack;
  UINT32    CheckSum;
  UINT32    Control;
  UINT32    Win;
  UINT32    Urg;
  UINT8     *Options;
  UINT32    OptionsLen;
  UINT8     *Payload;
  UINT32    PayloadLen;
  PACKET_T  *PacketPointer;

  CheckSum  = 0;
  Control   = 0;
  Urg       = 0;
  Options   = NULL;
  OptionsLen = 0;
  Payload   = NULL;
  PayloadLen = 0;

  LogCurrentCommand (Argc, Argv);

  if (Argc < 2) {
    goto arg_wrong;
  }

  Name  = Argv[1];
  Tcb   = EmsNlFindGoodsByName (Name, &VTcbList);
  if (NULL == Tcb) {
    Tcl_AppendResult (
      Interp,
      "UpdateTcpSendBuffer: No such TCB",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  Seq = Tcb->LocalNextSeq + Tcb->LocalIsn;
  Ack = Tcb->RemoteNextSeq + Tcb->RemoteIsn;
  Win = Tcb->LocalWin;

  for (Index = 2; Index < (UINT32) Argc; Index++) {
    if ('-' != Argv[Index][0]) {
      goto arg_wrong;
    }

    switch (Argv[Index][1]) {
    case 's':
    case 'S':
      Index++;
      AsciiStringToUint32 (Argv[Index], &Seq);
      break;

    case 'a':
    case 'A':
      Index++;
      AsciiStringToUint32 (Argv[Index], &Ack);
      break;

    case 'c':
    case 'C':
      Index++;
      AsciiStringToUint32 (Argv[Index], &Control);
      break;

    case 'w':
    case 'W':
      Index++;
      AsciiStringToUint32 (Argv[Index], &Win);
      break;

    case 'u':
    case 'U':
      Index++;
      AsciiStringToUint32 (Argv[Index], &Urg);
      break;

    case 'o':
    case 'O':
      Index++;
      PacketPointer = EmsPacketFindByName (Argv[Index]);
      if (NULL == PacketPointer) {
        Tcl_AppendResult (
          Interp,
          "UpdateTcpSendBuffer: No such Payload for option",
          (INT8 *) NULL
          );
      }

      Options   = PacketPointer->Data;
      OptionsLen = PacketPointer->DataLen;
      break;

    case 'p':
    case 'P':
      Index++;
      PacketPointer = EmsPacketFindByName (Argv[Index]);
      if (NULL == PacketPointer) {
        Tcl_AppendResult (
          Interp,
          "UpdateTcpSendBuffer: No such Payload for option",
          (INT8 *) NULL
          );
      }

      Payload   = PacketPointer->Data;
      PayloadLen = PacketPointer->DataLen;
      break;

    case 'k':
    case 'K':
      Index++;
      AsciiStringToUint32 (Argv[Index], &CheckSum);
      break;

    default:
      goto arg_wrong;
    }
  }

  if (EmsVTcbUpdateSendBuff (
        Tcb,
        Seq,
        Ack,
        (UINT16) CheckSum,
        (UINT8) Control,
        (UINT16) Win,
        (UINT16) Urg,
        Options,
        OptionsLen,
        Payload,
        PayloadLen
        ) < 0) {
    Tcl_AppendResult (
      Interp,
      "UpdateTcpSendBuffer: Fail to update send Buffer",
      (INT8 *) NULL
      );
  };

  if (Control & TH_ACK) {
    if (Ack > Tcb->RemoteIsn) {
      Tcb->LocalAckedSeq = Ack - Tcb->RemoteIsn;
    }

    Tcb->LocalMaxAckedSeq = MAX (Tcb->LocalAckedSeq, Tcb->LocalMaxAckedSeq);
  }

  Tcb->LocalNextSeq = Seq - Tcb->LocalIsn + ((Control & TH_SYN) ? 1 : 0) + ((Control & TH_FIN) ? 1 : 0) + PayloadLen;
  Tcb->LocalMaxSeq  = MAX (Tcb->LocalMaxSeq, Tcb->LocalNextSeq);
  return TCL_OK;
arg_wrong:
  Tcl_AppendResult (
    Interp,
    "UpdateTcpSendBuffer: UpdateTcpSendBuffer <Name> [Options]",
    "  Options: ",
    "    -s/S  Seq ",
    "    -a/A  Ack ",
    "    -c/C  Control ",
    "    -w/W  Win ",
    "    -u/U  Urg",
    "    -o/O  Options ",
    "    -PacketPointer/P  Payload",
    "    -k/K  CheckSum",
    (INT8 *) NULL
    );
ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclVTcpRecvPacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "ReceiveTcpPacket" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  CONST INT8    *Name;
  VTCB    *Tcb;
  UINT32  Timeout;

  LogCurrentCommand (Argc, Argv);

  if (Argc != 3) {
    Tcl_AppendResult (
      Interp,
      "ReceiveTcpPacket: ReceiveTcpPacket <Name> <Timeout>",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  Name  = Argv[1];
  Tcb   = EmsNlFindGoodsByName (Name, &VTcbList);
  if (NULL == Tcb) {
    Tcl_AppendResult (
      Interp,
      "ReceiveTcpPacket: No such TCB",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (strlen (Argv[2]) != AsciiStringToUint32 ((INT8 *) Argv[2], &Timeout)) {
    Tcl_AppendResult (
      Interp,
      "ReceiveTcpPacket: Timeout is invalid",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (EmsVTcbCapture (Timeout, Tcb) < 0) {
    Tcl_AppendResult (
      Interp,
      "ReceiveTcpPacket: Fail to receive TCP Packet",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (Tcb->Received) {
    EmsVTcbParsePacket (Tcb);
    switch (Tcb->RemoteError) {

    case OPTION_PADDING_ERROR:
      RecordAssertion (
        2,
        GenericGuid,
        "TCB -OPTION PARSE \n",
        "LOG:OPTION NOT PADDING"
        );
      break;

    case OPTION_LEN_ERROR:
      RecordAssertion (
        2,
        GenericGuid,
        "TCB -OPTION PARSE \n",
        "LOG:Option Length is no 32 bit boundary "
        );

    }

    Tcb->RemoteError = EmsVTcbDoChecksum (Tcb);
    Tcl_AppendResult (
      Interp,
      "1",
      (INT8 *) NULL
      );
  } else {
    Tcl_AppendResult (
      Interp,
      "0",
      (INT8 *) NULL
      );
  }

  return TCL_OK;
ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclVTcpBuildOption (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "BuildOption" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  CONST INT8    *Name;
  UINT32  Index;
  UINT32  mss;
  UINT8   Options[MAX_OPTION_LEN];
  UINT32  position;
  UINT32  Length;
  UINT8   *Data;

  position  = 0;
  Length    = 0;

  LogCurrentCommand (Argc, Argv);

  if (Argc <= 2) {
    goto arg_wrong;
  }

  Name = Argv[1];

  for (Index = 2; Index < (UINT32) Argc; Index++) {
    if ('-' != Argv[Index][0]) {
      goto arg_wrong;
    }

    switch (Argv[Index][1]) {
    case 'm':
    case 'M':
      Index++;
      AsciiStringToUint32 (Argv[Index], &mss);
      Options[position++] = TCP_OPTION_MSS;
      Options[position++] = MSS_OPTION_LEN;
      Options[position++] = (UINT8) (mss >> 8);
      Options[position++] = (UINT8) (mss & 0xFF);
      break;

    case 'l':
    case 'L':
      Index++;
      AsciiStringToUint32 (Argv[Index], &Length);
      break;

    default:
      goto arg_wrong;
    }
  }

  Length = MAX (position, Length);
  if (0 != Length % 4) {
    Length = ((Length >> 2) + 1) << 2;
  }

  Data = calloc (sizeof (UINT8), Length);
  memcpy (Data, Options, position);
  for (Index = position; Index < Length; Index++) {
    Options[Index] = 0x00;
  }

  EmsPacketCreateAdd (Name, Data, Length);

  return TCL_OK;
arg_wrong:
  Tcl_AppendResult (
    Interp,
    "BuildTcpOption: BuildTcpOption <Name> [Options]",
    "  Options: ",
    "    -l/L  Options Length ",
    "    -m/M  MSS ",
    (INT8 *) NULL
    );
  return TCL_ERROR;
}

STATIC
INT32
TclVTcpGetChecksum (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetTcpChecksum" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{

  UINT16          CheckSum;
  CONST INT8  *Name;
  INT8            *Arg;
  PAYLOAD_T       TcpPayload;
  UINT8           *Data;
  PACKET_T        *PacketPointer;
  INT32           Len;
  struct timeval  Time;

  LogCurrentCommand (Argc, Argv);
  if (Argc <= 2) {
    goto arg_wrong;
  }

  Name          = Argv[1];

  Arg           = (INT8 *) Argv[2];
  PacketPointer = EmsPacketFindByName (Arg);
  if (NULL == PacketPointer) {
    return 0 - ERROR_WRONGFORMAT;
  }

  TcpPayload.Payload = (UINT8 *) malloc (PacketPointer->DataLen);
  memcpy (TcpPayload.Payload, PacketPointer->Data, PacketPointer->DataLen);
  TcpPayload.Len  = PacketPointer->DataLen;

  CheckSum        = EmsVTcbInChecksum ((UINT16 *) (TcpPayload.Payload), PacketPointer->DataLen);

  Data            = (UINT8 *) malloc (sizeof (UINT16));
  memcpy ((UINT8 *) Data, (UINT8 *) &CheckSum, sizeof (UINT16));
  Len           = sizeof (UINT16);

  PacketPointer = EmsPacketFindByName (Arg);
  if (PacketPointer) {
    EmsPacketRemove (PacketPointer);
    EmsPacketDestroy (PacketPointer);
  }

  PacketPointer = EmsPacketCreate (Name, Data, Len, &Time);
  EmsPacketAdd (PacketPointer);
  return TCL_OK;
arg_wrong:
  Tcl_AppendResult (
    Interp,
    "GetTcpChecksum: GetTcpChecksum <Name>  <Payload Name>",
    "  Name  : the CheckSum Value will be stroe here ",
    "  Payload Name   : the Payload you create before ",
    (INT8 *) NULL
    );
  return TCL_ERROR;
}
