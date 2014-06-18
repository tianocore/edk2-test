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

  ReportSupport.c

Abstract:

  This file provides the support services for test report generation.

--*/

#include "Sct.h"
#include "ReportSupport.h"

//
// Module variables
//

CHAR16  *mReportBuffer        = NULL;
UINTN   mReportBufferMaxSize  = 0;
UINTN   mReportBufferUsedSize = 0;

CHAR16  *mLineBuffer          = NULL;
CHAR16  *mFieldBuffer         = NULL;


//
// Internal functions declaration
//

UINTN
StrSpn (
  IN CHAR16                       *String,
  IN CHAR16                       *CharSet
  );

CHAR16 *
StrBrk (
  IN CHAR16                       *String,
  IN CHAR16                       *CharSet
  );


//
// Module functions implementation
//

BOOLEAN
FileExist (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Check whether a file exists.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL)) {
    return FALSE;
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
    return FALSE;
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
    return FALSE;
  }

  //
  // Open the root directory
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  //
  // Open the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR (Status)) {
    RootDir->Close (RootDir);
    return FALSE;
  }

  RootDir->Close (RootDir);
  Handle->Close (Handle);
  return TRUE;
}


EFI_STATUS
ReadFileToBuffer (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT UINTN                       *BufferSize,
  OUT VOID                        **Buffer
  )
/*++

Routine Description:

  Read a file.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  UINTN                             FileInfoSize;
  EFI_FILE_INFO                     *FileInfo;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath;
  UINTN                             TempBufferSize;
  VOID                              *TempBuffer;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (Buffer == NULL)) {
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
  // Open the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open file - %r", Status));
    RootDir->Close (RootDir);
    return Status;
  }

  RootDir->Close (RootDir);

  //
  // Get the file information
  //
  FileInfoSize = sizeof(EFI_FILE_INFO) + 1024;

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 FileInfoSize,
                 (VOID **)&FileInfo
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    Handle->Close (Handle);
    return Status;
  }

  SctZeroMem (FileInfo, FileInfoSize);

  Status = Handle->GetInfo (
                     Handle,
                     &gEfiFileInfoGuid,
                     &FileInfoSize,
                     FileInfo
                     );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get file info - %r", Status));
    Handle->Close (Handle);
    tBS->FreePool (FileInfo);
    return Status;
  }

  //
  // Allocate buffer for the file data. The last CHAR16 is for L'\0'
  //
  TempBufferSize = (UINTN) FileInfo->FileSize + sizeof(CHAR16);

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 TempBufferSize,
                 (VOID **)&TempBuffer
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    Handle->Close (Handle);
    tBS->FreePool (FileInfo);
    return Status;
  }

  SctZeroMem (TempBuffer, TempBufferSize);

  tBS->FreePool (FileInfo);

  //
  // Read the file data to the buffer
  //
  Status = Handle->Read (
                     Handle,
                     &TempBufferSize,
                     TempBuffer
                     );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Read file - %r", Status));
    Handle->Close (Handle);
    tBS->FreePool (TempBuffer);
    return Status;
  }

  Handle->Close (Handle);

  *BufferSize = TempBufferSize;
  *Buffer     = TempBuffer;
  return EFI_SUCCESS;
}


EFI_STATUS
GetIndexFromFileName (
  IN OUT CHAR16                   *FileName,
  OUT CHAR16                      **CaseIndex,
  OUT CHAR16                      **CaseIteration
  )
/*++

Routine Description:

  Get index and iteration from the file name. The input file name will be
  modified in this function.

  FileName should be in format "Name_<Index>_<Iteration>_<GUID>.ekl", in
  which GUID is in format XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX.

--*/
{
  UINTN   Index;
  CHAR16  *String;

  //
  // Check parameters
  //
  if ((FileName == NULL) || (CaseIndex == NULL) || (CaseIteration == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Check .ekl
  //
  if (!SctStrEndWith (FileName, L".ekl")) {
    return EFI_INVALID_PARAMETER;
  }
  if (SctStrLen (FileName) <= SctStrLen(L"XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX.ekl")) {
    return EFI_INVALID_PARAMETER;
  }

  String = FileName + SctStrLen (FileName) - SctStrLen(L"XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX.ekl");

  //
  // Check the last '_'
  //
  String --;
  if (*String != L'_') {
    return EFI_INVALID_PARAMETER;
  }

  *String = L'\0';

  //
  // Check the middle '_'
  //
  for (Index = 0; Index < 20; Index ++) {
    String --;

    if (*String == L'_') {
      *CaseIteration = String + 1;
      *String = L'\0';
      break;
    }
  }

  if ((Index == 0) || (Index == 20)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Check the first '_'
  //
  for (Index = 0; Index < 20; Index ++) {
    String --;

    if (*String == L'_') {
      *CaseIndex = String + 1;
      *String = L'\0';
      break;
    }
  }

  if ((Index == 0) || (Index == 20)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the index and iteration successfully
  //
  return EFI_SUCCESS;
}

EFI_STATUS
AutoStrCat (
  IN OUT CHAR16                   **DstBuffer,
  IN CHAR16                       *SrcBuffer
  )
/*++

Routine Description:

  Append one string to an automatically enlarged string.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *TempBuffer;

  //
  // Check parameters
  //
  if ((DstBuffer == NULL) || (SrcBuffer == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (SctStrLen (SrcBuffer) >= EFI_SCT_LOG_BUFFER_SIZE) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Need to create a new buffer?
  //
  if (*DstBuffer == NULL) {
    //
    // Allocate buffer for the destination data
    //
    mReportBufferMaxSize  = EFI_SCT_LOG_BUFFER_SIZE;
    mReportBufferUsedSize = 0;

    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   mReportBufferMaxSize * sizeof(CHAR16),
                   (VOID **)&mReportBuffer
                   );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
      mReportBufferMaxSize = 0;
      return Status;
    }

    SctZeroMem (mReportBuffer, mReportBufferMaxSize * sizeof(CHAR16));
  }

  //
  // Need to enlarge a new buffer
  //
  if (mReportBufferUsedSize + SctStrLen (SrcBuffer) >= mReportBufferMaxSize) {
    //
    // Allocate buffer for the destination data
    //
    mReportBufferMaxSize = mReportBufferMaxSize * 2;

    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   mReportBufferMaxSize * sizeof(CHAR16),
                   (VOID **)&TempBuffer
                   );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
      mReportBufferMaxSize = mReportBufferMaxSize / 2;
      return Status;
    }

    SctZeroMem (TempBuffer, mReportBufferMaxSize * sizeof(CHAR16));

    //
    // Copy the original data
    //
    SctCopyMem (TempBuffer, mReportBuffer, mReportBufferUsedSize * sizeof(CHAR16));

    //
    // Free the original buffer
    //
    tBS->FreePool (mReportBuffer);
    mReportBuffer = TempBuffer;
  }

  //
  // Append the source data to the destination data
  //
  SctStrCpy (mReportBuffer + mReportBufferUsedSize, SrcBuffer);
  mReportBufferUsedSize += SctStrLen (SrcBuffer);

  //
  // Done
  //
  *DstBuffer = mReportBuffer;
  return EFI_SUCCESS;
}


CHAR16 *
StrTokenLine (
  IN CHAR16                       *String OPTIONAL,
  IN CHAR16                       *CharSet
  )
/*++

Routine Description:

  Find the next token after one or more specified characters.

--*/
{
  CHAR16  *Begin;
  CHAR16  *End;

  Begin = (String == NULL) ? mLineBuffer : String;
  if (Begin == NULL) {
    return NULL;
  }

  Begin += StrSpn (Begin, CharSet);
  if (*Begin == L'\0') {
    mLineBuffer = NULL;
    return NULL;
  }

  End = StrBrk (Begin, CharSet);
  if ((End != NULL) && (*End != L'\0')) {
    *End = L'\0';
    End ++;
  }

  mLineBuffer = End;
  return Begin;
}


CHAR16 *
StrTokenField (
  IN CHAR16                       *String OPTIONAL,
  IN CHAR16                       *CharSet
  )
/*++

Routine Description:

  Find the next token after one specificed characters.

--*/
{
  CHAR16  *Begin;
  CHAR16  *End;


  Begin = (String == NULL) ? mFieldBuffer : String;
  if (Begin == NULL) {
    return NULL;
  }

  if (*Begin == L'\0') {
    mFieldBuffer = NULL;
    return NULL;
  }

  End = StrBrk (Begin, CharSet);
  if ((End != NULL) && (*End != L'\0')) {
    *End = L'\0';
    End ++;
  }

  mFieldBuffer = End;
  return Begin;
}


//
// Internal functions implementation
//

UINTN
StrSpn (
  IN CHAR16                       *String,
  IN CHAR16                       *CharSet
  )
/*++

Routine Description:

  Find the first substring.

--*/
{
  UINTN   Count;
  CHAR16  *Str1;
  CHAR16  *Str2;

  Count = 0;

  for (Str1 = String; *Str1 != L'\0'; Str1 ++) {
    for (Str2 = CharSet; *Str2 != L'\0'; Str2 ++) {
      if (*Str1 == *Str2) {
        break;
      }
    }

    if (*Str2 == L'\0') {
      return Count;
    }

    Count ++;
  }

  return Count;
}


CHAR16 *
StrBrk (
  IN CHAR16                       *String,
  IN CHAR16                       *CharSet
  )
/*++

Routine Description:

  Searches a string for the first occurrence of a character contained in a
  specified buffer.

--*/
{
  CHAR16  *Str1;
  CHAR16  *Str2;

  for (Str1 = String; *Str1 != L'\0'; Str1 ++) {
    for (Str2 = CharSet; *Str2 != L'\0'; Str2 ++) {
      if (*Str1 == *Str2) {
        return (CHAR16 *) Str1;
      }
    }
  }

  return NULL;
}
