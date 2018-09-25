/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EntsMisc.c

Abstract:

  ENTS misc services implementations.

--*/
#include "SctLib.h"
#include <Library/EntsLib.h>

EFI_STATUS
GetImageDevicePath (
  IN EFI_HANDLE                   ImageHandle,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **FilePath
  )
/*++

Routine Description:

  Get device path and file path from the image handle.

Arguments:

  ImageHandle - The image handle.
  DevicePath  - The device path of the image handle.
  FilePath    - The file path of the image handle.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  EFI_NOT_FOUND        - File path not found.
  Others               - Some failure happened.

--*/
{
  EFI_STATUS                Status;
  EFI_LOADED_IMAGE_PROTOCOL *Image;
  EFI_DEVICE_PATH_PROTOCOL  *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *TempDeviceNode;
  CHAR16                    *TempFilePath;

  //
  // Get the image instance from the image handle
  //
  Status = gntBS->HandleProtocol (
                    ImageHandle,
                    &gEfiLoadedImageProtocolGuid,
                   (VOID **) &Image
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Get the device instance from the device handle
  //
  Status = gntBS->HandleProtocol (
                    Image->DeviceHandle,
                    &gEfiDevicePathProtocolGuid,
                   (VOID **) &TempDevicePath
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  *DevicePath = EntsDuplicateDevicePath (TempDevicePath);
  if (*DevicePath == NULL) {
    EntsFreePool (TempDevicePath);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // Get the file name from the image instance
  //
  TempDevicePath  = EntsUnpackDevicePath (Image->FilePath);

  TempFilePath    = NULL;
  TempDeviceNode  = TempDevicePath;
  while (!SctIsDevicePathEnd (TempDeviceNode)) {
    if ((SctDevicePathType (TempDeviceNode) == MEDIA_DEVICE_PATH) &&
        (SctDevicePathSubType (TempDeviceNode) == MEDIA_FILEPATH_DP)
        ) {
      TempFilePath = EntsStrDuplicate (((FILEPATH_DEVICE_PATH *) TempDeviceNode)->PathName);
      if (TempFilePath == NULL) {
        EntsFreePool (TempDevicePath);
        EntsFreePool (*DevicePath);
        return EFI_OUT_OF_RESOURCES;
      }
      break;
    }

    TempDeviceNode = SctNextDevicePathNode (TempDeviceNode);
  }

  EntsFreePool (TempDevicePath);

  if (TempFilePath == NULL) {
    EntsFreePool (*DevicePath);
    return EFI_NOT_FOUND;
  }
  //
  // If the file path is only a root directory "\\", remove it
  //
  if ((TempFilePath[0] == L'\\') && (TempFilePath[1] == L'\0')) {
    TempFilePath[0] = L'\0';
  }

  *FilePath = TempFilePath;

  //
  // Done
  //
  return EFI_SUCCESS;
}

VOID *
EntsAllocatePool (
  IN UINTN                Size
  )
/*++

Routine Description:

  Allocates pool memory.

Arguments:

  Size                 - Size in bytes of the pool being requested.

Returns:
  EFI_SUCEESS          - The requested number of bytes were allocated.
  EFI_OUT_OF_RESOURCES - The pool requested could not be allocated.

--*/
{
  EFI_STATUS  Status;
  VOID        *p;

  Status = gntBS->AllocatePool (EfiLoaderData, Size, (VOID **) &p);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "AllocatePool: out of pool  %x\n", Status));
    p = NULL;
  }

  return p;
}

VOID *
EntsAllocateZeroPool (
  IN UINTN                Size
  )
/*++

Routine Description:

  Allocates pool memory and initializes the memory to zeros.

Arguments:

  Size                 - Size in bytes of the pool being requested.

Returns:
  EFI_SUCEESS          - The requested number of bytes were allocated.
  EFI_OUT_OF_RESOURCES - The pool requested could not be allocated.

--*/
{
  VOID  *p;

  p = EntsAllocatePool (Size);
  if (p) {
    EntsZeroMem (p, Size);
  }

  return p;
}

VOID *
EntsReallocatePool (
  IN VOID                 *OldPool,
  IN UINTN                OldSize,
  IN UINTN                NewSize
  )
/*++

Routine Description:

  Adjusts the size of a previously allocated buffer.

Arguments:
  OldPool               - A pointer to the buffer whose size is being adjusted.
  OldSize               - The size of the current buffer.
  NewSize               - The size of the new buffer.

Returns:

  EFI_SUCEESS           - The requested number of bytes were allocated.
  EFI_OUT_OF_RESOURCES  - The pool requested could not be allocated.
  EFI_INVALID_PARAMETER - The buffer was invalid.

--*/
{
  VOID  *NewPool;

  NewPool = NULL;
  if (NewSize) {
    NewPool = EntsAllocatePool (NewSize);
  }

  if (OldPool) {
    if (NewPool) {
      EntsCopyMem (NewPool, OldPool, OldSize < NewSize ? OldSize : NewSize);
    }

    EntsFreePool (OldPool);
  }

  return NewPool;
}

VOID
EntsFreePool (
  IN VOID                 *Buffer
  )
/*++

Routine Description:

  Releases a previously allocated buffer.

Arguments:
  Buffer                - A pointer to the buffer to free.

Returns:
  EFI_SUCEESS           - The requested number of bytes were allocated.
  EFI_INVALID_PARAMETER - The buffer was invalid.

--*/
{
  gntBS->FreePool (Buffer);
}

VOID
EntsZeroMem (
  IN VOID     *Buffer,
  IN UINTN    Size
  )
/*++

Routine Description:

  Fills a buffer with zeros.

Arguments:

  Buffer                - A pointer to the buffer to fill with zeros.
  Size                  - Number of bytes to zero in the buffer.

Returns:

  None

--*/
{
  INT8  *pt;

  pt = Buffer;
  while (Size--) {
    *(pt++) = 0;
  }
}

VOID
EntsSetMem (
  IN VOID     *Buffer,
  IN UINTN    Size,
  IN UINT8    Value
  )
/*++

Routine Description:

  Fills a buffer with a value.

Arguments:

  Buffer                - A pointer to the buffer to free.
  Size                  - The number of bytes in the buffer to fill.
  Value                 - The value to fill Buffer with.

Returns:

  None

--*/
{
  INT8  *pt;

  pt = Buffer;
  while (Size--) {
    *(pt++) = Value;
  }
}

VOID
EntsCopyMem (
  IN VOID     *Dest,
  IN VOID     *Src,
  IN UINTN    len
  )
/*++

Routine Description:

  Copies the contents of one buffer to another.

Arguments:

  Dest                - A pointer to the buffer to copy to
  Src                 - A pointer to the buffer to copy from.
  len                 - The number of bytes to copy.

Returns:

  None

--*/
{
  CHAR8 *d;

  CHAR8 *s;

  d = Dest;
  s = Src;
  while (len--) {
    *(d++) = *(s++);
  }
}

INTN
EntsCompareMem (
  IN VOID     *Dest,
  IN VOID     *Src,
  IN UINTN    len
  )
/*++

Routine Description:

  Compares the contents of one buffer to another.

Arguments:

  Dest                - A pointer to the buffer to compare
  Src                 - A pointer to the buffer to compare
  len                 - The number of bytes to compare

Returns:

  0                   - Dest is identical to Src for len bytes.
  !=0                 - Dest is not identical to Src for len bytes.

--*/
{
  CHAR8 *d;

  CHAR8 *s;

  d = Dest;
  s = Src;
  while (len--) {
    if (*d != *s) {
      return *d -*s;
    }

    d += 1;
    s += 1;
  }

  return 0;
}

BOOLEAN
EntsGrowBuffer (
  IN OUT EFI_STATUS   *Status,
  IN OUT VOID         **Buffer,
  IN UINTN            BufferSize
  )
/*++

Routine Description:

    Helper function called as part of the code needed
    to allocate the proper sized buffer for various
    EFI interfaces.

Arguments:

    Status      - Current status

    Buffer      - Current allocated buffer, or NULL

    BufferSize  - Current buffer size needed

Returns:

    TRUE - if the buffer was reallocated and the caller
    should try the API again.

--*/
{
  BOOLEAN TryAgain;

  //
  // If this is an initial request, buffer will be null with a new buffer size
  //
  if (!*Buffer && BufferSize) {
    *Status = EFI_BUFFER_TOO_SMALL;
  }
  //
  // If the status code is "buffer too small", resize the buffer
  //
  TryAgain = FALSE;
  if (*Status == EFI_BUFFER_TOO_SMALL) {

    if (*Buffer) {
      EntsFreePool (*Buffer);
    }

    *Buffer = EntsAllocatePool (BufferSize);

    if (*Buffer) {
      TryAgain = TRUE;
    } else {
      *Status = EFI_OUT_OF_RESOURCES;
    }
  }
  //
  // If there's an error, free the buffer
  //
  if (!TryAgain && EFI_ERROR (*Status) && *Buffer) {
    EntsFreePool (*Buffer);
    *Buffer = NULL;
  }

  return TryAgain;
}
