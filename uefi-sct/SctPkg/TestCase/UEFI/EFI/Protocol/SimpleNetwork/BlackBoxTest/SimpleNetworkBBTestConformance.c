/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2022, ARM Limited. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  SimpleNetworkBBTestConformance.c

Abstract:

  Conformance Test Cases of SimpleNetwork Protocol

--*/

#include "SctLib.h"
#include "SimpleNetworkBBTestMain.h"

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Start() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestStartConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStarted.
  // If not, change the state to EfiSimpleNetworkStarted.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.1.2.1
  // Call Start() function if network interface already started.
  //
  Status = SnpInterface->Start (SnpInterface);
  if ((Status == EFI_ALREADY_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStarted)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // restore SNP status
  //
  if (State1 == EfiSimpleNetworkInitialized) {
    Status1 = SnpInterface->Initialize(SnpInterface, 0, 0);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid001,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Start - Invoke Start() when network interface already started.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (State1 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;

}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Stop() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.2
//
EFI_STATUS
EFIAPI
BBTestStopConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.2.2.1
  // Call Stop() function if network interface not start.
  //
  Status = SnpInterface->Stop (SnpInterface);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Restore SNP status
  //
  if (State1 != EfiSimpleNetworkStopped) {
    Status1 = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

   if (State1 == EfiSimpleNetworkInitialized) {
    Status1 = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid002,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Stop - Invoke Stop() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Initialize() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.3
//
EFI_STATUS
EFIAPI
BBTestInitializeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.3.2.1
  // Call Initialize() function if network interface not start.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Restore SNP status
  //
  if (State1 != EfiSimpleNetworkStopped) {
    Status1 = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  if (State1 == EfiSimpleNetworkInitialized) {
    //
    // Re-initialize Snp Interface
    //
    Status1 = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }


  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid003,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Initialize - Invoke Initialize() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;

}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Reset() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.4
//
EFI_STATUS
EFIAPI
BBTestResetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.4.2.1
  // Call Reset() function when network interface not start.
  //
  Status = SnpInterface->Reset (SnpInterface, FALSE);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  //
  // Restore SNP status
  //
  if (State1 != EfiSimpleNetworkStopped) {
    Status1 = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  if (State1 == EfiSimpleNetworkInitialized) {
    Status1 = SnpInterface->Initialize(SnpInterface, 0, 0);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid004,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Reset - Invoke Reset() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Shutdown() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.5
//
EFI_STATUS
EFIAPI
BBTestShutdownConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.5.2.1
  // Call Shutdown() function if network interface not start.
  //
  Status = SnpInterface->Shutdown (SnpInterface);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Restore SNP status
  //
  if (State1 != EfiSimpleNetworkStopped) {
    Status1 = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  if (State1 == EfiSimpleNetworkInitialized) {
    Status1 = SnpInterface->Initialize(SnpInterface, 0, 0);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid005,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Shutdown - Invoke Shutdown() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilter() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.6
//
EFI_STATUS
EFIAPI
BBTestReceiveFilterConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_MAC_ADDRESS                       MAC;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  if (SnpInterface->Mode->State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  if (SnpInterface->Mode->State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.6.2.1
  // Call ReceiveFilters() function if network interface not start.
  //
  Status = SnpInterface->ReceiveFilters (SnpInterface, 0, 0, FALSE, 0, NULL);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gSimpleNetworkBBTestConformanceAssertionGuid006,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() when network interface not start.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );


  //
  // Assertion Point 5.6.2.2
  // Call ReceiveFilters() function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->ReceiveFilters (SnpInterface, 0, 0, FALSE, 0, NULL);
  if (Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gSimpleNetworkBBTestConformanceAssertionGuid007,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() when network interface not initialized.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Assertion Point 5.6.2.3
  // Call ReceiveFilters() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //  Call ReceiveFilters with invalide Enable
  //
  Status = SnpInterface->ReceiveFilters (SnpInterface, ~(SnpInterface->Mode->ReceiveFilterMask), 0, FALSE, 0, NULL);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gSimpleNetworkBBTestConformanceAssertionGuid008,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() with invalid Enable.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  //  Call ReceiveFilters with invalide MCastFilterCnt
  //
  if ((SnpInterface->Mode->ReceiveFilterMask & EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST) != 0) {
    SctSetMem (&MAC, sizeof (MAC), 0x00);
    MAC.Addr[0] = 0x01;
    MAC.Addr[1] = 0x00;
    MAC.Addr[2] = 0x5e;
    MAC.Addr[3] = 0x00;
    MAC.Addr[4] = 0x00;
    MAC.Addr[5] = 0x02;

    Status = SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST, 0, FALSE, SnpInterface->Mode->MaxMCastFilterCount + 1, &MAC);
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
    StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gSimpleNetworkBBTestConformanceAssertionGuid009,
                    L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() with invalid MCastFilterCnt is greater than Snp->Mode->MaxMCastFilterCount.",
                    L"%a:%d:Status - %r",
                    __FILE__,
                    (UINTN)__LINE__,
                    Status
                    );

    Status = SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST, 0, FALSE, 0, &MAC);
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
    StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gSimpleNetworkBBTestConformanceAssertionGuid043,
                    L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() with invalid MCastFilterCnt is 0.",
                    L"%a:%d:Status - %r",
                    __FILE__,
                    (UINTN)__LINE__,
                    Status
                    );

    Status = SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST, 0, FALSE, 1, NULL);
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
    StandardLib->RecordAssertion (
                      StandardLib,
                      AssertionType,
                      gSimpleNetworkBBTestConformanceAssertionGuid010,
                      L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() with MCastFilterCnt not match MCastFilter.",
                      L"%a:%d:Status - %r",
                      __FILE__,
                      (UINTN)__LINE__,
                      Status
                      );
  }

  //
  // Restore SNP State
  //
  if (SnpInterface->Mode->State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.7
//
EFI_STATUS
EFIAPI
BBTestStationAddressConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            StatusBuf[2];
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.7.2.1
  // Call StationAddress() function if network interface not start.
  //
  StatusBuf[0] = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);
  //
  // save current snp state
  //
  State2 = SnpInterface->Mode->State;

  //
  // Assertion Point 5.7.2.2
  // Call StationAddress() function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  StatusBuf[1] = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);

  //
  // Restore SNP Status
  //
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Initialize(SnpInterface, 0, 0);
    if (EFI_ERROR(Status)){
      return Status;
    }
  }

  if ((StatusBuf[0] == EFI_NOT_STARTED) && (State2 == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if ((StatusBuf[0] == EFI_INVALID_PARAMETER) || (StatusBuf[0] == EFI_UNSUPPORTED)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gSimpleNetworkBBTestConformanceAssertionGuid011,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress - Invoke StationAddress() when network interface not start.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  StatusBuf[0]
                  );


  if (StatusBuf[1] == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if ((StatusBuf[1] == EFI_INVALID_PARAMETER) || (StatusBuf[1] == EFI_UNSUPPORTED)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gSimpleNetworkBBTestConformanceAssertionGuid012,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress - Invoke StationAddress() when network interface not initialized.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  StatusBuf[1]
                  );

  if (State1 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)){
      return Status;
    }
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Statistics() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.8
//
EFI_STATUS
EFIAPI
BBTestStatisticsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;
  EFI_NETWORK_STATISTICS                StatisticsTable;
  UINTN                                 StatisticsSize;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);
  //
  // Assertion Point 5.8.2.1
  // Call Statistics() function while network interface is not started.
  //
  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gSimpleNetworkBBTestConformanceAssertionGuid014,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.Statistics - Invoke Statistics() while network interface not started.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Assertion Point 5.8.2.2
  // Call Statistics() function while network interface is not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);
  if (Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gSimpleNetworkBBTestConformanceAssertionGuid015,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.Statistics - Invoke Statistics() while network interface is not initialized.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Assertion Point 5.8.2.3
  // Call Statistics() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 5.8.2.4
  // Call Statistics() function with small buffer.
  //
  StatisticsSize = 0;

  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gSimpleNetworkBBTestConformanceAssertionGuid017,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.Statistics - Invoke Statistics() with small buffer.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

  //
  // Restore SNP State
  //
  if (State1 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.MCastIpToMac() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.9
//
EFI_STATUS
EFIAPI
BBTestMCastIpToMacConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;
  EFI_IP_ADDRESS                        IP;
  EFI_MAC_ADDRESS                       MAC;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.9.2.1
  // Call MCastIpToMac() function if network interface not start.
  //
  IP.v4.Addr[0] = 239;
  IP.v4.Addr[1] = 255;
  IP.v4.Addr[2] = 255;
  IP.v4.Addr[3] = 255;
  SctSetMem (&MAC, sizeof (EFI_MAC_ADDRESS), 0x0);

  Status = SnpInterface->MCastIpToMac(SnpInterface, FALSE, &IP, &MAC);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Restore SNP status
  //
  if (State1 != EfiSimpleNetworkStopped) {
    Status1 = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  if (State1 == EfiSimpleNetworkInitialized) {
    Status1 = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status1)) {
      return Status1;
    }
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid018,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.MCastIpToMac - Invoke MCastIpToMac() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.NVData() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.10
//
EFI_STATUS
EFIAPI
BBTestNVDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            StatusBuf[4];
  EFI_TEST_ASSERTION                    AssertionType[4];
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2, State3;
  VOID                                  *Buffer;
  UINT32                                CheckPoint1State;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the network interface support NvData if not return
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  if ((SnpInterface->Mode->NvRamAccessSize == 0) || (SnpInterface->Mode->NvRamSize == 0)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - NvRAM device is not attached\n"
                   );
    return EFI_SUCCESS;
  }

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State3 = SnpInterface->Mode->State;
  if (State3 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State3 = SnpInterface->Mode->State;
  if (State3 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Buffer = NULL;
  Status = gtBS->AllocatePool (EfiLoaderData, SnpInterface->Mode->NvRamSize, (VOID **) &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 5.10.2.1
  // Call NvData() function if network interface not start.
  //

  StatusBuf[0] = SnpInterface->NvData (SnpInterface, TRUE, 0, SnpInterface->Mode->NvRamAccessSize, Buffer);
  CheckPoint1State = SnpInterface->Mode->State;


  //
  // Assertion Point 5.10.2.2
  // Call NvData() function with invalid parameters.
  //

  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Check Point A: "Offset" not be a multiple of NvRamAccessSize
  //
  StatusBuf[1] = SnpInterface->NvData (SnpInterface, TRUE, (SnpInterface->Mode->NvRamAccessSize/2), SnpInterface->Mode->NvRamAccessSize, Buffer);


  //
  // Check Point B: "BufferSize" not be a multiple of NvRamAccessSize
  //
  StatusBuf[2] = SnpInterface->NvData (SnpInterface, TRUE, 0, (SnpInterface->Mode->NvRamAccessSize/2), Buffer);


  //
  // Check Point C: "BufferSize" + "Offset" exceeds "NvRamSize"
  //
  StatusBuf[3] = SnpInterface->NvData (SnpInterface, TRUE, 0, SnpInterface->Mode->NvRamSize+100, Buffer);



  if ((StatusBuf[0] == EFI_NOT_STARTED) && (CheckPoint1State == EfiSimpleNetworkStopped)) {
    AssertionType[0] = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == StatusBuf[0]) {
      AssertionType[0] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType[0] = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType[0],
                  gSimpleNetworkBBTestConformanceAssertionGuid020,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() when network interface not start.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  StatusBuf[0]
                  );


  if (StatusBuf[1] == EFI_INVALID_PARAMETER) {
    AssertionType[1] = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == StatusBuf[1]) {
      AssertionType[1] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType[1] = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType[1],
                  gSimpleNetworkBBTestConformanceAssertionGuid021,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() with Offset not be a multiple of NvRamAccessSize.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  StatusBuf[1]
                  );


  if (StatusBuf[2] == EFI_INVALID_PARAMETER) {
    AssertionType[2] = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == StatusBuf[2]) {
      AssertionType[2] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType[2] = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType[2],
                  gSimpleNetworkBBTestConformanceAssertionGuid022,
                  L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() with BufferSize not be a multiple of NvRamAccessSize.",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  StatusBuf[2]
                  );

  if (StatusBuf[3] == EFI_INVALID_PARAMETER) {
    AssertionType[3] = EFI_TEST_ASSERTION_PASSED;
  } else {
    if (EFI_UNSUPPORTED == StatusBuf[3]) {
      AssertionType[3] = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType[3] = EFI_TEST_ASSERTION_FAILED;
    }
  }
  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType[3],
                gSimpleNetworkBBTestConformanceAssertionGuid023,
                L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() with BufferSize + Offset exceeds NvRamSize.",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                StatusBuf[3]
                );

  //
  // Restore SNP Status
  //
  if (State1 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Status = gtBS->FreePool (Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.11
//
EFI_STATUS
EFIAPI
BBTestGetStatusConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            StatusBuf[3];
  EFI_TEST_ASSERTION                    AssertionType[3];
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;
  VOID                                  *TxBuf;
  UINT32                                InterruptStatus;
  //UINT32                                *pInterruptStatus;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  TxBuf = NULL;
  InterruptStatus = 0;

  //
  // Assertion Point 5.11.2.1
  // Call GetStatus() function if network interface not start.
  //
  StatusBuf[0] = SnpInterface->GetStatus (SnpInterface, &InterruptStatus, &TxBuf);
  if ((StatusBuf[0] == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType[0] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[0] = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Assertion Point 5.11.2.2
  // Call GetStatus () function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_NETWORK_PROTOCOL.Start - Can not start",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  StatusBuf[1] = SnpInterface->GetStatus (SnpInterface, &InterruptStatus, &TxBuf);
  if (StatusBuf[1] == EFI_DEVICE_ERROR) {
    AssertionType[1] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[1] = EFI_TEST_ASSERTION_FAILED;
  }

/*
  //
  // Assertion Point 5.11.2.3
  // Call GetStatus() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_NETWORK_PROTOCOL.Initialize - Can not Initialize",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  pInterruptStatus = NULL;
  StatusBuf[2] = SnpInterface->GetStatus (SnpInterface, pInterruptStatus, NULL);
  if (StatusBuf[2] == EFI_INVALID_PARAMETER) {
    AssertionType[2] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[2] = EFI_TEST_ASSERTION_FAILED;
  }
*/

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[0],
                 gSimpleNetworkBBTestConformanceAssertionGuid024,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus - Invoke GetStatus() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[0]
                 );

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[1],
                 gSimpleNetworkBBTestConformanceAssertionGuid025,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus - Invoke GetStatus() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[1]
                 );
/*
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[2],
                 gSimpleNetworkBBTestConformanceAssertionGuid026,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus - Invoke GetStatus() with invalid parameter.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[2]
                 );
*/
  //
  // Restore SNP State
  //
  if (State1 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Transmit() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.12
//
EFI_STATUS
EFIAPI
BBTestTransmitConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            StatusBuf[7];
  EFI_TEST_ASSERTION                    AssertionType[7];
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;
  VOID                                  *Buffer;
  UINTN                                 HeaderSize;
  UINTN                                 BufferSize;
  EFI_MAC_ADDRESS                       SrcAddr;
  EFI_MAC_ADDRESS                       DestAddr;
  UINT16                                Protocol;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Buffer = NULL;
  HeaderSize = 0;
  BufferSize = SnpInterface->Mode->MediaHeaderSize;
  SctSetMem (&SrcAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  SctSetMem (&DestAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  Protocol = SnpInterface->Mode->IfType;
  Status = gtBS->AllocatePool (EfiLoaderData, 2048, (VOID **) &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  // Reset the MAC Address
  SnpInterface->StationAddress (SnpInterface, TRUE, NULL);

  //
  // Assertion Point 5.12.2.1
  // Call Transmit() function if network interface not start.
  //
  StatusBuf[0] = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, NULL, NULL, 0);
  if ((StatusBuf[0] == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType[0] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[0] = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Assertion Point 5.12.2.2
  // Call Transmit () function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  StatusBuf[1] = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, NULL, NULL, 0);
  if (StatusBuf[1] == EFI_DEVICE_ERROR) {
    AssertionType[1] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[1] = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Assertion Point 5.12.2.3
  // Call Transmit() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Check Point A: HeaderSize is nonzero and not equal to MediaHeaderSize.
  //
  HeaderSize = SnpInterface->Mode->MediaHeaderSize + 2;
  BufferSize = 1024;
  StatusBuf[2] = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SrcAddr, &DestAddr, &Protocol);
  if (StatusBuf[2] == EFI_INVALID_PARAMETER) {
    AssertionType[2] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[2] = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Check Point B: BufferSize is less than  MediaHeaderSize.
  //
  HeaderSize = SnpInterface->Mode->MediaHeaderSize;
  BufferSize = SnpInterface->Mode->MediaHeaderSize - 2;
  StatusBuf[3] = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SrcAddr, &DestAddr, &Protocol);
  if (StatusBuf[3] == EFI_BUFFER_TOO_SMALL) {
    AssertionType[3] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[3] = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Check Point C: Buffer is NULL.
  //
  BufferSize = 1024;
  StatusBuf[4] = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, NULL, &SrcAddr, &DestAddr, &Protocol);
  if (StatusBuf[4] == EFI_INVALID_PARAMETER) {
    AssertionType[4] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[4] = EFI_TEST_ASSERTION_FAILED;
  }


  //
  // Check Point D: HeaderSize is nonzero and DestAddr is NULL.
  //
  StatusBuf[5] = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SrcAddr, NULL, &Protocol);
  if (StatusBuf[5] == EFI_INVALID_PARAMETER) {
    AssertionType[5] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[5] = EFI_TEST_ASSERTION_FAILED;
  }


  //
  // Check Point E: HeaderSize is nonzero and Protocol is NULL.
  //
  StatusBuf[6] = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SrcAddr, &DestAddr, NULL);
  if (StatusBuf[6] == EFI_INVALID_PARAMETER) {
    AssertionType[6] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[6] = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[0],
                 gSimpleNetworkBBTestConformanceAssertionGuid027,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[0]
                 );

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[1],
                 gSimpleNetworkBBTestConformanceAssertionGuid028,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[1]
                 );

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[2],
                 gSimpleNetworkBBTestConformanceAssertionGuid029,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with HeaderSize is nonzero and not equal to MediaHeaderSize.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[2]
                 );

   StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[3],
                 gSimpleNetworkBBTestConformanceAssertionGuid030,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with BufferSize is less than  MediaHeaderSize.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[3]
                 );
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[4],
                 gSimpleNetworkBBTestConformanceAssertionGuid031,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with Buffer is NULL.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[4]
                 );

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[5],
                 gSimpleNetworkBBTestConformanceAssertionGuid032,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with HeaderSize is nonzero and DestAddr is NULL.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[5]
                 );

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[6],
                 gSimpleNetworkBBTestConformanceAssertionGuid033,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with HeaderSize is nonzero and Protocol is NULL.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[6]
                 );
  //
  // Restore SNP State
  //
  if (State1 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Status = gtBS->FreePool (Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Receive() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.13
//
EFI_STATUS
EFIAPI
BBTestReceiveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            StatusBuf[3];
  EFI_TEST_ASSERTION                    AssertionType[3];
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State1, State2;
  VOID                                  *Buffer;
  VOID                                  *Buffer1;
  UINTN                                 HeaderSize;
  UINTN                                 BufferSize;
  EFI_MAC_ADDRESS                       SrcAddr;
  EFI_MAC_ADDRESS                       DestAddr;
  UINT16                                Protocol;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State1 = SnpInterface->Mode->State;
  if (State1 == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  State2 = SnpInterface->Mode->State;
  if (State2 == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Buffer = NULL;
  Buffer1 = NULL;
  HeaderSize = 0;
  BufferSize = 0;
  SctSetMem (&SrcAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  SctSetMem (&DestAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  Protocol = 0;
  Status = gtBS->AllocatePool (EfiLoaderData, 2048, (VOID **) &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = gtBS->AllocatePool (EfiLoaderData, 48, (VOID **) &Buffer1);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 5.13.2.1
  // Call Receive() function if network interface not start.
  //
  StatusBuf[0] = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, Buffer, NULL, NULL, 0);
  if ((StatusBuf[0] == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType[0] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[0] = EFI_TEST_ASSERTION_FAILED;
  }


  //
  // Assertion Point 5.13.2.2
  // Call Receive() function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  StatusBuf[1] = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, Buffer, NULL, NULL, 0);
  if (StatusBuf[1] == EFI_DEVICE_ERROR) {
    AssertionType[1] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[1] = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Assertion Point 5.13.2.3
  // Call Receive() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Enable receive filters
  //
  SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_UNICAST|EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST, 0, FALSE, 0, NULL);

  //
  // Check Point A: Buffer is NULL.
  //
  StatusBuf[2] = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, NULL, &SrcAddr, &DestAddr, &Protocol);
  if (StatusBuf[2] == EFI_INVALID_PARAMETER) {
    AssertionType[2] = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType[2] = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[0],
                 gSimpleNetworkBBTestConformanceAssertionGuid038,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[0]
                 );

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[1],
                 gSimpleNetworkBBTestConformanceAssertionGuid039,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[1]
                 );

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType[2],
                 gSimpleNetworkBBTestConformanceAssertionGuid040,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() with Buffer is NULL.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusBuf[2]
                 );

  //
  // Restore SNP State
  //
  if (State1 == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

#if 0
  //
  // Assertion Point 5.13.2.4
  // No Packet Received in the Network Interface when Receive().
  //
  // We should disable the muticast and broadcast receive filters first. because
  // some muticast or broadcast packets maybe on the LAN
  //
  Status = SnpInterface->ReceiveFilters (
                           SnpInterface,
                           0,
                           EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST | EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST,
                           TRUE,
                           0,
                           NULL);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Can not disable multicast and broadcase receive filters",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = EFI_SUCCESS;
  BufferSize = 65;
  while (!EFI_ERROR(Status)) {
    Status = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, Buffer, &SrcAddr, &DestAddr, &Protocol);
  }
  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid042,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - No Packet Received in the Network Interface when Receive().",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
#endif
  Status = gtBS->FreePool (Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = gtBS->FreePool (Buffer1);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}
