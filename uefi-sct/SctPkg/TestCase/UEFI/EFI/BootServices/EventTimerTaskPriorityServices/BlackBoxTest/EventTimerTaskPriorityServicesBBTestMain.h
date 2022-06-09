/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EventTimerTaskPriorityServicesBBTestMain.h

Abstract:

  Test Driver of Event and Timer and Task Priority Services header file

--*/

#ifndef _EVENT_TIMER_TASK_PRIORITY_SERVICES_BB_TEST_MAIN_H
#define _EVENT_TIMER_TASK_PRIORITY_SERVICES_BB_TEST_MAIN_H

#include "Efi.h"
#include <Library/EfiTestLib.h>

#include "Guid.h"

#define EVENT_TIMER_TASK_PRIORITY_SERVICES_TEST_REVISION    0x00010000

#define EVENT_TIMER_TASK_PRIORITY_SERVICES_TEST_GUID        \
  { 0x7AB1E93F, 0xB439, 0x4e2e, {0xB7, 0x73, 0xCA, 0x54, 0x0C, 0xEB, 0xCF, 0xEF }}

#define EFI_TEST_GENERIC_FAILURE(Title, Status)             \
  StandardLib->RecordAssertion (                            \
                 StandardLib,                               \
                 EFI_TEST_ASSERTION_FAILED,                 \
                 gTestGenericFailureGuid,                   \
                 Title,                                     \
                 L"%a:%d:Status - %r",                      \
                 __FILE__,                                  \
                 (UINTN)__LINE__,                                  \
                 Status                                     \
                 );

#define MAX_TEST_EVENT_NUM    3
#define SIGNAL_CONTEXT        0xAA    //To check the buffer content is modifed by exception or not
//
// Prototypes: Test Cases
//

EFI_STATUS
EFIAPI
BBTestCreateEvent_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestCreateEvent_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)	
EFI_STATUS
EFIAPI
BBTestCreateEventEx_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestCreateEventEx_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
#endif
EFI_STATUS
EFIAPI
BBTestCloseEvent_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSignalEvent_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestCheckEvent_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestCheckEvent_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestRaiseTPL_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestRestoreTPL_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes: Support Functions
//

VOID
EFIAPI
NotifyFunction (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  );

VOID
EFIAPI
NotifyFunctionTpl (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  );

VOID
EFIAPI
NotifyFunctionTplEx (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  );

VOID
EFIAPI
NotifyFunctionSignal (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  );

VOID
EFIAPI
NotifyFunctionNoSignal (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  );

#endif
