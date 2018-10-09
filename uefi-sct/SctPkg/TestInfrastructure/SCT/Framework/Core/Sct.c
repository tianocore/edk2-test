/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Sct.c

Abstract:

  EFI SCT Framework

--*/

#include "Sct.h"

//
// Global veriables definition
//

EFI_SCT_FRAMEWORK_TABLE *gFT = NULL;

EFI_GUID gEfiSystemHangAssertionGuid = EFI_SYSTEM_HANG_ASSERTION_GUID;

UINTN gTestCaseMaxRunTimeMax = 0x7FFFFFFF;

BOOLEAN gForceExecution = FALSE;

//
// Internal functions declaration
//

VOID
PrintUsage (
  VOID
  );

EFI_STATUS
ParseCommandLine (
  IN EFI_HANDLE                   ImageHandle
  );

EFI_STATUS
SctMainFunc (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );

//
// Check MonitorName if it is Mnp, Ip4 or Serial
//
STATIC
EFI_STATUS
CheckMonitorName (
  CHAR16  *Argv
  );

//
// Entry point
//
EFI_STATUS
EFIAPI
InitializeSct (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
/*++

Routine Description:

  Entry point of SCT.

Arguments:

  ImageHandle   - The image handle.
  SystemTable   - The system table.

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;
  EFI_TPL     OldTPL;

  //
  // Initialize libraries
  //
  SctShellApplicationInit (ImageHandle, SystemTable);

  OldTPL = tBS->RaiseTPL (TPL_HIGH_LEVEL);
  if(OldTPL != TPL_APPLICATION) {
    tBS->RestoreTPL(OldTPL);
    SctPrint(L"ERROR: SCT should run at TPL_APPLICATION level\n");
    return EFI_SUCCESS;
  }
  tBS->RestoreTPL(OldTPL);

  //
  // Initialize the framework table
  //
  Status = InitializeFrameworkTable (ImageHandle, SystemTable);
  if (EFI_ERROR (Status)) {
    SctPrint (L"ERROR: Cannot initialize the framework table. Status - %r\n", Status);
    return Status;
  }

  //
  // Initialize EfiInitializeEntsLib.
  //
  EfiInitializeEntsLib (ImageHandle, SystemTable);

  //
  // Parse the command line
  //
  Status = ParseCommandLine (ImageHandle);
  if (EFI_ERROR (Status)) {
    SctPrint (L"ERROR: Invalid command line. Status - %r\n", Status);
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Invoke the SCT main function to do the operations
  //
  Status = SctMainFunc (ImageHandle, SystemTable);
  if (EFI_ERROR (Status)) {
    SctPrint (L"ERROR: Cannot do the operations. Status - %r\n", Status);
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Free the framework table
  //
  Status = FreeFrameworkTable ();
  if (EFI_ERROR (Status)) {
    SctPrint (L"ERROR: Cannot free the framework table. Status - %r\n", Status);
    return Status;
  }

  //
  // Done
  //
  SctPrint (L"Done!\n");
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

VOID
PrintUsage (
  VOID
  )
/*++

Routine Description:

  Print out the usage model of the SCT.

--*/
{
  SctPrint (
    L"%s\n"
    L"\n"
    L"usage:\n"
    L"%s [-a | -c | -s <seq> | -u | -p <MNP | IP4 | SERIAL>] [-r] [-g <report>][-v]\n"
    L"\n"
    L"  -a    Executes all test cases.\n"
    L"  -c    Continues execute the test cases.\n"
    L"  -g    Generates test report.\n"
    L"  -p    Passive Mode with specified communication layer\n"
    L"  -r    Resets all test results.\n"
    L"  -s    Executes the test cases in the test sequence file.\n"
    L"  -u    Turns into user-friendly interface.\n"
    L"  -f    Force the operation execution, no confirmation from user.\n"
    L"  -v    Verbose function to disable screen output.\n"
    L"\n",
    EFI_SCT_NAME,
    EFI_SCT_SHORT_NAME
    );
}

STATIC UINT32 SCT_VALID_OPERATIONS[] = {
  EFI_SCT_OPERATIONS_NONE,                                                                    // sct -h | sct -?
  EFI_SCT_OPERATIONS_ALL,                                                                     // sct -a
  EFI_SCT_OPERATIONS_ALL | EFI_SCT_OPERATIONS_VERBOSE,                                        // sct -a -v
  EFI_SCT_OPERATIONS_RESET,                                                                   // sct -r
  EFI_SCT_OPERATIONS_ALL | EFI_SCT_OPERATIONS_RESET,                                          // sct -r -a
  EFI_SCT_OPERATIONS_ALL | EFI_SCT_OPERATIONS_RESET | EFI_SCT_OPERATIONS_VERBOSE,             // sct -r -a -v
  EFI_SCT_OPERATIONS_CONTINUE,                                                                // sct -c
  EFI_SCT_OPERATIONS_CONTINUE | EFI_SCT_OPERATIONS_VERBOSE,                                   // sct -c -v
  EFI_SCT_OPERATIONS_REPORT,                                                                  // sct -g
  EFI_SCT_OPERATIONS_SEQUENCE,                                                                // sct -s
  EFI_SCT_OPERATIONS_SEQUENCE | EFI_SCT_OPERATIONS_VERBOSE,                                   // sct -s -v
  EFI_SCT_OPERATIONS_UI,                                                                      // sct -u
  EFI_SCT_OPERATIONS_RESET | EFI_SCT_OPERATIONS_UI,                                           // sct -r -u
  EFI_SCT_OPERATIONS_PASSIVEMODE,                                                             // sct -p
  EFI_SCT_OPERATIONS_PASSIVEMODE | EFI_SCT_OPERATIONS_VERBOSE,                                // sct -p -r
  EFI_SCT_OPERATIONS_PASSIVEMODE | EFI_SCT_OPERATIONS_SEQUENCE,                               // sct -s -p
  EFI_SCT_OPERATIONS_PASSIVEMODE | EFI_SCT_OPERATIONS_SEQUENCE | EFI_SCT_OPERATIONS_VERBOSE,  // sct -s -p -r
  EFI_SCT_OPERATIONS_PASSIVEMODE | EFI_SCT_OPERATIONS_CONTINUE,                               // sct -c -p
  EFI_SCT_OPERATIONS_PASSIVEMODE | EFI_SCT_OPERATIONS_CONTINUE | EFI_SCT_OPERATIONS_VERBOSE,  // sct -c -p -r
  EFI_SCT_OPERATIONS_REPORT | EFI_SCT_OPERATIONS_PASSIVEMODE,                                 // sct -g -p
  EFI_SCT_OPERATIONS_EXTENDED,                                                                // sct -x omit
  EFI_SCT_OPERATIONS_INVALID                                                                  // invalid end of table
};

STATIC
VOID
SctCmdLineGetMonitorName (
  IN CHAR16                       *ArgStr
  )
{
  EFI_STATUS                      Status;

  Status = CheckMonitorName(ArgStr);
  if (!EFI_ERROR (Status)) {
    gFT->MonitorName = ArgStr;
  } else {
    gFT->MonitorName = NULL;
  }
}

STATIC
EFI_STATUS
SctCmdLineGetFileName (
  IN  CHAR16    *Directory,
  IN  CHAR16    *ArgStr,
  OUT CHAR16   **Path
  )
{
  *Path = SctPoolPrint (L"%s\\%s\\%s", gFT->FilePath, Directory, ArgStr);
  if (*Path == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  return EFI_SUCCESS;
}

#define SCT_OPERATION_MASK(OP)    (gFT->Operations |= (OP))
#define SCT_OPERATION_EQU(OP)     (gFT->Operations == (OP))

EFI_STATUS
ParseCommandLine (
  IN EFI_HANDLE                   ImageHandle
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINTN       Argc;
  CHAR16      **Argv;

  //
  // Get the parameters from the shell interface
  //
  SctShellGetArguments (&Argc, &Argv);

  gFT->Operations = 0;

  for (Index = 1; Index < Argc; Index++) {
    if (Argv[Index][0] == L'-' && Argv[Index][2] == L'\0') {
      switch(Argv[Index][1]) {
      case L'a': case L'A':
        SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_ALL);
        break;
      case L'c': case L'C':
        SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_CONTINUE);
		break;
      case L'g': case L'G':
        SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_REPORT);
        Index++;
        if (Index == Argc) {
          EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"Not set the report file name"));
          return EFI_NOT_FOUND;
        }
        Status = SctCmdLineGetFileName(EFI_SCT_PATH_REPORT, Argv[Index], &gFT->RepFileName);
        if (EFI_ERROR(Status)) {
          EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"Get report file name fail - %r", Status));
          return Status;
        }
		break;
      case L'p': case L'P':
        SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_PASSIVEMODE);
        Index++;
        if (Index == Argc) {
          EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"Not set the monitor name"));
          return EFI_INVALID_PARAMETER;
        } else {
          SctCmdLineGetMonitorName(Argv[Index]);
        }
        break;
      case L'r': case L'R':
        SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_RESET);
        break;
      case L's': case L'S':
        SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_SEQUENCE);
        Index++;
        if (Index == Argc) {
          EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"Not set the sequence file name"));
          return EFI_NOT_FOUND;
        }
        Status = SctCmdLineGetFileName(EFI_SCT_PATH_SEQUENCE, Argv[Index], &gFT->SeqFileName);
        if (EFI_ERROR(Status)) {
          EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"get sequence file name fail - %r", Status));
          return Status;
        }
        break;
      case L'u': case L'U':
	  	SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_UI);
        break;
      case L'x': case L'X':
        SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_EXTENDED);
        break;
      case L'f': case L'F':
        gForceExecution = TRUE;
        break;
      case L'v': case L'V':
      	 SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_VERBOSE);
      	 break;
      case L'h': case L'H': case L'?':
        SCT_OPERATION_MASK(EFI_SCT_OPERATIONS_NONE);
        return EFI_SUCCESS;;
      default:
        return EFI_INVALID_PARAMETER;
      }
    } else {
      return EFI_INVALID_PARAMETER;
    }
  }

  Status = EFI_INVALID_PARAMETER;
  for(Index = 0; SCT_VALID_OPERATIONS[Index] != EFI_SCT_OPERATIONS_INVALID; Index++) {
    if (SCT_OPERATION_EQU(SCT_VALID_OPERATIONS[Index])) {
      Status = EFI_SUCCESS;
      break;
    }
  }

  return Status;
}

EFI_STATUS
SctMainFunc (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
/*++

Routine Description:

  The main routine of SCT.

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Check the operations
  //
  if (gFT->Operations == EFI_SCT_OPERATIONS_NONE) {
    //
    // No operation. Print out the help information
    //
    PrintUsage ();
    return EFI_SUCCESS;
  }

  //
  // If EFI_SCT_OPERATIONS_PASSIVEMODE unmasked then delete the passive test context 
  //
  if ((gFT->Operations & EFI_SCT_OPERATIONS_PASSIVEMODE) == 0) {
    PassiveTestContextDelete(gFT->DevicePath, SCT_PASSIVE_MODE_RECORD_FILE);
  }

  //
  // Attach the first stage test data (before the test files are loaded)
  //
  Status = AttachFirstStageTestData ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach first stage test data - %r", Status));
    return Status;
  }

  //
  // Do the first stage operations (before the test files are loaded)
  //
  Status = DoFirstStageOperations ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"First stage operations - %r", Status));
    return Status;
  }

  //
  // Attach the second stage test data (after the test files are loaded)
  //
  Status = AttachSecondStageTestData ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach second stage test data - %r", Status));
    return Status;
  }

  //
  // Do the second stage operations (after the test files are loaded)
  //
  Status = DoSecondStageOperations ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Second stage operations - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
CheckMonitorName (
  CHAR16  *Argv
  )
{
//  CHAR16 *Temp;
//  Temp = UpperCaseString(Argv);

  if ((SctStrCmp (Argv, L"MNP") == 0) || (SctStrCmp(Argv, L"mnp") == 0))
  	return EFI_SUCCESS;
  if ((SctStrCmp (Argv, L"IP4") == 0) || (SctStrCmp(Argv, L"ip4") == 0))
  	return EFI_SUCCESS;
  if ((SctStrCmp (Argv, L"SERIAL") == 0) || (SctStrCmp(Argv, L"serial") == 0))
  	return EFI_SUCCESS;  

  return EFI_INVALID_PARAMETER;
}

