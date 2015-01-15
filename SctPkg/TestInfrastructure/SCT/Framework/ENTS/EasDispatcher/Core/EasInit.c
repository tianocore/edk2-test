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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  EasInit.c

Abstract:

--*/

#include "SctLib.h"
#include "Eas.h"
#include EFI_TEST_PROTOCOL_DEFINITION (EntsMonitorProtocol)

EFI_NETWORK_TEST_FRAMEWORK_TABLE  *gEasFT = NULL;

EFI_STATUS
AttachNetworkTestFrameworkTable (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable,
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath,
  IN CHAR16                    *FilePath
  );

EFI_STATUS
DetachNetworkTestFrameworkTable (
  VOID
  );

EFI_STATUS
EntsAttachMonitor (
  IN CHAR16                     *MonitorName
  );

EFI_STATUS
EntsDetachMonitor (
  VOID
  );

EFI_STATUS
EntsAttachSupportFiles (
  VOID
  );

EFI_STATUS
EntsDetachSupportFiles (
  VOID
  );

EFI_STATUS
EntsAttachTestFiles (
  VOID
  );

EFI_STATUS
EntsDetachTestFiles (
  VOID
  );

EFI_STATUS
InitResources (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable,
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath,
  IN CHAR16                    *FilePath,
  IN CHAR16                    *MonitorName
  )
/*++

Routine Description:

  Initialize the system resources.

Arguments:

  ImageHandle - The image handle.
  SystemTable - The system table.
  DevicePath  - The device path of the image handle.
  FilePath    - The file path of the image handle.
  MonitorName - Monitor name for Communication layer, current we define the 
                following three types: Mnp  Ip4  Serial

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others - Operation failed.

--*/
{
  EFI_STATUS  Status;


  //
  // Attach Framework Table and the items of Framework Table
  //
  Status = AttachNetworkTestFrameworkTable (
             ImageHandle, 
             SystemTable,
             DevicePath,
             FilePath
             );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG (
      (EFI_ENTS_D_ERROR,
      L"%s: Cannot intiailize NetworkTest framework table - %r\n",
      EFI_ENTS_SHORT_NAME,
      Status)
      );
    return Status;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"AttachNetworkTestFrameworkTable success"));

  //
  // Initialize debug file
  //
  Status = EntsInitializeDebugServices (gEasFT->DevicePath, gEasFT->FilePath);
  if (EFI_ERROR (Status)) {
    goto EntsInitDebugServicesError;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"EntsInitializeDebugServices success"));

  //
  // Attach Support Files
  //
  EFI_ENTS_STATUS ((L"Begin to Attach NetworkTest support files"));
  Status = EntsAttachSupportFiles ();
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"%s: Cannot intiailize NetworkTest support files - %r", EFI_ENTS_SHORT_NAME, Status));
    goto AttachSupportFilesError;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"EntsAttachSupportFiles"));

  //
  // Attach Monitor
  //
  Status = EntsAttachMonitor (MonitorName);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Fail to Attach NetworkTest monitor - %r", Status));
    goto AttachMonitorError;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"EntsAttachMonitor"));

  //
  // Attach Test Files
  //
  EFI_ENTS_STATUS ((L"Begin to Attach NetworkTest test files"));
  Status = EntsAttachTestFiles ();
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"%s: Cannot intiailize NetworkTest test files - %r", EFI_ENTS_SHORT_NAME, Status));
    goto AttachTestFilesError;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"EntsAttachTestFiles"));

  return EFI_SUCCESS;

AttachTestFilesError:
  EntsDetachMonitor();
AttachMonitorError:
  EntsDetachSupportFiles();
AttachSupportFilesError:
  CloseDebugServices();
EntsInitDebugServicesError:
  DetachNetworkTestFrameworkTable ();
  return Status;
}

EFI_STATUS
FreeResources (
  VOID
  )
/*++

Routine Description:

  Detach all test data.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others - Operation failed.

--*/
{
  EFI_STATUS                      Status;

  Status = EntsDetachTestFiles ();
  if (EFI_ERROR(Status)) {
  	EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Detach Test Files fail - %r", Status));
	return Status;
  }

  Status = EntsDetachMonitor();
  if (EFI_ERROR(Status)) {
  	EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Detach Monitor fail - %r", Status));
	return Status;
  }

  Status = EntsDetachSupportFiles ();
  if (EFI_ERROR(Status)) {
  	EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Detach Support Files fail - %r", Status));
	return Status;
  }

  Status = DetachNetworkTestFrameworkTable ();
  if (EFI_ERROR(Status)) {
  	EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Detach Network Teset Files fail - %r", Status));
	return Status;
  }

  Status = CloseDebugServices ();
  if (EFI_ERROR(Status)) {
  	EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Close Debug Services fail - %r", Status));
	return Status;
  }
  

  return EFI_SUCCESS;
}

EFI_STATUS
AttachNetworkTestFrameworkTable (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable,
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath,
  IN CHAR16                    *FilePath
  )
/*++

Routine Description:

  Initialize Framework Table and the items of Framework Table.

Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.
  DevicePath            - The device path of the image handle.
  FilePath              - The file path of the image handle.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                Status;

  //
  // Allocate memory for Framework Table
  //
  Status = tBS->AllocatePool (
                EfiBootServicesData,
                sizeof (EFI_NETWORK_TEST_FRAMEWORK_TABLE),
                (VOID **)&gEasFT
                );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Initialize the items of Framework Table
  //
  SctZeroMem (gEasFT, sizeof (EFI_NETWORK_TEST_FRAMEWORK_TABLE));

  Status = tBS->AllocatePool (
                EfiBootServicesData,
                sizeof (EFI_MONITOR_COMMAND),
                (VOID **)&gEasFT->Cmd
                );
  if (EFI_ERROR (Status)) {
    goto AttachFail;
  }
  
  gEasFT->Signature                 = EFI_NETWORK_TEST_FRAMEWORK_TABLE_SIGNATURE;
  gEasFT->Version                   = EFI_NETWORK_TEST_FRAMEWORK_TABLE_VERSION;
  gEasFT->ImageHandle               = ImageHandle;
  gEasFT->SystemTable               = SystemTable;
  gEasFT->DevicePath                = DevicePath;
  gEasFT->FilePath                  = FilePath;

  gEasFT->Cmd->Signature            = EFI_MONITOR_COMMAND_SIGNATURE;
  gEasFT->Cmd->Version              = EFI_MONITOR_COMMAND_VERSION;
  gEasFT->Cmd->ComdName             = NULL;
  gEasFT->Cmd->ComdArg              = NULL;
  gEasFT->Cmd->ComdRuntimeInfo      = NULL;
  gEasFT->Cmd->ComdRuntimeInfoSize  = 0;
  gEasFT->Cmd->ComdOutput           = NULL;
  gEasFT->Cmd->ComdOutputSize       = 0;
  gEasFT->Cmd->ComdResult           = PASS;
  gEasFT->Cmd->TestFile             = NULL;
  gEasFT->Cmd->ComdInterface        = NULL;

  return EFI_SUCCESS;

AttachFail:
  tBS->FreePool (gEasFT);
  gEasFT = NULL;
  return Status;
}

EFI_STATUS
DetachNetworkTestFrameworkTable (
  VOID
  )
/*++

Routine Description:

  Free Framework Table and the items of Framework Table.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  if (gEasFT == NULL) {
    return EFI_SUCCESS;
  }
  
  //
  // Free Command
  //
  if (gEasFT->Cmd != NULL) {
    tBS->FreePool (gEasFT->Cmd);
    gEasFT->Cmd = NULL;
  }

  //
  // Free Framework Table
  //
  tBS->FreePool (gEasFT);
  gEasFT = NULL;

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EntsAttachSupportFiles (
  VOID
  )
/*++

Routine Description:

  Load support files.

Arguments:

  None

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;

  SctInitializeListHead (&gEasFT->SupportList);

  //
  // Create the test file path
  //
  FilePath = SctPoolPrint (L"%s\\%s", gEasFT->FilePath, EFI_NETWORK_PATH_SUPPORT);
  if (FilePath == NULL) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Pool print - %r", EFI_OUT_OF_RESOURCES));
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // Load test files
  //
  Status = EntsLoadSupportFiles (
            gEasFT->DevicePath,
            FilePath,
            TRUE  // Recursive
            );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Load support files - %r", Status));
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
EntsDetachSupportFiles (
  VOID
  )
{
  EFI_STATUS                        Status;

  //
  // Unload support files
  //
  Status = EntsUnloadSupportFiles (&gEasFT->SupportList);

  return Status;
}

EFI_STATUS
EntsAttachTestFiles (
  VOID
  )
/*++

Routine Description:

  Load test files.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;

  SctInitializeListHead (&gEasFT->TestAppList);

  //
  // Create the test file path
  //
  FilePath = SctPoolPrint (L"%s\\%s", gEasFT->FilePath, EFI_NETWORK_PATH_TEST);
  if (FilePath == NULL) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Pool print - %r", EFI_OUT_OF_RESOURCES));
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // Load test files
  //
  Status = EntsLoadTestFiles (
            gEasFT->DevicePath,
            FilePath,
            TRUE  // Recursive
            );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Load test files - %r", Status));
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
EntsDetachTestFiles (
  VOID
  )
{
  EFI_STATUS                       Status;

  //
  // Unload test files
  //
  Status = EntsUnloadTestFiles (&gEasFT->TestAppList);

  return Status;
}

EFI_STATUS
EntsAttachMonitor (
  IN CHAR16                     *MonitorName
  )
/*++

Routine Description:

  Attach ENTS Monitor.

Arguments:

  MonitorName - Monitor name string.
  EntsMonitor - A pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - The handle of EFI_ENTS_MONITOR_PROTOCOL was not found.
  Others        - Some failure happened.

--*/
{
  EFI_STATUS                    Status;
  EFI_ENTS_MONITOR_PROTOCOL     *EntsMonitorInterface;
  UINTN                         NoHandles;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         Index;

  EntsMonitorInterface = NULL;

  //
  // Locate all the handle of EFI_ENTS_MONITOR_PROTOCOL
  //
  Status = tBS->LocateHandleBuffer (
                ByProtocol,
                &gEfiEntsMonitorProtocolGuid,
                NULL,
                &NoHandles,
                &HandleBuffer
                );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Can not locate any EFI_ENTS_MONITOR_PROTOCOL handles - %r", Status));
    Status = EFI_NOT_FOUND;
    goto AttachErr;
  }

  //
  // Search the proper EFI_ENTS_MONITOR_PROTOCOL
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = tBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiEntsMonitorProtocolGuid,
                 (void **)&EntsMonitorInterface
                  );
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Can not get ENTS Monitor interface - %r", Status));
      Status = EFI_NOT_FOUND;
      goto AttachErr;
    }

    if (SctStriCmp (MonitorName, EntsMonitorInterface->MonitorName) == 0) {
      break;
    }
  }

  tBS->FreePool (HandleBuffer);

  gEasFT->Monitor = EntsMonitorInterface;
  Status          = EntsMonitorInterface->InitMonitor (EntsMonitorInterface);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Fail to InitMonitor - %r", Status));
    goto AttachErr;
  }

  return EFI_SUCCESS;

AttachErr:
  gEasFT->Monitor = NULL;
  return Status;
}

EFI_STATUS
EntsDetachMonitor (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_ENTS_MONITOR_PROTOCOL     *EntsMonitor;

  Status = EFI_SUCCESS;
  if (gEasFT->Monitor != NULL) {
    EntsMonitor = gEasFT->Monitor;
    gEasFT->Monitor = NULL;
    Status = EntsMonitor->ResetMonitor (EntsMonitor);
  }

  return Status;
}

