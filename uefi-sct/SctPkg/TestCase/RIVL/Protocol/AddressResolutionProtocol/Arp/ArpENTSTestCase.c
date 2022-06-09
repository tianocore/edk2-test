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

  ArpENTSTestCase.c

Abstract:

--*/

#include "ArpENTSTestCase.h"

//
// Arp.Config
//
static EFI_ARP_CONFIG_DATA  *ArpConfigConfigData;
static EFI_STATUS           *ArpConfigStatus;

ENTS_ARG_FIELD              gArpConfigArgField[] = {
  {
    POINTER,
    &ArpConfigConfigData
  },
  {
    POINTER,
    &ArpConfigStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpConfig_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpConfig Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_ARP_PROTOCOL  *Arp;

  Arp = (EFI_ARP_PROTOCOL *) ClientInterface;

  *ArpConfigStatus = Arp->Configure (
                            Arp,
                            ArpConfigConfigData
                            );
  return EFI_SUCCESS;
}

//
// Arp.Add
//
static BOOLEAN    ArpAddDenyFlag;
static VOID       *ArpAddTargetSwAddress;
static VOID       *ArpAddTargetHwAddress;
static UINT32     ArpAddTimeoutValue;
static BOOLEAN    ArpAddOverwrite;
static EFI_STATUS *ArpAddStatus;

ENTS_ARG_FIELD    gArpAddArgField[] = {
  {
    BOOL,
    &ArpAddDenyFlag
  },
  {
    POINTER,
    &ArpAddTargetSwAddress
  },
  {
    POINTER,
    &ArpAddTargetHwAddress
  },
  {
    OCTET4,
    &ArpAddTimeoutValue
  },
  {
    BOOL,
    &ArpAddOverwrite
  },
  {
    POINTER,
    &ArpAddStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpAdd_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpAdd Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_ARP_PROTOCOL  *Arp;

  Arp = (EFI_ARP_PROTOCOL *) ClientInterface;

  *ArpAddStatus = Arp->Add (
                        Arp,
                        ArpAddDenyFlag,
                        ArpAddTargetSwAddress,
                        ArpAddTargetHwAddress,
                        ArpAddTimeoutValue,
                        ArpAddOverwrite
                        );
  return EFI_SUCCESS;
}

//
// Arp.Find
//
static BOOLEAN            ArpFindBySwAddress;
static VOID               *ArpFindAddressBuffer;
static UINT32             *ArpFindEntryLength;
static UINT32             *ArpFindEntryCount;
static EFI_ARP_FIND_DATA  **ArpFindEntries;
static BOOLEAN            ArpFindRefresh;
static EFI_STATUS         *ArpFindStatus;

ENTS_ARG_FIELD            gArpFindArgField[] = {
  {
    BOOL,
    &ArpFindBySwAddress
  },
  {
    POINTER,
    &ArpFindAddressBuffer
  },
  {
    POINTER,
    &ArpFindEntryLength
  },
  {
    POINTER,
    &ArpFindEntryCount
  },
  {
    POINTER,
    &ArpFindEntries
  },
  {
    BOOL,
    &ArpFindRefresh
  },
  {
    POINTER,
    &ArpFindStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpFind_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpFind Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_ARP_PROTOCOL  *Arp;

  Arp = (EFI_ARP_PROTOCOL *) ClientInterface;

  *ArpFindStatus = Arp->Find (
                          Arp,
                          ArpFindBySwAddress,
                          ArpFindAddressBuffer,
                          ArpFindEntryLength,
                          ArpFindEntryCount,
                          ArpFindEntries,
                          ArpFindRefresh
                          );
  return EFI_SUCCESS;
}

//
// Arp.Delete
//
static BOOLEAN    ArpDeleteBySwAddress;
static VOID       *ArpDeleteAddressBuffer;
static EFI_STATUS *ArpDeleteStatus;

ENTS_ARG_FIELD    gArpDeleteArgField[] = {
  {
    BOOL,
    &ArpDeleteBySwAddress
  },
  {
    POINTER,
    &ArpDeleteAddressBuffer
  },
  {
    POINTER,
    &ArpDeleteStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpDelete_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpDelete Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_ARP_PROTOCOL  *Arp;

  Arp = (EFI_ARP_PROTOCOL *) ClientInterface;

  *ArpDeleteStatus = Arp->Delete (
                            Arp,
                            ArpDeleteBySwAddress,
                            ArpDeleteAddressBuffer
                            );
  return EFI_SUCCESS;
}

//
// Arp.Flush
//
static EFI_STATUS *ArpFlushStatus;

ENTS_ARG_FIELD    gArpFlushArgField[] = {
  {
    POINTER,
    &ArpFlushStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpFlush_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpFlush Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_ARP_PROTOCOL  *Arp;

  Arp             = (EFI_ARP_PROTOCOL *) ClientInterface;

  *ArpFlushStatus = Arp->Flush (Arp);
  return EFI_SUCCESS;
}

//
// Arp.Request
//
static VOID       *ArpRequestTargetSwAddress;
static EFI_EVENT  ArpRequestResolvedEvent;
static VOID       *ArpRequestTargetHwAddress;
static EFI_STATUS *ArpRequestStatus;

ENTS_ARG_FIELD    gArpRequestArgField[] = {
  {
    POINTER,
    &ArpRequestTargetSwAddress
  },
  {
    OCTETN,
    &ArpRequestResolvedEvent
  },
  {
    POINTER,
    &ArpRequestTargetHwAddress
  },
  {
    POINTER,
    &ArpRequestStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpRequest_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpRequest Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_ARP_PROTOCOL  *Arp;

  Arp = (EFI_ARP_PROTOCOL *) ClientInterface;

  *ArpRequestStatus = Arp->Request (
                            Arp,
                            ArpRequestTargetSwAddress,
                            ArpRequestResolvedEvent,
                            ArpRequestTargetHwAddress
                            );
  return EFI_SUCCESS;
}

//
// Arp.Cancel
//
static VOID       *ArpCancelTargetSwAddress;
static EFI_EVENT  ArpCancelResolvedEvent;
static EFI_STATUS *ArpCancelStatus;

ENTS_ARG_FIELD    gArpCancelArgField[] = {
  {
    POINTER,
    &ArpCancelTargetSwAddress
  },
  {
    OCTETN,
    &ArpCancelResolvedEvent
  },
  {
    POINTER,
    &ArpCancelStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpCancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpCancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_ARP_PROTOCOL  *Arp;

  Arp = (EFI_ARP_PROTOCOL *) ClientInterface;

  *ArpCancelStatus = Arp->Cancel (
                            Arp,
                            ArpCancelTargetSwAddress,
                            ArpCancelResolvedEvent
                            );
  return EFI_SUCCESS;
}
