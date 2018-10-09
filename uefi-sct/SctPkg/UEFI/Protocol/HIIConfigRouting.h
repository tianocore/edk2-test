/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  HIIConfigRouting.h

Abstract:

  HII ConfigRouting Protocol from the UEFI 2.1 specification.

--*/

#ifndef _HII_CONFIG_ROUTING_PROTOCOL_H_
#define _HII_CONFIG_ROUTING_PROTOCOL_H_

//
// Global ID for the HII ConfigRouting Protocol
//
#define EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID \
  {0x587e72d7, 0xcc50, 0x4f79, {0x82, 0x09, 0xca, 0x29, 0x1f, 0xc1, 0xa1, 0x0f }}

//typedef CHAR16* EFI_STRING;

typedef struct _EFI_HII_CONFIG_ROUTING_PROTOCOL EFI_HII_CONFIG_ROUTING_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_HII_EXTRACT_CONFIG) (
  IN  CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
  IN  CONST EFI_STRING                      Request,
  OUT       EFI_STRING                      *Progress,
  OUT       EFI_STRING                      *Results
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_EXPORT_CONFIG) (
  IN  CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
  OUT       EFI_STRING                      *Results
  );
	
typedef
EFI_STATUS
(EFIAPI *EFI_HII_ROUTE_CONFIG) (
  IN  CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
  IN  CONST EFI_STRING                      Configuration,
  OUT       EFI_STRING                      *Progress
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_BLOCK_TO_CONFIG) (
  IN     CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
  IN     CONST EFI_STRING                      ConfigRequest,
  IN OUT CONST UINT8                           *Block,
  IN OUT       UINTN                           BlockSize,
  OUT          EFI_STRING                      *Config,
  OUT          EFI_STRING                      *Progress
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_CONFIG_TO_BLOCK) (
  IN  CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
  IN  CONST EFI_STRING                      ConfigResp,
  IN  CONST UINT8                           *Block,
  IN  CONST UINTN                           *BlockSize,
  OUT       EFI_STRING                      *Progress
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_ALT_CFG) (
  IN  CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
  IN  CONST EFI_STRING                      ConfigResp,
  IN  CONST EFI_GUID                        *Guid,
  IN  CONST EFI_STRING                      Name,
  IN  CONST EFI_DEVICE_PATH_PROTOCOL        *DevicePath,
  IN  CONST UINT16                          *AltCfgId,
  OUT       EFI_STRING                      *AltCfgResp
);


struct _EFI_HII_CONFIG_ROUTING_PROTOCOL {
  EFI_HII_EXTRACT_CONFIG     ExtractConfig;
  EFI_HII_EXPORT_CONFIG      ExportConfig;
  EFI_HII_ROUTE_CONFIG       RouteConfig;
  EFI_HII_BLOCK_TO_CONFIG    BlockToConfig;
  EFI_HII_CONFIG_TO_BLOCK    ConfigToBlock;
  EFI_HII_GET_ALT_CFG        GetAltCfg;
};

extern EFI_GUID  gBlackBoxEfiHIIConfigRoutingProtocolGuid;

#endif

