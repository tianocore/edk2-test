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

  SctMisc.h

Abstract:

  This file provides all miscellaneous services for SCT.

--*/

#ifndef _EFI_SCT_MISC_H_
#define _EFI_SCT_MISC_H_

//
// External functions declaration
//

EFI_STATUS
GetFilesystemDevicePath (
  IN CHAR16                       *Name,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **RemainingFilePath OPTIONAL
  );

EFI_STATUS
StripLastPathComponent (
  IN OUT CHAR16                       *Name
  );

EFI_STATUS
GetMaxWatchdogTimer (
  OUT UINTN                       *MaxWatchdogTimer
  );

INTN
SctDevicePathCompare (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath1,
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath2
  );

CHAR16 *
SctGetShortFilePathAndName (
  IN CHAR16                       *FileName,
  IN CHAR16                       *RootFilePath
  );

CHAR16 *
SctGetShortFileNameAndExt (
  IN CHAR16                       *FileName
  );

EFI_STATUS
SctMapDeviceFromName (
  IN CHAR16                       *FilePath,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath
  );

EFI_STATUS
SctMapNameFromDevice (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  OUT CHAR16                      **FilePath
  );

EFI_STATUS
SctJudgeInput (
  IN CHAR16                       *Message,
  OUT BOOLEAN                     *Result
  );

EFI_STATUS
SctChangeDirectory (
  IN EFI_HANDLE                   ImageHandle,
  IN CHAR16                       *DirName
  );

EFI_STATUS
SctCreateDirectory (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName
  );

EFI_STATUS
SctCreateFile (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName,
  OUT EFI_FILE_HANDLE             *Handle
  );

EFI_STATUS
SctCreateDirectoryFromDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath
  );

EFI_STATUS
SctCreateFileFromDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_FILE_HANDLE             *Handle
  );

//
// Conversion functions declaration
//

EFI_STATUS
SctIntToStr (
  IN UINTN                        Value,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctStrToInt (
  IN CHAR16                       *Buffer,
  OUT UINTN                       *Value
  );

EFI_STATUS
SctShortToStr (
  IN UINT32                       Value,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctStrToShort (
  IN CHAR16                       *Buffer,
  OUT UINT32                      *Value
  );

EFI_STATUS
SctIntToHexStr (
  IN UINTN                        Value,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctHexStrToInt (
  IN CHAR16                       *Buffer,
  OUT UINTN                       *Value
  );

EFI_STATUS
SctShortToHexStr (
  IN UINT32                       Value,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctHexStrToShort (
  IN CHAR16                       *Buffer,
  OUT UINT32                      *Value
  );

EFI_STATUS
SctBooleanToStr (
  IN BOOLEAN                      Value,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctStrToBoolean (
  IN CHAR16                       *Buffer,
  OUT BOOLEAN                     *Value
  );

EFI_STATUS
SctGuidToStr (
  IN EFI_GUID                     *Guid,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctStrToGuid (
  IN CHAR16                       *Buffer,
  OUT EFI_GUID                    *Guid
  );

EFI_STATUS
SctGuidArrayToStr (
  IN EFI_GUID                     *GuidArray,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctStrToGuidArray (
  IN CHAR16                       *Buffer,
  OUT EFI_GUID                    **GuidArray
  );

EFI_STATUS
SctTestLevelToStr (
  IN EFI_TEST_LEVEL               TestLevel,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctStrToTestLevel (
  IN CHAR16                       *Buffer,
  OUT EFI_TEST_LEVEL              *TestLevel
  );

EFI_STATUS
SctVerboseLevelToStr (
  IN EFI_VERBOSE_LEVEL            VerboseLevel,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctStrToVerboseLevel (
  IN CHAR16                       *Buffer,
  OUT EFI_VERBOSE_LEVEL           *VerboseLevel
  );

EFI_STATUS
SctCaseAttributeToStr (
  IN UINT32                       CaseAttribute,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
SctStrToCaseAttribute (
  IN CHAR16                       *Buffer,
  OUT UINT32                      *CaseAttribute
  );

BOOLEAN
SctStrBeginWith (
  IN CHAR16                       *Str,
  IN CHAR16                       *SubStr
  );

BOOLEAN
SctStrEndWith (
  IN CHAR16                       *Str,
  IN CHAR16                       *SubStr
  );

CHAR16 *
SctStrBeginReplace (
  IN CHAR16                       *Str,
  IN CHAR16                       *SubStr
  );

CHAR16 *
SctStrEndReplace (
  IN CHAR16                       *Str,
  IN CHAR16                       *SubStr
  );

#endif
