/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ResetNotificationBBTestMain.h

Abstract:

  Test Driver of Reset Notification Protocol header file

--*/

#ifndef _RESET_NOTIFICATION_BB_TEST_MAIN_
#define _RESET_NOTIFICATION_BB_TEST_MAIN_

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/ResetNotification.h>
#include "Guid.h"


#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)


#define EFI_RESET_NOTIFICATION_PROTOCOL_TEST_REVISION    0x00010000

#define TEST_VENDOR_GUID                         \
  { 0xF6FAB04F, 0xACAF, 0x4af3, { 0xB9, 0xFA, 0xDC, 0xF9, 0x7F, 0xB4, 0x42, 0x6F } }


#define MAX_BUFFER_SIZE    1024

//
// Entry GUIDs for Func Test
//
#define EFI_RESET_NOTIFICATION_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x5b16218b, 0xfd90, 0x40f0, { 0x88, 0xfe, 0x4e, 0x9e, 0x44, 0xe1, 0x24, 0x74 } }

#define EFI_RESET_NOTIFICATION_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0xee5b57b0, 0xaad3, 0x49c7, { 0x96, 0xbf, 0x25, 0xdf, 0x42, 0x2f, 0x27, 0xa4 } }
//
// Entry GUIDs for Conf Test
//
#define EFI_RESET_NOTIFICATION_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x91d30199, 0x63c9, 0x4d1e, { 0x93, 0x97, 0xd2, 0x29, 0x3, 0xce, 0x0, 0x69 } }

#define EFI_RESET_NOTIFICATION_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x3b8f4c78, 0xab7a, 0x4d93, { 0x9c, 0x2, 0xa, 0x3f, 0x6e, 0x16, 0xd1, 0xd6 } }


extern EFI_GUID    gTestVendorGuid;
extern CHAR16      *VariableName;
extern UINT32      Attributes;

//
//
//
EFI_STATUS
EFIAPI
InitializeResetNotificationBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
UnloadResetNotificationBBTest (
  IN EFI_HANDLE                   ImageHandle
  ); 
  
//
//Test Cases
//
EFI_STATUS
BBTestRegisterResetNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestUnregisterResetNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
EFI_STATUS
BBTestRegisterResetNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestUnregisterResetNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

/**
 *  Support function - Get test support protocol library.
 *  @param SupportHandle  A handle containing support protocols.
 *  @param StandardLib    A pointer to Standard Test Support Protocol.
 *  @param RecoveryLib    A pointer to Test Recovery Support Protocol.
 *  @param LoggingLib     A pointer to Test Logging Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  **RecoveryLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  );


VOID
EFIAPI
TestOnReset (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  );


#endif

