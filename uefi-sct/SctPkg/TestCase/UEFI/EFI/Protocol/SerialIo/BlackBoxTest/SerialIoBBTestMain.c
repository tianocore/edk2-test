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
  SerialIoBbTestMain.c

Abstract:
  Source file for Serial IO Protocol Black-Box Test.

--*/

#include "SctLib.h"
#include "SerialIoBBTestMain.h"

//
// Declarations
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SERIAL_IO_BB_TEST_REVISION,
  EFI_SERIAL_IO_PROTOCOL_GUID,
  L"Serial IO Protocol Test",
  L"UEFI Serial IO Protocol Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    RESET_FUNC_TEST_GUID,
    L"Reset_Func",
    L"Test the functionality of Reset() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    ResetFuncTest
  },
  {
    SET_ATTRIBUTES_FUNC_TEST_GUID,
    L"SetAttributes_Func",
    L"Test the functionality of SetAttributes() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetAttributesFuncTest
  },
  {
    SET_CONTROL_FUNC_TEST_GUID,
    L"SetControl_Func",
    L"Test the functionality of SetControl() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetControlFuncTest
  },
  {
    GET_CONTROL_FUNC_TEST_GUID,
    L"GetControl_Func",
    L"Test the functionality of GetControl() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetControlFuncTest
  },
  {
    WRITE_FUNC_TEST_GUID,
    L"Write_Func",
    L"Test the functionality of Write() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    WriteFuncTest
  },
  {
    READ_FUNC_TEST_GUID,
    L"Read_Func",
    L"Test the functionality of Read() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    ReadFuncTest
  },
  {
    SET_ATTRIBUTES_CONF_TEST_GUID,
    L"SetAttributes_Conf",
    L"Perform the consistency check of SetAttributes() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetAttributesConfTest
  },
  {
    SET_CONTROL_CONF_TEST_GUID,
    L"SetControl_Conf",
    L"Perform the consistency check of SetControl() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetControlConfTest
  },
  {
    READ_CONF_TEST_GUID,
    L"Read_Conf",
    L"Perform the consistency check of Read() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    ReadConfTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    RESET_STRESS_TEST_GUID,
    L"Reset_Stress",
    L"Stress test for Reset() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    ResetStressTest
  },
  {
    SET_ATTRIBUTES_STRESS_TEST_GUID,
    L"SetAttributes_Stress",
    L"Stress test for SetAttributes() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetAttributesStressTest
  },
  {
    SET_CONTROL_STRESS_TEST_GUID,
    L"SetControl_Stress",
    L"Stress test for SetControl() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetControlStressTest
  },
  {
    GET_CONTROL_STRESS_TEST_GUID,
    L"GetControl_Stress",
    L"Stress test for GetControl() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetControlStressTest
  },
  {
    WRITE_STRESS_TEST_GUID,
    L"Write_Stress_Manual",
    L"Stress test for Write() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    WriteStressTest
  },
  {
    READ_STRESS_TEST_GUID,
    L"Read_Stress_Manual",
    L"Stress test for Read() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    ReadStressTest
  },
#endif

  0
};

CHAR16 *gParityString[] = {
  L"DefaultParity",
  L"NoParity",
  L"EvenParity",
  L"OddParity",
  L"MarkParity",
  L"SpaceParity",
  L"InvalidParity"
};

CHAR16 *gStopBitsString[] = {
  L"DefaultStopBits",
  L"OneStopBit",
  L"OneFiveStopBits",
  L"TwoStopBits",
  L"InvalidStopBits"
};

EFI_BB_TEST_PROTOCOL      *gBBTestProtocolInterface;

//
// Prototypes
//

EFI_STATUS
EFIAPI
InitializeSerialIoBbTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadSerialIoBbTest (
  IN EFI_HANDLE           ImageHandle
  );

//
// Functions
//


/**
 *  Creates/installs the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @param SystemTable    The system table.
 *  @return EFI_SUCCESS   The interface was installed successfully.
 *  @return EFI_OUT_OF_RESOURCES    Failed due to the lack of resources.
 *  @return EFI_INVALID_PARAMETER   One of parameters is invalid.
 */
EFI_STATUS
EFIAPI
InitializeSerialIoBbTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  SctInitializeLib (ImageHandle, SystemTable);
  EfiInitializeTestLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadSerialIoBbTest,
           &gBBTestProtocolInterface
           );
}


/**
 *  Unloads the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @return EFI_SUCCESS   The interface was uninstalled successfully.
 */
EFI_STATUS
EFIAPI
UnloadSerialIoBbTest (
  IN EFI_HANDLE           ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


/**
 *  Support function - Get test support protocol library.
 *  @param SupportHandle  A handle containing support protocols.
 *  @param StandardLib    A pointer to Standard Test Support Protocol.
 *  @param LoggingLib     A pointer to Test Logging Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  )
{
  EFI_STATUS            Status;

  //
  // Get the standard test support library interface
  //
  *StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the test logging support library interface
  //
  *LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) LoggingLib
                   );
  // Test logging support library is optional

  //
  // Done
  //
  return EFI_SUCCESS;
}
