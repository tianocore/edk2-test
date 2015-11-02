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

  StallForKey.c

Abstract:

  Waiting for a key input.

--*/

#include "StallForKey.h"

EFI_STATUS
StallForKey (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS      Status;
  UINTN           Argc;
  CHAR16          **Argv;
  UINTN           Seconds;
  EFI_EVENT       TimerEvent;
  EFI_EVENT       WaitList[2];
  UINTN           WaitIndex;
  EFI_INPUT_KEY   Key;

  //
  // Initialize libraries
  //
  SctShellApplicationInit (ImageHandle, SystemTable);

  //
  // Process the arguments
  //
  SctShellGetArguments (&Argc, &Argv);
  Seconds = DEFAULT_WAIT_TIME;
  if (Argc > 1) {
    Seconds = SctAtoi (Argv[1]);
  }

  //
  // Create timer event
  //
  Status = tBS->CreateEvent (
		         EVT_TIMER,
                 0,
                 NULL,
                 NULL,
                 &TimerEvent
                 );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Create event. %a:%d:%r\n", __FILE__, __LINE__, Status));
    return Status;
  }

  //
  // Set up the timer
  //
  Status = tBS->SetTimer (
                 TimerEvent,
                 TimerPeriodic,
                 10000000                   // 1 second
                 );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Set timer. %a:%d:%r\n", __FILE__, __LINE__, Status));
    tBS->CloseEvent (TimerEvent);
    return Status;
  }

  //
  // Set up waiting list
  //
  WaitList[0] = tST->ConIn->WaitForKey;
  WaitList[1] = TimerEvent;

  //
  // Do it until timeout
  //
  while (Seconds != 0) {
    //
    // Print the prompt information (The last blank char is used to clean up
    // the last string. Don't remove it.)
    //
    SctPrint (L"Press any key within %d seconds \r", Seconds);

    //
    // Wait for timeout or key input
    //
    Status = tBS->WaitForEvent (
                   2,
                   WaitList,
                   &WaitIndex
                   );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Wait for event. %a:%d:%r\n", __FILE__, __LINE__, Status));
      break;
    }

    //
    // Check the triggered event
    //
    if (WaitIndex == 0) {
      //
      // Key input event is triggered
      //
      Key.ScanCode = SCAN_NULL;
      Status = tST->ConIn->ReadKeyStroke (tST->ConIn, &Key);
      if (!EFI_ERROR (Status)) {
        break;
      }

      DEBUG ((EFI_D_ERROR, "Read key stroke. %a:%d:%r\n", __FILE__, __LINE__, Status));
    } else {
      //
      // Timer event is triggered
      //
      Seconds --;
    }
  }

  //
  // Close the timer event
  //
  tBS->CloseEvent (TimerEvent);

  //
  // Done
  //
  if (Seconds == 0) {
    return EFI_TIMEOUT;
  } else {
    return EFI_SUCCESS;
  }
}
