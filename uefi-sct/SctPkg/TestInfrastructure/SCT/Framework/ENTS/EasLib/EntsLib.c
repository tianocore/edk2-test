/** @file

  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2019, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EntsLib.c

Abstract:

  ENTS library global data

--*/
#include "Efi.h"
#include <Library/EntsLib.h>

#include EFI_PROTOCOL_DEFINITION(ManagedNetwork)

BOOLEAN                         mEntsTestLibInitialized = FALSE;

//
// Global variables, Global Network Test(GNT) Variables.
//
EFI_SYSTEM_TABLE                *gntST  = NULL;
EFI_BOOT_SERVICES               *gntBS  = NULL;
EFI_RUNTIME_SERVICES            *gntRT  = NULL;

//
// Default pool allocation type
//
EFI_MEMORY_TYPE                 EntsPoolAllocationType = EfiBootServicesData;

//
// Unicode collation functions that are in use
//
EFI_UNICODE_COLLATION_PROTOCOL  EntsLibStubUnicodeInterface = {
  EntsLibStubStriCmp,
  EntsLibStubMetaiMatch,
  EntsLibStubStrLwrUpr,
  EntsLibStubStrLwrUpr,
  NULL, // FatToStr
  NULL, // StrToFat
  NULL  // SupportedLanguages
};

EFI_UNICODE_COLLATION_PROTOCOL  *EntsUnicodeInterface = &EntsLibStubUnicodeInterface;

//
// EFI IDs
//
EFI_GUID                        tEfiGlobalVariable  = EFI_GLOBAL_VARIABLE_GUID;
EFI_GUID                        tNullGuid           = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 }};

//
// Protocol IDs
//
EFI_GUID                        gtEfiDevicePathProtocolGuid       = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID                        gtEfiLoadedImageProtocolGuid      = EFI_LOADED_IMAGE_PROTOCOL_GUID;
EFI_GUID                        gtEfiSimpleTextInProtocolGuid     = EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID;
EFI_GUID                        gtEfiSimpleTextOutProtocolGuid    = EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID;
EFI_GUID                        gtEfiBlockIoProtocolGuid          = EFI_BLOCK_IO_PROTOCOL_GUID;
EFI_GUID                        gtEfiDiskIoProtocolGuid           = EFI_DISK_IO_PROTOCOL_GUID;
EFI_GUID                        gtEfiSimpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
EFI_GUID                        gtEfiLoadFileProtocolGuid         = LOAD_FILE_PROTOCOL_GUID;
EFI_GUID                        gtEfiSerialIoProtocolGuid         = EFI_SERIAL_IO_PROTOCOL_GUID;
EFI_GUID                        gtEfiSimpleNetworkProtocolGuid    = EFI_SIMPLE_NETWORK_PROTOCOL_GUID;
EFI_GUID                        gtEfiPxeBaseCodeProtocolGuid      = EFI_PXE_BASE_CODE_PROTOCOL_GUID;
EFI_GUID                        gtEfiPxeCallbackProtocolGuid      = EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID;
EFI_GUID                        gtEfiNetworkInterfaceIdentifierProtocolGuid =
  EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID;
//
// File system information IDs
//
EFI_GUID                        tGenericFileInfo                    = EFI_FILE_INFO_ID;
EFI_GUID                        gtEfiFileSystemInfoGuid             = EFI_FILE_SYSTEM_INFO_ID_GUID;
EFI_GUID                        gtEfiFileSystemVolumeLabelInfoGuid  = EFI_FILE_SYSTEM_VOLUME_LABEL_INFO_ID_GUID;

//
// Reference implementation public protocol IDs
//
EFI_GUID                        gtEfiVariableStoreProtocolGuid = EFI_VARIABLE_STORE_PROTOCOL_GUID;

//
// Device path media protocol IDs
//
EFI_GUID                        tPcAnsiProtocol = DEVICE_PATH_MESSAGING_PC_ANSI;
EFI_GUID                        tVt100Protocol  = DEVICE_PATH_MESSAGING_VT_100;

//
// EFI GPT Partition Type GUIDs
//
EFI_GUID                        gtEfiPartTypeSystemPartitionGuid  = EFI_PART_TYPE_EFI_SYSTEM_PART_GUID;
EFI_GUID                        gtEfiPartTypeLegacyMbrGuid        = EFI_PART_TYPE_LEGACY_MBR_GUID;

//
// Reference implementation Vendor Device Path Guids
//
EFI_GUID                        gtEfiUnknownDeviceGuid = UNKNOWN_DEVICE_GUID;

//
// Configuration Table GUIDs
//
EFI_GUID                        gtEfiMpsTableGuid       = EFI_MPS_TABLE_GUID;
EFI_GUID                        gtEfiAcpiTableGuid      = EFI_ACPI_TABLE_GUID;
EFI_GUID                        gtEfiAcpi20TableGuid    = EFI_ACPI_20_TABLE_GUID;
EFI_GUID                        gtEfiSMBIOSTableGuid    = EFI_SMBIOS_TABLE_GUID;

EFI_HANDLE                      mImageHandle            = NULL;
EFI_DEVICE_PATH_PROTOCOL        *gntDevicePath          = NULL;
CHAR16                          *gntFilePath            = NULL;


//
// External functions implementation
//
EFI_STATUS
EFIAPI
EfiInitializeEntsLib (
  IN  EFI_HANDLE                  ImageHandle,
  IN  EFI_SYSTEM_TABLE            *SystemTable
  )
/*++

Routine Description:

  Initialize Ents library.

Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                      Status;

  if (!mEntsTestLibInitialized) {
    mEntsTestLibInitialized = TRUE;

    mImageHandle            = ImageHandle;

    gntST                   = SystemTable;
    gntBS                   = gntST->BootServices;
    gntRT                   = gntST->RuntimeServices;

    Status = GetImageDevicePath(
               ImageHandle, 
               &gntDevicePath,
               &gntFilePath
               );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}
