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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Tcp4ENTSTestCase.h

Abstract:

--*/

#ifndef _TCP4_ENTS_TESTCASE_H_
#define _TCP4_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Tcp4.h>

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

extern CHAR16         *gTcp4EntsRuntimeInfo;
extern UINTN          gTcp4EntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gTcp4GetModeDataArgField[];
extern ENTS_ARG_FIELD gTcp4ConfigureArgField[];
extern ENTS_ARG_FIELD gTcp4RoutesArgField[];
extern ENTS_ARG_FIELD gTcp4ConnectArgField[];
extern ENTS_ARG_FIELD gTcp4AcceptArgField[];
extern ENTS_ARG_FIELD gTcp4TransmitArgField[];
extern ENTS_ARG_FIELD gTcp4ReceiveArgField[];
extern ENTS_ARG_FIELD gTcp4CloseArgField[];
extern ENTS_ARG_FIELD gTcp4CancelArgField[];
extern ENTS_ARG_FIELD gTcp4PollArgField[];

#endif // _TCP4_ENTS_TESTCASE_H_
