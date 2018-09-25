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

  CombinationImage10.c

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
InitializeCombinationImage10 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );


EFI_STATUS
EFIAPI
InitializeCombinationImage10 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_HANDLE                  Handle;

  //
  // Init
  //
  Handle = NULL;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  gtBS->InstallProtocolInterface (
          &Handle,
          &mImageTestNoInterfaceProtocol10Guid,
          EFI_NATIVE_INTERFACE,
          NULL
          );

  gtBS->UninstallProtocolInterface (
          Handle,
          &mImageTestNoInterfaceProtocol10Guid,
          NULL
          );

  gtBS->Exit (ImageHandle, EFI_SUCCESS, 0, NULL);

  //
  // actually should not arrive here. Just to pass compiling.
  //
  return EFI_SUCCESS;
}
