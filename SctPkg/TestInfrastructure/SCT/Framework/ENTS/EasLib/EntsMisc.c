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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
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

  Status = gntBS->AllocatePool (EfiLoaderData, Size, &p);
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
