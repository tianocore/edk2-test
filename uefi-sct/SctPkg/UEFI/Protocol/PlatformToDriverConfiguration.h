/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
