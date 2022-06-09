/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>

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

#define  IHV_SIMPLE_TEXT_IN_PROTOCOL_GUID         \
  { 0x30794d5d, 0xdba9, 0x44ed, 0xae, 0xaf, 0xaf, 0x61, 0x49, 0x93, 0x7c, 0x9f }

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
BBTestSimpleTextInProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

//
// Conformance function
//

EFI_STATUS
BBTestReadKeyStrokeConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
);


EFI_STATUS
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
BBTestReadKeyStrokeFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
);

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
  { 0x6e0503cb, 0xe13b, 0x4fa8, 0xbc, 0xf5, 0xa5, 0x43, 0xcb, 0x3b, 0x59, 0x51 }

#define SIMPLE_TEXT_IN_PROTOCOL_READKEYSTROKE_CONFORMANCE_AUTO_GUID \
  { 0x63d6f19c, 0xf1d4, 0x44c1, 0x81, 0xbe, 0x7a, 0x8e, 0x36, 0x1d, 0x1f, 0x05 }

#define SIMPLE_TEXT_IN_PROTOCOL_WAITFORKEY_CONFORMANCE_MANUAL_GUID \
  { 0xce330c06, 0xf769, 0x451d, 0x8f, 0x1b, 0xf0, 0xa4, 0x10, 0xf5, 0x23, 0x53 }


#define SIMPLE_TEXT_IN_PROTOCOL_READKEYSTROKE_FUNCTION_MANUAL_GUID \
  { 0x18b2429e, 0x875c, 0x426e, 0x9d, 0x9e, 0xbd, 0xe9, 0x27, 0xe4, 0xa6, 0x96 }

#define SIMPLE_TEXT_IN_PROTOCOL_WAITFORKEY_FUNCTION_MANUAL_GUID \
  { 0xdc161000, 0xecad, 0x4732, 0xb0, 0xb5, 0xe3, 0x96, 0xbf, 0x6e, 0x40, 0x86 }


#define SIMPLE_TEXT_IN_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0xe57b0a7c, 0x5a2c, 0x4b7f, 0x89, 0xeb, 0x5d, 0xb7, 0x00, 0xe5, 0xe1, 0xce }

#define SIMPLE_TEXT_IN_PROTOCOL_RESET_FUNCTION_MANUAL_GUID \
  { 0x989003d2, 0x839c, 0x4087, 0xa6, 0x6f, 0xed, 0x14, 0xde, 0x29, 0x4e, 0xda }

#define SIMPLE_TEXT_IN_PROTOCOL_READWAIT_EXTENSIVE_MANUAL_GUID \
  { 0x93f6fe85, 0x4f9b, 0x420a, 0x89, 0x1c, 0x46, 0xbd, 0xb0, 0x08, 0xf9, 0x36 }

#define SIMPLE_TEXT_IN_PROTOCOL_RESET_EXTENSIVE_MANUAL_GUID \
  { 0x5e61681e, 0x2bc7, 0x4c96, 0xa8, 0x8c, 0xa0, 0x53, 0xb3, 0x7a, 0x4e, 0xe7 }

#endif

