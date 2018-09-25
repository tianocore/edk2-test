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

  StallForKey.c

Abstract:

  Waiting for a key input.

--*/

#include "StallForKey.h"

EFI_STATUS
EFIAPI
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
                 (EFI_EVENT_NOTIFY) NULL,
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
