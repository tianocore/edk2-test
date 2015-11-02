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
