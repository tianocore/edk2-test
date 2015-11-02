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

  MnpENTSTestCase.h

Abstract:

--*/

#ifndef _MANAGEDNETWORK_ENTS_TESTCASE_H_
#define _MANAGEDNETWORK_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/ManagedNetwork.h>

EFI_STATUS
MnpConfig_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Config Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpGetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpMCastIpToMac_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp MCastIpToMac Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpGroup_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Group Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpTransmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpReceive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpPoll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpTransmitMultiPacket_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp TransmitMultiPacket Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_DEVICE_ERROR - Some error happens.

--*/
;

EFI_STATUS
MnpReceiveMultiPacket_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp ReceiveMultiPacket Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpPollPattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Poll Pattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
MnpCancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gEntsRuntimeInfo;
extern UINTN          gEntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gMnpConfigArgField[];
extern ENTS_ARG_FIELD gMnpGetModeDataArgField[];
extern ENTS_ARG_FIELD gMnpMCastIpToMacArgField[];
extern ENTS_ARG_FIELD gMnpGroupArgField[];
extern ENTS_ARG_FIELD gMnpTransmitArgField[];
extern ENTS_ARG_FIELD gMnpReceiveArgField[];
extern ENTS_ARG_FIELD gMnpReceiveMultiArgField[];
extern ENTS_ARG_FIELD gMnpPollArgField[];
extern ENTS_ARG_FIELD gMnpTransmitMultiPacketArgField[];
extern ENTS_ARG_FIELD gMnpPollPattern1ArgField[];
extern ENTS_ARG_FIELD gMnpCancelArgField[];
#endif // _MANAGEDNETWORK_ENTS_TESTCASE_H_
