/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

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

#define IHV_ISCSI_INITIATOR_NAME_PROTOCOL_GUID \
  { 0x3f10cfd2, 0x6cb6, 0x4a2b, { 0x91, 0x9a, 0xb6, 0x3b, 0x83, 0x9a, 0x3, 0x63 } }


EFI_STATUS
BBTestGetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#define EFI_SAMPLE_BB_TEST_CATEGORY_GUID \
  { 0xb33e697e, 0x4e71, 0x4c98, { 0x84, 0xc6, 0x45, 0x31, 0xfb, 0x78, 0xc0, 0x86 } }

#define ISCSI_INITIATORNAME_PROTOCOL_GET_FUNCTION_GUID \
  { 0x73a08d82, 0x470c, 0x41f1, { 0xa5, 0x1a, 0x3e, 0x2, 0xf1, 0xa9, 0x47, 0x72 } }

#define ISCSI_INITIATORNAME_PROTOCOL_SET_FUNCTION_GUID \
  { 0x2b80b048, 0xa611, 0x4b9f, { 0x82, 0x12, 0xf9, 0xe5, 0x6a, 0x53, 0x5e, 0x4f } }

#define ISCSI_INITIATORNAME_PROTOCOL_GET_CONFORMANCE_GUID \
  { 0x2c77d11b, 0x8d7d, 0x4559, { 0xbd, 0x73, 0x65, 0xe0, 0x11, 0xab, 0x69, 0x98 } }

#define ISCSI_INITIATORNAME_PROTOCOL_SET_CONFORMANCE_GUID \
  { 0x75905aa6, 0x3d6d, 0x4982, { 0xbc, 0x9b, 0x8f, 0xb0, 0xba, 0xf8, 0x99, 0x84 } }

#endif
