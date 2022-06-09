/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AcpiTableBBTestMain.h

Abstract:

  Test Driver of Acpi Table Protocol header file

--*/

#ifndef _SIMPLE_TEXT_INPUT_EX_BB_TEST_MAIN
#define _SIMPLE_TEXT_INPUT_EX_BB_TEST_MAIN

#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/SimpleTextInEx.h>
#include "Guid.h"


#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x50efbf91, 0xea77, 0x468b, { 0xa5, 0xda, 0xc9, 0x81, 0x3d, 0x99, 0xac, 0x4 } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x94ab132a, 0xd623, 0x418d, { 0xb4, 0x70, 0x7b, 0x1b, 0x9c, 0x9, 0x5b, 0xa3 } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x93911458, 0x49af, 0x43dd, { 0xa8, 0x63, 0xec, 0x99, 0xc5, 0x74, 0x7c, 0x34 } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x64e98cea, 0xe8dc, 0x4e84, { 0x87, 0x96, 0xed, 0x59, 0x34, 0x42, 0x8b, 0x1e } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0x44400ba3, 0xc903, 0x4763, { 0x80, 0x9d, 0xf2, 0x5a, 0x53, 0xcf, 0x17, 0xc5 } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0106 \
{ 0xdbc6e659, 0xb0e0, 0x4471, { 0x94, 0x13, 0x45, 0x1b, 0xdc, 0xe2, 0xad, 0xc7 } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0107 \
{ 0x2c3ca282, 0x5644, 0x41b6, { 0xaf, 0xc9, 0x43, 0x87, 0xf2, 0x53, 0x89, 0xbd } }
//
// Entry GUIDs for Conf Test
//
#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xbf81459a, 0xc896, 0x4e68, { 0xa3, 0x3c, 0x41, 0xca, 0xe1, 0x10, 0x61, 0x8 } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x5b40a8a9, 0xf77a, 0x4134, { 0x9f, 0xf1, 0x41, 0x77, 0x20, 0xb7, 0x65, 0xb4 } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x4cff3a2d, 0x9dd0, 0x485b, { 0x83, 0xd7, 0x4e, 0xc2, 0xda, 0x93, 0xc0, 0xb9 } }

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0x4a1ed648, 0x8328, 0x4e1c, { 0xb6, 0x4a, 0xaf, 0xc3, 0xf4, 0x6, 0x6f, 0xaf } }

extern BOOLEAN BeenExecuted;

typedef enum {
  PC_ANSI                             = 0,
  VT_100,
  VT_100_PLUS,
  VT_UTF8
} TYPE_OF_TERMINAL;


//
//
//
EFI_STATUS
EFIAPI
InitializeSimpleTextInputExBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
EFIAPI
UnloadSimpleTextInputExBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
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
BBTestReadKeyStrokeExFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestSetStateFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestSetStateConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestResetFunctionAutoTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestResetFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );
  
  
EFI_STATUS
EFIAPI
BBTestSetStateFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );
  

EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExFunctionAutoTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestSetStateConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );
  
  
EFI_STATUS
EFIAPI
BBTestSetStateConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  );
  

//
//
//
BOOLEAN
WaitTimeOrKey (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *SimpleTextInputEx,
  IN  UINTN                        Seconds
  );
  
  
BOOLEAN
AutoJudge (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *SimpleTextInputEx,
  IN  UINTN                              Seconds,
  IN  BOOLEAN                            Default,
  IN  CHAR16                             *Message
  );


CHAR16*
ScanCodeDesc (
  IN  UINT16    ScanCode
  );
  

EFI_STATUS
KeyStatePrint (
  IN EFI_KEY_STATE KeyState
);
  
  
EFI_STATUS
EFIAPI
TestRegisterNotifyFunction (
  IN EFI_KEY_DATA *KeyData
);


EFI_STATUS
EFIAPI
FunctionTestNotifyFunction (
  IN EFI_KEY_DATA *KeyData
);


EFI_STATUS
LocateDevicePathFromSimpleTextInputEx (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *SimpleTextInputEx,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );


BOOLEAN
IsATerminalDevice (
  IN CHAR16 *DevicePathStr
  );

BOOLEAN
IsTerminalDevicePath (
  IN  EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  OUT TYPE_OF_TERMINAL         *Termi,
  OUT UINTN                    *Com
  );

#endif
