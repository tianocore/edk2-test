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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DevicePathFromTextBBTestMain.h

Abstract:

  BB test header file of Device Path From Text protocol

--*/

#ifndef _DEVICE_PATH_FROM_TEXT_BBTEST_H_
#define _DEVICE_PATH_FROM_TEXT_BBTEST_H_

#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/DevicePathFromText.h>
#include <UEFI/Protocol/DevicePathUtilities.h>
#include <UEFI/Protocol/DevicePathToText.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define DEVICE_PATH_PROTOCOL_TEST_REVISION  0x00010001

#pragma pack(1)

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL  Header;
  UINT32                    HID;
  UINT32                    UID;
  UINT32                    CID;
  CHAR8                     HidUidCidStr[3];
} ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL  Header;
  EFI_GUID                  Guid;
  UINT8                     VendorDefinedData[1];
} VENDOR_DEFINED_MESSAGING_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL  Header;
  UINT16                    NetworkProtocol;
  UINT16                    LoginOption;
  UINT64                    Lun;
  UINT16                    TargetPortalGroupTag;
  CHAR8                     iSCSITargetName[1];
} ISCSI_DEVICE_PATH_WITH_NAME;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL  Header;
  EFI_GUID                  Guid;
  UINT8                     VendorDefinedData[1];
} VENDOR_DEFINED_HARDWARE_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL  Header;
  UINT32                    Reserved;
  UINT64                    StartingOffset;
  UINT64                    EndingOffset;
} MEDIA_OFFSET_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  UINT32                          Reserved;
  UINT8                           WWN[8];
  UINT8                           Lun[8];
} FIBRECHANNELEX_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  UINT8                           SasAddress[8];
  UINT8                           Lun[8];
  UINT16                          DeviceTopology;
  UINT16                          RelativeTargetPort;
} SASEX_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  UINT32                          NamespaceId;
  UINT64                          EUId;
} NVME_DEVICE_PATH;

#pragma pack()

EFI_STATUS
InitializeBBTestDevicePathFromTextProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDevicePathFromTextProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//
EFI_STATUS
DevicePathFromTextConvertTextToDeviceNodeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathFromTextConvertTextToDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathFromTextConvertTextToDeviceNodeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathFromTextConvertTextToDevicePathConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathFromTextConvertTextToDeviceNodeCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathFromTextConvertTextToDevicePathCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//
//
// Entry GUIDs
//
#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_FUNCTION_GUID \
  { \
    0x5cb6c4b1, 0x9a66, 0x49c4, \
    { \
      0xa9, 0xbf, 0x5e, 0xc1, 0x2, 0x1d, 0x3c, 0xbc \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_FUNCTION_GUID \
  { \
    0x8e08526d, 0x57f9, 0x4b24, \
    { \
      0xb4, 0x92, 0x55, 0xdb, 0xbd, 0x8c, 0x98, 0x7a \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_CONFORMANCE_GUID \
  { \
    0xb09f3cab, 0x144d, 0x4111, \
    { \
      0xa3, 0x91, 0x62, 0x73, 0xaf, 0x5e, 0x3, 0x86 \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_CONFORMANCE_GUID \
  { \
    0x26f7a7b7, 0xa851, 0x401b, \
    { \
      0x80, 0xc0, 0x1b, 0xde, 0xea, 0xd8, 0xe0, 0x5c \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_COVERAGE_GUID \
  { \
    0x5befac81, 0x4bf3, 0x4ff9, \
    { \
      0xb2, 0x24, 0xaa, 0xe3, 0x26, 0xc4, 0xb3, 0xb5 \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_COVERAGE_GUID \
  { \
    0xfa8223ce, 0x39d, 0x4886, \
    { \
      0x8a, 0x9f, 0x69, 0xd4, 0x87, 0xc3, 0x6a, 0x9d \
    } \
  }

#endif
