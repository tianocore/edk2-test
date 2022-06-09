/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Ip4ConfigENTSTestCase.h

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
Ip4ConfigStart_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4ConfigStop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config Stop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4ConfigGetData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config GetData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gIp4ConfigRuntimeInfo;
extern UINTN          gIp4ConfigRuntimeInfoSize;

extern ENTS_ARG_FIELD gIp4ConfigStartArgField[];
extern ENTS_ARG_FIELD gIp4ConfigStopArgField[];
extern ENTS_ARG_FIELD gIp4ConfigGetDataArgField[];

#endif
