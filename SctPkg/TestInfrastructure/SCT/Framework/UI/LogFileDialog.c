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

  FileDialog.c

Abstract:

  This file provides the services for File Dialog.

--*/
#include "Sct.h"
#include "UI.h"
#include "BuildMenu.h"
#include "LogFileDialog.h"

//
//File Type Info definition
//

STATIC EFI_FILE_TYPE_INFO FileTypeInfo[] = {
  { L".*"   , L"All Files, (*.*)"       },
  { L".log" , L"Log Files, (*.log)"     },
  { L".ekl" , L"Key Files, (*.ekl)"     },
  { L".txt" , L"Text Files, (*.txt)"    },
  { L".doc" , L"Doc Files, (*.doc)"     },
  { L".bat" , L"Batch Files, (*.bat)"   },
  { L".ini" , L"Ini Files, (*.ini)"     },
  { L".seq" , L"Sequence Files,(*.seq)" },
  { L".h" ,   L"Header Files, (*.h)"    },
  { L".c" ,   L"'C' Files, (*.c)"       },
  { L".efi" , L"EFI Files, (*.efi)"     },
  { L".csv" , L"CSV Files (*.csv)"      }
};

//
// protypes (external)
//

EFI_STATUS
DoLogFileDialog (
 IN OUT EFI_FILE_DIALOG_CONTEXT   *DialogContext
  );

//
// protypes (internal)
//

EFI_STATUS
LogFreeFileSystemDialog (
  IN EFI_FILE_DIALOG              *Dialog
  );

EFI_STATUS
LogFreeDirDialog (
  IN EFI_FILE_DIALOG              *Dialog
  );

EFI_STATUS
LogFileDialogItemRefresh (
  IN EFI_FILE_DIALOG              *LogFileDialog,
  IN EFI_FILE_DIALOG_ITEM         *Item
  );

EFI_STATUS
LogDialogInputRefresh (
  IN EFI_FILE_DIALOG              *LogFileDialog
  );

EFI_STATUS
LogFileDialogRefresh (
  IN EFI_FILE_DIALOG              *LogFileDialog,
  IN BOOLEAN                      RefreshAll
  );

EFI_STATUS
LogFileDialogUpFunc (
  EFI_FILE_DIALOG                 *LogFileDialog
  );

EFI_STATUS
LogFileDialogDownFunc (
  EFI_FILE_DIALOG                 *LogFileDialog
  );

EFI_STATUS
LogFileDialogPageUpFunc (
  EFI_FILE_DIALOG                 *LogFileDialog
  );

EFI_STATUS
LogFileDialogPageDownFunc(
  EFI_FILE_DIALOG                 *LogFileDialog
  );

VOID *
DisplayLogFileDialog (
  IN  EFI_FILE_DIALOG             *Dialog,
  IN  EFI_INPUT_KEY               *Key
  );

EFI_FILE_DIALOG_ITEM *
AllocateLogFileDialogItem (
  IN EFI_FILE_DIALOG              *Dialog,
  IN UINT16                       *String,
  IN VOID                         *Context
  );

BOOLEAN
LogIsSearchedFile (
  IN EFI_FILTER_FILE_TYPE         FileType,
  IN CHAR16                       *FileName
  );
BOOLEAN
LogBuildDirDialog (
  IN  EFI_FILE_DIALOG_ITEM_CONTEXT    *ItemContext,
  IN  EFI_FILE_DIALOG                 *DirDialog
  );

BOOLEAN
LogFindAFileInDialog (
  IN  EFI_FILE_DIALOG_ITEM_CONTEXT    *ItemContext,
  IN  EFI_FILE_DIALOG                 *DirDialog,
  IN  OUT EFI_FILE_DIALOG_CONTEXT     *DialogContext
  );

BOOLEAN
DoLogFileDialogInSpecifiedDir(
 IN OUT EFI_FILE_DIALOG_CONTEXT       *DialogContext
  );

EFI_STATUS
LogFreeFileSystemDialogItemContext (
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
LogProccessFileName (
  IN CHAR16                       *FileName
  )
{
  INTN            Length;
  INTN            Index;

  if (FileName == NULL) {
    return EFI_SUCCESS;
  }

  Length = (INTN)SctStrLen (FileName);

  //
  //replace "xx\xx\.." with "xx"
  //
  if (Length > 3) {
    if (FileName[Length - 1] == L'.' && FileName[Length - 2] == L'.' &&
        FileName[Length - 3] == L'\\' ) {
      FileName[Length - 3] = '\0';
      Length = (INTN)SctStrLen (FileName);
      for (Index = (Length - 1);Index >= 0; Index --) {
        if (FileName[Index] == L'\\') {
          FileName[Index] = '\0';
          break;
        }
      }
    }
  }

  //
  //replace "xxx\." with "xxx"
  //
  if (Length >= 2) {
    if (FileName[Length - 1] == L'.' && FileName[Length - 2] == L'\\') {
      FileName[Length - 2] = '\0';
    }
  }

  //
  //make sure the file name begin with "\"
  //
  if (SctStrLen (FileName) == 0) {
    SctStrCat (FileName, L"\\");
  }
  return EFI_SUCCESS;
}


EFI_STATUS
LogFreeFileSystemDialog (
  IN EFI_FILE_DIALOG              *Dialog
  )
/*++

Routine Description:

  Free file system Dialog Items and relative Context.

Arguments:

  Dialog        - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS   - the resource was freed successfully.

--*/
{
  EFI_FILE_DIALOG_ITEM               *DialogItem;
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
      LogFreeFileSystemDialogItemContext (ItemContext);
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
LogFreeDirDialog (
  IN EFI_FILE_DIALOG              *Dialog
  )
/*++

Routine Description:

  Free directory Dialog Items Item Context but don't free the Dialog' Title
  and FileName.

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
LogFileDialogItemRefresh (
  IN EFI_FILE_DIALOG              *LogFileDialog,
  IN EFI_FILE_DIALOG_ITEM         *Item
  )
/*++

Routine Description:

  Refresh one item.

Arguments:

  LogFileDialog         - The EFI_FILE_DIALOG instance pointer.
  Item                  - The EFI_FILE_DIALOG_ITEM instance poiter.

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

  if (LogFileDialog == NULL ||Item == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;

  X0 = LogFileDialog->BodyRect.TopLeft.Col;
  Y0 = LogFileDialog->BodyRect.TopLeft.Row;
  X1 = LogFileDialog->BodyRect.BottomRight.Col;

  //
  //caculate Item offset in lines.
  //
  Line = 0;
  TempDialogItem = LogFileDialog->FirstInDisplay;
  while (TempDialogItem != NULL && TempDialogItem != Item) {
    Line++;
    TempDialogItem = TempDialogItem->Next;
  }
  Line++;

  //
  //based on current dialog staus set the console attribute
  //
  if (TempDialogItem == LogFileDialog->CurrentSelected &&
      LogFileDialog->CurrentArea == FILE_DIALOG_MENU_AREA) {
    tST->ConOut->SetAttribute (
                  tST->ConOut,
                  EFI_TEXT_ATTR(LogFileDialog->BackColor, LogFileDialog->ForeColor)
                  );
  } else if (TempDialogItem == LogFileDialog->CurrentSelected) {
    tST->ConOut->SetAttribute (
                  tST->ConOut,
                  EFI_TEXT_ATTR(LogFileDialog->BackColor, EFI_LIGHTGRAY)
                  );
  } else {
    tST->ConOut->SetAttribute (
                  tST->ConOut,
                  EFI_TEXT_ATTR(LogFileDialog->ForeColor, LogFileDialog->BackColor)
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

  if (TempDialogItem == LogFileDialog->CurrentSelected) {
    tST->ConOut->SetAttribute (
                  tST->ConOut,
                  EFI_TEXT_ATTR(LogFileDialog->ForeColor, LogFileDialog->BackColor)
                  );
  }
  return Status;
}

EFI_STATUS
LogDialogInputRefresh (
  IN EFI_FILE_DIALOG              *LogFileDialog
  )
/*++

Routine Description:

  refresh the LogFileDialog input area.

Arguments:

  LogFileDialog - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS   - the input area was refreshed successfully.

--*/
{
  UINTN       Xpos;
  UINTN       Ypos;
  CHAR16      Buffer[EFI_MAX_ITEM_VALUE_LENGTH + 1];
  UINTN       Length;
  UINTN       Index;
  EFI_STATUS  Status;

  Xpos = LogFileDialog -> BodyRect.TopLeft.Col + 20;
  Ypos = LogFileDialog -> BodyRect.BottomRight.Row + 1;
  Length = SctStrLen (LogFileDialog->FileName);
  if (Length > EFI_MAX_ITEM_VALUE_LENGTH) {
    tBS->CopyMem (
      Buffer,
      LogFileDialog->FileName,
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

    tBS->CopyMem (Buffer, LogFileDialog->FileName, (Length + 1) * sizeof(CHAR16));
  }
  //
  //print the input string
  //
  Status = TestPrintAt (Xpos, Ypos, Buffer);

  return Status;
}

EFI_STATUS
LogFileDialogRefresh (
  IN EFI_FILE_DIALOG              *LogFileDialog,
  IN BOOLEAN                      RefreshAll
  )
/*++

Routine Description:

  refresh the LogFileDialog.

Arguments:

  LogFileDialog         - The EFI_FILE_DIALOG instance pointer.

Returns:

  EFI_SUCCESS           - the LogFileDialog was rendered successfully.
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

  if (LogFileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  DialogItem = NULL;

  X0 = LogFileDialog->BodyRect.TopLeft.Col;
  Y0 = LogFileDialog->BodyRect.TopLeft.Row;
  X1 = LogFileDialog->BodyRect.BottomRight.Col;
  Y1 = LogFileDialog->BodyRect.BottomRight.Row;

  if ((X1 < X0 + 45) || (Y1 < Y0 + 5)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;

  tST->ConOut->SetAttribute (
                tST->ConOut,
                EFI_TEXT_ATTR(LogFileDialog->ForeColor,
                LogFileDialog->BackColor)
                );

  if (RefreshAll) {

    for (Index = 0; Index < X1 - X0 + 1; Index++) {
      Buffer[Index] = L' ';
    }
    Buffer[Index] = L'\0';
    //
    //clear the Dialog Rect Area.
    //
    for (SubIndex = Y0 - 1; SubIndex <= Y1 + 2; SubIndex++) {
      Status = TestPrintAt (X0, SubIndex, Buffer);
      if (EFI_ERROR(Status)) {
        return Status;
      }
    }
    //
    //display the title
    //
    if (LogFileDialog->Title != NULL) {
      LogFileDialog->Title[X1 - X0] = L'\0';
      TestPrintAt (X0, Y0 - 1, LogFileDialog->Title);
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

    //
    //display the "File Name:" or "Dir Name:"
    //
    if (LogFileDialog->Type == EFI_FILE_DIALOG_TYPE_SELECT_DIR) {
      TestPrintAt (X0 + 4, Y1 + 1, L"Dir Name:");
    } else {
      TestPrintAt (X0 + 4, Y1 + 1, L"File Name:");
    }

    TestPrintAt (X0 + 19, Y1 + 1, L"[");
    TestPrintAt (X0 + 40, Y1 + 1, L"]");


    if (LogFileDialog->FileName != NULL && LogFileDialog->ItemList != NULL ) {
      Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(LogFileDialog->CurrentSelected->Context);
      if (!Context->RootContext) {
        //
        //reset the file name to current selected item file name
        //
        ShortName = NULL;
        ShortName = SctGetShortFileNameAndExt (Context->FileName);
        if (ShortName != NULL) {
          SctStrCpy (LogFileDialog->FileName, ShortName);
        } else {
          return EFI_OUT_OF_RESOURCES;
        }
        //
        //display File Name.
        //
        if (SctStrLen (LogFileDialog->FileName) > EFI_MAX_ITEM_VALUE_LENGTH) {
          tBS->CopyMem (
            Buffer,
            LogFileDialog->FileName,
            EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16)
            );
          Buffer[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';
          TestPrintAt (X0 + 20, Y1 + 1, Buffer);
        } else {
          TestPrintAt (X0 + 20, Y1 + 1, LogFileDialog->FileName);
        }
      }
    }

    //
    //display the file type info
    //
    if (LogFileDialog->Type == EFI_FILE_DIALOG_TYPE_OPEN_FILE) {
      TestPrintAt (X0 + 4, Y1 + 2, L"Files of type:");
      TestPrintAt (
        X0 + 19,
        Y1 + 2,
        FileTypeInfo[LogFileDialog->FileType].FileTypeDesc
        );
    } else if (LogFileDialog->Type == EFI_FILE_DIALOG_TYPE_SAVE_FILE) {
      TestPrintAt (X0 + 4, Y1 + 2, L"Save as type:");
      TestPrintAt (
        X0 + 19,
        Y1 + 2,
        FileTypeInfo[LogFileDialog->FileType].FileTypeDesc
        );
    } else {
      TestPrintAt (X0 + 10, Y1 + 2, L"Press ESC to return and F1 to Save");
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
  if (NULL == LogFileDialog->CurrentSelected || NULL == LogFileDialog->ItemList) {
    return EFI_SUCCESS;
  }

  Ypos = Y0 + 1;

  DialogItem = LogFileDialog->FirstInDisplay;
  while (DialogItem != NULL && DialogItem != LogFileDialog->LastInDisplay->Next) {
    if (DialogItem == LogFileDialog->CurrentSelected &&
        LogFileDialog->CurrentArea == FILE_DIALOG_MENU_AREA) {
      tST->ConOut->SetAttribute (
                    tST->ConOut,
                    EFI_TEXT_ATTR(LogFileDialog->BackColor, LogFileDialog->ForeColor)
                    );
    } else if (DialogItem == LogFileDialog->CurrentSelected) {
      tST->ConOut->SetAttribute (
                    tST->ConOut,
                    EFI_TEXT_ATTR(LogFileDialog->BackColor, EFI_LIGHTGRAY)
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
    if (DialogItem == LogFileDialog->CurrentSelected) {
      tST->ConOut->SetAttribute (
                    tST->ConOut,
                    EFI_TEXT_ATTR(LogFileDialog->ForeColor, LogFileDialog->BackColor)
                    );
    }

    Ypos = Ypos + 1;

    DialogItem = DialogItem->Next;
  }
  return Status;
}

EFI_STATUS
LogFileDialogUpFunc (
  EFI_FILE_DIALOG                 *LogFileDialog
  )
/*++

Routine Description:

  response to UP key.

Arguments:

  LogFileDialog         - The EFI_FILE_DIALOG instance pointer.

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

  if (LogFileDialog  == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // if there was no item to display return EFI_SUCCESS.
  //
  if ( LogFileDialog->ItemList == NULL || LogFileDialog->CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  Status              = EFI_SUCCESS;
  CurrentPointedLine  = 0;
  DialogItem          = LogFileDialog->FirstInDisplay;

  //
  //caculate current selected line offset
  //
  while (DialogItem != NULL && DialogItem != LogFileDialog->CurrentSelected) {
    CurrentPointedLine++;
    DialogItem = DialogItem->Next;
  }
  CurrentPointedLine++;

  DialogItem = LogFileDialog->CurrentSelected;

  //
  //caculate if need scroll
  //
  if (DialogItem->Prev == NULL || (CurrentPointedLine >= 2)) {
    SCROLLING = FALSE;
  } else {
    SCROLLING = TRUE;
  }

  if (SCROLLING) {
    LogFileDialog->FirstInDisplay  = LogFileDialog->FirstInDisplay->Prev;
    LogFileDialog->CurrentSelected = LogFileDialog->CurrentSelected->Prev;
    LogFileDialog->LastInDisplay   = LogFileDialog->LastInDisplay->Prev;

    Status = LogFileDialogRefresh(LogFileDialog,FALSE);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    //
    //if is in File System Dialog the Edit area don't need to refresh
    //
    Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(LogFileDialog->CurrentSelected->Context);
    if (Context->RootContext) {
      return EFI_SUCCESS;
    }

    //
    //reset the current selected File Name.
    //
    ShortName = NULL;
    ShortName = SctGetShortFileNameAndExt (Context->FileName);
    if (ShortName != NULL) {
      SctStrCpy (LogFileDialog->FileName, ShortName);
    } else {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //refresh the file name display
    //
    Status = LogDialogInputRefresh (LogFileDialog);
    return Status;

  } else {

    if (LogFileDialog->CurrentSelected->Prev != NULL) {
      LogFileDialog->CurrentSelected =  LogFileDialog->CurrentSelected->Prev;
      //
      //refresh two changed item
      //
      Status = LogFileDialogItemRefresh (
                 LogFileDialog,
                 LogFileDialog->CurrentSelected->Next
                 );
      if (EFI_ERROR (Status) ) {
        return Status;
      }

      Status = LogFileDialogItemRefresh (
                 LogFileDialog,
                 LogFileDialog->CurrentSelected
                 );
      if (EFI_ERROR(Status)) {
        return Status;
      }
      //
      // root File System dialog don't need to refresh the Edit area
      //
      Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(LogFileDialog->CurrentSelected->Context);
      if (Context->RootContext) {
        return EFI_SUCCESS;
      }
      //
      //reset the current selected File Name
      //
      ShortName = NULL;
      ShortName = SctGetShortFileNameAndExt (Context->FileName);
      if (ShortName != NULL) {
        SctStrCpy (LogFileDialog->FileName, ShortName);
      } else {
        return EFI_OUT_OF_RESOURCES;
      }
      //
      //refresh the file name display
      //
      Status = LogDialogInputRefresh (LogFileDialog);
      return Status;
    }
    //
    //no item changed so don't need to refresh
    //
    return EFI_SUCCESS;
  }
}

EFI_STATUS
LogFileDialogDownFunc (
  EFI_FILE_DIALOG                 *LogFileDialog
  )
/*++

Routine Description:

  response to DOWN key.

Arguments:

  LogFileDialog         - The EFI_FILE_DIALOG instance pointer.

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

  if (LogFileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // if there was no item to display return EFI_SUCCESS.
  //
  if ( LogFileDialog->ItemList == NULL || LogFileDialog->CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  if (LogFileDialog->CurrentArea == FILE_DIALOG_EDIT_AREA) {
    return EFI_SUCCESS;
  }

  Status              = EFI_SUCCESS;
  TotalLines          = LogFileDialog->BodyRect.BottomRight.Row - LogFileDialog->BodyRect.TopLeft.Row - 1;
  CurrentPointedLine  = 0;
  DialogItem          = LogFileDialog->FirstInDisplay;

  //
  //caculate current selected line offset
  //
  while (DialogItem != NULL && DialogItem != LogFileDialog->CurrentSelected) {
    CurrentPointedLine++;
    DialogItem = DialogItem->Next;
  }
  CurrentPointedLine++;
  DialogItem = LogFileDialog->CurrentSelected;

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
    LogFileDialog->FirstInDisplay  = LogFileDialog->FirstInDisplay->Next;
    LogFileDialog->CurrentSelected = LogFileDialog->CurrentSelected->Next;
    LogFileDialog->LastInDisplay   = LogFileDialog->LastInDisplay->Next;

    //
    //refresh the items
    //
    Status = LogFileDialogRefresh (LogFileDialog, FALSE);
    if (EFI_ERROR(Status)) {
      return Status;
    }
    Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(LogFileDialog->CurrentSelected->Context);
    if (Context->RootContext) {
      return EFI_SUCCESS;
    }
    //
    //reset the current selected File Name
    //
    ShortName = NULL;
    ShortName = SctGetShortFileNameAndExt (Context->FileName);
    if (ShortName != NULL) {
      SctStrCpy (LogFileDialog->FileName, ShortName);
    } else {
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //refresh the file name display
    //
    Status = LogDialogInputRefresh (LogFileDialog);
    return Status;

  } else {

    if (LogFileDialog->CurrentSelected->Next != NULL) {
      LogFileDialog->CurrentSelected =  LogFileDialog->CurrentSelected->Next;
      //
      //refresh two changed item
      //
      Status = LogFileDialogItemRefresh (
                 LogFileDialog,
                 LogFileDialog->CurrentSelected->Prev
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }

      Status = LogFileDialogItemRefresh (
                 LogFileDialog,
                 LogFileDialog->CurrentSelected
                 );
      if (EFI_ERROR(Status)) {
        return Status;
      }
      Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(LogFileDialog->CurrentSelected->Context);
      if (Context->RootContext) {
        return EFI_SUCCESS;
      }
      //
      //reset the current selected File Name
      //
      ShortName = NULL;
      ShortName = SctGetShortFileNameAndExt (Context->FileName);
      if (ShortName != NULL) {
        SctStrCpy (LogFileDialog->FileName, ShortName);
      } else {
        return EFI_OUT_OF_RESOURCES;
      }
      //
      //refresh the file name display
      //
      Status = LogDialogInputRefresh (LogFileDialog);
      return Status;
    }
    return EFI_SUCCESS;
  }
}

EFI_STATUS
LogFileDialogPageUpFunc (
  EFI_FILE_DIALOG                 *LogFileDialog
  )
/*++

Routine Description:

  response to Page Up key.

Arguments:

  LogFileDialog         - The EFI_FILE_DIALOG instance pointer.

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

  if (LogFileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // if there was no item to display return EFI_SUCCESS.
  //
  if ( LogFileDialog->ItemList == NULL || LogFileDialog->CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  if (LogFileDialog->CurrentArea == FILE_DIALOG_EDIT_AREA) {
    return EFI_SUCCESS;
  }

  //
  //there is no item before current selected item, so return EFI_SUCCCSS.
  //
  if (LogFileDialog->CurrentSelected->Prev == NULL) {
    return EFI_SUCCESS;
  }

  if (LogFileDialog->CurrentSelected != LogFileDialog->FirstInDisplay) {
    DialogItem = LogFileDialog->CurrentSelected;
    LogFileDialog->CurrentSelected = LogFileDialog->FirstInDisplay;

    //
    //refresh the two items.
    //
    Status = LogFileDialogItemRefresh (
               LogFileDialog,
               DialogItem
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = LogFileDialogItemRefresh (
               LogFileDialog,
               LogFileDialog->CurrentSelected
               );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  } else {
    TotalLines = LogFileDialog->BodyRect.BottomRight.Row - LogFileDialog->BodyRect.TopLeft.Row - 1;
    //
    //move the first in display and last in display pointer up at most
    //'totalLines' line.
    //
    for (Index = 0; Index < TotalLines; Index ++) {
      LogFileDialog->FirstInDisplay = LogFileDialog->FirstInDisplay->Prev;
      LogFileDialog->LastInDisplay  = LogFileDialog->LastInDisplay->Prev;
      if (LogFileDialog->FirstInDisplay->Prev == NULL) {
        break;
      }
    }
    LogFileDialog->CurrentSelected = LogFileDialog->FirstInDisplay;

    //
    //refresh the items
    //
    Status = LogFileDialogRefresh (LogFileDialog, FALSE);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  //at last refresh the edit area.
  //
  Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(LogFileDialog->CurrentSelected->Context);
  if (Context->RootContext) {
    return EFI_SUCCESS;
  }

  //
  //reset the current selected File Name
  //
  ShortName = NULL;
  ShortName = SctGetShortFileNameAndExt (Context->FileName);
  if (ShortName != NULL) {
    SctStrCpy (LogFileDialog->FileName, ShortName);
  } else {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //refresh the file name display
  //
  Status = LogDialogInputRefresh (LogFileDialog);
  return Status;
}

EFI_STATUS
LogFileDialogPageDownFunc (
  EFI_FILE_DIALOG                 *LogFileDialog
  )
/*++

Routine Description:

  response to Page Down key.

Arguments:

  LogFileDialog         - The EFI_FILE_DIALOG instance pointer.

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

  if (LogFileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // if there was no item to display return EFI_SUCCESS.
  //
  if ( LogFileDialog->ItemList == NULL || LogFileDialog->CurrentSelected == NULL) {
    return EFI_SUCCESS;
  }

  if (LogFileDialog->CurrentArea == FILE_DIALOG_EDIT_AREA) {
    return EFI_SUCCESS;
  }

  //
  //there is no item behind current selected item, so return EFI_SUCCCSS.
  //
  if (LogFileDialog->CurrentSelected->Next == NULL) {
    return EFI_SUCCESS;
  }

  if (LogFileDialog->CurrentSelected != LogFileDialog->LastInDisplay) {
    DialogItem = LogFileDialog->CurrentSelected;
    LogFileDialog->CurrentSelected = LogFileDialog->LastInDisplay;
    //
    //refresh the two items.
    //
    Status = LogFileDialogItemRefresh (
               LogFileDialog,
               DialogItem
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = LogFileDialogItemRefresh (
               LogFileDialog,
               LogFileDialog->CurrentSelected
               );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  } else {
    TotalLines = LogFileDialog->BodyRect.BottomRight.Row - LogFileDialog->BodyRect.TopLeft.Row - 1;
    //
    //move the first in display and last in display pointer down at most
    //'totalLines' line.
    //
    for (Index = 0; Index < TotalLines; Index ++) {
      LogFileDialog->LastInDisplay  = LogFileDialog->LastInDisplay->Next;
      LogFileDialog->FirstInDisplay = LogFileDialog->FirstInDisplay->Next;
      if (LogFileDialog->LastInDisplay->Next == NULL) {
        break;
      }
    }
    LogFileDialog->CurrentSelected = LogFileDialog->LastInDisplay;
    //
    //refresh the items
    //
    Status = LogFileDialogRefresh (LogFileDialog, FALSE);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  //at last refresh the edit area.
  //
  Context = (EFI_FILE_DIALOG_ITEM_CONTEXT*)(LogFileDialog->CurrentSelected->Context);
  if (Context->RootContext) {
    return EFI_SUCCESS;
  }

  //
  //reset the current selected File Name
  //
  ShortName = NULL;
  ShortName = SctGetShortFileNameAndExt (Context->FileName);
  if (ShortName != NULL) {
    SctStrCpy (LogFileDialog->FileName, ShortName);
  } else {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //refresh the file name display
  //
  Status = LogDialogInputRefresh (LogFileDialog);
  return Status;
}


EFI_STATUS
LogFileDialogEditFunc (
  IN  EFI_FILE_DIALOG             *LogFileDialog,
  IN  EFI_INPUT_KEY               *InKey
  )
/*++

Routine Description:

  response the key input in dialog edit area

Arguments:

  LogFileDialog - The EFI_FILE_DIALOG instance pointer.
  InKey         - the EFI_INPUT_KEY instance pointer.

Returns:

  EFI_SUCCESS   - all the keys were responsed successfully

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
  if (LogFileDialog == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status     = EFI_SUCCESS;
  WAITING    = TRUE;
  TempStr[0] = L'\0';
  tBS->SetMem (&Key, sizeof(EFI_INPUT_KEY), 0);

  Ypos  = LogFileDialog->BodyRect.BottomRight.Row + 1;
  XLeft = LogFileDialog->BodyRect.TopLeft.Col + 20;

  CurrentLength = SctStrLen (LogFileDialog->FileName);
  //
  //save the filename in buffer
  //
  SctStrCpy (Buffer, LogFileDialog->FileName);

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
      break;
    }

    switch (Key.ScanCode) {
      case SCAN_ESC:
      case SCAN_F1:
        if (Key.ScanCode == SCAN_ESC ||
           (Key.ScanCode == SCAN_F1 &&
            LogFileDialog->Type == EFI_FILE_DIALOG_TYPE_SELECT_DIR)) {
          //
          //save the input value in FileName
          //
          SctStrCpy (LogFileDialog->FileName, Buffer);
          //
          //disable cursor.
          //
          tST->ConOut->EnableCursor (tST->ConOut, FALSE);

          tBS->CopyMem (TempStr, Buffer, EFI_MAX_ITEM_VALUE_LENGTH * sizeof(CHAR16));
          TempStr[EFI_MAX_ITEM_VALUE_LENGTH] = L'\0';
          //
          //refresh input area in screen.
          //
          Status = TestPrintAt (XLeft, Ypos, TempStr);
          if (EFI_ERROR (Status) ) {
            return Status;
          }

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
            SctStrCpy (LogFileDialog->FileName, Buffer);

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
          case CHAR_TAB:
            //
            //save the input value in FileName
            //
            SctStrCpy (LogFileDialog->FileName, Buffer);

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
DisplayLogFileDialog (
  IN  EFI_FILE_DIALOG             *Dialog,
  IN  EFI_INPUT_KEY               *Key
  )
/*++

Routine Description:

  Display File Dialog and response press key.

Arguments:

  LogFileDialog   - The EFI_FILE_DIALOG instance pointer.
  Key             - the EFI_INPUT_KEY instance pointer.

Returns:

  EFI_FILE_DIALOG_ITEM_CONTEXT pointer.

--*/
{
  EFI_STATUS      Status;
  UINTN           Index;
  BOOLEAN         Stopped;
  VOID            *Ret;
  UINTN           Length;

  if (Dialog == NULL || Key == NULL) {
    return NULL;
  }

  Status  = EFI_SUCCESS;
  Stopped = FALSE;
  Ret     = NULL;

  //
  //refresh  Dialog
  //
  Status = LogFileDialogRefresh (Dialog, TRUE);
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
      break;
    }

    //
    //if there is no item to select wait for press ESC to return.
    //
    if (Dialog->CurrentSelected == NULL) {
      if (Key->ScanCode != SCAN_ESC) {
        continue;
      }
    }

    switch(Key->ScanCode) {
      case SCAN_UP:

        Status = LogFileDialogUpFunc (Dialog);
        break;

      case SCAN_DOWN:

        Status = LogFileDialogDownFunc (Dialog);
        break;

      case SCAN_PAGE_DOWN:

        Status = LogFileDialogPageDownFunc (Dialog);
        break;

      case SCAN_PAGE_UP:

        Status = LogFileDialogPageUpFunc (Dialog);
        break;
      case SCAN_ESC:

        Ret = NULL;
        Dialog->FileName[0] = L'\0';
        Stopped = TRUE;
        break;
     case SCAN_F1:
        //
        //if the dialog is not for directory selection then do nothing
        //
        if (Dialog->Type != EFI_FILE_DIALOG_TYPE_SELECT_DIR) {
          break;
        }
        Ret = Dialog->CurrentSelected->Context;
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
          LogFileDialogItemRefresh (Dialog, Dialog->CurrentSelected);

          //
          //process edit function
          //
          Status = LogFileDialogEditFunc (Dialog, Key);

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
            Status = LogFileDialogItemRefresh (Dialog, Dialog->CurrentSelected);
            break;

          } else if (Key->UnicodeChar == CHAR_CARRIAGE_RETURN) {
            Ret = Dialog->CurrentSelected->Context;

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

  } while (!EFI_ERROR(Status) && !Stopped);

  if (EFI_ERROR(Status)) {
    Ret = NULL;
  }

  return Ret;
}

EFI_FILE_DIALOG_ITEM *
AllocateLogFileDialogItem (
  IN EFI_FILE_DIALOG              *Dialog,
  IN UINT16                       *String,
  IN VOID                         *Context
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
LogIsSearchedFile (
  IN EFI_FILTER_FILE_TYPE         FileType,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  varify if the File Name meets with the filter name.

Arguments:

  Filter    - the filter string.
  FileName  - the file name to be verified.

Returns:

  TRUE      - the FileName meets the Filter needs.
  FALSE     - the FileName can not meet the Filter.

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
LogAppendFileName (
  IN  CHAR16                      *Str1,
  IN  CHAR16                      *Str2
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
  CHAR16     *Ptr;
  CHAR16     *LastSlash;
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

  Ptr = Str;
  LastSlash = Str;
  while (*Ptr != 0) {
    if (*Ptr == '\\' && *(Ptr+1) == '.' && *(Ptr+2) == '.' && *(Ptr+3) != 0) {

      //
      // Convert '\Name\..\' to '\'
      //  DO NOT convert the .. if it is at the end of the string. This will
      //  break the .. behavior in changing directories.
      //
      SctStrCpy (LastSlash, Ptr+3);
      Ptr = LastSlash;
    } else if (*Ptr == '\\' && *(Ptr+1) == '.' && *(Ptr + 2) == '\\') {

      //
      // Convert a '\.\' to a '\'
      //
      SctStrCpy (Ptr, Ptr+2);
      Ptr = LastSlash;
    } else if (*Ptr == '\\') {
      LastSlash = Ptr;
    }
    Ptr++;
  }

  return Str;
}

BOOLEAN
LogBuildDirDialog (
  IN  EFI_FILE_DIALOG_ITEM_CONTEXT    *ItemContext,
  IN  EFI_FILE_DIALOG                 *DirDialog
  )
/*++

Routine Description:

  build one File Dialog based on the files and directories
  below current directory.

Arguments:

  ItemContext - the EFI_FILE_DIALOG_ITEM_CONTEXT instance poiter.
  DirDialog   - The EFI_FILE_DIALOG instance pointer.

Returns:

  TRUE    - the Dialog was built successfully.
  FALSE   - can not build the Dialog.

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
  CHAR16                        *Str;
  CHAR16                        *Str1;

  if (ItemContext == NULL || DirDialog == NULL) {
    return FALSE;
  }

  Str = NULL;
  Status = SctMapNameFromDevice (ItemContext->DevicePath, &Str);
  if (EFI_ERROR(Status)) {
    LogFreeFileSystemDialogItemContext (ItemContext);
    return FALSE;
  }

  Str1 = SctPoolPrint(L"%s:%s", Str, ItemContext->FileName);
  if (Str1 == NULL) {
    return FALSE;
  }

  //
  //set Dialog Title based on the dialog type
  //
  switch (DirDialog->Type) {
    case EFI_FILE_DIALOG_TYPE_OPEN_FILE:
      SctSPrint (DirDialog->Title, MAX_CHAR, L"%s: %s", L" Open File", Str1);
      break;

    case EFI_FILE_DIALOG_TYPE_SAVE_FILE:
      SctSPrint (DirDialog->Title, MAX_CHAR, L"%s: %s", L" Save File", Str1);
      break;

    default:
      DirDialog->Type  = EFI_FILE_DIALOG_TYPE_OPEN_FILE;
      SctSPrint (DirDialog->Title, MAX_CHAR, L" Open File");
      break;
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

  if (EFI_ERROR(Status)) {
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

      if (!(DirInfo->Attribute & EFI_FILE_DIRECTORY ||
          LogIsSearchedFile (DirDialog->FileType,DirInfo->FileName))) {
        //
        // Slip file unless it is a directory entry or is searched  file type
        //
        continue;
      }

      SctSPrint (Buffer, MAX_CHAR, L" %s %s",
              DirInfo->Attribute & EFI_FILE_DIRECTORY ? L"<DIR>" : L"     ",
              DirInfo->FileName
             );

      Status = tBS->AllocatePool (
                     EfiBootServicesData,
                     sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT),
                     (VOID **)&Context
                     );

      if (EFI_ERROR(Status)) {
        LogFreeDirDialog (DirDialog);
        NewDir->Close (NewDir);
        tBS->FreePool (DirInfo);
        return FALSE;
      }

      tBS->SetMem (Context,sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT),0);

      Context->Handle   = ItemContext->Handle;
      Context->FileName = LogAppendFileName (
                            ItemContext->FileName,
                            DirInfo->FileName
                            );

      Context->FHandle       = NewDir;
      Context->DevicePath    = SctDuplicateDevicePath (ItemContext->DevicePath);
      Context->DevicePathStr = SctDevicePathToStr (Context->DevicePath);
      Context->IsDir         = (BOOLEAN)((DirInfo->Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY);

      DialogItem = AllocateLogFileDialogItem (DirDialog, Buffer, Context);

      if (DialogItem == NULL) {
        LogFreeDirDialog (DirDialog);
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
LogFindAFileInDialog (
  IN  EFI_FILE_DIALOG_ITEM_CONTEXT  *ItemContext,
  IN  EFI_FILE_DIALOG               *DirDialog,
  IN  OUT EFI_FILE_DIALOG_CONTEXT   *DialogContext
  )
/*++

Routine Description:

  Get a file in current file system.

Arguments:

  ItemContext   - the EFI_FILE_DIALOG_ITEM_CONTEXT instance poiter.
  DirDialog     - The EFI_FILE_DIALOG instance pointer.
  DialogContext - The FILE_DIALOG_CONTEXT,it contains filter filename string.

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
  EFI_FILE_INFO                   *FileInfo;
  BOOLEAN                         RET;
  CHAR16                          *TempName;
  INTN                            Length;
  INTN                            Index;

  if (ItemContext == NULL || DirDialog == NULL || DialogContext == NULL ) {
    return FALSE;
  }

  RET = FALSE;

  Status = LogBuildDirDialog (ItemContext, DirDialog);

  if  (EFI_ERROR(Status)) {
    return FALSE;
  }
  tBS->SetMem ((VOID *)&ContextCopy, sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT), 0);

  for (;;) {

    ResultContext =(EFI_FILE_DIALOG_ITEM_CONTEXT*) DisplayLogFileDialog (DirDialog, &Key);

    if (ResultContext == NULL) {
      break;
    }
    //
    // use File Interface to open the selected file
    //
    TempHandle = ResultContext->FHandle;

    Status = TempHandle->Open(
            TempHandle,
            &FHandle,
            DirDialog->FileName,
            EFI_FILE_MODE_READ,
            0
            );
    if (Status == EFI_NOT_FOUND) {
      if (DirDialog->Type == EFI_FILE_DIALOG_TYPE_SAVE_FILE) {

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
        } else {

          //
          //first remove the last file name in ResultContext->FileName
          // get current directory
          //
          Length = SctStrLen (ResultContext->FileName);
          if (Length > 0) {
            TempName = ResultContext->FileName;
            for (Index = Length- 1; Index >= 0; Index --) {
              if (TempName[Index] == L'\\') {
                TempName[Index] = L'\0';
                break;
              }
            }
          }

          //
          //append the file name inputed in edit area into current directory
          //
          DialogContext->FileName = LogAppendFileName (
                                      ResultContext->FileName,
                                      DirDialog->FileName
                                      );

          DialogContext->DevicePath = SctDuplicateDevicePath (ResultContext->DevicePath);
          RET = TRUE;
          break;
        }
      } else if (DirDialog->Type == EFI_FILE_DIALOG_TYPE_SELECT_DIR) {

        //
        //this is Select Directory Dialog
        //
        if (Key.ScanCode == SCAN_F1) {

          Status = TempHandle->Open(
                  TempHandle,
                  &FHandle,
                  DirDialog->FileName,
                  EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                  EFI_FILE_DIRECTORY
                  );
          if (EFI_ERROR(Status)) {
            continue;
          } else {
            FHandle->Close (FHandle);
          }
          //
          //save this directory in DialogContext
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
          DialogContext->DevicePath = SctDuplicateDevicePath (ResultContext->DevicePath);
          if (SctStrBeginWith (DirDialog->FileName, L"\\")) {
            DialogContext->FileName = SctStrDuplicate (DirDialog->FileName);
          } else {

            //
            //first remove the last file name in ResultContext->FileName
            //get current directory
            //
            Length = SctStrLen (ResultContext->FileName);
            if (Length > 0) {
              TempName = ResultContext->FileName;
              for (Index = Length- 1;Index >= 0; Index --) {
                if (TempName[Index] == L'\\') {
                  TempName[Index] = L'\0';
                  break;
                }
              }
            }

            //
            //append the file name inputed in edit area into current directory
            //
            DialogContext->FileName = LogAppendFileName (
                                        ResultContext->FileName,
                                        DirDialog->FileName
                                        );
          }
          RET = TRUE;
          break;

        } else {
          //
          //invalid directory name
          //
          continue;
        }

      } else {
        //
        //select a not exist file is invalid so continue excute
        //
        continue;
      }

    } else if (EFI_ERROR(Status)) {
      //
      //error when open the file so break
      //
      break;

    } else {

      //
      //success opened the file
      //
      Status = SctGetFileInfo (FHandle, &FileInfo);
      if (EFI_ERROR (Status)) {
        break;
      }

      if ((FileInfo->Attribute & EFI_FILE_DIRECTORY )&&
           Key.ScanCode != SCAN_F1) {

        //
        //it is a directory then expand it
        //
        tBS->CopyMem (
          &ContextCopy,
          ResultContext,
          sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT)
          );

        //
        //set devicepath
        //
        ContextCopy.DevicePath = SctDuplicateDevicePath (ResultContext->DevicePath);
        if ( ContextCopy.DevicePath == NULL ) {
          FHandle->Close(FHandle);
          break;
        }
        //
        //set the file name
        //
        if (SctStrBeginWith (DirDialog->FileName, L"\\")) {
          ContextCopy.FileName = SctStrDuplicate (DirDialog->FileName);
        } else {
          //
          //first remove the last file name in ResultContext->FileName
          //get current directory
          //
          Length = SctStrLen (ResultContext->FileName);
          TempName = ResultContext->FileName;
          if (Length > 0) {
            for (Index = Length- 1;Index >= 0; Index --) {
              if (TempName[Index] == L'\\') {
                TempName[Index] = L'\0';
                break;
              }
            }
          }

          //
          //append the file name inputed in edit area into current directory
          //
          ContextCopy.FileName = LogAppendFileName (
                                   ResultContext->FileName,
                                   DirDialog->FileName
                                   );
          if ( ContextCopy.FileName == NULL) {
            tBS->FreePool (ContextCopy.DevicePath);
            FHandle->Close(FHandle);
            break;
          }
        }

        //
        //Free all the MenuItems and Context relative to current Directory.
        //
        LogFreeDirDialog (DirDialog);

        //
        //build a new file dialog in current selected directory
        //
        if (!LogBuildDirDialog (&ContextCopy, DirDialog)) {
          tBS->FreePool (ContextCopy.DevicePath);
          tBS->FreePool (ContextCopy.FileName);
          FHandle->Close(FHandle);
          break;
        }
        //
        //free not used resource
        //
        tBS->FreePool (ContextCopy.DevicePath);
        tBS->FreePool (ContextCopy.FileName);
        //
        //close the file handle that not to be used
        //
        FHandle->Close(FHandle);
      } else {
        //
        //return this file or
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
        } else {
          //
          //first remove the last file name in ResultContext->FileName
          //get current directory
          //
          Length = SctStrLen (ResultContext->FileName);
          TempName = ResultContext->FileName;
          if (Length>0) {
            for (Index = Length- 1;Index >= 0; Index --) {
              if (TempName[Index] == L'\\') {
                TempName[Index] = L'\0';
                break;
              }
            }
          }

          //
          //append the file name inputed in edit area into current directory
          //
          DialogContext->FileName = LogAppendFileName (
                                      ResultContext->FileName,
                                      DirDialog->FileName
                                      );
        }

        DialogContext->DevicePath = SctDuplicateDevicePath (ResultContext->DevicePath);
        RET = TRUE;
        FHandle->Close (FHandle);
        break;
      }
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
  LogFreeDirDialog (DirDialog);
  return RET;
}

EFI_STATUS
DoLogFileDialog(
 IN OUT EFI_FILE_DIALOG_CONTEXT       *DialogContext
  )
/*++

Routine Description:

  The entry point to do popup menu.

Arguments:

  DialogContext   - The FILE_DIALOG_CONTEXT,it contains filter
                    filename string.

Returns:

  EFI_SUCCESS.

--*/
{
  EFI_STATUS                      Status;
  EFI_FILE_DIALOG                 *FileSystemDialog;
  EFI_FILE_DIALOG                 *DirDialog;
  CHAR16                          Buffer[MAX_CHAR];
  UINTN                           Index;
  UINTN                           NumberFsHandles;
  EFI_HANDLE                      *FsHandles;
  UINTN                           NumberLoadFileHandles;
  EFI_HANDLE                      *LoadFileHandles;
  EFI_FILE_DIALOG_ITEM            *TempDialogItem;
  EFI_FILE_DIALOG_ITEM_CONTEXT    *ResultContext;
  EFI_FILE_DIALOG_ITEM_CONTEXT    *Context;
  EFI_INPUT_KEY                   Key;
  CHAR16                          *Str;
  UINTN                           TotalDisplayLine;
  UINTN                           ConAttrib;
  UINTN                           Y0;
  UINTN                           Y1;

  if (DialogContext == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (DoLogFileDialogInSpecifiedDir (DialogContext)) {
    return EFI_SUCCESS;
  }

  Status                = EFI_SUCCESS;
  NumberFsHandles       = 0;
  NumberLoadFileHandles = 0;
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

  //
  //set Dialog Title based on the dialog type
  //

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 MAX_CHAR,
                 (VOID **)&FileSystemDialog->Title
                 );
  if (EFI_ERROR(Status)) {
    LogFreeFileSystemDialog (FileSystemDialog);
    return EFI_OUT_OF_RESOURCES;
  }

  switch (FileSystemDialog->Type) {
    case EFI_FILE_DIALOG_TYPE_OPEN_FILE:
      SctSPrint(FileSystemDialog->Title, MAX_CHAR, L" Open File");
      break;

    case EFI_FILE_DIALOG_TYPE_SAVE_FILE:
      SctSPrint(FileSystemDialog->Title, MAX_CHAR, L" Save File");
      break;

    default:
      FileSystemDialog->Type  = EFI_FILE_DIALOG_TYPE_OPEN_FILE;
      SctSPrint(FileSystemDialog->Title, MAX_CHAR, L" Open File");
      break;
  }

  if ( FileSystemDialog->Title == NULL ) {
    tBS->FreePool (FileSystemDialog);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 (EFI_MAX_EDIT_LENGTH + 1) * sizeof(CHAR16),
                 (VOID **)&FileSystemDialog->FileName
                 );
  if (EFI_ERROR(Status)) {
    LogFreeFileSystemDialog (FileSystemDialog);
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

  //
  // Search by simple file system protocol
  //
  FsHandles = NULL;
  SctLocateHandle(
            ByProtocol,
            &gEfiSimpleFileSystemProtocolGuid,
            NULL,
            &NumberFsHandles,
            &FsHandles
            );

  for (Index = 0; Index < NumberFsHandles; Index++) {

    Status = tBS->AllocatePool (
            EfiBootServicesData,
            sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT),
            (VOID **)&Context
            );

     if (EFI_ERROR(Status)) {
      LogFreeFileSystemDialog (FileSystemDialog);
      return EFI_OUT_OF_RESOURCES;
    }

    tBS->SetMem (Context, sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT), 0);

    Context->Handle         = FsHandles[Index];
    Context->FHandle        = SctOpenRoot (Context->Handle);
    Context->DevicePath     = SctDevicePathFromHandle (Context->Handle);
    Context->DevicePathStr  = SctDevicePathToStr (Context->DevicePath);
    Context->FileName       = SctStrDuplicate (L"\\");
    Context->IsDir          = TRUE;
    Context->RootContext    = TRUE;

    if (Context->FHandle == NULL || Context->DevicePath == NULL ||
        Context->FileName == NULL) {
      LogFreeFileSystemDialogItemContext (Context);
      continue;
    }

    //
    //get file system map from devicepath
    //
    Str = NULL;
    Status = SctMapNameFromDevice (Context->DevicePath, &Str);
    if (!EFI_ERROR(Status)) {
      SctSPrint (Buffer, MAX_CHAR, L"<VOL> %s", Str);
      tBS->FreePool (Str);
    } else {
      LogFreeFileSystemDialogItemContext (Context);
      continue;
    }

    //
    //add a new menu item
    //
    TempDialogItem = AllocateLogFileDialogItem (FileSystemDialog, Buffer,Context);
    if (TempDialogItem == NULL) {
      LogFreeFileSystemDialog (FileSystemDialog);
      return EFI_OUT_OF_RESOURCES;
    }

  } //end for

  if (FsHandles != NULL) {
    tBS->FreePool (FsHandles);
  }

  //
  // add loadfileprotocol devices
  //
  LoadFileHandles = NULL;
  SctLocateHandle (
     ByProtocol,
     &gEfiLoadFileProtocolGuid,
     NULL,
     &NumberLoadFileHandles,
     &LoadFileHandles
     );
  for (Index = 0; Index < NumberLoadFileHandles; Index++) {

    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT),
                   (VOID **)&Context
                   );

    if (EFI_ERROR(Status)) {
      LogFreeFileSystemDialog (FileSystemDialog);
      return EFI_OUT_OF_RESOURCES;
    }

    tBS->SetMem (Context, sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT), 0);

    Context->Handle        = LoadFileHandles[Index];
    Context->FHandle       = SctOpenRoot (Context->Handle);
    Context->DevicePath    = SctDevicePathFromHandle (Context->Handle);
    Context->DevicePathStr = SctDevicePathToStr (Context->DevicePath);
    Context->FileName      = SctStrDuplicate (L"\\");
    Context->IsDir         = TRUE;
    Context->RootContext   = TRUE;

    if (Context->FHandle == NULL || Context->DevicePath == NULL ||
        Context->FileName == NULL) {
      LogFreeFileSystemDialogItemContext (Context);
      continue;
    }

    //
    //get file system map from devicepath
    //
    Str = NULL;
    Status = SctMapNameFromDevice (Context->DevicePath, &Str);
    if (!EFI_ERROR(Status)) {
      SctSPrint (Buffer, MAX_CHAR, L"<VOL> %s", Str);
      tBS->FreePool (Str);
    } else {
      LogFreeFileSystemDialogItemContext (Context);
      continue;
    }

    //
    //add a new menu item
    //
    TempDialogItem = AllocateLogFileDialogItem (FileSystemDialog, Buffer,Context);
    if (TempDialogItem == NULL) {
      LogFreeFileSystemDialog (FileSystemDialog);
      LogFreeFileSystemDialogItemContext (Context);
      return EFI_OUT_OF_RESOURCES;
    }
  }

  if (LoadFileHandles != NULL) {
    tBS->FreePool (LoadFileHandles);
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
    LogFreeFileSystemDialog (FileSystemDialog);
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

  for (;;) {
    ResultContext = DisplayLogFileDialog (FileSystemDialog, &Key);

    if (ResultContext == NULL) {
      break;
    }

    if (Key.ScanCode == SCAN_F1) {
      if (DialogContext->DevicePath != NULL) {
        tBS->FreePool (DialogContext->DevicePath);
      }
      if (DialogContext->FileName != NULL) {
        tBS->FreePool (DialogContext->FileName);
      }
      DialogContext->DevicePath = SctDuplicateDevicePath (ResultContext->DevicePath);
      DialogContext->FileName   = SctStrDuplicate (L"\\");
      break;
    }

    if (LogFindAFileInDialog (ResultContext, DirDialog , DialogContext)) {
      break;
    }
  }

  //
  //process the returned filename.
  //
  LogProccessFileName (DialogContext->FileName);

  //
  //free MenuItems and relative Context.
  //
  LogFreeDirDialog (DirDialog);
  tBS->FreePool (DirDialog);
  LogFreeFileSystemDialog(FileSystemDialog);

  //
  //
  //restore original console attribute
  //
  tST->ConOut->SetAttribute ( tST->ConOut,ConAttrib);

  return EFI_SUCCESS;
}

BOOLEAN
DoLogFileDialogInSpecifiedDir (
 IN OUT EFI_FILE_DIALOG_CONTEXT       *DialogContext
  )
/*++

Routine Description:

  The entry point to do popup menu.

Arguments:

  DialogContext - The FILE_DIALOG_CONTEXT,it contains filter
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
  BOOLEAN                         Ret;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;

  if (DialogContext == NULL) {
    return FALSE;
  }

  Status                = EFI_SUCCESS;
  ConAttrib             = tST->ConOut->Mode->Attribute;
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG),
                 (VOID **)&FileSystemDialog
                 );
  if (EFI_ERROR(Status)) {
    return FALSE;
  }

  tBS->SetMem (FileSystemDialog, sizeof(EFI_FILE_DIALOG), 0);

  FileSystemDialog->Type = DialogContext->DialogType;

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 (EFI_MAX_EDIT_LENGTH + 1) * sizeof(CHAR16),
                 (VOID **)&FileSystemDialog->FileName
                 );
  if (EFI_ERROR(Status)) {
    LogFreeFileSystemDialog (FileSystemDialog);
    return FALSE;
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
    return FALSE;
  }

  Status = tBS->AllocatePool (
          EfiBootServicesData,
          sizeof(EFI_FILE_DIALOG_ITEM_CONTEXT),
          (VOID **)&Context
          );

  if (EFI_ERROR(Status)) {
    LogFreeFileSystemDialog (FileSystemDialog);
    return FALSE;
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
  } else if (DialogContext->FileType == EFI_FILTER_FILE_TYPE_LOG) {
    Context->FileName       = SctPoolPrint(L"%s\\%s", gFT->FilePath, EFI_SCT_PATH_LOG);
  } else {
    Context->FileName       = SctStrDuplicate (gFT->FilePath);
  }

  Context->IsDir          = TRUE;
  Context->RootContext    = TRUE;

  if (Context->FHandle == NULL || Context->DevicePath == NULL ||
      Context->FileName == NULL) {
    LogFreeFileSystemDialogItemContext (Context);
    return FALSE;
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
    LogFreeFileSystemDialogItemContext (Context);
    return FALSE;
  }

  if (DialogContext->FileType == EFI_FILTER_FILE_TYPE_CSV) {
    Str1 = SctPoolPrint(L"%s%s\\%s", Buffer, gFT->FilePath, EFI_SCT_PATH_REPORT);
  } else if (DialogContext->FileType == EFI_FILTER_FILE_TYPE_SEQ) {
    Str1 = SctPoolPrint(L"%s%s\\%s", Buffer, gFT->FilePath, EFI_SCT_PATH_SEQUENCE);
  } else if (DialogContext->FileType == EFI_FILTER_FILE_TYPE_LOG) {
    Str1 = SctPoolPrint(L"%s%s\\%s", Buffer, gFT->FilePath, EFI_SCT_PATH_LOG);
  } else {
    Str1 = SctPoolPrint(L"%s%s", Buffer, gFT->FilePath);
  }
  if (Str1 == NULL) {
    LogFreeFileSystemDialogItemContext (Context);
    return FALSE;
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
    LogFreeFileSystemDialog (FileSystemDialog);
    return FALSE;
  }

  //
  //add a new menu item
  //
  TempDialogItem = AllocateLogFileDialogItem (FileSystemDialog, Buffer, Context);
  if (TempDialogItem == NULL) {
    LogFreeFileSystemDialog (FileSystemDialog);
    LogFreeFileSystemDialogItemContext (Context);
    return FALSE;
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
    LogFreeFileSystemDialog (FileSystemDialog);
    return FALSE;
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

  if (LogFindAFileInDialog (ResultContext, DirDialog , DialogContext)) {
    Ret = TRUE;
  } else {
    Ret = FALSE;
  }

  //
  //free MenuItems and relative Context.
  //
  LogFreeDirDialog (DirDialog);
  tBS->FreePool (DirDialog);
  LogFreeFileSystemDialog(FileSystemDialog);

  //
  //restore original console attribute
  //
  tST->ConOut->SetAttribute ( tST->ConOut,ConAttrib);

  return Ret;
}
