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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  HIIConfigAccessBBTestMain.h

Abstract:

  Test Driver of HII Configuration Access Protocol header file

--*/

#ifndef _HII_CONFIG_ACCESS_BB_TEST_MAIN
#define _HII_CONFIG_ACCESS_BB_TEST_MAIN

#define __UEFI_INTERNAL_FORMREPRESENTATION_H__
#include <Base.h>
#include "SctLib.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Hii.h>
#include <UEFI/Protocol/HIIConfigAccess.h>
#include <UEFI/Protocol/HIIConfigRouting.h>


#define EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x2a85387e, 0xdcf9, 0x45e9, { 0xb3, 0x8f, 0x5d, 0xa1, 0x75, 0x41, 0xcf, 0x1a } }

#define EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x1a15df85, 0x6cc1, 0x43f2, { 0x9b, 0x86, 0x21, 0x8b, 0xd5, 0xfd, 0xf4, 0xa0 } }


//
// Entry GUIDs for Conf Test
//
#define EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xe2c3b0fe, 0xfbe9, 0x46a9, { 0xa3, 0x1b, 0xa3, 0xf3, 0x82, 0xd, 0xcf, 0x4 } }

#define EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x495c99f3, 0x231, 0x45a5, { 0xaf, 0xfa, 0xd2, 0x5c, 0x6f, 0x9a, 0x19, 0x1c } }



EFI_STATUS
InitializeHIIConfigAccessBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
UnloadHIIConfigAccessBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
/*
EFI_STATUS
BBTestUnitTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
*/
EFI_STATUS
BBTestExtractConfigConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestRouteConfigConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
/*  
EFI_STATUS
BBTestCallBackConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
*/  
EFI_STATUS
BBTestExtractConfigFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestRouteConfigFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
/*   
EFI_STATUS
BBTestCallBackFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  ); 
*/
EFI_STATUS
GetDevicePath (
  IN  EFI_HII_CONFIG_ACCESS_PROTOCOL       *ConfigAccess,
  OUT EFI_STRING                           *DevicePathStr
  );

EFI_STATUS
GetCorrespondingRequest (
  IN     EFI_STRING    MultiConfigAltResp,
  IN     EFI_STRING    DevicePath,
  IN OUT EFI_STRING    Request
  );

EFI_STATUS
GetCorrespondingResp (
  IN     EFI_STRING    MultiConfigAltResp,
  IN     EFI_STRING    DevicePath,
  IN OUT EFI_STRING    Resp
  );

EFI_STATUS
GetHIIConfigRoutingInterface (
  OUT EFI_HII_CONFIG_ROUTING_PROTOCOL    **HIIConfigRouting
  );

EFI_STATUS
MultiAltRespToMultiReq (
  IN       EFI_STRING                           Resp,
  IN OUT   EFI_STRING                           Req
  );

#endif
