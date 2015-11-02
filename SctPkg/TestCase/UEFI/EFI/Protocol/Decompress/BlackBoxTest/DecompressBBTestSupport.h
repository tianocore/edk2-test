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

  DecompressBBTestSupport.h

Abstract:

  BB test support header file for Decompress protocol

--*/

#ifndef _DECOMPRESS_BBTEST_SUPPORT_H
#define _DECOMPRESS_BBTEST_SUPPORT_H

//
//global variables
//

#define MAX_STRING_LEN                 256

#define DEPENDECY_DIR_NAME             L"dependency\\DecompressBBTest"
#define DECOMPRESS_TEST_INI_FILE       L"DecompressBBTest.ini"

extern EFI_DEVICE_PATH_PROTOCOL        *gDevicePath;
extern CHAR16                          *gFilePath;
extern EFI_HANDLE                      gDeviceHandle;

//
//support function protype
//

EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL  **ProfileLib
  );

EFI_STATUS
OpenTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                *FileHandle
  );

EFI_STATUS
CloseTestIniFile (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  IN  EFI_INI_FILE_HANDLE                 FileHandle
  );

EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  );

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
GetUncompressedFileSize (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT32              *FileSize
  );

EFI_STATUS
GetCompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  );

EFI_STATUS
GetUncompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  );

EFI_STATUS
GetInvalidCompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  );

EFI_STATUS
GetStringItemFromFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN UINTN                Order,
  IN CHAR16               *SectionName,
  IN CHAR16               *ItemName,
  OUT CHAR16              **String
  );

EFI_STATUS
OpenFileAndGetSize (
  IN  CHAR16          *FileName,
  OUT EFI_FILE_HANDLE *FileHandle,
  OUT UINT32          *FileSize
  );

 #endif
