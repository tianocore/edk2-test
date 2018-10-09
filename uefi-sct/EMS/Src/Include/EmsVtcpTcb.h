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
  
    EmsVtcpTcb.h
    
Abstract:

    Data definition for Vtcp

--*/

#ifndef __EMS_TCP_TCB_H__
#define __EMS_TCP_TCB_H__

#include "EmsTypes.h"
#include "EmsVtcpNamedList.h"
#include "EmsTclInit.h"
#include "EmsNet.h"

#include "EmsLogUtility.h"

enum TCP_STATE
{
  TCP_CLOSED      = 0,  /* connection doesn't exist at all */
  TCP_LISTEN      = 1,  /* passively listening for new connection */
  TCP_SYN_SENT    = 2,  /* we've requested a connection (active) */
  TCP_SYN_RECEIVED= 3,  /* she's requested a connection (passive) */
  TCP_ESTABLISHED = 4,  /* connection established, both sides open */
  TCP_FIN_WAIT_1  = 5,  /* we've closed our output side */
  TCP_FIN_WAIT_2  = 6,  /* she's seen us close our output side */
  TCP_CLOSING     = 7,  /* we've both closed but she hasn't acked us */
  TCP_CLOSE_WAIT  = 8,  /* she's closed her output side */
  TCP_LAST_ACK    = 9,  /* we've both closed, we know, she doesn't */
  TCP_TIME_WAIT   = 10  /* she doesn't know we know she closed */
};

#define DEFAULT_MSS           1460
#define DEFAULT_WIN           64000

#define TCP_OPTION_END        0
#define TCP_OPTION_NOP        1
#define TCP_OPTION_MSS        2
#define TCP_OPTION_SACKP      4
#define TCP_OPTION_SCALWIN    3
#define TCP_OPTION_TIMSTAM    8

#define MSS_OPTION_LEN        4
#define SACKP_OPTION_LEN      2
#define SCALWIN_OPTION_LEN    3
#define TIMSTAM_OPTION_LEN    10

#define CHECKSUM_ERROR        1
#define OPTION_PADDING_ERROR  2
#define OPTION_LEN_ERROR      3
#define MAX_OPTION_LEN  256

#define TCP_PTCL              6

/* Tcp CheckSum Pseudo Header*/
typedef struct _PSEUDO_HEADER {
  UINT32  Source;               /* IP source */
  UINT32  Dest;                 /* IP destination */
  UINT8   Mbz;
  UINT8   Protocol;             /* Protocol */
  UINT16  Length;               /* Data field length */
} PSEUDO_HEADER;

typedef struct _VTCB {

  enum TCP_STATE  LocalState;   /* local connection state , not used yet*/
  enum TCP_STATE  RemoteState;  /* expected remote connection state , not used yet */

  UINT32          LocalMss;     /* local mss */
  UINT32          RemoteMss;    /* remote advertised msss*/

  UINT32          LocalIp;
  UINT32          LocalPort;
  UINT32          RemoteIp;
  UINT32          RemotePort;

  UINT32          LocalSaP;
  UINT32          RemoteSaP;

  UINT32          LocalIsn;
  UINT32          RemoteIsn;
  //
  // Flags in lastest received segment
  //
  UINT32          RemoteFCwr;
  UINT32          RemoteFEce;
  UINT32          RemoteFUrg;
  UINT32          RemoteFAck;
  UINT32          RemoteFPsh;
  UINT32          RemoteFRst;
  UINT32          RemoteFSyn;
  UINT32          RemoteFFin;

  UINT32          RemoteSeq;
  UINT32          RemoteAck;
  UINT32          RemoteWin;
  UINT32          RemoteUrg;

  UINT32          RemoteLen;
  UINT32          LocalWin;

  UINT32          RemoteError;        /* Some thing wrong in the received packet */

  UINT32          LocalNextSeq;       /* The sequence number, calculated by the last out packet */
  UINT32          LocalMaxSeq;        /* The max sequence number, has been sent out*/

  UINT32          LocalAckedSeq;      /* The ACK sequence number, calculated by the last out packet */
  UINT32          LocalMaxAckedSeq;   /* The MAX ACK sequence number, has been sent out */

  UINT32          RemoteNextSeq;      /* The sequence number received in the last packet */
  UINT32          RemoteMaxSeq;       /* The MAX sequence number received*/

  UINT32          RemoteAckedSeq;     /* The ACK number in the last packet from peer */
  UINT32          RemoteMaxAckedSeq;  /* The MAX ACK number received */

  UINT32          RemoteScalWinShif;  /* The scale win shif cnt, this is tcp header option section*/
  UINT32          RemoteTsVal;        /*The Time stamp value, this is tcp header option section*/
  UINT32          RemoteTsEcr;        /*The time stamp echo reply, this is tcp header option section*/

  libnet_t        *SendBuff;          /* A temp buffer to send */

  /* Libnet tags for fast rebuild send buffer, not used yet */
  libnet_ptag_t   TcpOptionTag;
  libnet_ptag_t   TcpTag;
  libnet_ptag_t   IpTag;
  libnet_ptag_t   EthTag;

  UINT8           *ReceiveBuff;       /* Buffer the lasted packet received */
  UINT32          ReceiveLen;         /* */
  UINT32          Received;           /* Received*/

  pcap_t          *Capturer;          /* Pcap Capturer, for receiving remote packet */
  UINT8           CaptureFilter[100]; /* Packet filter */
} VTCB;

extern NL_LIST  VTcbList;

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
;

VOID_P
EmsVTcbCreateTcls (
  Tcl_Interp *Interp,
  IN CONST INT8       *Name,
  VTCB       *Tcb
  )
/*++

Routine Description:

  Create TCL variables for virtual TCP

Arguments:

  Interp      - TCL intepreter.
  Name    - The name of the TCL variable
  Tcb     - The structure of the TCB

Returns:

  None

--*/
;

VOID_P
EmsVTcbDestroyTcls (
  Tcl_Interp       *Interp,
  CONST INT8       *Name
  )
/*++

Routine Description:

  Destroy some TCL variables about virtual TCB

Arguments:

  Interp      - TCL intepreter.
  Name    - The part name of TCL variable

Returns:

  None

--*/
;

VTCB *
EmsVTcbCreate (
  UINT32          LocalIp,
  UINT16          LocalPort,
  UINT32          RemoteIp,
  UINT16          RemotePort
  )
/*++

Routine Description:

  Create a tcb structure.

Arguments:

  LocalIp    - The IP of the local machine
  LocalPort  - The Port used by local machine
  RemoteIp   - The IP of the remote machine
  RemotePort - The prot used by remote machine

Returns:

  Return the virtual TCB structure

--*/
;

INT32
EmsVTcbInitSendBuff (
  VTCB              *Tcb
  )
/*++

Routine Description:

  initialize the send data buffer

Arguments:

  Tcb - The structure of TCP

Returns:

  -1 Failure
  0  Success

--*/
;

INT32
EmsVTcbDoChecksum (
  VTCB               *Tcb
  )
/*++

Routine Description:

  Do the checksum for virtual TCP

Arguments:

  Tcb - The structure of the TCP

Returns:

  1  Some error occur
  0  Success

--*/
;

UINT16
EmsVTcbInChecksum (
  IN  UINT16    *Buffer,
  IN  UINT32    Size
  )
/*++

Routine Description:

  compute the checksum

Arguments:

  Buffer  - The data buffer
  Size    - The size of the buffer

Returns:

  Return the checksum

--*/
;

INT32
EmsVTcbSend (
  VTCB   *Tcb
  )
/*++

Routine Description:

  The virtual send packet function

Arguments:

  Tcb - The data structure of the TCP

Returns:

  return the result of libnet_write

--*/
;

INT32
EmsVTcbUpdateSendBuff (
  VTCB              *Tcb,
  UINT32            Seq,
  UINT32            Ack,
  UINT16            CheckSum,
  UINT8             Control,
  UINT16            Win,
  UINT16            Urg,
  UINT8             *Options,
  UINT32            OptionsLen,
  UINT8             *Payload,
  UINT32            PayloadLen
  )
/*++

Routine Description:

  Update the virtual TCP send data buffer

Arguments:

  Tcb       - The data structure of TCP
  Seq       - the sequence
  Ack       - the ack
  CheckSum  - the checksum
  Control   - the control
  Win       - the win
  Urg       - whe urgent
  Options   - The options
  OptionsLen - The size of the options
  Payload   - The payload
  PayloadLen - The size of the payload

Returns:

  -1 Failure

--*/
;

INT32
EmsVTcbCapture (
  IN     UINT32 Timeout,
  IN     VTCB   *Tcb
  )
/*++

Routine Description:

  The virtual TCP's capture packet routine

Arguments:

  Timeout - The maxinum time will wait
  Tcb     - The structure of the TCP

Returns:

  0

--*/
;

INT32
EmsVTcbParsePacket (
  IN     VTCB   *Tcb
  )
/*++

Routine Description:

  Parse a virtual TCP packet

Arguments:

  Tcb - The structure of the virtual TCP

Returns:

  -1 Failure
  0  Success

--*/
;

#define MIN(a, b)                 ((a) < (b) ? (a) : (b))
#define MAX(a, b)                 ((a) > (b) ? (a) : (b))

#define _CR(Record, TYPE, Field)  ((TYPE *) ((UINT8 *) (Record) - (UINT8 *) &(((TYPE *) 0)->Field)))

#define _OFFSET(TYPE, Field)      (UINT8) (&(((TYPE *) 0)->Field))

#endif
