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

  Execute.c

Abstract:

  This file provides the test execution services.

--*/

#include "Sct.h"


//
// Internal functions declaration
//


EFI_STATUS
ExecuteStart (
  IN EFI_SCT_TEST_CASE            *TestCase
  );

EFI_STATUS
ContinueExecuteStart (
  IN EFI_SCT_TEST_CASE            *TestCase
  );

EFI_STATUS
ExecuteMainFunc (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteBbTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_INTERFACE_FILTER         FilterFunc
  );

EFI_STATUS
ExecuteMdeLibraryInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteWbTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteApTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteBbTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN VOID                         *Interface OPTIONAL,
  IN EFI_HANDLE                   Handle OPTIONAL
  );

EFI_STATUS
ExecuteWbTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL
  );

EFI_STATUS
ExecuteApTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
PreExecuteTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL,
  OUT BOOLEAN                     *IsSkip
  );

EFI_STATUS
PostExecuteTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_STATUS                   TestStatus
  );

EFI_STATUS
InitializeTestConfigData (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL,
  IN EFI_LIB_CONFIG_DATA          *ConfigData
  );

EFI_STATUS
FreeTestConfigData (
  IN EFI_LIB_CONFIG_DATA          *ConfigData
  );

UINTN
GetLibInstanceNo (
  IN SCT_LIST_ENTRY        *LinkHead
  );

//
// External functions implementation
//

EFI_STATUS
SctExecute (
  VOID
  )
/*++

Routine Description:

  Execute the test cases.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS                       Status;
  EFI_SCT_TEST_CASE                *TestCase;
  CHAR16                           *FileName = NULL;
  EFI_FILE_HANDLE                  FileHandle;
  EFI_HANDLE                       DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *Vol = NULL;
  EFI_FILE_HANDLE                  RootDir;
  EFI_DEVICE_PATH_PROTOCOL         *DevicePath = gFT->DevicePath;
  
  SctPrint (L"Test preparing...\n");

  //
  // 1. Create verbose state file for system reset 
  // startup.nsh will check it to decide whether attach -v option during restart
  //
  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_PATH_VERBOSE
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gntBS->LocateDevicePath (
                    &gEfiSimpleFileSystemProtocolGuid,
                    &DevicePath,
                    &DeviceHandle
                    );
  if (EFI_ERROR(Status)) {
    goto FUNC_EXIT;
  }
  
  Status = gntBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiSimpleFileSystemProtocolGuid,
                    (VOID *)&Vol
                    );
  if (EFI_ERROR(Status)) {
    goto FUNC_EXIT;
  }
  
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    goto FUNC_EXIT;
  }
  
  Status = CreateFile (RootDir, FileName, &FileHandle);
  if (EFI_ERROR(Status)) {
    SctFreePool (FileName);
    return Status;
  }
  FileHandle->Close (FileHandle);
  
  //
  // if screen output enabled, always remove .verbose.mode file
  //
  if (gFT->ConfigData->EnableScreenOutput == TRUE) {
    RemoveFile (gFT->DevicePath, FileName);
  }

  //
  // 2. Reset the test results of the selected test cases
  //
  Status = ResetTestCaseResults ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test case results - %r", Status));
    goto FUNC_EXIT;
  }

  //
  // 3. Find the next test case
  //
  Status = GetNextTestCase (&TestCase);
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get next test case - %r", Status));
    goto FUNC_EXIT;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // No test case is found, all test cases have been executed
    //
    goto FUNC_EXIT;
  }
  
  //
  // 4. Start the execution
  //
  Status = ExecuteStart (TestCase);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute start - %r", Status));
  }

FUNC_EXIT:
	
  //
  // 5. Remove verbose state file when test case all finished
  // 
  if (gFT->ConfigData->EnableScreenOutput == FALSE) {
    RemoveFile (gFT->DevicePath, FileName);
  }

  if (FileName != NULL) {
    SctFreePool (FileName);
  }
  
  //
  // Done
  //
  return Status;
}


EFI_STATUS
SctContinueExecute (
  VOID
  )
/*++

Routine Description:

  Continue to execute the test cases after system reset or any interrupts.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS                       Status;
  EFI_SCT_TEST_CASE                *TestCase;
  CHAR16                           *FileName = NULL;
  EFI_FILE_HANDLE                  FileHandle;
  EFI_HANDLE                       DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *Vol = NULL;
  EFI_FILE_HANDLE                  RootDir;
  EFI_DEVICE_PATH_PROTOCOL         *DevicePath = gFT->DevicePath;
  
  SctPrint (L"Continue test preparing...\n");
 
  //
  // 1. Create verbose state file for system reset 
  // startup.nsh will check it to decide whether attach -v option during restart
  //
  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_PATH_VERBOSE
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gntBS->LocateDevicePath (
                    &gEfiSimpleFileSystemProtocolGuid,
                    &DevicePath,
                    &DeviceHandle
                    );
  if (EFI_ERROR(Status)) {
    goto FUNC_EXIT;
  }
  
  Status = gntBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiSimpleFileSystemProtocolGuid,
                    (VOID *)&Vol
                    );
  if (EFI_ERROR(Status)) {
    goto FUNC_EXIT;
  }
  
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    goto FUNC_EXIT;
  }
  
  Status = CreateFile (RootDir, FileName, &FileHandle);
  if (EFI_ERROR(Status)) {
  	 SctFreePool (FileName);
    return Status;
  }
  FileHandle->Close (FileHandle);
  
  //
  // if screen output enabled, always remove .verbose.mode file
  //
  if (gFT->ConfigData->EnableScreenOutput == TRUE) {
    RemoveFile (gFT->DevicePath, FileName);
  }

  //
  // Initialize the first time execute flag
  //
  gFT->IsFirstTimeExecute = FALSE;

  //
  // Find the running test case
  //
  Status = GetRunningTestCase (&TestCase);
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get running test case - %r", Status));
    goto FUNC_EXIT;
  }

  if (Status != EFI_NOT_FOUND) {
    //
    // Continue start the execution
    //
    Status = ContinueExecuteStart (TestCase);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Continue execute start - %r", Status));
    }

    //
    // Done
    //
    goto FUNC_EXIT;
  }

  //
  // No running test case is found, start normal execution
  //

  //
  // Find the next test case
  //
  Status = GetNextTestCase (&TestCase);
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get next test case - %r", Status));
    goto FUNC_EXIT;
	 }

  if (Status == EFI_NOT_FOUND) {
    //
    // No test case is found, all test cases have been executed
    //
    return EFI_SUCCESS;
  }

  //
  // 2. Start the execution
  //
  Status = ExecuteStart (TestCase);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute start - %r", Status));
  }


FUNC_EXIT:
  //
  // 3. Remove verbose state file when test case all finished
  // 
  if (gFT->ConfigData->EnableScreenOutput == FALSE) {    
    RemoveFile (gFT->DevicePath, FileName);
  }

  if (FileName != NULL) {
    SctFreePool (FileName);
  }
  
  //
  // Done
  //
  return Status;
}


//
// Internal functions implementation
//

EFI_STATUS
ExecuteStart (
  IN EFI_SCT_TEST_CASE            *TestCase
  )
/*++

Routine Description:

  Start the test execution from the input test case.

--*/
{
  EFI_STATUS            Status;
  EFI_SCT_EXECUTE_INFO  ExecuteInfo;

  //
  // Initialize the execute information
  //
  Status = InitializeExecuteInfo (
             TestCase,
             &ExecuteInfo
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initialize execute info - %r", Status));
    return Status;
  }

  //
  // Reset the execute test results
  //
  Status = ResetExecuteTestResults (
             &ExecuteInfo
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset execute test results - %r", Status));
    return Status;
  }

  //
  // Start the execution
  //
  Status = ExecuteMainFunc (&ExecuteInfo);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute - %r", Status));
    return Status;
  }

  Status = SaveTestCases ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Save test cases - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ContinueExecuteStart (
  IN EFI_SCT_TEST_CASE            *TestCase
  )
/*++

Routine Description:

  Continue to start the test execution from the input test case.

--*/
{
  EFI_STATUS            Status;
  EFI_SCT_EXECUTE_INFO  ExecuteInfo;
  CHAR16                *FullMetaName;

  //
  // Initialize the execute information
  //
  Status = InitializeExecuteInfo (
             TestCase,
             &ExecuteInfo
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initialize execute info - %r", Status));
    return Status;
  }

  //
  // Get the full meta name of key files
  //
  Status = GetKeyFileFullMetaName (
             &ExecuteInfo,
             &FullMetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get key file full meta name - %r", Status));
    return Status;
  }

  //
  // Get the test information from the key files
  //
  Status = GetInstanceAssertion (
             gFT->DevicePath,
             FullMetaName,
             &ExecuteInfo.State,
             &ExecuteInfo.Index,
             &ExecuteInfo.Iteration,
             &ExecuteInfo.Passes,
             &ExecuteInfo.Warnings,
             &ExecuteInfo.Failures
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get instance assertion - %r", Status));
    tBS->FreePool (FullMetaName);
    return Status;
  }

  tBS->FreePool (FullMetaName);

  //
  // Start the execution
  //
  Status = ExecuteMainFunc (&ExecuteInfo);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute - %r", Status));
    return Status;
  }

  Status = SaveTestCases ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Save test cases - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteMainFunc (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  It is main routine for test execution.

--*/
{
  EFI_STATUS          Status;
  EFI_SCT_TEST_CASE   *TestCase;
  CHAR16              DescBuff[256];
  UINTN               Remain;

  Remain = 0;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Execute test cases"));

  //
  // Walk through all test cases
  //
  while (TRUE) {
    //
    // Calculate the number of remained cases
    //
    GetTestCaseRemainNum(&Remain);
    SctPrint(L"  Remained test cases: %d\n", Remain);

    //
    // Send assertion to remotion computer in passive mode to inform case begin.
    //
    if (gFT->Operations & EFI_SCT_OPERATIONS_PASSIVEMODE) {
      SctSPrint (DescBuff, 256, L"%s Case Begins!\n", ExecuteInfo->TestCase->Name);
      Status = NetRecordAssertion(NET_EFI_TEST_ASSERTION_CASE_BEGIN, ExecuteInfo->TestCase->Guid, DescBuff);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"NetRecordAssertion - %r", Status));
        return Status;
      }
    }

    //
    // Execute the test case and send case running status to host
    // 
    Status = ExecuteTestCase (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute test case - %r", Status));
      return Status;
    }

    //
    // Send assertion to remotion computer in passive mode to inform case end.
    //
    if (gFT->Operations & EFI_SCT_OPERATIONS_PASSIVEMODE) {
      SctSPrint (DescBuff, 256, L"PASS(%d) WARN(%d) FAIL(%d)\n", ExecuteInfo->TestCase->Passes, ExecuteInfo->TestCase->Warnings, ExecuteInfo->TestCase->Failures);
      Status = NetRecordAssertion(NET_EFI_TEST_ASSERTION_CASE_OVER, ExecuteInfo->TestCase->Guid, DescBuff);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"NetRecordAssertion - %r", Status));
        return Status;
      }
    }

    //
    // Find the next test case
    //
    Status = GetNextTestCase (&TestCase);
    if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get running test case - %r", Status));
      return Status;
    }

    if (Status == EFI_NOT_FOUND) {
      //
      // No test case is found, all test cases have been executed
      //
      return EFI_SUCCESS;
    }

    //
    // Initialize the execute information
    //
    Status = InitializeExecuteInfo (
               TestCase,
               ExecuteInfo
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initialize execute info - %r", Status));
      return Status;
    }

    //
    // Reset the execute test results
    //
    Status = ResetExecuteTestResults (
               ExecuteInfo
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset execute test results - %r", Status));
      return Status;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute a test case.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FullMetaName;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Deal with the different kind of test files
  //
  switch (ExecuteInfo->TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
    Status = ExecuteBbTestCase (ExecuteInfo, IhvInterfaceFilter);
	if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute IHV BB test case - %r", Status));
      return Status;
	}
	break;

  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    Status = ExecuteBbTestCase (ExecuteInfo, NULL);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute BB test case - %r", Status));
      return Status;
    }
    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    Status = ExecuteWbTestCase (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute WB test case - %r", Status));
      return Status;
    }
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    Status = ExecuteApTestCase (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute AP test case - %r", Status));
      return Status;
    }
    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    return EFI_UNSUPPORTED;
  }

  //
  // Get the full meta name of key files
  //
  Status = GetKeyFileFullMetaName (
             ExecuteInfo,
             &FullMetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get key file full meta name - %r", Status));
    return Status;
  }

  //
  // Get the results of test case
  //
  Status = GetInterfaceAssertion (
             gFT->DevicePath,
             FullMetaName,
             &ExecuteInfo->TestCase->Passes,
             &ExecuteInfo->TestCase->Warnings,
             &ExecuteInfo->TestCase->Failures
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get interface assertion - %r", Status));
	goto Done;
  }

Done:
  tBS->FreePool (FullMetaName);
  return EFI_SUCCESS;
}

EFI_STATUS
ExecuteMdeLibraryInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
{
  EFI_STATUS                      Status;
  EFI_GUID                        *Guid;
  EFI_BB_TEST_PROTOCOL            *BbTest;
  UINTN                           Index;
  MDK_LIBRARY_INSTANCE            *MdkLibInstance;
  SCT_LIST_ENTRY                  *Link;
  UINTN                           NoInstance;
  UINTN                           InstanceIndex;

  MdkLibInstance        = NULL;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Black-box test protocol
  //
  BbTest = (EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;

  //
  // Get the GUID of tested interface
  //
  if (ExecuteInfo->Category != NULL) {
    Guid = &ExecuteInfo->Category->InterfaceGuid;
  } else {
    Guid = &BbTest->CategoryGuid;
  }

  //
  // Search this GUID from configuration table
  //
  for (Index = 0; Index < tST->NumberOfTableEntries; Index++) {
    if (SctCompareGuid (Guid, &tST->ConfigurationTable[Index].VendorGuid) == 0) {
      //
	  // Get library instance No.
      //
      Link = (SCT_LIST_ENTRY *) tST->ConfigurationTable[Index].VendorTable; 

      NoInstance = GetLibInstanceNo(Link);

      SctPrint (L"\nNumber of library instance: %hd\n", NoInstance); 
        
      while (ExecuteInfo->Index < NoInstance) {
        //
        // Get the library instance from link list based on the InstanceIndex
        //
        InstanceIndex = 0;
        Link = ((SCT_LIST_ENTRY *) tST->ConfigurationTable[Index].VendorTable)->ForwardLink;
        for (InstanceIndex = 0; InstanceIndex < ExecuteInfo->Index; InstanceIndex ++) {
          Link = Link->ForwardLink;
        }
        MdkLibInstance = CR (Link, MDK_LIBRARY_INSTANCE, Link, MDK_LIBRARY_INSTANCE_SIGNATURE);

		//
        // Print out the library instance name
        //
        SctPrint (L"\n\n");
        SctPrint (L"************************************************************\n");
        SctPrint (L"Library instance name: %hs\n", MdkLibInstance->Name);
        SctPrint (L"************************************************************\n");
        SctPrint (L"\n");

        while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
          //
          // Configuration table item test
          //
          if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
            EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
            ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
            ExecuteInfo->Iteration ++;
            continue;
          }

          //
          // Process information
          //
          SctPrint (L"  Configuration table item test: %hs\n", ExecuteInfo->TestCase->Name);
          SctPrint (L"  Library instance name: %hs\n", MdkLibInstance->Name);
          SctPrint (L"  Instances: %hd/%hd\n", ExecuteInfo->Index + 1, NoInstance);
          SctPrint (L"  Iterations: %hd/%hd\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

          //
          // Start the test case with configuration table item
          //
          Status = ExecuteBbTestInstance (ExecuteInfo, MdkLibInstance->Interface, NULL);
          if (EFI_ERROR (Status)) {
            EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance - %r", Status));
            return Status;
          }

          ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
          ExecuteInfo->Iteration ++;
        }

        ExecuteInfo->Iteration = 0;
        ExecuteInfo->Index ++;
      }
      break;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ExecuteBbTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_INTERFACE_FILTER         InterfaceFilter
  )
/*++

Routine Description:

  Execute a black-box test case.

--*/
{
  EFI_STATUS            Status;
  UINTN                 Index;
  UINTN                 NoInstance;
  UINTN                 InstanceIndex;
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;
  EFI_GUID              *Guid;
  SCT_LIST_ENTRY        *Link;
  MDK_LIBRARY_INSTANCE  *MdkLibInstance;
  VOID                  *Interface;
  EFI_BB_TEST_PROTOCOL  *BbTest;
  UINTN                 HandleIndex;
  CHAR16                *FileName;

  MdkLibInstance = NULL;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Black-box test protocol
  //
  BbTest = (EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;

  //
  // Get the GUID of tested interface
  //
  if (ExecuteInfo->Category != NULL) {
    Guid = &ExecuteInfo->Category->InterfaceGuid;
  } else {
    Guid = &BbTest->CategoryGuid;
  }

  //
  // Get the tested interface from the GUID
  //
  if (SctCompareGuid (Guid, &gEfiGenericCategoryGuid) == 0) {
    while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
      //
      // Generic services test
      //
      if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
        ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
        ExecuteInfo->Iteration ++;
        continue;
      }

      //
      // Process information
      //
      SctPrint (L"  Generic services test: %s\n", ExecuteInfo->TestCase->Name);
      SctPrint (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

      //
      // Start the test case with NULL interface
      //
      Status = ExecuteBbTestInstance (ExecuteInfo, NULL, NULL);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance - %r", Status));
        return Status;
      }

      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
    }

  } else if (SctCompareGuid (Guid, &gEfiBootServicesCategoryGuid) == 0) {
    while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
      //
      // Boot services test
      //
      if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
        ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
        ExecuteInfo->Iteration ++;
        continue;
      }

      //
      // Process information
      //
      SctPrint (L"  Boot services test: %s\n", ExecuteInfo->TestCase->Name);
      SctPrint (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

      //
      // Start the test case with BS interface
      //
      Status = ExecuteBbTestInstance (ExecuteInfo, tBS, NULL);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance - %r", Status));
        return Status;
      }

      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
    }

  } else if (SctCompareGuid (Guid, &gEfiRuntimeServicesCategoryGuid) == 0) {
    while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
      //
      // Runtime services test
      //
      if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
        ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
        ExecuteInfo->Iteration ++;
        continue;
      }

      //
      // Process information
      //
      SctPrint (L"  Runtime services test: %s\n", ExecuteInfo->TestCase->Name);
      SctPrint (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

      //
      // Start the test case with RT interface
      //
      Status = ExecuteBbTestInstance (ExecuteInfo, tRT, NULL);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance - %r", Status));
        return Status;
      }

      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
    }

  } else {
    //
    // Protocol test
    //
    Status = tBS->LocateHandleBuffer (
                   ByProtocol,
                   Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
    if ( (EFI_NOT_FOUND == Status) && (NoHandles == 0) ) {

      Status = RecordSkippedCases(ExecuteInfo);
      
      if (EFI_SUCCESS == Status) {
        //
        // Create the name of test case file
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
        
        Status = SaveSkippedCases (
                   gFT->DevicePath,
                   FileName,
                   ExecuteInfo
                   );
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Save skipped cases - %r", Status));
          tBS->FreePool (FileName);
          return Status;
        }
        
        tBS->FreePool (FileName);
      
      }
    }
    if (!EFI_ERROR (Status) && (NoHandles != 0)) {
      //
      // Walk through each instance need to be tested
      //
      for (HandleIndex = ExecuteInfo->Index; HandleIndex < NoHandles; HandleIndex++) {
        //
        // Add one new logic to filter the SerialIo Protocol
        //
        if (SctCompareGuid (Guid, &gEfiSerialIoProtocolGuid) == 0) {
          Status = tBS->OpenProtocol (
                         HandleBuffer[HandleIndex],
                         Guid,
                         &Interface,
                         HandleBuffer[HandleIndex],
		                 NULL,
		                 0x00000020    //EXCLUSIVE
                         );
          if (EFI_ERROR (Status)) {
            EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open protocol - %r", Status));
            return Status;
          }
        } else {
          Status = tBS->HandleProtocol (
                         HandleBuffer[HandleIndex],
                         Guid,
                         &Interface
                         );
          if (EFI_ERROR (Status)) {
            EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Handle protocol - %r", Status));
            return Status;
          }
        }
  
        if (InterfaceFilter != NULL) {
          if (InterfaceFilter (Interface, gFT->SupportHandle, Guid) == FALSE) {
            ExecuteInfo->Iteration = 0;
  	        continue;
          }
        }
  
        while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
          if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
            EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
            ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
            ExecuteInfo->Iteration ++;
            continue;
          }
  
          //
          // Process information
          //
          SctPrint (L"  Protocol test: %s\n", ExecuteInfo->TestCase->Name);
          SctPrint (L"  Instances: %d/%d\n", HandleIndex + 1, NoHandles);
          SctPrint (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);
  
          Status = ExecuteBbTestInstance (
                     ExecuteInfo,
                     Interface,
                     HandleBuffer[HandleIndex]
                     );
          if (EFI_ERROR (Status)) {
            EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance- %r", Status));
            return Status;
          }
  
          ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
          ExecuteInfo->Iteration++;
        }

		if (SctCompareGuid (Guid, &gEfiSerialIoProtocolGuid) == 0) {
          Status = tBS->CloseProtocol (
                         HandleBuffer[HandleIndex],
                         Guid,
                         HandleBuffer[HandleIndex],
		                 NULL
                         );
          if (EFI_ERROR (Status)) {
            EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Close protocol - %r", Status));
            return Status;
          }
        }
        ExecuteInfo->Iteration = 0;
        ExecuteInfo->Index ++;
      }
    }

    //
    // Search this GUID from configuration table
    //
    for (Index = 0; Index < tST->NumberOfTableEntries; Index++) {
      if (SctCompareGuid (Guid, &tST->ConfigurationTable[Index].VendorGuid) == 0) {
        //
	    // Get library instance No.
        //
        Link = (SCT_LIST_ENTRY *) tST->ConfigurationTable[Index].VendorTable; 
        
        NoInstance = GetLibInstanceNo(Link);

        SctPrint (L"\nNumber of library instance: %hd\n", NoInstance); 
        
        while (ExecuteInfo->Index < NoInstance) {
          //
          // Get the library instance from link list based on the InstanceIndex
          //
          InstanceIndex = 0;
          Link = ((SCT_LIST_ENTRY *) tST->ConfigurationTable[Index].VendorTable)->ForwardLink;
          for (InstanceIndex = 0; InstanceIndex < ExecuteInfo->Index; InstanceIndex ++) {
            Link = Link->ForwardLink;
          }
          MdkLibInstance = CR (Link, MDK_LIBRARY_INSTANCE, Link, MDK_LIBRARY_INSTANCE_SIGNATURE);

          //
          // Print out the library instance name
          //
          SctPrint (L"\n\n");
          SctPrint (L"************************************************************\n");
          SctPrint (L"Library instance name: %hs\n", MdkLibInstance->Name);
          SctPrint (L"************************************************************\n");
          SctPrint (L"\n");
          
          while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
            //
            // Configuration table item test
            //
            if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
              EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
              ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
              ExecuteInfo->Iteration ++;
              continue;
            }

            //
            // Process information
            //
            SctPrint (L"  Configuration table item test: %hs\n", ExecuteInfo->TestCase->Name);
            SctPrint (L"  Library instance name: %hs\n", MdkLibInstance->Name);
            SctPrint (L"  Instances: %hd/%hd\n", ExecuteInfo->Index + 1, NoInstance);
            SctPrint (L"  Iterations: %hd/%hd\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

            //
            // Start the test case with configuration table item
            //
            Status = ExecuteBbTestInstance (ExecuteInfo, MdkLibInstance->Interface, NULL);
            if (EFI_ERROR (Status)) {
              EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance - %r", Status));
              return Status;
            }

            ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
          ExecuteInfo->Iteration ++;
        }

        ExecuteInfo->Iteration = 0;
        ExecuteInfo->Index ++;
        }
        break;
      }
    }
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteWbTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute a white-box test case.

--*/
{
  EFI_STATUS            Status;
  EFI_WB_TEST_PROTOCOL  *WbTest;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // White-box test protocol
  //
  WbTest = (EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;

  while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
    //
    // White-box test
    //
    if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
      continue;
    }

    //
    // Process infromation
    //
    SctPrint (L"  White-box test: %s\n", ExecuteInfo->TestCase->Name);
    SctPrint (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

    Status = ExecuteWbTestInstance (ExecuteInfo, WbTest->ClientHandle);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a WB test instance - %r", Status));
      return Status;
    }

    ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
    ExecuteInfo->Iteration ++;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteApTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute an application or a script test case.

--*/
{
  EFI_STATUS              Status;
  EFI_AP_TEST_INTERFACE   *ApTest;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Application test interface
  //
  ApTest = (EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol;

  while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
    //
    // Application test
    //
    if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
      continue;
    }

    //
    // Process infromation
    //
    SctPrint (L"  Application test: %s\n", ExecuteInfo->TestCase->Name);
    SctPrint (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

    Status = ExecuteApTestInstance (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute an AP test instance - %r", Status));
      return Status;
    }

    ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
    ExecuteInfo->Iteration ++;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteBbTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN VOID                         *Interface OPTIONAL,
  IN EFI_HANDLE                   Handle OPTIONAL
  )
/*++

Routine Description:

  Execute a black-box test instance.

--*/
{
  EFI_STATUS            Status;
  EFI_STATUS            TestStatus;
  BOOLEAN               IsSkip;
  EFI_BB_TEST_PROTOCOL  *BbTest;
  EFI_BB_TEST_ENTRY     *BbEntry;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Black-box test instance
  //
  BbTest  = (EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;
  BbEntry = (EFI_BB_TEST_ENTRY *) ExecuteInfo->TestEntry;

  TestStatus = EFI_UNSUPPORTED;

  //
  // Do pre-operations for a test instance
  //
  Status = PreExecuteTestInstance (
             ExecuteInfo,
             Handle,
             &IsSkip
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre execute test instance - %r", Status));
    return Status;
  }

  if (!IsSkip) {
    //
    // Open the test support files
    //
    Status = OpenExtendedSupportFiles (BbEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Open support files - %r", Status));
    }

    if (!EFI_ERROR (Status)) {
      //
      // Invoke the test entry point
      //
      TestStatus = BbEntry->EntryPoint (
                              BbTest,
                              Interface,
                              gFT->ConfigData->TestLevel,
                              gFT->SupportHandle
                              );
    }

    //
    // Close the test support files
    //
    Status = CloseExtendedSupportFiles (BbEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Close support files - %r", Status));
    }
  }

  //
  // Do post-operations for a test instance
  //
  Status = PostExecuteTestInstance (
             ExecuteInfo,
             TestStatus
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Post execute test instance - %r", Status));
    return Status;
  }

  //
  // Deal with the specific attributes of test case
  //
  if (!IsSkip) {
    //
    // Reset required
    //
    if ((BbEntry->CaseAttribute & EFI_TEST_CASE_RESET_REQUIRED) != 0) {
      FreeDebugServices ();

      //
      // Free 1 second to let all flush works done
      //
      tBS->Stall (1000000);
      tRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteWbTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL
  )
/*++

Routine Description:

  Execute a white-box test instance.

--*/
{
  EFI_STATUS            Status;
  EFI_STATUS            TestStatus;
  BOOLEAN               IsSkip;
  EFI_WB_TEST_PROTOCOL  *WbTest;
  EFI_WB_TEST_ENTRY     *WbEntry;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // White-box test instance
  //
  WbTest  = (EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;
  WbEntry = (EFI_WB_TEST_ENTRY *) ExecuteInfo->TestEntry;

  TestStatus = EFI_UNSUPPORTED;

  //
  // Do pre-operations for a test instance
  //
  Status = PreExecuteTestInstance (
             ExecuteInfo,
             Handle,
             &IsSkip
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre execute test instance - %r", Status));
    return Status;
  }

  if (!IsSkip) {
    //
    // Open the test support files
    //
    Status = OpenExtendedSupportFiles (WbEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Open support files - %r", Status));
    }

    if (!EFI_ERROR (Status)) {
      //
      // Invoke the test entry point
      //
      TestStatus = WbEntry->EntryPoint (
                              WbTest,
                              gFT->ConfigData->TestLevel,
                              gFT->SupportHandle
                              );
    }

    //
    // Close the test support files
    //
    Status = CloseExtendedSupportFiles (WbEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Close support files - %r", Status));
    }
  }

  //
  // Do post-operations for a test instance
  //
  Status = PostExecuteTestInstance (
             ExecuteInfo,
             TestStatus
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Post execute test instance - %r", Status));
    return Status;
  }

  //
  // Deal with the specific attributes of test case
  //
  if (!IsSkip) {
    //
    // Reset required
    //
    if ((WbEntry->CaseAttribute & EFI_TEST_CASE_RESET_REQUIRED) != 0) {
      FreeDebugServices ();

      //
      // Free 1 second to let all flush works done
      //
      tBS->Stall (1000000);
      tRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteApTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute an application or a script test instance.

--*/
{
  EFI_STATUS              Status;
  EFI_STATUS              TestStatus;
  BOOLEAN                 IsSkip;
  CHAR16                  *CmdLine;
  EFI_AP_TEST_INTERFACE   *ApTest;
  EFI_AP_TEST_ENTRY       *ApEntry;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Application test instance
  //
  ApTest  = (EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol;
  ApEntry = (EFI_AP_TEST_ENTRY *) ExecuteInfo->TestEntry;

  TestStatus = EFI_UNSUPPORTED;

  //
  // Do pre-operations for a test instance
  //
  Status = PreExecuteTestInstance (
             ExecuteInfo,
             NULL,
             &IsSkip
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre execute test instance - %r", Status));
    return Status;
  }

  if (!IsSkip) {
    //
    // Open the test support files
    //
    Status = OpenExtendedSupportFiles (ApEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Open support files - %r", Status));
    }

    if (!EFI_ERROR (Status)) {
      //
      // Invoke the test entry point
      //
      CmdLine = SctPoolPrint (
                  L"\"%s\" %s",
                  ExecuteInfo->TestFile->FileName,
                  ApEntry->Parameters
                  );
      if (CmdLine == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
      }

      if (CmdLine != NULL) {
        TestStatus = SctShellExecute (
                       &gFT->ImageHandle,
                       CmdLine,
                       FALSE,
                       NULL, NULL
                       );
      }
    }

    //
    // Close the test support files
    //
    Status = CloseExtendedSupportFiles (ApEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Close support files - %r", Status));
    }
  }

  //
  // Do post-operations for a test instance
  //
  Status = PostExecuteTestInstance (
             ExecuteInfo,
             TestStatus
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Post execute test instance - %r", Status));
    return Status;
  }

  //
  // Deal with the specific attributes of test case
  //
  if (!IsSkip) {
    //
    // Reset required
    //
    if ((ApEntry->CaseAttribute & EFI_TEST_CASE_RESET_REQUIRED) != 0) {
      FreeDebugServices ();

      //
      // Free 1 second to let all flush works done
      //
      tBS->Stall (1000000);
      tRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
InitializeTestConfigData (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL,
  OUT EFI_LIB_CONFIG_DATA         *ConfigData
  )
/*++

Routine Description:

  Initialize the test configuration data for test support libraries.

--*/
{
  EFI_STATUS                Status;
  CHAR16                    *FullMetaName;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_BB_TEST_PROTOCOL      *BbTest;
  EFI_BB_TEST_ENTRY         *BbEntry;
  EFI_WB_TEST_PROTOCOL      *WbTest;
  EFI_WB_TEST_ENTRY         *WbEntry;
  EFI_AP_TEST_INTERFACE     *ApTest;
  EFI_AP_TEST_ENTRY         *ApEntry;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (ConfigData == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  SctZeroMem (ConfigData, sizeof(EFI_LIB_CONFIG_DATA));

  //
  // Get th full meta name of log files
  //
  Status = GetFileFullMetaName (
             ExecuteInfo,
             &FullMetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get file full meta name - %r", Status));
    return Status;
  }

  //
  // Set the test configuration data
  //
  ConfigData->OutputProtocol      = gFT->TolProtocol;

  //
  // Set the recovery information
  //
  if (ExecuteInfo->State == EFI_SCT_LOG_STATE_RUNNING) {
    ConfigData->IsRecovery        = TRUE;
    ConfigData->PassCount         = ExecuteInfo->Passes;
    ConfigData->WarningCount      = ExecuteInfo->Warnings;
    ConfigData->FailCount         = ExecuteInfo->Failures;
  } else {
    ConfigData->IsRecovery        = FALSE;
    ConfigData->PassCount         = 0;
    ConfigData->WarningCount      = 0;
    ConfigData->FailCount         = 0;
  }

  //
  // Set the system log file and key file
  //
  ConfigData->SystemLogFile.EnableScreenOutput = FALSE;
  ConfigData->SystemLogFile.DevicePath         = gFT->DevicePath;
  ConfigData->SystemLogFile.FileName           =
    SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_SUMMARY_LOG);
  ConfigData->SystemLogFile.OverwriteFile      = gFT->IsFirstTimeExecute;

  ConfigData->SystemKeyFile.EnableScreenOutput = FALSE;
  ConfigData->SystemKeyFile.DevicePath         = gFT->DevicePath;
  ConfigData->SystemKeyFile.FileName           =
    SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_SUMMARY_EKL);
  ConfigData->SystemKeyFile.OverwriteFile      = gFT->IsFirstTimeExecute;

  //
  // Set the case log file and key file
  //
  ConfigData->CaseLogFile.EnableScreenOutput   = gFT->ConfigData->EnableScreenOutput;
  ConfigData->CaseLogFile.DevicePath           = gFT->DevicePath;
  ConfigData->CaseLogFile.FileName             =
    SctPoolPrint (FullMetaName, ExecuteInfo->Index, ExecuteInfo->Iteration, L"log");
  ConfigData->CaseLogFile.OverwriteFile        = (BOOLEAN) !ConfigData->IsRecovery;

  ConfigData->CaseKeyFile.EnableScreenOutput   = FALSE;
  ConfigData->CaseKeyFile.DevicePath           = gFT->DevicePath;
  ConfigData->CaseKeyFile.FileName             =
    SctPoolPrint (FullMetaName, ExecuteInfo->Index, ExecuteInfo->Iteration, L"ekl");
  ConfigData->CaseKeyFile.OverwriteFile        = (BOOLEAN) !ConfigData->IsRecovery;

  //
  // Set the platform information
  //
  ConfigData->BiosId              = gFT->ConfigData->BiosId;
  ConfigData->PlatformNumber      = (UINT32) gFT->ConfigData->PlatformNumber;
  ConfigData->ConfigurationNumber = (UINT32) gFT->ConfigData->ConfigurationNumber;
  ConfigData->ScenarioString      = gFT->ConfigData->ScenarioString;

  //
  // Set the test information
  //
  switch (ExecuteInfo->TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    BbTest  = (EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;
    BbEntry = (EFI_BB_TEST_ENTRY *) ExecuteInfo->TestEntry;

    ConfigData->TestRevision     = BbTest->TestRevision;
    ConfigData->TestName         = BbTest->Name;
    ConfigData->EntryId          = &BbEntry->EntryId;
    ConfigData->EntryName        = BbEntry->Name;
    ConfigData->EntryDescription = BbEntry->Description;
    ConfigData->SupportProtocols = BbEntry->SupportProtocols;
    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    WbTest  = (EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;
    WbEntry = (EFI_WB_TEST_ENTRY *) ExecuteInfo->TestEntry;

    ConfigData->TestRevision     = WbTest->TestRevision;
    ConfigData->TestName         = WbTest->Name;
    ConfigData->EntryId          = &WbEntry->EntryId;
    ConfigData->EntryName        = WbEntry->Name;
    ConfigData->EntryDescription = WbEntry->Description;
    ConfigData->SupportProtocols = WbEntry->SupportProtocols;
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    ApTest  = (EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol;
    ApEntry = (EFI_AP_TEST_ENTRY *) ExecuteInfo->TestEntry;

    ConfigData->TestRevision     = ApTest->TestRevision;
    ConfigData->TestName         = ApTest->Name;
    ConfigData->EntryId          = &ApEntry->EntryId;
    ConfigData->EntryName        = ApEntry->Name;
    ConfigData->EntryDescription = ApEntry->Description;
    ConfigData->SupportProtocols = ApEntry->SupportProtocols;
    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    FreeTestConfigData (ConfigData);
    return EFI_UNSUPPORTED;
  }

  ConfigData->VerboseLevel        = gFT->ConfigData->VerboseLevel;

  //
  // Set the test category and device path info
  //
  if (ExecuteInfo->Category != NULL) {
    ConfigData->TestCategory = SctStrDuplicate (ExecuteInfo->Category->Name);
  } else {
    ConfigData->TestCategory = SctStrDuplicate (L"Unknown");
  }

  if (Handle != NULL) {
    DevicePath = SctDevicePathFromHandle (Handle);
    if (DevicePath != NULL) {
      ConfigData->DevicePath = SctDevicePathToStr (DevicePath);
    } else {
      ConfigData->DevicePath = SctStrDuplicate (L"No device path");
    }
  } else {
    ConfigData->DevicePath = SctStrDuplicate (L"No device path");
  }

  //
  // Free resources
  //
  tBS->FreePool (FullMetaName);

  //
  // Check error
  //
  if ((ConfigData->SystemLogFile.FileName == NULL) ||
      (ConfigData->SystemKeyFile.FileName == NULL) ||
      (ConfigData->CaseLogFile.FileName   == NULL) ||
      (ConfigData->CaseKeyFile.FileName   == NULL) ||
      (ConfigData->TestCategory           == NULL) ||
      (ConfigData->DevicePath             == NULL)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    FreeTestConfigData (ConfigData);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeTestConfigData (
  IN EFI_LIB_CONFIG_DATA          *ConfigData
  )
/*++

Routine Description:

  Free the test configuration data.

--*/
{
  //
  // Free the items of test configuration data
  //
  if (ConfigData->SystemLogFile.FileName != NULL) {
    tBS->FreePool (ConfigData->SystemLogFile.FileName);
    ConfigData->SystemLogFile.FileName = NULL;
  }

  if (ConfigData->SystemKeyFile.FileName != NULL) {
    tBS->FreePool (ConfigData->SystemKeyFile.FileName);
    ConfigData->SystemKeyFile.FileName = NULL;
  }

  if (ConfigData->CaseLogFile.FileName != NULL) {
    tBS->FreePool (ConfigData->CaseLogFile.FileName);
    ConfigData->CaseLogFile.FileName = NULL;
  }

  if (ConfigData->CaseKeyFile.FileName != NULL) {
    tBS->FreePool (ConfigData->CaseKeyFile.FileName);
    ConfigData->CaseKeyFile.FileName = NULL;
  }

  if (ConfigData->TestCategory != NULL) {
    tBS->FreePool (ConfigData->TestCategory);
    ConfigData->TestCategory = NULL;
  }

  if (ConfigData->DevicePath != NULL) {
    tBS->FreePool (ConfigData->DevicePath);
    ConfigData->DevicePath = NULL;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
PreExecuteTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL,
  OUT BOOLEAN                     *IsSkip
  )
/*++

Routine Description:

  Do the pre-operations (start logging, set watchdog timer, etc) before the
  test execution.

--*/
{
  EFI_STATUS                Status;
  UINTN                     BufferSize;
  UINT8                     Buffer[1024];
  EFI_LIB_CONFIG_DATA       ConfigData;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (IsSkip == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize the test configuration data
  //
  Status = InitializeTestConfigData (
             ExecuteInfo,
             Handle,
             &ConfigData
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initialize test config data - %r", Status));
    return Status;
  }

  //
  // Now, we can set the first time execute flag to FALSE
  //
  gFT->IsFirstTimeExecute = FALSE;

  //
  // Set the configuration data to standard test
  //
  Status = gFT->StslInterface->SetConfig (
                                 gFT->StslInterface,
                                 &ConfigData
                                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Set standard test config - %r", Status));
    FreeTestConfigData (&ConfigData);
    return Status;
  }

  //
  // Set the configuration data to test logging
  //
  Status = gFT->TllInterface->SetConfig (
                                gFT->TllInterface,
                                &ConfigData
                                );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Set test logging config - %r", Status));
    FreeTestConfigData (&ConfigData);
    return Status;
  }

  //
  // Start the logging
  //
  Status = gFT->StslInterface->BeginLogging (gFT->StslInterface);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Start standard test - %r", Status));
    FreeTestConfigData (&ConfigData);
    return Status;
  }

  Status = gFT->TllInterface->BeginLogging (gFT->TllInterface);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Start test logging - %r", Status));
    FreeTestConfigData (&ConfigData);
    return Status;
  }

  //
  // Free resources
  //
  Status = FreeTestConfigData (&ConfigData);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test config data - %r", Status));
    return Status;
  }

  //
  // Check the test recovery data
  //
  *IsSkip = FALSE;

  if (ExecuteInfo->State != EFI_SCT_LOG_STATE_UNKNOWN) {
    Status = gFT->TrlProtocol->ReadResetRecord (
                                 gFT->TrlProtocol,
                                 &BufferSize,
                                 Buffer
                                 );
    if (EFI_ERROR (Status) || (BufferSize == 0)) {
      //
      // No recovery data, record a SYSTEM_HANG assertion
      //
      gFT->StslProtocol->RecordAssertion (
                           gFT->StslProtocol,
                           EFI_TEST_ASSERTION_FAILED,
                           gEfiSystemHangAssertionGuid,
                           L"Sysem hangs or stops abnormally.",
                           L"%a:%d",
                           __FILE__,
                           __LINE__
                           );

      //
      // Skip this test instance
      //
      *IsSkip = TRUE;
    }
  }

  //
  // Set the watchdog timer for recovery
  //
  Status = tBS->SetWatchdogTimer (
                 gFT->ConfigData->TestCaseMaxRunTime,
                 0,
                 0,
                 NULL
                 );
  if (EFI_ERROR (Status)) {
    //
    // Platform supported? It was not handled as an error
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Set watchdog timer - %r", Status));
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
PostExecuteTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_STATUS                   TestStatus
  )
/*++

Routine Description:

  Do the post-operations (reset watchdog timer, end logging, etc) after the
  test execution.

--*/
{
  EFI_STATUS  Status;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Reset the watchdog timer
  //
  Status = tBS->SetWatchdogTimer (
                 0,
                 0,
                 0,
                 NULL
                 );
  if (EFI_ERROR (Status)) {
    //
    // Platform supported? It was not handled as an error
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Set watchdog timer - %r", Status));
  }

  //
  // Stop the logging
  //
  Status = gFT->StslInterface->EndLogging (
                                 gFT->StslInterface,
                                 TestStatus
                                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Stop standard test - %r", Status));
  }

  Status = gFT->TllInterface->EndLogging (
                                gFT->TllInterface,
                                TestStatus
                                );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Stop test logging - %r", Status));
  }

  //
  // Remove recovery file
  //
  Status = RemoveRecoveryFile ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove recovery file - %r", Status));
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

UINTN
GetLibInstanceNo (
  IN SCT_LIST_ENTRY        *LinkHead
  )
{
  UINTN              Index;
  SCT_LIST_ENTRY     *Link;

  Index = 0;
  
  for (Link = LinkHead->ForwardLink; Link != LinkHead; Link = Link->ForwardLink) { 
    Index ++;
  }

  return Index; 
}
