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

  Dialog.h

Abstract:

  This file defines Dialog data structure.

--*/

#ifndef _EFI_DIALOG_H_
#define _EFI_DIALOG_H_

//
// Includes
//

//
// Definitions
//

typedef enum {
  EFI_DIALOG_TYPE_YES_OR_NO = 0,
  EFI_DIALOG_TYPE_MESSAGE,
  EFI_DIALOG_TYPE_REMINDER,
  EFI_DIALOG_TYPE_MAX
} EFI_DIALOG_TYPE;

#define DIALOG_MENU_AREA       0
#define DIALOG_EDIT_AREA       1

//
//File Dialog Definition
//
typedef struct  {
  EFI_DIALOG_TYPE               Type;
  CHAR16                        *Title;
  EFI_RECT                      BodyRect;
  UINT32                        BackColor;
  UINT32                        ForeColor;
} EFI_DIALOG;

//
//file dialog context
//
typedef struct {
  EFI_DIALOG_TYPE               Type;
  UINT32                        ChooseNumber;
} EFI_DIALOG_CONTEXT;

//
// Functions
//

EFI_STATUS
DoDialog(
  IN CHAR16                        *DialogTitle,
  IN OUT EFI_DIALOG_CONTEXT        *DialogContext
  )
/*++

Routine Description:

  Through file dialog open or save a file.

Arguments:

  Context     - The EFI_FILE_DIALOG_CONTEXT instance pointer.

Returns:

  EFI_SUCCESS           - the FileName and DevicePath was set successfully.
  EFI_INVALID_PARAMETER - the Parameter is Invalid

--*/
;

#endif
