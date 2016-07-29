/*++
  The material contained herein is not a license, either
  expressly or impliedly, to any intellectual property owned
  or controlled by any of the authors or developers of this
  material or to any contribution thereto. The material
  contained herein is provided on an "AS IS" basis and, to the
  maximum extent permitted by applicable law, this information
  is provided AS IS AND WITH ALL FAULTS, and the authors and
  developers of this material hereby disclaim all other
  warranties and conditions, either express, implied or
  statutory, including, but not limited to, any (if any)
  implied warranties, duties or conditions of merchantability,
  of fitness for a particular purpose, of accuracy or
  completeness of responses, of results, of workmanlike
  effort, of lack of viruses and of lack of negligence, all
  with regard to this material and any contribution thereto.
  Designers must not rely on the absence or characteristics of
  any features or instructions marked "reserved" or
  "undefined." The Unified EFI Forum, Inc. reserves any
  features or instructions so marked for future definition and
  shall have no responsibility whatsoever for conflicts or
  incompatibilities arising from future changes to them. ALSO,
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY
  CONTRIBUTION THERETO.

  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF
  THE POSSIBILITY OF SUCH DAMAGES.

  Copyright 2006 - 2016 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2016, ARM Corporation. All rights reserved.<BR>

--*/
/*++

Module Name:

  SysEnvConfigBBTestMain.h

Abstract:

  Contains definitions for test information and test GUIDs.

--*/

#ifndef _SYSENVCONFIG_TEST_MAIN_H_
#define _SYSENVCONFIG_TEST_MAIN_H_

#include <Library/EfiTestLib.h>

#define SYSENVCONFIG_TEST_REVISION 0x00010000

#define SYSENVCONFIG_TEST_GUID     \
  {0xd84a6430, 0x99f5, 0x4660, {0x84, 0x54, 0x6e, 0x4c, 0x89, 0x6a, 0x7e, 0x51}}

EFI_STATUS
InitializeBBTestSysEnvConfig (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestBootSysEnvConfig (
  IN EFI_HANDLE       ImageHandle
  );

//
// Entry GUIDs
//

#define SYSENVCONFIG_BOOT_EXC_LEVEL_GUID \
  {0x591cb467, 0x530b, 0x4b16, {0xb0, 0x90, 0xc6, 0xce, 0xfa, 0xfc, 0xc1, 0x56}}

#define SYSENVCONFIG_MEM_ADDR_ALIGNMENT_GUID \
  {0xe24959d0, 0x9539, 0x4c7b, {0xbd, 0xbc, 0x12, 0x2a, 0xc5, 0xe9, 0xef, 0xd8}}

#define SYSENVCONFIG_OS_DISK_FORMAT_GUID \
  {0x78f530dd, 0xfe16, 0x4daf, {0xa2, 0x01, 0xbc, 0xb9, 0x37, 0x15, 0x03, 0xa2}}

#define SYSENVCONFIG_EBC_INTERPRETER_PRESENT_GUID \
  {0xff469a32, 0x6d0a, 0x4a99, {0x8b, 0x1e, 0xd1, 0x37, 0x50, 0x34, 0x08, 0xb6}}


#endif /* _SYSENVCONFIG_TEST_MAIN_H_ */
