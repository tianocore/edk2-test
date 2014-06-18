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

    iScsiInitiatorNameBBTestMain.h

Abstract:

    IscsiInitiatorName Protocol (define according to the UEFI Spec 2.0 )

Revision History

--*/

#ifndef __ISCSIINITIATORNAMEBBTESTMAIN_H__
#define __ISCSIINITIATORNAMEBBTESTMAIN_H__

#include "Efi.h"
#include <UEFI/Protocol/iScsiInitiatorName.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define ISCSI_INITIATOR_NAME_PROTOCOL_TEST_REVISION    0x00010000

#define ISCSI_INITIATORNAME_MAXIMUM_SIZE  224

EFI_STATUS
BBTestGetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#define EFI_SAMPLE_BB_TEST_CATEGORY_GUID \
  { 0x3367794b, 0x363f, 0x47a0, 0x88, 0x90, 0x5b, 0xd8, 0x43, 0xdf, 0x38, 0xc0 }

#define ISCSI_INITIATORNAME_PROTOCOL_GET_FUNCTION_GUID \
  { 0xcd653384, 0x3b5f, 0x4fbe, { 0xbf, 0x8, 0x7b, 0xb1, 0xc8, 0x16, 0x27, 0xc5 } }

#define ISCSI_INITIATORNAME_PROTOCOL_SET_FUNCTION_GUID \
  { 0xe3e287a3, 0x844, 0x477b, { 0x83, 0xf9, 0x81, 0xb5, 0x5e, 0xa9, 0x94, 0x4f } }

#define ISCSI_INITIATORNAME_PROTOCOL_GET_CONFORMANCE_GUID \
  { 0x4f6d045b, 0x1cf7, 0x4036, { 0x88, 0x85, 0x2b, 0x2, 0x30, 0x0, 0xd, 0xde } }

#define ISCSI_INITIATORNAME_PROTOCOL_SET_CONFORMANCE_GUID \
  { 0x5b739f67, 0xf291, 0x46eb, { 0xb0, 0x71, 0x2c, 0xb4, 0x66, 0xba, 0x21, 0x74 } }

#endif
