/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DebugSupportBBTestMain.h

Abstract:

  BB test header file of Debugsupport protocol

--*/


#ifndef _DEBUG_SUPPORT_BBTEST_H_
#define _DEBUG_SUPPORT_BBTEST_H_

#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/DebugSupport.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  DEBUG_SUPPORT_PROTOCOL_TEST_REVISION    0x00010000

extern EFI_INSTRUCTION_SET_ARCHITECTURE PlatformIsa;

EFI_STATUS
EFIAPI
InitializeBBTestDebugSupport (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDebugSupportProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestIsaFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetMaximumProcessorIndexFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestRegisterPeriodicCallbackFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestRegisterExceptionCallbackFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestInvalidateInstructionCacheFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//
void
PeriodicCallback (
  IN EFI_SYSTEM_CONTEXT   SystemContext
  );

void
PeriodicCallback1 (
  IN EFI_SYSTEM_CONTEXT   SystemContext
  );

void
ExceptionCallback (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  );

void
ExceptionCallback1 (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  );

//
// Entry GUIDs
//

#define DEBUG_SUPPORT_PROTOCOL_ISA_FUNCTION_AUTO_GUID \
  { 0x48d4f0dd, 0x2ec1, 0x4e84, { 0xb0, 0xfc, 0x2c, 0xd0, 0x1, 0x7f, 0x64, 0x2f } }

#define DEBUG_SUPPORT_PROTOCOL_GETMAXIMUMPROCESSORINDEX_FUNCTION_AUTO_GUID \
  { 0x7a73d0f1, 0x7cab, 0x4f45, { 0x96, 0x20, 0x3a, 0x25, 0x35, 0xdf, 0x48, 0x43 } }

#define DEBUG_SUPPORT_PROTOCOL_REGISTERPERIODICCALLBACK_FUNCTION_AUTO_GUID \
  { 0x12acc495, 0x91a6, 0x4600, { 0xbd, 0xc8, 0xe0, 0x4c, 0xca, 0xa9, 0x54, 0x64 } }

#define DEBUG_SUPPORT_PROTOCOL_REGISTEREXCEPTIONCALLBACK_FUNCTION_MANUAL_GUID \
  { 0x2e5204a3, 0x6a7e, 0x4371, { 0x87, 0xeb, 0x9, 0xf7, 0x9c, 0x18, 0xb8, 0xec } }

#define DEBUG_SUPPORT_PROTOCOL_INVALIDATEINSTRUCTIONCACHE_FUNCTION_AUTO_GUID \
  { 0x5c107c17, 0x4c2f, 0x440c, { 0xae, 0xa5, 0xd2, 0xf1, 0x47, 0x77, 0x1c, 0xcb } }



#endif

