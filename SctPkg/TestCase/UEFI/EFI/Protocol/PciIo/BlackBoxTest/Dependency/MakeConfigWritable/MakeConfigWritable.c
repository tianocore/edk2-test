/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MakeConfigWritable.c

Abstract:

  source file to make the Card configuration space writable.

--*/

#include "Common.h"
#include "Main.h"

EFI_STATUS
MakeConfigWritable  (
 IN PCIDev  *Dev
 )
{
  UINT8           CurrentState;

  CurrentState = ReadCardState (Dev);

  if (CurrentState == 0xFF) {

    //
    //the card has been plugged in just now and initialize the card.
    //
    if (!InitializeCard (Dev)) {
      SctPrint (L"Unable to init Test Card.");
      return  EFI_DEVICE_ERROR;
    }
  }

  return WriteMaskBytes (Dev);
}

/*
 *  Read the current state associated with a function of a specialized
 *  PCI add-in card.
 *  @param Device the specific device to read state from.
 *
 */
UINT8
ReadCardState (
  IN  PCIDev      *Device
  )
{
  UINT8   Byte = 0;


  Byte = ReadConfigByte (
           Device->RootBridgeIo,
           Device->BaseInfo.BusNum,
           Device->BaseInfo.DevNum,
           Device->BaseInfo.FuncNum,
           OFF_SP_STATE
           );
  return Byte;
}

/*
 *  Write the current state associated with a function of a specialized
 *  PCI add-in card.
 *  @param Device the device pointer to be written.
 *  @param State the state to be written.
 */
VOID
WriteCardState (
  IN  PCIDev          *Device,
  IN  UINT8           State
  )
{
  WriteConfigByte (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    Device->BaseInfo.FuncNum,
    OFF_SP_STATE,
    State
    );
}

/*
 *  Sets the current state for each special device to the initial state.
 *  @param List the PCIDev device list pointer.
 */
BOOLEAN
InitializeCard (
  IN  PCIDev          *Dev
  )
{
  PCIDev        *Device;
  UINT32        MemoryAddress;
  UINT32        CtrlReg;
  UINT16        ByteCount;
  UINT16        Function ;
  UINT32        Dword;
  UINT8         Index;

  //
  // Setup for routine
  //

  Device        = Dev;
  Dword         = 0;
  Index         = 0;

  //
  // Initialize special device
  //

  //
  // Only initialize the card once.  This is only an issue if the card
  // has already been active in some previous state.  Then this routine
  // will be called for each function of the card.
  //
  if (Device->BaseInfo.FuncNum == 0) {
    //
    // Reset the card
    //

    CtrlReg = ReadConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MASTER_CTRL_REG
                );

    WriteConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MASTER_CTRL_REG,
                CtrlReg | NC_RESET_BIT
                );

    CtrlReg = ReadConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MASTER_CTRL_REG
                );

    Dword = ReadConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MASTER_CTRL_REG
                );


    WriteConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MASTER_CTRL_REG,
                CtrlReg & ~NC_RESET_BIT
                );

    //
    // Setup for mode 3
    //
    Dword = ReadConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MASTER_CTRL_REG
                );


    WriteConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MASTER_CTRL_REG,
                Dword | NC_MODE3_BIT | NC_ROM_224K_BIT
                );

    //
    // Initialize the SRAM on the card
    //
    // (1) Fill function areas with zeros
    // (2) Fill mask areas with zeros
    //

    for (Function = 0 ; Function < NC_MAX_FUNCTION ; Function++) {
      for (MemoryAddress = NC_ROM_TOP_ADDRESS + (Function * NC_BYTES_PER_FUNCTION * 2),
        ByteCount = 0 ; ByteCount < NC_BYTES_PER_FUNCTION ;
          MemoryAddress += sizeof (UINT32), ByteCount += sizeof (UINT32)) {
        if ((ByteCount != NC_MASTER_CTRL_REG) &&
          (ByteCount != NC_MEMORY_ADDRESS_REG) &&
          (ByteCount != NC_MEMORY_DATA_REG) &&
          (ByteCount != NC_EXPROM_REG) )  {
          WriteConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MEMORY_ADDRESS_REG,
                MemoryAddress
                );

          WriteConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MEMORY_DATA_REG,
                0x00000000
                );
        }
      }
    }

    for (Function = 0 ; Function < NC_MAX_FUNCTION ; Function++) {
      for (MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION + (Function * NC_BYTES_PER_FUNCTION * 2),
        ByteCount = 0 ; ByteCount < NC_BYTES_PER_FUNCTION ; MemoryAddress += sizeof (UINT32), ByteCount += sizeof (UINT32)) {

        WriteConfigDWord (
                Device->RootBridgeIo,
                Device->BaseInfo.BusNum,
                Device->BaseInfo.DevNum,
                Device->BaseInfo.FuncNum,
                NC_MEMORY_ADDRESS_REG,
                MemoryAddress
                );

        if ((ByteCount != NC_MEMORY_DATA_REG) &&
            (ByteCount != NC_EXPROM_REG) ) {

          WriteConfigDWord (
                  Device->RootBridgeIo,
                  Device->BaseInfo.BusNum,
                  Device->BaseInfo.DevNum,
                  Device->BaseInfo.FuncNum,
                  NC_MEMORY_DATA_REG,
                  0x00000000
                  );
        } else {
          WriteConfigDWord (
                    Device->RootBridgeIo,
                    Device->BaseInfo.BusNum,
                    Device->BaseInfo.DevNum,
                    Device->BaseInfo.FuncNum,
                    NC_MEMORY_DATA_REG,
                    0xffffffff
                    );
        }
      }
    }

    //
    // Initialize function 0
    //
    if (InitializeCardFunction (Device, 0) == FALSE) {
      return FALSE;
    }
    //
    //set the card state as 0
    //
    WriteCardState (Device, 0);
  }
  return TRUE;
}

/**
 *  update the option rom Image.
 *  @param Device the Pci Device option rom to be updated.
 *  @return EFI_SUCCESS the Rom was updated successfully.
 */
EFI_STATUS
WriteMaskBytes (
  IN PCIDev         *Device
  )
{
  UINTN                   Index;
  UINT32                  MemoryAddress;
  UINT32                  BaseAddress;
  UINT8                   Offset;
  UINT8                   Length;
  CHAR16                  Buffer[MAX_STRING_LENGTH];

  //
  //get the address offset.
  //
  SctInput (
    L"Please input the Address Offset in this Pci configuration space (4 bytes alligned),such as 0x80\r\n",
    Buffer,
    MAX_STRING_LENGTH
    );
  SctPrint (L"\r\n");

  for (Index = 0; Buffer[Index] == L' '; Index++) {
    ;
  }

  if (Buffer[Index] == L'\0') {
    return EFI_ABORTED;
  }

  Offset = (UINT8) SctXtoi (&Buffer[Index]);
  Offset = (UINT8) (Offset & 0xfc);

  //
  //then get the Address length to be masked.
  //
  SctInput (
    L"Please input the Address length to be masked (dividable by 4), such as 0x20\r\n",
    Buffer,
    MAX_STRING_LENGTH
    );
  SctPrint (L"\r\n");

  for (Index = 0; Buffer[Index] == L' '; Index++) {
    ;
  }

  if (Buffer[Index] == L'\0') {
    return EFI_ABORTED;
  }

  Length = (UINT8) SctXtoi (&Buffer[Index]);
  Length = (UINT8) (Length & 0xfc);

  BaseAddress = (UINT32)(NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION + Offset);

  for (MemoryAddress = BaseAddress; MemoryAddress < BaseAddress + Length;
    MemoryAddress += sizeof (UINT32)) {

    //
    //write mask address value.
    //
    WriteConfigDWord (
      Device->RootBridgeIo,
      Device->BaseInfo.BusNum,
      Device->BaseInfo.DevNum,
      Device->BaseInfo.FuncNum,
      NC_MEMORY_ADDRESS_REG,
      MemoryAddress
      );

    //
    //write mask data value to all 1's.
    //
    WriteConfigDWord (
      Device->RootBridgeIo,
      Device->BaseInfo.BusNum,
      Device->BaseInfo.DevNum,
      Device->BaseInfo.FuncNum,
      NC_MEMORY_DATA_REG,
      0xffffffff
      );
  }
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/*
 *  Sets the current state for a given funciton of the special device to
 *  the initial state.  Note that this function sets the header type to 80h.
 *  @param Device the device pointer.
 *  @param FuncNum the function number to be set.
 */
BOOLEAN
InitializeCardFunction (
  IN  PCIDev    *Device,
  IN  UINT8     FuncNum
  )
{
  UINT32  MemoryAddress;
  UINT32  FuncNumBitmask;
  UINT32  InterruptMask;
  UINT32  Dword;

  MemoryAddress  = 0;
  FuncNumBitmask = 0;
  InterruptMask  = 0;

  //
  // Turn on the specified function
  //
  if (FuncNum != 0) {

    FuncNumBitmask = NC_FUNC0_ENABLE ;
    FuncNumBitmask <<= FuncNum ;
    Dword = ReadConfigDWord (
              Device->RootBridgeIo,
              Device->BaseInfo.BusNum,
              Device->BaseInfo.DevNum,
              0,
              NC_MASTER_CTRL_REG
              );

    WriteConfigDWord (
              Device->RootBridgeIo,
              Device->BaseInfo.BusNum,
              Device->BaseInfo.DevNum,
              0,
              NC_MASTER_CTRL_REG,
              Dword | FuncNumBitmask
              );
  }

  //
  // Set the vendor id and device id
  //

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_VENDOR_ID ;
  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xFFFFFFFF
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + (FuncNum * NC_BYTES_PER_FUNCTION * 2)
    + OFF_VENDOR_ID ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x04538086
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_VENDOR_ID ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xC0000000
    );

   //
   // Set the command and status registers
   //

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_COMMAND ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xFFFFFFFF
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + (FuncNum * NC_BYTES_PER_FUNCTION * 2)
    + OFF_COMMAND ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x04000000
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_COMMAND;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x00000007
    );

  //
  //set mask as 0x0007 the low 3 bit can be written in command register.
  //0x00000007

  //
  // Set the class code and revision id
  //

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_REVISION_ID ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xFFFFFFFF
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + (FuncNum * NC_BYTES_PER_FUNCTION * 2)
    + OFF_REVISION_ID ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xFF000005
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_REVISION_ID ;


  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x00000000
    );
  //
  // Set the BIST, header type, latency timer, and cache line size
  //
  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_CACHELS;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xFFFFFFFF
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + (FuncNum * NC_BYTES_PER_FUNCTION * 2)
    + OFF_CACHELS ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x00800000
    );

   MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_CACHELS ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x0000FF00
    );
  //
  // Set the int line, int pin, min grant, and max latency
  //

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_INTLINE ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xFFFFFFFF
    );

  if ((FuncNum == 0) || (FuncNum == 3) || (FuncNum == 6) || (FuncNum == 7)) {
    InterruptMask = NC_INTA_MASK ;
  } else if (FuncNum == 4) {
    InterruptMask = NC_INTB_MASK ;
  } else if (FuncNum == 5) {
    InterruptMask = NC_INTC_MASK ;
  } else if ((FuncNum == 1) || (FuncNum == 2)) {
    InterruptMask = NC_INTD_MASK ;
  }

  MemoryAddress = NC_ROM_TOP_ADDRESS + (FuncNum * NC_BYTES_PER_FUNCTION * 2)
    + OFF_INTLINE ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    InterruptMask
    );


  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_INTLINE ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x000000FF
    );
  //
  // Set the state, expected value, expected don't care, and ctrl registers
  //

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_SP_STATE;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xFFFFFFFF
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + (FuncNum * NC_BYTES_PER_FUNCTION * 2)
    + OFF_SP_STATE ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x00000000
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + NC_BYTES_PER_FUNCTION
    + (FuncNum * NC_BYTES_PER_FUNCTION * 2) + OFF_SP_EX_DONT_CARE ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0xFFFFFFFF
    );

  MemoryAddress = NC_ROM_TOP_ADDRESS + (FuncNum * NC_BYTES_PER_FUNCTION * 2)
    + OFF_SP_EX_DONT_CARE ;

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_ADDRESS_REG,
    MemoryAddress
    );

  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    NC_MEMORY_DATA_REG,
    0x00000C00
    );
   //
   //Clear the command register
   //
  WriteConfigDWord (
    Device->RootBridgeIo,
    Device->BaseInfo.BusNum,
    Device->BaseInfo.DevNum,
    FuncNum,
    OFF_COMMAND,
    0
    );

  return TRUE;
}
