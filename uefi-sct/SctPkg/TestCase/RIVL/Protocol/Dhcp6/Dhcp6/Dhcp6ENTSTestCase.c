/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Dhcp6ENTSTestCase.c

Abstract:

--*/

#include "Dhcp6ENTSTestCase.h"

//
// DHCP message types
//
enum {
  DHCP6_MSG_SOLICIT          = 1,
  DHCP6_MSG_ADVERTISE        = 2,
  DHCP6_MSG_REQUEST          = 3,
  DHCP6_MSG_CONFIRM          = 4,
  DHCP6_MSG_RENEW            = 5,
  DHCP6_MSG_REBIND           = 6,
  DHCP6_MSG_REPLY            = 7,
  DHCP6_MSG_RELEASE          = 8,
  DHCP6_MSG_DECLINE          = 9,
  DHCP6_MSG_RECONFIGURE      = 10,
  DHCP6_MSG_INFO_REQUEST     = 11,
};

//
// Dhcp6.GetModeData
//
static EFI_DHCP6_MODE_DATA   *GetModeDataDhcp6ModeData;
static EFI_DHCP6_CONFIG_DATA *GetModeDataDhcp6ConfigData;
static EFI_STATUS            *GetModeDataDhcp6Status;

ENTS_ARG_FIELD               gDhcp6GetModeDataArgField[] = {
  {
    POINTER,
    &GetModeDataDhcp6ModeData
  },
  {
    POINTER,
    &GetModeDataDhcp6ConfigData
  },
  {
    POINTER,
    &GetModeDataDhcp6Status
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL  *Dhcp6;

  Dhcp6 = (EFI_DHCP6_PROTOCOL *) ClientInterface;

  *GetModeDataDhcp6Status = Dhcp6->GetModeData (
                                    Dhcp6,
                                    (EFI_DHCP6_MODE_DATA *)   GetModeDataDhcp6ModeData,
                                    (EFI_DHCP6_CONFIG_DATA *) GetModeDataDhcp6ConfigData
                                    );
  return EFI_SUCCESS;
}

//
// Define Call Back Function
//
static
EFI_STATUS
Dhcp6CallBackFunc_Abort (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_STATE         CurrentState,
  IN EFI_DHCP6_EVENT         Dhcp6Event,
  IN EFI_DHCP6_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP6_PACKET       **NewPacket OPTIONAL
  );

static
EFI_STATUS
Dhcp6CallBackFunc_DoNothing (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_STATE         CurrentState,
  IN EFI_DHCP6_EVENT         Dhcp6Event,
  IN EFI_DHCP6_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP6_PACKET       **NewPacket OPTIONAL
  );

static
EFI_STATUS
Dhcp6CallBackFunc_AbortAfterBound (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_STATE         CurrentState,
  IN EFI_DHCP6_EVENT         Dhcp6Event,
  IN EFI_DHCP6_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP6_PACKET       **NewPacket OPTIONAL
  );

static EFI_DHCP6_CALLBACK Dhcp6CallBackFuncList[] = {
  NULL,
  Dhcp6CallBackFunc_Abort,
  Dhcp6CallBackFunc_DoNothing,
  Dhcp6CallBackFunc_AbortAfterBound
};

static
EFI_STATUS
Dhcp6CallBackFunc_Abort (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_STATE         CurrentState,
  IN EFI_DHCP6_EVENT         Dhcp6Event,
  IN EFI_DHCP6_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP6_PACKET       **NewPacket OPTIONAL
  )
{
  EntsPrint (L"Abort DHCP process\n");
  return EFI_ABORTED;
}

static
EFI_STATUS
Dhcp6CallBackFunc_DoNothing (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_STATE         CurrentState,
  IN EFI_DHCP6_EVENT         Dhcp6Event,
  IN EFI_DHCP6_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP6_PACKET       **NewPacket OPTIONAL
  )
{ EFI_STATUS                 Status;

  Status = EFI_ABORTED;
  (*((int *)Context))++;
  
  switch ( Dhcp6Event )
  {
    case Dhcp6SendSolicit:
    	 EntsPrint (L"Dhcp6SendSolicit\n");
	     if((CurrentState == Dhcp6Init) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_SOLICIT) )
		       {
		         Status = EFI_SUCCESS;
		       }
	     break;
	  
	   case Dhcp6RcvdAdvertise:
	   	 EntsPrint (L"Dhcp6RcvdAdvertise\n");
	     if((CurrentState == Dhcp6Selecting) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_ADVERTISE))
		       {
		         Status = EFI_SUCCESS;  
		       }
	     break;
	     
    case Dhcp6SelectAdvertise:
    	 EntsPrint (L"Dhcp6SelectAdvertise\n");
	     if((CurrentState == Dhcp6Selecting) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_ADVERTISE))
		       {
		         Status = EFI_SUCCESS;  
		       }
	     break;
	     
	   case Dhcp6SendRequest:
	   	 EntsPrint (L"Dhcp6SendRequest\n");
	     if ((CurrentState == Dhcp6Selecting) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_REQUEST))
	         {
		          Status = EFI_SUCCESS;
		        }
		    break;
		    
	   case Dhcp6RcvdReply:
	   	 EntsPrint (L"Dhcp6RecvdReply\n");
	     if ((CurrentState == Dhcp6Requesting) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_REPLY))
	         {
		          Status = EFI_SUCCESS;
		        }
	     if ((CurrentState == Dhcp6Declining) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_REPLY))
	         {
		          Status = EFI_SUCCESS;
		        }
	     if ((CurrentState == Dhcp6Releasing) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_REPLY))
	         {
		          Status = EFI_SUCCESS;
		        }
	     if ((CurrentState == Dhcp6Renewing) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_REPLY))
	         {
		          Status = EFI_SUCCESS;
		        }
	     if ((CurrentState == Dhcp6Rebinding) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_REPLY))
	         {
		          Status = EFI_SUCCESS;
		        }
		    break;
		    
	   case Dhcp6SendDecline:
	   	 EntsPrint (L"Dhcp6SendDecline\n");
	     if ((CurrentState == Dhcp6Bound) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_DECLINE))
	         {
		          Status = EFI_SUCCESS;		        }
		    break;
		    
	   case Dhcp6SendRelease:
	   	 EntsPrint (L"Dhcp6SendRelease\n");
	     if ((CurrentState == Dhcp6Bound) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_RELEASE))
	         {
		          Status = EFI_SUCCESS;
		        } 
    		break;
    		
	   case Dhcp6EnterRenewing:
	   	 EntsPrint (L"Dhcp6EnterRenewing\n");
	     if ((CurrentState == Dhcp6Bound) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_RENEW))
	         {
		          Status = EFI_SUCCESS;
		        } 
		    break;
		    
	   case Dhcp6EnterRebinding:
	   	 EntsPrint (L"Dhcp6EnterRebinding\n");
	     if ((CurrentState == Dhcp6Bound) && (Packet->Dhcp6.Header.MessageType == DHCP6_MSG_REBIND))
	         {
		          Status = EFI_SUCCESS;
		        } 	
	     break;
	     
    default: Status = EFI_ABORTED;
    
  }
  return Status;
}

static
EFI_STATUS
Dhcp6CallBackFunc_AbortAfterBound (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_STATE         CurrentState,
  IN EFI_DHCP6_EVENT         Dhcp6Event,
  IN EFI_DHCP6_PACKET        * Packet, OPTIONAL
  OUT EFI_DHCP6_PACKET       **NewPacket OPTIONAL
  )
{
  EFI_STATUS                   Status;

  switch ( Dhcp6Event )
  {
    case Dhcp6EnterRenewing:
    case Dhcp6EnterRebinding:
    case Dhcp6SendRelease:
    case Dhcp6SendDecline:
      EntsPrint (L"Abort DHCP process\n");
      Status = EFI_ABORTED;
      break;
    default: Status = EFI_SUCCESS;
  }  
  return Status;
}

//
//
// Dhcp6.Configure
//
static EFI_DHCP6_CONFIG_DATA  *ConfigureDhcp6CfgData;
static EFI_STATUS             *ConfigureDhcp6Status;

ENTS_ARG_FIELD                gDhcp6ConfigArgField[] = {
  {
    POINTER,
    &ConfigureDhcp6CfgData
  },
  {
    POINTER,
    &ConfigureDhcp6Status
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6Config_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Config Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL    *Dhcp6;
  EFI_DHCP6_CONFIG_DATA *Cfg;
  INTN                  CallbackIndex;

  Dhcp6 = (EFI_DHCP6_PROTOCOL *)    ClientInterface;
  Cfg   = (EFI_DHCP6_CONFIG_DATA *) ConfigureDhcp6CfgData;
  if (Cfg != NULL) {
    CallbackIndex       = (INTN) (Cfg->Dhcp6Callback);
    Cfg->Dhcp6Callback  = Dhcp6CallBackFuncList[CallbackIndex];
  }

  *ConfigureDhcp6Status = Dhcp6->Configure (
                                  Dhcp6,
                                  Cfg
                                  );
  return EFI_SUCCESS;
}

//
// Dhcp6.Start
//
static EFI_STATUS *StartDhcp6Status;

ENTS_ARG_FIELD    gDhcp6StartArgField[] = {
  {
    POINTER,
    &StartDhcp6Status
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6Start_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Start Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL  *Dhcp6;

  Dhcp6 = (EFI_DHCP6_PROTOCOL *) ClientInterface;

  *StartDhcp6Status = Dhcp6->Start (
                              Dhcp6                             
                              );
  return EFI_SUCCESS;
}

//
// Define Info Call Back Function
//
static
EFI_STATUS
Dhcp6InfoCallBackFunc_Abort (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_PACKET        * Packet
  );

static
EFI_STATUS
Dhcp6InfoCallBackFunc_DoNothing (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_PACKET        * Packet
  );

static EFI_DHCP6_INFO_CALLBACK Dhcp6InfoCallBackFuncList[] = {
  NULL,
  Dhcp6InfoCallBackFunc_Abort,
  Dhcp6InfoCallBackFunc_DoNothing
};

static
EFI_STATUS
Dhcp6InfoCallBackFunc_Abort (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_PACKET        * Packet
  )
{
  //EFI_DHCP6_STATE *State;

  //BUGBUG
  //if (Context != NULL) {
  //  State   = (EFI_DHCP6_STATE *) Context;
  //  *State  = CurrentState;
  //}

  EntsPrint (L"Abort DHCP process\n");
  return EFI_ABORTED;
}

static
EFI_STATUS
Dhcp6InfoCallBackFunc_DoNothing (
  IN EFI_DHCP6_PROTOCOL      * This,
  IN VOID                    *Context,
  IN EFI_DHCP6_PACKET        * Packet
  )
{
  (*((int *)Context))=(*((int *)Context))+ 8;
  return EFI_SUCCESS;
}

//
// Dhcp6.InfoRequest
//
static BOOLEAN                        InfoRequestSendClientId;
static EFI_DHCP6_PACKET_OPTION        *InfoRequestOptionRequest;
static UINT32                         InfoRequestOptionCount;
static EFI_DHCP6_PACKET_OPTION        **InfoRequestOptionList;
static EFI_DHCP6_RETRANSMISSION       *InfoRequestRetransmission;
static EFI_EVENT                      InfoRequestTimeoutEvent;
static EFI_DHCP6_INFO_CALLBACK        InfoRequestReplyCallBack;
static VOID                           *InfoRequestCallbackContext;
static EFI_STATUS                     *InfoRequestStatus;

ENTS_ARG_FIELD                gDhcp6InfoRequestArgField[] = {
  {
    BOOL,
    &InfoRequestSendClientId
  },
  {
    POINTER,
    &InfoRequestOptionRequest
  },
  {
    OCTET4,
    &InfoRequestOptionCount
  },
  {
    POINTER,
    &InfoRequestOptionList
  },
  {
    POINTER,
    &InfoRequestRetransmission
  },
  {
    OCTETN,
    &InfoRequestTimeoutEvent
  },
  {
    OCTETN,
    &InfoRequestReplyCallBack
  },
  {
    POINTER,
    &InfoRequestCallbackContext
  },
  {
    POINTER,
    &InfoRequestStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6InfoRequest_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 InfoRequest Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL       *Dhcp6;
  UINTN                    CallBackIndex;

  Dhcp6 = (EFI_DHCP6_PROTOCOL *) ClientInterface;
  
  CallBackIndex = (UINTN) (InfoRequestReplyCallBack);
  InfoRequestReplyCallBack = Dhcp6InfoCallBackFuncList [CallBackIndex];
 
//Install Call Back Function handle
  *InfoRequestStatus = Dhcp6->InfoRequest (
                                  Dhcp6,
                                  InfoRequestSendClientId,
                                  (EFI_DHCP6_PACKET_OPTION *) InfoRequestOptionRequest,
                                  InfoRequestOptionCount,
                                  (EFI_DHCP6_PACKET_OPTION **) InfoRequestOptionList,
                                  (EFI_DHCP6_RETRANSMISSION *) InfoRequestRetransmission,
                                  InfoRequestTimeoutEvent,
                                  InfoRequestReplyCallBack,
                                  InfoRequestCallbackContext
                                  );
  return EFI_SUCCESS;
}


//
// Dhcp6.RenewRebind
//
static BOOLEAN    RenewRebindRebindRequest;
static EFI_STATUS *RenewRebindStatus;

ENTS_ARG_FIELD    gDhcp6RenewRebindArgField[] = {
  {
    BOOL,
    &RenewRebindRebindRequest
  },
  {
    POINTER,
    &RenewRebindStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6RenewRebind_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 RenewRebind Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL  *Dhcp6;

  Dhcp6 = (EFI_DHCP6_PROTOCOL *) ClientInterface;

  *RenewRebindStatus = Dhcp6->RenewRebind (
                                Dhcp6,
                                RenewRebindRebindRequest
                                );
  return EFI_SUCCESS;
}

//
//Dhcp6.Decline
//
static UINT32 DeclineAddressCount;
static EFI_IPv6_ADDRESS *DeclineAddresses;
static EFI_STATUS *DeclineStatus;

ENTS_ARG_FIELD    gDhcp6DeclineArgField[] = {
  {
    OCTET4,
    &DeclineAddressCount
  },
  {
    POINTER,
    &DeclineAddresses
  },  
  {
    POINTER,
    &DeclineStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6Decline_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Decline Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL  *Dhcp6;

  Dhcp6 = (EFI_DHCP6_PROTOCOL *) ClientInterface;

  *DeclineStatus = Dhcp6->Decline (
                                Dhcp6,
                                DeclineAddressCount,
                                (EFI_IPv6_ADDRESS *) DeclineAddresses
                                );
  return EFI_SUCCESS;
}

//
// Dhcp6.Release
//
static UINT32        ReleaseAddressCount;
static EFI_IPv6_ADDRESS *ReleaseAddresses;
static EFI_STATUS *ReleaseStatus;
ENTS_ARG_FIELD    gDhcp6ReleaseArgField[] = {
  {
    OCTET4,
    &ReleaseAddressCount
  },
  {
    POINTER,
    &ReleaseAddresses
  },
  {
    POINTER,
    &ReleaseStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6Release_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Release Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL  *Dhcp6;

  Dhcp6           = (EFI_DHCP6_PROTOCOL *) ClientInterface;

  *ReleaseStatus  = Dhcp6->Release (Dhcp6,
                                    ReleaseAddressCount,
                                    ReleaseAddresses
                                    );

  return EFI_SUCCESS;
}

//
// Dhcp6.Stop
//
static EFI_STATUS *StopStatus;
ENTS_ARG_FIELD    gDhcp6StopArgField[] = {
  {
    POINTER,
    &StopStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6Stop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Stop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL  *Dhcp6;

  Dhcp6       = (EFI_DHCP6_PROTOCOL *) ClientInterface;

  *StopStatus = Dhcp6->Stop (Dhcp6);

  return EFI_SUCCESS;
}

//
// Dhcp6.Parse
//
static EFI_DHCP6_PACKET         *ParsePacket;
static UINT32                   *ParseOptionCount;
static EFI_DHCP6_PACKET_OPTION  **ParsePacketOptionList;
static EFI_STATUS               *ParseStatus;

ENTS_ARG_FIELD                  gDhcp6ParseArgField[] = {
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
EFIAPI
Dhcp6Parse_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Parse Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_DHCP6_PROTOCOL  *Dhcp6;

  Dhcp6 = (EFI_DHCP6_PROTOCOL *) ClientInterface;

  *ParseStatus = Dhcp6->Parse (
                          Dhcp6,
                          ParsePacket,
                          ParseOptionCount,
                          (EFI_DHCP6_PACKET_OPTION **) ParsePacketOptionList
                          );

  return EFI_SUCCESS;
}
