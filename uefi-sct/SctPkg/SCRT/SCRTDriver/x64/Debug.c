/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   

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

VOID
UartReadWrite (
  IN BOOLEAN                 ReadFlag,
  IN EFI_PHYSICAL_ADDRESS    Address,
  IN OUT UINT8               *Data
  )
{
  if (ReadFlag) {
    MemoryFence (); 
    *Data = *(volatile UINT8 *)(UINTN)Address;
  } else {
    *(volatile UINT8 *)(UINTN)Address = *Data;
    MemoryFence (); 
  }
}


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

   *ConfigData =  HandOffPtr->ConfigureInfo;

   return EFI_SUCCESS;
}




VOID
Send2IO (
  UINT64     Address,
  CHAR8      *String
  )
{
  UINT8 Data;
  CHAR8 *Ptr;

  Ptr = String;
  //
  // Send text message to IO UART
  //
  while (*Ptr) {
    EfiIoRead (EfiPeiCpuIoWidthUint8, Address + 0x5, 1, &Data);
    //
    // Wait until Line Status Register (LSR) Bit5 Transmitter Holding 
    // Register Empty(THRE) is high, then write.
    //
    while ((Data & 0x20) == 0) {
      EfiIoRead (EfiPeiCpuIoWidthUint8, Address + 0x5, 1, &Data);
    }
    Data = *Ptr++;
    //
    // Write data into Transmit Buffer Register
    //
    EfiIoWrite (EfiPeiCpuIoWidthUint8, Address, 1, &Data);
  }
}


VOID
Send2MMIO (
  UINT64     Address,
  CHAR8      *String
  )
{
  UINT8 Data;
  CHAR8 *Ptr;

  Ptr = String;
  //
  // Send text message to MMIO UART
  //
  while (*Ptr) {
    UartReadWrite(TRUE, Address + 0x5, &Data);
    //
    // Wait until Line Status Register (LSR) Bit5 Transmitter Holding 
    // Register Empty(THRE) is high, then write.
    //
    while ((Data & 0x20) == 0) {
      UartReadWrite(TRUE, Address + 0x5, &Data);
    }
    Data = *Ptr++;
    //
    // Write data into Transmit Buffer Register
    //
    UartReadWrite(FALSE, Address, &Data);
  }
}


EFI_STATUS
Send2UART (
  CHAR8                *String
  )
{
   RUNTIME_HANDOFF   *HandOffPtr;
   HandOffPtr  = (RUNTIME_HANDOFF*)mHandOffPtr;

  //
  // Only concern System Memory Space and System I/O Space
  //
  if(HandOffPtr->DebuggerInfo.MmioFlag) {
    Send2MMIO(HandOffPtr->DebuggerInfo.MmioBase, String);
  } else {
    Send2IO (HandOffPtr->DebuggerInfo.IoPort, String);
  }
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
