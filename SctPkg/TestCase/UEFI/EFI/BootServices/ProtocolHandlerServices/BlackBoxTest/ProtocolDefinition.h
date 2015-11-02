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

  ProtocolDefinition.h

Abstract:

  Include for those protocols that will be used during the Protocol Handler
    Boot Services Test

--*/

#ifndef _PROTOCOL_DEFINITION_H
#define _PROTOCOL_DEFINITION_H

//
// Include
//
#include "Efi.h"

//
// below are drivers name definition
//

//
// drivers for OpenProtocol222 test
//
#define TEST_DRIVER_1_NAME  L"TestDriver1.efi"
#define TEST_DRIVER_2_NAME  L"TestDriver2.efi"
#define TEST_DRIVER_3_NAME  L"TestDriver3.efi"
#define TEST_DRIVER_4_NAME  L"TestDriver4.efi"
#define TEST_DRIVER_5_NAME  L"TestDriver5.efi"

//
// drivers for OpenProtocol333 test
//
#define DRIVERBINDING_DRIVER_1_NAME  L"DBindingDriver1.efi"
#define DRIVERBINDING_DRIVER_2_NAME  L"DBindingDriver2.efi"
#define DRIVERBINDING_DRIVER_3_NAME  L"DBindingDriver3.efi"
#define DRIVERBINDING_DRIVER_4_NAME  L"DBindingDriver4.efi"
#define DRIVERBINDING_DRIVER_5_NAME  L"DBindingDriver5.efi"

//
// drivers for ConnectController test
//
#define DEVICE_DRIVER_1_NAME  L"DeviceDriver1.efi"
#define BUS_DRIVER_1_NAME     L"BusDriver1.efi"
#define DEVICE_DRIVER_2_NAME  L"DeviceDriver2.efi"
#define BUS_DRIVER_2_NAME     L"BusDriver2.efi"

#define DEVICE_DRIVER_3_NAME  L"DeviceDriver3.efi"
#define DEVICE_DRIVER_4_NAME  L"DeviceDriver4.efi"
#define DEVICE_DRIVER_5_NAME  L"DeviceDriver5.efi"
#define DEVICE_DRIVER_6_NAME  L"DeviceDriver6.efi"
#define DEVICE_DRIVER_7_NAME  L"DeviceDriver7.efi"

#define DEVICE_DRIVER_18_NAME  L"DeviceDriver18.efi"
#define DEVICE_DRIVER_19_NAME  L"DeviceDriver19.efi"
#define DEVICE_DRIVER_110_NAME  L"DeviceDriver110.efi"
#define DEVICE_DRIVER_111_NAME  L"DeviceDriver111.efi"

#define PLATFORM_OVERRIDE_DRIVER_1_NAME  L"PlatformOverrideDriver1.efi"
#define BUS_OVERRIDE_DRIVER_1_NAME  L"BusOverrideDriver1.efi"

// BusDriver3 will install a bus driver guid on the passed in handle
#define BUS_DRIVER_3_NAME     L"BusDriver3.efi"

//
// drivers for Combination test
//
#define BUS_DRIVER_4_NAME     L"BusDriver4.efi"
#define DEVICE_DRIVER_11_NAME  L"DeviceDriver11.efi"
#define DEVICE_DRIVER_12_NAME  L"DeviceDriver12.efi"
#define DEVICE_DRIVER_13_NAME  L"DeviceDriver13.efi"
#define DEVICE_DRIVER_14_NAME  L"DeviceDriver14.efi"
#define DEVICE_DRIVER_15_NAME  L"DeviceDriver15.efi"

//
// module globals
//

//
// TestProtocol1
//

#define TEST_PROTOCOL_1_GUID \
  {0x65d50e3c, 0x2174, 0x4b24, 0xaf, 0x95, 0xd1, 0x8e, 0xb2, 0x49, 0xae, 0xed };

extern EFI_GUID mTestProtocol1Guid;

typedef struct _TEST_PROTOCOL_1 TEST_PROTOCOL_1;;

typedef
EFI_STATUS
(EFIAPI *TEST_PROTOCOL_1_FUN_1) (
  IN TEST_PROTOCOL_1            *This
);

struct _TEST_PROTOCOL_1 {
  TEST_PROTOCOL_1_FUN_1          TestProtocol1Func1;
};


//
// TestProtocol2
//

#define TEST_PROTOCOL_2_GUID \
  {0x64fa18a0, 0x2666, 0x4924, 0x96, 0xe3, 0xa3, 0xd8, 0x91, 0x68, 0x39, 0xc };


extern EFI_GUID mTestProtocol2Guid;

typedef struct _TEST_PROTOCOL_2 TEST_PROTOCOL_2;;

typedef
EFI_STATUS
(EFIAPI *TEST_PROTOCOL_2_FUN_1) (
  IN TEST_PROTOCOL_2            *This
);

struct _TEST_PROTOCOL_2 {
  TEST_PROTOCOL_2_FUN_1          TestProtocol2Func1;
};


//
// InterfaceFunctionTestProtocol1
//

typedef struct {
  UINT16      ProtocolId;
  UINT32      ReinstallField;
} PROTOCOL_ATTRIBUTES;

#define INTERFACE_FUNCTION_TEST_PROTOCOL_1_GUID \
  {0xab2bfdfb, 0x15a0, 0x4757, 0xad, 0x67, 0x3e, 0xc8, 0x90, 0x36, 0x36, 0x11 };

extern EFI_GUID mInterfaceFunctionTestProtocol1Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_1 INTERFACE_FUNCTION_TEST_PROTOCOL_1;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_1_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_1   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_1 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol1Id    1


//
// InterfaceFunctionTestProtocol2
//

#define INTERFACE_FUNCTION_TEST_PROTOCOL_2_GUID \
  {0xc8a7b7c1, 0x5406, 0x4757, 0x99, 0xda, 0x6e, 0x97, 0x21, 0x47, 0x96, 0x23 }

extern EFI_GUID mInterfaceFunctionTestProtocol2Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_2 INTERFACE_FUNCTION_TEST_PROTOCOL_2;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_2_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_2   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_2 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol2Id    2

//
// InterfaceFunctionTestProtocol3
//

#define INTERFACE_FUNCTION_TEST_PROTOCOL_3_GUID \
  {0xa06e9d2c, 0x88d5, 0x4952, 0x8f, 0x6c, 0xab, 0xf7, 0x3e, 0x5c, 0xca, 0x59 }

extern EFI_GUID mInterfaceFunctionTestProtocol3Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_3 INTERFACE_FUNCTION_TEST_PROTOCOL_3;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_3_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_3   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_3 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol3Id    3


//
// InterfaceFunctionTestProtocol4
//

#define INTERFACE_FUNCTION_TEST_PROTOCOL_4_GUID \
  {0xc3ca2ffa, 0xe954, 0x404e, 0xa2, 0xb, 0xb5, 0xa8, 0x0, 0x86, 0xee, 0x76 }


extern EFI_GUID mInterfaceFunctionTestProtocol4Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_4 INTERFACE_FUNCTION_TEST_PROTOCOL_4;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_4_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_4   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_4 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol4Id    4


//
// InterfaceFunctionTestProtocol5
//

#define INTERFACE_FUNCTION_TEST_PROTOCOL_5_GUID \
  {0x3bfaa661, 0xbde6, 0x480a, 0x87, 0x8f, 0x5f, 0x7b, 0xac, 0x33, 0x80, 0x4 }

extern EFI_GUID mInterfaceFunctionTestProtocol5Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_5 INTERFACE_FUNCTION_TEST_PROTOCOL_5;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_5_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_5   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_5 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_5_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol5Id    5

//
// InterfaceFunctionTestProtocol6
//

#define INTERFACE_FUNCTION_TEST_PROTOCOL_6_GUID \
  {0xc32f87a6, 0x2375, 0x485f, 0x96, 0x91, 0xbe, 0xe7, 0x19, 0x86, 0xf4, 0x5c }

extern EFI_GUID mInterfaceFunctionTestProtocol6Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_6 INTERFACE_FUNCTION_TEST_PROTOCOL_6;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_6_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_6   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_6 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_6_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol6Id    6

//
// InterfaceFunctionTestProtocol7
//

#define INTERFACE_FUNCTION_TEST_PROTOCOL_7_GUID \
  {0xe6cda008, 0x27b0, 0x4aa3, 0x91, 0x7f, 0xeb, 0x8d, 0x2b, 0x60, 0x86, 0xba }

extern EFI_GUID mInterfaceFunctionTestProtocol7Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_7 INTERFACE_FUNCTION_TEST_PROTOCOL_7;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_7_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_7   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_7 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_7_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol7Id    7

//
// InterfaceFunctionTestProtocol8
//

#define INTERFACE_FUNCTION_TEST_PROTOCOL_8_GUID \
  {0x640f55de, 0x3204, 0x4696, 0x96, 0xeb, 0x33, 0x9f, 0x24, 0x70, 0x73, 0x0 }

extern EFI_GUID mInterfaceFunctionTestProtocol8Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_8 INTERFACE_FUNCTION_TEST_PROTOCOL_8;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_8_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_8   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_8 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_8_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol8Id    8

//
// InterfaceFunctionTestProtocol9
//
#define INTERFACE_FUNCTION_TEST_PROTOCOL_9_GUID \
  {0xaf83d35f, 0xd24e, 0x4049, 0x93, 0xbe, 0xcf, 0xcf, 0xb, 0xf9, 0x8d, 0x62 }

extern EFI_GUID mInterfaceFunctionTestProtocol9Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_9 INTERFACE_FUNCTION_TEST_PROTOCOL_9;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_9_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_9   *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_9 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_9_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol9Id    9

//
// InterfaceFunctionTestProtocol10
//
#define INTERFACE_FUNCTION_TEST_PROTOCOL_10_GUID \
  {0x9ef05d0f, 0x4bd0, 0x40c8, 0x94, 0xf9, 0x1b, 0x33, 0xbf, 0xfc, 0xcb, 0x1b }

extern EFI_GUID mInterfaceFunctionTestProtocol10Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_10 INTERFACE_FUNCTION_TEST_PROTOCOL_10;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_10_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_10  *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_10 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_10_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol10Id    10

//
// InterfaceFunctionTestProtocol11
//
#define INTERFACE_FUNCTION_TEST_PROTOCOL_11_GUID \
  {0xf12f2b1f, 0x67a8, 0x4d00, 0xbf, 0x37, 0x5, 0x94, 0x74, 0xe, 0x21, 0x31 }

extern EFI_GUID mInterfaceFunctionTestProtocol11Guid;

typedef struct _INTERFACE_FUNCTION_TEST_PROTOCOL_11 INTERFACE_FUNCTION_TEST_PROTOCOL_11;;

typedef
VOID
(EFIAPI *INTERFACE_FUNCTION_TEST_PROTOCOL_11_FUN_1) (
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_11  *This,
  OUT PROTOCOL_ATTRIBUTES                 *ProtocolAttributes
);

struct _INTERFACE_FUNCTION_TEST_PROTOCOL_11 {
  PROTOCOL_ATTRIBUTES                       ProtocolAttributes;
  INTERFACE_FUNCTION_TEST_PROTOCOL_11_FUN_1  ReportProtocolAttributes;
};

#define InterfaceFunctionTestProtocol11Id    11

//
// ExternalDriverProtocol1
//

#define EXTERNAL_DRIVER_PROTOCOL_1_GUID \
  {0x26c3e985, 0xb498, 0x4726, 0xad, 0x55, 0x7c, 0xc3, 0x2d, 0x4a, 0x19, 0xe3 }

extern EFI_GUID mExternalDriverProtocol1Guid;

typedef struct _EXTERNAL_DRIVER_PROTOCOL_1 EXTERNAL_DRIVER_PROTOCOL_1;;

typedef
VOID
(EFIAPI *GET_NEXT_STATUS_REPORT) (
  IN EXTERNAL_DRIVER_PROTOCOL_1   *This,
  IN EFI_STATUS                   *NextStatus
);

struct _EXTERNAL_DRIVER_PROTOCOL_1 {
  GET_NEXT_STATUS_REPORT                    GetNextStatusReport;
};

//
// TestNoInterfaceProtocol1
//
#define TEST_NO_INTERFACE_PROTOCOL_1_GUID \
  {0xa67c7a32, 0x2014, 0x4bdd, 0x86, 0x83, 0xf6, 0xbc, 0x1f, 0x10, 0x1a, 0x7c };

extern EFI_GUID mTestNoInterfaceProtocol1Guid;

//
// TestNoInterfaceProtocol2
//
#define TEST_NO_INTERFACE_PROTOCOL_2_GUID \
  {0x3175e4f7, 0xf347, 0x42b0, 0xb2, 0x26, 0xb1, 0x38, 0x3a, 0xc7, 0x7d, 0x10 };

extern EFI_GUID mTestNoInterfaceProtocol2Guid;

//
// Bus Driver 3's GUID
//
#define BUS_DRIVER_3_GUID \
  {0xcb3c0818, 0x6d0d, 0x408a, 0x97, 0x42, 0x73, 0xee, 0x31, 0x49, 0x8c, 0xfd };

extern EFI_GUID mBusDriver3Guid;

//
// Platform Override Driver 1's GUID
//
#define PLATFORM_OVERRIDE_DRIVER_1_GUID \
  {0xf8a23bc5, 0x4e3b, 0x4cc6, 0xb7, 0x9e, 0x7b, 0x4, 0x88, 0xbc, 0xcd, 0xf2 };

extern EFI_GUID mPlatformOverrideDriver1Guid;

//
// Vendor Device Path Guid
//
#define VENDOR_DEVICE_PATH_1_GUID \
  {0x142d3fbf, 0x3a78, 0x47cf, 0xa8, 0xa9, 0xc3, 0xb3, 0xcf, 0x9f, 0xc, 0x0 };

extern EFI_GUID mVendorDevicePath1Guid;

#define VENDOR_DEVICE_PATH_2_GUID \
  {0x729cd265, 0xab50, 0x4dde, 0x8d, 0x8c, 0x76, 0x9, 0x4b, 0xd3, 0x3f, 0x6a };

extern EFI_GUID mVendorDevicePath2Guid;

#define VENDOR_DEVICE_PATH_3_GUID \
  {0xde1caad6, 0x2a5c, 0x4f2f, 0x87, 0x1f, 0x72, 0x88, 0x5a, 0x20, 0x80, 0x28 };

extern EFI_GUID mVendorDevicePath3Guid;

#define VENDOR_DEVICE_PATH_4_GUID \
  {0x44f4853, 0xebf3, 0x4613, 0xa4, 0x4b, 0x37, 0x12, 0x2d, 0x3f, 0x1f, 0x22 };

extern EFI_GUID mVendorDevicePath4Guid;

#define VENDOR_DEVICE_PATH_5_GUID \
  {0x3a81e159, 0xfc10, 0x4148, 0xb4, 0xaf, 0x50, 0x78, 0xd1, 0x8d, 0x48, 0x64 };

extern EFI_GUID mVendorDevicePath5Guid;

#define VENDOR_DEVICE_PATH_6_GUID \
  {0x877b7e9a, 0x10ab, 0x4a6c, 0x81, 0x7, 0x67, 0xa4, 0xad, 0x89, 0xab, 0x12 };

extern EFI_GUID mVendorDevicePath6Guid;

#define VENDOR_DEVICE_PATH_7_GUID \
  {0x1ac12c97, 0xade5, 0x4d12, 0x82, 0x7f, 0xd4, 0x5b, 0x5f, 0xcc, 0x11, 0xab };

extern EFI_GUID mVendorDevicePath7Guid;

#define VENDOR_DEVICE_PATH_8_GUID \
  {0x356dc6d9, 0x2263, 0x4e73, 0x82, 0x5a, 0x53, 0x0, 0x36, 0xfa, 0xd, 0x17 };

extern EFI_GUID mVendorDevicePath8Guid;

#define VENDOR_DEVICE_PATH_9_GUID \
  {0x7b51bdd5, 0xa9ce, 0x4a59, 0xb6, 0x28, 0xd8, 0xa, 0x45, 0x1f, 0xfb, 0xa2 };

extern EFI_GUID mVendorDevicePath9Guid;

#define VENDOR_DEVICE_PATH_10_GUID \
  {0x94c3318e, 0x7520, 0x4334, 0x9f, 0xe4, 0x81, 0xd5, 0x9b, 0xda, 0x43, 0xb1 };

extern EFI_GUID mVendorDevicePath10Guid;

#endif
