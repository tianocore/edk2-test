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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  HIIConfigRoutingBBTestMain.h

Abstract:

  Test Driver of HII Config Routing Protocol

--*/
#ifndef _HII_CONFIG_ROUTING_BBTEST_H_
#define _HII_CONFIG_ROUTING_BBTEST_H_

#define __UEFI_INTERNAL_FORMREPRESENTATION_H__
#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/Hii.h>
#include <UEFI/Protocol/HIIConfigRouting.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  EFI_HII_CONFIG_ROUTING_PROTOCOL_TEST_REVISION    0x00010000

#define TESTBLOCKZISE  1024


EFI_STATUS
InitializeBBTestHIIConfigRouting (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestHIIConfigRoutingProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//
/*
EFI_STATUS
BBTestUnitAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
*/
EFI_STATUS
BBTestExtractConfigFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestExportConfigFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestRouteConfigFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestBlockToConfigFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestConfigToBlockFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetAltCfgFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestExtractConfigConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestExportConfigConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestRouteConfigConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestBlockToConfigConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestConfigToBlockConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetAltCfgConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Entry GUIDs
//

#define HII_CONFIG_ROUTING_PROTOCOL_EXTRACT_CONFIG_FUNCTION_AUTO_GUID \
{ 0xce3459f7, 0x60f1, 0x443d, { 0xb4, 0x91, 0x91, 0x68, 0x9c, 0x9c, 0x6d, 0x9b } }

#define HII_CONFIG_ROUTING_PROTOCOL_EXPORT_CONFIG_FUNCTION_AUTO_GUID \
{ 0xc28dcae3, 0x7110, 0x40f0, { 0xac, 0xb0, 0xa, 0xe7, 0x55, 0x5a, 0xa9, 0xb } }

#define HII_CONFIG_ROUTING_PROTOCOL_ROUTE_CONFIG_FUNCTION_AUTO_GUID \
{ 0x2171b161, 0xf840, 0x40bc, { 0x94, 0x2b, 0xed, 0x74, 0x21, 0xa, 0x72, 0x27 } }

#define HII_CONFIG_ROUTING_PROTOCOL_BLOCK_TO_CONFIG_FUNCTION_AUTO_GUID \
{ 0x95aa4e37, 0x50ca, 0x48a9, { 0x93, 0x51, 0x9c, 0xbb, 0xd8, 0xe7, 0xaa, 0x75 } }

#define HII_CONFIG_ROUTING_PROTOCOL_CONFIG_TO_BLOCK_FUNCTION_AUTO_GUID \
{ 0xdd03468, 0x95d0, 0x4049, { 0xb4, 0x43, 0x78, 0xfc, 0x9d, 0xf2, 0xa3, 0x6d } }

#define HII_CONFIG_ROUTING_PROTOCOL_GET_ALT_CFG_FUNCTION_AUTO_GUID \
{ 0xa12826e8, 0x864a, 0x4822, { 0xba, 0x52, 0x85, 0x3a, 0x28, 0xe7, 0xc0, 0x6a } }

#define HII_CONFIG_ROUTING_PROTOCOL_EXTRACT_CONFIG_CONFORMANCE_AUTO_GUID \
{ 0x1cefb84a, 0xebd9, 0x483b, { 0x8e, 0xc2, 0x28, 0xe6, 0x9b, 0x3e, 0x75, 0x30 } }

#define HII_CONFIG_ROUTING_PROTOCOL_EXPORT_CONFIG_CONFORMANCE_AUTO_GUID \
{ 0x4db159f1, 0xca3b, 0x4517, { 0xa3, 0x25, 0x9d, 0xf8, 0x77, 0x15, 0x52, 0x87 } }

#define HII_CONFIG_ROUTING_PROTOCOL_ROUTE_CONFIG_CONFORMANCE_AUTO_GUID \
{ 0x446c6b3, 0xd3e5, 0x4519, { 0x9e, 0x29, 0xb4, 0x8f, 0xd6, 0x1f, 0xeb, 0xc1 } }

#define HII_CONFIG_ROUTING_PROTOCOL_BLOCK_TO_CONFIG_CONFORMANCE_AUTO_GUID \
{ 0x3d77b4b1, 0x9e60, 0x40d7, { 0xb4, 0xcd, 0x2c, 0x21, 0xbb, 0x4a, 0x48, 0x91 } }

#define HII_CONFIG_ROUTING_PROTOCOL_CONFIG_TO_BLOCK_CONFORMANCE_AUTO_GUID \
{ 0xcd94f3d7, 0x2687, 0x42aa, { 0xbf, 0x8b, 0x86, 0x5b, 0xf9, 0xdf, 0x93, 0xd8 } }

#define HII_CONFIG_ROUTING_PROTOCOL_GET_ALT_CFG_CONFORMANCE_AUTO_GUID \
{ 0x0748927e, 0xc4eb, 0x4dc0, { 0xaf, 0xac, 0x37, 0xf5, 0x52, 0x99, 0xc8, 0x13 } }

//
// Assistant Function 
//

EFI_STATUS
MultiAltRespToMultiReq (
  IN       EFI_STRING                           Resp,
  IN OUT   EFI_STRING                           Req
);

EFI_STATUS
MultiAltRespToMultiResp (
  IN       EFI_STRING                           Resp1,
  IN OUT   EFI_STRING                           Resp2
  );

EFI_STATUS
MultiAltRespToReq(
  IN       EFI_STRING                           Resp,
  IN OUT   EFI_STRING                           Req
  );

EFI_STATUS
MultiAltRespToResp (
  IN       EFI_STRING                           Resp1,
  IN OUT   EFI_STRING                           Resp2
  );

#define EFI_HII_DEFAULT_CLASS_STANDARD       0x0000
#define EFI_HII_DEFAULT_CLASS_MANUFACTURING  0x0001
#define EFI_HII_DEFAULT_CLASS_SAFE           0x0002
#define EFI_HII_DEFAULT_CLASS_PLATFORM_BEGIN 0x4000
#define EFI_HII_DEFAULT_CLASS_PLATFORM_END   0x7fff
#define EFI_HII_DEFAULT_CLASS_HARDWARE_BEGIN 0x8000
#define EFI_HII_DEFAULT_CLASS_HARDWARE_END   0xbfff
#define EFI_HII_DEFAULT_CLASS_FIRMWARE_BEGIN 0xc000
#define EFI_HII_DEFAULT_CLASS_FIRMWARE_END   0xffff

#endif

