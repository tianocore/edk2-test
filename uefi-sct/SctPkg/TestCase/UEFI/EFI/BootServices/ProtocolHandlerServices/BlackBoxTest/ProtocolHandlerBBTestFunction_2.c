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

  ProtocolHandlerServicesInterfaceTest_2.c

Abstract:

  for Protocol Handler Boot Services' Interface Function Test

--*/

#include "SctLib.h"
#include "Misc.h"

//
// Checkpoint Functions for InstallProtocolInterface()
//

EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

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
  HandleBuffer = NULL;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;
    IFTestProt1 = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid001;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid002;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid003;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check new handle is created
    //
    if (Handle != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid004;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid005;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid006;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    //
    // Step 3: locate handle via protocol
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((Status == EFI_SUCCESS) && (HandleBuffer[0] == Handle)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid007;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid008;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid009;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, HandleBuffer[0] - 0x%x, Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HandleBuffer[0],
                   Handle,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    //
    // Step 4: locate protocol via handle
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((Status == EFI_SUCCESS)
        && (IFTestProt1 == &InterfaceFunctionTestProt1Instance)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid010;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid011;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid012;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, Protocol - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   IFTestProt1,
                   TplArray[Index]
                   );
    //
    // Step 5: access protocol function
    // this verification based upon success of the Step 4.
    //
    if (NULL != IFTestProt1) {
      IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
      if (ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid013;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid014;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid015;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallProtocolInterface - InterfaceTestCheckpoint1",
                     L"%a:%d:ProtocolId - %x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     ProtocolAttributes.ProtocolId,
                     TplArray[Index]
                     );
    }

    //
    // restore environment for next loop
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallProtocolInterface - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // do not perform following tests
      //
      break;
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

EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint2 (
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
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

  TEST_PROTOCOL_1                         TestProtocol1Instance;
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
  Handle = NULL;
  InitializeTestProtocol1 (&TestProtocol1Instance);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &TestProtocol1Instance
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    HandleBuffer = NULL;
    IFTestProt1 = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    //
    // retrieve the sum of handles
    //
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
                     L"BS.LocateHandleBuffer - get handle number",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
    SavedNoHandles = NoHandles;
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid016;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid017;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid018;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check NO new handle is created
    //
    Status = gtBS->LocateHandleBuffer (
                     AllHandles,
                     NULL,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) || (SavedNoHandles == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid019;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid020;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid021;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, AllHandles - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // Step 3: locate handle via protocol
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((Status == EFI_SUCCESS) || (HandleBuffer[0] == Handle)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid022;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid023;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid024;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, HandleBuffer - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HandleBuffer[0],
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    //
    // Step 4: locate protocol via handle
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((Status == EFI_SUCCESS)
        && (IFTestProt1 == &InterfaceFunctionTestProt1Instance)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid025;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid026;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid027;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, Protocol - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   IFTestProt1,
                   TplArray[Index]
                   );
    //
    // Step 5: access protocol function
    // this verification based upon success of the Step 4.
    //
    if (NULL != IFTestProt1) {
      IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
      if (ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid028;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid029;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid030;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallProtocolInterface - InterfaceTestCheckpoint2",
                     L"%a:%d:ProtocolId - %x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     ProtocolAttributes.ProtocolId,
                     TplArray[Index]
                     );
    }

    //
    // restore environment for next loop
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallProtocolInterface - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // do not perform following tests
      //
      break;
    }
  }

Done:
  //
  // restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestProtocol1Guid,
          &TestProtocol1Instance
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
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle[10];
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  UINTN                 SavedNoHandles;
  UINTN                 HandleIndex;


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1[10];
  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (Handle, 10 * sizeof (EFI_HANDLE), 0);
    HandleBuffer = NULL;
    gtBS->SetMem (IFTestProt1, 10 * sizeof (INTERFACE_FUNCTION_TEST_PROTOCOL_1*), 0);
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    //
    // retrieve the sum of handles
    //
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
                     L"BS.LocateHandleBuffer - get handle number",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }
    SavedNoHandles = NoHandles;
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      Status = gtBS->InstallProtocolInterface (
                       &Handle[HandleIndex],
                       &mInterfaceFunctionTestProtocol1Guid,
                       EFI_NATIVE_INTERFACE,
                       &InterfaceFunctionTestProt1Instance
                       );
      if (EFI_SUCCESS != Status) {
        break;
      }
    }
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid031;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid032;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid033;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, HandleIndex - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HandleIndex,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // Step 2: check 10 new handles are created
    //
    Status = gtBS->LocateHandleBuffer (
                     AllHandles,
                     NULL,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) && ((SavedNoHandles + 10) == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid034;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid035;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid036;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, Increased - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles - SavedNoHandles,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // Step 3: locate handle via protocol
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((Status == EFI_SUCCESS) && (NoHandles == 10)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid037;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid038;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid039;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // Step 4: locate protocol via handle
    //
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      Status = gtBS->HandleProtocol (
                       Handle[HandleIndex],
                       &mInterfaceFunctionTestProtocol1Guid,
                       (VOID **) &IFTestProt1[HandleIndex]
                       );
      if ((Status == EFI_SUCCESS)
        && (IFTestProt1[HandleIndex] == &InterfaceFunctionTestProt1Instance)) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid040;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid041;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid042;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallProtocolInterface - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, HandleIndex - %d, Protocol - 0x%x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     HandleIndex,
                     IFTestProt1[HandleIndex],
                     TplArray[Index]
                     );
      if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
        goto NextLoop;
      }
    }

    //
    // Step 5: access protocol function
    // this verification based upon success of the Step 4.
    //
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {

      IFTestProt1[HandleIndex]->ReportProtocolAttributes (IFTestProt1[Index], &ProtocolAttributes);
      if (ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid043;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid044;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid045;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallProtocolInterface - InterfaceTestCheckpoint3",
                     L"%a:%d:HandleIndex - %d, ProtocolId - %x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     HandleIndex,
                     ProtocolAttributes.ProtocolId,
                     TplArray[Index]
                     );
    }

NextLoop:
    //
    // restore environment for next loop
    //
    for (HandleIndex = 0; HandleIndex < 10; HandleIndex++) {
      if (Handle[HandleIndex] != NULL) {
        Status = gtBS->UninstallProtocolInterface (
                         Handle[HandleIndex],
                         &mInterfaceFunctionTestProtocol1Guid,
                         &InterfaceFunctionTestProt1Instance
                         );
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"BS.UninstallProtocolInterface - restore environment",
                         L"%a:%d:Status - %r, HandleIndex - %d, TPL - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         HandleIndex,
                         TplArray[Index]
                         );
        }
      }
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


EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status = EFI_SUCCESS;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  UINTN                 ProtocolIndex;
  VOID                  *ProtocolInstanceArray[5];
  EFI_GUID              *ProtocolGuidArray[5];
  VOID                  *ProtocolArray[5];


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4      InterfaceFunctionTestProt4Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_5      InterfaceFunctionTestProt5Instance;

  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

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


  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;
    HandleBuffer = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    for (ProtocolIndex = 0; ProtocolIndex < 5; ProtocolIndex++) {
      Status = gtBS->InstallProtocolInterface (
                       &Handle,
                       ProtocolGuidArray[ProtocolIndex],
                       EFI_NATIVE_INTERFACE,
                       ProtocolInstanceArray[ProtocolIndex]
                       );
      if (EFI_SUCCESS != Status) {
        break;
      }
    }
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid046;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid047;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid048;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, ProtocolIndex - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ProtocolIndex,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // Step 2: check new handle is created
    //
    if (Handle != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid049;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid050;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid051;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint4",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: locate handle via protocols
    //
    for (ProtocolIndex = 0; ProtocolIndex < 5; ProtocolIndex++) {
      Status = gtBS->LocateHandleBuffer (
                       ByProtocol,
                       ProtocolGuidArray[ProtocolIndex],
                       NULL,
                       &NoHandles,
                       &HandleBuffer
                       );
      if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid052;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid053;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid054;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallProtocolInterface - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, ProtocolIndex - 0x%x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ProtocolIndex,
                     TplArray[Index]
                     );
      if (NULL != HandleBuffer) {
        gtBS->FreePool (HandleBuffer);
        HandleBuffer = NULL;
      }
    }

    //
    // Step 4: locate protocols via handle
    //
    for (ProtocolIndex = 0; ProtocolIndex < 5; ProtocolIndex++) {
      Status = gtBS->HandleProtocol (
                       Handle,
                       ProtocolGuidArray[ProtocolIndex],
                       (VOID **) &ProtocolArray[ProtocolIndex]
                       );
      if ((Status == EFI_SUCCESS)
          && (ProtocolArray[ProtocolIndex] == ProtocolInstanceArray[ProtocolIndex])) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid055;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid056;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid057;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallProtocolInterface - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
        goto NextLoop;
      }
    }

NextLoop:

    //
    // restore environment for next loop
    //
    for (ProtocolIndex = 0; ProtocolIndex < 5; ProtocolIndex++) {
      Status = gtBS->UninstallProtocolInterface (
                       Handle,
                       ProtocolGuidArray[ProtocolIndex],
                       ProtocolInstanceArray[ProtocolIndex]
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.UninstallProtocolInterface - restore environment",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        //
        // do not perform following tests
        //
        break;
      }
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

EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint5 (
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
  VOID                  *Protocol;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;
    HandleBuffer = NULL;
    Protocol = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid058;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid059;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid060;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check new handle is created
    //
    if (Handle != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid061;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid062;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid063;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    //
    // Step 3: locate handle via protocol
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((Status == EFI_SUCCESS) && (HandleBuffer[0] == Handle)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid064;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid065;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid066;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, HandleBuffer - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HandleBuffer[0],
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    //
    // Step 4: locate protocol via handle
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     (VOID **) &Protocol
                     );
    if ((Status == EFI_SUCCESS) && (Protocol == NULL)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid067;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid068;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid069;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // restore environment for next loop
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallProtocolInterface - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // do not perform following tests
      //
      break;
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
// Checkpoint Functions for UninstallProtocolInterface()
//

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_STATUS            Status1, Status2;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      *IFTestProt2;

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
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status1 = gtBS->InstallProtocolInterface (
                      &Handle,
                      &mInterfaceFunctionTestProtocol1Guid,
                      EFI_NATIVE_INTERFACE,
                      &InterfaceFunctionTestProt1Instance
                      );
    Status2 = gtBS->InstallProtocolInterface (
                      &Handle,
                      &mInterfaceFunctionTestProtocol2Guid,
                      EFI_NATIVE_INTERFACE,
                      &InterfaceFunctionTestProt2Instance
                      );
    if ((EFI_SUCCESS != Status1) || (EFI_SUCCESS != Status2)) {
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
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid070;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid071;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid072;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists: not enough, step 4 can verify this
    //
    if (Handle != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid073;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid074;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid075;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }
    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists on the handle
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid076;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid077;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid078;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, HandleBuffer - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HandleBuffer,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid079;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid080;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid081;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 4: InterfaceFunctionTestProtocol2 still exists on the handle
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2
                     );
    if ((Status == EFI_SUCCESS)
        && (IFTestProt2 == &InterfaceFunctionTestProt2Instance)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid082;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid083;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid084;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, Protocol2 - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   IFTestProt2,
                   TplArray[Index]
                   );
NextLoop:

    //
    // restore environment for next loop
    //
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol2Guid,
            &InterfaceFunctionTestProt2Instance
            );
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
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_STATUS            Status1, Status2;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;

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
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status1 = gtBS->InstallProtocolInterface (
                      &Handle,
                      &mInterfaceFunctionTestProtocol1Guid,
                      EFI_NATIVE_INTERFACE,
                      &InterfaceFunctionTestProt1Instance
                      );
    Status2 = gtBS->InstallProtocolInterface (
                      &Handle,
                      &mInterfaceFunctionTestProtocol2Guid,
                      EFI_NATIVE_INTERFACE,
                      &InterfaceFunctionTestProt2Instance
                      );
    if ((EFI_SUCCESS != Status1) || (EFI_SUCCESS != Status2)) {
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

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status1 = gtBS->UninstallProtocolInterface (
                      Handle,
                      &mInterfaceFunctionTestProtocol1Guid,
                      &InterfaceFunctionTestProt1Instance
                      );
    Status2 = gtBS->UninstallProtocolInterface (
                      Handle,
                      &mInterfaceFunctionTestProtocol2Guid,
                      &InterfaceFunctionTestProt2Instance
                      );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if ((EFI_SUCCESS == Status1) && (EFI_SUCCESS == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid085;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid086;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid087;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle no longer exists
    //
    Status1 = gtBS->OpenProtocol (
                      Handle,
                      &mInterfaceFunctionTestProtocol1Guid,
                      (VOID **) NULL,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
    Status2 = gtBS->OpenProtocol (
                      Handle,
                      &mInterfaceFunctionTestProtocol2Guid,
                      (VOID **) NULL,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
    if ((EFI_INVALID_PARAMETER == Status1) && (EFI_INVALID_PARAMETER == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid088;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid089;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid090;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }
    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid091;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid092;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid093;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint2",
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
    //
    // Step 4: InterfaceFunctionTestProtocol2 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol2Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid094;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid095;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid096;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint2",
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
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint3 (
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol BY_HANDLE_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance
              );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid097;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid098;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid099;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle destroyed
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid100;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid101;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid102;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint3",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }

    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid103;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid104;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid105;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint3",
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
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint4 (
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

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;

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
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol GET_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_GET_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance
              );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid106;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid107;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid108;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle destroyed
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid109;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid110;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid111;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint4",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }

    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid112;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid113;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid114;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint4",
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
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint5 (
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol TEST_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance
              );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid115;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid116;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid117;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle destroyed
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid118;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid119;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid120;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }

    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid121;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid122;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid123;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint5",
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
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint6 (
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
  EFI_HANDLE            ChildHandle;

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
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status = gtBS->InstallProtocolInterface (
                   &ChildHandle,
                   &mInterfaceFunctionTestProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt2Instance
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol BY_CHILD_CONTROLLER
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance
                );
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid124;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid125;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid126;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid127;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid128;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid129;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint6",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: InterfaceFunctionTestProtocol1 still exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid130;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid131;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid132;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint6",
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

    //
    // Step 4: when CloseProtocol InterfaceFunctionTestProtocol1,
    //         uninstall should succeed
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            ChildHandle
            );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid133;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid134;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid135;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint6",
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
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint7 (
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol EXCLUSIVE
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance
              );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid136;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid137;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid138;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid139;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid140;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid141;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint7",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: InterfaceFunctionTestProtocol1 still exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid142;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid143;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid144;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint7",
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

    //
    // Step 4: when CloseProtocol InterfaceFunctionTestProtocol1,
    //         uninstall should succeed
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            NULL
            );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid145;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid146;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid147;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
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
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint8 (
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
  EFI_HANDLE            Handle2;

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

  Handle2 = NULL;
  Status = gtBS->InstallProtocolInterface (
                   &Handle2,
                   &mInterfaceFunctionTestProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt2Instance
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol BY_DRIVER
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     Handle2,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance
              );
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid148;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid149;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid150;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid151;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid152;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid153;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint8",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: InterfaceFunctionTestProtocol1 still exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid154;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid155;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid156;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint8",
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

    //
    // Step 4: when CloseProtocol InterfaceFunctionTestProtocol1,
    //         uninstall should succeed
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            Handle2
            );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid157;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid158;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid159;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint8",
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
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint9 (
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
  EFI_HANDLE            Handle2;

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
  Handle2 = NULL;

  Status = gtBS->InstallProtocolInterface (
                   &Handle2,
                   &mInterfaceFunctionTestProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt2Instance
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol BY_DRIVER | EXCLUSIVE
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     Handle2,
                     (EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE)
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              Handle,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance
              );
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid160;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid161;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid162;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid163;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid164;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid165;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint9",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: InterfaceFunctionTestProtocol1 still exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid166;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid167;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid168;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint9",
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

    //
    // Step 4: when CloseProtocol InterfaceFunctionTestProtocol1,
    //         uninstall should succeed
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            Handle2
            );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid169;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid170;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid171;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint9",
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
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint10 (
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
  VOID                  *Protocol;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;
    Protocol = NULL;

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

    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid172;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid173;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid174;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle no longer exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid175;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid176;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid177;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }
    //
    // Step 3: TestNoInterfaceProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid178;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid179;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid180;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallProtocolInterface - InterfaceTestCheckpoint10",
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
// Checkpoint Functions for ReinstallProtocolInterface()
//

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;

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

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt1Instance
                   );
  if (EFI_SUCCESS != Status) {
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid181;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid182;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid183;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check the new interface pointer equals
    // the address of the old interface
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((EFI_SUCCESS == Status)
          && (IFTestProt1 == &InterfaceFunctionTestProt1Instance)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid184;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid185;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid186;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }

    //
    // Step 3: the protocol interface was really updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField == NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid187;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid188;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid189;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint1",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

  }

Done:
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;

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
  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance1);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance2);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance1
                     );
    if (EFI_SUCCESS != Status) {
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

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid190;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid191;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid192;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check the new interface pointer equals
    // the address of the new interface
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((EFI_SUCCESS == Status)
          && (IFTestProt1 == &InterfaceFunctionTestProt1Instance2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid193;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid194;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid195;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // Step 3: the protocol interface was really updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField == NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid196;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid197;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid198;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint2",
                   L"%a:%d:RetrievedReinstallField - %d, NewReinstallField - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolAttributes.ReinstallField,
                   NewReinstallField,
                   TplArray[Index]
                   );

NextLoop:
    //
    // restore environment for the next loop
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance2
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallProtocolInterface - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
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

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;

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

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt1Instance
                   );
  if (EFI_SUCCESS != Status) {
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    //
    // open protocol BY_HANDLE_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid199;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid200;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid201;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check the new interface pointer equals
    // the address of the old interface
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((EFI_SUCCESS == Status)
          && (IFTestProt1 == &InterfaceFunctionTestProt1Instance)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid202;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid203;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid204;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }

    //
    // Step 3: the protocol interface was really updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField == NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid205;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid206;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid207;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint3",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

  }

Done:
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;

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

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt1Instance
                   );
  if (EFI_SUCCESS != Status) {
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    //
    // open protocol GET_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_GET_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid208;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid209;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid210;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check the new interface pointer equals
    // the address of the old interface
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((EFI_SUCCESS == Status)
          && (IFTestProt1 == &InterfaceFunctionTestProt1Instance)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid211;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid212;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid213;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }

    //
    // Step 3: the protocol interface was really updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField == NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid214;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid215;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid216;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint4",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

  }

Done:
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;

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

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt1Instance
                   );
  if (EFI_SUCCESS != Status) {
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    //
    // open protocol TEST_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     &InterfaceFunctionTestProt1Instance
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid217;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid218;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid219;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check the new interface pointer equals
    // the address of the old interface
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((EFI_SUCCESS == Status)
          && (IFTestProt1 == &InterfaceFunctionTestProt1Instance)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid220;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid221;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid222;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }

    //
    // Step 3: the protocol interface was really updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField == NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid223;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid224;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid225;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint5",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

  }

Done:
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;
  EFI_HANDLE            ChildHandle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance2;
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
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance1);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance2);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status = gtBS->InstallProtocolInterface (
                   &ChildHandle,
                   &mInterfaceFunctionTestProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt2Instance
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance1
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              ChildHandle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance
              );
      return Status;
    }

    //
    // open protocol BY_CHILD_CONTROLLER
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
    if (EFI_SUCCESS != Status) {
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
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid226;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid227;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid228;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: the protocol interface was not updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField != NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid229;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid230;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid231;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint6",
                   L"%a:%d:RetrievedReinstallField - %d, Expected - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolAttributes.ReinstallField,
                   NewReinstallField,
                   TplArray[Index]
                   );

    //
    // Step 3: when close the protocol, the protocol could be reinstalled again
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
                     L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint6",
                     L"%a:%d:CloseProtocol failed, Status- %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid232;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid233;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid234;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
NextLoop:

    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance1
            );
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance2
            );
  }

  //
  // restore environment
  //
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;
  EFI_HANDLE            ChildHandle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance2;
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
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance1);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance2);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status = gtBS->InstallProtocolInterface (
                   &ChildHandle,
                   &mInterfaceFunctionTestProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt2Instance
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance1
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              ChildHandle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance
              );
      return Status;
    }

    //
    // open protocol BY_DRIVER
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
    if (EFI_SUCCESS != Status) {
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
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid235;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid236;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid237;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: the protocol interface was not updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField != NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid238;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid239;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid240;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint7",
                   L"%a:%d:RetrievedReinstallField - %d, Expected - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolAttributes.ReinstallField,
                   NewReinstallField,
                   TplArray[Index]
                   );

    //
    // Step 3: when close the protocol, the protocol could be reinstalled again
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
                     L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint7",
                     L"%a:%d:CloseProtocol failed, Status- %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid241;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid242;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid243;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
NextLoop:
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance1
            );
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance2
            );
  }

  //
  // restore environment
  //
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;

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
  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance1);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance2);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance1
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol EXCLUSIVE
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    if (EFI_SUCCESS != Status) {
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
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid244;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid245;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid246;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: the protocol interface was not updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField != NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid247;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid248;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid249;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint8",
                   L"%a:%d:RetrievedReinstallField - %d, Expected - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolAttributes.ReinstallField,
                   NewReinstallField,
                   TplArray[Index]
                   );

    //
    // Step 3: when close the protocol, the protocol could be reinstalled again
    //
    Status = gtBS->CloseProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     mImageHandle,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint8",
                     L"%a:%d:CloseProtocol failed, Status- %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid250;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid251;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid252;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
NextLoop:

    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance1
            );
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance2
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;
  EFI_HANDLE            ChildHandle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance2;
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
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance1);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance2);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

  Status = gtBS->InstallProtocolInterface (
                   &ChildHandle,
                   &mInterfaceFunctionTestProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt2Instance
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance1
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallProtocolInterface (
              ChildHandle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance
              );
      return Status;
    }

    //
    // open protocol BY_DRIVER | EXCLUSIVE
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     (EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE)
                     );
    if (EFI_SUCCESS != Status) {
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
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ACCESS_DENIED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid253;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid254;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid255;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: the protocol interface was not updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField != NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid256;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid257;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid258;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint9",
                   L"%a:%d:RetrievedReinstallField - %d, Expected - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolAttributes.ReinstallField,
                   NewReinstallField,
                   TplArray[Index]
                   );

    //
    // Step 3: when close the protocol, the protocol could be reinstalled again
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
                     L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint9",
                     L"%a:%d:Status- %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      goto NextLoop;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid259;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid260;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid261;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
NextLoop:
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance1
            );
    gtBS->UninstallProtocolInterface (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            &InterfaceFunctionTestProt1Instance2
            );
  }

  //
  // restore environment
  //
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid262;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid263;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid264;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint10",
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
          &mTestNoInterfaceProtocol1Guid,
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
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint11 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance1;

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
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance1);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     &InterfaceFunctionTestProt1Instance1
                     );
    if (EFI_SUCCESS != Status) {
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

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance1,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid484;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid485;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid486;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint11",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check the new interface pointer equals NULL
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((EFI_SUCCESS == Status)
          && (IFTestProt1 == NULL)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid487;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid488;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid489;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint11",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

NextLoop:
    //
    // restore environment for the next loop
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallProtocolInterface - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
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

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint12 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINT32                NewReinstallField;
  PROTOCOL_ATTRIBUTES   ProtocolAttributes;

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
  //
  // init
  //
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance2);

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    Handle = NULL;

    Status = gtBS->InstallProtocolInterface (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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

    InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField++;
    NewReinstallField = InterfaceFunctionTestProt1Instance2.ProtocolAttributes.ReinstallField;

    Status = gtBS->ReinstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &InterfaceFunctionTestProt1Instance2
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid490;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid491;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid492;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint12",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check the new interface pointer equals
    // the address of the new interface
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((EFI_SUCCESS == Status)
          && (IFTestProt1 == &InterfaceFunctionTestProt1Instance2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid493;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid494;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid495;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint12",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // Step 3: the protocol interface was really updated
    //
    IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
    if (ProtocolAttributes.ReinstallField == NewReinstallField) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid496;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid497;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid498;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.ReinstallProtocolInterface - InterfaceTestCheckpoint12",
                   L"%a:%d:RetrievedReinstallField - %d, NewReinstallField - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ProtocolAttributes.ReinstallField,
                   NewReinstallField,
                   TplArray[Index]
                   );

NextLoop:
    //
    // restore environment for the next loop
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance2
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallProtocolInterface - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
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
// Checkpoint Functions for RegisterProtocolNotify()
//

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[4] = {NULL, NULL, NULL, NULL};
  EFI_STATUS            Status1, Status2, Status3, Status4;
  UINTN                 EventIndex;
  VOID                  *Registration;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_STATUS            Status;

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

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_WAIT,
                    TPL_CALLBACK,
                    TestNotifyFunction0,
                    NULL,
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction0,
                    NULL,
                    &EventArray[1]
                    );
  Status3 = gtBS->CreateEvent (
                    EVT_NOTIFY_WAIT,
                    TPL_NOTIFY,
                    TestNotifyFunction0,
                    NULL,
                    &EventArray[2]
                    );
  Status4 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction0,
                    NULL,
                    &EventArray[3]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) ||
      EFI_ERROR(Status3) || EFI_ERROR(Status4)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4
                   );
    
    for (EventIndex = 0; EventIndex < 4; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    for (EventIndex = 0; EventIndex < 4; EventIndex++) {

      //
      // init
      //
      Registration = NULL;

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->RegisterProtocolNotify (
                       &mTestNoInterfaceProtocol1Guid,
                       EventArray[EventIndex],
                       &Registration
                       );
      gtBS->RestoreTPL (OldTpl);

      //
      // Step 1: check return status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid265;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid266;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid267;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint1",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // Step 2: check registration
      //
      if (NULL != Registration) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid268;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid269;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid270;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint1",
                     L"%a:%d:Registration - 0x%x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Registration,
                     TplArray[Index]
                     );
    }
  }

  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 4; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
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

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[2] = {NULL, NULL};
  EFI_STATUS            Status1, Status2;
  UINTN                 EventIndex;
  VOID                  *Registration;
  UINTN                 NotifiedTimesArray[2];
  EFI_TEST_ASSERTION    AssertionType;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;

  UINTN                 Numbers;

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

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[1],
                    &EventArray[1]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    
    for (EventIndex = 0; EventIndex < 2; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
    
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    //
    // init
    //
    Registration = NULL;

    Status = gtBS->RegisterProtocolNotify (
                     &mTestNoInterfaceProtocol1Guid,
                     EventArray[EventIndex],
                     &Registration
                     );
    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid271,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Step 2: Install TestNoInterfaceProtocol1
  //
  gtBS->SetMem (NotifiedTimesArray, 2 * sizeof (UINTN), 0);
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
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestFunction_2AssertionGuid272,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
    goto Done;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (1 == NotifiedTimesArray[EventIndex]) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid273,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint2",
                   L"%a:%d:EventIndex - %d,NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   NotifiedTimesArray[EventIndex]
                   );
  }

  //
  // Step 3: Reinstall TestNoInterfaceProtocol1
  //
  Status = gtBS->ReinstallProtocolInterface (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestFunction_2AssertionGuid274,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
    goto Done;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (2 == NotifiedTimesArray[EventIndex]) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid275,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint2",
                   L"%a:%d:EventIndex - %d,NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   NotifiedTimesArray[EventIndex]
                   );
  }

Done:
  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
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
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[2] = {NULL, NULL};
  EFI_STATUS            Status1, Status2;
  UINTN                 EventIndex;
  VOID                  *Registration;
  UINTN                 NotifiedTimesArray[2];
  UINTN                 FirstNotifiedTimesArray[2];
  UINTN                 SecondNotifiedTimesArray[2];
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid276[2] = {EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED};
  EFI_TEST_ASSERTION    AssertionTypeGuid277 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid278[2] = {EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED};
  EFI_TEST_ASSERTION    AssertionTypeGuid279 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid280[2] = {EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED};
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  UINTN                 Numbers;
  	
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

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[1],
                    &EventArray[1]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    
     for (EventIndex = 0; EventIndex < 2; EventIndex++) {
       if (EventArray[EventIndex] != NULL) {
         gtBS->CloseEvent (EventArray[EventIndex]);
       }
     }
     return EFI_SUCCESS;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    //
    // init
    //
    Registration = NULL;
    Handle = NULL;

    Status = gtBS->RegisterProtocolNotify (
                     &mTestNoInterfaceProtocol1Guid,
                     EventArray[EventIndex],
                     &Registration
                     );
    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionTypeArrayForGuid276[EventIndex] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionTypeArrayForGuid276[EventIndex] = EFI_TEST_ASSERTION_FAILED;
    }
  }

  
  //
  // Raise TPL to TPL_CALLBACK
  //
  OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);

  //
  // Step 2: Install TestNoInterfaceProtocol1
  //
  gtBS->SetMem (NotifiedTimesArray, 2 * sizeof (UINTN), 0);
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_SUCCESS == Status) {
    AssertionTypeGuid277 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeGuid277 = EFI_TEST_ASSERTION_FAILED;
  }
  
  
  if (EFI_TEST_ASSERTION_FAILED == AssertionTypeGuid277) {
    goto RecordPlace;
  }
  
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // Event 0 will not be signaled, Event 1 ~ 2 will be signaled.
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    FirstNotifiedTimesArray[EventIndex] = NotifiedTimesArray[EventIndex];

    if (EventIndex < 1) {
      if (0 == NotifiedTimesArray[EventIndex]) {
        AssertionTypeArrayForGuid278[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid278[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if (1 == NotifiedTimesArray[EventIndex]) {
        AssertionTypeArrayForGuid278[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid278[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    }
  }


  //
  // Step 3: Reinstall TestNoInterfaceProtocol1
  //
  Status = gtBS->ReinstallProtocolInterface (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_SUCCESS == Status) {
    AssertionTypeGuid279 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeGuid279 = EFI_TEST_ASSERTION_FAILED;
  }

  
  if (EFI_TEST_ASSERTION_FAILED == AssertionTypeGuid279) {
    goto RecordPlace;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // Event 0 will not be signaled, Event 1 ~ 2 will be signaled.
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    SecondNotifiedTimesArray[EventIndex] = NotifiedTimesArray[EventIndex];

    if (EventIndex < 1) {
      if (0 == NotifiedTimesArray[EventIndex]) {
        AssertionTypeArrayForGuid280[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid280[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if (2 == NotifiedTimesArray[EventIndex]) {
        AssertionTypeArrayForGuid280[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid280[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    }
  }

  
RecordPlace:
  //
  // Restore TPL
  //
  gtBS->RestoreTPL (OldTpl);

  //
  // Log test results
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid276[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid276,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeGuid277,
                 gProtocolHandlerBBTestFunction_2AssertionGuid277,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid278[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid278,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint3",
                   L"%a:%d:EventIndex - %d,NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   FirstNotifiedTimesArray[EventIndex]
                   );
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeGuid279,
                 gProtocolHandlerBBTestFunction_2AssertionGuid279,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid278[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid280,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint3",
                   L"%a:%d:EventIndex - %d,NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   SecondNotifiedTimesArray[EventIndex]
                   );
  	}

  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
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
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[2] = {NULL, NULL};
  EFI_STATUS            Status1, Status2;
  UINTN                 EventIndex;
  VOID                  *Registration;
  UINTN                 NotifiedTimesArray[2];
  EFI_TEST_ASSERTION    AssertionType;
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_STATUS            StatusForGuid107;
  EFI_STATUS            StatusForGuid109;
  EFI_TEST_ASSERTION    AssertionTypeForGuid107;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid108[2];
  EFI_TEST_ASSERTION    AssertionTypeForGuid109;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid110[2];
  UINTN                 FirstNotifiedTimesArray[2];
  UINTN                 SecondNotifiedTimesArray[2];

  UINTN                 Numbers;

  StatusForGuid109 = EFI_SUCCESS;
  AssertionTypeForGuid109 = EFI_TEST_ASSERTION_PASSED;

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

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[1],
                    &EventArray[1]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    
    for (EventIndex = 0; EventIndex < 2; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    //
    // init
    //
    Registration = NULL;
    Handle = NULL;

    Status = gtBS->RegisterProtocolNotify (
                     &mTestNoInterfaceProtocol1Guid,
                     EventArray[EventIndex],
                     &Registration
                     );
    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid281,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Raise TPL to TPL_NOTIFY
  // the RecordAssertion could only be invoked at TPL lower
  // than TPL_NOTIFY, therefore, all records will be performed
  // at the label "RecordPlace", where TPL has been lowered down to
  // TPL_APPLICATION
  //
  OldTpl = gtBS->RaiseTPL (TPL_NOTIFY);

  //
  // Step 2: Install TestNoInterfaceProtocol1
  //
  gtBS->SetMem (NotifiedTimesArray, 2 * sizeof (UINTN), 0);
  StatusForGuid107 = gtBS->InstallProtocolInterface (
                             &Handle,
                             &mTestNoInterfaceProtocol1Guid,
                             EFI_NATIVE_INTERFACE,
                             NULL
                             );
  if (EFI_SUCCESS == StatusForGuid107) {
    AssertionTypeForGuid107 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeForGuid107 = EFI_TEST_ASSERTION_FAILED;
    goto RecordPlace;
  }

  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // Event 0, 1 will not be signaled, Event 2 will be signaled.
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    FirstNotifiedTimesArray[EventIndex] = NotifiedTimesArray[EventIndex];

    if (0 == NotifiedTimesArray[EventIndex]) {
      AssertionTypeArrayForGuid108[EventIndex] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionTypeArrayForGuid108[EventIndex] = EFI_TEST_ASSERTION_FAILED;
    }
  }

  //
  // Step 3: Reinstall TestNoInterfaceProtocol1
  //
  StatusForGuid109 = gtBS->ReinstallProtocolInterface (
                             Handle,
                             &mTestNoInterfaceProtocol1Guid,
                             NULL,
                             NULL
                             );
  if (EFI_SUCCESS == StatusForGuid109) {
    AssertionTypeForGuid109 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeForGuid109 = EFI_TEST_ASSERTION_FAILED;
    goto RecordPlace;
  }

  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // Event 0, 1 will not be signaled, Event 2 will be signaled.
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    SecondNotifiedTimesArray[EventIndex] = NotifiedTimesArray[EventIndex];

    if (0 == NotifiedTimesArray[EventIndex]) {
      AssertionTypeArrayForGuid110[EventIndex] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionTypeArrayForGuid110[EventIndex] = EFI_TEST_ASSERTION_FAILED;
    }
  }

RecordPlace:

  gtBS->RestoreTPL (OldTpl);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeForGuid107,
                 gProtocolHandlerBBTestFunction_2AssertionGuid282,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusForGuid107
                 );
  if (EFI_ERROR(StatusForGuid107)) {
    goto Done;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid108[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid283,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint4",
                   L"%a:%d:EventIndex - %d, NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   FirstNotifiedTimesArray[EventIndex]
                   );
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeForGuid109,
                 gProtocolHandlerBBTestFunction_2AssertionGuid284,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusForGuid109
                 );
  if (EFI_ERROR(StatusForGuid109)) {
    goto Done;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid110[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid285,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint4",
                   L"%a:%d:EventIndex - %d, NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   SecondNotifiedTimesArray[EventIndex]
                   );
  }

Done:
  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
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
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[2] = {NULL, NULL};
  EFI_STATUS            Status1, Status2;
  UINTN                 EventIndex;
  NOTIFY_CONTEXT_2      NotifyContextArray[2];
  EFI_TEST_ASSERTION    AssertionType;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;

  UINTN                 Numbers;

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
  // Init
  //
  gtBS->SetMem (NotifyContextArray, 2 * sizeof (NOTIFY_CONTEXT_2), 0);

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction2,
                    &NotifyContextArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction2,
                    &NotifyContextArray[1],
                    &EventArray[1]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );

    for (EventIndex = 0; EventIndex < 2; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->RegisterProtocolNotify (
                     &mTestNoInterfaceProtocol1Guid,
                     EventArray[EventIndex],
                     &(NotifyContextArray[EventIndex].Registration)
                     );
    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid286,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }
  }

  //
  // Step 2: Install TestNoInterfaceProtocol1
  //
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
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestFunction_2AssertionGuid287,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
    goto Done;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    if ((EFI_SUCCESS == NotifyContextArray[EventIndex].Status)
        && (1 == NotifyContextArray[EventIndex].NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid288,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint5",
                   L"%a:%d:EventIndex - %d, Status - %d, Handles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   NotifyContextArray[EventIndex].Status,
                   NotifyContextArray[EventIndex].NoHandles
                   );
    //
    // Reset the Status field
    //
    NotifyContextArray[EventIndex].Status = EFI_NOT_FOUND;
    NotifyContextArray[EventIndex].NoHandles = 0;
  }

  //
  // Step 3: Reinstall TestNoInterfaceProtocol1
  //
  Status = gtBS->ReinstallProtocolInterface (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestFunction_2AssertionGuid289,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
    goto Done;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    if ((EFI_SUCCESS == NotifyContextArray[EventIndex].Status)
        && (1 == NotifyContextArray[EventIndex].NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid290,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint5",
                   L"%a:%d:EventIndex - %d, Status - %r, Handles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   NotifyContextArray[EventIndex].Status,
                   NotifyContextArray[EventIndex].NoHandles
                   );
  }

Done:
  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }


  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
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
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[2] = {NULL, NULL};
  EFI_STATUS            Status1, Status2;
  UINTN                 EventIndex;
  NOTIFY_CONTEXT_2      NotifyContextArray[2];
  NOTIFY_CONTEXT_2      FirstNotifyContextArray[2];
  NOTIFY_CONTEXT_2      SecondNotifyContextArray[2];  
  EFI_TEST_ASSERTION    AssertionType;
  EFI_TEST_ASSERTION    AssertionTypeGuid292 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid293[2] = {EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED};
  EFI_TEST_ASSERTION    AssertionTypeGuid294 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid295[2] = {EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED};
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  UINTN                 Numbers;

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
  // Init
  //
  gtBS->SetMem (NotifyContextArray, 2 * sizeof (NOTIFY_CONTEXT_2), 0);
  NotifyContextArray[0].Status = 0x5a;
  NotifyContextArray[1].Status = 0x5a;

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction2,
                    &NotifyContextArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction2,
                    &NotifyContextArray[1],
                    &EventArray[1]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    
    for (EventIndex = 0; EventIndex < 2; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->RegisterProtocolNotify (
                     &mTestNoInterfaceProtocol1Guid,
                     EventArray[EventIndex],
                     &(NotifyContextArray[EventIndex].Registration)
                     );
    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid291,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }
  }

  //
  // Raise TPL to TPL_CALLBACK
  //
  OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);

  //
  // Step 2: Install TestNoInterfaceProtocol1
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_SUCCESS == Status) {
    AssertionTypeGuid292 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeGuid292 = EFI_TEST_ASSERTION_FAILED;
  }
 
  if (EFI_TEST_ASSERTION_FAILED == AssertionTypeGuid292) {
    goto RecordPlace;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // Event 0 not be signaled, Event 1 will be signaled.
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
  	
    FirstNotifyContextArray[EventIndex] = NotifyContextArray[EventIndex];

    if (EventIndex < 1) {
      if (0x5a == NotifyContextArray[EventIndex].Status) {
      	
        AssertionTypeArrayForGuid293[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid293[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if ((EFI_SUCCESS == NotifyContextArray[EventIndex].Status)
        && (1 == NotifyContextArray[EventIndex].NoHandles)) {
        
        AssertionTypeArrayForGuid293[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid293[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    }

    //
    // Reset the Status field
    //
    NotifyContextArray[EventIndex].Status = 0x5a;
    NotifyContextArray[EventIndex].NoHandles = 0;
  }

  //
  // Step 3: Reinstall TestNoInterfaceProtocol1
  //
  Status = gtBS->ReinstallProtocolInterface (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_SUCCESS == Status) {
    AssertionTypeGuid294 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeGuid294 = EFI_TEST_ASSERTION_FAILED;
  }
 
  if (EFI_TEST_ASSERTION_FAILED == AssertionTypeGuid294) {
    goto RecordPlace;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // Event 0 not be signaled, Event 1 will be signaled.
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    SecondNotifyContextArray[EventIndex] = NotifyContextArray[EventIndex];

    if (EventIndex < 1) {
      if (0x5a == NotifyContextArray[EventIndex].Status) {

        AssertionTypeArrayForGuid295[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid295[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if ((EFI_SUCCESS == NotifyContextArray[EventIndex].Status)
        && (1 == NotifyContextArray[EventIndex].NoHandles)) {

        AssertionTypeArrayForGuid295[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid295[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    }

  }

RecordPlace:
  //
  // Restore TPL
  // 
  gtBS->RestoreTPL (OldTpl);
  //
  // Log test results
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeGuid292,
                 gProtocolHandlerBBTestFunction_2AssertionGuid292,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint6",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid293[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid293,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint6",
                   L"%a:%d:EventIndex - %d, Status - %r, Handles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   FirstNotifyContextArray[EventIndex].Status,
                   FirstNotifyContextArray[EventIndex].NoHandles
                   );
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeGuid294,
                 gProtocolHandlerBBTestFunction_2AssertionGuid294,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint6",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid295[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid295,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint6",
                   L"%a:%d:EventIndex - %d, Status - %r, Handles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   SecondNotifyContextArray[EventIndex].Status,
                   SecondNotifyContextArray[EventIndex].NoHandles
                   );
  	}
  
Done:
  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
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
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[2] = {NULL, NULL};
  EFI_STATUS            Status1, Status2;
  UINTN                 EventIndex;
  NOTIFY_CONTEXT_2      NotifyContextArray[2];
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_STATUS            StatusForGuid122;
  EFI_STATUS            StatusForGuid124;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_TEST_ASSERTION    AssertionTypeForGuid122;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid123[2];
  EFI_TEST_ASSERTION    AssertionTypeForGuid124;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid125[2];
  NOTIFY_CONTEXT_2      FirstNotifyContextArray[2];
  NOTIFY_CONTEXT_2      SecondNotifyContextArray[2];

  UINTN                 Numbers;

  StatusForGuid124 = EFI_SUCCESS;
  AssertionTypeForGuid124 = EFI_TEST_ASSERTION_PASSED;

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
  // Init
  //
  gtBS->SetMem (NotifyContextArray, 2 * sizeof (NOTIFY_CONTEXT_2), 0);
  NotifyContextArray[0].Status = 0x5a;
  NotifyContextArray[1].Status = 0x5a;

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction2,
                    &NotifyContextArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction2,
                    &NotifyContextArray[1],
                    &EventArray[1]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );

    for (EventIndex = 0; EventIndex < 2; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    //
    // init
    //
    Handle = NULL;

    Status = gtBS->RegisterProtocolNotify (
                     &mTestNoInterfaceProtocol1Guid,
                     EventArray[EventIndex],
                     &(NotifyContextArray[EventIndex].Registration)
                     );
    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid296,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }
  }

  //
  // Raise TPL to TPL_NOTIFY
  // the RecordAssertion could only be invoked at TPL lower
  // than TPL_NOTIFY, therefore, all records will be performed
  // at the label "RecordPlace", where TPL has been lowered down to
  // TPL_APPLICATION
  //
  OldTpl = gtBS->RaiseTPL (TPL_NOTIFY);

  //
  // Step 2: Install TestNoInterfaceProtocol1
  //
  StatusForGuid122 = gtBS->InstallProtocolInterface (
                       &Handle,
                       &mTestNoInterfaceProtocol1Guid,
                       EFI_NATIVE_INTERFACE,
                       NULL
                       );
  if (EFI_SUCCESS == StatusForGuid122) {
    AssertionTypeForGuid122 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeForGuid122 = EFI_TEST_ASSERTION_FAILED;
    goto RecordPlace;
  }

  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // Event 0 ~ 1 not be signaled
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    FirstNotifyContextArray[EventIndex] = NotifyContextArray[EventIndex];

    if (0x5a == NotifyContextArray[EventIndex].Status) {

      AssertionTypeArrayForGuid123[EventIndex] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionTypeArrayForGuid123[EventIndex] = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Reset the Status field
    //
    NotifyContextArray[EventIndex].Status = 0x5a;
    NotifyContextArray[EventIndex].NoHandles = 0;
  }

  //
  // Step 3: Reinstall TestNoInterfaceProtocol1
  //
  StatusForGuid124 = gtBS->ReinstallProtocolInterface (
                       Handle,
                       &mTestNoInterfaceProtocol1Guid,
                       NULL,
                       NULL
                       );
  if (EFI_SUCCESS == StatusForGuid124) {
    AssertionTypeForGuid124 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeForGuid124 = EFI_TEST_ASSERTION_FAILED;
    goto RecordPlace;
  }

  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // Event 0 ~ 1 not be signaled
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    SecondNotifyContextArray[EventIndex] = NotifyContextArray[EventIndex];

    if (0x5a == NotifyContextArray[EventIndex].Status) {

      AssertionTypeArrayForGuid125[EventIndex] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionTypeArrayForGuid125[EventIndex] = EFI_TEST_ASSERTION_FAILED;
    }
  }

RecordPlace:

  gtBS->RestoreTPL (OldTpl);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeForGuid122,
                 gProtocolHandlerBBTestFunction_2AssertionGuid297,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint7",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusForGuid122
                 );
  if (EFI_ERROR(StatusForGuid122)) {
    goto Done;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid123[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid298,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint7",
                   L"%a:%d:EventIndex - %d, Status - %r, Handles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   FirstNotifyContextArray[EventIndex].Status,
                   FirstNotifyContextArray[EventIndex].NoHandles
                   );
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeForGuid124,
                 gProtocolHandlerBBTestFunction_2AssertionGuid299,
                 L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint7",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusForGuid124
                 );
  if (EFI_ERROR(StatusForGuid124)) {
    goto Done;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid125[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid300,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint7",
                   L"%a:%d:EventIndex - %d, Status - %r, Handles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   SecondNotifyContextArray[EventIndex].Status,
                   SecondNotifyContextArray[EventIndex].NoHandles
                   );
  }

Done:
  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }

  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
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
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[2] = {NULL, NULL};
  EFI_STATUS            Status1, Status2;
  UINTN                 EventIndex;
  VOID                  *Registration;
  UINTN                 NotifiedTimesArray[2];
  EFI_TEST_ASSERTION    AssertionType;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;

  UINTN                 Numbers;

  Handle = NULL;

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

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[1],
                    &EventArray[1]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    
    for (EventIndex = 0; EventIndex < 2; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return Status1 | Status2;
  }

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {

    //
    // init
    //
    Registration = NULL;

    Status = gtBS->RegisterProtocolNotify (
                     &mTestNoInterfaceProtocol1Guid,
                     EventArray[EventIndex],
                     &Registration
                     );
    if (EFI_SUCCESS != Status) {
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
      break;
    }
  }
  if (EFI_SUCCESS != Status) {
    for (EventIndex = 0; EventIndex < 2; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return Status;
  }
  
  //
  // Step 2: Close the events at first, and then InstallProtocolInterface
  //
  gtBS->SetMem (NotifiedTimesArray, 2 * sizeof (UINTN), 0);

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }  
  

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_SUCCESS != Status) {

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
  
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (0 == NotifiedTimesArray[EventIndex]) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid523,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint8",
                   L"%a:%d:EventIndex - %d,NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   NotifiedTimesArray[EventIndex]
                   );
  }

  //
  // Step 3: Reinstall TestNoInterfaceProtocol1
  //
  Status = gtBS->ReinstallProtocolInterface (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_SUCCESS != Status) {

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

    goto Done;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  for (EventIndex = 0; EventIndex < 2; EventIndex++) {
    if (0 == NotifiedTimesArray[EventIndex]) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid524,
                   L"BS.RegisterProtocolNotify - InterfaceTestCheckpoint8",
                   L"%a:%d:EventIndex - %d,NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   NotifiedTimesArray[EventIndex]
                   );
  }

Done:
  //
  // restore environment
  //
  if (Handle != NULL) {
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
// Checkpoint Functions for InstallMultipleProtocolInterfaces()
//

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;
    IFTestProt1 = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);
    HandleBuffer = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->InstallMultipleProtocolInterfaces (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid301;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid302;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid303;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check new handle is created
    //
    if (NULL != Handle) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid304;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid305;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid306;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    //
    // Step 3: locate handle via protocol
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) && (HandleBuffer[0] == Handle)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid307;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid308;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid309;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, HandleBuffer[0] - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HandleBuffer[0],
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    //
    // Step 4: locate protocol via handle
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((EFI_SUCCESS == Status)
        && (IFTestProt1 == &InterfaceFunctionTestProt1Instance)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid310;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid311;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid312;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, Protocol - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   IFTestProt1,
                   TplArray[Index]
                   );
    //
    // Step 5: access protocol function
    // this verification based upon success of the Step 4.
    //
    if (NULL != IFTestProt1) {
      IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
      if (ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid313;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid314;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid315;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                     L"%a:%d:ProtocolId - %x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     ProtocolAttributes.ProtocolId,
                     TplArray[Index]
                     );
    }

    //
    // restore environment for next loop
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallProtocolInterface - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // do not perform following tests
      //
      break;
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

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint2 (
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
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      *IFTestProt1;
  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

  TEST_PROTOCOL_1                         TestProtocol1Instance;

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
  InitializeTestProtocol1 (&TestProtocol1Instance);
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   &TestProtocol1Instance
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    HandleBuffer = NULL;
    IFTestProt1 = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    //
    // retrieve the sum of handles
    //
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
                     L"BS.LocateHandleBuffer - get handle number",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
    SavedNoHandles = NoHandles;
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->InstallMultipleProtocolInterfaces (
                     &Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid316;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid317;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid318;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check NO new handle is created
    //
    Status = gtBS->LocateHandleBuffer (
                     AllHandles,
                     NULL,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) || (SavedNoHandles == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid319;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid320;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid321;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, AllHandles - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // Step 3: locate handle via protocol
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((Status == EFI_SUCCESS) || (HandleBuffer[0] == Handle)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid322;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid323;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid324;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, HandleBuffer - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HandleBuffer[0],
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }
    //
    // Step 4: locate protocol via handle
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if ((Status == EFI_SUCCESS)
        && (IFTestProt1 == &InterfaceFunctionTestProt1Instance)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid325;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid326;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid327;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, Protocol - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   IFTestProt1,
                   TplArray[Index]
                   );
    //
    // Step 5: access protocol function
    // this verification based upon success of the Step 4.
    //
    if (NULL != IFTestProt1) {
      IFTestProt1->ReportProtocolAttributes (IFTestProt1, &ProtocolAttributes);
      if (ProtocolAttributes.ProtocolId == InterfaceFunctionTestProtocol1Id) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid328;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid329;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid330;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
                     L"%a:%d:ProtocolId - %x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     ProtocolAttributes.ProtocolId,
                     TplArray[Index]
                     );
    }

    //
    // restore environment for next loop
    //
    Status = gtBS->UninstallProtocolInterface (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallProtocolInterface - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // do not perform following tests
      //
      break;
    }
  }

Done:
  //
  // restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestProtocol1Guid,
          &TestProtocol1Instance
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
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint3 (
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
  UINTN                 ProtocolIndex;
  VOID                  *ProtocolInstanceArray[3];
  EFI_GUID              *ProtocolGuidArray[3];
  VOID                  *ProtocolArray[3];


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;

  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

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

  ProtocolInstanceArray[0] = (VOID*)&InterfaceFunctionTestProt1Instance;
  ProtocolInstanceArray[1] = (VOID*)&InterfaceFunctionTestProt2Instance;
  ProtocolInstanceArray[2] = (VOID*)&InterfaceFunctionTestProt3Instance;

  ProtocolGuidArray[0] = &mInterfaceFunctionTestProtocol1Guid;
  ProtocolGuidArray[1] = &mInterfaceFunctionTestProtocol2Guid;
  ProtocolGuidArray[2] = &mInterfaceFunctionTestProtocol3Guid;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;
    HandleBuffer = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
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
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid331;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid332;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid333;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // Step 2: check new handle is created
    //
    if (NULL != Handle) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid334;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid335;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid336;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: locate handle via protocols
    //
    for (ProtocolIndex = 0; ProtocolIndex < 3; ProtocolIndex++) {
      Status = gtBS->LocateHandleBuffer (
                       ByProtocol,
                       ProtocolGuidArray[ProtocolIndex],
                       NULL,
                       &NoHandles,
                       &HandleBuffer
                       );
      if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid337;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid338;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid339;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, ProtocolIndex - 0x%x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ProtocolIndex,
                     TplArray[Index]
                     );
      if (NULL != HandleBuffer) {
        gtBS->FreePool (HandleBuffer);
        HandleBuffer = NULL;
      }
    }

    //
    // Step 4: locate protocols via handle
    //
    for (ProtocolIndex = 0; ProtocolIndex < 3; ProtocolIndex++) {
      Status = gtBS->HandleProtocol (
                       Handle,
                       ProtocolGuidArray[ProtocolIndex],
                       (VOID **) &ProtocolArray[ProtocolIndex]
                       );
      if ((EFI_SUCCESS == Status)
          && (ProtocolArray[ProtocolIndex] == ProtocolInstanceArray[ProtocolIndex])) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid340;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid341;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid342;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
        goto NextLoop;
      }
    }

NextLoop:

    //
    // restore environment for next loop
    //
    for (ProtocolIndex = 0; ProtocolIndex < 3; ProtocolIndex++) {
      Status = gtBS->UninstallProtocolInterface (
                       Handle,
                       ProtocolGuidArray[ProtocolIndex],
                       ProtocolInstanceArray[ProtocolIndex]
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.UninstallProtocolInterface - restore environment",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                     );
        //
        // do not perform following tests
        //
        break;
      }
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

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint4 (
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
  UINTN                 ProtocolIndex;
  VOID                  *ProtocolInstanceArray[3];
  EFI_GUID              *ProtocolGuidArray[3];
  VOID                  *ProtocolArray[3];


  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;

  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

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

  ProtocolInstanceArray[0] = (VOID*)&InterfaceFunctionTestProt1Instance;
  ProtocolInstanceArray[1] = (VOID*)&InterfaceFunctionTestProt2Instance;
  ProtocolInstanceArray[2] = (VOID*)&InterfaceFunctionTestProt3Instance;

  ProtocolGuidArray[0] = &mInterfaceFunctionTestProtocol1Guid;
  ProtocolGuidArray[1] = &mInterfaceFunctionTestProtocol2Guid;
  ProtocolGuidArray[2] = &mInterfaceFunctionTestProtocol3Guid;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    HandleBuffer = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    //
    // retrieve the sum of handles
    //
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
                     L"BS.LocateHandleBuffer - get handle number",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
    SavedNoHandles = NoHandles;
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
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
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid343;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid344;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid345;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // Step 2: check NO new handle is created
    //
    Status = gtBS->LocateHandleBuffer (
                     AllHandles,
                     NULL,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) || (SavedNoHandles == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid346;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid347;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid348;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, AllHandles - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // Step 3: locate handle via protocols
    //
    for (ProtocolIndex = 0; ProtocolIndex < 3; ProtocolIndex++) {
      Status = gtBS->LocateHandleBuffer (
                       ByProtocol,
                       ProtocolGuidArray[ProtocolIndex],
                       NULL,
                       &NoHandles,
                       &HandleBuffer
                       );
      if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid349;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid350;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid351;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, ProtocolIndex - 0x%x, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ProtocolIndex,
                     TplArray[Index]
                     );
      if (NULL != HandleBuffer) {
        gtBS->FreePool (HandleBuffer);
        HandleBuffer = NULL;
      }
    }

    //
    // Step 4: locate protocols via handle
    //
    for (ProtocolIndex = 0; ProtocolIndex < 3; ProtocolIndex++) {
      Status = gtBS->HandleProtocol (
                       Handle,
                       ProtocolGuidArray[ProtocolIndex],
                       (VOID **) &ProtocolArray[ProtocolIndex]
                       );
      if ((EFI_SUCCESS == Status)
          && (ProtocolArray[ProtocolIndex] == ProtocolInstanceArray[ProtocolIndex])) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid352;
      } else if (Index == 1) {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid353;
      } else {
        TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid354;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
        goto NextLoop;
      }
    }

NextLoop:

    //
    // restore environment for next loop
    //
    for (ProtocolIndex = 0; ProtocolIndex < 3; ProtocolIndex++) {
      Status = gtBS->UninstallProtocolInterface (
                       Handle,
                       ProtocolGuidArray[ProtocolIndex],
                       ProtocolInstanceArray[ProtocolIndex]
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.UninstallProtocolInterface - restore environment",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        //
        // do not perform following tests
        //
        break;
      }
    }
  }

Done:
  //
  // restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol1Guid,
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
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle1;
  EFI_STATUS            Status, Status1, Status2;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  UINTN                 SavedNoHandles;
  EFI_HANDLE            Handle2;

  EFI_DEVICE_PATH_PROTOCOL                *DevicePath1;
  EFI_DEVICE_PATH_PROTOCOL                *DevicePath2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  PROTOCOL_ATTRIBUTES                     ProtocolAttributes;

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

  //
  // Create 2 identical vendor device paths  ## destroy before leave
  //
  CreateVendorDevicePath (&DevicePath1, mVendorDevicePath1Guid);
  CreateVendorDevicePath (&DevicePath2, mVendorDevicePath1Guid);

  Handle1 = NULL;

  //
  // Install a vendor device path onto a new handle. ## destroy before leave
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle1,
                   &gEfiDevicePathProtocolGuid,
                   EFI_NATIVE_INTERFACE,
                   DevicePath1
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
    FreeVendorDevicePath (DevicePath1);
    FreeVendorDevicePath (DevicePath2);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle2 = NULL;
    HandleBuffer = NULL;
    gtBS->SetMem (&ProtocolAttributes, sizeof (PROTOCOL_ATTRIBUTES), 0);

    //
    // retrieve the sum of handles
    //
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
                     L"BS.LocateHandleBuffer - get handle number",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
    SavedNoHandles = NoHandles;
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->InstallMultipleProtocolInterfaces (
                     &Handle2,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &gEfiDevicePathProtocolGuid,
                     DevicePath2,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_ALREADY_STARTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid355;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid356;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid357;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // Step 2: check NO new handle is created
    //
    Status = gtBS->LocateHandleBuffer (
                     AllHandles,
                     NULL,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) || (SavedNoHandles == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid358;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid359;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid360;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, AllHandles - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );
    if (NULL != HandleBuffer) {
      gtBS->FreePool (HandleBuffer);
      HandleBuffer = NULL;
    }

    //
    // Step 3: Protocol1 and Protocol2 could not be located
    //
    Status1 = gtBS->LocateHandleBuffer (
                      ByProtocol,
                      &mInterfaceFunctionTestProtocol1Guid,
                      NULL,
                      &NoHandles,
                      &HandleBuffer
                      );
    if (NULL != HandleBuffer) {
        gtBS->FreePool (HandleBuffer);
        HandleBuffer = NULL;
    }
    Status2 = gtBS->LocateHandleBuffer (
                      ByProtocol,
                      &mInterfaceFunctionTestProtocol2Guid,
                      NULL,
                      &NoHandles,
                      &HandleBuffer
                      );
    if (NULL != HandleBuffer) {
        gtBS->FreePool (HandleBuffer);
        HandleBuffer = NULL;
    }

    if ((EFI_NOT_FOUND == Status1) && (EFI_NOT_FOUND == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid361;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid362;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid363;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

NextLoop:

    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      //
      // restore environment for next loop
      //
      Status = gtBS->UninstallMultipleProtocolInterfaces (
                       Handle2,
                       &mInterfaceFunctionTestProtocol1Guid,
                       &InterfaceFunctionTestProt1Instance,
                       &mInterfaceFunctionTestProtocol2Guid,
                       &InterfaceFunctionTestProt2Instance,
                       NULL
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.UninstallMultipleProtocolInterfaces - restore environment",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
      }
    }
  }

Done:
  //
  // restore environment
  //
  gtBS->UninstallProtocolInterface (
          Handle1,
          &gEfiDevicePathProtocolGuid,
          DevicePath1
          );
  FreeVendorDevicePath (DevicePath1);
  FreeVendorDevicePath (DevicePath2);

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
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[4];
  EFI_STATUS            Status1, Status2, Status3, Status4;
  UINTN                 EventIndex;
  VOID                  *Registration;
  UINTN                 NotifiedTimesArray[4];
  EFI_TEST_ASSERTION    AssertionType;
  EFI_STATUS            Status;
  EFI_HANDLE            Handle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;

  UINTN                 Numbers;

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

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[1],
                    &EventArray[1]
                    );
  Status3 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[2],
                    &EventArray[2]
                    );
  Status4 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[3],
                    &EventArray[3]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) ||
      EFI_ERROR(Status3) || EFI_ERROR(Status4)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4
                   );

    for (EventIndex = 0; EventIndex < 4; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
  }

  for (EventIndex = 0; EventIndex < 4;) {

    //
    // init
    //
    Registration = NULL;
    Handle = NULL;

    Status1 = gtBS->RegisterProtocolNotify (
                      &mInterfaceFunctionTestProtocol1Guid,
                      EventArray[EventIndex++],
                      &Registration
                      );
    Status2 = gtBS->RegisterProtocolNotify (
                      &mInterfaceFunctionTestProtocol2Guid,
                      EventArray[EventIndex++],
                      &Registration
                      );
    //
    // Step 1: check return status
    //
    if ((EFI_SUCCESS == Status1) && (EFI_SUCCESS == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid364,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }
  }

  //
  // Step 2: Install Protocol1 & Protocol2
  //
  gtBS->SetMem (NotifiedTimesArray, 4 * sizeof (UINTN), 0);
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   &mInterfaceFunctionTestProtocol2Guid,
                   &InterfaceFunctionTestProt2Instance,
                   NULL
                   );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerBBTestFunction_2AssertionGuid365,
                 L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
                 L"%a:%d:Status - %r, TPL - TPL_APPLICATION",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
    goto Done;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  for (EventIndex = 0; EventIndex < 4; EventIndex++) {
    if (1 == NotifiedTimesArray[EventIndex]) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid366,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
                   L"%a:%d:EventIndex - %d, NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   NotifiedTimesArray[EventIndex]
                   );
  }

Done:
  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 4; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
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

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[4] = {NULL, NULL, NULL, NULL};
  EFI_STATUS            Status1, Status2, Status3, Status4;
  UINTN                 EventIndex;
  VOID                  *Registration;
  UINTN                 NotifiedTimesArray[4];
  EFI_TEST_ASSERTION    AssertionType;
  EFI_TEST_ASSERTION    AssertionTypeGuid368 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid369[4] = {EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED};
  EFI_TPL               OldTpl;
  EFI_STATUS            Status;
  EFI_HANDLE            Handle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;

  UINTN                 Numbers;

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

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[1],
                    &EventArray[1]
                    );
  Status3 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[2],
                    &EventArray[2]
                    );
  Status4 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[3],
                    &EventArray[3]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) ||
      EFI_ERROR(Status3) || EFI_ERROR(Status4)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4
                   );
    
    for (EventIndex = 0; EventIndex < 4; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
  }

  for (EventIndex = 0; EventIndex < 4;) {

    //
    // init
    //
    Registration = NULL;
    Handle = NULL;

    Status1 = gtBS->RegisterProtocolNotify (
                      &mInterfaceFunctionTestProtocol1Guid,
                      EventArray[EventIndex++],
                      &Registration
                      );
    Status2 = gtBS->RegisterProtocolNotify (
                      &mInterfaceFunctionTestProtocol2Guid,
                      EventArray[EventIndex++],
                      &Registration
                      );
    //
    // Step 1: check return status
    //
    if ((EFI_SUCCESS == Status1) && (EFI_SUCCESS == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid367,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint7",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }
  }

  //
  // Step 2: Install Protocol1 & Protocol2
  //
  OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);

  gtBS->SetMem (NotifiedTimesArray, 4 * sizeof (UINTN), 0);
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   &mInterfaceFunctionTestProtocol2Guid,
                   &InterfaceFunctionTestProt2Instance,
                   NULL
                   );
  if (EFI_SUCCESS == Status) {
    AssertionTypeGuid368 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeGuid368 = EFI_TEST_ASSERTION_FAILED;
  }

  if (EFI_TEST_ASSERTION_FAILED == AssertionTypeGuid368) {
    goto RecordPlace;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // EventIndex 0 ~ 1 will not be signaled, EventIndex 2 ~ 5 will be signaled.
  //
  for (EventIndex = 0; EventIndex < 4; EventIndex++) {

    if (EventIndex < 2) {
      if (0 == NotifiedTimesArray[EventIndex]) {
        AssertionTypeArrayForGuid369[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid369[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if (1 == NotifiedTimesArray[EventIndex]) {
        AssertionTypeArrayForGuid369[EventIndex] = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionTypeArrayForGuid369[EventIndex] = EFI_TEST_ASSERTION_FAILED;
      }
    }
  }

RecordPlace:
  //
  // Restore TPL
  //
  gtBS->RestoreTPL (OldTpl);
  //
  // Log results
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeGuid368,
                 gProtocolHandlerBBTestFunction_2AssertionGuid368,
                 L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint7",
                 L"%a:%d:Status - %r, TPL - TPL_CALLBACK",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
   
  for (EventIndex = 0; EventIndex < 4; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid369[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid369,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint7",
                   L"%a:%d:EventIndex - %d, NotifiedTimes - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex,
                   NotifiedTimesArray[EventIndex]
                   );
  }
Done:
  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 4; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
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

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_EVENT             EventArray[4] = {NULL, NULL, NULL, NULL};
  EFI_STATUS            Status1, Status2, Status3, Status4;
  UINTN                 EventIndex;
  VOID                  *Registration;
  UINTN                 NotifiedTimesArray[4];
  EFI_TEST_ASSERTION    AssertionType;
  EFI_TEST_ASSERTION    AssertionTypeGuid371 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION    AssertionTypeArrayForGuid372[4] = {EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED, \
                                                           EFI_TEST_ASSERTION_FAILED};
  EFI_TPL               OldTpl;
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;

  UINTN                 Numbers;

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

  Status1 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[0],
                    &EventArray[0]
                    );
  Status2 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[1],
                    &EventArray[1]
                    );
  Status3 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[2],
                    &EventArray[2]
                    );
  Status4 = gtBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    TestNotifyFunction1,
                    &NotifiedTimesArray[3],
                    &EventArray[3]
                    );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) ||
      EFI_ERROR(Status3) || EFI_ERROR(Status4)) {

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - build environment",
                   L"%a:%d:Statuses - %r %r %r %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4
                   );

    for (EventIndex = 0; EventIndex < 4; EventIndex++) {
      if (EventArray[EventIndex] != NULL) {
        gtBS->CloseEvent (EventArray[EventIndex]);
      }
    }
    return EFI_SUCCESS;
  }

  for (EventIndex = 0; EventIndex < 4;) {

    //
    // init
    //
    Registration = NULL;
    Handle = NULL;

    Status1 = gtBS->RegisterProtocolNotify (
                      &mInterfaceFunctionTestProtocol1Guid,
                      EventArray[EventIndex++],
                      &Registration
                      );
    Status2 = gtBS->RegisterProtocolNotify (
                      &mInterfaceFunctionTestProtocol2Guid,
                      EventArray[EventIndex++],
                      &Registration
                      );
    //
    // Step 1: check return status
    //
    if ((EFI_SUCCESS == Status1) && (EFI_SUCCESS == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerBBTestFunction_2AssertionGuid370,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint8",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto Done;
    }
  }

  //
  // Step 2: Install Protocol1 & Protocol2
  //
  OldTpl = gtBS->RaiseTPL (TPL_NOTIFY);

  gtBS->SetMem (NotifiedTimesArray, 4 * sizeof (UINTN), 0);
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mInterfaceFunctionTestProtocol1Guid,
                   &InterfaceFunctionTestProt1Instance,
                   &mInterfaceFunctionTestProtocol2Guid,
                   &InterfaceFunctionTestProt2Instance,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    AssertionTypeGuid371 = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionTypeGuid371 = EFI_TEST_ASSERTION_FAILED;
  }
  
  if (EFI_TEST_ASSERTION_FAILED == AssertionTypeGuid371) {
    goto RecordPlace;
  }
  //
  // stall 10 seconds to wait for notify function execution
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  //
  // EventIndex 0 ~ 3 will not be signaled, EventIndex 4 ~ 5 will be signaled.
  //
  for (EventIndex = 0; EventIndex < 4; EventIndex++) {

    if (0 == NotifiedTimesArray[EventIndex]) {
      AssertionTypeArrayForGuid372[EventIndex] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionTypeArrayForGuid372[EventIndex] = EFI_TEST_ASSERTION_FAILED;
    }

  
  }
RecordPlace:
  gtBS->RestoreTPL (OldTpl);


  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionTypeGuid371,
                 gProtocolHandlerBBTestFunction_2AssertionGuid371,
                 L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint8",
                 L"%a:%d:Status - %r, TPL - TPL_NOTIFY",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  for (EventIndex = 0; EventIndex < 4; EventIndex++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeArrayForGuid372[EventIndex],
                   gProtocolHandlerBBTestFunction_2AssertionGuid372,
                   L"BS.InstallMultipleProtocolInterfaces - InterfaceTestCheckpoint8",
                   L"%a:%d:EventIndex - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   EventIndex
                   );
  }
  
Done:
  //
  // restore environment
  //
  for (EventIndex = 0; EventIndex < 4; EventIndex++) {
    if (EventArray[EventIndex] != NULL) {
      gtBS->CloseEvent (EventArray[EventIndex]);
    }
  }

  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &mInterfaceFunctionTestProtocol1Guid,
          &InterfaceFunctionTestProt1Instance,
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
// Checkpoint Functions for UninstallMultipleProtocolInterfaces()
//

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint1 (
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
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);

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
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid373;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid374;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid375;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    if (Handle != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid376;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid377;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid378;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }
    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists on the handle
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid379;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid380;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid381;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
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
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1
                     );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid382;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid383;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid384;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 4: InterfaceFunctionTestProtocol2 still exists on the handle
    //
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     (VOID **) &IFTestProt2
                     );
    if ((EFI_SUCCESS == Status)
        && (IFTestProt2 == &InterfaceFunctionTestProt2Instance)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid385;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid386;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid387;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, Protocol2 - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   IFTestProt2,
                   TplArray[Index]
                   );
NextLoop:
    //
    // restore environment for next loop
    //
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.UninstallMultipleProtocolInterfaces - restore environment",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // do not perform following tests
      //
      break;
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


EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint2 (
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
  EFI_STATUS            Status1, Status2;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;

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
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid388;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid389;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid390;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle no longer exists
    //
    Status1 = gtBS->OpenProtocol (
                      Handle,
                      &mInterfaceFunctionTestProtocol1Guid,
                      (VOID **) NULL,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
    Status2 = gtBS->OpenProtocol (
                      Handle,
                      &mInterfaceFunctionTestProtocol2Guid,
                      (VOID **) NULL,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
    if ((EFI_INVALID_PARAMETER == Status1) && (EFI_INVALID_PARAMETER == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid391;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid392;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid393;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
                   L"%a:%d:Status1 - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }
    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid394;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid395;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid396;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
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
    //
    // Step 4: InterfaceFunctionTestProtocol2 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol2Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid397;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid398;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid399;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint2",
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
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_STATUS            Status2;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;

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
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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
    // open protocol BY_HANDLE_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              NULL
              );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid400;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid401;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid402;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // Step 2: check handle destroyed
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    Status2 = gtBS->OpenProtocol (
                      Handle,
                      &mInterfaceFunctionTestProtocol2Guid,
                      (VOID **) NULL,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
    if ((EFI_INVALID_PARAMETER == Status) && (EFI_INVALID_PARAMETER == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid403;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid404;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid405;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
                   L"%a:%d:Handle - 0x%x, Status - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   Status,
                   Status2,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }

    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid406;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid407;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid408;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
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

    //
    // Step 4: InterfaceFunctionTestProtocol2 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol2Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid499;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid500;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid501;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
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
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_STATUS            Status2;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;

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
                    NULL
                    );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol GET_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_GET_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              NULL
              );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid409;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid410;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid411;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle destroyed
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    Status2 = gtBS->OpenProtocol (
                      Handle,
                      &mInterfaceFunctionTestProtocol2Guid,
                      (VOID **) NULL,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
    if ((EFI_INVALID_PARAMETER == Status) && (EFI_INVALID_PARAMETER == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid412;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid413;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid414;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint4",
                   L"%a:%d:Handle - 0x%x, Status - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   Status,
                   Status2,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }

    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid415;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid416;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid417;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint4",
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

    //
    // Step 4: InterfaceFunctionTestProtocol2 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol2Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid502;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid503;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid504;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
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
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_STATUS            Status2;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;

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
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol TEST_PROTOCOL
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              NULL
              );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid418;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid419;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid420;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle destroyed
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    Status2 = gtBS->OpenProtocol (
                      Handle,
                      &mInterfaceFunctionTestProtocol2Guid,
                      (VOID **) NULL,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
    if ((EFI_INVALID_PARAMETER == Status) && (EFI_INVALID_PARAMETER == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid421;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid422;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid423;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint5",
                   L"%a:%d:Handle - 0x%x, Status - %r, Status2 - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   Status,
                   Status2,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }

    //
    // Step 3: InterfaceFunctionTestProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid424;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid425;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid426;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint5",
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

    //
    // Step 4: InterfaceFunctionTestProtocol2 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol2Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid505;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid506;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid507;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint3",
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
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint6 (
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
  EFI_HANDLE            ChildHandle;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
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
  ChildHandle = NULL;
  InitializeInterfaceFunctionTestProtocol1 (&InterfaceFunctionTestProt1Instance);
  InitializeInterfaceFunctionTestProtocol2 (&InterfaceFunctionTestProt2Instance);
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);

  Status = gtBS->InstallProtocolInterface (
                   &ChildHandle,
                   &mInterfaceFunctionTestProtocol3Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt3Instance
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
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol BY_CHILD_CONTROLLER
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              NULL
              );
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid427;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid428;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid429;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid430;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid431;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid432;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: InterfaceFunctionTestProtocol1 still exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid433;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid434;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid435;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
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

    //
    // Step 4: InterfaceFunctionTestProtocol2 still exists
    //
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid508;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid509;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid510;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
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

    //
    // Step 5: when CloseProtocol InterfaceFunctionTestProtocol1,
    //         uninstall should succeed
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            ChildHandle
            );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid436;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid437;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid438;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
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
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint7 (
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
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol EXCLUSIVE
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              NULL
              );
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid439;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid440;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid441;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid442;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid443;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid444;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint7",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: InterfaceFunctionTestProtocol1 still exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid445;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid446;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid447;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint7",
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

    //
    // Step 4: InterfaceFunctionTestProtocol2 still exists
    //
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid511;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid512;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid513;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
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

    //
    // Step 5: when CloseProtocol InterfaceFunctionTestProtocol1,
    //         uninstall should succeed
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            NULL
            );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid448;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid449;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid450;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
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
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint8 (
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
  EFI_HANDLE            Handle2;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
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
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);

  Handle2 = NULL;
  Status = gtBS->InstallProtocolInterface (
                   &Handle2,
                   &mInterfaceFunctionTestProtocol3Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt3Instance
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
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol BY_DRIVER
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     Handle2,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                    );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              NULL
              );
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid451;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid452;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid453;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid454;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid455;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid456;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint8",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: InterfaceFunctionTestProtocol1 still exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid457;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid458;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid459;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint8",
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

    //
    // Step 4: InterfaceFunctionTestProtocol2 still exists
    //
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid514;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid515;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid516;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
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

    //
    // Step 5: when CloseProtocol InterfaceFunctionTestProtocol1,
    //         uninstall should succeed
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            Handle2
            );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid460;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid461;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid462;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint8",
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
  gtBS->UninstallProtocolInterface (
          Handle2,
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
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint9 (
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
  EFI_HANDLE            Handle2;

  INTERFACE_FUNCTION_TEST_PROTOCOL_1      InterfaceFunctionTestProt1Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2      InterfaceFunctionTestProt2Instance;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3      InterfaceFunctionTestProt3Instance;
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
  InitializeInterfaceFunctionTestProtocol3 (&InterfaceFunctionTestProt3Instance);
  Handle2 = NULL;

  Status = gtBS->InstallProtocolInterface (
                   &Handle2,
                   &mInterfaceFunctionTestProtocol3Guid,
                   EFI_NATIVE_INTERFACE,
                   &InterfaceFunctionTestProt3Instance
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
                     NULL
                     );
    if (EFI_SUCCESS != Status) {
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

    //
    // open protocol BY_DRIVER | EXCLUSIVE
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     mImageHandle,
                     Handle2,
                     (EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE)
                     );
    if (EFI_SUCCESS != Status) {
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
      gtBS->UninstallMultipleProtocolInterfaces (
              Handle,
              &mInterfaceFunctionTestProtocol2Guid,
              &InterfaceFunctionTestProt2Instance,
              &mInterfaceFunctionTestProtocol1Guid,
              &InterfaceFunctionTestProt1Instance,
              NULL
              );
      goto Done;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid463;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid464;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid465;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle still exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid466;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid467;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid468;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint9",
                   L"%a:%d:Handle - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Handle,
                   TplArray[Index]
                   );

    //
    // Step 3: InterfaceFunctionTestProtocol1 still exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mInterfaceFunctionTestProtocol1Guid,
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid469;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid470;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid471;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint9",
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

    //
    // Step 4: InterfaceFunctionTestProtocol2 still exists
    //
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
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid517;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid518;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid519;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint6",
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

    //
    // Step 5: when CloseProtocol InterfaceFunctionTestProtocol1,
    //         uninstall should succeed
    //
    gtBS->CloseProtocol (
            Handle,
            &mInterfaceFunctionTestProtocol1Guid,
            mImageHandle,
            Handle2
            );

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &InterfaceFunctionTestProt2Instance,
                     &mInterfaceFunctionTestProtocol1Guid,
                     &InterfaceFunctionTestProt1Instance,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid472;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid473;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid474;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint9",
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
  gtBS->UninstallProtocolInterface (
          Handle2,
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
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;
  EFI_STATUS            Status2;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  VOID                  *Protocol;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // init
    //
    Handle = NULL;
    Protocol = NULL;

    Status = gtBS->InstallMultipleProtocolInterfaces (
                     &Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     &mTestNoInterfaceProtocol2Guid,
                     NULL,
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

    Status = gtBS->UninstallMultipleProtocolInterfaces (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     &mTestNoInterfaceProtocol2Guid,
                     NULL,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid475;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid476;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid477;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check handle no longer exists
    //
    Status = gtBS->OpenProtocol (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     (VOID **) NULL,
                     mImageHandle,
                     NULL,
                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                     );
    Status2 = gtBS->OpenProtocol (
                      Handle,
                      &mTestNoInterfaceProtocol2Guid,
                      (VOID **) NULL,
                      mImageHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
    if ((EFI_INVALID_PARAMETER == Status) && (EFI_INVALID_PARAMETER == Status2)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid478;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid479;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid480;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      break;
    }
    //
    // Step 3: TestNoInterfaceProtocol1 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid481;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid482;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid483;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint10",
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

    //
    // Step 4: TestNoInterfaceProtocol2 no longer exists
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mTestNoInterfaceProtocol2Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid520;
    } else if (Index == 1) {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid521;
    } else {
      TplGuid = gProtocolHandlerBBTestFunction_2AssertionGuid522;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UninstallMultipleProtocolInterfaces - InterfaceTestCheckpoint10",
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
