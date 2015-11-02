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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
  Prints a debug message to the debug output device if the specified error level is enabled.

  If Format is NULL, then ASSERT().

  @param  ErrorLevel  The error level of the debug message.
  @param  Format      The format string for the debug message to print.
  @param  ...         The variable argument list whose contents are accessed
                      based on the format string specified by Format.

**/
  VOID
EfiDebugPrint (
  IN  UINTN   ErrorLevel,
  IN  CHAR8  *Format,
  ...
  )
{
  CHAR16   Buffer[MAX_DEBUG_MESSAGE_LENGTH];
  VA_LIST  Marker;
  CHAR16   *FormatUnicode;

  //
  // If Format is NULL, then ASSERT().
  //
  ASSERT (Format != NULL);

  //
  // Check driver debug mask value and global mask
  //
  if ((ErrorLevel & EfiDebugMask) == 0) {
    return;
}

//
  // Convert the DEBUG() message to a Unicode String
//
  VA_START (Marker, Format);
  FormatUnicode = SctAllocatePool(SctAsciiStrSize (Format) * sizeof (CHAR16));
  SctAsciiToUnicode (FormatUnicode, Format, SctAsciiStrSize (Format));
  SctVSPrint (Buffer, MAX_DEBUG_MESSAGE_LENGTH, FormatUnicode, Marker);
  VA_END (Marker);

  //
  // Send the print string to the Standard Error device
  //
  if ((tST != NULL) && (tST->StdErr != NULL)) {
    tST->StdErr->OutputString (tST->StdErr, Buffer);
  }
}


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
