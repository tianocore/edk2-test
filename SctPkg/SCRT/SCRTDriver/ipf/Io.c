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

  Io.c

--*/

#include "Io.h"

//
// Each IPF platform has to define this value.
//
extern EFI_PHYSICAL_ADDRESS  mIoPortSpaceAddress;


EFI_STATUS
SalInternalIoOrMemRead (
  IN      BOOLEAN                      MmioFlag,
  IN      EFI_PEI_CPU_IO_PPI_WIDTH    Width,
  IN      VOLATILE_POINTER             Address,
  IN      UINTN                        Count,
  IN OUT  VOLATILE_POINTER             Buffer
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  MmioFlag  - GC_TODO: add argument description
  Width     - GC_TODO: add argument description
  Address   - GC_TODO: add argument description
  Count     - GC_TODO: add argument description
  Buffer    - GC_TODO: add argument description

Returns:

  EFI_INVALID_PARAMETER - GC_TODO: Add description for return value
  EFI_INVALID_PARAMETER - GC_TODO: Add description for return value
  EFI_SUCCESS - GC_TODO: Add description for return value

--*/
{
  UINTN     AlignMask;
  BOOLEAN   BufferAlignedFlag;
  DATA_SIZE Data;
  UINT64    IoAddress;
  UINTN     AddressStride;
  UINTN     BufferStride;

  AlignMask = (1 << (Width & 0x03)) - 1;

  if (Address.Value & AlignMask) {
    return EFI_INVALID_PARAMETER;
  }

  AddressStride = (UINTN)1 << (Width & 0x03);
  BufferStride  = AddressStride;

  if (Width >= EfiPeiCpuIoWidthFifoUint8 && Width <= EfiPeiCpuIoWidthFifoUint64) {
    AddressStride = 0;
  }

  if (Width >= EfiPeiCpuIoWidthFillUint8 && Width <= EfiPeiCpuIoWidthFillUint64) {
    BufferStride = 0;
  }

  Width             = Width & 0x03;

  BufferAlignedFlag = (BOOLEAN) (Buffer.Value & AlignMask) == 0;

  //
  // Do count transfers of Width size. If EfiPeiCpuIoWidthUint8, EfiPeiCpuIoWidthUint16,
  // EfiPeiCpuIoWidthUint32, or EfiPeiCpuIoWidthUint64 increment Address and the buffer by Width after every
  // transaction. If EfiPeiCpuIoWidthFifoUint8, EfiPeiCpuIoWidthFifoUint16, EfiPeiCpuIoWidthFifoUint32,
  // or EfiPeiCpuIoWidthFifoUint64 repeat the accesses to the same Address but increment the buffer after
  // every transaction. If EfiPeiCpuIoWidthFillUint8, EfiPeiCpuIoWidthFillUint16, EfiPeiCpuIoWidthFillUint32,
  // or EfiPeiCpuIoWidthFillUint64 increament the Address, but not the buffer after every transaction.
  //
  // If Buffer is not aligned on a Width boundry we read data into a local
  // variable and byte copy it into the callers non aligned buffer.
  //
  // If we are doing Io access IoPort is IO BASE + Port address.
  //  IO BASE is 64 MB aligned 0xfffffffffc000000
  //  Port address is 0 - 64K  0x000000000000ffff
  // Every time through the loop we convert IoPort to the MMIO Address used to
  // do IO.
  //
  IoAddress = Address.Value;
  while (Count > 0) {
    MemoryFence ();

    if (!MmioFlag) {
      Address.Value = PORT_AND_IO_BASE_TO_MEM (IoAddress);
    }

    switch (Width) {

    case EfiPeiCpuIoWidthUint8:
      *Buffer.Uint8 = *Address.Uint8;
      break;

    case EfiPeiCpuIoWidthUint16:
      if (BufferAlignedFlag) {
        *Buffer.Uint16 = *Address.Uint16;
      } else {
        //
        // If Buffer is misaligned read Address data into temp area and byte
        //  copy into the users buffer.
        //
        Data.Uint16         = *Address.Uint16;
        (*Buffer.Array)[0]  = Data.Array[0];
        (*Buffer.Array)[1]  = Data.Array[1];
      }
      break;

    case EfiPeiCpuIoWidthUint32:
      if (BufferAlignedFlag) {
        *Buffer.Uint32 = *Address.Uint32;
      } else {
        //
        // If Buffer is misaligned read Address data into temp area and byte
        //  copy into the users buffer.
        //
        Data.Uint32         = *Address.Uint32;
        (*Buffer.Array)[0]  = Data.Array[0];
        (*Buffer.Array)[1]  = Data.Array[1];
        (*Buffer.Array)[2]  = Data.Array[2];
        (*Buffer.Array)[3]  = Data.Array[3];
      }
      break;

    case EfiPeiCpuIoWidthUint64:
      if (BufferAlignedFlag) {
        *Buffer.Uint64++ = *Address.Uint64;
      } else {
        //
        // If Buffer is misaligned read Address data into temp area and byte
        //  copy into the users buffer.
        //
        Data.Uint64         = *Address.Uint64;
        (*Buffer.Array)[0]  = Data.Array[0];
        (*Buffer.Array)[1]  = Data.Array[1];
        (*Buffer.Array)[2]  = Data.Array[2];
        (*Buffer.Array)[3]  = Data.Array[3];
        (*Buffer.Array)[4]  = Data.Array[4];
        (*Buffer.Array)[5]  = Data.Array[5];
        (*Buffer.Array)[6]  = Data.Array[6];
        (*Buffer.Array)[7]  = Data.Array[7];
      }
      break;

    default:
      return EFI_INVALID_PARAMETER;
    }

    Buffer.Uint8 += BufferStride;
    if (MmioFlag) {
      Address.Uint8 += AddressStride;
    } else {
      IoAddress += AddressStride;
    }

    Count--;
  }

  return EFI_SUCCESS;
}



EFI_STATUS
SalInternalIoOrMemWrite (
  IN      BOOLEAN                      MmioFlag,
  IN      EFI_PEI_CPU_IO_PPI_WIDTH    Width,
  IN      VOLATILE_POINTER             Address,
  IN      UINTN                        Count,
  IN OUT  VOLATILE_POINTER             Buffer
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  MmioFlag  - GC_TODO: add argument description
  Width     - GC_TODO: add argument description
  Address   - GC_TODO: add argument description
  Count     - GC_TODO: add argument description
  Buffer    - GC_TODO: add argument description

Returns:

  EFI_INVALID_PARAMETER - GC_TODO: Add description for return value
  EFI_INVALID_PARAMETER - GC_TODO: Add description for return value
  EFI_SUCCESS - GC_TODO: Add description for return value

--*/
{
  UINTN     AlignMask;
  BOOLEAN   BufferAlignedFlag;
  DATA_SIZE Data;
  UINT64    IoAddress;
  UINTN     AddressStride;
  UINTN     BufferStride;

  AlignMask = (1 << (Width & 0x03)) - 1;

  if (Address.Value & AlignMask) {
    return EFI_INVALID_PARAMETER;
  }

  AddressStride = (UINTN)1 << (Width & 0x03);
  BufferStride  = AddressStride;

  if (Width >= EfiPeiCpuIoWidthFifoUint8 && Width <= EfiPeiCpuIoWidthFifoUint64) {
    AddressStride = 0;
  }

  if (Width >= EfiPeiCpuIoWidthFillUint8 && Width <= EfiPeiCpuIoWidthFillUint64) {
    BufferStride = 0;
  }

  Width             = Width & 0x03;

  BufferAlignedFlag = (BOOLEAN) (Buffer.Value & AlignMask) == 0;

  //
  // Do count transfers of Width size. If EfiPeiCpuIoWidthUint8, EfiPeiCpuIoWidthUint16,
  // EfiPeiCpuIoWidthUint32, or EfiPeiCpuIoWidthUint64 increment Address and the buffer by Width after every
  // transaction. If EfiPeiCpuIoWidthFifoUint8, EfiPeiCpuIoWidthFifoUint16, EfiPeiCpuIoWidthFifoUint32,
  // or EfiPeiCpuIoWidthFifoUint64 repeat the accesses to the same Address but increment the buffer after
  // every transaction. If EfiPeiCpuIoWidthFillUint8, EfiPeiCpuIoWidthFillUint16, EfiPeiCpuIoWidthFillUint32,
  // or EfiPeiCpuIoWidthFillUint64 increament the Address, but not the buffer after every transaction.
  // If Buffer is not aligned on a Width boundry we read data into a local
  // variable and byte copy it into the callers non aligned buffer.
  //
  // If we are doing Io access IoPort is IO BASE + Port address.
  //  IO BASE is 64 MB aligned 0xfffffffffc000000
  //  Port address is 0 - 64K  0x000000000000ffff
  // Every time through the loop we convert IoPort to the MMIO Address used to
  // do IO.
  //
  IoAddress = Address.Value;
  while (Count > 0) {

    if (!MmioFlag) {
      Address.Value = PORT_AND_IO_BASE_TO_MEM (IoAddress);
    }

    switch (Width) {

    case EfiPeiCpuIoWidthUint8:
      *Address.Uint8 = *Buffer.Uint8;
      break;

    case EfiPeiCpuIoWidthUint16:
      if (BufferAlignedFlag) {
        *Address.Uint16 = *Buffer.Uint16;
      } else {
        //
        // If Buffer is misaligned read Address data into temp area and byte
        //  copy into the users buffer.
        //
        Data.Array[0]   = (*Buffer.Array)[0];
        Data.Array[1]   = (*Buffer.Array)[1];
        *Address.Uint16 = Data.Uint16;
      }
      break;

    case EfiPeiCpuIoWidthUint32:
      if (BufferAlignedFlag) {
        *Address.Uint32 = *Buffer.Uint32;
      } else {
        //
        // If Buffer is misaligned read Address data into temp area and byte
        //  copy into the users buffer.
        //
        Data.Array[0]   = (*Buffer.Array)[0];
        Data.Array[1]   = (*Buffer.Array)[1];
        Data.Array[2]   = (*Buffer.Array)[2];
        Data.Array[3]   = (*Buffer.Array)[3];
        *Address.Uint32 = Data.Uint32;
      }
      break;

    case EfiPeiCpuIoWidthUint64:
      if (BufferAlignedFlag) {
        *Address.Uint64 = *Buffer.Uint64;
      } else {
        //
        // If Buffer is misaligned read Address data into temp area and byte
        //  copy into the users buffer.
        //
        Data.Array[0]   = (*Buffer.Array)[0];
        Data.Array[1]   = (*Buffer.Array)[1];
        Data.Array[2]   = (*Buffer.Array)[2];
        Data.Array[3]   = (*Buffer.Array)[3];
        Data.Array[4]   = (*Buffer.Array)[4];
        Data.Array[5]   = (*Buffer.Array)[5];
        Data.Array[6]   = (*Buffer.Array)[6];
        Data.Array[7]   = (*Buffer.Array)[7];
        *Address.Uint64 = Data.Uint64;
      }
      break;

    default:
      return EFI_INVALID_PARAMETER;
    }

    Buffer.Uint8 += BufferStride;
    if (MmioFlag) {
      Address.Uint8 += AddressStride;
    } else {
      IoAddress += AddressStride;
    }

    MemoryFence ();
    Count--;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
SalIoRead (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  )
/*++

Routine Description:

 Performs CPU native Memory IO read.

Arguments:

  Global   - SalGlobal variable
  Width    - Signifies the width of the I/O operation.  
  Address - The base address of the I/O operation.  The caller is responsible 
             for aligning the Address if required. 
  Count    - The number of I/O operations to perform.  Bytes moved is Width 
             size * Count, starting at Address.
  Buffer  - The destination buffer to store the results.  
              
Returns: 

  EFI_SUCCESS            - The data was read from or written to the EFI System.
  EFI_INVALID_PARAMETER - Width is invalid for this EFI System.
  EFI_INVALID_PARAMETER  - Buffer is NULL.
  EFI_UNSUPPORTED        - The Buffer is not aligned for the given Width.
  EFI_UNSUPPORTED        - The address range specified by Address, Width, and
                           Count is not valid for this EFI System.

--*/
// GC_TODO:    VirtualMode - add argument and description to function comment
// GC_TODO:    IoPortSpaceAddress - add argument and description to function comment
{
  VOLATILE_POINTER  VolatileAddress;
  VOLATILE_POINTER  VolatileBuffer;

  VolatileBuffer.Void   = Buffer;
  VolatileAddress.Value = Address;
  //
  // Add the 64MB aligned IO Port space to the IO address
  //
  VolatileAddress.Value += mIoPortSpaceAddress;

  return SalInternalIoOrMemRead (
          FALSE,
          Width,
          VolatileAddress,
          Count,
          VolatileBuffer
          );
}



EFI_STATUS
EFIAPI
SalIoWrite (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  )
/*++

Routine Description:

 Performs CPU native Memory IO.

Arguments:

  Global   - SalGlobal variable
  Width    - Signifies the width of the I/O operation.  
  Address  - The base address of the I/O operation.  The caller is responsible 
             for aligning the Address if required. 
  Count    - The number of I/O operations to perform.  Bytes moved is Width 
             size * Count, starting at Address.
  Buffer  - The source buffer to write data.

Returns: 

  EFI_SUCCESS            - The data was read from or written to the EFI System.
  EFI_INVALID_PARAMETER  - Width is invalid for this EFI System.
  EFI_INVALID_PARAMETER  - Buffer is NULL.
  EFI_UNSUPPORTED        - The Buffer is not aligned for the given Width.
  EFI_UNSUPPORTED        - The address range specified by Address, Width, and 
                           Count is not valid for this EFI System.
--*/
// GC_TODO:    VirtualMode - add argument and description to function comment
// GC_TODO:    IoPortSpaceAddress - add argument and description to function comment
{
  VOLATILE_POINTER  VolatileAddress;
  VOLATILE_POINTER  VolatileBuffer;

  VolatileBuffer.Void   = Buffer;
  VolatileAddress.Value = Address;
  //
  // Add the 64MB aligned IO Port space to the IO address
  //
  VolatileAddress.Value += mIoPortSpaceAddress;

  return SalInternalIoOrMemWrite (
          FALSE,
          Width,
          VolatileAddress,
          Count,
          VolatileBuffer
          );
}



EFI_STATUS
EfiIoWrite (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  )
/*++

Routine Description:
  Perform an IO write into Buffer.

Arguments:
  Width   - Width of write transaction, and repeat operation to use
  Address - IO address to write
  Count   - Number of times to write the IO address.
  Buffer  - Buffer to write data from. size is Width * Count

Returns:
  Status code

--*/
{
  return SalIoWrite ((UINT64) Width, Address, Count, Buffer);
}


EFI_STATUS
EfiIoRead (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  )
/*++

Routine Description:
  Perform an IO read into Buffer.

Arguments:
  Width   - Width of read transaction, and repeat operation to use
  Address - IO address to read
  Count   - Number of times to read the IO address.
  Buffer  - Buffer to read data into. size is Width * Count

Returns:
  Status code

--*/
{
  return SalIoRead ((UINT64) Width, Address, Count, Buffer);
}


VOID
FixAddress (
  IN UINTN     *PhyAddress
  ) 
{
  //
  // IPF Address Mapping Mechanism:
  // Virtual Address = Physical Address  + VIRT_TO_PHYS_OFFSET (Only for Runtime Memory and ACPI Memory)
  // For ACPI tables, they should be fixed when referenced in runtime virtual addressing.
  //
  if (*PhyAddress != 0) {
    *PhyAddress += VIRT_TO_PHYS_OFFSET;
  }
}
