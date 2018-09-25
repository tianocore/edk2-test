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

  Application4.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "Misc.h"
#include <Library/EfiTestLib.h>

//
// data definition here
//

EFI_STATUS
EFIAPI
InitializeEfiApplication4 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );


EFI_STATUS
EFIAPI
InitializeEfiApplication4 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NoHandles;
  CHAR16                  *ExitData;
  CHAR16                  *ErrorMessage;
  UINTN                   ExitSize;

  HandleBuffer = NULL;
  ExitData = NULL;
  ExitSize = 0;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  gtBS->InstallProtocolInterface (
          &ImageHandle,
          &mImageTestNoInterfaceProtocol3Guid,
          EFI_NATIVE_INTERFACE,
          NULL
          );

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestNoInterfaceProtocol4Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    goto Done;
  }

  gtBS->OpenProtocol (
          HandleBuffer[0],
          &mImageTestNoInterfaceProtocol4Guid,
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
          &mImageTestNoInterfaceProtocol3Guid,
          NULL
          );

  ErrorMessage = ERROR_MESSAGE_FOR_APPLICATION_4;

  ExitSize = SctStrSize (ErrorMessage);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ExitSize,
                   (VOID**)&ExitData
                   );
  if (!EFI_ERROR(Status)) {
    gtBS->CopyMem (ExitData, ErrorMessage, ExitSize);
  }

  gtBS->Exit (ImageHandle, EFI_DEVICE_ERROR, ExitSize, ExitData);

  //
  //the code should not arrive here so we add a variable to verify if the Exit
  //return control to StartImage correctly.
  //

  //
  //first make sure there is no duplicated variable exist so we first delete once.
  //
  gtRT->SetVariable (
          IMAGE_APPLICATION4_CALLED_AFTER_EXIT,
          &mImageTestVariableVendorGuid,
          EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
          0,
          (VOID*)&ImageHandle
          );

  //
  //then call SetVariable to set a variable.
  //

  gtRT->SetVariable (
          IMAGE_APPLICATION4_CALLED_AFTER_EXIT,
          &mImageTestVariableVendorGuid,
          EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
          sizeof(EFI_HANDLE),
          (VOID*)&ImageHandle
          );

  //
  // actually should not arrive here. Just to pass compiling.
  //
  return EFI_SUCCESS;
}

