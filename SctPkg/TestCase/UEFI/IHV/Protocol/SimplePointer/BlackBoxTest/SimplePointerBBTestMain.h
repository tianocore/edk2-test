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

#define  IHV_SIMPLE_POINTER_PROTOCOL_GUID         \
  { 0xf251dd1a, 0xf5c7, 0x453f, 0x91, 0x1f, 0x87, 0x99, 0x2e, 0x44, 0x1c, 0x0f }


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
BBTestResetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
EFI_STATUS

BBTestGetStateFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetStateFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWaitForInputFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestDevicePathAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Conformance Test
//
EFI_STATUS
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
BBTestResetClearanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
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
  { 0x77383b66, 0xa2d5, 0x44c4, 0xb1, 0x65, 0x60, 0xd3, 0x38, 0x1b, 0xe0, 0xdf }

#define SIMPLE_POINTER_PROTOCOL_RESET_FUNCTION_MANUAL_GUID \
  { 0x92c9d326, 0x817e, 0x4401, 0xb5, 0xf9, 0x81, 0x38, 0x1e, 0x89, 0xc0, 0x1c }

#define SIMPLE_POINTER_PROTOCOL_GETSTATE_FUNCTION_AUTO_GUID \
  { 0xe87a152b, 0x7c8f, 0x47f5, 0x9c, 0x6a, 0x99, 0xbf, 0xda, 0x2c, 0xc3, 0x80 }

#define SIMPLE_POINTER_PROTOCOL_GETSTATE_FUNCTION_MANUAL_GUID \
  { 0xcadf2af1, 0xfe8d, 0x46e2, 0x9b, 0x25, 0xd4, 0xed, 0x11, 0x74, 0x7f, 0xbe }

#define SIMPLE_POINTER_PROTOCOL_WAITFORINPUT_FUNCTION_MANUAL_GUID\
  { 0xea7bc749, 0xf74c, 0x44e6, 0x80, 0xa7, 0xe0, 0xc8, 0x4c, 0xb6, 0x70, 0xb7 }

#define SIMPLE_POINTER_PROTOCOL_DEVICE_PATH_AUTO_GUID \
  { 0xd14efb67, 0x4cd6, 0x4b39, 0xab, 0x7e, 0x57, 0x39, 0x68, 0x52, 0xa0, 0x52 }

#define SIMPLE_POINTER_PROTOCOL_WAITFORINPUT_CONFORMANCE_MANUAL_GUID\
  { 0x641545f7, 0xeb28, 0x4060, 0x80, 0xab, 0xfc, 0xac, 0x79, 0x9f, 0xb0, 0x1d }

#define SIMPLE_POINTER_PROTOCOL_RESET_CLEARANCE_MANUAL_GUID\
  { 0xc69b862c, 0xa587, 0x4590, 0x83, 0xa2, 0x2e, 0xa6, 0xc1, 0x67, 0xea, 0xc6 }

#define SIMPLE_POINTER_PROTOCOL_GETSTATE_EXTENSIVE_MANUAL_GUID\
  { 0x6f5813e3, 0xfe7f, 0x47f5, 0xad, 0x25, 0xb6, 0xe0, 0x5b, 0x6f, 0x0c, 0xc4 }

#endif

