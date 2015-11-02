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
