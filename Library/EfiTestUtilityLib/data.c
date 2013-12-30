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

  data.c

Abstract:

  EFI library global data

--*/

#include "lib.h"

//
// LibInitialized - TRUE once InitializeLib() is called for the first time
//

BOOLEAN  LibInitialized = FALSE;

//
// ST - pointer to the EFI system table
//

EFI_SYSTEM_TABLE        *tST;

//
// BS - pointer to the boot services table
//

EFI_BOOT_SERVICES       *tBS;


//
// Default pool allocation type
//

EFI_MEMORY_TYPE PoolAllocationType = EfiBootServicesData;

//
// Unicode collation functions that are in use
//

EFI_UNICODE_COLLATION_PROTOCOL   LibStubUnicodeInterface = {
    LibStubStriCmp,
    LibStubMetaiMatch,
    LibStubStrLwrUpr,
    LibStubStrLwrUpr,
    NULL,   // FatToStr
    NULL,   // StrToFat
    NULL    // SupportedLanguages
};

EFI_UNICODE_COLLATION_PROTOCOL   *UnicodeInterface = &LibStubUnicodeInterface;

//
// Root device path
//

//EFI_DEVICE_PATH_PROTOCOL RootDevicePath[] = {
//    END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, END_DEVICE_PATH_LENGTH, 0
//};

typedef struct {
  ACPI_HID_DEVICE_PATH              AcpiDevicePath;
  EFI_DEVICE_PATH_PROTOCOL          EndDevicePath;
} EFI_PCI_ROOT_BRIDGE_DEVICE_PATH;

EFI_PCI_ROOT_BRIDGE_DEVICE_PATH RootDevicePathTemp = {
  {
    ACPI_DEVICE_PATH,
    ACPI_DP,
    (UINT8) (sizeof(ACPI_HID_DEVICE_PATH)),
    (UINT8) ((sizeof(ACPI_HID_DEVICE_PATH)) >> 8),
    EISA_PNP_ID(0x0A03),
    0
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    END_DEVICE_PATH_LENGTH,
    0
  }
};

EFI_DEVICE_PATH_PROTOCOL  *RootDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)&RootDevicePathTemp;



EFI_DEVICE_PATH_PROTOCOL EndDevicePath[] = {
    END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, END_DEVICE_PATH_LENGTH, 0
};

EFI_DEVICE_PATH_PROTOCOL EndInstanceDevicePath[] = {
    END_DEVICE_PATH_TYPE, END_INSTANCE_DEVICE_PATH_SUBTYPE, END_DEVICE_PATH_LENGTH, 0
};


//
// EFI IDs
//

EFI_GUID tEfiGlobalVariable  = EFI_GLOBAL_VARIABLE_GUID;
EFI_GUID tNullGuid = { 0,0,0,0,0,0,0,0,0,0,0 };

//
// Protocol IDs
//

EFI_GUID gtEfiDevicePathProtocolGuid       = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID gtEfiLoadedImageProtocolGuid      = EFI_LOADED_IMAGE_PROTOCOL_GUID;
EFI_GUID gtEfiSimpleTextInProtocolGuid     = EFI_SIMPLE_TEXT_IN_PROTOCOL_GUID;
EFI_GUID gtEfiSimpleTextOutProtocolGuid    = EFI_SIMPLE_TEXT_OUT_PROTOCOL_GUID;
EFI_GUID gtEfiBlockIoProtocolGuid          = EFI_BLOCK_IO_PROTOCOL_GUID;
EFI_GUID gtEfiDiskIoProtocolGuid           = EFI_DISK_IO_PROTOCOL_GUID;
EFI_GUID gtEfiSimpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
EFI_GUID gtEfiLoadFileProtocolGuid         = LOAD_FILE_PROTOCOL_GUID;
EFI_GUID gtEfiDeviceIoProtocolGuid         = EFI_DEVICE_IO_PROTOCOL_GUID;
EFI_GUID gtEfiUnicodeCollationProtocolGuid = EFI_UNICODE_COLLATION_PROTOCOL_GUID;
EFI_GUID gtEfiSerialIoProtocolGuid         = EFI_SERIAL_IO_PROTOCOL_GUID;
EFI_GUID gtEfiSimpleNetworkProtocolGuid    = EFI_SIMPLE_NETWORK_PROTOCOL_GUID;
EFI_GUID gtEfiPxeBaseCodeProtocolGuid      = EFI_PXE_BASE_CODE_PROTOCOL_GUID;
EFI_GUID gtEfiPxeCallbackProtocolGuid      = EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID;
EFI_GUID gtEfiNetworkInterfaceIdentifierProtocolGuid = EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID;
EFI_GUID tUiProtocol               = EFI_UI_PROTOCOL;
//
// File system information IDs
//

EFI_GUID tGenericFileInfo           = EFI_FILE_INFO_ID;
EFI_GUID gtEfiFileSystemInfoGuid            = EFI_FILE_SYSTEM_INFO_ID_GUID;
EFI_GUID gtEfiFileSystemVolumeLabelInfoGuid = EFI_FILE_SYSTEM_VOLUME_LABEL_INFO_ID_GUID;

//
// Reference implementation public protocol IDs
//

EFI_GUID gtEfiInternalShellProtocolGuid = INTERNAL_SHELL_GUID;
EFI_GUID gtEfiVariableStoreProtocolGuid = EFI_VARIABLE_STORE_PROTOCOL_GUID;
EFI_GUID tAdapterDebugProtocol = ADAPTER_DEBUG_PROTOCOL;

//
// Device path media protocol IDs
//
EFI_GUID tPcAnsiProtocol = DEVICE_PATH_MESSAGING_PC_ANSI;
EFI_GUID tVt100Protocol  = DEVICE_PATH_MESSAGING_VT_100;

//
// EFI GPT Partition Type GUIDs
//
EFI_GUID gtEfiPartTypeSystemPartitionGuid = EFI_PART_TYPE_EFI_SYSTEM_PART_GUID;
EFI_GUID gtEfiPartTypeLegacyMbrGuid = EFI_PART_TYPE_LEGACY_MBR_GUID;


//
// Reference implementation Vendor Device Path Guids
//
EFI_GUID gtEfiUnknownDeviceGuid      = UNKNOWN_DEVICE_GUID;

//
// Configuration Table GUIDs
//

EFI_GUID gtEfiMpsTableGuid             = EFI_MPS_TABLE_GUID;
EFI_GUID gtEfiAcpiTableGuid            = EFI_ACPI_TABLE_GUID;
EFI_GUID gtEfiAcpi20TableGuid          = EFI_ACPI_20_TABLE_GUID;
EFI_GUID gtEfiSMBIOSTableGuid          = EFI_SMBIOS_TABLE_GUID;
EFI_GUID gtEfiSalSystemTableGuid       = EFI_SAL_SYSTEM_TABLE_GUID;

#if (EFI_SPECIFICATION_VERSION < 0x0002000A)
EFI_GUID gEfiHiiProtocolGuid = EFI_HII_PROTOCOL_GUID;
#endif
