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

  SctMisc.c

Abstract:

  This file provides all miscellaneous services for SCT.

--*/

#include "Sct.h"

//
// Internal functions declaration
//

UINTN
SctXtoi (
  CHAR16                          *Str
  );

UINTN
SctHexStrnToInt (
  IN CHAR16                       *String,
  IN UINTN                        Length
  );

EFI_STATUS
SctStrTokens (
  IN CHAR16                       *String,
  OUT UINTN                       *NumberOfTokens,
  OUT CHAR16                      ***Tokens
  );


//
// External functions implementation
//

EFI_STATUS
ExpandFileName (
  IN CHAR16                       *Name,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **FileName
  )
/*++

Routine Description:

  Expand a file name to the device path and full file name.

--*/
{
  EFI_STATUS                Status;
  CHAR16                    *TempStr;
  EFI_LIST_ENTRY            FileList;
  SHELL_FILE_ARG            *Arg;
  EFI_DEVICE_PATH_PROTOCOL  *DeviceNode;

  //
  // Initialize
  //
  *DevicePath = NULL;
  *FileName   = NULL;
  InitializeListHead (&FileList);

  //
  // Expand the input file name
  //
  Status = ShellFileMetaArg (Name, &FileList);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Empty file list is not acceptable
  //
  if (IsListEmpty (&FileList)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Multiple items file list is not acceptable
  //
  if (FileList.Flink->Flink != &FileList) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Last status doesn't mean everything is ok, so do more check at here
  //
  Arg = CR (FileList.Flink, SHELL_FILE_ARG, Link, SHELL_FILE_ARG_SIGNATURE);

  if (EFI_ERROR (Arg->Status) && (Arg->Status != EFI_NOT_FOUND)) {
    ShellFreeFileList (&FileList);
    return EFI_LOAD_ERROR;
  }

  //
  // Duplicate the device path and remove the file path from that
  //
  if (Arg->ParentDevicePath == NULL) {
    ShellFreeFileList (&FileList);
    return EFI_INVALID_PARAMETER;
  }

  *DevicePath = DuplicateDevicePath (Arg->ParentDevicePath);
  if (*DevicePath == NULL) {
    ShellFreeFileList (&FileList);
    return EFI_OUT_OF_RESOURCES;
  }

  DeviceNode = *DevicePath;
  while (!IsDevicePathEnd (DeviceNode)) {
    if ((DevicePathType (DeviceNode)    == MEDIA_DEVICE_PATH) &&
        (DevicePathSubType (DeviceNode) == MEDIA_FILEPATH_DP)) {
      SetDevicePathEndNode (DeviceNode);
      break;
    }
    DeviceNode = NextDevicePathNode (DeviceNode);
  }

  //
  // Duplicate the full file name and remove the file system name from that
  //
  if (Arg->FullName == NULL) {
    FreePool (*DevicePath);
    ShellFreeFileList (&FileList);
    return EFI_INVALID_PARAMETER;
  }

  TempStr = Arg->FullName;
  while ((*TempStr != L'\0') && (*TempStr != L':')) {
    TempStr ++;
  }

  *FileName = StrDuplicate (TempStr + 1);
  if (*FileName == NULL) {
    FreePool (*DevicePath);
    ShellFreeFileList (&FileList);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Free resources
  //
  ShellFreeFileList (&FileList);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExpandFilePath (
  IN CHAR16                       *Name,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **FilePath
  )
/*++

Routine Description:

  Expand a file name to the device path and full file path.

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  CHAR16      *FileName;

  //
  // Expand to the device path and full name
  //
  Status = ExpandFileName (
             Name,
             DevicePath,
             &FileName
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Remove the file name from full name
  //
  for (Index = 0; Index < StrLen (FileName); Index++) {
    if (FileName[StrLen (FileName) - Index - 1] == L'\\') {
      FileName[StrLen (FileName) - Index - 1] = L'\0';
      break;
    }
  }

  *FilePath = FileName;

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetMaxWatchdogTimer (
  OUT UINTN                       *MaxWatchdogTimer
  )
/*++

Routine Description:

  Get the maximum value to watchdog timer. Some platforms may not support a
  watchdog timer in long time.

  Notice: Here our target is to get a value, but not an accurate value.

--*/
{
  EFI_STATUS  Status;
  UINTN       Min;
  UINTN       Max;
  UINTN       Current;

  Min     = 0;
  Max     = 0x7FFFFFFF;
  Current = (Min + Max) / 2;

  while (Min != Current) {
    Status = BS->SetWatchdogTimer (
                   Current,
                   0,
                   0,
                   NULL
                   );
    if (EFI_ERROR (Status)) {
      Max = Current;
    } else {
      Min = Current;
    }

    Current = (Min + Max) / 2;
  }

  BS->SetWatchdogTimer (0, 0, 0, NULL);

  *MaxWatchdogTimer = Current;
  return EFI_SUCCESS;
}


INTN
SctDevicePathCompare (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath1,
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath2
  )
/*++

Routine Description:

  Compare two device pathes.

--*/
{
  UINTN   DevPathSize1;
  UINTN   DevPathSize2;

  DevPathSize1 = DevicePathSize (DevicePath1);
  DevPathSize2 = DevicePathSize (DevicePath2);

  if (DevPathSize1 > DevPathSize2) {
    return 1;
  } else if (DevPathSize1 < DevPathSize2) {
    return -1;
  } else {
    return CompareMem (DevicePath1, DevicePath2, DevPathSize1);
  }
}


VOID
SctStrnCpy (
  OUT CHAR16                      *Dst,
  IN CHAR16                       *Src,
  IN UINTN                        Length
  )
/*++

Routine Description:

  Copy characters from one string to another.

--*/
{
  UINTN   SrcIndex;
  UINTN   DstIndex;

  SrcIndex = DstIndex = 0;
  while (DstIndex < Length) {
      Dst[DstIndex] = Src[SrcIndex];
      DstIndex ++;
      SrcIndex ++;
  }
}


CHAR16 *
SctGetShortFilePathAndName (
  IN CHAR16                       *FileName,
  IN CHAR16                       *RootFilePath
  )
/*++

Routine Description:

  Get the short file path and name (without the extension name).

  Notice: This function will allocate a new memory for the short file path
  and name. It is the caller's responsibility to free it.

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINTN       Length;
  CHAR16      *ShortFileName;

  //
  // Allocate new memory to store the short file path and name
  //
  Length = StrLen (FileName) - StrLen (RootFilePath) - 1;

  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(CHAR16) * (Length + 1),
                 (VOID **)&ShortFileName
                 );
  if (EFI_ERROR(Status)) {
    return NULL;
  }

  StrCpy (ShortFileName, FileName + StrLen(RootFilePath) + 1);

  //
  // Remove the extension name
  //
  for (Index = Length - 1; Index >= 0; Index --) {
    if (ShortFileName[Index] == L'.') {
      ShortFileName[Index] = L'\0';
      break;
    }
  }

  //
  // Done
  //
  return ShortFileName;
}


CHAR16 *
SctGetShortFileNameAndExt (
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Get the short file name and extension (without the path name).

  Notice: This function will NOT allocate a new memory for the short file
  name and extension. The caller SHOULD NOT free it.

--*/
{
  INTN  Index;

  //
  // Find the last '\' or '/'
  //
  for (Index = StrLen(FileName) - 1; Index >= 0; Index --) {
    if ((FileName[Index] == L'\\') || (FileName[Index] == L'/')) {
      break;
    }
  }

  //
  // Done
  //
  return FileName + Index + 1;
}


EFI_STATUS
SctMapDeviceFromName (
  IN CHAR16                       *FilePath,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath
  )
/*++

Routine Description:

  Map the device path from the file path of file system.

--*/
{
  EFI_DEVICE_PATH_PROTOCOL  *TempDevicePath;

  //
  // Get device path
  //
  TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *) ShellGetMap (FilePath);
  if (TempDevicePath == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Copy device path into a new instance
  //
  *DevicePath = DuplicateDevicePath (TempDevicePath);
  if (*DevicePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SctMapNameFromDevice (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  OUT CHAR16                      **FilePath
  )
/*++

Routine Description:

  Map the file path from the device path of file system.

--*/
{
  UINTN                     Size;
  UINTN                     Index;
  CHAR16                    *TempFilePath;
  EFI_DEVICE_PATH_PROTOCOL  *TempDevicePath;

  Size = DevicePathSize (DevicePath);

  //
  // Why hard code? Currently we cannot get the file system name from the device
  // path via shell services.
  //

  //
  // HARDCODE: 256 file systems
  //
  for (Index = 0; Index < 0x100; Index ++) {
    TempFilePath = PoolPrint (L"fs%x", Index);
    if (TempFilePath == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *) ShellGetMap (TempFilePath);
    if (TempDevicePath == NULL) {
      BS->FreePool (TempFilePath);
      continue;
    }

    if (SctDevicePathCompare (DevicePath, TempDevicePath) == 0) {
      *FilePath = TempFilePath;
      return EFI_SUCCESS;
    }

    BS->FreePool (TempFilePath);
  }

  //
  // HARDCODE: for NT32 filesystem
  //
  for (Index = 0; Index < 0x100; Index ++) {
    TempFilePath = PoolPrint (L"fsnt%x", Index);
    if (TempFilePath == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *) ShellGetMap (TempFilePath);
    if (TempDevicePath == NULL) {
      BS->FreePool (TempFilePath);
      continue;
    }

    if (SctDevicePathCompare (DevicePath, TempDevicePath) == 0) {
      *FilePath = TempFilePath;
      return EFI_SUCCESS;
    }

    BS->FreePool (TempFilePath);
  }

  //
  // No matched
  //
  return EFI_NOT_FOUND;
}


EFI_STATUS
SctJudgeInput (
  IN CHAR16                       *Message,
  OUT BOOLEAN                     *Result
  )
/*++

Routine Description:

  Assistant function to judge the user's choice, YES or NO?

--*/
{
  EFI_STATUS      Status;
  UINTN           Index;
  EFI_EVENT       EventList[1];
  EFI_INPUT_KEY   Key;

  while (TRUE) {
    //
    // Print the message
    //
    Print (L"%s", Message);

    //
    // Wait for a key
    //
    EventList[0] = gFT->SystemTable->ConIn->WaitForKey;
    Status = BS->WaitForEvent (1, EventList, &Index);
    if (EFI_ERROR(Status)) {
      return Status;
    }

    //
    // Read the key
    //
    Status = gFT->SystemTable->ConIn->ReadKeyStroke (
                                        gFT->SystemTable->ConIn,
                                        &Key
                                        );
    if (EFI_ERROR(Status)) {
      return Status;
    }

    Print (L"%c\n", Key.UnicodeChar);

    //
    // Check the key
    //
    if ((Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'Y')) {
      *Result = TRUE;
      break;
    } else if ((Key.UnicodeChar == L'n') || (Key.UnicodeChar == L'N')) {
      *Result = FALSE;
      break;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctChangeDirectory (
  IN EFI_HANDLE                   ImageHandle,
  IN CHAR16                       *DirName
  )
/*++

Routine Description:

  Change the current working directory.

  Don't know what the best way is. Here the shell command "CD" is used directly.

--*/
{
  EFI_STATUS    Status;
  CHAR16        *CmdLine;

  CmdLine = PoolPrint (L"CD %s", DirName);
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = ShellExecute (
             ImageHandle,
             CmdLine,
             FALSE
             );
  if (EFI_ERROR (Status)) {
    BS->FreePool (CmdLine);
    return Status;
  }

  BS->FreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctCreateDirectory (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Create a directory.

--*/
{
  EFI_STATUS        Status;
  CHAR16            *StringEnd;
  CHAR16            CSaved;
  EFI_FILE_HANDLE   Handle;

  //
  // Try to open the directory
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                      EFI_FILE_DIRECTORY
                      );
  if (!EFI_ERROR (Status)) {
    RootDir->Close (Handle);
    return Status;
  }

  if (Status != EFI_NOT_FOUND) {
    return Status;
  }

  //
  // Create the parent directory
  //
  StringEnd = FileName + StrLen(FileName) - 1;
  while (StringEnd >= FileName) {
    if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
      break;
    }
    StringEnd --;
  }

  if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
    CSaved = *StringEnd;
    *StringEnd = L'\0';

    if (StrLen(FileName) != 0) {
      Status = SctCreateDirectory (RootDir, FileName);
      if (EFI_ERROR (Status)) {
        *StringEnd = CSaved;
        return Status;
      }
    }

    *StringEnd = CSaved;
  }

  //
  // Create the directory
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
                      EFI_FILE_DIRECTORY
                      );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  RootDir->Close (Handle);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctCreateFile (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName,
  OUT EFI_FILE_HANDLE             *Handle
  )
/*++

Routine Description:

  Create a file.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *StringEnd;
  CHAR16      CSaved;

  //
  // Create the parent directory
  //
  StringEnd = FileName + StrLen(FileName) - 1;
  while (StringEnd >= FileName) {
    if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
      break;
    }
    StringEnd --;
  }

  if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
    CSaved = *StringEnd;
    *StringEnd = L'\0';

    if (StrLen(FileName) != 0) {
      Status = SctCreateDirectory (RootDir, FileName);
      if (EFI_ERROR (Status)) {
        *StringEnd = CSaved;
        return Status;
      }
    }

    *StringEnd = CSaved;
  }

  //
  // Open the file
  //
  Status = RootDir->Open (
                      RootDir,
                      Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                      0
                      );
  if (!EFI_ERROR (Status)) {
    //
    // If the file already exists, delete it
    //
    (*Handle)->Delete (*Handle);
  }

  //
  // Create the file
  //
  Status = RootDir->Open (
                      RootDir,
                      Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
                      0
                      );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctCreateDirectoryFromDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath
  )
/*++

Routine Description:

  Create a directory from the device path and the file path.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath;

  //
  // Locate the device handle
  //
  RemainingDevicePath = DevicePath;
  Status = BS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &RemainingDevicePath,
                 &DeviceHandle
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Locate the simple file system
  //
  Status = BS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 (VOID **)&Vol
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open the root directory of the simple file system
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open or create the directory
  //
  Status = SctCreateDirectory (RootDir, FilePath);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctCreateFileFromDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_FILE_HANDLE             *Handle
  )
/*++

Routine Description:

  Create a file from the device path and the file name.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath;

  //
  // Locate the device handle
  //
  RemainingDevicePath = DevicePath;
  Status = BS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &RemainingDevicePath,
                 &DeviceHandle
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Locate the simple file system
  //
  Status = BS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 (VOID **)&Vol
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open the root directory of the simple file system
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open or create the file
  //
  Status = SctCreateFile (RootDir, FileName, Handle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctIntToStr (
  IN UINTN                        Value,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert an integer to a decimal string.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert an integer to a string
  //
  SPrint (Buffer, 0, L"%d", Value);

  return EFI_SUCCESS;
}


EFI_STATUS
SctStrToInt (
  IN CHAR16                       *Buffer,
  OUT UINTN                       *Value
  )
/*++

Routine Description:

  Convert a decimal string to an integer.

--*/
{
  if ((Buffer == NULL) || (Value == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to an integer
  //
  if (Buffer[0] == L'-') {
    *Value = (UINTN) (0 - Atoi (Buffer + 1));
  } else {
    *Value = Atoi (Buffer);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SctShortToStr (
  IN UINT32                       Value,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert a short integer to a decimal string.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a short integer to a string
  //
  SPrint (Buffer, 0, L"%d", (UINTN) Value);

  return EFI_SUCCESS;
}


EFI_STATUS
SctStrToShort (
  IN CHAR16                       *Buffer,
  OUT UINT32                      *Value
  )
/*++

Routine Description:

  Convert a decimal string to a short integer.

--*/
{
  if ((Buffer == NULL) || (Value == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to a short integer
  //
  if (Buffer[0] == L'-') {
    *Value = (UINT32) (0 - Atoi (Buffer + 1));
  } else {
    *Value = (UINT32) Atoi (Buffer);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SctIntToHexStr (
  IN UINTN                        Value,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert an integer to a hexadecimal string.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert an integer to a string
  //
  SPrint (Buffer, 0, L"0x%x", Value);

  return EFI_SUCCESS;
}


EFI_STATUS
SctHexStrToInt (
  IN CHAR16                       *Buffer,
  OUT UINTN                       *Value
  )
/*++

Routine Description:

  Convert a hexadecimal string to an integer.

--*/
{
  if ((Buffer == NULL) || (Value == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to an integer
  //
  *Value = SctXtoi (Buffer);

  return EFI_SUCCESS;
}


EFI_STATUS
SctShortToHexStr (
  IN UINT32                       Value,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert a short integer to a hexadecimal string.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a short integer to a string
  //
  SPrint (Buffer, 0, L"0x%x", (UINTN) Value);

  return EFI_SUCCESS;
}


EFI_STATUS
SctHexStrToShort (
  IN CHAR16                       *Buffer,
  OUT UINT32                      *Value
  )
/*++

Routine Description:

  Convert a hexadecimal string to a short integer.

--*/
{
  if ((Buffer == NULL) || (Value == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to a short integer
  //
  *Value = (UINT32) SctXtoi (Buffer);

  return EFI_SUCCESS;
}


EFI_STATUS
SctBooleanToStr (
  IN BOOLEAN                      Value,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert a boolean to a string.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a boolean to a string
  //
  if (Value) {
    StrCpy (Buffer, L"True");
  } else {
    StrCpy (Buffer, L"False");
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SctStrToBoolean (
  IN CHAR16                       *Buffer,
  OUT BOOLEAN                     *Value
  )
/*++

Routine Description:

  Convert a string to a boolean.

--*/
{
  if ((Buffer == NULL) || (Value == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (StriCmp (Buffer, L"True") == 0) {
    *Value = TRUE;
  } else if (StriCmp (Buffer, L"False") == 0) {
    *Value = FALSE;
  } else {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SctGuidToStr (
  IN EFI_GUID                     *Guid,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert a GUID to a string.

--*/
{
  UINT32  Index;
  UINT32  BufferIndex;
  UINT32  DataIndex;
  UINT32  Len;
  
  if ((Guid == NULL) || (Buffer == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  BufferIndex = 0;

  //
  // Convert a GUID to a string
  //
  Len = sizeof(UINT32)*2;
  for (Index = 0; Index < Len; Index++) {
    Buffer[BufferIndex]  = 0;
    Buffer[BufferIndex] = (CHAR16)((Guid->Data1 & (0xf0000000>>(4 * Index)))>>(4 * (Len - Index - 1)));
    if (Buffer[BufferIndex] < 0x0A) {
       Buffer[BufferIndex] += (CHAR16)(L'0');
    } else {
       Buffer[BufferIndex] = (CHAR16)((L'A') + (Buffer[BufferIndex] - 0x0A));
    }
    BufferIndex ++;
  }

  Buffer[BufferIndex++] = L'-';
  
  //
  // Convert Guid->Data2
  //
  Len = sizeof(UINT16)*2;
  for (Index = 0; Index < Len; Index++) {
    Buffer[BufferIndex]  = 0;
    Buffer[BufferIndex] = (CHAR16)((Guid->Data2 & (0xf000>>(4 * Index)))>>(4 * (Len - Index - 1)));
    if (Buffer[BufferIndex] < 0x0A) {
       Buffer[BufferIndex] += (CHAR16)(L'0');
    } else {
       Buffer[BufferIndex] = (CHAR16)((L'A') + (Buffer[BufferIndex] - 0x0A));
    }
    BufferIndex ++;
  }

  Buffer[BufferIndex++] = L'-';
  
  //
  // Convert Guid->Data3
  //
  Len = sizeof(UINT16)*2;
  for (Index = 0; Index < Len; Index++) {
    Buffer[BufferIndex]  = 0;
    Buffer[BufferIndex] = (CHAR16)((Guid->Data3 & (0xf000>>(4 * Index)))>>(4 * (Len - Index - 1)));
    if (Buffer[BufferIndex] < 0x0A) {
       Buffer[BufferIndex] += (CHAR16)(L'0');
    } else {
       Buffer[BufferIndex] = (CHAR16)((L'A') + (Buffer[BufferIndex] - 0x0A));
    }
    BufferIndex ++;
  }

  Buffer[BufferIndex++] = L'-';
  
  //
  // Convert Guid->Data4[x]
  //
  Len = sizeof(UINT8)*2;
  for (DataIndex = 0; DataIndex < 8; DataIndex++) {
     for (Index = 0; Index < Len; Index++) {
        Buffer[BufferIndex]  = 0;
        Buffer[BufferIndex] = (CHAR16)((Guid->Data4[DataIndex] & (0xf0>>(4 * Index)))>>(4 * (Len - Index - 1)));
        if (Buffer[BufferIndex] < 0x0A) {
           Buffer[BufferIndex] += (CHAR16)(L'0');
        } else {
       Buffer[BufferIndex] = (CHAR16)((L'A') + (Buffer[BufferIndex] - 0x0A));
        }
        BufferIndex ++;
     }

     if (DataIndex == 1) {
       Buffer[BufferIndex++] = L'-';
     }
  }

  Buffer[BufferIndex] = 0;

  return EFI_SUCCESS;
}


EFI_STATUS
SctStrToGuid (
  IN CHAR16                       *Buffer,
  OUT EFI_GUID                    *Guid
  )
/*++

Routine Description:

  Convert a string to a GUID.

--*/
{
  if ((Buffer == NULL) || (Guid == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to a GUID
  //
  Guid->Data1     = (UINT32) SctHexStrnToInt (Buffer,      8);
  Guid->Data2     = (UINT16) SctHexStrnToInt (Buffer + 9,  4);
  Guid->Data3     = (UINT16) SctHexStrnToInt (Buffer + 14, 4);
  Guid->Data4[0]  = (UINT8)  SctHexStrnToInt (Buffer + 19, 2);
  Guid->Data4[1]  = (UINT8)  SctHexStrnToInt (Buffer + 21, 2);
  Guid->Data4[2]  = (UINT8)  SctHexStrnToInt (Buffer + 24, 2);
  Guid->Data4[3]  = (UINT8)  SctHexStrnToInt (Buffer + 26, 2);
  Guid->Data4[4]  = (UINT8)  SctHexStrnToInt (Buffer + 28, 2);
  Guid->Data4[5]  = (UINT8)  SctHexStrnToInt (Buffer + 30, 2);
  Guid->Data4[6]  = (UINT8)  SctHexStrnToInt (Buffer + 32, 2);
  Guid->Data4[7]  = (UINT8)  SctHexStrnToInt (Buffer + 34, 2);

  return EFI_SUCCESS;
}


EFI_STATUS
SctGuidArrayToStr (
  IN EFI_GUID                     *GuidArray,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert a GUID array to a string.

--*/
{
  EFI_STATUS  Status;

  if ((GuidArray == NULL) || (Buffer == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert the GUIDs to a string
  //
  Buffer[0] = L'\0';
  while (CompareGuid (GuidArray, &gEfiNullGuid) != 0) {
    Status = SctGuidToStr (GuidArray, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    GuidArray ++;
    StrCpy (Buffer + 36, L",");
    Buffer += 37;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SctStrToGuidArray (
  IN CHAR16                       *Buffer,
  OUT EFI_GUID                    **GuidArray
  )
/*++

Routine Description:

  Convert a string to a GUID array.

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINTN       NumberOfTokens;
  CHAR16      *TempBuffer;
  CHAR16      **Tokens;

  if ((Buffer == NULL) || (GuidArray == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to the tokens
  //
  TempBuffer = StrDuplicate (Buffer);

  Status = SctStrTokens (TempBuffer, &NumberOfTokens, &Tokens);
  if (EFI_ERROR (Status)) {
    BS->FreePool (TempBuffer);
    return Status;
  }

  //
  // Convert the tokens to the GUIDs
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 (NumberOfTokens + 1) * sizeof(EFI_GUID),
                 (VOID **)GuidArray
                 );
  if (EFI_ERROR (Status)) {
    BS->FreePool (TempBuffer);
    BS->FreePool (Tokens);
    return Status;
  }

  ZeroMem (*GuidArray, (NumberOfTokens + 1) * sizeof(EFI_GUID));

  for (Index = 0; Index < NumberOfTokens; Index ++) {
    if (Tokens[Index][0] == L'\0') {
      continue;
    }

    Status = SctStrToGuid (Tokens[Index], *GuidArray);
    if (EFI_ERROR (Status)) {
      BS->FreePool (TempBuffer);
      BS->FreePool (Tokens);
      return Status;
    }

    (*GuidArray) ++;
  }

  BS->FreePool (TempBuffer);
  BS->FreePool (Tokens);
  return EFI_SUCCESS;
}


EFI_STATUS
SctTestLevelToStr (
  IN EFI_TEST_LEVEL               TestLevel,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert a test level to a string.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a test level to a string
  //
  SPrint (
    Buffer,
    0,
    L"%s,%s,%s",
    (TestLevel & EFI_TEST_LEVEL_MINIMAL)    ? L"Minimal"    : L"",
    (TestLevel & EFI_TEST_LEVEL_DEFAULT)    ? L"Default"    : L"",
    (TestLevel & EFI_TEST_LEVEL_EXHAUSTIVE) ? L"Exhaustive" : L""
    );

  return EFI_SUCCESS;
}


EFI_STATUS
SctStrToTestLevel (
  IN CHAR16                       *Buffer,
  OUT EFI_TEST_LEVEL              *TestLevel
  )
/*++

Routine Description:

  Convert a string to a test level.

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINTN       NumberOfTokens;
  CHAR16      *TempBuffer;
  CHAR16      **Tokens;

  if ((Buffer == NULL) || (TestLevel == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to the tokens
  //
  TempBuffer = StrDuplicate (Buffer);

  Status = SctStrTokens (TempBuffer, &NumberOfTokens, &Tokens);
  if (EFI_ERROR (Status)) {
    BS->FreePool (TempBuffer);
    return Status;
  }

  //
  // Convert the tokens to the test level
  //
  *TestLevel = 0;

  for (Index = 0; Index < NumberOfTokens; Index ++) {
    if (Tokens[Index][0] == L'\0') {
      continue;
    }

    if (StriCmp (Tokens[Index], L"Minimal") == 0) {
      *TestLevel |= EFI_TEST_LEVEL_MINIMAL;
    } else if (StriCmp (Tokens[Index], L"Default") == 0) {
      *TestLevel |= EFI_TEST_LEVEL_DEFAULT;
    } else if (StriCmp (Tokens[Index], L"Exhaustive") == 0) {
      *TestLevel |= EFI_TEST_LEVEL_EXHAUSTIVE;
    } else {
      BS->FreePool (TempBuffer);
      BS->FreePool (Tokens);
      return EFI_UNSUPPORTED;
    }
  }

  BS->FreePool (TempBuffer);
  BS->FreePool (Tokens);
  return EFI_SUCCESS;
}


EFI_STATUS
SctVerboseLevelToStr (
  IN EFI_VERBOSE_LEVEL            VerboseLevel,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert a verbose level to a string.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a verbose level to a string
  //
  switch (VerboseLevel) {
  case EFI_VERBOSE_LEVEL_QUIET:
    StrCpy (Buffer, L"Quiet");
    break;
  case EFI_VERBOSE_LEVEL_MINIMAL:
    StrCpy (Buffer, L"Minimal");
    break;
  case EFI_VERBOSE_LEVEL_DEFAULT:
    StrCpy (Buffer, L"Default");
    break;
  case EFI_VERBOSE_LEVEL_NOISY:
    StrCpy (Buffer, L"Noisy");
    break;
  case EFI_VERBOSE_LEVEL_EXHAUSTIVE:
    StrCpy (Buffer, L"Exhaustive");
    break;
  default:
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SctStrToVerboseLevel (
  IN CHAR16                       *Buffer,
  OUT EFI_VERBOSE_LEVEL           *VerboseLevel
  )
/*++

Routine Description:

  Convert a string to a verbose level.

--*/
{
  if ((Buffer == NULL) || (VerboseLevel == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to a verbose level
  //
  if (StriCmp (Buffer, L"Quiet") == 0) {
    *VerboseLevel = EFI_VERBOSE_LEVEL_QUIET;
  } else if (StriCmp (Buffer, L"Minimal") == 0) {
    *VerboseLevel = EFI_VERBOSE_LEVEL_MINIMAL;
  } else if (StriCmp (Buffer, L"Default") == 0) {
    *VerboseLevel = EFI_VERBOSE_LEVEL_DEFAULT;
  } else if (StriCmp (Buffer, L"Noisy") == 0) {
    *VerboseLevel = EFI_VERBOSE_LEVEL_NOISY;
  } else if (StriCmp (Buffer, L"Exhaustive") == 0) {
    *VerboseLevel = EFI_VERBOSE_LEVEL_EXHAUSTIVE;
  } else {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SctCaseAttributeToStr (
  IN UINT32                       CaseAttribute,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Convert a case attribute to a string.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a case attribute to a string
  //
  SPrint (
    Buffer,
    0,
    L"%s,%s,%s",
    (CaseAttribute & EFI_TEST_CASE_MANUAL)         ? L"Manual"        : L"",
    (CaseAttribute & EFI_TEST_CASE_DESTRUCTIVE)    ? L"Destructive"   : L"",
    (CaseAttribute & EFI_TEST_CASE_RESET_REQUIRED) ? L"ResetRequired" : L""
    );

  return EFI_SUCCESS;
}


EFI_STATUS
SctStrToCaseAttribute (
  IN CHAR16                       *Buffer,
  OUT UINT32                      *CaseAttribute
  )
/*++

Routine Description:

  Convert a string to a case attribute.

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINTN       NumberOfTokens;
  CHAR16      *TempBuffer;
  CHAR16      **Tokens;

  if ((Buffer == NULL) || (CaseAttribute == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert a string to the tokens
  //
  TempBuffer = StrDuplicate (Buffer);

  Status = SctStrTokens (TempBuffer, &NumberOfTokens, &Tokens);
  if (EFI_ERROR (Status)) {
    BS->FreePool (TempBuffer);
    return Status;
  }

  //
  // Convert the tokens to the case attribute
  //
  *CaseAttribute = EFI_TEST_CASE_AUTO;

  for (Index = 0; Index < NumberOfTokens; Index ++) {
    if (Tokens[Index][0] == L'\0') {
      continue;
    }

    if (StriCmp (Tokens[Index], L"Manual") == 0) {
      *CaseAttribute |= EFI_TEST_CASE_MANUAL;
    } else if (StriCmp (Tokens[Index], L"Destructive") == 0) {
      *CaseAttribute |= EFI_TEST_CASE_DESTRUCTIVE;
    } else if (StriCmp (Tokens[Index], L"ResetRequired") == 0) {
      *CaseAttribute |= EFI_TEST_CASE_RESET_REQUIRED;
    } else {
      BS->FreePool (TempBuffer);
      BS->FreePool (Tokens);
      return EFI_UNSUPPORTED;
    }
  }

  BS->FreePool (TempBuffer);
  BS->FreePool (Tokens);
  return EFI_SUCCESS;
}


BOOLEAN
SctStrBeginWith (
  IN CHAR16                       *Str,
  IN CHAR16                       *SubStr
  )
/*++

Routine Description:

  Verify if the string is begin with the sub string.

--*/
{
  if ((Str == NULL) || (SubStr == NULL) || (StrLen(Str) < StrLen(SubStr))) {
    return FALSE;
  }

  //
  // Remove the pre-space characters
  //
  while (*SubStr == L' ') {
    SubStr ++;
  }

  //
  // Compare
  //
  if (StrnCmp (Str, SubStr, StrLen(SubStr)) == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}


BOOLEAN
SctStrEndWith (
  IN CHAR16                       *Str,
  IN CHAR16                       *SubStr
  )
/*++

Routine Description:

  Verify if the string is end with the sub string.

--*/
{
  CHAR16  *Temp;

  if ((Str == NULL) || (SubStr == NULL) || (StrLen(Str) < StrLen(SubStr))) {
    return FALSE;
  }

  Temp = Str + StrLen(Str) - StrLen(SubStr);

  //
  // Compare
  //
  if (StriCmp (Temp, SubStr) == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}


CHAR16 *
SctStrBeginReplace (
  IN CHAR16                       *Str,
  IN CHAR16                       *SubStr
  )
/*++

Routine Description:

  Replace the begin characters with the sub string.

--*/
{
  CHAR16  *Temp;

  if ((Str == NULL) || (SubStr == NULL) || (StrLen(Str) < StrLen(SubStr))) {
    return NULL;
  }

  Temp = StrDuplicate (Str);
  SctStrnCpy (Temp, SubStr, StrLen(SubStr));

  return Temp;
}


CHAR16 *
SctStrEndReplace (
  IN CHAR16                       *Str,
  IN CHAR16                       *SubStr
  )
/*++

Routine Description:

  Replace the end characeters with the sub string.

--*/
{
  CHAR16  *Temp;

  if ((Str == NULL) || (SubStr == NULL) || (StrLen(Str) < StrLen(SubStr))) {
    return NULL;
  }

  Temp = StrDuplicate (Str);
  StrCpy (Temp + StrLen(Str) - StrLen(SubStr), SubStr);

  return Temp;
}


//
// Internal functions implementation
//

UINTN
SctXtoi (
  CHAR16                          *String
  )
/*++

Routine Description:

  Convert a hexadecimal stromg to an integer.

--*/
{
  UINTN   Index;
  UINTN   Value;

  //
  // Skip the preceeding L"0x"
  //
  if ((String[0] == L'0') && ((String[1] == L'x') || (String[1] == L'X'))) {
    String += 2;
  }

  Value = 0;

  for (Index = 0; String[Index] != L'\0'; Index ++) {
    if ((String[Index] >= L'0') && (String[Index] <= L'9')) {
      Value = (Value << 4) + (String[Index] - L'0');
    } else if ((String[Index] >= L'A') && (String[Index] <= L'F')) {
      Value = (Value << 4) + (String[Index] - L'A' + 10);
    } else if ((String[Index] >= L'a') && (String[Index] <= L'f')) {
      Value = (Value << 4) + (String[Index] - L'a' + 10);
    } else {
      return 0;
    }
  }

  return Value;
}


UINTN
SctHexStrnToInt (
  IN CHAR16                       *String,
  IN UINTN                        Length
  )
/*++

Routine Description:

  Convert part of hexadecimal string to an integer.

--*/
{
  UINTN   Index;
  UINTN   Value;

  Value = 0;

  for (Index = 0; Index < Length; Index ++) {
    if ((String[Index] >= L'0') && (String[Index] <= L'9')) {
      Value = (Value << 4) + (String[Index] - L'0');
    } else if ((String[Index] >= L'A') && (String[Index] <= L'F')) {
      Value = (Value << 4) + (String[Index] - L'A' + 10);
    } else if ((String[Index] >= L'a') && (String[Index] <= L'f')) {
      Value = (Value << 4) + (String[Index] - L'a' + 10);
    } else {
      return 0;
    }
  }

  return Value;
}


EFI_STATUS
SctStrTokens (
  IN CHAR16                       *String,
  OUT UINTN                       *NumberOfTokens,
  OUT CHAR16                      ***Tokens
  )
/*++

Routine Description:

  Convert a string to the tokens. ',' is the delimiter character.

  Notice: 1. The input string is modified after the conversion.
          2. The caller needs to free the token array, but should not to free
             each token (it still points to the input string).

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINTN       Number;
  CHAR16      **TempTokens;

  if ((String == NULL) || (NumberOfTokens == NULL) || (Tokens == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the number of tokens
  //
  Number = 1;
  for (Index = 0; String[Index] != L'\0'; Index ++) {
    if (String[Index] == L',') {
      Number ++;
    }
  }

  //
  // Allocate memory for the pointers to tokens
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 Number * sizeof(CHAR16 *),
                 (VOID **)&TempTokens
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (TempTokens, Number * sizeof(CHAR16 *));

  //
  // Set all pointers to tokens
  //
  TempTokens[0] = String;
  Number = 1;
  for (Index = 0; String[Index] != L'\0'; Index ++) {
    if (String[Index] == L',') {
      TempTokens[Number] = String + Index + 1;
      String[Index]    = L'\0';
      Number ++;
    }
  }

  //
  // Done
  //
  *NumberOfTokens = Number;
  *Tokens = TempTokens;
  return EFI_SUCCESS;
}
