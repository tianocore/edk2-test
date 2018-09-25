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

  EntsHandle.c

Abstract:

  Handle operation functions

--*/
#include "Efi.h"
#include <Library/EntsLib.h>

EFI_STATUS
EntsLibLocateProtocol (
  IN  EFI_GUID    *ProtocolGuid,
  OUT VOID        **Interface
  )
/*++

Routine Description:

  Find the first instance of this Protocol in the system and return it's interface

Arguments:

  ProtocolGuid    - Provides the protocol to search for
  Interface       - On return, a pointer to the first interface that matches ProtocolGuid

Returns:

  EFI_SUCCESS     - A protocol instance matching ProtocolGuid was found

  EFI_NOT_FOUND   - No protocol instances were found that match ProtocolGuid

--*/
{
  EFI_STATUS  Status;
  UINTN       NumberHandles;
  UINTN       Index;
  EFI_HANDLE  *Handles;

  *Interface  = NULL;
  Status      = EntsLocateHandle (ByProtocol, ProtocolGuid, NULL, &NumberHandles, &Handles);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "EntsLibLocateProtocol: Handle not found\n"));
    return Status;
  }

  for (Index = 0; Index < NumberHandles; Index++) {
    Status = gntBS->HandleProtocol (
                      Handles[Index],
                      ProtocolGuid,
                      (VOID **) Interface
                      );

    if (!EFI_ERROR (Status)) {
      break;
    }
  }

  if (Handles) {
    EntsFreePool (Handles);
  }

  return Status;
}

EFI_STATUS
EntsLocateHandle (
  IN EFI_LOCATE_SEARCH_TYPE       SearchType,
  IN EFI_GUID                     * Protocol OPTIONAL,
  IN VOID                         *SearchKey OPTIONAL,
  IN OUT UINTN                    *NoHandles,
  OUT EFI_HANDLE                  **Buffer
  )
/*++

Routine Description:

  Function returns an array of handles that support the requested protocol
  in a buffer allocated from pool.

Arguments:

  SearchType           - Specifies which handle(s) are to be returned.
  Protocol             - Provides the protocol to search by.
                         This parameter is only valid for SearchType ByProtocol.
  SearchKey            - Supplies the search key depending on the SearchType.
  NoHandles            - The number of handles returned in Buffer.
  Buffer               - A pointer to the buffer to return the requested array of
                         handles that support Protocol.

Returns:

  EFI_SUCCESS           - The result array of handles was returned.
  EFI_NOT_FOUND         - No handles match the search.
  EFI_OUT_OF_RESOURCES - There is not enough pool memory to store the matching results.

--*/
{
  EFI_STATUS  Status;
  UINTN       BufferSize;

  //
  // Initialize for GrowBuffer loop
  //
  Status      = EFI_SUCCESS;
  *Buffer     = NULL;
  BufferSize  = 50 * sizeof (EFI_HANDLE);

  //
  // Call the real function
  //
  while (EntsGrowBuffer (&Status, (VOID **) Buffer, BufferSize)) {
    Status = gntBS->LocateHandle (
                      SearchType,
                      Protocol,
                      SearchKey,
                      &BufferSize,
                      *Buffer
                      );
  }

  *NoHandles = BufferSize / sizeof (EFI_HANDLE);
  if (EFI_ERROR (Status)) {
    *NoHandles = 0;
  }

  return Status;
}
