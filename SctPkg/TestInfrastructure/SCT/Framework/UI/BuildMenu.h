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

  BuildMenu.h

Abstract:

  This file provides the services to build a menu.

--*/

#ifndef _EFI_BUILD_MENU_H_
#define _EFI_BUILD_MENU_H_

//
// Includes
//

//
// Definitions
//

#define EFI_MENU_HEADER_ROWS        1
#define EFI_MENU_FOOTER_ROWS        2
#define EFI_MENU_DESCRIPTOR_COLS    20

#define EFI_CREATE_BY_PROTOCOL      0
#define EFI_CREATE_BY_DRIVER        1
#define EFI_CREATE_BY_FILENAME      2

//
// Prototypes (from BuildMenu.c)
//

EFI_STATUS
BuildMenuSystem (
  VOID
  );

EFI_STATUS
CreateStandardMenuPage (
  IN CHAR16                       *MenuItemHeaderText,
  OUT EFI_MENU_PAGE               **Page
  );

EFI_STATUS
DestroyMenuPage (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
AddHotKey (
  IN CHAR16                       *HotKeyNameText,
  IN CHAR16                       *HotKeyDescText,
  IN UINT16                       ScanCode,
  IN CHAR16                       UnicodeChar,
  IN KEY_FUNCTION                 KeyFunc,
  IN BOOLEAN                      Visible,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddSimpleMenuItem (
  IN EFI_ITEM_TYPE                ItemType,
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddEditMenuItem (
  IN EFI_ITEM_TYPE                SubType,
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN CHAR16                       *ItemValue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddCaseMenuItem (
  IN EFI_ITEM_TYPE                SubType,
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN CHAR16                       *ItemValue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddMenuItemCheckValue (
  IN CHAR16                       *ItemNameText,
  IN UINTN                        MaxValue,
  IN UINTN                        MinValue,
  IN UINTN                        DefaultValue,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddPopupMenuItem (
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN CHAR16                       *ItemValue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddComboListMenuItem (
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN EFI_ITEM_VALUE_QUEUE         *ValueQueue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddSeparateLine (
  IN UINTN                        Number,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
InsertValueQueue (
  IN OUT EFI_ITEM_VALUE_QUEUE     **ValueQueue,
  IN CHAR16                       *StringValue,
  IN UINTN                        IntValue
  );

EFI_STATUS
DestroyValueQueue (
  IN EFI_ITEM_VALUE_QUEUE         *ValueQueue
  );

EFI_STATUS
AddScrollBar (
  IN OUT EFI_MENU_PAGE            *Page
  );

//
//protypes (from BuildMenuByFile.c)
//

EFI_STATUS
BuildMenuByFile (
  IN CHAR16                       *FileName,
  IN CHAR16                       *MenuItemHeaderText,
  OUT EFI_MENU_PAGE               **Page
  );

//
// Prototypes (from MainMenu.c)
//

EFI_STATUS
DisplayMainMenu (
  VOID
  );

//
// Prototypes (from ConfigMenu.c)
//

EFI_STATUS
DisplayConfigMenu (
  IN EFI_MENU_PAGE                *ParentPage
  );

//
// Prototypes (from CaseMgmtMenu.c)
//

EFI_STATUS
DisplayCaseMgmtMenu (
  IN EFI_MENU_PAGE                *ParentPage
  );

//
// Prototypes (from ProtocolMenu.c)
//

EFI_STATUS
DisplayProtocolMenu (
  IN EFI_MENU_PAGE                *ParentPage
  );

//
// Prototypes (from DriverMenu.c)
//

EFI_STATUS
DisplayDriverMenu (
  IN EFI_MENU_PAGE                *ParentPage
  );

//
// Prototypes (from FileSequenceMenu.c)
//

EFI_STATUS
DisplayFileNameMenu (
  IN EFI_MENU_PAGE                *ParentPage
  );

EFI_STATUS
DisplaySequenceMenu (
  IN EFI_MENU_PAGE                *ParentPage
  );

//
// Prototypes (from CaseMenu.c)
//

EFI_STATUS
DisplayCaseMenu (
  IN UINTN                        Type,
  IN EFI_MENU_PAGE                *ParentPage
  );

//
//prototypes (from ResultMgmtMenu.c)
//
EFI_STATUS
DisplayResultMgmtMenu (
  IN EFI_MENU_PAGE                *ParentPage
  );
//
//protypes (from UtilityMenu.c)
//
EFI_STATUS
DisplayUtilityMenu (
  IN EFI_MENU_PAGE                *ParentPage
  );

#endif
