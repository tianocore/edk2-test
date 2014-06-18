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

  SCRTDriver.c

--*/

#include "SCRTDriver.h"
#include "SctLib.h"


CHAR16  *gVarName             = L"UEFIRuntimeVariable";
CHAR16  *gTestRecordName      = L"TestRecord";
EFI_RUNTIME_SERVICES            *VRT;
static EFI_BOOT_SERVICES        *mBS;
static EFI_RUNTIME_SERVICES     *mRT;
static EFI_EVENT                mEfiVirtualNotifyEvent;

EFI_GUID  gRuntimeFuncAddressGuid = RUNTIME_FUNC_ADDRESS_GUID;


VOID
EFIAPI
SCRTDriverVirtualNotifyEvent (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_EVENT_NOTIFY  ChildNotify;

  if (Context != NULL) {
    ChildNotify = (EFI_EVENT_NOTIFY) (UINTN) Context;
    ChildNotify (Event, NULL);
  }
}


EFI_STATUS
SCRTRuntimeDriverInit(
  IN EFI_SYSTEM_TABLE        *SystemTable,
  IN EFI_EVENT_NOTIFY        GoVirtualChildEvent
)
{
  EFI_STATUS  Status;
  mBS  = SystemTable->BootServices;
  mRT  = SystemTable->RuntimeServices;
  VRT  = mRT;
  
  Status = mBS->CreateEvent (
                  EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
                  TPL_NOTIFY,
                  SCRTDriverVirtualNotifyEvent,
                  (VOID *)(UINTN)GoVirtualChildEvent,
                  &mEfiVirtualNotifyEvent
                  );
  return Status;
}

VOID
SCRTDriverClassAddressChangeEvent (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
/*++

Routine Description:

  The event handler to change physical address to virtual address

Arguments:

  Event   - The event that be siganlled when virtual address changed
  Context - The pointer of the procedure instance

Returns:

  None

--*/  
{
  //
  // Register a virtual notification event to convert the global pointer variables.
  //
  mRT->ConvertPointer (0, (VOID **)&VRT);
}


EFI_STATUS
InitializeSCRTDriver (
  IN EFI_HANDLE              ImageHandle,
  IN EFI_SYSTEM_TABLE        *SystemTable
  )
/*++

Routine Description:

  This function does initialization for SCRTDriver

Arguments:

  ImageHandle   - The firmware allocated handle for the EFI image.
  SystemTable   - A pointer to the EFI System Table.

Returns:
  
  Status code
  
--*/  
{
  UINTN                Size;
  UINTN                FuncAddr;
  EFI_STATUS           Status;
  SCRT_STUB_TABLE      *StubTable;
  
  //
  // Intialize Runtime Driver Lib and Register a virtual notification event.
  //
  SCRTRuntimeDriverInit (SystemTable,SCRTDriverClassAddressChangeEvent);

  FuncAddr = (UINTN) RuntimeTestFunc;

  Size = sizeof(SCRT_STUB_TABLE);
  Status  = mBS->AllocatePool (EfiRuntimeServicesData, Size, (VOID **) &StubTable);
  if (EFI_ERROR(Status)){
    return Status;
  }
  StubTable->Signature = SCRT_STUB_TABLE_SIGNATURE;
  StubTable->FuncAddr  = FuncAddr;
  
  Status = mBS->InstallConfigurationTable (&gRuntimeFuncAddressGuid, (VOID*)StubTable);
  if (EFI_ERROR(Status)){
    return Status;
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
RuntimeTestFunc (
  UINTN    HandOffAddr
  )
/*++

Routine Description:

  Perform runtime service test in a virtual addressing mode.
  
Arguments:

  NONE

Returns:

  NONE
  
--*/   
{
  CONF_INFO  ConfigData;

  //
  // Parse runtime hand off data
  //
  ConsumeHandOff(HandOffAddr, &ConfigData);
  SctAPrint ("BitMap = 0x%x\n", ConfigData.InfoData);
  if (ConfigData.BitMap.Signature != CONFIGURE_INFO_SIGNATURE) {
    SctAPrint ("Find Configuration Data Corrupted, Hang!!\n");
    return EFI_COMPROMISED_DATA;
  } 
  //
  // Dump Runtime Table
  //
  DumpRuntimeTable();

  InitVariableRecord(&ConfigData);
  SctAPrint ("==================Variable Services Test Start==================\n\n");
  EfiVariableTestVirtual(&ConfigData);
  SctAPrint ("===================Variable Services Test End===================\n\n\n");

  SctAPrint ("====================Time Services Test Start====================\n\n");
  EfiTimeTestVirtual(&ConfigData);
  SctAPrint ("=====================Time Services Test End=====================\n\n\n");

  SctAPrint ("==================Capsule Services Test Start===================\n\n");
  EfiCapsuleTestVirtual(&ConfigData);
  SctAPrint ("===================Capsule Services Test End====================\n\n\n");

  SctAPrint ("====================Misc Services Test Start====================\n\n");
  EfiMiscTestVirtual(&ConfigData);
  SctAPrint ("=====================Misc Services Test End=====================\n\n\n");

  SctAPrint ("===================Reset Services Test Start=================\n\n");
  EfiResetTestVirtual(&ConfigData);

  return EFI_SUCCESS;
}
