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

  Tcp4ENTSTestCase.c

Abstract:

--*/

#include "Tcp4ENTSTestCase.h"

//
// Tcp4.GetModeData
//
static EFI_TCP4_CONNECTION_STATE        *GetModeData_Tcp4State;
static EFI_TCP4_CONFIG_DATA             *GetModeData_Tcp4ConfigData;
static EFI_IP4_MODE_DATA                *GetModeData_Ip4ModeData;
static EFI_MANAGED_NETWORK_CONFIG_DATA  *GetModeData_MnpConfigData;
static EFI_SIMPLE_NETWORK_MODE          *GetModeData_SnpModeData;
static EFI_STATUS                       *GetModeData_Status;

ENTS_ARG_FIELD                          gTcp4GetModeDataArgField[] = {
  {
    POINTER,
    &GetModeData_Tcp4State
  },
  {
    POINTER,
    &GetModeData_Tcp4ConfigData
  },
  {
    POINTER,
    &GetModeData_Ip4ModeData
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
Tcp4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *GetModeData_Status = Tcp4->GetModeData (
                                Tcp4,
                                GetModeData_Tcp4State,
                                GetModeData_Tcp4ConfigData,
                                GetModeData_Ip4ModeData,
                                GetModeData_MnpConfigData,
                                GetModeData_SnpModeData
                                );

  return EFI_SUCCESS;
}

//
// Tcp4.Configure
//
static EFI_TCP4_CONFIG_DATA *Configure_Tcp4ConfigData;
static EFI_STATUS           *Configure_Status;

ENTS_ARG_FIELD              gTcp4ConfigureArgField[] = {
  {
    POINTER,
    &Configure_Tcp4ConfigData
  },
  {
    POINTER,
    &Configure_Status
  },
  0
};

EFI_STATUS
Tcp4Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Configure_Status = Tcp4->Configure (
                              Tcp4,
                              Configure_Tcp4ConfigData
                              );

  return EFI_SUCCESS;
}

//
// Tcp4.Routes
//
static BOOLEAN          Routes_DeleteRoute;
static EFI_IPv4_ADDRESS *Routes_SubnetAddress;
static EFI_IPv4_ADDRESS *Routes_SubnetMask;
static EFI_IPv4_ADDRESS *Routes_GatewayAddress;
static EFI_STATUS       *Routes_Status;

ENTS_ARG_FIELD          gTcp4RoutesArgField[] = {
  {
    BOOL,
    &Routes_DeleteRoute
  },
  {
    POINTER,
    &Routes_SubnetAddress
  },
  {
    POINTER,
    &Routes_SubnetMask
  },
  {
    POINTER,
    &Routes_GatewayAddress
  },
  {
    POINTER,
    &Routes_Status
  },
  0
};

EFI_STATUS
Tcp4Routes_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Routes Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Routes_Status = Tcp4->Routes (
                          Tcp4,
                          Routes_DeleteRoute,
                          Routes_SubnetAddress,
                          Routes_SubnetMask,
                          Routes_GatewayAddress
                          );

  return EFI_SUCCESS;
}

//
// Tcp4.Connect
//
static EFI_TCP4_CONNECTION_TOKEN  *Connect_ConnectionToken;
static EFI_STATUS                 *Connect_Status;

ENTS_ARG_FIELD                    gTcp4ConnectArgField[] = {
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
Tcp4Connect_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Connect Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Connect_Status = Tcp4->Connect (
                            Tcp4,
                            Connect_ConnectionToken
                            );

  return EFI_SUCCESS;
}

//
// Tcp4.Accept
//
static EFI_TCP4_LISTEN_TOKEN  *Accept_ListenToken;
static EFI_STATUS             *Accept_Status;

ENTS_ARG_FIELD                gTcp4AcceptArgField[] = {
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
Tcp4Accept_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Accept Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Accept_Status = Tcp4->Accept (
                          Tcp4,
                          Accept_ListenToken
                          );

  return EFI_SUCCESS;
}

//
// Tcp4.Transmit
//
static EFI_TCP4_IO_TOKEN  *Transmit_Token;
static EFI_STATUS         *Transmit_Status;

ENTS_ARG_FIELD            gTcp4TransmitArgField[] = {
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
Tcp4Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Transmit_Status = Tcp4->Transmit (
                            Tcp4,
                            Transmit_Token
                            );

  return EFI_SUCCESS;
}

//
// Tcp4.Receive
//
static EFI_TCP4_IO_TOKEN  *Receive_Token;
static EFI_STATUS         *Receive_Status;

ENTS_ARG_FIELD            gTcp4ReceiveArgField[] = {
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
Tcp4Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Receive_Status = Tcp4->Receive (
                            Tcp4,
                            Receive_Token
                            );

  return EFI_SUCCESS;
}

//
// Tcp4.Close
//
static EFI_TCP4_CLOSE_TOKEN *Close_Token;
static EFI_STATUS           *Close_Status;

ENTS_ARG_FIELD              gTcp4CloseArgField[] = {
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
Tcp4Close_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Close Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Close_Status = Tcp4->Close (
                          Tcp4,
                          Close_Token
                          );

  return EFI_SUCCESS;
}

//
// Tcp4.Cancel
//
static EFI_TCP4_COMPLETION_TOKEN  *Cancel_Token;
static EFI_STATUS                 *Cancel_Status;

ENTS_ARG_FIELD                    gTcp4CancelArgField[] = {
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
Tcp4Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4 = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Cancel_Status = Tcp4->Cancel (
                          Tcp4,
                          Cancel_Token
                          );

  return EFI_SUCCESS;
}

//
// Tcp4.Poll
//
static EFI_STATUS *Poll_Status;

ENTS_ARG_FIELD    gTcp4PollArgField[] = {
  {
    POINTER,
    &Poll_Status
  },
  0
};

EFI_STATUS
Tcp4Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_TCP4_PROTOCOL *Tcp4;

  Tcp4          = (EFI_TCP4_PROTOCOL *) ClientInterface;

  *Poll_Status  = Tcp4->Poll (Tcp4);

  return EFI_SUCCESS;
}
