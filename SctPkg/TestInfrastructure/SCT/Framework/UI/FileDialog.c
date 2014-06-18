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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  FileDialog.c

Abstract:

  This file implements the interface display File Dialog

--*/
#include "Sct.h"
#include "UI.h"
#include "BuildMenu.h"
#include "FileDialog.h"

//
//File Type Info definition
//

STATIC EFI_FILE_TYPE_INFO FileTypeInfo[] = {
  { L".*"   , L"All Files (*.*)"       },
  { L".log" , L"Log Files (*.log)"     },
  { L".ekl" , L"Key Files (*.ekl)"     },
  { L".txt" , L"Text Files (*.txt)"    },
  { L".doc" , L"Doc Files (*.doc)"     },
  { L".bat" , L"Batch Files (*.bat)"   },
  { L".ini" , L"Ini Files (*.ini)"     },
  { L".seq" , L"Sequence Files(*.seq)" },
  { L".h" ,   L"Header Files (*.h)"    },
  { L".c" ,   L"'C' Files (*.c)"       },
  { L".efi" , L"EFI Files (*.efi)"     },
  { L".csv" , L"CSV Files (*.csv)"     }
};

//
// protypes (external)
//

EFI_STATUS
DoFileDialog (
  IN OUT EFI_FILE_DIALOG_CONTEXT  *DialogContext
  );

//
// protypes (internal)
//

EFI_STATUS
FreeFileSystemDialog (
  IN EFI_FILE_DIALOG        *Dialog
  );

EFI_STATUS
FreeDirDialog (
  IN EFI_FILE_DIALOG        *Dialog
  );

EFI_STATUS
FileDialogItemRefresh (
  IN EFI_FILE_DIALOG        *FileDialog,
  IN EFI_FILE_DIALOG_ITEM   *Item
  );

EFI_STATUS
DialogInputRefresh (
  IN EFI_FILE_DIALOG        *FileDialog
  );

EFI_STATUS
FileDialogRefresh (
  IN EFI_FILE_DIALOG        *FileDialog,
  IN BOOLEAN                RefreshAll
  );

EFI_STATUS
FileDialogUpFunc (
  EFI_FILE_DIALOG           *FileDialog
  );

EFI_STATUS
FileDialogDownFunc (
  EFI_FILE_DIALOG           *FileDialog
  );

EFI_STATUS
FileDialogPageUpFunc (
  EFI_FILE_DIALOG           *FileDialog
  );

EFI_STATUS
FileDialogPageDownFunc (
  EFI_FILE_DIALOG           *FileDialog
  );

VOID *
DisplayFileDialog (
  IN  EFI_FILE_DIALOG       *Dialog,
  IN  EFI_INPUT_KEY         *Key
  );

EFI_FILE_DIALOG_ITEM *
AllocateFileDialogItem (
  IN EFI_FILE_DIALOG        *Dialog,
  IN UINT16                 *String,
  IN VOID                   *Context
  );

BOOLEAN
IsSearchedFile (
  IN EFI_FILTER_FILE_TYPE   FileType,
  IN CHAR16                 *FileName
  );
BOOLEAN
BuildDirDialog (
  IN  EFI_FILE_DIALOG_ITEM_CONTEXT    *ItemContext,
  IN  EFI_FILE_DIALOG                 *DirDialog
  );

BOOLEAN
FindAFileInDialog (
  IN  EFI_FILE_DIALOG_ITEM_CONTEXT    *ItemContext,
  IN  EFI_FILE_DIALOG                 *DirDialog,
  IN  OUT EFI_FILE_DIALOG_CONTEXT     *DialogContext
  );


EFI_STATUS
FreeFileSystemDialogItemContext (
  IN EFI_FILE_DIALOG_ITEM_CONTEXT     *ItemContext
  )
{
  if (ItemContext == NULL) {
    return EFI_SUCCESS;
  }

  if (ItemContext->FHandle) {
    //
    //close file handle
    //
    ItemContext->FHandle->Close (ItemContext->FHandle);
  }
  //
  //free device path string and file name string
  //
  if (ItemContext->DevicePathStr != NULL) {
    tBS->FreePool (ItemContext->DevicePathStr);
    ItemContext->DevicePathStr = NULL;
  }
  if (ItemContext->FileName != NULL) {
    tBS->FreePool (ItemContext->FileName);
    ItemContext->FileName = NULL;
  }

  //
  //free item context
  //
  tBS->FreePool (ItemContext);
  return EFI_SUCCESS;
}


EFI_STATUS
FreeFileSystemDialog (
  IN EFI_FILE_DIALOG        *Dialog
  )
/*++

Routine Description:

  Free file system Dialog Items and relative Context.

Arguments:

  Dialog    - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS - the resource was freed successfully.

--*/
{ EFI_FILE_DIALOG_ITEM               *DialogItem;
  EFI_FILE_DIALOG_ITEM               *TempDialogItem;
  EFI_FILE_DIALOG_ITEM_CONTEXT       *ItemContext;

  if (Dialog == NULL ) {
    return EFI_INVALID_PARAMETER;
  }

  if (Dialog->Title != NULL) {
    tBS->FreePool (Dialog->Title);
    Dialog->Title = NULL;
  }

  DialogItem = Dialog->ItemList;
  while (DialogItem != NULL) {
    TempDialogItem  = DialogItem ->Next;
    ItemContext     = (EFI_FILE_DIALOG_ITEM_CONTEXT *)DialogItem->Context;
    if (ItemContext != NULL) {
      //
      //free item context
      //
      FreeFileSystemDialogItemContext (ItemContext);
    }
    if (DialogItem->ItemName != NULL) {
      //
      //free item name
      //
      tBS->FreePool (DialogItem->ItemName);
    }
    //
    //free dialog item
    //
    tBS->FreePool (DialogItem);
    DialogItem = TempDialogItem;
  }

  //
  //free file name
  //
  if (Dialog->FileName != NULL) {
    tBS->FreePool (Dialog->FileName);
    Dialog->FileName = NULL;
  }

  //
  //at last free the Dialog
  //
  tBS->FreePool (Dialog);

  return EFI_SUCCESS;

}

EFI_STATUS
FreeDirDialog (
  IN EFI_FILE_DIALOG        *Dialog
  )
/*++

Routine Description:

  Free directory Dialog Items Item Context but don't free the
  Dialog's Title and FileName.

Arguments:

  Dialog      - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS - the resource was freed successfully.

--*/
{
  EFI_FILE_DIALOG_ITEM         *DialogItem;
  EFI_FILE_DIALOG_ITEM         *TempDialogItem;
  EFI_FILE_DIALOG_ITEM_CONTEXT *ItemContext;

  if (Dialog == NULL ) {
    return EFI_INVALID_PARAMETER;
  }

  DialogItem = Dialog->ItemList;

  while (DialogItem != NULL) {
    TempDialogItem = DialogItem ->Next;

    ItemContext = (EFI_FILE_DIALOG_ITEM_CONTEXT *)DialogItem->Context;

    if (ItemContext != NULL) {
      //
      //free device path.
      //
      if (ItemContext->DevicePath != NULL) {
        tBS->FreePool (ItemContext->DevicePath);
        ItemContext->DevicePath = NULL;
      }
      //
      //free device path string and file name string.
      //
      if (ItemContext->DevicePathStr != NULL) {
        tBS->FreePool (ItemContext->DevicePathStr);
        ItemContext->DevicePathStr = NULL;
      }
      if (ItemContext->FileName != NULL) {
        tBS->FreePool (ItemContext->FileName);
        ItemContext->FileName = NULL;
      }
      tBS->FreePool (ItemContext);
    }

    if (DialogItem->ItemName != NULL) {
      //
      //free item name
      //
      tBS->FreePool (DialogItem->ItemName);
      DialogItem->ItemName = NULL;
    }

    tBS->FreePool (DialogItem);

    DialogItem = TempDialogItem;
  }
  //
  //set all the pointer to NULL.
  //
  Dialog->ItemList        = NULL;
  Dialog->FirstInDisplay  = NULL;
  Dialog->LastInDisplay   = NULL;
  Dialog->CurrentSelected = NULL;

  return EFI_SUCCESS;
}

EFI_STATUS
FileDialogItemRefresh (
  IN EFI_FILE_DIALOG        *FileDialog,
  IN EFI_FILE_DIALOG_ITEM   *Item
  )
/*++

Routine Description:

  Refresh one item.

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.
  Item        - The EFI_FILE_DIALOG_ITEM instance poiter.
  Line        - The offset of Item in Dialog.

Returns:

  EFI_SUCCESS           - the item was refreshed successfully.
  EFI_INVALID_PARAMETER - one of parameters is invalid.

--*/
{
  EFI_STATUS            Status;
  EFI_FILE_DIALOG_ITEM  *TempDialogItem;
  UINTN                 X0;
  UINTN                 X1;
  UINTN                 Y0;
  CHAR16                Buffer[EFI_MAX_LINE_LENGTH + 1];
  UINTN                 Index;
  UINTN                 Line;

  if (FileDialog == NULL ||Item == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;

  X0 = FileDialog->BodyRect.TopLeft.Col;
  Y0 = FileDialog->BodyRect.TopLeft.Row;
  X1 = FileDialog->BodyRect.BottomRight.Col;

  //
  //caculate Item offset in lines.
  //
  Line = 0;
  TempDialogItem = FileDialog->FirstInDisplay;
  while (TempDialogItem != NULL && TempDialogItem != Item) {
    Line++;
    TempDialogItem = TempDialogItem->Next;
  }
  Line++;

  //
  //based on current dialog staus set the console attribute
  //
  if (TempDialogItem == FileDialog->CurrentSelected &&
      FileDialog->CurrentArea == FILE_DIALOG_MENU_AREA) {
    tST->ConOut->SetAttribute (
                  tST->ConOut,
                  EFI_TEXT_ATTR(FileDialog->BackColor, FileDialog->ForeColor)
                  );
  } else if (TempDialogItem == FileDialog->CurrentSelected) {
    tST->ConOut->SetAttribute (
                  tST->ConOut,
                  EFI_TEXT_ATTR(FileDialog->BackColor, EFI_LIGHTGRAY)
                  );
  } else {
    tST->ConOut->SetAttribute (
                  tST->ConOut,
                  EFI_TEXT_ATTR(FileDialog->ForeColor, FileDialog->BackColor)
                  );
  }

  //
  //display ItemName.
  //
  if (SctStrLen (TempDialogItem->ItemName) > (X1 - X0 - 1)) {
    tBS->CopyMem (
      Buffer,
      TempDialogItem->ItemName,
      (X1 - X0 - 1) * sizeof(CHAR16)
      );
    Buffer[X1-X0-1] = L'\0';
    Status = TestPrintAt (X0 + 1, Y0 + Line, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    SctStrCpy (Buffer, TempDialogItem->ItemName);
    for (Index = SctStrLen (Buffer); Index < X1 - X0 - 1; Index++ ) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';

    Status = TestPrintAt (X0 + 1, Y0 + Line, Buffer);
    if (EFI_ERROR (Status) ) {
      return Status;
    }
  }

  if (TempDialogItem == FileDialog->CurrentSelected) {
    tST->ConOut->SetAttribute (
                  tST->ConOut,
                  EFI_TEXT_ATTR(FileDialog->ForeColor, FileDialog->BackColor)
                  );
  }

  return Status;
}

EFI_STATUS
DialogInputRefresh (
  IN EFI_FILE_DIALOG        *FileDialog
  )
/*++

Routine Description:

  refresh the FileDialog input area.

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS - the input area was refreshed successfully.

--*/
{
  UINTN       Xpos;
  UINTN       Ypos;
  CHAR16      Buffer[EFI_MAX_ITEM_VALUE_LENGTH + 1];
  UINTN       Length;
  UINTN       Index;
  EFI_STATUS  Status;

  Xpos = FileDialog -> BodyRect.TopLeft.Col + 20;
  Ypos = FileDialog -> BodyRect.BottomRight.Row + 1;
  Length = SctStrLen (FileDialog->FileName);
  if (Length > EFI_MAX_ITEM_VALUE_LENGTH) {
    tBS->CopyMem (
      Buffer,
      FileDialog->FileName,
      EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16)
      );
    Buffer[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';
  } else {
    //
    //clear the input area
    //
    for (Index = 0; Index < EFI_MAX_ITEM_VALUE_LENGTH; Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';
    TestPrintAt (Xpos, Ypos, Buffer);

    tBS->CopyMem (Buffer, FileDialog->FileName, (Length + 1) * sizeof(CHAR16));
  }
  //
  //print the input string
  //
  Status = TestPrintAt (Xpos, Ypos, Buffer);

  return Status;
}

EFI_STATUS
FileDialogRefresh (
  IN EFI_FILE_DIALOG        *FileDialog,
  IN BOOLEAN                RefreshAll
  )
/*++

Routine Description:

  refresh the FileDialog.

Arguments:

  FileDialog            - The EFI_FILE_DIALOG instance pointer.

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
  UINTN                                  Ypos;
  EFI_STATUS                             Status;
  CHAR16                                 *ShortName;
  EFI_FILE_DIALOG_ITEM                   *DialogItem;
  EFI_FILE_DIALOG_ITEM_CONTEXT           *Context;

  if (FileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  DialogItem = NULL;

  X0 = FileDialog->BodyRect.TopLeft.Col;
  Y0 = FileDialog->BodyRect.TopLeft.Row;
  X1 = FileDialog->BodyRect.BottomRight.Col;
  Y1 = FileDialog->BodyRect.BottomRight.Row;

  if ((X1 < X0 + 45) || (Y1 < Y0 + 5)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;

  tST->ConOut->SetAttribute (
                tST->ConOut,
                EFI_TEXT_ATTR(FileDialog->ForeColor,
                FileDialog->BackColor)
                );

  if (RefreshAll) {

    for (Index = 0; Index < X1 - X0 + 1; Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';
    //
    //clear the Dialog Rect Area.
    //
    for (SubIndex = Y0 - 1; SubIndex <= Y1 + 3; SubIndex++) {
      Status = TestPrintAt (X0, SubIndex, Buffer);
      if (EFI_ERROR(Status)) {
        return Status;
      }
    }

    //
    //display the title
    //
    if (FileDialog->Title != NULL) {
      if (SctStrLen (FileDialog->Title) > X1 - X0) {
        tBS->CopyMem (
              Buffer,
              FileDialog->Title,
              (X1 - X0)* sizeof(CHAR16)
              );
        Buffer[X1 - X0] = L'\0';
        TestPrintAt (X0, Y0 - 1, Buffer);
      } else {
        TestPrintAt (X0, Y0 - 1, FileDialog->Title);
      }
    }

    //
    // then we draw the four corner.
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

    //
    //display the "File Name:" or "Dir Name:"
    //

    TestPrintAt (X0 + 4, Y1 + 1, L"File Name:");

    TestPrintAt (X0 + 19, Y1 + 1, L"[");
    TestPrintAt (X0 + 40, Y1 + 1, L"]");

    if (FileDialog->FileName != NULL && FileDialog->ItemList != NULL ) {
      Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(FileDialog->CurrentSelected->Context);
      if (!Context->RootContext) {
        //
        //reset the file name to current selected item file name
        //
        ShortName = NULL;
        ShortName = SctGetShortFileNameAndExt (Context->FileName);
        if (ShortName != NULL) {
          SctStrCpy (FileDialog->FileName, ShortName);
        } else {
          return EFI_OUT_OF_RESOURCES;
        }
        //
        //display File Name.
        //
        if (SctStrLen (FileDialog->FileName) > EFI_MAX_ITEM_VALUE_LENGTH) {
          tBS->CopyMem (
            Buffer,
            FileDialog->FileName,
            EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16)
            );
          Buffer[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';
          TestPrintAt (X0 + 20, Y1 + 1, Buffer);
        } else {
          TestPrintAt (X0 + 20, Y1 + 1, FileDialog->FileName);
        }
      }
    }

    //
    //display the file type info
    //
    if (FileDialog->Type == EFI_FILE_DIALOG_TYPE_OPEN_FILE) {
      TestPrintAt (X0 + 4, Y1 + 2, L"Files of type:");
      TestPrintAt (
        X0 + 19,
        Y1 + 2,
        FileTypeInfo[FileDialog->FileType].FileTypeDesc
        );
    } else if (FileDialog->Type == EFI_FILE_DIALOG_TYPE_SAVE_FILE) {
      TestPrintAt (X0 + 4, Y1 + 2, L"Save as type:");
      TestPrintAt (
        X0 + 19,
        Y1 + 2,
        FileTypeInfo[FileDialog->FileType].FileTypeDesc
        );
      TestPrintAt (X0 + 4, Y1 + 3, L"Press F2 to edit filename");
    } else {
      TestPrintAt (X0 + 10, Y1 + 2, L"Press ESC to return");
    }
  } else {

    //
    //clear the Popup Dialog Rect Area.
    //
    for (Index = 0; Index < X1 - X0 - 1; Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';
    for (SubIndex = Y0 + 1; SubIndex < Y1; SubIndex++) {
      Status = TestPrintAt (X0 + 1, SubIndex, Buffer);
      if (EFI_ERROR(Status)) {
        return Status;
      }
    }
  }

  //
  //draw all the Items.
  //
  if (NULL == FileDialog->CurrentSelected || NULL == FileDialog->ItemList) {
    return EFI_SUCCESS;
  }

  Ypos = Y0 + 1;

  DialogItem = FileDialog->FirstInDisplay;
  while (DialogItem != NULL && DialogItem != FileDialog->LastInDisplay->Next) {
    if (DialogItem == FileDialog->CurrentSelected &&
        FileDialog->CurrentArea == FILE_DIALOG_MENU_AREA) {
      tST->ConOut->SetAttribute (
                    tST->ConOut,
                    EFI_TEXT_ATTR(FileDialog->BackColor, FileDialog->ForeColor)
                    );
    } else if (DialogItem == FileDialog->CurrentSelected) {
      tST->ConOut->SetAttribute (
                    tST->ConOut,
                    EFI_TEXT_ATTR(FileDialog->BackColor, EFI_LIGHTGRAY)
                    );
    }

    if (SctStrLen (DialogItem->ItemName) > (X1 - X0 - 1)) {
      tBS->CopyMem (
        Buffer,
        DialogItem->ItemName,
        (X1 - X0 - 1) * sizeof(CHAR16)
        );
      Buffer[X1 - X0 - 1] = L'\0';

      Status = TestPrintAt (X0 + 1, Ypos, Buffer);
      if (EFI_ERROR (Status)) {
        return Status;
      }

    } else {

      SctStrCpy (Buffer, DialogItem->ItemName);
      for ( Index = SctStrLen (Buffer); Index < X1 - X0 - 1; Index++ ) {
        Buffer[Index] = L' ';
      }
      Buffer[Index] = L'\0';

      Status = TestPrintAt (X0 + 1, Ypos, Buffer);
      if (EFI_ERROR (Status) ) {
        return Status;
      }
    }
    if (DialogItem == FileDialog->CurrentSelected) {
      tST->ConOut->SetAttribute (
                    tST->ConOut,
                    EFI_TEXT_ATTR(FileDialog->ForeColor, FileDialog->BackColor)
                    );
    }

    Ypos = Ypos + 1;

    DialogItem = DialogItem->Next;
  }

  return Status;
}

EFI_STATUS
FileDialogUpFunc (
  EFI_FILE_DIALOG           *FileDialog
  )
/*++

Routine Description:

  response to UP key.

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS           - the UP key was responsed successfully.
  EFI_INVALID_PARAMETER - one of parameters is invalid.

--*/
{
  EFI_STATUS                    Status;
  EFI_FILE_DIALOG_ITEM          *DialogItem;
  EFI_FILE_DIALOG_ITEM_CONTEXT  *Context;
  BOOLEAN                       SCROLLING;
  INTN                          CurrentPointedLine;
  CHAR16                        *ShortName;

  if (FileDialog  == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // if there was no item to display return EFI_SUCCESS.
  //
  if ( FileDialog->ItemList == NULL || FileDialog->CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  Status              = EFI_SUCCESS;
  CurrentPointedLine  = 0;
  DialogItem          = FileDialog->FirstInDisplay;

  //
  //caculate current selected line offset
  //
  while (DialogItem != NULL && DialogItem != FileDialog->CurrentSelected) {
    CurrentPointedLine++;
    DialogItem = DialogItem->Next;
  }
  CurrentPointedLine++;

  DialogItem = FileDialog->CurrentSelected;

  //
  //caculate if need scroll
  //
  if (DialogItem->Prev == NULL || (CurrentPointedLine >= 2)) {
    SCROLLING = FALSE;
  } else {
    SCROLLING = TRUE;
  }

  if (SCROLLING) {
    FileDialog->FirstInDisplay  = FileDialog->FirstInDisplay->Prev;
    FileDialog->CurrentSelected = FileDialog->CurrentSelected->Prev;
    FileDialog->LastInDisplay   = FileDialog->LastInDisplay->Prev;

    Status = FileDialogRefresh(FileDialog,FALSE);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    //
    //if is in File System Dialog the Edit area don't need to refresh
    //
    Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(FileDialog->CurrentSelected->Context);
    if (Context->RootContext) {
      return EFI_SUCCESS;
    }

    //
    //reset the current selected File Name.
    //
    ShortName = NULL;
    ShortName = SctGetShortFileNameAndExt (Context->FileName);
    if (ShortName != NULL) {
      SctStrCpy (FileDialog->FileName, ShortName);
    } else {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //refresh the file name display
    //
    Status = DialogInputRefresh (FileDialog);
    return Status;

  } else {

    if (FileDialog->CurrentSelected->Prev != NULL) {
      FileDialog->CurrentSelected =  FileDialog->CurrentSelected->Prev;
      //
      //refresh two changed item
      //
      Status = FileDialogItemRefresh (
                 FileDialog,
                 FileDialog->CurrentSelected->Next
                 );
      if (EFI_ERROR (Status) ) {
        return Status;
      }

      Status = FileDialogItemRefresh (
                 FileDialog,
                 FileDialog->CurrentSelected
                 );
      if (EFI_ERROR(Status)) {
        return Status;
      }
      //
      // root File System dialog don't need to refresh the Edit area
      //
      Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(FileDialog->CurrentSelected->Context);
      if (Context->RootContext) {
        return EFI_SUCCESS;
      }
      //
      //reset the current selected File Name
      //
      ShortName = NULL;
      ShortName = SctGetShortFileNameAndExt (Context->FileName);
      if (ShortName != NULL) {
        SctStrCpy (FileDialog->FileName, ShortName);
      } else {
        return EFI_OUT_OF_RESOURCES;
      }
      //
      //refresh the file name display
      //
      Status = DialogInputRefresh (FileDialog);
      return Status;
    }
    //
    //no item changed so don't need to refresh
    //
    return EFI_SUCCESS;
  }
}

EFI_STATUS
FileDialogDownFunc (
  EFI_FILE_DIALOG           *FileDialog
  )
/*++

Routine Description:

  response to DOWN key.

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS           - the DOWN key was responsed successfully.
  EFI_INVALID_PARAMETER - one of parameters is invalid.

--*/
{
  EFI_STATUS                    Status;
  EFI_FILE_DIALOG_ITEM          *DialogItem;
  BOOLEAN                       SCROLLING;
  INTN                          TotalLines;
  INTN                          CurrentPointedLine;
  CHAR16                        *ShortName;
  EFI_FILE_DIALOG_ITEM_CONTEXT  *Context;

  if (FileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // if there was no item to display return EFI_SUCCESS.
  //
  if ( FileDialog->ItemList == NULL || FileDialog->CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  if (FileDialog->CurrentArea == FILE_DIALOG_EDIT_AREA) {
    return EFI_SUCCESS;
  }

  Status              = EFI_SUCCESS;
  TotalLines          = FileDialog->BodyRect.BottomRight.Row - FileDialog->BodyRect.TopLeft.Row - 1;
  CurrentPointedLine  = 0;
  DialogItem          = FileDialog->FirstInDisplay;

  //
  //caculate current selected line offset
  //
  while (DialogItem != NULL && DialogItem != FileDialog->CurrentSelected) {
    CurrentPointedLine++;
    DialogItem = DialogItem->Next;
  }
  CurrentPointedLine++;
  DialogItem = FileDialog->CurrentSelected;

  //
  //caculate if need to scroll
  //
  if (DialogItem->Next == NULL || (CurrentPointedLine < TotalLines)) {
    SCROLLING = FALSE;
  } else {
    SCROLLING = TRUE;
  }

  if (SCROLLING) {
    //
    //reset pointers
    //
    FileDialog->FirstInDisplay  = FileDialog->FirstInDisplay->Next;
    FileDialog->CurrentSelected = FileDialog->CurrentSelected->Next;
    FileDialog->LastInDisplay   = FileDialog->LastInDisplay->Next;

    //
    //refresh the items
    //
    Status = FileDialogRefresh (FileDialog, FALSE);
    if (EFI_ERROR(Status)) {
      return Status;
    }
    Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(FileDialog->CurrentSelected->Context);
    if (Context->RootContext) {
      return EFI_SUCCESS;
    }
    //
    //reset the current selected File Name
    //
    ShortName = NULL;
    ShortName = SctGetShortFileNameAndExt (Context->FileName);
    if (ShortName != NULL) {
      SctStrCpy (FileDialog->FileName, ShortName);
    } else {
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //refresh the file name display
    //
    Status = DialogInputRefresh (FileDialog);
    return Status;

  } else {

    if (FileDialog->CurrentSelected->Next != NULL) {
      FileDialog->CurrentSelected =  FileDialog->CurrentSelected->Next;
      //
      //refresh two changed item
      //
      Status = FileDialogItemRefresh (
                 FileDialog,
                 FileDialog->CurrentSelected->Prev
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }

      Status = FileDialogItemRefresh (
                 FileDialog,
                 FileDialog->CurrentSelected
                 );
      if (EFI_ERROR(Status)) {
        return Status;
      }
      Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(FileDialog->CurrentSelected->Context);
      if (Context->RootContext) {
        return EFI_SUCCESS;
      }
      //
      //reset the current selected File Name
      //
      ShortName = NULL;
      ShortName = SctGetShortFileNameAndExt (Context->FileName);
      if (ShortName != NULL) {
        SctStrCpy (FileDialog->FileName, ShortName);
      } else {
        return EFI_OUT_OF_RESOURCES;
      }
      //
      //refresh the file name display
      //
      Status = DialogInputRefresh (FileDialog);
      return Status;
    }
    return EFI_SUCCESS;
  }
}

EFI_STATUS
FileDialogPageUpFunc (
  EFI_FILE_DIALOG           *FileDialog
  )
/*++

Routine Description:

  response to Page Up key.

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS           - the Page Up key was responsed successfully.
  EFI_INVALID_PARAMETER - one of parameters is invalid.

--*/
{
  EFI_STATUS                    Status;
  EFI_FILE_DIALOG_ITEM          *DialogItem;
  INTN                          TotalLines;
  INTN                          Index;
  CHAR16                        *ShortName;
  EFI_FILE_DIALOG_ITEM_CONTEXT  *Context;

  if (FileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // if there was no item to display return EFI_SUCCESS.
  //
  if ( FileDialog->ItemList == NULL || FileDialog->CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  if (FileDialog->CurrentArea == FILE_DIALOG_EDIT_AREA) {
    return EFI_SUCCESS;
  }
  //
  //there is no item before current selected item, so return EFI_SUCCCSS.
  //
  if (FileDialog->CurrentSelected->Prev == NULL) {
    return EFI_SUCCESS;
  }

  if (FileDialog->CurrentSelected != FileDialog->FirstInDisplay) {
    DialogItem = FileDialog->CurrentSelected;
    FileDialog->CurrentSelected = FileDialog->FirstInDisplay;
    //
    //refresh the two items.
    //
    Status = FileDialogItemRefresh (
               FileDialog,
               DialogItem
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = FileDialogItemRefresh (
               FileDialog,
               FileDialog->CurrentSelected
               );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  } else {
    TotalLines = FileDialog->BodyRect.BottomRight.Row - FileDialog->BodyRect.TopLeft.Row - 1;
    //
    //move the first in display and last in display pointer up at most
    //'totalLines' line.
    //
    for (Index = 0; Index < TotalLines; Index ++) {
      FileDialog->FirstInDisplay = FileDialog->FirstInDisplay->Prev;
      FileDialog->LastInDisplay  = FileDialog->LastInDisplay->Prev;
      if (FileDialog->FirstInDisplay->Prev == NULL) {
        break;
      }
    }
    FileDialog->CurrentSelected = FileDialog->FirstInDisplay;
    //
    //refresh the items
    //
    Status = FileDialogRefresh (FileDialog, FALSE);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }
  //
  //at last refresh the edit area.
  //
  Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(FileDialog->CurrentSelected->Context);
  if (Context->RootContext) {
    return EFI_SUCCESS;
  }
  //
  //reset the current selected File Name
  //
  ShortName = NULL;
  ShortName = SctGetShortFileNameAndExt (Context->FileName);
  if (ShortName != NULL) {
    SctStrCpy (FileDialog->FileName, ShortName);
  } else {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //refresh the file name display
  //
  Status = DialogInputRefresh (FileDialog);
  return Status;
}

EFI_STATUS
FileDialogPageDownFunc (
  EFI_FILE_DIALOG           *FileDialog
  )
/*++

Routine Description:

  response to Page Down key.

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS           - the Page Down key was responsed successfully.
  EFI_INVALID_PARAMETER - one of parameters is invalid.

--*/
{
  EFI_STATUS                    Status;
  EFI_FILE_DIALOG_ITEM          *DialogItem;
  INTN                          TotalLines;
  INTN                          Index;
  CHAR16                        *ShortName;
  EFI_FILE_DIALOG_ITEM_CONTEXT  *Context;

  if (FileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // if there was no item to display return EFI_SUCCESS.
  //
  if ( FileDialog->ItemList == NULL || FileDialog->CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  if (FileDialog->CurrentArea == FILE_DIALOG_EDIT_AREA) {
    return EFI_SUCCESS;
  }
  //
  //there is no item behind current selected item, so return EFI_SUCCCSS.
  //
  if (FileDialog->CurrentSelected->Next == NULL) {
    return EFI_SUCCESS;
  }

  if (FileDialog->CurrentSelected != FileDialog->LastInDisplay) {
    DialogItem = FileDialog->CurrentSelected;
    FileDialog->CurrentSelected = FileDialog->LastInDisplay;
    //
    //refresh the two items.
    //
    Status = FileDialogItemRefresh (
               FileDialog,
               DialogItem
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = FileDialogItemRefresh (
               FileDialog,
               FileDialog->CurrentSelected
               );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  } else {
    TotalLines = FileDialog->BodyRect.BottomRight.Row - FileDialog->BodyRect.TopLeft.Row - 1;
    //
    //move the first in display and last in display pointer down at most
    //'totalLines' line.
    //
    for (Index = 0; Index < TotalLines; Index ++) {
      FileDialog->LastInDisplay  = FileDialog->LastInDisplay->Next;
      FileDialog->FirstInDisplay = FileDialog->FirstInDisplay->Next;
      if (FileDialog->LastInDisplay->Next == NULL) {
        break;
      }
    }
    FileDialog->CurrentSelected = FileDialog->LastInDisplay;
    //
    //refresh the items
    //
    Status = FileDialogRefresh (FileDialog, FALSE);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }
  //
  //at last refresh the edit area.
  //
  Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(FileDialog->CurrentSelected->Context);
  if (Context->RootContext) {
    return EFI_SUCCESS;
  }
  //
  //reset the current selected File Name
  //
  ShortName = NULL;
  ShortName = SctGetShortFileNameAndExt (Context->FileName);
  if (ShortName != NULL) {
    SctStrCpy (FileDialog->FileName, ShortName);
  } else {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //refresh the file name display
  //
  Status = DialogInputRefresh (FileDialog);
  return Status;
}


EFI_STATUS
FileDialogEditFunc (
  IN  EFI_FILE_DIALOG       *FileDialog,
  IN  EFI_INPUT_KEY         *InKey
  )
/*++

Routine Description:

  response the key input in dialog edit area

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.
  InKey       - the EFI_INPUT_KEY instance pointer.

Returns:

  EFI_SUCCESS - all the keys were responsed successfully

--*/
{
  EFI_STATUS            Status;
  INTN                  Ypos;
  INTN                  XLeft;
  INTN                  Num;
  EFI_INPUT_KEY         Key;
  INTN                  Index;
  BOOLEAN               WAITING;
  CHAR16                Buffer[EFI_MAX_EDIT_LENGTH + 1];
  CHAR16                TempStr[EFI_MAX_ITEM_VALUE_LENGTH + 1];
  INTN                  XOffSetInScreen;
  INTN                  XOffSetInBuffer;
  INTN                  FirstInDisplay;
  INTN                  LastInDisplay;
  INTN                  CurrentLength;

  //
  // check parameter
  //
  if (FileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status     = EFI_SUCCESS;
  WAITING    = TRUE;
  TempStr[0] = L'\0';
  tBS->SetMem (&Key, sizeof(EFI_INPUT_KEY), 0);

  Ypos  = FileDialog->BodyRect.BottomRight.Row + 1;
  XLeft = FileDialog->BodyRect.TopLeft.Col + 20;

  CurrentLength = SctStrLen (FileDialog->FileName);
  //
  //save the filename in buffer
  //
  SctStrCpy (Buffer, FileDialog->FileName);

  XOffSetInScreen = 0;
  XOffSetInBuffer = 0;
  FirstInDisplay  = 0;

  if (CurrentLength > EFI_MAX_ITEM_VALUE_LENGTH) {
    LastInDisplay = EFI_MAX_ITEM_VALUE_LENGTH - 1;
  } else if (CurrentLength > 0) {
    LastInDisplay = CurrentLength - 1;
  } else {
    LastInDisplay = 0;
  }
  //
  //enable cursor.
  //
  tST->ConOut->SetCursorPosition (tST->ConOut, XLeft + XOffSetInScreen, Ypos);
  tST->ConOut->EnableCursor (tST->ConOut,TRUE);

  while (WAITING) {
    Status = tBS->WaitForEvent (1, &(tST->ConIn->WaitForKey), (UINTN *)&Num);
    if (!EFI_ERROR(Status)) {
      Status = tST->ConIn->ReadKeyStroke (tST->ConIn, &Key);
    }
    if ( EFI_ERROR(Status)) {
      continue;
    }
    switch (Key.ScanCode) {
      case SCAN_ESC:
        if (Key.ScanCode == SCAN_ESC) {
          //
          //save the input value in FileName
          //
          SctStrCpy (FileDialog->FileName, Buffer);
          //
          //disable cursor.
          //
          tST->ConOut->EnableCursor (tST->ConOut, FALSE);

          tBS->CopyMem (TempStr, Buffer, EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16));
          TempStr[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';

          WAITING             = FALSE;
          InKey->ScanCode     = Key.ScanCode;
          InKey->UnicodeChar  = Key.UnicodeChar;
        }
        break;

      case SCAN_LEFT:
        if (XOffSetInScreen > 0) {
          //
          //move cursor directly in screen and in buffer.
          //
          XOffSetInScreen--;
          if (XOffSetInBuffer > 0) {
            XOffSetInBuffer--;
          }
          //
          //set cursor position
          //
          tST->ConOut->SetCursorPosition (
                        tST->ConOut,
                        XLeft + XOffSetInScreen,
                        Ypos
                        );

        } else if (FirstInDisplay > 0 ) {
          //
          //on the left of cursor there is char also,so move the char
          //to right so let it been displayed.
          //
          if ((LastInDisplay - FirstInDisplay + 1) >= EFI_MAX_ITEM_VALUE_LENGTH) {
            LastInDisplay--;
          }
          FirstInDisplay--;

          if (XOffSetInBuffer > 0) {
            XOffSetInBuffer--;
          }
          //
          //refresh display in screen
          //
          tBS->CopyMem (
            TempStr,
            Buffer + FirstInDisplay,
            EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16)
            );

          TempStr[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';

          Status = TestPrintAt (XLeft, Ypos, TempStr);
          if (EFI_ERROR (Status) ) {
            return Status;
          }
          tST->ConOut->SetCursorPosition (
                        tST->ConOut,
                        XLeft + XOffSetInScreen,
                        Ypos
                        );
        }
        break;

      case SCAN_RIGHT:

        if (XOffSetInBuffer < CurrentLength) {

          if (XOffSetInScreen < EFI_MAX_ITEM_VALUE_LENGTH -1) {
            //
            //before the cursor in screen point to the LastInDisplay
            //move the cursor to next char.
            //
            XOffSetInBuffer++;
            XOffSetInScreen++;
            tST->ConOut->SetCursorPosition (
                          tST->ConOut,
                          XLeft + XOffSetInScreen,
                          Ypos
                          );
            break;
          } else {
            if (LastInDisplay + 1 < CurrentLength) {

              XOffSetInBuffer++;
              LastInDisplay++;
              FirstInDisplay++;
              //
              //refresh edit area.
              //
              tBS->CopyMem (
                TempStr,
                Buffer + FirstInDisplay,
                EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16)
                );
              TempStr[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';
              Status = TestPrintAt (XLeft, Ypos, TempStr);
              if (EFI_ERROR (Status)) {
                return Status;
              }
              //
              //reset cursor position
              //
              tST->ConOut->SetCursorPosition (
                            tST->ConOut,
                            XLeft + XOffSetInScreen,
                            Ypos
                            );
              break;
            } else if (LastInDisplay + 1 == CurrentLength) {
              FirstInDisplay++;
              XOffSetInBuffer++;
              for (Index = 0; Index < LastInDisplay - FirstInDisplay + 1; Index++) {
                TempStr[Index] = Buffer[Index + FirstInDisplay];
              }
              TempStr[EFI_MAX_ITEM_VALUE_LENGTH -1] = L' ';
              TempStr[EFI_MAX_ITEM_VALUE_LENGTH]    = L'\0';
              Status = TestPrintAt (XLeft, Ypos, TempStr);
              if (EFI_ERROR (Status) ) {
                return Status;
              }
              tST->ConOut->SetCursorPosition (
                            tST->ConOut,
                            XLeft + XOffSetInScreen,
                            Ypos
                            );
            }
          }
        }
        break;

      case SCAN_HOME:

        if (CurrentLength > 0) {
          //
          //reset these position varibles
          //
          FirstInDisplay    = 0;
          XOffSetInScreen   = 0;
          XOffSetInBuffer   = 0;
          if (CurrentLength >= EFI_MAX_ITEM_VALUE_LENGTH) {
            LastInDisplay = EFI_MAX_ITEM_VALUE_LENGTH-1;
          } else {
            LastInDisplay = CurrentLength-1;
          }
          for (Index = 0; Index < LastInDisplay + 1; Index++) {
            TempStr[Index] = Buffer[Index];
          }
          TempStr[Index] = L'\0';

          Status = TestPrintAt (XLeft, Ypos, TempStr);
          if ( EFI_ERROR (Status) ) {
            return Status;
          }
          //
          //refresh cursor position.
          //
          tST->ConOut->SetCursorPosition (
                        tST->ConOut,
                        XLeft + XOffSetInScreen,
                        Ypos
                        );
        }
        break;

      case SCAN_END:
        if (CurrentLength > 0) {
          //
          //reset these position varibles.
          //
          LastInDisplay = CurrentLength - 1;
          if (CurrentLength < EFI_MAX_ITEM_VALUE_LENGTH) {
            FirstInDisplay  = 0;
            XOffSetInBuffer = CurrentLength;
            XOffSetInScreen = CurrentLength;
          } else {
            XOffSetInScreen = EFI_MAX_ITEM_VALUE_LENGTH - 1;
            XOffSetInBuffer = CurrentLength;
            FirstInDisplay  = LastInDisplay - EFI_MAX_ITEM_VALUE_LENGTH + 2;
          }
          //
          //first clear the edit display area
          //
          for (Index = 0; Index < EFI_MAX_ITEM_VALUE_LENGTH; Index++ ) {
            TempStr[Index] = L' ';
          }
          TempStr[Index] = L'\0';

          Status = TestPrintAt (XLeft, Ypos, TempStr);
          if (EFI_ERROR (Status) ) {
            return Status;
          }
          for (Index = 0; Index < LastInDisplay - FirstInDisplay + 1; Index++ ) {
            TempStr[Index] = Buffer[Index + FirstInDisplay];
          }
          TempStr[Index] = L'\0';

          Status = TestPrintAt (XLeft, Ypos, TempStr);
          if (EFI_ERROR (Status) ) {
            return Status;
          }
          //
          //reset cusor.
          //
          tST->ConOut->SetCursorPosition (
                        tST->ConOut,
                        XLeft + XOffSetInScreen,
                        Ypos
                        );
        }
        break;

      case SCAN_DELETE:
        if (Buffer[XOffSetInBuffer] != L'\0' ) {
          for (Index = XOffSetInBuffer; Index < CurrentLength; Index++) {
            Buffer[Index] = Buffer[Index + 1];
          }
          if ((CurrentLength - FirstInDisplay) <= EFI_MAX_ITEM_VALUE_LENGTH &&
               LastInDisplay > FirstInDisplay) {
            LastInDisplay--;
          }
          if ((CurrentLength - FirstInDisplay) <= EFI_MAX_ITEM_VALUE_LENGTH) {
            //
            //first clear the edit area
            //
            for (Index = 0; Index < EFI_MAX_ITEM_VALUE_LENGTH; Index++) {
              TempStr[Index] = L' ';
            }
            TempStr[Index] = L'\0';
            Status = TestPrintAt (XLeft, Ypos, TempStr);
            if (EFI_ERROR (Status)) {
              return Status;
            }
          }
          //
          //refresh the edit area
          //
          for (Index = 0; Index < LastInDisplay - FirstInDisplay + 1; Index++) {
            TempStr[Index] = Buffer[Index + FirstInDisplay];
          }
          TempStr[Index] = L'\0';
          Status = TestPrintAt (XLeft, Ypos, TempStr);
          if (EFI_ERROR (Status) ) {
            return Status;
          }
          //
          //set cursor
          //
          tST->ConOut->SetCursorPosition (
                        tST->ConOut,
                        XLeft + XOffSetInScreen,
                        Ypos
                        );
          CurrentLength--;
        }
        break;
      case SCAN_F2:
            //
            //save the input value in FileName
            //
            SctStrCpy (FileDialog->FileName, Buffer);

            tST->ConOut->EnableCursor (tST->ConOut, FALSE);

            tBS->CopyMem (
              TempStr,
              Buffer,
              EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16)
              );
            TempStr[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';
            Status = TestPrintAt (XLeft, Ypos, TempStr);
            if (EFI_ERROR(Status)) {
              return Status;
            }
            WAITING             = FALSE;
            InKey->ScanCode     = Key.ScanCode;
            InKey->UnicodeChar  = Key.UnicodeChar;
            break;

      case SCAN_NULL:

        switch (Key.UnicodeChar) {

          case CHAR_NULL:
            break;

          case CHAR_BACKSPACE:
            if (XOffSetInBuffer > 0) {
              //
              //remove the char before current pointed char in buffer.
              //
              for (Index = XOffSetInBuffer; Index <= CurrentLength; Index++) {
                Buffer[Index - 1] = Buffer[Index];
              }
              XOffSetInBuffer--;

              if (XOffSetInScreen > 0) {
                XOffSetInScreen--;
                //
                //clear the Edit area
                //
                for (Index = 0; Index < EFI_MAX_ITEM_VALUE_LENGTH; Index++) {
                  TempStr[Index] = L' ';
                }
                TempStr[Index] = L'\0';

                Status = TestPrintAt (XLeft, Ypos, TempStr);
                if (EFI_ERROR (Status)) {
                  return Status;
                }
                if ((CurrentLength - FirstInDisplay) <= EFI_MAX_ITEM_VALUE_LENGTH &&
                     LastInDisplay > FirstInDisplay) {

                  LastInDisplay--;
                }
                //
                //refresh the Edit area
                //
                for (Index = 0; Index < LastInDisplay - FirstInDisplay + 1; Index++) {
                  TempStr[Index] = Buffer[Index + FirstInDisplay];
                }
                TempStr[Index] = L'\0';

                Status = TestPrintAt (XLeft, Ypos, TempStr);
                if (EFI_ERROR (Status) ) {
                  return Status;
                }
                tST->ConOut->SetCursorPosition (
                              tST->ConOut,
                              XLeft + XOffSetInScreen,
                              Ypos
                              );
              } else if ( FirstInDisplay > 0 ) {
                FirstInDisplay--;
                LastInDisplay--;
              }
              CurrentLength--;
            }
            break;

          case CHAR_CARRIAGE_RETURN:
            //
            //save the input value in FileName
            //
            SctStrCpy (FileDialog->FileName, Buffer);

            tST->ConOut->EnableCursor (tST->ConOut, FALSE);

            tBS->CopyMem (
              TempStr,
              Buffer,
              EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16)
              );
            TempStr[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';
            Status = TestPrintAt (XLeft, Ypos, TempStr);
            if (EFI_ERROR(Status)) {
              return Status;
            }
            WAITING             = FALSE;
            InKey->ScanCode     = Key.ScanCode;
            InKey->UnicodeChar  = Key.UnicodeChar;
            break;

          case CHAR_LINEFEED:
            //
            //ignore the Linefeed char.
            //
            break;


          default:

            if (CurrentLength < EFI_MAX_EDIT_LENGTH) {
              //
              //add this input key into the Buffer and refresh the display
              //
              if (XOffSetInScreen < EFI_MAX_ITEM_VALUE_LENGTH - 1) {
                //
                //set last char and first char in screen position.
                //
                if ((LastInDisplay - FirstInDisplay + 1) < EFI_MAX_ITEM_VALUE_LENGTH &&
                     LastInDisplay != CurrentLength) {

                  LastInDisplay++;

                }
                XOffSetInScreen++;
                //
                //add this char into buffer.
                //
                for (Index = CurrentLength; Index >= XOffSetInBuffer; Index--) {
                  Buffer[Index + 1] = Buffer[Index];
                }
                Buffer[XOffSetInBuffer] = Key.UnicodeChar;
                XOffSetInBuffer++;
                //
                //the count of char increase one
                //
                CurrentLength++;

                for (Index = 0; Index < LastInDisplay - FirstInDisplay + 1; Index++) {
                  TempStr[Index] = Buffer[Index + FirstInDisplay];
                }
                TempStr[Index] = L'\0';
                Status = TestPrintAt (XLeft, Ypos, TempStr);
                if (EFI_ERROR (Status)) {
                  return Status;
                }
                tST->ConOut->SetCursorPosition (tST->ConOut, XLeft + XOffSetInScreen, Ypos);
              } else {
                LastInDisplay  = LastInDisplay + 1;
                FirstInDisplay = FirstInDisplay + 1;
                //
                //add this char into buffer.
                //
                if (Buffer[XOffSetInBuffer] == L'\0') {
                  Buffer[XOffSetInBuffer] = Key.UnicodeChar;
                  XOffSetInBuffer++;
                  Buffer[XOffSetInBuffer] = L'\0';
                } else {
                  for (Index = CurrentLength; Index >= XOffSetInBuffer; Index--) {
                    Buffer[Index + 1] = Buffer[Index];
                  }
                  Buffer[XOffSetInBuffer] = Key.UnicodeChar;
                  XOffSetInBuffer++;
                }
                //
                //the count of char increase one
                //
                CurrentLength++;

                for (Index = 0; Index < LastInDisplay - FirstInDisplay + 1; Index++) {
                  TempStr[Index] = Buffer[Index + FirstInDisplay];
                }
                TempStr[Index] = L'\0';
                Status = TestPrintAt (XLeft, Ypos, TempStr);
                if (EFI_ERROR (Status) ) {
                  return Status;
                }
                tST->ConOut->SetCursorPosition (
                              tST->ConOut,
                              XLeft + XOffSetInScreen,
                              Ypos
                              );
              }
            }
            break;
        }

        //
        //end switch UnicodeChar.
        //

      default:

        break;
    }
    //
    //end switch ScanCode
    //
  }
  return Status;
}

VOID *
DisplayFileDialog (
  IN  EFI_FILE_DIALOG       *Dialog,
  IN  EFI_INPUT_KEY         *Key
  )
/*++

Routine Description:

  Display File Dialog and response press key.

Arguments:

  FileDialog  - The EFI_FILE_DIALOG instance pointer.
  Key         - the EFI_INPUT_KEY instance pointer.

Returns:

  EFI_FILE_DIALOG_ITEM_CONTEXT pointer.

--*/
{
  EFI_STATUS      Status;
  UINTN           Index;
  BOOLEAN         Stopped;
  VOID            *Ret;
  UINTN           Length;
  CHAR16                        *ShortName;
  EFI_FILE_DIALOG_ITEM_CONTEXT  *Context;

  if (Dialog == NULL || Key == NULL) {
    return NULL;
  }

  Status  = EFI_SUCCESS;
  Stopped = FALSE;
  Ret     = NULL;

  //
  //refresh  Dialog
  //
  Status = FileDialogRefresh (Dialog, TRUE);
  if (EFI_ERROR (Status)) {
    return NULL;
  }

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
    Status = tST->ConIn->ReadKeyStroke (tST->ConIn, Key);

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if there is no item to select wait for press ESC to return.
    //
    if (Dialog->CurrentSelected == NULL) {
      if (Key->ScanCode != SCAN_ESC) {

        if(Dialog -> Type == EFI_FILE_DIALOG_TYPE_SAVE_FILE && Key->ScanCode == SCAN_F2) {
          //
          //if the dir is empty, the current selected is NULL, only ESC and F2 is permitted
          //
          if (Dialog->CurrentArea == FILE_DIALOG_MENU_AREA) {

            //
            //change dialog response area to input file name
            //
            Dialog->CurrentArea = FILE_DIALOG_EDIT_AREA;

            //
            //process edit function
            //
            Status = FileDialogEditFunc (Dialog, Key);

            //
            //return dialog response to Menu Area.
            //
            Dialog->CurrentArea = FILE_DIALOG_MENU_AREA;

            if (EFI_ERROR(Status)) {
              break;
            }

            //
            //check key node return from edit
            //
            if (Key->ScanCode == SCAN_ESC) {

              Ret                 = NULL;
              Dialog->FileName[0] = L'\0';
              Stopped             = TRUE;
              break;

            } else if (Key->ScanCode == SCAN_F2) {

              continue;

            } else if (Key->UnicodeChar == CHAR_CARRIAGE_RETURN) {

              Ret = NULL;
              if (Dialog->FileName[0] == L'\0') {
                continue;
              }
              //
              //check if the file name is all space
              //
              for (Length = 0; Length < SctStrLen (Dialog->FileName); Length++) {
                if (Dialog->FileName[Length] != L' ') {
                  break;
                }
              }
              if (Length < SctStrLen (Dialog->FileName)) {
                Stopped = TRUE;
              } else {
                Dialog->FileName[0] = L'\0';
                continue;
              }
            }
          } else {

            //
            //current area is edit area, F2 will shift to select area
            //
            break;
          }
        }

        //
        //no valid key input, continue wait for key
        //
        continue;
      }
    }

    switch(Key->ScanCode) {
      case SCAN_UP:

        Status = FileDialogUpFunc (Dialog);
        break;

      case SCAN_DOWN:

        Status = FileDialogDownFunc (Dialog);
        break;

      case SCAN_PAGE_DOWN:

        Status = FileDialogPageDownFunc (Dialog);
        break;

      case SCAN_PAGE_UP:

        Status = FileDialogPageUpFunc (Dialog);
        break;
      case SCAN_ESC:

        Ret = NULL;
        Dialog->FileName[0] = L'\0';
        Stopped = TRUE;
        break;

      case SCAN_F2:

        //
        //in FileSystemDialog we dont't resonse TAB to Edit the File Name
        //
        if (Dialog -> Type != EFI_FILE_DIALOG_TYPE_SAVE_FILE) {
          break;
        }
        if (((EFI_FILE_DIALOG_ITEM_CONTEXT *)Dialog->CurrentSelected->Context)->RootContext) {
          break;
        }

        if (Dialog->CurrentArea == FILE_DIALOG_MENU_AREA) {

          //
          //change dialog response area to input file name
          //
          Dialog->CurrentArea = FILE_DIALOG_EDIT_AREA;
          FileDialogItemRefresh (Dialog, Dialog->CurrentSelected);

          //
          //process edit function
          //
          Status = FileDialogEditFunc (Dialog, Key);

          //
          //return dialog response to Menu Area.
          //
          Dialog->CurrentArea = FILE_DIALOG_MENU_AREA;

          if (EFI_ERROR(Status)) {
            break;
          }
          if (Key->ScanCode == SCAN_ESC) {

            Ret                 = NULL;
            Dialog->FileName[0] = L'\0';
            Stopped             = TRUE;
            break;

          } else if (Key->ScanCode == SCAN_F2) {

            //
            //refresh current selected item
            //
            Status = FileDialogItemRefresh (Dialog, Dialog->CurrentSelected);
            Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(Dialog->CurrentSelected->Context);
            if (Context->RootContext) {
              break;
            }
            //
            //reset the current selected File Name
            //
            ShortName = NULL;
            ShortName = SctGetShortFileNameAndExt (Context->FileName);
            if (ShortName != NULL) {
              SctStrCpy (Dialog->FileName, ShortName);
            } else {
              break;
            }
            //
            //refresh the file name display
            //
            Status = DialogInputRefresh (Dialog);
            break;

          } else if (Key->UnicodeChar == CHAR_CARRIAGE_RETURN) {
            Ret = Dialog->CurrentSelected->Context;

            if (Dialog->FileName[0] == L'\0') {
              Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(Dialog->CurrentSelected->Context);
              if (Context->RootContext) {
                break;
              }
              //
              //reset the current selected File Name
              //
              ShortName = NULL;
              ShortName = SctGetShortFileNameAndExt (Context->FileName);
              if (ShortName != NULL) {
                SctStrCpy (Dialog->FileName, ShortName);
              } else {
                break;
              }
              //
              //refresh the file name display
              //
              Status = DialogInputRefresh (Dialog);
              break;
            }
            //
            //check if the file name is all space
            //
            for (Length = 0; Length < SctStrLen (Dialog->FileName); Length++) {
              if (Dialog->FileName[Length] != L' ') {
                break;
              }
            }
            if (Length < SctStrLen (Dialog->FileName)) {
              Stopped = TRUE;
            } else {
              Dialog->FileName[0] = L'\0';
            }
            break;
          }
        } else {
          break;
        }
      case SCAN_NULL:

        switch(Key->UnicodeChar) {

          case CHAR_CARRIAGE_RETURN:

            Ret = Dialog->CurrentSelected->Context;
            //
            //root filesystem ignore the input area
            //
            if (((EFI_FILE_DIALOG_ITEM_CONTEXT *)Ret)->RootContext) {
              Stopped = TRUE;
              break;
            }

            if (Dialog->FileName[0] == L'\0') {
              break;
            }
            //
            //check if the file name is all space
            //
            for (Length = 0; Length < SctStrLen (Dialog->FileName); Length++) {
              if (Dialog->FileName[Length] != L' ') {
                break;
              }
            }
            if (Length < SctStrLen (Dialog->FileName)) {
              Stopped = TRUE;
            }
            break;
          default:
            break;
        }

        //end case SCAN_NULL
        break;

      default:
        break;

    } // end switch ScanCode

  } while (!Stopped);

  if (EFI_ERROR(Status)) {
    Ret = NULL;
  }

  return Ret;
}

EFI_FILE_DIALOG_ITEM *
AllocateFileDialogItem (
  IN EFI_FILE_DIALOG        *Dialog,
  IN UINT16                 *String,
  IN VOID                   *Context
  )
/*++

Routine Description:

  allocate one new Dialog File item.

Arguments:

  Dialog    - The EFI_FILE_DIALOG instance pointer.
  String    - The popup menu item display string.
  Context   - the Item relative Context pointer.

Returns:

  EFI_FILE_DIALOG_ITEM instance pointer.
  NULL      - no New Item was allocated.

--*/
{
  EFI_FILE_DIALOG_ITEM     *DialogItem;
  EFI_FILE_DIALOG_ITEM     *TempDialogItem;
  EFI_STATUS               Status;

  if (Dialog == NULL || String == NULL) {
    return NULL;
  }

  //
  //allocate one new Dialog Item
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_ITEM),
                 (VOID **)&DialogItem
                 );
  if (EFI_ERROR(Status)) {
    return NULL;
  }
  tBS->SetMem (DialogItem, sizeof(EFI_FILE_DIALOG_ITEM), 0);

  DialogItem->Prev      = NULL;
  DialogItem->Next      = NULL;
  DialogItem->ItemName  = SctStrDuplicate (String);

  if (DialogItem->ItemName == NULL) {
    tBS->FreePool (DialogItem);
    return NULL;
  }
  DialogItem->Context = Context;

  //
  //link this item to menu item list tail
  //
  TempDialogItem = Dialog->ItemList;
  if (TempDialogItem == NULL) {
    Dialog->ItemList = DialogItem;
  } else {
    while (TempDialogItem->Next != NULL) {
      TempDialogItem = TempDialogItem->Next;
    }

    TempDialogItem->Next = DialogItem;
    DialogItem->Prev     = TempDialogItem;
  }

  return DialogItem;
}

BOOLEAN
IsSearchedFile (
  IN EFI_FILTER_FILE_TYPE   FileType,
  IN CHAR16                 *FileName
  )
/*++

Routine Description:

  varify if the File Name meets with the filter name.

Arguments:

  Filter    - the filter string.
  FileName  - the file name to be verified.

Returns:

  TRUE    - the FileName meets the Filter needs.
  FALSE   - the FileName can not meet the Filter.

--*/
{
  CHAR16  *Temp;
  CHAR16  *Str;

  if (FileType >= EFI_FILTER_FILE_TYPE_MAX  || FileName == NULL) {
    return FALSE;
  }
  if (FileType == EFI_FILTER_FILE_TYPE_ALL) {
    return TRUE;
  }

  if (SctStrLen (FileName) < SctStrLen (FileTypeInfo[FileType].FileTypeSuffix)) {
    return FALSE;
  }
  Temp = FileTypeInfo[FileType].FileTypeSuffix;

  Str = FileName + SctStrLen (FileName) - SctStrLen (Temp);

  if (SctStriCmp (Temp,Str) == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

CHAR16 *
AppendFileName (
  IN  CHAR16                *Str1,
  IN  CHAR16                *Str2
  )
/*++

Routine Description:

  Append one FileName to another File Name,remove the directory
  relation of '.' and '..'.

Arguments:

  Str1    - the file name to be appended.
  Str2    - the appended string.

Returns:

  appened file name.

--*/
{
  INTN       Size1;
  INTN       Size2;
  CHAR16     *Str;
  EFI_STATUS Status;

  Size1 = SctStrSize (Str1);
  Size2 = SctStrSize (Str2);
  Status = tBS->AllocatePool (
          EfiBootServicesData,
          Size1 + Size2 + sizeof(CHAR16),
          (VOID **)&Str
          );
  if (EFI_ERROR(Status)) {
    return NULL;
  }
  tBS->SetMem (Str, Size1 + Size2 + sizeof(CHAR16), 0);

  SctStrCat (Str, Str1);
  if ( !((*Str == '\\') && (*(Str + 1) == 0)) ) {
    SctStrCat (Str, L"\\");
  }

  //
  //skip the space before the filename.
  //
  while (*Str2 == L' ') {
    Str2 = Str2 +1;
  }

  SctStrCat (Str, Str2);

  return Str;
}

BOOLEAN
BuildDirDialog (
  IN  EFI_FILE_DIALOG_ITEM_CONTEXT   *ItemContext,
  IN  EFI_FILE_DIALOG                *DirDialog
  )
/*++

Routine Description:

  build one File Dialog based on the files and directories
  below current directory.

Arguments:

  ItemContext - the EFI_FILE_DIALOG_ITEM_CONTEXT instance poiter.
  DirDialog   - The EFI_FILE_DIALOG instance pointer.

Returns:

  TRUE        - the Dialog was built successfully.
  FALSE       - can not build the Dialog.

--*/
{
  EFI_FILE_HANDLE               NewDir;
  EFI_FILE_HANDLE               Dir;
  EFI_FILE_INFO                 *DirInfo;
  UINTN                         BufferSize;
  UINTN                         DirBufferSize;
  CHAR16                        Buffer[MAX_CHAR];
  EFI_STATUS                    Status;
  EFI_FILE_DIALOG_ITEM_CONTEXT  *Context;
  UINTN                         Pass;
  UINTN                         TotalDisplayLine;
  EFI_FILE_DIALOG_ITEM          *DialogItem;
  EFI_FILE_DIALOG_ITEM          *TempDialogItem;
  UINTN                         PassNumber;
  UINTN                         Y0;
  UINTN                         Y1;

  if (ItemContext == NULL || DirDialog == NULL) {
    return FALSE;
  }

  Dir = ItemContext->FHandle;
  //
  //open the sub directory
  //
  Status = Dir->Open (
                  Dir,
                  &NewDir,
                  ItemContext->FileName,
                  EFI_FILE_MODE_READ,
                  0
                  );

  if (!ItemContext->RootContext) {
    Dir->Close (Dir);
  }
  if (EFI_NOT_FOUND == Status) {
    Status = Dir->Open (
                Dir,
                &NewDir,
                ItemContext->FileName,
                EFI_FILE_MODE_CREATE|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                EFI_FILE_DIRECTORY
                );
    if (EFI_ERROR(Status)) {
      return FALSE;
    }
  } else if (EFI_ERROR(Status)) {
    return FALSE;
  }

  Status = SctGetFileInfo (NewDir, &DirInfo);
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  if (!(DirInfo->Attribute & EFI_FILE_DIRECTORY)) {
    return FALSE;
  }

  DirBufferSize = sizeof(EFI_FILE_INFO) + 1024;
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 DirBufferSize,
                 (VOID **)&DirInfo
                 );

  if (EFI_ERROR(Status)) {
    return FALSE;
  }
  //
  //if dialog type is select dir then only use pass one.
  //
  if (DirDialog->Type == EFI_FILE_DIALOG_TYPE_SELECT_DIR) {
    PassNumber = 1;
  } else {
    PassNumber = 2;
  }

  for (Pass = 1; Pass <= PassNumber; Pass++) {
    NewDir->SetPosition (NewDir, 0);
    for (;;) {

      BufferSize = DirBufferSize;

      Status = NewDir->Read (NewDir, &BufferSize, DirInfo);

      if (EFI_ERROR(Status) || BufferSize == 0) {
        break;
      }

      if ((DirInfo->Attribute & EFI_FILE_DIRECTORY && Pass == 2)
          || (!(DirInfo->Attribute & EFI_FILE_DIRECTORY) && Pass == 1)) {
        //
        // Pass 1 is for Directories
        // Pass 2 is for file names
        //
        continue;
      }

      if (DirInfo->Attribute & EFI_FILE_DIRECTORY ||
          !(IsSearchedFile (DirDialog->FileType,DirInfo->FileName))) {
        //
        // Slip file unless it is a directory entry or is searched  file type
        //
        continue;
      }
      SctSPrint (Buffer, MAX_CHAR, L" %s %s",
              DirInfo->Attribute & EFI_FILE_DIRECTORY ? L"<DIR>" : L" ",
              DirInfo->FileName
             );

      Status = tBS->AllocatePool (
                     EfiBootServicesData,
                     sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT),
                     (VOID **)&Context
                     );

      if (EFI_ERROR(Status)) {
        FreeDirDialog (DirDialog);
        NewDir->Close (NewDir);
        tBS->FreePool (DirInfo);
        return FALSE;
      }
      tBS->SetMem (Context,sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT),0);

      Context->Handle   = ItemContext->Handle;
      Context->FileName = AppendFileName (
                            ItemContext->FileName,
                            DirInfo->FileName
                            );

      Context->FHandle       = NewDir;
      Context->DevicePath    = SctDuplicateDevicePath (ItemContext->DevicePath);
      Context->DevicePathStr = SctDevicePathToStr (Context->DevicePath);
      Context->IsDir         = (BOOLEAN)((DirInfo->Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY);

      DialogItem = AllocateFileDialogItem (DirDialog, Buffer, Context);

      if (DialogItem == NULL) {
        FreeDirDialog (DirDialog);
        NewDir->Close (NewDir);
        tBS->FreePool (DirInfo);
        return FALSE;
      }
    }
  }

  TempDialogItem   = DirDialog->ItemList;
  TotalDisplayLine = 0;

  DirDialog->FirstInDisplay  = DirDialog->ItemList;
  DirDialog->CurrentSelected = DirDialog->ItemList;
  //
  //caculate the postion of LastInDisplay
  //
  Y0 = DirDialog->BodyRect.TopLeft.Row;
  Y1 = DirDialog->BodyRect.BottomRight.Row;
  while (TempDialogItem   && TotalDisplayLine < (Y1 - Y0 -1)) {
    TotalDisplayLine = TotalDisplayLine + 1;
    if (TempDialogItem->Next && TotalDisplayLine < (Y1 - Y0 -1)) {
      TempDialogItem = TempDialogItem->Next;
    } else {
      break;
    }
  }
  DirDialog->LastInDisplay = TempDialogItem;

  tBS->FreePool (DirInfo);

  return TRUE;
}

BOOLEAN
FindAFileInDialog (
  IN  EFI_FILE_DIALOG_ITEM_CONTEXT  *ItemContext,
  IN  EFI_FILE_DIALOG               *DirDialog,
  IN  OUT EFI_FILE_DIALOG_CONTEXT   *DialogContext
  )
/*++

Routine Description:

  Get a file in current file system.

Arguments:

  ItemContext   - the EFI_FILE_DIALOG_ITEM_CONTEXT instance poiter.
  DialogContext - The FILE_DIALOG_CONTEXT,it contains filter filename string.
  DirDialog     - The EFI_FILE_DIALOG instance pointer.

Returns:

  TRUE    - the file was found.
  FALSE   - not found the file in current file system.

--*/
{
  EFI_FILE_DIALOG_ITEM_CONTEXT    *ResultContext;
  EFI_FILE_DIALOG_ITEM_CONTEXT    ContextCopy;
  EFI_INPUT_KEY                   Key;
  EFI_STATUS                      Status;
  EFI_FILE_HANDLE                 FHandle;
  EFI_FILE_HANDLE                 TempHandle;
  BOOLEAN                         RET;
  CHAR16                          *TempName;
  INTN                            Length;
  INTN                            Index;
  BOOLEAN                         ResultContextWasNull;

  if (ItemContext == NULL || DirDialog == NULL || DialogContext == NULL ) {
    return FALSE;
  }

  RET = FALSE;

  Status = BuildDirDialog (ItemContext, DirDialog);

  if  (EFI_ERROR(Status)) {
    return FALSE;
  }
  tBS->SetMem ((VOID *)&ContextCopy, sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT), 0);

  for (;;) {

    ResultContext =(EFI_FILE_DIALOG_ITEM_CONTEXT*) DisplayFileDialog (DirDialog, &Key);

    if (ResultContext == NULL) {
      ResultContext = ItemContext;
      ResultContextWasNull = TRUE;
    } else {
      ResultContextWasNull = FALSE;
    }
    TempHandle = ResultContext->FHandle;

    //
    //set the new file
    //
    if (DialogContext->FileName != NULL) {
      tBS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      tBS->FreePool (DialogContext->DevicePath);
    }

    //
    //set the FileName and DevicePath
    //
    if (SctStrBeginWith (DirDialog->FileName, L"\\")) {
      DialogContext->FileName = SctStrDuplicate (DirDialog->FileName);
      if (DialogContext->FileName == NULL) {
        return FALSE;
      }
    } else {

      //
      //first remove the last file name in ResultContext->FileName
      // get current directory
      //
      if (ResultContextWasNull == FALSE) {
        Length = SctStrLen (ResultContext->FileName);
        if (Length > 0) {
          TempName = ResultContext->FileName;
          for (Index = Length - 1; Index >= 0; Index --) {
            if (TempName[Index] == L'\\') {
              TempName[Index] = L'\0';
              break;
            }
          }
        }
      }

      //
      //append the file name inputed in edit area into current directory
      //
      DialogContext->FileName = AppendFileName (
                                  ResultContext->FileName,
                                  DirDialog->FileName
                                  );
      if (DialogContext->FileName == NULL) {
        return FALSE;
      }

      DialogContext->DevicePath = SctDuplicateDevicePath (ResultContext->DevicePath);
      RET = TRUE;
      break;
    }
  }
  //
  //close the current Dir File Handle if it is not The Root Dir.
  //
  if (DirDialog->ItemList  != NULL && DirDialog->ItemList->Context &&
      !((EFI_FILE_DIALOG_ITEM_CONTEXT *)DirDialog->ItemList->Context)->RootContext) {

    FHandle = ((EFI_FILE_DIALOG_ITEM_CONTEXT *)DirDialog->ItemList->Context)->FHandle;
    FHandle->Close (FHandle);
  }
  //
  //free the dir dialog items.
  //
  FreeDirDialog (DirDialog);
  return RET;
}

EFI_STATUS
DoFileDialog (
 IN OUT EFI_FILE_DIALOG_CONTEXT   *DialogContext
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
  EFI_FILE_DIALOG                 *FileSystemDialog;
  EFI_FILE_DIALOG                 *DirDialog;
  CHAR16                          Buffer[MAX_CHAR];
  EFI_HANDLE                      FsHandles;
  EFI_FILE_DIALOG_ITEM            *TempDialogItem;
  EFI_FILE_DIALOG_ITEM_CONTEXT    *ResultContext;
  EFI_FILE_DIALOG_ITEM_CONTEXT    *Context;
  CHAR16                          *Str;
  CHAR16                          *Str1;
  UINTN                           TotalDisplayLine;
  UINTN                           ConAttrib;
  UINTN                           Y0;
  UINTN                           Y1;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;

  if (DialogContext == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status                = EFI_SUCCESS;
  ConAttrib             = tST->ConOut->Mode->Attribute;
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG),
                 (VOID **)&FileSystemDialog
                 );
  if (EFI_ERROR(Status)) {
    return EFI_OUT_OF_RESOURCES;
  }
  tBS->SetMem (FileSystemDialog, sizeof(EFI_FILE_DIALOG), 0);

  FileSystemDialog->Type = DialogContext->DialogType;

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 (EFI_MAX_EDIT_LENGTH + 1) * sizeof(CHAR16),
                 (VOID **)&FileSystemDialog->FileName
                 );
  if (EFI_ERROR(Status)) {
    FreeFileSystemDialog (FileSystemDialog);
    return EFI_OUT_OF_RESOURCES;
  }
  FileSystemDialog->FileName[0] = L'\0';
  //
  //initialize the item values
  //
  FileSystemDialog->BodyRect.TopLeft.Row      = 5;
  FileSystemDialog->BodyRect.TopLeft.Col      = 10;
  FileSystemDialog->BodyRect.BottomRight.Row  = 16;
  FileSystemDialog->BodyRect.BottomRight.Col  = 65;

  FileSystemDialog->ForeColor = EFI_POPUP_MENU_FORECOLOR;
  FileSystemDialog->BackColor = EFI_POPUP_MENU_BACKCOLOR;

  FileSystemDialog->FileType = DialogContext->FileType;
  if (FileSystemDialog->FileType >= EFI_FILTER_FILE_TYPE_MAX ) {
     FileSystemDialog->FileType = EFI_FILTER_FILE_TYPE_ALL;
  }

  DevicePath = gFT->DevicePath;
  Status = tBS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &DevicePath,
                 &FsHandles
                 );
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  Status = tBS->AllocatePool (
          EfiBootServicesData,
          sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT),
          (VOID **)&Context
          );

  if (EFI_ERROR(Status)) {
    FreeFileSystemDialog (FileSystemDialog);
    return EFI_OUT_OF_RESOURCES;
  }
  tBS->SetMem (Context, sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT), 0);

  //
  //Find current file system device path
  //
  Context->Handle         = FsHandles;
  Context->FHandle        = SctOpenRoot (Context->Handle);
  Context->DevicePath     = SctDevicePathFromHandle (Context->Handle);
  Context->DevicePathStr  = SctDevicePathToStr (Context->DevicePath);

  //
  //Append dir path
  //
  if (DialogContext->FileType == EFI_FILTER_FILE_TYPE_CSV) {
    Context->FileName       = SctPoolPrint(L"%s\\%s", gFT->FilePath, EFI_SCT_PATH_REPORT);
  } else if (DialogContext->FileType == EFI_FILTER_FILE_TYPE_SEQ) {
    Context->FileName       = SctPoolPrint(L"%s\\%s", gFT->FilePath, EFI_SCT_PATH_SEQUENCE);
  } else {
    Context->FileName       = SctStrDuplicate (gFT->FilePath);
  }

  Context->IsDir          = TRUE;
  Context->RootContext    = TRUE;

  if (Context->FHandle == NULL || Context->DevicePath == NULL ||
      Context->FileName == NULL) {
    FreeFileSystemDialogItemContext (Context);
    return EFI_DEVICE_ERROR;
  }

  //
  //get file system map from devicepath
  //
  Str = NULL;
  Status = SctMapNameFromDevice (Context->DevicePath, &Str);
  if (!EFI_ERROR(Status)) {
    SctSPrint (Buffer, MAX_CHAR, L"%s:", Str);
    tBS->FreePool (Str);
  } else {
    FreeFileSystemDialogItemContext (Context);
    return EFI_DEVICE_ERROR;
  }

  if (DialogContext->FileType == EFI_FILTER_FILE_TYPE_CSV) {
    Str1 = SctPoolPrint(L"%s%s\\%s", Buffer, gFT->FilePath, EFI_SCT_PATH_REPORT);
  } else if (DialogContext->FileType == EFI_FILTER_FILE_TYPE_SEQ) {
    Str1 = SctPoolPrint(L"%s%s\\%s", Buffer, gFT->FilePath, EFI_SCT_PATH_SEQUENCE);
  } else {
    Str1 = SctPoolPrint(L"%s%s", Buffer, gFT->FilePath);
  }
  if (Str1 == NULL) {
    FreeFileSystemDialogItemContext (Context);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //set Dialog Title based on the dialog type
  //
  switch (FileSystemDialog->Type) {
    case EFI_FILE_DIALOG_TYPE_OPEN_FILE:
      FileSystemDialog->Title = SctPoolPrint(L"%s:  %s", L"    Open File", Str1);
      break;

    case EFI_FILE_DIALOG_TYPE_SAVE_FILE:
      FileSystemDialog->Title = SctPoolPrint(L"%s:  %s", L"    Save File", Str1);
      break;

    default:
      FileSystemDialog->Type  = EFI_FILE_DIALOG_TYPE_OPEN_FILE;
      FileSystemDialog->Title = SctStrDuplicate (L"Open File");
      break;
  }

  if ( FileSystemDialog->Title == NULL ) {
    FreeFileSystemDialog (FileSystemDialog);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //add a new menu item
  //
  TempDialogItem = AllocateFileDialogItem (FileSystemDialog, Buffer, Context);
  if (TempDialogItem == NULL) {
    FreeFileSystemDialog (FileSystemDialog);
    FreeFileSystemDialogItemContext (Context);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //Set the pointer of FileSystemDialog CurrentSelected,FirstInDisplay,LastInDisplay.
  //
  TempDialogItem   = FileSystemDialog->ItemList;
  TotalDisplayLine = 0;

  FileSystemDialog->FirstInDisplay  = FileSystemDialog->ItemList;
  FileSystemDialog->CurrentSelected = FileSystemDialog->ItemList;

  Y0 = FileSystemDialog->BodyRect.TopLeft.Row;
  Y1 = FileSystemDialog->BodyRect.BottomRight.Row;

  while (TempDialogItem  && TotalDisplayLine < (Y1 - Y0 -1)) {
    TotalDisplayLine = TotalDisplayLine + 1;
    if (TempDialogItem->Next && TotalDisplayLine < (Y1 - Y0 -1)) {
      TempDialogItem = TempDialogItem->Next;
    } else {
      break;
    }
  }
  FileSystemDialog->LastInDisplay = TempDialogItem;

  Status = tBS->AllocatePool (
          EfiBootServicesData,
          sizeof(EFI_FILE_DIALOG),
          (VOID **)&DirDialog
          );

  if (EFI_ERROR(Status)) {
    FreeFileSystemDialog (FileSystemDialog);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //share the FileSystemDialog's info so copy mem from FileSystemDialog.
  //
  tBS->CopyMem (DirDialog, FileSystemDialog, sizeof(EFI_FILE_DIALOG));

  //
  //initialize the default pointer and item values
  //
  DirDialog->CurrentArea     = FILE_DIALOG_MENU_AREA;
  DirDialog->FileName[0]     = L'\0';
  DirDialog->ItemList        = NULL;
  DirDialog->FirstInDisplay  = NULL;
  DirDialog->LastInDisplay   = NULL;
  DirDialog->CurrentSelected = NULL;

  ResultContext = FileSystemDialog->CurrentSelected->Context;

  FindAFileInDialog (ResultContext, DirDialog , DialogContext);

  //  ProccessFileName (DialogContext->FileName);
  if (DirDialog->FileName[0] == L'\0') {
    DialogContext->FileName[0] = L'\0';
  }
  //
  //free MenuItems and relative Context.
  //
  FreeDirDialog (DirDialog);
  tBS->FreePool (DirDialog);
  FreeFileSystemDialog(FileSystemDialog);

  //
  //restore original console attribute
  //
  tST->ConOut->SetAttribute ( tST->ConOut,ConAttrib);

  return EFI_SUCCESS;
}
