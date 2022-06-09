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

  ProtocolHandlerBBTestStress.c

Abstract:

  for Protocol Handler Boot Services' Stress Test

--*/

#include "SctLib.h"
#include "Misc.h"

EFI_GUID    StressTestNonInterfaceProtocolGuid[40];
//
// protocols for combination test 2 checkpoint 1 use
//
EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_0_GUID =
  { 0x5342f6be, 0xae45, 0x48b1, {0x8f, 0xb6, 0xd8, 0x64, 0xfd, 0x1b, 0xfe, 0xc }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_1_GUID =
  { 0xa31641ea, 0xbccd, 0x409a, {0x8e, 0x87, 0x19, 0xdf, 0x17, 0xbc, 0x11, 0x44 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_2_GUID =
  { 0x7a5464d, 0x617a, 0x4f9d, {0x86, 0x60, 0xee, 0x1f, 0x44, 0x25, 0xdd, 0xec }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_3_GUID =
  { 0x82c967bd, 0xe1b9, 0x4d08, {0x82, 0xde, 0x6b, 0x85, 0x85, 0x36, 0xa3, 0x61 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_4_GUID =
  { 0xcd825d0c, 0x440d, 0x4c3e, {0x80, 0x95, 0xa, 0xf0, 0x8c, 0x19, 0x78, 0x91 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_5_GUID =
  { 0x392606c4, 0xb34d, 0x45b9, {0x8d, 0x6a, 0x31, 0x45, 0xee, 0xfc, 0xb0, 0x8b }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_6_GUID =
  { 0x4e59c8cd, 0xdc26, 0x4bc8, {0x8a, 0x9a, 0x0, 0xf4, 0xe3, 0x48, 0xe0, 0x1 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_7_GUID =
  { 0xd39cdac9, 0xcfda, 0x41dd, {0xab, 0x47, 0xce, 0x96, 0x10, 0x8, 0x68, 0x99 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_8_GUID =
  { 0x5ac86e87, 0x6aeb, 0x489b, {0xbf, 0xfe, 0xc6, 0x73, 0xaf, 0x29, 0xb9, 0x2b }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_9_GUID =
  { 0xdf2774ab, 0xb7d0, 0x4927, {0xb0, 0x3c, 0x25, 0xc7, 0xb1, 0x51, 0x85, 0x53 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_10_GUID =
  { 0x7951ec52, 0xa168, 0x4341, {0xb9, 0x39, 0xea, 0x45, 0x9, 0x71, 0xd0, 0x19 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_11_GUID =
  { 0xe817f238, 0xf2ce, 0x450e, {0xb7, 0x65, 0xd1, 0x57, 0x8e, 0xc0, 0xc4, 0x56 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_12_GUID =
  { 0x973df5aa, 0x4a95, 0x4c47, {0xb8, 0xe9, 0x6, 0xa3, 0x31, 0x3e, 0x53, 0x2e }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_13_GUID =
  { 0x77213e78, 0x7c6b, 0x4362, {0xa6, 0xe, 0x17, 0x9a, 0x9f, 0xfc, 0x2d, 0xca }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_14_GUID =
  { 0x86786e89, 0x2b0a, 0x48ba, {0xb2, 0x3d, 0x8c, 0xa3, 0x53, 0xf1, 0x1, 0x1c }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_15_GUID =
  { 0xa418a1de, 0xfdf1, 0x4ace, {0x82, 0x22, 0xed, 0xf, 0x38, 0xbb, 0xf8, 0xa6 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_16_GUID =
  { 0x4ae35aae, 0x297a, 0x4057, {0xa3, 0x98, 0x29, 0x3c, 0xf4, 0xb2, 0x84, 0x10 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_17_GUID =
  { 0xacb47059, 0x8754, 0x4fbf, {0xb4, 0x42, 0x96, 0x6a, 0x45, 0xfc, 0xa9, 0x6e }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_18_GUID =
  { 0x85cdbcfc, 0xa82d, 0x4b4b, {0x8c, 0xf4, 0x36, 0x93, 0xc8, 0xa8, 0x1b, 0xa }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_19_GUID =
  { 0xd59cf679, 0x7b52, 0x4608, {0xaf, 0x1a, 0x5a, 0x39, 0xec, 0xfe, 0x2a, 0xee }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_20_GUID =
  { 0x64254ad4, 0xf6c5, 0x4b94, {0x8d, 0xab, 0x7e, 0x8a, 0xbd, 0xf6, 0xc1, 0x9c }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_21_GUID =
  { 0xc8b177fb, 0x4123, 0x4f25, {0xb8, 0xbc, 0x95, 0x57, 0x11, 0xa3, 0x58, 0xfa }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_22_GUID =
  { 0xcc5ec88f, 0x71aa, 0x49e4, {0xb0, 0xa5, 0x45, 0x12, 0x7d, 0xe1, 0x7e, 0x5e }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_23_GUID =
  { 0xb03dad41, 0x646f, 0x470f, {0x81, 0x58, 0x5c, 0x26, 0xe5, 0xf1, 0xaa, 0xab }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_24_GUID =
  { 0x5439583d, 0x5ba9, 0x496a, {0xb8, 0x15, 0xf6, 0x64, 0xf0, 0x0, 0xf7, 0x40 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_25_GUID =
  { 0xb4517d6b, 0xd058, 0x447b, {0x95, 0x86, 0xbe, 0xd4, 0x6d, 0x69, 0x43, 0xba }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_26_GUID =
  { 0xd9ef292c, 0x240, 0x47ca, {0xba, 0x2, 0xe5, 0xfb, 0x49, 0x9f, 0xe1, 0xc0 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_27_GUID =
  { 0x38dc6d9e, 0x1603, 0x4f37, {0xa4, 0x76, 0xf3, 0x19, 0xf1, 0xe3, 0xe8, 0x74 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_28_GUID =
  { 0x623d19a2, 0x5780, 0x4171, {0x91, 0x71, 0xd1, 0xea, 0x6c, 0x98, 0x49, 0xbf }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_29_GUID =
  { 0x68587c83, 0xd743, 0x4046, {0x9a, 0x5f, 0xe3, 0xa9, 0xe, 0xdb, 0x1f, 0xcd }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_30_GUID =
  { 0x27fa5329, 0x763, 0x4fa8, {0x9c, 0x28, 0x40, 0x75, 0xc2, 0x8d, 0xac, 0x48 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_31_GUID =
  { 0x938f1aaa, 0x8911, 0x441f, {0xa4, 0x4c, 0x31, 0x8e, 0xf5, 0x7f, 0x8b, 0xd5 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_32_GUID =
  { 0x60f95a9d, 0x3181, 0x49a2, {0xba, 0xe9, 0x29, 0xca, 0xf0, 0x79, 0xf6, 0xd4 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_33_GUID =
  { 0x985b0984, 0x5779, 0x445c, {0xbf, 0x3f, 0xfe, 0x49, 0x44, 0xe8, 0x6c, 0x25 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_34_GUID =
  { 0x2dbe2664, 0x6582, 0x4738, {0xb0, 0x3d, 0x47, 0xef, 0x2a, 0x33, 0xfe, 0x7f }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_35_GUID =
  { 0x8817006a, 0x1ba9, 0x4885, {0x80, 0x83, 0xde, 0xef, 0xe6, 0x88, 0x50, 0x2b }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_36_GUID =
  { 0xe6934d9f, 0xacec, 0x4b75, {0x9e, 0x73, 0x77, 0x16, 0xb7, 0x69, 0x3f, 0x4e }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_37_GUID =
  { 0xb229ea0a, 0x2130, 0x419e, {0x97, 0x2d, 0xc5, 0xde, 0xd3, 0xce, 0x32, 0x6f }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_38_GUID =
  { 0xa67023bd, 0x5127, 0x4fbc, {0x82, 0x8b, 0x78, 0xc, 0x76, 0xe2, 0xd7, 0x32 }};

EFI_GUID STRESS_TEST_NON_INTERFACE_PROTOCOL_39_GUID =
  { 0x169370a, 0xbc3d, 0x4326, {0x8a, 0x7, 0xa, 0x6c, 0x25, 0x73, 0x20, 0xd9 }};

/**
 *  @brief
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestCombinationTest1 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINTN                                   HandleCount;
  EFI_HANDLE                              *HandleBuffer;
  UINTN                                   HandleIndex;
  EFI_GUID                                **ProtocolGuidArray;
  UINTN                                   ArrayCount;
  UINTN                                   ProtocolIndex;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *OpenInfo;
  UINTN                                   OpenInfoCount;
  UINTN                                   OpenInfoIndex;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_ASSERTION                      AssertionType;
  VOID                                    *Instance;

  UINTN                                   Numbers;

  //
  // Init
  //
  StandardLib = NULL;
  HandleBuffer = NULL;

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
  // Retrieve the list of all handles from the handle database
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &HandleCount,
                   &HandleBuffer
                   );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid001,
                 L"BS.CombinationTest1 - Checkpoint1",
                 L"%a:%d:LocateHandleBuffer Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (!EFI_ERROR (Status)) {

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {

      ProtocolGuidArray = NULL;
      //
      // Retrieve the list of all the protocols on each handle
      //
      Status = gtBS->ProtocolsPerHandle (
                       HandleBuffer[HandleIndex],
                       &ProtocolGuidArray,
                       &ArrayCount
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gProtocolHandlerServicesCombinationTestAssertionGuid002,
                     L"BS.CombinationTest1 - Checkpoint1",
                     L"%a:%d:ProtocolsPerHandle Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      if (!EFI_ERROR (Status)) {

        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {

          //
          // Retrieve the protocol instance for each protocol
          //
          Status = gtBS->OpenProtocol (
                           HandleBuffer[HandleIndex],
                           ProtocolGuidArray[ProtocolIndex],
                           (VOID **) &Instance,
                           mImageHandle,
                           NULL,
                           EFI_OPEN_PROTOCOL_GET_PROTOCOL
                           );
          //
          // Retrieve the list of agents that have opened each protocol
          //
          OpenInfo = NULL;
          Status = gtBS->OpenProtocolInformation (
                           HandleBuffer[HandleIndex],
                           ProtocolGuidArray[ProtocolIndex],
                           &OpenInfo,
                           &OpenInfoCount
                           );
          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gProtocolHandlerServicesCombinationTestAssertionGuid003,
                         L"BS.CombinationTest1 - Checkpoint1",
                         L"%a:%d:OpenProtocolInformation Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (!EFI_ERROR (Status)) {
            for (OpenInfoIndex = 0;OpenInfoIndex < OpenInfoCount;OpenInfoIndex++) {
              //
              // HandleBuffer[HandleIndex] is the handle
              // ProtocolGuidArray[ProtocolIndex] is the protocol GUID
              // Instance is the protocol instance for the protocol
              // OpenInfo[OpenInfoIndex] is an agent that has opened a protocol
              //
            }

            if (OpenInfo != NULL) {
              gtBS->FreePool (OpenInfo);
            }
          }
        }
      }

      if (ProtocolGuidArray != NULL) {
        gtBS->FreePool (ProtocolGuidArray);
      }
    }
  }

  if (HandleBuffer != NULL) {
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

/**
 *  @brief
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2
//
EFI_STATUS
EFIAPI
BBTestCombinationTest2 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

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
  // Checkpoint 1:
  // 5.2.2.1  Stress test for
  // InstallProtocolInterface / UninstallProtocolInterface.
  //
  BBTestCombinationTest2CheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 5.2.2.2  Stress test for RegisterProtocolNotify.
  //
  BBTestCombinationTest2CheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 5.2.2.3  Stress test for HandleProtocol
  //
  BBTestCombinationTest2CheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 5.2.2.4  Stress test for OpenProtocol
  //
  BBTestCombinationTest2CheckPoint4 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.3
//
EFI_STATUS
EFIAPI
BBTestCombinationTest3 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_STATUS                              Status;
  UINTN                                   Index;
  EFI_HANDLE                              BusDriverImageHandle;
  EFI_HANDLE                              DeviceDriverImageHandle1;
  EFI_HANDLE                              DeviceDriverImageHandle2;
  EFI_HANDLE                              DeviceDriverImageHandle3;
  EFI_HANDLE                              DeviceDriverImageHandle4;
  EFI_HANDLE                              DeviceDriverImageHandle5;
  EFI_STATUS                              Status1, Status2, Status3;
  EFI_HANDLE                              Handle;
  EFI_GUID                                ProtGuid[7];
  VOID                                    *ProtInst[7];
  EFI_EVENT                               Event;
  UINTN                                   NotifyTimes;
  VOID                                    *Registration;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_HANDLE                              *HandleBuffer;
  UINTN                                   NoHandles;
  EFI_HANDLE                              DriverImageHandle[2];

  UINTN                                   Numbers;

  StandardLib = NULL;
  HandleBuffer = NULL;
  Handle = NULL;
  Event = NULL;
  NotifyTimes = 0;
  BusDriverImageHandle = NULL;
  DeviceDriverImageHandle1 = NULL;
  DeviceDriverImageHandle2 = NULL;
  DeviceDriverImageHandle3 = NULL;
  DeviceDriverImageHandle4 = NULL;
  DeviceDriverImageHandle5 = NULL;

  ProtGuid[0] = mInterfaceFunctionTestProtocol1Guid;
  ProtGuid[1] = mInterfaceFunctionTestProtocol2Guid;
  ProtGuid[2] = mInterfaceFunctionTestProtocol3Guid;

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

  Status = LoadStartImage (
             StandardLib,
             mImageHandle,
             BUS_DRIVER_4_NAME,
             &BusDriverImageHandle
             );
  Status1 = LoadStartImage (
              StandardLib,
              mImageHandle,
              DEVICE_DRIVER_11_NAME,
              &DeviceDriverImageHandle1
              );
  Status2 = LoadStartImage (
              StandardLib,
              mImageHandle,
              DEVICE_DRIVER_12_NAME,
              &DeviceDriverImageHandle2
              );
  Status3 = LoadStartImage (
              StandardLib,
              mImageHandle,
              DEVICE_DRIVER_13_NAME,
              &DeviceDriverImageHandle3
              );
  if (EFI_ERROR (Status) || EFI_ERROR (Status1)
      || EFI_ERROR (Status2) || EFI_ERROR (Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Helper Function LoadStartImage - build environment",
                   L"%a:%d:Status - %r, Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Status1,
                   Status2,
                   Status3
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR (Status)) {
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
  // Scenario 1
  //

  //
  // connect bus driver and the 3 device drivers
  //
  Status = gtBS->ConnectController (Handle, NULL, NULL, TRUE);
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid004,
                 L"BS.CombinationTest3 - Integrated Test",
                 L"%a:%d:ConnectController 1 Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // Bus driver produces protocol1 ~ 3,
  // Device drivers produce protocol4 ~ 6
  //
  ProtGuid[3] = mInterfaceFunctionTestProtocol4Guid;
  ProtGuid[4] = mInterfaceFunctionTestProtocol5Guid;
  ProtGuid[5] = mInterfaceFunctionTestProtocol6Guid;
  for (Index = 0; Index < 6; Index++) {
    Status = gtBS->LocateProtocol (
                     &ProtGuid[Index],
                     NULL,
                     (VOID **) &ProtInst[Index]
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerServicesCombinationTestAssertionGuid005,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateProtocol 1 Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }

  //
  // Scenario 2
  //

  //
  // event for protocol4 installation & reinstallation
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) TestNotifyFunction1,
                   &NotifyTimes,
                   &Event
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:CreateEvent Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
    goto Scenario_2_clean;
  }

  Status = gtBS->RegisterProtocolNotify (
                   &mInterfaceFunctionTestProtocol4Guid,
                   Event,
                   &Registration
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:RegisterProtocolNotify Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
    goto Scenario_2_clean;
  }

  //
  // reinstall protocol1
  //

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mInterfaceFunctionTestProtocol1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (1 != NoHandles)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateHandleBuffer 1 Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
    goto Scenario_2_clean;
  }

  Status = gtBS->HandleProtocol (
                   *HandleBuffer,
                   &mInterfaceFunctionTestProtocol1Guid,
                   (VOID **) &ProtInst[0]
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:HandleProtocol 1 Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
    goto Scenario_2_clean;
  }

  Status = gtBS->ReinstallProtocolInterface (
                   *HandleBuffer,
                   &mInterfaceFunctionTestProtocol1Guid,
                   ProtInst[0],
                   ProtInst[0]
                   );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid006,
                 L"BS.CombinationTest3 - Integrated Test",
                 L"%a:%d:ReinstallProtocol 1 Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // protocol4 will be installed again by device driver 1,
  // so event registered for protocol4 will be signaled
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  if (1 == NotifyTimes) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid007,
                 L"BS.CombinationTest3 - Integrated Test",
                 L"%a:%d:Scenario 2 check, protocol4 be installed %d times",
                 __FILE__,
                 (UINTN)__LINE__,
                 NotifyTimes
                 );

  //
  // protocol1 ~ 6 could still be accessed
  //
  for (Index = 0; Index < 6; Index++) {
    Status = gtBS->LocateProtocol (
                     &ProtGuid[Index],
                     NULL,
                     (VOID **) &ProtInst[Index]
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerServicesCombinationTestAssertionGuid008,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateProtocol 2 Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }

Scenario_2_clean:
  //
  // restore environment for scenario 2
  //
  if (Event != NULL) {
    gtBS->CloseEvent (Event);
    Event = NULL;
  }
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }

  //
  // Scenario 3 , connect device driver4
  //
  Status = LoadStartImage (
             StandardLib,
             mImageHandle,
             DEVICE_DRIVER_14_NAME,
             &DeviceDriverImageHandle4
             );
  if (EFI_ERROR (Status)) {
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

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mInterfaceFunctionTestProtocol1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (1 != NoHandles)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateHandleBuffer 2 Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
    goto Scenario_3_clean;
  }

  DriverImageHandle[0] = DeviceDriverImageHandle4;
  DriverImageHandle[1] = NULL;
  Status = gtBS->ConnectController (*HandleBuffer, DriverImageHandle, NULL, TRUE);
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid009,
                 L"BS.CombinationTest3 - Integrated Test",
                 L"%a:%d:ConnectController 2 Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // this time, protocol1 ~ 3 and 5 ~ 7 should be able to be accessed,
  // protocol4 could not
  //
  ProtGuid[3] = mInterfaceFunctionTestProtocol5Guid;
  ProtGuid[4] = mInterfaceFunctionTestProtocol6Guid;
  ProtGuid[5] = mInterfaceFunctionTestProtocol7Guid;
  ProtGuid[6] = mInterfaceFunctionTestProtocol4Guid;
  for (Index = 0; Index < 7; Index++) {
    Status = gtBS->LocateProtocol (
                     &ProtGuid[Index],
                     NULL,
                     (VOID **) &ProtInst[Index]
                     );
    if (Index == 6) {
      if (EFI_NOT_FOUND == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerServicesCombinationTestAssertionGuid010,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateProtocol 3 Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }
Scenario_3_clean:
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }

  //
  // Scenario 4 , connect device driver5
  //
  Status = LoadStartImage (
             StandardLib,
             mImageHandle,
             DEVICE_DRIVER_15_NAME,
             &DeviceDriverImageHandle5
             );
  if (EFI_ERROR (Status)) {
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
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mInterfaceFunctionTestProtocol3Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (1 != NoHandles)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateHandleBuffer 3 Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                  );
    goto Scenario_4_clean;
  }

  DriverImageHandle[0] = DeviceDriverImageHandle5;
  DriverImageHandle[1] = NULL;
  Status = gtBS->ConnectController (*HandleBuffer, DriverImageHandle, NULL, TRUE);
  if (EFI_NOT_FOUND == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid011,
                 L"BS.CombinationTest3 - Integrated Test",
                 L"%a:%d:ConnectController 3 Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // this time, protocol1 ~ 3 and 5 ~ 7 still be able to be accessed
  //
  ProtGuid[3] = mInterfaceFunctionTestProtocol5Guid;
  ProtGuid[4] = mInterfaceFunctionTestProtocol6Guid;
  ProtGuid[5] = mInterfaceFunctionTestProtocol7Guid;
  for (Index = 0; Index < 6; Index++) {
    Status = gtBS->LocateProtocol (
                     &ProtGuid[Index],
                     NULL,
                     (VOID **) &ProtInst[Index]
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerServicesCombinationTestAssertionGuid012,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateProtocol 4 Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }
Scenario_4_clean:
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }

  //
  // Scenario 5 , uninstall protocol3 to disconnect device driver 3
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mInterfaceFunctionTestProtocol3Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (1 != NoHandles)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateHandleBuffer 4 Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
    goto Scenario_5_clean;
  }

  Status = gtBS->HandleProtocol (
                   *HandleBuffer,
                   &mInterfaceFunctionTestProtocol3Guid,
                   (VOID **) &ProtInst[0]
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:HandleProtocol 2 Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
    goto Scenario_5_clean;
  }

  Status = gtBS->DisconnectController (Handle, NULL, *HandleBuffer);
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid013,
                 L"BS.CombinationTest3 - Integrated Test",
                 L"%a:%d:UninstallProtocolInterface 1 Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // this time, protocol1, 2 and 5, 7 still be able to be accessed,
  // protoocol3, 6 could not be accessed.
  //
  ProtGuid[3] = mInterfaceFunctionTestProtocol5Guid;
  ProtGuid[4] = mInterfaceFunctionTestProtocol6Guid;
  ProtGuid[5] = mInterfaceFunctionTestProtocol7Guid;
  for (Index = 0; Index < 6; Index++) {
    Status = gtBS->LocateProtocol (
                     &ProtGuid[Index],
                     NULL,
                     (VOID **) &ProtInst[Index]
                     );
    if ((Index == 2) || (Index == 4)) {
      if (EFI_NOT_FOUND == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerServicesCombinationTestAssertionGuid014,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateProtocol 5 Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }
Scenario_5_clean:
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
    HandleBuffer = NULL;
  }

  //
  // Scenario 6 , disconnect bus driver
  //
  Status = gtBS->DisconnectController (Handle, NULL, NULL);
  if (EFI_NOT_FOUND == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid015,
                 L"BS.CombinationTest3 - Integrated Test",
                 L"%a:%d:DisconnectController 1 Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // this time, protocol1, 3, 7 could not be accessed,
  // protocol 2, 5 still could be accessed.
  //
  ProtGuid[3] = mInterfaceFunctionTestProtocol5Guid;
  ProtGuid[4] = mInterfaceFunctionTestProtocol7Guid;
  for (Index = 0; Index < 5; Index++) {
    Status = gtBS->LocateProtocol (
                     &ProtGuid[Index],
                     NULL,
                     (VOID **) &ProtInst[Index]
                     );
    if (Index == 1 || Index == 3) {
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      if (EFI_NOT_FOUND == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerServicesCombinationTestAssertionGuid016,
                   L"BS.CombinationTest3 - Integrated Test",
                   L"%a:%d:LocateProtocol 6 Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }

  Status = EFI_SUCCESS;
Done:

  gtBS->UnloadImage (DeviceDriverImageHandle1);
  gtBS->UnloadImage (DeviceDriverImageHandle2);
  gtBS->UnloadImage (DeviceDriverImageHandle3);
  gtBS->UnloadImage (DeviceDriverImageHandle4);
  gtBS->UnloadImage (DeviceDriverImageHandle5);
  gtBS->UnloadImage (BusDriverImageHandle);

  gtBS->UninstallProtocolInterface (
          Handle,
          &mTestNoInterfaceProtocol2Guid,
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
BBTestCombinationTest2CheckPoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_STATUS                              Status;
  UINTN                                   Index;
  EFI_HANDLE                              Handle;
  UINTN                                   LastIndex;

  UINTN                                   Numbers;

  StressTestNonInterfaceProtocolGuid[0] = STRESS_TEST_NON_INTERFACE_PROTOCOL_0_GUID;
  StressTestNonInterfaceProtocolGuid[1] = STRESS_TEST_NON_INTERFACE_PROTOCOL_1_GUID;
  StressTestNonInterfaceProtocolGuid[2] = STRESS_TEST_NON_INTERFACE_PROTOCOL_2_GUID;
  StressTestNonInterfaceProtocolGuid[3] = STRESS_TEST_NON_INTERFACE_PROTOCOL_3_GUID;
  StressTestNonInterfaceProtocolGuid[4] = STRESS_TEST_NON_INTERFACE_PROTOCOL_4_GUID;
  StressTestNonInterfaceProtocolGuid[5] = STRESS_TEST_NON_INTERFACE_PROTOCOL_5_GUID;
  StressTestNonInterfaceProtocolGuid[6] = STRESS_TEST_NON_INTERFACE_PROTOCOL_6_GUID;
  StressTestNonInterfaceProtocolGuid[7] = STRESS_TEST_NON_INTERFACE_PROTOCOL_7_GUID;
  StressTestNonInterfaceProtocolGuid[8] = STRESS_TEST_NON_INTERFACE_PROTOCOL_8_GUID;
  StressTestNonInterfaceProtocolGuid[9] = STRESS_TEST_NON_INTERFACE_PROTOCOL_9_GUID;
  StressTestNonInterfaceProtocolGuid[10] = STRESS_TEST_NON_INTERFACE_PROTOCOL_10_GUID;
  StressTestNonInterfaceProtocolGuid[11] = STRESS_TEST_NON_INTERFACE_PROTOCOL_11_GUID;
  StressTestNonInterfaceProtocolGuid[12] = STRESS_TEST_NON_INTERFACE_PROTOCOL_12_GUID;
  StressTestNonInterfaceProtocolGuid[13] = STRESS_TEST_NON_INTERFACE_PROTOCOL_13_GUID;
  StressTestNonInterfaceProtocolGuid[14] = STRESS_TEST_NON_INTERFACE_PROTOCOL_14_GUID;
  StressTestNonInterfaceProtocolGuid[15] = STRESS_TEST_NON_INTERFACE_PROTOCOL_15_GUID;
  StressTestNonInterfaceProtocolGuid[16] = STRESS_TEST_NON_INTERFACE_PROTOCOL_16_GUID;
  StressTestNonInterfaceProtocolGuid[17] = STRESS_TEST_NON_INTERFACE_PROTOCOL_17_GUID;
  StressTestNonInterfaceProtocolGuid[18] = STRESS_TEST_NON_INTERFACE_PROTOCOL_18_GUID;
  StressTestNonInterfaceProtocolGuid[19] = STRESS_TEST_NON_INTERFACE_PROTOCOL_19_GUID;
  StressTestNonInterfaceProtocolGuid[20] = STRESS_TEST_NON_INTERFACE_PROTOCOL_20_GUID;
  StressTestNonInterfaceProtocolGuid[21] = STRESS_TEST_NON_INTERFACE_PROTOCOL_21_GUID;
  StressTestNonInterfaceProtocolGuid[22] = STRESS_TEST_NON_INTERFACE_PROTOCOL_22_GUID;
  StressTestNonInterfaceProtocolGuid[23] = STRESS_TEST_NON_INTERFACE_PROTOCOL_23_GUID;
  StressTestNonInterfaceProtocolGuid[24] = STRESS_TEST_NON_INTERFACE_PROTOCOL_24_GUID;
  StressTestNonInterfaceProtocolGuid[25] = STRESS_TEST_NON_INTERFACE_PROTOCOL_25_GUID;
  StressTestNonInterfaceProtocolGuid[26] = STRESS_TEST_NON_INTERFACE_PROTOCOL_26_GUID;
  StressTestNonInterfaceProtocolGuid[27] = STRESS_TEST_NON_INTERFACE_PROTOCOL_27_GUID;
  StressTestNonInterfaceProtocolGuid[28] = STRESS_TEST_NON_INTERFACE_PROTOCOL_28_GUID;
  StressTestNonInterfaceProtocolGuid[29] = STRESS_TEST_NON_INTERFACE_PROTOCOL_29_GUID;
  StressTestNonInterfaceProtocolGuid[30] = STRESS_TEST_NON_INTERFACE_PROTOCOL_30_GUID;
  StressTestNonInterfaceProtocolGuid[31] = STRESS_TEST_NON_INTERFACE_PROTOCOL_31_GUID;
  StressTestNonInterfaceProtocolGuid[32] = STRESS_TEST_NON_INTERFACE_PROTOCOL_32_GUID;
  StressTestNonInterfaceProtocolGuid[33] = STRESS_TEST_NON_INTERFACE_PROTOCOL_33_GUID;
  StressTestNonInterfaceProtocolGuid[34] = STRESS_TEST_NON_INTERFACE_PROTOCOL_34_GUID;
  StressTestNonInterfaceProtocolGuid[35] = STRESS_TEST_NON_INTERFACE_PROTOCOL_35_GUID;
  StressTestNonInterfaceProtocolGuid[36] = STRESS_TEST_NON_INTERFACE_PROTOCOL_36_GUID;
  StressTestNonInterfaceProtocolGuid[37] = STRESS_TEST_NON_INTERFACE_PROTOCOL_37_GUID;
  StressTestNonInterfaceProtocolGuid[38] = STRESS_TEST_NON_INTERFACE_PROTOCOL_38_GUID;
  StressTestNonInterfaceProtocolGuid[39] = STRESS_TEST_NON_INTERFACE_PROTOCOL_39_GUID;

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

  Handle = NULL;
  LastIndex = 40;
  for (Index = 0; Index < 40; Index++) {
      Status = gtBS->InstallProtocolInterface (
                       &Handle,
                       &StressTestNonInterfaceProtocolGuid[Index],
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
                     gProtocolHandlerServicesCombinationTestAssertionGuid017,
                     L"BS.CombinationTest2 - Checkpoint1 - Install stress",
                     L"%a:%d:Status - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      if (EFI_ERROR(Status)) {
        LastIndex = Index;
        break;
      }
    }

    for (Index = 0; Index < LastIndex; Index++) {
      Status = gtBS->UninstallProtocolInterface (
                       Handle,
                       &StressTestNonInterfaceProtocolGuid[Index],
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
                   gProtocolHandlerServicesCombinationTestAssertionGuid018,
                   L"BS.CombinationTest2 - Checkpoint1 - Uninstall stress",
                   L"%a:%d:Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
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
BBTestCombinationTest2CheckPoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_STATUS                              Status;
  EFI_EVENT                               Event[100];
  UINTN                                   Index;
  UINTN                                   NotifyTimes;
  VOID                                    *Registration;
  EFI_HANDLE                              Handle;

  UINTN                                   Numbers;

  Handle = NULL;
  NotifyTimes = 0;

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

  for (Index = 0; Index < 100; Index++) {
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_WAIT,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) TestNotifyFunction1,
                     &NotifyTimes,
                     &Event[Index]
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environment",
                     L"%a:%d:Status - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      return Status;
    }
  }

  for (Index = 0; Index < 100; Index++) {
    Status = gtBS->RegisterProtocolNotify (
                     &mTestNoInterfaceProtocol1Guid,
                     Event[Index],
                     &Registration
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerServicesCombinationTestAssertionGuid019,
                   L"BS.CombinationTest2 - Checkpoint2 - RegisterProtocolNotify stress",
                   L"%a:%d:Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }

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
                   L"%a:%d:Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
    goto Done;
  }

  //
  // wait some time for the events triggering
  //
  SctPrint (L"Waiting a few seconds for signal ...\n");
  gtBS->Stall (STALL_10_SECONDS);

  if (100 != NotifyTimes) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid020,
                 L"BS.CombinationTest2 - Checkpoint2 - RegisterProtocolNotify stress",
                 L"%a:%d:Check notification times: expected - 100, real - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 NotifyTimes
                 );
Done:
  //
  // restore environment
  //
  for (Index = 0; Index < 100; Index++) {
    gtBS->CloseEvent (Event[Index]);
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
BBTestCombinationTest2CheckPoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_STATUS                              Status;
  UINTN                                   Index;
  EFI_HANDLE                              Handle;
  VOID                                    *ProtInstance;

  UINTN                                   Numbers;

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

  for (Index = 0; Index < 1000; Index++) {
    Status = gtBS->HandleProtocol (
                     Handle,
                     &mTestNoInterfaceProtocol1Guid,
                     (VOID **) &ProtInstance
                     );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gProtocolHandlerServicesCombinationTestAssertionGuid021,
                   L"BS.CombinationTest2 - Checkpoint3 - HandleProtocol stress",
                   L"%a:%d:Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
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
BBTestCombinationTest2CheckPoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_STATUS                              Status;
  UINTN                                   Index;
  EFI_HANDLE                              Handle;
  EFI_HANDLE                              ChildHandle;
  UINT32                                  Attributes[4];
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *OpenInfo;
  UINTN                                   OpenInfoCount;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *TempInfo;
  BOOLEAN                                 MisMatch;
  BOOLEAN                                 Found;
  UINTN                                   AttributesIndex;
  VOID                                    *ProtInstance;

  UINTN                                   Numbers;

  Handle = NULL;
  ChildHandle = NULL;
  Attributes[0] = EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL;
  Attributes[1] = EFI_OPEN_PROTOCOL_GET_PROTOCOL;
  Attributes[2] = EFI_OPEN_PROTOCOL_TEST_PROTOCOL;
  Attributes[3] = EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER;

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

  Status = gtBS->InstallProtocolInterface (
                   &ChildHandle,
                   &mTestNoInterfaceProtocol2Guid,
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
    gtBS->UninstallProtocolInterface (
            Handle,
            &mTestNoInterfaceProtocol1Guid,
            NULL
            );
    return Status;
  }

  for (Index = 0; Index < 100; Index++) {

    for (AttributesIndex = 0; AttributesIndex < 4; AttributesIndex++) {

      Status = gtBS->OpenProtocol (
                       Handle,
                       &mTestNoInterfaceProtocol1Guid,
                       (VOID **) &ProtInstance,
                       mImageHandle,
                       ChildHandle,
                       Attributes[AttributesIndex]
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gProtocolHandlerServicesCombinationTestAssertionGuid022,
                     L"BS.CombinationTest2 - Checkpoint4 - OpenProtocol stress",
                     L"%a:%d:Status - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
    }
  }

  //
  // check by OpenProtocolInformation
  //
  OpenInfo = NULL;
  Status = gtBS->OpenProtocolInformation (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   &OpenInfo,
                   &OpenInfoCount
                   );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid023,
                 L"BS.CombinationTest2 - Checkpoint4 - OpenProtocol stress",
                 L"%a:%d:OpenProtocolInformation Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (4 == OpenInfoCount) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gProtocolHandlerServicesCombinationTestAssertionGuid024,
                 L"BS.CombinationTest2 - Checkpoint4 - OpenProtocol stress",
                 L"%a:%d:OpenInfoCount - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 OpenInfoCount
                 );

  MisMatch = FALSE;
  TempInfo = OpenInfo;
  for (Index = 0; Index < 4; Index++) {

    if ((TempInfo->AgentHandle != mImageHandle)
        || (TempInfo->ControllerHandle != ChildHandle)
        || (TempInfo->OpenCount != 100)) {

          MisMatch = TRUE;
          break;
    }

    TempInfo++;
  }

  if (!MisMatch) {

    for (AttributesIndex = 0; AttributesIndex < 4; AttributesIndex++) {

      TempInfo = OpenInfo;
      Found = FALSE;
      for (Index = 0; Index < 4; Index++) {

        if (TempInfo->Attributes == Attributes[AttributesIndex]) {
          Found = TRUE;
          break;
        }

        TempInfo++;
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
  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gProtocolHandlerServicesCombinationTestAssertionGuid025,
                L"BS.CombinationTest2 - Checkpoint4 - OpenProtocol stress",
                L"%a:%d:MisMatch is - %d, TPL - %d",
                __FILE__,
                (UINTN)__LINE__,
                MisMatch,
                TplArray[Index]
                );

  if (OpenInfo != NULL) {
    gtBS->FreePool (OpenInfo);
  }

  //
  // restore environment
  //
  Status = gtBS->CloseProtocol (
                   Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   mImageHandle,
                   ChildHandle
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CloseProtocol - restore environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
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
                   L" UninstallProtocol 1 - restore environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  Status = gtBS->UninstallProtocolInterface (
                   ChildHandle,
                   &mTestNoInterfaceProtocol2Guid,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" UninstallProtocol 2 - restore environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
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