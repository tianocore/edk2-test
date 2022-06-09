/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Phoenix Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AuthenticationBBTestMain.h

Abstract:

  Test Driver of Authentication Protocol

--*/

#ifndef __EFI_LOAD_FILE_TEST_H__
#define __EFI_LOAD_FILE_TEST_H__


#include "SctLib.h"
#include "AuthenticationGuid.h"
#include <Library/EfiTestLib.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#define AUTH_TEST_REVISION 0x00010000

#define AUTH_FUNCTION_TEST_GUID \
  { 0x7671d9d0, 0x53db, 0x4173, {0xaa, 0x69, 0x23, 0x27, 0xf2, 0x1f, 0x0b, 0xc7 }}
  
extern EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;

EFI_STATUS
EFIAPI
InitializeAuthenticationTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadAuthenticationTest (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
EFIAPI
BBTestAuthenticationFunctionTestA (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestAuthenticationFunctionTestB(
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

VOID
AuthenticationTestWaitForAnyInput (
  );

#endif
