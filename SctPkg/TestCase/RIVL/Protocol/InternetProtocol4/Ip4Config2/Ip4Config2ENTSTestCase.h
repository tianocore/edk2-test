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

  Ip4Confi2gENTSTestCase.h

Abstract:

--*/

#ifndef _IP4_CONFIG_ENTS_TESTCASE_H_
#define _IP4_CONFIG_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
//#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
//#include <Library/EntsLib.h>
#include <UEFI/Protocol/Ip4.h>

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
;

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
;

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
;

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
;

extern CHAR16         *gIp4Config2RuntimeInfo;
extern UINTN          gIp4Config2RuntimeInfoSize;

extern ENTS_ARG_FIELD gIp4Config2SetDataArgField[];
extern ENTS_ARG_FIELD gIp4Config2GetDataArgField[];
extern ENTS_ARG_FIELD gIp4Config2RegisterDataNotifyArgField[];
extern ENTS_ARG_FIELD gIp4Config2UnregisterDataNotifyArgField[];

#endif
