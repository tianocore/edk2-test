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

  Operation.c

Abstract:

  This file provides the main operations of SCT.

--*/

#include "Sct.h"

//
// Internal functions declaration
//

EFI_STATUS
AttachSupportFiles (
  VOID
  );

EFI_STATUS
AttachConfigData (
  VOID
  );

EFI_STATUS
AttachCategoryData (
  VOID
  );

EFI_STATUS
AttachProxyFiles (
  VOID
  );

EFI_STATUS
AttachTestCases (
  VOID
  );

EFI_STATUS
AttachSkippedCases (
  VOID
  );

EFI_STATUS
AttachTestFiles (
  VOID
  );

EFI_STATUS
DoPreOperationAll (
  VOID
  );

EFI_STATUS
DoPreOperationContinue (
  VOID
  );

EFI_STATUS
DoPreOperationSequence (
  VOID
  );

EFI_STATUS
DoPreOperationUi (
  VOID
  );

//
// External functions implementation
//

EFI_STATUS
AttachFirstStageTestData (
  VOID
  )
/*++

Routine Description:

  Attach the first stage test data (before the test files are loaded).

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Attach all test support files
  //
  Status = AttachSupportFiles ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach support files - %r", Status));
    return Status;
  }

  //
  // Attach the test config data
  //
  Status = AttachConfigData ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach config data - %r", Status));
    return Status;
  }

  //
  // Attach the test category data
  //
  Status = AttachCategoryData ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach category data - %r", Status));
    return Status;
  }

  //
  // Attach the proxy cases
  //
  Status = AttachProxyFiles ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach proxy files - %r", Status));
    return Status;
  }

  //
  // Attach the test cases
  //
  Status = AttachTestCases ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach test cases - %r", Status));
    return Status;
  }

  //
  // Attach the skipped cases
  //
  Status = AttachSkippedCases ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach test cases - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AttachSecondStageTestData (
  VOID
  )
/*++

Routine Description:

  Attach the second stage test data (after the test files are loaded.)

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Attach the test files
  //
  Status = AttachTestFiles ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach test files - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoFirstStageOperations (
  VOID
  )
/*++

Routine Description:

  Do the first stage operations (before the test files are loaded).

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;
  BOOLEAN     UserInput;

  //
  // Check reset operation
  //
  if ((gFT->Operations & EFI_SCT_OPERATIONS_RESET) != 0) {
    //
    // Check the last test is finished or not when '-f' option is not included.
    //
    if (!IsTestFinished () && !gForceExecution) {
      //
      // Not finished, ask user to confirm that
      //
      Status = SctJudgeInput (
                 L"The last test is not finished. Are you sure to reset it? (Y/N)",
                 &UserInput
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Judge input - %r", Status));
        return Status;
      }

      if (!UserInput) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"User aborted!"));
        return EFI_ABORTED;
      }
    }

    //
    // Reset all test results
    //
    Status = ResetAllTestResults ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset all test results - %r", Status));
      return Status;
    }
  }

  //
  // Check execute all or execute sequence operation
  //
  if (((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) == EFI_SCT_OPERATIONS_ALL     ) ||
      ((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) == EFI_SCT_OPERATIONS_SEQUENCE)) {
    //
    // Check the last test is finished or not when '-f' option is not included.
    //
    if (!IsTestFinished () && !gForceExecution) {
      //
      // Not finished, ask user to confirm that
      //
      Status = SctJudgeInput (
                 L"The last test is not finished. Are you sure to start a new test? (Y/N)",
                 &UserInput
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Judge input - %r", Status));
        return Status;
      }

      if (!UserInput) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"User aborted!"));
        return EFI_ABORTED;
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
DoPassiveModeOperations (
  VOID
  )
{
  EFI_STATUS                                Status;

  //
  // Handle different operations in passive mode
  //
  switch(gFT->Operations) {
  case EFI_SCT_OPERATIONS_SEQUENCE | EFI_SCT_OPERATIONS_PASSIVEMODE:
  case EFI_SCT_OPERATIONS_SEQUENCE | EFI_SCT_OPERATIONS_PASSIVEMODE | EFI_SCT_OPERATIONS_VERBOSE: 
    Status = NetAssertionUtilityInstall();
    if (EFI_ERROR(Status)) {
      EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"NetAssertionUtilityInstall fail - %r", Status));
    }

    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"DoPassiveModeOperations: Do sct -s -p Begain"));

    //
    // Execute the test cases in the sequence file
    //
    Status = DoPreOperationSequence ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation SEQUENCE - %r", Status));
      return Status;
    }
    Status = SctExecute ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation SEQUENCE - %r", Status));
      return Status;
    }

    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"DoPassiveModeOperations: Do sct -s -p End"));

    NetAssertionUtilityUninstall();

    break;

  case EFI_SCT_OPERATIONS_CONTINUE | EFI_SCT_OPERATIONS_PASSIVEMODE:
  case EFI_SCT_OPERATIONS_CONTINUE | EFI_SCT_OPERATIONS_PASSIVEMODE  | EFI_SCT_OPERATIONS_VERBOSE:
  		
    Status = NetAssertionUtilityInstall();
    if (EFI_ERROR(Status)) {
      EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"NetAssertionUtilityInstall fail - %r", Status));
    }

    //
    // Continue execute the test cases and then enter into SCT passive execution
    //
    Status = DoPreOperationContinue ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation CONTINUE - %r", Status));
      return Status;
    }
    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"Do SctContinueExecute Begin"));
    Status = SctContinueExecute ();
	EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"Do SctContinueExecute End"));
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation CONTINUE - %r", Status));
    }

    NetAssertionUtilityUninstall();

    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"NetAssertionUtilityUninstall success"));

    Status = DelaySctAgentCmdPost(EFI_SCT_CONTINUE_EXECUTION_NAME,Status, (Status == EFI_SUCCESS) ? PASS : FAIL);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"DelaySctAgentCmdPost success"));

    //
    // Finish the continue execution and then enter into passive execution
    //
    Status = SctPassiveExecute();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Check if need enter passive mode - %r", Status));
      return Status;
    }

    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"SctPassiveExecute success"));

    //
    // Delete the passive test context
    //
    Status = PassiveTestContextDelete(gFT->DevicePath, SCT_PASSIVE_MODE_RECORD_FILE);
    if (EFI_ERROR(Status)) {
      EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"PassiveTestContextDelete Fail - %r", Status));
      return Status;
    }

    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"PassiveTestContextDelete success"));

	break;

  case EFI_SCT_OPERATIONS_REPORT | EFI_SCT_OPERATIONS_PASSIVEMODE:
//    Status = NetAssertionUtilityInstall();
//    if (EFI_ERROR(Status)) {
//      EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"NetAssertionUtilityInstall fail - %r", Status));
//    }

    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"DoPassiveModeOperations: Do sct -g -p Begain"));

    Status = DoThirdStageOperations ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"sct -g -p - %r", Status));
      return Status;
    }

    EFI_SCT_DEBUG((EFI_SCT_D_TRACE, L"DoPassiveModeOperations: Do sct -g -p End"));

//    NetAssertionUtilityUninstall();

    break;
  case EFI_SCT_OPERATIONS_PASSIVEMODE:
  case EFI_SCT_OPERATIONS_PASSIVEMODE | EFI_SCT_OPERATIONS_VERBOSE:
    //
    // Create a new the passive test context
    //
    Status = PassiveTestContextCreate (gFT->DevicePath, SCT_PASSIVE_MODE_RECORD_FILE);
    if (EFI_ERROR(Status)) {
      EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"PassiveTestContextCreate fail - %r", Status));
      return Status;
    }

    //
    // Should choose NIC before enter into passive test with command "sct -p xxx"
    //
    EntsChooseNICAndSave();

    //
    // Generate CaseTree file for sychronization with EMS
    //
    GenerateCaseTreeFile();

    Status = SctPassiveExecute();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPassiveExecute error - %r", Status));
    }
    //
    // Delete the passive test context
    //
    Status = PassiveTestContextDelete(gFT->DevicePath, SCT_PASSIVE_MODE_RECORD_FILE);
    if (EFI_ERROR(Status)) {
      EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"PassiveTestContextDelete Fail - %r", Status));
      return Status;
    }
    break;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
DoNativeModeOperations (
  VOID
  )
{
  EFI_STATUS                          Status;

  //
  // Handle different operations in native mode
  //
  switch (gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) {
  case EFI_SCT_OPERATIONS_ALL:
    //
    // Execute all test cases
    //
    Status = DoPreOperationAll ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation ALL - %r", Status));
      return Status;
    }

    Status = SctExecute ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation ALL - %r", Status));
      return Status;
    }

    break;

  case EFI_SCT_OPERATIONS_CONTINUE :    
    //
    // Continue execute the test cases
    //
    Status = DoPreOperationContinue ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation CONTINUE - %r", Status));
      return Status;
    }
  
    Status = SctContinueExecute ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation CONTINUE - %r", Status));
      return Status;
    }

    break;

  case EFI_SCT_OPERATIONS_SEQUENCE:
    //
    // Execute the test cases in the sequence file
    //
    Status = DoPreOperationSequence ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation SEQUENCE - %r", Status));
      return Status;
    }

    Status = SctExecute ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation SEQUENCE - %r", Status));
      return Status;
    }

    break;

  case EFI_SCT_OPERATIONS_UI:
    //
    // Turn into the user-friendly interface
    //
    Status = DoPreOperationUi ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation UI - %r", Status));
      return Status;
    }

    Status = SctMenu ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation UI - %r", Status));
      return Status;
    }

    break;
  }

  switch(gFT->Operations & EFI_SCT_OPERATIONS_HIGH_MASK) {
  case EFI_SCT_OPERATIONS_REPORT:
    //
    // generate report
    //
    Status = DoThirdStageOperations ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"generate report - %r", Status));
      return Status;
    }
	break;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
DoSecondStageOperations (
  VOID
  )
/*++

Routine Description:

  Do the second stage operations (after the test files are loaded).

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS                                Status;

  Status = EFI_SUCCESS;

  if (gFT->Operations & EFI_SCT_OPERATIONS_PASSIVEMODE) {
    Status = DoPassiveModeOperations();
  } else {
    Status = DoNativeModeOperations();
  }

  return Status;
}


EFI_STATUS
DoThirdStageOperations (
  VOID
  )
/*++

Routine Description:

  Do the third stage operations (generate report).

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS        Status;
  CHAR16            *LogFilePath;
  EFI_FILE_HANDLE   Handle;

  //
  // Check report operation
  //
  if ((gFT->Operations & EFI_SCT_OPERATIONS_REPORT) != 0) {
    SctPrint (L"Generate test report. Expect this to take about several minutes ...\n");

    LogFilePath = SctPoolPrint (
                    L"%s\\%s",
                    gFT->FilePath,
                    EFI_SCT_PATH_LOG
                    );
    if (LogFilePath == NULL) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Try to create the report file
    //
    Status = SctCreateFileFromDevicePath (
               gFT->DevicePath,
               gFT->RepFileName,
               &Handle
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create report file - %r", Status));
      SctPrint (L"  ERROR: Cannot create the report file. Status - %r\n", Status);
      tBS->FreePool (LogFilePath);
      return Status;
    }

    Handle->Close (Handle);

    //
    // Generate the report file
    //
    Status = GenerateReport (
               gFT->DevicePath,
               LogFilePath,
               gFT->RepFileName
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Generate report file - %r", Status));
      SctPrint (L"  ERROR: Cannot generate the report file. Status - %r\n", Status);
      tBS->FreePool (LogFilePath);
      return Status;
    }

    SctPrint (L"  Succeed!\n");
    tBS->FreePool (LogFilePath);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
AttachSupportFiles (
  VOID
  )
/*++

Routine Description:

  Attach the test support files.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;

  //
  // Create the test support file path
  //
  FilePath = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_PATH_SUPPORT
               );
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the test support files
  //
  SctPrint (L"Load support files ...\n");

  Status = LoadSupportFiles (
             gFT->DevicePath,
             FilePath,
             TRUE,                // Recursive
             &gFT->SupportFileList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load support files - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);

  //
  // Open the standard test support files
  //
  Status = OpenStandardSupportFiles ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open standard support files - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AttachConfigData (
  VOID
  )
/*++

Routine Description:

  Attach the test configuration data.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Allocate memory for the configuration data
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_CONFIG_DATA),
                 (VOID **)&gFT->ConfigData
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  //
  // Create the configuration data file name
  //
  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_CONFIG
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the configuration data
  //
  Status = LoadConfigData (
             gFT->DevicePath,
             FileName,
             gFT->ConfigData
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load config data - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }

  //
  // Now we provides -v in cmd to enable/disable screen out put 
  // So when use -a -c -s, Screen output depends on cmd input
  // while not configure data.
  // 
  if ((gFT->Operations & EFI_SCT_OPERATIONS_UI) == 0) {
    if (gFT->Operations & EFI_SCT_OPERATIONS_VERBOSE) {
      gFT->ConfigData->EnableScreenOutput = FALSE;
    }
    else {
      gFT->ConfigData->EnableScreenOutput = TRUE;
    }
  }
  
  tBS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AttachCategoryData (
  VOID
  )
/*++

Routine Description:

  Attach the category data.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Create the category data file name
  //
  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_CATEGORY
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the category data
  //
  Status = LoadCategoryData (
             gFT->DevicePath,
             FileName,
             &gFT->CategoryList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load category data - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }

  tBS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
AttachProxyFiles (
  VOID
  )
/*++

Routine Description:

  Attach the proxy files.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;

  //
  // Create the test support file path
  //
  FilePath = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_PATH_PROXY
               );
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the test support files
  //
  SctPrint (L"Load proxy files ...\n");

  Status = LoadProxyFiles (
             gFT->DevicePath,
             FilePath,
             TRUE,                // Recursive
             &gFT->ProxyFileList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load proxy files - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
AttachTestCases (
  VOID
  )
/*++

Routine Description:

  Attach the test cases.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Create the test cases file name
  //
  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_TEST_CASE
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the test cases
  //
  Status = LoadTestCases (
             gFT->DevicePath,
             FileName,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load test cases - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }

  tBS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
AttachSkippedCases (
  VOID
  )
/*++

Routine Description:

  Attach the skipped cases.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Create the test cases file name
  //
  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_SKIPPED_CASE
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the test cases
  //
  Status = LoadSkippedCases (
             gFT->DevicePath,
             FileName,
             &gFT->SkippedCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load skipped cases - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }

  tBS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AttachTestFiles (
  VOID
  )
/*++

Routine Description:

  Attach the test files.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;

  //
  // Check operations
  //
  if ((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) == 0) {
    //
    // No execute operation. Need not attach the test files
    //
    return EFI_SUCCESS;
  }

  //
  // Create the test file path
  //
  FilePath = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_PATH_TEST
               );
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load test files
  //
  SctPrint (L"Load test files ...\n");

  Status = LoadTestFiles (
             gFT->DevicePath,
             FilePath,
             TRUE,                // Recursive
             &gFT->TestFileList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load test files - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoPreOperationAll (
  VOID
  )
/*++

Routine Description:

  Do the pre-operation for operation ALL.

--*/
{
  EFI_STATUS      Status;
  SCT_LIST_ENTRY  *Link;
  SCT_LIST_ENTRY  TestCaseList;

  SctInitializeListHead (&TestCaseList);

  //
  // Create the test cases
  //
  Status = CreateTestCases (&TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test cases - %r", Status));
    return Status;
  }

  //
  // Merge the test cases
  //
  Status = MergeTestCases (
             &TestCaseList,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge tet cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  //
  // Free the old test cases and add the new one
  //
  Status = FreeTestCases (&gFT->TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  while (!SctIsListEmpty (&TestCaseList)) {
    Link = TestCaseList.ForwardLink;
    SctRemoveEntryList (Link);
    SctInsertTailList (&gFT->TestCaseList, Link);
  }

  //
  // Reset the order of test cases
  //
  Status = ResetTestCaseOrder ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test case order - %r", Status));
    return Status;
  }

  //
  // Create the test nodes
  //
  Status = CreateTestNodes (&gFT->TestNodeList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test nodes - %r", Status));
    return Status;
  }

  //
  // Build the order of test cases
  //
  Status = BuildTestCaseOrder ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Build test case order - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoPreOperationContinue (
  VOID
  )
/*++

Routine Description:

  Do pre-operation for operation CONTINUE.

--*/
{
  EFI_STATUS      Status;
  SCT_LIST_ENTRY  *Link;
  SCT_LIST_ENTRY  TestCaseList;

  SctInitializeListHead (&TestCaseList);

  //
  // Create the test cases
  //
  Status = CreateTestCases (&TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test cases - %r", Status));
    return Status;
  }

  //
  // Merge the test cases
  //
  Status = MergeTestCases (
             &TestCaseList,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge tet cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  //
  // Free the old test cases and add the new one
  //
  Status = FreeTestCases (&gFT->TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  while (!SctIsListEmpty (&TestCaseList)) {
    Link = TestCaseList.ForwardLink;
    SctRemoveEntryList (Link);
    SctInsertTailList (&gFT->TestCaseList, Link);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoPreOperationSequence (
  VOID
  )
/*++

Routine Description:

  Do pre-operation for operation SEQUENCE.

--*/
{
  EFI_STATUS      Status;
  SCT_LIST_ENTRY  *Link;
  SCT_LIST_ENTRY  TestCaseList;

  SctInitializeListHead (&TestCaseList);

  //
  // Create the test cases
  //
  Status = CreateTestCases (&TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test cases - %r", Status));
    return Status;
  }

  //
  // Merge the test cases
  //
  Status = MergeTestCases (
             &TestCaseList,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge tet cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  //
  // Free the old test cases and add the new one
  //
  Status = FreeTestCases (&gFT->TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  while (!SctIsListEmpty (&TestCaseList)) {
    Link = TestCaseList.ForwardLink;
    SctRemoveEntryList (Link);
    SctInsertTailList (&gFT->TestCaseList, Link);
  }

  //
  // Reset the order of test cases
  //
  Status = ResetTestCaseOrder ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test case order - %r", Status));
    return Status;
  }

  //
  // Load the test sequence
  //
  Status = LoadTestSequence (
             gFT->DevicePath,
             gFT->SeqFileName,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load test sequence - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoPreOperationUi (
  VOID
  )
/*++

Routine Description:

  Do pre-operation for operation UI.

--*/
{
  EFI_STATUS      Status;
  SCT_LIST_ENTRY  *Link;
  SCT_LIST_ENTRY  TestCaseList;

  SctInitializeListHead (&TestCaseList);

  //
  // Create the test cases
  //
  Status = CreateTestCases (&TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test cases - %r", Status));
    return Status;
  }

  //
  // Merge the test cases
  //
  Status = MergeTestCases (
             &TestCaseList,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge tet cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  //
  // Free the old test cases and add the new one
  //
  Status = FreeTestCases (&gFT->TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  while (!SctIsListEmpty (&TestCaseList)) {
    Link = TestCaseList.ForwardLink;
    SctRemoveEntryList (Link);
    SctInsertTailList (&gFT->TestCaseList, Link);
  }

  //
  // Create the test nodes
  //
  Status = CreateTestNodes (&gFT->TestNodeList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test nodes - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
