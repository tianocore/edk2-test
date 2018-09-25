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

  Dialog.c

Abstract:

  This file provides the Dialog services

--*/

#include "Sct.h"
#include "UI.h"
#include "Dialog.h"

//
//File Type Info definition
//

//
// protypes (external)
//

EFI_STATUS
DoDialog (
  IN CHAR16                        *DialogTitle,
  IN OUT EFI_DIALOG_CONTEXT        *DialogContext
  );

EFI_STATUS
FreeDialog (
  IN EFI_DIALOG  *Dialog
  );

EFI_STATUS
DialogRefresh (
  IN EFI_DIALOG                     *Dialog,
  IN EFI_DIALOG_CONTEXT             *Context,
  IN BOOLEAN                        RefreshAll
);

EFI_STATUS
FreeDialog (
  IN EFI_DIALOG  *Dialog
  )
/*++

Routine Description:

  Free file system Dialog Items and relative Context.

Arguments:

  Dialog      - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS - the resource was freed successfully.

--*/
{
  //
  //at last free the Dialog
  //
  tBS->FreePool (Dialog);
  return EFI_SUCCESS;
}

EFI_STATUS
DialogRefresh (
  IN EFI_DIALOG                     *Dialog,
  IN EFI_DIALOG_CONTEXT             *Context,
  IN BOOLEAN                        RefreshAll
  )
/*++

Routine Description:

  refresh the Dialog.

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS           - the FileDialog was rendered successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid

--*/
{
  UINTN                                  Index;
  UINTN                                  SubIndex;
  CHAR16                                 Buffer[EFI_MAX_LINE_LENGTH +1 ];
  UINTN                                  X0;
  UINTN                                  Y0;
  UINTN                                  X1;
  UINTN                                  Y1;

  EFI_STATUS                             Status;


  if (Dialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (Context == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  X0 = Dialog->BodyRect.TopLeft.Col;
  Y0 = Dialog->BodyRect.TopLeft.Row;
  X1 = Dialog->BodyRect.BottomRight.Col;
  Y1 = Dialog->BodyRect.BottomRight.Row;

  if ((X1 < X0 + 15) || (Y1 < Y0 + 5)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;
  tST->ConOut->EnableCursor (
                tST->ConOut,
                FALSE
                );
  tST->ConOut->SetAttribute (
                tST->ConOut,
                EFI_TEXT_ATTR(Dialog->ForeColor,
                Dialog->BackColor)
                );

  if (RefreshAll) {

    for (Index = 0; Index < X1 - X0 + 1; Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';
    //
    //clear the Dialog Rect Area.
    //
    for (SubIndex = Y0; SubIndex <= Y1; SubIndex++) {
      Status = TestPrintAt (X0, SubIndex, Buffer);
      if (EFI_ERROR(Status)) {
        return Status;
      }
    }
    //
    //display the title
    //
    if (Dialog->Title != NULL) {
      Status = DisplayMessage(X0 + 4, Y0 + 1, X1 - 3, Y1 - 4, Dialog->Title);
    }
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    // than we draw the four corner.
    //
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
    for (Index = 0; Index < X1 - X0 - 1; Index++) {
      Buffer[Index] = BOXDRAW_HORIZONTAL;
    }
    Buffer[Index] = L'\0';

    Status = TestPrintAt (X0 + 1, Y0, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    Status = TestPrintAt (X0 + 1 , Y1, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    //draw  up-down line.
    //

    Buffer[0] = BOXDRAW_VERTICAL;
    Buffer[1] = L'\0';
    for (Index= Y0 + 1; Index < Y1; Index++) {
      Status = TestPrintAt (X0, Index, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
      Status = TestPrintAt (X1, Index, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
    }

    if (Context->Type == EFI_DIALOG_TYPE_MESSAGE) {
      SctStrCpy (Buffer, L"[ OK ]");
      Status = TestPrintAt (X0 + (X1 - X0) / 2 - 2 , Y1 - 2, Buffer);
    }

    if (Context->Type == EFI_DIALOG_TYPE_YES_OR_NO) {
      if (Context -> ChooseNumber == 1) {
        SctStrCpy (Buffer, L"[ No ]");
        Status = TestPrintAt (X0 + (X1 - X0) / 4 * 3 - 4, Y1 - 2, Buffer);
        if (EFI_ERROR (Status)) {
          return Status;
        }
        tST->ConOut->SetAttribute (
            tST->ConOut,
            EFI_TEXT_ATTR(EFI_YELLOW,
            Dialog->BackColor)
            );
        SctStrCpy (Buffer, L"[ Yes ]");
        Status = TestPrintAt (X0+ (X1 - X0) / 4 - 2, Y1 - 2, Buffer);
        if (EFI_ERROR (Status)) {
          return Status;
        }
        tST->ConOut->SetAttribute (
            tST->ConOut,
            EFI_TEXT_ATTR(Dialog->ForeColor,
            Dialog->BackColor)
            );
      } else {
        SctStrCpy (Buffer, L"[ Yes ]");
        Status = TestPrintAt (X0 + (X1 - X0) / 4 - 2, Y1 - 2, Buffer);
        if (EFI_ERROR (Status)) {
          return Status;
        }
        tST->ConOut->SetAttribute (
            tST->ConOut,
            EFI_TEXT_ATTR(EFI_YELLOW,
            Dialog->BackColor)
            );

        SctStrCpy (Buffer, L"[ No ]");
        Status = TestPrintAt (X0 + (X1 - X0) / 4 * 3 - 4, Y1 - 2, Buffer);
        if (EFI_ERROR (Status)) {
          return Status;
        }
        tST->ConOut->SetAttribute (
            tST->ConOut,
            EFI_TEXT_ATTR(Dialog->ForeColor,
            Dialog->BackColor)
            );
      }
    }

  } else {
    tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_TEXT_ATTR(Dialog->ForeColor,
          Dialog->BackColor)
          );
    if (Context -> ChooseNumber == 1) {
      SctStrCpy (Buffer, L"[ No ]");
      Status = TestPrintAt (X0 + (X1 - X0) / 4 * 3 - 4, Y1 - 2, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_TEXT_ATTR(EFI_YELLOW,
          Dialog->BackColor)
          );
      SctStrCpy (Buffer, L"[ Yes ]");
      Status = TestPrintAt (X0 + (X1 - X0) / 4 - 2 , Y1 - 2, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_TEXT_ATTR(Dialog->ForeColor,
          Dialog->BackColor)
          );
    } else {
      SctStrCpy (Buffer, L"[ Yes ]");
      Status = TestPrintAt (X0 + (X1 - X0) / 4 - 2, Y1 - 2, Buffer);

      if (EFI_ERROR (Status)) {
        return Status;
      }
      tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_TEXT_ATTR(EFI_YELLOW,
          Dialog->BackColor)
          );
      SctStrCpy (Buffer, L"[ No ]");
      Status = TestPrintAt (X0 + (X1 - X0) / 4 * 3 - 4, Y1 - 2, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      tST->ConOut->SetAttribute (
          tST->ConOut,
          EFI_TEXT_ATTR(Dialog->ForeColor,
          Dialog->BackColor)
          );
    }
  }

  return Status;
}

EFI_STATUS
DisplayDialog (
  IN  EFI_DIALOG            *Dialog,
  IN  EFI_DIALOG_CONTEXT    *Context
  )
/*++

Routine Description:

  Display Dialog and response press key.

Arguments:

  Dialog    - The EFI_DIALOG instance pointer.
  Context   - the EFI_DIALOG_CONTEXT instance pointer.

Returns:

  EFI_STATUS.

--*/
{

  EFI_INPUT_KEY             Key;
  EFI_STATUS                Status;
  UINTN                     Index;
  BOOLEAN                   Stopped;
  UINT32                    ChooseNumber;

  if (Dialog == NULL || Context == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  Status  = EFI_SUCCESS;

  //
  //refresh  Dialog
  //
  DialogRefresh (Dialog, Context, TRUE);
  switch (Dialog->Type) {
    case EFI_DIALOG_TYPE_YES_OR_NO:
      ChooseNumber = Context -> ChooseNumber;
      Stopped = FALSE;
      Status = EFI_SUCCESS;
      do {
        //
        //wait for key press event
        //
        Status = tBS->WaitForEvent (1, &(tST->ConIn->WaitForKey), &Index);
        if (EFI_ERROR(Status)) {
          break;
        }

        //
        //read pressed key
        //
        Status = tST->ConIn->ReadKeyStroke (tST->ConIn, &Key);
        if (EFI_ERROR(Status)) {
          break;
        }

        //
        //if there is no item to select wait for press ESC to return.
        //
        switch(Key.ScanCode) {
          case SCAN_UP:
          case SCAN_LEFT:
            //
            // "Yes"
            //
            ChooseNumber = 1;
            Context -> ChooseNumber = ChooseNumber;
            DialogRefresh (Dialog, Context, FALSE);
            break;

          case SCAN_DOWN:
          case SCAN_RIGHT:
            //
            // "No"
            //
            ChooseNumber = 0;
            Context -> ChooseNumber = ChooseNumber;
            DialogRefresh (Dialog, Context, FALSE);
            break;

          case SCAN_ESC:
            ChooseNumber = 0;
            Context -> ChooseNumber = ChooseNumber;
            Stopped = TRUE;
            break;

          case SCAN_NULL:

            switch(Key.UnicodeChar) {
              case CHAR_CARRIAGE_RETURN:
                Context -> ChooseNumber = ChooseNumber;
                Stopped = TRUE;
                break;

              case CHAR_TAB:
                //
                //in Dialog we dont't resonse TAB to Edit the File Name
                //
                break;

              default:
                break;
            }

            //end case SCAN_NULL
            break;

          default:

            break;

        } // end switch ScanCode

      } while (!EFI_ERROR(Status) && !Stopped);
      break;

    case EFI_DIALOG_TYPE_MESSAGE:
      //
      // Need user to press any key
      //
      Status = tBS->WaitForEvent (1, &(tST->ConIn->WaitForKey), &Index);
      Status = tST->ConIn->ReadKeyStroke (tST->ConIn, &Key);
      if (EFI_ERROR(Status)) {
        break;
      }
      break;

    case EFI_DIALOG_TYPE_REMINDER:
      //
      // Just display reminder, no interaction with user
      //
      break;

    default:
      break;
  }
  return Status;
}


EFI_STATUS
DoDialog(
  IN CHAR16                        *DialogTitle,
  IN OUT EFI_DIALOG_CONTEXT        *DialogContext
  )
/*++

Routine Description:

  The entry point to do popup menu.

Arguments:

  DialogContext The FILE_DIALOG_CONTEXT,it contains filter
  filename string.

Returns:

  EFI_SUCCESS.

--*/
{
  EFI_STATUS                      Status;
  EFI_DIALOG                      *Dialog;

  UINTN                           ConAttrib;

  if (DialogContext == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status                = EFI_SUCCESS;

  ConAttrib             = tST->ConOut->Mode->Attribute;
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_DIALOG),
                 (VOID **)&Dialog
                 );
  if (EFI_ERROR(Status)) {
    return EFI_OUT_OF_RESOURCES;
  }
  tBS->SetMem (Dialog, sizeof(EFI_DIALOG), 0);

  Dialog->Type = DialogContext->Type;

  //
  //set Dialog Title
  //
  Dialog->Title = DialogTitle;

  if ( Dialog->Title == NULL ) {
    tBS->FreePool (Dialog);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //initialize the item values
  //
  Dialog->BodyRect.TopLeft.Row      = 10;
  Dialog->BodyRect.TopLeft.Col      = 18;
  Dialog->BodyRect.BottomRight.Row  = 17;
  Dialog->BodyRect.BottomRight.Col  = 62;

  Dialog->ForeColor = EFI_POPUP_MENU_FORECOLOR;
  Dialog->BackColor = EFI_BLUE;

  //
  //initialize the default pointer and item values
  //

  Status = DisplayDialog (Dialog, DialogContext);

  FreeDialog(Dialog);

  //
  //
  //restore original console attribute
  //
  tST->ConOut->SetAttribute ( tST->ConOut,ConAttrib);

  return EFI_SUCCESS;
}
