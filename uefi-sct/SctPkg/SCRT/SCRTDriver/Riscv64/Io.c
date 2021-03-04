/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2011 - 2012 ARM Ltd. All rights reserved.<BR>   
  (C) Copyright 2021 Hewlett Packard Enterprise Development LP<BR>

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

#include "SCRTDriver.h"

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
  return EFI_UNSUPPORTED;
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
  return EFI_UNSUPPORTED;
}


VOID
FixAddress (
  IN UINTN     *PhyAddress
  )
{
		//
		//Note: On RISC-V platforms don't have to do this as all the functions are virtually mapped.
		//
}

// Quick port to RISC-V. It doesn't have traditional I/O-Port 80h POST Codes

VOID
Port80 (
  UINT8 Number
  )
{
  //EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Port80 %02x", Number));
}
