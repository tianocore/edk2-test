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

  TimeENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "TimeENTSTestCase.h"

//
// RT.GetTime
//
static EFI_TIME               *RTGetTimeTime;
static EFI_TIME_CAPABILITIES  *RTGetTimeCapabilities;
static EFI_STATUS             *RTGetTimeStatus;

ENTS_ARG_FIELD                tRTGetTimeArgField[] = {
  {
    POINTER,
    &RTGetTimeTime
  },
  {
    POINTER,
    &RTGetTimeCapabilities
  },
  {
    POINTER,
    &RTGetTimeStatus
  },
  0
};

EFI_STATUS
RT_GetTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  GetTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTGetTimeStatus = RuntimeService->GetTime (
                                      RTGetTimeTime,
                                      RTGetTimeCapabilities
                                      );
  return EFI_SUCCESS;
}

//
// RT.SetTime
//
static EFI_TIME   *RTSetTimeTime;
static EFI_STATUS *RTSetTimeStatus;

ENTS_ARG_FIELD    tRTSetTimeArgField[] = {
  {
    POINTER,
    &RTSetTimeTime
  },
  {
    POINTER,
    &RTSetTimeStatus
  },
  0
};

EFI_STATUS
RT_SetTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SetTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService    = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTSetTimeStatus  = RuntimeService->SetTime (RTSetTimeTime);
  return EFI_SUCCESS;
}

//
// RT.GetWakeupTime
//
static BOOLEAN    *RTGetWakeupTimeEnabled;
static BOOLEAN    *RTGetWakeupTimePending;
static EFI_TIME   *RTGetWakeupTimeTime;
static EFI_STATUS *RTGetWakeupTimeStatus;

ENTS_ARG_FIELD    tRTGetWakeupTimeArgField[] = {
  {
    POINTER,
    &RTGetWakeupTimeEnabled
  },
  {
    POINTER,
    &RTGetWakeupTimePending
  },
  {
    POINTER,
    &RTGetWakeupTimeTime
  },
  {
    POINTER,
    &RTGetWakeupTimeStatus
  },
  0
};

EFI_STATUS
RT_GetWakeupTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  GetWakeupTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTGetWakeupTimeStatus = RuntimeService->GetWakeupTime (
                                            RTGetWakeupTimeEnabled,
                                            RTGetWakeupTimePending,
                                            RTGetWakeupTimeTime
                                            );
  return EFI_SUCCESS;
}

//
// RT.SetWakeupTime
//
static BOOLEAN    RTSetWakeupTimeEnabled;
static EFI_TIME   *RTSetWakeupTimeTime;
static EFI_STATUS *RTSetWakeupTimeStatus;

ENTS_ARG_FIELD    tRTSetWakeupTimeArgField[] = {
  {
    BOOL,
    &RTSetWakeupTimeEnabled
  },
  {
    POINTER,
    &RTSetWakeupTimeTime
  },
  {
    POINTER,
    &RTSetWakeupTimeStatus
  },
  0
};

EFI_STATUS
RT_SetWakeupTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SetWakeupTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTSetWakeupTimeStatus = RuntimeService->SetWakeupTime (
                                            RTSetWakeupTimeEnabled,
                                            RTSetWakeupTimeTime
                                            );
  return EFI_SUCCESS;
}
