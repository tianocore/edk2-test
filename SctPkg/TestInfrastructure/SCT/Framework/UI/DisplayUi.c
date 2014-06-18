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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DisplayUi.c

Abstract:

  SCT user interface functions

--*/
#include "Sct.h"
#include "UI.h"
#include "BuildMenu.h"
#include "TestNodeMenu.h"

//
// the global varibles used in UI.
//
INTN             gMode;
INTN             gConAttrib;
EFI_MENU_PAGE    *gMenuPage;
BOOLEAN          gMenuExit;

//
//protypes (external)
//
EFI_STATUS
DrawScrollBar (
  IN EFI_SCROLL_BAR     *ScrollBar
);

EFI_STATUS
TestPrintAt (
  IN  UINTN             Col,
  IN  UINTN             Row,
  IN  CHAR16            *String
);

EFI_STATUS
SetScrollBarPos (
  IN  OUT EFI_SCROLL_BAR  *ScrollBar,
  IN  UINTN               Pos
);

EFI_STATUS
MenuBodyRefresh (
  IN EFI_MENU_PAGE      *MenuPage
);

EFI_STATUS
MenuFooterRefresh (
  IN EFI_MENU_PAGE      *MenuPage
);

EFI_STATUS
MenuBodyItemsRefresh (
  IN EFI_MENU_PAGE      *MenuPage
);

EFI_STATUS
MenuItemRefresh (
  IN EFI_MENU_PAGE      *MenuPage,
  IN EFI_MENU_ITEM      *Item,
  IN BOOLEAN            DisplayDesc
);

EFI_STATUS
MenuPageRefresh (
  IN EFI_MENU_PAGE      *MenuPage
);

EFI_STATUS
InitializeTestFrameworkUi (
  INTN *Mode
  );

EFI_STATUS
RestoreAttribute (
  VOID
  );

//
//funcntions
//

EFI_STATUS
TestPrintAt (
  IN  UINTN             Col,
  IN  UINTN             Row,
  IN  CHAR16            *String
  )
/*++

Routine Description:

  Simply Set Cursor Position and then Output the String at current Cursor.

Arguments:

  Col               - the column position that the cursor to be set.
  Row               - the Row position that the cursor to be set
  String            - is the Pointer the String to be Printed.

Returns:

  EFI_SUCCESS       - the String was output to device successfully.
  EFI_DEVICE_ERROR

--*/
{
  EFI_STATUS Status;

  Status = tST->ConOut->SetCursorPosition (tST->ConOut, Col, Row);
  if (!EFI_ERROR(Status)) {
    Status = tST->ConOut->OutputString (tST->ConOut, String);
  }
  return Status;
}

EFI_STATUS
DrawScrollBar (
  IN EFI_SCROLL_BAR     *ScrollBar
  )
/*++

Routine Description:

  draw the scroll bar on the menupage body.

Arguments:

  ScrollBar         - the scroll bar to be rendered in output device.

Returns:

  EFI_SUCCESS       - the ScrollBar was rendered successfully.
  EFI_DEVICE_ERROR

--*/
{
  CHAR16              Buffer[4];
  UINTN               Index;
  UINTN               X0;
  UINTN               Y0;
  UINTN               Y1;
  EFI_STATUS          Status;

  if (ScrollBar == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //initialize varibles
  //
  X0      = ScrollBar->ScrollBarRect.TopLeft.Col;
  Y0      = ScrollBar->ScrollBarRect.TopLeft.Row;
  Y1      = ScrollBar->ScrollBarRect.BottomRight.Row;
  Status  = EFI_SUCCESS;

  tST->ConOut->SetAttribute (
        tST->ConOut,
        EFI_MENUPAGE_BODY_BGCOLOR | EFI_MENUPAGE_SCROLLBAR_FORECOLOR
        );

  //
  //draw up triangle
  //
  Buffer[1] = L'\0';
  Buffer[0] = GEOMETRICSHAPE_UP_TRIANGLE;
  Status = TestPrintAt (X0, Y0, Buffer);
  if( EFI_ERROR (Status)) {
    return Status;
  }

  //
  //draw light shade before scroll bar
  //
  Buffer[0] = BLOCKELEMENT_LIGHT_SHADE;
  for (Index = Y0 + 1; Index < Y0 + 1 + ScrollBar->Pos; Index++) {
    Status = TestPrintAt (X0, Index, Buffer);
    if( EFI_ERROR (Status)) {
      return Status;
    }
  }
  //
  //draw full block
  //
  Buffer[0] = BLOCKELEMENT_FULL_BLOCK;
  for(Index = Y0 + 1 + ScrollBar->Pos; Index < Y0 + 1 + ScrollBar->Pos + ScrollBar->PinLength; Index++) {
    TestPrintAt (X0,  Index, Buffer);
    if( EFI_ERROR (Status)) {
      return Status;
    }
  }

  //
  //draw remaining light shade
  //
  Buffer[0] = BLOCKELEMENT_LIGHT_SHADE;
  for (Index = Y0 + 1 + ScrollBar->Pos + ScrollBar->PinLength; Index < Y1; Index ++) {
    Status = TestPrintAt (
               X0,
               Index,
               Buffer
               );
    if( EFI_ERROR (Status)) {
      return Status;
    }
  }

  //
  //draw down triangle
  //
  Buffer[0] = GEOMETRICSHAPE_DOWN_TRIANGLE;
  Status = TestPrintAt (X0, Y1, Buffer);
  return  Status;

}

EFI_STATUS
SetScrollBarPos (
  IN  OUT EFI_SCROLL_BAR  *ScrollBar,
  IN  UINTN               Pos
  )
/*++

Routine Description:

  draw the scroll bar on the menupage body.

Arguments:

  ScrollBar         - the scroll bar to be rendered in output device.

Returns:

  EFI_SUCCESS       - the ScrollBar was rendered successfully.
  EFI_DEVICE_ERROR

--*/
{

  UINTN       CurrentPos;
  UINTN       Y0;
  UINTN       Y1;
  EFI_STATUS  Status;
  UINTN       Index;

  if(ScrollBar == NULL || Pos > ScrollBar->Count) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;
  Y0     = ScrollBar->ScrollBarRect.TopLeft.Row;
  Y1     = ScrollBar->ScrollBarRect.BottomRight.Row;
  //
  //caculate current scroll bar position
  //
  if (Pos > (ScrollBar->Count - (Y1 - Y0 + 1))) {
    Pos = ScrollBar->Count - (Y1 - Y0 + 1);
  }
  CurrentPos = (Pos * (Y1  - Y0 - 1)) / ScrollBar->Count;
  Index      = (Pos * (Y1  - Y0 - 1)) % ScrollBar->Count;

  if (Index > ScrollBar->Count / 2 &&
      CurrentPos + ScrollBar->PinLength < Y1 - Y0 - 1) {
    CurrentPos ++;
  }
  //
  //redraw scroll bar
  //
  ScrollBar->Pos = CurrentPos;
  Status = DrawScrollBar (ScrollBar);

  return  Status;
}

EFI_STATUS
MenuHeaderRefresh (
  IN EFI_MENU_PAGE      *MenuPage
  )
/*++

Routine Description:

  refresh the menupage header.

Arguments:

  MenuPage              - whose header to be drawed/redrawed.

Returns:

  EFI_SUCCESS           - the menupage header was rendered successfully.
  EFI_DEVICE_ERROR
  EFI_INVALID_PARAMETER

--*/
{
  UINTN            Xpos;
  UINTN            Ypos;
  UINTN            X0;
  UINTN            Y0;
  UINTN            X1;
  UINTN            Y1;
  CHAR16           Buffer[EFI_MAX_LINE_LENGTH+1];
  UINTN            Index;
  EFI_STATUS       Status;

  if (MenuPage == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  //initialize variables
  //
  Status  = EFI_SUCCESS;
  X0      = MenuPage->Header.HeaderRect.TopLeft.Col;
  Y0      = MenuPage->Header.HeaderRect.TopLeft.Row;
  X1      = MenuPage->Header.HeaderRect.BottomRight.Col;
  Y1      = MenuPage->Header.HeaderRect.BottomRight.Row;
  Xpos    = 0;
  Ypos    = (Y1 + Y0) / 2;

  //
  //first clear the header area.
  //
  tST->ConOut->SetAttribute (tST->ConOut,EFI_MENUPAGE_HEADER_BGCOLOR);
  for (Index = 0; Index < X1 - X0 + 1; Index++) {
    Buffer[Index] = L' ';
  }
  Buffer[Index] = L'\0';
  for (Index = 0; Index < Y1 - Y0 + 1; Index++) {
    Status = TestPrintAt (X0, Y0 + Index, Buffer);
    if (EFI_ERROR (Status)) {
      break;
    }
  }
  if( EFI_ERROR (Status)) {
    return Status;
  }

  if (MenuPage->HasHeader) {
    if (MenuPage->Header.HeaderString.Text == NULL) {
      return EFI_SUCCESS;
    }

    //
    //now we only support one line Head Name String to be displayed.
    //
    if (SctStrLen (MenuPage->Header.HeaderString.Text) > (X1 - X0 + 1)) {
      MenuPage->Header.HeaderString.Text[X1 - X0 + 1] = L'\0';
    }
    switch (MenuPage->Header.HeaderString.Align) {
      case  EFI_ALIGNMENT_LEFT:
        Xpos = MenuPage->Header.HeaderRect.TopLeft.Col;
        break;
      case  EFI_ALIGNMENT_RIGHT:
        Xpos = X1 - SctStrLen (MenuPage->Header.HeaderString.Text) + 1;
        break;
      default:
        Xpos = (X1 + X0 + 1) / 2 - SctStrLen (MenuPage->Header.HeaderString.Text) / 2;
        break;
    }

    Status = tST->ConOut->SetAttribute (
                   tST->ConOut,
                   EFI_MENUPAGE_HEADER_FORECOLOR | EFI_MENUPAGE_HEADER_BGCOLOR
                   );

    if (!EFI_ERROR(Status) ) {
      Status = TestPrintAt (Xpos, Ypos, (MenuPage->Header.HeaderString.Text));
    }
  }
  return Status;

 }

EFI_STATUS
MenuBodyRefresh (
  IN EFI_MENU_PAGE      *MenuPage
  )
/*++

Routine Description:

  refresh the menupage body.

Arguments:

  MenuPage              - whose body to be refreshed.

Returns:

  EFI_SUCCESS           - the menupage body was refreshed successfully.
  EFI_INVALID_PARAMETER

--*/
{
  UINTN               Index;
  CHAR16              Buffer[EFI_MAX_LINE_LENGTH+1];
  UINTN               X0;
  UINTN               Y0;
  UINTN               X1;
  UINTN               Y1;
  UINTN               X2;
  UINTN               Y2;
  EFI_STATUS          Status;
  EFI_MENU_ITEM       *MenuItem;

  if (MenuPage==NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  //initialize local varibles
  //

  X0 = MenuPage->Body.BodyRect.TopLeft.Col;
  Y0 = MenuPage->Body.BodyRect.TopLeft.Row;
  X1 = MenuPage->Body.BodyRect.BottomRight.Col;
  Y1 = MenuPage->Body.BodyRect.BottomRight.Row;
  X2 = MenuPage->Body.SplitPoint.Col;
  Y2 = MenuPage->Body.SplitPoint.Row;

  MenuItem   = NULL;
  Status = EFI_SUCCESS;

  //
  //disable cursor before print
  //
  tST->ConOut->EnableCursor (tST->ConOut, FALSE);
  if (MenuPage->HasBody) {

    //
    //first clear the body  area
    //
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_ITEM_EDIT_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );
    for (Index = 0; Index < (X1 - X0 + 1); Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';
    for(Index = Y0; Index <= Y1; Index++) {
      Status = TestPrintAt (X0, Index, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }

    //
    //then draw the four  corner.
    //
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_MENUPAGE_ITEM_COMMON_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );

    Buffer[1] = L'\0';
    Buffer[0] = BOXDRAW_DOWN_RIGHT;
    Status = TestPrintAt (X0, Y0, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    Buffer[0] = BOXDRAW_UP_RIGHT;
    Status = TestPrintAt (X0, Y1, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    Buffer[0] = BOXDRAW_DOWN_LEFT;
    Status = TestPrintAt (X1, Y0, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    Buffer[0] = BOXDRAW_UP_LEFT;
    Status = TestPrintAt (X1, Y1, Buffer);
    if (EFI_ERROR (Status) ) {
      return Status;
    }

    //
    //draw  left-right line.
    //
    Buffer[0] = BOXDRAW_HORIZONTAL;
    for  (Index = X0 + 1; Index < X1; Index++) {
      Status = TestPrintAt (Index, Y0, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      Status = TestPrintAt (Index, Y2, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      Status = TestPrintAt (Index, Y1, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
    //
    //draw  up-down line.
    //
    Buffer[0] = BOXDRAW_VERTICAL;
    for (Index = Y0 + 1; Index < Y1; Index++) {
      Status = TestPrintAt (X0, Index, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
      Status = TestPrintAt (X2, Index, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
      Status = TestPrintAt (X1, Index, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
    }

    //
    //draw the  other  corner.
    //
    Buffer[0] = BOXDRAW_VERTICAL_RIGHT;
    Status = TestPrintAt (X0, Y2, Buffer);
    if (EFI_ERROR (Status) ) {
        return Status;
    }
    Buffer[0] = BOXDRAW_VERTICAL_LEFT;
    Status = TestPrintAt (X1, Y2, Buffer);
    if (EFI_ERROR (Status) ) {
        return Status;
    }
    Buffer[0] = BOXDRAW_DOWN_HORIZONTAL;
    Status = TestPrintAt (X2, Y0, Buffer);
    if (EFI_ERROR (Status) ) {
        return Status;
    }
    Buffer[0] = BOXDRAW_UP_HORIZONTAL;
    Status = TestPrintAt (X2, Y1, Buffer);
    if (EFI_ERROR (Status) ) {
        return Status;
    }
    Buffer[0] = BOXDRAW_VERTICAL_HORIZONTAL;
    Status = TestPrintAt (X2, Y2, Buffer);
    if (EFI_ERROR (Status) ) {
        return Status;
    }

    //
    //print  the  item header.
    //
    if (MenuPage->Body.MenuItemHeader.Text != NULL) {
      tST->ConOut->SetAttribute (
            tST->ConOut,
            EFI_MENUPAGE_ITEM_COMMON_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
            );
      if(SctStrLen (MenuPage->Body.MenuItemHeader.Text) > X2 -X0 - 1) {
        MenuPage->Body.MenuItemHeader.Text[ X2 - X0 - 1] = L'\0';
      }

      switch (MenuPage->Body.MenuItemHeader.Align) {
        case EFI_ALIGNMENT_LEFT:
          Status = TestPrintAt (
                     X0 + 1,
                     (Y0 + Y2) / 2,
                     MenuPage->Body.MenuItemHeader.Text
                     );
          break;
        case EFI_ALIGNMENT_RIGHT:
          Status = TestPrintAt (
                     X2 -1 - SctStrLen (MenuPage->Body.MenuItemHeader.Text),
                     (Y0 + Y2) / 2,
                     MenuPage->Body.MenuItemHeader.Text
                     );
          break;
        default:
          Status = TestPrintAt (
                    (X2 + X0) / 2 - SctStrLen (MenuPage->Body.MenuItemHeader.Text) / 2,
                    (Y0 + Y2)/ 2,
                    MenuPage->Body.MenuItemHeader.Text
                    );
          break;
      }
      if (EFI_ERROR (Status) ) {
        return Status;
      }
    }

    //
    //print the Description header.
    //
    if (MenuPage->Body.DescriptionHeader.Text != NULL) {
      tST->ConOut->SetAttribute (
            tST->ConOut,
            EFI_ITEM_DESC_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
            );
      if (SctStrLen (MenuPage->Body.DescriptionHeader.Text) > X1 - X2 - 1) {
        MenuPage->Body.DescriptionHeader.Text[X1 - X2 - 1] = L'\0';
      }
      switch (MenuPage->Body.DescriptionHeader.Align)   {
        case EFI_ALIGNMENT_LEFT:
          Status = TestPrintAt (
                     X2 + 1,
                     (Y0 + Y2) / 2,
                     MenuPage->Body.DescriptionHeader.Text
                     );
          break;
        case EFI_ALIGNMENT_RIGHT:
          Status = TestPrintAt (
                     X1 -1 - SctStrLen (MenuPage->Body.DescriptionHeader.Text),
                     (Y0 + Y2) / 2,
                     MenuPage->Body.DescriptionHeader.Text
                     );
          break;
        default:
          Status = TestPrintAt (
                     (X2 + X1) / 2 - SctStrLen (MenuPage->Body.DescriptionHeader.Text) / 2,
                     (Y0 + Y2) / 2,
                     MenuPage->Body.DescriptionHeader.Text
                     );
          break;
      }
      if (EFI_ERROR(Status)) {
        return Status;
      }
    }

    //
    //if there is no menu item then return EFI_SUCCESS
    //
    if (MenuPage->Body.CurrentSelected == NULL||
        MenuPage->Body.ItemList == NULL) {
      return EFI_SUCCESS;
    }

    //
    //set the default poiter if has not been set.
    //
    if (MenuPage->Body.FirstInDisplay == NULL) {
      MenuPage->Body.FirstInDisplay = MenuPage->Body.ItemList;
    }

    //
    //Set the LastInDisplay pointer on first time display.
    //
    if (MenuPage->Body.LastInDisplay == NULL) {
      Index = 0;
      MenuItem = MenuPage->Body.FirstInDisplay;
      if (MenuItem) {
        Index += (MenuItem->Skip + 1);
        while (MenuItem->Next != NULL && Index<( Y1 - Y2 - 1)) {
          MenuItem = MenuItem->Next;
          Index += (MenuItem->Skip + 1);
        }
      }
      MenuPage->Body.LastInDisplay = MenuItem;
    }

    //
    //at last display the menu items.
    //
    Status = MenuBodyItemsRefresh (MenuPage);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    if (MenuPage->Body.CurrentSelected != NULL) {

      Index = 0;
      MenuItem  = MenuPage->Body.FirstInDisplay;
      while (MenuItem != MenuPage->Body.CurrentSelected) {
        Index += (MenuItem->Skip + 1);
        MenuItem = MenuItem->Next;
      }
      Index++;

      //
      //White color is better
      //
      tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR >> 4
              );
      if (MENU_ITEM_TYPE (MenuPage->Body.CurrentSelected->ItemType) == EFI_ITEM_CASE) {
        tST->ConOut->EnableCursor (tST->ConOut, TRUE);
        tST->ConOut->SetCursorPosition(
                    tST->ConOut,
                    MenuPage->Body.BodyRect.TopLeft.Col + EFI_ITEM_TYPE_TAG_LENGTH + 2 + EFI_MAX_CASE_ITEM_NAME_LENGTH,
                    MenuPage->Body.SplitPoint.Row + Index
                    );
      }
      if (MENU_ITEM_TYPE (MenuPage->Body.CurrentSelected->ItemType) == EFI_ITEM_HAVE_EDIT) {
        tST->ConOut->EnableCursor (tST->ConOut, TRUE);
        tST->ConOut->SetCursorPosition(
                    tST->ConOut,
                    MenuPage->Body.SplitPoint.Col - 22,
                    MenuPage->Body.SplitPoint.Row + Index
                    );
      }

    }
  }

  if (gMenuPage == MenuPage && !(MenuPage->HasBody)) {

    for(Index = 0;Index < (X1 - X0 + 1); Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_TEXT_ATTR (MenuPage->Body.ForeColor, MenuPage->BackColor)
          );

    for(Index = Y0; Index <= Y1; Index++) {
      Status = TestPrintAt (X0, Index, Buffer);
      if(EFI_ERROR (Status) ) {
        return Status;
      }
    }
  }
  //
  //done successfully return EFI_SUCCESS
  //
  return  EFI_SUCCESS;
}

EFI_STATUS
MenuFooterRefresh (
  IN EFI_MENU_PAGE      *MenuPage
  )
/*++

Routine Description:

  refresh the menupage footer.

Arguments:

  MenuPage              - whose footer to be refreshed.

Returns:

  EFI_SUCCESS           - the menupage footer was refreshed successfully.
  EFI_INVALID_PARAMETER

--*/
{
  UINTN                X0;
  UINTN                Y0;
  UINTN                X1;
  UINTN                Y1;
  UINTN                Lines;
  UINTN                Columns;
  UINTN                Xpos;
  UINTN                Ypos;
  EFI_HOT_KEY          *HotKey;
  EFI_STATUS           Status;
  CHAR16               Buffer[EFI_MAX_LINE_LENGTH+1];
  UINTN                Index;


  if (MenuPage == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  //initialize local variables
  //

  X0 = MenuPage->Footer.FooterRect.TopLeft.Col;
  Y0 = MenuPage->Footer.FooterRect.TopLeft.Row;
  X1 = MenuPage->Footer.FooterRect.BottomRight.Col;
  Y1 = MenuPage->Footer.FooterRect.BottomRight.Row;
  Lines   = Y1-Y0+1;
  Columns = X1-X0+1;
  Xpos = X0;
  Ypos = Y0;

  Status = EFI_SUCCESS;

  //
  //clear footer area.
  //
  for(Index = 0; Index < X1 - X0; Index++) {
    Buffer[Index] = L' ';
  }
  Buffer[Index] = L'\0';

  tST->ConOut->SetAttribute (tST->ConOut, EFI_MENUPAGE_FOOTER_BGCOLOR);

  for  (Index = 0; Index < Lines; Index++) {
    Status = TestPrintAt (X0, Y0 + Index, Buffer);
    if(EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (MenuPage->HasFooter) {

    HotKey = MenuPage->Footer.HotKeyList;

    if (HotKey == NULL) {
      return EFI_SUCCESS;
    }
    while (HotKey != NULL && HotKey->Visible == FALSE) {
      HotKey = HotKey->Next;
    }
    while(HotKey != NULL) {

      Ypos = Y0;
      if ((Xpos + EFI_HOTKEY_NAME_SPAN + EFI_HOTKEY_DESC_SPAN - 1) > X1) {
        break;
      }

      for (Index = 0; Index < Lines; Index ++ ) {
        if (HotKey == NULL) {
          break;
        }

        //
        //first draw HotKeyName
        //
        tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_FOOTER_HOTKEY_FORECOLOR | EFI_MENUPAGE_FOOTER_BGCOLOR
              );
        if (SctStrLen (HotKey->HotKeyName.Text) > EFI_HOTKEY_NAME_SPAN) {
          HotKey->HotKeyName.Text[EFI_HOTKEY_NAME_SPAN] = L'\0';
        }
        TestPrintAt (Xpos, Ypos, HotKey->HotKeyName.Text);

        Xpos = Xpos + EFI_HOTKEY_NAME_SPAN;

        //
        //then draw HotKeyDesc
        //
        tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_FOOTER_DESC_FORECOLOR | EFI_MENUPAGE_FOOTER_BGCOLOR
              );
        if (SctStrLen (HotKey->HotKeyDesc.Text) > EFI_HOTKEY_DESC_SPAN) {
          HotKey->HotKeyDesc.Text[EFI_HOTKEY_DESC_SPAN] = L'\0';
        }
        Status = TestPrintAt (Xpos, Ypos, HotKey->HotKeyDesc.Text);
        if (EFI_ERROR (Status) ) {
          return Status;
        }

        Xpos    = Xpos - EFI_HOTKEY_NAME_SPAN;
        HotKey  = HotKey->Next;
        while (HotKey != NULL && HotKey->Visible == FALSE) {
          HotKey = HotKey->Next;
        }
        Ypos    = Ypos + 1;
      }

      Xpos = Xpos + EFI_HOTKEY_NAME_SPAN + EFI_HOTKEY_DESC_SPAN;
    }
  }
  //
  //set default MenuPage Console attribute
  //
  tST->ConOut->SetAttribute (tST->ConOut, EFI_BACKGROUND_BLACK | EFI_WHITE);
  return Status;
}

EFI_STATUS
MenuBodyItemsRefresh (
  IN EFI_MENU_PAGE      *MenuPage
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
{
  UINTN                 Index;
  CHAR16                Buffer[EFI_MAX_LINE_LENGTH+1];
  UINTN                 X0;
  UINTN                 X1;
  UINTN                 Y1;
  UINTN                 X2;
  UINTN                 Y2;
  EFI_STATUS            Status;
  EFI_MENU_ITEM         *MenuItem;

  if (MenuPage == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (MenuPage->Body.CurrentSelected == NULL ||
      MenuPage->Body.ItemList == NULL) {
    return EFI_SUCCESS;
  }

  //
  //initialize local variables
  //
  MenuItem = NULL;

  X0 = MenuPage->Body.BodyRect.TopLeft.Col;
  X1 = MenuPage->Body.BodyRect.BottomRight.Col;
  Y1 = MenuPage->Body.BodyRect.BottomRight.Row;
  X2 = MenuPage->Body.SplitPoint.Col;
  Y2 = MenuPage->Body.SplitPoint.Row;

  Status = EFI_SUCCESS;

  //
  //disable cursor before print
  //
  tST->ConOut->EnableCursor (tST->ConOut, FALSE);
  if (MenuPage->HasBody) {
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_ITEM_EDIT_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );
    for(Index = 0; Index < ( X2 - X0 - 1); Index++) {
      Buffer[Index] = L' ';
    }
    if (MenuPage->Body.HasScrollBar) {
      Buffer[Index - 1] = L'\0';
    }
    Buffer[Index] = L'\0';

    //
    //clear the menu item area.
    //
    for(Index = Y2+ 1; Index < Y1; Index++) {
      Status = TestPrintAt (X0 + 1, Index, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
    }
    if ( MenuPage->Body.SplitPoint.Col != 0 ) {
      for (Index = 0; Index < (X1 - X2 - 1); Index++) {
        Buffer[Index] = L' ';
      }
      Buffer[Index] = L'\0';

      //
      //clear the description area.
      //
      for (Index = Y2 + 1; Index < Y1; Index++) {
        Status = TestPrintAt (X2 + 1, Index, Buffer);
        if (EFI_ERROR (Status) ) {
          return Status;
        }
      }
    }

    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_MENUPAGE_ITEM_COMMON_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );
    //
    //refresh scroll bar.
    //
    if (MenuPage->Body.HasScrollBar) {
      MenuItem = MenuPage->Body.ItemList;
      Index = 0;
      while(MenuItem != MenuPage->Body.FirstInDisplay) {
        Index++;
        Index   += MenuItem->Skip;
        MenuItem = MenuItem->Next;
      }
      Status = SetScrollBarPos (MenuPage->Body.ScrollBar, Index);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }

    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_MENUPAGE_ITEM_COMMON_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );
    MenuItem = MenuPage->Body.FirstInDisplay;

    while  (MenuItem != NULL && MenuItem != MenuPage->Body.LastInDisplay->Next) {
      MenuItemRefresh (MenuPage, MenuItem, FALSE);
      MenuItem = MenuItem->Next;
    }

    //
    //call  the  selected item's  desc print function.
    //
    if (MenuPage->Body.CurrentSelected != NULL &&
        MenuPage->Body.CurrentSelected->DescPrint != NULL) {
      Status = MenuPage->Body.CurrentSelected->DescPrint(
                                                 MenuPage->Body.CurrentSelected,
                                                 (void *)MenuPage,
                                                 Y2 + 1,
                                                 X2 + 1
                                                 );
      if (EFI_ERROR (Status) ) {
        return Status;
      }
    } else if (MenuPage->Body.CurrentSelected != NULL) {
      Status = DefaultDescPrint(
                 MenuPage->Body.CurrentSelected,
                 (void *)MenuPage,
                 Y2 + 1,
                 X2 + 1
                 );
      if (EFI_ERROR (Status) ) {
        return Status;
      }
    }
  }
  //
  //set the cursor if current selected item type is EFI_ITEM_HAVE_EDIT.
  //
  if (MenuPage->Body.CurrentSelected != NULL) {

    Index = 0;
    MenuItem  = MenuPage->Body.FirstInDisplay;
    while (MenuItem != MenuPage->Body.CurrentSelected) {
      Index     += (MenuItem->Skip+1);
      MenuItem   = MenuItem->Next;
    }
    Index++;

    //
    //White color is better
    //
    tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
              );
    if (MENU_ITEM_TYPE (MenuPage->Body.CurrentSelected->ItemType) == EFI_ITEM_CASE) {
      tST->ConOut->EnableCursor (tST->ConOut, TRUE);
      tST->ConOut->SetCursorPosition(
                    tST->ConOut,
                    MenuPage->Body.BodyRect.TopLeft.Col + EFI_ITEM_TYPE_TAG_LENGTH + 2 + EFI_MAX_CASE_ITEM_NAME_LENGTH,
                    MenuPage->Body.SplitPoint.Row + Index
                    );
    }
    if (MENU_ITEM_TYPE (MenuPage->Body.CurrentSelected->ItemType) == EFI_ITEM_HAVE_EDIT) {
      tST->ConOut->EnableCursor (tST->ConOut, TRUE);
      tST->ConOut->SetCursorPosition(
                    tST->ConOut,
                    MenuPage->Body.SplitPoint.Col - 22,
                    MenuPage->Body.SplitPoint.Row + Index
                    );
    }
  }
  return Status;
}

EFI_STATUS
MenuItemRefresh (
  IN EFI_MENU_PAGE      *MenuPage,
  IN EFI_MENU_ITEM      *Item,
  IN BOOLEAN            DisplayDesc
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
  EFI_INVALID_PARAMETER - on of the parameter is invalid.

--*/
{
  EFI_STATUS             Status;
  EFI_MENU_ITEM          *MenuItem;
  UINTN                  X0;
  UINTN                  X2;
  UINTN                  Y2;
  UINTN                  Attrib;
  UINTN                  Ypos;
  UINTN                  Index;
  CHAR16                 Buffer[EFI_MAX_LINE_LENGTH+1];
  EFI_SCT_TEST_NODE      *TestNode;
  UINTN                  Passes;
  UINTN                  Failures;

  if (MenuPage == NULL ||Item == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  //initialize local variables
  //
  Status  = EFI_SUCCESS;
  X0      = MenuPage->Body.BodyRect.TopLeft.Col;
  Y2      = MenuPage->Body.SplitPoint.Row;

  if (MenuPage->Body.SplitPoint.Col > 0) {
    X2 = MenuPage->Body.SplitPoint.Col;
  } else {
    X2 = MenuPage->Body.BodyRect.BottomRight.Col;
  }

  MenuItem = MenuPage->Body.FirstInDisplay;
  //
  //caculate Item offset in menu
  //
  Index   = 0;
  while (MenuItem != NULL && MenuItem != Item) {
    Index ++;
    Index   += MenuItem->Skip;
    MenuItem = MenuItem->Next;
  }
  Index++;

  if (MenuPage->Body.SplitPoint.Row > 0) {
    Ypos = MenuPage->Body.SplitPoint.Row + Index;
  } else {
    Ypos = MenuPage->Body.BodyRect.TopLeft.Row + Index;
  }

  MenuItem = Item;
  if (MenuItem == MenuPage->Body.CurrentSelected) {
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );
  } else {
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_MENUPAGE_ITEM_COMMON_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );
  }
  //
  //disable cursor before print.
  //
  tST->ConOut->EnableCursor (tST->ConOut, FALSE);
  switch (MENU_ITEM_TYPE (MenuItem->ItemType)) {
    case EFI_ITEM_HAVE_SUBITEMS:
      //
      //draw right triangle.
      //
      Buffer[0] = GEOMETRICSHAPE_RIGHT_TRIANGLE;
      Buffer[1] = L'\0';
      Status = TestPrintAt (X0 + 3, Ypos, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
      break;

    case EFI_ITEM_HAVE_POPUP :

      //
      //print Item Value
      //
      if (MenuItem->ItemValue != NULL) {
        if (SctStrLen ((CHAR16 *)MenuItem->ItemValue) <= 20) {
          Status = TestPrintAt (X2 -22, Ypos, (CHAR16  *)MenuItem->ItemValue);
        } else {
          for  (Index = 0; Index < 20; Index++) {
            Buffer[Index] = MenuItem->ItemValue[Index];
          }
          Buffer[Index]=L'\0';
          Status = TestPrintAt (X2 - 22, Ypos, Buffer);
        }
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }

      break;

    case EFI_ITEM_HAVE_EDIT:

      if (MenuItem == MenuPage->Body.CurrentSelected) {
        tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_ITEM_EDIT_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
              );
      }
      //
      //draw "[" and "]"
      //
      Status = TestPrintAt (X2 - 23, Ypos, L"[");
      if (EFI_ERROR (Status) ) {
        return Status;
      }
      Status = TestPrintAt (X2 - 2, Ypos, L"]");
      if (EFI_ERROR (Status) ) {
        return Status;
      }

      if (MenuItem->ItemValue) {
        //
        //clear the area
        //
        for  (Index = 0; Index < 20; Index++) {
          Buffer[Index] = ' ';
        }
        Buffer[Index] = L'\0';
        Status = TestPrintAt (X2 - 22, Ypos, Buffer);
        //
        //display item value.
        //
        if (SctStrLen ((CHAR16 *)MenuItem->ItemValue) < 20) {
          Status = TestPrintAt (X2 - 22, Ypos, MenuItem->ItemValue);
        } else {
          for  (Index = 0; Index < 20; Index++) {
            Buffer[Index] = MenuItem->ItemValue[Index];
          }
          Buffer[Index] = L'\0';
          Status = TestPrintAt (X2 - 22, Ypos, Buffer);
        }
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }
      if (MenuItem == MenuPage->Body.CurrentSelected) {
        tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
              );
      }
      break;

    case EFI_ITEM_HAVE_COMBOLIST:

      for (Index = 0; Index < X2 - X0 - 2; Index++) {
        Buffer[Index] = L' ';
      }
      Buffer[Index] = L'\0';
      Attrib = tST->ConOut->Mode->Attribute;
      tST->ConOut->SetAttribute (
            tST->ConOut,
            EFI_MENUPAGE_BODY_BGCOLOR >>  4 | EFI_MENUPAGE_BODY_BGCOLOR
            );
      TestPrintAt (X0 + 1, Ypos, Buffer);

      tST->ConOut->SetAttribute (tST->ConOut , Attrib);
      //
      //draw "[" and "]".
      //
      Status = TestPrintAt (X2 - 23, Ypos, L"[");
      if (EFI_ERROR (Status)) {
        return Status;
      }
      Status = TestPrintAt (X2 - 2 , Ypos, L"]");
      if (EFI_ERROR (Status)) {
        return Status;
      }

      if (MenuItem->ItemValue != NULL) {
         //
        //display Item Value
        //
        if(SctStrLen (MenuItem->ItemValue) <= 20) {
          Status = TestPrintAt (X2 - 22, Ypos, MenuItem->ItemValue);
        } else {
          for  (Index = 0; Index < 20; Index++)  {
            Buffer[Index] = MenuItem->ItemValue[Index];
          }
          Buffer[Index] = L'\0';

          Status = TestPrintAt (X2 - 22, Ypos, Buffer);
        }
        if (EFI_ERROR (Status) ) {
          return Status;
        }
      }

      break;

    case EFI_ITEM_HAVE_CHECKBOX:

      switch ( MenuItem->Status )  {
        case EFI_ITEM_SELECT_NONE:
          Buffer[1] = L' ';
          break;
        case EFI_ITEM_SELECT_SOME:
          Buffer[1] = L'x';
          break;
        case EFI_ITEM_SELECT_ALL:
          Buffer[1] = L'X';
          break;
        default :
          Buffer[1] = L' ';
          break;
      }
      //
      //display "[ ]" or "[X]" or "[x]"
      //
      Buffer[0] = L'[';
      Buffer[2] = L']';
      Buffer[3] = L'\0';
      Status = TestPrintAt (X0 + 2, Ypos, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      break;

    case EFI_ITEM_HAVE_RADIOBOX:

      if (MenuItem->IsSelected) {
        Buffer[0] = L'*';
      } else {
        Buffer[0] = L' ';
      }
      Buffer[1] = L'\0';
      Status = TestPrintAt (X0 + 3, Ypos, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
      break;

    case EFI_ITEM_COMMAND:
      break;

    case EFI_ITEM_CASE:
      //
      // Checkbox related
      //
      switch ( MenuItem->Status )  {
        case EFI_ITEM_SELECT_NONE:
          Buffer[1] = L' ';
          break;
        case EFI_ITEM_SELECT_SOME:
          Buffer[1] = L'x';
          break;
        case EFI_ITEM_SELECT_ALL:
          Buffer[1] = L'X';
          break;
        default :
          Buffer[1] = L' ';
          break;
      }
      //
      //display "[ ]" or "[X]" or "[x]"
      //
      Buffer[0] = L'[';
      Buffer[2] = L']';
      Buffer[3] = L'\0';
      Status = TestPrintAt (X0 + 2, Ypos, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }

      //
      // Editbox related
      //
      if (MenuItem == MenuPage->Body.CurrentSelected) {
        //
        //White color is better
        //
        tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
              );
      }

      for (Index = 0; Index < 20; Index ++) {
        Buffer[Index] = L' ';
      }
      Buffer[12] = L'\0';

      Buffer[0] = L'[';
      Buffer[4] = L']';
      for (Index = 1; Index < 5; Index++) {
        if (Buffer[Index] == 0) {
          Buffer[Index] = L' ';
        }
      }

      TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;

      if (IsTestRunning (TestNode)) {
        SctSPrint (&Buffer[8], MAX_STRING_LEN, L"Test");
      } else {
        Passes = CalculatePassNumber(TestNode); //#Pass
        Failures = CalculateFailNumber(TestNode); //#Fail
        if (Failures > 0) {
          SctSPrint (&Buffer[8], MAX_STRING_LEN, L"FAIL");
        } else if (Passes > 0) {
          SctSPrint (&Buffer[8], MAX_STRING_LEN, L"PASS");
        } else {
          SctSPrint (&Buffer[8], MAX_STRING_LEN, L"    ");
        }
      }
      Status = TestPrintAt (X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1 + EFI_MAX_CASE_ITEM_NAME_LENGTH, Ypos, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }

      if (MenuItem->ItemValue) {
        //
        //display item value.
        //
        if (SctStrLen ((CHAR16 *)MenuItem->ItemValue) < EFI_MAX_CASE_ITEM_VALUE_LENGTH) {
          Status = TestPrintAt (X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1 + EFI_MAX_CASE_ITEM_NAME_LENGTH + 1, Ypos, MenuItem->ItemValue);
        }
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }
      if (MenuItem == MenuPage->Body.CurrentSelected) {
        tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
              );
      }
      break;

    default:

      break;

  }
  //
  //print Item String
  //
  switch (MENU_ITEM_TYPE (MenuItem->ItemType)) {
    case EFI_ITEM_HAVE_EDIT:
    case EFI_ITEM_HAVE_COMBOLIST:
      if (SctStrLen (MenuItem->ItemString.Text) <= EFI_MAX_EDIT_ITEM_NAME_LENGTH) {
        Status = TestPrintAt (
                   X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1,
                   Ypos,
                   MenuItem->ItemString.Text
                   );
      } else {

        tBS->CopyMem (
          Buffer,
          MenuItem->ItemString.Text,
          EFI_MAX_EDIT_ITEM_NAME_LENGTH * sizeof(CHAR16)
          );
        Buffer[EFI_MAX_EDIT_ITEM_NAME_LENGTH] = L'\0';

        Status = TestPrintAt (X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1, Ypos, Buffer);
      }
      if (EFI_ERROR (Status)) {
        return Status;
      }
      break;
    case EFI_ITEM_CASE:
      if (SctStrLen (MenuItem->ItemString.Text) <= EFI_MAX_CASE_ITEM_NAME_LENGTH) {
        Status = TestPrintAt (
                   X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1,
                   Ypos,
                   MenuItem->ItemString.Text
                   );
      } else {

        tBS->CopyMem (
          Buffer,
          MenuItem->ItemString.Text,
          EFI_MAX_CASE_ITEM_NAME_LENGTH * sizeof(CHAR16)
          );
        Buffer[EFI_MAX_CASE_ITEM_NAME_LENGTH] = L'\0';

        Status = TestPrintAt (X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1, Ypos, Buffer);
      }
      if (EFI_ERROR (Status)) {
        return Status;
      }
      break;
    default:
      if (SctStrLen (MenuItem->ItemString.Text) <= EFI_MAX_ITEM_NAME_LENGTH) {
        Status = TestPrintAt (
                   X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1,
                   Ypos,
                   MenuItem->ItemString.Text
                   );
      } else {

        tBS->CopyMem (
          Buffer,
          MenuItem->ItemString.Text,
          (EFI_MAX_ITEM_NAME_LENGTH + 1) * sizeof(CHAR16)
          );
        Buffer[EFI_MAX_ITEM_NAME_LENGTH + 1] = L'\0';

        Status = TestPrintAt (X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1, Ypos, Buffer);
      }
      if (EFI_ERROR (Status)) {
        return Status;
      }
      break;
  }

  if (DisplayDesc) {

    //
    //print item description
    //
    if (MenuItem->DescPrint != NULL) {
      Status = MenuItem->DescPrint (MenuItem, (void *)MenuPage, Y2 + 1, X2 + 1);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
    } else {
      Status = DefaultDescPrint (MenuItem, (void *)MenuPage, Y2 + 1, X2 + 1);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  }
  //
  //if current selected item type is EFI_ITEM_HAVE_EDIT then set the cursor.
  //
  if (MenuPage->Body.CurrentSelected != NULL  &&
      ((MENU_ITEM_TYPE (MenuPage->Body.CurrentSelected->ItemType) == EFI_ITEM_HAVE_EDIT) ||
       (MENU_ITEM_TYPE (MenuPage->Body.CurrentSelected->ItemType) == EFI_ITEM_CASE))) {
//    tST->ConOut->EnableCursor (tST->ConOut, TRUE);

    Index = 0;
    MenuItem = MenuPage->Body.FirstInDisplay;
    while (MenuItem != MenuPage->Body.CurrentSelected) {
      Index    += (MenuItem->Skip + 1);
      MenuItem  = MenuItem->Next;
    }
    Index++;

    //
    //White color is better
    //
    tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
              );
    if (MENU_ITEM_TYPE (MenuPage->Body.CurrentSelected->ItemType) == EFI_ITEM_CASE) {
      tST->ConOut->SetCursorPosition(
                    tST->ConOut,
                    MenuPage->Body.BodyRect.TopLeft.Col + EFI_ITEM_TYPE_TAG_LENGTH + 2 + EFI_MAX_CASE_ITEM_NAME_LENGTH,
                    MenuPage->Body.SplitPoint.Row + Index
                    );
      tST->ConOut->EnableCursor (tST->ConOut, TRUE);
    }
    if (MENU_ITEM_TYPE (MenuPage->Body.CurrentSelected->ItemType) == EFI_ITEM_HAVE_EDIT) {
      tST->ConOut->SetCursorPosition(
                    tST->ConOut,
                    MenuPage->Body.SplitPoint.Col - 22,
                    MenuPage->Body.SplitPoint.Row + Index
                    );
      tST->ConOut->EnableCursor (tST->ConOut, TRUE);
    }
  }
  return Status;
}

EFI_STATUS
MenuItemStatusRefresh (
  IN EFI_MENU_PAGE      *MenuPage,
  IN EFI_MENU_ITEM      *Item,
  IN BOOLEAN            DisplayDesc
  )
/*++

Routine Description:

  refresh the status display of one case item in the body.

Arguments:

  MenuPage              - whose body's menu item to be refreshed.
  Item                  - the item to be refreshed.

Returns:

  EFI_SUCCESS           - the item was refreshed successfully.
  EFI_INVALID_PARAMETER - on of the parameter is invalid.

--*/
{
  EFI_STATUS             Status;
  EFI_MENU_ITEM          *MenuItem;
  UINTN                  X0;
  UINTN                  X2;
  UINTN                  Y2;
  UINTN                  Ypos;
  UINTN                  Index;
  CHAR16                 Buffer[EFI_MAX_LINE_LENGTH+1];
  EFI_SCT_TEST_NODE      *TestNode;
  UINTN                  Passes;
  UINTN                  Failures;

  if (MenuPage == NULL ||Item == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  //initialize local variables
  //
  Status  = EFI_SUCCESS;
  X0      = MenuPage->Body.BodyRect.TopLeft.Col;
  Y2      = MenuPage->Body.SplitPoint.Row;

  if (MenuPage->Body.SplitPoint.Col > 0) {
    X2 = MenuPage->Body.SplitPoint.Col;
  } else {
    X2 = MenuPage->Body.BodyRect.BottomRight.Col;
  }

  MenuItem = MenuPage->Body.FirstInDisplay;
  //
  //caculate Item offset in menu
  //
  Index   = 0;
  while (MenuItem != NULL && MenuItem != Item) {
    Index ++;
    Index   += MenuItem->Skip;
    MenuItem = MenuItem->Next;
  }
  Index++;

  if (MenuPage->Body.SplitPoint.Row > 0) {
    Ypos = MenuPage->Body.SplitPoint.Row + Index;
  } else {
    Ypos = MenuPage->Body.BodyRect.TopLeft.Row + Index;
  }

  MenuItem = Item;
  if (MenuItem == MenuPage->Body.CurrentSelected) {
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );
  } else {
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_MENUPAGE_ITEM_COMMON_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
          );
  }

  switch (MENU_ITEM_TYPE (MenuItem->ItemType)) {

    case EFI_ITEM_CASE:
      //
      // Test Case related
      //
      switch ( MenuItem->Status )  {
        case EFI_ITEM_SELECT_NONE:
          Buffer[1] = L' ';
          break;
        case EFI_ITEM_SELECT_SOME:
          Buffer[1] = L'x';
          break;
        case EFI_ITEM_SELECT_ALL:
          Buffer[1] = L'X';
          break;
        default :
          Buffer[1] = L' ';
          break;
      }

      //
      //display "[ ]" or "[X]" or "[x]"
      //
      Buffer[0] = L'[';
      Buffer[2] = L']';
      Buffer[3] = L'\0';
      Status = TestPrintAt (X0 + 2, Ypos, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
            for (Index = 0; Index < 20; Index ++) {
        Buffer[Index] = L' ';
      }
      Buffer[12] = L'\0';

      //
      //Display test results
      //
      Buffer[0] = L'[';
      Buffer[4] = L']';
      for (Index = 1; Index < 5; Index++) {
        if (Buffer[Index] == 0) {
          Buffer[Index] = L' ';
        }
      }

      TestNode = (EFI_SCT_TEST_NODE*)MenuItem->Context;

      if (IsTestRunning (TestNode)) {
        SctSPrint (&Buffer[8], MAX_STRING_LEN, L"Test");
      } else {
        Passes = CalculatePassNumber(TestNode); //#Pass
        Failures = CalculateFailNumber(TestNode); //#Fail
        if (Failures > 0) {
          SctSPrint (&Buffer[8], MAX_STRING_LEN, L"FAIL");
        } else if (Passes > 0) {
          SctSPrint (&Buffer[8], MAX_STRING_LEN, L"PASS");
        } else {
          SctSPrint (&Buffer[8], MAX_STRING_LEN, L"    ");
        }
      }
      Status = TestPrintAt (X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1 + EFI_MAX_CASE_ITEM_NAME_LENGTH, Ypos, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      if (MenuItem->ItemValue) {
        //
        //display item value.
        //
        if (SctStrLen ((CHAR16 *)MenuItem->ItemValue) < EFI_MAX_CASE_ITEM_VALUE_LENGTH) {
          Status = TestPrintAt (X0 + EFI_ITEM_TYPE_TAG_LENGTH + 1 + EFI_MAX_CASE_ITEM_NAME_LENGTH + 1, Ypos, MenuItem->ItemValue);
        }
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }

      if (DisplayDesc) {

        //
        //print item description
        //
        if (MenuItem->DescPrint != NULL) {
          Status = MenuItem->DescPrint (MenuItem, (void *)MenuPage, Y2 + 1, X2 + 1);
          if (EFI_ERROR (Status) ) {
            return Status;
          }
        } else {
          Status = DefaultDescPrint (MenuItem, (void *)MenuPage, Y2 + 1, X2 + 1);
          if (EFI_ERROR (Status)) {
            return Status;
          }
        }
        tST->ConOut->SetAttribute (
              tST->ConOut,
              EFI_MENUPAGE_ITEM_SELECTED_FORECOLOR | EFI_MENUPAGE_BODY_BGCOLOR
              );
      }
      break;
    default:
      return EFI_INVALID_PARAMETER;
  }
  return Status;
}

EFI_STATUS
MenuPageRefresh (
  IN EFI_MENU_PAGE      *MenuPage
  )
/*++

Routine Description:

  refresh the total menupage.

Arguments:

  MenuPage              - which menu page to be refreshed.

Returns:

  EFI_SUCCESS           - the menupage  was refreshed successfully.
  EFI_INVALID_PARAMETER

--*/
{
  EFI_STATUS Status;

  if (MenuPage == NULL)  {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;
  //
  //set default Console Attribute and clear the screen
  //
  tST->ConOut->SetAttribute (tST->ConOut, EFI_BACKGROUND_BLACK | EFI_WHITE);
  tST->ConOut->ClearScreen (tST->ConOut);

  //
  //refesh header
  //
  MenuHeaderRefresh (MenuPage);

  //
  //refresh footer
  //
  Status = MenuFooterRefresh (MenuPage);

  //
  //refresh body
  //
  Status = MenuBodyRefresh (MenuPage);


  if (gMenuPage != MenuPage) {
    gMenuPage = MenuPage;
  }

  return Status;

}

EFI_STATUS
InitializeTestFrameworkUi (
  INTN *Mode
  )
/*++

Routine Description:

  UI initialize function,save current Output Console attribute.

Returns:

  EFI_SUCCESS - The initialize has been done successfully.
  Other       - error condition.

--*/
{
    //
    //save console current attributes
    //
    gMode      = *Mode;

    gConAttrib = tST->ConOut->Mode->Attribute;
    gMenuPage  = NULL;
    gMenuExit  = FALSE;
    //
    //disable cursor
    //
    tST->ConOut->EnableCursor (tST->ConOut,FALSE);
    tST->ConOut->ClearScreen (tST->ConOut);
    return EFI_SUCCESS;
}

EFI_STATUS
TestFrameworkUiRestore (
  VOID
  )
/*++

Routine Description:

  restore the original output console attribute.

Returns:

  EFI_SUCCESS - The output console was restored successfully.
  Other       - error condition.

--*/
{
  //
  //restore console Attribute
  //
  if (tST->ConOut->Mode->Attribute != gConAttrib) {
    tST->ConOut->SetAttribute (tST->ConOut, gConAttrib);
  }

  //
  //restore console cursor
  //
  tST->ConOut->EnableCursor (tST->ConOut, TRUE);

  //
  //restore console display mode
  //
  if (gMode != tST->ConOut->Mode->Mode) {
    tST->ConOut->SetMode (tST->ConOut, (UINTN)gMode);
  }
  tST->ConOut->ClearScreen (tST->ConOut);
  return EFI_SUCCESS;
}

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
{
   tST->ConOut->SetAttribute (tST->ConOut, gConAttrib);
   tST->ConOut->ClearScreen (tST->ConOut);
   tST->ConOut->EnableCursor (tST->ConOut, TRUE);
   return EFI_SUCCESS;
}
