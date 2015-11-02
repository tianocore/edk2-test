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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsRpcMain.c
    
Abstract:

    This file defines the rpc related function

--*/

#include "EmsRpcMsg.h"
#include "EmsRpcMain.h"
#include "EmsLogUtility.h"
#include "EmsRpcEth.h"
#include "EmsRpcTarget.h"
#include "EmsTclInit.h"
#include "EmsUtilityString.h"

//
// Global variable
//
INT32               SendQId;
INT32               RecvQId;
struct THREAD_DATA  ThreadData;
//pthread_mutex_t     MutexSentFlag;
INT32               SentFlag;

#define MAX_DATA_LEN  4096
STATIC INT8         DataMessage[MAX_DATA_LEN];
STATIC INT32        LastDataId = MSG_BASE_ID;

//
// local variable
//
#define LINK_NONE   0
#define LINK_SERIAL 1
#define LINK_ETHER  2

STATIC HANDLE       ListenThreadHandle;
STATIC HANDLE       TimerThreadHandle;
STATIC LPDWORD      ListenThreadId;
STATIC LPDWORD      TimerThreadId;
HANDLE              EmsTimerMutex;
HANDLE              EmsListenMutex;
extern BOOLEAN      EthernetListenRun;
extern BOOLEAN      EthernetTimerRun;

STATIC INT32        Link1 = LINK_NONE;

#define SEND_QUE_ID 111
#define RECV_QUE_ID 110

#define FILTER_SPACE(Pointer) \
  { \
    while (*Pointer == ' ') \
    { \
      Pointer++; \
    } \
  }

STATIC TCL_CMD_TBL  TclCmds[] = {
  {
    "OpenDev",
    TclOpenDev
  },
  {
    "GetTargetMac",
	EmsGetTargetMac
  },
  {
    "SetTargetMac",
    EmsSetTargetMac
  },
  {
    "CloseDev",
    TclCloseDev
  },
  {
    "RestartRecv",
    TclRestartRecv
  },
  {
    "CheckTarget",
    TclCheckTarget
  },
  {
    "DumpTarget",
    TclDumpTarget
  },
  {
    "TclTargetCleanup",
    TclTargetCleanup
  },
  {
    NULL,
    NULL
  }
};

STATIC
INT32
FillDataFlag (
  INT8                              *Data,
  INT8                              *Message,
  INT32                             *DataLen,
  INT32                             DataId
  );

STATIC
INT32
CheckDataId (
  INT8                                      *Message,
  INT32                                     ExpectId
  );

STATIC
VOID
RpcTclMutexInit(
  VOID
  )
/*++

Routine Description:

  Initialize the RPC mutex

Arguments:

  None

Returns:

  None

--*/
{
  EmsTimerMutex   = CreateMutex (NULL, FALSE, NULL);
  EmsListenMutex  = CreateMutex (NULL, FALSE, NULL);
}

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
{
  UINT32  Index;
  //
  // Create internal TCL commands
  //
  for (Index = 0; TclCmds[Index].Cmd; Index++) {
    Tcl_CreateCommand (
      Interp,
      TclCmds[Index].Cmd,
      TclCmds[Index].Proc,
      (ClientData) NULL,
      (Tcl_CmdDeleteProc *) NULL
      );
  }
}

VOID_P
RpcTclInit (
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  Initialize the EMS RPC

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  RpcTclCmdInit(Interp);
  RpcTclMutexInit();
}

STATIC
INT32
TclOpenDev (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "OpenDev" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  INT32 touse;

  if (Argc != 2) {
    goto WrongArg;
  }

  if (strcmp_i ((UINT8 *) Argv[1], "mnp") == 0) {
    touse = LINK_ETHER;
  } else {
    sprintf (ErrorBuff, "OpenDev:  Interface %s not support", Argv[1]);
    goto ErrorExit;
  }

  if (Link1 != LINK_NONE) {
    sprintf (ErrorBuff, "OpenDev:  Interface %s already open", Argv[1]);
    goto ErrorExit;
  }

  if (RpcOpenDev ((INT8 *) Argv[1]) < 0) {
    sprintf (ErrorBuff, "OpenDev:  open %s failed", Argv[1]);
    goto ErrorExit;
  }

  Link1 = touse;

  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "OpenDev:  OpenDev DeviceName");

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

STATIC
INT32
TclCloseDev (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "CloseDev" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  INT32 devid;

  if (Argc != 2) {
    goto WrongArg;
  }

  if (strcmp_i ((UINT8 *) Argv[1], "mnp") == 0) {
    devid = LINK_ETHER;
  } else {
    sprintf (ErrorBuff, "CloseDev:  Interface %s not support", Argv[1]);
    goto ErrorExit;
  }

  if (Link1 != devid) {
    sprintf (ErrorBuff, "CloseDev:  Interface %s not open", Argv[1]);
    goto ErrorExit;
  }

  if (RpcCloseDev ((INT8 *) Argv[1]) < 0) {
    sprintf (ErrorBuff, "CloseDev:  close %s failed", Argv[1]);
    goto ErrorExit;
  }

  Link1 = LINK_NONE;
  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "CloseDev:  CloseDev DeviceName");
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

STATIC
INT32
TclDumpTarget (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DumpTarget" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];

  if (Argc != 1) {
    goto WrongArg;
  }

  ErrorBuff[0] = '\0';
  RpcTargetDumpAll (ErrorBuff);

  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "DumpTarget:  DumpTarget");
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
EmsTargetCleanup(
  UINT8                 *TargetMac
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
{
  RestoreEmsRpcEnv();
  return SendOutCleanup(TargetMac);
}

STATIC
INT32
TclTargetCleanup(
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "TclTargetCleanup" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  UINT8 Mac[6], TargetMac[6];

  sprintf(ErrorBuff, "OK");

  if(Argc != 2)
  {
    sprintf (ErrorBuff, "TclResetTarget:  TclResetTarget Target");
    goto Done;
  }

  if ((AsciiStringToMac ((INT8 *) Argv[1], Mac) < 0) || 
      (GetEasMac(TargetMac) < 0 ) ||
  	  (memcmp(TargetMac, Mac, 6) != 0))
  {
    sprintf (ErrorBuff, "Input target mac not exist!\n");
	goto Done;
  }

  if(EmsTargetCleanup(Mac) != 0)
  {
    sprintf (ErrorBuff, "cleanup Target failure\n");
	goto Done;
  }

Done:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_OK;
}

STATIC
INT32
TclCheckTarget (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "CheckTarget" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  UINT8 Target[6];

  if ((Argc != 3) && (Argc != 1)) {
    goto WrongArg;
  }

  if (Argc == 3) {
    if (AsciiStringToMac ((INT8 *) Argv[2], Target) < 0) {
      goto WrongArg;
    }

    SendOutProbe (Target);
  } else {
    SendOutProbe (NULL);
  }

  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "CheckTarget:  CheckTarget [-T Target]");
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

STATIC
INT32
EmsGetTargetMac (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetTargetMac" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  INT8  TargetMacS[32];
  UINT8 TargetMacI[6];

  if (Argc != 1)
    goto WrongArg;

  if(GetEasMac(TargetMacI) < 0)
  {
    sprintf (ErrorBuff, "EmsGetTargetMac:  Specified Target MAC Not Active");
    goto ErrorExit;
  }

  memset(TargetMacS, 0, sizeof(TargetMacS));

  if(MacToAsciiString(TargetMacS, TargetMacI) < 0)
    goto WrongArg;

  Tcl_AppendResult (Interp, TargetMacS, (INT8 *) NULL);
  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "EmsGetTargetMac:  EmsGetTargetMac");

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

STATIC
INT32
EmsSetTargetMac (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "SetTargetMac" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  UINT8 Target[6];

  if (Argc != 2) {
    goto WrongArg;
  }

  if (AsciiStringToMac ((INT8 *) Argv[1], Target) < 0) {
    goto WrongArg;
  }

  if (SetEasMac (Target) < 0) {
    sprintf (ErrorBuff, "EmsSetTargetMac:  Specified Target MAC Not Active");
    goto ErrorExit;
  }

  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "EmsSetTargetMac:  EmsSetTargetMac Target");

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

STATIC
INT32
TclRestartRecv (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "RestartRecv" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  EmsMsgQEmpty ();
  return TCL_OK;
}

INT32
RpcOpenDev (
  INT8            *Dev
  )
/*++

Routine Description:

  create a thread, open a channel, and listen to the channel

Arguments:

  Dev - dev name

Returns:

  If succeed return 0, else return -1

--*/
{
  //
  // Sanity Check
  //
  if (Dev == NULL) {
    return -1;
  }
  //
  // Initialize recv_q
  //
  RecvQId = EmsMsgQCreate ();
  if (RecvQId == -1) {
    return EMS_RPC_NO_QUEUE;
  }
  //
  // initialize client thread info
  //
  ThreadData.Dev = malloc (MAX_DEV_LEN);
  strcpy (ThreadData.Dev, Dev);
  ThreadData.RecvQ  = RECV_QUE_ID;
  ThreadData.Run    = 1;

  //
  // start sub-thread to recv-from/sent-to serial
  //
  if (strcmp_i (Dev, "mnp") == 0) {
    ListenThreadHandle = CreateThread (
                          NULL,           // default security attributes
                          0,              // use default stack size
                          EthernetListen, // thread function
                          NULL,           // argument to thread function
                          0,              // use default creation flags
                          ListenThreadId
                          );
    //
    // returns the thread identifier
    //
    if (NULL == ListenThreadHandle) {
      RecordMessage (
        EMS_VERBOSE_LEVEL_DEFAULT,
        "EMS:  Fail to create listen thread "
        );
      return -1;
    }

    TimerThreadHandle = CreateThread (
                          NULL,               // default security attributes
                          0,                  // use default stack size
                          ResendTimeHandler,  // thread function
                          NULL,               // argument to thread function
                          0,                  // use default creation flags
                          TimerThreadId
                          );
    //
    // returns the thread identifier
    //
    if (NULL == TimerThreadHandle) {
      RecordMessage (
        EMS_VERBOSE_LEVEL_DEFAULT,
        "EMS:  Fail to create resend timer thread "
        );
      return -1;
    }
  } else {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Device '%s' is not supported ",
      Dev
      );
    return -1;
  }

  while (!EthernetListenRun) {
    Tcl_Sleep (1);
  }

  return 0;
}

INT32
RpcCloseDev (
  INT8 *Dev
  )
/*++

Routine Description:

  kill the listen thread

Arguments:

  Dev - dev name

Returns:

  If succeed return 0, else return -1

--*/
{
  EthernetListenExit ();
  return 0;
}

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
{
  LastDataId++;
  FillDataFlag (Buff, DataMessage, &Length, LastDataId);

  if (Link1 == LINK_ETHER) {
    Tcl_Sleep (5);
    printf ("sent: (%s), Length (%d)\n", DataMessage + sizeof (RIVL_DATA_FLAG), Length);
    return SendRivlMessage (DataMessage, Length);
  } else {
    return -1;
  }

  return 0;
}

STATIC
INT32
FillDataFlag (
  INT8                    *Data,
  INT8                    *Message,
  INT32                   *DataLen,
  INT32                   DataId
  )
/*++

Routine Description:

  Fill the flag of the data in packet

Arguments:

  Data    - The data of message
  Message - Return the rpc message
  DataLen - The size of data
  DataId  - The DataId of the rpc message

Returns:

  If succeed return 0, else return -1

--*/
{
  RIVL_DATA_FLAG  Flag;

  if (!Message || !Data) {
    return -1;
  }

  Flag.Flag.DataId  = htonl (DataId);
  Flag.Flag.Rsvd    = 0;

  memcpy (Message, &Flag, sizeof (Flag));
  memcpy (Message + sizeof (Flag), Data, *DataLen);
  //
  // append zero to the message tail
  //
  Message[sizeof (Flag) +*DataLen] = '\0';

  *DataLen += sizeof (Flag) + 1;

  return 0;
}

STATIC
INT32
CheckDataId (
  INT8            *Message,
  INT32           ExpectId
  )
/*++

Routine Description:

  Check the data id of one message

Arguments:

  Message   - the message
  ExpectId  - expect id

Returns:

  0 equal otherwise the data id of the message

--*/
{
  RIVL_DATA_FLAG  Flag;

  memcpy (&Flag, Message, sizeof (Flag));
  Flag.Flag.DataId = ntohl (Flag.Flag.DataId);
  return (Flag.Flag.DataId == ExpectId) ? 0 : Flag.Flag.DataId;
}

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
{
  INT32            Run;
  INT32            retlen;
  INT32            Count;
  INT32            DataId;

  //
  // Get current time, and Compute timeout timestamp
  // If timeout == -1, means blocking
  //
  if (-1 != Timeout) {
    Count = 0;
  }
  //
  // I can get the operation result, and out parameter
  //
  Run = 1;
  while (Run)
  {
    //
    // If timeout, no longer recv
    //
    if (-1 != Timeout) {
      if (Count >= Timeout * 1000) {
        Run = 0;
      }
	  Count++;
    }

    //
    // If get message, no longer recv
    //
    retlen = EmsMsgQReceive (DataMessage, Length);
    if (retlen > 0)
	{
      if ((DataId = CheckDataId (DataMessage, LastDataId)) != 0)
      {
        printf ("Error Data Id: ExpectId:%d --- Message DataId:%d\n", LastDataId, DataId);
		continue;
      }

      memcpy (Message, DataMessage + sizeof (RIVL_DATA_FLAG), retlen - sizeof (RIVL_DATA_FLAG));
      *(Message + retlen - sizeof (RIVL_DATA_FLAG)) = 0;
      printf ("recv: (%s), Length: %d\n", Message, retlen);
      RecordMessage (EMS_VERBOSE_LEVEL_NOISY, "EMS: recv \"%a\"", Message);
      return retlen;
    }

    Tcl_Sleep (1);
  }

  return -1;
}

BOOLEAN
ParseAckMessage (
  INT32              Length,
  INT8               *Message,
  BOOLEAN            *Pass,
  INT8               **Out,
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
{
  INT8               *Pointer;
  INT8               *LogEnd;
  INT8               *OutEnd;
  INT32              TLen;

  TLen    = strlen (Message);
  LogEnd  = NULL;
  OutEnd  = NULL;

  //
  //  check if the message beginning with " _ACK_ "
  //
  if (NULL == strstr (Message, " _ACK_ ")) {
    return FALSE;
  }
  //
  // pase P/F
  //
  Pointer = Message + strlen (" _ACK_ ");
  FILTER_SPACE (Pointer);
  if ((*Pointer == 'P') || (*Pointer == 'p')) {
    *Pass = TRUE;
  } else if ((*Pointer == 'F') || (*Pointer == 'f')) {
    *Pass = FALSE;
  } else {
    return FALSE;
  }
  //
  // parse _LOG_
  //
  Pointer = strstr (Message, " _LOG_ ");
  if (NULL != Pointer) {
    Pointer += strlen (" _LOG_ ");
    if (Pointer - Message >= (TLen - 1)) {
      *Log = NULL;
    } else {
      //
      // ignore the duplicate space
      //
      FILTER_SPACE (Pointer);
      *Log = Pointer;
      //
      // while ((*p!='\0') && (*p != ' ')) {
      //
      while ((*Pointer != '\0') && (strstr (Pointer, " _OUT_ ") != Pointer)) {
        Pointer++;
      }

      LogEnd = Pointer;
    }
  } else {
    *Log = NULL;
  }
  //
  // parse _OUT_
  //
  Pointer = strstr (Message, " _OUT_ ");
  if (NULL != Pointer) {
    Pointer += strlen (" _OUT_ ");
    if (Pointer - Message >= (TLen - 1)) {
      *Out = NULL;
    } else {
      //
      // ignore the duplicate space
      //
      FILTER_SPACE (Pointer);
      *Out = Pointer;
      //
      // while ((*p!='\0') && (*p != ' ')) {
      //
      while ((*Pointer != '\0') && (strstr (Pointer, " _LOG_ ") != Pointer)) {
        Pointer++;
      }

      OutEnd = Pointer;
    }
  } else {
    *Out = NULL;
  }

  if (OutEnd) {
    *OutEnd = 0;
  }

  if (LogEnd) {
    *LogEnd = 0;
  }

  return TRUE;
}
