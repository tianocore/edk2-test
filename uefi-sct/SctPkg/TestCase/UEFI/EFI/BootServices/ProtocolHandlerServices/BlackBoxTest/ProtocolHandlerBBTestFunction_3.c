/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ProtocolHandlerServicesInterfaceTest_3.c

Abstract:

  for Protocol Handler Boot Services' Interface Function Test

--*/

#include "SctLib.h"
#include "Misc.h"

//
// Checkpoint Functions for SctLocateHandle ()
//
EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINTN                 BufferSize;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  UINTN                 RealSize;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  NoHandles = 0;
  HandleBuffer = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);

  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  if (NULL != HandleBuffer) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }

  BufferSize = NoHandles * sizeof (EFI_HANDLE);
  RealSize = BufferSize + sizeof (EFI_HANDLE);
  Status = gtBS->AllocatePool (EfiBootServicesData, RealSize, (VOID**)&HandleBuffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Action 1: retrieve all handles in the system
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandle (
                     AllHandles,
                     NULL,
                     NULL,
                     &BufferSize,
                     HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid001;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid002;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid003;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Action 2: add a new handle
    //
    Handle = NULL;
    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid004;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid005;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid006;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }
    BufferSize = RealSize;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandle (
                     AllHandles,
                     NULL,
                     NULL,
                     &BufferSize,
                     HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid007;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid008;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid009;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (BufferSize == RealSize) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid010;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid011;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid012;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedSize - %d, BufferSize - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   RealSize,
                   BufferSize,
                   TplArray[Index]
                   );
    //
    // Action 3: remove the new handle
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid013;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid014;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid015;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    BufferSize = RealSize - sizeof (EFI_HANDLE);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandle (
                     AllHandles,
                     NULL,
                     NULL,
                     &BufferSize,
                     HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid016;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid017;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid018;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (BufferSize == RealSize - sizeof (EFI_HANDLE)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid019;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid020;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid021;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedSize - %d, BufferSize - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   RealSize - sizeof (EFI_HANDLE),
                   BufferSize,
                   TplArray[Index]
                   );
  }
Done:

  if (NULL != HandleBuffer) {
    gtBS->FreePool (HandleBuffer);
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            HandleArray[10];
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINTN                 BufferSize;
  EFI_HANDLE            *HandleBuffer;
  EFI_EVENT             Event;
  VOID                  *Registration;
  UINTN                 HandleIndex;
  UINTN                 MatchTimes;
  UINTN                 SavedBufferSize;
  UINTN                 MatchIndex;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  Event = NULL;
  HandleBuffer = NULL;

  //
  // event for register notify
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_CALLBACK,
                   TestNotifyFunction0,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // buffersize large enough for locating handle
  //
  BufferSize = sizeof (EFI_HANDLE) * 10;
  SavedBufferSize = BufferSize;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&HandleBuffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // register for TestNoInterfaceProtocol1
  //
  Status = gtBS->RegisterProtocolNotify (
                   &mTestNoInterfaceProtocol1Guid,
                   Event,
                   &Registration
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.RegisterProtocolNotify - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // init
    //
    gtBS->SetMem (HandleArray, 10 * sizeof (EFI_HANDLE), 0);
    MatchTimes = 0;

    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {

      Status = gtBS->InstallProtocolInterface (
                       &HandleArray[HandleIndex],
                       &mTestNoInterfaceProtocol1Guid,
                       EFI_NATIVE_INTERFACE,
                       NULL
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid022;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid023;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid024;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.LocateHandle - InterfaceTestCheckpoint2",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }

    //
    // stall 10 seconds to wait for event signal
    //
    SctPrint (L"Waiting a few seconds for signal ...\n");
    gtBS->Stall (STALL_10_SECONDS);

    //
    // according to EFI spec, SctLocateHandle () returns the
    // next handle that is new for the registration. Only one handle is
    // returned at a time, and the caller must loop until no more handles
    // are returned.
    //
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      //
      // init
      //
      BufferSize = sizeof (EFI_HANDLE) * 10;

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->LocateHandle (
                       ByRegisterNotify,
                       NULL,
                       Registration,
                       &BufferSize,
                       HandleBuffer
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid025;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid026;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid027;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.LocateHandle - InterfaceTestCheckpoint2",
                     L"%a:%d:Status - %r, BufferSize - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     BufferSize,
                     TplArray[Index]
                     );
      //
      // check whether buffersize is expected
      //
      if (BufferSize == sizeof (EFI_HANDLE)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid028;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid029;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid030;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.LocateHandle - InterfaceTestCheckpoint2",
                     L"%a:%d:ExpectedSize - %d, BufferSize - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     sizeof (EFI_HANDLE),
                     BufferSize,
                     TplArray[Index]
                     );
      //
      // check whether handles are match
      //
      for (MatchIndex = 0; MatchIndex < 10; MatchIndex++) {
        if (HandleArray[MatchIndex] == HandleBuffer[0]) {
          MatchTimes++;
        }
      }
    }

    if (10 == MatchTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid031;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid032;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid033;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint2",
                   L"%a:%d:MatchTimes:%d, Expected: 10, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   MatchTimes,
                   TplArray[Index]
                   );

    //
    // call LocateHandle again, expected status is EFI_NOT_FOUND
    //
    BufferSize = sizeof (EFI_HANDLE) * 10;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandle (
                     ByRegisterNotify,
                     NULL,
                     Registration,
                     &BufferSize,
                     HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid034;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid035;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid036;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      gtBS->UninstallProtocolInterface (
              HandleArray[HandleIndex],
              &mTestNoInterfaceProtocol1Guid,
              NULL
              );
    }

  }

Done:
  if (NULL != Event) {
    gtBS->CloseEvent (Event);
  }

  if (NULL != HandleBuffer) {
    gtBS->FreePool (HandleBuffer);
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            HandleArray[10];
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINTN                 BufferSize;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 HandleIndex;
  UINTN                 MatchTimes;
  UINTN                 SavedBufferSize;
  UINTN                 BufferIndex;
  VOID                  *Interface;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  HandleBuffer = NULL;
  BufferSize = sizeof (EFI_HANDLE) * 10;
  SavedBufferSize = BufferSize;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&HandleBuffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    gtBS->SetMem (HandleArray, 10 * sizeof (EFI_HANDLE), 0);

    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {

      Status = gtBS->InstallProtocolInterface (
                       &HandleArray[HandleIndex],
                       &mTestNoInterfaceProtocol1Guid,
                       EFI_NATIVE_INTERFACE,
                       NULL
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid037;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid038;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid039;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.LocateHandle - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }

    //
    // stall 10 seconds to wait for event signal
    //
    SctPrint (L"Waiting a few seconds for signal ...\n");
    gtBS->Stall (STALL_10_SECONDS);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandle (
                     ByProtocol,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     &BufferSize,
                     HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid040;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid041;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid042;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check whether buffersize is expected
    //
    if (BufferSize == SavedBufferSize) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid043;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid044;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid045;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint3",
                   L"%a:%d:ExpectedSize - %d, BufferSize - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   SavedBufferSize,
                   BufferSize,
                   TplArray[Index]
                   );
    //
    // check whether handles are match
    //
    MatchTimes = 0;
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      for (BufferIndex = 0; BufferIndex < 10; BufferIndex++) {
        if (HandleArray[HandleIndex] == HandleBuffer[BufferIndex]) {
          MatchTimes++;
        }
      }
    }
    if (10 == MatchTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid046;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid047;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid048;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint3",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // each located handle supports TestNoInterfaceProtocol1
    //
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[HandleIndex],
                       &mTestNoInterfaceProtocol1Guid,
                       (VOID **) &Interface
                       );

      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid049;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid050;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid051;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.LocateHandle - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, HandleIndex - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     HandleIndex,
                     TplArray[Index]
                     );
    }

    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      gtBS->UninstallProtocolInterface (
              HandleArray[HandleIndex],
              &mTestNoInterfaceProtocol1Guid,
              NULL
              );
    }
  }

  if (NULL != HandleBuffer) {
    gtBS->FreePool (HandleBuffer);
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            HandleArray[10];
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINTN                 BufferSize;
  EFI_HANDLE            *HandleBuffer;
  EFI_EVENT             Event;
  VOID                  *Registration;
  UINTN                 SavedBufferSize;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  Event = NULL;
  HandleBuffer = NULL;

  //
  // event for register notify
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_CALLBACK,
                   TestNotifyFunction0,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // buffersize large enough for locating handle
  //
  BufferSize = sizeof (EFI_HANDLE) * 10;
  SavedBufferSize = BufferSize;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&HandleBuffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // register for TestNoInterfaceProtocol1
  //
  Status = gtBS->RegisterProtocolNotify (
                   &mTestNoInterfaceProtocol1Guid,
                   Event,
                   &Registration
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.RegisterProtocolNotify - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // init
    //
    gtBS->SetMem (HandleArray, 10 * sizeof (EFI_HANDLE), 0);

    Status = gtBS->InstallProtocolInterface (
                     &HandleArray[0],
                     &mTestNoInterfaceProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid592;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid593;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid594;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // stall 10 seconds to wait for event signal
    //
    SctPrint (L"Waiting a few seconds for signal ...\n");
    gtBS->Stall (STALL_10_SECONDS);

    //
    // init
    //
    BufferSize = sizeof (EFI_HANDLE) * 10;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandle (
                     ByRegisterNotify,
                     NULL,
                     Registration,
                     &BufferSize,
                     HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid595;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid596;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid597;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, BufferSize - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BufferSize,
                   TplArray[Index]
                   );
    //
    // check whether buffersize is expected
    //
    if (BufferSize == sizeof (EFI_HANDLE)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid598;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid599;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid600;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:ExpectedSize - %d, BufferSize - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   sizeof (EFI_HANDLE),
                   BufferSize,
                   TplArray[Index]
                   );
    //
    // check whether handles are match
    //
    if (HandleBuffer[0] == HandleArray[0]) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid601;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid602;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid603;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // uninstall
    //
    gtBS->UninstallProtocolInterface (
            HandleArray[0],
            &mTestNoInterfaceProtocol1Guid,
            NULL
            );

    //
    // install again
    //
    Status = gtBS->InstallProtocolInterface (
                     &HandleArray[1],
                     &mTestNoInterfaceProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid604;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid605;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid606;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // stall 10 seconds to wait for event signal
    //
    SctPrint (L"Waiting a few seconds for signal ...\n");
    gtBS->Stall (STALL_10_SECONDS);

    //
    // init
    //
    BufferSize = sizeof (EFI_HANDLE) * 10;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandle (
                     ByRegisterNotify,
                     NULL,
                     Registration,
                     &BufferSize,
                     HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid607;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid608;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid609;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, BufferSize - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BufferSize,
                   TplArray[Index]
                   );
    //
    // check whether buffersize is expected
    //
    if (BufferSize == sizeof (EFI_HANDLE)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid610;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid611;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid612;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:ExpectedSize - %d, BufferSize - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   sizeof (EFI_HANDLE),
                   BufferSize,
                   TplArray[Index]
                   );
    //
    // check whether handles are match
    //
    if (HandleBuffer[0] == HandleArray[1]) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid613;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid614;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid615;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // call LocateHandle again, expected status is EFI_NOT_FOUND
    //
    BufferSize = sizeof (EFI_HANDLE) * 10;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandle (
                     ByRegisterNotify,
                     NULL,
                     Registration,
                     &BufferSize,
                     HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid616;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid617;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid618;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    gtBS->UninstallProtocolInterface (
            HandleArray[1],
            &mTestNoInterfaceProtocol1Guid,
            NULL
            );
  }

Done:
  if (NULL != Event) {
    gtBS->CloseEvent (Event);
  }

  if (NULL != HandleBuffer) {
    gtBS->FreePool (HandleBuffer);
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

//
// Checkpoint Functions for LocateHandleBuffer()
//

EFI_STATUS
EFIAPI
BBTestLocateHandleBufferInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  UINTN                 SavedNoHandles;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  NoHandles = 0;
  HandleBuffer = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Action 1: retrieve all handles in the system
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandleBuffer (
                     AllHandles,
                     NULL,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid052;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid053;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid054;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    SavedNoHandles = NoHandles;

    //
    // Action 2: add a new handle
    //
    Handle = NULL;
    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid055;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid056;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid057;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_ERROR(Status)) {
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandleBuffer (
                     AllHandles,
                     NULL,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid058;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid059;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid060;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    if (NoHandles == SavedNoHandles + 1) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid061;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid062;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid063;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedNo - %d, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   SavedNoHandles + 1,
                   NoHandles,
                   TplArray[Index]
                   );
    //
    // Action 3: remove the new handle
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid064;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid065;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid066;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandleBuffer (
                     AllHandles,
                     NULL,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid067;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid068;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid069;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    if (NoHandles == SavedNoHandles) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid070;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid071;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid072;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedNo - %d, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   SavedNoHandles,
                   NoHandles,
                   TplArray[Index]
                   );
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                    Status,
                    Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestLocateHandleBufferInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  EFI_EVENT             Event;
  VOID                  *Registration;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  Event = NULL;
  HandleBuffer = NULL;

  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) TestNotifyFunction0,
                   NULL,
                   &Event
                      );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->RegisterProtocolNotify (
                   &mTestNoInterfaceProtocol1Guid,
                   Event,
                   &Registration
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.RegisterProtocolNotify - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    Handle = NULL;

    HandleBuffer = NULL;
    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid073;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid074;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid075;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // stall 10 seconds to wait for event signal
    //
    SctPrint (L"Waiting a few seconds for signal ...\n");
    gtBS->Stall (STALL_10_SECONDS);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandleBuffer (
                     ByRegisterNotify,
                     NULL,
                     Registration,
                     &NoHandles,
                     &HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid076;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid077;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid078;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check whether buffersize is expected
    //
    if (1 == NoHandles) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid079;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid080;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid081;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint2",
                   L"%a:%d:ExpectedHandles - 1, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NoHandles,
                   TplArray[Index]
                   );
    //
    // check whether handles are match
    //
    if (Handle == HandleBuffer[0]) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid082;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid083;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid084;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint2",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // call LocateHandleBuffer again, expected status is EFI_NOT_FOUND
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandleBuffer (
                     ByRegisterNotify,
                     NULL,
                     Registration,
                     &NoHandles,
                     &HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid085;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid086;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid087;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    gtBS->UninstallProtocolInterface (
            Handle,
            &mTestNoInterfaceProtocol1Guid,
            NULL
            );
  }

Done:
  if (NULL != Event) {
    gtBS->CloseEvent (Event);
  }

  if (NULL != HandleBuffer) {
    gtBS->FreePool (HandleBuffer);
  }
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestLocateHandleBufferInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            HandleArray[10];
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 HandleIndex;
  UINTN                 MatchTimes;
  UINTN                 BufferIndex;
  VOID                  *Interface;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  HandleBuffer = NULL;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    gtBS->SetMem (HandleArray, 10 * sizeof (EFI_HANDLE), 0);

    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {

      Status = gtBS->InstallProtocolInterface (
                       &HandleArray[HandleIndex],
                       &mTestNoInterfaceProtocol1Guid,
                       EFI_NATIVE_INTERFACE,
                       NULL
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid088;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid089;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid090;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.LocateHandleBuffer - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }

    //
    // stall 10 seconds to wait for event signal
    //
    SctPrint (L"Waiting a few seconds for signal ...\n");
    gtBS->Stall (STALL_10_SECONDS);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid091;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid092;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid093;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check whether buffersize is expected
    //
    if (10 == NoHandles) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid094;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid095;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid096;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint3",
                   L"%a:%d:ExpectedNo - 10, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NoHandles,
                   TplArray[Index]
                   );
    //
    // check whether handles are match
    //
    MatchTimes = 0;
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      for (BufferIndex = 0; BufferIndex < 10; BufferIndex++) {
        if (HandleArray[HandleIndex] == HandleBuffer[BufferIndex]) {
          MatchTimes++;
        }
      }
    }
    if (10 == MatchTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid097;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid098;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid099;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateHandleBuffer - InterfaceTestCheckpoint3",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // each located handle supports TestNoInterfaceProtocol1
    //
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[HandleIndex],
                       &mTestNoInterfaceProtocol1Guid,
                       (VOID **) &Interface
                       );

      //
      // check status
      //
      if ((EFI_SUCCESS == Status) && (Interface == NULL)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid100;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid101;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid102;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.LocateHandleBuffer - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, HandleIndex - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     HandleIndex,
                     TplArray[Index]
                     );
    }

    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      gtBS->UninstallProtocolInterface (
              HandleArray[HandleIndex],
              &mTestNoInterfaceProtocol1Guid,
              NULL
              );
    }

    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return EFI_SUCCESS;
}

//
// Checkpoint Functions for HandleProtocol()
//

EFI_STATUS
EFIAPI
BBTestHandleProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;
  UINTN                 NewReinstallField;
  BOOLEAN               ReinstallFail;
  EFI_HANDLE            Handle;
  EFI_TPL               OldTpl;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance1);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance2);
  InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
  NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    IFTestProt1 = NULL;
    ReinstallFail = FALSE;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance1
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.InstallProtocolInterface - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid103;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid104;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid105;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.HandleProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);

    if ((ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id)
        && (0 == ProtocolAttributes.ReinstallField)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid106;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid107;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid108;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.HandleProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.ReinstallProtocolInterface - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      ReinstallFail = TRUE;
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid109;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid110;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid111;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.HandleProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);

    if ((ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id)
        && (NewReinstallField == ProtocolAttributes.ReinstallField)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid112;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid113;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid114;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.HandleProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );
NextLoop:
    //
    // restore environment
    //
    if (ReinstallFail) {
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance1
              );
    } else {
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance2
              );
    }
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

//
// Checkpoint Functions for SctLocateProtocol ()
//

EFI_STATUS
EFIAPI
BBTestLocateProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;
  EFI_HANDLE            Handle;
  EFI_TPL               OldTpl;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    IFTestProt1 = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.InstallProtocolInterface - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateProtocol (
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     (VOID **) &IFTestProt1
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid115;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid116;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid117;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_ERROR(Status)) {
      goto NextLoop;
    }

    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);

    if ((ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id)
        && (0 == ProtocolAttributes.ReinstallField)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid118;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid119;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid120;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

NextLoop:
    //
    // restore environment
    //
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance
            );
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestLocateProtocolInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;
  EFI_EVENT             Event;
  VOID                  *Registration;
  EFI_HANDLE            Handle;
  EFI_TPL               OldTpl;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Event = NULL;
  //
  // event for register notify
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_CALLBACK,
                   TestNotifyFunction0,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // register for InterfaceFunctionTestProtocol1
  //
  Status = gtBS->RegisterProtocolNotify (
                        &mInterfaceFunctionTestProtocol1Guid,
                        Event,
                        &Registration
                        );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.RegisterProtocolNotify - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    IFTestProt1 = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.InstallProtocolInterface - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateProtocol (
                     &mInterfaceFunctionTestProtocol1Guid,
                     Registration,
                     (VOID **) &IFTestProt1
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid121;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid122;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid123;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateProtocol - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_ERROR(Status)) {
      goto NextLoop;
    }

    //
    // access the protocol function
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);

    if ((ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id)
        && (0 == ProtocolAttributes.ReinstallField)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid124;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid125;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid126;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateProtocol - InterfaceTestCheckpoint2",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );
    //
    // LocateProtocol again, this time return EFI_NOT_FOUND,
    // since no new protocol installed for the "Registration"
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateProtocol (
                     &mInterfaceFunctionTestProtocol1Guid,
                     Registration,
                     (VOID **) &IFTestProt1
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid127;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid128;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid129;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateProtocol - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
NextLoop:
    //
    // restore environment
    //
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance
            );
  }

Done:

  gtBS->CloseEvent (Event);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestLocateProtocolInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_HANDLE            Handle;
  EFI_TPL               OldTpl;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;
  VOID                  *Protocol;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.InstallProtocolInterface - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->LocateProtocol (
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     (VOID **) &Protocol
                     );
    gtBS->RestoreTPL (OldTpl);

    if ((EFI_SUCCESS == Status) && (Protocol == NULL)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid619;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid620;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid621;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.LocateProtocol - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_ERROR(Status)) {
      goto NextLoop;
    }

NextLoop:
    //
    // restore environment
    //
    gtBS->UninstallProtocolInterface (
              Handle,
              &mTestNoInterfaceProtocol1Guid,
              NULL
              );
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

//
// Checkpoint Functions for LocateDevicePath()
//

EFI_STATUS
EFIAPI
BBTestLocateDevicePathInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath4;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath5;

  EFI_DEVICE_PATH_PROTOCOL                *TestDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL                *TestDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL                *TestDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL                *TestDevicePath4;
  EFI_DEVICE_PATH_PROTOCOL                *TestDevicePath5;

  EFI_DEVICE_PATH_PROTOCOL                *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL                *SavedDevicePath;
  EFI_DEVICE_PATH_PROTOCOL                *ExpectedReturnedDevicePath;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_5      InterfaceFunctionTestProt5Instance;

  EFI_DEVICE_PATH_PROTOCOL                *DevicePathArray[5];
  VOID                                    *ProtocolInstanceArray[5];
  EFI_GUID                                *ProtocolGuidArray[5];
  VOID                                    *ProtocolArray[5];
  EFI_HANDLE                              HandleArray[5];
  UINTN                                   DeviceIndex;
  UINTN                                   AnotherIndex;
  EFI_TPL                                 OldTpl;
  EFI_TEST_ASSERTION                      AssertionType;
  UINTN                                   Index;
  EFI_STATUS                              Status;
  EFI_HANDLE                              Handle;

  UINTN                                   Numbers;
  EFI_GUID                                TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  CreateVendorDevicePath (&VendorDevicePath1, mVendorDevicePath1Guid);
  CreateVendorDevicePathNode (&VendorDevicePath2, mVendorDevicePath2Guid);
  CreateVendorDevicePathNode (&VendorDevicePath3, mVendorDevicePath3Guid);
  CreateVendorDevicePathNode (&VendorDevicePath4, mVendorDevicePath4Guid);
  CreateVendorDevicePathNode (&VendorDevicePath5, mVendorDevicePath5Guid);

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);
  InitializeInterfaceFunctionTestProtocol5 (&InterfaceFunctionTestProt5Instance);

  ProtocolInstanceArray[0] = (VOID*)&InterfaceFunctionTestProt1Instance;
  ProtocolInstanceArray[1] = (VOID*)&InterfaceFunctionTestProt2Instance;
  ProtocolInstanceArray[2] = (VOID*)&InterfaceFunctionTestProt3Instance;
  ProtocolInstanceArray[3] = (VOID*)&InterfaceFunctionTestProt4Instance;
  ProtocolInstanceArray[4] = (VOID*)&InterfaceFunctionTestProt5Instance;

  ProtocolGuidArray[0] = &mInterfaceFunctionTestProtocol1Guid;
  ProtocolGuidArray[1] = &mInterfaceFunctionTestProtocol2Guid;
  ProtocolGuidArray[2] = &mInterfaceFunctionTestProtocol3Guid;
  ProtocolGuidArray[3] = &mInterfaceFunctionTestProtocol4Guid;
  ProtocolGuidArray[4] = &mInterfaceFunctionTestProtocol5Guid;

  //
  // the device paths below should free before leave this function:
  // VendorDevicePath1 ~ 5, TestDevicePath2 ~ 5.
  //
  TestDevicePath1 = VendorDevicePath1;
  TestDevicePath2 = SctAppendDevicePathNode (TestDevicePath1, VendorDevicePath2);
  TestDevicePath3 = SctAppendDevicePathNode (TestDevicePath2, VendorDevicePath3);
  TestDevicePath4 = SctAppendDevicePathNode (TestDevicePath3, VendorDevicePath4);
  TestDevicePath5 = SctAppendDevicePathNode (TestDevicePath4, VendorDevicePath5);

  DevicePathArray[0] = TestDevicePath1;
  DevicePathArray[1] = TestDevicePath2;
  DevicePathArray[2] = TestDevicePath3;
  DevicePathArray[3] = TestDevicePath4;
  DevicePathArray[4] = TestDevicePath5;

  gtBS->SetMem (HandleArray, 5 * sizeof (EFI_HANDLE), 0);

  for (DeviceIndex = 0; DeviceIndex < 5; DeviceIndex++) {
    Status = gtBS->InstallMultipleProtocolInterfaces (
                     &HandleArray[DeviceIndex],
                     ProtocolGuidArray[DeviceIndex],
                     ProtocolInstanceArray[DeviceIndex],
                     &gEfiDevicePathProtocolGuid,
                     DevicePathArray[DeviceIndex],
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.InstallMultipleProtocolInterfaces - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (DeviceIndex = 4; DeviceIndex != 0; DeviceIndex--) {

      //
      // locate protocol from protocol1 ~ (5 - DeviceIndex)
      //
      for (AnotherIndex = 0; AnotherIndex <= DeviceIndex; AnotherIndex++) {

        //
        // init
        //
        TempDevicePath = SctDuplicateDevicePath (DevicePathArray[DeviceIndex]);
        //
        // for the use of free resource
        //
        SavedDevicePath = TempDevicePath;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Handle = NULL;
        Status = gtBS->LocateDevicePath (
                         ProtocolGuidArray[AnotherIndex],
                         &TempDevicePath,
                         &Handle
                         );
        gtBS->RestoreTPL (OldTpl);

        //
        // Check return status
        //
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid130;
        } else if (Index == 1) {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid131;
        } else {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid132;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"BS.LocateDevicePath - InterfaceTestCheckpoint1",
                       L"%a:%d:Status - %r, DeviceIndex - %d, AnotherIndex - %d, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       DeviceIndex,
                       AnotherIndex,
                       TplArray[Index]
                       );
        //
        // check returned device path
        //
        ExpectedReturnedDevicePath =  (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)SavedDevicePath +
                               (AnotherIndex + 1) * sizeof (VENDOR_DEVICE_PATH));
        if (!SctCompareMem (
               TempDevicePath,
               ExpectedReturnedDevicePath,
               SctDevicePathSize (TempDevicePath)
               )) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid133;
        } else if (Index == 1) {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid134;
        } else {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid135;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"BS.LocateDevicePath - InterfaceTestCheckpoint1",
                       L"%a:%d:TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index]
                       );
        //
        // free the temporary device path
        //
        gtBS->FreePool (SavedDevicePath);

        //
        // check returned handle with the specified protocol
        //
        Status = gtBS->HandleProtocol (
                         Handle,
                         ProtocolGuidArray[AnotherIndex],
                         (VOID **) &ProtocolArray[AnotherIndex]
                         );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid136;
        } else if (Index == 1) {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid137;
        } else {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid138;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"BS.LocateDevicePath - InterfaceTestCheckpoint1",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          break;
        }
      }
    }
  }

Done:

  //
  // uninstall those protocols
  //
  for (DeviceIndex = 0; DeviceIndex < 5; DeviceIndex++) {
    if (NULL != HandleArray[DeviceIndex]) {
      Status = gtBS->UninstallMultipleProtocolInterfaces (
                       HandleArray[DeviceIndex],
                       ProtocolGuidArray[DeviceIndex],
                       ProtocolInstanceArray[DeviceIndex],
                       &gEfiDevicePathProtocolGuid,
                       DevicePathArray[DeviceIndex],
                       NULL
                       );
    }
  }

  //
  // release vendor device paths
  //
  FreeVendorDevicePath (VendorDevicePath1);
  FreeVendorDevicePathNode (VendorDevicePath2);
  FreeVendorDevicePathNode (VendorDevicePath3);
  FreeVendorDevicePathNode (VendorDevicePath4);
  FreeVendorDevicePathNode (VendorDevicePath5);

  //
  // free other device paths
  //
  gtBS->FreePool (TestDevicePath2);
  gtBS->FreePool (TestDevicePath3);
  gtBS->FreePool (TestDevicePath4);
  gtBS->FreePool (TestDevicePath5);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

//
// Checkpoint Functions for ProtocolsPerHandle()
//

EFI_STATUS
EFIAPI
BBTestProtocolsPerHandleInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;

  EFI_GUID              **ProtocolGuidBuffer;
  UINTN                 ProtocolBufferCount;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_5      InterfaceFunctionTestProt5Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);
  InitializeInterfaceFunctionTestProtocol5 (&InterfaceFunctionTestProt5Instance);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;
    Status = gtBS->InstallMultipleProtocolInterfaces (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol3Guid,
                     &InterfaceFunctionTestProt3Instance,
                     &mInterfaceFunctionTestProtocol4Guid,
                     &InterfaceFunctionTestProt4Instance,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.InstallMultipleProtocolInterfaces - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ProtocolsPerHandle (
                     Handle,
                     &ProtocolGuidBuffer,
                     &ProtocolBufferCount
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid139;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid140;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid141;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ProtocolsPerHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check protocol count
    //
    if (4 == ProtocolBufferCount) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid142;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid143;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid144;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ProtocolsPerHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedProtNumber - 4, Actual - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolBufferCount,
                   TplArray[Index]
                   );
    gtBS->FreePool ((VOID*)ProtocolGuidBuffer);

    //
    // add a protocol
    //
    Status = gtBS->InstallMultipleProtocolInterfaces (
                     &Handle,
                     &mInterfaceFunctionTestProtocol5Guid,
                     &InterfaceFunctionTestProt5Instance,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.InstallMultipleProtocolInterfaces - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol3Guid,
              &InterfaceFunctionTestProt3Instance,
              &mInterfaceFunctionTestProtocol4Guid,
              &InterfaceFunctionTestProt4Instance,
              NULL
              );
      continue;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ProtocolsPerHandle (
                     Handle,
                     &ProtocolGuidBuffer,
                     &ProtocolBufferCount
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid145;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid146;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid147;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ProtocolsPerHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check protocol count
    //
    if (5 == ProtocolBufferCount) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid148;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid149;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid150;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ProtocolsPerHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedProtNumber - 5, Actual - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolBufferCount,
                   TplArray[Index]
                   );
    gtBS->FreePool ((VOID*)ProtocolGuidBuffer);

    //
    // remove 2 protocols
    //
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.InstallMultipleProtocolInterfaces - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol3Guid,
              &InterfaceFunctionTestProt3Instance,
              &mInterfaceFunctionTestProtocol4Guid,
              &InterfaceFunctionTestProt4Instance,
              &mInterfaceFunctionTestProtocol5Guid,
              &InterfaceFunctionTestProt5Instance,
              NULL
              );
      continue;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ProtocolsPerHandle (
                    Handle,
                    &ProtocolGuidBuffer,
                    &ProtocolBufferCount
                    );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid151;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid152;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid153;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ProtocolsPerHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check protocol count
    //
    if (3 == ProtocolBufferCount) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid154;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid155;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid156;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ProtocolsPerHandle - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedProtNumber - 3, Actual - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolBufferCount,
                   TplArray[Index]
                   );
    gtBS->UninstallMultipleProtocolInterfaces (
            Handle,
            &mInterfaceFunctionTestProtocol3Guid,
            &InterfaceFunctionTestProt3Instance,
            &mInterfaceFunctionTestProtocol4Guid,
            &InterfaceFunctionTestProt4Instance,
            &mInterfaceFunctionTestProtocol5Guid,
            &InterfaceFunctionTestProt5Instance,
            NULL
            );
    gtBS->FreePool ((VOID*)ProtocolGuidBuffer);
  }

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest111()
//

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            AgentHandleArray[2];
  EFI_HANDLE            ControllerHandleArray[2];
  UINT32                AttributesArray[7];
  UINTN                 Indexi, Indexj, RetryIndex, AttributesIndex;


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  AgentHandleArray[0] = NULL;
  AgentHandleArray[1] = mImageHandle;
  ControllerHandleArray[0] = NULL;
  ControllerHandleArray[1] = mImageHandle;
  AttributesArray[0] = EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL;
  AttributesArray[1] = EFI_OPEN_PROTOCOL_GET_PROTOCOL;
  AttributesArray[2] = EFI_OPEN_PROTOCOL_TEST_PROTOCOL;
  AttributesArray[3] = EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER;
  AttributesArray[4] = EFI_OPEN_PROTOCOL_BY_DRIVER;
  AttributesArray[5] = EFI_OPEN_PROTOCOL_EXCLUSIVE;
  AttributesArray[6] = EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE;


  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt1Instance
                   );
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (RetryIndex = 0; RetryIndex < 2; RetryIndex++) {

    for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

      for (Indexi = 0; Indexi < 2; Indexi++) {

        for (Indexj = 0; Indexj < 2; Indexj++) {

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = gtBS->OpenProtocol (
                           Handle,
                           &mInterfaceFunctionTestProtocol1Guid,
                           (VOID **) &IFTestProt1,
                           AgentHandleArray[Indexi],
                           ControllerHandleArray[Indexj],
                           EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                           );
          gtBS->RestoreTPL (OldTpl);
          //
          // check status
          //
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid157;
          } else if (Index == 1) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid158;
          } else {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid159;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"BS.OpenProtocolInterfaceTest111 - Checkpoint1",
                         L"%a:%d:Status - %r, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index]
                         );
        }
      }
    }

    //
    // Open Protocols BY all kinds of attributes
    //
    for (AttributesIndex = 0; AttributesIndex < 2; AttributesIndex++) {

      for (Indexi = 0; Indexi < 2; Indexi++) {

        for (Indexj = 0; Indexj < 2; Indexj++) {

          //
          // bugbug: some attributes may fail by open
          //
          gtBS->OpenProtocol (
                  Handle,
                  &mInterfaceFunctionTestProtocol1Guid,
                  (VOID **) &IFTestProt1,
                  AgentHandleArray[Indexi],
                  ControllerHandleArray[Indexj],
                  AttributesArray[AttributesIndex]
                  );
        }
      }
    }
  }

  //
  // restore environment
  //
  for (Indexi = 0; Indexi < 2; Indexi++) {

    for (Indexj = 0; Indexj < 2; Indexj++) {
      gtBS->CloseProtocol (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              AgentHandleArray[Indexi],
              ControllerHandleArray[Indexj]
              );
    }
  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            AgentHandleArray[2];
  EFI_HANDLE            ControllerHandleArray[2];
  UINT32                AttributesArray[7];
  UINTN                 Indexi, Indexj, RetryIndex, AttributesIndex;


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  AgentHandleArray[0] = NULL;
  AgentHandleArray[1] = mImageHandle;
  ControllerHandleArray[0] = NULL;
  ControllerHandleArray[1] = mImageHandle;
  AttributesArray[0] = EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL;
  AttributesArray[1] = EFI_OPEN_PROTOCOL_GET_PROTOCOL;
  AttributesArray[2] = EFI_OPEN_PROTOCOL_TEST_PROTOCOL;
  AttributesArray[3] = EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER;
  AttributesArray[4] = EFI_OPEN_PROTOCOL_BY_DRIVER;
  AttributesArray[5] = EFI_OPEN_PROTOCOL_EXCLUSIVE;
  AttributesArray[6] = EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE;


  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt1Instance
                   );
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (RetryIndex = 0; RetryIndex < 2; RetryIndex++) {

    for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

      for (Indexi = 0; Indexi < 2; Indexi++) {

        for (Indexj = 0; Indexj < 2; Indexj++) {

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = gtBS->OpenProtocol (
                           Handle,
                           &mInterfaceFunctionTestProtocol1Guid,
                           (VOID **) &IFTestProt1,
                           AgentHandleArray[Indexi],
                           ControllerHandleArray[Indexj],
                           EFI_OPEN_PROTOCOL_GET_PROTOCOL
                           );
          gtBS->RestoreTPL (OldTpl);
          //
          // check status
          //
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid160;
          } else if (Index == 1) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid161;
          } else {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid162;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"BS.OpenProtocolInterfaceTest111 - Checkpoint2",
                         L"%a:%d:Status - %r, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index]
                         );
        }
      }
    }

    //
    // Open Protocols BY all kinds of attributes
    //
    for (AttributesIndex = 0; AttributesIndex < 2; AttributesIndex++) {

      for (Indexi = 0; Indexi < 2; Indexi++) {

        for (Indexj = 0; Indexj < 2; Indexj++) {

          //
          // bugbug: some attributes may fail by open
          //
          gtBS->OpenProtocol (
                  Handle,
                  &mInterfaceFunctionTestProtocol1Guid,
                  (VOID **) &IFTestProt1,
                  AgentHandleArray[Indexi],
                  ControllerHandleArray[Indexj],
                  AttributesArray[AttributesIndex]
                  );
        }
      }
    }
  }

  //
  // restore environment
  //
  for (Indexi = 0; Indexi < 2; Indexi++) {

    for (Indexj = 0; Indexj < 2; Indexj++) {
      gtBS->CloseProtocol (
                Handle,
                &mInterfaceFunctionTestProtocol1Guid,
                AgentHandleArray[Indexi],
                ControllerHandleArray[Indexj]
                  );
    }
  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            AgentHandleArray[2];
  EFI_HANDLE            ControllerHandleArray[2];
  UINT32                AttributesArray[7];
  UINTN                 Indexi, Indexj, RetryIndex, AttributesIndex;


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  AgentHandleArray[0] = NULL;
  AgentHandleArray[1] = mImageHandle;
  ControllerHandleArray[0] = NULL;
  ControllerHandleArray[1] = mImageHandle;
  AttributesArray[0] = EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL;
  AttributesArray[1] = EFI_OPEN_PROTOCOL_GET_PROTOCOL;
  AttributesArray[2] = EFI_OPEN_PROTOCOL_TEST_PROTOCOL;
  AttributesArray[3] = EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER;
  AttributesArray[4] = EFI_OPEN_PROTOCOL_BY_DRIVER;
  AttributesArray[5] = EFI_OPEN_PROTOCOL_EXCLUSIVE;
  AttributesArray[6] = EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE;


  Status = gtBS->InstallProtocolInterface (
                          &Handle,
                          &mInterfaceFunctionTestProtocol1Guid,
                          EFI_NATIVE_INTERFACE,
                          &InterfaceFunctionTestProt1Instance
                          );
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (RetryIndex = 0; RetryIndex < 2; RetryIndex++) {

    for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

      for (Indexi = 0; Indexi < 2; Indexi++) {

        for (Indexj = 0; Indexj < 2; Indexj++) {

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = gtBS->OpenProtocol (
                           Handle,
                           &mInterfaceFunctionTestProtocol1Guid,
                           (VOID **) &IFTestProt1,
                           AgentHandleArray[Indexi],
                           ControllerHandleArray[Indexj],
                           EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                           );
          gtBS->RestoreTPL (OldTpl);
          //
          // check status
          //
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid163;
          } else if (Index == 1) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid164;
          } else {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid165;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"BS.OpenProtocolInterfaceTest111 - Checkpoint3",
                         L"%a:%d:Status - %r, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index]
                         );
        }
      }
    }

    //
    // Open Protocols BY all kinds of attributes
    //
    for (AttributesIndex = 0; AttributesIndex < 2; AttributesIndex++) {

      for (Indexi = 0; Indexi < 2; Indexi++) {

        for (Indexj = 0; Indexj < 2; Indexj++) {

          //
          // bugbug: some attributes may fail by open
          //
          gtBS->OpenProtocol (
                  Handle,
                  &mInterfaceFunctionTestProtocol1Guid,
                  (VOID **) &IFTestProt1,
                  AgentHandleArray[Indexi],
                  ControllerHandleArray[Indexj],
                  AttributesArray[AttributesIndex]
                  );
        }
      }
    }
  }

  //
  // restore environment
  //
  for (Indexi = 0; Indexi < 2; Indexi++) {

    for (Indexj = 0; Indexj < 2; Indexj++) {
      gtBS->CloseProtocol (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              AgentHandleArray[Indexi],
              ControllerHandleArray[Indexj]
              );
    }
  }
  gtBS->UninstallProtocolInterface (
                          Handle,
                          &mInterfaceFunctionTestProtocol1Guid,
                          &InterfaceFunctionTestProt1Instance
                          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            AgentHandleArray[2];
  EFI_HANDLE            ControllerHandleArray[2];
  UINT32                AttributesArray[7];
  UINTN                 Indexi, Indexj, RetryIndex, AttributesIndex;
  EFI_STATUS            Status1, Status2;


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  AgentHandleArray[0] = NULL;
  AgentHandleArray[1] = mImageHandle;
  ControllerHandleArray[0] = NULL;
  ControllerHandleArray[1] = mImageHandle;
  AttributesArray[0] = EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL;
  AttributesArray[1] = EFI_OPEN_PROTOCOL_GET_PROTOCOL;
  AttributesArray[2] = EFI_OPEN_PROTOCOL_TEST_PROTOCOL;
  AttributesArray[3] = EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER;
  AttributesArray[4] = EFI_OPEN_PROTOCOL_BY_DRIVER;
  AttributesArray[5] = EFI_OPEN_PROTOCOL_EXCLUSIVE;
  AttributesArray[6] = EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE;


  Status1 = gtBS->InstallProtocolInterface (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (RetryIndex = 0; RetryIndex < 2; RetryIndex++) {

    for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->OpenProtocol (
                       Handle,
                       &mInterfaceFunctionTestProtocol1Guid,
                       (VOID **) &IFTestProt1,
                       mImageHandle,
                       ChildHandle,
                       EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid166;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid167;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid168;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest111 - Checkpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }


    //
    // Open Protocols BY all kinds of attributes
    //
    for (AttributesIndex = 0; AttributesIndex < 2; AttributesIndex++) {

      for (Indexi = 0; Indexi < 2; Indexi++) {

        for (Indexj = 0; Indexj < 2; Indexj++) {

          //
          // bugbug: some attributes may fail by open
          //
          gtBS->OpenProtocol (
                  Handle,
                  &mInterfaceFunctionTestProtocol1Guid,
                  (VOID **) &IFTestProt1,
                  AgentHandleArray[Indexi],
                  ControllerHandleArray[Indexj],
                  AttributesArray[AttributesIndex]
                  );
        }
      }
    }
  }

  //
  // restore environment
  //
  for (Indexi = 0; Indexi < 2; Indexi++) {

    for (Indexj = 0; Indexj < 2; Indexj++) {
      gtBS->CloseProtocol (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              AgentHandleArray[Indexi],
              ControllerHandleArray[Indexj]
              );
    }
  }

  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          mImageHandle,
          ChildHandle
          );

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            ControllerHandleArray[2];
  UINTN                 ControllerHandleIndex;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  ControllerHandleArray[0] = NULL;
  ControllerHandleArray[1] = mImageHandle;

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt1Instance
                   );
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r,",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (ControllerHandleIndex = 0; ControllerHandleIndex < 2; ControllerHandleIndex++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->OpenProtocol (
                       Handle,
                       &mInterfaceFunctionTestProtocol1Guid,
                       (VOID **) &IFTestProt1,
                       mImageHandle,
                       ControllerHandleArray[ControllerHandleIndex],
                       EFI_OPEN_PROTOCOL_EXCLUSIVE
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid169;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid170;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid171;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest111 - Checkpoint5",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // close the protocol for next loop test
      //
      gtBS->CloseProtocol (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              mImageHandle,
              ControllerHandleArray[ControllerHandleIndex]
              );

    }
  }

  //
  // restore environment
  //

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            Status1, Status2;


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid172;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid173;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid174;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // close the protocol for next loop test
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            ChildHandle
            );
  }

  //
  // restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
      StandardLib,
      EFI_TEST_ASSERTION_FAILED,
      gTestGenericFailureGuid,
      L" CheckForCleanEnvironment - restore environment",
      L"%a:%d:Status - %r, Number - %d",
      __FILE__,
      (UINTN)__LINE__,
      Status,
      Numbers
      );
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            Status1, Status2;


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid175;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid176;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid177;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // close the protocol for next loop test
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            ChildHandle
            );
  }

  //
  // restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            Status1, Status2, Status3;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN               Numbers;
  EFI_GUID            TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    &InterfaceFunctionTestProt1Instance,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &InterfaceFunctionTestProt2Instance,
                    &mInterfaceFunctionTestProtocol3Guid,
                    &InterfaceFunctionTestProt3Instance,
                    NULL
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol4Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt4Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  //
  // open protocol1 BY_DRIVER
  //
  Status1 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    (VOID **) &IFTestProt1,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_BY_DRIVER
                    );
  //
  // open protocol2 EXCLUSIVE
  //
  Status2 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    (VOID **) &IFTestProt2,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_EXCLUSIVE
                    );
  //
  // open protocol3 BY_DRIVER | EXCLUSIVE
  //
  Status3 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol3Guid,
                    (VOID **) &IFTestProt3,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.OpenProtocol - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Open protocol1 again BY_DRIVER
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ALREADY_STARTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid178;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid179;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid180;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                 );
    //
    // Open protocol2 again BY_DRIVER
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid181;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid182;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid183;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Open protocol3 again BY_DRIVER
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol3Guid,
                     (VOID **) &IFTestProt3,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid184;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid185;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid186;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

Done:
  //
  // restore environment
  //
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          mImageHandle,
          ChildHandle
          );
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol2Guid,
          mImageHandle,
          ChildHandle
          );
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol3Guid,
          mImageHandle,
          ChildHandle
          );

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance,
          NULL
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol4Guid,
          &InterfaceFunctionTestProt4Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            Status1, Status2, Status3;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    &InterfaceFunctionTestProt1Instance,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &InterfaceFunctionTestProt2Instance,
                    &mInterfaceFunctionTestProtocol3Guid,
                    &InterfaceFunctionTestProt3Instance,
                    NULL
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol4Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt4Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  //
  // open protocol1 BY_DRIVER
  //
  Status1 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    (VOID **) &IFTestProt1,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_BY_DRIVER
                    );
  //
  // open protocol2 EXCLUSIVE
  //
  Status2 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    (VOID **) &IFTestProt2,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_EXCLUSIVE
                    );
  //
  // open protocol3 BY_DRIVER | EXCLUSIVE
  //
  Status3 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol3Guid,
                    (VOID **) &IFTestProt3,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.OpenProtocol - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Open protocol1 again EXCLUSIVE
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid187;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid188;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid189;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Open protocol2 again EXCLUSIVE
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid190;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid191;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid192;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Open protocol3 again EXCLUSIVE
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol3Guid,
                     (VOID **) &IFTestProt3,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid193;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid194;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid195;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

Done:
  //
  // restore environment
  //
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          mImageHandle,
          ChildHandle
          );
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol2Guid,
          mImageHandle,
          ChildHandle
          );
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol3Guid,
          mImageHandle,
          ChildHandle
          );
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance,
          NULL
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol4Guid,
          &InterfaceFunctionTestProt4Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            Status1, Status2, Status3;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    &InterfaceFunctionTestProt1Instance,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &InterfaceFunctionTestProt2Instance,
                    &mInterfaceFunctionTestProtocol3Guid,
                    &InterfaceFunctionTestProt3Instance,
                    NULL
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol4Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt4Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  //
  // open protocol1 BY_DRIVER
  //
  Status1 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    (VOID **) &IFTestProt1,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_BY_DRIVER
                    );
  //
  // open protocol2 EXCLUSIVE
  //
  Status2 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    (VOID **) &IFTestProt2,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_EXCLUSIVE
                    );
  //
  // open protocol2 BY_DRIVER | EXCLUSIVE
  //
  Status3 = gtBS->OpenProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol3Guid,
                    (VOID **) &IFTestProt3,
                    mImageHandle,
                    ChildHandle,
                    EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.OpenProtocol - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Open protocol1 again BY_DRIVER | EXCLUSIVE
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid196;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid197;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid198;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Open protocol2 again BY_DRIVER | EXCLUSIVE
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid199;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid200;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid201;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Open protocol3 again BY_DRIVER | EXCLUSIVE
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol3Guid,
                     (VOID **) &IFTestProt3,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ALREADY_STARTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid202;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid203;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid204;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest111 - Checkpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

Done:
  //
  // restore environment
  //
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          mImageHandle,
          ChildHandle
          );
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol2Guid,
          mImageHandle,
          ChildHandle
          );
  gtBS->CloseProtocol (
          Handle,
          &mInterfaceFunctionTestProtocol3Guid,
          mImageHandle,
          ChildHandle
          );
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance,
          NULL
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol4Guid,
          &InterfaceFunctionTestProt4Instance
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}


//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest222()
//

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle1;
  EFI_HANDLE            Handle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            DriverImageHandle;
  EFI_STATUS            NextStatus;
  UINTN                 StatusIndex;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle1 = NULL;
  Handle2 = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle1,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &Handle2,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // open protocol2 BY_HANDLE_PROTOCOL
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle2,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid205;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid206;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid207;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // load & start external driver
    //
    Status = LoadStartImage (
               StandardLib, mImageHandle,
               TEST_DRIVER_1_NAME,
               &DriverImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->CloseProtocol (
              Handle2,
              &mInterfaceFunctionTestProtocol2Guid,
              mImageHandle,
              NULL
              );
      goto Done;
    }

    //
    // check the status reported by the external driver
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid208;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid209;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid210;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint1",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 2; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_SUCCESS == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid211;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid212;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid213;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest222 - Checkpoint1",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // open protocol1 BY_HANDLE_PROTOCOL
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                      Handle1,
                      &mInterfaceFunctionTestProtocol1Guid,
                      (VOID **) &IFTestProt1,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                      );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid214;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid215;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid216;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // unload the external driver
    //
    gtBS->UnloadImage (DriverImageHandle);
    gtBS->CloseProtocol (
            Handle1,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            NULL
            );
    gtBS->CloseProtocol (
            Handle2,
            &mInterfaceFunctionTestProtocol2Guid,
            mImageHandle,
            NULL
            );
  }
  Status = EFI_SUCCESS;
Done:
  gtBS->UninstallProtocolInterface (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle1;
  EFI_HANDLE            Handle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            DriverImageHandle;
  EFI_STATUS            NextStatus;
  EFI_STATUS            StatusIndex;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle1 = NULL;
  Handle2 = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle1,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &Handle2,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // open protocol2 GET_PROTOCOL
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle2,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_GET_PROTOCOL
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid217;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid218;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid219;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // load & start external driver
    //
    Status = LoadStartImage (
               StandardLib, mImageHandle,
               TEST_DRIVER_2_NAME,
               &DriverImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->CloseProtocol (
              Handle2,
              &mInterfaceFunctionTestProtocol2Guid,
              mImageHandle,
              NULL
              );
      goto Done;
    }

    //
    // check the status reported by the external driver
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid220;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid221;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid222;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint2",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 2; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_SUCCESS == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid223;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid224;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid225;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest222 - Checkpoint2",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // open protocol1 GET_PROTOCOL
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle1,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_GET_PROTOCOL
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid226;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid227;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid228;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // unload the external driver
    //
    gtBS->UnloadImage (DriverImageHandle);

    gtBS->CloseProtocol (
            Handle2,
            &mInterfaceFunctionTestProtocol2Guid,
            mImageHandle,
            NULL
            );
    gtBS->CloseProtocol (
            Handle1,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            NULL
            );
  }
  Status = EFI_SUCCESS;
Done:
  gtBS->UninstallProtocolInterface (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle1;
  EFI_HANDLE            Handle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            DriverImageHandle;
  EFI_STATUS            NextStatus;
  UINTN                 StatusIndex;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle1 = NULL;
  Handle2 = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle1,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &Handle2,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // open protocol2 TEST_PROTOCOL
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle2,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid229;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid230;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid231;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // load & start external driver
    //
    Status = LoadStartImage (
               StandardLib, mImageHandle,
               TEST_DRIVER_3_NAME,
               &DriverImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->CloseProtocol (
              Handle2,
              &mInterfaceFunctionTestProtocol2Guid,
              mImageHandle,
              NULL
              );
      goto Done;
    }

    //
    // check the status reported by the external driver
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid232;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid233;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid234;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint3",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 2; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_SUCCESS == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid235;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid236;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid237;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest222 - Checkpoint3",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // open protocol1 GET_PROTOCOL
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle1,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_GET_PROTOCOL
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid238;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid239;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid240;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // unload the external driver
    //
    gtBS->UnloadImage (DriverImageHandle);

    gtBS->CloseProtocol (
            Handle2,
            &mInterfaceFunctionTestProtocol2Guid,
            mImageHandle,
            NULL
            );
    gtBS->CloseProtocol (
            Handle1,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            NULL
            );
  }

  Status = EFI_SUCCESS;
Done:
  gtBS->UninstallProtocolInterface (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle1;
  EFI_HANDLE            Handle2;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status3;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            DriverImageHandle;
  EFI_STATUS            NextStatus;
  UINTN                 StatusIndex;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle1 = NULL;
  Handle2 = NULL;
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle1,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &Handle2,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  Status3 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol3Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt3Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // open protocol2 BY_CHILD_CONTROLLER
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle2,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid241;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid242;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid243;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // load & start external driver
    //
    Status = LoadStartImage (
               StandardLib, mImageHandle,
               TEST_DRIVER_4_NAME,
               &DriverImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->CloseProtocol (
              Handle2,
              &mInterfaceFunctionTestProtocol2Guid,
              mImageHandle,
              ChildHandle
              );
      goto Done;
    }

    //
    // check the status reported by the external driver
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid244;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid245;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid246;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint4",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                 );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 2; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_SUCCESS == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid247;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid248;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid249;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest222 - Checkpoint4",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // open protocol1 BY_CHILD_CONTROLLER
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle1,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid250;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid251;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid252;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // unload the external driver
    //
    gtBS->UnloadImage (DriverImageHandle);

    gtBS->CloseProtocol (
            Handle2,
            &mInterfaceFunctionTestProtocol2Guid,
            mImageHandle,
            ChildHandle
            );
    gtBS->CloseProtocol (
            Handle1,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            ChildHandle
            );
  }

  Status = EFI_SUCCESS;
Done:
  gtBS->UninstallProtocolInterface (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle1;
  EFI_HANDLE            Handle2;
  EFI_HANDLE            Handle3;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status3;
  EFI_STATUS            Status4;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            DriverImageHandle;
  EFI_STATUS            NextStatus;
  UINTN                 StatusIndex;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle1 = NULL;
  Handle2 = NULL;
  Handle3 = NULL;
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle1,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &Handle2,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  Status3 = gtBS->InstallProtocolInterface (
                    &Handle3,
                    &mInterfaceFunctionTestProtocol3Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt3Instance
                    );
  Status4 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol4Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt4Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)
      || EFI_ERROR(Status3) || EFI_ERROR(Status4)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r, Status4 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // load & start external driver5
    // (open protocol1 BY_DRIVER; open protocol2 EXCLUSIVE;
    //  open protocol3 BY_DRIVER | EXCLUSIVE
    //

    Status = LoadStartImage (
               StandardLib,
               mImageHandle,
               TEST_DRIVER_5_NAME,
               &DriverImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
    //
    // check the status reported by the external driver
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid253;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid254;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid255;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint5",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 3; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_SUCCESS == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid256;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid257;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid258;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest222 - Checkpoint5",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // open protocol1 ~ 3 BY_DRIVER
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                      Handle1,
                      &mInterfaceFunctionTestProtocol1Guid,
                      (VOID **) &IFTestProt1,
                      mImageHandle,
                      ChildHandle,
                      EFI_OPEN_PROTOCOL_BY_DRIVER
                      );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid259;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid260;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid261;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle2,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid262;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid263;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid264;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle3,
                     &mInterfaceFunctionTestProtocol3Guid,
                     (VOID **) &IFTestProt3,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid265;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid266;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid267;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // unload the external driver
    //
    gtBS->UnloadImage (DriverImageHandle);

    gtBS->CloseProtocol (
            Handle1,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            ChildHandle
            );
    gtBS->CloseProtocol (
            Handle2,
            &mInterfaceFunctionTestProtocol2Guid,
            mImageHandle,
            ChildHandle
            );
    gtBS->CloseProtocol (
            Handle3,
            &mInterfaceFunctionTestProtocol3Guid,
            mImageHandle,
            ChildHandle
            );
  }

  Status = EFI_SUCCESS;

Done:

  gtBS->UninstallProtocolInterface (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle3,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol4Guid,
          &InterfaceFunctionTestProt4Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle1;
  EFI_HANDLE            Handle2;
  EFI_HANDLE            Handle3;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status3;
  EFI_STATUS            Status4;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            DriverImageHandle;
  EFI_STATUS            NextStatus;
  UINTN                 StatusIndex;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle1 = NULL;
  Handle2 = NULL;
  Handle3 = NULL;
  ChildHandle = NULL;
  DriverImageHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle1,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &Handle2,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  Status3 = gtBS->InstallProtocolInterface (
                    &Handle3,
                    &mInterfaceFunctionTestProtocol3Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt3Instance
                    );
  Status4 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol4Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt4Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)
      || EFI_ERROR(Status3) || EFI_ERROR(Status4)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r, Status4 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // load & start external driver5
    // (open protocol1 BY_DRIVER; open protocol2 EXCLUSIVE;
    //  open protocol3 BY_DRIVER | EXCLUSIVE
    //
    DriverImageHandle = NULL;
    Status = LoadStartImage (
               StandardLib, mImageHandle,
               TEST_DRIVER_5_NAME,
               &DriverImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
    //
    // check the status reported by the external driver
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid268;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid269;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid270;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint6",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 3; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_SUCCESS == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid271;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid272;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid273;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest222 - Checkpoint6",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // open protocol1 ~ 3 EXCLUSIVE
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle1,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid274;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid275;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid276;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle2,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid277;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid278;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid279;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle3,
                     &mInterfaceFunctionTestProtocol3Guid,
                     (VOID **) &IFTestProt3,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid280;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid281;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid282;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // unload the external driver
    //
    gtBS->UnloadImage (DriverImageHandle);
    DriverImageHandle = NULL;
  }
  Status = EFI_SUCCESS;
Done:

  gtBS->UnloadImage (DriverImageHandle);

  gtBS->CloseProtocol (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          mImageHandle,
          ChildHandle
          );

  gtBS->CloseProtocol (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          mImageHandle,
          ChildHandle
          );

  gtBS->CloseProtocol (
          Handle3,
          &mInterfaceFunctionTestProtocol3Guid,
          mImageHandle,
          ChildHandle
          );

  gtBS->UninstallProtocolInterface (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle3,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol4Guid,
          &InterfaceFunctionTestProt4Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle1;
  EFI_HANDLE            Handle2;
  EFI_HANDLE            Handle3;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status3;
  EFI_STATUS            Status4;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            DriverImageHandle;
  EFI_STATUS            NextStatus;
  UINTN                 StatusIndex;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN               Numbers;
  EFI_GUID            TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle1 = NULL;
  Handle2 = NULL;
  Handle3 = NULL;
  ChildHandle = NULL;
  DriverImageHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);

  Status1 = gtBS->InstallProtocolInterface (
                    &Handle1,
                    &mInterfaceFunctionTestProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt1Instance
                    );
  Status2 = gtBS->InstallProtocolInterface (
                    &Handle2,
                    &mInterfaceFunctionTestProtocol2Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt2Instance
                    );
  Status3 = gtBS->InstallProtocolInterface (
                    &Handle3,
                    &mInterfaceFunctionTestProtocol3Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt3Instance
                    );
  Status4 = gtBS->InstallProtocolInterface (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol4Guid,
                    EFI_NATIVE_INTERFACE,
                    &InterfaceFunctionTestProt4Instance
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)
      || EFI_ERROR(Status3) || EFI_ERROR(Status4)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r, Status4 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // load & start external driver5
    // (open protocol1 BY_DRIVER; open protocol2 EXCLUSIVE;
    //  open protocol3 BY_DRIVER | EXCLUSIVE
    //
    DriverImageHandle = NULL;
    Status = LoadStartImage (
               StandardLib, mImageHandle,
               TEST_DRIVER_5_NAME,
               &DriverImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
    //
    // check the status reported by the external driver
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid283;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid284;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid285;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint7",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 3; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_SUCCESS == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid286;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid287;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid288;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest222 - Checkpoint7",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // open protocol1 ~ 3 BY_DRIVER | EXCLUSIVE
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle1,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid289;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid290;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid291;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle2,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid292;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid293;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid294;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocol (
                     Handle3,
                     &mInterfaceFunctionTestProtocol3Guid,
                     (VOID **) &IFTestProt3,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid295;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid296;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid297;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest222 - Checkpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // unload the external driver
    //
    gtBS->UnloadImage (DriverImageHandle);
    DriverImageHandle = NULL;
  }

  Status = EFI_SUCCESS;

Done:

  gtBS->UnloadImage (DriverImageHandle);

  gtBS->CloseProtocol (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          mImageHandle,
          ChildHandle
          );

  gtBS->CloseProtocol (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          mImageHandle,
          ChildHandle
          );

  gtBS->CloseProtocol (
          Handle3,
          &mInterfaceFunctionTestProtocol3Guid,
          mImageHandle,
          ChildHandle
          );

  gtBS->UninstallProtocolInterface (
          Handle1,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle2,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );
  gtBS->UninstallProtocolInterface (
          Handle3,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol4Guid,
          &InterfaceFunctionTestProt4Instance
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest333
//

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest333CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            NextStatus;
  EFI_HANDLE            DriverImageHandle1;
  EFI_HANDLE            DriverImageHandle2;
  EFI_HANDLE            DriverImageHandleArray[2];

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;
  EFI_HANDLE                  Handle;
  UINTN                       StatusIndex;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;

  UINTN                   Numbers;
  EFI_GUID                TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);

  Handle = NULL;
  DriverImageHandle1 = NULL;
  DriverImageHandle2 = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   &mInterfaceFunctionTestProtocol2Guid,
                   &InterfaceFunctionTestProt2Instance,
                   &mInterfaceFunctionTestProtocol3Guid,
                   &InterfaceFunctionTestProt3Instance,
                   NULL
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = LoadStartImage (
             StandardLib,
             mImageHandle,
             DRIVERBINDING_DRIVER_1_NAME,
             &DriverImageHandle1
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }


  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DRIVERBINDING_DRIVER_2_NAME,
             &DriverImageHandle2
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // connect Handle to Driver1
    // Driver1.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 BY_DRIVER.
    // * Call OpenProtocol() to open TestProtocol2 EXCLUSIVE.
    // * Call OpenProtocol() to open TestProtocol3 BY_DRIVER | EXCLUSIVE.
    //
    DriverImageHandleArray[0] = DriverImageHandle1;
    DriverImageHandleArray[1] = NULL;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (Handle, DriverImageHandleArray, NULL, FALSE);
    gtBS->RestoreTPL (OldTpl);
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid298;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid299;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid300;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // connect Handle to Driver2
    // Driver2.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 BY_DRIVER.
    // * Call OpenProtocol() to open TestProtocol2 BY_DRIVER.
    // * Call OpenProtocol() to open TestProtocol3 BY_DRIVER.
    //
    DriverImageHandleArray[0] = DriverImageHandle2;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (Handle, DriverImageHandleArray, NULL, FALSE);
    gtBS->RestoreTPL (OldTpl);

    //
    // check the status reported by the Driver2
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid301;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid302;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid303;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint1",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 3; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_ACCESS_DENIED == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid304;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid305;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid306;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest333 - Checkpoint1",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }
    //
    // disconnect Handle from Driver1
    // Driver1.Stop() will:
    // * Call CloseProtocol() to close TestProtocol1 ~ 3
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (Handle, NULL, NULL);
    gtBS->RestoreTPL (OldTpl);

    //
    // connect Handle to Driver2 again
    // Driver2.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 BY_DRIVER.
    // * Call OpenProtocol() to open TestProtocol2 BY_DRIVER.
    // * Call OpenProtocol() to open TestProtocol3 BY_DRIVER.
    //
    DriverImageHandleArray[0] = DriverImageHandle2;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (Handle, DriverImageHandleArray, NULL, FALSE);
    gtBS->RestoreTPL (OldTpl);

    //
    // check the status reported by the Driver2
    //
    Status = gtBS->LocateProtocol (
                &mExternalDriverProtocol1Guid,
                NULL,
                (VOID **) &ExProt1
                );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid307;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid308;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid309;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint1",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;

    for (StatusIndex = 0; StatusIndex < 3; StatusIndex++) {

      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (EFI_SUCCESS == NextStatus) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid310;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid311;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid312;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest333 - Checkpoint1",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }
    //
    // disconnect Handle from Driver2
    // Driver2.Stop() will:
    // * close TestProtocol1 ~ 4
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (Handle, NULL, NULL);
    gtBS->RestoreTPL (OldTpl);
  }

Done:
  //
  // Driver1's Unload will close TestProtocol4
  //
  gtBS->UnloadImage (DriverImageHandle1);
  gtBS->UnloadImage (DriverImageHandle2);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest333CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            NextStatus;
  EFI_HANDLE            DriverImageHandle1;
  EFI_HANDLE            DriverImageHandle2;
  EFI_HANDLE            DriverImageHandleArray[2];
  UINTN                 StatusIndex;
  EFI_HANDLE            Handle;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);

  Handle = NULL;
  DriverImageHandle1 = NULL;
  DriverImageHandle2 = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   &mInterfaceFunctionTestProtocol2Guid,
                   &InterfaceFunctionTestProt2Instance,
                   &mInterfaceFunctionTestProtocol3Guid,
                   &InterfaceFunctionTestProt3Instance,
                   &mInterfaceFunctionTestProtocol4Guid,
                   &InterfaceFunctionTestProt4Instance,
                   NULL
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    Status = LoadStartImage (
               StandardLib, mImageHandle,
               DRIVERBINDING_DRIVER_3_NAME,
               &DriverImageHandle1
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    Status = LoadStartImage (
               StandardLib, mImageHandle,
               DRIVERBINDING_DRIVER_4_NAME,
               &DriverImageHandle2
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Helper Function LoadStartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    //
    // connect Handle to Driver3, 4
    // Driver3.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 EXCLUSIVE.
    // * Call OpenProtocol() to open TestProtocol2 BY_DRIVER | EXCLUSIVE.
    // * Call OpenProtocol() to open TestProtocol3 BY_DRIVER
    // * Call OpenProtocol() to open TestProtocol4 BY_DRIVER
    //
    // Driver4.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 ~ 4 EXCLUSIVE.
    //
    DriverImageHandleArray[0] = DriverImageHandle1;
    DriverImageHandleArray[1] = NULL;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (Handle, DriverImageHandleArray, NULL, FALSE);
    gtBS->RestoreTPL (OldTpl);
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid313;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid314;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid315;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check the status reported by the Driver4
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                    (VOID **) &ExProt1
                    );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid316;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid317;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid318;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint2",
                   L"%a:%d:Locate External Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 4; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (StatusIndex == 2) {

        if (EFI_SUCCESS == NextStatus) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

      } else {

        if (EFI_ACCESS_DENIED == NextStatus) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid319;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid320;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid321;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest333 - Checkpoint2",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // connect Handle to Driver4 again
    // Driver4.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 ~ 4 EXCLUSIVE.
    //
    DriverImageHandleArray[0] = DriverImageHandle2;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (Handle, DriverImageHandleArray, NULL, FALSE);
    gtBS->RestoreTPL (OldTpl);

    //
    // check the status reported by the Driver4
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid322;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid323;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid324;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;

    for (StatusIndex = 0; StatusIndex < 4; StatusIndex++) {

      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (StatusIndex > 1) {

        if (EFI_ACCESS_DENIED == NextStatus) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

      } else {

        if (EFI_SUCCESS == NextStatus) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid325;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid326;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid327;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest333 - Checkpoint2",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }
    //
    // disconnect Handle from Driver4
    // Driver4.Close() will:
    // * close TestProtocol1 ~ 4
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (Handle, NULL, NULL);
    gtBS->RestoreTPL (OldTpl);

    gtBS->UnloadImage (DriverImageHandle1);
    DriverImageHandle1 = NULL;
    gtBS->UnloadImage (DriverImageHandle2);
    DriverImageHandle2 = NULL;
  }

  Status = EFI_SUCCESS;
Done:
  //
  // Driver3's Unload will close TestProtocol4
  //
  gtBS->UnloadImage (DriverImageHandle1);
  gtBS->UnloadImage (DriverImageHandle2);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance,
          &mInterfaceFunctionTestProtocol4Guid,
          &InterfaceFunctionTestProt4Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest333CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            NextStatus;
  EFI_HANDLE            DriverImageHandle1;
  EFI_HANDLE            DriverImageHandle2;
  EFI_HANDLE            DriverImageHandleArray[2];
  UINTN                 StatusIndex;
  EFI_HANDLE            Handle;

  EXTERNAL_DRIVER_PROTOCOL_1  *ExProt1;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  InitializeInterfaceFunctionTestProtocol4 (&InterfaceFunctionTestProt4Instance);

  Handle = NULL;
  DriverImageHandle1 = NULL;
  DriverImageHandle2 = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   &mInterfaceFunctionTestProtocol2Guid,
                   &InterfaceFunctionTestProt2Instance,
                   &mInterfaceFunctionTestProtocol3Guid,
                   &InterfaceFunctionTestProt3Instance,
                   &mInterfaceFunctionTestProtocol4Guid,
                   &InterfaceFunctionTestProt4Instance,
                   NULL
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DRIVERBINDING_DRIVER_3_NAME,
             &DriverImageHandle1
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DRIVERBINDING_DRIVER_5_NAME,
             &DriverImageHandle2
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // connect Handle to Driver3, 5
    // Driver3.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 EXCLUSIVE.
    // * Call OpenProtocol() to open TestProtocol2 BY_DRIVER | EXCLUSIVE.
    // * Call OpenProtocol() to open TestProtocol3 BY_DRIVER
    // * Call OpenProtocol() to open TestProtocol4 BY_DRIVER
    //
    // Driver5.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 ~ 4 BY_DRIVER | EXCLUSIVE.
    //
    DriverImageHandleArray[0] = DriverImageHandle1;
    DriverImageHandleArray[1] = NULL;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (Handle, DriverImageHandleArray, NULL, FALSE);
    gtBS->RestoreTPL (OldTpl);
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid328;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid329;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid330;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // check the status reported by the Driver5
    //
    Status = gtBS->LocateProtocol (
                &mExternalDriverProtocol1Guid,
                NULL,
                (VOID **) &ExProt1
                );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid331;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid332;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid333;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;
    for (StatusIndex = 0; StatusIndex < 4; StatusIndex++) {
      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (StatusIndex == 2) {

        if (EFI_SUCCESS == NextStatus) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

      } else {

        if (EFI_ACCESS_DENIED == NextStatus) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid334;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid335;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid336;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest333 - Checkpoint3",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }
    //
    // disconnect Handle from Driver3
    // Driver3.Close() will:
    // * close TestProtocol1 ~ 3, but will not close TestProtocol4
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (Handle, NULL, NULL);
    gtBS->RestoreTPL (OldTpl);

    //
    // connect Handle to Driver5 again
    // Driver5.Start() will:
    // * Call OpenProtocol() to open TestProtocol1 ~ 4 BY_DRIVER | EXCLUSIVE.
    //
    DriverImageHandleArray[0] = DriverImageHandle2;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (Handle, DriverImageHandleArray, NULL, FALSE);
    gtBS->RestoreTPL (OldTpl);

    //
    // check the status reported by the Driver5
    //
    Status = gtBS->LocateProtocol (
                     &mExternalDriverProtocol1Guid,
                     NULL,
                     (VOID **) &ExProt1
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid337;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid338;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid339;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInterfaceTest333 - Checkpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    NextStatus = 0xffffffff;

    for (StatusIndex = 0; StatusIndex < 4; StatusIndex++) {

      ExProt1->GetNextStatusReport (ExProt1, &NextStatus);

      if (StatusIndex == 3) {

        if (EFI_ACCESS_DENIED == NextStatus) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

      } else {

        if (EFI_SUCCESS == NextStatus) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid340;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid341;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid342;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInterfaceTest333 - Checkpoint3",
                     L"%a:%d:Locate External Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NextStatus,
                     TplArray[Index]
                     );
    }

    //
    // disconnect Handle from Driver5
    // Driver5.Close() will:
    // * close TestProtocol1 ~ 4
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (Handle, NULL, NULL);
    gtBS->RestoreTPL (OldTpl);
  }

  Status = EFI_SUCCESS;
Done:
  //
  // Driver3's Unload will close TestProtocol4
  //
  gtBS->UnloadImage (DriverImageHandle1);
  gtBS->UnloadImage (DriverImageHandle2);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance,
          &mInterfaceFunctionTestProtocol3Guid,
          &InterfaceFunctionTestProt3Instance,
          &mInterfaceFunctionTestProtocol4Guid,
          &InterfaceFunctionTestProt4Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

//
// Checkpoint Functions for CloseProtocol
//

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer;
  UINTN                               EntryCount;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    EntryBuffer = NULL;

    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.OpenProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // first time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid343;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid344;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid345;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check by OpenProtocolInformation
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EntryCount == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid346;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid347;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid348;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }
    //
    // second time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid349;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid350;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid351;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer;
  UINTN                               EntryCount;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    EntryBuffer = NULL;

    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_GET_PROTOCOL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.OpenProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // first time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    mImageHandle,
                    NULL
                    );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid352;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid353;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid354;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check by OpenProtocolInformation
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EntryCount == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid355;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid356;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid357;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }
    //
    // second time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid358;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid359;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid360;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer;
  UINTN                               EntryCount;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    EntryBuffer = NULL;

    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.OpenProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // first time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid361;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid362;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid363;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check by OpenProtocolInformation
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EntryCount == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid364;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid365;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid366;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }
    //
    // second time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid367;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid368;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid369;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer;
  UINTN                               EntryCount;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  Handle = NULL;
  ChildHandle = NULL;

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    &InterfaceFunctionTestProt1Instance,
                    NULL
                    );
  Status2 = gtBS->InstallMultipleProtocolInterfaces (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &InterfaceFunctionTestProt2Instance,
                    NULL
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    EntryBuffer = NULL;

    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.OpenProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // first time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     ChildHandle
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid370;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid371;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid372;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                 );
    //
    // check by OpenProtocolInformation
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EntryCount == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid373;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid374;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid375;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }
    //
    // second time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                    Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    mImageHandle,
                    NULL
                    );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid376;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid377;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid378;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer;
  UINTN                               EntryCount;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  Handle = NULL;
  ChildHandle = NULL;

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    &InterfaceFunctionTestProt1Instance,
                    NULL
                    );
  Status2 = gtBS->InstallMultipleProtocolInterfaces (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &InterfaceFunctionTestProt2Instance,
                    NULL
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    EntryBuffer = NULL;

    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.OpenProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // first time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     ChildHandle
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid379;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid380;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid381;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check by OpenProtocolInformation
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EntryCount == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid382;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid383;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid384;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }
    //
    // second time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid385;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid386;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid387;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer;
  UINTN                               EntryCount;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  Handle = NULL;
  ChildHandle = NULL;

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    &InterfaceFunctionTestProt1Instance,
                    NULL
                    );
  Status2 = gtBS->InstallMultipleProtocolInterfaces (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &InterfaceFunctionTestProt2Instance,
                    NULL
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    EntryBuffer = NULL;

    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.OpenProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // first time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     ChildHandle
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid388;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid389;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid390;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check by OpenProtocolInformation
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EntryCount == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid391;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid392;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid393;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    //
    // second time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid394;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid395;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid396;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer;
  UINTN                               EntryCount;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  Handle = NULL;
  ChildHandle = NULL;

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    &InterfaceFunctionTestProt1Instance,
                    NULL
                    );
  Status2 = gtBS->InstallMultipleProtocolInterfaces (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &InterfaceFunctionTestProt2Instance,
                    NULL
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    EntryBuffer = NULL;

    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.OpenProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // first time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     ChildHandle
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid397;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid398;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid399;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check by OpenProtocolInformation
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EntryCount == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid400;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid401;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid402;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    //
    // second time closeprotocol
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid403;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid404;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid405;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.CloseProtocol - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );
  gtBS->UninstallProtocolInterface (
          ChildHandle,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

//
// Checkpoint Functions for OpenProtocolInformation
//

EFI_STATUS
EFIAPI
BBTestOpenProtocolInformationInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            ChildHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  UINT32                AttributesArray[7];
  UINT32                Attributes;
  UINTN                 Indexi, RetryIndex, AttributesIndex;
  UINTN                 OpenTimes[2];
  UINTN                 LastCount;
  BOOLEAN               MisMatch;
  BOOLEAN               Found;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *TempEntry;
  UINTN                               EntryCount;
  UINTN                               EntryIndex;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  Handle = NULL;
  ChildHandle = NULL;

  AttributesArray[0] = EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL;
  AttributesArray[1] = EFI_OPEN_PROTOCOL_GET_PROTOCOL;
  AttributesArray[2] = EFI_OPEN_PROTOCOL_TEST_PROTOCOL;
  AttributesArray[3] = EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER;

  AttributesArray[4] = EFI_OPEN_PROTOCOL_BY_DRIVER;
  AttributesArray[5] = EFI_OPEN_PROTOCOL_EXCLUSIVE;
  AttributesArray[6] = EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE;

  OpenTimes[0] = 1;
  OpenTimes[1] = 5;

  LastCount = 0;
  EntryBuffer = NULL;

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &mInterfaceFunctionTestProtocol1Guid,
                    &InterfaceFunctionTestProt1Instance,
                    NULL
                    );
  Status2 = gtBS->InstallMultipleProtocolInterfaces (
                    &ChildHandle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &InterfaceFunctionTestProt2Instance,
                    NULL
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    return Status1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    LastCount = 0;

    //
    // first 2 tests
    //
    for (RetryIndex = 0; RetryIndex < 2; RetryIndex++) {

      //
      // open by 4 attributes and each will be opened in OpenTimes[RetryIndex] times
      //
      for (AttributesIndex = 0; AttributesIndex < 4; AttributesIndex++) {

        for (Indexi = 0; Indexi < OpenTimes[RetryIndex]; Indexi++) {
          Status = gtBS->OpenProtocol (
                           Handle,
                           &mInterfaceFunctionTestProtocol1Guid,
                           (VOID **) &IFTestProt1,
                           mImageHandle,
                           ChildHandle,
                           AttributesArray[AttributesIndex]
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.OpenProtocol - build environment",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            continue;
          }
        }
      }

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->OpenProtocolInformation (
                       Handle,
                       &mInterfaceFunctionTestProtocol1Guid,
                       &EntryBuffer,
                       &EntryCount
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid406;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid407;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid408;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_ERROR(Status)) {
        continue;
      }
      //
      // check the EntryCount
      //
      if (4 == EntryCount) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid409;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid410;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid411;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:ExpectedEntryCount - 4, Actual - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     EntryCount,
                     TplArray[Index]
                     );
      //
      // check the EntryBuffer
      //
      TempEntry = EntryBuffer;
      MisMatch = FALSE;
      for (EntryIndex = 0; EntryIndex < 4; EntryIndex++) {

        if ((TempEntry->AgentHandle != mImageHandle)
            || (TempEntry->ControllerHandle != ChildHandle)
            || (TempEntry->OpenCount != (LastCount + OpenTimes[RetryIndex]))) {

              MisMatch = TRUE;
              break;
        }
        TempEntry++;
      }
      if (!MisMatch) {
        for (AttributesIndex = 0; AttributesIndex < 4; AttributesIndex++) {

          TempEntry = EntryBuffer;
          Found = FALSE;
          for (EntryIndex = 0; EntryIndex < 4; EntryIndex++) {

            if (TempEntry->Attributes == AttributesArray[AttributesIndex]) {
              Found = TRUE;
              break;
            }

            TempEntry++;
          }

          if (!Found) {
            MisMatch = TRUE;
            break;
          }
        }
      }
      if (!MisMatch) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid412;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid413;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid414;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:MisMatch is - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     MisMatch,
                     TplArray[Index]
                     );
      //
      // free EntryBuffer
      //
      if (EntryBuffer != NULL) {
        gtBS->FreePool (EntryBuffer);
        EntryBuffer = NULL;
      }
      LastCount += OpenTimes[RetryIndex];
    }

    //
    // 3rd and 4th test (info of open BY_DRIVER, EXCLUSIVE)
    //
    AttributesArray[4] = EFI_OPEN_PROTOCOL_BY_DRIVER;
    Attributes = EFI_OPEN_PROTOCOL_BY_DRIVER;
    for (RetryIndex = 0; RetryIndex < 2; RetryIndex++) {

      if (RetryIndex == 1) {
        Attributes = EFI_OPEN_PROTOCOL_EXCLUSIVE;
      }

      gtBS->OpenProtocol (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              (VOID **) &IFTestProt1,
              mImageHandle,
              ChildHandle,
              Attributes
              );

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->OpenProtocolInformation (
                       Handle,
                       &mInterfaceFunctionTestProtocol1Guid,
                       &EntryBuffer,
                       &EntryCount
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid415;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid416;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid417;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_ERROR(Status)) {
        continue;
      }
      //
      // check the EntryCount
      //
      if (5 == EntryCount) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid418;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid419;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid420;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:ExpectedEntryCount - 5, Actual - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     EntryCount,
                     TplArray[Index]
                     );
      //
      // check the EntryBuffer
      //
      TempEntry = EntryBuffer;
      MisMatch = FALSE;
      for (EntryIndex = 0; EntryIndex < 5; EntryIndex++) {

        if (TempEntry->AgentHandle != mImageHandle
            || TempEntry->ControllerHandle != ChildHandle) {

              MisMatch = TRUE;
              break;
        }

        if (TempEntry->Attributes == EFI_OPEN_PROTOCOL_BY_DRIVER) {
          if (TempEntry->OpenCount != 1) {
            MisMatch = TRUE;
            break;
          }
        } else {
          if (TempEntry->OpenCount != LastCount) {
            MisMatch = TRUE;
            break;
          }
        }
        TempEntry++;
      }

      if (!MisMatch) {
        for (AttributesIndex = 0; AttributesIndex < 5; AttributesIndex++) {

          TempEntry = EntryBuffer;
          Found = FALSE;
          for (EntryIndex = 0; EntryIndex < 5; EntryIndex++) {

            if (TempEntry->Attributes == AttributesArray[AttributesIndex]) {
              Found = TRUE;
              break;
            }

            TempEntry++;
          }

          if (!Found) {
            MisMatch = TRUE;
            break;
          }
        }
      }
      if (!MisMatch) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid421;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid422;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid423;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:MisMatch is - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     MisMatch,
                     TplArray[Index]
                     );
      //
      // free EntryBuffer
      //
      if (EntryBuffer != NULL) {
        gtBS->FreePool (EntryBuffer);
        EntryBuffer = NULL;
      }
    }

    //
    // close the reference to the protocol1
    //
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     ChildHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CloseProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    //
    // fifth & sixth test
    //
    Attributes = EFI_OPEN_PROTOCOL_EXCLUSIVE;
    for (RetryIndex = 0; RetryIndex < 2; RetryIndex++) {

      if (RetryIndex == 1) {
        Attributes = EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE;
      }
      Status = gtBS->OpenProtocol (
                       Handle,
                       &mInterfaceFunctionTestProtocol1Guid,
                       (VOID **) &IFTestProt1,
                       mImageHandle,
                       ChildHandle,
                       Attributes
                       );
      if (EFI_ERROR(Status) && (RetryIndex == 0)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.OpneProtocol - build environment",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto Done;
      }

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->OpenProtocolInformation (
                       Handle,
                       &mInterfaceFunctionTestProtocol1Guid,
                       &EntryBuffer,
                       &EntryCount
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid424;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid425;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid426;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_ERROR(Status)) {
        continue;
      }
      //
      // check the EntryCount
      //
      if (1 == EntryCount) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid427;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid428;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid429;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:ExpectedEntryCount - 1, Actual - %d TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     EntryCount,
                     TplArray[Index]
                     );
      //
      // check the EntryBuffer
      //
      if (EntryBuffer->AgentHandle == mImageHandle
          && EntryBuffer->ControllerHandle == ChildHandle
          && EntryBuffer->OpenCount == 1
          && EntryBuffer->Attributes == EFI_OPEN_PROTOCOL_EXCLUSIVE) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid430;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid431;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid432;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                     L"%a:%d:TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     TplArray[Index]
                     );
      //
      // free EntryBuffer
      //
      if (EntryBuffer != NULL) {
        gtBS->FreePool (EntryBuffer);
        EntryBuffer = NULL;
      }
    }

    //
    // close the reference to the protocol1
    //
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     ChildHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CloseProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    //
    // seventh test
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.OpneProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid433;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid434;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid435;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                  );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    // check the EntryCount
    //
    if (1 == EntryCount) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid436;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid437;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid438;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedEntryCount - 1, Actual - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EntryCount,
                   TplArray[Index]
                   );
    //
    // check the EntryBuffer
    //
    if (EntryBuffer->AgentHandle == mImageHandle
        && EntryBuffer->ControllerHandle == ChildHandle
        && EntryBuffer->OpenCount == 1
        && EntryBuffer->Attributes == (EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid439;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid440;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid441;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );
    //
    // free EntryBuffer
    //
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
      EntryBuffer = NULL;
    }

    //
    // close the reference to the protocol1
    //
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     ChildHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CloseProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    //
    // eighth test
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid442;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid443;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid444;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // check the EntryCount
    //
    if (0 == EntryCount) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid445;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid446;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid447;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.OpenProtocolInformation - InterfaceTestCheckpoint1",
                   L"%a:%d:ExpectedEntryCount - 0, Actual - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EntryCount,
                   TplArray[Index]
                    );
    //
    // free EntryBuffer
    //
    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
      EntryBuffer = NULL;
    }

  }

Done:
  //
  // uninstall protocols
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  gtBS->UninstallMultipleProtocolInterfaces (
          ChildHandle,
          &mInterfaceFunctionTestProtocol2Guid,
          &InterfaceFunctionTestProt2Instance,
          NULL
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

//
// Checkpoint Functions for ConnectController()
//

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  BOOLEAN               Recursive[2];
  UINTN                 RecursiveIndex;
  UINTN                 NodeIndex;

  EFI_DEVICE_PATH_PROTOCOL    EndDevicePathNodeArray[1];

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  //
  // create 4 types of End Device Path Nodes
  //
  SctSetDevicePathEndNode (&EndDevicePathNodeArray[0]);
  //SctSetDevicePathEndNode (&EndDevicePathNodeArray[1]);
  EndDevicePathNodeArray[0].Type = 0x7f;
  //EndDevicePathNodeArray[1].Type = 0xff;

  Recursive[0] = FALSE;
  Recursive[1] = TRUE;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (NodeIndex = 0; NodeIndex < 1; NodeIndex++) {

      for (RecursiveIndex = 0; RecursiveIndex < 2; RecursiveIndex++) {

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->ConnectController (
                         Handle,
                         NULL,
                         &EndDevicePathNodeArray[NodeIndex],
                         Recursive[RecursiveIndex]
                         );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid448;
        } else if (Index == 1) {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid449;
        } else {
          TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid450;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"BS.ConnectController - InterfaceTestCheckpoint1",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
      }
    }
  }

  //
  // restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 DevicePathIndex;
  UINTN                 ImageIndex;
  UINTN                 RecursiveIndex;
  EFI_HANDLE            ImageHandle;

  EFI_DEVICE_PATH_PROTOCOL                *DevicePath[2];
  EFI_HANDLE                              DriverImageHandle[3];
  BOOLEAN                                 Recursive[2];

  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  CreateVendorDevicePath (&VendorDevicePath1, mVendorDevicePath1Guid);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  ImageHandle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external device driver
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DEVICE_DRIVER_1_NAME,
             &ImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                     );
    goto Done;
  }

  DevicePath[0] = NULL;
  DevicePath[1] = VendorDevicePath1;
  DriverImageHandle[0] = NULL;
  DriverImageHandle[1] = ImageHandle;
  DriverImageHandle[2] = NULL;
  Recursive[0] = FALSE;
  Recursive[1] = TRUE;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (ImageIndex = 0; ImageIndex < 2; ImageIndex++) {

      for (DevicePathIndex = 0; DevicePathIndex < 2; DevicePathIndex++) {

        for (RecursiveIndex = 0; RecursiveIndex < 2; RecursiveIndex++) {

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = gtBS->ConnectController (
                           Handle,
                           &DriverImageHandle[ImageIndex],
                           DevicePath[DevicePathIndex],
                           Recursive[RecursiveIndex]
                           );
          gtBS->RestoreTPL (OldTpl);
          //
          // check status
          //
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid451;
          } else if (Index == 1) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid452;
          } else {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid453;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"BS.ConnectController - InterfaceTestCheckpoint2",
                         L"%a:%d:Status - %r, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index]
                       );
          //
          // check whether protocol2 could be located
          //
          Status = gtBS->LocateProtocol (
                           &mInterfaceFunctionTestProtocol2Guid,
                           NULL,
                           (VOID **) &IFTestProt2
                           );
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid454;
          } else if (Index == 1) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid455;
          } else {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid456;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"BS.ConnectController - InterfaceTestCheckpoint2",
                         L"%a:%d:Status - %r, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index]
                         );
          //
          // restore environment for next loop
          //
          gtBS->DisconnectController (Handle, NULL, NULL);
        }
      }
    }
  }

  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (ImageHandle);
  FreeVendorDevicePath (VendorDevicePath1);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 DevicePathIndex;
  UINTN                 ImageIndex;
  UINTN                 RecursiveIndex;
  EFI_HANDLE            ImageHandle;
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 ExpectedHandleCount;

  EFI_DEVICE_PATH_PROTOCOL                *DevicePath[11];
  EFI_HANDLE                              DriverImageHandle[3];
  BOOLEAN                                 Recursive[2];

  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath4;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath5;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath6;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath7;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath8;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath9;
  EFI_DEVICE_PATH_PROTOCOL                *VendorDevicePath10;
  EFI_DEVICE_PATH_PROTOCOL                *NewDevicePath;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  UINTN                   Numbers;
  EFI_GUID                TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  CreateVendorDevicePath (&VendorDevicePath1, mVendorDevicePath1Guid);
  CreateVendorDevicePath (&VendorDevicePath2, mVendorDevicePath2Guid);
  CreateVendorDevicePath (&VendorDevicePath3, mVendorDevicePath3Guid);
  CreateVendorDevicePath (&VendorDevicePath4, mVendorDevicePath4Guid);
  CreateVendorDevicePath (&VendorDevicePath5, mVendorDevicePath5Guid);
  CreateVendorDevicePath (&VendorDevicePath6, mVendorDevicePath6Guid);
  CreateVendorDevicePath (&VendorDevicePath7, mVendorDevicePath7Guid);
  CreateVendorDevicePath (&VendorDevicePath8, mVendorDevicePath8Guid);
  CreateVendorDevicePath (&VendorDevicePath9, mVendorDevicePath9Guid);
  CreateVendorDevicePath (&VendorDevicePath10, mVendorDevicePath10Guid);

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  ImageHandle = NULL;
  HandleBuffer = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external bus driver
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_DRIVER_1_NAME,
             &ImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  DevicePath[0] = NULL;
  DevicePath[1] = VendorDevicePath1;
  DevicePath[2] = VendorDevicePath2;
  DevicePath[3] = VendorDevicePath3;
  DevicePath[4] = VendorDevicePath4;
  DevicePath[5] = VendorDevicePath5;
  DevicePath[6] = VendorDevicePath6;
  DevicePath[7] = VendorDevicePath7;
  DevicePath[8] = VendorDevicePath8;
  DevicePath[9] = VendorDevicePath9;
  DevicePath[10] = VendorDevicePath10;

  DriverImageHandle[0] = NULL;
  DriverImageHandle[1] = ImageHandle;
  DriverImageHandle[2] = NULL;
  Recursive[0] = FALSE;
  Recursive[1] = TRUE;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (ImageIndex = 0; ImageIndex < 2; ImageIndex++) {

      for (DevicePathIndex = 0; DevicePathIndex < 11; DevicePathIndex++) {

        for (RecursiveIndex = 0; RecursiveIndex < 2; RecursiveIndex++) {

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = gtBS->ConnectController (
                           Handle,
                           &DriverImageHandle[ImageIndex],
                           DevicePath[DevicePathIndex],
                           Recursive[RecursiveIndex]
                           );
          gtBS->RestoreTPL (OldTpl);
          //
          // check status
          //
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid457;
          } else if (Index == 1) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid458;
          } else {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid459;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"BS.ConnectController - InterfaceTestCheckpoint3",
                         L"%a:%d:Status - %r, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index]
                         );
          //
          // check whether protocol2 could be located
          //
          if (HandleBuffer != NULL) {
            gtBS->FreePool (HandleBuffer);
            HandleBuffer = NULL;
          }
          Status = gtBS->LocateHandleBuffer (
                           ByProtocol,
                           &mInterfaceFunctionTestProtocol2Guid,
                           NULL,
                           &NoHandles,
                           &HandleBuffer
                           );
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid460;
          } else if (Index == 1) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid461;
          } else {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid462;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"BS.ConnectController - InterfaceTestCheckpoint3",
                         L"%a:%d:Status - %r, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index]
                         );

          if (EFI_ERROR(Status)) {
            gtBS->DisconnectController (Handle, NULL, NULL);
            continue;
          }
          //
          // handle count should equal the expected value
          //
          if (DevicePathIndex == 0) {
            ExpectedHandleCount = 10;
          } else {
            ExpectedHandleCount = 1;
          }

          if (NoHandles == ExpectedHandleCount) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid463;
          } else if (Index == 1) {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid464;
          } else {
            TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid465;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"BS.ConnectController - InterfaceTestCheckpoint3",
                         L"%a:%d:ExpectedHandleCount - %d, NoHandles - %d, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         ExpectedHandleCount,
                         NoHandles,
                         TplArray[Index]
                          );

          //
          // The device path on the handle should have the same node as the
          // RemainingDevicePath
          //
          if (DevicePathIndex != 0) {
            Status = gtBS->HandleProtocol (
                             *HandleBuffer,
                             &gEfiDevicePathProtocolGuid,
                             (VOID **) &NewDevicePath
                             );
            if (EFI_SUCCESS == Status) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }

            if (Index == 0) {
              TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid466;
            } else if (Index == 1) {
              TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid467;
            } else {
              TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid468;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"BS.ConnectController - InterfaceTestCheckpoint3",
                           L"%a:%d:Status - %r, TPL - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index]
                           );
            if (IsNodeInDevicePath (DevicePath[DevicePathIndex], NewDevicePath)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }

            if (Index == 0) {
              TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid469;
            } else if (Index == 1) {
              TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid470;
            } else {
              TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid471;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"BS.ConnectController - InterfaceTestCheckpoint3",
                           L"%a:%d:TPL - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           TplArray[Index]
                           );
          }
          //
          // restore environment for next loop
          //
          gtBS->DisconnectController (Handle, NULL, NULL);
        }
      }
    }
  }

  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (ImageHandle);
  FreeVendorDevicePath (VendorDevicePath1);
  FreeVendorDevicePath (VendorDevicePath2);
  FreeVendorDevicePath (VendorDevicePath3);
  FreeVendorDevicePath (VendorDevicePath4);
  FreeVendorDevicePath (VendorDevicePath5);
  FreeVendorDevicePath (VendorDevicePath6);
  FreeVendorDevicePath (VendorDevicePath7);
  FreeVendorDevicePath (VendorDevicePath8);
  FreeVendorDevicePath (VendorDevicePath9);
  FreeVendorDevicePath (VendorDevicePath10);

  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 ImageIndex;
  EFI_HANDLE            BusDriverImageHandle;
  EFI_HANDLE            DeviceDriverImageHandle;

  EFI_HANDLE                              DriverImageHandle[3];
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  BusDriverImageHandle = NULL;
  DeviceDriverImageHandle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external bus driver 2 and device driver 2
  //

  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_DRIVER_2_NAME,
             &BusDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                     );
    goto Done;
  }

  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DEVICE_DRIVER_2_NAME,
             &DeviceDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  DriverImageHandle[0] = NULL;
  DriverImageHandle[1] = BusDriverImageHandle;
  DriverImageHandle[2] = NULL;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (ImageIndex = 0; ImageIndex < 2; ImageIndex++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->ConnectController (
                       Handle,
                       &DriverImageHandle[ImageIndex],
                       NULL,
                       FALSE
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid472;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid473;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid474;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                   );
      //
      // protocol2 should be located
      //
      Status = gtBS->LocateProtocol (
                       &mInterfaceFunctionTestProtocol2Guid,
                       NULL,
                       (VOID **) &IFTestProt2
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid475;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid476;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid477;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // protocol3 should not be located
      //
      Status = gtBS->LocateProtocol (
                       &mInterfaceFunctionTestProtocol3Guid,
                       NULL,
                       (VOID **) &IFTestProt3
                       );
      if (EFI_NOT_FOUND == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid478;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid479;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid480;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // restore environment for next loop
      //
      gtBS->DisconnectController (Handle, NULL, NULL);
    }
  }

  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (BusDriverImageHandle);
  gtBS->UnloadImage (DeviceDriverImageHandle);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 ImageIndex;
  EFI_HANDLE            BusDriverImageHandle;
  EFI_HANDLE            DeviceDriverImageHandle;

  EFI_HANDLE                              DriverImageHandle[3];

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  BusDriverImageHandle = NULL;
  DeviceDriverImageHandle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external bus driver 2 and device driver 2
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_DRIVER_2_NAME,
             &BusDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                     );
    goto Done;
  }

  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DEVICE_DRIVER_2_NAME,
             &DeviceDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  DriverImageHandle[0] = NULL;
  DriverImageHandle[1] = BusDriverImageHandle;
  DriverImageHandle[2] = NULL;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (ImageIndex = 0; ImageIndex < 2; ImageIndex++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->ConnectController (
                       Handle,
                       &DriverImageHandle[ImageIndex],
                       NULL,
                       TRUE
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid481;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid482;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid483;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint5",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // protocol2 should be located
      //
      Status = gtBS->LocateProtocol (
                       &mInterfaceFunctionTestProtocol2Guid,
                       NULL,
                       (VOID **) &IFTestProt2
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid484;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid485;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid486;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint5",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // protocol3 should also be located
      //
      Status = gtBS->LocateProtocol (
                       &mInterfaceFunctionTestProtocol3Guid,
                       NULL,
                       (VOID **) &IFTestProt3
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid487;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid488;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid489;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint5",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // restore environment for next loop
      //
      gtBS->DisconnectController (Handle, NULL, NULL);
    }
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (BusDriverImageHandle);
  gtBS->UnloadImage (DeviceDriverImageHandle);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 RecursiveIndex;
  EFI_HANDLE            DeviceDriverImageHandle1;
  EFI_HANDLE            DeviceDriverImageHandle2;
  EFI_HANDLE            DeviceDriverImageHandle3;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status3;
  BOOLEAN               Recursive[2];

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      *IFTestProt4;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  DeviceDriverImageHandle1 = NULL;
  DeviceDriverImageHandle2 = NULL;
  DeviceDriverImageHandle3 = NULL;
  Recursive[0] = TRUE;
  Recursive[1] = FALSE;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external device driver 1 ~ 3
  //
  Status1 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_1_NAME,
              &DeviceDriverImageHandle1
              );
  Status2 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_2_NAME,
              &DeviceDriverImageHandle2
              );
  Status3 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_3_NAME,
              &DeviceDriverImageHandle3
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (RecursiveIndex = 0; RecursiveIndex < 2; RecursiveIndex++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->ConnectController (
                       Handle,
                       NULL,
                       NULL,
                       Recursive[RecursiveIndex]
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid490;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid491;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid492;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint6",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // protocol2, 3, 4 should be located
      //
      Status1 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol2Guid,
                        NULL,
                        (VOID **) &IFTestProt2
                        );
      Status2 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol3Guid,
                        NULL,
                        (VOID **) &IFTestProt3
                        );
      Status3 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol4Guid,
                        NULL,
                        (VOID **) &IFTestProt4
                        );
      if ((EFI_SUCCESS == Status1)
          && (EFI_SUCCESS == Status2)
          && (EFI_SUCCESS == Status3)) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid493;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid494;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid495;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint6",
                     L"%a:%d:TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     TplArray[Index]
                     );
      //
      // restore environment for next loop
      //
      gtBS->DisconnectController (Handle, NULL, NULL);
    }
  }

  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (DeviceDriverImageHandle1);
  gtBS->UnloadImage (DeviceDriverImageHandle2);
  gtBS->UnloadImage (DeviceDriverImageHandle3);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint7_13 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 RecursiveIndex;
  EFI_HANDLE            DeviceDriverImageHandle1;
  EFI_HANDLE            DeviceDriverImageHandle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  BOOLEAN               Recursive[2];
  EFI_HANDLE            ImageHandle[3];

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  DeviceDriverImageHandle1 = NULL;
  DeviceDriverImageHandle2 = NULL;
  Recursive[0] = TRUE;
  Recursive[1] = FALSE;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external device driver 1, 4
  //
  Status1 = LoadStartImage (
              StandardLib,
              mImageHandle,
              DEVICE_DRIVER_1_NAME,
              &DeviceDriverImageHandle1
              );
  Status2 = LoadStartImage (
              StandardLib,
              mImageHandle,
              DEVICE_DRIVER_4_NAME,
              &DeviceDriverImageHandle2
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  ImageHandle[0] = DeviceDriverImageHandle1;
  ImageHandle[1] = DeviceDriverImageHandle2;
  ImageHandle[2] = NULL;


  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (RecursiveIndex = 0; RecursiveIndex < 2; RecursiveIndex++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->ConnectController (
                       Handle,
                       ImageHandle,
                       NULL,
                       Recursive[RecursiveIndex]
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid496;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid497;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid498;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint7&13",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                   );
      //
      // protocol2 should be located while protocol3 should not
      //
      Status1 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol2Guid,
                        NULL,
                        (VOID **) &IFTestProt2
                        );
      Status2 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol3Guid,
                        NULL,
                        (VOID **) &IFTestProt3
                        );
      if ((EFI_SUCCESS == Status1)
          && (EFI_NOT_FOUND == Status2)) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid499;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid500;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid501;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint7&13",
                     L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1,
                     Status2,
                     TplArray[Index]
                     );
      //
      // restore environment for next loop
      //
      gtBS->DisconnectController (Handle, NULL, NULL);
    }
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (DeviceDriverImageHandle1);
  gtBS->UnloadImage (DeviceDriverImageHandle2);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 RecursiveIndex;
  EFI_HANDLE            DriverImageHandle[2];
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  BOOLEAN               Recursive[2];
  EFI_HANDLE            ControllerHandle;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  EFI_HANDLE            OverrideDriverImageHandle;
  EFI_HANDLE            ImageHandle;

  EFI_DEVICE_PATH_PROTOCOL                *DriverImagePath;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL   *PlatformDriverOverrideInterface;

  INTERFACE_FUNCTION_TEST_PROTOCOL_8      *IFTestProt8;
  INTERFACE_FUNCTION_TEST_PROTOCOL_9      *IFTestProt9;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  ControllerHandle = NULL;
  DriverImageHandle[0] = NULL;
  DriverImageHandle[1] = NULL;
  Recursive[0] = TRUE;
  Recursive[1] = FALSE;
  OverrideDriverImageHandle = NULL;
  HandleBuffer = NULL;
  ImageHandle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &ControllerHandle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start PlatformOverrideDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             PLATFORM_OVERRIDE_DRIVER_1_NAME,
             &OverrideDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // Connect the PlatformOverrideDriver1
  //
  Status = gtBS->ConnectController (Handle, NULL, NULL, TRUE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // locate the EFI Platform Driver Override Protocol
  //
  HandleBuffer = NULL;
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mPlatformOverrideDriver1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || NoHandles != 1) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - build environment",
                   L"%a:%d:Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    goto Done;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gEfiPlatformDriverOverrideProtocolGuid,
                   (VOID **) &PlatformDriverOverrideInterface
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // load and start those drivers returned by Platform Driver Override Protocol
  //
  DriverImagePath = NULL;
  for (Index = 0; Index < 2; Index++) {

    Status = PlatformDriverOverrideInterface->GetDriverPath (
               PlatformDriverOverrideInterface,
               ControllerHandle,
               &DriverImagePath
               );
    if (EFI_ERROR(Status)) {
      break;
    }

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     DriverImagePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    DriverImageHandle[Index] = ImageHandle;

    Status = gtBS->StartImage (ImageHandle, NULL, NULL);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    Status = PlatformDriverOverrideInterface->DriverLoaded (
               PlatformDriverOverrideInterface,
               ControllerHandle,
               DriverImagePath,
               ImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"PlatformDriverOverrideInterface - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (RecursiveIndex = 0; RecursiveIndex < 2; RecursiveIndex++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->ConnectController (
                       ControllerHandle,
                       NULL,
                       NULL,
                       Recursive[RecursiveIndex]
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid502;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid503;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid504;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint8",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // protocol8 should be located while protocol9 should not
      //
      Status1 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol8Guid,
                        NULL,
                        (VOID **) &IFTestProt8
                        );
      Status2 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol9Guid,
                        NULL,
                        (VOID **) &IFTestProt9
                        );
      if ((EFI_SUCCESS == Status1)
          && (EFI_NOT_FOUND == Status2)) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid505;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid506;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid507;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint8",
                     L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1,
                     Status2,
                     TplArray[Index]
                     );
      //
      // restore environment for next loop
      //
      gtBS->DisconnectController (ControllerHandle, NULL, NULL);
    }
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  gtBS->DisconnectController (Handle, NULL, NULL);

  gtBS->UnloadImage (DriverImageHandle[0]);
  gtBS->UnloadImage (DriverImageHandle[1]);
  gtBS->UnloadImage (OverrideDriverImageHandle);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
          NULL,
          NULL
          );

  gtBS->UninstallMultipleProtocolInterfaces (
          ControllerHandle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_HANDLE            OverrideDriverImageHandle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_10      *IFTestProt10;
  INTERFACE_FUNCTION_TEST_PROTOCOL_11      *IFTestProt11;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  OverrideDriverImageHandle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestNoInterfaceProtocol2Guid,
                   NULL,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start BusOverrideDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_OVERRIDE_DRIVER_1_NAME,
             &OverrideDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                     );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (
                     Handle,
                     NULL,
                     NULL,
                     TRUE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid508;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid509;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid510;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // protocol10 should be located while protocol11 should not
    //
    Status1 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol10Guid,
                      NULL,
                      (VOID **) &IFTestProt10
                      );
    Status2 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol11Guid,
                      NULL,
                      (VOID **) &IFTestProt11
                      );
    if ((EFI_SUCCESS == Status1)
        && (EFI_NOT_FOUND == Status2)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid511;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid512;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid513;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint9",
                   L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
    //
    // restore environment for next loop
    //
    gtBS->DisconnectController (Handle, NULL, NULL);
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestNoInterfaceProtocol2Guid,
          NULL,
          NULL
          );
  gtBS->UnloadImage (OverrideDriverImageHandle);
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}


EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 RecursiveIndex;
  EFI_HANDLE            DeviceDriverImageHandle1;
  EFI_HANDLE            DeviceDriverImageHandle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  BOOLEAN               Recursive[2];

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  DeviceDriverImageHandle1 = NULL;
  DeviceDriverImageHandle2 = NULL;
  Recursive[0] = TRUE;
  Recursive[1] = FALSE;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external device driver 1, 5
  // both drivers consumes the Handle's protocol1, driver1 produces protocol2,
  // driver2 produces protocol3.
  // In this case, driver2's DriverBindingVersion is higher than driver1's
  //
  Status1 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_1_NAME,
              &DeviceDriverImageHandle1
              );
  Status2 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_5_NAME,
              &DeviceDriverImageHandle2
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (RecursiveIndex = 0; RecursiveIndex < 2; RecursiveIndex++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->ConnectController (
                       Handle,
                       NULL,
                       NULL,
                       Recursive[RecursiveIndex]
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid514;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid515;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid516;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint10",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // protocol2 should be located while protocol3 should not
      //
      Status1 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol2Guid,
                        NULL,
                        (VOID **) &IFTestProt2
                        );
      Status2 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol3Guid,
                        NULL,
                        (VOID **) &IFTestProt3
                        );
      if ((EFI_SUCCESS == Status1)
          && (EFI_NOT_FOUND == Status2)) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid517;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid518;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid519;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint10",
                     L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1,
                     Status2,
                     TplArray[Index]
                     );
      //
      // restore environment for next loop
      //
      gtBS->DisconnectController (Handle, NULL, NULL);
    }
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  gtBS->UnloadImage (DeviceDriverImageHandle1);
  gtBS->UnloadImage (DeviceDriverImageHandle2);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint11 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  UINTN                 RecursiveIndex;
  EFI_HANDLE            DriverImageHandle[2];
  EFI_HANDLE            DeviceDriver1ImageHandle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  BOOLEAN               Recursive[2];
  EFI_HANDLE            ControllerHandle;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  EFI_HANDLE            OverrideDriverImageHandle;
  EFI_HANDLE            ImageHandle[2];
  EFI_HANDLE            TempImageHandle;

  EFI_DEVICE_PATH_PROTOCOL                *DriverImagePath;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL   *PlatformDriverOverrideInterface;

  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_8      *IFTestProt8;
  INTERFACE_FUNCTION_TEST_PROTOCOL_9      *IFTestProt9;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  ControllerHandle = NULL;
  DriverImageHandle[0] = NULL;
  DriverImageHandle[1] = NULL;
  DeviceDriver1ImageHandle = NULL;
  Recursive[0] = TRUE;
  Recursive[1] = FALSE;
  OverrideDriverImageHandle = NULL;
  HandleBuffer = NULL;
  ImageHandle[0] = NULL;
  ImageHandle[1] = NULL;
  TempImageHandle = NULL;


  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &ControllerHandle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start PlatformOverrideDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             PLATFORM_OVERRIDE_DRIVER_1_NAME,
             &OverrideDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // Connect the PlatformOverrideDriver1
  //
  Status = gtBS->ConnectController (Handle, NULL, NULL, TRUE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // locate the EFI Platform Driver Override Protocol
  //
  HandleBuffer = NULL;
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mPlatformOverrideDriver1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || NoHandles != 1) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - build environment",
                   L"%a:%d:Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    goto Done;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gEfiPlatformDriverOverrideProtocolGuid,
                   (VOID **) &PlatformDriverOverrideInterface
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // load and start those drivers returned by Platform Driver Override Protocol
  //
  DriverImagePath = NULL;
  for (Index = 0; Index < 2; Index++) {

    Status = PlatformDriverOverrideInterface->GetDriverPath (
               PlatformDriverOverrideInterface,
               ControllerHandle,
               &DriverImagePath
               );
    if (EFI_ERROR(Status)) {
      break;
    }

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     DriverImagePath,
                     NULL,
                     0,
                     &TempImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    DriverImageHandle[Index] = TempImageHandle;

    Status = gtBS->StartImage (TempImageHandle, NULL, NULL);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    Status = PlatformDriverOverrideInterface->DriverLoaded (
               PlatformDriverOverrideInterface,
               ControllerHandle,
               DriverImagePath,
               TempImageHandle
               );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"PlatformDriverOverrideInterface - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
  }

  //
  // load and start TestDeviceDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DEVICE_DRIVER_1_NAME,
             &DeviceDriver1ImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  ImageHandle[0] = DeviceDriver1ImageHandle;
  ImageHandle[1] = NULL;
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (RecursiveIndex = 0; RecursiveIndex < 2; RecursiveIndex++) {

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->ConnectController (
                       ControllerHandle,
                       ImageHandle,
                       NULL,
                       Recursive[RecursiveIndex]
                       );
      gtBS->RestoreTPL (OldTpl);
      //
      // check status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid520;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid521;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid522;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint11",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // protocol2 should be located while protocol8, 9 should not
      //
      Status = gtBS->LocateProtocol (
                       &mInterfaceFunctionTestProtocol2Guid,
                       NULL,
                       (VOID **) &IFTestProt2
                       );
      Status1 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol8Guid,
                        NULL,
                        (VOID **) &IFTestProt8
                        );
      Status2 = gtBS->LocateProtocol (
                        &mInterfaceFunctionTestProtocol9Guid,
                        NULL,
                        (VOID **) &IFTestProt9
                        );
      if ((EFI_SUCCESS == Status) && (EFI_NOT_FOUND == Status1)
          && (EFI_NOT_FOUND == Status2)) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid523;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid524;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid525;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.ConnectController - InterfaceTestCheckpoint11",
                     L"%a:%d:Status - %r, Status1 - %r, Status2 - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Status1,
                     Status2,
                     TplArray[Index]
                     );
      //
      // restore environment for next loop
      //
      gtBS->DisconnectController (ControllerHandle, NULL, NULL);
    }
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  gtBS->DisconnectController (Handle, NULL, NULL);

  gtBS->UnloadImage (DriverImageHandle[0]);
  gtBS->UnloadImage (DriverImageHandle[1]);
  gtBS->UnloadImage (OverrideDriverImageHandle);
  gtBS->UnloadImage (DeviceDriver1ImageHandle);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
          NULL,
          NULL
          );
  gtBS->UninstallMultipleProtocolInterfaces (
          ControllerHandle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint12 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_HANDLE            OverrideDriverImageHandle;
  EFI_HANDLE            DeviceDriver1ImageHandle;
  EFI_HANDLE            ImageHandle[2];
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  EFI_HANDLE            ControllerHandle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_2       *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_10      *IFTestProt10;
  INTERFACE_FUNCTION_TEST_PROTOCOL_11      *IFTestProt11;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  OverrideDriverImageHandle = NULL;
  DeviceDriver1ImageHandle = NULL;
  HandleBuffer = NULL;
  ControllerHandle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestNoInterfaceProtocol2Guid,
                   NULL,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start BusOverrideDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_OVERRIDE_DRIVER_1_NAME,
             &OverrideDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // load and start TestDeviceDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DEVICE_DRIVER_1_NAME,
             &DeviceDriver1ImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // Connect BusOverrideDriver1 to generate the ControllerHandle which
  // has TestProtocol1 installed. (Recursive = FALSE, for do not connect the
  // device drivers.)
  //
  Status = gtBS->ConnectController (
                   Handle,
                   NULL,
                   NULL,
                   FALSE
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.ConnectController - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // locate the controller handle that has the TestProtocol1 installed
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mInterfaceFunctionTestProtocol1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles != 1)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - build environment",
                   L"%a:%d:Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    goto Done;
  }
  ControllerHandle = HandleBuffer[0];

  ImageHandle[0] = DeviceDriver1ImageHandle;
  ImageHandle[1] = NULL;
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (
                     ControllerHandle,
                     ImageHandle,
                     NULL,
                     TRUE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid526;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid527;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid528;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint12",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // protocol2 should be located while protocol10, 11 should not
    //
    Status = gtBS->LocateProtocol (
                     &mInterfaceFunctionTestProtocol2Guid,
                     NULL,
                     (VOID **) &IFTestProt2
                     );
    Status1 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol10Guid,
                      NULL,
                      (VOID **) &IFTestProt10
                      );
    Status2 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol11Guid,
                      NULL,
                      (VOID **) &IFTestProt11
                      );
    if ((EFI_SUCCESS == Status) && (EFI_NOT_FOUND == Status1)
        && (EFI_NOT_FOUND == Status2)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid529;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid530;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid531;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint12",
                   L"%a:%d:Status - %r, Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
    //
    // restore environment for next loop
    //
    gtBS->DisconnectController (ControllerHandle, NULL, NULL);
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestNoInterfaceProtocol2Guid,
          NULL,
          NULL
          );
  gtBS->DisconnectController (Handle, NULL, NULL);
  gtBS->UnloadImage (OverrideDriverImageHandle);
  gtBS->UnloadImage (DeviceDriver1ImageHandle);

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint14 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle1;
  EFI_HANDLE            Handle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_HANDLE            ControllerHandle;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  EFI_HANDLE            PlatformOverrideDriverImageHandle;
  EFI_HANDLE            BusOverrideDriverImageHandle;
  EFI_HANDLE            *ImageHandleBuffer;
  UINTN                 HandleNo;

  INTERFACE_FUNCTION_TEST_PROTOCOL_8      *IFTestProt8;
  INTERFACE_FUNCTION_TEST_PROTOCOL_10     *IFTestProt10;
  INTERFACE_FUNCTION_TEST_PROTOCOL_11     *IFTestProt11;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle1 = NULL;
  Handle2 = NULL;
  ControllerHandle = NULL;
  PlatformOverrideDriverImageHandle = NULL;
  BusOverrideDriverImageHandle = NULL;
  HandleBuffer = NULL;
  ImageHandleBuffer = NULL;
  HandleNo = 0;

  Status1 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle1,
                    &mTestNoInterfaceProtocol1Guid,
                    NULL,
                    NULL
                    );
  Status2 = gtBS->InstallMultipleProtocolInterfaces (
                    &Handle2,
                    &mTestNoInterfaceProtocol2Guid,
                    NULL,
                    NULL
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    return Status;
  }

  //
  // load and start PlatformOverrideDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             PLATFORM_OVERRIDE_DRIVER_1_NAME,
             &PlatformOverrideDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // Connect the PlatformOverrideDriver1
  //
  Status = gtBS->ConnectController (Handle1, NULL, NULL, FALSE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.ConnectController - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // load and start BusOverrideDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_OVERRIDE_DRIVER_1_NAME,
             &BusOverrideDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                     );
    goto Done;
  }

  //
  // Connect BusOverrideDriver1 to generate the ControllerHandle which
  // has TestProtocol1 installed. (Recursive = FALSE, for do not connect the
  // device drivers.)
  //
  Status = gtBS->ConnectController (
                   Handle2,
                   NULL,
                   NULL,
                   FALSE
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.ConnectController - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // locate the controller handle that has the TestProtocol1 installed
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mInterfaceFunctionTestProtocol1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles != 1)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - build environment",
                   L"%a:%d:Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    goto Done;
  }
  ControllerHandle = HandleBuffer[0];

  ImageHandleBuffer = NULL;
  Status = GetPlatformOverrideDriverImages (
             StandardLib,
             mImageHandle,
             ControllerHandle,
             &ImageHandleBuffer,
             &HandleNo
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"GetPlatformOverrideDriverImages - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (
                     ControllerHandle,
                     NULL,
                     NULL,
                     TRUE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid532;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid533;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid534;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint14",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                 );
    //
    // protocol8 should be located while protocol10, 11 should not
    //
    Status = gtBS->LocateProtocol (
                     &mInterfaceFunctionTestProtocol8Guid,
                     NULL,
                     (VOID **) &IFTestProt8
                     );
    Status1 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol10Guid,
                      NULL,
                      (VOID **) &IFTestProt10
                      );
    Status2 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol11Guid,
                      NULL,
                      (VOID **) &IFTestProt11
                      );
    if ((EFI_SUCCESS == Status) && (EFI_NOT_FOUND == Status1)
        && (EFI_NOT_FOUND == Status2)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid535;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid536;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid537;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint14",
                   L"%a:%d:Status - %r, Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
    //
    // restore environment for next loop
    //
    gtBS->DisconnectController (ControllerHandle, NULL, NULL);
  }

  Status = EFI_SUCCESS;

Done:
  //
  // restore environment
  //
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  gtBS->DisconnectController (Handle1, NULL, NULL);
  gtBS->DisconnectController (Handle2, NULL, NULL);

  if (ImageHandleBuffer != NULL) {
    for (Index = 0; Index < HandleNo; Index++) {
      gtBS->UnloadImage (ImageHandleBuffer[Index]);
    }

    gtBS->FreePool (ImageHandleBuffer);
  }

  gtBS->UnloadImage (PlatformOverrideDriverImageHandle);
  gtBS->UnloadImage (BusOverrideDriverImageHandle);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle1,
          &mTestNoInterfaceProtocol1Guid,
          NULL,
          NULL
          );
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle2,
          &mTestNoInterfaceProtocol2Guid,
          NULL,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint15 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_HANDLE            ControllerHandle;
  EFI_HANDLE            PlatformOverrideDriverImageHandle;
  EFI_HANDLE            DeviceDriverImageHandle;
  EFI_HANDLE            *ImageHandleBuffer;
  UINTN                 HandleNo;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  INTERFACE_FUNCTION_TEST_PROTOCOL_8      *IFTestProt8;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  ControllerHandle = NULL;
  PlatformOverrideDriverImageHandle = NULL;
  DeviceDriverImageHandle = NULL;
  ImageHandleBuffer = NULL;
  HandleNo = 0;

  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &ControllerHandle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start PlatformOverrideDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             PLATFORM_OVERRIDE_DRIVER_1_NAME,
             &PlatformOverrideDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                     );
    goto Done;
  }

  //
  // Connect the PlatformOverrideDriver1
  //
  Status = gtBS->ConnectController (Handle, NULL, NULL, FALSE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.ConnectController - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // setup the drivers for the platform override
  //
  ImageHandleBuffer = NULL;
  Status = GetPlatformOverrideDriverImages (
             StandardLib,
             mImageHandle,
             ControllerHandle,
             &ImageHandleBuffer,
             &HandleNo
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"GetPlatformOverrideDriverImages - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // load and start TestDeviceDriver4
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DEVICE_DRIVER_4_NAME,
             &DeviceDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (
                     ControllerHandle,
                     NULL,
                     NULL,
                     TRUE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid538;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid539;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid540;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint15",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // protocol8 should be located while protocol3 should not
    //
    Status1 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol8Guid,
                      NULL,
                      (VOID **) &IFTestProt8
                      );
    Status2 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol3Guid,
                      NULL,
                      (VOID **) &IFTestProt3
                      );
    if ((EFI_SUCCESS == Status1) && (EFI_NOT_FOUND == Status2)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid541;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid542;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid543;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint15",
                   L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
    //
    // restore environment for next loop
    //
    gtBS->DisconnectController (ControllerHandle, NULL, NULL);
  }

  Status = EFI_SUCCESS;

Done:
  //
  // restore environment
  //
  gtBS->DisconnectController (Handle, NULL, NULL);

  if (ImageHandleBuffer != NULL) {
    for (Index = 0; Index < HandleNo; Index++) {
      gtBS->UnloadImage (ImageHandleBuffer[Index]);
    }

    gtBS->FreePool (ImageHandleBuffer);
  }

  gtBS->UnloadImage (PlatformOverrideDriverImageHandle);
  gtBS->UnloadImage (DeviceDriverImageHandle);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
          NULL,
          NULL
          );
  gtBS->UninstallMultipleProtocolInterfaces (
          ControllerHandle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint16 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_HANDLE            OverrideDriverImageHandle;
  EFI_HANDLE            DeviceDriverImageHandle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_10      *IFTestProt10;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3       *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  Handle = NULL;
  OverrideDriverImageHandle = NULL;
  DeviceDriverImageHandle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mTestNoInterfaceProtocol2Guid,
                   NULL,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start BusOverrideDriver1
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_OVERRIDE_DRIVER_1_NAME,
             &OverrideDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // load and start TestDeviceDriver4
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             DEVICE_DRIVER_4_NAME,
             &DeviceDriverImageHandle
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->ConnectController (
                     Handle,
                     NULL,
                     NULL,
                     TRUE
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid544;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid545;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid546;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint16",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // protocol10 should be located while protocol11 should not
    //
    Status1 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol10Guid,
                      NULL,
                      (VOID **) &IFTestProt10
                      );
    Status2 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol3Guid,
                      NULL,
                      (VOID **) &IFTestProt3
                      );
    if ((EFI_SUCCESS == Status1)
        && (EFI_NOT_FOUND == Status2)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid547;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid548;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid549;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ConnectController - InterfaceTestCheckpoint16",
                   L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
    //
    // restore environment for next loop
    //
    gtBS->DisconnectController (Handle, NULL, NULL);
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (OverrideDriverImageHandle);
  gtBS->UnloadImage (DeviceDriverImageHandle);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mTestNoInterfaceProtocol2Guid,
          NULL,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

//
// Checkpoint Functions for DisconnectController()
//

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (
                     Handle,
                     NULL,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid550;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid551;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid552;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  //
  // restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (
                     Handle,
                     mImageHandle,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // check status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid553;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid554;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid555;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  //
  // restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            DeviceDriverImageHandle1;
  EFI_HANDLE            DeviceDriverImageHandle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  DeviceDriverImageHandle1 = NULL;
  DeviceDriverImageHandle2 = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external device driver 1, 2
  // driver1 consumes the Handle's protocol1, produces protocol2,
  // driver2 consumes the Handle's protocol2, produces protocol3.
  //
  Status1 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_1_NAME,
              &DeviceDriverImageHandle1
              );
  Status2 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_2_NAME,
              &DeviceDriverImageHandle2
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    Status = gtBS->ConnectController (
                     Handle,
                     NULL,
                     NULL,
                     TRUE
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.ConnectController - build environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      goto Done;
    }
    //
    // disconnect driver2
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (
                     Handle,
                     DeviceDriverImageHandle2,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    //
    // protocol2 should be located while protocol3 should not
    //
    Status1 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol2Guid,
                      NULL,
                      (VOID **) &IFTestProt2
                      );
    Status2 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol3Guid,
                      NULL,
                      (VOID **) &IFTestProt3
                      );
    if ((EFI_SUCCESS == Status1)
        && (EFI_NOT_FOUND == Status2)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid556;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid557;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid558;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint3",
                   L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
    //
    // restore environment
    //
    gtBS->DisconnectController (Handle, NULL, NULL);
  }
  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (DeviceDriverImageHandle1);
  gtBS->UnloadImage (DeviceDriverImageHandle2);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            DeviceDriverImageHandle1;
  EFI_HANDLE            DeviceDriverImageHandle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  DeviceDriverImageHandle1 = NULL;
  DeviceDriverImageHandle2 = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external device driver 1, 2
  // driver1 consumes the Handle's protocol1, produces protocol2,
  // driver2 consumes the Handle's protocol2, produces protocol3.
  Status1 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_1_NAME,
              &DeviceDriverImageHandle1
              );
  Status2 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_2_NAME,
              &DeviceDriverImageHandle2
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    Status = gtBS->ConnectController (
                     Handle,
                     NULL,
                     NULL,
                     TRUE
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.ConnectController - build environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      goto Done;
    }
    //
    // disconnect all drivers
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (
                     Handle,
                     NULL,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid559;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid560;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid561;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                 );
    //
    // both protocol2 and protocol3 could not be located
    //
    Status1 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol2Guid,
                      NULL,
                      (VOID **) &IFTestProt2
                      );
    Status2 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol3Guid,
                      NULL,
                      (VOID **) &IFTestProt3
                      );
    if ((EFI_NOT_FOUND == Status1)
        && (EFI_NOT_FOUND == Status2)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid562;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid563;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid564;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint4",
                   L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
  }

  Status = EFI_SUCCESS;
Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (DeviceDriverImageHandle1);
  gtBS->UnloadImage (DeviceDriverImageHandle2);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            BusDriverImageHandle;
  EFI_HANDLE            DeviceDriverImageHandle1;
  EFI_HANDLE            DeviceDriverImageHandle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status3;
  VOID                  *ProtInstance;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      *IFTestProt3;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      *IFTestProt4;
  INTERFACE_FUNCTION_TEST_PROTOCOL_5      *IFTestProt5;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  BusDriverImageHandle = NULL;
  DeviceDriverImageHandle1 = NULL;
  DeviceDriverImageHandle2 = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external bus driver 3 and device driver 6, 7
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_DRIVER_3_NAME,
             &BusDriverImageHandle
             );
  Status1 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_6_NAME,
              &DeviceDriverImageHandle1
              );
  Status2 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_7_NAME,
              &DeviceDriverImageHandle2
              );
  if (EFI_ERROR (Status) || EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r, Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    Status = gtBS->ConnectController (
                     Handle,
                     NULL,
                     NULL,
                     TRUE
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.ConnectController - build environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      goto Done;
    }
    //
    // disconnect all drivers
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (
                     Handle,
                     NULL,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid565;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid566;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid567;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // protocol2, 3, 4, 5 should not be located
    //
    Status = gtBS->LocateProtocol (
                     &mInterfaceFunctionTestProtocol2Guid,
                     NULL,
                     (VOID **) &IFTestProt2
                     );
    Status1 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol3Guid,
                      NULL,
                      (VOID **) &IFTestProt3
                      );
    Status2 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol4Guid,
                      NULL,
                      (VOID **) &IFTestProt4
                      );
    Status3 = gtBS->LocateProtocol (
                      &mInterfaceFunctionTestProtocol5Guid,
                      NULL,
                      (VOID **) &IFTestProt5
                      );
    if ((EFI_NOT_FOUND == Status)
        && (EFI_NOT_FOUND == Status1)
        && (EFI_NOT_FOUND == Status2)
        && (EFI_NOT_FOUND == Status3)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid568;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid569;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid570;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, Status1 - %r, Status2 - %r, Status3 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Status1,
                   Status2,
                   Status3,
                   TplArray[Index]
                   );
    //
    // busguid installed by bus driver could not be located
    //
    Status = gtBS->HandleProtocol (
                    Handle,
                    &mBusDriver3Guid,
                    (VOID **) &ProtInstance
                    );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid571;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid572;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid573;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  Status = EFI_SUCCESS;

Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (BusDriverImageHandle);
  gtBS->UnloadImage (DeviceDriverImageHandle1);
  gtBS->UnloadImage (DeviceDriverImageHandle2);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_HANDLE            BusDriverImageHandle;
  EFI_HANDLE            DeviceDriverImageHandle1;
  EFI_HANDLE            DeviceDriverImageHandle2;
  EFI_STATUS            Status1;
  EFI_STATUS            Status2;
  EFI_STATUS            Status3;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer2;
  UINTN                 NoHandles2;
  VOID                  *ProtInstance;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;

  UINTN                 Numbers;
  EFI_GUID              TplGuid;

  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  Handle = NULL;
  BusDriverImageHandle = NULL;
  DeviceDriverImageHandle1 = NULL;
  DeviceDriverImageHandle2 = NULL;
  HandleBuffer = NULL;
  HandleBuffer2 = NULL;

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallMultipleProtocolInterfaces - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // load and start external bus driver 3 and device driver 6, 7
  //
  Status = LoadStartImage (
             StandardLib, mImageHandle,
             BUS_DRIVER_3_NAME,
             &BusDriverImageHandle
             );
  Status1 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_6_NAME,
              &DeviceDriverImageHandle1
              );
  Status2 = LoadStartImage (
              StandardLib, mImageHandle,
              DEVICE_DRIVER_7_NAME,
              &DeviceDriverImageHandle2
              );
  if (EFI_ERROR (Status) || EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r, Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    Status = gtBS->ConnectController (Handle, NULL, NULL, TRUE);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.ConnectController - build environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      goto Done;
    }

    //
    // retrieve the child handle that has protocol2 installed,
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol2Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_ERROR (Status) || (NoHandles != 1)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LocateHandleBuffer - build environment",
                     L"%a:%d:Status - %r, Expected - 1, Actual - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     NoHandles,
                     TplArray[Index]
                     );
      goto NextLoop;  // disconnect all drivers
    }

    //
    // disconnect the child handle that has protocol2 installed
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (
                     Handle,
                     NULL,
                     HandleBuffer[0]
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid574;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid575;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid576;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // TestProtocol4, 2 could not be located,
    // while TestProtocol2, 3, 5 could be located
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol4Guid,
                     NULL,
                     &NoHandles2,
                     &HandleBuffer2
                     );
    if (HandleBuffer2 != NULL) {
      gtBS->FreePool (HandleBuffer2);
      HandleBuffer2 = NULL;
    }
    Status1 = gtBS->LocateHandleBuffer (
                      ByProtocol,
                      &mInterfaceFunctionTestProtocol2Guid,
                      NULL,
                      &NoHandles2,
                      &HandleBuffer2
                      );
    if (HandleBuffer2 != NULL) {
      gtBS->FreePool (HandleBuffer2);
      HandleBuffer2 = NULL;
    }
    Status2 = gtBS->LocateHandleBuffer (
                      ByProtocol,
                      &mInterfaceFunctionTestProtocol3Guid,
                      NULL,
                      &NoHandles2,
                      &HandleBuffer2
                      );
    if (HandleBuffer2 != NULL) {
      gtBS->FreePool (HandleBuffer2);
      HandleBuffer2 = NULL;
    }
    Status3 = gtBS->LocateHandleBuffer (
                      ByProtocol,
                      &mInterfaceFunctionTestProtocol5Guid,
                      NULL,
                      &NoHandles2,
                      &HandleBuffer2
                      );
    if (HandleBuffer2 != NULL) {
      gtBS->FreePool (HandleBuffer2);
      HandleBuffer2 = NULL;
    }
    if ((EFI_NOT_FOUND == Status) && (EFI_NOT_FOUND == Status1)
        && (EFI_SUCCESS == Status2) && (EFI_SUCCESS == Status3)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid577;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid578;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid579;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, Status1 - %r, Status2 - %r, Status3 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Status1,
                   Status2,
                   Status3,
                   TplArray[Index]
                   );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // busguid installed by bus driver still could be located
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mBusDriver3Guid,
                     (VOID **) &ProtInstance
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid580;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid581;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid582;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    /*
    //
    // connect the driver back
    //
    gtBS->ConnectController (Handle, NULL, NULL, TRUE);
    */
    //
    // retrieve the child handle that has protocol3 installed,
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol3Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_ERROR (Status) || (NoHandles != 1)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LocateHandleBuffer - build environment",
                     L"%a:%d:Status - %r, Expected - 1, Actual - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     NoHandles,
                     TplArray[Index]
                     );
      goto NextLoop;  // disconnect all drivers
    }

    //
    // disconnect the child handle that has protocol3 installed
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->DisconnectController (
                     Handle,
                     NULL,
                     HandleBuffer[0]
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid583;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid584;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid585;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // TestProtocol5, 2, 3, 4 could not be located,
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol5Guid,
                     NULL,
                     &NoHandles2,
                     &HandleBuffer2
                     );
    if (HandleBuffer2 != NULL) {
      gtBS->FreePool (HandleBuffer2);
      HandleBuffer2 = NULL;
    }
    Status1 = gtBS->LocateHandleBuffer (
                      ByProtocol,
                      &mInterfaceFunctionTestProtocol2Guid,
                      NULL,
                      &NoHandles2,
                      &HandleBuffer2
                      );
    if (HandleBuffer2 != NULL) {
      gtBS->FreePool (HandleBuffer2);
      HandleBuffer2 = NULL;
    }
    Status2 = gtBS->LocateHandleBuffer (
                      ByProtocol,
                      &mInterfaceFunctionTestProtocol3Guid,
                      NULL,
                      &NoHandles2,
                      &HandleBuffer2
                      );
    if (HandleBuffer2 != NULL) {
      gtBS->FreePool (HandleBuffer2);
      HandleBuffer2 = NULL;
    }
    Status3 = gtBS->LocateHandleBuffer (
                      ByProtocol,
                      &mInterfaceFunctionTestProtocol4Guid,
                      NULL,
                      &NoHandles2,
                      &HandleBuffer2
                      );
    if (HandleBuffer2 != NULL) {
      gtBS->FreePool (HandleBuffer2);
      HandleBuffer2 = NULL;
    }
    if ((EFI_NOT_FOUND == Status) && (EFI_NOT_FOUND == Status1)
        && (EFI_NOT_FOUND == Status2) && (EFI_NOT_FOUND == Status3)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid586;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid587;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid588;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, Status1 - %r, Status2 - %r, Status3 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Status1,
                   Status2,
                   Status3,
                   TplArray[Index]
                   );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // both two children have been uninstalled, so busguid installed by bus
    // driver could not be located again
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mBusDriver3Guid,
                     (VOID **) &ProtInstance
                     );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid589;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid590;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_3AssertionGuid591;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.DisconnectController - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
NextLoop:
    //
    // Disconnect all drivers
    //
    Status = gtBS->DisconnectController (Handle, NULL, NULL);
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

  }
  Status = EFI_SUCCESS;

Done:
  //
  // restore environment
  //
  gtBS->UnloadImage (BusDriverImageHandle);
  gtBS->UnloadImage (DeviceDriverImageHandle1);
  gtBS->UnloadImage (DeviceDriverImageHandle2);

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
          NULL
          );
  Status = CheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}
