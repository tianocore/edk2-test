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
  
    EmsEftp.c
    
Abstract:

    EMS EFTP implementation.

--*/

#include "EmsEftp.h"
#include "EmsEftpSession.h"

extern INT8 *EmsInterface;

VOID
EmsEftpModEnable (
  VOID
  )
/*++

Routine Description:

  Enable the EMS Eftp utility

Arguments:

  None

Returns:

  None

--*/
{
  EmsEftpSessionModSetup ();
}

VOID
EftpTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS Eftp related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  Tcl_CreateCommand (
    Interp,
    "EftpStart",
    TclEftpStart,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
}

STATIC
VOID
EmsEftpGetOpcodeFromPkt (
  UINT16       *OpCode,
  CONST INT8   *Pkt
  )
/*++

Routine Description:

  Get Opcode from a packet

Arguments:

  OpCode  - The Opcode should be get and return
  Pkt     - The packet should be analyze

Returns:

  None

--*/
{
  memcpy (OpCode, Pkt + OPCODE_OFFSET, 2);
  *OpCode = ntohs ((UINT16) (*OpCode));
}

STATIC
VOID
EmsEftpGetSrcMacFromPkt (
  INT8         *SrcMacAddr,
  CONST UINT8  *Packet
  )
/*++

Routine Description:

  Get source MAC address from a packet

Arguments:

  SrcMacAddr  - The MAC address should be get and return
  Packet      - The packet should be analyze

Returns:

  None

--*/
{
  memcpy (SrcMacAddr, Packet + SRC_MAC_OFFSET, MAX_MAC_LEN);
  SrcMacAddr[MAX_MAC_LEN] = 0;
}

STATIC
VOID
EmsEftpGetDesMacFromPkt (
  INT8         *DesMacAddr,
  CONST UINT8  *Packet
  )
/*++

Routine Description:

  Get target MAC address from a packet

Arguments:

  DesMacAddr  - The MAC address of target machine should be get and return
  Packet      - The packet should be analyze

Returns:

  None

--*/
{
  memcpy (DesMacAddr, Packet + DES_MAC_OFFSET, MAX_MAC_LEN);
  DesMacAddr[MAX_MAC_LEN] = 0;
}

STATIC
VOID
EmsEftpGetFileNameFromPkt (
  INT8         *FileName,
  CONST UINT8  *Packet
  )
/*++

Routine Description:

  Get name of the file the Eftp will upload from a packet

Arguments:

  FileName  - The file name should be get and return
  Packet    - The packet should be analyze

Returns:

  None

--*/
{
  strcpy (FileName, Packet + FILE_NAME_OFFSET);
}

STATIC
VOID
EmsEftpPktDispatch (
  UINT8                    *User,
  CONST struct pcap_pkthdr *PktHdr,
  CONST UINT8              *Packet
  )
/*++

Routine Description:

  Process the packet according to the opcode and dispatch it to 
  the corresponding routine

Arguments:

  User    - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  None

--*/
{
  Eftp_Session  *Session;
  UINT16        OpCode;
  UINT8         SrcMacAddr[MAX_MAC_LEN + 1];
  UINT8         DesMacAddr[MAX_MAC_LEN + 1];
  INT8          FileName[MAX_FILENAME_LEN];
  EmsEftpPkt    *Pkt;

  Session = NULL;
  Pkt     = NULL;

  EmsEftpGetOpcodeFromPkt (&OpCode, Packet);
  EmsEftpGetSrcMacFromPkt (SrcMacAddr, Packet);
  EmsEftpGetDesMacFromPkt (DesMacAddr, Packet);

  if (EmsEftpSessionPktSave (&Pkt, Packet, PktHdr->len) != 0) {
    EFTP_ERROR_MSG ("EmsEftpPktDispatch EmsEftpSessionPktSave failure\n");
    return ;
  }

  switch (OpCode) {
  case EFTP_RRQ:
  case EFTP_WRQ:
    EmsEftpGetFileNameFromPkt (FileName, Packet);

    /* new request must accroding new session otherwise error occur */
    if (EmsEftpSessionRegister (&Session, SrcMacAddr, DesMacAddr, OpCode, FileName) != 0) {
      EFTP_ERROR_MSG ("EmsEftpPktDispatch EmsEftpSessionRegister failure\n");
      goto EmsEftpPktDispatchError2;
    }

    if (EmsEftpSessionPktPut (SrcMacAddr, Pkt) != 0) {
      EFTP_ERROR_MSG ("EmsEftpPktDispatch EmsEftpSessionPktPut (to New Session) failure\n");
      goto EmsEftpPktDispatchError1;
    }
    break;

  case EFTP_DATA:
  case EFTP_ACK:
  case EFTP_ERROR:
    if (EmsEftpSessionPktPut (SrcMacAddr, Pkt) != 0) {
      EFTP_ERROR_MSG ("EmsEftpPktDispatch EmsEftpSessionPktPut failure\n");
      goto EmsEftpPktDispatchError2;
    }
    break;

  default:
    printf ("######Fatual error: get pkt OpCode:%x\n", OpCode);
    exit (-1);
  }

  return ;

EmsEftpPktDispatchError1:
  EmsEftpSessionUnregister (Session);
EmsEftpPktDispatchError2:
  EMsEftpSessionPktFree (Pkt);
}

STATIC
VOID
EmsEftpRecvThread (
  VOID  *HostMacAddr
  )
/*++

Routine Description:

  The thread routine for Eftp receiving packet

Arguments:

  HostMacAddr - The MAC address of the host machine

Returns:

  None

--*/
{
  pcap_t              *Capturer;          /* Pcap Capturer, for receiving remote Packet */
  UINT8               CaptureFilter[100]; /* Packet filter */
  INT8                ErrBuff[PCAP_ERRBUF_SIZE * 2];
  struct bpf_program  Bp;

  if ((Capturer = pcap_open_live (
                    EmsInterface,         // name of the device
                    65536,                // portion of the packet to capture
                    1,                    // promiscuous mode
                    1,                    // read timeout
                    ErrBuff               // error buffer
                    )) == NULL) {
    EFTP_ERROR_MSG ("EmsEftpRecvThread: pcap_open_live error! \n");
    goto EmsEftpRecvThreadError2;
  }

  /* set the filter */
  sprintf (CaptureFilter, "ether proto %d and ether dst %s", EFTP_TYPE, (UINT8 *) HostMacAddr);

  if (-1 == pcap_compile (Capturer, &Bp, CaptureFilter, 0, 0xFFFFFF)) {
    EFTP_ERROR_MSG ("EmsEftpRecvThread: pcap_compile error! \n");
    goto EmsEftpRecvThreadError1;
  }

  if (-1 == pcap_setfilter (Capturer, &Bp)) {
    EFTP_ERROR_MSG ("EmsEftpRecvThread: pcap_setfilter error! \n");
    goto EmsEftpRecvThreadError1;
  }

  EFTP_DEBUG_MSG ("Starting EftpServer now ... \n");

  while (1) {
    /* Capture the packet */
    pcap_dispatch (Capturer, 1, EmsEftpPktDispatch, NULL);
  }

  pcap_close (Capturer);
  return ;

EmsEftpRecvThreadError1:
  pcap_close (Capturer);
EmsEftpRecvThreadError2:
  exit (-1);
}

STATIC
INT32
TclEftpStart (
  ClientData      clientData,
  Tcl_Interp      *Interp,
  INT32           Argc,
  CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "TclEftpStart" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  EmsThread *Thread;

  if (Argc < 2) {
    EFTP_ERROR_MSG ("You should call this function with the host mac Address!\n");
    return TCL_ERROR;
  }

  if (EFI_SUCCESS != EmsCreateThread (&Thread, EmsEftpRecvThread, (VOID *) Argv[1], NULL, NULL)) {
    printf ("EmsEftpStart Error!\n");
    exit (-1);
  }

  return TCL_OK;
}

/*-------------------------------------------------------------------------*/
STATIC EmsEftpRequest *EmsEftpRequestListHead = NULL;
STATIC EmsEftpRequest *EmsEftpRequestListTail = NULL;
STATIC HANDLE         EmsEftpRequestListMutex = NULL;

EmsEftpRequest *
EmsEftpRegisterRequest (
  VOID
  )
/*++

Routine Description:

  Register an EMS Eftp request

Arguments:

  None

Returns:

  The new EMS Eftp request

--*/
{
  EmsEftpRequest  *Req;
  Req = (EmsEftpRequest *) malloc (sizeof (EmsEftpRequest));

  if (NULL == Req) {
    printf ("======EmsEftpRegisterRequest malloc EmsEftpRequest failure\n");
    exit (-1);
  }

  Req->Next       = NULL;
  Req->WaitEvent  = CreateEvent (0, FALSE, FALSE, NULL);

  WaitForSingleObject (EmsEftpRequestListMutex, INFINITE);
  if (NULL == EmsEftpRequestListHead) {
    EmsEftpRequestListHead  = Req;
    EmsEftpRequestListTail  = Req;
  } else {
    EmsEftpRequestListTail->Next  = Req;
    EmsEftpRequestListTail        = Req;
  }

  ReleaseMutex (EmsEftpRequestListMutex);

  return Req;
}

VOID
EmsEftpRequestWait (
  EmsEftpRequest *Req
  )
/*++

Routine Description:

  Wait for the EMS Eftp request

Arguments:

  Req - EMS Eftp request should wait for

Returns:

  None

--*/
{
  printf ("======Enter EmsEftpRequestWait\n");
  if (Req) {
    WaitForSingleObject (Req->WaitEvent, INFINITE);
  }

  printf ("======Exit EmsEftpRequestWait\n");

  CloseHandle (Req->WaitEvent);
  free (Req);
}

VOID
EmsEftpRequestSignal (
  VOID
  )
/*++

Routine Description:

  Signal The EMS thread which waiting for the EMS Eftp Request

Arguments:

  None

Returns:

  None

--*/
{
  EmsEftpRequest  *Req;

  Req = NULL;

  WaitForSingleObject (EmsEftpRequestListMutex, INFINITE);
  if (EmsEftpRequestListHead == EmsEftpRequestListTail) {
    Req = EmsEftpRequestListHead;
    EmsEftpRequestListHead = EmsEftpRequestListTail = NULL;
  } else {
    Req                     = EmsEftpRequestListHead;
    EmsEftpRequestListHead  = EmsEftpRequestListHead->Next;
  }

  ReleaseMutex (EmsEftpRequestListMutex);

  if (Req) {
    SetEvent (Req->WaitEvent);
  }
}
