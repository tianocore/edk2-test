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

  TestNodeMenu.c

Abstract:

  Deal with the test case management menu in the user interface

--*/

#include "Sct.h"
#include "UI.h"
#include "BuildMenu.h"
#include "Dialog.h"
#include "TestNodeMenu.h"

#define EFI_MENU_ITEM_UTILITY             3

//
// Variable Definitions
//

//
// A variable from MainMenu.c indicating continue running flag
//
extern BOOLEAN          gContinueExec;

//
// Prototype (external)
//

EFI_STATUS
DisplayTestNodeMenu (
  IN SCT_LIST_ENTRY               *Root,
  IN EFI_MENU_PAGE                *ParentPage
  );

//
// Prototypes (internal)
//
EFI_STATUS
EFIAPI
TestNodeMenuEnterFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
TestNodeMenuEscFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
TestNodeMenuSpaceFunc(
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
TestNodeMenuF9Func(
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
TestNodeMenuF8Func(
  IN EFI_MENU_PAGE                *Page
  );

EFI_ITEM_SELECT_STATUS
GetItemSelectStatus(
  EFI_SCT_TEST_NODE               *TestNode
  );

VOID
SelectTestNode (
  IN EFI_SCT_TEST_NODE            *TestNode,
  IN UINT32                       Iterations
  );

VOID
SelectSomeTestNode (
  EFI_SCT_TEST_NODE               *TestNode,
  UINT32                          Iterations
  );

VOID
UnSelectTestNode (
  EFI_SCT_TEST_NODE               *TestNode
  );

EFI_STATUS
EFIAPI
TestNodeMenuDescPrintFunc (
  IN EFI_MENU_ITEM                *MenuItem,
  IN VOID                         *Context,
  IN UINTN                        Row,
  IN UINTN                        Column
  );

EFI_STATUS
GetIterString(
  EFI_SCT_TEST_NODE               *TestNode,
  CHAR16                          *IterString
  );

//
// Functions
//

EFI_STATUS
DisplayTestNodeMenu (
  IN SCT_LIST_ENTRY               *Root,
  IN EFI_MENU_PAGE                *ParentPage
  )
/*++

Routine Description:

  Display the case menu

Arguments:

  ParentPage    - A pointer to the parent page of this menu

Returns:

  EFI_SUCCESS   - Display the menu successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS                Status;
  EFI_MENU_PAGE             *Page;
  EFI_MENU_ITEM             *MenuItem;
  EFI_SCT_TEST_NODE         *TestNode;
  SCT_LIST_ENTRY            *TempLink;
  CHAR16                    *EditBuffer;

  //
  // Create a standard menu page
  //
  Status = CreateStandardMenuPage (
             ParentPage->Body.CurrentSelected->ItemString.Text,
             &Page
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Page->Parent = ParentPage;

  //
  // Add Test Title
  //
  Status = AddSimpleMenuItem (
             EFI_ITEM_STRING,
             L"                                      #Iter  Result",
             L"",
             0,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  for (TempLink = Root->ForwardLink; TempLink != Root; TempLink = TempLink->ForwardLink) {
    TestNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);

    //
    // Case Menu Items
    //  - All test cases tested in the test file list
    //
    EditBuffer = NULL;
    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   (EFI_MAX_EDIT_LENGTH + 1) * sizeof(CHAR16),
                   (VOID **)&EditBuffer
                   );
    if (EFI_ERROR (Status)) {
      DestroyMenuPage (Page);
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // set iteration value
    //
    Status = GetIterString (TestNode, EditBuffer);
    if (EFI_ERROR (Status)) {
      DestroyMenuPage (Page);
      tBS->FreePool (EditBuffer);
      return Status;
    }

    Status = AddCaseMenuItem (
               EFI_ITEM_CASE | EFI_ITEM_EDIT_NUMBER,
               TestNode->Name,
               TestNode->Description,
               EditBuffer,
               (VOID *)TestNode,
               Page
               );
    if (EFI_ERROR (Status)) {
      DestroyMenuPage (Page);
      tBS->FreePool (EditBuffer);
      return Status;
    }

    Status = AddMenuItemCheckValue(
               TestNode->Name,
               ITERATION_NUMBER_MAX,
               ITERATION_NUMBER_MIN,
               ITERATION_NUMBER_DEFAULT,
               Page
               );
  }

  MenuItem = Page->Body.ItemList;

  //
  // Skip the first one
  //
  MenuItem = MenuItem->Next;

  //
  //verify parent menu item status.
  //
  //
  //set MenuItem DescPrint function.
  //
  while (MenuItem != NULL) {
    MenuItem->DescPrint = TestNodeMenuDescPrintFunc;
    TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;
    MenuItem->Status = GetItemSelectStatus(TestNode);
    MenuItem = MenuItem -> Next;
  }

  //
  //if parent page current selected item is CHECKBOX and the status is
  //SELECT_ALL
  //set all the sub menu item status as EFI_ITEM_SELECT_ALL.
  //

  //
  //add Scroll Bar.
  //
  Status = AddScrollBar (Page);
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  //
  // Case Menu Hot Keys
  //  - Up, Down, Pgup, PgDn, Space, F9, Esc
  //
  Status = AddHotKey (
             L"Up/Dn",
             L"Select Item",
             SCAN_UP,
             CHAR_NULL,
             UpFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"Down",
             L"Select Item",
             SCAN_DOWN,
             CHAR_NULL,
             DownFunc,
             FALSE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"PgUp",
             L"Up One Page",
             SCAN_PAGE_UP,
             CHAR_NULL,
             PageUpFunc,
             FALSE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"PgDn",
             L"Down One Page",
             SCAN_PAGE_DOWN,
             CHAR_NULL,
             PageDownFunc,
             FALSE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"Space",
             L"Change Status",
             SCAN_NULL,
             L' ',
             TestNodeMenuSpaceFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"Enter",
             L"Select SubMenu",
             SCAN_NULL,
             CHAR_CARRIAGE_RETURN,
             TestNodeMenuEnterFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"ESC",
             L"Exit",
             SCAN_ESC,
             CHAR_NULL,
             TestNodeMenuEscFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F9",
             L"Run",
             SCAN_F9,
             CHAR_NULL,
             TestNodeMenuF9Func,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  if (gContinueExec) {
    Status = AddHotKey (
               L"F8",
               L"Continue Run",
               SCAN_F8,
               CHAR_NULL,
               TestNodeMenuF8Func,
               TRUE,
               Page
               );
    if (EFI_ERROR (Status)) {
      DestroyMenuPage (Page);
      return Status;
    }
  }

  //
  // Display the case menu
  //
  MenuPageRefresh (Page);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestNodeMenuEnterFunc (
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle Enter key in case management menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle Enter key successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS Status;
  EFI_SCT_TEST_NODE *TestNode;

  Status = EFI_SUCCESS;

  //
  // Based on current selected item, display different menu page
  //
  if ((EFI_SCT_TEST_NODE*)Page->Body.CurrentSelected == NULL) {
    return EFI_NOT_FOUND;
  }

  TestNode = (EFI_SCT_TEST_NODE*)Page->Body.CurrentSelected->Context;

  //
  // for string item
  //
  if (TestNode == NULL) {
    return EFI_SUCCESS;
  }

  if (SctIsListEmpty (&(TestNode->Child))) {
    // No sub-node

    //
    //refresh the menu item.
    //
    Status = MenuItemRefresh (
               Page,
               Page->Body.CurrentSelected,
               FALSE
               );
    return EFI_UNSUPPORTED;
  } else {
    DisplayTestNodeMenu (&(TestNode->Child),Page);
  }

  return Status;
}

EFI_STATUS
EFIAPI
TestNodeMenuEscFunc (
  IN EFI_MENU_PAGE           *Page
  )
/*++

Routine Description:

  Handle ESC key in case menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle ESC key successfully
  Other Value   - Something failed

--*/
{
  EFI_MENU_ITEM          *MenuItem;
  EFI_MENU_ITEM          *ParentMenuItem;
  BOOLEAN                 SelectAll;
  BOOLEAN                 SelectNone;
  BOOLEAN                 IterEqual;
  CHAR16                 *TempString;
  EFI_STATUS              Status;

  //
  // Update the parent menu item select status
  //
  if (SctStrCmp (Page->Parent->Body.MenuItemHeader.Text, L"Main Menu")) {
    MenuItem = Page->Body.ItemList;
    ParentMenuItem  = Page->Parent->Body.CurrentSelected;
    SelectAll = TRUE;
    SelectNone = TRUE;

    MenuItem = MenuItem -> Next;
    while (MenuItem != NULL) {
      if (MenuItem->Status != EFI_ITEM_SELECT_ALL) {
        SelectAll = FALSE;
      }
      if (MenuItem->Status != EFI_ITEM_SELECT_NONE) {
        SelectNone = FALSE;
      }

      MenuItem = MenuItem -> Next;
    }

    if (SelectAll) {
      ParentMenuItem->Status = EFI_ITEM_SELECT_ALL;
    } else if (SelectNone) {
      ParentMenuItem->Status = EFI_ITEM_SELECT_NONE;
    } else {
      ParentMenuItem->Status = EFI_ITEM_SELECT_SOME;
    }

    //
    //Update Parent Iteration
    //
    TempString = NULL;
    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
                   (VOID **)&TempString
                   );
    if (EFI_ERROR (Status)) {
      return EFI_OUT_OF_RESOURCES;
    }

    SctSPrint (
      TempString,
      (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
      L"0"
      );

    MenuItem = Page->Body.ItemList;
    MenuItem = MenuItem -> Next;
    while (MenuItem != NULL) {
      if (SctAtoi (MenuItem->ItemValue) != 0) {
        SctSPrint (
          TempString,
          (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
          L"%s",
          MenuItem->ItemValue
          );
        break;
      }
      MenuItem = MenuItem -> Next;
    }

    MenuItem = Page->Body.ItemList;
    MenuItem = MenuItem -> Next;
    IterEqual = TRUE;
    while (MenuItem != NULL) {
      if (MenuItem->ItemValue[0] == L'*') {
        IterEqual = FALSE;
        break;
      }
      if (SctAtoi (MenuItem->ItemValue) != 0) {
        if (SctStrCmp (TempString, MenuItem->ItemValue)) {
          IterEqual = FALSE;
          break;
        }
      }
      MenuItem = MenuItem -> Next;
    }

    if (IterEqual) {
      SctSPrint (
        ParentMenuItem->ItemValue,
        (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
        L"%s",
        TempString
        );
    } else {
        SctSPrint (
        ParentMenuItem->ItemValue,
        (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
        L"*"
        );
    }

    SctFreePool (TempString);
  }

  //
  // Display the parent menu page
  //
  MenuPageRefresh (Page->Parent);
  DestroyMenuPage (Page);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
TestNodeMenuSpaceFunc(
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle Space key in case menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle Space key successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS             Status;
  EFI_MENU_ITEM          *MenuItem;
  EFI_SCT_TEST_NODE      *TestNode;

  //
  //check parameter.
  //
  if (Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (Page->Body.ItemList == NULL || Page->Body.CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  MenuItem = Page->Body.CurrentSelected;

  if ((MENU_ITEM_TYPE (MenuItem->ItemType) != EFI_ITEM_HAVE_CHECKBOX) &&
      (MENU_ITEM_TYPE (MenuItem->ItemType) != EFI_ITEM_CASE         )) {
    return EFI_SUCCESS;
  }

  //
  //change item select status
  //
  TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;

  Status = EFI_SUCCESS;
  if (MenuItem->Status == EFI_ITEM_SELECT_NONE ) {
    MenuItem->Status = EFI_ITEM_SELECT_ALL;
    SelectTestNode (TestNode, 1);
    SctSPrint (
      MenuItem->ItemValue,
      (EFI_MAX_ITER_EDIT_LENGTH + 1) * 2,
      L"1"
      );
  } else {
    MenuItem->Status = EFI_ITEM_SELECT_NONE;
    UnSelectTestNode (TestNode);
    SctSPrint (
      MenuItem->ItemValue,
      (EFI_MAX_ITER_EDIT_LENGTH + 1) * 2,
      L"0"
      );
  }

  //
  //at last refresh the menu item.
  //
  Status = MenuItemRefresh (Page, Page->Body.CurrentSelected, TRUE);

  return Status;
}

EFI_STATUS
EFIAPI
TestNodeMenuF9Func(
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle F9 key in case menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle Space key successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS                Status;
  EFI_INPUT_KEY             Key;
  EFI_DIALOG_CONTEXT        MsgDialogContext;
  CHAR16                   *MsgDialogTitle;

  //
  //check parameter.
  //
  if (Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MsgDialogTitle = SctStrDuplicate (L"Prepare running...");
  MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;
  DoDialog (MsgDialogTitle, &MsgDialogContext);

  tST->ConOut->SetAttribute (
                tST->ConOut,
                EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK
                );
  tST->ConOut->ClearScreen (tST->ConOut);

  Status = SctExecute ();
  if (Status != EFI_SUCCESS) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute - %r", Status));
  }

  //
  //Clear surplus key stroke.
  //
  Status = EFI_SUCCESS;
  while(!EFI_ERROR(Status)) {
    Status = tST->ConIn->ReadKeyStroke (tST->ConIn, &Key);
  }

  MenuPageRefresh (Page);
  return Status;
}

EFI_STATUS
EFIAPI
TestNodeMenuF8Func(
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle F8 key in case menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle Space key successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS             Status;
  EFI_INPUT_KEY             Key;

  //
  //check parameter.
  //
  if (Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  tST->ConOut->SetAttribute (
                tST->ConOut,
                EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK
                );
  tST->ConOut->ClearScreen (tST->ConOut);
  Status = SctContinueExecute ();

  gContinueExec = FALSE;
  MenuPageRefresh (Page);

  Status = EFI_SUCCESS;
  while(!EFI_ERROR(Status)) {
    Status = tST->ConIn->ReadKeyStroke (tST->ConIn, &Key);
  }

  return Status;
}

EFI_ITEM_SELECT_STATUS
GetItemSelectStatus(
  EFI_SCT_TEST_NODE         *TestNode
  )
/*++

Routine Description:

  Get the selected status of one menu item.

Arguments:

  TestNode      - The pointer to test node related this menu item

Returns:

  EFI_ITEM_SELECT_ALL   - All sub-items are selected
  EFI_ITEM_SELECT_NONE  - None of sub-item is selected
  EFI_ITEM_SELECT_SOME  - Part of sub-items are selected

--*/
{
  EFI_ITEM_SELECT_STATUS    ItemSelectStatus;
  EFI_SCT_TEST_NODE        *SubNode;
  SCT_LIST_ENTRY           *TempLink;
  BOOLEAN                   SelectAll;
  BOOLEAN                   SelectNone;
  UINTN                     TestCaseStatus;

  if (!SctIsListEmpty (&TestNode->Child)) {
    ItemSelectStatus = EFI_ITEM_SELECT_NONE;
    SelectAll = TRUE;
    SelectNone = TRUE;
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      ItemSelectStatus = GetItemSelectStatus (SubNode);
      if (ItemSelectStatus != EFI_ITEM_SELECT_ALL) {
        SelectAll = FALSE;
      }
      if (ItemSelectStatus != EFI_ITEM_SELECT_NONE) {
        SelectNone = FALSE;
      }
    }

    if (SelectAll) {
      ItemSelectStatus = EFI_ITEM_SELECT_ALL;
    } else if (SelectNone) {
      ItemSelectStatus = EFI_ITEM_SELECT_NONE;
    } else {
      ItemSelectStatus = EFI_ITEM_SELECT_SOME;
    }
  } else {
    GetTestCaseState (&TestNode->Guid, &TestCaseStatus);

    if (TestCaseStatus == EFI_SCT_TEST_STATE_NOT_IN_LIST) {
      ItemSelectStatus = EFI_ITEM_SELECT_NONE;
    } else {
      ItemSelectStatus = EFI_ITEM_SELECT_ALL;
    }
  }

  return ItemSelectStatus;
}

VOID
SelectTestNode (
  EFI_SCT_TEST_NODE           *TestNode,
  UINT32                      Iterations
  )
/*++

Routine Description:

  Select one test node and its sub-nodes.

Arguments:

  TestNode      - Test node to be selected
  Iterations    - Number of iterations

--*/
{

  EFI_SCT_TEST_NODE        *SubNode;
  SCT_LIST_ENTRY           *TempLink;

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      SelectTestNode (SubNode, Iterations);
    }
  } else {
    SelectTestCase (&TestNode->Guid, Iterations);
  }
}

VOID
SelectSomeTestNode (
  EFI_SCT_TEST_NODE           *TestNode,
  UINT32                      Iterations
  )
/*++

Routine Description:

  Select one test node and its sub-nodes, which are selected before.

Arguments:

  TestNode      - Test node to be selected
  Iterations    - Number of iterations

--*/
{

  EFI_SCT_TEST_NODE        *SubNode;
  SCT_LIST_ENTRY           *TempLink;

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      SelectSomeTestNode (SubNode, Iterations);
    }
  } else {
    if (GetTestCaseIterations (&TestNode->Guid) != 0) {
      SelectTestCase (&TestNode->Guid, Iterations);
    }
  }
}

VOID
UnSelectTestNode (
  EFI_SCT_TEST_NODE           *TestNode
  )
/*++

Routine Description:

  Unselect one test node and its sub-nodes.

Arguments:

  TestNode      - Test node to be unselected

--*/
{
  EFI_SCT_TEST_NODE        *SubNode;
  SCT_LIST_ENTRY           *TempLink;

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      UnSelectTestNode (SubNode);
    }
  } else {
    UnselectTestCase (&TestNode->Guid);
  }
}

EFI_STATUS
EFIAPI
TestNodeMenuDescPrintFunc (
  IN EFI_MENU_ITEM          *MenuItem,
  IN VOID                   *Context,
  IN UINTN                  Row,
  IN UINTN                  Column
  )
/*++

Routine Description:

  the  MenuItem description information displaying function.

Arguments:

  MenuItem      - The EFI_MENU_ITEM instance pointer.
  Context       - the EFI_MENU_PAGE instance pointer, the MenuItem belongs
                  to this MenuPage.
  Row           - The beginning Row on Output Console to display the
                  description message.
  Column        - The beginning Column on Output Console to display the
                  description message.

Returns:

  EFI_SUCCESS   - the description was displayed successfully.
  other         - error condition.

--*/
{
  UINTN           X0;
  UINTN           X1;
  UINTN           Y0;
  UINTN           Y1;
  UINTN           Index;
  UINTN           BufLen;
  UINTN           Attrib;
  UINTN           Order;
  UINTN           Passes;
  UINTN           Warnings;
  UINTN           Failures;
  EFI_STATUS      Status;
  EFI_MENU_PAGE   *Page;
  CHAR16          *Buffer;
  EFI_SCT_TEST_NODE      *TestNode;

  if (Context == NULL || MenuItem == NULL ) {
    return EFI_INVALID_PARAMETER;
  }

  BufLen  = 0;
  Page    = (EFI_MENU_PAGE *)Context;
  Attrib  = tST->ConOut->Mode->Attribute;
  X0      = Column;
  Y0      = Row;
  X1      = Page->Body.BodyRect.BottomRight.Col - 1;
  Y1      = Page->Body.BodyRect.BottomRight.Row - 1;

  if (X0 > X1 || Y0 > Y1) {
    return EFI_INVALID_PARAMETER;
  }

  if (MenuItem == Page->Body.CurrentSelected) {
    Status = tST->ConOut->SetAttribute (
                           tST->ConOut,
                           EFI_ITEM_DESC_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
                           );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    //First we display the default description information given by the menu
    //item directly
    //
    Buffer = MenuItem->ItemDesc.Text;

    if (Buffer != NULL && SctStrLen (Buffer) > 0 ) {
      //
      //Display the default description.
      //
      if (Y1 >= Y0 + 4) {
        Status = DisplayMessage(X0, Y0, X1, Y1 - 4, Buffer);
      }
    }

    //
    //then we display specific information for this menu item
    //
    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   MAX_STRING_LEN * sizeof (CHAR16),
                   (VOID **)&Buffer
                   );
    if (EFI_ERROR (Status)) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //first clear this area.
    //
    BufLen = (X1 - X0 + 2) * sizeof (CHAR16);

    for (Index = 0; Index < BufLen / 2 - 1; Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';

    for (Index = Y1 - 3; Index <= Y1; Index++) {
      Status = TestPrintAt (X0, Index, Buffer);
      if (EFI_ERROR (Status)) {
        tBS->FreePool (Buffer);
        return Status;
      }
    }

    //
    //display Select Index.
    //

    Order = 0;
    if (MenuItem->Context != NULL) {
      TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;
      Order = GetTestCaseOrder (&TestNode->Guid);
      Buffer[0] = L'\0';
      SctStrCat (Buffer, L"Order:");
      SctSPrint (Buffer, MAX_STRING_LEN, L"%s %d", Buffer, Order);
      if (SctStrLen (Buffer) > (X1 - X0 - 7)) {
        Buffer [X1 - X0 - 7] = L'\0';
      }
      Status = TestPrintAt (X0, Y1 - 4, Buffer);
    }

    Passes = 0;
    if (MenuItem->Context != NULL) {
      TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;
      Passes = CalculatePassNumber(TestNode);
      Buffer[0] = L'\0';
      SctStrCat (Buffer, L"Pass:");
      SctSPrint (Buffer, MAX_STRING_LEN, L"%s  %d", Buffer, Passes);
      if (SctStrLen (Buffer) > (X1 - X0 - 7)) {
        Buffer [X1 - X0 - 7] = L'\0';
      }
      Status = TestPrintAt (X0, Y1 - 3, Buffer);
    }

    Warnings = 0;
    if (MenuItem->Context != NULL) {
      TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;
      Warnings = CalculateWarningNumber(TestNode);
      Buffer[0] = L'\0';
      SctStrCat (Buffer, L"Warning:");
      SctSPrint (Buffer, MAX_STRING_LEN, L"%s  %d", Buffer, Warnings);
      if (SctStrLen (Buffer) > (X1 - X0 - 7)) {
        Buffer [X1 - X0 - 7] = L'\0';
      }
      Status = TestPrintAt (X0, Y1 - 2, Buffer);
    }

    Failures = 0;
    if (MenuItem->Context != NULL) {
      TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;
      Failures = CalculateFailNumber(TestNode);
      Buffer[0] = L'\0';
      SctStrCat (Buffer, L"Fail:");
      SctSPrint (Buffer, MAX_STRING_LEN, L"%s  %d", Buffer, Failures);
      if (SctStrLen (Buffer) > (X1 - X0 - 7)) {
        Buffer [X1 - X0 - 7] = L'\0';
      }
      Status = TestPrintAt (X0, Y1 - 1, Buffer);
    }

    tBS->FreePool (Buffer);

    tST->ConOut->SetAttribute (tST->ConOut, Attrib);

    //
    //successfully displayed the message
    //
    return EFI_SUCCESS;

  } else {

    //
    //clear the display area.
    //
    Status = tST->ConOut->SetAttribute (
                           tST->ConOut,
                           EFI_MENUPAGE_BODY_BGCOLOR >> 4 | EFI_MENUPAGE_BODY_BGCOLOR
                           );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    BufLen = (X1 - X0 + 2) * sizeof(CHAR16);
    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   BufLen,
                   (VOID **)&Buffer
                   );
    if (EFI_ERROR (Status)) {
      return EFI_OUT_OF_RESOURCES;
    }

    for (Index = 0; Index < BufLen / 2 - 1; Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';

    for (Index = Y0; Index <= Y1; Index ++) {
      Status = TestPrintAt (X0, Index, Buffer);
      if (EFI_ERROR (Status)) {
        tBS->FreePool (Buffer);
        return Status;
      }
    }

    tBS->FreePool (Buffer);
    tST->ConOut->SetAttribute (tST->ConOut, Attrib);
    return EFI_SUCCESS;
  }
}

UINTN
CalculateTotalPassNumber (
  SCT_LIST_ENTRY                  *Root
  )
/*++

Routine Description:

  Calculate the total pass number.

--*/
{
  UINTN            PassedNumber;
  EFI_SCT_TEST_NODE *SubNode;
  SCT_LIST_ENTRY    *TempLink;

  PassedNumber = 0;

  if (!SctIsListEmpty (Root)) {
    for (TempLink = Root->ForwardLink; TempLink != Root; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      PassedNumber += CalculatePassNumber (SubNode);
    }
  }

  return PassedNumber;
}


UINTN
CalculatePassNumber (
  EFI_SCT_TEST_NODE               *TestNode
  )
/*++

Routine Description:

  Calculate the pass number of this test node.

--*/
{
  UINTN             PassedNumber;
  EFI_SCT_TEST_NODE *SubNode;
  SCT_LIST_ENTRY    *TempLink;

  PassedNumber = 0;

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      PassedNumber += CalculatePassNumber (SubNode);
    }
  } else {
    PassedNumber = GetTestCasePasses (&TestNode->Guid);
  }

  return PassedNumber;
}

UINTN
CalculateTotalWarningNumber (
  SCT_LIST_ENTRY                  *Root
  )
/*++

Routine Description:

  Calculate the total warning number.

--*/
{
  UINTN            WarningNumber;
  EFI_SCT_TEST_NODE *SubNode;
  SCT_LIST_ENTRY    *TempLink;

  WarningNumber = 0;

  if (!SctIsListEmpty (Root)) {
    for (TempLink = Root->ForwardLink; TempLink != Root; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      WarningNumber += CalculateWarningNumber (SubNode);
    }
  }

  return WarningNumber;
}

UINTN
CalculateWarningNumber (
  EFI_SCT_TEST_NODE               *TestNode
  )
/*++

Routine Description:

  Calculate the warning number of this test node.

--*/
{
  UINTN             WarningNumber;
  EFI_SCT_TEST_NODE *SubNode;
  SCT_LIST_ENTRY    *TempLink;

  WarningNumber = 0;

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      WarningNumber += CalculateWarningNumber (SubNode);
    }
  } else {
    WarningNumber = GetTestCaseWarnings (&TestNode->Guid);
  }

  return WarningNumber;
}

UINTN
CalculateTotalFailNumber (
  SCT_LIST_ENTRY                  *Root
  )
/*++

Routine Description:

  Calculate the total fail number.

--*/
{
  UINTN             FailedNumber;
  EFI_SCT_TEST_NODE *SubNode;
  SCT_LIST_ENTRY    *TempLink;

  FailedNumber = 0;

  if (!SctIsListEmpty (Root)) {
    for (TempLink = Root->ForwardLink; TempLink != Root; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      FailedNumber += CalculateFailNumber (SubNode);
    }
  }

  return FailedNumber;
}


UINTN
CalculateFailNumber (
  EFI_SCT_TEST_NODE               *TestNode
  )
/*++

Routine Description:

  Calculate the pass number of this test node.

--*/
{
  UINTN             FailedNumber;
  EFI_SCT_TEST_NODE *SubNode;
  SCT_LIST_ENTRY    *TempLink;

  FailedNumber = 0;

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      FailedNumber += CalculateFailNumber (SubNode);
    }
  } else {
    FailedNumber = GetTestCaseFailures (&TestNode->Guid);
  }

  return FailedNumber;
}

BOOLEAN
IsTestRunning (
  EFI_SCT_TEST_NODE               *TestNode
  )
/*++

Routine Description:

  Check this test is running or not.

--*/
{
  BOOLEAN Running;
  EFI_SCT_TEST_NODE           *SubNode;
  SCT_LIST_ENTRY              *TempLink;
  EFI_SCT_TEST_STATE          TestState;

  Running = FALSE;

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      Running = IsTestRunning (SubNode);
      if (Running) {
        return TRUE;
      }
    }
  } else {
    GetTestCaseState (&TestNode->Guid, &TestState);
    if (TestState == EFI_SCT_TEST_STATE_RUNNING) {
      return TRUE;
    } else {
      return FALSE;
    }
  }

  return FALSE;
}

BOOLEAN
IsTestCaseFinished (
  EFI_SCT_TEST_NODE               *TestNode
  )
/*++

Routine Description:

  Check this test is finished or not.

--*/
{
  BOOLEAN                     Finished;
  EFI_SCT_TEST_NODE           *SubNode;
  SCT_LIST_ENTRY              *TempLink;
  EFI_SCT_TEST_STATE          TestState;

  Finished = FALSE;

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      Finished = IsTestCaseFinished (SubNode);
      if (Finished) {
        return TRUE;
      }
    }
  } else {
    GetTestCaseState (&TestNode->Guid, &TestState);
    if (TestState == EFI_SCT_TEST_STATE_FINISHED) {
      return TRUE;
    } else {
      return FALSE;
    }
  }

  return FALSE;
}

EFI_STATUS
UpdateIter (
  IN EFI_MENU_PAGE                *MenuPage,
  IN EFI_MENU_ITEM                *MenuItem,
  IN UINT32                       Iterations
  )
{
  EFI_SCT_TEST_NODE      *TestNode;
  EFI_STATUS             Status;

  //
  //change item select status
  //
  TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;

  if (Iterations == 0) {
    MenuItem->Status = EFI_ITEM_SELECT_NONE;
    UnSelectTestNode (TestNode);
    Status = MenuItemStatusRefresh (
                 MenuPage,
                 MenuPage->Body.CurrentSelected,
                 FALSE
                 );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    if (MenuItem->Status == EFI_ITEM_SELECT_NONE) {
      MenuItem->Status = EFI_ITEM_SELECT_ALL;
      SelectTestNode (TestNode, Iterations);
      Status = MenuItemStatusRefresh (
                 MenuPage,
                 MenuPage->Body.CurrentSelected,
                 TRUE
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }

    if (MenuItem->Status == EFI_ITEM_SELECT_ALL) {
      SelectTestNode (TestNode, Iterations);
      Status = MenuItemStatusRefresh (
                 MenuPage,
                 MenuPage->Body.CurrentSelected,
                 FALSE
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }

    if (MenuItem->Status == EFI_ITEM_SELECT_SOME) {
      SelectSomeTestNode (TestNode, Iterations);
      Status = MenuItemStatusRefresh (
                 MenuPage,
                 MenuPage->Body.CurrentSelected,
                 FALSE
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetIterString(
  EFI_SCT_TEST_NODE                  *TestNode,
  CHAR16                             *IterString
  )
{
  UINTN             IterNumber;
  EFI_SCT_TEST_NODE *SubNode;
  SCT_LIST_ENTRY    *TempLink;
  CHAR16            *TempString;
  UINT32            TempValue;
  UINTN             Count;
  EFI_STATUS        Status;

  Count = 0;
  IterNumber = 0;
  TempValue = 0;
  TempString = NULL;
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
                 (VOID **)&TempString
                 );
  if (EFI_ERROR (Status)) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (!SctIsListEmpty (&TestNode->Child)) {
    for (TempLink = (&TestNode->Child)->ForwardLink; TempLink != &TestNode->Child; TempLink = TempLink->ForwardLink) {
      SubNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
      GetIterString (SubNode, TempString);
      if (TempString[0] == L'*') {
        //
        // set iteration value
        //
        SctSPrint (
          IterString,
          (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
          L"*"
          );
        SctFreePool (TempString);
        return EFI_SUCCESS;
      } else {
        if (Count == 0) {
          TempValue = (UINT32) SctAtoi (TempString);
          if (TempValue != 0) {
            SctSPrint (
              IterString,
              (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
              L"%s",
              TempString
              );
            Count ++; //get the first selected item and record its iterations
          }
        } else {
          if ((SctAtoi (TempString) > 0 ) && TempValue != SctAtoi (TempString)) {
            SctSPrint (
              IterString,
              (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
              L"*"
              );
            SctFreePool (TempString);
            return EFI_SUCCESS;
          }
        } // end if (Count == 0)
      }
    } //end for

    if (Count == 0) {
      SctSPrint (
        IterString,
        (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
        L"0"
        );
    }
  } else {
    IterNumber = GetTestCaseIterations (&TestNode->Guid);
    SctSPrint (
      IterString,
      (EFI_MAX_ITER_EDIT_LENGTH + 2) * 2,
      L"%d",
      IterNumber
      );
  }

  SctFreePool (TempString);
  return EFI_SUCCESS;
}
