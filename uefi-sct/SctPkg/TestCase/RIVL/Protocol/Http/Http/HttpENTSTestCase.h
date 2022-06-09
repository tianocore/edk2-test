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

  HttpENTSTestCase.h

Abstract:

--*/

#ifndef _HTTP_ENTS_TESTCASE_H_
#define _HTTP_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Http.h>

EFI_STATUS
EFIAPI
HttpGetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Http GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
HttpConfigure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Http Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;


EFI_STATUS
EFIAPI
HttpRequest_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Http Request Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
HttpCancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Http Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
HttpResponse_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Http Response Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
HttpPoll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Http Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;


extern CHAR16         *gHttpEntsRuntimeInfo;
extern UINTN          gHttpEntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gHttpGetModeDataArgField[];
extern ENTS_ARG_FIELD gHttpConfigureArgField[];
extern ENTS_ARG_FIELD gHttpRequestArgField[];
extern ENTS_ARG_FIELD gHttpResponseArgField[];
extern ENTS_ARG_FIELD gHttpCancelArgField[];
extern ENTS_ARG_FIELD gHttpPollArgField[];

#endif // _HTTP_ENTS_TESTCASE_H_
