/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
EFIAPI
InitializeHIIConfigAccessBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
EFIAPI
UnloadHIIConfigAccessBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
/*
EFI_STATUS
EFIAPI
BBTestUnitTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
*/
EFI_STATUS
EFIAPI
BBTestExtractConfigConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRouteConfigConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
/*  
EFI_STATUS
EFIAPI
BBTestCallBackConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
*/  
EFI_STATUS
EFIAPI
BBTestExtractConfigFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRouteConfigFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
/*   
EFI_STATUS
EFIAPI
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
