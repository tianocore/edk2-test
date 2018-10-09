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
  
    EmsPktRecvAssertion.h
    
Abstract:

    

--*/

#ifndef __EMS_RECV_ASSERTION_H__
#define __EMS_RECV_ASSERTION_H__

#define PRINT_MAC_STRING_LEN    35
#define PRINT_TYPE_STRING_LEN   10
#define PRINT_GUID_STRING_LEN   50
#define PRINT_RESULT_STRING_LEN 15
#define PRINT_DISC_STRING_LEN   1400

//
// Recv port
//
#define ASSERTION_LOCAL_PORT  1514
#define ASSERTION_REMOTE_PORT 1514

typedef struct _ASSERTION_PACKAGE {
  UINT8   *ReceiveBuff;       // Buffer the lasted packet received
  UINT32  ReceiveLen;
  UINT32  Received;           // Received
  pcap_t  *Capturer;          // Pcap Capturer, for receiving remote packet
  UINT8   CaptureFilter[100]; // Packet filter
} ASSERTION_PACKAGE;

STATIC Tcl_CmdProc  EmsRecvAssertionPkt;

VOID
EmsRecvAssertionThread (
  VOID* Parameter
  )
/*++

Routine Description:

  The thread routine of receiving assertion message

Arguments:

  Parameter - The parameter of the thread routine

Returns:

  None

--*/
;

VOID_P
EmsRecvedAssertionPkt (
  IN UINT8                    *User,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST UINT8              *Packet
  )
/*++

Routine Description:

  The callback routine of receive assertion packet

Arguments:

  User    - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  None

--*/
;

INT32
EmsParseAssertionPkt (
  ASSERTION_PACKAGE *AssertionPackagePtr
  )
/*++

Routine Description:

  Parse the assertion packet

Arguments:

  AssertionPackagePtr - The pointer to the assertion packet

Returns:

  -1 Failure
  0  Success

--*/
;

INT32
EmsShowAssertion (
  UINT8 *MessageBuf
  )
/*++

Routine Description:

  Show the Assertion

Arguments:

  MessageBuf  - The data of the message to show

Returns:

  0

--*/
;

VOID_P
RecvAssertionTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  RecvAssertion related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

#endif
