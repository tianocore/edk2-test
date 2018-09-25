/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Io.c

--*/

#include "Io.h"

STATIC
EFI_STATUS
CpuIoCheckParameter (
  IN EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN UINT64                     Address,
  IN UINTN                      Count,
  IN VOID                       *Buffer,
  IN UINT64                     Limit
  )
/*++

Routine Description:

  Check the validation of parameters for CPU I/O interface functions.

Arguments:

  Width   - Width of the Memory Access
  Address - Address of the Memory access
  Count   - Count of the number of accesses to perform
  Buffer  - Pointer to the buffer to read from memory
  Buffer  - Memory buffer for the I/O operation
  Limit   - Maximum address supported

Returns:

  EFI_INVALID_PARAMETER - Buffer is NULL
  EFI_UNSUPPORTED       - The address range specified by Width, Address and Count is invalid
  EFI_UNSUPPORTED       - The memory buffer is not aligned
  EFI_SUCCESS           - Parameters are OK

--*/
{
  UINTN AlignMask;

  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (Address > Limit) {
    return EFI_UNSUPPORTED;
  }

  //
  // For FiFo type, the target address won't increase during the access,
  // so treat count as 1
  //
  if (Width >= EfiPeiCpuIoWidthFifoUint8 && Width <= EfiPeiCpuIoWidthFifoUint64) {
    Count = 1;
  }

  Width = Width & 0x03;
  if (Address - 1 + ((UINTN)1 << Width) * Count > Limit) {
    return EFI_UNSUPPORTED;
  }

  AlignMask = ((UINTN)1 << Width) - 1;
  if ((UINTN) Buffer & AlignMask) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EFIAPI
CpuIoServiceRead (
  IN  EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN  UINT64                     UserAddress,
  IN  UINTN                      Count,
  OUT VOID                       *UserBuffer
  )
/*++

Routine Description:

  Perform the port I/O read service

Arguments:

  Width   - Width of the port I/O operation
  Address - Base address of the port I/O operation
  Count   - Count of the number of accesses to perform
  Buffer  - Pointer to the destination buffer to store the results

Returns:

  EFI_SUCCESS           - The data was read.
  EFI_INVALID_PARAMETER - Width is invalid.
  EFI_INVALID_PARAMETER - Buffer is NULL.
  EFI_UNSUPPORTED       - The Buffer is not aligned for the given Width.
  EFI_UNSUPPORTED       - The address range specified by Address, Width,
                          and Count is not valid.

--*/
{
  UINTN      InStride;
  UINTN      OutStride;
  UINTN      Address;
  PTR        Buffer;
  EFI_STATUS Status;

  Buffer.buf = (UINT8 *) UserBuffer;

  if (Width >= EfiPeiCpuIoWidthMaximum) {
    return EFI_INVALID_PARAMETER;
  }

  Status = CpuIoCheckParameter (Width, UserAddress, Count, UserBuffer, IA32_MAX_IO_ADDRESS);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Address   = (UINTN) UserAddress;
  InStride  = (UINTN)1 << (Width & 0x03);
  OutStride = InStride;
  if (Width >= EfiPeiCpuIoWidthFifoUint8 && Width <= EfiPeiCpuIoWidthFifoUint64) {
    InStride = 0;
  }

  if (Width >= EfiPeiCpuIoWidthFillUint8 && Width <= EfiPeiCpuIoWidthFillUint64) {
    OutStride = 0;
  }

  Width = Width & 0x03;

  //
  // Loop for each iteration and move the data
  //
  switch (Width) {
  case EfiPeiCpuIoWidthUint8:
    for (; Count > 0; Count--, Buffer.buf += OutStride, Address += InStride) {
      *Buffer.ui8 = CpuIoRead8 ((UINT16) Address);
    }
    break;

  case EfiPeiCpuIoWidthUint16:
    for (; Count > 0; Count--, Buffer.buf += OutStride, Address += InStride) {
      *Buffer.ui16 = CpuIoRead16 ((UINT16) Address);
    }
    break;

  case EfiPeiCpuIoWidthUint32:
    for (; Count > 0; Count--, Buffer.buf += OutStride, Address += InStride) {
      *Buffer.ui32 = CpuIoRead32 ((UINT16) Address);
    }
    break;

  default:
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EFIAPI
CpuIoServiceWrite (
  IN EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN UINT64                     UserAddress,
  IN UINTN                      Count,
  IN VOID                       *UserBuffer
  )
/*++

Routine Description:

  Perform the port I/O write service

Arguments:

  Width   - Width of the port I/O operation
  Address - Base address of the port I/O operation
  Count   - Count of the number of accesses to perform
  Buffer  - Pointer to the source buffer from which to write data

Returns:

  EFI_SUCCESS           - The data was written.
  EFI_INVALID_PARAMETER - Width is invalid.
  EFI_INVALID_PARAMETER - Buffer is NULL.
  EFI_UNSUPPORTED       - The Buffer is not aligned for the given Width.
  EFI_UNSUPPORTED       - The address range specified by Address, Width,
                          and Count is not valid.

--*/
{
  UINTN      InStride;
  UINTN      OutStride;
  UINTN      Address;
  PTR        Buffer;
  EFI_STATUS Status;

  Buffer.buf = (UINT8 *) UserBuffer;

  if (Width >= EfiPeiCpuIoWidthMaximum) {
    return EFI_INVALID_PARAMETER;
  }

  Status = CpuIoCheckParameter (Width, UserAddress, Count, UserBuffer, IA32_MAX_IO_ADDRESS);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Address   = (UINTN) UserAddress;
  InStride  = (UINTN)1 << (Width & 0x03);
  OutStride = InStride;
  if (Width >= EfiPeiCpuIoWidthFifoUint8 && Width <= EfiPeiCpuIoWidthFifoUint64) {
    InStride = 0;
  }

  if (Width >= EfiPeiCpuIoWidthFillUint8 && Width <= EfiPeiCpuIoWidthFillUint64) {
    OutStride = 0;
  }

  Width = Width & 0x03;

  //
  // Loop for each iteration and move the data
  //
  switch (Width) {
  case EfiPeiCpuIoWidthUint8:
    for (; Count > 0; Count--, Buffer.buf += OutStride, Address += InStride) {
      CpuIoWrite8 ((UINT16) Address, *Buffer.ui8);
    }
    break;

  case EfiPeiCpuIoWidthUint16:
    for (; Count > 0; Count--, Buffer.buf += OutStride, Address += InStride) {
      CpuIoWrite16 ((UINT16) Address, *Buffer.ui16);
    }
    break;

  case EfiPeiCpuIoWidthUint32:
    for (; Count > 0; Count--, Buffer.buf += OutStride, Address += InStride) {
      CpuIoWrite32 ((UINT16) Address, *Buffer.ui32);
    }
    break;

  default:
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
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
  return CpuIoServiceWrite(Width, Address, Count, Buffer);
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
  return CpuIoServiceRead (Width, Address, Count, Buffer);
}


VOID
FixAddress (
  IN UINTN     *PhyAddress
  ) 
{
  //
  // IA32 Address Mapping Mechanism:
  // Virtual Address = Physical Address - VIRT_TO_PHYS_OFFSET (if Physical Address > VIRT_TO_PHYS_OFFSET)
  // Virtual Address = Physical Address + VIRT_TO_PHYS_OFFSET (if Physical Address < VIRT_TO_PHYS_OFFSET)
  //
  if ( 0 < *PhyAddress <= VIRT_TO_PHYS_OFFSET) {
    *PhyAddress += VIRT_TO_PHYS_OFFSET;
  } else if (*PhyAddress > VIRT_TO_PHYS_OFFSET) {
    *PhyAddress -= VIRT_TO_PHYS_OFFSET;
  }
}
