/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DebugSupportBBTestMain.c

Abstract:

  Test Driver of DebugSupport Protocol

--*/

#include "DebugSupportBBTestMain.h"


//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  DEBUG_SUPPORT_PROTOCOL_TEST_REVISION,
  EFI_DEBUG_SUPPORT_PROTOCOL_GUID,
  L"Debug Support Protocol Test",
  L"UEFI Debug Support Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    DEBUG_SUPPORT_PROTOCOL_ISA_FUNCTION_AUTO_GUID,
    L"Isa_Func",
    L"Verify the correctness of Isa within the testcase",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestIsaFunctionAutoTest
  },

  {
    DEBUG_SUPPORT_PROTOCOL_GETMAXIMUMPROCESSORINDEX_FUNCTION_AUTO_GUID,
    L"GetMaximumProcessorIndex_Func",
    L"Invoke GetMaximumProcessorIndex and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetMaximumProcessorIndexFunctionAutoTest
  },

  {
    DEBUG_SUPPORT_PROTOCOL_REGISTERPERIODICCALLBACK_FUNCTION_AUTO_GUID,
    L"RegisterPeriodicCallback_Func",
    L"Invoke RegisterPeriodicCallback and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_RESET_REQUIRED,
    BBTestRegisterPeriodicCallbackFunctionAutoTest
  },
  {
    DEBUG_SUPPORT_PROTOCOL_INVALIDATEINSTRUCTIONCACHE_FUNCTION_AUTO_GUID,
    L"InvalidateInstructionCache_Func",
    L"Invoke InvalidateInstructionCache and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInvalidateInstructionCacheFunctionAutoTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    DEBUG_SUPPORT_PROTOCOL_REGISTEREXCEPTIONCALLBACK_FUNCTION_MANUAL_GUID,
    L"RegisterExceptionCallback_Func_Manual",
    L"Invoke RegisterExceptionCallback and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL | EFI_TEST_CASE_RESET_REQUIRED,
    BBTestRegisterExceptionCallbackFunctionManualTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestDebugSupportProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Debug Support Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestDebugSupport (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);


  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestDebugSupportProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
EFIAPI
BBTestDebugSupportProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

volatile  UINTN InvokedPeriodicCallback;

VOID
PeriodicCallback (
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  InvokedPeriodicCallback = TRUE;
  return;
}

VOID
PeriodicCallback1 (
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  return;
}

volatile  UINTN InvokedExceptionCallback;

VOID
ExceptionCallback (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  InvokedExceptionCallback = TRUE;
  return;
}

VOID
ExceptionCallback1 (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  return;
}

