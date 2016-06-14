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
