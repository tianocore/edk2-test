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

  Copyright (c) 2016, ARM Ltd. All rights reserved.

--*/
/*++

Module Name:

  SbbrBootServicesBBTestMain.h

Abstract:

  Contains definitions for test information and test GUIDs.

--*/

#ifndef _SBBRBOOTSERVICES_TEST_MAIN_H_
#define _SBBRBOOTSERVICES_TEST_MAIN_H_

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define SBBRBOOTSERVICES_TEST_REVISION 0x00010000

#define SBBRBOOTSERVICES_TEST_GUID \
  { 0x8dafd7a7, 0x44d0, 0x4cf4, {0x9d, 0x28, 0x9f, 0x87, 0x08, 0x0f, 0xc0, 0x91 }}

#define ACPI_TABLE_EXPECTED_LENGTH 36
#define ACPI_TABLE_CHECKSUM_LENGTH 20
#define SMBIOS30_ANCHOR_STRING "_SM3_"
#define RSDP_SIGNATURE_STRING "RSD PTR "

EFI_STATUS
InitializeBBTestSbbrBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestSbbrBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Test Case GUIDs
//

#define SBBRBOOTSERVICES_MEMORYMAP_GUID \
  { 0x8540c12d, 0x5413, 0x4a0b, {0xa5, 0x45, 0x89, 0xa8, 0xe3, 0xc7, 0xda, 0x4b }}

#define SBBRBOOTSERVICES_ACPITABLE_GUID \
  { 0x40ff8495, 0x8ae9, 0x442e, {0x89, 0xf2, 0xf8, 0x97, 0xbb, 0x7c, 0x41, 0x75 }}

#define SBBRBOOTSERVICES_SMBIOSTABLE_GUID \
  { 0xc44ca44c, 0x4f4e, 0x4760, {0x96, 0xc9, 0xb8, 0xcd, 0xe5, 0x31, 0xb4, 0xc4 }}

#endif /* _SBBRBOOTSERVICES_TEST_MAIN_H_ */
