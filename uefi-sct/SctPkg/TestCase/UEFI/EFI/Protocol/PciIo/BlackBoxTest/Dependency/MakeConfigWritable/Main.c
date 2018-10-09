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

  Main.c

Abstract:

  main source file for make pci configuraiton space writable

--*/
#include "Common.h"
#include "Main.h"


EFI_STATUS
EFIAPI
MakeConfigWritableEntryPoint (
  IN EFI_HANDLE                      ImageHandle,
  IN EFI_SYSTEM_TABLE                *SystemTable
  )
{
  EFI_STATUS     Status;
  PCIDev         *TestDev;

  //
  //Initialize Libraries
  //
  SctShellApplicationInit (ImageHandle, SystemTable);

  Status = FindTestCard (&TestDev);
  if (EFI_ERROR(Status)) {
    SctPrint (L"Not found the Test Card, please insert the Pci Test Card and run this program again.\r\n");
    return Status;
  }

  Status = MakeConfigWritable (TestDev);
  if (EFI_ERROR(Status)) {
    SctPrint (L"Failed make the configuration space writable.\r\n");
  } else {
    SctPrint (L"Successfully make the configuration space writable.\r\n");
  }

  SctFreePool (TestDev);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}
