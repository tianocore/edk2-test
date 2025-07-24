/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright 2025, Arm Ltd.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  SecureBootBBTestMain.h

Abstract:
  Header file for Secure Boot Black-Box Test.

--*/

#ifndef _SECURE_BOOT_BB_TEST_MAIN_H
#define _SECURE_BOOT_BB_TEST_MAIN_H

//
// Includes
//
#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

//
// Definitions
//

#define SECURE_BOOT_BB_TEST_REVISION    0x00010000

#define DEF_SECURE_VARS_NUM 4
#define MAX_VAR_NAME_LEN    1024

typedef struct {
  CHAR16    Name[MAX_VAR_NAME_LEN];
  UINT32   Attributes;
  EFI_GUID TestAssertionGuid;
} VARIABLE_DATA;

#define SECURE_BOOT_BB_TEST_GUID        \
  { 0xCBADA58E, 0xA1AA, 0x45DF, {0xBD, 0xDF, 0xF9, 0xBA, 0x12, 0x92, 0xF8, 0x87 }}

#define MAX_BUFFER_SIZE                       256

#define VARIABLE_ATTRIBUTES_TEST_GUID \
  { 0xE39747C4, 0x22D0, 0x4D52, {0x9C, 0x15, 0x3C, 0x4E, 0xFA, 0x80, 0xE6, 0xC8 }}

#define VARIABLE_UPDATES_TEST_GUID \
  { 0x495CB6D7, 0x0817, 0x4015, {0xA4, 0x79, 0x0D, 0xB4, 0xC2, 0x30, 0x86, 0x26 }}

#define IMAGE_LOADING_TEST_GUID \
  { 0xBA4A8DD9, 0x2D6A, 0x43A6, {0x96, 0xCF, 0x79, 0x47, 0x89, 0x2B, 0x73, 0x59 }}


#define EFI_TEST_GENERIC_FAILURE(Title, Status)             \
  StandardLib->RecordAssertion (                            \
                 StandardLib,                               \
                 EFI_TEST_ASSERTION_FAILED,                 \
                 gTestGenericFailureGuid,                   \
                 Title,                                     \
                 L"%a:%d:Status - %r",                      \
                 __FILE__,                                  \
                 (UINTN)__LINE__,                           \
                 Status                                     \
                 );

//
// Prototypes
//
EFI_STATUS
VariableAttributesTest(
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
VariableUpdatesTest(
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
ImageLoadingTest(
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Support functions
//
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL   **ProfileLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  );

#endif
