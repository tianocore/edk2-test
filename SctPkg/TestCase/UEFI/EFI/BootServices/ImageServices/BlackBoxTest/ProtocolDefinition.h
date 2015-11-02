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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  ProtocolDefinition.h

Abstract:

  Include for those protocols that will be used during the Image Boot Services Test

--*/

#ifndef _IMAGE_TEST_PROTOCOL_DEFINITION_H
#define _IMAGE_TEST_PROTOCOL_DEFINITION_H

//
// Include
//
#include "SctLib.h"

//
// ImageTestNoInterfaceProtocol1
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_1_GUID \
  {0x4719a636, 0x7387, 0x4037, 0xb5, 0x72, 0x2e, 0x7f, 0xd7, 0xe8, 0x4f, 0xe1 };

extern EFI_GUID mImageTestNoInterfaceProtocol1Guid;

//
// ImageTestNoInterfaceProtocol2
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_2_GUID \
  {0xc73b5566, 0x83c0, 0x40f6, 0xa1, 0xba, 0xe6, 0x22, 0x12, 0x21, 0x20, 0x87 };

extern EFI_GUID mImageTestNoInterfaceProtocol2Guid;

//
// ImageTestNoInterfaceProtocol3
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_3_GUID \
  {0xee4872b1, 0xa5d4, 0x497c, 0xb0, 0x67, 0x41, 0x58, 0x28, 0x35, 0x5c, 0xf7 };

extern EFI_GUID mImageTestNoInterfaceProtocol3Guid;

//
// ImageTestNoInterfaceProtocol4
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_4_GUID \
  {0xe0d2d5f3, 0x81fb, 0x46ab, 0xa4, 0x11, 0x91, 0xce, 0xdf, 0xe5, 0xf5, 0x42 };

extern EFI_GUID mImageTestNoInterfaceProtocol4Guid;

//
// ImageTestNoInterfaceProtocol5
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_5_GUID \
  {0xc463faf2, 0x1b50, 0x4b4c, 0x83, 0xdd, 0xde, 0x54, 0x9, 0x9a, 0xc4, 0xf0 };

extern EFI_GUID mImageTestNoInterfaceProtocol5Guid;

//
// ImageTestNoInterfaceProtocol6
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_6_GUID \
  {0x9977880e, 0x2462, 0x4fc1, 0x82, 0x4f, 0x4f, 0x98, 0x5, 0x11, 0x8d, 0xf9 };

extern EFI_GUID mImageTestNoInterfaceProtocol6Guid;

//
// ImageTestNoInterfaceProtocol7
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_7_GUID \
  {0xb39d9f40, 0x51f0, 0x42cf, 0xbc, 0x92, 0xcc, 0xb2, 0x69, 0x42, 0xde, 0xa0 };

extern EFI_GUID mImageTestNoInterfaceProtocol7Guid;

//
// ImageTestNoInterfaceProtocol8
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_8_GUID \
  {0x7cd42be4, 0x3ee1, 0x460c, 0x90, 0x63, 0x95, 0x3f, 0xf4, 0x90, 0x40, 0xcd };

extern EFI_GUID mImageTestNoInterfaceProtocol8Guid;

//
// ImageTestNoInterfaceProtocol9
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_9_GUID \
  {0x720e34a, 0x4328, 0x492b, 0xb8, 0x9f, 0xbc, 0x97, 0xdc, 0xfe, 0xd8, 0xfe };

extern EFI_GUID mImageTestNoInterfaceProtocol9Guid;

//
// ImageTestNoInterfaceProtocol10
//
#define IMAGE_TEST_NO_INTERFACE_PROTOCOL_10_GUID \
  {0x7eb47305, 0xc852, 0x49a0, 0xa7, 0xa3, 0xea, 0x23, 0x89, 0xbf, 0x84, 0xc2 };

extern EFI_GUID mImageTestNoInterfaceProtocol10Guid;

//
// mImageTestForLoadFileProtocol1Guid
//
#define IMAGE_TEST_FOR_LOAD_FILE_PROTOCOL_1_GUID \
  {0xef036185, 0x6fd7, 0x4c12, 0xb2, 0x29, 0x96, 0x8, 0x8e, 0xbb, 0x29, 0xe0 };

extern EFI_GUID mImageTestForLoadFileProtocol1Guid;

//
// Vendor Device Path Guid
//
#define IMAGE_TEST_VENDOR_DEVICE_PATH_1_GUID \
  {0x142d3fbf, 0x3a78, 0x47cf, 0xa8, 0xa9, 0xc3, 0xb3, 0xcf, 0x9f, 0xc, 0x0 };

extern EFI_GUID mImageTestVendorDevicePath1Guid;

//
// Vendor Device Path Guid for Load File Driver Device Path
//
#define IMAGE_TEST_LOAD_FILE_DRIVER_PATH_GUID \
  {0x6e79bbf8, 0x16d3, 0x4a8d, 0x85, 0x5f, 0xa6, 0x24, 0x55, 0x2, 0xaa, 0x15 };

extern EFI_GUID mImageTestLoadFileDriverPathGuid;

//
// Vendor Device Path Guid for application type file path
//
#define IMAGE_TEST_LOAD_FILE_APPLICATION_PATH_GUID \
  {0x2f377cb7, 0xa86, 0x4da5, 0xa5, 0xc7, 0x9e, 0x4c, 0xd9, 0x8d, 0x13, 0xa8 };

extern EFI_GUID mImageTestLoadFileApplicationPathGuid;

//
// Vendor Device Path Guid for boot services driver type file path
//
#define IMAGE_TEST_LOAD_FILE_BOOT_PATH_GUID \
  {0x7fe5da8f, 0x8f18, 0x4bfc, 0x8e, 0xb0, 0x89, 0x36, 0xb, 0xff, 0x71, 0x84 };

extern EFI_GUID mImageTestLoadFileBootPathGuid;

//
// Vendor Device Path Guid for runtime services driver type file path
//
#define IMAGE_TEST_LOAD_FILE_RUNTIME_PATH_GUID \
  {0x1632bc1f, 0xeaba, 0x4c81, 0xae, 0xf4, 0x29, 0xc9, 0x1d, 0x29, 0x64, 0xe7 };

extern EFI_GUID mImageTestLoadFileRuntimePathGuid;

//
// some definitions for the test images
//
#define ERROR_MESSAGE_FOR_APPLICATION_4     L"Application 4's Error Code is EFI_DEVICE_ERROR"
#define ERROR_MESSAGE_FOR_BOOT_SERVICES_DRIVER_2      L"Boot Services Driver 2's Error Code is EFI_DEVICE_ERROR"
#define ERROR_MESSAGE_FOR_BOOT_SERVICES_DRIVER_6      L"Boot Services Driver 6's Error Code is EFI_NOT_FOUND"
#define ERROR_MESSAGE_FOR_RUNTIME_SERVICES_DRIVER_2   L"Runtime Services Driver 2's Error Code is EFI_NOT_FOUND"
#define ERROR_MESSAGE_FOR_RUNTIME_SERVICES_DRIVER_6   L"Runtime Services Driver 6's Error Code is EFI_UNSUPPORTED"

//
//some variable name to be used by the loaded drivers to notify if the Exit
//function return control to StargImage() correctly.
//
#define IMAGE_TEST_VARIABLE_VENDOR_GUID \
  {0x3c445ada, 0xb7e5, 0x41a0, 0xaa, 0x77, 0xcb, 0xc7, 0x33, 0x6b, 0xf5, 0xc1}

extern EFI_GUID mImageTestVariableVendorGuid;


#define IMAGE_APPLICATION3_CALLED_AFTER_EXIT  L"Application3CalledAfterExit"

#define IMAGE_APPLICATION4_CALLED_AFTER_EXIT  L"Application4CalledAfterExit"

#define IMAGE_BOOTSERVICESDRIVER5_CALLED_AFTER_EXIT L"BootServicesDriver5CalledAfterExit"

#define IMAGE_BOOTSERVICESDRIVER6_CALLED_AFTER_EXIT L"BootServicesDriver6CalledAfterExit"

#define IMAGE_RUNTIMESERVICESDRIVER5_CALLED_AFTER_EXIT L"RuntimeServicesDriver5CalledAfterExit"

#define IMAGE_RUNTIMESERVICESDRIVER6_CALLED_AFTER_EXIT L"RuntimeServicesDriver6CalledAfterExit"

//
// directory and file name definition
//
#define DEPENDENCY_DIR_NAME                   L"Dependency\\ImageServicesBBTest"

#define IMAGE_TEST_LOAD_FILE_DRIVER_NAME      L"LoadFileDriver.efi"

#define APPLICATION_IMAGE_1_NAME              L"Application1.efi"
#define APPLICATION_IMAGE_3_NAME              L"Application3.efi"
#define APPLICATION_IMAGE_4_NAME              L"Application4.efi"

#define BOOT_SERVICES_DRIVER_IMAGE_1_NAME     L"BootServicesDriver1.efi"
#define BOOT_SERVICES_DRIVER_IMAGE_2_NAME     L"BootServicesDriver2.efi"
#define BOOT_SERVICES_DRIVER_IMAGE_3_NAME     L"BootServicesDriver3.efi"
#define BOOT_SERVICES_DRIVER_IMAGE_4_NAME     L"BootServicesDriver4.efi"
#define BOOT_SERVICES_DRIVER_IMAGE_5_NAME     L"BootServicesDriver5.efi"
#define BOOT_SERVICES_DRIVER_IMAGE_6_NAME     L"BootServicesDriver6.efi"

#define RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME  L"RuntimeServicesDriver1.efi"
#define RUNTIME_SERVICES_DRIVER_IMAGE_2_NAME  L"RuntimeServicesDriver2.efi"
#define RUNTIME_SERVICES_DRIVER_IMAGE_3_NAME  L"RuntimeServicesDriver3.efi"
#define RUNTIME_SERVICES_DRIVER_IMAGE_4_NAME  L"RuntimeServicesDriver4.efi"
#define RUNTIME_SERVICES_DRIVER_IMAGE_5_NAME  L"RuntimeServicesDriver5.efi"
#define RUNTIME_SERVICES_DRIVER_IMAGE_6_NAME  L"RuntimeServicesDriver6.efi"

#define COMBINATION_IMAGE_1_NAME              L"CombinationImage1.efi"
#define COMBINATION_IMAGE_2_NAME              L"CombinationImage2.efi"
#define COMBINATION_IMAGE_3_NAME              L"CombinationImage3.efi"
#define COMBINATION_IMAGE_4_NAME              L"CombinationImage4.efi"
#define COMBINATION_IMAGE_5_NAME              L"CombinationImage5.efi"
#define COMBINATION_IMAGE_6_NAME              L"CombinationImage6.efi"
#define COMBINATION_IMAGE_7_NAME              L"CombinationImage7.efi"
#define COMBINATION_IMAGE_8_NAME              L"CombinationImage8.efi"
#define COMBINATION_IMAGE_9_NAME              L"CombinationImage9.efi"
#define COMBINATION_IMAGE_10_NAME             L"CombinationImage10.efi"

#define INVALID_IMAGE_1_NAME                  L"InvalidImage1"
#define INVALID_IMAGE_2_NAME                  L"InvalidImage2"
#define INVALID_IMAGE_3_NAME                  L"InvalidImage3"
#define INVALID_IMAGE_4_NAME                  L"InvalidImage4"
#define INVALID_IMAGE_5_NAME                  L"InvalidImage5"
#define INVALID_IMAGE_6_NAME                  L"InvalidImage6"
#define INVALID_IMAGE_7_NAME                  L"InvalidImage7"
#define INVALID_IMAGE_8_NAME                  L"InvalidImage8"
#define INVALID_IMAGE_9_NAME                  L"InvalidImage9"
#define INVALID_IMAGE_10_NAME                 L"InvalidImage10"
#define INVALID_IMAGE_11_NAME                 L"InvalidImage11"
#define INVALID_IMAGE_12_NAME                 L"InvalidImage12"
#define INVALID_IMAGE_13_NAME                 L"InvalidImage13"
#define INVALID_IMAGE_14_NAME                 L"InvalidImage14"

#define VERY_LARGE_IMAGE_1_NAME               L"VeryLargeImage1"

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
#define VALID_HII_IMAGE_1_GUID \
  {0x8E7104E4, 0x6B5C, 0x43a8, 0xB3, 0x6D, 0xE8, 0x0B, 0x4E, 0xFA, 0x6A, 0x32};

extern EFI_GUID   mValidHiiImage1Guid;

#define VALID_HII_IMAGE_1_NAME                    L"ValidHiiImage1.efi"
#endif

#define APPLICATION_IMAGE_2_NAME_GUID \
  {0xFE7104D4, 0x6B5C, 0x43a8, 0xB3, 0x6D, 0xE8, 0x0B, 0x4E, 0xFA, 0x6A, 0x32};

#define BOOT_SERVICES_DRIVER_IMAGE_2_NAME_GUID \
  {0x399C6A02, 0x60A3, 0x4108, 0x83,0x02, 0xF5, 0xD6, 0xF3, 0x4D, 0x32, 0xE7};

#define RUNTIME_SERVICES_DRIVER_IMAGE_2_NAME_GUID \
  {0x66CFAD, 0xDBB0, 0x497d, 0xBF, 0x87, 0x70, 0x9D, 0x5E, 0x30, 0x36, 0xCA};

#endif
