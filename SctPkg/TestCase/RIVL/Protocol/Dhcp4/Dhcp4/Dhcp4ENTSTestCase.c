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

  Dhcp4ENTSTestCase.c

Abstract:

--*/

#include "Dhcp4ENTSTestCase.h"

//
// Dhcp4.GetModeData
//
static EFI_DHCP4_MODE_DATA  *GetModeDataDhcp4ModeData;
static EFI_STATUS           *GetModeDataDhcp4Status;

ENTS_ARG_FIELD              gDhcp4GetModeDataArgField[] = {
  {
    POINTER,
    &GetModeDataDhcp4ModeData
  },
  {
    POINTER,
    &GetModeDataDhcp4Status
  },
  0
};

EFI_STATUS
Dhcp4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL  *Dhcp4;

  Dhcp4 = (EFI_DHCP4_PROTOCOL *) ClientInterface;

  *GetModeDataDhcp4Status = Dhcp4->GetModeData (
                                    Dhcp4,
                                    (EFI_DHCP4_MODE_DATA *) GetModeDataDhcp4ModeData
                                    );
  return EFI_SUCCESS;
}

//
// Define Call Back Function
//
static
EFI_STATUS
Dhcp4CallBackFunc_Abort (
  IN EFI_DHCP4_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP4_STATE         CurrentState,
  IN EFI_DHCP4_EVENT         Dhcp4Event,
  IN EFI_DHCP4_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP4_PACKET       **NewPacket OPTIONAL
  );

static
EFI_STATUS
Dhcp4CallBackFunc_DoNothing (
  IN EFI_DHCP4_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP4_STATE         CurrentState,
  IN EFI_DHCP4_EVENT         Dhcp4Event,
  IN EFI_DHCP4_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP4_PACKET       **NewPacket OPTIONAL
  );

static EFI_DHCP4_CALLBACK Dhcp4CallBackFuncList[] = {
  NULL,
  Dhcp4CallBackFunc_Abort,
  Dhcp4CallBackFunc_DoNothing
};

static
EFI_STATUS
Dhcp4CallBackFunc_Abort (
  IN EFI_DHCP4_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP4_STATE         CurrentState,
  IN EFI_DHCP4_EVENT         Dhcp4Event,
  IN EFI_DHCP4_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP4_PACKET       **NewPacket OPTIONAL
  )
{
  EFI_DHCP4_STATE *State;

  if (Context != NULL) {
    State   = (EFI_DHCP4_STATE *) Context;
    *State  = CurrentState;
  }

  EntsPrint (L"Abort DHCP process\n");
  return EFI_ABORTED;
}

static
EFI_STATUS
Dhcp4CallBackFunc_DoNothing (
  IN EFI_DHCP4_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP4_STATE         CurrentState,
  IN EFI_DHCP4_EVENT         Dhcp4Event,
  IN EFI_DHCP4_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP4_PACKET       **NewPacket OPTIONAL
  )
{
  return EFI_SUCCESS;
}
//
//
// Dhcp4.Configure
//
static EFI_DHCP4_CONFIG_DATA  *ConfigureDhcp4CfgData;
static EFI_STATUS             *ConfigureDhcp4Status;

ENTS_ARG_FIELD                gDhcp4ConfigArgField[] = {
  {
    POINTER,
    &ConfigureDhcp4CfgData
  },
  {
    POINTER,
    &ConfigureDhcp4Status
  },
  0
};

EFI_STATUS
Dhcp4Config_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Config Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL    *Dhcp4;
  EFI_DHCP4_CONFIG_DATA *Cfg;
  INTN                  CallbackIndex;

  Dhcp4 = (EFI_DHCP4_PROTOCOL *) ClientInterface;
  Cfg   = (EFI_DHCP4_CONFIG_DATA *) ConfigureDhcp4CfgData;
  if (Cfg != NULL) {
    CallbackIndex       = (INTN) (Cfg->Dhcp4Callback);
    Cfg->Dhcp4Callback  = Dhcp4CallBackFuncList[CallbackIndex];
  }

  *ConfigureDhcp4Status = Dhcp4->Configure (
                                  Dhcp4,
                                  Cfg
                                  );
  return EFI_SUCCESS;
}

//
// Dhcp4.Start
//
static EFI_EVENT  StartCompletionEvent;
static EFI_STATUS *StartDhcp4Status;

ENTS_ARG_FIELD    gDhcp4StartArgField[] = {
  {
    OCTETN,
    &StartCompletionEvent
  },
  {
    POINTER,
    &StartDhcp4Status
  },
  0
};

EFI_STATUS
Dhcp4Start_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Start Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL  *Dhcp4;

  Dhcp4 = (EFI_DHCP4_PROTOCOL *) ClientInterface;

  *StartDhcp4Status = Dhcp4->Start (
                              Dhcp4,
                              StartCompletionEvent
                              );
  return EFI_SUCCESS;
}

//
// Dhcp4.RenewRebind
//
static BOOLEAN    RenewRebindRebindRequest;
static EFI_EVENT  RenewRebindCompletionEvent;
static EFI_STATUS *RenewRebindStatus;

ENTS_ARG_FIELD    gDhcp4RenewRebindArgField[] = {
  {
    BOOL,
    &RenewRebindRebindRequest
  },
  {
    OCTETN,
    &RenewRebindCompletionEvent
  },
  {
    POINTER,
    &RenewRebindStatus
  },
  0
};

EFI_STATUS
Dhcp4RenewRebind_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 RenewRebind Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL  *Dhcp4;

  Dhcp4 = (EFI_DHCP4_PROTOCOL *) ClientInterface;

  *RenewRebindStatus = Dhcp4->RenewRebind (
                                Dhcp4,
                                RenewRebindRebindRequest,
                                RenewRebindCompletionEvent
                                );
  return EFI_SUCCESS;
}

//
// Dhcp4.Release
//
static EFI_STATUS *ReleaseStatus;
ENTS_ARG_FIELD    gDhcp4ReleaseArgField[] = {
  {
    POINTER,
    &ReleaseStatus
  },
  0
};

EFI_STATUS
Dhcp4Release_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Release Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL  *Dhcp4;

  Dhcp4           = (EFI_DHCP4_PROTOCOL *) ClientInterface;

  *ReleaseStatus  = Dhcp4->Release (Dhcp4);

  return EFI_SUCCESS;
}

//
// Dhcp4.Stop
//
static EFI_STATUS *StopStatus;
ENTS_ARG_FIELD    gDhcp4StopArgField[] = {
  {
    POINTER,
    &StopStatus
  },
  0
};

EFI_STATUS
Dhcp4Stop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Stop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL  *Dhcp4;

  Dhcp4       = (EFI_DHCP4_PROTOCOL *) ClientInterface;

  *StopStatus = Dhcp4->Stop (Dhcp4);

  return EFI_SUCCESS;
}

//
// Dhcp4.Build
//
static EFI_DHCP4_PACKET         *BuildSeedPacket;
static UINT32                   BuildDeleteCount;
static UINT8                    *BuildDeleteList;
static UINT32                   BuildAppendCount;
static EFI_DHCP4_PACKET_OPTION  **BuildAppendList;
static EFI_DHCP4_PACKET         **BuildNewPacket;
static EFI_STATUS               *BuildStatus;

ENTS_ARG_FIELD                  gDhcp4BuildArgField[] = {
  {
    POINTER,
    &BuildSeedPacket
  },
  {
    OCTET4,
    &BuildDeleteCount
  },
  {
    POINTER,
    &BuildDeleteList
  },
  {
    OCTET4,
    &BuildAppendCount
  },
  {
    POINTER,
    &BuildAppendList
  },
  {
    POINTER,
    &BuildNewPacket
  },
  {
    POINTER,
    &BuildStatus
  },
  0
};

EFI_STATUS
Dhcp4Build_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Build Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL  *Dhcp4;

  Dhcp4 = (EFI_DHCP4_PROTOCOL *) ClientInterface;

  *BuildStatus = Dhcp4->Build (
                          Dhcp4,
                          BuildSeedPacket,
                          BuildDeleteCount,
                          BuildDeleteList,
                          BuildAppendCount,
                          BuildAppendList,
                          BuildNewPacket
                          );
  return EFI_SUCCESS;
}

//
// Dhcp4.TransmitReceive
//
static EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN *TransmitReceiveToken;
static EFI_STATUS                       *TransmitReceiveStatus;
ENTS_ARG_FIELD                          gDhcp4TransmitReceiveArgField[] = {
  {
    POINTER,
    &TransmitReceiveToken
  },
  {
    POINTER,
    &TransmitReceiveStatus
  },
  0
};

EFI_STATUS
Dhcp4TransmitReceive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 TransmitReceive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL  *Dhcp4;

  Dhcp4 = (EFI_DHCP4_PROTOCOL *) ClientInterface;

  *TransmitReceiveStatus = Dhcp4->TransmitReceive (
                                    Dhcp4,
                                    (EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN *) TransmitReceiveToken
                                    );

  return EFI_SUCCESS;
}

//
// Dhcp4.Parse
//
static EFI_DHCP4_PACKET         *ParsePacket;
static UINT32                   *ParseOptionCount;
static EFI_DHCP4_PACKET_OPTION  *ParsePacketOptionList;
static EFI_STATUS               *ParseStatus;

ENTS_ARG_FIELD                  gDhcp4ParseArgField[] = {
  {
    POINTER,
    &ParsePacket
  },
  {
    POINTER,
    &ParseOptionCount
  },
  {
    POINTER,
    &ParsePacketOptionList
  },
  {
    POINTER,
    &ParseStatus
  },
  0
};

EFI_STATUS
Dhcp4Parse_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Parse Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP4_PROTOCOL  *Dhcp4;

  Dhcp4 = (EFI_DHCP4_PROTOCOL *) ClientInterface;

  *ParseStatus = Dhcp4->Parse (
                          Dhcp4,
                          ParsePacket,
                          ParseOptionCount,
                          (EFI_DHCP4_PACKET_OPTION **) ParsePacketOptionList
                          );

  return EFI_SUCCESS;
}
