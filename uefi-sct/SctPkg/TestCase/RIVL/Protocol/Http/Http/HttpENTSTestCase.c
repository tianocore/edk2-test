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

  HttpENTSTestCase.c

Abstract:

--*/

#include "HttpENTSTestCase.h"

//
// Http.GetModeData
//
static EFI_HTTP_CONFIG_DATA             *GetModeData_HttpConfigData;
static EFI_STATUS                       *GetModeData_Status;

ENTS_ARG_FIELD                          gHttpGetModeDataArgField[] = {
  {
    POINTER,
    &GetModeData_HttpConfigData
  },
  {
    POINTER,
    &GetModeData_Status
  },
  0
};

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
{
  EFI_HTTP_PROTOCOL *Http;

  Http = (EFI_HTTP_PROTOCOL *) ClientInterface;

  *GetModeData_Status = Http->GetModeData (
                                Http,
                                GetModeData_HttpConfigData
                                );

  return EFI_SUCCESS;
}

//
// Http.Configure
//
static EFI_HTTP_CONFIG_DATA  *Configure_HttpConfigData;
static EFI_STATUS            *Configure_Status;

ENTS_ARG_FIELD              gHttpConfigureArgField[] = {
  {
    POINTER,
    &Configure_HttpConfigData
  },
  {
    POINTER,
    &Configure_Status
  },
  0
};

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
{
  EFI_HTTP_PROTOCOL *Http;

  Http = (EFI_HTTP_PROTOCOL *) ClientInterface;

  *Configure_Status = Http->Configure (
                              Http,
                              Configure_HttpConfigData
                              );

  return EFI_SUCCESS;
}

//
// Http.Request
//
static EFI_HTTP_TOKEN   *Request_Token;
static EFI_STATUS       *Request_Status;

ENTS_ARG_FIELD          gHttpRequestArgField[] = {
  {
    POINTER,
    &Request_Token
  },
  {
    POINTER,
    &Request_Status
  },
  0
};

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
{
  EFI_HTTP_PROTOCOL *Http;

  Http = (EFI_HTTP_PROTOCOL *) ClientInterface;

  *Request_Status = Http->Request (
                          Http,
                          Request_Token
                          );
  return EFI_SUCCESS;
}


//
// Http.Receive
//
static EFI_HTTP_TOKEN    *Response_Token;
static EFI_STATUS        *Response_Status;

ENTS_ARG_FIELD            gHttpResponseArgField[] = {
  {
    POINTER,
    &Response_Token
  },
  {
    POINTER,
    &Response_Status
  },
  0
};

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
{
  EFI_HTTP_PROTOCOL *Http;

  Http = (EFI_HTTP_PROTOCOL *) ClientInterface;

  *Response_Status = Http->Response (
                            Http,
                            Response_Token
                            );

  return EFI_SUCCESS;
}

//
// Http.Cancel
//
static EFI_HTTP_TOKEN             *Cancel_Token;
static EFI_STATUS                 *Cancel_Status;

ENTS_ARG_FIELD                    gHttpCancelArgField[] = {
  {
    POINTER,
    &Cancel_Token
  },
  {
    POINTER,
    &Cancel_Status
  },
  0
};

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
{
  EFI_HTTP_PROTOCOL *Http;

  Http = (EFI_HTTP_PROTOCOL *) ClientInterface;

  *Cancel_Status = Http->Cancel (
                          Http,
                          Cancel_Token
                          );

  return EFI_SUCCESS;
}

//
// Http.Poll
//
static EFI_STATUS *Poll_Status;

ENTS_ARG_FIELD    gHttpPollArgField[] = {
  {
    POINTER,
    &Poll_Status
  },
  0
};

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
{
  EFI_HTTP_PROTOCOL *Http;

  Http          = (EFI_HTTP_PROTOCOL *) ClientInterface;

  *Poll_Status  = Http->Poll (Http);

  return EFI_SUCCESS;
}
