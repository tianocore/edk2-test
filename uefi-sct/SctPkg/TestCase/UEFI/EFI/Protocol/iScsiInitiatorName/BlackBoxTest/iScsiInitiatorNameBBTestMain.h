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

    iScsiInitiatorNameBBTestMain.h

Abstract:

    IscsiInitiatorName Protocol (define according to the UEFI Spec 2.0 )

Revision History

--*/

#ifndef __ISCSIINITIATORNAMEBBTESTMAIN_H__
#define __ISCSIINITIATORNAMEBBTESTMAIN_H__

#include "Efi.h"
#include <UEFI/Protocol/iScsiInitiatorName.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define ISCSI_INITIATOR_NAME_PROTOCOL_TEST_REVISION    0x00010000

#define ISCSI_INITIATORNAME_MAXIMUM_SIZE  224

EFI_STATUS
EFIAPI
BBTestGetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#define EFI_SAMPLE_BB_TEST_CATEGORY_GUID \
  { 0x3367794b, 0x363f, 0x47a0, {0x88, 0x90, 0x5b, 0xd8, 0x43, 0xdf, 0x38, 0xc0 }}

#define ISCSI_INITIATORNAME_PROTOCOL_GET_FUNCTION_GUID \
  { 0xcd653384, 0x3b5f, 0x4fbe, { 0xbf, 0x8, 0x7b, 0xb1, 0xc8, 0x16, 0x27, 0xc5 } }

#define ISCSI_INITIATORNAME_PROTOCOL_SET_FUNCTION_GUID \
  { 0xe3e287a3, 0x844, 0x477b, { 0x83, 0xf9, 0x81, 0xb5, 0x5e, 0xa9, 0x94, 0x4f } }

#define ISCSI_INITIATORNAME_PROTOCOL_GET_CONFORMANCE_GUID \
  { 0x4f6d045b, 0x1cf7, 0x4036, { 0x88, 0x85, 0x2b, 0x2, 0x30, 0x0, 0xd, 0xde } }

#define ISCSI_INITIATORNAME_PROTOCOL_SET_CONFORMANCE_GUID \
  { 0x5b739f67, 0xf291, 0x46eb, { 0xb0, 0x71, 0x2c, 0xb4, 0x66, 0xba, 0x21, 0x74 } }

#endif
