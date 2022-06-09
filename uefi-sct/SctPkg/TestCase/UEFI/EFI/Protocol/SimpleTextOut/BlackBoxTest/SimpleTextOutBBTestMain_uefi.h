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

  SimpleTextOutBBTestMain_uefi.h

Abstract:

  BB test header file of Simple Text Output Protocol

--*/


#ifndef _BBTEST_SIMPLE_TEXT_OUTPUT_MAIN_H
#define _BBTEST_SIMPLE_TEXT_OUTPUT_MAIN_H

#include <Base.h>
#include "SctLib.h"
#include "Guid_uefi.h"
#include <UEFI/Protocol/SimpleTextOut.h>
#include EFI_PROTOCOL_DEFINITION (GraphicsOutput)

#include <Library/EfiTestLib.h>

extern   EFI_EVENT               TimerEvent;
extern   CHAR16                  *mAttribStr[];

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_TEST_REVISION 0x00010001

EFI_STATUS
EFIAPI
InitializeBBTestSimpleTextOutput (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestSimpleTextOutputProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
BBTestResetFunctionManualTest (
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
BBTestOutputStringFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestOutputStringFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestTestStringFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestQueryModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetModeFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetAttributeFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetAttributeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestClearScreenFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestClearScreenFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetCursorPositionFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetCursorPositionFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEnableCursorFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEnableCursorFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Conformance test function definition
//
EFI_STATUS
BBTestQueryModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetAttributeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetCursorPositionConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Associatianal function
//

VOID
CopyUnicodeString (
  IN CHAR16                     *Destination,
  IN CHAR16                     *Source
  ) ;

UINTN
PrintXY (
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL                    *ForeGround,  OPTIONAL
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL                    *BackGround,  OPTIONAL
  IN CHAR16                           *Fmt
  );

UINTN
_IPrint (
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL            *GraphicsOutput,
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL     *Sto,
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL                    *Foreground,
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL                    *Background,
  IN CHAR16                           *fmt
  );


BOOLEAN
AutoJudge(
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

BOOLEAN
AutoJudgeUga(
  IN  UINTN         X,
  IN  UINTN         Y,
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );


VOID
BackupMode(
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut,
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE          *SavedMode
  );

EFI_STATUS
RestoreMode(
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut,
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE          *SavedMode,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
LocateDevicePathFromSimpleTextOut(
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
LocateGopFromSimpleTextOut (
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL           **GraphicsOutput,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

BOOLEAN
CheckModeIntegrity (
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE          *ModeExpected,
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE          *Mode
  );

VOID
WaitTimeOrKey(
  IN  UINTN       Seconds
  );

//
// Entry GUIDs
//


#define SIMPLE_TEXT_OUTPUT_PROTOCOL_RESET_FUNCTION_MANUAL_GUID \
  { 0x407000e0, 0xfc55, 0x43c3, { 0x8b, 0xca, 0x91, 0x52, 0xff, 0x6c, 0xb5, 0xd7 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0x36bdbf05, 0x2759, 0x49ca, { 0xb1, 0x28, 0xbe, 0x19, 0xbe, 0x46, 0xef, 0x6f } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_OUTPUTSTRING_FUNCTION_AUTO_GUID \
  { 0xa50a89d5, 0x89c1, 0x4214, { 0x80, 0x96, 0x08, 0xc8, 0x79, 0x10, 0x97, 0x6f } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_OUTPUTSTRING_FUNCTION_MANUAL_GUID \
  { 0x2d87f604, 0xafb4, 0x4699, { 0xab, 0x40, 0xe8, 0x8f, 0x7a, 0x7c, 0x25, 0x35 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_TESTSTRING_FUNCTION_AUTO_GUID \
  { 0xc6a4f228, 0xe80a, 0x42f9, { 0xb8, 0x78, 0x41, 0x3f, 0xf, 0x99, 0x6c, 0x11 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_QUERYMODE_FUNCTION_AUTO_GUID \
  { 0xd493e3fd, 0x6b56, 0x4f8e, { 0xba, 0x45, 0x60, 0x6d, 0xe, 0x8f, 0x56, 0x71 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_FUNCTION_MANUAL_GUID \
  { 0x37c4b95e, 0xca9d, 0x41f7, { 0xa2, 0x82, 0xe6, 0xe0, 0xfd, 0x8c, 0x4, 0x26 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_FUNCTION_AUTO_GUID \
  { 0x6fa016c7, 0x428, 0x4997, { 0x86, 0xfa, 0x8f, 0x5, 0xa1, 0x26, 0x5d, 0xc8 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_FUNCTION_MANUAL_GUID \
  { 0xe0927716, 0xf982, 0x4400, { 0xbc, 0xbd, 0xfa, 0x2f, 0x84, 0x8c, 0x20, 0x41 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_FUNCTION_AUTO_GUID \
  { 0x7937289, 0x8337, 0x4b7b, { 0xac, 0xe9, 0x91, 0x82, 0x70, 0x4f, 0xcb, 0xe8 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_CLEARSCREEN_FUNCTION_MANUAL_GUID \
  { 0x80be8c23, 0xffba, 0x4ff7, { 0x8c, 0x47, 0x77, 0x42, 0xdf, 0xdc, 0xc0, 0x59 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_CLEARSCREEN_FUNCTION_AUTO_GUID \
  { 0xd3533d69, 0x75a9, 0x46e0, { 0x9f, 0x50, 0xa5, 0x56, 0x23, 0x2f, 0x43, 0x90 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_FUNCTION_MANUAL_GUID \
  { 0x60fb69a4, 0x9eb4, 0x4d2d, { 0xb8, 0x51, 0xe7, 0x7, 0x13, 0x22, 0x65, 0x99 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_FUNCTION_AUTO_GUID \
  { 0x87f03e4b, 0x37de, 0x4c91, { 0xa6, 0xde, 0x33, 0x56, 0xe2, 0x45, 0xe2, 0xc5 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_ENABLECURSOR_FUNCTION_MANUAL_GUID \
  { 0x48870327, 0xa599, 0x4622, { 0xbf, 0xaa, 0xa0, 0x17, 0x57, 0x14, 0xe3, 0xb8 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_ENABLECURSOR_FUNCTION_AUTO_GUID \
  { 0x4558978e, 0xf938, 0x424e, { 0xb3, 0xa4, 0x48, 0xd4, 0xef, 0xa5, 0x22, 0xa5 } }

//
// Conformance test function entrance guid
//

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_QUERYMODE_CONFORMANCE_AUTO_GUID \
  { 0x64f2e0f9, 0x87c6, 0x4d4e, { 0xbb, 0x4, 0x2d, 0x4e, 0x60, 0xfa, 0x29, 0xa5 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_CONFORMANCE_AUTO_GUID \
  { 0x37f5c015, 0xe5a2, 0x4089, { 0xa9, 0x4b, 0xcc, 0x97, 0x21, 0xa8, 0x1c, 0x2d } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_CONFORMANCE_AUTO_GUID \
  { 0x33b78449, 0xcfb9, 0x4fb7, { 0xbe, 0xa2, 0x81, 0x90, 0xa, 0x64, 0x70, 0x24 } }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_CONFORMANCE_AUTO_GUID \
  { 0xb07194f2, 0xe025, 0x42eb, { 0xb9, 0xe4, 0x96, 0x4a, 0x4f, 0xa6, 0x4c, 0x8c } }

#endif

