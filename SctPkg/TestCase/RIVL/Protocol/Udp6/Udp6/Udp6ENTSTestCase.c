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

  Udp6ENTSTestCase.c

Abstract:

--*/

#include "Udp6ENTSTestCase.h"

//
// Udp6.GetModeData
//
static EFI_STATUS                       *GetModeData_Status;
static EFI_UDP6_CONFIG_DATA             *GetModeData_Udp6ConfigData;
static EFI_IP6_MODE_DATA                *GetModeData_Ip6ModeData;
static EFI_MANAGED_NETWORK_CONFIG_DATA  *GetModeData_MnpConfigData;
static EFI_SIMPLE_NETWORK_MODE          *GetModeData_SnpModeData;

ENTS_ARG_FIELD                          gUdp6GetModeDataArgField[] = {
  {
    POINTER,
    &GetModeData_Udp6ConfigData
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
Udp6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_UDP6_PROTOCOL *Udp6;

  Udp6 = (EFI_UDP6_PROTOCOL *) ClientInterface;

  *GetModeData_Status = Udp6->GetModeData (
                                Udp6,
                                GetModeData_Udp6ConfigData,
                                GetModeData_Ip6ModeData,
                                GetModeData_MnpConfigData,
                                GetModeData_SnpModeData
                                );
  RecordMessage (
    &gUdp6EntsRuntimeInfo,
    &gUdp6EntsRuntimeInfoSize,
    L"Status - %r",
    *GetModeData_Status
    );
  return EFI_SUCCESS;
}

//
// Udp6.Configure
//
static EFI_STATUS               *Configure_Status;
static IN EFI_UDP6_CONFIG_DATA  *Configure_UdpConfigData;

ENTS_ARG_FIELD                  gUdp6ConfigureArgField[] = {
  {
    POINTER,
    &Configure_UdpConfigData
  },
  {
    POINTER,
    &Configure_Status
  },
  0
};

EFI_STATUS
Udp6Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_UDP6_PROTOCOL *Udp6;

  Udp6 = (EFI_UDP6_PROTOCOL *) ClientInterface;

  *Configure_Status = Udp6->Configure (
                              Udp6,
                              Configure_UdpConfigData
                              );
  RecordMessage (
    &gUdp6EntsRuntimeInfo,
    &gUdp6EntsRuntimeInfoSize,
    L"Status - %r",
    *Configure_Status
    );
  return EFI_SUCCESS;
}

//
// Udp6.Groups
//
static EFI_STATUS       *Groups_Status;
static BOOLEAN          Groups_JoinFlag;
static EFI_IPv6_ADDRESS *Groups_MulticastAddress;

ENTS_ARG_FIELD          gUdp6GroupsArgField[] = {
  {
    BOOL,
    &Groups_JoinFlag
  },
  {
    POINTER,
    &Groups_MulticastAddress
  },
  {
    POINTER,
    &Groups_Status
  },
  0
};

EFI_STATUS
Udp6Groups_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Groups Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_UDP6_PROTOCOL *Udp6;

  Udp6 = (EFI_UDP6_PROTOCOL *) ClientInterface;

  *Groups_Status = Udp6->Groups (
                          Udp6,
                          Groups_JoinFlag,
                          Groups_MulticastAddress
                          );
  RecordMessage (
    &gUdp6EntsRuntimeInfo,
    &gUdp6EntsRuntimeInfoSize,
    L"Status - %r",
    *Groups_Status
    );
  return EFI_SUCCESS;
}

//
// Udp6.Poll
//
static EFI_STATUS *Poll_Status;

ENTS_ARG_FIELD    gUdp6PollArgField[] = {
  {
    POINTER,
    &Poll_Status
  },
  0
};

EFI_STATUS
Udp6Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_UDP6_PROTOCOL *Udp6;

  Udp6          = (EFI_UDP6_PROTOCOL *) ClientInterface;

  *Poll_Status  = Udp6->Poll (Udp6);
  RecordMessage (
    &gUdp6EntsRuntimeInfo,
    &gUdp6EntsRuntimeInfoSize,
    L"Status - %r",
    *Poll_Status
    );
  return EFI_SUCCESS;
}

//
// Udp6.Receive
//
static EFI_STATUS                 *Receive_Status;
static EFI_UDP6_COMPLETION_TOKEN  *Receive_Token;

ENTS_ARG_FIELD                    gUdp6ReceiveArgField[] = {
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
Udp6Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_UDP6_PROTOCOL *Udp6;

  Udp6 = (EFI_UDP6_PROTOCOL *) ClientInterface;

  *Receive_Status = Udp6->Receive (
                            Udp6,
                            Receive_Token
                            );
  RecordMessage (
    &gUdp6EntsRuntimeInfo,
    &gUdp6EntsRuntimeInfoSize,
    L"Status - %r",
    *Receive_Status
    );
  return EFI_SUCCESS;
}

//
// Udp6.Transmit
//
static EFI_STATUS                 *Transmit_Status;
static EFI_UDP6_COMPLETION_TOKEN  *Transmit_CompletionToken;

ENTS_ARG_FIELD                    gUdp6TransmitArgField[] = {
  {
    POINTER,
    &Transmit_CompletionToken
  },
  {
    POINTER,
    &Transmit_Status
  },
  0
};

EFI_STATUS
Udp6Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_UDP6_PROTOCOL *Udp6;

  Udp6 = (EFI_UDP6_PROTOCOL *) ClientInterface;

  *Transmit_Status = Udp6->Transmit (
                            Udp6,
                            Transmit_CompletionToken
                            );
  RecordMessage (
    &gUdp6EntsRuntimeInfo,
    &gUdp6EntsRuntimeInfoSize,
    L"Status - %r",
    *Transmit_Status
    );
  return EFI_SUCCESS;
}

//
// Udp6.Cancel
//
static EFI_STATUS                 *Cancel_Status;
static EFI_UDP6_COMPLETION_TOKEN  *Cancel_Token;

ENTS_ARG_FIELD                    gUdp6CancelArgField[] = {
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
Udp6Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_UDP6_PROTOCOL *Udp6;

  Udp6 = (EFI_UDP6_PROTOCOL *) ClientInterface;

  *Cancel_Status = Udp6->Cancel (
                          Udp6,
                          Cancel_Token
                          );
  RecordMessage (
    &gUdp6EntsRuntimeInfo,
    &gUdp6EntsRuntimeInfoSize,
    L"Status - %r",
    *Cancel_Status
    );
  return EFI_SUCCESS;
}

//
// SignalRecycleEvent
//
static EFI_STATUS                 *SignalRecycleEvent_Status;
static EFI_UDP6_COMPLETION_TOKEN  *Completion_Token;

ENTS_ARG_FIELD                    gUdp6SignalRecycleEventArgField[] = {
  {
    POINTER,
    &Completion_Token
  },
  {
    POINTER,
    &SignalRecycleEvent_Status
  },
  0
};

EFI_STATUS
Udp6SignalRecycleEvent_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 SignalRecycleEvent Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_UDP6_PROTOCOL *Udp6;

  Udp6 = (EFI_UDP6_PROTOCOL *) ClientInterface;

  *SignalRecycleEvent_Status = EFI_SUCCESS;
  if (Completion_Token->Status == EFI_SUCCESS) {
    *SignalRecycleEvent_Status = tBS->SignalEvent (Completion_Token->Packet.RxData->RecycleSignal);
  }

  RecordMessage (
    &gUdp6EntsRuntimeInfo,
    &gUdp6EntsRuntimeInfoSize,
    L"Status - %r",
    *SignalRecycleEvent_Status
    );
  return EFI_SUCCESS;
}

