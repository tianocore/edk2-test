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

  ProtocolDefinition.c

Abstract:

  Protocols that will be used during the Image Boot Services Test

--*/
#include "Efi.h"
#include "ProtocolDefinition.h"

//
// module globals
//
EFI_GUID mImageTestNoInterfaceProtocol1Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_1_GUID;
EFI_GUID mImageTestNoInterfaceProtocol2Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_2_GUID;
EFI_GUID mImageTestNoInterfaceProtocol3Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_3_GUID;
EFI_GUID mImageTestNoInterfaceProtocol4Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_4_GUID;
EFI_GUID mImageTestNoInterfaceProtocol5Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_5_GUID;
EFI_GUID mImageTestNoInterfaceProtocol6Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_6_GUID;
EFI_GUID mImageTestNoInterfaceProtocol7Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_7_GUID;
EFI_GUID mImageTestNoInterfaceProtocol8Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_8_GUID;
EFI_GUID mImageTestNoInterfaceProtocol9Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_9_GUID;
EFI_GUID mImageTestNoInterfaceProtocol10Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_10_GUID;

EFI_GUID mImageTestForLoadFileProtocol1Guid = IMAGE_TEST_FOR_LOAD_FILE_PROTOCOL_1_GUID;

EFI_GUID mImageTestVariableVendorGuid       = IMAGE_TEST_VARIABLE_VENDOR_GUID;

EFI_GUID mImageTestVendorDevicePath1Guid = IMAGE_TEST_VENDOR_DEVICE_PATH_1_GUID;

EFI_GUID mImageTestLoadFileDriverPathGuid       = IMAGE_TEST_LOAD_FILE_DRIVER_PATH_GUID;
EFI_GUID mImageTestLoadFileApplicationPathGuid  = IMAGE_TEST_LOAD_FILE_APPLICATION_PATH_GUID;
EFI_GUID mImageTestLoadFileBootPathGuid         = IMAGE_TEST_LOAD_FILE_BOOT_PATH_GUID;
EFI_GUID mImageTestLoadFileRuntimePathGuid      = IMAGE_TEST_LOAD_FILE_RUNTIME_PATH_GUID;

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
EFI_GUID  mValidHiiImage1Guid = VALID_HII_IMAGE_1_GUID;
#endif
