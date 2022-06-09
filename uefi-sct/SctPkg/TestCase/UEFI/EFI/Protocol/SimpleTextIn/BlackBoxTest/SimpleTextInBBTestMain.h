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

  SimpleTextInBBTestMain.h

Abstract:

  BB test header file of Simple Input Protocol
--*/


#ifndef _SIMPLE_TEXT_IN_BBTEST_H_
#define _SIMPLE_TEXT_IN_BBTEST_H_

#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/DevicePath.h>
#include <UEFI/Protocol/SimpleTextIn.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>


#define  SIMPLE_TEXT_IN_PROTOCOL_TEST_REVISION    0x00010000

#define  MAX_KEY_BUFFER_SIZE                      256
#define  REPEAT_EXECUTE_OF_TEST                   30

#define  SCANCODE_EXTENDED              0xE0
#define  SCANCODE_EXTENDED1             0xE1
#define  SCANCODE_CTRL_MAKE             0x1D
#define  SCANCODE_CTRL_BREAK            0x9D
#define  SCANCODE_ALT_MAKE              0x38
#define  SCANCODE_ALT_BREAK             0xB8
#define  SCANCODE_LEFT_SHIFT_MAKE       0x2A
#define  SCANCODE_LEFT_SHIFT_BREAK      0xAA
#define  SCANCODE_RIGHT_SHIFT_MAKE      0x36
#define  SCANCODE_RIGHT_SHIFT_BREAK     0xB6
#define  SCANCODE_CAPS_LOCK_MAKE        0x3A
#define  SCANCODE_NUM_LOCK_MAKE         0x45
#define  SCANCODE_SCROLL_LOCK_MAKE      0x46

extern   EFI_EVENT              TimerEvent;
extern   UINT8                  PrintableKeyCheckingMap[][6];
extern   CHAR16                 *PrintableKeySymbol[];
extern   UINT8                  UnprintableKeyCheckingMap[][6];
extern   CHAR16                 *UnprintableKeySymbol[];

EFI_STATUS
EFIAPI
InitializeBBTestSimpleTextIn (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestSimpleTextInProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

//
// Conformance function
//

EFI_STATUS
EFIAPI
BBTestReadKeyStrokeConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
);


EFI_STATUS
EFIAPI
BBTestWaitForKeyConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Interface function
//
EFI_STATUS
EFIAPI
BBTestReadKeyStrokeFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
);

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
BBTestWaitForKeyFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Stress function
//

EFI_STATUS
EFIAPI
BBTestReadKeyStrokeManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

void
WaitTimeOrKey(
  IN  UINTN       Seconds
  );

EFI_STATUS
LocateDevicePathFromSimpleTextIn(
  IN EFI_SIMPLE_TEXT_IN_PROTOCOL         *SimpleIn,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

BOOLEAN
AutoJudge(
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

CHAR16*
ScanCodeDesc(
  IN  UINT16    ScanCode
  );

BOOLEAN
WaitTimeOrKeySimpleIn(
  IN  EFI_SIMPLE_TEXT_IN_PROTOCOL  *ConIn,
  IN  UINTN                        Seconds
  );


//
// Entry GUIDs
//

#define SIMPLE_TEXT_IN_PROTOCOL_READKEYSTROKE_CONFORMANCE_MANUAL_GUID \
  { 0xef1afcfd, 0x25df, 0x4bbe, { 0xbd, 0xfe, 0x20, 0x35, 0x81, 0x2f, 0x9c, 0x59 } }

#define SIMPLE_TEXT_IN_PROTOCOL_READKEYSTROKE_CONFORMANCE_AUTO_GUID \
  { 0xce028ac1, 0x90b, 0x4299, { 0xa9, 0x73, 0x51, 0x2c, 0x3a, 0x4d, 0x86, 0x35 } }

#define SIMPLE_TEXT_IN_PROTOCOL_WAITFORKEY_CONFORMANCE_MANUAL_GUID \
  { 0x98cb8599, 0x4aba, 0x4d7e, { 0xa6, 0x6d, 0x9d, 0xb, 0xe8, 0xb7, 0x61, 0xdb } }


#define SIMPLE_TEXT_IN_PROTOCOL_READKEYSTROKE_FUNCTION_MANUAL_GUID \
  { 0xc3ba3a6c, 0xbfd0, 0x442a, { 0xa8, 0xec, 0x51, 0x75, 0x16, 0x85, 0x75, 0x1f } }

#define SIMPLE_TEXT_IN_PROTOCOL_WAITFORKEY_FUNCTION_MANUAL_GUID \
  { 0x16f4362e, 0xac55, 0x4f87, { 0xbc, 0xf8, 0x45, 0x30, 0xba, 0x27, 0x1a, 0x33 } }


#define SIMPLE_TEXT_IN_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0x156a250f, 0xd164, 0x4305, { 0xbd, 0xfb, 0x1e, 0x62, 0xb9, 0x7f, 0x6d, 0x88 } }

#define SIMPLE_TEXT_IN_PROTOCOL_RESET_FUNCTION_MANUAL_GUID \
  { 0xf196b844, 0xa67a, 0x465e, { 0xa3, 0xdb, 0xdb, 0x43, 0xe9, 0x69, 0x7a, 0xac } }

#define SIMPLE_TEXT_IN_PROTOCOL_READWAIT_EXTENSIVE_MANUAL_GUID \
  { 0x88dab7ce, 0x6582, 0x47b2, { 0xa9, 0x8b, 0x41, 0xdc, 0x31, 0xbb, 0xf9, 0xe1 } }

#define SIMPLE_TEXT_IN_PROTOCOL_RESET_EXTENSIVE_MANUAL_GUID \
  { 0x79bfe6d2, 0x6016, 0x4112, { 0x8b, 0xb1, 0x12, 0xc7, 0x2b, 0x38, 0xa6, 0xae } }

#endif

