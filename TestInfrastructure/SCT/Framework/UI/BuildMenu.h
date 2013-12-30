/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
