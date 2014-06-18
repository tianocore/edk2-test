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

  Report.c

Abstract:

  Description

--*/

#include "Sct.h"
#include "ReportSupport.h"

//
// External functions implemenation
//

EFI_STATUS
GetInstanceAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *MetaName,
  OUT EFI_SCT_LOG_STATE           *FileState,
  OUT UINT32                      *Index,
  OUT UINT32                      *Iteration,
  OUT UINT32                      *PassNumber,
  OUT UINT32                      *WarnNumber,
  OUT UINT32                      *FailNumber
  )
/*++

Routine Description:

  Get the assertion number of a instance.

Arguments:

  DevicePath    - Device path of the key files.
  MetaName      - Meta name of the key files.
  FileState     - The log state.
  Index         - The index of the instance.
  Interation    - The index of the iteration.
  PassNumber    - The number of passed assertions.
  WarnNumber    - The number of warning assertions.
  FailNumber    - The number of failed assertions.

Returns:

  EFI_SUCCESS   - Get instance assertion number successfully.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;
  UINT32      InstanceIndex;
  UINT32      IterationIndex;
  UINTN       BufferSize;
  CHAR16      *Buffer;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (MetaName   == NULL) ||
      (FileState  == NULL) || (Index      == NULL) ||
      (Iteration  == NULL) || (PassNumber == NULL) ||
      (WarnNumber == NULL) || (FailNumber == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  *FileState  = EFI_SCT_LOG_STATE_UNKNOWN;
  *Index      = 0;
  *Iteration  = 0;
  *PassNumber = 0;
  *WarnNumber = 0;
  *FailNumber = 0;

  InstanceIndex  = 0;
  IterationIndex = 0;

  //
  // Found the maximum index of instance and iteration
  //
  for (InstanceIndex = 0; TRUE; InstanceIndex ++) {
    for (IterationIndex = 0; TRUE; IterationIndex ++) {
      FileName = SctPoolPrint (MetaName, InstanceIndex, IterationIndex);
      if (FileName == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
        return EFI_OUT_OF_RESOURCES;
      }

      if (!FileExist (DevicePath, FileName)) {
        //
        // File does not exist
        //
        if (IterationIndex != 0) {
          *Index     = InstanceIndex;
          *Iteration = IterationIndex - 1;
        }

        tBS->FreePool (FileName);
        break;
      }

      tBS->FreePool (FileName);
    }

    if (IterationIndex == 0) {
      break;
    }
  }

  //
  // No instance file is found
  //
  if ((InstanceIndex == 0) && (IterationIndex == 0)) {
    *FileState = EFI_SCT_LOG_STATE_EMPTY;
    *Index     = 0;
    *Iteration = 0;
    return EFI_SUCCESS;
  }

  //
  // The maximum instance index is found
  //
  FileName = SctPoolPrint (MetaName, *Index, *Iteration);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Read the file to a buffer
  //
  Status = ReadFileToBuffer (
             DevicePath,
             FileName,
             &BufferSize,
             (VOID **)&Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Read file to buffer - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }

  tBS->FreePool (FileName);

  //
  // Load the buffer to the GUID assertion table with duplicate
  //
  Status = LoadGuidAssertion (Buffer, TRUE, FileState);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load GUID assertion - %r", Status));
    tBS->FreePool (Buffer);
    return Status;
  }

  tBS->FreePool (Buffer);

  //
  // Get the assertion number (free the GUID assertion table)
  //
  Status = GetAssertionNumber (PassNumber, WarnNumber, FailNumber);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get assertion number - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetInterfaceAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *MetaName,
  OUT UINT32                      *PassNumber,
  OUT UINT32                      *WarnNumber,
  OUT UINT32                      *FailNumber
  )
/*++

Routine Description:

  Get the assertion number of an interface.

Arguments:

  DevicePath    - Device path of the key files.
  MetaName      - Meta name of the key files.
  PassNumber    - The number of passed assertions.
  WarnNumber    - The number of warning assertions.
  FailNumber    - The number of failed assertions.

Returns:

  EFI_SUCCESS   - Get instance assertion number successfully.

--*/
{
  EFI_STATUS          Status;
  CHAR16              *FileName;
  UINT32              InstanceIndex;
  UINT32              IterationIndex;
  UINTN               BufferSize;
  CHAR16              *Buffer;
  EFI_SCT_LOG_STATE   FileState;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (MetaName   == NULL) ||
      (PassNumber == NULL) || (WarnNumber == NULL) ||
      (FailNumber == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  *PassNumber = 0;
  *WarnNumber = 0;
  *FailNumber = 0;

  //
  // For each instance file
  //
  for (InstanceIndex = 0; TRUE; InstanceIndex ++) {
    for (IterationIndex = 0; TRUE; IterationIndex ++) {
      FileName = SctPoolPrint (MetaName, InstanceIndex, IterationIndex);
      if (FileName == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
        return EFI_OUT_OF_RESOURCES;
      }

      if (!FileExist (DevicePath, FileName)) {
        //
        // File does not exist
        //
        tBS->FreePool (FileName);
        break;
      }

      //
      // Read the file to a buffer
      //
      Status = ReadFileToBuffer (
                 DevicePath,
                 FileName,
                 &BufferSize,
                 (VOID **)&Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Read file to buffer - %r", Status));
        tBS->FreePool (FileName);
        return Status;
      }

      tBS->FreePool (FileName);

      //
      // Load the buffer to the GUID assertion table without duplicate
      //
      Status = LoadGuidAssertion (Buffer, FALSE, &FileState);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load GUID assertion - %r", Status));
        tBS->FreePool (Buffer);
        return Status;
      }

      tBS->FreePool (Buffer);

      //
      // Get the assertion number (free the GUID assertion table)
      //
      Status = GetAssertionNumber (PassNumber, WarnNumber, FailNumber);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get assertion number - %r", Status));
        return Status;
      }
    }

    if (IterationIndex == 0) {
      break;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetProtocolAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  OUT UINT32                      *PassNumber,
  OUT UINT32                      *WarnNumber,
  OUT UINT32                      *FailNumber
  )
/*++

Routine Description:

  Get the assertion number of a protocol or service.

Arguments:

  DevicePath    - Device path of the key files.
  FilePath      - Path of the key files.
  PassNumber    - The number of passed assertions.
  WarnNumber    - The number of warning assertions.
  FailNumber    - The number of failed assertions.

Returns:

  EFI_SUCCESS   - Get instance assertion number successfully.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   LogDir;
  UINTN                             FileInfoSize;
  EFI_FILE_INFO                     *FileInfo;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath;
  UINTN                             BufferSize;
  CHAR16                            *Buffer;
  CHAR16                            *FileName;
  CHAR16                            *LogName;
  CHAR16                            *TempName;
  CHAR16                            *CaseIndexStr;
  CHAR16                            *CaseIterationStr;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FilePath   == NULL) ||
      (PassNumber == NULL) || (WarnNumber == NULL) ||
      (FailNumber == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Locate the device handle
  //
  RemainingDevicePath = DevicePath;
  Status = tBS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &RemainingDevicePath,
                 &DeviceHandle
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Locate device path - %r", Status));
    return Status;
  }

  //
  // Locate the simple file system
  //
  Status = tBS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 (VOID **)&Vol
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Handle protocol - %r", Status));
    return Status;
  }

  //
  // Open the root directory
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open volume - %r", Status));
    return Status;
  }

  //
  // Open the log directory
  //
  Status = RootDir->Open (
                      RootDir,
                      &LogDir,
                      FilePath,
                      EFI_FILE_MODE_READ,
                      EFI_FILE_DIRECTORY
                      );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open directory - %r", Status));
    RootDir->Close (RootDir);
    return Status;
  }

  RootDir->Close (RootDir);

  //
  // Allocate memory for the entries in the directory
  //
  FileInfoSize = sizeof(EFI_FILE_INFO) + 1024;

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 FileInfoSize,
                 (VOID **)&FileInfo
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    LogDir->Close (LogDir);
    return Status;
  }

  //
  // Walk through each file in the directory
  //
  while (TRUE) {
    //
    // Read a file entry
    //
    FileInfoSize = sizeof(EFI_FILE_INFO) + 1024;

    Status = LogDir->Read (
                       LogDir,
                       &FileInfoSize,
                       FileInfo
                       );
    if (EFI_ERROR (Status) || (FileInfoSize == 0)) {
      break;
    }

    if ((FileInfo->Attribute & EFI_FILE_DIRECTORY) == 0) {
      //
      // This is a file
      //

      //
      // Only deal with the EFI key file
      //
      if (!SctStrEndWith (FileInfo->FileName, L".ekl")) {
        continue;
      }

      //
      // Read the file to a buffer
      //
      FileName = SctPoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
      if (FileName == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
        return EFI_OUT_OF_RESOURCES;
      }

      Status = ReadFileToBuffer (
                 DevicePath,
                 FileName,
                 &BufferSize,
                 (VOID **)&Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Read file to buffer - %r", Status));
        tBS->FreePool (FileName);
        continue;
      }

      tBS->FreePool (FileName);

      //
      // Get the index and iteration from the file name
      //
      TempName = SctStrDuplicate (FileInfo->FileName);

      //
      // The following function didn't allocate memory for CaseIndexStr and
      // CaseIterationStr. So DON'T free the TempName before these two strings
      // are still used.
      //
      Status = GetIndexFromFileName (
                 TempName,
                 &CaseIndexStr,
                 &CaseIterationStr
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Get index from file name - %r", Status));
        tBS->FreePool (TempName);
        continue;
      }

      //
      // Load the buffer to the report information structure
      //
      LogName = SctStrEndReplace (FileInfo->FileName, L"log");

      Status = LoadReportInfor (
                 CaseIndexStr,
                 CaseIterationStr,
                 Buffer,
                 LogName
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load report infor - %r", Status));
        tBS->FreePool (TempName);
        tBS->FreePool (LogName);
        tBS->FreePool (Buffer);
        continue;
      }

      tBS->FreePool (TempName);
      tBS->FreePool (LogName);
      tBS->FreePool (Buffer);

      //
      // Get the assertion number (free the GUID assertion table)
      //
      Status = GetAssertionNumber (PassNumber, WarnNumber, FailNumber);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Get assertion number - %r", Status));
        continue;
      }

    } else {
      //
      // This is a directory
      //

      //
      // Skip the '.' and '..' dir
      //
      if ((SctStrCmp (FileInfo->FileName, L".")  == 0) ||
          (SctStrCmp (FileInfo->FileName, L"..") == 0)) {
        continue;
      }

      //
      // Get the report information from the sub directories
      //
      FileName = SctPoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
      if (FileName == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
        return EFI_OUT_OF_RESOURCES;
      }

      Status = GetProtocolAssertion (
                 DevicePath,
                 FileName,
                 PassNumber,
                 WarnNumber,
                 FailNumber
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Get protocol assertion - %r", Status));
        tBS->FreePool (FileName);
        continue;
      }

      tBS->FreePool (FileName);
    }
  }

  //
  // Free resources
  //
  tBS->FreePool (FileInfo);
  LogDir->Close (LogDir);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GenerateReport (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *LogFilePath,
  IN CHAR16                       *ReportFileName
  )
/*++

Routine Description:

  Generate test report.

Arguments:

  DevicePath        - Device path of the report file.
  LogFilePath       - Path of the key files.
  ReportFileName    - Name of the report file.

  EFI_SUCCESS       - Generate the test report successfully.

--*/
{
  EFI_STATUS        Status;
  UINT32            PassNumber;
  UINT32            WarnNumber;
  UINT32            FailNumber;
  CHAR16            *FileName;
  CHAR16            *Buffer;
  UINTN             AsciiBufferSize;
  CHAR8             *AsciiBuffer;
  UINTN             ConfigBufferSize;
  CHAR8             *ConfigBuffer;
  EFI_FILE_HANDLE   Handle;

  //
  // Check parameters
  //
  if ((DevicePath    == NULL) || (LogFilePath == NULL) || (ReportFileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  PassNumber = 0;
  WarnNumber = 0;
  FailNumber = 0;

  //
  // Get the configuration data. Start this operation at first since the next
  //  operations will take more time. We could stop the entire process if we
  //  meet any problem in configuration collection.
  //
  Status = SctReportConfig (
             &ConfigBufferSize,
             (VOID **)&ConfigBuffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctReportConfig: %r", Status));
    return Status;
  }

  //
  // Load the GUID database
  //
  FileName = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_GUID_DATABASE);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    tBS->FreePool (ConfigBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = LoadGuidDatabase (gFT->DevicePath, FileName);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load GUID database - %r", Status));
    tBS->FreePool (ConfigBuffer);
    tBS->FreePool (FileName);
    return Status;
  }

  tBS->FreePool (FileName);

  //
  // Load the assertion information from the log directory
  //
  Status = GetProtocolAssertion (
             DevicePath,
             LogFilePath,
             &PassNumber,
             &WarnNumber,
             &FailNumber
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get protocol assertion - %r", Status));
    tBS->FreePool (ConfigBuffer);
    UnloadGuidDatabase ();
    UnloadReportInfor ();
    return Status;
  }

  //
  // Get the report information to a buffer
  //
  Status = GetReportInfor (&Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get report infor - %r", Status));
    tBS->FreePool (ConfigBuffer);
    UnloadGuidDatabase ();
    UnloadReportInfor ();
    return Status;
  }

  UnloadGuidDatabase ();
  UnloadReportInfor ();

  //
  // Convert the buffer to ASCII buffer
  //
  AsciiBufferSize = SctStrLen (Buffer) + 1;

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 AsciiBufferSize,
                 (VOID **)&AsciiBuffer
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    tBS->FreePool (ConfigBuffer);
    tBS->FreePool (Buffer);
    return Status;
  }

  Status = SctUnicodeToAscii (AsciiBuffer, Buffer, SctStrLen (Buffer));
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Convert Unicode to ASCII - %r", Status));
    tBS->FreePool (ConfigBuffer);
    tBS->FreePool (Buffer);
    tBS->FreePool (AsciiBuffer);
    return Status;
  }

  tBS->FreePool (Buffer);

  //
  // Create the report file
  //
  Status = SctCreateFileFromDevicePath (
             DevicePath,
             ReportFileName,
             &Handle
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create report file - %r", Status));
    tBS->FreePool (ConfigBuffer);
    tBS->FreePool (AsciiBuffer);
    return Status;
  }

  //
  // Write the ASCII buffer to the report file (remove the null-terminator)
  //
  AsciiBufferSize --;

  Status = Handle->Write (
                     Handle,
                     &AsciiBufferSize,
                     AsciiBuffer
                     );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Write report file - %r", Status));
    tBS->FreePool (ConfigBuffer);
    tBS->FreePool (AsciiBuffer);
    Handle->Close (Handle);
    return Status;
  }

  //
  // Write the config buffer to the report file
  //
  Status = Handle->Write (
                     Handle,
                     &ConfigBufferSize,
                     ConfigBuffer
                     );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Write report file - %r", Status));
    tBS->FreePool (ConfigBuffer);
    tBS->FreePool (AsciiBuffer);
    Handle->Close (Handle);
    return Status;
  }

  tBS->FreePool (ConfigBuffer);
  tBS->FreePool (AsciiBuffer);

  //
  // Close the report file
  //
  Handle->Close (Handle);

  //
  // Done
  //
  return EFI_SUCCESS;
}
