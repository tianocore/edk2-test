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

  ProtocolHandlerBBTest.h

Abstract:

  head file of test driver of Protocol Handler Boot Services

--*/

#ifndef _PROTOCOL_HANDLER_BBTEST_H
#define _PROTOCOL_HANDLER_BBTEST_H


#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include "Guid.h"

#include EFI_PROTOCOL_DEFINITION (PlatformDriverOverride)

#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_REVISION  0x00010002

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_GUID      \
  { 0x58688B05, 0xF5C2, 0x4e8b, {0xA0, 0x35, 0xC2, 0x47, 0xD6, 0xA4, 0x0E, 0xB4 }}

#define INVALID_HANDLE  0xffffffff

extern EFI_HANDLE                   mImageHandle;
extern EFI_DEVICE_PATH_PROTOCOL     *mDevicePath;
extern CHAR16                       *mFilePath;

#define TPL_ARRAY_SIZE 3

extern EFI_TPL TplArray [TPL_ARRAY_SIZE];

//
// Why need to stall, need more investigation later
//
#define STALL_10_SECONDS    10000000 // in microsecond unit

#define MAX_STRING_LEN      250

#define DEPENDENCY_DIR_NAME   L"Dependency\\ProtocolHandlerServicesBBTest"


//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Consistency Test
//
#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0101 \
 { 0x6df68724, 0x5d03, 0x4555, {0x9f, 0xdc, 0xab, 0x4c, 0xe4, 0x2b, 0x45, 0x9 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0102 \
 { 0xc46151f4, 0x362f, 0x41f6, {0x8b, 0xbe, 0x81, 0xd0, 0xc6, 0xa9, 0x38, 0x1f }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0103 \
 { 0x9fef66c1, 0x3509, 0x4e88, {0x84, 0x6d, 0xb9, 0xcc, 0x26, 0x4f, 0x69, 0xbc }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0104 \
 { 0x91666998, 0x769f, 0x4075, {0x8d, 0x43, 0xc5, 0xf3, 0x91, 0x73, 0x64, 0x53 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0105 \
 { 0xb6de8de0, 0x7375, 0x4804, {0xa0, 0x29, 0x9e, 0xd0, 0xcb, 0x43, 0xf7, 0x4d }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0106 \
 { 0xdb11a27e, 0x2fc0, 0x42f0, {0xa0, 0xc6, 0xf1, 0x2b, 0xc2, 0xe2, 0x55, 0xe3 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0107 \
 { 0xa829fd94, 0xb308, 0x4b8f, {0x87, 0x3f, 0x1e, 0xaf, 0xf3, 0x54, 0x64, 0xbc }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0108 \
 { 0x6bae06d3, 0x3be7, 0x480e, {0x9e, 0x71, 0x33, 0x2a, 0xd0, 0xc8, 0x21, 0x3e }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0109 \
 { 0x231e4965, 0xfda4, 0x4fa2, {0x8a, 0xe2, 0x8c, 0x79, 0x2, 0xc5, 0x7, 0xe9 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0110 \
 { 0x852c03c5, 0x5ff1, 0x48e6, {0xa8, 0xa4, 0x49, 0x6e, 0xa1, 0x14, 0x8a, 0x33 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0111 \
 { 0x624e28e8, 0x78bc, 0x4d77, {0xab, 0x85, 0xd2, 0xcb, 0xd3, 0x74, 0x4e, 0x21 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0112 \
 { 0xf02e4084, 0x6fd5, 0x4b01, {0x8c, 0x3e, 0xac, 0xc9, 0x59, 0xfb, 0x6b, 0xa0 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0113 \
 { 0xf9df2097, 0x7c10, 0x4551, {0x91, 0x4c, 0x55, 0x11, 0x92, 0xc0, 0x19, 0x81 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0114 \
 { 0x85302e6f, 0x328b, 0x407b, {0xbd, 0x6d, 0x83, 0x5d, 0xd5, 0x4b, 0xa5, 0x4b }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0115 \
 { 0x6b57a087, 0xf432, 0x4da7, {0xab, 0x65, 0xa3, 0xbc, 0x2f, 0x2c, 0xe3, 0xf1 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0116 \
 { 0xb6c90cce, 0x9063, 0x4a76, {0xb8, 0x2d, 0xca, 0xd4, 0x19, 0x1e, 0x75, 0x14 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0117 \
 { 0x94eedbec, 0x55ca, 0x442e, {0xb9, 0x9f, 0x7, 0x88, 0xb8, 0xe5, 0x1c, 0x10 }}

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Interface Function Test
//
#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0200 \
 { 0xedc7240b, 0x6a14, 0x45d4, {0x93, 0x7b, 0xa2, 0xb6, 0x2c, 0x51, 0x12, 0x7b }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0201 \
 { 0x4aa7dd8f, 0xe3c3, 0x434d, {0xae, 0x27, 0x8c, 0x9d, 0xa6, 0x6f, 0x58, 0xa3 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0202 \
 { 0x8188cfec, 0x5094, 0x41bb, {0x89, 0x4d, 0x4f, 0x75, 0xd8, 0x42, 0xf5, 0xfc }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0203 \
 { 0xcdf41a28, 0xec2a, 0x4b25, {0x92, 0x2c, 0x77, 0xb0, 0xec, 0x18, 0xc7, 0x97 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0204 \
 { 0xb6a82616, 0xe08e, 0x4226, {0xa8, 0xe2, 0xe6, 0x91, 0x2b, 0xaa, 0x8e, 0x8c }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0205 \
 { 0x717259a7, 0x658c, 0x4616, {0xb5, 0x2c, 0x6c, 0x8f, 0x66, 0x1e, 0xa7, 0x26 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0206 \
 { 0x283ccdda, 0xd4cd, 0x4bd1, {0x8a, 0x9d, 0xa4, 0xae, 0xf1, 0xa7, 0xa2, 0x14 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0207 \
 { 0x11779290, 0x1b6e, 0x4a3f, {0xab, 0xad, 0x8, 0x16, 0xeb, 0xca, 0x6e, 0x5f }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0208 \
 { 0xa21ffa59, 0x9a2, 0x46d4, {0xa1, 0xff, 0x94, 0xd5, 0xc6, 0x6, 0x14, 0x91 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0209 \
 { 0xd689e19d, 0x54fe, 0x40dc, {0x91, 0x18, 0xb9, 0xab, 0xf2, 0xc0, 0x0, 0x48 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0210 \
 { 0xe5d3c7d0, 0x1cf8, 0x4cc1, {0x8f, 0x0, 0xcc, 0x91, 0xac, 0xf2, 0x88, 0x9e }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0211 \
 { 0x8e436aaf, 0x37e9, 0x4190, {0x8d, 0xc7, 0x57, 0x99, 0xd4, 0x76, 0x9b, 0x19 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0212 \
 { 0xc1126254, 0x8fd3, 0x4170, {0xa0, 0xa1, 0x99, 0xd4, 0xce, 0xe2, 0x14, 0xcb }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0213 \
 { 0x7a4b18a0, 0x7b00, 0x4786, {0x81, 0x28, 0x56, 0x4f, 0x3b, 0xa4, 0x1c, 0xe1 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0214 \
 { 0x4f00a0c1, 0x77bf, 0x4ce9, {0xb4, 0xa6, 0x57, 0x89, 0x76, 0xdf, 0x52, 0x88 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0215 \
 { 0xd0bb122f, 0x231e, 0x4eef, {0x94, 0xd4, 0x4e, 0x3, 0xa7, 0x9c, 0x46, 0x9d }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0216 \
 { 0x11b44246, 0xa65e, 0x4832, {0x85, 0x89, 0x8f, 0x60, 0x69, 0x29, 0xc9, 0xfb }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0217 \
 { 0x89fbae4a, 0x6132, 0x44e0, {0xbb, 0xf0, 0xb, 0x5c, 0x3c, 0xa8, 0xa2, 0xa5 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0218 \
 { 0x705e2497, 0x1b8f, 0x4307, {0x91, 0xe1, 0xf3, 0x3f, 0x2f, 0x2b, 0x55, 0x6 }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0219 \
 { 0x2aeea797, 0xc967, 0x463e, {0xbb, 0xbc, 0x1d, 0x24, 0x90, 0xd1, 0x7c, 0x91 }}

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Combination Test
//
#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0301 \
 { 0x9872d562, 0xa6dd, 0x4b02, {0x80, 0x73, 0x52, 0xe7, 0xb8, 0x21, 0xbc, 0x3d }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0302 \
 { 0x1e97fd0c, 0x1a8d, 0x4961, {0x8f, 0xa2, 0xaf, 0xb4, 0xc0, 0x8a, 0xd0, 0xaa }}

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0303 \
 { 0xc64c46fa, 0x3789, 0x4c3f, {0xbc, 0x39, 0x82, 0x36, 0xd, 0x22, 0x53, 0x27 }}

//
// Functions for MainTest.c
//
EFI_STATUS
EFIAPI
InitializeBBTestProtocolHandlerBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestProtocolHandlerBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
InitializeGlobalData ();

VOID
ReleaseGlobalData ();

///////////////////////////////////////////////////////////////////////////////
//
// Functions for Consistency Test
//

//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceConsistencyTest (
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
BBTestUninstallProtocolInterfaceConsistencyTest (
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
BBTestReinstallProtocolInterfaceConsistencyTest (
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
BBTestRegisterProtocolNotifyConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.5
//
EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.6
//
EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.7
//
EFI_STATUS
EFIAPI
BBTestLocateHandleConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.8
//
EFI_STATUS
EFIAPI
BBTestLocateHandleBufferConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.9
//
EFI_STATUS
EFIAPI
BBTestHandleProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.10
//
EFI_STATUS
EFIAPI
BBTestLocateProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.11
//
EFI_STATUS
EFIAPI
BBTestLocateDevicePathConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.12
//
EFI_STATUS
EFIAPI
BBTestProtocolsPerHandleConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.13
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.14
//
EFI_STATUS
EFIAPI
BBTestCloseProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.15
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInformationConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.16
//
EFI_STATUS
EFIAPI
BBTestConnectControllerConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.17
//
EFI_STATUS
EFIAPI
BBTestDisconnectControllerConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

///////////////////////////////////////////////////////////////////////////////
//
// Functions for Interface Function Test
//

//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTest (
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
BBTestUninstallProtocolInterfaceInterfaceTest (
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
BBTestReinstallProtocolInterfaceInterfaceTest (
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
BBTestRegisterProtocolNotifyInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.5
//
EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.6
//
EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.7
//
EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.8
//
EFI_STATUS
EFIAPI
BBTestLocateHandleBufferInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.9
//
EFI_STATUS
EFIAPI
BBTestHandleProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.10
//
EFI_STATUS
EFIAPI
BBTestLocateProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.11
//
EFI_STATUS
EFIAPI
BBTestLocateDevicePathInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.12
//
EFI_STATUS
EFIAPI
BBTestProtocolsPerHandleInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.13
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.14
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.15
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest333 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.16
//
EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.17
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInformationInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.18
//
EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.19
//
EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint Functions for InstallProtocolInterface()
//
EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for UninstallProtocolInterface()
//

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for ReinstallProtocolInterface()
//

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint11 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint12 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for ReinstallProtocolInterface()
//

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for InstallMultipleProtocolInterfaces()
//

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for UninstallMultipleProtocolInterfaces()
//

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for SctLocateHandle ()
//

EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for LocateHandleBuffer()
//

EFI_STATUS
EFIAPI
BBTestLocateHandleBufferInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestLocateHandleBufferInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestLocateHandleBufferInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for HandleProtocol()
//

EFI_STATUS
EFIAPI
BBTestHandleProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for SctLocateProtocol ()
//

EFI_STATUS
EFIAPI
BBTestLocateProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestLocateProtocolInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestLocateProtocolInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for LocateDevicePath()
//

EFI_STATUS
EFIAPI
BBTestLocateDevicePathInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for ProtocolsPerHandle()
//

EFI_STATUS
EFIAPI
BBTestProtocolsPerHandleInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest111()
//

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111CheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest222()
//

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222CheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest333
//

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest333CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest333CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest333CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for CloseProtocol
//

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for OpenProtocolInformation
//

EFI_STATUS
EFIAPI
BBTestOpenProtocolInformationInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for ConnectController()
//

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint7_13 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint11 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint12 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint14 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint15 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTestCheckPoint16 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for DisconnectController()
//

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

///////////////////////////////////////////////////////////////////////////////
//
// Functions for Combination Test
//

//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestCombinationTest1 (
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
BBTestCombinationTest2 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
EFIAPI
BBTestCombinationTest3 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint Functions
//

EFI_STATUS
EFIAPI
BBTestCombinationTest2CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCombinationTest2CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCombinationTest2CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCombinationTest2CheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );


#endif
