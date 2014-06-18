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
                                                                
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++         

Module Name:

  AdapterInfoProtocol.h

Abstract:

  Adapter Information protocol from the UEFI 2.4 specification.

--*/

#ifndef _ADAPTER_INFORMATION_PROTOCOL_H_
#define _ADAPTER_INFORMATION_PROTOCOL_H_

//
// Global ID for the Adapter Information Protocol
//
#define EFI_ADAPTER_INFORMATION_PROTOCOL_GUID \
{ 0xE5DD1403, 0xD622, 0xC24E, 0x84, 0x88, 0xC7, 0x1B, 0x17, 0xF5, 0xE8, 0x02 } 



typedef struct _EFI_ADAPTER_INFORMATION_PROTOCOL EFI_ADAPTER_INFORMATION_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_GET_INFO) (
IN EFI_ADAPTER_INFORMATION_PROTOCOL     *This,
IN EFI_GUID                             *InformationType,
OUT VOID                                **InformationBlock,
OUT UINTN                               *InformationBlockSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_SET_INFO) (
IN EFI_ADAPTER_INFORMATION_PROTOCOL     *This,
IN EFI_GUID                             *InformationType,
IN VOID                                 *InformationBlock,
IN UINTN                                InformationBlockSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES) (
IN EFI_ADAPTER_INFORMATION_PROTOCOL     *This,
OUT EFI_GUID                            **InfoTypesBuffer,
OUT UINTN                               *InfoTypesBufferCount
) ;



typedef struct _EFI_ADAPTER_INFORMATION_PROTOCOL {
EFI_ADAPTER_INFO_GET_INFO               GetInformation;
EFI_ADAPTER_INFO_SET_INFO               SetInformation;
EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES    GetSupportedTypes;
} EFI_ADAPTER_INFORMATION_PROTOCOL;


//Information Blocks  Struct

typedef struct {
  EFI_STATUS MediaState;
} EFI_ADAPTER_INFO_MEDIA_STATE;


typedef struct {
  BOOLEAN iSsciIpv4BootCapablity;
  BOOLEAN iScsiIpv6BootCapablity;
  BOOLEAN FCoeBootCapablity;
  BOOLEAN OffloadCapability;
  BOOLEAN iScsiMpioCapability;
  BOOLEAN iScsiIpv4Boot;
  BOOLEAN iScsiIpv6Boot;
  BOOLEAN FCoeBoot;
} EFI_ADAPTER_INFO_NETWORK_BOOT;


typedef struct {
  EFI_MAC_ADDRESS SanMacAddress;
} EFI_ADAPTER_INFO_SAN_MAC_ADDRESS;


extern EFI_GUID gEfiAdapterInformationProtocolGuid;

#endif

