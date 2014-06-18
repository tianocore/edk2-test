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

  DriverConfigurationProtocol.h

Abstract:

  EFI Driver Configuration Protocol

--*/

#ifndef _DRIVER_CONFIGURATION_PROTOCOL_H_
#define _DRIVER_CONFIGURATION_PROTOCOL_H_

//
// Global ID for the Driver Configuration Protocol
//
#define EFI_DRIVER_CONFIGURATION_PROTOCOL_GUID    \
  { 0x107a772b, 0xd5e1, 0x11d4, 0x9a, 0x46, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d }

typedef struct _EFI_DRIVER_CONFIGURATION_PROTOCOL EFI_DRIVER_CONFIGURATION_PROTOCOL;;

typedef enum {
  EfiDriverConfigurationActionNone               = 0,
  EfiDriverConfigurationActionStopController     = 1,
  EfiDriverConfigurationActionRestartController  = 2,
  EfiDriverConfigurationActionRestartPlatform    = 3,
  EfiDriverConfigurationActionMaximum
} EFI_DRIVER_CONFIGURATION_ACTION_REQUIRED;

#define EFI_DRIVER_CONFIGURATION_SAFE_DEFAULTS           0x00000000
#define EFI_DRIVER_CONFIGURATION_MANUFACTURING_DEFAULTS  0x00000001
#define EFI_DRIVER_CONFIGURATION_CUSTOM_DEFAULTS         0x00000002
#define EFI_DRIVER_CONFIGURATION_PERORMANCE_DEFAULTS     0x00000003

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_CONFIGURATION_SET_OPTIONS) (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL          *This,
  IN  EFI_HANDLE                                 ControllerHandle,
  IN  EFI_HANDLE                                 ChildHandle  OPTIONAL,
  IN  CHAR8                                      *Language,
  OUT EFI_DRIVER_CONFIGURATION_ACTION_REQUIRED   *ActionRequired
  );
/*++

  Routine Description:
    Allows the user to set controller specific options for a controller that a
    driver is currently managing.

  Arguments:
    This             - A pointer to the EFI_DRIVER_CONFIGURATION_ PROTOCOL instance.
    ControllerHandle - The handle of the controller to set options on.
    ChildHandle      - The handle of the child controller to set options on.  This
                       is an optional parameter that may be NULL.  It will be NULL
                       for device drivers, and for a bus drivers that wish to set
                       options for the bus controller.  It will not be NULL for a
                       bus driver that wishes to set options for one of its child
                       controllers.
    Language         - A pointer to a three character ISO 639-2 language identifier.
                       This is the language of the user interface that should be
                       presented to the user, and it must match one of the languages
                       specified in SupportedLanguages.  The number of languages
                       supported by a driver is up to the driver writer.
    ActionRequired   - A pointer to the action that the calling agent is required
                       to perform when this function returns.  See "Related
                       Definitions" for a list of the actions that the calling
                       agent is required to perform prior to accessing
                       ControllerHandle again.

  Returns:
    EFI_SUCCESS           - The driver specified by This successfully set the
                            configuration options for the controller specified
                            by ControllerHandle..
    EFI_INVALID_PARAMETER - ControllerHandle is not a valid EFI_HANDLE.
    EFI_INVALID_PARAMETER - ChildHandle is not NULL and it is not a valid EFI_HANDLE.
    EFI_INVALID_PARAMETER - ActionRequired is NULL.
    EFI_UNSUPPORTED       - The driver specified by This does not support setting
                            configuration options for the controller specified by
                            ControllerHandle and ChildHandle.
    EFI_UNSUPPORTED       - The driver specified by This does not support the
                            language specified by Language.
    EFI_DEVICE_ERROR      - A device error occurred while attempt to set the
                            configuration options for the controller specified
                            by ControllerHandle and ChildHandle.
    EFI_OUT_RESOURCES     - There are not enough resources available to set the
                            configuration options for the controller specified
                            by ControllerHandle and ChildHandle.

--*/

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_CONFIGURATION_OPTIONS_VALID) (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL          *This,
  IN  EFI_HANDLE                                 ControllerHandle,
  IN  EFI_HANDLE                                 ChildHandle  OPTIONAL
  );
/*++

  Routine Description:
    Tests to see if a controller's current configuration options are valid.

  Arguments:
    This             - A pointer to the EFI_DRIVER_CONFIGURATION_PROTOCOL instance.
    ControllerHandle - The handle of the controller to test if it's current
                       configuration options are valid.
    ChildHandle      - The handle of the child controller to test if it's current
                       configuration options are valid.  This is an optional
                       parameter that may be NULL.  It will be NULL for device
                       drivers.  It will also be NULL for a bus drivers that wish
                       to test the configuration options for the bus controller.
                       It will not be NULL for a bus driver that wishes to test
                       configuration options for one of its child controllers.

  Returns:
    EFI_SUCCESS           - The controller specified by ControllerHandle and
                            ChildHandle that is being managed by the driver
                            specified by This has a valid set of  configuration
                            options.
    EFI_INVALID_PARAMETER - ControllerHandle is not a valid EFI_HANDLE.
    EFI_INVALID_PARAMETER - ChildHandle is not NULL and it is not a valid EFI_HANDLE.
    EFI_UNSUPPORTED       - The driver specified by This is not currently
                            managing the controller specified by ControllerHandle
                            and ChildHandle.
    EFI_DEVICE_ERROR      - The controller specified by ControllerHandle and
                            ChildHandle that is being managed by the driver
                            specified by This has an invalid set of configuration
                            options.

--*/

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_CONFIGURATION_FORCE_DEFAULTS) (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL          *This,
  IN  EFI_HANDLE                                 ControllerHandle,
  IN  EFI_HANDLE                                 ChildHandle  OPTIONAL,
  IN  UINT32                                     DefaultType,
  OUT EFI_DRIVER_CONFIGURATION_ACTION_REQUIRED   *ActionRequired
  );
/*++

  Routine Description:
    Forces a driver to set the default configuration options for a controller.

  Arguments:
    This             - A pointer to the EFI_DRIVER_CONFIGURATION_ PROTOCOL instance.
    ControllerHandle - The handle of the controller to force default configuration options on.
    ChildHandle      - The handle of the child controller to force default configuration options on  This is an optional parameter that may be NULL.  It will be NULL for device drivers.  It will also be NULL for a bus drivers that wish to force default configuration options for the bus controller.  It will not be NULL for a bus driver that wishes to force default configuration options for one of its child controllers.
    DefaultType      - The type of default configuration options to force on the controller specified by ControllerHandle and ChildHandle.  See Table 9-1 for legal values.  A DefaultType of 0x00000000 must be supported by this protocol.
    ActionRequired   - A pointer to the action that the calling agent is required to perform when this function returns.  See "Related Definitions" in Section 9.1for a list of the actions that the calling agent is required to perform prior to accessing ControllerHandle again.

  Returns:
    EFI_SUCCESS           - The driver specified by This successfully forced the default configuration options on the controller specified by ControllerHandle and ChildHandle.
    EFI_INVALID_PARAMETER - ControllerHandle is not a valid EFI_HANDLE.
    EFI_INVALID_PARAMETER - ChildHandle is not NULL and it is not a valid EFI_HANDLE.
    EFI_INVALID_PARAMETER - ActionRequired is NULL.
    EFI_UNSUPPORTED       - The driver specified by This does not support forcing the default configuration options on the controller specified by ControllerHandle and ChildHandle.
    EFI_UNSUPPORTED       - The driver specified by This does not support the configuration type specified by DefaultType.
    EFI_DEVICE_ERROR      - A device error occurred while attempt to force the default configuration options on the controller specified by  ControllerHandle and ChildHandle.
    EFI_OUT_RESOURCES     - There are not enough resources available to force the default configuration options on the controller specified by ControllerHandle and ChildHandle.

--*/

//
// Interface structure for the Driver Configuration Protocol
//

struct _EFI_DRIVER_CONFIGURATION_PROTOCOL {
  EFI_DRIVER_CONFIGURATION_SET_OPTIONS      SetOptions;
  EFI_DRIVER_CONFIGURATION_OPTIONS_VALID    OptionsValid;
  EFI_DRIVER_CONFIGURATION_FORCE_DEFAULTS   ForceDefaults;
  CHAR8                                     *SupportedLanguages;
};

/*++

  Protocol Description:
    Used to set configuration options for a controller that an EFI Driver is managing.

  Parameters:
    SetOptions         - Allows the use to set drivers specific configuration
                         options for a controller that the driver is currently
                         managing.
    OptionsValid       - Tests to see if a controller's current configuration
                         options are valid.
    ForceDefaults      - Forces a driver to set the default configuration options
                         for a controller.
    SupportedLanguages - A Null-terminated ASCII string that contains one or more
                         ISO 639-2 language codes.  This is the list of language
                         codes that this protocol supports.

--*/

extern EFI_GUID gBlackBoxEfiDriverConfigurationProtocolGuid;

#endif
