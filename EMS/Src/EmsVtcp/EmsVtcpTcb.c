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
  
    EmsVtcpTcb.c
    
Abstract:

    

--*/

#include "EmsVtcpTcb.h"
#include "EmsMain.h"
#include "EmsTclInit.h"
#include "EmsNet.h"

#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsProtoTcp.h"
#include "EmsLogUtility.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern INT8   *EmsInterface;
extern UINT8  RemoteEthaddr[6];
extern UINT8  LocalEthaddr[6];

typedef struct _VTCB_FIELD_T {
  INT8    *Name;
  UINT32  Offset;
} VTCB_FIELD_T;

STATIC VTCB_FIELD_T VTcbFields[] = {
  {
    "l_state",
    _OFFSET(VTCB, LocalState)
  },
  {
    "r_state",
    _OFFSET(VTCB, RemoteState)
  },
  {
    "l_mss",
    _OFFSET(VTCB, LocalMss)
  },
  {
    "r_mss",
    _OFFSET(VTCB, RemoteMss)
  },
  {
    "l_ip",
    _OFFSET(VTCB, LocalIp)
  },
  {
    "l_port",
    _OFFSET(VTCB, LocalPort)
  },
  {
    "r_ip",
    _OFFSET(VTCB, RemoteIp)
  },
  {
    "r_port",
    _OFFSET(VTCB, RemotePort)
  },
  {
    "l_sa_p",
    _OFFSET(VTCB, LocalSaP)
  },
  {
    "r_sa_p",
    _OFFSET(VTCB, RemoteSaP)
  },
  {
    "l_isn",
    _OFFSET(VTCB, LocalIsn)
  },
  {
    "r_isn",
    _OFFSET(VTCB, RemoteIsn)
  },
  {
    "r_f_cwr",
    _OFFSET(VTCB, RemoteFCwr)
  },
  {
    "r_f_ece",
    _OFFSET(VTCB, RemoteFEce)
  },
  {
    "r_f_urg",
    _OFFSET(VTCB, RemoteFUrg)
  },
  {
    "r_f_ack",
    _OFFSET(VTCB, RemoteFAck)
  },
  {
    "r_f_psh",
    _OFFSET(VTCB, RemoteFPsh)
  },
  {
    "r_f_rst",
    _OFFSET(VTCB, RemoteFRst)
  },
  {
    "r_f_syn",
    _OFFSET(VTCB, RemoteFSyn)
  },
  {
    "r_f_fin",
    _OFFSET(VTCB, RemoteFFin)
  },
  {
    "r_seq",
    _OFFSET(VTCB, RemoteSeq)
  },
  {
    "r_ack",
    _OFFSET(VTCB, RemoteAck)
  },
  {
    "r_win",
    _OFFSET(VTCB, RemoteWin)
  },
  {
    "r_urg",
    _OFFSET(VTCB, RemoteUrg)
  },
  {
    "r_len",
    _OFFSET(VTCB, RemoteLen)
  },
  {
    "l_win",
    _OFFSET(VTCB, LocalWin)
  },
  {
    "r_error",
    _OFFSET(VTCB, RemoteError)
  },
  {
    "l_next_seq",
    _OFFSET(VTCB, LocalNextSeq)
  },
  {
    "l_max_seq",
    _OFFSET(VTCB, LocalMaxSeq)
  },
  {
    "l_acked_seq",
    _OFFSET(VTCB, LocalAckedSeq)
  },
  {
    "l_max_acked_seq",
    _OFFSET(VTCB, LocalMaxAckedSeq)
  },
  {
    "r_next_seq",
    _OFFSET(VTCB, RemoteNextSeq)
  },
  {
    "r_max_seq",
    _OFFSET(VTCB, RemoteMaxSeq)
  },
  {
    "r_acked_seq",
    _OFFSET(VTCB, RemoteAckedSeq)
  },
  {
    "r_max_acked_seq",
    _OFFSET(VTCB, RemoteMaxAckedSeq)
  },
  {
    "r_scalwin_shif",
    _OFFSET(VTCB, RemoteScalWinShif)
  },
  {
    "r_ts_val",
    _OFFSET(VTCB, RemoteTsVal)
  },
  {
    "r_ts_ecr",
    _OFFSET(VTCB, RemoteTsEcr)
  },
  {
    "receive_len",
    _OFFSET(VTCB, ReceiveLen)
  },
  {
    "received",
    _OFFSET(VTCB, Received)
  },
  {
    NULL,
    0
  }
};

STATIC
VOID_P
TcbGotPacket (
  IN u_char                   *User,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  );

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
{
  VTCB                *Con;
  INT8                ErrBuff[PCAP_ERRBUF_SIZE * 2];
  struct bpf_program  Bp;

  Con = malloc (sizeof (VTCB));
  if (NULL == Con) {
    return Con;

  }

  Con->LocalState   = TCP_CLOSED; /* connection state */
  Con->RemoteState  = TCP_CLOSED; /* connection state */

  Con->LocalMss     = DEFAULT_MSS;
  Con->RemoteMss    = 0;

  Con->LocalIp      = LocalIp;
  Con->LocalPort    = LocalPort;
  Con->RemoteIp     = RemoteIp;
  Con->RemotePort   = RemotePort;

  sprintf (
    Con->CaptureFilter,
    "dst %d.%d.%d.%d and src %d.%d.%d.%d and tcp and port %d and port %d",
    LocalIp >> 24,
    LocalIp >> 16 & 0xFF,
    LocalIp >> 8 & 0xFF,
    LocalIp & 0xFF,
    RemoteIp >> 24,
    RemoteIp >> 16 & 0xFF,
    RemoteIp >> 8 & 0xFF,
    RemoteIp & 0xFF,
    LocalPort,
    RemotePort
    );

  Con->LocalSaP   = 0;
  Con->RemoteSaP  = 0;

  Con->LocalIsn   = 0x1234;
  Con->RemoteIsn  = 0;
  //
  // Flags in lastest received segment
  //
  Con->RemoteFSyn         = 0;
  Con->RemoteFAck         = 0;
  Con->RemoteFPsh         = 0;
  Con->RemoteFUrg         = 0;
  Con->RemoteSeq          = 0;
  Con->RemoteAck          = 0;
  Con->RemoteWin          = 0;
  Con->RemoteLen          = 0;

  Con->RemoteError        = 0;

  Con->LocalNextSeq       = 0;
  Con->LocalMaxSeq        = 0;
  Con->LocalAckedSeq      = 0;
  Con->LocalMaxAckedSeq   = 0;

  Con->RemoteNextSeq      = 0;
  Con->RemoteMaxSeq       = 0;
  Con->RemoteAckedSeq     = 0;
  Con->RemoteMaxAckedSeq  = 0;

  Con->LocalWin           = DEFAULT_WIN;

  Con->RemoteScalWinShif  = 0;
  Con->RemoteTsEcr        = 0;
  Con->RemoteTsVal        = 0;

  Con->SendBuff           = NULL;
  Con->TcpOptionTag       = 0;
  Con->TcpTag             = 0;
  Con->IpTag              = 0;
  Con->EthTag             = 0;

  Con->ReceiveBuff        = NULL;
  Con->ReceiveLen         = 0;      /* */
  Con->Received           = 0;      /* Received ??*/

  if ((
        Con->Capturer = pcap_open_live (
                    EmsInterface,         // name of the device
                    65536,                // portion of the packet to capture
                    1,                    // promiscuous mode
                    1,                    // read timeout
                    ErrBuff               // error buffer
                    )) == NULL) {
    free (Con);
    return NULL;
  }

  if (-1 == pcap_compile (Con->Capturer, &Bp, Con->CaptureFilter, 0, 0xFFFFFF)) {
    free (Con);
    return NULL;
  }

  if (-1 == pcap_setfilter (Con->Capturer, &Bp)) {
    free (Con);
    return NULL;
  }

  return Con;
}

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
{
  INT8    VarName[100];
  UINT32  Index;

  for (Index = 0; VTcbFields[Index].Name; Index++) {
    sprintf (VarName, "%s.%s", Name, VTcbFields[Index].Name);
    Tcl_UnlinkVar (Interp, VarName);
    Tcl_LinkVar (Interp, VarName, (UINT8 *) Tcb + VTcbFields[Index].Offset, TCL_LINK_INT);
  }

  return ;
}

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
{
  INT8    VarName[100];
  UINT32  Index;

  for (Index = 0; VTcbFields[Index].Name; Index++) {
    sprintf (VarName, "%s.%s", Name, VTcbFields[Index].Name);
    Tcl_UnlinkVar (Interp, VarName);
  }

  return ;
}

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
{

  libnet_t      *l;
  libnet_ptag_t TcpOptionTag;
  libnet_ptag_t TcpTag;
  libnet_ptag_t IpTag;
  libnet_ptag_t EthTag;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  UINT32        Len;
  //
  //  Initialize the libnet
  //
  l = libnet_init (
        LIBNET_LINK,
        /* injection type */EmsInterface,
        /* network interface */ErrBuf /* errbuf */
        );
  if (NULL == l) {
    return -1;
  }

  /*
   * Build TCP options
   */
  TcpOptionTag = libnet_build_tcp_options (
                  NULL,
                  0,
                  l,
                  0
                  );
  if (-1 == TcpOptionTag) {
    return -1;
  }

  /*
  * Build TCP packet
  */
  Len = LIBNET_TCP_H;

  TcpTag = libnet_build_tcp (
            (UINT16) (Tcb->LocalPort),
            (UINT16) (Tcb->RemotePort),
            0,
            0,
            0,
            (UINT16) (Tcb->LocalWin),
            0,
            0,
            Len,
            NULL,
            0,
            l,
            0
            );

  if (-1 == TcpTag) {
    return -1;
  }

  Len = LIBNET_IPV4_H + LIBNET_TCP_H;

  IpTag = libnet_build_ipv4 (
            Len,
            0,
            /* TOS */GetIpId (),
            /* IP ID */0,
            /* IP Frag */0x40,
            /* TTL */IPPROTO_TCP,
            /* protocol */0,
            /* CheckSum */htonl (Tcb->LocalIp),
            htonl (Tcb->RemoteIp),
            NULL,
            /* payload */0,
            /* payload size */l,
            0
            );
  if (-1 == IpTag) {
    return -1;
  }

  EthTag = libnet_build_ethernet (
            RemoteEthaddr,
            LocalEthaddr,
            ETHERTYPE_IP,
            NULL,
            0,
            l,
            0
            );
  if (-1 == EthTag) {
    return -1;
  }

  Tcb->TcpOptionTag = TcpOptionTag;
  Tcb->TcpTag       = TcpTag;
  Tcb->IpTag        = IpTag;
  Tcb->EthTag       = EthTag;
  Tcb->SendBuff     = l;

  return 0;
}

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
  0  Success

--*/
{
  libnet_t      *l;
  libnet_ptag_t TcpOptionTag;
  libnet_ptag_t TcpTag;
  libnet_ptag_t IpTag;
  libnet_ptag_t EthTag;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  UINT32        Len;

  l = Tcb->SendBuff;

  if (NULL != l) {
    libnet_cq_remove(l);
    libnet_destroy (l);
  }

  l = libnet_init (
        LIBNET_LINK,
        /* injection type */EmsInterface,
        /* network interface */ErrBuf /* errbuf */
        );
  if (NULL == l) {
    return -1;
  }

  TcpOptionTag  = Tcb->TcpOptionTag;
  TcpTag        = Tcb->TcpTag;
  IpTag         = Tcb->IpTag;
  EthTag        = Tcb->EthTag;

  TcpOptionTag = libnet_build_tcp_options (
                  Options,
                  OptionsLen,
                  l,                  //        TcpOptionTag
                  0
                  );
  if (-1 == TcpOptionTag) {
    return -1;
  }

  Len = LIBNET_TCP_H;
  Len += PayloadLen + OptionsLen;

  TcpTag = libnet_build_tcp (
            (UINT16) (Tcb->LocalPort),
            (UINT16) (Tcb->RemotePort),
            Seq,
            Ack,
            Control,
            Win,
            CheckSum,
            Urg,
            Len,
            Payload,
            PayloadLen,
            l,                        //        TcpTag
            0
            );

  if (-1 == TcpTag) {
    return -1;
  }

  Len = LIBNET_IPV4_H + LIBNET_TCP_H;
  Len += PayloadLen + OptionsLen;

  IpTag = libnet_build_ipv4 (
            Len,
            0,
            /* TOS      */GetIpId (),
            /* IP ID    */0,
            /* IP Frag  */0x40,
            /* TTL      */IPPROTO_TCP,
            /* protocol */0,
            /* CheckSum */htonl (Tcb->LocalIp),
            htonl (Tcb->RemoteIp),
            NULL,
            /* payload */0,
            /* payload size */l,  //        IpTag
            0
            );
  if (-1 == IpTag) {
    return -1;
  }

  EthTag = libnet_build_ethernet (
            RemoteEthaddr,
            LocalEthaddr,
            ETHERTYPE_IP,
            NULL,
            0,
            l,                    //          EthTag
            0
            );
  if (-1 == EthTag) {
    return -1;
  }

  Tcb->SendBuff     = l;
  Tcb->TcpOptionTag = TcpOptionTag;
  Tcb->TcpTag       = TcpTag;
  Tcb->IpTag        = IpTag;
  Tcb->EthTag       = EthTag;
  return 0;
}

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
{
  //
  //  _asm int 3;
  //
  return libnet_write (Tcb->SendBuff);
}

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
{
  INT32   Index;

  INT32   Res;
  UINT32  DueTime;

  Index         = 0;
  Tcb->Received = 0;

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
    Res = pcap_dispatch (Tcb->Capturer, 1, TcbGotPacket, (UINT8 *) Tcb);
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
VOID_P
TcbGotPacket (
  IN u_char                   *User,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  )
/*++

Routine Description:

  The callback function of geting a TCP packet

Arguments:

  User    - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  None

--*/
{
  VTCB  *Tcb;

  Tcb = (VTCB *) User;
  if (Tcb->ReceiveBuff) {
    free (Tcb->ReceiveBuff);
  }

  Tcb->ReceiveBuff = malloc (PktHdr->len);
  memcpy (Tcb->ReceiveBuff, Packet, PktHdr->len);
  Tcb->ReceiveLen = PktHdr->len;
  Tcb->Received   = 1;
}

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
{
  TCP_HEADER  *TcpHdr;
  IP_HEADER   *IpHdr;
  UINT32      Length;
  UINT32      OptionsLen;
  UINT32      TcpDataOffset;
  UINT8       *OptionsPointer;
  UINT8       *OptionsEnd;
  UINT32      IpLength;

  //
  // _asm int 3;
  //
  if (NULL == Tcb->ReceiveBuff) {
    return -1;
  }

  Length = Tcb->ReceiveLen;

  if (Length < (sizeof (TCP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
    return -1;
  }

  TcpHdr          = (TCP_HEADER *) (Tcb->ReceiveBuff + sizeof (ETH_HEADER) + sizeof (IP_HEADER));

  TcpDataOffset   = (TcpHdr->TcpDataOffset >> 4) & 0x0F;
  Tcb->RemoteFCwr = (TcpHdr->TcpCtrlFlag & TH_CWR) ? 1 : 0;
  Tcb->RemoteFEce = (TcpHdr->TcpCtrlFlag & TH_ECE) ? 1 : 0;
  Tcb->RemoteFUrg = (TcpHdr->TcpCtrlFlag & TH_URG) ? 1 : 0;
  Tcb->RemoteFAck = (TcpHdr->TcpCtrlFlag & TH_ACK) ? 1 : 0;
  Tcb->RemoteFPsh = (TcpHdr->TcpCtrlFlag & TH_PUSH) ? 1 : 0;
  Tcb->RemoteFRst = (TcpHdr->TcpCtrlFlag & TH_RST) ? 1 : 0;
  Tcb->RemoteFSyn = (TcpHdr->TcpCtrlFlag & TH_SYN) ? 1 : 0;
  Tcb->RemoteFFin = (TcpHdr->TcpCtrlFlag & TH_FIN) ? 1 : 0;

  if (0 == Tcb->RemoteIsn) {
    Tcb->RemoteIsn = ntohl (TcpHdr->TcpSeq);
  }

  Tcb->RemoteSeq  = ntohl (TcpHdr->TcpSeq) - Tcb->RemoteIsn;
  Tcb->RemoteAck  = ntohl (TcpHdr->TcpAck) - Tcb->LocalIsn;
  Tcb->RemoteWin  = ntohs (TcpHdr->TcpWinSize);
  Tcb->RemoteUrg  = ntohs (TcpHdr->TcpUrgent);
  //
  //  tcb -> r_sum    = ntohs (TcpHdr->tcp_checksum);
  //

  /*
   * data offset is 4 bits width.
   */
  if (TcpDataOffset < 5 || TcpDataOffset > 15) {
    OptionsLen = 0;
  } else {
    OptionsLen = TcpDataOffset * 4 - LIBNET_TCP_H;
  }

  /* debuge */

  //
  // OptionsLen = 20;
  //
  // Begin to parse TCP options
  //
  OptionsPointer  = (UINT8 *) TcpHdr + LIBNET_TCP_H;
  OptionsEnd      = OptionsPointer + OptionsLen;

  while (OptionsPointer < OptionsEnd) {

    switch (*OptionsPointer++) {

    case TCP_OPTION_MSS:
      if ((*OptionsPointer++ == MSS_OPTION_LEN) && (OptionsPointer + MSS_OPTION_LEN - 2) <= OptionsEnd) {
        Tcb->RemoteMss = *OptionsPointer++ << 8;
        //
        // get mss value
        //
        Tcb->RemoteMss |= *OptionsPointer++;
      } else {
        Tcb->RemoteError  = OPTION_LEN_ERROR;
        OptionsPointer    = OptionsEnd;
      }
      break;

    case TCP_OPTION_END:
      while (OptionsPointer < OptionsEnd) {
        if (*OptionsPointer++ != 0) {
          Tcb->RemoteError  = OPTION_PADDING_ERROR;
          OptionsPointer    = OptionsEnd;
          break;
        }
      }
      break;

    case TCP_OPTION_NOP:
      break;

    case TCP_OPTION_SACKP:
      if (*OptionsPointer++ == SACKP_OPTION_LEN) {
        Tcb->RemoteSaP = 1;
      } else {
        Tcb->RemoteError  = OPTION_LEN_ERROR;
        OptionsPointer    = OptionsEnd;
      }
      break;

    case TCP_OPTION_SCALWIN:
      if ((*OptionsPointer++ == SCALWIN_OPTION_LEN) && (OptionsPointer + SCALWIN_OPTION_LEN - 2) <= OptionsEnd) {

        Tcb->RemoteScalWinShif = *OptionsPointer++;

      } else {
        Tcb->RemoteError  = OPTION_LEN_ERROR;
        OptionsPointer    = OptionsEnd;
      }
      break;

    case TCP_OPTION_TIMSTAM:
      if ((*OptionsPointer++ == TIMSTAM_OPTION_LEN) && (OptionsPointer + TIMSTAM_OPTION_LEN - 2) <= OptionsEnd) {
        Tcb->RemoteTsVal = ntohl (*((UINT32 *) OptionsPointer));
        ((UINT32 *) OptionsPointer)++;
        Tcb->RemoteTsEcr = ntohl (*((UINT32 *) OptionsPointer));
        ((UINT32 *) OptionsPointer)++;
      } else {
        Tcb->RemoteError  = OPTION_LEN_ERROR;
        OptionsPointer    = OptionsEnd;
      }
      break;

    default:
      if (*OptionsPointer < 2) {
        Tcb->RemoteError = OPTION_LEN_ERROR;
      } else {
        /* Length is ok */
        OptionsPointer += (*OptionsPointer) - 1;
      }

      continue;
    }
  }

  IpHdr                   = (IP_HEADER *) (Tcb->ReceiveBuff + sizeof (ETH_HEADER));
  IpLength                = ntohs (IpHdr->IpLen);

  Tcb->RemoteLen          = IpLength - OptionsLen - sizeof (TCP_HEADER) - sizeof (IP_HEADER);

  Tcb->RemoteNextSeq      = Tcb->RemoteSeq + Tcb->RemoteFSyn + Tcb->RemoteFFin + Tcb->RemoteLen;
  Tcb->RemoteMaxSeq       = MAX (Tcb->RemoteNextSeq, Tcb->RemoteMaxSeq);

  Tcb->RemoteAckedSeq     = Tcb->RemoteAck;
  Tcb->RemoteMaxAckedSeq  = MAX (Tcb->RemoteMaxAckedSeq, Tcb->RemoteAckedSeq);

  return 0;
}

INT32
EmsVTcbDoChecksum (
  IN     VTCB   *Tcb
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
{
  UINT16        Sum;
  UINT32        Len;
  TCP_HEADER    *TcpPacket; /*Tcp packet need to CheckSum include tcp header and data*/
  PSEUDO_HEADER *PseudoHdr; /*Tcp pseudo header */
  IP_HEADER     *IpHdr;
  UINT8         *PkgBuffer;

  Sum       = 0;
  TcpPacket = (TCP_HEADER *) (Tcb->ReceiveBuff + sizeof (ETH_HEADER) + sizeof (IP_HEADER));
  IpHdr     = (IP_HEADER *) (Tcb->ReceiveBuff + sizeof (ETH_HEADER));
  Len       = htons (IpHdr->IpLen) - sizeof (IP_HEADER);
  PkgBuffer = (UINT8 *) malloc (Len + sizeof (PSEUDO_HEADER));

  /* pseudo header */
  PseudoHdr           = (PSEUDO_HEADER *) PkgBuffer;
  PseudoHdr->Source   = IpHdr->IpSrc;
  PseudoHdr->Dest     = IpHdr->IpDst;
  PseudoHdr->Mbz      = 0;
  PseudoHdr->Protocol = TCP_PTCL;
  PseudoHdr->Length   = ntohs (Len);

  /* check Sum tcp packet include pseudo header, tcp header and tcp packet*/
  memcpy ((PkgBuffer + sizeof (PSEUDO_HEADER)), (UINT8 *) TcpPacket, Len);
  Sum = EmsVTcbInChecksum ((UINT16 *) PkgBuffer, (sizeof (PSEUDO_HEADER) + Len));

  free (PkgBuffer);

  if (0x0000 != Sum) {
    RecordAssertion (
      2,
      GenericGuid,
      "TCB -RECEIVETCBPACKET \n",
      "LOG:The CheckSum of this Packet is error"
      );
    return 1;
  }

  return 0;
}

UINT16
EmsVTcbInChecksum (
  IN UINT16 *Buffer,
  IN UINT32 Size
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
{
  UINT32  Chksum;

  Chksum = 0;

  while (Size > 1) {
    Chksum += *Buffer++;
    Size -= sizeof (UINT16);
  }

  if (Size) {
    Chksum += *(UINT8 *) Buffer;
  }

  Chksum = (Chksum >> 16) + (Chksum & 0xffff);
  Chksum += (Chksum >> 16);

  return (UINT16) (~Chksum);
}
