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
