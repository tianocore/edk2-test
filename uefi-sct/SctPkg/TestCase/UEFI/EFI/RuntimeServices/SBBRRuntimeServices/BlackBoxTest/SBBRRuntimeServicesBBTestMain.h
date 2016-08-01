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

  SBBRRuntimeServicesBBTestMain.h

Abstract:

  Header file for SBBRRuntimeServicesBBTestMain.c.

--*/

#ifndef _SBBRRUNTIMESERVICES_TEST_MAIN_H_
#define _SBBRRUNTIMESERVICES_TEST_MAIN_H_

#include "Efi.h"

#define SBBRRUNTIMESERVICES_TEST_REVISION 0x00010000

#define SBBRRUNTIMESERVICES_TEST_GUID     \
  { 0x52A69BBF, 0xE19F, 0x4e82, {0x93, 0xD6, 0xAA, 0xC4, 0x6E, 0x2E, 0x1E, 0x06 }}

EFI_STATUS
InitializeBBTestSBBRRuntimeServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestSBBRRuntimeServices (
  IN EFI_HANDLE       ImageHandle
  );

//
// Entry GUIDs
//

#define SBBRRUNTIMESERVICES_TEST_CASE_GUID \
  { 0xe867fa15, 0x942b, 0x4c69, {0xad, 0xee, 0xf9, 0x3b, 0x11, 0x71, 0xd0, 0x8c }}

#endif /* _SBBRRUNTIMESERVICES_TEST_MAIN_H_ */
