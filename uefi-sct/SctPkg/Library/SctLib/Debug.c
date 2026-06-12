/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Debug.c

Abstract:

  Support for Debug primatives.

--*/

#include "SctLibInternal.h"

#include EFI_GUID_DEFINITION (GlobalVariable)

#define MAX_DEBUG_MESSAGE_LENGTH 0x1000

//
// EfiDebugMask - Debug mask
//
UINTN    EfiDebugMask    = EFI_DBUG_MASK;

/**
  Prints an assert message containing a filename, line number, and description.
  This may be followed by a breakpoint or a dead loop.

  Print a message of the form "ASSERT <FileName>(<LineNumber>): <Description>\n"
  to the debug output device.  If DEBUG_PROPERTY_ASSERT_BREAKPOINT_ENABLED bit of
  PcdDebugProperyMask is set then CpuBreakpoint() is called. Otherwise, if
  DEBUG_PROPERTY_ASSERT_DEADLOOP_ENABLED bit of PcdDebugProperyMask is set then
  CpuDeadLoop() is called.  If neither of these bits are set, then this function
  returns immediately after the message is printed to the debug output device.
  DebugAssert() must actively prevent recursion.  If DebugAssert() is called while
  processing another DebugAssert(), then DebugAssert() must return immediately.

  If FileName is NULL, then a <FileName> string of "(NULL) Filename" is printed.
  If Description is NULL, then a <Description> string of "(NULL) Description" is printed.

  @param  FileName     The pointer to the name of the source file that generated
                       the assert condition.
  @param  LineNumber   The line number in the source file that generated the
                       assert condition
  @param  Description  The pointer to the description of the assert condition.

**/
VOID
EfiDebugAssert (
  IN CHAR8  *FileName,
  IN INTN   LineNumber,
  IN CHAR8  *Description
  )
{
  CHAR16  Buffer[MAX_DEBUG_MESSAGE_LENGTH];

  //
  // Generate the ASSERT() message in Unicode format
  //
  SctSPrint (
    Buffer,
    sizeof (Buffer),
    L"ASSERT %a(%d): %a\n",
    FileName,
    LineNumber,
    Description
    );

  //
  // Send the print string to the Standard Error device
  //
  if ((tST != NULL) && (tST->StdErr != NULL)) {
    tST->StdErr->OutputString (tST->StdErr, Buffer);
  }

  while (TRUE);
}

/*++

Routine Description:
  Initializes the EfiDebugMask variable for our build

Arguments:

  None

Returns:

  None

--*/
VOID
EfiDebugVariable (
  VOID
  )
{
  EFI_STATUS      Status;
  UINT32          Attributes;
  UINTN           DataSize;
  UINTN           NewEfiDebugMask;

  DataSize = sizeof(EfiDebugMask);
  Status = tRT->GetVariable (L"EfiDebugMask", &gEfiGlobalVariableGuid, &Attributes, &DataSize, &NewEfiDebugMask);
  if (!EFI_ERROR(Status)) {
    EfiDebugMask = NewEfiDebugMask;
  }
}

EFI_STATUS
EfiDebugAssertInit (
  VOID
  )
{
  return EFI_SUCCESS;
}
