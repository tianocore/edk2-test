/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EventTimerTaskPriorityServicesBBTestMain.c

Abstract:

  Test Driver of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Global variables
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EVENT_TIMER_TASK_PRIORITY_SERVICES_TEST_REVISION,
  EVENT_TIMER_TASK_PRIORITY_SERVICES_TEST_GUID,
  L"Event, Timer, and Task Priority Services Test",
  L"UEFI Event, Timer, and Task Priority Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    { 0x50bf9d26, 0xb53d, 0x4cff, { 0xbc, 0x10, 0xbc, 0x65, 0x81, 0xbf, 0x50, 0x9d } },
    L"CreateEvent_Conf",
    L"Conformance test for boot service CreateEvent().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCreateEvent_Conf
  },
  {
    {0x83cf7f0b, 0xc274, 0x4918, { 0xae, 0xa6, 0x41, 0x3d, 0xa9, 0xcf, 0x68, 0xcf } },
    L"CreateEvent_Func",
    L"Functional test for boot service CreateEvent().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCreateEvent_Func
  },
  {
    { 0xefbd4523, 0x10dd, 0x44b3, { 0xa5, 0x20, 0x58, 0xaf, 0x83, 0xe5, 0xbf, 0x64 } },
    L"CloseEvent_Func",
    L"Functional test for boot service CloseEvent().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCloseEvent_Func
  },
  {
    { 0x8c3860c8, 0xdf25, 0x4b8d, { 0x98, 0xb6, 0x07, 0x79, 0x1d, 0x66, 0x1f, 0x5d } },
    L"SignalEvent_Func",
    L"Functional test for boot service SignalEvent().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSignalEvent_Func
  },
  {
    { 0x69442339, 0x151e, 0x4eaa, { 0xa2, 0xb6, 0x84, 0xf7, 0x89, 0xd6, 0x0d, 0x83 } },
    L"WaitForEvent_Conf",
    L"Conformance test for boot service WaitForEvent().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestWaitForEvent_Conf
  },
  {
    { 0xa64ffbc1, 0x6b44, 0x45bb, { 0x97, 0x3a, 0x88, 0x7d, 0x91, 0xfe, 0x4a, 0x6b } },
    L"WaitForEvent_Func",
    L"Functional test for boot service WaitForEvent().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestWaitForEvent_Func
  },
  {
    { 0xc4a57d1b, 0x59cd, 0x4722, { 0xa7, 0xfe, 0xdf, 0x79, 0x44, 0x6d, 0x03, 0x32 } },
    L"CheckEvent_Conf",
    L"Conformance test for boot service CheckEvent().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCheckEvent_Conf
  },
  {
    { 0x29481844, 0xc567, 0x4a8d, { 0xb9, 0x2f, 0xd5, 0x7b, 0x32, 0xf0, 0x39, 0xb8 } },
    L"CheckEvent_Func",
    L"Functional test for boot service CheckEvent().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCheckEvent_Func
  },
  {
    { 0x0bde93b5, 0xbc1e, 0x4b6d, { 0xa9, 0x60, 0x2f, 0xbe, 0x38, 0x88, 0xad, 0xcc } },
    L"SetTimer_Conf",
    L"Conformance test for boot service SetTimer().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetTimer_Conf
  },
  {
    { 0x86baab81, 0xd547, 0x45f5, { 0xae, 0x0f, 0x86, 0x47, 0xfe, 0x91, 0x55, 0x9d } },
    L"SetTimer_Func",
    L"Functional test for boot service SetTimer().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetTimer_Func
  },
  {
    { 0xd4a835eb, 0x0830, 0x4c7a, { 0xb3, 0x06, 0x2e, 0x3e, 0xca, 0xb4, 0xa6, 0x94 } },
    L"RaiseTPL_Func",
    L"Functional test for boot service RaiseTPL().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRaiseTPL_Func
  },
  {
    { 0x8c096f99, 0x268c, 0x42fc, { 0xa6, 0xc0, 0xe1, 0x0e, 0xb7, 0x05, 0x06, 0xc0 } },
    L"RestoreTPL_Func",
    L"Functional test for boot service RestoreTPL().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRestoreTPL_Func
  },
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)	
  {
    {0xf9b16c34, 0xeab5, 0x4c9c, { 0xbe, 0x90, 0x01, 0xb1, 0x2e, 0x64, 0xf1, 0x17} },
    L"CreateEventEx_Conf",
    L"Conformance test for boot service CreateEventEx().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCreateEventEx_Conf
  },

  {
    {0x0f9fa263, 0x7396, 0x4759, { 0x8f, 0x4c, 0xef, 0xc6, 0xb6, 0xf1, 0x59, 0xb8} },
    L"CreateEventEx_Func",
    L"Functional test for boot service CreateEventEx().",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCreateEventEx_Func
  },  
#endif
#ifdef EFI_TEST_EXHAUSTIVE
  {
    { 0x01046003, 0xad0d, 0x472c, { 0xa1, 0x76, 0x06, 0x4c, 0x51, 0xd6, 0x26, 0x57 } },
    L"WaitForEvent_Stress",
    L"Stress test for boot service WaitForEvent().",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestWaitForEvent_Stress
  },
  {
    { 0x31fe9d6a, 0xda99, 0x4bee, { 0xbe, 0xad, 0xd3, 0xe7, 0x8d, 0xb9, 0x5a, 0xfb } },
    L"SetTimer_Stress",
    L"Stress test for boot service SetTimer().",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetTimer_Stress
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL                  *gBBTestProtocolInterface;
EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *gStandardLib;

//
// Unload function
//

EFI_STATUS
EFIAPI
UnloadEventTimerTaskPriorityServicesBBTest (
  IN EFI_HANDLE                   ImageHandle
  );

//
// Entry point
//
EFI_STATUS
EFIAPI
InitializeEventTimerTaskPriorityServicesBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadEventTimerTaskPriorityServicesBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadEventTimerTaskPriorityServicesBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
