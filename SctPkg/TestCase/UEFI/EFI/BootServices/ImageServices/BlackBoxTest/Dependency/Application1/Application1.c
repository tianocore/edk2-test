/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Application1.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include <Library/EfiTestLib.h>

//
// data definition here
//

EFI_STATUS
EFIAPI
InitializeEfiApplication1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );


EFI_STATUS
EFIAPI
InitializeEfiApplication1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NoHandles;

  HandleBuffer = NULL;
  NoHandles    = 0;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  Status = gtBS->InstallProtocolInterface (
                   &ImageHandle,
                   &mImageTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestNoInterfaceProtocol2Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    goto Done;
  }

  Status = gtBS->OpenProtocol (
                   HandleBuffer[0],
                   &mImageTestNoInterfaceProtocol2Guid,
                   (VOID **) NULL,
                   ImageHandle,
                   NULL,
                   EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                   );


Done:

  if (HandleBuffer != NULL && NoHandles > 0) {
    gtBS->FreePool (HandleBuffer);
  }

  gtBS->UninstallProtocolInterface (
          ImageHandle,
          &mImageTestNoInterfaceProtocol1Guid,
          NULL
          );
  return EFI_SUCCESS;
}

