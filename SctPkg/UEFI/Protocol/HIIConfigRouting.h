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
{ 0x587e72d7, 0xcc50, 0x4f79, 0x82, 0x09, 0xca, 0x29, 0x1f, 0xc1, 0xa1, 0x0f }

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

