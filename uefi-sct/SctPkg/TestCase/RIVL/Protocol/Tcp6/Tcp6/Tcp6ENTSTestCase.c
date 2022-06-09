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

  Tcp6ENTSTestCase.c

Abstract:

--*/

#include "Tcp6ENTSTestCase.h"

//
// Tcp6.GetModeData
//
static EFI_TCP6_CONNECTION_STATE        *GetModeData_Tcp6State;
static EFI_TCP6_CONFIG_DATA             *GetModeData_Tcp6ConfigData;
static EFI_IP6_MODE_DATA                *GetModeData_Ip6ModeData;
static EFI_MANAGED_NETWORK_CONFIG_DATA  *GetModeData_MnpConfigData;
static EFI_SIMPLE_NETWORK_MODE          *GetModeData_SnpModeData;
static EFI_STATUS                       *GetModeData_Status;

ENTS_ARG_FIELD                          gTcp6GetModeDataArgField[] = {
  {
    POINTER,
    &GetModeData_Tcp6State
  },
  {
    POINTER,
    &GetModeData_Tcp6ConfigData
  },
  {
    POINTER,
    &GetModeData_Ip6ModeData
  },
  {
    POINTER,
    &GetModeData_MnpConfigData
  },
  {
    POINTER,
    &GetModeData_SnpModeData
  },
  {
    POINTER,
    &GetModeData_Status
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *GetModeData_Status = Tcp6->GetModeData (
                                Tcp6,
                                GetModeData_Tcp6State,
                                GetModeData_Tcp6ConfigData,
                                GetModeData_Ip6ModeData,
                                GetModeData_MnpConfigData,
                                GetModeData_SnpModeData
                                );

  return EFI_SUCCESS;
}

//
// Tcp6.Configure
//
static EFI_TCP6_CONFIG_DATA *Configure_Tcp6ConfigData;
static EFI_STATUS           *Configure_Status;

ENTS_ARG_FIELD              gTcp6ConfigureArgField[] = {
  {
    POINTER,
    &Configure_Tcp6ConfigData
  },
  {
    POINTER,
    &Configure_Status
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *Configure_Status = Tcp6->Configure (
                              Tcp6,
                              Configure_Tcp6ConfigData
                              );

  return EFI_SUCCESS;
}

//
// Tcp6.Connect
//
static EFI_TCP6_CONNECTION_TOKEN  *Connect_ConnectionToken;
static EFI_STATUS                 *Connect_Status;

ENTS_ARG_FIELD                    gTcp6ConnectArgField[] = {
  {
    POINTER,
    &Connect_ConnectionToken
  },
  {
    POINTER,
    &Connect_Status
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6Connect_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Connect Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *Connect_Status = Tcp6->Connect (
                            Tcp6,
                            Connect_ConnectionToken
                            );

  return EFI_SUCCESS;
}

//
// Tcp6.Accept
//
static EFI_TCP6_LISTEN_TOKEN  *Accept_ListenToken;
static EFI_STATUS             *Accept_Status;

ENTS_ARG_FIELD                gTcp6AcceptArgField[] = {
  {
    POINTER,
    &Accept_ListenToken
  },
  {
    POINTER,
    &Accept_Status
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6Accept_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Accept Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *Accept_Status = Tcp6->Accept (
                          Tcp6,
                          Accept_ListenToken
                          );

  return EFI_SUCCESS;
}

//
// Tcp6.Transmit
//
static EFI_TCP6_IO_TOKEN  *Transmit_Token;
static EFI_STATUS         *Transmit_Status;

ENTS_ARG_FIELD            gTcp6TransmitArgField[] = {
  {
    POINTER,
    &Transmit_Token
  },
  {
    POINTER,
    &Transmit_Status
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *Transmit_Status = Tcp6->Transmit (
                            Tcp6,
                            Transmit_Token
                            );

  return EFI_SUCCESS;
}

//
// Tcp6.Receive
//
static EFI_TCP6_IO_TOKEN  *Receive_Token;
static EFI_STATUS         *Receive_Status;

ENTS_ARG_FIELD            gTcp6ReceiveArgField[] = {
  {
    POINTER,
    &Receive_Token
  },
  {
    POINTER,
    &Receive_Status
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *Receive_Status = Tcp6->Receive (
                            Tcp6,
                            Receive_Token
                            );

  return EFI_SUCCESS;
}

//
// Tcp6.Close
//
static EFI_TCP6_CLOSE_TOKEN *Close_Token;
static EFI_STATUS           *Close_Status;

ENTS_ARG_FIELD              gTcp6CloseArgField[] = {
  {
    POINTER,
    &Close_Token
  },
  {
    POINTER,
    &Close_Status
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6Close_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Close Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *Close_Status = Tcp6->Close (
                          Tcp6,
                          Close_Token
                          );

  return EFI_SUCCESS;
}

//
// Tcp6.Cancel
//
static EFI_TCP6_COMPLETION_TOKEN  *Cancel_Token;
static EFI_STATUS                 *Cancel_Status;

ENTS_ARG_FIELD                    gTcp6CancelArgField[] = {
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
Tcp6Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *Cancel_Status = Tcp6->Cancel (
                          Tcp6,
                          Cancel_Token
                          );

  return EFI_SUCCESS;
}

//
// Tcp6.Poll
//
static EFI_STATUS *Poll_Status;

ENTS_ARG_FIELD    gTcp6PollArgField[] = {
  {
    POINTER,
    &Poll_Status
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP6_PROTOCOL *Tcp6;

  Tcp6 = (EFI_TCP6_PROTOCOL *) ClientInterface;

  *Poll_Status  = Tcp6->Poll (Tcp6);

  return EFI_SUCCESS;
}
