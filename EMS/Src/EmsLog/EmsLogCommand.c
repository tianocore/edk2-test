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
  
    EmsLogCommand.c
    
Abstract:

    Implementation for Log related TCL commands

--*/

#include "EmsLogCommand.h"
#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsLogUtility.h"
#include "EmsLogReport.h"
#include "EmsThread.h"

INT8                    CaseName[256];
INT8                    CaseCategory[256];
INT8                    CaseDescription[2048];

extern EmsThread        EmsGuiThreadCtl;

#define EMS_DEFAULT_CASE_GUID \
  { \
    0x12345687, 0x1234, 0x1234, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12 \
  }

STATIC Tcl_CmdProc      TclCaseName;
STATIC Tcl_CmdProc      TclCaseCategory;
STATIC Tcl_CmdProc      TclCaseDescription;
STATIC Tcl_CmdProc      TclCaseLevel;
STATIC Tcl_CmdProc      TclCaseAttribute;
STATIC Tcl_CmdProc      TclCaseVerboseLevel;
STATIC Tcl_CmdProc      TclCaseGuid;
STATIC Tcl_CmdProc      TclBeginLog;
STATIC Tcl_CmdProc      TclEndLog;
STATIC Tcl_CmdProc      TclRecordMessage;
STATIC Tcl_CmdProc      TclRecordAssertion;
STATIC Tcl_CmdProc      TclGenerateReport;
STATIC Tcl_CmdProc      TclSetOutput;
STATIC Tcl_CmdProc      TclBeginLogPacket;
STATIC Tcl_CmdProc      TclEndLogPacket;
STATIC Tcl_CmdProc      TclSendLogFilePacket;
STATIC Tcl_CmdProc      TclResendCapturedPacket;

STATIC TCL_CMD_TBL      TclCmd[] = {
  {
    "BeginLog",
    TclBeginLog
  },
  {
    "EndLog",
    TclEndLog
  },
  {
    "CaseName",
    TclCaseName
  },
  {
    "CaseCategory",
    TclCaseCategory
  },
  {
    "CaseDescription",
    TclCaseDescription
  },
  {
    "CaseLevel",
    TclCaseLevel
  },
  {
    "CaseAttribute",
    TclCaseAttribute
  },
  {
    "CaseVerboseLevel",
    TclCaseVerboseLevel
  },
  {
    "CaseGuid",
    TclCaseGuid
  },
  {
    "RecordMessage",
    TclRecordMessage
  },
  {
    "RecordAssertion",
    TclRecordAssertion
  },
  {
    "GenerateReport",
    TclGenerateReport
  },
  {
    "SetOutput",
    TclSetOutput
  },
  {
    "BeginLogPacket",
    TclBeginLogPacket
  },
  {
    "EndLogPacket",
    TclEndLogPacket
  },
  {
    "SendLogFilePacket",
    TclSendLogFilePacket
  },
  {
    "ResendCapturedPacket",
    TclResendCapturedPacket
  },
  {
    NULL,
    NULL
  }
};

STATIC EMS_CASE_CONFIG  CurrentConfig = {
  DEFAULT_CASE_NAME,
  DEFAULT_CASE_CATEGORY,
  DEFAULT_CASE_DESCRIPTION,
  EMS_DEFAULT_CASE_INDEX,
  EMS_TEST_LEVEL_DEFAULT,
  EMS_CASE_ATTRIBUTE_AUTO,
  EMS_VERBOSE_LEVEL_DEFAULT,
  EMS_DEFAULT_CASE_GUID
};

struct _LEVELS {
  INT8          *Name;
  EmsTestLevel  Value;
}
Levels[] = {
  {
    "Conformance",
    EMS_TEST_LEVEL_MINIMAL
  },
  {
    "Function",
    EMS_TEST_LEVEL_DEFAULT
  },
  {
    "Stress",
    EMS_TEST_LEVEL_EXHAUSTIVE
  },
  {
    NULL
  }
};

struct _ATTRIBUTE {
  INT8              *Name;
  EmsCaseAttribute  Value;
}
Attribs[] = {
  {
    "Auto",
    EMS_CASE_ATTRIBUTE_AUTO
  },
  {
    "Manual",
    EMS_CASE_ATTRIBUTE_MANUAL
  },
  {
    NULL
  }
};

struct _VERBOSELEVEL {
  INT8            *Name;
  EmsVerboseLevel Value;
}
VerboseLevels[] = {
  {
    "Quiet",
    EMS_VERBOSE_LEVEL_QUIET
  },
  {
    "Minimal",
    EMS_VERBOSE_LEVEL_MINIMAL
  },
  {
    "Default",
    EMS_VERBOSE_LEVEL_DEFAULT
  },
  {
    "Noisy",
    EMS_VERBOSE_LEVEL_NOISY
  },
  {
    "Exhaustive",
    EMS_VERBOSE_LEVEL_EXHAUSTIVE
  },
  {
    NULL
  }
};

struct _ASSERTION {
  INT8              *Name;
  EmsTestAssertion  Value;
}
Assertions[] = {
  {
    "Pass",
    EMS_TEST_ASSERTION_PASSED
  },
  {
    "Fail",
    EMS_TEST_ASSERTION_FAILED
  },
  {
    "Warn",
    EMS_TEST_ASSERTION_WARNING
  },
  {
    NULL
  }
};

//
// A TCL command to output the Log information to screen
//
#define EMSOUTPUTCMDLEN	0x200
STATIC INT8  EmsOutputCmd[EMSOUTPUTCMDLEN + 1] = {0, };
STATIC INT8  EmsOutputStr[EMSOUTPUTCMDLEN + EMS_MAX_PRINT_BUFFER + 1] = {0, };

VOID_P
LogTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Ems Log related TCL initialization.

Arguments:

  Interp  - Tcl Interpreter.

Returns:

  None.

--*/
{
  INT32 Index;
  //
  // Create Packet related TCL commands
  //
  for (Index = 0; TclCmd[Index].Cmd; Index++) {
    Tcl_CreateCommand (
      Interp,
      TclCmd[Index].Cmd,
      TclCmd[Index].Proc,
      (ClientData) NULL,
      (Tcl_CmdDeleteProc *) NULL
      );
  }
}

STATIC
INT32
TclBeginLog (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "BeginLog" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
{
  SetConfig (CurrentConfig);
  return BeginLogging ();
}

STATIC
INT32
TclEndLog (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "EndLog" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
{
  EndLogging (EFI_SUCCESS);
  Tcl_AppendResult (
    Interp,
    (INT8 *) NULL
    );
  return TCL_OK;
}

STATIC
INT32
TclCaseName (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "CaseName" implementation routine

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
  if (Argc == 1) {
    Tcl_AppendResult (
      Interp,
      CurrentConfig.CaseName,
      (INT8 *) NULL
      );
    return TCL_OK;
  }

  CaseName[0] = '\0';
  strcat (CaseName, Argv[1]);

  for (Index = 2; Index < Argc; Index++) {
    strcat (CaseName, " ");
    strcat (CaseName, Argv[Index]);
  }

  CurrentConfig.CaseName = CaseName;

  return TCL_OK;
}

STATIC
INT32
TclCaseCategory (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "CaseCategory" implementation routine

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
  if (Argc == 1) {
    Tcl_AppendResult (
      Interp,
      CurrentConfig.CaseCategory,
      (INT8 *) NULL
      );
    return TCL_OK;
  }

  CaseCategory[0] = '\0';
  strcat (CaseCategory, Argv[1]);

  for (Index = 2; Index < Argc; Index++) {
    strcat (CaseCategory, " ");
    strcat (CaseCategory, Argv[Index]);
  }

  CurrentConfig.CaseCategory = CaseCategory;
  return TCL_OK;
}

STATIC
INT32
TclCaseDescription (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "CaseDescription" implementation routine

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
  if (Argc == 1) {
    Tcl_AppendResult (
      Interp,
      CurrentConfig.CaseDescription,
      (INT8 *) NULL
      );
    return TCL_OK;
  }

  CaseDescription[0] = '\0';
  strcat (CaseDescription, Argv[1]);

  for (Index = 2; Index < Argc; Index++) {
    strcat (CaseDescription, " ");
    strcat (CaseDescription, Argv[Index]);
  }

  CurrentConfig.CaseDescription = CaseDescription;

  return TCL_OK;
}

STATIC
INT32
TclCaseGuid (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "CaseGuid" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  Log[100];

  if (Argc == 1) {
    Sprint (Log, 100, "%g", &CurrentConfig.Guid);
    Tcl_AppendResult (
      Interp,
      Log,
      (INT8 *) NULL
      );
    return TCL_OK;
  }

  if (StrToGuid ((INT8 *) Argv[1], &CurrentConfig.Guid) < 0) {
    Tcl_AppendResult (
      Interp,
      "Error GUID Format",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }

  return TCL_OK;
}

STATIC
INT32
TclCaseLevel (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "CaseLevel" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  UINT32  Index;

  if (Argc == 1) {
    for (Index = 0; Levels[Index].Name; Index++) {
      if (Levels[Index].Value == CurrentConfig.TestLevel) {
        Tcl_AppendResult (
          Interp,
          Levels[Index].Name,
          (INT8 *) NULL
          );
        return TCL_OK;
      }
    }
  }

  for (Index = 0; Levels[Index].Name; Index++) {
    if (0 == strcmp_i (Levels[Index].Name, (INT8 *) Argv[1])) {
      CurrentConfig.TestLevel = Levels[Index].Value;
      return TCL_OK;
    }
  }

  Tcl_AppendResult (
    Interp,
    "The level MUST be one of : CONFORMANCE, FUNCTION, STRESS",
    (INT8 *) NULL
    );

  return TCL_ERROR;
}

STATIC
INT32
TclCaseAttribute (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "CaseAttribute" implementation routine

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

  if (Argc == 1) {
    for (Index = 0; Attribs[Index].Name; Index++) {
      if (Attribs[Index].Value == CurrentConfig.CaseAttribute) {
        Tcl_AppendResult (
          Interp,
          Attribs[Index].Name,
          (INT8 *) NULL
          );
        return TCL_OK;
      }
    }
  }

  for (Index = 0; Attribs[Index].Name; Index++) {
    if (0 == strcmp_i (Attribs[Index].Name, (INT8 *) Argv[1])) {
      CurrentConfig.CaseAttribute = Attribs[Index].Value;
      return TCL_OK;
    }
  }

  Tcl_AppendResult (
    Interp,
    "The attribute MUST be one of : AUTO, MANUAL.",
    (INT8 *) NULL
    );

  return TCL_ERROR;
}

STATIC
INT32
TclCaseVerboseLevel (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "CaseVerboseLevel" implementation routine

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

  if (Argc == 1) {
    for (Index = 0; VerboseLevels[Index].Name; Index++) {
      if (VerboseLevels[Index].Value == CurrentConfig.VerboseLevel) {
        Tcl_AppendResult (
          Interp,
          VerboseLevels[Index].Name,
          (INT8 *) NULL
          );
        return TCL_OK;
      }
    }
  }

  for (Index = 0; VerboseLevels[Index].Name; Index++) {
    if (0 == strcmp_i (VerboseLevels[Index].Name, (INT8 *) Argv[1])) {
      CurrentConfig.VerboseLevel = VerboseLevels[Index].Value;
      return TCL_OK;
    }
  }

  Tcl_AppendResult (
    Interp,
    "The verbose level MUST be one of : QUIET, MINIMAL, ",
    "DEFAULT, NOISY, EXHAUSTIVE",
    (INT8 *) NULL
    );

  return TCL_ERROR;
}

STATIC
INT32
TclRecordMessage (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "RecordMessage" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT32           Index;
  INT8            Log[1024];
  EmsVerboseLevel l;
  if (Argc == 1) {
    Tcl_AppendResult (
      Interp,
      "recordmessage: recordmessage LEVEL Informations... ",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  for (Index = 0; VerboseLevels[Index].Name; Index++) {
    if (0 == strcmp_i (VerboseLevels[Index].Name, (INT8 *) Argv[1])) {
      l = VerboseLevels[Index].Value;
      break;
    }
  }

  if (NULL == VerboseLevels[Index].Name) {
    Tcl_AppendResult (
      Interp,
      "The verbose level MUST be one of : QUIET, MINIMAL, ",
      "DEFAULT, NOISY, EXHAUSTIVE",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  Log[0] = '\0';
  for (Index = 2; Index < Argc; Index++) {
    strcat (Log, (INT8 *) Argv[Index]);
    strcat (Log, " ");
  }

  RecordMessage (l, Log);
  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclRecordAssertion (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "RecordAssertion" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT32             Index;
  INT8              Log[1024];
  EmsTestAssertion  a;
  EFI_GUID          temp_guid;

  if (Argc < 3) {
    Tcl_AppendResult (
      Interp,
      "recordassertion: recordassertion RESULT DESCRIPTION Informations... ",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  for (Index = 0; Assertions[Index].Name; Index++) {
    if (0 == strcmp_i (Assertions[Index].Name, (INT8 *) Argv[1])) {
      a = Assertions[Index].Value;
      break;
    }
  }

  if (NULL == Assertions[Index].Name) {
    Tcl_AppendResult (
      Interp,
      "recordassertion: 1st argument MUST be one of ",
      "PASS, FAIL, WARN",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (StrToGuid ((INT8 *) Argv[2], &temp_guid) > 0) {
    Tcl_AppendResult (
      Interp,
      "Error GUID Format",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  Log[0] = '\0';
  for (Index = 4; Index < Argc; Index++) {
    strcat (Log, Argv[Index]);
    strcat (Log, " ");
  }
  //
  // add a CurrentConfig.guid item
  //
  RecordAssertion (a, (INT8 *) Argv[2], (INT8 *) Argv[3], Log);

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclGenerateReport (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "GenerateReport" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  FileAssertion[1024];
  INT8  FileCase[1024];

  if (Argc == 1) {
    Tcl_AppendResult (
      Interp,
      "generatereport: generatereport FILENAME ",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }

  FileAssertion[0]  = '\0';
  FileCase[0]       = '\0';

  strcat (FileAssertion, (INT8 *) Argv[1]);
  strcat (FileCase, (INT8 *) Argv[1]);
  strcat (FileAssertion, "_assertion.csv");
  strcat (FileCase, "_case.csv");
  GenerateReport (FileAssertion);
  GenerateReportCase (FileCase);

  return TCL_OK;
}

VOID_P
LogCurrentCommand (
  IN INT32          Argc,
  IN CONST84 INT8   *Argv[]
  )
/*++

Routine Description:

  Log the argumems into runtime information.

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  None.

--*/
{
  INT32 Index;
  INT8  Log[1024];
  INT32 Length;
  INT32 DotCnt;

  Length  = 0;
  DotCnt  = 0;
  Log[0]  = '\0';
  for (Index = 0; Index < Argc; Index++) {
    if (Length + strlen (Argv[Index]) > 512) {
      while ((Length < 512) && (DotCnt < 6)) {
        strcat (Log, ".");
        Length++;
        DotCnt++;
      }
      break;
    }

    strcat (Log, Argv[Index]);
    strcat (Log, " ");
    Length += strlen (Argv[Index]);
  }

  RecordMessage (
    EMS_VERBOSE_LEVEL_DEFAULT,
    "EMS: execute \"%a\"",
    Log
    );

  return ;
}

STATIC
INT32
TclSetOutput (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "SetOutPut" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[100];

  if (Argc == 1) {
    sprintf (ErrorBuff, "%s: Please specify the output command\n", Argv[0]);
    goto ErrorExit;
  }

  if (strlen(Argv[1]) > EMSOUTPUTCMDLEN) {
    sprintf (ErrorBuff, "The output command is too long\n");
    goto ErrorExit;
  }

  strcpy(EmsOutputCmd, Argv[1]);
  Tcl_AppendResult (Interp, (INT8 *) NULL);
  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
Output2Screen (
  IN INT8 *Str
  )
/*++

Routine Description:

  Oupput the string to screen, using specified Tcl command

Arguments:

  Str - String to be output.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  if (NULL == EmsOutputCmd) {
    return printf ("%s", Str);
  }

  sprintf (EmsOutputStr, "%s {%s}", EmsOutputCmd, Str);
  ThreadCommand(&EmsGuiThreadCtl, EmsOutputStr, CMD_NOWAIT, NULL);
  ThreadCommand(&EmsGuiThreadCtl, "update", CMD_NOWAIT, NULL);

  return strlen(Str);
}

STATIC
INT32
TclBeginLogPacket (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "BeginLogPacket" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  if (Argc != 3) {
    Tcl_AppendResult (
      Interp,
      "BeginLogPacket: BeginLogPacket <FileName> <Filter>",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  SetConfig (CurrentConfig);
  if (EFI_SUCCESS != BeginPacketLogging (Argv[1], Argv[2])) {
    goto ErrorExit;
  };
  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclEndLogPacket (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "EndLogPacket" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  EndPacketLogging ();
  Tcl_AppendResult (
    Interp,
    (INT8 *) NULL
    );

  return TCL_OK;
}

STATIC
INT32
TclSendLogFilePacket (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "tcl_send_log_file_packet" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  if (Argc != 2) {
    Tcl_AppendResult (
      Interp,
      "SendLogFilePacket: SendLogFilePacket <FileName>",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  SetConfig (CurrentConfig);
  if (EFI_SUCCESS != LoggingPacketProcess (Argv[1])) {
    goto ErrorExit;
  };
  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclResendCapturedPacket (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "tcl_resend_captured_packet" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  UINT32  Timeout;
  UINT32  Count;
  UINT32  Interval;

  Count = 1;
  if (Argc < 4 || Argc > 5) {
    Tcl_AppendResult (
      Interp,
      "ResendCapturedPacket: ResendCapturedPacket <Filter> <Timeout> <Interval> <Count>\n",
      "          <Filter>   - Same Format as Ethreal.\n",
      "          <Timeout>  - total capture Time period(s).\n",
      "          <Interval> - Time Interval(ms) between each capture.\n",
      "          <Count>    - resending counts for captured packets, default is 1.\n",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (AsciiStringToUint32 ((INT8 *) Argv[2], &Timeout) <= 0) {
    Tcl_AppendResult (
      Interp,
      "ResendCapturedPacket: Timeout Value is incorrect.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if ((AsciiStringToUint32 ((INT8 *) Argv[3], &Interval) < 0)) {
    Tcl_AppendResult (
      Interp,
      "ResendCapturedPacket: Interval Value is incorrect.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (Argc == 5) {
    if ((AsciiStringToUint32 ((INT8 *) Argv[4], &Count) <= 0) || (Count >= 64)) {
      Tcl_AppendResult (
        Interp,
        "ResendCapturedPacket: Count is incorrect, Value should be < 64, default is 1.",
        (INT8 *) NULL
        );
      goto ErrorExit;
    }
  }

  SetConfig (CurrentConfig);
  if (EFI_SUCCESS != ProcessCapturedPacket (Argv[1], Timeout, Interval, (UINT8) Count)) {
    goto ErrorExit;
  }

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}
