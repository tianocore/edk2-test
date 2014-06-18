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
