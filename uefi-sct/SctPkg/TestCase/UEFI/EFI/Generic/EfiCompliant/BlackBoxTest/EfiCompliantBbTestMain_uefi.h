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

  EfiCompliantBbTestMain.h

Abstract:

  EFI Compliant Black-Box Test.

--*/

#ifndef _EFI_COMPLIANT_BB_TEST_MAIN_H_
#define _EFI_COMPLIANT_BB_TEST_MAIN_H_

//
// Includes
//

#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include "Guid_uefi.h"

#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

//
// Definitions
//

#define EFI_COMPLIANT_BB_TEST_REVISION      0x00010001

// {4796995E-528F-4e7e-8BAF-FA4A931D2502}
#define EFI_COMPLIANT_BB_TEST_GUID          \
  { 0x4796995e, 0x528f, 0x4e7e, {0x8b, 0xaf, 0xfa, 0x4a, 0x93, 0x1d, 0x25, 0x02 }}

#define EFI_COMPLIANT_BB_TEST_INI_PATH      L"Dependency\\EfiCompliantBBTest"
#define EFI_COMPLIANT_BB_TEST_INI_FILE      L"EfiCompliant.Ini"

#define EFI_GLOBAL_VARIABLE \
  { 0x8BE4DF61, 0x93CA, 0x11d2, {0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C }}

#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS   0x00000020
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS              0x00000010

//
// Prototype of conformance tests
//

EFI_STATUS
EFIAPI
RequiredElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  );

EFI_STATUS
EFIAPI
PlatformSpecificElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  );

EFI_STATUS
DriverSpecificElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  );

//
// Support services
//

EFI_STATUS
OpenIniFile (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  CHAR16                              *IniPathName,
  IN  CHAR16                              *IniFileName,
  OUT EFI_INI_FILE_HANDLE                 *IniFile
  );

EFI_STATUS
CloseIniFile (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  EFI_INI_FILE_HANDLE                 IniFile
  );

//
// GUIDs for the test entry points
//

// {117C9ABC-489D-4504-ACDB-12AACE8F505B}
#define REQUIRED_ELEMENTS_BB_TEST_GUID                \
  { 0x117c9abc, 0x489d, 0x4504, {0xac, 0xdb, 0x12, 0xaa, 0xce, 0x8f, 0x50, 0x5b }}

// {A0A8BED3-3D6F-4ad8-907A-84D52EE1543B}
#define PLATFORM_SPECIFIC_ELEMENTS_BB_TEST_GUID       \
  { 0xa0a8bed3, 0x3d6f, 0x4ad8, {0x90, 0x7a, 0x84, 0xd5, 0x2e, 0xe1, 0x54, 0x3b }}

// {EED18069-2B1F-47c0-9C3C-20D5B070B84C}
#define DRIVER_SPECIFIC_ELEMENTS_BB_TEST_GUID         \
  { 0xeed18069, 0x2b1f, 0x47c0, {0x9c, 0x3c, 0x20, 0xd5, 0xb0, 0x70, 0xb8, 0x4c }}

#endif
