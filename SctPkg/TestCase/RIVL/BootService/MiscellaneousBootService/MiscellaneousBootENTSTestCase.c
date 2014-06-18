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

  MiscellaneousBootENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "MiscellaneousBootENTSTestCase.h"

//
// tBS.SetWatchdogTimer
//
static UINTN      BSSetWatchdogTimerTimeout;
static UINT64     BSSetWatchdogTimerWatchdogCode;
static UINTN      BSSetWatchdogTimerDataSize;
static CHAR16     *BSSetWatchdogTimerWatchdogData;
static EFI_STATUS *BSSetWatchdogTimerStatus;

ENTS_ARG_FIELD    BSSetWatchdogTimerArgField[] = {
  {
    OCTETN,
    &BSSetWatchdogTimerTimeout
  },
  {
    OCTET8,
    &BSSetWatchdogTimerWatchdogCode
  },
  {
    OCTETN,
    &BSSetWatchdogTimerDataSize
  },
  {
    POINTER,
    &BSSetWatchdogTimerWatchdogData
  },
  {
    POINTER,
    &BSSetWatchdogTimerStatus
  },
  0
};

EFI_STATUS
BS_SetWatchdogTimer_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 SetWatchdogTimer Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSSetWatchdogTimerStatus = BootService->SetWatchdogTimer (
                                            BSSetWatchdogTimerTimeout,
                                            BSSetWatchdogTimerWatchdogCode,
                                            BSSetWatchdogTimerDataSize,
                                            BSSetWatchdogTimerWatchdogData
                                            );
  return EFI_SUCCESS;
}

//
// tBS.Stall
//
static UINTN      BSStallMicroseconds;
static EFI_STATUS *BSStallStatus;

ENTS_ARG_FIELD    BSStallArgField[] = {
  {
    OCTETN,
    &BSStallMicroseconds
  },
  {
    POINTER,
    &BSStallStatus
  },
  0
};

EFI_STATUS
BS_Stall_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 Stall Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService     = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSStallStatus  = BootService->Stall (BSStallMicroseconds);
  return EFI_SUCCESS;
}

//
// tBS.CopyMem
//
static VOID     *BSCopyMemDestination;
static VOID     *BSCopyMemSource;
static UINTN    BSCopyMemLength;

ENTS_ARG_FIELD  BSCopyMemArgField[] = {
  {
    POINTER,
    &BSCopyMemDestination
  },
  {
    POINTER,
    &BSCopyMemSource
  },
  {
    OCTETN,
    &BSCopyMemLength
  },
  0
};

EFI_STATUS
BS_CopyMem_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 CopyMem Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  BootService->CopyMem (
                BSCopyMemDestination,
                BSCopyMemSource,
                BSCopyMemLength
                );
  return EFI_SUCCESS;
}

//
// tBS.SetMem
//
static VOID     *BSSetMemBuffer;
static UINTN    BSSetMemSize;
static UINT8    BSSetMemValue;

ENTS_ARG_FIELD  BSSetMemArgField[] = {
  {
    POINTER,
    &BSSetMemBuffer
  },
  {
    OCTETN,
    &BSSetMemSize
  },
  {
    OCTET1,
    &BSSetMemValue
  },
  0
};

EFI_STATUS
BS_SetMem_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 SetMem Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  BootService->SetMem (
                BSSetMemBuffer,
                BSSetMemSize,
                BSSetMemValue
                );
  return EFI_SUCCESS;
}
