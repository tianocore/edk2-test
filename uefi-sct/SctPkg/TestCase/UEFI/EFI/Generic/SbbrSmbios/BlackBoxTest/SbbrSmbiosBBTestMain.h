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

  Copyright (c) 2016, ARM LTD. All rights reserved.

--*/
/*++

Module Name:

  SbbrSmbiosBBTestMain.h

Abstract:

  Contains definitions for test information and test GUIDs.

--*/

#ifndef _SBBRSMBIOS_TEST_MAIN_H_
#define _SBBRSMBIOS_TEST_MAIN_H_

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define SBBRSMBIOS_TEST_REVISION 0x00010000

#define SBBRSMBIOS_TEST_GUID     \
  { 0x852e92eb, 0xd7aa, 0x4d61, {0x84, 0xef, 0xd3, 0x2d, 0xc5, 0xd5, 0x45, 0xec }}

#define SBBRSMBIOS_MAJOR_VERSION 3

EFI_STATUS
InitializeBBTestSbbrSmbios (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestSbbrSmbiosUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Entry GUIDs
//

#define SBBRSMBIOS_UEFISMBIOS_GUID \
  { 0x71b32221, 0x8b9d, 0x4b41, {0x8b, 0x04, 0xee, 0x6d, 0x18, 0xa6, 0xe5, 0x25 }}

#endif /* _SBBRSMBIOS_TEST_MAIN_H_ */
