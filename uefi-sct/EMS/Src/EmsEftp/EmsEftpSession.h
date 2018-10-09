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
  
    EmsEftpSession.h
    
Abstract:

    Incude header files EMS Eftp

--*/

#ifndef __EMS_EFTP_SESSION_H__
#define __EMS_EFTP_SESSION_H__

#include "EmsTypes.h"
#include "EmsThread.h"
#include "EmsEftpStrategy.h"

enum _Eftp_State
{
  /*
   * when session in state INVALID, it belong public resource.
   * so if one session in state INVALID changes to other state
   * or other state sessions change to state INVALID the operation
   * should put into critical region
   */
  INVALID     = 1,

  /* ESTABLISHED CLOSING and CLOSED state changed only by session self */
  ESTABLISHED,
  CLOSING,
  CLOSED
};

enum _Eftp_Opcode_
{
  EFTP_RRQ    = 1,
  EFTP_WRQ,
  EFTP_DATA,
  EFTP_ACK,
  EFTP_ERROR,
  EFTP_OACK
};

enum _Eftp_Error_Code_
{
  ERR_NOT_DEFINED       = 0,
  ERR_FILE_NOT_FOUND    = 1,
  ERR_ACCESS_VIOLATION  = 2,
  ERR_DISK_FULL         = 3,
  ERR_ILLEGAL_OPERATION = 4,
  ERR_UNKNOW_TRANSFER_ID= 5,
  ERR_FILE_ALREADY_EXIST= 6,
  ERR_NO_SUCH_USER      = 7,
  ERR_REQUEST_DENIED    = 8,
  ERRCODE_LEN           = 2
};

//
// EFTP Session Structure.
//
typedef struct Eftp_Session_Struct {
  struct Eftp_Session_Struct  *Next;
  UINT32                      SessionId;
  UINT8                       SrcMacAddr[MAX_MAC_LEN + 1];
  UINT8                       DesMacAddr[MAX_MAC_LEN + 1];
  INT32                       State;
  INT32                       ByteSend;
  INT32                       ByteRecv;
  INT8                        LastSentMsg[MAX_EFTP_BUF_LEN];
  UINT32                      LastSentLen;
  UINT32                      Timeout;
  UINT32                      TimeoutCount;
  libnet_t                    *LibnetHandler;
  Eftp_Strategy               Strategy;

  EmsThread                   *SessionThread;
  HANDLE                      *SessionWaitPktEvent;
  EmsEftpPkt                  *SessionPktListHead;
  EmsEftpPkt                  *SessionPktListTail;
  UINT32                      SessionPktListNodeNum;

  HANDLE                      Mutex;

  VOID (*SendData) (struct Eftp_Session_Struct *, INT8 *, UINT32);
  VOID (*ResendData) (struct Eftp_Session_Struct *);
  VOID (*GetOpCode) (CONST INT8 *, UINT16 *);
  VOID (*GetBlkNo) (CONST INT8 *, UINT16 *);
  VOID (*GetLength) (INT8 *, UINT16 *);
  UINT32 (*BuildPkt) (struct Eftp_Session_Struct *, UINT8 *, UINT16, UINT16, UINT16, INT8 *, UINT32);
  VOID_P (*SilentShutdown) (struct Eftp_Session_Struct *);
  VOID_P (*LoudShutdown) (struct Eftp_Session_Struct *);
}
Eftp_Session;

VOID
EMsEftpSessionPktFree (
  EmsEftpPkt *Pkt
  )
/*++

Routine Description:

  Free a packet

Arguments:

  Pkt - The packet should be free

Returns:

  None

--*/
;

INT32
EmsEftpSessionPktSave (
  EmsEftpPkt        **Pkt,
  CONST UINT8       *Buffer,
  INT32             Len
  )
/*++

Routine Description:

  Save a packet to a given buffer

Arguments:

  Pkt     - The packet to be saved
  Buffer  - The buffer used to save the content of packet
  Len     - The length of the buffer

Returns:

  -1 Failure
  0  Success

--*/
;

INT32
EmsEftpSessionRegister (
  Eftp_Session **Session,
  UINT8        *SrcMacAddr,
  UINT8        *DesMacAddr,
  UINT16       OpCode,
  INT8         *FileName
  )
/*++

Routine Description:

  Register an EMS Eftp session

Arguments:

  Session     - The session should be opened
  SrcMacAddr  - The source MAC address which is the session's attribution
  DesMacAddr  - The target MAC address which is the session's attribution
  OpCode      - The opcode of the session
  FileName    - The name of the file which the session will open

Returns:

  -1 Failure
  0  Success

--*/
;

VOID
EmsEftpSessionUnregister (
  Eftp_Session *Session
  )
/*++

Routine Description:

  Unregister an EMS Eftp session

Arguments:

  Session - The session which should be unregister

Returns:

  None

--*/
;

INT32
EmsEftpSessionPktPut (
  UINT8             *SrcMacAddr,
  EmsEftpPkt        *Pkt
  )
/*++

Routine Description:

  Give a packet to the corresponding session and let the Session to 
  process it.

Arguments:

  SrcMacAddr  - The MAC address of the source machine
  Pkt         - The packet should be put

Returns:

  -1 Failure
  0  Success

--*/
;

VOID
EmsEftpSessionPktGet (
  Eftp_Session      *Session,
  EmsEftpPkt        **Pkt
  )
/*++

Routine Description:

  Get a packet from the packet list in the session data structure

Arguments:

  Session - The Session data structure which contain packet list
  Pkt     - The packet which be got

Returns:

  None

--*/
;

#define EmsEftpSessionSignal(S)   SetEvent ((S)->SessionWaitPktEvent)
#define EmsEftpSessionWait(S)     WaitForSingleObject ((S)->SessionWaitPktEvent, INFINITE)
#define EmsEftpSessionTimeWait(S) WaitForSingleObjectEx ((S)->SessionWaitPktEvent, (S)->Timeout, TRUE)

VOID
EmsEftpSessionModSetup (
  VOID
  )
/*++

Routine Description:

  enable the utility of EMS Eftp Session

Arguments:

  None

Returns:

  None

--*/
;

#endif
