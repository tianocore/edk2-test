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
                                                                
  Copyright 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
