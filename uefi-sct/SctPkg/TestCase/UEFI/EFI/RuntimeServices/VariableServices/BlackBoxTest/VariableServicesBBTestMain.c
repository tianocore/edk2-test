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
  VariableServicesBbTestMain.c

Abstract:
  The main source file for Variable Services Black-Box Test.

--*/

//
// Includes
//

#include "SctLib.h"
#include "VariableServicesBBTestMain.h"

//
// Declarations
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  VARIABLE_SERVICES_BB_TEST_REVISION,
  VARIABLE_SERVICES_BB_TEST_GUID,
  L"Variable Services Test",
  L"UEFI Variable Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_RECOVERY_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    GET_VARIABLE_CONF_TEST_GUID,
    L"GetVariable_Conf",
    L"Perform the consistence check of GetVariable() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetVariableConfTest
  },
  {
    GET_NEXT_VARIABLE_NAME_CONF_TEST_GUID,
    L"GetNextVariableName_Conf",
    L"Perform the consistence check of GetNextVariableName() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetNextVariableNameConfTest
  },
  {
    SET_VARIABLE_CONF_TEST_GUID,
    L"SetVariable_Conf",
    L"Perform the consistence check of SetVariable() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetVariableConfTest
  },
  {
    GET_VARIABLE_FUNC_TEST_GUID,
    L"GetVariable_Func",
    L"Test the functionality of GetVariable() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetVariableFuncTest
  },
  {
    GET_NEXT_VARIABLE_NAME_FUNC_TEST_GUID,
    L"GetNextVariableName_Func",
    L"Test the functionality of GetNextVariableName() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetNextVariableNameFuncTest
  },
  {
    SET_VARIABLE_FUNC_TEST_GUID,
    L"SetVariable_Func",
    L"Test the functionality of SetVariable() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetVariableFuncTest
  },
  
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
	{
    QUERY_VAR_INFO_CONF_TEST_GUID,
    L"QueryVariableInfo_Conf",
    L"Test the consistence of QueryVariableInfo() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    QueryVariableInfoConfTest
  },

  {
    QUERY_VAR_INFO_FUNC_TEST_GUID,
    L"QueryVariableInfo_Func",
    L"Test the function of QueryVariableInfo() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    QueryVariableInfoFuncTest
  },

  {
    EFI_AUTHVARIABLE_DER_FUNC_TEST_GUID,
    L"AuthVar_Func",
    L"Test the function of Auth Variable",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    AuthVariableDERFuncTest
  },

  {
    EFI_AUTHVARIABLE_DER_CONF_TEST_GUID,
    L"AuthVar_Conf",
    L"Test the conformance of Auth Variable",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    AuthVariableDERConfTest
  },

#endif

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
  {
    HARDWARE_ERROR_RECORD_FUNC_TEST_GUID,
    L"HardwareErrorRecord_Func",
    L"Test the function of HardwareErrorRecord_Func.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    HardwareErrorRecordFuncTest
  },
  
  {
    HARDWARE_ERROR_RECORD_CONF_TEST_GUID,
    L"HardwareErrorRecord_Conf",
    L"Test the Conformance of HardwareErrorRecord_Conf.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    HardwareErrorRecordConfTest
  },

#endif

#ifdef EFI_TEST_EXHAUSTIVE
  {
    MULTIPLE_STRESS_TEST_GUID,
    L"Multiple_Stress",
    L"Multiple tests on GetVariable(), GetNextVariableName(), and SetVariable() services.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    MultipleStressTest
  },
  {
    OVERFLOW_STRESS_TEST_GUID,
    L"Overflow_Stress",
    L"Overflow tests on SetVariable() service",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    OverflowStressTest
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_GUID gTestVendor1Guid = TEST_VENDOR1_GUID;
EFI_GUID gTestVendor2Guid = TEST_VENDOR2_GUID;

//
// Prototypes
//

EFI_STATUS
EFIAPI
InitializeVariableServicesBbTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadVariableServicesBbTest (
  IN EFI_HANDLE       ImageHandle
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
InitializeVariableServicesBbTest (
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
           UnloadVariableServicesBbTest,
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
UnloadVariableServicesBbTest (
  IN EFI_HANDLE       ImageHandle
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
 *  @param RecoveryLib    A pointer to Test Recovery Support Protocol.
 *  @param LoggingLib     A pointer to Test Logging Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  **RecoveryLib,
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
  // Get the test recovery support library interface
  //
  *RecoveryLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   (VOID **) RecoveryLib
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


#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
EFI_STATUS
EFIAPI
Myitox (
  IN UINTN        Num,
  OUT CHAR16      *StringNum
)
{
  UINTN          CurrentNum;
  UINTN          CurrentPos;
  const UINTN    Times = 4;
  
  for ( CurrentPos = 0; CurrentPos < Times; CurrentPos++ ) {
    CurrentNum = Num % 16;
    Num /= 16;
    
    if ( CurrentNum < 10 )
      StringNum[Times-CurrentPos-1] = (CHAR16)( L'0' + CurrentNum );
    else
      StringNum[Times-CurrentPos-1] = (CHAR16)( L'A' + ( CurrentNum - 10 ) );
  }
  
  StringNum[Times] = '\0';
  
  return EFI_SUCCESS;
}
#endif
