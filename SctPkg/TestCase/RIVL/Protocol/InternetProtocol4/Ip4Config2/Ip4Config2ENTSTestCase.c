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
                                                                
  Copyright 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
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

