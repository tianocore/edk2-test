/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AbsolutePointerBBTestConformance.c

Abstract:

  Conformance Test Cases of Absolute Pointer Protocol

--*/


#include "SctLib.h"
#include "AbsolutePointerBBTestMain.h"


/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
EFIAPI
BBTestGetStateConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  //
  // Return status when call GetState with State being NULL is not described in Spec
  // According to Spec 1-12, this situation will not be tested
  // though, some implementation will bring out different result
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
EFIAPI
BBTestGetStateConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  //
  // Return status when call GetState with State being NULL is not described in Spec
  // According to Spec 1-12, this situation will not be tested
  // though, some implementation will bring out different result
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.WaitForInput() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
EFIAPI
BBTestWaitForInputConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  return EFI_SUCCESS;
}


