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

  SctPrint.c

--*/

#include "SCRTDriver.h"
#include "SctLib.h"


//
// Length of temp string buffer to store value string.
//
#define EFI_MAX_PRINT_BUFFER         1024


#ifndef VA_START
typedef CHAR8 *VA_LIST;
#define VA_START(ap, v) (ap = (VA_LIST) & (v) + _EFI_INT_SIZE_OF (v))
#define VA_ARG(ap, t)   (*(t *) ((ap += _EFI_INT_SIZE_OF (t)) - _EFI_INT_SIZE_OF (t)))
#define VA_END(ap)      (ap = (VA_LIST) 0)
#endif

STATIC
EFI_STATUS
LocalPrintf (
  IN CHAR8     *String
  )
/*++

Routine Description:

  Print text message to COM1 and COM2 synchronously.

Arguments:

  String  - Pointer to text message.

Returns:

--*/  
{
  return DebugWorker(String);
}


VOID 
RecordAssertion (
  IN   EFI_TEST_ASSERTION    Status,
  IN   EFI_GUID              EventId,
  IN   CHAR8                *Description,
  IN   CHAR8                *Format,
  ...
  )
/*++

Routine Description:

  Print a formatted string specially for checkpoint to COM1 and COM2 synchronously.

Arguments:

  Status           - Checkpoint Status.
  EventId          - Checkpoint related unique GUID
  Description      - Checkpoint concise description
  Format           - Format string
  ...              - Vararg list consumed by processing Format.
  
Returns:

  NONE

--*/  
{
  VA_LIST Marker;
  CHAR8   AssertionType[10];
  CHAR8   Buffer1[EFI_MAX_PRINT_BUFFER];
  CHAR8   Buffer2[EFI_MAX_PRINT_BUFFER];
  CHAR8   Buffer3[EFI_MAX_PRINT_BUFFER];

  switch (Status) {
  case EFI_TEST_ASSERTION_PASSED:
    SctAsciiStrCpy (AssertionType, "PASS");
    break;
  default:
    SctAsciiStrCpy (AssertionType, "FAILURE");
    break;
  }

  SctASPrint (Buffer1, EFI_MAX_PRINT_BUFFER, "%s -- %s\n", Description, AssertionType);
  SctASPrint (Buffer2, EFI_MAX_PRINT_BUFFER, "%g\n", &EventId);

  VA_START (Marker, Format);
  SctASPrint (Buffer3, EFI_MAX_PRINT_BUFFER, Format, Marker);
  VA_END (Marker);

  if (SctAsciiStrLen (Buffer3) + 5 < EFI_MAX_PRINT_BUFFER ) {
    SctAsciiStrCat (Buffer3, "\r\n\r\n");
  }

  LocalPrintf(Buffer1);
  LocalPrintf(Buffer2);
  LocalPrintf(Buffer3);
}
