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
                                                                
  Copyright 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/


#ifndef _DRIVER_SAMPLE_H_
#define _DRIVER_SAMPLE_H_

#include <Uefi.h>

#include <Protocol/HiiConfigRouting.h>
#include <Protocol/FormBrowser2.h>
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiString.h>
#include <Protocol/FormBrowserEx.h>
#include <Protocol/ConfigKeywordHandler.h>

#include <Guid/MdeModuleHii.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HiiLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>

#include "NVDataStruc.h"

//
// This is the generated IFR binary data for each formset defined in VFR.
// This data array is ready to be used as input of HiiAddPackages() to
// create a packagelist (which contains Form packages, String packages, etc).
//
extern UINT8  VfrBin[];
extern UINT8  InventoryBin[];

//
// This is the generated String package data for all .UNI files.
// This data array is ready to be used as input of HiiAddPackages() to
// create a packagelist (which contains Form packages, String packages, etc).
//
extern UINT8  ConfigKeywordHandler_DriverSampleStrings[];

#define DYNAMIC_ONE_OF_VAR_OFFSET        OFFSET_OF (DRIVER_SAMPLE_CONFIGURATION, DynamicOneof)
#define DYNAMIC_ORDERED_LIST_VAR_OFFSET  OFFSET_OF (DRIVER_SAMPLE_CONFIGURATION, DynamicOrderedList)

#define DEFAULT_CLASS_MANUFACTURING_VALUE     0xFF
#define DEFAULT_CLASS_STANDARD_VALUE          0x0

//
// Number of name in Name/Value storage
//
#define NAME_VALUE_NAME_NUMBER       3

#define DRIVER_SAMPLE_PRIVATE_SIGNATURE SIGNATURE_32 ('D', 'S', 'p', 's')

typedef struct {
  UINTN                            Signature;

  EFI_HANDLE                       DriverHandle[2];
  EFI_HII_HANDLE                   HiiHandle[2];
  DRIVER_SAMPLE_CONFIGURATION      Configuration;
  MY_EFI_VARSTORE_DATA             VarStoreConfig;
  UINT8                            PasswordState;

  //
  // Name/Value storage Name list
  //
  EFI_STRING_ID                    NameStringId[NAME_VALUE_NAME_NUMBER];
  EFI_STRING                       NameValueName[NAME_VALUE_NAME_NUMBER];

  //
  // Consumed protocol
  //
  EFI_HII_DATABASE_PROTOCOL        *HiiDatabase;
  EFI_HII_STRING_PROTOCOL          *HiiString;
  EFI_HII_CONFIG_ROUTING_PROTOCOL  *HiiConfigRouting;
  EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL *HiiKeywordHandler;

  EFI_FORM_BROWSER2_PROTOCOL       *FormBrowser2;

  //
  // Produced protocol
  //
  EFI_HII_CONFIG_ACCESS_PROTOCOL   ConfigAccess;
} DRIVER_SAMPLE_PRIVATE_DATA;

#define DRIVER_SAMPLE_PRIVATE_FROM_THIS(a)  CR (a, DRIVER_SAMPLE_PRIVATE_DATA, ConfigAccess, DRIVER_SAMPLE_PRIVATE_SIGNATURE)

#pragma pack(1)

///
/// HII specific Vendor Device Path definition.
///
typedef struct {
  VENDOR_DEVICE_PATH             VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL       End;
} HII_VENDOR_DEVICE_PATH;

#pragma pack()

#endif
