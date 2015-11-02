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
                                                                
  Copyright (c) 2010 - 2012, Dell Inc.  All rights reserved.   
   
--*/

/*++         

Module Name:

  FirmwareManagement.h

Abstract:

  Firmware Management Protocol from the UEFI 2.3 specification.

--*/

#ifndef _FIRMWARE_MANAGEMENT_PROTOCOL_H_
#define _FIRMWARE_MANAGEMENT_PROTOCOL_H_

//
// Global ID for the Firmware Management Protocol
//

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GUID \
{ 0x86c77a67, 0xb97, 0x4633, 0xa1, 0x87, 0x49, 0x10, 0x4d, 0x6, 0x85, 0xc7 }

extern EFI_GUID  gBlackBoxEfiFirmwareManagementProtocolGuid; 

// ****************************************************************************
//   Definitions
// ****************************************************************************

//
// EFI_FIRMWARE_IMAGE_DESCRIPTOR
//

typedef struct {
UINT8     ImageIndex;
EFI_GUID  ImageTypeId;
UINT64    ImageId;
CHAR16    *ImageIdName;
UINT32    Version;
CHAR16    *VersionName;
UINTN     Size;
UINT64    AttributesSupported;
UINT64    AttributesSetting;
UINT64    Compatibilities;
} EFI_FIRMWARE_IMAGE_DESCRIPTOR;

//
// Image Attribute Definitions
//

#define IMAGE_ATTRIBUTE_IMAGE_UPDATABLE          0x0000000000000001
#define IMAGE_ATTRIBUTE_RESET_REQUIRED           0x0000000000000002
#define IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED  0x0000000000000004
#define IMAGE_ATTRIBUTE_IN_USE                   0x0000000000000008

//
// Image Compatibility Definitions
//

#define IMAGE_COMPATIBILITY_CHECK_SUPPORTED  0x0000000000000001

//
// Descriptor Version
//

#define EFI_FIRMWARE_IMAGE_DESCRIPTOR_VERSION  1

/*++
//
// Image Attribute Authentication Required
//

#define ANYSIZE_ARRAY  256

typedef struct _WIN_CERTIFICATE {
UINT32                                           dwLength;
UINT16                                           wRevision;
UINT16                                           wCertificateType;
//UINT8                                          bCertificate[ANYSIZE_ARRAY];
} WIN_CERTIFICATE;

typedef struct _WIN_CERTIFICATE_UEFI_GUID {
WIN_CERTIFICATE                                  Hdr;
EFI_GUID                                         CertType;
UINT8                                            CertData[ANYSIZE_ARRAY];
} WIN_CERTIFICATE_UEFI_GUID;

typedef struct {
UINT64                     MonotonicCount;
WIN_CERTIFICATE_UEFI_GUID                        AuthInfo;
} EFI_FIRMWARE_IMAGE_AUTHENTICATION;
--*/

//
// Progress Report
// 

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS) (
IN UINTN                                         Completion
) ;

//
// ImageUpdatable Definitions
//

#define IMAGE_UPDATABLE_VALID         0x0000000000000001
#define IMAGE_UPDATABLE_INVALID       0x0000000000000002
#define IMAGE_UPDATABLE_INVALID_TYPE  0x0000000000000004
#define IMAGE_UPDATABLE_INVALID_OLD   0x0000000000000008

//
// Package Attribute Definitions
//

#define PACKAGE_ATTRIBUTE_VERSION_UPDATABLE        0x0000000000000001
#define PACKAGE_ATTRIBUTE_RESET_REQUIRED           0x0000000000000002
#define PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED  0x0000000000000004

// ****************************************************************************
//   Firmware Management Protocol functions
// ****************************************************************************

typedef struct _EFI_FIRMWARE_MANAGEMENT_PROTOCOL EFI_FIRMWARE_MANAGEMENT_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE_INFO) (
IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *This,
IN OUT UINTN                                     *ImageInfoSize,
IN OUT EFI_FIRMWARE_IMAGE_DESCRIPTOR             *ImageInfo,
OUT UINT32                                       *DescriptorVersion,
OUT UINT8                                        *DescriptorCount,
OUT UINTN                                        *DescriptorSize,
OUT UINT32                                       *PackageVersion,
OUT CHAR16                                       **PackageVersionName
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE) (
IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *This,
IN UINT8                                         ImageIndex,
IN OUT VOID                                      *Image,
IN OUT UINTN                                     *ImageSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_IMAGE) (
IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *This,
IN UINT8                                         ImageIndex,
IN CONST VOID                                    *Image,
IN UINTN                                         ImageSize,
IN CONST VOID                                    *VendorCode,
IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress,
OUT CHAR16                                       **AbortReason
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_CHECK_IMAGE) (
IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *This,
IN UINT8                                         ImageIndex,
IN CONST VOID                                    *Image,
IN UINTN                                         ImageSize,
OUT UINT32                                       *ImageUpdatable
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_PACKAGE_INFO) (
IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *This,
OUT UINT32                                       *PackageVersion,
OUT CHAR16                                       **PackageVersionName,
OUT UINT32                                       *PackageVersionNameMaxLen,
OUT UINT64                                       *AttributesSupported,
OUT UINT64                                       *AttributesSetting
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_PACKAGE_INFO) (
IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *This,
IN CONST VOID                                    *Image,
IN UINTN                                         ImageSize,
IN CONST VOID                                    *VendorCode,
IN UINT32                                        PackageVersion,
IN CONST CHAR16                                  *PackageVersionName
);

// 
// Interface structure for the Firmware Management Protocol
//

struct _EFI_FIRMWARE_MANAGEMENT_PROTOCOL {
EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE_INFO    GetImageInfo;
EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE         GetImage;
EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_IMAGE         SetImage;
EFI_FIRMWARE_MANAGEMENT_PROTOCOL_CHECK_IMAGE       CheckImage;
EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_PACKAGE_INFO  GetPackageInfo;
EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_PACKAGE_INFO  SetPackageInfo;
};

#endif