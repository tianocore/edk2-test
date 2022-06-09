/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
                  (EFI_EVENT_NOTIFY) SCRTDriverVirtualNotifyEvent,
                  (VOID *)(UINTN)GoVirtualChildEvent,
                  &mEfiVirtualNotifyEvent
                  );
  return Status;
}

VOID
EFIAPI
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
EFIAPI
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
  Printf("BitMap = 0x%x\n", ConfigData.InfoData);
  if (ConfigData.BitMap.Signature != CONFIGURE_INFO_SIGNATURE) {
    Printf ("Find Configuration Data Corrupted, Hang!!\n");
    return EFI_COMPROMISED_DATA;
  } 
  //
  // Dump Runtime Table
  //
  DumpRuntimeTable();

  InitVariableRecord(&ConfigData);
  Printf ("==================Variable Services Test Start==================\n\n");
  EfiVariableTestVirtual(&ConfigData);
  Printf ("===================Variable Services Test End===================\n\n\n");

  Printf ("====================Time Services Test Start====================\n\n");
  EfiTimeTestVirtual(&ConfigData);
  Printf ("=====================Time Services Test End=====================\n\n\n");

  Printf ("==================Capsule Services Test Start===================\n\n");
  EfiCapsuleTestVirtual(&ConfigData);
  Printf ("===================Capsule Services Test End====================\n\n\n");

  Printf ("====================Misc Services Test Start====================\n\n");
  EfiMiscTestVirtual(&ConfigData);
  Printf ("=====================Misc Services Test End=====================\n\n\n");

  Printf ("===================Reset Services Test Start=================\n\n");
  EfiResetTestVirtual(&ConfigData);

  return EFI_SUCCESS;
}
