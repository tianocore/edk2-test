/** @file

  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
