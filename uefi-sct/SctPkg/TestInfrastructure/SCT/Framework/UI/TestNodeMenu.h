/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  TestNodeMenu.h

Abstract:

  Deal with the user interface menu for test nodes.

--*/

#ifndef _EFI_TEST_NODE_MENU_H_
#define _EFI_TEST_NODE_MENU_H_

//
//  Includes
//

//
// Definitions
//

#define ITERATION_NUMBER_MAX     999
#define ITERATION_NUMBER_MIN     0
#define ITERATION_NUMBER_DEFAULT 0

//
// Functions
//

EFI_STATUS
DisplayTestNodeMenu (
  IN SCT_LIST_ENTRY               *Root,
  IN EFI_MENU_PAGE                *ParentPage
  );

UINTN
CalculatePassNumber (
  EFI_SCT_TEST_NODE               *TestNode
  );

UINTN
CalculateTotalPassNumber (
  SCT_LIST_ENTRY                  *Root
  );

UINTN
CalculateWarningNumber (
  EFI_SCT_TEST_NODE               *TestNode
  );

UINTN
CalculateTotalWarningNumber (
  SCT_LIST_ENTRY                  *Root
  );

UINTN
CalculateFailNumber (
  EFI_SCT_TEST_NODE               *TestNode
  );

UINTN
CalculateTotalFailNumber (
  SCT_LIST_ENTRY                  *Root
  );

UINT32
GetTestCaseIterations (
  IN EFI_GUID                     *Guid
  );

#endif
