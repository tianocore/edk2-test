/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

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
 { 0x86c77a67, 0xb97, 0x4633, {0xa1, 0x87, 0x49, 0x10, 0x4d, 0x6, 0x85, 0xc7 }}

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
