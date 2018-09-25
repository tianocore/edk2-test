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

  FileDialog.h

Abstract:

  This file defines EFI Test Framework file dialog

--*/

#ifndef _EFI_FILE_DIALOG_H_
#define _EFI_FILE_DIALOG_H_

//
// Includes
//

//
// Definitions
//

typedef enum {
  EFI_FILE_DIALOG_TYPE_OPEN_FILE = 0,
  EFI_FILE_DIALOG_TYPE_SAVE_FILE,
  EFI_FILE_DIALOG_TYPE_SELECT_DIR,
  EFI_FILE_DIALOG_TYPE_MAX
} EFI_FILE_DIALOG_TYPE;

typedef enum {
  EFI_FILTER_FILE_TYPE_ALL = 0,
  EFI_FILTER_FILE_TYPE_LOG,
  EFI_FILTER_FILE_TYPE_EKL,
  EFI_FILTER_FILE_TYPE_TXT,
  EFI_FILTER_FILE_TYPE_DOC,
  EFI_FILTER_FILE_TYPE_BAT,
  EFI_FILTER_FILE_TYPE_INI,
  EFI_FILTER_FILE_TYPE_SEQ,
  EFI_FILTER_FILE_TYPE_H,
  EFI_FILTER_FILE_TYPE_C,
  EFI_FILTER_FILE_TYPE_EFI,
  EFI_FILTER_FILE_TYPE_CSV,
  EFI_FILTER_FILE_TYPE_MAX
} EFI_FILTER_FILE_TYPE;

typedef struct {
  CHAR16   *FileTypeSuffix;
  CHAR16   *FileTypeDesc;
} EFI_FILE_TYPE_INFO;

#define FILE_DIALOG_MENU_AREA       0
#define FILE_DIALOG_EDIT_AREA       1

//
//popup menu item definition
//
typedef struct _EFI_FILE_DIALOG_ITEM {
  struct _EFI_FILE_DIALOG_ITEM    *Prev;
  struct _EFI_FILE_DIALOG_ITEM    *Next;
  CHAR16                          *ItemName;
  VOID                            *Context;
} EFI_FILE_DIALOG_ITEM;

//
//file menu item context definition
//
typedef struct {
  EFI_HANDLE                      Handle;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  UINT16                          *DevicePathStr;
  EFI_FILE_HANDLE                 FHandle;
  UINT16                          *FileName;
  BOOLEAN                         RootContext;
  BOOLEAN                         IsDir;
} EFI_FILE_DIALOG_ITEM_CONTEXT;



//
//File Dialog Definition
//
typedef struct  {
  EFI_FILE_DIALOG_TYPE            Type;
  CHAR16                          *Title;
  UINT32                          CurrentArea;
  EFI_RECT                        BodyRect;
  EFI_FILE_DIALOG_ITEM            *ItemList;
  EFI_FILE_DIALOG_ITEM            *CurrentSelected;
  EFI_FILE_DIALOG_ITEM            *FirstInDisplay;
  EFI_FILE_DIALOG_ITEM            *LastInDisplay;
  CHAR16                          *FileName;
  EFI_FILTER_FILE_TYPE            FileType;
  UINT32                          BackColor;
  UINT32                          ForeColor;
} EFI_FILE_DIALOG;

//
//file dialog context
//
typedef struct {
  EFI_FILE_DIALOG_TYPE            DialogType;
  EFI_FILTER_FILE_TYPE            FileType;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  CHAR16                          *FileName;
} EFI_FILE_DIALOG_CONTEXT;

//
// Functions
//

EFI_STATUS
DoFileDialog(
  IN OUT EFI_FILE_DIALOG_CONTEXT  *DialogContext
  )
/*++

Routine Description:

  Through file dialog open or save a file.

Arguments:

  DialogContext         - The EFI_FILE_DIALOG_CONTEXT instance pointer.

Returns:

  EFI_SUCCESS           - the FileName and DevicePath was set successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid

--*/
;

EFI_STATUS
DoLogFileDialog(
  IN OUT EFI_FILE_DIALOG_CONTEXT  *DialogContext
  )
/*++

Routine Description:

  Through file dialog open or save a log file.

Arguments:

  DialogContext         - The EFI_FILE_DIALOG_CONTEXT instance pointer.

Returns:

  EFI_SUCCESS           - the FileName and DevicePath was set successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid

--*/
;

#endif
