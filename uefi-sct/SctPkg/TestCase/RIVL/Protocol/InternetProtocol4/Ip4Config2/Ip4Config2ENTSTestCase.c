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

  Ip4Config2ENTSTestCase.c

Abstract:

--*/

#include "Ip4Config2ENTSTestCase.h"

//
// Ip4Config2.SetData
//
static EFI_IP4_CONFIG2_DATA_TYPE  SetDataDataType;
static UINTN                      SetDataDataSize;
static VOID                       *SetDataData;
static EFI_STATUS                 *Ip4Config2SetDataStatus;

ENTS_ARG_FIELD    gIp4Config2SetDataArgField[] = {
  {
    OCTETN,
    &SetDataDataType
  },
  {
    OCTETN,
    &SetDataDataSize
  },
  {
    POINTER,
    &SetDataData
  },
  {
    POINTER,
    &Ip4Config2SetDataStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip4Config2SetData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config2 SetData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_CONFIG2_PROTOCOL  *Ip4Config2;

  Ip4Config2 = (EFI_IP4_CONFIG2_PROTOCOL *) ClientInterface;

  *Ip4Config2SetDataStatus = Ip4Config2->SetData (
                                           Ip4Config2,
                                           SetDataDataType,
                                           SetDataDataSize,
                                           SetDataData
                                           );
  return EFI_SUCCESS;
}

//
// Ip4Config2.GetData
//
static EFI_IP4_CONFIG2_DATA_TYPE  GetDataDataType;
static UINTN                      *GetDataDataSize;
static VOID                       *GetDataData;
static EFI_STATUS                 *Ip4Config2GetDataStatus;

ENTS_ARG_FIELD    gIp4Config2GetDataArgField[] = {
  {
    OCTETN,
    &GetDataDataType
  },
  {
    POINTER,
    &GetDataDataSize
  },
  {
    POINTER,
    &GetDataData
  },
  {
    POINTER,
    &Ip4Config2GetDataStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip4Config2GetData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config2 GetData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_CONFIG2_PROTOCOL *Ip4Config2;

  Ip4Config2             = (EFI_IP4_CONFIG2_PROTOCOL *) ClientInterface;

  *Ip4Config2GetDataStatus  = Ip4Config2->GetData (
  	                                         Ip4Config2,
                                            GetDataDataType,
                                            GetDataDataSize,
                                            GetDataData
                                            );
  return EFI_SUCCESS;
}

//
// Ip4Config2.RegisterDataNotify
//
static EFI_IP4_CONFIG2_DATA_TYPE    RegisterDataNotifyDataType;
static EFI_EVENT                    RegisterDataNotifyEvent;
static EFI_STATUS                   *Ip4Config2RegisterDataNotifyStatus;

ENTS_ARG_FIELD                gIp4Config2RegisterDataNotifyArgField[] = {
  {
    OCTETN,
    &RegisterDataNotifyDataType
  },
  {
    OCTETN,
    &RegisterDataNotifyEvent
  },
  {
    POINTER,
    &Ip4Config2RegisterDataNotifyStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip4Config2RegisterDataNotify_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config2 RegisterDataNotify Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_CONFIG2_PROTOCOL *Ip4Config2;

  Ip4Config2 = (EFI_IP4_CONFIG2_PROTOCOL *) ClientInterface;

  *Ip4Config2RegisterDataNotifyStatus = Ip4Config2->RegisterDataNotify (
                                                      Ip4Config2,
                                                      RegisterDataNotifyDataType,
                                                      RegisterDataNotifyEvent
                                                      );
  return EFI_SUCCESS;
}

//
// Ip4Config2.UnregisterDataNotify
//
static EFI_IP4_CONFIG2_DATA_TYPE    UnregisterDataNotifyDataType;
static EFI_EVENT                    UnregisterDataNotifyEvent;
static EFI_STATUS                   *Ip4Config2UnregisterDataNotifyStatus;

ENTS_ARG_FIELD                gIp4Config2UnregisterDataNotifyArgField[] = {
  {
    OCTETN,
    &UnregisterDataNotifyDataType
  },
  {
    OCTETN,
    &UnregisterDataNotifyEvent
  },
  {
    POINTER,
    &Ip4Config2UnregisterDataNotifyStatus
  },
  0
};


EFI_STATUS
EFIAPI
Ip4Config2UnregisterDataNotify_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4Config2 UnregisterDataNotify Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_IP4_CONFIG2_PROTOCOL *Ip4Config2;

  Ip4Config2 = (EFI_IP4_CONFIG2_PROTOCOL *) ClientInterface;

  *Ip4Config2UnregisterDataNotifyStatus = Ip4Config2->UnregisterDataNotify (
                                                        Ip4Config2,
                                                        UnregisterDataNotifyDataType,
                                                        UnregisterDataNotifyEvent
                                                        );
  return EFI_SUCCESS;
}

