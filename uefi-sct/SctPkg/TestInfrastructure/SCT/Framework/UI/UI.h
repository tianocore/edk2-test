/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ui.h

Abstract:

  This file defines EFI Test Framework basic UI, include macro structure and
  function porotype.

--*/

#ifndef _EFI_UI_H_
#define _EFI_UI_H_

//
//const color defines
//
#define  EFI_MENUPAGE_HEADER_BGCOLOR            (EFI_BACKGROUND_BLACK)
#define  EFI_MENUPAGE_BODY_BGCOLOR              (EFI_BACKGROUND_LIGHTGRAY)
#define  EFI_MENUPAGE_FOOTER_BGCOLOR            (EFI_BACKGROUND_BLACK)
#define  EFI_MENUPAGE_HEADER_FORECOLOR          (EFI_WHITE)
#define  EFI_MENUPAGE_ITEM_COMMON_FORECOLOR     (EFI_BLUE)
#define  EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR   (EFI_WHITE)
#define  EFI_ITEM_DESC_FORECOLOR                (EFI_BLACK)
#define  EFI_MENUPAGE_FOOTER_HOTKEY_FORECOLOR   (EFI_GREEN)
#define  EFI_MENUPAGE_SCROLLBAR_FORECOLOR       EFI_MENUPAGE_ITEM_COMMON_FORECOLOR
#define  EFI_MENUPAGE_FOOTER_DESC_FORECOLOR     (EFI_WHITE)
#define  EFI_ITEM_EDIT_FORECOLOR                (EFI_WHITE)
#define  EFI_POPUP_MENU_FORECOLOR               (EFI_LIGHTGRAY)
#define  EFI_POPUP_MENU_BACKCOLOR               (EFI_BLACK)

//
//const length defines
//
#define  EFI_HOTKEY_NAME_SPAN                   9
#define  EFI_HOTKEY_DESC_SPAN                   17
#define  EFI_MAX_EDIT_ITEM_NAME_LENGTH          30
#define  EFI_MAX_ITEM_NAME_LENGTH               50
#define  EFI_MAX_ITEM_VALUE_LENGTH              20
#define  EFI_MAX_CASE_ITEM_NAME_LENGTH          38
#define  EFI_MAX_CASE_ITEM_VALUE_LENGTH         4
#define  EFI_ITEM_TYPE_TAG_LENGTH               5
#define  EFI_POPUP_MENU_ITEM_TAG_LENGTH         7
#define  EFI_MAX_LINE_LENGTH                    160
#define  EFI_MAX_EDIT_LENGTH                    256
#define  MAX_CHAR                               240
#define  EFI_MAX_ITER_EDIT_LENGTH               3

//
//EFI_ALIGNMENT_TYPE
//
typedef enum  {
  EFI_ALIGNMENT_LEFT = 0,
  EFI_ALIGNMENT_MIDDLE,
  EFI_ALIGNMENT_RIGHT
}EFI_ALIGNMENT_TYPE;

//
//EFI_ITEM_TYPE
//
#define  EFI_ITEM_HAVE_SUBITEMS                 0x00
#define  EFI_ITEM_HAVE_POPUP                    0x01
#define  EFI_ITEM_HAVE_EDIT                     0x02
#define  EFI_ITEM_HAVE_CHECKBOX                 0x08
#define  EFI_ITEM_HAVE_COMBOLIST                0x04
#define  EFI_ITEM_HAVE_RADIOBOX                 0x10
#define  EFI_ITEM_COMMAND                       0x20
#define  EFI_ITEM_STRING                        0x40
#define  EFI_ITEM_EDIT_NUMBER                   0x100
#define  EFI_ITEM_EDIT_STRING                   0x200
#define  EFI_ITEM_CASE                          0x80

typedef UINTN       EFI_ITEM_TYPE;

#define EFI_ITEM_TYPE_MASK                      0xFF
#define EFI_EDIT_SUB_TYPE_MASK                  0x300
#define MENU_ITEM_TYPE(type)                    (type & EFI_ITEM_TYPE_MASK)

#define EFI_DIALOG_SELECT_YES                   1
#define EFI_DIALOG_SELECT_NO                    0

typedef enum {
  EFI_ITEM_SELECT_NONE = 0,
  EFI_ITEM_SELECT_SOME,
  EFI_ITEM_SELECT_ALL
}EFI_ITEM_SELECT_STATUS;

typedef struct {
  UINT16                      *Text;
  UINTN                       TextColor;
  EFI_ALIGNMENT_TYPE          Align;
} EFI_MENU_STRING;

typedef struct {
  UINTN                       Row;
  UINTN                       Col;
} EFI_POINT;

typedef struct {
  EFI_POINT                   TopLeft;
  EFI_POINT                   BottomRight;
}EFI_RECT;

typedef struct {
  EFI_MENU_STRING             HeaderString;
  EFI_RECT                    HeaderRect;
} EFI_MENU_HEADER;

//
// Forward reference for pure ANSI compatibility
//
typedef struct _EFI_MENU_ITEM EFI_MENU_ITEM;
typedef struct _EFI_MENU_PAGE EFI_MENU_PAGE;
typedef struct _EFI_ITEM_VALUE_QUEUE EFI_ITEM_VALUE_QUEUE;
typedef struct _EFI_HOT_KEY EFI_HOT_KEY;

typedef
EFI_STATUS
(EFIAPI *DESC_PRINT) (
  IN EFI_MENU_ITEM            *MenuItem,
  IN VOID                     *Context,
  IN UINTN                    Row,
  IN UINTN                    Column
  );

struct _EFI_ITEM_VALUE_QUEUE {
  EFI_ITEM_VALUE_QUEUE        *Next;
  EFI_ITEM_VALUE_QUEUE        *Prev;
  UINT16                      *StringValue;
  UINTN                       IntValue;
};

typedef struct _EFI_MENU_ITEM_CONTEXT {
  EFI_GUID                    *ItemGuid;
} EFI_MENU_ITEM_CONTEXT;

struct _EFI_MENU_ITEM {
  EFI_MENU_ITEM               *Next;
  EFI_MENU_ITEM               *Prev;
  EFI_ITEM_TYPE               ItemType;
  BOOLEAN                     IsSelected; // only valid when Item type is Radio Box
  EFI_ITEM_SELECT_STATUS      Status;     // only valid when Item type is Check Box
  EFI_MENU_STRING             ItemString;
  EFI_ITEM_VALUE_QUEUE        *ValueQueue; // only valid when Item type is combolist
  UINT16                      *ItemValue;
  UINTN                       MaxValue;    // only valid when Item type is edit number
  UINTN                       MinValue;    // only valid when Item type is edit number
  UINTN                       DefaultValue;// only valid when Item type is edit number
  BOOLEAN                     CheckValue;  // only valid when Item type is edit number
  UINTN                       Attribute;
  UINTN                       Skip;
  EFI_MENU_STRING             ItemDesc;
  DESC_PRINT                  DescPrint;
  VOID                        *Context; // can point to function or data struct
};

typedef struct {
  EFI_RECT                    ScrollBarRect;
  UINTN                       PinLength;
  UINTN                       Count;
  UINTN                       Pos;
  UINTN                       ForeColor;
} EFI_SCROLL_BAR;

typedef struct {
  UINTN                       BackColor;
  UINTN                       ForeColor;
  EFI_RECT                    BodyRect;
  EFI_POINT                   SplitPoint;
  EFI_MENU_STRING             MenuItemHeader;
  BOOLEAN                     HasScrollBar;
  EFI_MENU_STRING             DescriptionHeader;
  EFI_SCROLL_BAR              *ScrollBar;
  EFI_MENU_ITEM               *ItemList;
  EFI_MENU_ITEM               *CurrentSelected;
  EFI_MENU_ITEM               *FirstInDisplay;
  EFI_MENU_ITEM               *LastInDisplay;
} EFI_MENU_BODY;

typedef
EFI_STATUS
(EFIAPI *KEY_FUNCTION) (
  IN EFI_MENU_PAGE            *MenuPage
);

struct _EFI_HOT_KEY {
  EFI_MENU_STRING             HotKeyName;
  EFI_MENU_STRING             HotKeyDesc;
  EFI_INPUT_KEY               KeyCode;
  BOOLEAN                     Visible;
  KEY_FUNCTION                Context;
  EFI_HOT_KEY                 *Next;
};

typedef struct {
  EFI_HOT_KEY                 *HotKeyList;
  EFI_RECT                    FooterRect;
} EFI_MENU_FOOTER;

struct _EFI_MENU_PAGE {
  UINTN                       BackColor;
  BOOLEAN                     HasHeader;
  EFI_MENU_HEADER             Header;
  BOOLEAN                     HasBody;
  EFI_MENU_BODY               Body;
  BOOLEAN                     HasFooter;
  EFI_MENU_FOOTER             Footer;
  EFI_MENU_PAGE               *Parent;
};

EFI_STATUS
TestPrintAt (
  IN  UINTN                   Col,
  IN  UINTN                   Row,
  IN  CHAR16                  *String
  )
/*++

Routine Description:

  Simply  Set the Cursor Position and then Output the String.

Arguments:

  Col               - the column position that the cursor to be set.
  Row               - the Row position that the cursor to be set
  String            - is the Pointer the String to be Printed.

Returns:

  EFI_SUCCESS       - the String was output to device successfully.
  EFI_DEVICE_ERROR

--*/
;


EFI_STATUS
MenuHeaderRefresh (
  IN EFI_MENU_PAGE            *MenuPage
  )
/*++

Routine Description:

  refresh the menupage header.

Arguments:

  MenuPage              - whose header to be drawed/redrawed.

Returns:

  EFI_SUCCESS           - the menupage header was rendered successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid

--*/
;

EFI_STATUS
MenuBodyRefresh (
  IN EFI_MENU_PAGE            *MenuPage
  )
/*++

Routine Description:

  refresh the menupage body.

Arguments:

  MenuPage              - whose body to be refreshed.

Returns:

  EFI_SUCCESS           - the menupage body was refreshed successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid.

--*/
;

//
//internal function to refresh menu items and menu item.
//

EFI_STATUS
MenuBodyItemsRefresh (
  IN EFI_MENU_PAGE            *MenuPage
  )
/*++

Routine Description:

  refresh the All the MenuItem in the MenuBody but don't redraw the lines.

Arguments:

  MenuPage              - Whose MenuItems to be refreshed.

Returns:

  EFI_SUCCESS           - The menupage Items was refreshed successfully.
  EFI_INVALID_PARAMETER - The Parameter is Invalid.

--*/
;

EFI_STATUS
MenuItemRefresh (
  IN EFI_MENU_PAGE            *MenuPage,
  IN EFI_MENU_ITEM            *Item,
  IN BOOLEAN                  DisplayDesc
  )
/*++

Routine Description:

  refresh the menupage one item in the body.

Arguments:

  MenuPage              - whose body's menu item to be refreshed.
  Item                  - the item to be refreshed.
  Line                  - the offset to the menupage body splitpoint Row.

Returns:

  EFI_SUCCESS           - the item was refreshed successfully.
  EFI_INVALID_PARAMETER

--*/
;

EFI_STATUS
MenuItemStatusRefresh(
  IN EFI_MENU_PAGE          *MenuPage,
  IN EFI_MENU_ITEM          *Item,
  IN BOOLEAN                DisplayDesc
  )
/*++

Routine Description:

  refresh the status of case item in the body.

Arguments:

  MenuPage              - whose body's menu item to be refreshed.
  Item                  - the item to be refreshed.

Returns:

  EFI_SUCCESS           - the item was refreshed successfully.
  EFI_INVALID_PARAMETER

--*/
;

EFI_STATUS
MenuFooterRefresh (
  IN EFI_MENU_PAGE            *MenuPage
  )
/*++

Routine Description:

  refresh the menupage footer.

Arguments:

  MenuPage              - whose footer to be refreshed.

Returns:

  EFI_SUCCESS           - the menupage footer was refreshed successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid

--*/
;

EFI_STATUS
MenuPageRefresh (
  IN EFI_MENU_PAGE            *MenuPage
  )
/*++

Routine Description:

  refresh the total menupage.

Arguments:

  MenuPage              - which menu page to be refreshed.

Returns:

  EFI_SUCCESS           - the menupage  was refreshed successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid

--*/
;

EFI_STATUS
MenuPageKeyInput (
  VOID
  )
/*++

Routine Description:

  the menupage key input event response function.
  what ever key was pressed this function will give correct response.

Returns:

  EFI_SUCCESS           - the keys was processed successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid

--*/
;

EFI_STATUS
DefaultDescPrint (
  IN EFI_MENU_ITEM            *MenuItem,
  IN VOID                     *Context,
  IN UINTN                    Row,
  IN UINTN                    Column
  )
/*++

Routine Description:

  the default MenuItem description information displaying function.

Arguments:

  MenuItem    - The EFI_MENU_ITEM instance pointer.
  Context     - the EFI_MENU_PAGE instance pointer.
  Row         - The beginning Row on Output Console.
  Column      - The beginning Column on Output Console.

Returns:

  EFI_SUCCESS - the description was displayed successfully.
  other       - error condition.

--*/
;

EFI_STATUS
DisplayMessage (
  IN UINTN                    X0,
  IN UINTN                    Y0,
  IN UINTN                    X1,
  IN UINTN                    Y1,
  IN CHAR16                   *Str
  );

EFI_STATUS
DoEdit (
  IN EFI_MENU_PAGE            *MenuPage,
  IN EFI_INPUT_KEY            *InKey
  );

EFI_STATUS
DoIterEdit (
  IN EFI_MENU_PAGE            *MenuPage,
  IN EFI_INPUT_KEY            *InKey
  );

//
//below are some default Key Process Function.
//

EFI_STATUS
EFIAPI
UpFunc (
  IN EFI_MENU_PAGE            *MenuPage
  );

EFI_STATUS
EFIAPI
DownFunc (
  IN EFI_MENU_PAGE            *MenuPage
  );

EFI_STATUS
EFIAPI
PageUpFunc (
  IN EFI_MENU_PAGE            *MenuPage
  );

EFI_STATUS
EFIAPI
PageDownFunc (
  IN EFI_MENU_PAGE            *MenuPage
  );

EFI_STATUS
SpaceFunc (
  IN EFI_MENU_PAGE            *MenuPage
  );

EFI_STATUS
EFIAPI
LeftArrowFunc (
  IN EFI_MENU_PAGE            *MenuPage
  );

EFI_STATUS
EFIAPI
RightArrowFunc (
  IN EFI_MENU_PAGE            *MenuPage
  );

EFI_STATUS
InitializeTestFrameworkUi (
  INTN *Mode
  )
/*++

Routine Description:

  UI initialize function,save current Output Console attribute and
  restore them when finish the UI interactive.

Arguments:

  ImageHandle   - Current Image Handle.
  SystemTable   - The SystemTable Pointer.

Returns:

  EFI_SUCCESS   - The initialize has been done successfully.
  Other         - error condition.

--*/
;

EFI_STATUS
TestFrameworkUiRestore (
  VOID
  )
/*++

Routine Description:

  restore     - the original output console attribute.

Arguments:

  EFI_SUCCESS - The output console was restored successfully.
  Other       - error condition.

--*/
;

EFI_STATUS
RestoreAttribute (
  VOID
  )
/*++

Routine Description:

  restore original console attribute.

Returns:

  EFI_SUCCESS.

--*/
;

EFI_STATUS
UpdateIter (
  IN EFI_MENU_PAGE            *MenuPage,
  IN EFI_MENU_ITEM            *MenuItem,
  IN UINT32                   Iterations
  );

BOOLEAN
IsTestCaseFinished(
  EFI_SCT_TEST_NODE           *TestNode
  );

BOOLEAN
IsTestRunning(
  EFI_SCT_TEST_NODE           *TestNode
  );

#endif
