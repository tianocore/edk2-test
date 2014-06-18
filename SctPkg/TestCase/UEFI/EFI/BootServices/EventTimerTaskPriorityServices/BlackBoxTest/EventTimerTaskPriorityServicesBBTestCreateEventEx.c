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

  EventTimerTaskPriorityServicesBBTestCreateEvent.c

Abstract:

  Test Driver of CreateEvent() of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

#ifndef EVT_NOTIFY_SIGNAL_ALL
#define EVT_NOTIFY_SIGNAL_ALL     0x00000400
#endif

#ifndef EVT_SIGNAL_READY_TO_BOOT
#define EVT_SIGNAL_READY_TO_BOOT  0x00000203
#endif

#ifndef EVT_SIGNAL_LEGACY_BOOT
#define EVT_SIGNAL_LEGACY_BOOT    0x00000204
#endif

//
// Declarations
//

EFI_STATUS
BBTestCreateEventEx_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );


EFI_STATUS
BBTestCreateEventEx_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );


EFI_STATUS
BBTestCreateEventEx_Conf_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );
  

EFI_STATUS
BBTestCreateEventEx_Conf_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );
  
EFI_STATUS
BBTestCreateEventEx_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)	  
EFI_STATUS
BBTestCreateEventEx_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );
#endif
  
//
// Functions
//

EFI_STATUS
BBTestCreateEventEx_Conf (
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

  if (FALSE == CheckBBTestCanRunAndRecordAssertion(
                  StandardLib, 
                  L"BS.CreateEventEx - CreateEventEx() tests it's not Supported in EFI",
                  __FILE__,
                  (UINTN)__LINE__
                  )) {
    return EFI_SUCCESS;
  }

  //
  // CreateEventEx() returns EFI_INVALID_PARAMETER with Event being NULL.
  //
  BBTestCreateEventEx_Conf_Sub1 (StandardLib);

  //
  // CreateEventEx() returns EFI_INVALID_PARAMETER with invalid event type. 
  //
  BBTestCreateEventEx_Conf_Sub2 (StandardLib);

  //
  // CreateEventEx() returns EFI_INVALID_PARAMETER with NULL notify function.
  //
  BBTestCreateEventEx_Conf_Sub3 (StandardLib);

  //
  // CreateEventEx() returns EFI_INVALID_PARAMETER with invalid notify TPL.
  //
  BBTestCreateEventEx_Conf_Sub4 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestCreateEventEx_Func (
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

  if (FALSE == CheckBBTestCanRunAndRecordAssertion(
                  StandardLib, 
                  L"BS.CreateEventEx - CreateEventEx() tests it's not Supported in EFI",
                  __FILE__,
                  (UINTN)__LINE__
                  )) {
    return EFI_SUCCESS;
  }

  //
  // The events created by CreateEventEx() are invoked in order of each specified
  // notify TPL.
  //
  BBTestCreateEventEx_Func_Sub1 (StandardLib);
  
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)	
  //
  //When call InstallConfigurationTable(), the events created by CreateEventEx() are invoked in order of
  //each specified notify TPL
  BBTestCreateEventEx_Func_Sub2 (StandardLib);
#endif  
  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Sub functions
//

EFI_STATUS
BBTestCreateEventEx_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               TypeIndex;
  UINTN               TplIndex;
  UINTN               EventGroupIndex;
  UINT32              EventTypes[] = {
                        EVT_NOTIFY_WAIT,
                        EVT_NOTIFY_SIGNAL,
                        EVT_TIMER | EVT_NOTIFY_SIGNAL,
                        EVT_RUNTIME | EVT_NOTIFY_SIGNAL,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_GUID            *EventGroups[] = {
                         &EventGroupTestGroup1Guid,
                         &EventGroupTestGroup2Guid,
                         0
                      };
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Walk through with valid parameters and event being NULL
  //
  for (TypeIndex = 0; EventTypes[TypeIndex] != 0; TypeIndex++) {
    for (TplIndex = 0; NotifyTpls[TplIndex] != 0; TplIndex++) {
      for (EventGroupIndex = 0; EventGroups[EventGroupIndex] != 0; EventGroupIndex++) {
        //
        // Create an event with valid parameters and event being NULL
        //
        Status = gtBS->CreateEventEx (
                         EventTypes[TypeIndex],
                         NotifyTpls[TplIndex],
                         NotifyFunction,
                         NULL,
                         EventGroups[EventGroupIndex],
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
                       gEventTimerTaskPriorityServicesBBTestCreateEventExAssertionGuid003,
                       L"BS.CreateEventEx - Create event with Event being NULL.",
                       L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTPL - %d, EventGroup %x-%x-%x-%x%x%x%x%x%x%x%x ",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       EventTypes[TypeIndex],
                       NotifyTpls[TplIndex],
                       EventGroups[EventGroupIndex]->Data1,
                       EventGroups[EventGroupIndex]->Data2,
                       EventGroups[EventGroupIndex]->Data3,
                       EventGroups[EventGroupIndex]->Data4[0],
                       EventGroups[EventGroupIndex]->Data4[1],
                       EventGroups[EventGroupIndex]->Data4[2],
                       EventGroups[EventGroupIndex]->Data4[3],
                       EventGroups[EventGroupIndex]->Data4[4],
                       EventGroups[EventGroupIndex]->Data4[5],
                       EventGroups[EventGroupIndex]->Data4[6],
                       EventGroups[EventGroupIndex]->Data4[7]
                       );
      }
    }
  }
  
  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestCreateEventEx_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               TypeIndex;
  UINTN               TplIndex;
  UINTN               EventGroupIndex;
  UINT32              InvalidEventTypes[] = {
                        EVT_NOTIFY_WAIT | EVT_NOTIFY_SIGNAL,
                        EVT_NOTIFY_WAIT | EVT_SIGNAL_EXIT_BOOT_SERVICES,
                        EVT_NOTIFY_WAIT | EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
                        EVT_TIMER | EVT_SIGNAL_EXIT_BOOT_SERVICES,
                        EVT_TIMER | EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
                        EVT_SIGNAL_EXIT_BOOT_SERVICES,
                        EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_GUID            *EventGroups[] = {
                         &EventGroupTestGroup1Guid,
                         &EventGroupTestGroup2Guid,
                         0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through with valid parameters and invalid event types
  //
  for (TypeIndex = 0; InvalidEventTypes[TypeIndex] != 0; TypeIndex++) {
    for (TplIndex = 0; NotifyTpls[TplIndex] != 0; TplIndex++) {
      for (EventGroupIndex = 0; EventGroups[EventGroupIndex] != 0; EventGroupIndex++) {
        //
        // Create an event with valid parameters and invalid event type
        //
        Status = gtBS->CreateEventEx (
                         InvalidEventTypes[TypeIndex],
                         NotifyTpls[TplIndex],
                         NotifyFunction,
                         NULL,
                         EventGroups[EventGroupIndex],
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
                       gEventTimerTaskPriorityServicesBBTestCreateEventExAssertionGuid001,
                       L"BS.CreateEventEx - Create event with invalid event type.",
                       L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTPL - %d, EventGroup %x-%x-%x-%x%x%x%x%x%x%x%x ",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       InvalidEventTypes[TypeIndex],
                       NotifyTpls[TplIndex],
                       EventGroups[EventGroupIndex]->Data1,
                       EventGroups[EventGroupIndex]->Data2,
                       EventGroups[EventGroupIndex]->Data3,
                       EventGroups[EventGroupIndex]->Data4[0],
                       EventGroups[EventGroupIndex]->Data4[1],
                       EventGroups[EventGroupIndex]->Data4[2],
                       EventGroups[EventGroupIndex]->Data4[3],
                       EventGroups[EventGroupIndex]->Data4[4],
                       EventGroups[EventGroupIndex]->Data4[5],
                       EventGroups[EventGroupIndex]->Data4[6],
                       EventGroups[EventGroupIndex]->Data4[7]
                       );

        //
        // Close the event if required
        //
        if (!EFI_ERROR (Status)) {
          gtBS->CloseEvent (Event);
        }
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestCreateEventEx_Conf_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               TypeIndex;
  UINTN               TplIndex;
  UINTN               EventGroupIndex;
  UINT32              EventTypes[] = {                        
                        EVT_NOTIFY_WAIT,
                        EVT_TIMER | EVT_NOTIFY_WAIT,
                        EVT_NOTIFY_SIGNAL,
                        EVT_TIMER | EVT_NOTIFY_SIGNAL,                   
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_GUID            *EventGroups[] = {
                         &EventGroupTestGroup1Guid,
                         &EventGroupTestGroup2Guid,
                         0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through with invalid combination of event type and NotifyFunction
  //
  for (TypeIndex = 0; EventTypes[TypeIndex] != 0; TypeIndex++) {
    for (TplIndex = 0; NotifyTpls[TplIndex] != 0; TplIndex++) {
      for (EventGroupIndex = 0; EventGroups[EventGroupIndex] != 0; EventGroupIndex++) {
        //
        // Create an event with invalid combinatin of event type and NotifyFunction
        //
        Status = gtBS->CreateEventEx (
                         EventTypes[TypeIndex],
                         NotifyTpls[TplIndex],
                         NULL,
                         NULL,
                         EventGroups[EventGroupIndex],
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
                       gEventTimerTaskPriorityServicesBBTestCreateEventExAssertionGuid004,
                       L"BS.CreateEventEx - Create event with either EVT_NOTIFY_WAIT or EVT_NOTIFY_SIGNAL set and NotifyFunction being NULL",
                       L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTPL - %d, EventGroup NULL ",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       EventTypes[TypeIndex],
                       NotifyTpls[TplIndex]
                       );

        //
        // Close the event if required
        //
        if (!EFI_ERROR (Status)) {
          gtBS->CloseEvent (Event);
        }
      }
    }
  }
  
  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestCreateEventEx_Conf_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               TypeIndex;
  UINTN               TplIndex;
  UINTN               EventGroupIndex;
  UINT32              EventTypes[] = {
                        // NotifyTpl will be ignored with EVT_TIMER
                        EVT_NOTIFY_WAIT,
                        EVT_NOTIFY_SIGNAL,
                        0
                      };
  EFI_TPL             InvalidNotifyTpls[] = {
                        (EFI_TPL) (TPL_HIGH_LEVEL + 1),
                        (EFI_TPL) -1,
                        0
                      };
  EFI_GUID            *EventGroups[] = {
                         &EventGroupTestGroup1Guid,
                         &EventGroupTestGroup2Guid,
                         0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through with valid parameters and invalid tpl
  //
  for (TypeIndex = 0; EventTypes[TypeIndex] != 0; TypeIndex++) {
    for (TplIndex = 0; InvalidNotifyTpls[TplIndex] != 0; TplIndex++) {
      for (EventGroupIndex = 0; EventGroups[EventGroupIndex] != 0; EventGroupIndex++) {
        //
        // Create an event with invalid tpl
        //
        Status = gtBS->CreateEventEx (
                         EventTypes[TypeIndex],
                         InvalidNotifyTpls[TplIndex],
                         NotifyFunction,
                         NULL,
                         EventGroups[EventGroupIndex],
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
                       gEventTimerTaskPriorityServicesBBTestCreateEventExAssertionGuid002,
                       L"BS.CreateEventEx - Create event with invalid notify TPL.",
                       L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTPL - %d, EventGroup %x-%x-%x-%x%x%x%x%x%x%x%x ",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       EventTypes[TypeIndex],
                       InvalidNotifyTpls[TplIndex],
                       EventGroups[EventGroupIndex]->Data1,
                       EventGroups[EventGroupIndex]->Data2,
                       EventGroups[EventGroupIndex]->Data3,
                       EventGroups[EventGroupIndex]->Data4[0],
                       EventGroups[EventGroupIndex]->Data4[1],
                       EventGroups[EventGroupIndex]->Data4[2],
                       EventGroups[EventGroupIndex]->Data4[3],
                       EventGroups[EventGroupIndex]->Data4[4],
                       EventGroups[EventGroupIndex]->Data4[5],
                       EventGroups[EventGroupIndex]->Data4[6],
                       EventGroups[EventGroupIndex]->Data4[7]
                       );

        //
        // Close the event if required
        //
        if (!EFI_ERROR (Status)) {
          gtBS->CloseEvent (Event);
        }
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestCreateEventEx_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
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
  EFI_EVENT           Event[MAX_TEST_EVENT_NUM];

  //
  //  Buffer[0] Buffer[1] Buffer[2] store event index
  //
  //  Buffer[3] stores the index of the first event notified
  //  Buffer[4] stores the Tpl of the notification function of the first event notified
  //
  //  Buffer[5] stores the index of the second event notified
  //  Buffer[6] stores the Tpl of the notification function of the second event notified  
  //
  //  Buffer[7] stores the index of the third event notified
  //  Buffer[8] stores the Tpl of the notification function of the third event notified  
  //
  UINTN               Buffer[MAX_TEST_EVENT_NUM + MAX_TEST_EVENT_NUM*2];

  //
  // Initialize Buffer
  //
  for (Index = 0; Index < MAX_TEST_EVENT_NUM; Index ++) {
    Buffer[Index] = Index;
    Buffer[Index + MAX_TEST_EVENT_NUM + Index] = (UINTN)(-1);
    Buffer[Index + MAX_TEST_EVENT_NUM + 1 + Index] = (UINTN)(-1);
  }

  //
  // Creat Event0 in the EventGroup
  //
  Status = gtBS->CreateEventEx (
                   EventTypes[0],
                   NotifyTpls[0],
                   NotifyFunctionTplEx,
                   &Buffer[0],
                   &EventGroupTestGroup3Guid,
                   &Event[0]
                   );

  if (EFI_ERROR (Status)) {
      return Status;
  }

  //
  // Creat Event1 in the EventGroup
  //  
  Status = gtBS->CreateEventEx (
                   EventTypes[0],
                   NotifyTpls[0],
                   NotifyFunctionTplEx,
                   &Buffer[1],
                   &EventGroupTestGroup3Guid,
                   &Event[1]
                   );

  if (EFI_ERROR (Status)) {
      gtBS->CloseEvent (Event[0]);
      return Status;
  }

  //
  // Creat Event2 not in a EventGroup
  //  
  Status = gtBS->CreateEventEx (
                   EventTypes[0],
                   NotifyTpls[1],
                   NotifyFunctionTplEx,
                   &Buffer[2],
                   NULL,
                   &Event[2]
                   );

  if (EFI_ERROR (Status)) {
      gtBS->CloseEvent (Event[0]);
      gtBS->CloseEvent (Event[1]);
      return Status;
  }
  
  //
  // Signal these events at TPL_HIGH_LEVEL
  //
  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);

  Status = gtBS->SignalEvent (Event[0]);
  if (EFI_ERROR (Status)) {
        gtBS->CloseEvent (Event[0]);
        gtBS->CloseEvent (Event[1]);
        gtBS->CloseEvent (Event[2]);
        return Status;
  }

  Status = gtBS->SignalEvent (Event[2]);
  if (EFI_ERROR (Status)) {
        gtBS->CloseEvent (Event[0]);
        gtBS->CloseEvent (Event[1]);
        gtBS->CloseEvent (Event[2]);
        return Status;
  }
      
  gtBS->RestoreTPL (OldTpl);

  //
  // Close all the events created
  //
  gtBS->CloseEvent (Event[0]);
  gtBS->CloseEvent (Event[1]);
  gtBS->CloseEvent (Event[2]);

  //
  // Compare the notify order
  //
  if ( (Buffer[MAX_TEST_EVENT_NUM] == 2 && Buffer[MAX_TEST_EVENT_NUM + 1] == TPL_NOTIFY) &&
       (Buffer[MAX_TEST_EVENT_NUM + 3] == TPL_CALLBACK) &&
       (Buffer[MAX_TEST_EVENT_NUM + 5] == TPL_CALLBACK) ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCreateEventExAssertionGuid005,
                 L"BS.CreateEventEx - Check the notification of the EventGroup and the notify order.",
                 L"%a:%d:Event notify Tpl - %d,%d,%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Buffer[MAX_TEST_EVENT_NUM + 1],
                 Buffer[MAX_TEST_EVENT_NUM + 3],
                 Buffer[MAX_TEST_EVENT_NUM + 5]
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)	
EFI_STATUS
BBTestCreateEventEx_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  EFI_TPL             OldTpl;
  UINTN               TestTable;
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
  EFI_EVENT           Event[MAX_TEST_EVENT_NUM];

  //
  //  Buffer[0] Buffer[1] Buffer[2] store event index
  //
  //  Buffer[3] stores the index of the first event notified
  //  Buffer[4] stores the Tpl of the notification function of the first event notified
  //
  //  Buffer[5] stores the index of the second event notified
  //  Buffer[6] stores the Tpl of the notification function of the second event notified  
  //
  //  Buffer[7] stores the index of the third event notified
  //  Buffer[8] stores the Tpl of the notification function of the third event notified  
  //
  UINTN               Buffer[MAX_TEST_EVENT_NUM + MAX_TEST_EVENT_NUM*2];

  //
  // Initialize Buffer
  //
  for (Index = 0; Index < MAX_TEST_EVENT_NUM; Index ++) {
    Buffer[Index] = Index;
    Buffer[Index + MAX_TEST_EVENT_NUM + Index] = (UINTN)(-1);
    Buffer[Index + MAX_TEST_EVENT_NUM + 1 + Index] = (UINTN)(-1);
  }

  //
  // Creat Event0 in the EventGroup
  //
  Status = gtBS->CreateEventEx (
                   EventTypes[0],
                   NotifyTpls[0],
                   NotifyFunctionTplEx,
                   &Buffer[0],
                   &EventGroupTestGroup3Guid,
                   &Event[0]
                   );

  if (EFI_ERROR (Status)) {
      return Status;
  }

  //
  // Creat Event1 in the EventGroup
  //  
  Status = gtBS->CreateEventEx (
                   EventTypes[0],
                   NotifyTpls[0],
                   NotifyFunctionTplEx,
                   &Buffer[1],
                   &EventGroupTestGroup3Guid,
                   &Event[1]
                   );

  if (EFI_ERROR (Status)) {
      gtBS->CloseEvent (Event[0]);
      return Status;
  }

  //
  // Creat Event2 in the EventGroup
  //  
  Status = gtBS->CreateEventEx (
                   EventTypes[0],
                   NotifyTpls[1],
                   NotifyFunctionTplEx,
                   &Buffer[2],
                   &EventGroupTestGroup3Guid,
                   &Event[2]
                   );

  if (EFI_ERROR (Status)) {
      gtBS->CloseEvent (Event[0]);
      gtBS->CloseEvent (Event[1]);
      return Status;
  }
  
  //
  // Install a configuration table at TPL_HIGH_LEVEL
  //
  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  
  Status = gtBS->InstallConfigurationTable (
                     &EventGroupTestGroup3Guid,
                     (VOID*)&TestTable
                     );
  if (EFI_ERROR (Status)) {
        gtBS->CloseEvent (Event[0]);
        gtBS->CloseEvent (Event[1]);
        gtBS->CloseEvent (Event[2]);
		gtBS->InstallConfigurationTable (
                     &EventGroupTestGroup3Guid,
                     NULL
                     );
        return Status;
	}
	
  gtBS->RestoreTPL (OldTpl);

  //
  // Close all the events created and remove the new installed configuration table
  //
  gtBS->CloseEvent (Event[0]);
  gtBS->CloseEvent (Event[1]);
  gtBS->CloseEvent (Event[2]);
  gtBS->InstallConfigurationTable (
                     &EventGroupTestGroup3Guid,
                     NULL
                     );

  //
  // Compare the notify order
  //
  if ( (Buffer[MAX_TEST_EVENT_NUM] == 2 && Buffer[MAX_TEST_EVENT_NUM + 1] == TPL_NOTIFY) &&
       Buffer[MAX_TEST_EVENT_NUM + 3] == TPL_CALLBACK &&
       Buffer[MAX_TEST_EVENT_NUM + 5] == TPL_CALLBACK ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCreateEventExAssertionGuid006,
                 L"BS.CreateEventEx - Check the notification of the EventGroup and the notify order when call InstallConfigurationTable.",
                 L"%a:%d:Event's notify Tpl - %d,%d,%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Buffer[MAX_TEST_EVENT_NUM + 1],
                 Buffer[MAX_TEST_EVENT_NUM + 3],
                 Buffer[MAX_TEST_EVENT_NUM + 5]
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}
#endif