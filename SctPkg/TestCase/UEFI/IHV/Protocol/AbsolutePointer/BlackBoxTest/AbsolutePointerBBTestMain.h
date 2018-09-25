/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AbsolutePointerBBTestMain.h

Abstract:

  BB test header file of Absolute Pointer protocol

--*/


#ifndef _ABSOLUTE_POINTER_BBTEST_H_
#define _ABSOLUTE_POINTER_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/AbsolutePointer.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  ABSOLUTE_POINTER_PROTOCOL_TEST_REVISION    0x00010000

#define IHV_ABSOLUTE_POINTER_PROTOCOL_GUID    \
{      \
      0x39189210, 0x7e24, 0x4c29, 0xa0, 0x6e, 0x42, 0xa, 0xd0, 0x53, 0xde, 0x68          \
}

EFI_STATUS
EFIAPI
InitializeBBTestAbsolutePointer (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestAbsolutePointerProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
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

EFI_STATUS
BBTestResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetStateConformanceAutoTest (
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
LocateDevicePathFromAbsolutePointer(
  IN EFI_ABSOLUTE_POINTER_PROTOCOL          *AbsolutePointer,
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
  IN  EFI_ABSOLUTE_POINTER_PROTOCOL   *AbsolutePointer
  );

BOOLEAN
PointerKeepSilent(
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  );

BOOLEAN
SupportAltActive (
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  );

BOOLEAN
SupportAltActiveExt (
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  );

BOOLEAN
SupportPressureAsZ(
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  );

BOOLEAN
SupportPressureAsZExt (
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  );

BOOLEAN
PointerMovedExt(
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  );

//
// Entry GUIDs
//

#define ABSOLUTE_POINTER_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0x61b81e9c, 0x38d9, 0x46dd, 0x80, 0xae, 0xe7, 0xe8, 0x69, 0xf6, 0x52, 0xff }

#define ABSOLUTE_POINTER_PROTOCOL_RESET_FUNCTION_MANUAL_GUID \
  { 0x40af6558, 0xa11a, 0x4a4d, 0x8d, 0x35, 0x24, 0xe0, 0xa6, 0xf7, 0xed, 0x5e }

#define ABSOLUTE_POINTER_PROTOCOL_GETSTATE_FUNCTION_AUTO_GUID \
  { 0x802a52e9, 0x1b2f, 0x43e6, 0xa7, 0xdc, 0x7, 0x9, 0xef, 0x97, 0x31, 0xa }

#define ABSOLUTE_POINTER_PROTOCOL_GETSTATE_FUNCTION_MANUAL_GUID \
  { 0xb742dc3, 0x7506, 0x4d84, 0xb6, 0x60, 0xef, 0xbe, 0x1, 0xf3, 0xc3, 0x7e }

#define ABSOLUTE_POINTER_PROTOCOL_WAITFORINPUT_FUNCTION_MANUAL_GUID\
  { 0x5d58584c, 0x3e04, 0x496c, 0xa8, 0x84, 0xee, 0x17, 0x33, 0x7e, 0xa0, 0xb3 }

#define ABSOLUTE_POINTER_PROTOCOL_WAITFORINPUT_CONFORMANCE_MANUAL_GUID\
  { 0xf83d1a10, 0xd525, 0x4abc, 0xaf, 0x24, 0x4c, 0xc6, 0xa1, 0x64, 0xe5, 0x7f }

#define ABSOLUTE_POINTER_PROTOCOL_RESET_CLEARANCE_MANUAL_GUID\
  { 0x4783e283, 0xbb27, 0x4206, 0x8d, 0xf9, 0x1d, 0x12, 0x9c, 0x3a, 0x48, 0x6d }

#define ABSOLUTE_POINTER_PROTOCOL_GETSTATE_EXTENSIVE_MANUAL_GUID\
  { 0xb0ab9cf, 0x6c74, 0x4857, 0xad, 0xa5, 0xa4, 0xf4, 0x5e, 0x9a, 0xe6, 0x3d }

#define ABSOLUTE_POINTER_PROTOCOL_GETSTATE_CONFORMANCE_AUTO_GUID \
  { 0xbdbb7779, 0xb050, 0x4f43, 0xba, 0xf0, 0xcb, 0xf3, 0xb3, 0x7b, 0x80, 0xe4 }


#endif


