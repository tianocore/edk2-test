/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Ip4Confi2gENTSTestCase.h

Abstract:

--*/

#ifndef _IP4_CONFIG_ENTS_TESTCASE_H_
#define _IP4_CONFIG_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
//#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
//#include <Library/EntsLib.h>
#include <UEFI/Protocol/Ip4.h>

EFI_STATUS
EFIAPI
Ip4Config2SetData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config2 SetData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Config2GetData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config2 GetData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Config2RegisterDataNotify_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config2 RegisterDataNotify Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Config2UnregisterDataNotify_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config2 UnregisterDataNotify Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gIp4Config2RuntimeInfo;
extern UINTN          gIp4Config2RuntimeInfoSize;

extern ENTS_ARG_FIELD gIp4Config2SetDataArgField[];
extern ENTS_ARG_FIELD gIp4Config2GetDataArgField[];
extern ENTS_ARG_FIELD gIp4Config2RegisterDataNotifyArgField[];
extern ENTS_ARG_FIELD gIp4Config2UnregisterDataNotifyArgField[];

#endif
