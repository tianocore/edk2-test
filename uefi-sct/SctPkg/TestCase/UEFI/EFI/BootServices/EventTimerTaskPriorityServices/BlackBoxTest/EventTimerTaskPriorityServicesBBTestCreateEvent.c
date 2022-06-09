/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2021, ARM Limited. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EventTimerTaskPriorityServicesBBTestCreateEvent.c

Abstract:

  Test Driver of CreateEvent() of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Declarations
//

EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCreateEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCreateEvent_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );
  
EFI_STATUS
EFIAPI
BBTestCreateEvent_Func_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;

  //
  // Locate standard test library
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // CreateEvent() returns EFI_INVALID_PARAMETER with invalid event type.
  //
  BBTestCreateEvent_Conf_Sub1 (StandardLib);

  //
  // CreateEvent() returns EFI_INVALID_PARAMETER with invalid notify TPL.
  //
  BBTestCreateEvent_Conf_Sub2 (StandardLib);

  //
  // CreateEvent() returns EFI_INVALID_PARAMETER with Event being NULL.
  //
  BBTestCreateEvent_Conf_Sub3 (StandardLib);

  //
  // CreateEvent() returns EFI_INVALID_PARAMETER with NotifyFunction being NULL and Type is EVT_NOTIFY_WAIT or EVT_NOTIFY_SIGNAL..
  //
  BBTestCreateEvent_Conf_Sub4 (StandardLib);
  
  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestCreateEvent_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;

  //
  // Locate standard test library
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // CreateEvent() returns EFI_SUCCESS with all valid parameters.
  //
  BBTestCreateEvent_Func_Sub1 (StandardLib);
  
  //
  //CreateEvent() returns EFI_SUCCESS with neither EVENT_NOTIFY_WAIT nor 
  //EVENT_NOTIFY_SIGNAL event types and unsupported notify TPLs
  //
  BBTestCreateEvent_Func_Sub2 (StandardLib);

  //
  // The events created by CreateEvent() are invoked in order of each specified
  // notify TPL.
  //
  BBTestCreateEvent_Func_Sub3 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Sub functions
//

EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               SubIndex;
  UINT32              InvalidEventTypes[] = {
                        EVT_NOTIFY_WAIT | EVT_NOTIFY_SIGNAL,
                        EVT_NOTIFY_WAIT | EVT_SIGNAL_EXIT_BOOT_SERVICES,
                        EVT_NOTIFY_WAIT | EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
                        EVT_TIMER | EVT_SIGNAL_EXIT_BOOT_SERVICES,
                        EVT_TIMER | EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through the invalid event types and valid notify TPLs
  //
  for (Index = 0; InvalidEventTypes[Index] != 0; Index++) {
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      //
      // Create an event with invalid event type
      //
      Status = gtBS->CreateEvent (
                       InvalidEventTypes[Index],
                       NotifyTpls[SubIndex],
                       NotifyFunction,
                       NULL,
                       &Event
                       );

      if (Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEventTimerTaskPriorityServicesBBTestCreateEventAssertionGuid003,
                     L"BS.CreateEvent - Create event with invalid event type.",
                     L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     InvalidEventTypes[Index],
                     NotifyTpls[SubIndex]
                     );

      //
      // Close the event if required
      //
      if (!EFI_ERROR (Status)) {
        gtBS->CloseEvent (Event);
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               SubIndex;
  UINT32              EventTypes[] = {
                        // NotifyTpl will be ignored with EVT_TIMER
                        EVT_NOTIFY_WAIT,
                        EVT_NOTIFY_SIGNAL,
                        0
                      };
  EFI_TPL             InvalidNotifyTpls[] = {
                        (EFI_TPL) (TPL_HIGH_LEVEL + 1),
                        (EFI_TPL) (TPL_APPLICATION - 1),
                        (EFI_TPL) TPL_APPLICATION,
                        (EFI_TPL) -1,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through the valid event types and invalid notify TPLs
  //
  for (Index = 0; EventTypes[Index] != 0; Index++) {
    for (SubIndex = 0; InvalidNotifyTpls[SubIndex] != 0; SubIndex++) {
      //
      // Create event with invalid TPLs
      //
      Status = gtBS->CreateEvent (
                       EventTypes[Index],
                       InvalidNotifyTpls[SubIndex],
                       NotifyFunction,
                       NULL,
                       &Event
                       );

      if (Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEventTimerTaskPriorityServicesBBTestCreateEventAssertionGuid004,
                     L"BS.CreateEvent - Create event with invalid notify TPL.",
                     L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EventTypes[Index],
                     InvalidNotifyTpls[SubIndex]
                     );

      //
      // Close the event if required
      //
      if (!EFI_ERROR (Status)) {
        gtBS->CloseEvent (Event);
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               SubIndex;
  UINT32              EventTypes[] = {
                        EVT_TIMER | EVT_NOTIFY_SIGNAL,
                        EVT_RUNTIME | EVT_NOTIFY_SIGNAL,							
                        EVT_NOTIFY_WAIT,
                        EVT_NOTIFY_SIGNAL,
                        EVT_SIGNAL_EXIT_BOOT_SERVICES ,
                        EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Walk through the event types and notify TPLs
  //
  for (Index = 0; EventTypes[Index] != 0; Index++) {
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      //
      // Create event with Event is NULL
      //
      Status = gtBS->CreateEvent (
                       EventTypes[Index],
                       NotifyTpls[SubIndex],
                       NotifyFunction,
                       NULL,
                       NULL
                       );

      if (Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCreateEventAssertionGuid005,
                 L"BS.CreateEvent - Create event with Event being NULL.",
                 L"%a:%d:Status = %r, EventType - 0x%08x, NotifyTpl - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EventTypes[Index],
                 NotifyTpls[SubIndex]
                 );

    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               SubIndex;
  UINT32              EventTypes[] = {						
                        EVT_NOTIFY_WAIT,
                        EVT_NOTIFY_SIGNAL,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;  

  //
  // Walk through the event types and notify TPLs
  //
  for (Index = 0; EventTypes[Index] != 0; Index++) {
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      //
      // Create event with Event is NULL
      //
      Status = gtBS->CreateEvent (
                       EventTypes[Index],
                       NotifyTpls[SubIndex],
                       NULL,
                       NULL,
                       &Event
                       );

      if (Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCreateEventAssertionGuid007,
                 L"BS.CreateEvent - Create event with NotifyFunction being NULL and Type is EVT_NOTIFY_WAIT or EVT_NOTIFY_SIGNAL.",
                 L"%a:%d:Status = %r, EventType - 0x%08x, NotifyTpl - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EventTypes[Index],
                 NotifyTpls[SubIndex]
                 );
      //
      // Close the event if required
      //
      if (!EFI_ERROR (Status)) {
        gtBS->CloseEvent (Event);
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestCreateEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               SubIndex;
  UINT32              EventTypes[] = {
                        EVT_TIMER,
                        EVT_NOTIFY_WAIT,
                        EVT_NOTIFY_SIGNAL,
                        EVT_TIMER | EVT_NOTIFY_WAIT,
                        EVT_TIMER | EVT_NOTIFY_SIGNAL,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through common event types and notify TPLs
  //
  for (Index = 0; EventTypes[Index] != 0; Index++) {
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      //
      // Create event with valid event type and supported notify TPL
      //
      Status = gtBS->CreateEvent (
                       EventTypes[Index],
                       NotifyTpls[SubIndex],
                       NotifyFunction,
                       NULL,
                       &Event
                       );

      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEventTimerTaskPriorityServicesBBTestCreateEventAssertionGuid001,
                     L"BS.CreateEvent - Create event with all valid event type and supported TPL.",
                     L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EventTypes[Index],
                     NotifyTpls[SubIndex]
                     );

      //
      // Close the event if required
      //
      if (!EFI_ERROR (Status)) {
        gtBS->CloseEvent (Event);
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestCreateEvent_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               SubIndex;
  UINT32              EventTypes[] = {
                        EVT_TIMER,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        (EFI_TPL) (TPL_HIGH_LEVEL + 1),
                        (EFI_TPL) -1,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through neither EVENT_NOTIFY_WAIT nor EVENT_NOTIFY_SIGNAL event types and unsupported notify TPLs
  //
  for (Index = 0; EventTypes[Index] != 0; Index++) {
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      //
      // Create event with neither EVENT_NOTIFY_WAIT nor EVENT_NOTIFY_SIGNAL event type and unsupported notify TPL
      //
      Status = gtBS->CreateEvent (
                       EventTypes[Index],
                       NotifyTpls[SubIndex],
                       NotifyFunction,
                       NULL,
                       &Event
                       );

      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEventTimerTaskPriorityServicesBBTestCreateEventAssertionGuid006,
                     L"BS.CreateEvent - Create event with neither EVENT_NOTIFY_WAIT nor EVENT_NOTIFY_SIGNAL event types and unsupported notify TPLs.",
                     L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EventTypes[Index],
                     NotifyTpls[SubIndex]
                     );

      //
      // Close the event if required
      //
      if (!EFI_ERROR (Status)) {
        gtBS->CloseEvent (Event);
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestCreateEvent_Func_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               SubIndex;
  EFI_TPL             OldTpl;
  UINT32              EventTypes[] = {
                        EVT_NOTIFY_SIGNAL,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Events[2];
  UINTN               Buffer[4];

  //
  // Walk through the common event types
  //
  Status = EFI_SUCCESS;

  for (Index = 0; EventTypes[Index] != 0; Index++) {
    //
    // Create event with different TPLs
    //
    Buffer[0] = 2;  // Max
    Buffer[1] = 0;  // Used
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      Status = gtBS->CreateEvent (
                       EventTypes[Index],
                       NotifyTpls[SubIndex],
                       NotifyFunctionTpl,
                       Buffer,
                       &Events[SubIndex]
                       );
      if (EFI_ERROR (Status)) {
        break;
      }
    }

    if (EFI_ERROR (Status)) {
      break;
    }

    //
    // Signal these events at TPL_HIGH_LEVEL
    //
    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      Status = gtBS->SignalEvent (Events[SubIndex]);
      if (EFI_ERROR (Status)) {
        break;
      }
    }
    gtBS->RestoreTPL (OldTpl);

    if (EFI_ERROR (Status)) {
      break;
    }

    //
    // Compare the notify order
    //
    if ((Buffer[1] == 2                       ) &&
        (Buffer[2] == (UINTN) TPL_NOTIFY  ) &&
        (Buffer[3] == (UINTN) TPL_CALLBACK)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEventTimerTaskPriorityServicesBBTestCreateEventAssertionGuid002,
                   L"BS.CreateEvent - Check the notify order.",
                   L"%a:%d:EventType - 0x%08x, Count - %d, TplOrder - %d,%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventTypes[Index],
                   Buffer[1],
                   Buffer[2],
                   Buffer[3]
                   );

    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++){
      gtBS->CloseEvent (Events[SubIndex]);
    }
	
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
