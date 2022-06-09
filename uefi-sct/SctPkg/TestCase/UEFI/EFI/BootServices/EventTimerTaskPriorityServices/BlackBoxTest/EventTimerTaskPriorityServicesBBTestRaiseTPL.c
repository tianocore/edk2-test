/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EventTimerTaskPriorityServicesBBTestRaiseTPL.c

Abstract:

  Test Driver of RaiseTPL() of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Declarations
//

EFI_STATUS
EFIAPI
BBTestRaiseTPL_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
EFIAPI
BBTestRaiseTPL_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;

  //
  // Locate standard test library
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // RaiseTPL() returns EFI_SUCCESS with valid parameters.
  //
  BBTestRaiseTPL_Func_Sub1 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Sub functions
//

EFI_STATUS
EFIAPI
BBTestRaiseTPL_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  UINTN               Index;
  EFI_TPL             OldTpl;
  EFI_TPL             Tpl1;
  EFI_TPL             Tpl2;
  EFI_TPL             CheckTpls[] = {
                        TPL_APPLICATION,
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        TPL_HIGH_LEVEL,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Walk through all valid TPLs
  //
  for (Index = 0; CheckTpls[Index] != 0; Index++) {
    //
    // Check the current TPL
    //
    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    if (OldTpl > CheckTpls[Index]) {
      continue;
    }

    //
    // Raise to check TPL and then to highest TPL
    //
    Tpl1 = gtBS->RaiseTPL (CheckTpls[Index]);
    Tpl2 = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    if ((Tpl1 == OldTpl) && (Tpl2 == CheckTpls[Index])) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEventTimerTaskPriorityServicesBBTestRaiseTPLAssertionGuid001,
                   L"BS.RaiseTPL - Raise TPL with valid parameters.",
                   L"%a:%d:OldTpl - %d, ToTpl - %d, Tpl1 - %d, Tpl2 - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   OldTpl,
                   CheckTpls[Index],
                   Tpl1,
                   Tpl2
                   );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
