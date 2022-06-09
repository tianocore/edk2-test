/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  TimeServicesBBTestMain.h

Abstract:

  BB test header file of Time Services

--*/


#ifndef _TIME_SERVICES
#define _TIME_SERVICES

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#define TIME_SERVICES_TEST_REVISION 0x00010000

#define TIME_SERVICES_TEST_GUID     \
  { 0x0C1D662C, 0xEA60, 0x48f5, {0x9D, 0x77, 0x22, 0xF8, 0x53, 0x49, 0x9C, 0x4A }}

#define TPL_ARRAY_SIZE 2

extern EFI_TPL TplArray[TPL_ARRAY_SIZE];

//
// Prototypes of Consistency Test
//

//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestGetTimeConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestSetTimeConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.3
//
EFI_STATUS
EFIAPI
BBTestGetWakeupTimeConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.4
//
EFI_STATUS
EFIAPI
BBTestSetWakeupTimeConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Interface Test
//

//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestGetTimeInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestSetTimeInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestGetWakeupTimeInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.4
//
EFI_STATUS
EFIAPI
BBTestSetWakeupTimeInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Combination Test
//

//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestGetTimeStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
EFIAPI
BBTestGetWakeupTimeStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Internal Functions
//
BOOLEAN
TimeFieldsValid (
  IN EFI_TIME *Time
  );

void AddOneHour (
  IN OUT EFI_TIME   *Time
  );

EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  **RecoveryLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  );

INTN
CompareTime (
  IN EFI_TIME   From,
  IN EFI_TIME   To
  );

//
// Entry GUIDs
//

#define TIME_SERVICES_GETTIME_CONSISTENCY_GUID \
  { 0xc3756910, 0x91b4, 0x4bbf, {0xbf, 0x40, 0x33, 0x15, 0xf1, 0x3c, 0x2d, 0x4d }}

#define TIME_SERVICES_SETTIME_CONSISTENCY_GUID \
  { 0xa8821b44, 0x6ce4, 0x462a, {0xbc, 0xd9, 0x52, 0x7b, 0x1a, 0x22, 0xaf, 0x13 }}

#define TIME_SERVICES_GETWAKEUPTIME_CONSISTENCY_GUID \
  { 0x735ba337, 0x2a44, 0x46a2, {0xaf, 0xab, 0xaf, 0xbe, 0xd7, 0x35, 0x8f, 0x8 }}

#define TIME_SERVICES_SETWAKEUPTIMEL_CONSISTENCY_GUID \
  { 0x8721b500, 0xf13a, 0x40fa, {0x82, 0x17, 0x70, 0xac, 0xdd, 0xdc, 0x67, 0xbf }}

#define TIME_SERVICES_GETTIME_INTERFACE_GUID \
  { 0x7f27237a, 0xd0f7, 0x451e, {0xbd, 0xa9, 0xf6, 0x36, 0x59, 0x15, 0xff, 0x15 }}

#define TIME_SERVICES_SETTIME_INTERFACE_GUID \
  { 0x603b46be, 0x7e14, 0x408a, {0x93, 0xd7, 0xdd, 0x9d, 0xec, 0x73, 0x29, 0x68 }}

#define TIME_SERVICES_GETWAKEUPTIME_INTERFACE_GUID \
  { 0xf508572d, 0x74f7, 0x4c6c, {0x9c, 0xef, 0xdb, 0xa4, 0x9c, 0x56, 0xf7, 0xae }}

#define TIME_SERVICES_SETWAKEUPTIME_INTERFACE_GUID \
  { 0x8a878bfb, 0x6be1, 0x4226, {0x8f, 0x69, 0x4e, 0xbf, 0x7a, 0x1f, 0xf9, 0xa5 }}

#define TIME_SERVICES_GETTIME_STRESS_TEST_GUID \
  { 0x82dd03eb, 0xa5f7, 0x4ac8, {0x80, 0x5d, 0x45, 0xa0, 0x88, 0x44, 0x70, 0x48 }}

#define TIME_SERVICES_GETWAKEUPTIME_STRESS_TEST_GUID \
  { 0x4f2569ef, 0xe9f, 0x462d, {0xb4, 0xe6, 0xe9, 0x26, 0x6a, 0x18, 0x0, 0x33 }}

#endif
