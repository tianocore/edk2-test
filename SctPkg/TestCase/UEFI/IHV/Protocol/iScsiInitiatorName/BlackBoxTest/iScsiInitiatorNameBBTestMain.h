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

#define IHV_ISCSI_INITIATOR_NAME_PROTOCOL_GUID \
  { 0x3f10cfd2, 0x6cb6, 0x4a2b, { 0x91, 0x9a, 0xb6, 0x3b, 0x83, 0x9a, 0x3, 0x63 } }


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
  { 0xb33e697e, 0x4e71, 0x4c98, { 0x84, 0xc6, 0x45, 0x31, 0xfb, 0x78, 0xc0, 0x86 } }

#define ISCSI_INITIATORNAME_PROTOCOL_GET_FUNCTION_GUID \
  { 0x73a08d82, 0x470c, 0x41f1, { 0xa5, 0x1a, 0x3e, 0x2, 0xf1, 0xa9, 0x47, 0x72 } }

#define ISCSI_INITIATORNAME_PROTOCOL_SET_FUNCTION_GUID \
  { 0x2b80b048, 0xa611, 0x4b9f, { 0x82, 0x12, 0xf9, 0xe5, 0x6a, 0x53, 0x5e, 0x4f } }

#define ISCSI_INITIATORNAME_PROTOCOL_GET_CONFORMANCE_GUID \
  { 0x2c77d11b, 0x8d7d, 0x4559, { 0xbd, 0x73, 0x65, 0xe0, 0x11, 0xab, 0x69, 0x98 } }

#define ISCSI_INITIATORNAME_PROTOCOL_SET_CONFORMANCE_GUID \
  { 0x75905aa6, 0x3d6d, 0x4982, { 0xbc, 0x9b, 0x8f, 0xb0, 0xba, 0xf8, 0x99, 0x84 } }

#endif
