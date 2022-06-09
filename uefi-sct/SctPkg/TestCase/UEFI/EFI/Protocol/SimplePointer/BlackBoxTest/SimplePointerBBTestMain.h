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

  SimplePointerBBTestMain.h

Abstract:

  BB test header file of Simple Pointer Protocol

--*/


#ifndef _SIMPLE_POINTER_BBTEST_H_
#define _SIMPLE_POINTER_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/SimplePointer.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  SIMPLE_POINTER_PROTOCOL_TEST_REVISION    0x00010000



extern   EFI_EVENT              TimerEvent;

EFI_STATUS
EFIAPI
InitializeBBTestSimplePointer (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestSimplePointerProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

//
// Interface function
//
EFI_STATUS
EFIAPI
BBTestResetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetStateFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetStateFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestWaitForInputFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Conformance Test
//
EFI_STATUS
EFIAPI
BBTestWaitForInputConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Extensive Test
//
EFI_STATUS
EFIAPI
BBTestResetClearanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetStateExtensiveManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Assocaitional Fucntion
//
VOID
WaitTimeOrKey(
  IN  UINTN       Seconds
  );

EFI_STATUS
LocateDevicePathFromSimplePointer(
  IN EFI_SIMPLE_POINTER_PROTOCOL          *SimplePointer,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

BOOLEAN
AutoJudge(
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

BOOLEAN
WaitTimeOrPointer(
  IN  UINTN                         Seconds ,
  IN  EFI_SIMPLE_POINTER_PROTOCOL   *SimplePointer
  );

BOOLEAN
PointerKeepSilent(
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  );

BOOLEAN
PointerRButtonPressed(
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  );

BOOLEAN
PointerRButtonPressedExt(
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  );

BOOLEAN
PointerLButtonPressed(
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  );

BOOLEAN
PointerLButtonPressedExt(
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  );

BOOLEAN
PointerMovedExt(
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  );

//
// Entry GUIDs
//

#define SIMPLE_POINTER_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0xb18e7416, 0x3d1d, 0x4595, { 0xbd, 0x28, 0xe3, 0x16, 0xee, 0xb0, 0xa5, 0x92 } }

#define SIMPLE_POINTER_PROTOCOL_RESET_FUNCTION_MANUAL_GUID \
  { 0x4f063838, 0xddb3, 0x4077, { 0x80, 0xd9, 0xf, 0x43, 0xf7, 0x60, 0x5a, 0x77 } }

#define SIMPLE_POINTER_PROTOCOL_GETSTATE_FUNCTION_AUTO_GUID \
  { 0x51276932, 0x473, 0x4f5e, { 0xa5, 0xb, 0x1c, 0x35, 0xb2, 0x51, 0x8, 0xad } }

#define SIMPLE_POINTER_PROTOCOL_GETSTATE_FUNCTION_MANUAL_GUID \
  { 0xa75ac398, 0x2c5c, 0x4069, { 0x82, 0x5f, 0x46, 0xf2, 0x4d, 0x9, 0x92, 0xaa } }

#define SIMPLE_POINTER_PROTOCOL_WAITFORINPUT_FUNCTION_MANUAL_GUID\
  { 0xd6038070, 0xb199, 0x4e77, { 0x89, 0xbb, 0x68, 0x6a, 0xc8, 0x71, 0xaf, 0xc7 } }

#define SIMPLE_POINTER_PROTOCOL_WAITFORINPUT_CONFORMANCE_MANUAL_GUID\
  { 0x2abe84d5, 0x5e4e, 0x4205, { 0x8b, 0x75, 0x80, 0x2f, 0x65, 0xe, 0xf5, 0x9b } }

#define SIMPLE_POINTER_PROTOCOL_RESET_CLEARANCE_MANUAL_GUID\
  { 0xc1f3b46d, 0x1012, 0x4b23, { 0x8a, 0xca, 0x86, 0x44, 0x2c, 0xd3, 0xeb, 0xcc } }

#define SIMPLE_POINTER_PROTOCOL_GETSTATE_EXTENSIVE_MANUAL_GUID\
  { 0xc824a780, 0x21b2, 0x4ebf, { 0xac, 0x4b, 0xa2, 0x53, 0xfb, 0xf5, 0x17, 0x6b } }

#endif

