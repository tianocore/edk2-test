/** @file

  Copyright 2025, Arm Ltd.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SampleAppForSecureBootTest2.c

Abstract:

  for Secure Boot Black Box Test

--*/

#include "Efi.h"

//
// data definition here
//

EFI_STATUS
EFIAPI
InitializeEfiSampleAppForSecureBootTest2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  return EFI_SUCCESS;
}
