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

  BisBBTestMain.c

Abstract:

  Test Driver of Bis Protocol

--*/

#include "SctLib.h"
#include "BisBBTestMain.h"

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  BIS_TEST_REVISION,
  EFI_BIS_PROTOCOL_GUID,
  L"Boot Integrity Services Protocol Test",
  L"UEFI Boot Integrity Services Protocol Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {

#ifdef EFI_TEST_EXHAUSTIVE
  {
    BIS_MANUAL_TEST_GUID,
    L"Bis_Manual",
    L"Manual Test for Bis Protocol",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestManualTest
  },
#endif

  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestBisUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Bis Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestBisProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  //
  // Initialize library
  //
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);
  SctInitializeDriver (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestBisUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestBisUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

/**
 *  Get the device path of floppy disk.
 */
EFI_STATUS
GetFloppyDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL        **FloppyDevicePath
  )
{
  EFI_STATUS                      Status;
  UINTN                           NoHandle;
  EFI_HANDLE                      *Buffer;
  UINTN                           Index;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL        *RemainPath;
  EFI_DEVICE_PATH_PROTOCOL        *LastNode;
  ACPI_HID_DEVICE_PATH            *AcpiNode;

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gEfiDevicePathProtocolGuid,
                   NULL,
                   &NoHandle,
                   &Buffer
               );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  for (Index = 0; Index < NoHandle; Index++) {
    Status = gtBS->HandleProtocol (
                     Buffer[Index],
                     &gEfiDevicePathProtocolGuid,
                     &DevicePath
                 );
    RemainPath = DevicePath;
    LastNode = DevicePath;
    while (!SctIsDevicePathEnd (RemainPath)) {
      LastNode = RemainPath;
      RemainPath = SctNextDevicePathNode (RemainPath);
    }
    //
    // Is LastNode ACPI device path node ?
    //
    if ((SctDevicePathType (LastNode) == 2) &&
        (SctDevicePathSubType (LastNode) == 1)) {
      AcpiNode = (ACPI_HID_DEVICE_PATH*)LastNode;
      //
      // Is floppy device path ?
      //
      if (EISA_ID_TO_NUM(AcpiNode->HID) == 0x0604) {
        *FloppyDevicePath = DevicePath;
        return EFI_SUCCESS;
      }
    }
  }
  return EFI_NOT_FOUND;
}

/**
 *  Read a file from floppy disk.
 */
EFI_STATUS
ReadFloppyFile (
  IN CHAR16       *FileName,
  OUT UINT32      *Length,
  OUT VOID        **Buffer
  )
{
  EFI_STATUS                          Status;
  EFI_HANDLE                          DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL     *Vol;
  EFI_FILE_HANDLE                     RootDir;
  EFI_FILE_HANDLE                     Handle;
  EFI_FILE_INFO                       *FileInfo;
  UINTN                               FileInfoSize;
  VOID*                               FileBuffer;
  UINTN                               FileSize;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;

  //
  // Get floppy device path
  //
  Status = GetFloppyDevicePath (&DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //  Determine device handle for fs protocol on floppy device path
  //
  Status = gtBS->LocateDevicePath (
                   &gEfiSimpleFileSystemProtocolGuid,
                   &DevicePath,
                   &DeviceHandle
                   );
  if (EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //  Determine volume for file system on device handle
  //
  Status = gtBS->HandleProtocol (
                   DeviceHandle,
                   &gEfiSimpleFileSystemProtocolGuid,
                   (VOID*)&Vol
                   );
  if (EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Open volume for file system on device path
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (Status == EFI_MEDIA_CHANGED) {
    //
    // Reopen the volume
    //
    Status = gtBS->HandleProtocol (
                     DeviceHandle,
                     &gEfiSimpleFileSystemProtocolGuid,
                     (VOID*)&Vol
                     );
    if (EFI_ERROR(Status) ) {
      return Status;
    }
    Status = Vol->OpenVolume (Vol, &RootDir);
  }
  if (EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Open file for read
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR(Status) ) {
    RootDir->Close (RootDir);
    return Status;
  }


  //
  // Get file size
  //
  FileInfoSize = 1;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   FileInfoSize,
                   (VOID **)&FileInfo
                   );
  if (EFI_ERROR(Status) ) {
    Handle->Close (Handle);
    RootDir->Close (RootDir);
    return Status;
  }
  //
  // the return code should be EFI_BUFFER_TOO_SMALL
  //
  Status = Handle->GetInfo (
                     Handle,
                     &gEfiFileInfoGuid,
                     &FileInfoSize,
                     FileInfo
                     );

  gtBS->FreePool (FileInfo);
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   FileInfoSize,
                   (VOID **)&FileInfo
                   );
  if (EFI_ERROR(Status) ) {
    Handle->Close (Handle);
    RootDir->Close (RootDir);
    return Status;
  }
  Status = Handle->GetInfo (
                     Handle,
                     &gEfiFileInfoGuid,
                     &FileInfoSize,
                     FileInfo
                     );
  FileSize = (UINTN)FileInfo->FileSize;
  gtBS->FreePool (FileInfo);

  //
  // Read the file
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   FileSize,
                   (VOID **)&FileBuffer
                   );
  if (EFI_ERROR(Status) ) {
    Handle->Close (Handle);
    RootDir->Close (RootDir);
    return Status;
  }
  Status = Handle->Read (
                     Handle,
                     &FileSize,
                     FileBuffer
                     );
  if (EFI_ERROR(Status) ) {
    gtBS->FreePool (FileBuffer);
  } else {
    *Buffer = FileBuffer;
    *Length = (UINT32)FileSize;
  }
  Handle->Close (Handle);
  RootDir->Close (RootDir);
  return Status;
}

/**
 *  Write a file to floppy disk.
 */
EFI_STATUS
WriteFloppyFile (
  IN CHAR16      *FileName,
  IN OUT UINT32  Length,
  IN VOID        *Buffer
  )
{
  EFI_STATUS                          Status;
  EFI_HANDLE                          DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL     *Vol;
  EFI_FILE_HANDLE                     RootDir;
  EFI_FILE_HANDLE                     Handle;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  UINTN                               BufLen;

  //
  // Get floppy device path
  //
  Status = GetFloppyDevicePath (&DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //  Determine device handle for fs protocol on floppy device path
  //
  Status = gtBS->LocateDevicePath (
                   &gEfiSimpleFileSystemProtocolGuid,
                   &DevicePath,
                   &DeviceHandle
                   );
  if (EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //  Determine volume for file system on device handle
  //
  Status = gtBS->HandleProtocol (
                   DeviceHandle,
                   &gEfiSimpleFileSystemProtocolGuid,
                   (VOID*)&Vol
                   );
  if (EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Open volume for file system on device path
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (Status == EFI_MEDIA_CHANGED) {
    //
    // Reopen the volume
    //
    Status = gtBS->HandleProtocol (
                     DeviceHandle,
                     &gEfiSimpleFileSystemProtocolGuid,
                     (VOID*)&Vol
                     );
    if (EFI_ERROR(Status) ) {
      return Status;
    }
    Status = Vol->OpenVolume (Vol, &RootDir);
  }
  if (EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Determine the existence of the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                      0
                      );
  if ((Status != EFI_SUCCESS) && (Status != EFI_NOT_FOUND)) {
    RootDir->Close (RootDir);
    return Status;
  }

  if (Status == EFI_SUCCESS) {
    //
    // Delete the existent file
    //
    Status = Handle->Delete (Handle);
    if (Status != EFI_SUCCESS) {
      Handle->Close (Handle);
      RootDir->Close (RootDir);
      return Status;
    }
  }

  //
  // Create the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_CREATE|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR(Status)) {
    RootDir->Close (RootDir);
    return Status;
  }

  //
  // Write the file
  //
  BufLen = Length;
  Status = Handle->Write (Handle, &BufLen, Buffer);

  Handle->Close (Handle);
  RootDir->Close (RootDir);
  return Status;
}

/**
 *  Wait for any key stroke.
 */
VOID
PressAnyKey ()
{
  UINTN                                WaitIndex;
  EFI_INPUT_KEY                        Key;

  gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
  gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);

  return;
}

/**
 *  Wait for Y or N key stroke.
 */
BOOLEAN
PressYes ()
{
  UINTN                                WaitIndex;
  EFI_INPUT_KEY                        Key;

  while (1)
  {
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if((Key.UnicodeChar == L'Y') || (Key.UnicodeChar == L'y')) {
      return TRUE;
    } else if ((Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
      return FALSE;
    } else {
      SctPrint (L"Please press \"Y\" or \"N\"\n");
    }
  }
}

/**
 *  Convert predefined digital signature algorithm to string.
 */
CHAR16 *
AlgToStr (
  BIS_ALG_ID      AlgId
)
{
  switch (AlgId) {
  case BIS_ALG_DSA:
    return L"DSA";
    break;
  case BIS_ALG_RSA_MD5:
    return L"RSA_MD5";
    break;
  default:
    return L"Unknown";
    break;
  }
}
