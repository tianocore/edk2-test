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
  
    EmsRpcMain.h
    
Abstract:

    Incude header files for RPC related functions

--*/

#ifndef __EMS_RPC_H__
#define __EMS_RPC_H__

#include <tcl.h>
#include <EmsTypes.h>

#define IN_PARA     1
#define OUT_PARA    2
#define EXPECT_PARA 3

//
// thread data for serial-listen thread
//
struct THREAD_DATA {
  INT32 Run;
  INT8  *Dev;
  INT32 SendQ;
  INT32 RecvQ;
};

//
// definition
//
#define MAX_DEV_LEN         15
#define MAX_SERIAL_NUM      8
#define MAX_SERIAL_TMP_SIZE 4096
#ifndef MAX_MSG_LEN
#define MAX_MSG_LEN 4096
#endif

typedef enum SpecialMsg {RESET = 0, UNDEFINE} SPECIAL_MSG;

#pragma pack(1)
typedef union {
  struct {
    UINT32  DataId;
    UINT32  Rsvd;
  } Flag;
  UINT64  DataFlag;
} RIVL_DATA_FLAG;
#pragma pack()
//
// pattern of key word in elet-call-message
//
#define IN_PATTERN      " _IN_ "
#define OUT_PATTERN     " _OUT_ "
#define EXPECT_PATTERN  " _EXPECT_ "
#define LOG_PATTERN     " _LOG_ "
#define ACK_PATTERN     " _ACK_ "

//
// pattern test-control-message
//
#define TEST_END_MSG    "TEST_END"
#define TEST_STOP_MSG   "TEST_STOP"
#define TEST_ABORT_MSG  "TEST_ABORT"

//
//
//
#define ELET_RESULT_PASS  1
#define ELET_RESULT_FAIL  2
#define ELET_RESULT_WARN  3

//
//
//
#define PARAM_DELIM ' '

//
// RPC error code
//
#define EMS_RPC_SUCCESS       0
#define EMS_RPC_OPEN_FAIL     1
#define EMS_RPC_NOT_SUPPORT   2
#define EMS_RPC_ALREADY_OPEN  3
#define EMS_RPC_NO_RESOURCE   4
#define EMS_RPC_SETATTR_FAIL  5
#define EMS_RPC_NO_SUCH_DEV   6
#define EMS_RPC_NO_QUEUE      7
#define EMS_RPC_ENQUE_FAIL    8
#define EMS_RPC_MSG_TOOLONG   9
#define EMS_RPC_GEN_FAIL      - 1

//
//
//
#define MAX_VAR_NAME_LEN          18
#define MAX_STR_VAR_LEN           20

#define ACK_MSG_ERR               - 1

#define IS_PATTERN(Buff, Pattern) (strlen (Buff) >= strlen (Pattern) && strcmp ((Buff), Pattern) == 0)
#define NOT_PATTERN(Str, Pattern) ((strlen (Str) != strlen (Pattern)) || (strcmp (Buff, Pattern) != 0))

#define MSG_BASE_ID               0x01

//
// EMS library serial API
//
INT32
RpcOpenDev (
  INT8              *Dev
  )
/*++

Routine Description:

  create a thread, open a channel, and listen to the channel

Arguments:

  Dev - dev name

Returns:

  If succeed return 0, else return -1

--*/
;

INT32
RpcCloseDev (
  INT8              *Dev
  )
/*++

Routine Description:

  kill the listen thread

Arguments:

  Dev - dev name

Returns:

  If succeed return 0, else return -1

--*/
;

INT32
RpcSendMessage (
  INT32       Length,
  INT8        *Buff
  )
/*++

Routine Description:

  Send a rpc message

Arguments:

  Length  - The size of rpc message
  Buff    - The data of rpc message

Returns:

  If succeed return 0, else return -1

--*/
;

INT32
RpcRecvMessage (
  INT32     Timeout,
  UINT32     Length,
  INT8      *Message
  )
/*++

Routine Description:

  Receive the rpc message

Arguments:

  Timeout - The maxinum time to wait
  Length  - The length of message received
  Message - The data of message received

Returns:

  If succeed return 0, else return -1

--*/
;

BOOLEAN
ParseAckMessage (
  INT32              Length,
  INT8               *Message,
  BOOLEAN            *pass,
  INT8               **out,
  INT8               **Log
  )
/*++

Routine Description:

  Parse message according to key word

Arguments:

  Length  - The size of the ACK message
  Message - The message
  Pass    - Whether the message is "ACK_P"
  Out     - Used to parse "_OUT_"
  Log     - Used to parse "_LOG_"

Returns:

  TRUE of FALSE

--*/
;

INT32
EmsTargetCleanup(
  UINT8                *TargetMac
  )
/*++

Routine Description:

  Cleanup the target machine

Arguments:

  TargetMac  - The MAC addres of target machine

Returns:

  -1 Failure
  0  Success

--*/
;

STATIC Tcl_CmdProc  EmsSetTargetMac;
STATIC Tcl_CmdProc  EmsGetTargetMac;
STATIC Tcl_CmdProc  TclOpenDev;
STATIC Tcl_CmdProc  TclCloseDev;
STATIC Tcl_CmdProc  TclRestartRecv;
STATIC Tcl_CmdProc  TclCheckTarget;
STATIC Tcl_CmdProc  TclDumpTarget;
STATIC Tcl_CmdProc  TclTargetCleanup;

VOID
RpcTclCmdInit(
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS RPC related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

#endif
