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
