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
                                                                
  Copyright 2006 - 2015 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Efi.h

Abstract:

  Just reference Tiano.h.

  It's for compatibility of old drivers outside Tiano.

--*/

#ifndef _EFI_H_
#define _EFI_H_

// If we use the new build system
#ifndef __BASE_H__
  #include "Tiano.h"
  #include "PeiHob.h"

  #define EDK_PROTOCOL_DEFINITION(a)      EFI_STRINGIZE (Protocol/a/a.h)
#else
  #include <PiDxe.h>

  #include <Library/DebugLib.h>

  //
  // Define macros for including Protocols and Guids.
  //
  #define EFI_STRINGIZE(a)            #a
  #define EFI_PROTOCOL_DEFINITION(a)  EFI_STRINGIZE (Protocol/a.h)
  #define EFI_GUID_DEFINITION(a)      EFI_STRINGIZE (Guid/a.h)

  #define EFI_ARCH_PROTOCOL_DEFINITION(a) EFI_STRINGIZE (Protocol/a.h)

  // For FileInfo.h
  #define EDK_PROTOCOL_DEFINITION(a)      EFI_STRINGIZE (Guid/a.h)

  //
  // EdkCompatibilityPkg definitions
  //
  #define EFI_DBUG_MASK   (EFI_D_ERROR | EFI_D_INFO | EFI_D_WARN)
  
  #if defined(EFI32) | defined(EFIARM)
    #define EFI_BAD_POINTER          (UINTN)0xAFAFAFAF
  #else
    #define EFI_BAD_POINTER          (UINTN)0xAFAFAFAFAFAFAFAF
  #endif

  #define VOLATILE volatile

  //
  // Type differences between EdkCompatibiltyPkg & MdePkg
  #define EFI_EVENT_TIMER                 EVT_TIMER
  #define EFI_GUID                        GUID
  #define EFI_MAX_BIT                     MAX_BIT

  #define EFI_SIGNATURE_32(a,b,c,d)       SIGNATURE_32(a,b,c,d)

  typedef EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUT_PROTOCOL;
  typedef EFI_SIMPLE_TEXT_INPUT_PROTOCOL  EFI_SIMPLE_TEXT_IN_PROTOCOL;

  //
  // Device Path differences
  //
  #define EFI_DP_TYPE_UNPACKED                0x80
  #define IsDevicePathUnpacked(a)     ( (a)->Type & EFI_DP_TYPE_UNPACKED )

  #define UNKNOWN_DEVICE_GUID \
    { 0xcf31fac5, 0xc24e, 0x11d2,  {0x85, 0xf3, 0x0, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b}  }

#if 0
  #define SAL_SYSTEM_TABLE_GUID \
  { \
    0xeb9d2d32, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} \
  }	
#endif	
	
  #define NextMemoryDescriptor(_Ptr, _Size)   ((EFI_MEMORY_DESCRIPTOR *) (((UINT8 *) (_Ptr)) + (_Size)))

  #define EFI_GLOBAL_VARIABLE_GUID EFI_GLOBAL_VARIABLE
  #define EFI_SMBIOS_TABLE_GUID SMBIOS_TABLE_GUID
  #define EFI_SAL_SYSTEM_TABLE_GUID SAL_SYSTEM_TABLE_GUID
  #define EFI_FILE_SYSTEM_VOLUME_LABEL_INFO_ID_GUID EFI_FILE_SYSTEM_VOLUME_LABEL_ID
  #define LOAD_FILE_PROTOCOL_GUID EFI_LOAD_FILE_PROTOCOL_GUID
  #define EFI_SIMPLE_TEXT_OUT_PROTOCOL_GUID EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID
  #define EFI_FILE_SYSTEM_INFO_ID_GUID EFI_FILE_SYSTEM_INFO_ID

  extern EFI_GUID  gEfiVariableStoreProtocolGuid;

  #define EFI_VARIABLE_STORE_PROTOCOL_GUID    \
    { 0xf088cd91, 0xa046, 0x11d2, {0x8e, 0x42, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }

#endif

#endif
