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

  Ip6ConfigENTSTestCase.c

Abstract:

--*/

#include "Ip6ConfigENTSTestCase.h"
//
// Ip6Config.SetData
//
static EFI_IP6_CONFIG_DATA_TYPE  Ip6ConfigSetDataDataType;
static UINTN  Ip6ConfigSetDataDataSize;
static VOID  *Ip6ConfigSetDataData;
static EFI_STATUS *Ip6ConfigSetDataStatus;

ENTS_ARG_FIELD    gIp6ConfigSetDataArgField[] = {
  {
    OCTET4,
    &Ip6ConfigSetDataDataType
  },
  {
    OCTETN,
    &Ip6ConfigSetDataDataSize
  },
  {
    POINTER,
    &Ip6ConfigSetDataData
  },
  {
    POINTER,
    &Ip6ConfigSetDataStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6ConfigSetData_EntsTest (
  VOID *ClientInterface
  )
{
  EFI_IP6_CONFIG_PROTOCOL *Ip6Config;

  Ip6Config = (EFI_IP6_CONFIG_PROTOCOL *) ClientInterface;

  *Ip6ConfigSetDataStatus = Ip6Config->SetData (
                                      Ip6Config,
                                      Ip6ConfigSetDataDataType,
                                      Ip6ConfigSetDataDataSize,
                                      Ip6ConfigSetDataData
                                      );
  return EFI_SUCCESS;
}

//
// Ip6Config.GetData
//
static EFI_IP6_CONFIG_DATA_TYPE   Ip6ConfigGetDataDataType;
static UINTN  *Ip6ConfigGetDataDataSize;
static VOID *Ip6ConfigGetDataData;
static EFI_STATUS             *Ip6ConfigGetDataStatus;

ENTS_ARG_FIELD                gIp6ConfigGetDataArgField[] = {
  {
   OCTET4,
    &Ip6ConfigGetDataDataType
  },
  {
    POINTER,
    &Ip6ConfigGetDataDataSize
  },
  {
    POINTER,
    &Ip6ConfigGetDataData
  },
  {
    POINTER,
    &Ip6ConfigGetDataStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6ConfigGetData_EntsTest (
  VOID *ClientInterface
  )
{
  EFI_IP6_CONFIG_PROTOCOL *Ip6Config;

  Ip6Config = (EFI_IP6_CONFIG_PROTOCOL *) ClientInterface;

  *Ip6ConfigGetDataStatus = Ip6Config->GetData (
                                        Ip6Config,
                                        Ip6ConfigGetDataDataType,
                                        Ip6ConfigGetDataDataSize,
                                        Ip6ConfigGetDataData
                                        );
  return EFI_SUCCESS;
}

//
//Ip6Config.RegisterDataNotify
//
static EFI_IP6_CONFIG_DATA_TYPE   Ip6ConfigRegisterDataNotifyDataType;
static EFI_EVENT Ip6ConfigRegisterDataNotifyEvent;
static EFI_STATUS             *Ip6ConfigRegisterDataNotifyStatus;

ENTS_ARG_FIELD                gIp6ConfigRegisterDataNotifyArgField[] = {
  {
    OCTET4,
	&Ip6ConfigRegisterDataNotifyDataType
  },
  {
    OCTETN,
    &Ip6ConfigRegisterDataNotifyEvent
  },
  {
    POINTER,
    &Ip6ConfigRegisterDataNotifyStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6ConfigRegisterDataNotify_EntsTest (
  VOID *ClientInterface
  )
{
  EFI_IP6_CONFIG_PROTOCOL *Ip6Config;

  Ip6Config = (EFI_IP6_CONFIG_PROTOCOL *) ClientInterface;

  *Ip6ConfigRegisterDataNotifyStatus = Ip6Config->RegisterDataNotify (
                                        Ip6Config,
										Ip6ConfigRegisterDataNotifyDataType,
										Ip6ConfigRegisterDataNotifyEvent
                                        );
  
  return EFI_SUCCESS;
}

//
//Ip6Config.UnregisterDataNotify
//
static EFI_IP6_CONFIG_DATA_TYPE   Ip6ConfigUnregisterDataNotifyDataType;
static EFI_EVENT Ip6ConfigUnregisterDataNotifyEvent;
static EFI_STATUS             *Ip6ConfigUnregisterDataNotifyStatus;

ENTS_ARG_FIELD                gIp6ConfigUnregisterDataNotifyArgField[] = {
  {
    OCTET4,
	&Ip6ConfigUnregisterDataNotifyDataType
  },
  {
    OCTETN,
    &Ip6ConfigUnregisterDataNotifyEvent
  },
  {
    POINTER,
    &Ip6ConfigUnregisterDataNotifyStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6ConfigUnregisterDataNotify_EntsTest (
  VOID *ClientInterface
  )
{
  EFI_IP6_CONFIG_PROTOCOL *Ip6Config;

  Ip6Config = (EFI_IP6_CONFIG_PROTOCOL *) ClientInterface;

  *Ip6ConfigUnregisterDataNotifyStatus = Ip6Config->UnregisterDataNotify (
                                        Ip6Config,
										Ip6ConfigUnregisterDataNotifyDataType,
										Ip6ConfigUnregisterDataNotifyEvent
                                        );
  return EFI_SUCCESS;
}
