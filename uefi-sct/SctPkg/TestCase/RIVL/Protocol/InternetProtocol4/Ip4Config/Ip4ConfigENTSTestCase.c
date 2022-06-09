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

  Ip4ConfigENTSTestCase.c

Abstract:

--*/

#include "Ip4ConfigENTSTestCase.h"

//
// Ip4Config.Start
//
static EFI_EVENT  Ip4ConfigStartDoneEvent;
static EFI_EVENT  Ip4ConfigStartReconfigEvent;
static EFI_STATUS *Ip4ConfigStartStatus;

ENTS_ARG_FIELD    gIp4ConfigStartArgField[] = {
  {
    OCTETN,
    &Ip4ConfigStartDoneEvent
  },
  {
    OCTETN,
    &Ip4ConfigStartReconfigEvent
  },
  {
    POINTER,
    &Ip4ConfigStartStatus
  },
  0
};

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
{
  EFI_IP4_CONFIG_PROTOCOL *Ip4Config;

  Ip4Config = (EFI_IP4_CONFIG_PROTOCOL *) ClientInterface;

  *Ip4ConfigStartStatus = Ip4Config->Start (
                                      Ip4Config,
                                      Ip4ConfigStartDoneEvent,
                                      Ip4ConfigStartReconfigEvent
                                      );
  return EFI_SUCCESS;
}

//
// Ip4Config.Stop
//
static EFI_STATUS *Ip4ConfigStopStatus;

ENTS_ARG_FIELD    gIp4ConfigStopArgField[] = {
  {
    POINTER,
    &Ip4ConfigStopStatus
  },
  0
};

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
{
  EFI_IP4_CONFIG_PROTOCOL *Ip4Config;

  Ip4Config             = (EFI_IP4_CONFIG_PROTOCOL *) ClientInterface;

  *Ip4ConfigStopStatus  = Ip4Config->Stop (Ip4Config);
  return EFI_SUCCESS;
}

//
// Ip4Config.GetData
//
static UINTN                  *Ip4ConfigGetDataConfigDataSize;
static EFI_IP4_IPCONFIG_DATA  *Ip4ConfigGetDataConfigData;
static EFI_STATUS             *Ip4ConfigGetDataStatus;

ENTS_ARG_FIELD                gIp4ConfigGetDataArgField[] = {
  {
    POINTER,
    &Ip4ConfigGetDataConfigDataSize
  },
  {
    POINTER,
    &Ip4ConfigGetDataConfigData
  },
  {
    POINTER,
    &Ip4ConfigGetDataStatus
  },
  0
};

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
{
  EFI_IP4_CONFIG_PROTOCOL *Ip4Config;

  Ip4Config = (EFI_IP4_CONFIG_PROTOCOL *) ClientInterface;

  *Ip4ConfigGetDataStatus = Ip4Config->GetData (
                                        Ip4Config,
                                        Ip4ConfigGetDataConfigDataSize,
                                        Ip4ConfigGetDataConfigData
                                        );
  return EFI_SUCCESS;
}
