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

  Protocols that will be used during the Protocol Handler
    Boot Services Test

--*/
#include "Efi.h"
#include "ProtocolDefinition.h"

//
// module globals
//


EFI_GUID mTestProtocol1Guid = TEST_PROTOCOL_1_GUID;
EFI_GUID mTestProtocol2Guid = TEST_PROTOCOL_2_GUID;

EFI_GUID mInterfaceFunctionTestProtocol1Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_1_GUID;
EFI_GUID mInterfaceFunctionTestProtocol2Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_2_GUID;
EFI_GUID mInterfaceFunctionTestProtocol3Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_3_GUID;
EFI_GUID mInterfaceFunctionTestProtocol4Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_4_GUID;
EFI_GUID mInterfaceFunctionTestProtocol5Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_5_GUID;
EFI_GUID mInterfaceFunctionTestProtocol6Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_6_GUID;
EFI_GUID mInterfaceFunctionTestProtocol7Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_7_GUID;
EFI_GUID mInterfaceFunctionTestProtocol8Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_8_GUID;
EFI_GUID mInterfaceFunctionTestProtocol9Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_9_GUID;
EFI_GUID mInterfaceFunctionTestProtocol10Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_10_GUID;
EFI_GUID mInterfaceFunctionTestProtocol11Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_11_GUID;

EFI_GUID mExternalDriverProtocol1Guid = EXTERNAL_DRIVER_PROTOCOL_1_GUID;

EFI_GUID mTestNoInterfaceProtocol1Guid = TEST_NO_INTERFACE_PROTOCOL_1_GUID;
EFI_GUID mTestNoInterfaceProtocol2Guid = TEST_NO_INTERFACE_PROTOCOL_2_GUID;

EFI_GUID mBusDriver3Guid = BUS_DRIVER_3_GUID;
EFI_GUID mPlatformOverrideDriver1Guid = PLATFORM_OVERRIDE_DRIVER_1_GUID;

EFI_GUID mVendorDevicePath1Guid = VENDOR_DEVICE_PATH_1_GUID;
EFI_GUID mVendorDevicePath2Guid = VENDOR_DEVICE_PATH_2_GUID;
EFI_GUID mVendorDevicePath3Guid = VENDOR_DEVICE_PATH_3_GUID;
EFI_GUID mVendorDevicePath4Guid = VENDOR_DEVICE_PATH_4_GUID;
EFI_GUID mVendorDevicePath5Guid = VENDOR_DEVICE_PATH_5_GUID;
EFI_GUID mVendorDevicePath6Guid = VENDOR_DEVICE_PATH_6_GUID;
EFI_GUID mVendorDevicePath7Guid = VENDOR_DEVICE_PATH_7_GUID;
EFI_GUID mVendorDevicePath8Guid = VENDOR_DEVICE_PATH_8_GUID;
EFI_GUID mVendorDevicePath9Guid = VENDOR_DEVICE_PATH_9_GUID;
EFI_GUID mVendorDevicePath10Guid = VENDOR_DEVICE_PATH_10_GUID;

