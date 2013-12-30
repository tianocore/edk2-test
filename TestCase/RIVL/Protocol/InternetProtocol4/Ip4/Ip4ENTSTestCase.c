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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Ip4ENTSTestCase.c

Abstract:

--*/

#include "Ip4ENTSTestCase.h"

//
// Ip4.GetModeData
//
static EFI_IP4_MODE_DATA                *Ip4GetModeDataIp4ModeData;
static EFI_MANAGED_NETWORK_CONFIG_DATA  *Ip4GetModeDataMnpConfigData;
static EFI_SIMPLE_NETWORK_MODE          *Ip4GetModeDataSnpModeData;
static EFI_STATUS                       *Ip4GetModeDataStatus;

ENTS_ARG_FIELD                          gIp4GetModeDataArgField[] = {
  {
    POINTER,
    &Ip4GetModeDataIp4ModeData
  },
  {
    POINTER,
    &Ip4GetModeDataMnpConfigData
  },
  {
    POINTER,
    &Ip4GetModeDataSnpModeData
  },
  {
    POINTER,
    &Ip4GetModeDataStatus
  },
  0
};

EFI_STATUS
Ip4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_PROTOCOL  *Ip4;

  Ip4 = (EFI_IP4_PROTOCOL *) ClientInterface;

  *Ip4GetModeDataStatus = Ip4->GetModeData (
                                Ip4,
                                Ip4GetModeDataIp4ModeData,
                                Ip4GetModeDataMnpConfigData,
                                Ip4GetModeDataSnpModeData
                                );
  return EFI_SUCCESS;
}

//
// Ip4.Configure
//
static EFI_IP4_CONFIG_DATA  *Ip4ConfigureIpConfigData;
static EFI_STATUS           *Ip4ConfigureStatus;

ENTS_ARG_FIELD              gIp4ConfigureArgField[] = {
  {
    POINTER,
    &Ip4ConfigureIpConfigData
  },
  {
    POINTER,
    &Ip4ConfigureStatus
  },
  0
};

EFI_STATUS
Ip4Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_PROTOCOL  *Ip4;

  Ip4 = (EFI_IP4_PROTOCOL *) ClientInterface;

  *Ip4ConfigureStatus = Ip4->Configure (
                              Ip4,
                              Ip4ConfigureIpConfigData
                              );
  return EFI_SUCCESS;
}

//
// Ip4.Groups
//
static BOOLEAN          Ip4GroupsJoinFlag;
static EFI_IPv4_ADDRESS *Ip4GroupsGroupAddress;
static EFI_STATUS       *Ip4GroupsStatus;

ENTS_ARG_FIELD          gIp4GroupsArgField[] = {
  {
    BOOL,
    &Ip4GroupsJoinFlag
  },
  {
    POINTER,
    &Ip4GroupsGroupAddress
  },
  {
    POINTER,
    &Ip4GroupsStatus
  },
  0
};

EFI_STATUS
Ip4Groups_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Groups Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_PROTOCOL  *Ip4;

  Ip4 = (EFI_IP4_PROTOCOL *) ClientInterface;

  *Ip4GroupsStatus = Ip4->Groups (
                            Ip4,
                            Ip4GroupsJoinFlag,
                            Ip4GroupsGroupAddress
                            );
  return EFI_SUCCESS;
}

//
// Ip4.Routes
//
static BOOLEAN          Ip4RoutesDeleteRoute;
static EFI_IPv4_ADDRESS *Ip4RoutesSubnetAddress;
static EFI_IPv4_ADDRESS *Ip4RoutesSubnetMask;
static EFI_IPv4_ADDRESS *Ip4RoutesGatewayAddress;
static EFI_STATUS       *Ip4RoutesStatus;

ENTS_ARG_FIELD          gIp4RoutesArgField[] = {
  {
    BOOL,
    &Ip4RoutesDeleteRoute
  },
  {
    POINTER,
    &Ip4RoutesSubnetAddress
  },
  {
    POINTER,
    &Ip4RoutesSubnetMask
  },
  {
    POINTER,
    &Ip4RoutesGatewayAddress
  },
  {
    POINTER,
    &Ip4RoutesStatus
  },
  0
};

EFI_STATUS
Ip4Routes_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Routes Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_PROTOCOL  *Ip4;

  Ip4 = (EFI_IP4_PROTOCOL *) ClientInterface;

  *Ip4RoutesStatus = Ip4->Routes (
                            Ip4,
                            Ip4RoutesDeleteRoute,
                            Ip4RoutesSubnetAddress,
                            Ip4RoutesSubnetMask,
                            Ip4RoutesGatewayAddress
                            );
  return EFI_SUCCESS;
}

//
// Ip4.Transmit
//
static EFI_IP4_COMPLETION_TOKEN *Ip4TransmitToken;
static EFI_STATUS               *Ip4TransmitStatus;

ENTS_ARG_FIELD                  gIp4TransmitArgField[] = {
  {
    POINTER,
    &Ip4TransmitToken
  },
  {
    POINTER,
    &Ip4TransmitStatus
  },
  0
};

EFI_STATUS
Ip4Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_PROTOCOL  *Ip4;

  Ip4 = (EFI_IP4_PROTOCOL *) ClientInterface;

  *Ip4TransmitStatus = Ip4->Transmit (
                              Ip4,
                              Ip4TransmitToken
                              );
  return EFI_SUCCESS;
}

//
// Ip4.Receive
//
static EFI_IP4_COMPLETION_TOKEN *Ip4ReceiveToken;
static EFI_STATUS               *Ip4ReceiveStatus;

ENTS_ARG_FIELD                  gIp4ReceiveArgField[] = {
  {
    POINTER,
    &Ip4ReceiveToken
  },
  {
    POINTER,
    &Ip4ReceiveStatus
  },
  0
};

EFI_STATUS
Ip4Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_PROTOCOL  *Ip4;

  Ip4 = (EFI_IP4_PROTOCOL *) ClientInterface;

  *Ip4ReceiveStatus = Ip4->Receive (
                            Ip4,
                            Ip4ReceiveToken
                            );
  return EFI_SUCCESS;
}

//
// Ip4.Cancel
//
static EFI_STATUS               *Ip4CancelStatus;
static EFI_IP4_COMPLETION_TOKEN *Ip4CancelToken;

ENTS_ARG_FIELD                  gIp4CancelArgField[] = {
  {
    POINTER,
    &Ip4CancelToken
  },
  {
    POINTER,
    &Ip4CancelStatus
  },
  0
};

EFI_STATUS
Ip4Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_PROTOCOL  *Ip4;

  Ip4 = (EFI_IP4_PROTOCOL *) ClientInterface;

  *Ip4CancelStatus = Ip4->Cancel (
                            Ip4,
                            Ip4CancelToken
                            );
  return EFI_SUCCESS;
}

//
// Ip4.Poll
//
static EFI_STATUS *Ip4PollStatus;

ENTS_ARG_FIELD    gIp4PollArgField[] = {
  {
    POINTER,
    &Ip4PollStatus
  },
  0
};

EFI_STATUS
Ip4Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_PROTOCOL  *Ip4;

  Ip4             = (EFI_IP4_PROTOCOL *) ClientInterface;

  *Ip4PollStatus  = Ip4->Poll (Ip4);
  return EFI_SUCCESS;
}
