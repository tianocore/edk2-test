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

#define IHV_SIMPLE_TEXT_OUT_PROTOCOL_GUID         \
  { 0x3395ddfa, 0xb843, 0x4fb2, 0xbc, 0x81, 0x10, 0xab, 0x95, 0xff, 0x87, 0x34 }

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
  { 0x109b9d48, 0x4636, 0x45d4, 0x8d, 0x92, 0x6a, 0xc3, 0x16, 0x58, 0xdd, 0xe7 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0x865d41c1, 0x7c9c, 0x4aa4, 0xb5, 0x05, 0xba, 0xc7, 0xc3, 0x33, 0x22, 0x22 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_OUTPUTSTRING_FUNCTION_AUTO_GUID \
  { 0x61276254, 0x3af3, 0x4e3d, 0x88, 0x55, 0x6c, 0x91, 0x94, 0x81, 0x70, 0xd3 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_OUTPUTSTRING_FUNCTION_MANUAL_GUID \
  { 0xcb3c98d7, 0x145c, 0x4414, 0x94, 0x4a, 0xf4, 0x35, 0xc3, 0xdf, 0xce, 0xe7 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_TESTSTRING_FUNCTION_AUTO_GUID \
  { 0x4dc47aaa, 0x96de, 0x4fa5, 0xb4, 0xa3, 0xd7, 0x34, 0xb2, 0xf0, 0xfd, 0x68 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_QUERYMODE_FUNCTION_AUTO_GUID \
  { 0x0295ac30, 0xf1b5, 0x490e, 0xaa, 0x6b, 0x8b, 0x8f, 0xdf, 0xa6, 0xeb, 0x81 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_FUNCTION_MANUAL_GUID \
  { 0x6a2742eb, 0xd381, 0x499b, 0x89, 0x0c, 0x18, 0x00, 0xf6, 0xe6, 0xb7, 0x68 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_FUNCTION_AUTO_GUID \
  { 0x100a6917, 0x8e80, 0x41f7, 0xac, 0xc4, 0x3c, 0xb1, 0xe2, 0x39, 0x77, 0x3c }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_FUNCTION_MANUAL_GUID \
  { 0x3674ddc6, 0x1c10, 0x400c, 0x9e, 0x2c, 0xec, 0xad, 0xbb, 0x27, 0x14, 0xfd }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_FUNCTION_AUTO_GUID \
  { 0xecde876e, 0xfd57, 0x4852, 0xad, 0x4f, 0x65, 0xaf, 0xa7, 0xea, 0x92, 0x89 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_CLEARSCREEN_FUNCTION_MANUAL_GUID \
  { 0x75317e38, 0x630a, 0x49d5, 0x95, 0x99, 0x30, 0x65, 0x4e, 0x31, 0xb3, 0x8a }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_CLEARSCREEN_FUNCTION_AUTO_GUID \
  { 0x741c63f6, 0x36b5, 0x476a, 0xbf, 0x31, 0xb9, 0xcf, 0xe6, 0x92, 0x61, 0xae }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_FUNCTION_MANUAL_GUID \
  { 0x572a09de, 0xfdce, 0x443f, 0x91, 0x03, 0xb4, 0x7c, 0xd3, 0x31, 0xba, 0x09 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_FUNCTION_AUTO_GUID \
  { 0x0e84faf9, 0xf09c, 0x42f4, 0xa2, 0x02, 0xc1, 0x0a, 0xde, 0xa1, 0x56, 0xab }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_ENABLECURSOR_FUNCTION_MANUAL_GUID \
  { 0xd29726e1, 0x549f, 0x4b7e, 0x96, 0xdd, 0x05, 0x3b, 0xe5, 0x9b, 0xff, 0x5d }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_ENABLECURSOR_FUNCTION_AUTO_GUID \
  { 0x4588b556, 0x52d4, 0x4371, 0x94, 0x69, 0x05, 0x70, 0xa4, 0xef, 0x6e, 0x6a }

//
// Conformance test function entrance guid
//

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_QUERYMODE_CONFORMANCE_AUTO_GUID \
  { 0x35fefe7c, 0xf968, 0x4d79, 0x83, 0x6c, 0x2e, 0x24, 0xa8, 0x68, 0xb2, 0x5b }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_CONFORMANCE_AUTO_GUID \
  { 0x49bb4116, 0xb4c6, 0x45fb, 0xa3, 0x5d, 0x35, 0x71, 0x06, 0xf7, 0xae, 0x97 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_CONFORMANCE_AUTO_GUID \
  { 0x602ea53a, 0xec31, 0x4bde, 0x96, 0x4f, 0x34, 0x6e, 0x8a, 0x0a, 0xda, 0x36 }

#define SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_CONFORMANCE_AUTO_GUID \
  { 0x1ed228e3, 0xd381, 0x45fa, 0xb0, 0x1f, 0x9a, 0xd7, 0xf3, 0xac, 0x53, 0xfd }

#endif

