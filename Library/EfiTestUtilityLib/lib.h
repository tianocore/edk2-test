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

  lib.h

Abstract:

  EFI library header files

--*/

#include "Efi.h"
#include "EfiTestUtilityLib.h"
#include "EfiCommonLib.h"

#include EFI_PROTOCOL_DEFINITION (UnicodeCollation)
#include EFI_PROTOCOL_DEFINITION (SimpleTextOut)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCode)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCodeCallBack)
#include EFI_PROTOCOL_DEFINITION (EfiNetworkInterfaceIdentifier)
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (DiskIo)
#include EFI_PROTOCOL_DEFINITION (LoadFile)
#include EFI_PROTOCOL_DEFINITION (SerialIo)
#include EFI_PROTOCOL_DEFINITION (SimpleNetwork)
#include EFI_PROTOCOL_DEFINITION (VariableStore)
#include EFI_PROTOCOL_DEFINITION (DebugAssert)
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (DriverConfiguration)
#include EFI_PROTOCOL_DEFINITION (DriverDiagnostics)
#include EFI_PROTOCOL_DEFINITION (ComponentName)
#include EFI_GUID_DEFINITION (GlobalVariable)
#include EFI_GUID_DEFINITION (Gpt)
#include EFI_GUID_DEFINITION (Mps)
#include EFI_GUID_DEFINITION (Acpi)
#include EFI_GUID_DEFINITION (SmBios)
#include EFI_GUID_DEFINITION (SalSystemTable)

//
// Prototypes
//

INTN
LibStubStriCmp (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *S1,
    IN CHAR16                           *S2
    );

BOOLEAN
LibStubMetaiMatch (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *String,
    IN CHAR16                           *Pattern
    );

VOID
LibStubStrLwrUpr (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *Str
    );

BOOLEAN
LibMatchDevicePaths (
    IN  EFI_DEVICE_PATH_PROTOCOL *Multi,
    IN  EFI_DEVICE_PATH_PROTOCOL *Single
    );

EFI_DEVICE_PATH_PROTOCOL *
LibDuplicateDevicePathInstance (
    IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
    );


//
// Globals
//
extern BOOLEAN                          LibInitialized;
extern BOOLEAN                          LibFwInstance;
extern EFI_SIMPLE_TEXT_OUT_PROTOCOL     *LibRuntimeDebugOut;
extern EFI_UNICODE_COLLATION_PROTOCOL   *UnicodeInterface;
extern EFI_UNICODE_COLLATION_PROTOCOL   LibStubUnicodeInterface;
extern EFI_RAISE_TPL                    LibRuntimeRaiseTPL;
extern EFI_RESTORE_TPL                  LibRuntimeRestoreTPL;
extern UINTN                            EFIDebug;
