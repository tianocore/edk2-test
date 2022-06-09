/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MainMenu.c

Abstract:

  Deal with the main menu in the user interface.

--*/
#include "Sct.h"
#include "UI.h"
#include "BuildMenu.h"
#include "Dialog.h"
#include "FileDialog.h"

#include "TestNodeMenu.h"

//
// Definitions
//

#define EFI_MENU_ITEM_CONFIG              0
#define EFI_MENU_ITEM_CASE_MANAGEMENT     1
#define EFI_MENU_ITEM_REPORT_GENERATOR    2
#define EFI_MENU_ITEM_VIEW_LOG            3
#define EFI_MENU_ITEM_UTILITY             4
#define EFI_MENU_ITEM_DEVICE_CONFIG       5

//
// a globel variable indicating continue exec flag
//
BOOLEAN                gContinueExec;
SCT_LIST_ENTRY         *TestTree;

//
// A variable imported from UI.c
//
extern BOOLEAN          gMenuExit;

//
// Prototypes (external)
//

EFI_STATUS
DisplayMainMenu (
  VOID
  );

//
// Prototypes (internal)
//

VOID
DisplayDeviceConfig (
  IN EFI_MENU_PAGE                *Page
  );

VOID
DisplayReportGenerator(
  IN EFI_MENU_PAGE                *Page
  );

VOID
DisplayLog(
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
MainMenuEnterFunc  (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
MainMenuEscFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
MainMenuLoadSeqFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
MainMenuSaveSeqFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
MainMenuF9Func(
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
EFIAPI
MainMenuClearFunc (
  IN EFI_MENU_PAGE                *Page
  );

//
// Functions
//

EFI_STATUS
DisplayMainMenu (
  VOID
  )
/*++

Routine Description:

  Display the main menu

Returns:

  EFI_SUCCESS   - Display the menu successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_MENU_PAGE         *Page;
  EFI_DIALOG_CONTEXT    DialogContext;
  CHAR16                *DialogTitle;

  //
  // Create a standard menu
  //
  Status = CreateStandardMenuPage (
             L"Main Menu",
             &Page
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Main Menu Items
  //  - Test Case Management
  //  - Test Environment Configuration
  //  - Test Report Generator ...
  //  - Help
  //
  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Test Case Management",
             L"Select and execute test cases",
             (VOID *)(UINTN)EFI_MENU_ITEM_CASE_MANAGEMENT,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Test Environment Configuration",
             L"Set configuration data for testing",
             (VOID *)(UINTN)EFI_MENU_ITEM_CONFIG,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Test Device Configuration",
             L"Set device configuration data for IHV's add-in card testing",
             (VOID *)(UINTN)EFI_MENU_ITEM_DEVICE_CONFIG,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"View Test Log ...",
             L"View test log",
             (VOID *)(UINTN)EFI_MENU_ITEM_VIEW_LOG,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Test Report Generator ...",
             L"Generate test report",
             (VOID *)(UINTN)EFI_MENU_ITEM_REPORT_GENERATOR,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

#if (EFI_SPECIFICATION_VERSION == 0x0001000A)
  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Help",
             L"EFI1.1 Self Certification Test is a toolkit to check an EFI1.1 "
             L"implementation is EFI1.1 Specification compliant or not.",
             (VOID *)(UINTN)EFI_MENU_ITEM_UTILITY,
             Page
             );
#elif (EFI_SPECIFICATION_VERSION == 0x00020000)
  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Help",
             L"UEFI2.0 Self Certification Test is a toolkit to check an UEFI2.0 "
             L"implementation is UEFI2.0 Specification compliant or not.",
             (VOID *)(UINTN)EFI_MENU_ITEM_UTILITY,
             Page
             );
#elif (EFI_SPECIFICATION_VERSION == 0x0002000A)
  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Help",
             L"UEFI2.1 Self Certification Test is a toolkit to check an UEFI2.1 "
             L"implementation is UEFI2.1 Specification compliant or not.",
             (VOID *)(UINTN)EFI_MENU_ITEM_UTILITY,
             Page
             );
#elif (EFI_SPECIFICATION_VERSION == 0x0002001E)
  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Help",
             L"UEFI2.3 Self Certification Test is a toolkit to check an UEFI2.3 "
             L"implementation is UEFI2.3 Specification compliant or not.",
             (VOID *)(UINTN)EFI_MENU_ITEM_UTILITY,
             Page
             );
#elif (EFI_SPECIFICATION_VERSION == 0x0002001F)
  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Help",
             L"UEFI2.3.1C Self Certification Test is a toolkit to check an UEFI2.3.1C "
             L"implementation is UEFI2.3.1C Specification compliant or not.",
             (VOID *)(UINTN)EFI_MENU_ITEM_UTILITY,
             Page
             );
#elif (EFI_SPECIFICATION_VERSION == 0x00020028)
  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Help",
             L"UEFI2.4B Self Certification Test is a toolkit to check an UEFI2.4B "
             L"implementation is UEFI2.4B Specification compliant or not.",
             (VOID *)(UINTN)EFI_MENU_ITEM_UTILITY,
             Page
             );
#endif  
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  //
  // Main Menu Hot Keys
  //  - Up, Down, Enter, Esc, F5, F6
  //
  Status = AddHotKey (
             L"Up/Dn",
             L"Select Item",
             SCAN_UP,
             CHAR_NULL,
             UpFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"Down",
             L"Select Item",
             SCAN_DOWN,
             CHAR_NULL,
             DownFunc,
             FALSE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F4",
             L"Reset results",
             SCAN_F4,
             CHAR_NULL,
             MainMenuClearFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F5",
             L"Load Sequence",
             SCAN_F5,
             CHAR_NULL,
             MainMenuLoadSeqFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F6",
             L"Save Sequence",
             SCAN_F6,
             CHAR_NULL,
             MainMenuSaveSeqFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"Enter",
             L"Select SubMenu",
             SCAN_NULL,
             CHAR_CARRIAGE_RETURN,
             MainMenuEnterFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"ESC",
             L"Exit",
             SCAN_ESC,
             CHAR_NULL,
             MainMenuEscFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F9",
             L"Run",
             SCAN_F9,
             CHAR_NULL,
             MainMenuF9Func,
             FALSE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }
  //
  // Display the main menu
  //
  MenuPageRefresh (Page);

  //
  //If start from recovery, remind user to continue running
  //
  if (!IsTestFinished () && !gForceExecution) {
    //
    //Execution was not finished in last time. Display yes or no dialog
    //
    DialogContext.Type = EFI_DIALOG_TYPE_YES_OR_NO;

    //
    //Set Yes as default choise
    //
    DialogContext.ChooseNumber = EFI_DIALOG_SELECT_YES;
    DialogTitle = SctStrDuplicate (L"Continue Run?");

    //
    //Display ask dialog
    //
    DoDialog (DialogTitle, &DialogContext);

    if (DialogContext.ChooseNumber == EFI_DIALOG_SELECT_YES) {

      //
      //Change to running background
      //
      tST->ConOut->SetAttribute (
                    tST->ConOut,
                    EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK
                    );
      tST->ConOut->ClearScreen (tST->ConOut);
      Status = SctContinueExecute ();
      gContinueExec = FALSE;
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Continue execute - %r", Status));
      }
    } else {

      //
      //user choose not to continue run immediatly, set global flag, let user to
      //continue run later
      //
      gContinueExec = TRUE;
    }
    MenuPageRefresh (Page);
  } else {

    //
    //not start from recovery mode
    //
    gContinueExec = FALSE;
  }

  //
  // Start to handle input keys
  //
  MenuPageKeyInput ();

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MainMenuEnterFunc  (
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle Enter key in main menu

Arguments:

  Page          - A pointer to the menu

Reutrns

  EFI_SUCCESS   - Handle Enter key successfully
  Other Value   - Something failed

--*/
{
  //
  // Based on current selected item, display different menu page
  //
  switch ((UINTN)Page->Body.CurrentSelected->Context) {
    case EFI_MENU_ITEM_CONFIG:
      DisplayConfigMenu (Page);
      break;

    case EFI_MENU_ITEM_DEVICE_CONFIG:
      DisplayDeviceConfig (Page);
      break;

    case EFI_MENU_ITEM_CASE_MANAGEMENT:
      DisplayTestNodeMenu (&gFT->TestNodeList, Page);
      break;

    case EFI_MENU_ITEM_REPORT_GENERATOR:
      DisplayReportGenerator(Page);
      break;

    case EFI_MENU_ITEM_VIEW_LOG:
      DisplayLog(Page);
      break;

    case EFI_MENU_ITEM_UTILITY:
      break;

    default:  // Error
      return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
MainMenuEscFunc (
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle ESC key in main menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle ESC key successfully
  Other Value   - Something failed

--*/
{
  //
  // Destroy the main menu page
  //
  DestroyMenuPage (Page);

  //
  // Stop to handle input keys, and exit menu system
  //
  gMenuExit = TRUE;

  return EFI_SUCCESS;
}

VOID
DisplayDeviceConfig (
  IN EFI_MENU_PAGE                *Page
  )
{
  EFI_STATUS    Status;

  //
  // Check parameters
  //
  if (Page == NULL) {
    return;
  }

  //
  // Clears the screen
  //
  tST->ConOut->SetAttribute (
                tST->ConOut,
                EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK
                );
  tST->ConOut->ClearScreen (tST->ConOut);

  //
  // Gather the device configuration data
  //
  Status = SctDeviceConfig ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device Config - %r", Status));
  }

  //
  // Refresh the menu page
  //
  MenuPageRefresh (Page);

  //
  // Done
  //
  return;
}

VOID
DisplayReportGenerator(
  IN EFI_MENU_PAGE                *Page
  )
{

  EFI_STATUS               Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;
  CHAR16                  *LogFilePath;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID **)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return;
  }

  tBS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_SAVE_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_CSV;

  //
  //get filename through FileDialog
  //
  Status = DoFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = SctStrDuplicate (L"Generate Report Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
      && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    if (SctStrLen (DialogContext->FileName) > 4 &&
      SctStriCmp (DialogContext->FileName + SctStrLen (DialogContext->FileName) - 4, L".csv") == 0) {
      FileName = SctStrDuplicate (DialogContext->FileName);
    } else if ( SctStrLen (DialogContext->FileName) > 1 &&
      SctStriCmp (DialogContext->FileName + SctStrLen (DialogContext->FileName) - 1, L".") == 0) {
      FileName = SctPoolPrint (L"%scsv", DialogContext->FileName);
    } else {
      FileName = SctPoolPrint (L"%s.csv", DialogContext->FileName);
    }
    if (FileName == NULL) {
      tBS->FreePool (DialogContext->DevicePath);
      tBS->FreePool (DialogContext->FileName);
      tBS->FreePool (DialogContext);
      return;
    }

    MsgDialogTitle = SctStrDuplicate (L"Wait a few minutes...");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);

    LogFilePath = SctPoolPrint (
                    L"%s\\%s",
                    gFT->FilePath,
                    EFI_SCT_PATH_LOG
                    );
    if (LogFilePath == NULL) {
      return;
    }

    //
    // Generate the report file
    //
    Status = GenerateReport (
               gFT->DevicePath,
               LogFilePath,
               FileName
               );

    if (EFI_ERROR (Status)) {
      MsgDialogTitle = SctStrDuplicate (L"Generate Report Error!");
    } else {
      MsgDialogTitle = SctStrDuplicate (L"Generate Report Succeed!");
    }

    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;

    DoDialog (MsgDialogTitle, &MsgDialogContext);

    tBS->FreePool (FileName);
    tBS->FreePool (DialogContext->DevicePath);
    tBS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      tBS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      tBS->FreePool (DialogContext->DevicePath);
    }
  }

  tBS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return;
}


VOID
DisplayLog (
  IN EFI_MENU_PAGE                *Page
  )
{

  EFI_STATUS               Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;
  CHAR16                  *CmdLine;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID **)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return;
  }

  tBS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_OPEN_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_LOG;

  //
  //get filename through FileDialog
  //
  Status = DoLogFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = SctStrDuplicate (L"Display Log Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
      && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    if (SctStrLen (DialogContext->FileName) > 4 &&
      SctStriCmp (DialogContext->FileName + SctStrLen (DialogContext->FileName) - 4, L".log") == 0) {
      FileName = SctStrDuplicate (DialogContext->FileName);
    }else if ( SctStrLen (DialogContext->FileName) > 1 &&
       SctStriCmp (DialogContext->FileName + SctStrLen (DialogContext->FileName) - 1, L".") == 0) {
       FileName = SctPoolPrint (L"%slog", DialogContext->FileName);
    }else {
      FileName = SctPoolPrint (L"%s.log", DialogContext->FileName);
    }
    if (FileName == NULL) {
      tBS->FreePool (DialogContext->DevicePath);
      tBS->FreePool (DialogContext->FileName);
      tBS->FreePool (DialogContext);
      return;
    }

    MsgDialogTitle = SctStrDuplicate (L"Wait a few minutes...");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;

    //
    //set default Console Attribute and clear the screen
    //
    tST->ConOut->SetAttribute (tST->ConOut, EFI_BACKGROUND_BLACK | EFI_WHITE);
    tST->ConOut->ClearScreen (tST->ConOut);

    CmdLine = SctPoolPrint (L"%s \"%s\"", gFT->ConfigData->EditCommandString, FileName);
    if (CmdLine != NULL) {
      Status = SctShellExecute (
                 &gFT->ImageHandle,
                 CmdLine,
                 FALSE,
                 NULL, NULL
                 );
      if (EFI_ERROR (Status)) {
        MsgDialogTitle = SctStrDuplicate (L"Cannot open the log file! Please check the edit command in the configuration page.");
        MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;

        DoDialog (MsgDialogTitle, &MsgDialogContext);
      }

      tBS->FreePool (CmdLine);
    }

    tBS->FreePool (FileName);
    tBS->FreePool (DialogContext->DevicePath);
    tBS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      tBS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      tBS->FreePool (DialogContext->DevicePath);
    }
  }

  tBS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return;
}

EFI_STATUS
EFIAPI
MainMenuLoadSeqFunc (
  IN EFI_MENU_PAGE                *Page
  )
{
  EFI_STATUS              Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID **)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  tBS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_OPEN_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_SEQ;

  //
  //get filename through FileDialog
  //
  Status = DoFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = SctStrDuplicate (L"Load Sequence Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
    && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    FileName = SctStrDuplicate (DialogContext->FileName);
    if (FileName == NULL) {
      tBS->FreePool (DialogContext->DevicePath);
      tBS->FreePool (DialogContext->FileName);
      tBS->FreePool (DialogContext);
      return EFI_DEVICE_ERROR;
    }

    Status = ResetTestCaseOrder ();

    Status = LoadTestSequence (
               gFT->DevicePath,
               FileName,
               &gFT->TestCaseList
               );
    if (EFI_ERROR (Status)) {
      MsgDialogTitle = SctStrDuplicate (L"Load Sequence Error!");
    } else {
      MsgDialogTitle = SctStrDuplicate (L"Load Sequence Succeed!");
    }

    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);

    tBS->FreePool (FileName);
    tBS->FreePool (DialogContext->DevicePath);
    tBS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      tBS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      tBS->FreePool (DialogContext->DevicePath);
    }
  }

  tBS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
MainMenuSaveSeqFunc (
  IN EFI_MENU_PAGE                *Page
  )
{
  EFI_STATUS              Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID **)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  tBS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_SAVE_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_SEQ;

  //
  //get devicepath and filename through FileDialog
  //
  Status = DoFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = SctStrDuplicate (L"Save Sequence Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
    && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    if (SctStrLen (DialogContext->FileName) > 4 &&
      SctStriCmp (DialogContext->FileName + SctStrLen (DialogContext->FileName) - 4, L".seq") == 0) {
      FileName = SctStrDuplicate (DialogContext->FileName);
    }else if ( SctStrLen (DialogContext->FileName) > 1 &&
       SctStriCmp (DialogContext->FileName + SctStrLen (DialogContext->FileName) - 1, L".") == 0) {
       FileName = SctPoolPrint (L"%sseq", DialogContext->FileName);
    }else {
      FileName = SctPoolPrint (L"%s.seq", DialogContext->FileName);
    }
    if (FileName == NULL) {
      tBS->FreePool (DialogContext->DevicePath);
      tBS->FreePool (DialogContext->FileName);
      tBS->FreePool (DialogContext);
      return EFI_DEVICE_ERROR;
    }

    Status = SaveTestSequence (
               gFT->DevicePath,
               FileName,
               &gFT->TestCaseList
               );
    if (EFI_ERROR (Status)) {
      MsgDialogTitle = SctStrDuplicate (L"Save sequence Error!");
    } else {
      MsgDialogTitle = SctStrDuplicate (L"Save sequence Succeed!");
    }

    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);

    tBS->FreePool (FileName);
    tBS->FreePool (DialogContext->DevicePath);
    tBS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      tBS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      tBS->FreePool (DialogContext->DevicePath);
    }
  }

  tBS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MainMenuF9Func(
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle F9 key in case menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle Space key successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS                Status;
  EFI_INPUT_KEY             Key;
  EFI_DIALOG_CONTEXT        MsgDialogContext;
  CHAR16                   *MsgDialogTitle;

  //
  //check parameter.
  //
  if (Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MsgDialogTitle = SctStrDuplicate (L"Prepare running...");
  MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;
  DoDialog (MsgDialogTitle, &MsgDialogContext);

  tST->ConOut->SetAttribute (
                tST->ConOut,
                EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK
                );
  tST->ConOut->ClearScreen (tST->ConOut);

  Status = SctExecute ();
  if (Status != EFI_SUCCESS) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute - %r", Status));
  }

  //
  //Clear surplus key stroke.
  //
  Status = EFI_SUCCESS;
  while(!EFI_ERROR(Status)) {
    Status = tST->ConIn->ReadKeyStroke (tST->ConIn, &Key);
  }

  MenuPageRefresh (Page);
  return Status;
}

EFI_STATUS
EFIAPI
MainMenuClearFunc (
  IN EFI_MENU_PAGE                *Page
  )
{
  EFI_STATUS               Status;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;

  MsgDialogTitle = SctStrDuplicate (L"Deleting files ...");
  MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;

  DoDialog (MsgDialogTitle, &MsgDialogContext);

  Status = ResetAllTestResults ();
  MenuPageRefresh (Page);
  if (EFI_ERROR(Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test results - %r", Status));
    return Status;
  }

  gContinueExec = FALSE;
  return EFI_SUCCESS;
}
