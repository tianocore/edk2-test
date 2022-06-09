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

  Ip6ENTSTestCase.c

Abstract:

--*/

#include "Ip6ENTSTestCase.h"

//
// Ip6.GetModeData
//
static EFI_IP6_MODE_DATA                *Ip6GetModeDataIp6ModeData;
static EFI_MANAGED_NETWORK_CONFIG_DATA  *Ip6GetModeDataMnpConfigData;
static EFI_SIMPLE_NETWORK_MODE          *Ip6GetModeDataSnpModeData;
static EFI_STATUS                       *Ip6GetModeDataStatus;

ENTS_ARG_FIELD                          gIp6GetModeDataArgField[] = {
  {
    POINTER,
    &Ip6GetModeDataIp6ModeData
  },
  {
    POINTER,
    &Ip6GetModeDataMnpConfigData
  },
  {
    POINTER,
    &Ip6GetModeDataSnpModeData
  },
  {
    POINTER,
    &Ip6GetModeDataStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP6_PROTOCOL  *Ip6;

  Ip6 = (EFI_IP6_PROTOCOL *) ClientInterface;

  *Ip6GetModeDataStatus = Ip6->GetModeData (
                                Ip6,
                                Ip6GetModeDataIp6ModeData,
                                Ip6GetModeDataMnpConfigData,
                                Ip6GetModeDataSnpModeData
                                );
  return EFI_SUCCESS;
}

//
// Ip6.Configure
//
static EFI_IP6_CONFIG_DATA  *Ip6ConfigureIp6ConfigData;
static EFI_STATUS           *Ip6ConfigureStatus;

ENTS_ARG_FIELD              gIp6ConfigureArgField[] = {
  {
    POINTER,
    &Ip6ConfigureIp6ConfigData
  },
  {
    POINTER,
    &Ip6ConfigureStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP6_PROTOCOL  *Ip6;

  Ip6 = (EFI_IP6_PROTOCOL *) ClientInterface;

  *Ip6ConfigureStatus = Ip6->Configure (
                              Ip6,
                              Ip6ConfigureIp6ConfigData
                              );
  return EFI_SUCCESS;
}

//
// Ip6.Groups
//
static BOOLEAN          Ip6GroupsJoinFlag;
static EFI_IPv6_ADDRESS *Ip6GroupsGroupAddress;
static EFI_STATUS       *Ip6GroupsStatus;

ENTS_ARG_FIELD          gIp6GroupsArgField[] = {
  {
    BOOL,
    &Ip6GroupsJoinFlag
  },
  {
    POINTER,
    &Ip6GroupsGroupAddress
  },
  {
    POINTER,
    &Ip6GroupsStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6Groups_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Groups Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP6_PROTOCOL  *Ip6;

  Ip6 = (EFI_IP6_PROTOCOL *) ClientInterface;

  *Ip6GroupsStatus = Ip6->Groups (
                            Ip6,
                            Ip6GroupsJoinFlag,
                            Ip6GroupsGroupAddress
                            );
  return EFI_SUCCESS;
}

//
// Ip6.Routes
//
static BOOLEAN          Ip6RoutesDeleteRoute;
static EFI_IPv6_ADDRESS *Ip6RoutesDestination;
static UINT8 Ip6RoutesPrefixLength;
static EFI_IPv6_ADDRESS *Ip6RoutesGatewayAddress;
static EFI_STATUS       *Ip6RoutesStatus;

ENTS_ARG_FIELD          gIp6RoutesArgField[] = {
  {
    BOOL,
    &Ip6RoutesDeleteRoute
  },
  {
    POINTER,
    &Ip6RoutesDestination
  },
  {
    OCTET1,
    &Ip6RoutesPrefixLength
  },
  {
    POINTER,
    &Ip6RoutesGatewayAddress
  },
  {
    POINTER,
    &Ip6RoutesStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6Routes_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Routes Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP6_PROTOCOL  *Ip6;

  Ip6 = (EFI_IP6_PROTOCOL *) ClientInterface;

  *Ip6RoutesStatus = Ip6->Routes (
                            Ip6,
                            Ip6RoutesDeleteRoute,
                            Ip6RoutesDestination,
                            Ip6RoutesPrefixLength,
                            Ip6RoutesGatewayAddress
                            );
  return EFI_SUCCESS;
}

//
//Ip6.Neighbors
//
static BOOLEAN Ip6NeighborsDeleteFlag;
static EFI_IPv6_ADDRESS *Ip6NeighborsTargetIp6Address;
static EFI_MAC_ADDRESS *Ip6NeighborsTargetLinkAddress;
static UINT32 Ip6NeighborsTimeout;
static BOOLEAN Ip6NeighborsOverride;
static EFI_STATUS *Ip6NeighborsStatus;

ENTS_ARG_FIELD gIp6NeighborsArgField[] = {
 {
  BOOL,
  &Ip6NeighborsDeleteFlag
 },
 {
  POINTER,
  &Ip6NeighborsTargetIp6Address
 },
 {
  POINTER,
  &Ip6NeighborsTargetLinkAddress
 },
 {
   OCTET4,
   &Ip6NeighborsTimeout		
 },
 {
   BOOL,
   &Ip6NeighborsOverride
 },
 {
   POINTER,
   &Ip6NeighborsStatus
 },
 0
};

EFI_STATUS
EFIAPI
Ip6Neighbors_EntsTest (
 VOID *ClientInterface
)
{
  EFI_IP6_PROTOCOL *Ip6;
  Ip6= (EFI_IP6_PROTOCOL *) ClientInterface;
  *Ip6NeighborsStatus = Ip6->Neighbors (
  	Ip6,
  	Ip6NeighborsDeleteFlag,
  	Ip6NeighborsTargetIp6Address,
  	Ip6NeighborsTargetLinkAddress,
  	Ip6NeighborsTimeout,
  	Ip6NeighborsOverride
   );
   return EFI_SUCCESS;  	
}



//
// Ip6.Transmit
//
static EFI_IP6_COMPLETION_TOKEN *Ip6TransmitToken;
static EFI_STATUS               *Ip6TransmitStatus;

ENTS_ARG_FIELD                  gIp6TransmitArgField[] = {
  {
    POINTER,
    &Ip6TransmitToken
  },
  {
    POINTER,
    &Ip6TransmitStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP6_PROTOCOL  *Ip6;

  Ip6 = (EFI_IP6_PROTOCOL *) ClientInterface;

  *Ip6TransmitStatus = Ip6->Transmit (
                              Ip6,
                              Ip6TransmitToken
                              );
  return EFI_SUCCESS;
}

//
// Ip6.Receive
//
static EFI_IP6_COMPLETION_TOKEN *Ip6ReceiveToken;
static EFI_STATUS               *Ip6ReceiveStatus;

ENTS_ARG_FIELD                  gIp6ReceiveArgField[] = {
  {
    POINTER,
    &Ip6ReceiveToken
  },
  {
    POINTER,
    &Ip6ReceiveStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP6_PROTOCOL  *Ip6;

  Ip6 = (EFI_IP6_PROTOCOL *) ClientInterface;

  *Ip6ReceiveStatus = Ip6->Receive (
                            Ip6,
                            Ip6ReceiveToken
                            );
  return EFI_SUCCESS;
}

//
// Ip6.Cancel
//
static EFI_STATUS               *Ip6CancelStatus;
static EFI_IP6_COMPLETION_TOKEN *Ip6CancelToken;

ENTS_ARG_FIELD                  gIp6CancelArgField[] = {
  {
    POINTER,
    &Ip6CancelToken
  },
  {
    POINTER,
    &Ip6CancelStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP6_PROTOCOL  *Ip6;

  Ip6 = (EFI_IP6_PROTOCOL *) ClientInterface;

  *Ip6CancelStatus = Ip6->Cancel (
                            Ip6,
                            Ip6CancelToken
                            );
  return EFI_SUCCESS;
}

//
// Ip6.Poll
//
static EFI_STATUS *Ip6PollStatus;

ENTS_ARG_FIELD    gIp6PollArgField[] = {
  {
    POINTER,
    &Ip6PollStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP6_PROTOCOL  *Ip6;

  Ip6             = (EFI_IP6_PROTOCOL *) ClientInterface;

  *Ip6PollStatus  = Ip6->Poll (Ip6);
  return EFI_SUCCESS;
}
