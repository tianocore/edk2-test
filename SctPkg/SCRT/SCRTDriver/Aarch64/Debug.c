/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2011 - 2012 ARM Ltd. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

/*++

Module Name:

  Debug.c

--*/

#include "SCRTDriver.h"

UINTN                 mHandOffPtr        =  0;
EFI_PHYSICAL_ADDRESS  mIoPortSpaceAddress = 0;


EFI_STATUS
ConsumeHandOff (
  IN  UINTN         HandOffAddr,
  OUT CONF_INFO     *ConfigData
  )
{
   RUNTIME_HANDOFF   *HandOffPtr;
   //
   // First fix the memory address of hand off data.
   //
   FixAddress(&HandOffAddr);
   mHandOffPtr = HandOffAddr;
   HandOffPtr  = (RUNTIME_HANDOFF*)mHandOffPtr;
   *ConfigData =  HandOffPtr->ConfigureInfo;

   if (!HandOffPtr->DebuggerInfo.MmioFlag){
     //
     // If debug port is I/O mapped, fix IoBase Address.
     //
     FixAddress(&HandOffPtr->DebuggerInfo.IoBase);
     mIoPortSpaceAddress = HandOffPtr->DebuggerInfo.IoBase;
   } else {
     //
     // If debug port is MMIO, fix MmioBase Address.
     //
     FixAddress(&HandOffPtr->DebuggerInfo.MmioBase);
   }

   return EFI_SUCCESS;
}


EFI_STATUS
Send2UART (
  CHAR8                *String
  )
{
  //
  // TODO: On ARM platforms use platform specific functions to
  // write the data to UART.
  //
  return EFI_SUCCESS;
}



EFI_STATUS
DebugWorker (
  IN CHAR8    *String
  )
{
  EFI_STATUS    Status;

  //
  // Send text message to registered UART.
  //
  Status = Send2UART(String);
  return Status;
}
