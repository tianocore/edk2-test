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
  
    EmsPktCapture.c
    
Abstract:

    

--*/

#include <EmsNet.h>

#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsPktCapture.h"
#include "EmsPktMain.h"
#include "EmsLogUtility.h"
#include "EmsLogCommand.h"
#include "EmsPktCcb.h"
#include "EmsThread.h"

NL_LIST             CcbList = NULL;

STATIC Tcl_CmdProc  TclCapturePacket;
STATIC Tcl_CmdProc  TclSetFilter;
STATIC Tcl_CmdProc  TclStartCapture;
STATIC Tcl_CmdProc  TclEndCapture;
STATIC Tcl_CmdProc  TclReceiveCcbPacket;

STATIC INT8         EmsFilter[MAX_FILTER_LEN];
STATIC CAP_INFO     *Info = NULL;
extern INT8         *EmsInterface;

STATIC
VOID_P
GotOnePacket (
  IN u_char                   *UserStr,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  );

INT32
ThreadCapture (
  IN     UINT32 Timeout
  )
/*++

Routine Description:

  Thread to capture packet continuously.

Arguments:

  Timeout - Timeout value used in pcap API.

Returns:

  0  - Success.
  -1 - Failure.

--*/
{
  INT8                ErrBuff[PCAP_ERRBUF_SIZE * 2];
  pcap_t              *Des;
  struct bpf_program  Bp;
  INT8                *TempFilter;
  INT32               Index;
  INT32               Res;
  UINT32              DueTime;
  Index = 0;

  /* Open the device */
  if ((
        Des = pcap_open_live (
                    EmsInterface,         // name of the device
                    65536,                // portion of the packet to capture
                    1,                    // promiscuous mode
                    10,                    // read timeout
                    ErrBuff               // error buffer
                    )) == NULL) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "CapturePacket: Cannot open network device to capture Packet - %a %a:%d",
      ErrBuff,
      __FILE__,
      __LINE__
      );
    return -1;
  }

  if (0 == strcmp_i (EmsFilter, " ALL")) {
    TempFilter = NULL;
  } else {
    TempFilter = EmsFilter;
  }

  if (-1 == pcap_compile (Des, &Bp, TempFilter, 0, 0xFFFFFF)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "CapturePacket: Cannot compile the Packet Filter - %a:%d",
      __FILE__,
      __LINE__
      );
    goto ErrorExit;
  }

  if (-1 == pcap_setfilter (Des, &Bp)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "CapturePacket: Cannot set Packet Filter - %a:%d",
      __FILE__,
      __LINE__
      );
    goto ErrorExit;
  }

  DueTime = GetTickCount ();
  DueTime = DueTime + Timeout * 1000;
  while (1) {
    //
    // bugbug
    //
    // Tcl_DoOneEvent(TCL_TIMER_EVEMS);
    //
    Res = pcap_dispatch (Des, 1, GotOnePacket, NULL);
    if (1 == Res) {
      break;
    }

    if (GetTickCount () >= DueTime) {
      break;
    }

    Tcl_Sleep (1);
  }
  //
  //  res = pcap_next_ex( des, &header, &pkt_data);
  //
  if (Des->Packet) {
    PacketFreePacket (Des->Packet);
    Des->Packet = NULL;
  }

  pcap_close (Des);
  WSACleanup ();
  return 0;
ErrorExit:
  return -1;
}

VOID_P
GotOnePacket (
  IN u_char                   *UserStr,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  )
/*++

Routine Description:

  Callback function to handle captured packet.

Arguments:

  UserStr - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  None.

--*/
{
  if (Info) {
    Info->Packet = malloc (PktHdr->len);
    memcpy (Info->Packet, Packet, PktHdr->len);
    Info->Len = PktHdr->len;
    memcpy (&(Info->Time), &(PktHdr->ts), sizeof (struct timeval));
    Info->GotOne = TRUE;
  }
}

VOID_P
CaptureTclInit (
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet capture related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None.

--*/
{
  //
  // Create packet capture related TCL commands
  //
  Tcl_CreateCommand (
    Interp,
    "CapturePacket",
    TclCapturePacket,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "SetFilter",
    TclSetFilter,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "StartCapture",
    TclStartCapture,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "ReceiveCcbPacket",
    TclReceiveCcbPacket,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "EndCapture",
    TclEndCapture,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
}

STATIC
INT32
TclCapturePacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "CapturePacket" implementation routine

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
  UINT32    Timeout;
  PACKET_T  *PacketPointer;
  INT8      ErrBuff[1000];
  UINT32    Count;

  Count = 0;

  LogCurrentCommand (Argc, Argv);
  //
  // Parse argument
  //
  if (Argc < 4) {
    goto ErrorExit;
  }

  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto arg_wrong;
  }

  if (0 != strcmp_i ((INT8 *) Argv[2], "-t")) {
    goto arg_wrong;
  }

  if (AsciiStringToUint32 ((INT8 *) Argv[3], &Timeout) <= 0) {
    goto arg_wrong;
  }
  //
  //  if (0 == timeout) goto arg_wrong;
  //
  Info = (CAP_INFO *) calloc (sizeof (CAP_INFO), 1);

  if (NULL == Info) {
    sprintf (ErrBuff, "CapturePacket: Fail to allocate memory.");
    goto ErrorExit;
  }

  if (-1 == ThreadCapture (Timeout)) {
    sprintf (ErrBuff, "CapturePacket: Filter error.");
    goto ErrorExit;
  };

  if (Info->GotOne == TRUE) {
    PacketPointer = EmsPacketFindByName (Name);
    if (PacketPointer) {
      EmsPacketRemove (PacketPointer);
      EmsPacketDestroy (PacketPointer);
    }

    PacketPointer = EmsPacketCreate (Name, Info->Packet, Info->Len, &(Info->Time));
    EmsPacketAdd (PacketPointer);
    Count = 1;
  } else {
    Count = 0;
  }

  if (Info) {
    if (Info->Packet) {
      free (Info->Packet);
    }

    free (Info);
    Info = NULL;
  }

  sprintf (ErrBuff, "%d", Count);
  Tcl_AppendResult (Interp, ErrBuff, (INT8 *) NULL);
  return TCL_OK;
ErrorExit:
  if (Info) {
    if (Info->Packet) {
      free (Info->Packet);
    }

    free (Info);
    Info = NULL;
  }

  Tcl_AppendResult (Interp, ErrBuff, (INT8 *) NULL);
  return TCL_ERROR;
arg_wrong:
  if (Info) {
    if (Info->Packet) {
      free (Info->Packet);
    }

    free (Info);
    Info = NULL;
  }

  Tcl_AppendResult (Interp, "CapturePacket: CapturePacket Name -t Timeout\n", (INT8 *) NULL);
  return TCL_ERROR;
}

static
INT32
TclSetFilter (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "SetFilter" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT32 Index;
  LogCurrentCommand (Argc, Argv);
  if (Argc == 1) {
    Tcl_AppendResult (
      Interp,
      "Current Filter is ",
      EmsFilter,
      (INT8 *) NULL
      );
    return TCL_OK;
  }

  EmsFilter[0] = '\0';

  for (Index = 1; Index < Argc; Index++) {
    strcat (EmsFilter, " ");
    strcat (EmsFilter, Argv[Index]);
  }

  return TCL_OK;
}

STATIC
VOID_P
CcbGotPacket (
  IN u_char                   *User,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  )
/*++

Routine Description:

  Callback function used to handle CCB (Capture Control Block) packet.

Arguments:

  User    - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  None.

--*/
{
  CCB *Ccb;

  Ccb = (CCB *) User;
  if (Ccb) {
    Ccb->ReceiveBuff = malloc (PktHdr->len);
    memcpy (Ccb->ReceiveBuff, Packet, PktHdr->len);
    Ccb->ReceiveLen = PktHdr->len;
    Ccb->Received   = 1;
    memcpy (&(Ccb->Time), &(PktHdr->ts), sizeof (struct timeval));
  }
}

INT32
EmsCcbCapture (
  IN UINT32 Timeout,
  IN CCB    *Ccb
  )
/*++

Routine Description:

  One specified process be responsible for capturing packet

Arguments:

  Timeout - Timeout value for packet capturing.
  Ccb     - CCB context.

Returns:

  0       - Successfully.

--*/
{
  INT32   Res;
  UINT32  DueTime;

  Ccb->Received = 0;

  DueTime       = GetTickCount ();
  DueTime       = DueTime + Timeout * 1000;
  while (1) {
    //
    // bugbug
    // There is one specified process be responsible for capturing packet,
    // which is different from other packets' capture. So the calling of this
    // function may cause packet capture blocking.
    //
    // Tcl_DoOneEvent(TCL_TIMER_EVEMS);
    //
    Res = pcap_dispatch (Ccb->Capturer, 1, CcbGotPacket, (UINT8 *) Ccb);
    if (1 == Res) {
      break;
    }

    if (GetTickCount () >= DueTime) {
      break;
    }

    Tcl_Sleep (1);
  }

  return 0;
}

STATIC
INT32
TclStartCapture (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "StartCapture" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  CONST INT8     *Name;
  CCB                 *Ccb;
  //
  //  HANDLE handle;
  //
  INT8                ErrBuff[1000];
  INT8                *TempFilter;
  struct bpf_program  Bp;
  INT32               Index;

  Index = 0;

  LogCurrentCommand (Argc, Argv);
  //
  // Parse argument
  //
  if (Argc < 3) {
    Tcl_AppendResult (
      Interp,
      "StartCapture: StartCapture <Name> <Filter>",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };
  Name  = Argv[1];

  Ccb   = malloc (sizeof (CCB));
  if (NULL == Ccb) {
    sprintf (ErrBuff, "StartCapture: Fail to allocate memory.");
    Tcl_AppendResult (Interp, ErrBuff, (INT8 *) NULL);
    goto ErrorExit;
  }

  Ccb->CaptureFilter[0] = '\0';
  for (Index = 2; Index < Argc; Index++) {
    strcat (Ccb->CaptureFilter, " ");
    strcat (Ccb->CaptureFilter, Argv[Index]);
  }

  Ccb->ReceiveBuff  = NULL;
  Ccb->ReceiveLen   = 0;
  Ccb->Received     = 0;

  /* Open the capture device */
  if ((
        Ccb->Capturer = pcap_open_live (
                    EmsInterface,         // name of the device
                    65536,                // portion of the packet to capture
                    1,                    // promiscuous mode
                    1,                    // read timeout
                    ErrBuff               // error buffer
                    )) == NULL) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "StartCapture: Cannot open network device to capture Packet - %a %a:%d",
      ErrBuff,
      __FILE__,
      __LINE__
      );
    free (Ccb);
    goto ErrorExit;
  }

  if (0 == strcmp_i (Ccb->CaptureFilter, " ALL")) {
    TempFilter = NULL;
  } else {
    TempFilter = Ccb->CaptureFilter;
  }

  if (-1 == pcap_compile (Ccb->Capturer, &Bp, TempFilter, 0, 0xFFFFFF)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "StartCapture: Cannot compile the Packet Filter - %a:%d",
      __FILE__,
      __LINE__
      );
    free (Ccb);
    goto ErrorExit;
  }

  if (-1 == pcap_setfilter (Ccb->Capturer, &Bp)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "StartCapture: Cannot set Packet Filter - %a:%d",
      __FILE__,
      __LINE__
      );
    free (Ccb);
    goto ErrorExit;
  }

  EmsNlAddGoods (Name, (VOID_P *) Ccb, &CcbList);
  EmsCcbCreateTcls (Interp, Name, Ccb);

  return TCL_OK;
ErrorExit:

  return TCL_ERROR;
}

STATIC
INT32
TclReceiveCcbPacket (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "ReceiveCcbPacket" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8      *CcbName;
  INT8      *PacketName;
  CCB       *Ccb;
  UINT32    Timeout;
  UINT32    Count;
  PACKET_T  *PacketPointer;
  INT8      ErrBuff[1000];

  Count = 0;

  LogCurrentCommand (Argc, Argv);

  if (Argc < 4) {
    Tcl_AppendResult (
      Interp,
      "ReceiveCcbPacket: ReceiveCcbPacket <CcbName> <PacketName><Timeout>",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  CcbName     = (INT8 *) Argv[1];
  PacketName  = (INT8 *) Argv[2];
  Ccb         = EmsNlFindGoodsByName (CcbName, &CcbList);
  if (NULL == Ccb) {
    Tcl_AppendResult (
      Interp,
      "ReceiveCcbPacket: No such Ccb",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (strlen (Argv[3]) != AsciiStringToUint32 ((INT8 *) Argv[3], &Timeout)) {
    Tcl_AppendResult (
      Interp,
      "ReceiveCcbPacket: Timeout is invalid",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (EmsCcbCapture (Timeout, Ccb) < 0) {
    Tcl_AppendResult (
      Interp,
      "ReceiveCcbPacket: Fail to receive Packet using capture control block ccb",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }
  //
  // the capture control block received a packet
  //
  if (Ccb->Received) {
    PacketPointer = EmsPacketFindByName (PacketName);
    if (PacketPointer) {
      EmsPacketRemove (PacketPointer);
      EmsPacketDestroy (PacketPointer);
    }

    PacketPointer = EmsPacketCreate (PacketName, Ccb->ReceiveBuff, Ccb->ReceiveLen, &(Ccb->Time));
    EmsPacketAdd (PacketPointer);
    Count = 1;
  } else {
    Count = 0;
  }

  if (Ccb->ReceiveBuff) {
    free (Ccb->ReceiveBuff);
    Ccb->ReceiveBuff = NULL;
  }

  sprintf (ErrBuff, "%d", Count);
  Tcl_AppendResult (Interp, ErrBuff, (INT8 *) NULL);

  return TCL_OK;
ErrorExit:

  if (Ccb) {
    free (Ccb);
  }

  return TCL_ERROR;
}

static
INT32
TclEndCapture (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EndCapture" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  CCB     *Ccb;
  NL_NODE *Node;
  NL_NODE *Node1;

  LogCurrentCommand (Argc, Argv);

  if (Argc > 2) {
    Tcl_AppendResult (
      Interp,
      "EndCapture: EndCapture [Name]",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  if (Argc == 1) {

    Node = CcbList;
    while (Node) {
      Node1 = Node;
      Node  = Node->Next;

      Ccb   = (CCB *) (Node1->Goods);

      EmsCcbDestroyTcls (Interp, Node1->Name);
      if (Ccb->Capturer->Packet) {
        PacketFreePacket (Ccb->Capturer->Packet);
        Ccb->Capturer->Packet = NULL;
      }

      pcap_close (Ccb->Capturer);

      EmsNlFreeNode (Node1);
    }

    CcbList = NULL;
    EmsPacketQueueDestroy ();

  } else {
    Node = EmsNlRemoveNodeByName (Argv[1], &CcbList);
    if (NULL == Node) {
      Tcl_AppendResult (
        Interp,
        "EndCapture: No such CCB",
        (INT8 *) NULL
        );
      goto ErrorExit;
    }

    EmsCcbDestroyTcls (Interp, Argv[1]);
    Ccb = (CCB *) (Node->Goods);
    if ((Ccb->Capturer)->Packet) {
      PacketFreePacket ((Ccb->Capturer)->Packet);
      (Ccb->Capturer)->Packet = NULL;
    }

    pcap_close (Ccb->Capturer);

    EmsNlFreeNode (Node);
    if (CcbList == NULL) {
      EmsPacketQueueDestroy ();
    }
  }

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

VOID
EmsCaptureEndAll(
  VOID
  )
/*++

Routine Description:

  Close all the EMS capture

Arguments:

  None

Returns:

  None

--*/
{
  NL_NODE *Node;
  CCB     *Ccb;

  while(CcbList)
  {
    Node    = CcbList;
	CcbList = CcbList->Next;

	Ccb     = (CCB *) (Node->Goods);
	EmsCcbDestroyTcls (EmsThreadSelf()->Interp, Node->Name);
	if(Ccb->Capturer->Packet)
    {
      PacketFreePacket(Ccb->Capturer->Packet);
	  Ccb->Capturer->Packet = NULL;
    }
	pcap_close(Ccb->Capturer);
    EmsNlFreeNode(Node);
  }

  EmsPacketQueueDestroy();
}
