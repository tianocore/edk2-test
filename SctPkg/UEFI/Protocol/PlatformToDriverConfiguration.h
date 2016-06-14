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
                                                                
  Copyright (c) 2010 - 2012, Byosoft Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  PlatformToDriverConfigurationProtocol.h

Abstract:

  Platform To Driver Configuration protocol as defined in the UEFI 2.10 specification.

--*/


#ifndef _PLATFORM_TO_DRIVER_CONFIGURATION_FOR_TEST_H_
#define _PLATFORM_TO_DRIVER_CONFIGURATION_FOR_TEST_H_

//
// Global ID for the Platform To Driver Configuration Protocol
//
#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID \
    { 0x642cd590, 0x8059, 0x4c0a, { 0xa9, 0x58, 0xc5, 0xec, 0x7, 0xd2, 0x3c, 0x4b} }


typedef struct _EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL;;

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_GUID \
  { \
    0x345ecc0e, 0x0cb6, 0x4b75, 0xbb, 0x57, 0x1b, 0x12, 0x9c, 0x47, 0x33, 0x3e \
  }
 //
 //Related Definitions
 //
typedef enum { 
  EfiPlatformConfigurationActionNone                                     = 0, 
  EfiPlatformConfigurationActionStopController                           = 1, 
  EfiPlatformConfigurationActionRestartController                        = 2, 
  EfiPlatformConfigurationActionRestartPlatform                          = 3, 
  EfiPlatformConfigurationActionNvramFailed                              = 4, 
  EfiPlatformConfigurationActionMaximum 
} EFI_PLATFORM_CONFIGURATION_ACTION;


//
// Parameter Block Definition
//
typedef struct {
  CHAR8          *CLPCommand;
  UINT32         CLPCommandLength;
  CHAR8          *CLPReturnString;
  UINT32         CLPReturnStringLength;
  UINT8           CLPCmdStatus;
  UINT8           CLPErrorValue;
  UINT16         CLPMsgCode;
} EFI_CONFIGURE_CLP_PARAMETER_BLK;

//extern EFI_GUID gBlackBoxEfiParameterBlockGuid;

//
// Prototypes for the Platform To Driver Configuration Protocol
//

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY) (
  IN  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL          *This,
  IN  EFI_HANDLE                                             ControllerHandle,
  IN  EFI_HANDLE                                             ChildHandle OPTIONAL,
  IN  UINTN                                               *Instance,
  OUT EFI_GUID                                            **ParameterTypeGuid,
  OUT VOID                                                **ParameterBlock,
  OUT UINTN                                               *ParameterBlockSize
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE) (
  IN  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL          *This,
  IN  EFI_HANDLE                                             ControllerHandle,
  IN  EFI_HANDLE                                             ChildHandle OPTIONAL,
  IN  UINTN                                                  *Instance,
  IN  EFI_GUID                                               *ParameterTypeGuid,
  IN  VOID                                                   *ParameterBlock,
  IN  UINTN                                                  ParameterBlockSize,
  IN  EFI_PLATFORM_CONFIGURATION_ACTION                      ConfigurationAction
  );

//
// Interface structure for the Platform To Driver Configuration Protocol
//
struct _EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL {
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY       Query;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE    Response;
};

extern EFI_GUID gBlackBoxEfiPlatformToDriverConfigurationProtocolGuid;
extern EFI_GUID gBlackBoxEfiPlatformToDriverConfigurationClpGuid;


#endif /* _PLATFORM_TO_DRIVER_CONFIGURATION_FOR_TEST_H_ */
