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

  Ip6ConfigENTSTestCase.h

Abstract:

--*/

#ifndef _IP6_CONFIG_ENTS_TESTCASE_H_
#define _IP6_CONFIG_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
#include <Library/EntsLib.h>
#include <UEFI/Protocol/Ip6.h>

EFI_STATUS
EFIAPI
Ip6ConfigSetData_EntsTest (
  VOID *ClientInterface
  );

EFI_STATUS
EFIAPI
Ip6ConfigGetData_EntsTest (
  VOID *ClientInterface
  );

EFI_STATUS
EFIAPI
Ip6ConfigRegisterDataNotify_EntsTest (
  VOID *ClientInterface
  );

EFI_STATUS
EFIAPI
Ip6ConfigUnregisterDataNotify_EntsTest (
  VOID *ClientInterface
  );

extern CHAR16         *gIp6ConfigRuntimeInfo;
extern UINTN          gIp6ConfigRuntimeInfoSize;

extern ENTS_ARG_FIELD gIp6ConfigSetDataArgField[];
extern ENTS_ARG_FIELD gIp6ConfigGetDataArgField[];
extern ENTS_ARG_FIELD gIp6ConfigRegisterDataNotifyArgField[];
extern ENTS_ARG_FIELD gIp6ConfigUnregisterDataNotifyArgField[];

#endif
