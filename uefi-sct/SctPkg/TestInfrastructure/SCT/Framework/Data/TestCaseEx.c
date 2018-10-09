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

  TestCaseEx.c

Abstract:

  This file provides the extended services to manage the test cases with the
  test execution.

--*/

#include "Sct.h"

//
// Internal functions declaration
//

EFI_STATUS
BuildTestCaseOrderFromNode (
  IN SCT_LIST_ENTRY               *TestNodeList,
  IN OUT UINT32                   *Order
  );


//
// External functions implementation
//

EFI_STATUS
SelectTestCase (
  IN EFI_GUID                     *Guid,
  IN UINT32                       Iterations
  )
/*++

Routine Description:

  Select a test case.

  This function will be implemented in two steps:
  Step 1: Search the test case list to get the largest assigned order.
  Step 2: Find the test case we want to select, and modify its order as the
          largest order + 1.

Arguments:

  Guid          - GUID of the test case.
  Iterations    - Number of interations.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  UINT32              Order;
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;
  EFI_SCT_TEST_CASE   *Target;

  //
  // Check parameters
  //
  if ((Guid == NULL) || (Iterations == EFI_SCT_TEST_CASE_INVALID)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  Order  = EFI_SCT_TEST_CASE_INVALID;
  Target = NULL;

  //
  // Walk through all test cases, find the largest order
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      Target = TestCase;
    }

    if (TestCase->Order != EFI_SCT_TEST_CASE_INVALID) {
      if ((Order == EFI_SCT_TEST_CASE_INVALID) ||
          (Order <  TestCase->Order          )) {
        Order = TestCase->Order;
      }
    }
  }

  //
  // Find it?
  //
  if (Target == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Select it
  //
  if (Target->Order == EFI_SCT_TEST_CASE_INVALID) {
    if (Order == EFI_SCT_TEST_CASE_INVALID) {
      Target->Order = 0;
    } else {
      Target->Order = Order + 1;
    }
  }

  Target->Iterations = Iterations;
  Target->Passes     = EFI_SCT_TEST_CASE_INVALID;
  Target->Warnings   = EFI_SCT_TEST_CASE_INVALID;
  Target->Failures   = EFI_SCT_TEST_CASE_INVALID;

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
UnselectTestCase (
  IN EFI_GUID                     *Guid
  )
/*++

Routine Description:

  Unselect a test case.

  This function will be implemented in two steps:
  Step 1: Find the test case we want to unselect.
  Step 2: Search the test case list to decrease the order larger than the
          unselected.

Arguments:

  Guid          - GUID of the test case.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  UINT32              Order;
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;
  EFI_SCT_TEST_CASE   *Target;

  //
  // Check parameters
  //
  if (Guid == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  Order  = EFI_SCT_TEST_CASE_INVALID;
  Target = NULL;

  //
  // Walk through all test cases, find the target test case
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      if (TestCase->Order == EFI_SCT_TEST_CASE_INVALID) {
        //
        // Has been unselected before
        //
        return EFI_SUCCESS;
      }

      Target = TestCase;
      break;
    }
  }

  //
  // Find it?
  //
  if (Target == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Walk through all test cases again, decrease the order
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (TestCase->Order != EFI_SCT_TEST_CASE_INVALID) {
      if (TestCase->Order > Target->Order) {
        TestCase->Order --;
      }
    }
  }

  //
  // Unselect it
  //
  Target->Order      = EFI_SCT_TEST_CASE_INVALID;
  Target->Iterations = EFI_SCT_TEST_CASE_INVALID;

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetTestCaseState (
  IN EFI_GUID                     *Guid,
  OUT EFI_SCT_TEST_STATE          *TestState
  )
/*++

Routine Description:

  Get the state of a test case.

Arguments:

  Guid          - GUID of the test case.
  TestState     - State of the test case.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS          Status;
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if ((Guid == NULL) || (TestState == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the running test case
  //
  Status = GetRunningTestCase (&TestCase);
  if (!EFI_ERROR (Status)) {
    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      *TestState = EFI_SCT_TEST_STATE_RUNNING;
      return EFI_SUCCESS;
    }
  }

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      if (TestCase->Order == EFI_SCT_TEST_CASE_INVALID) {
        *TestState = EFI_SCT_TEST_STATE_NOT_IN_LIST;
        return EFI_SUCCESS;
      }

      if ((TestCase->Passes   == EFI_SCT_TEST_CASE_INVALID) ||
          (TestCase->Warnings == EFI_SCT_TEST_CASE_INVALID) ||
          (TestCase->Failures == EFI_SCT_TEST_CASE_INVALID)) {
        *TestState = EFI_SCT_TEST_STATE_READY;
        return EFI_SUCCESS;
      } else {
        *TestState = EFI_SCT_TEST_STATE_FINISHED;
        return EFI_SUCCESS;
      }
    }
  }

  //
  // Not found
  //
  return EFI_NOT_FOUND;
}


UINT32
GetTestCaseOrder (
  IN EFI_GUID                     *Guid
  )
/*++

Routine Description:

  Get the order of a test case.

Arguments:

  Guid        - GUID of the test case.

Returns:

  UINT32      - The order of the test case. (0 means it is not found or
                not selected. Invoking GetTestCaseState() to check the
                state of the test case is required.)

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if (Guid == NULL) {
    return 0;
  }

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      if (TestCase->Order != EFI_SCT_TEST_CASE_INVALID) {
        return (UINT32) (TestCase->Order + 1);
      } else {
        return 0;
      }
    }
  }

  //
  // Not found
  //
  return 0;
}


UINT32
GetTestCaseIterations (
  IN EFI_GUID                     *Guid
  )
/*++

Routine Description:

  Get the iterations of a test case.

Arguments:

  Guid        - GUID of the test case.

Returns:

  UINT32      - The iterations of the test case.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if (Guid == NULL) {
    return 0;
  }

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      if (TestCase->Iterations != EFI_SCT_TEST_CASE_INVALID) {
        return TestCase->Iterations;
      } else {
        return 0;
      }
    }
  }

  //
  // Not found
  //
  return 0;
}


UINT32
GetTestCasePasses (
  IN EFI_GUID                     *Guid
  )
/*++

Routine Description:

  Get the number of passed assertions of a test case.

Arguments:

  Guid        - GUID of the test case.

Returns:

  UINT32      - The number of passed assertions.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if (Guid == NULL) {
    return 0;
  }

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      if ((TestCase->Passes != EFI_SCT_TEST_CASE_INVALID) &&
          (TestCase->Passes != EFI_SCT_TEST_CASE_RUNNING)) {
        return TestCase->Passes;
      } else {
        return 0;
      }
    }
  }

  //
  // Not found
  //
  return 0;
}

UINT32
GetTestCaseWarnings (
  IN EFI_GUID                     *Guid
  )
/*++

Routine Description:

  Get the number of warning assertions of a test case.

Arguments:

  Guid        - GUID of the test case.

Returns:

  UINT32      - The number of warning assertions.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if (Guid == NULL) {
    return 0;
  }

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      if ((TestCase->Warnings != EFI_SCT_TEST_CASE_INVALID) &&
          (TestCase->Warnings != EFI_SCT_TEST_CASE_RUNNING)) {
        return TestCase->Warnings;
      } else {
        return 0;
      }
    }
  }

  //
  // Not found
  //
  return 0;
}


UINT32
GetTestCaseFailures (
  IN EFI_GUID                     *Guid
  )
/*++

Routine Description:

  Get the number of failed assertions of a test case.

Arguments:

  Guid        - GUID of the test case.

Returns:

  UINT32      - The number of failed assertions.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if (Guid == NULL) {
    return 0;
  }

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TestCase->Guid, Guid) == 0) {
      if ((TestCase->Failures != EFI_SCT_TEST_CASE_INVALID) &&
          (TestCase->Failures != EFI_SCT_TEST_CASE_RUNNING)) {
        return TestCase->Failures;
      } else {
        return 0;
      }
    }
  }

  //
  // Not found
  //
  return 0;
}


EFI_STATUS
GetRunningTestCase (
  OUT EFI_SCT_TEST_CASE           **TestCase
  )
/*++

Routine Description:

  Get the running test case.

Arguments:

  TestCase      - Pointer to the running test case.

Returns:

  EFI_SUCCESS   - Successfully.
  EFI_NOT_FOUND - Not found.
  Other value   - Something failed.

--*/
{
  UINT32              Order;
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TempTestCase;
  EFI_SCT_TEST_CASE   *Target;

  //
  // Check parameters
  //
  if (TestCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  Order  = EFI_SCT_TEST_CASE_INVALID;
  Target = NULL;

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TempTestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (TempTestCase->Order != EFI_SCT_TEST_CASE_INVALID) {
      if ((Order == EFI_SCT_TEST_CASE_INVALID) ||
          (Order >  TempTestCase->Order      )) {
        if ((TempTestCase->Passes   == EFI_SCT_TEST_CASE_RUNNING) ||
            (TempTestCase->Warnings == EFI_SCT_TEST_CASE_RUNNING) ||
            (TempTestCase->Failures == EFI_SCT_TEST_CASE_RUNNING)) {
          Order  = TempTestCase->Order;
          Target = TempTestCase;
        }
      }
    }
  }

  //
  // Find it?
  //
  if (Target == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Done
  //
  *TestCase = Target;
  return EFI_SUCCESS;
}


EFI_STATUS
GetNextTestCase (
  OUT EFI_SCT_TEST_CASE           **TestCase
  )
/*++

Routine Description:

  Get the next test case.

Arguments:

  TestCase      - Pointer to the next test case.

Returns:

  EFI_SUCCESS   - Successfully.
  EFI_NOT_FOUND - Not found.
  Other value   - Something failed.

--*/
{
  UINT32              Order;
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TempTestCase;
  EFI_SCT_TEST_CASE   *Target;

  //
  // Check parameters
  //
  if (TestCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  Order  = EFI_SCT_TEST_CASE_INVALID;
  Target = NULL;

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TempTestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (TempTestCase->Order != EFI_SCT_TEST_CASE_INVALID) {
      if ((Order == EFI_SCT_TEST_CASE_INVALID) ||
          (Order >  TempTestCase->Order      )) {
        if ((TempTestCase->Passes   == EFI_SCT_TEST_CASE_INVALID) ||
            (TempTestCase->Warnings == EFI_SCT_TEST_CASE_INVALID) ||
            (TempTestCase->Failures == EFI_SCT_TEST_CASE_INVALID)) {
          Order  = TempTestCase->Order;
          Target = TempTestCase;
        }
      }
    }
  }

  //
  // Find it?
  //
  if (Target == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Done
  //
  *TestCase = Target;
  return EFI_SUCCESS;
}

EFI_STATUS
GetTestCaseRemainNum (
  UINTN                             *Remain
  )
{
  SCT_LIST_ENTRY                    *Link;
  EFI_SCT_TEST_CASE                 *TestCase;

  if (Remain == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *Remain = 0;

  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if ((TestCase->Order != EFI_SCT_TEST_CASE_INVALID) &&
        (TestCase->Passes   == EFI_SCT_TEST_CASE_INVALID) &&
        (TestCase->Warnings == EFI_SCT_TEST_CASE_INVALID) &&
        (TestCase->Failures == EFI_SCT_TEST_CASE_INVALID)) {
      (*Remain)++;
    }
  }

  return EFI_SUCCESS;
}

BOOLEAN
IsTestFinished (
  VOID
  )
/*++

Routine Description:

  Check whether the test is finished or not.

Returns:

  TRUE    - Finished.
  FALSE   - Not finished.

--*/
{
  EFI_STATUS          Status;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Find the running test case
  //
  Status = GetRunningTestCase (&TestCase);
  if (EFI_ERROR (Status)) {
    return TRUE;
  }

  return FALSE;
}


EFI_STATUS
ResetTestCaseOrder (
  VOID
  )
/*++

Routine Description:

  Reset the order of all test case.

Returns:

  EFI_SUCCESS   - Successfuly.
  Other value   - Something faied.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    TestCase->Order      = EFI_SCT_TEST_CASE_INVALID;
    TestCase->Iterations = EFI_SCT_TEST_CASE_INVALID;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ResetTestCaseResults (
  VOID
  )
/*++

Routine Description:

  Reset (remove) the test results of the selected test cases.

Returns:

  EFI_SUCCESS   - Successfuly.
  Other value   - Something faied.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (TestCase->Order != EFI_SCT_TEST_CASE_INVALID) {
      TestCase->Passes   = EFI_SCT_TEST_CASE_INVALID;
      TestCase->Warnings = EFI_SCT_TEST_CASE_INVALID;
      TestCase->Failures = EFI_SCT_TEST_CASE_INVALID;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ResetTestCaseOrderAndResults (
  VOID
  )
/*++

Routine Description:

  Reset (remove) the order and test results of all test cases.

Returns:

  EFI_SUCCESS   - Successfuly.
  Other value   - Something faied.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    TestCase->Order      = EFI_SCT_TEST_CASE_INVALID;
    TestCase->Iterations = EFI_SCT_TEST_CASE_INVALID;
    TestCase->Passes     = EFI_SCT_TEST_CASE_INVALID;
    TestCase->Warnings   = EFI_SCT_TEST_CASE_INVALID;
    TestCase->Failures   = EFI_SCT_TEST_CASE_INVALID;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BuildTestCaseOrder (
  VOID
  )
/*++

Routine Description:

  Build the order of test cases from the test node list.

Arguments:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  UINT32  Order;

  Order = 0;
  return BuildTestCaseOrderFromNode (
           &gFT->TestNodeList,
           &Order
           );
}


//
// Internal functions implementation
//

EFI_STATUS
BuildTestCaseOrderFromNode (
  IN SCT_LIST_ENTRY               *TestNodeList,
  IN OUT UINT32                   *Order
  )
/*++

Routine Description:

  Build the order of test cases from the test node list.

--*/
{
  EFI_STATUS          Status;
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_NODE   *TestNode;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if ((TestNodeList == NULL) || (Order == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test nodes
  //
  for (Link = TestNodeList->ForwardLink; Link != TestNodeList; Link = Link->ForwardLink) {
    TestNode = CR (Link, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);

    //
    // Check it is a leaf node or not
    //
    if (SctIsListEmpty (&TestNode->Child)) {
      //
      // Leaf node
      //
      Status = FindTestCaseByGuid (&TestNode->Guid, &TestCase);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Find test case by GUID - %r", Status));
        continue;
      }

      TestCase->Order      = *Order;
      TestCase->Iterations = 1;
      (*Order) ++;
    } else {
      //
      // Trunk node, recursive
      //
      Status = BuildTestCaseOrderFromNode (
                 &TestNode->Child,
                 Order
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Build test case order - %r", Status));
        continue;
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
