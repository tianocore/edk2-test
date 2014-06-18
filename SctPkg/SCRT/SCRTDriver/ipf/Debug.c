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
