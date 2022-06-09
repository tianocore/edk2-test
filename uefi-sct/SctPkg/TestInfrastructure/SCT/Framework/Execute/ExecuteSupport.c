/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ExecuteSupport.c

Abstract:

  This file provides the support services for test execution.

--*/

#include "Sct.h"
#include "ReportSupport.h"

#define EFI_SCT_FILE_DEVICE_CONFIG          L"Data\\DeviceConfig.ini"
#define EFI_SCT_SECTION_DEVICE_CONFIG       L"Device Configuration"

#define EFI_SCT_MAX_BUFFER_SIZE             512


//
// Internal functions declarations
//

EFI_STATUS
ConvertFilePath (
  IN OUT CHAR16                   *FilePath
  );

EFI_STATUS
ConvertFileName (
  IN OUT CHAR16                   *FileName
  );

//
// External functions implementation
//

EFI_STATUS
InitializeExecuteInfo (
  IN EFI_SCT_TEST_CASE            *TestCase,
  OUT EFI_SCT_EXECUTE_INFO        *ExecuteInfo
  )
/*++

Routine Description:

  Initialize the execute information.

Arguments:

  TestCase      - Pointer to the test case.
  ExecuteInfo   - Pointer to the execute information.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  EFI_GUID    *CategoryGuid;

  //
  // Check parameters
  //
  if ((TestCase == NULL) || (ExecuteInfo == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize the items of execute information
  //
  ExecuteInfo->TestCase     = TestCase;

  ExecuteInfo->Category     = NULL;
  ExecuteInfo->TestFile     = NULL;

  ExecuteInfo->SkippedCase  = NULL;

  ExecuteInfo->TestProtocol = NULL;
  ExecuteInfo->TestEntry    = NULL;

  ExecuteInfo->State        = EFI_SCT_LOG_STATE_UNKNOWN;

  ExecuteInfo->Index        = 0;
  ExecuteInfo->Iteration    = 0;
  ExecuteInfo->Passes       = 0;
  ExecuteInfo->Warnings     = 0;
  ExecuteInfo->Failures     = 0;

  //
  // Search the related test file
  //
  Status = FindTestFileByCaseGuid (
             &TestCase->Guid,
             &ExecuteInfo->TestFile,
             &ExecuteInfo->TestProtocol,
             &ExecuteInfo->TestEntry
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Find test file by case GUID - %r", Status));;
    return Status;
  }

  //
  // Get the category GUID from different kinds of test files
  //
  switch (ExecuteInfo->TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    CategoryGuid = &((EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol)->CategoryGuid;
    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    CategoryGuid = &((EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol)->CategoryGuid;
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    CategoryGuid = &((EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol)->CategoryGuid;
    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    return EFI_UNSUPPORTED;
  }

  //
  // Find the related category data
  //
  Status = FindCategoryByGuid (
             CategoryGuid,
             &ExecuteInfo->Category
             );
  if (EFI_ERROR (Status)) {
    //
    // If the category data doesn't exist, use the empty setting
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Find category by GUID - %r", Status));
    ExecuteInfo->Category = NULL;;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetFileMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FilePath,
  OUT CHAR16                      **MetaName
  )
/*++

Routine Description:

  Get the file path and the meta file name. The format of meta name will be
  "Name_%s_%s_GUID.%s". (Here, "%s" stands for the real string "%s".)

  Notice: If you need to change the format of this meta name, you should also
  review the code of each caller. The caller will generate the real file name
  based on the meta name returned by this function.

Arguments:

  ExecuteInfo   - Pointer to the execute information.
  FilePath      - The path of log files.
  MetaName      - The meta name of log files.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_GUID  *CategoryGuid;
  CHAR16    CategoryGuidStr[EFI_SCT_GUID_LEN];
  EFI_GUID  *EntryGuid;
  CHAR16    EntryGuidStr[EFI_SCT_GUID_LEN];
  CHAR16    *EntryName;
  UINTN     Index;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (FilePath == NULL) || (MetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the GUID and name of the test entry
  //
  switch (ExecuteInfo->TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    CategoryGuid = &((EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol)->CategoryGuid;
    SctGuidToStr (CategoryGuid, CategoryGuidStr);

    EntryGuid = &((EFI_BB_TEST_ENTRY *) ExecuteInfo->TestEntry)->EntryId;
    SctGuidToStr (EntryGuid, EntryGuidStr);

    EntryName = ((EFI_BB_TEST_ENTRY *) ExecuteInfo->TestEntry)->Name;
    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    CategoryGuid = &((EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol)->CategoryGuid;
    SctGuidToStr (CategoryGuid, CategoryGuidStr);

    EntryGuid = &((EFI_WB_TEST_ENTRY *) ExecuteInfo->TestEntry)->EntryId;
    SctGuidToStr (EntryGuid, EntryGuidStr);

    EntryName = ((EFI_WB_TEST_ENTRY *) ExecuteInfo->TestEntry)->Name;
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    CategoryGuid = &((EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol)->CategoryGuid;
    SctGuidToStr (CategoryGuid, CategoryGuidStr);

    EntryGuid = &((EFI_AP_TEST_ENTRY *) ExecuteInfo->TestEntry)->EntryId;
    SctGuidToStr (EntryGuid, EntryGuidStr);

    EntryName = ((EFI_AP_TEST_ENTRY *) ExecuteInfo->TestEntry)->Name;
    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    return EFI_UNSUPPORTED;
  }

  //
  // Create the file path
  //
  if (ExecuteInfo->Category == NULL) {
    *FilePath = SctPoolPrint (
                  L"%s\\%s\\Unknown\\%s",
                  gFT->FilePath,
                  EFI_SCT_PATH_LOG,
                  CategoryGuidStr
                  );
  } else {
    Index = 0;
    if (((ExecuteInfo->Index + 1) * (ExecuteInfo->Iteration + 1)) >= MaxInstanceNumInSingleDirectory) {
      Index = ((ExecuteInfo->Index) * (ExecuteInfo->Iteration + 1)) / MaxInstanceNumInSingleDirectory;
    }

    *FilePath = SctPoolPrint(
                  L"%s\\%s\\%s%d",
                  gFT->FilePath,
                  EFI_SCT_PATH_LOG,
                  ExecuteInfo->Category->Name,
                  Index
                  );

  }

  if (*FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  ConvertFilePath (*FilePath);

  //
  // Create the meta file name
  //
  *MetaName = SctPoolPrint (
                L"%s_%s_%s_%s.%s",
                EntryName,
                L"%s",              // Index
                L"%s",              // Iteration
                EntryGuidStr,
                L"%s"               // Extension
                );
  if (*MetaName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    tBS->FreePool (*FilePath);
    return EFI_OUT_OF_RESOURCES;
  }

  ConvertFileName (*MetaName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetFileFullMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FullMetaName
  )
/*++

Routine Description:

  Get the full meta name of log files. The format of full meta name will be
  "Path\Name_%d_%d_GUID.%s". (Here, "%d" stands for the real string "%d".)

Arguments:

  ExecuteInfo   - Pointer to the execute information.
  FullMetaName  - Full meta name of log files.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;
  CHAR16      *MetaName;
  CHAR16      *TempName;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (FullMetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the file meta name
  //
  Status = GetFileMetaName (
             ExecuteInfo,
             &FilePath,
             &MetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get file meta name - %r", Status));
    return Status;
  }

  //
  // Convert the meta file name to number file name
  //
  TempName = SctPoolPrint (MetaName, L"%d", L"%d", L"%s");
  if (TempName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    tBS->FreePool (FilePath);
    tBS->FreePool (MetaName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create the full meta name
  //
  *FullMetaName = SctPoolPrint (L"%s\\%s", FilePath, TempName);
  if (*FullMetaName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    tBS->FreePool (FilePath);
    tBS->FreePool (MetaName);
    tBS->FreePool (TempName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Free resources
  //
  tBS->FreePool (FilePath);
  tBS->FreePool (MetaName);
  tBS->FreePool (TempName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetKeyFileMetaName(
IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
OUT CHAR16                      **FilePath,
OUT CHAR16                      **MetaName
)
{
  EFI_STATUS  Status;
  CHAR16      *TempName;

  if ((ExecuteInfo == NULL) || (FilePath == NULL) || (MetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the file meta name
  //
  Status = GetFileMetaName(
             ExecuteInfo,
             FilePath,
             &TempName
             );
  if (EFI_ERROR(Status)) {
    EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"Get file meta name - %r", Status));
    return Status;
  }

  //
  // Convert the meta file name to number file name
  //
  *MetaName = SctPoolPrint(TempName, L"%d", L"%d", L"ekl");
  if (*MetaName == NULL) {
    EFI_SCT_DEBUG((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    tBS->FreePool(TempName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Free resources
  //
  tBS->FreePool(TempName);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
GetKeyFileFullMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FullMetaName
  )
/*++

Routine Description:

  Get the full meta name of key files. The format of full meta name will be
  "Path\Name_%d_%d_GUID.ekl". (Here, "%d" stands for the real string "%d".)

Arguments:

  ExecuteInfo   - Pointer to the execute information.
  FullMetaName  - Full meta name of key files.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;
  CHAR16      *MetaName;
  CHAR16      *TempName;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (FullMetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the file meta name
  //
  Status = GetFileMetaName (
             ExecuteInfo,
             &FilePath,
             &MetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get file meta name - %r", Status));
    return Status;
  }

  //
  // Convert the meta file name to number file name
  //
  TempName = SctPoolPrint (MetaName, L"%d", L"%d", L"ekl");
  if (TempName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    tBS->FreePool (FilePath);
    tBS->FreePool (MetaName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create the full meta name
  //
  *FullMetaName = SctPoolPrint (L"%s\\%s", FilePath, TempName);
  if (*FullMetaName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    tBS->FreePool (FilePath);
    tBS->FreePool (MetaName);
    tBS->FreePool (TempName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Free resources
  //
  tBS->FreePool (FilePath);
  tBS->FreePool (MetaName);
  tBS->FreePool (TempName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
ConvertFilePath (
  IN OUT CHAR16                   *FilePath
  )
/*++

Routine Description:

  Convert the illegal characters (* ? < > , ; : " = |) of file path to '_'.

--*/
{
  UINTN       Index;
  UINTN       SubIndex;
  CHAR16      *IllegalChar = L"*?<>,;:\"=|";

  //
  // Convert the invalid characters to '_'
  //
  for (Index = 0; FilePath[Index] != L'\0'; Index ++) {
    for (SubIndex = 0; IllegalChar[SubIndex] != L'\0'; SubIndex ++) {
      if (FilePath[Index] == IllegalChar[SubIndex]) {
        FilePath[Index] = L'_';
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
ConvertFileName (
  IN OUT CHAR16                   *FileName
  )
/*++

Routine Description:

  Convert the illegal characters (/ * ? < > , ; : " \ = |) of file name to '_'.

--*/
{
  UINTN       Index;
  UINTN       SubIndex;
  CHAR16      *IllegalChar = L"/*?<>,;:\"\\=|";

  //
  // Convert the invalid characters to '_'
  //
  for (Index = 0; FileName[Index] != L'\0'; Index ++) {
    for (SubIndex = 0; IllegalChar[SubIndex] != L'\0'; SubIndex ++) {
      if (FileName[Index] == IllegalChar[SubIndex]) {
        FileName[Index] = L'_';
        break;
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

STATIC
BOOLEAN
InsertHandle (
  IN OUT UINTN          *NoHandles,
  IN OUT EFI_HANDLE     *HandleBuffer,
  IN EFI_HANDLE         Handle
  )
{
  UINTN   Index;

  for (Index = 0; Index < *NoHandles; Index++) {
    if (HandleBuffer[Index] == Handle) {
      return FALSE;
    }
  }

  HandleBuffer[*NoHandles] = Handle;
  (*NoHandles) ++;

  return TRUE;
}

STATIC
BOOLEAN
MatchHandleInterface (
  IN UINTN              NoHandles,
  IN EFI_HANDLE         *HandleBuffer,
  IN EFI_GUID           *ClientGuid,
  IN VOID               *ClientInterface
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  VOID        *Interface;

  for (Index = 0; Index < NoHandles; Index++) {
    Status = tBS->HandleProtocol (
                     HandleBuffer[Index],
                     ClientGuid,
                     (VOID **) &Interface
                     );
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (Interface == ClientInterface) {
      return TRUE;
    }
  }

  return FALSE;
}

STATIC
EFI_STATUS
DeviceConfigGetOrderNum (
  IN EFI_INI_FILE_HANDLE    IniFile,
  OUT UINT32                *OrderNum
  )
{
  return IniFile->GetOrderNum (
                    IniFile,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    OrderNum
                    );
}

STATIC
EFI_STATUS
DeviceConfigGetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  OUT CHAR16                *Buffer
  )
{
  UINT32  BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}

STATIC
EFI_STATUS
DeviceConfigSetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  IN CHAR16                 *Buffer
  )
{
  return IniFile->SetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    Key,
                    Buffer
                    );
}

STATIC
VOID
InsertChildHandles (
  IN OUT UINTN          *NoHandles,
  IN OUT EFI_HANDLE     *HandleBuffer,
  IN EFI_HANDLE         Handle
  )
{
  EFI_STATUS                            Status;
  BOOLEAN                               Result;
  UINTN                                 Index1;
  UINTN                                 Index2;
  UINTN                                 ProtocolBufferCount;
  EFI_GUID                              **ProtocolBuffer;
  UINTN                                 EntryCount;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY   *EntryBuffer;

  //
  // Insert the handle itself
  //
  Result = InsertHandle (
             NoHandles,
             HandleBuffer,
             Handle
             );
  if (!Result) {
    //
    // Return if this handle already exists (stands for it has been processed.)
    //
    return;
  }

  //
  // Locate all protocols on the handle
  //
  Status = tBS->ProtocolsPerHandle (
                   Handle,
                   &ProtocolBuffer,
                   &ProtocolBufferCount
                   );
  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // Get the open protocol information for each protocol
  //
  for (Index1 = 0; Index1 < ProtocolBufferCount; Index1++) {
    //
    // Get the open protocol information
    //
    Status = tBS->OpenProtocolInformation (
                     Handle,
                     ProtocolBuffer[Index1],
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EFI_ERROR (Status)) {
      continue;
    }

    for (Index2 = 0; Index2 < EntryCount; Index2++) {
      //
      // Deal with the protocol opened by driver or by child controller
      //
      if ((EntryBuffer[Index2].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER          ) ||
          (EntryBuffer[Index2].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)) {
        //
        // Insert the agent handle
        //
        InsertHandle (
          NoHandles,
          HandleBuffer,
          EntryBuffer[Index2].AgentHandle
          );

        //
        // Insert the controller handle
        //
        InsertChildHandles (
          NoHandles,
          HandleBuffer,
          EntryBuffer[Index2].ControllerHandle
          );
      }
    }

    tBS->FreePool (EntryBuffer);
  }

  //
  // Free resources
  //
  tBS->FreePool (ProtocolBuffer);
}

STATIC
EFI_STATUS
GatherConfigHandles (
  IN EFI_HANDLE         SupportHandle,
  OUT UINTN             *NoConfigHandles,
  OUT EFI_HANDLE        **ConfigHandleBuffer
  )
{
  EFI_STATUS                          Status;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  CHAR16                              *FilePath;
  CHAR16                              *ConfigFilePath;
  EFI_INI_FILE_HANDLE                 IniFile;
  UINT32                              Order;
  UINT32                              OrderNum;
  CHAR16                              Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  UINTN                               Index;
  UINTN                               NoHandles;
  EFI_HANDLE                          *HandleBuffer;
  CHAR16                              *DevicePathStr;

  //
  // Locate test profile library protocol
  //
  Status = tBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **)&ProfileLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &DevicePath,
                         &FilePath
                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ConfigFilePath = SctPoolPrint (L"%s\\%s", FilePath, EFI_SCT_FILE_DEVICE_CONFIG);
  if (ConfigFilePath == NULL) {
    tBS->FreePool (DevicePath);
    tBS->FreePool (FilePath);
    return EFI_OUT_OF_RESOURCES;
  }

  tBS->FreePool (FilePath);

  //
  // Open the device configuration file
  //
  Status = ProfileLib->EfiIniOpen (
                         ProfileLib,
                         DevicePath,
                         ConfigFilePath,
                         &IniFile
                         );
  if (EFI_ERROR (Status)) {
    tBS->FreePool (DevicePath);
    tBS->FreePool (ConfigFilePath);
    return Status;
  }

  tBS->FreePool (DevicePath);
  tBS->FreePool (ConfigFilePath);

  //
  // Get the number of device configuration data
  //
  Status = DeviceConfigGetOrderNum (
             IniFile,
             &OrderNum
             );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    return Status;
  }

  //
  // Get all handles
  //
  Status = tBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    return Status;
  }

  //
  // Initialize the output variables
  //
  *NoConfigHandles = 0;

  Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_HANDLE) * NoHandles,
                   (VOID **)ConfigHandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    tBS->FreePool (HandleBuffer);
    return Status;
  }

  //
  // Scan each device configuration data
  //
  for (Order = 0; Order < OrderNum; Order++) {
    //
    // Here, only need to find the matched device path in the system
    //
    Status = DeviceConfigGetString (
               IniFile,
               Order,
               L"DevicePath",
               Buffer
               );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Search the matched device path in the system
    //
    for (Index = 0; Index < NoHandles; Index++) {
      Status = tBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gEfiDevicePathProtocolGuid,
                       (VOID **)&DevicePath
                       );
      if (EFI_ERROR (Status)) {
        continue;
      }

      DevicePathStr = SctDevicePathToStr (DevicePath);

      if (SctStrCmp (Buffer, DevicePathStr) == 0) {
        tBS->FreePool (DevicePathStr);
        break;
      }

      tBS->FreePool (DevicePathStr);
    }

    //
    // Found it?
    //
    if (Index < NoHandles) {
      InsertChildHandles (
        NoConfigHandles,
        *ConfigHandleBuffer,
        HandleBuffer[Index]
        );
    }
  }

  //
  // Free resources
  //
  tBS->FreePool (HandleBuffer);

  //
  // Close the device configuration file
  //
  ProfileLib->EfiIniClose (ProfileLib, IniFile);

  //
  // Done
  //
  return EFI_SUCCESS;
}

BOOLEAN
EFIAPI
IhvInterfaceFilter (
  IN VOID                       *ClientInterface,
  IN EFI_HANDLE                 SupportHandle,
  IN EFI_GUID                   *ProtocolGuid
  )
{
  EFI_STATUS            Status;
  BOOLEAN               Result;
  UINTN                 NoConfigHandles;
  EFI_HANDLE            *ConfigHandleBuffer;

  //
  // Gather all related handles from device configuration file
  //
  Status = GatherConfigHandles (
             SupportHandle,
             &NoConfigHandles,
             &ConfigHandleBuffer
             );
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  //
  // Find the matched handle with interface
  //
  Result = MatchHandleInterface (
             NoConfigHandles,
             ConfigHandleBuffer,
             ProtocolGuid,
             ClientInterface
             );

  //
  // Free sources
  //
  tBS->FreePool (ConfigHandleBuffer);

  //
  // Done
  //
  return Result;
}

