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

EFI_STATUS
EFIAPI
BBTestResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
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
  { 0x5a053036, 0xe321, 0x42ba, { 0x92, 0x6c, 0x23, 0x7e, 0x7d, 0xc5, 0xa1, 0xb6 } }

#define ABSOLUTE_POINTER_PROTOCOL_RESET_FUNCTION_MANUAL_GUID \
  { 0x226c7db7, 0x95f4, 0x49dd, { 0x98, 0xc9, 0xae, 0x1e, 0x72, 0x7e, 0x62, 0x26 } }

#define ABSOLUTE_POINTER_PROTOCOL_GETSTATE_FUNCTION_AUTO_GUID \
  { 0x415bc9ed, 0x45ec, 0x4565, { 0x8f, 0x9a, 0xb, 0x50, 0xe6, 0x4d, 0x99, 0xdb } }

#define ABSOLUTE_POINTER_PROTOCOL_GETSTATE_FUNCTION_MANUAL_GUID \
  { 0x2957dd41, 0xb75, 0x4543, { 0xac, 0x5a, 0xd4, 0x84, 0xdb, 0xf7, 0xbc, 0x60 } }

#define ABSOLUTE_POINTER_PROTOCOL_WAITFORINPUT_FUNCTION_MANUAL_GUID\
  { 0xd0e4f406, 0xbb55, 0x462a, { 0xb7, 0xa6, 0xbd, 0x36, 0x3c, 0x92, 0xbe, 0xb9 } }

#define ABSOLUTE_POINTER_PROTOCOL_WAITFORINPUT_CONFORMANCE_MANUAL_GUID\
  { 0xdb6251db, 0x1901, 0x4755, { 0x87, 0x78, 0x70, 0x22, 0x30, 0xb0, 0xc6, 0x41 } }

#define ABSOLUTE_POINTER_PROTOCOL_RESET_CLEARANCE_MANUAL_GUID\
  { 0x13f87e7b, 0xc08c, 0x4a6c, { 0x86, 0x36, 0x20, 0x20, 0xb, 0x32, 0x74, 0x48 } }

#define ABSOLUTE_POINTER_PROTOCOL_GETSTATE_EXTENSIVE_MANUAL_GUID\
  { 0xf7d45b7d, 0x9b3f, 0x4de6, { 0xbb, 0xc2, 0xdf, 0xf7, 0xd5, 0xec, 0x12, 0x22 } }

#define ABSOLUTE_POINTER_PROTOCOL_GETSTATE_CONFORMANCE_AUTO_GUID \
  { 0xd460ca2a, 0x6198, 0x4098, { 0x96, 0x68, 0x8d, 0x50, 0x48, 0x65, 0x87, 0x18 } }


#endif


