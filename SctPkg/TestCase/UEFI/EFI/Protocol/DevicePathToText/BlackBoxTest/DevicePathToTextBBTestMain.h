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

  DevicePathToTextBBTestMain.h

Abstract:

  BB test header file of Device Path To Text protocol

--*/

#ifndef _DEVICE_PATH_TO_TEXT_BBTEST_H_
#define _DEVICE_PATH_TO_TEXT_BBTEST_H_

#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/DevicePath.h>
#include <UEFI/Protocol/DevicePathUtilities.h>
#include <UEFI/Protocol/DevicePathFromText.h>
#include <UEFI/Protocol/DevicePathToText.h>
#include <UEFI/Protocol/DebugPort.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include EFI_PROTOCOL_DEFINITION (DebugPort)
#include EFI_GUID_DEFINITION (PcAnsi)

#define DEVICE_PATH_PROTOCOL_TEST_REVISION  0x00010001

#define USB_CLASS_AUDIO            1
#define USB_CLASS_CDCCONTROL       2
#define USB_CLASS_HID              3
#define USB_CLASS_IMAGE            6
#define USB_CLASS_PRINTER          7
#define USB_CLASS_MASS_STORAGE     8
#define USB_CLASS_HUB              9
#define USB_CLASS_CDCDATA          10
#define USB_CLASS_SMART_CARD       11
#define USB_CLASS_VIDEO            14
#define USB_CLASS_DIAGNOSTIC       220
#define USB_CLASS_WIRELESS         224

#define USB_CLASS_RESERVE          254
#define USB_SUBCLASS_FW_UPDATE     1
#define USB_SUBCLASS_IRDA_BRIDGE   2
#define USB_SUBCLASS_TEST          3

typedef struct {
  CHAR16                    *DevicePathNodeText;
  EFI_DEVICE_PATH_PROTOCOL  * (*Function) (CHAR16 *);
} DEVICE_PATH_FROM_TEXT_TABLE;

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
InitializeBBTestDevicePathToTextProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDevicePathToTextProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//
EFI_STATUS
DevicePathToTextConvertDeviceNodeToTextFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathToTextConvertDevicePathToTextFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathToTextConvertDeviceNodeToTextConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathToTextConvertDevicePathToTextConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathToTextConvertDeviceNodeToTextCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
DevicePathToTextConvertDevicePathToTextCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_DEVICE_PATH_PROTOCOL *
SctConvertTextToDeviceNode (
  IN CHAR16                *TextDevicePath
  );

EFI_DEVICE_PATH_PROTOCOL *
SctConvertTextToDevicePath (
  IN CHAR16 *TextDevicePath
  );

//
// Other function declaration section
//
//
// Entry GUIDs
//
#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_FUNCTION_GUID \
  { \
    0xa9092653, 0xd44e, 0x407f, \
    { \
      0xa5, 0x1e, 0x94, 0xb, 0xe4, 0x77, 0xa, 0x26 \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICEPATHTOTEXT_FUNCTION_GUID \
  { \
    0x1ab644ba, 0x1cb5, 0x4533, \
    { \
      0xb5, 0xcd, 0x30, 0x1e, 0xeb, 0x5c, 0x9, 0xd4 \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_CONFORMANCE_GUID \
  { \
    0x60e1b540, 0x3351, 0x455b, \
    { \
      0xb9, 0xf9, 0x86, 0x62, 0x5b, 0x7a, 0x15, 0x4e \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICEPATHTOTEXT_CONFORMANCE_GUID \
  { \
    0xf8489292, 0x27f2, 0x4aa6, \
    { \
      0xa4, 0x33, 0x6d, 0x57, 0xa8, 0xb, 0x4a, 0x91 \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_COVERAGE_GUID \
  { \
    0xc843762a, 0x8d11, 0x46b8, \
    { \
      0x84, 0x17, 0x97, 0xa8, 0x92, 0x80, 0x9a, 0xb0 \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICEPATHTOTEXT_COVERAGE_GUID \
  { \
    0xab54423, 0x22c5, 0x4391, \
    { \
      0xaf, 0x3a, 0x4, 0x8a, 0x4d, 0x4a, 0xfd, 0xe1 \
    } \
  }

#endif
