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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
