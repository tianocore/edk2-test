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

  EfiCompliantBbTestDriver.c

Abstract:

  Check the driver specific elements in EFI Spec.

--*/

//
// Includes
//

#include "SctLib.h"
#include "EfiCompliantBbTestMain_efi.h"

//
// Module definitions
//

#define SECTION_NAME_DRIVER_SPECIFIC        L"Driver Specific"

//
// External functions implementation
//

EFI_STATUS
DriverSpecificElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  )
/*++

Routine Description:

  Check the driver specific elements, which defined in the EFI spec 1.10,
  section 2.6.3.

  We didn't find a good way to test this item. So currently it is commented in
  the test entry point definitions of TestMain.c.

--*/
{
  return EFI_UNSUPPORTED;
}
