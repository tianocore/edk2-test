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
  
    EmsTest.c
    
Abstract:

  Implementation of EMS Test functions

--*/

#include "EmsRpcEth.h"
#include "EmsLogUtility.h"
#include "EmsThread.h"
#include "EmsTest.h"
#include "EmsInterface.h"
#include "EmsRivlType.h"
#include "EmsRivlFunc.h"
#include "EmsRivlVar.h"
#include "EmsRivlTclVar.h"
#include "EmsPktCapture.h"
#include "EmsTclCleanup.h"
#include "EmsRivlNameScope.h"
#include "EmsTimer.h"
#include "EmsRpcEth.h"
#include "EmsRpcMain.h"


EmsThread       EmsGuiThreadCtl;

EmsThread       *EmsRunCaseThreadCtl = NULL;

STATIC HANDLE            RemoteValidationTestStartEvent;
STATIC VOLATILE BOOLEAN  RemoteExecutionRunningFlag;
STATIC VOLATILE BOOLEAN  RemoteValidationRunningFlag;
STATIC VOLATILE BOOLEAN  RemoteValidationStopFlag;

static struct   RemoteValidationTestCaseMng {
  TESTCASE_LIST_HEAD  CaseList;
  BOOLEAN             CaseAllPost;
  HANDLE              CaseListMutex;

  TESTCASE_LIST_HEAD  ContinueList;
  HANDLE              ContinueListMutex;

  TESTCASE_LIST_HEAD  TrashList;
  UINT32              TrashMaxNum;
  HANDLE              TrashListMutex;
} RemoteValidationTestCaseMng;

VOID EmsVTcpDestroyAllTcb(VOID);

VOID
EmsTestTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS test related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  Tcl_CreateCommand (
    Interp,
    "EmsTestInit",
    EmsTestInit,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "EmsTestCaseScriptEval",
    EmsTestCaseScriptEval,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "EmsRemoteValidationTestStop",
    EmsRemoteValidationTestStop,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "EmsTestIsRunning",
    EmsTestIsRunning,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "EmsRemoteValidationTestStart",
    EmsRemoteValidationTestStart,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "RemoteValidationTestCaseAllPost",
    RemoteValidationTestCaseAllPost,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "EmsRemoteValidationTestContinue",
    EmsRemoteValidationTestContinue,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  Tcl_CreateCommand (
    Interp,
    "EmsThreadCmd",
    EmsThreadCmd,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
}

STATIC
VOID
RemoteValidationTestCaseListAddEntry (
  TESTCASE_LIST_ENTRY *ListEntry
  )
/*++

Routine Description:

  Add an remote validataion case entry to test case list

Arguments:

  ListEntry - The case entry which will be added

Returns:

  None

--*/
{
  TESTCASE_LIST_HEAD  *pHead;
  pHead = NULL;
  pHead = &RemoteValidationTestCaseMng.CaseList;
  if (pHead->Head == NULL) {
    pHead->Head = ListEntry;
    pHead->Tail = ListEntry;
  } else {
    pHead->Tail->Next = ListEntry;
    ListEntry->Next   = NULL;
    pHead->Tail       = ListEntry;
  }

  pHead->EntryNum++;
}

STATIC
VOID
RemoteValidationTestCaseListGetEntry (
  TESTCASE_LIST_ENTRY **pListEntry
  )
/*++

Routine Description:

  Get an remote validataion case entry from test case list

Arguments:

  pListEntry  - the case entry's container

Returns:

  None

--*/
{
  TESTCASE_LIST_HEAD  *pHead;

  pHead       = NULL;

  pHead       = &RemoteValidationTestCaseMng.CaseList;
  *pListEntry = pHead->Head;
  if (pHead->Head != NULL) {
    if (pHead->Head == pHead->Tail) {
      pHead->Head = NULL;
      pHead->Tail = NULL;
    } else {
      pHead->Head = pHead->Head->Next;
    }

    pHead->EntryNum--;
  }
}

STATIC
VOID
RemoteValidationContinueList2TrashList (
  VOID
  )
/*++

Routine Description:

  convert the case's continue list to case's trash list

Arguments:

  None

Returns:

  None

--*/
{
  TESTCASE_LIST_HEAD  pHead;

  WaitForSingleObject (RemoteValidationTestCaseMng.ContinueListMutex, INFINITE);
  pHead = RemoteValidationTestCaseMng.ContinueList;
  RemoteValidationTestCaseMng.ContinueList.EntryNum = 0;
  RemoteValidationTestCaseMng.ContinueList.Head     = NULL;
  RemoteValidationTestCaseMng.ContinueList.Tail     = NULL;
  ReleaseMutex (RemoteValidationTestCaseMng.ContinueListMutex);

  WaitForSingleObject (RemoteValidationTestCaseMng.TrashListMutex, INFINITE);
  if (RemoteValidationTestCaseMng.TrashList.Head == NULL) {
    RemoteValidationTestCaseMng.TrashList.Head  = pHead.Head;
    RemoteValidationTestCaseMng.TrashList.Tail  = pHead.Tail;
  } else {
    if (pHead.Head != NULL) {
      RemoteValidationTestCaseMng.TrashList.Tail->Next  = pHead.Head;
      RemoteValidationTestCaseMng.TrashList.Tail        = pHead.Tail;
    }
  }

  RemoteValidationTestCaseMng.TrashList.EntryNum += pHead.EntryNum;
  ReleaseMutex (RemoteValidationTestCaseMng.TrashListMutex);
}

STATIC
VOID
RemoteValidationCaseList2ContinueList (
  VOID
  )
/*++

Routine Description:

  convert case list to continue list

Arguments:

  None

Returns:

  None

--*/
{
  TESTCASE_LIST_HEAD  pHead;

  WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
  pHead = RemoteValidationTestCaseMng.CaseList;
  RemoteValidationTestCaseMng.CaseList.EntryNum = 0;
  RemoteValidationTestCaseMng.CaseList.Head     = NULL;
  RemoteValidationTestCaseMng.CaseList.Tail     = NULL;
  ReleaseMutex (RemoteValidationTestCaseMng.CaseListMutex);

  WaitForSingleObject (RemoteValidationTestCaseMng.ContinueListMutex, INFINITE);
  if (RemoteValidationTestCaseMng.ContinueList.Head == NULL) {
    RemoteValidationTestCaseMng.ContinueList.Head = pHead.Head;
    RemoteValidationTestCaseMng.ContinueList.Tail = pHead.Tail;
  } else {
    if (pHead.Head != NULL) {
      RemoteValidationTestCaseMng.ContinueList.Tail->Next = pHead.Head;
      RemoteValidationTestCaseMng.ContinueList.Tail       = pHead.Tail;
    }
  }

  RemoteValidationTestCaseMng.ContinueList.EntryNum += pHead.EntryNum;
  ReleaseMutex (RemoteValidationTestCaseMng.ContinueListMutex);
}

STATIC
VOID
RemoteValidationContinueList2CaseList (
  VOID
  )
/*++

Routine Description:

  convert continue list to case list

Arguments:

  None

Returns:

  None

--*/
{
  TESTCASE_LIST_HEAD  pHead;

  WaitForSingleObject (RemoteValidationTestCaseMng.ContinueListMutex, INFINITE);
  pHead = RemoteValidationTestCaseMng.ContinueList;
  RemoteValidationTestCaseMng.ContinueList.EntryNum = 0;
  RemoteValidationTestCaseMng.ContinueList.Head     = NULL;
  RemoteValidationTestCaseMng.ContinueList.Tail     = NULL;
  ReleaseMutex (RemoteValidationTestCaseMng.ContinueListMutex);

  WaitForSingleObject (RemoteValidationTestCaseMng.TrashListMutex, INFINITE);
  if (RemoteValidationTestCaseMng.CaseList.Head == NULL) {
    RemoteValidationTestCaseMng.CaseList.Head = pHead.Head;
    RemoteValidationTestCaseMng.CaseList.Tail = pHead.Tail;
  } else {
    if (pHead.Head != NULL) {
      RemoteValidationTestCaseMng.CaseList.Tail->Next = pHead.Head;
      RemoteValidationTestCaseMng.CaseList.Tail       = pHead.Tail;
    }
  }

  RemoteValidationTestCaseMng.CaseList.EntryNum += pHead.EntryNum;
  ReleaseMutex (RemoteValidationTestCaseMng.TrashListMutex);
}

#define RemoteValidationTestCaseListIsEmpty() (RemoteValidationTestCaseMng.CaseList.EntryNum <= 0)

STATIC
VOID
RemoteValidationTestCaseTrashListAddTail (
  TESTCASE_LIST_ENTRY *Entry
  )
/*++

Routine Description:

  Add an entry to the tail of the remote validation case's trash list

Arguments:

  Entry - The entry will be added.

Returns:

  None

--*/
{
  TESTCASE_LIST_HEAD  *pHead;

  pHead = NULL;

  pHead = &RemoteValidationTestCaseMng.TrashList;
  if (pHead->Head == NULL) {
    pHead->Head = Entry;
    pHead->Tail = Entry;
  } else {
    pHead->Tail->Next = Entry;
    Entry->Next       = NULL;
    pHead->Tail       = Entry;
  }

  pHead->EntryNum++;
}

STATIC
TESTCASE_LIST_ENTRY *
RemoteValidationTestCaseTrashListDelHead (
  VOID
  )
/*++

Routine Description:

  Delete an entry from the head of the remote validation case's trash list.

Arguments:

  None

Returns:

  None

--*/
{
  TESTCASE_LIST_HEAD  *pHead;
  TESTCASE_LIST_ENTRY *Entry;

  pHead = NULL;
  Entry = NULL;

  pHead = &RemoteValidationTestCaseMng.TrashList;
  Entry = pHead->Head;
  if (pHead->Head != NULL) {
    if (pHead->Head == pHead->Tail) {
      pHead->Head = NULL;
      pHead->Tail = NULL;
    } else {
      pHead->Head = pHead->Head->Next;
    }

    pHead->EntryNum--;
  }

  return Entry;
}

#define RemoteValidationTestCaseTrashListIsEmpty()  (RemoteValidationTestCaseMng.TrashList.EntryNum == 0)

STATIC
TESTCASE_LIST_ENTRY *
RemoteValidationTestCaseEntryGet (
  VOID
  )
/*++

Routine Description:

  Get an entry and use it to be the new remote validation case.

Arguments:

  None

Returns:

  The pointer to the new case entry

--*/
{
  TESTCASE_LIST_ENTRY *Entry;
  Entry = NULL;

  WaitForSingleObject (RemoteValidationTestCaseMng.TrashListMutex, INFINITE);
  if (!RemoteValidationTestCaseTrashListIsEmpty ()) {
    Entry = RemoteValidationTestCaseTrashListDelHead ();
  }

  ReleaseMutex (RemoteValidationTestCaseMng.TrashListMutex);
  if (!(Entry = (TESTCASE_LIST_ENTRY *) malloc (sizeof (TESTCASE_LIST_ENTRY)))) {
    puts ("The System has not enough memory\n");
    return NULL;
  }

  memset (Entry, 0x0, sizeof (TESTCASE_LIST_ENTRY));
  return Entry;
}

STATIC
BOOLEAN
IsValidResult (
  INT8        *Path,
  EMS_PRIVATE *SavedResult
  )
/*++

Routine Description:

  estimate whether the case's result is valid

Arguments:

  Path        - The case's path name
  SavedResult - The case's saved result

Returns:

  TRUE or FALSE

--*/
{
  INT8  *TempIdx;
  INT8  *CaseName;
  INT8  ResultCaseName[64];

  TempIdx   = NULL;
  CaseName  = NULL;

  for (TempIdx = Path; TempIdx = strchr (TempIdx, '/');) {
    for (; *TempIdx == '/'; TempIdx++)
      ;
    CaseName = TempIdx;
  }

  sprintf (ResultCaseName, "%s.tcl", SavedResult->CaseName);
  return (_stricmp (CaseName, ResultCaseName) == 0);
}

STATIC
VOID
GetTestCaseResult (
  INT8          *Path,
  UINT8         Result[]
  )
/*++

Routine Description:

  Get the case's test result

Arguments:

  Path    - The path name of case
  Result  - The Result of case

Returns:

  None

--*/
{
  INT8        TempBuffer[16];
  EMS_PRIVATE SavedResult;

  GetTemporaryLogData (&SavedResult);

  memset (Result, 0x0, sizeof (Result));

  if (IsValidResult (Path, &SavedResult)) {
    sprintf (TempBuffer, "PASS(%d)  ", SavedResult.PassCount);
    strcat (Result, TempBuffer);
    sprintf (TempBuffer, "WARN(%d)  ", SavedResult.WarnCount);
    strcat (Result, TempBuffer);
    sprintf (TempBuffer, "FAIL(%d)", SavedResult.FailCount);
    strcat (Result, TempBuffer);
  } else {
    sprintf (Result, "Case Error");
  }
}

#define RemoteExecutionCmdBegin() (RemoteExecutionRunningFlag = TRUE)
#define RemoteExecutionCmdEnd()   (RemoteExecutionRunningFlag = FALSE)

STATIC
VOID
RemoteExecutionCmdTimeout (
  VOID *Arg
  )
/*++

Routine Description:

  The call back routine for remote execution command timeout

Arguments:

  Arg - The target thread will be cancelled.

Returns:

  None

--*/
{
  DWORD     Result;
  EmsThread *Thread;
  Thread = (EmsThread *) Arg;

  EmsThreadCancel (Thread, &Result);
  RemoteExecutionCmdEnd ();
}

STATIC
VOID
EmsThreadCmdEnd (
  VOID *Arg
  )
/*++

Routine Description:

  The routine of marking remote execution command finished

Arguments:

  Arg - the timer will be deleted.

Returns:

  None

--*/
{
  if (Arg != NULL) {
    EmsDelTimer ((EmsTimer *) Arg);
  }

  RemoteExecutionCmdEnd ();
}

STATIC
INT32
EmsThreadCmd (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsThreadCmd" implementation routine  

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
  EmsTimer  *Timer;
  INT32     Timeout;

  Thread  = NULL;
  Timer   = NULL;
  Timeout = 0;

  if (Argc != 3) {
    ThreadCommand (&EmsGuiThreadCtl, "EmsGuiError \"EmsThreadCmd parameter error\"", CMD_WAIT, NULL);
  }

  if ((Timeout = atoi (Argv[2])) >= 0) {
    Timer = EmsSetTimer (Timeout, RemoteExecutionCmdTimeout, Thread);

  }

  RemoteExecutionCmdBegin ();
  if (EFI_SUCCESS != EmsCreateThread (
                  &Thread,
                  EmsThreadCmdEnd,
                  Timer,
                  NULL,
                  Argv[1]
                  )) {
    printf ("EmsThreadCmd EmsCreateThread Error\n");
    return TCL_ERROR;
  }

  return TCL_OK;
}

STATIC
VOID
RemoteValidationCleanupHostTestEnv (
  VOID
  )
/*++

Routine Description:

  Cleanup the host environment for remote validation.

Arguments:

  None

Returns:

  None

--*/
{
  VifDownAll ();
  EmsCaptureEndAll ();
  EmsVTcpDestroyAllTcb ();

  EmsClearLocalScope ();
  RivlVariableDestroyAll ();
  RivlRemoveTclVarsAll (EmsThreadSelf ()->Interp);
  RivlTypeDestroyAll ();
  RivlFunctionRemoveAll ();
  EmsClearLog ();
  EmsThreadInterpReset (EmsTestInterpInit);
}

STATIC
VOID
RemoteValidationCleanupTargetTestEnv (
  VOID
  )
/*++

Routine Description:

  Cleanup the target machine environmnet for remote validation

Arguments:

  None

Returns:

  None

--*/
{
  INT8  TargetMac[6];

  GetEasMac (TargetMac);
  EmsTargetCleanup (TargetMac);
}

STATIC
VOID
RemoteValidationCleanupTestEnv (
  VOID
  )
/*++

Routine Description:

  Cleanup the host and target machine environment for remote validation

Arguments:

  None

Returns:

  None

--*/
{
  RemoteValidationCleanupHostTestEnv ();
  RemoteValidationCleanupTargetTestEnv ();
}

STATIC
VOID
RemoteValidationTestWaitBegin (
  VOID
  )
{
  WaitForSingleObject(RemoteValidationTestStartEvent, INFINITE);
  RemoteValidationCleanupTestEnv();
}

STATIC
VOID
RemoteValidationTestEnd (
  VOID
  )
{
  RemoteValidationCleanupTestEnv();
  RemoteValidationStopFlag    = TRUE;
  RemoteValidationRunningFlag = FALSE;
}

#define RemoteValidationTestSetStop()        (RemoteValidationStopFlag = TRUE)
#define RemoteValidationTestIsStop()         (RemoteValidationStopFlag)
#define RemoteValidationTestCaseIsAllPost()  (RemoteValidationTestCaseMng.CaseAllPost)

INT32
EmsRemoteValidationTestStart (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsRemoteValidationTestStart" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
{
  RemoteValidationRunningFlag = TRUE;
  RemoteValidationStopFlag    = FALSE;
  WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
  RemoteValidationTestCaseMng.CaseAllPost = FALSE;
  ReleaseMutex(RemoteValidationTestCaseMng.CaseListMutex);
  SetEvent (RemoteValidationTestStartEvent);
  return TCL_OK;
}

INT32
RemoteValidationTestCaseAllPost (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
{
  WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
  RemoteValidationTestCaseMng.CaseAllPost = TRUE;
  ReleaseMutex(RemoteValidationTestCaseMng.CaseListMutex);
  return TCL_OK;
}

INT32
EmsRemoteValidationTestStop (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsRemoteValidationTestStop" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
{
  RemoteValidationStopFlag = TRUE;
  return TCL_OK;
}

INT32
EmsRemoteValidationTestContinue (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsRemoteValidationTestContinue" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
{
  RemoteValidationRunningFlag = TRUE;
  RemoteValidationStopFlag    = FALSE;
  RemoteValidationContinueList2CaseList ();
  WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
  RemoteValidationTestCaseMng.CaseAllPost = TRUE;
  ReleaseMutex(RemoteValidationTestCaseMng.CaseListMutex);
  SetEvent (RemoteValidationTestStartEvent);
  return TCL_OK;
}

INT32
EmsTestIsRunning (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsTestIsRunning" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
{
  INT8  *Ret;
  Ret = (RemoteExecutionRunningFlag == TRUE || RemoteValidationRunningFlag == TRUE) ? "1" : "0";

  Tcl_AppendResult (
    Interp,
    Ret,
    (INT8 *) NULL
    );

  return TCL_OK;
}

STATIC
VOID
RemoteValidationOneCaseTestBegin (
  TESTCASE_LIST_ENTRY  *ListEntry
  )
/*++

Routine Description:

  Change the case status when one remote validation case begin

Arguments:

  ListEntry - The list node of remote validation case

Returns:

  None

--*/
{
  INT8  CmdString[256];

  sprintf (CmdString, "RemoteValidationSetResultBegin \"%s\"", ListEntry->CaseName);
  ThreadCommand (&EmsGuiThreadCtl, CmdString, CMD_NOWAIT, NULL);
  ThreadCommand (&EmsGuiThreadCtl, "update", CMD_NOWAIT, NULL);
}

STATIC
VOID
RemoteValidationOneCaseEval (
  TESTCASE_LIST_ENTRY  *ListEntry
  )
/*++

Routine Description:

  evaluate one remote validation test case

Arguments:

  ListEntry - The list node of remote validation case

Returns:

  None

--*/
{
  INT8       CmdString[256];
  Tcl_Interp *Interp;

  Interp = EmsThreadSelf()->Interp;
  sprintf (CmdString, "source %s", ListEntry->CasePath);
  if (TCL_OK != Tcl_Eval (Interp, CmdString)) {
    printf ("RemoteValidataionRunCaseThread Tcl_Eval case file :%s error\n", ListEntry->CasePath);
    Tcl_BackgroundError (Interp);
  }
}

STATIC
BOOLEAN
RemoteValidataionOneCaseTestEnd (
  TESTCASE_LIST_ENTRY  *ListEntry
  )
/*++

Routine Description:

  Change the case status when one remote validation case end

Arguments:

  ListEntry - The list node of remote validation case

Returns:

  TRUE - Case passed
  FAIL - Case failed

--*/
{
  INT8  CmdString[256];
  INT8  TestResult[32];

  GetTestCaseResult (ListEntry->CasePath, TestResult);
  sprintf (CmdString, "RemoteValidationSetResultEnd \"%s\" \"%s\"", ListEntry->CaseName, TestResult);
  ThreadCommand (&EmsGuiThreadCtl, CmdString, CMD_NOWAIT, NULL);
  ThreadCommand (&EmsGuiThreadCtl, "update", CMD_NOWAIT, NULL);

  if(strcmp(TestResult, "Case Error") == 0) {
  	return FALSE;
  } else {
    return TRUE;
  }
}

VOID
RemoteValidataionRunCaseThread (
  VOID *Arg
  )
/*++

Routine Description:

  The thread routine for running remote validation cases.

Arguments:

  Arg - The parameter of the thread routine

Returns:

  None

--*/
{
  TESTCASE_LIST_ENTRY *ListEntry;

  printf ("======Enter RemoteValidataionRunCaseThread======\n");

  while (TRUE) {
  	RemoteValidationTestWaitBegin();

    WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
    while((RemoteValidationTestCaseListIsEmpty() == FALSE) || 
          (RemoteValidationTestCaseIsAllPost()   == FALSE)) { 
      RemoteValidationTestCaseListGetEntry (&ListEntry);
      ReleaseMutex (RemoteValidationTestCaseMng.CaseListMutex);

      if (ListEntry != NULL) {
        RemoteValidationOneCaseTestBegin (ListEntry);
        RemoteValidationOneCaseEval (ListEntry);
        if (RemoteValidataionOneCaseTestEnd (ListEntry) == FALSE) {
          RemoteValidationTestSetStop();
        }
      } else {
        WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
        Tcl_Sleep(200);
        continue;
      }

      if (RemoteValidationTestIsStop ()) {
        RemoteValidationContinueList2TrashList ();
        RemoteValidationCaseList2ContinueList ();
      }

      WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
    }
    ReleaseMutex (RemoteValidationTestCaseMng.CaseListMutex);

    RemoteValidationTestEnd();
  }
}

STATIC
VOID *
RemoteValidationTestCaseMngCleanup (
  VOID *Arg
  )
/*++

Routine Description:

  The cleanup routine of remote validation cases management

Arguments:

  Arg - The parameter of the cleanup routine

Returns:

  NULL

--*/
{
  TESTCASE_LIST_ENTRY *CaseList;
  TESTCASE_LIST_ENTRY *ContinueList;
  TESTCASE_LIST_ENTRY *TrashList;
  TESTCASE_LIST_ENTRY *Node;
  INT                 Result;

  CaseList      = NULL;
  ContinueList  = NULL;
  TrashList     = NULL;
  Node          = NULL;

  printf ("======Enter RemoteValidationTestCaseMngCleanup\n");

  EmsThreadCancel (EmsRunCaseThreadCtl, &Result);

  WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
  CaseList  = RemoteValidationTestCaseMng.CaseList.Head;
  RemoteValidationTestCaseMng.CaseList.EntryNum = 0;
  RemoteValidationTestCaseMng.CaseList.Head = RemoteValidationTestCaseMng.CaseList.Tail = NULL;
  ReleaseMutex (RemoteValidationTestCaseMng.CaseListMutex);
  WaitForSingleObject (RemoteValidationTestCaseMng.ContinueListMutex, INFINITE);
  ContinueList  = RemoteValidationTestCaseMng.ContinueList.Head;
  RemoteValidationTestCaseMng.ContinueList.EntryNum = 0;
  RemoteValidationTestCaseMng.ContinueList.Head = RemoteValidationTestCaseMng.ContinueList.Tail = NULL;
  ReleaseMutex (RemoteValidationTestCaseMng.ContinueListMutex);
  WaitForSingleObject (RemoteValidationTestCaseMng.TrashListMutex, INFINITE);
  TrashList = RemoteValidationTestCaseMng.TrashList.Head;
  RemoteValidationTestCaseMng.TrashList.EntryNum  = 0;
  RemoteValidationTestCaseMng.TrashList.Head = RemoteValidationTestCaseMng.TrashList.Tail = NULL;
  ReleaseMutex (RemoteValidationTestCaseMng.TrashListMutex);

  while (CaseList) {
    Node      = CaseList;
    CaseList  = CaseList->Next;
    free (Node);
  }

  while (ContinueList) {
    Node          = ContinueList;
    ContinueList  = ContinueList->Next;
    free (Node);
  }

  while (TrashList) {
    Node      = TrashList;
    TrashList = TrashList->Next;
    free (Node);
  }

  printf ("======Exit RemoteValidationTestCaseMngCleanup\n");
  return NULL;
}

STATIC
INT32
EmsTestInit (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsTestInit" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  EmsTclResMng  *Res;

  Res = NULL;

  RemoteValidationTestCaseMng.CaseListMutex         = CreateMutex (NULL, FALSE, NULL);
  RemoteValidationTestCaseMng.ContinueListMutex     = CreateMutex (NULL, FALSE, NULL);
  RemoteValidationTestCaseMng.TrashListMutex        = CreateMutex (NULL, FALSE, NULL);
  RemoteValidationTestCaseMng.TrashMaxNum           = 128;
  RemoteValidationTestCaseMng.CaseAllPost           = FALSE;
  RemoteValidationTestCaseMng.CaseList.EntryNum     = 0;
  RemoteValidationTestCaseMng.CaseList.Head         = RemoteValidationTestCaseMng.CaseList.Tail = NULL;
  RemoteValidationTestCaseMng.TrashList.EntryNum    = 0;
  RemoteValidationTestCaseMng.TrashList.Head        = RemoteValidationTestCaseMng.TrashList.Tail = NULL;
  RemoteValidationTestCaseMng.ContinueList.EntryNum = 0;
  RemoteValidationTestCaseMng.ContinueList.Head     = RemoteValidationTestCaseMng.ContinueList.Tail = NULL;

  if (NULL == (Res = (EmsTclResMng *) malloc (sizeof (EmsTclResMng)))) {
    return TCL_ERROR;

  }

  RemoteValidationTestStartEvent = CreateEvent (0, FALSE, FALSE, NULL);
  RemoteExecutionRunningFlag     = FALSE;
  RemoteValidationRunningFlag    = FALSE;

  if (EFI_SUCCESS != EmsCreateThread (
                  &EmsRunCaseThreadCtl,
                  RemoteValidataionRunCaseThread,
                  NULL,
                  TestCaseInterp,
                  "source ./Script/ThreadInit.tcl"
                  )) {
    ThreadCommand (&EmsGuiThreadCtl, "EmsGuiError \"Can not create run case thread\"", CMD_WAIT, NULL);
    return TCL_ERROR;
  }

  Res->CleanupFunc  = RemoteValidationTestCaseMngCleanup;
  Res->Res          = NULL;
  EmsTclResStackPush (Res);

  return TCL_OK;
}

STATIC
INT32
EmsTestCaseScriptEval (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsTestCaseScriptEval" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  TESTCASE_LIST_ENTRY *ListEntry;

  if (Argc != 3) {
    return TCL_ERROR;

  }

  ListEntry = RemoteValidationTestCaseEntryGet ();
  strcpy (ListEntry->CasePath, Argv[1]);
  strcpy (ListEntry->CaseName, Argv[2]);
  WaitForSingleObject (RemoteValidationTestCaseMng.CaseListMutex, INFINITE);
  RemoteValidationTestCaseListAddEntry (ListEntry);
  ReleaseMutex (RemoteValidationTestCaseMng.CaseListMutex);

  return TCL_OK;
}
