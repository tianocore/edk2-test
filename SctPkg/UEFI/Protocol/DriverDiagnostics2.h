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

  DriverDiagnostics2Protocol.h

Abstract:

  EFI Driver Diagnostics2 Protocol

--*/

#ifndef _DRIVER_DIAGNOSTICS2_PROTOCOL_H_
#define _DRIVER_DIAGNOSTICS2_PROTOCOL_H_

//
// Global ID for the Driver Diagnostics Protocol
//
#define EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_GUID    \
  { 0x4d330321, 0x025f, 0x4aac, 0x90, 0xd8, 0x5e, 0xd9, 0x00, 0x17, 0x3b, 0x63 }

typedef struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL EFI_DRIVER_DIAGNOSTICS2_PROTOCOL;;

typedef enum {
  EfiDriverDiagnosticTypeStandard               = 0,
  EfiDriverDiagnosticTypeExtended               = 1,
  EfiDriverDiagnosticTypeManufacturing          = 2,
  EfiDriverDiagnosticTypeMaximum
} EFI_DRIVER_DIAGNOSTIC_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS) (
  IN  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL         *This,
  IN  EFI_HANDLE                               ControllerHandle,
  IN  EFI_HANDLE                               ChildHandle  OPTIONAL,
  IN  EFI_DRIVER_DIAGNOSTIC_TYPE               DiagnosticType,
  IN  CHAR8                                    *Language,
  OUT EFI_GUID                                 **ErrorType,
  OUT UINTN                                    *BufferSize,
  OUT CHAR16                                   **Buffer
  );
/*++

  Routine Description:
    Runs diagnostics on a controller.

  Arguments:
    This             - A pointer to the EFI_DRIVER_DIAGNOSTICS2_PROTOCOL instance.
    ControllerHandle - The handle of the controller to run diagnostics on.
    ChildHandle      - The handle of the child controller to run diagnostics on
                       This is an optional parameter that may be NULL.  It will
                       be NULL for device drivers.  It will also be NULL for a
                       bus drivers that wish to run diagnostics on the bus
                       controller.  It will not be NULL for a bus driver that
                       wishes to run diagnostics on one of its child controllers.
    DiagnosticType   - Indicates type of diagnostics to perform on the controller
                       specified by ControllerHandle and ChildHandle.
    Language         - LanguageA pointer to a Null-terminated ASCII string array 
                       indicating the language. This is the language in which the 
                       optional error message should be returned in Buffer, and it 
                       must match one of the languages specified in SupportedLanguages. 
                       The number of languages supported by a driver is up to the driver 
                       writer. Language is specified in RFC 3066 language code format.
    ErrorType        - A GUID that defines the format of the data returned in
                       Buffer.
    BufferSize       - The size, in bytes, of the data returned in Buffer.
    Buffer           - A buffer that contains a Null-terminated Unicode string
                       plus some additional data whose format is defined by
                       ErrorType.  Buffer is allocated by this function with
                       SctAllocatePool (), and it is the caller's responsibility
                       to free it with a call to SctFreePool ().

  Returns:
    EFI_SUCCESS           - The controller specified by ControllerHandle and
                            ChildHandle passed the diagnostic.
    EFI_INVALID_PARAMETER - ControllerHandle is not a valid EFI_HANDLE.
    EFI_INVALID_PARAMETER - The driver specified by This is not a device driver, 
                            ChildHandle is not NULL and it is not a valid
                            EFI_HANDLE.
    EFI_INVALID_PARAMETER - Language is NULL.
    EFI_INVALID_PARAMETER - ErrorType is NULL.
    EFI_INVALID_PARAMETER - BufferType is NULL.
    EFI_INVALID_PARAMETER - Buffer is NULL.
    EFI_UNSUPPORTED       - The driver specified by This does not support
                            running diagnostics for the controller specified
                            by ControllerHandle and ChildHandle.
    EFI_UNSUPPORTED       - The driver specified by This does not support the
                            type of diagnostic specified by DiagnosticType.
    EFI_UNSUPPORTED       - The driver specified by This does not support the
                            language specified by Language.
    EFI_OUT_OF_RESOURCES  - There are not enough resources available to complete
                            the diagnostics.
    EFI_OUT_OF_RESOURCES  - There are not enough resources available to return
                            the status information in ErrorType, BufferSize,
                            and Buffer.
    EFI_DEVICE_ERROR      - The controller specified by ControllerHandle and
                            ChildHandle did not pass the diagnostic.

--*/

//
// Interface structure for the Driver Diagnostics2 Protocol
//

struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL {
  EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS  RunDiagnostics;
  CHAR8                                   *SupportedLanguages;
};

/*++

  Protocol Description:
    Used to perform diagnostics on a controller that an EFI Driver is managing.

  Parameters:
    RunDiagnostics     - Runs diagnostics on a controller.
    SupportedLanguages - SupportedLanguagesA Null-terminated ASCII string that 
                         contains one or more supported language codes. This is 
                         the list of language codes that this protocol supports. 
                         The number of languages supported by a driver is up to 
                         the driver writer. SupportedLanguages is specified in 
                         RFC 3066 format.

--*/

extern EFI_GUID gBlackBoxEfiDriverDiagnostics2ProtocolGuid;

#endif
