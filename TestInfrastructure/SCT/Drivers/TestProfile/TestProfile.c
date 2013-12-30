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
                                                                
  Copyright (c) 2006 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  TestProfile.c

Abstract:

  Driver to publish the Test Profile Library Protocol.

--*/

#include "Efi.h"
#include "EfiTest.h"
#include "EfiDriverLib.h"
#include "TestProfile.h"
#include "TestProfileSupport.h"

//
// Prototypes
//

EFI_STATUS
TestProfileEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

EFI_STATUS
TslInitUnload (
  IN EFI_HANDLE         ImageHandle
  );

//
// Prototypes of EFI_TSL_INIT_INTERFACE
//
EFI_STATUS
EFIAPI
TslOpen (
  IN EFI_TSL_INIT_INTERFACE       *This,
  IN OUT EFI_HANDLE               *LibHandle,
  OUT VOID                        **PrivateLibInterface
  );

EFI_STATUS
EFIAPI
TslClose (
  IN EFI_TSL_INIT_INTERFACE       *This,
  IN EFI_HANDLE                   LibHandle
  );

//
// Prototypes of EFI_TEST_PROFILE_LIBRARY_PROTOCOL
//
EFI_STATUS
EFIAPI
AtslEfiIniOpen (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *RootDevPath,
  IN CHAR16                                 *FileName,
  OUT EFI_INI_FILE_HANDLE                   *FileHandle
  );

EFI_STATUS
EFIAPI
AtslEfiIniCreate (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *RootDevPath,
  IN CHAR16                                 *FileName,
  OUT EFI_INI_FILE_HANDLE                   *FileHandle
  );

EFI_STATUS
EFIAPI
AtslEfiIniClose (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  );

EFI_STATUS
EFIAPI
AtslEfiGetSystemDevicePath (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  OUT EFI_DEVICE_PATH_PROTOCOL              **DevicePath,
  OUT CHAR16                                **FilePath
  );

EFI_STATUS
EFIAPI
AtslEfiSetSystemDevicePath (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *DevicePath,
  IN CHAR16                                 *FilePath
  );

//
// Prototypes of EFI_INI_FILE interface
//
EFI_STATUS
EFIAPI
EfiIniFlush (
  IN EFI_INI_FILE_HANDLE                    This
  );

EFI_STATUS
EFIAPI
EfiIniGetString (
  IN EFI_INI_FILE_HANDLE                    This,
  IN CHAR16                                 *Section,
  IN CHAR16                                 *Entry,
  OUT CHAR16                                *String,
  IN OUT UINT32                             *MaxLength
  );

EFI_STATUS
EFIAPI
EfiIniSetString (
  IN EFI_INI_FILE_HANDLE                    This,
  IN CHAR16                                 *Section,
  IN CHAR16                                 *Entry,
  IN CHAR16                                 *String
  );
EFI_STATUS
EFIAPI
EfiIniRmSection (
  IN EFI_INI_FILE_HANDLE                    This,
  IN CHAR16                                 *Section
  );
EFI_STATUS
EFIAPI
EfiIniGetStringByOrder (
  IN EFI_INI_FILE_HANDLE                    This,
  IN UINT32                                 Order,
  IN CHAR16                                 *Section,
  IN CHAR16                                 *Entry,
  OUT CHAR16                                *String,
  IN OUT UINT32                             *MaxLength
  );

EFI_STATUS
EFIAPI
EfiIniSetStringByOrder (
  IN EFI_INI_FILE_HANDLE                    This,
  IN UINT32                                 Order,
  IN CHAR16                                 *Section,
  IN CHAR16                                 *Entry,
  IN CHAR16                                 *String
  );

EFI_STATUS
EFIAPI
EfiIniRmSectionByOrder (
  IN EFI_INI_FILE_HANDLE                    This,
  IN UINT32                                 Order,
  IN CHAR16                                 *Section
  );

EFI_STATUS
EFIAPI
EfiIniGetOrderNum (
  IN EFI_INI_FILE_HANDLE                    This,
  IN CHAR16                                 *Section,
  OUT UINT32                                *Order
  );

//
// Internal functions
//
VOID
_initFile (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile
  );

VOID
_freeIniFile (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile
  );

VOID
_freePointer (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile
  );

CHAR8 *
_alltrim (
  IN OUT CHAR8                    *ptrStr
  );

VOID
_freeItem (
  IN INI                          *ptrItem
  );

INI *
_getNextSection (
  IN INI                          *CurSection
  );

VOID
_prosessLine (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile,
  IN CHAR8                        *ptrLine,
  OUT CHAR8                       *ptrSection,
  OUT BOOLEAN                     *isSectionGot,
  OUT UINT32                      *commentNo
  );

VOID
_getcomment (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile,
  IN CHAR8                        *ptrStr,
  OUT UINT32                      *commentNo
  );

VOID
_getsection (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile,
  IN CHAR8                        *ptrStr,
  OUT CHAR8                       *ptrSection,
  OUT UINT32                      *commentNo
  );

VOID
_additem (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile,
  IN INI                          *ptrItem
  );

VOID
_getentry (
  IN CHAR8                        *ptrStr,
  IN CHAR8                        *ptrEntry,
  OUT CHAR8                       *ptrValue
  );

INI *
_searchSection (
  IN INI                          *Head,
  IN UINT32                       Order,
  OUT CHAR8                       *Section
);

VOID
_rmComment (
  IN COMMENTLINE                  **CmtHead,
  IN INI                          *ptrItem
);

CHAR16 *
TplStrDuplicate (
  IN CHAR16             *String
  );

//
// Name and Description of EFI_TEST_PROFILE_LIBRARY_PROTOCOL
//
CHAR16 *gAtslName        = L"Test Profile Library";
CHAR16 *gAtslDescription = L"EFI Test Profile Library";

//
// Entry point
//
EFI_DRIVER_ENTRY_POINT (TestProfileEntryPoint)

EFI_STATUS
TestProfileEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
/*++

Routine Description:

  Test profile library driver's entry point.

Arguments:

  ImageHandle         - the driver image handle.
  SystemTable         - the system table.

Returns:

  EFI_SUCCESS         - the driver is loaded successfully.
  EFI_ALREADY_STARTED - the driver has already been loaded before.

--*/
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  TSL_INIT_PRIVATE_DATA       *Private;

  //
  // Initialize driver lib
  //
  EfiInitializeDriverLib (ImageHandle, SystemTable);

  //
  // Fill in the Unload() function
  //
  Status = gBS->OpenProtocol (
                  ImageHandle,
                  &gEfiLoadedImageProtocolGuid,
                  (VOID **)&LoadedImage,
                  ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  LoadedImage->Unload = TslInitUnload;

  //
  // Open the TslInit protocol to perform the supported test.
  //
  Status = gBS->OpenProtocol (
                  ImageHandle,
                  &gEfiTslInitInterfaceGuid,
                  NULL,
                  ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    return EFI_ALREADY_STARTED;
  }

  //
  // Initialize the TslInit private data
  //
  Status = gBS->AllocatePool(
                  EfiBootServicesData,
                  sizeof (TSL_INIT_PRIVATE_DATA),
                  (VOID **)&Private
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EfiZeroMem (Private, sizeof(TSL_INIT_PRIVATE_DATA));
  Private->Signature            = TSL_INIT_PRIVATE_DATA_SIGNATURE;
  Private->ImageHandle          = ImageHandle;
  Private->TslInit.Revision     = 0x10000;
  Private->TslInit.LibraryGuid  = gEfiTestProfileLibraryGuid;
  Private->TslInit.Open         = TslOpen;
  Private->TslInit.Close        = TslClose;

  //
  // Install TslInit protocol
  //
  Status = gBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gEfiTslInitInterfaceGuid,
                  EFI_NATIVE_INTERFACE,
                  &(Private->TslInit)
                  );

  return Status;
}

EFI_STATUS
TslInitUnload (
  IN EFI_HANDLE         ImageHandle
  )
/*++

Routine Description:

  Unload function for the driver, uninstall TslInit protocol.

Arguments:

  ImageHandle   - the driver image handle.

Returns:

  EFI_SUCCESS   - unload successfully.

--*/
{
  EFI_STATUS              Status;
  EFI_TSL_INIT_INTERFACE  *TslInit;
  TSL_INIT_PRIVATE_DATA   *Private;

  //
  // Open the TslInit protocol
  //
  Status = gBS->OpenProtocol (
                  ImageHandle,
                  &gEfiTslInitInterfaceGuid,
                  (VOID **)&TslInit,
                  ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    //
    // Uninstall TslInit protocol
    //
    Status = gBS->UninstallProtocolInterface (
                    ImageHandle,
                    &gEfiTslInitInterfaceGuid,
                    TslInit
                    );

    Private = TSL_INIT_PRIVATE_DATA_FROM_THIS (TslInit);
    gBS->FreePool (Private);
  }

  return Status;
}

EFI_STATUS
EFIAPI
TslOpen (
  IN EFI_TSL_INIT_INTERFACE       *This,
  IN OUT EFI_HANDLE               *LibHandle,
  OUT VOID                        **PrivateLibInterface
  )
/*++

Routine Description:

  Opens the test support library to get the handle with the public interface
  and the private interface.

Arguments:

  This              - TSL Initiation Interface instance.
  LibHandle         - The pointer to the handle on which the public interface
                      is installed.
  PrivateInterface  - The private interface of the test support library.

Returns:

  EFI_SUCCESS           - open the StandardTestLibrary successfully.
  EFI_INVALID_PARAMETER - invalid parameter, LibHandle is NULL.
  EFI_ALREADY_STARTED   - the StandardTestLibrary has been bind on the LibHandle
                          before.

--*/
{
  EFI_STATUS                  Status;
  TEST_PROFILE_PRIVATE_DATA  *Private;
  TSL_INIT_PRIVATE_DATA       *TslPrivate;

  //
  // Check parameter
  //
  if (LibHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  TslPrivate = TSL_INIT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Open the TestProfileLibrary protocol to perform the supported test.
  //
  if (*LibHandle != NULL) {
    Status = gBS->OpenProtocol (
                    *LibHandle,
                    &gEfiTestProfileLibraryGuid,
                    NULL,
                    TslPrivate->ImageHandle,
                    NULL,
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                    );
    if (!EFI_ERROR (Status)) {
      return EFI_ALREADY_STARTED;
    }
  }

  //
  // Initialize the TestProfileLibrary private data
  //
  Status = gBS->AllocatePool(
                  EfiBootServicesData,
                  sizeof (TEST_PROFILE_PRIVATE_DATA),
                  (VOID **)&Private
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EfiZeroMem (Private, sizeof(TEST_PROFILE_PRIVATE_DATA));
  Private->Signature                        = TEST_PROFILE_PRIVATE_DATA_SIGNATURE;
  Private->TestProfile.LibraryRevision     = 0x10000;
  Private->TestProfile.Name                = gAtslName;
  Private->TestProfile.Description         = gAtslDescription;
  Private->TestProfile.EfiIniOpen          = AtslEfiIniOpen;
  Private->TestProfile.EfiIniCreate        = AtslEfiIniCreate;
  Private->TestProfile.EfiIniClose         = AtslEfiIniClose;
  Private->TestProfile.EfiGetSystemDevicePath    = AtslEfiGetSystemDevicePath;
  Private->TestProfile.EfiSetSystemDevicePath    = AtslEfiSetSystemDevicePath;

  if (PrivateLibInterface != NULL) {
    //
    // currently there is no private interface
    //
    *PrivateLibInterface = NULL;
  }

  //
  // Install TestProfileLibrary protocol
  //
  Status = gBS->InstallProtocolInterface (
                  LibHandle,
                  &gEfiTestProfileLibraryGuid,
                  EFI_NATIVE_INTERFACE,
                  &(Private->TestProfile)
                  );

  return Status;
}

EFI_STATUS
EFIAPI
TslClose (
  IN EFI_TSL_INIT_INTERFACE       *This,
  IN EFI_HANDLE                   LibHandle
  )
/*++

Routine Description:

  Closes the test support library to free the public interface.

Arguments:

  This              - TSL Initiation Interface instance.
  LibHandle         - The handle on which the public interface was installed.

Returns:

  EFI_SUCCESS   - close the TestProfileLibrary successfully.

--*/
{
  EFI_STATUS                          Status;
  TEST_PROFILE_PRIVATE_DATA          *Private;
  TSL_INIT_PRIVATE_DATA               *TslPrivate;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *TestProfile;

  TslPrivate = TSL_INIT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Open the TestProfileLibrary protocol to perform the supported test.
  //
  Status = gBS->OpenProtocol (
                  LibHandle,
                  &gEfiTestProfileLibraryGuid,
                  (VOID **)&TestProfile,
                  TslPrivate->ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Uninstall TestProfileLibrary protocol
  //
  Status = gBS->UninstallProtocolInterface (
                  LibHandle,
                  &gEfiTestProfileLibraryGuid,
                  TestProfile
                  );
  Private = TEST_PROFILE_PRIVATE_DATA_FROM_THIS (TestProfile);
  gBS->FreePool (Private);

  return Status;
}

EFI_STATUS
EFIAPI
AtslEfiIniOpen (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *RootDevPath,
  IN CHAR16                                 *FileName,
  OUT EFI_INI_FILE_HANDLE                   *FileHandle
  )
/*++

Routine Description:

  One interface function of the TestProfileLibrary to open an ini file.

Arguments:

  This                  - the protocol instance structure.
  RootDevPath           - root device path of the ini file.
  FileName              - Unicode file name of the ini file relative to the
                          RootDevPath.
  FileHandle            - return the opened handle of the ini file.

Returns:

  EFI_SUCCESS           - open the ini file successfully.
  EFI_INVALID_PARAMETER - invalid parameters.
  EFI_OUT_OF_RESOURCES  - not enough memory.

--*/
{
  EFI_STATUS                        Status;
  EFI_INI_FILE_PRIVATE_DATA         *NewIniFile;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  UINTN                             Index;
  UINTN                             Number;
  UINTN                             BufSize;
  CHAR8                             ptrLine[MAX_LINE_LEN] ;
  UINT8                             Buffer[MAX_LINE_LEN * 2];
  CHAR8                             ptrSection[MAX_STRING_LEN + 1] ;
  UINT32                            commentNo ;
  BOOLEAN                           isSectionGot ;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;

  //
  // Check the parameters
  //
  if ((RootDevPath == NULL) || (FileName == NULL) || (FileHandle == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsLen (FileName) > MAX_STRING_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // New and initialize a ini file
  //
  NewIniFile = Malloc (sizeof(EFI_INI_FILE_PRIVATE_DATA));
  if (NewIniFile == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  _initFile (NewIniFile);

  NewIniFile->FileName = WcsDup (FileName);
  if ( NewIniFile->FileName == NULL ) {
    _freeIniFile (NewIniFile);
    return EFI_OUT_OF_RESOURCES;
  }

  NewIniFile->DevPath = EfiDuplicateDevicePath (RootDevPath);
  if ( NewIniFile->DevPath == NULL ) {
    _freeIniFile (NewIniFile);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // current section name is null
  //
  ptrSection[0] = '\0';

  //
  // section not found
  //
  isSectionGot = FALSE;

  //
  // current comment number :
  // every comment line's comment number is the same as the comment number of
  // the first non comment line after this comment line.
  //
  commentNo = 1;

  //
  //  Determine device handle for fs protocol on specified device path
  //
  Status = gBS->LocateDevicePath (
                  &gEfiSimpleFileSystemProtocolGuid,
                  &RootDevPath,
                  &DeviceHandle
                  );
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    return Status;
  }

  //
  //  Determine volume for file system on device handle
  //
  Status = gBS->HandleProtocol (
                  DeviceHandle,
                  &gEfiSimpleFileSystemProtocolGuid,
                  (VOID*)&Vol
                  );
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    return Status;
  }

  //
  // Open volume for file system on device path
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    return Status;
  }

  //
  // Open profile for read
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    RootDir->Close (RootDir);
    return Status;
  }

  //
  // Determine the file type: unicode or ansi
  //
  BufSize = MAX_LINE_LEN * 2;
  Status = Handle->Read (Handle, &BufSize, Buffer);
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    Handle->Close (Handle);
    RootDir->Close (RootDir);
    return Status;
  }

  if ((BufSize >= 2) && (Buffer[0] == 0xff) && (Buffer[1] == 0xfe)) {
    NewIniFile->isUnicode = TRUE;
    Number = 2;
  } else {
    Number = 0;
  }
  Index = 0;

  //
  // process the profile line by line
  //
  while (BufSize != 0) {
    while (Number < BufSize) {
      ptrLine[Index++] = Buffer[Number];
      if ((Buffer[Number] == '\n') || (Index >= MAX_LINE_LEN - 1)) {
        //
        // a line is read, process it
        //
        ptrLine[Index] = '\0';
        Index = 0;
        _prosessLine (
          NewIniFile,
          ptrLine,
          ptrSection,
          &isSectionGot,
          &commentNo
        );
      }

      if (NewIniFile->isUnicode) {
        Number += 2;
      } else {
        Number ++;
      }
    }

    Number = 0;
    BufSize = MAX_LINE_LEN * 2;
    Status = Handle->Read (Handle, &BufSize, Buffer);
    if (EFI_ERROR (Status)) {
      _freeIniFile (NewIniFile);
      Handle->Close (Handle);
      RootDir->Close (RootDir);
      return Status;
    }
  }

  //
  // process the last line without '\n'
  //
  ptrLine[Index] = '\0';
  Index = 0;
  _prosessLine (
    NewIniFile,
    ptrLine,
    ptrSection,
    &isSectionGot,
    &commentNo
  );

  //
  // close the profile, and return file handle
  //
  Handle->Close (Handle);
  RootDir->Close (RootDir);
  *FileHandle = &(NewIniFile->Handle);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AtslEfiIniCreate (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *RootDevPath,
  IN CHAR16                                 *FileName,
  OUT EFI_INI_FILE_HANDLE                   *FileHandle
  )
/*++

Routine Description:

  One interface function of the TestProfileLibrary to create an ini file.

Arguments:

  This                  - the protocol instance structure.
  RootDevPath           - root device path of the ini file.
  FileName              - Unicode file name of the ini file relative to the
                          RootDevPath.
  FileHandle            - return the created handle of the ini file.

Returns:

  EFI_SUCCESS           - create the ini file successfully.
  EFI_INVALID_PARAMETER - invalid parameters.
  EFI_OUT_OF_RESOURCES  - not enough memory.

--*/
{
  EFI_STATUS                        Status;
  EFI_INI_FILE_PRIVATE_DATA         *NewIniFile;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  UINTN                             BufSize;
  UINT8                             Buffer[2];
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;

  //
  // Check the parameters
  //
  if ((RootDevPath == NULL) || (FileName == NULL) || (FileHandle == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsLen (FileName) > MAX_STRING_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // New and initialize a ini file
  //
  NewIniFile = Malloc (sizeof(EFI_INI_FILE_PRIVATE_DATA));
  if (NewIniFile == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  _initFile (NewIniFile);

  NewIniFile->FileName = WcsDup (FileName);
  if ( NewIniFile->FileName == NULL ) {
    _freeIniFile (NewIniFile);
    return EFI_OUT_OF_RESOURCES;
  }

  NewIniFile->DevPath = EfiDuplicateDevicePath (RootDevPath);
  if ( NewIniFile->DevPath == NULL ) {
    _freeIniFile (NewIniFile);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //  Determine device handle for fs protocol on specified device path
  //
  Status = gBS->LocateDevicePath (
                  &gEfiSimpleFileSystemProtocolGuid,
                  &RootDevPath,
                  &DeviceHandle
                  );
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    return Status;
  }

  //
  //  Determine volume for file system on device handle
  //
  Status = gBS->HandleProtocol (
                  DeviceHandle,
                  &gEfiSimpleFileSystemProtocolGuid,
                  (VOID*)&Vol
                  );
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    return Status;
  }

  //
  // Open volume for file system on device path
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    return Status;
  }

  //
  // Open profile to test the existence
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ,
                      0
                      );
  if (Status != EFI_NOT_FOUND) {
    _freeIniFile (NewIniFile);
    RootDir->Close (RootDir);
    return EFI_ACCESS_DENIED;
  }

  //
  // New profile
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_CREATE|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    RootDir->Close (RootDir);
    return Status;
  }

  NewIniFile->isUnicode = TRUE;
  Buffer[0] = 0xff;
  Buffer[1] = 0xfe;
  BufSize = 2;
  Status = Handle->Write (Handle, &BufSize, Buffer);
  if (EFI_ERROR (Status)) {
    _freeIniFile (NewIniFile);
    Handle->Close (Handle);
    RootDir->Close (RootDir);
    return Status;
  }

  //
  // close the profile, and return file handle
  //
  Handle->Close (Handle);
  RootDir->Close (RootDir);
  *FileHandle = &(NewIniFile->Handle);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AtslEfiIniClose (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  )
/*++

Routine Description:

  One interface function of the TestProfileLibrary to close an ini file.

Arguments:

  This        - the protocol instance structure.
  FileHandle  - ini file to be closed.

Returns:

  EFI_SUCCESS - the ini file was closed successfully.

--*/
{
  EFI_STATUS                      Status;
  EFI_INI_FILE_PRIVATE_DATA       *IniFile;

  IniFile = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (FileHandle);

  Status = FileHandle->Flush (FileHandle);
  _freeIniFile (IniFile);
  return Status;
}

EFI_STATUS
EFIAPI
AtslEfiGetSystemDevicePath (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  OUT EFI_DEVICE_PATH_PROTOCOL              **DevicePath,
  OUT CHAR16                                **FilePath
  )
/*++

Routine Description:

  One interface function of the TestProfileLibrary to get system device path and
  file path.

Arguments:

  This        - the protocol instance structure.
  DevicePath  - the device path of this framework.
  FilePath    - the file path of this framework.

Returns:

  EFI_SUCCESS - get the device path and file path successfully.

--*/
{
  TEST_PROFILE_PRIVATE_DATA      *Private;

  Private = TEST_PROFILE_PRIVATE_DATA_FROM_THIS (This);

  if ((DevicePath == NULL) || (FilePath == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get system device path
  //
  *DevicePath = EfiDuplicateDevicePath (Private->DevicePath);
  if (*DevicePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Get system file path
  //
  *FilePath = TplStrDuplicate (Private->FilePath);
  if (*FilePath == NULL) {
    gBS->FreePool (*DevicePath);
    *DevicePath = NULL;
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AtslEfiSetSystemDevicePath (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *DevicePath,
  IN CHAR16                                 *FilePath
  )
/*++

Routine Description:

  One interface function of the TestProfileLibrary to set system device path and
  file path.

Arguments:

  This        - the protocol instance structure.
  DevicePath  - the device path of this framework.
  FilePath    - the file path of this framework.

Returns:

  EFI_SUCCESS - set the device path and file path successfully.

--*/
{
  TEST_PROFILE_PRIVATE_DATA      *Private;

  Private = TEST_PROFILE_PRIVATE_DATA_FROM_THIS (This);

  if ((DevicePath == NULL) || (FilePath == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Set system device path
  //
  Private->DevicePath = DevicePath;

  //
  // Set system file path
  //
  Private->FilePath = FilePath;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiIniFlush (
  IN EFI_INI_FILE_HANDLE                    This
  )
/*++

Routine Description:

  One interface function of the EFI_INI_FILE to flush an ini file.

Arguments:

  This        - the interface instance structure.

Returns:

  EFI_SUCCESS - the ini file was written to the disk successfully.

--*/
{
  INI                     *ptrCur;
  COMMENTLINE             *ptrCmtCur;
  CHAR8                   ptrCurSection[MAX_STRING_LEN + 1];
  BOOLEAN                 first;
  UINT32                  commentNo;

  EFI_STATUS              Status;
  EFI_HANDLE              DeviceHandle;
  EFI_FILE_HANDLE         RootDir;
  EFI_FILE_HANDLE         Handle;
  UINTN                   BufSize;
  CHAR8                   Buffer[MAX_LINE_LEN];
  CHAR8                   Line[MAX_LINE_LEN * 2];

  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *Vol;
  EFI_DEVICE_PATH_PROTOCOL         *RootDevPath;
  EFI_INI_FILE_PRIVATE_DATA        *Private;

  Private = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (This);

  commentNo = 0;

  //
  // File not modified, needn't to write back to the disk
  //
  if (!Private->Modified) {
    return EFI_SUCCESS;
  }

  RootDevPath = Private->DevPath;
  //
  //  Determine device handle for fs protocol on specified device path
  //
  Status = gBS->LocateDevicePath (
                  &gEfiSimpleFileSystemProtocolGuid,
                  &RootDevPath,
                  &DeviceHandle
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  //  Determine volume for file system on device handle
  //
  Status = gBS->HandleProtocol (
                  DeviceHandle,
                  &gEfiSimpleFileSystemProtocolGuid,
                  (VOID*)&Vol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open volume for file system on device path
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // open and delete the file before write
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      Private->FileName,
                      EFI_FILE_MODE_CREATE|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR (Status)) {
    RootDir->Close (RootDir);
    return Status;
  }

  Status = Handle->Delete (Handle);
  //
  // EFI_FILE.Delete() return a warning status
  //
  if (Status != EFI_SUCCESS) {
    RootDir->Close (RootDir);
    return EFI_UNSUPPORTED;
  }

  //
  // reopen the file to write
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      Private->FileName,
                      EFI_FILE_MODE_CREATE|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR (Status)) {
    RootDir->Close (RootDir);
    return Status;
  }

  ptrCur = Private->Head ;
  StrCpy (ptrCurSection, "");
  first = TRUE;

  //
  // write file head
  //
  if (Private->isUnicode) {
    Buffer[0] = 0xff;
    Buffer[1] = 0xfe;
    BufSize = 2;
    Status = Handle->Write (Handle, &BufSize, Buffer);
    if (EFI_ERROR (Status)) {
      Handle->Close (Handle);
      RootDir->Close (RootDir);
      return Status;
    }
  }

  //
  // write file line by line
  //
  while (ptrCur != NULL) {
    if (*(ptrCur->ptrEntry) == '\0') {
      //
      // New section encountered
      // If it's not the first section, add a blank line
      //
      if (first) {
        first = FALSE;
      } else {
        StrCpy (Buffer, "\r\n");
        BufSize = StrLen (Buffer);
        if (Private->isUnicode) {
          MbsToWcs ((CHAR16 *)Line, Buffer, BufSize + 1);
          BufSize *= 2;
          Status = Handle->Write (Handle, &BufSize, Line);
        } else {
          Status = Handle->Write (Handle, &BufSize, Buffer);
        }
        if (EFI_ERROR (Status)) {
          Handle->Close (Handle);
          RootDir->Close (RootDir);
          return Status;
        }
      }
    }

    //
    //  If there are comment lines before this line, write comment lines first
    //
    ptrCmtCur = Private->CommentLineHead;
    while (ptrCmtCur != NULL) {
      if (ptrCmtCur->commentNo == ptrCur->commentNo) {
        commentNo = ptrCmtCur->commentNo;
        StrCpy (Buffer, ptrCmtCur->ptrComment);
        StrCat (Buffer, "\r\n");
        BufSize = StrLen (Buffer);
        if (Private->isUnicode) {
          MbsToWcs ((CHAR16 *)Line, Buffer, BufSize + 1);
          BufSize *= 2;
          Status = Handle->Write (Handle, &BufSize, Line);
        } else {
          Status = Handle->Write (Handle, &BufSize, Buffer);
        }
        if (EFI_ERROR (Status)) {
          Handle->Close (Handle);
          RootDir->Close (RootDir);
          return Status;
        }
      }
      ptrCmtCur = ptrCmtCur->ptrNext ;
    }

    if (*(ptrCur->ptrEntry) == '\0') {
      //
      // new section, write the section head
      //
      StrCpy (ptrCurSection, ptrCur->ptrSection);
      StrCpy (Buffer, "[");
      StrCat (Buffer, ptrCurSection);
      StrCat (Buffer, "]\r\n");
      BufSize = StrLen (Buffer);
      if (Private->isUnicode) {
        MbsToWcs ((CHAR16 *)Line, Buffer, BufSize + 1);
        BufSize *= 2;
        Status = Handle->Write (Handle, &BufSize, Line);
      } else {
        Status = Handle->Write (Handle, &BufSize, Buffer);
      }
      if (EFI_ERROR (Status)) {
        Handle->Close (Handle);
        RootDir->Close (RootDir);
        return Status;
      }
    } else {
      //
      // write the entry and value line
      //
      StrCpy (Buffer, ptrCur->ptrEntry);
      StrCat (Buffer, "=");
      StrCat (Buffer, ptrCur->ptrValue);
      StrCat (Buffer, "\r\n");
      BufSize = StrLen (Buffer);
      if (Private->isUnicode) {
        MbsToWcs ((CHAR16 *)Line, Buffer, BufSize + 1);
        BufSize *= 2;
        Status = Handle->Write (Handle, &BufSize, Line);
      } else {
        Status = Handle->Write (Handle, &BufSize, Buffer);
      }
      if (EFI_ERROR (Status)) {
        Handle->Close (Handle);
        RootDir->Close (RootDir);
        return Status;
      }
    }

    ptrCur = ptrCur->ptrNext;
  }

  //
  //  If there are comment lines in the end of the file, write these comment lines
  //
  ptrCmtCur = Private->CommentLineHead;
  commentNo ++;
  while (ptrCmtCur != NULL) {
    if (ptrCmtCur->commentNo >= commentNo) {
      StrCpy (Buffer, ptrCmtCur->ptrComment);
      StrCat (Buffer, "\r\n");
      BufSize = StrLen (Buffer);
      if (Private->isUnicode) {
        MbsToWcs ((CHAR16 *)Line, Buffer, BufSize + 1);
        BufSize *= 2;
        Status = Handle->Write (Handle, &BufSize, Line);
      } else {
        Status = Handle->Write (Handle, &BufSize, Buffer);
      }
      if (EFI_ERROR (Status)) {
        Handle->Close (Handle);
        RootDir->Close (RootDir);
        return Status;
      }
    }
    ptrCmtCur = ptrCmtCur->ptrNext;
  }

  Handle->Flush (Handle);
  Handle->Close (Handle);
  RootDir->Close (RootDir);
  Private->Modified = FALSE;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiIniGetString (
  IN EFI_INI_FILE_HANDLE                    This,
  IN CHAR16                                 *Section,
  IN CHAR16                                 *Entry,
  OUT CHAR16                                *String,
  IN OUT UINT32                             *maxLength
  )
/*++

Routine Description:

  One interface function of the EFI_INI_FILE to get a string.

Arguments:

  This            - the interface instance structure.
  Section         - Unicode section name.
  Entry           - Unicode entry name.
  String          - Unicode string to be returned.
  maxLength       - On input, the size in bytes of String. On output,
                    the size, in bytes, of the String needed to obtain
                    the value (if the String was not large enough).

Returns:

  EFI_SUCCESS           - get string successfully.
  EFI_NOT_FOUND         - Entry not found.
  EFI_BUFFER_TOO_SMALL  - the maxLength is too small for the result.
                          maxLength has been updated with the size needed
                          to complete the request.
  EFI_INVALID_PARAMETER - invalid parameters.

--*/
{
  CHAR8   ptrSection[MAX_STRING_LEN + 1];
  CHAR8   ptrEntry[MAX_STRING_LEN + 1];
  CHAR8   ptrString[MAX_STRING_LEN + 1];
  INI     *ptrCur;

  CHAR8   tmpSection[MAX_STRING_LEN + 1];
  CHAR8   tmpEntry[MAX_STRING_LEN + 1];

  EFI_INI_FILE_PRIVATE_DATA       *Private;

  //
  // check the parameter
  //
  if (Section == NULL || Entry == NULL || String == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  WcsCpy (String, L"");

  if (WcsLen (Section) > MAX_STRING_LEN || WcsLen(Entry) > MAX_STRING_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrSection, Section, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrEntry, Entry, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  StrCpy (tmpSection, ptrSection);
  _alltrim (tmpSection);

  StrCpy (tmpEntry, ptrEntry);
  _alltrim (tmpEntry);

  if (StrLen (tmpSection) == 0 || StrLen (tmpEntry) == 0) {
    return EFI_INVALID_PARAMETER;
  }

  Private = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (This);

  //
  // file content are in memory
  // so to find the field
  //

  ptrCur = Private->Head;

  while (ptrCur != NULL) {
    //
    // the same, so find the field
    //
    if ((StriCmp (tmpSection, ptrCur->ptrSection) == 0) &&
        (StriCmp (tmpEntry, ptrCur->ptrEntry)     == 0)) {
      if (StrLen (ptrCur->ptrValue) < *maxLength) {
        StrCpy (ptrString, ptrCur->ptrValue);
        MbsToWcs (String, ptrString, StrLen(ptrString) + 1);
        return EFI_SUCCESS;
      } else {
        StrnCpy (ptrString, ptrCur->ptrValue, *maxLength - 1);
        ptrString[*maxLength-1] = '\0';
        MbsToWcs (String, ptrString, StrLen(ptrString) + 1);
        *maxLength = (UINT32) (StrLen (ptrCur->ptrValue) + 1);
        return EFI_BUFFER_TOO_SMALL;
      }
    }

    ptrCur = ptrCur->ptrNext;
  }

  return EFI_NOT_FOUND;
}

EFI_STATUS
EFIAPI
EfiIniSetString (
  IN EFI_INI_FILE_HANDLE                    This,
  IN CHAR16                                 *Section,
  IN CHAR16                                 *Entry,
  IN CHAR16                                 *String
  )
/*++

Routine Description:

  One interface function of the EFI_INI_FILE to set a string.

Arguments:

  This        - the interface instance structure.
  Section     - Unicode section name.
  Entry       - Unicode entry name.
  String      - Unicode string to be set.

Returns:

  EFI_SUCCESS           - set string successfully.
  EFI_INVALID_PARAMETER - invalid parameters.
  EFI_OUT_OF_RESOURCES  - not enough memory.

--*/
{
  CHAR8   ptrSection[MAX_STRING_LEN + 1];
  CHAR8   ptrEntry[MAX_STRING_LEN + 1];
  CHAR8   ptrString[MAX_STRING_LEN + 1];

  INI     *ptrCur;
  INI     *ptrPrev;
  INI     *ptrNew;

  CHAR8   tmpSection[MAX_STRING_LEN + 1];
  CHAR8   tmpEntry[MAX_STRING_LEN + 1];
  CHAR8   tmpString[MAX_STRING_LEN + 1];
  CHAR8   *tmpPtr;

  EFI_INI_FILE_PRIVATE_DATA   *Private;

  Private = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (This);

  //
  // check the parameter
  //
  if (Section == NULL || Entry == NULL || String == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsLen (Section) > MAX_STRING_LEN ||
      WcsLen (Entry)   > MAX_STRING_LEN ||
      WcsLen (String)  > MAX_STRING_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrSection, Section, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrEntry, Entry, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  StrCpy (tmpSection, ptrSection);
  _alltrim (tmpSection);

  StrCpy (tmpEntry, ptrEntry);
  _alltrim (tmpEntry);

  if (StrLen (tmpSection) == 0 || StrLen (tmpEntry) == 0) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrString, String, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  StrCpy (tmpString, ptrString);
  _alltrim (tmpString);

  //
  // if both section and entry are found
  //
  ptrCur = Private->Head;
  ptrPrev = NULL;
  while (ptrCur != NULL) {
    if (StriCmp (tmpSection, ptrCur->ptrSection) == 0) {
      if (StriCmp (tmpEntry, ptrCur->ptrEntry) == 0) {
        if (StriCmp (tmpString, ptrCur->ptrValue) != 0) {
          tmpPtr = StrDup (tmpString);
          if (tmpPtr == NULL) {
            return EFI_OUT_OF_RESOURCES;
          }
          Free (ptrCur->ptrValue);
          ptrCur->ptrValue = tmpPtr;
          Private->Modified = TRUE;
        }
        return EFI_SUCCESS;
      }
      ptrPrev = ptrCur;
    }
    ptrCur = ptrCur->ptrNext;
  }

  //
  // if not, should add a new item
  //
  ptrNew = (INI *) Malloc (sizeof(INI));
  MemSet (ptrNew, 0, sizeof(INI));
  if (ptrNew == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrSection = StrDup (tmpSection);
  if (ptrNew->ptrSection == NULL) {
    _freeItem (ptrNew);
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrEntry = StrDup (tmpEntry);
  if (ptrNew->ptrEntry == NULL) {
    _freeItem (ptrNew);
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrValue = StrDup (tmpString);
  if (ptrNew->ptrValue == NULL) {
    _freeItem (ptrNew) ;
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // 1. if only section is found
  //
  if (ptrPrev != NULL) {
    ptrNew->commentNo = 0;
    ptrNew->ptrNext   = ptrPrev->ptrNext;
    ptrPrev->ptrNext  = ptrNew;
    if (Private->Tail == ptrPrev) {
      Private->Tail = ptrNew;
    }
    Private->Modified = TRUE;
    return EFI_SUCCESS;
  }

  //
  // 2. if section is not found, should add a new section head
  //
  ptrCur = ptrNew;

  ptrNew = (INI *) Malloc (sizeof(INI));
  MemSet (ptrNew, 0, sizeof(INI));
  if (ptrNew == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrSection = StrDup (tmpSection);
  if (ptrNew->ptrSection == NULL) {
    _freeItem (ptrNew);
    _freeItem (ptrCur);
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrEntry = StrDup ("");
  if (ptrNew->ptrEntry == NULL) {
    _freeItem (ptrNew);
    _freeItem (ptrCur);
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrValue = StrDup ("");
  if (ptrNew->ptrValue == NULL) {
    _freeItem (ptrNew);
    _freeItem (ptrCur);
    return EFI_OUT_OF_RESOURCES;
  }

  ptrCur->commentNo = 0;
  ptrCur->ptrNext   = NULL;
  ptrNew->commentNo = 0;
  ptrNew->ptrNext   = ptrCur;
  if (Private->Tail != NULL) {
    Private->Tail->ptrNext = ptrNew;
  } else {
    Private->Head = ptrNew;
  }
  Private->Tail = ptrCur;

  Private->Modified = TRUE;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiIniRmSection (
  IN EFI_INI_FILE_HANDLE                    This,
  IN CHAR16                                 *Section
  )
/*++

Routine Description:

  One interface function of the EFI_INI_FILE to remove sections.

Arguments:

  This        - the interface instance structure.
  Section     - Unicode section name.

Returns:

  EFI_SUCCESS           - remove section successfully.
  EFI_INVALID_PARAMETER - invalid parameters.
  EFI_NOT_FOUND         - section not found.

--*/
{
  INI                             *ptrCur;
  INI                             *ptrPrev;
  INI                             *ptrNext;
  EFI_INI_FILE_PRIVATE_DATA       *Private;
  CHAR8                           ptrSection[MAX_STRING_LEN + 1];
  CHAR8                           tmpSection[MAX_STRING_LEN + 1];

  Private = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (This);

  if (Section == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrSection, Section, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }
  StrCpy (tmpSection, ptrSection);
  _alltrim (tmpSection);

  ptrCur = Private->Head;
  ptrPrev = NULL;
  while (ptrCur != NULL) {
    if (StriCmp (tmpSection, ptrCur->ptrSection) == 0) {
      Private->Modified = TRUE;
      _rmComment (&(Private->CommentLineHead), ptrCur);
      ptrNext = ptrCur->ptrNext;
      _freeItem (ptrCur);
      if (ptrPrev == NULL) {
        Private->Head = ptrNext;
      } else {
        ptrPrev->ptrNext = ptrNext;
      }
      if (ptrNext == NULL) {
        Private->Tail = ptrPrev;
      }
      ptrCur = ptrNext;
    } else {
      ptrPrev = ptrCur;
      ptrCur = ptrCur->ptrNext;
    }
  }

  if (Private->Modified) {
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_FOUND;
  }
}

EFI_STATUS
EFIAPI
EfiIniGetStringByOrder (
  IN EFI_INI_FILE_HANDLE                    This,
  IN UINT32                                 Order,
  IN CHAR16                                 *Section,
  IN CHAR16                                 *Entry,
  OUT CHAR16                                *String,
  IN OUT UINT32                             *maxLength
  )
/*++

Routine Description:

  One interface function of the EFI_INI_FILE to get a string by section order.

Arguments:

  This      - the interface instance structure.
  Order     - the section's order.
  Section   - Unicode section name.
  Entry     - Unicode entry name.
  String    - Unicode string to be returned.
  maxLength - on input, the size in bytes of String. On output,
              the size, in bytes, of the String needed to obtain
              the value (if the String was not large enough).

Returns:

  EFI_SUCCESS           - get string successfully.
  EFI_NOT_FOUND         - Entry not found.
  EFI_BUFFER_TOO_SMALL  - the maxLength is too small for the result.
                          maxLength has been updated with the size needed
                          to complete the request.
  EFI_INVALID_PARAMETER - invalid parameters.

--*/
{
  CHAR8 ptrSection[MAX_STRING_LEN + 1];
  CHAR8 ptrEntry[MAX_STRING_LEN + 1];
  CHAR8 ptrString[MAX_STRING_LEN + 1];
  INI   *ptrCur;

  CHAR8 tmpSection[MAX_STRING_LEN + 1];
  CHAR8 tmpEntry[MAX_STRING_LEN + 1];

  EFI_INI_FILE_PRIVATE_DATA       *Private;

  //
  // check the parameter
  //
  if (Section == NULL || Entry == NULL || String == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  WcsCpy (String, L"");

  if (WcsLen (Section) > MAX_STRING_LEN || WcsLen (Entry) > MAX_STRING_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrSection, Section, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrEntry, Entry, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  StrCpy (tmpSection, ptrSection);
  _alltrim (tmpSection);

  StrCpy (tmpEntry, ptrEntry);
  _alltrim (tmpEntry);

  if (StrLen (tmpSection) == 0 || StrLen (tmpEntry) == 0) {
    return EFI_INVALID_PARAMETER;
  }

  Private = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (This);

  //
  // file content are in memory
  // so to find the field
  //

  // find the section first
  ptrCur = _searchSection (Private->Head, Order, tmpSection);

  if (ptrCur != NULL) {
    ptrCur = ptrCur->ptrNext;
  }

  while (ptrCur != NULL) {
    if (*(ptrCur->ptrEntry) == '\0') {
      //
      // reached another section
      //
      break;
    }
    if ((StriCmp (tmpSection, ptrCur->ptrSection) == 0) &&
        (StriCmp (tmpEntry, ptrCur->ptrEntry)     == 0)) {
      if (StrLen (ptrCur->ptrValue) < *maxLength) {
        StrCpy (ptrString, ptrCur->ptrValue);
        MbsToWcs (String, ptrString, StrLen(ptrString) + 1);
        return EFI_SUCCESS;
      } else {
        StrnCpy (ptrString, ptrCur->ptrValue, *maxLength - 1);
        ptrString[*maxLength-1] = '\0';
        MbsToWcs (String, ptrString, StrLen(ptrString) + 1 );
        *maxLength = (UINT32) (StrLen (ptrCur->ptrValue) + 1);
        return EFI_BUFFER_TOO_SMALL;
      }
    }

    ptrCur = ptrCur->ptrNext;
  }  // endof while

  return EFI_NOT_FOUND;
}

EFI_STATUS
EFIAPI
EfiIniSetStringByOrder (
  IN EFI_INI_FILE_HANDLE                    This,
  IN UINT32                                 Order,
  IN CHAR16                                 *Section,
  IN CHAR16                                 *Entry,
  IN CHAR16                                 *String
  )
/*++

Routine Description:

  One interface function of the EFI_INI_FILE to set a string by section order.

Arguments:

  This        - the interface instance structure.
  Order       - the section's order.
  Section     - Unicode section name.
  Entry       - Unicode entry name.
  String      - Unicode string to be set.

Returns:

  EFI_SUCCESS           - set string successfully.
  EFI_INVALID_PARAMETER - invalid parameters.
  EFI_OUT_OF_RESOURCES  - not enough memory.

--*/
{
  CHAR8 ptrSection[MAX_STRING_LEN + 1];
  CHAR8 ptrEntry[MAX_STRING_LEN + 1];
  CHAR8 ptrString[MAX_STRING_LEN + 1];

  INI   *ptrCur;
  INI   *ptrPrev;
  INI   *ptrNew;

  CHAR8 tmpSection[MAX_STRING_LEN + 1];
  CHAR8 tmpEntry[MAX_STRING_LEN + 1];
  CHAR8 tmpString[MAX_STRING_LEN + 1];
  CHAR8 *tmpPtr;

  EFI_INI_FILE_PRIVATE_DATA        *Private;

  Private = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (This);

  //
  // check the parameter
  //
  if (Section == NULL || Entry == NULL || String == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsLen (Section) > MAX_STRING_LEN ||
      WcsLen (Entry)   > MAX_STRING_LEN ||
      WcsLen (String)  > MAX_STRING_LEN) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrSection, Section, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrEntry, Entry, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  StrCpy (tmpSection, ptrSection);
  _alltrim (tmpSection);

  StrCpy (tmpEntry, ptrEntry);
  _alltrim (tmpEntry);

  if (StrLen (tmpSection) == 0 || StrLen (tmpEntry) == 0) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrString, String, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  StrCpy (tmpString, ptrString);
  _alltrim (tmpString);

  //
  // if both section and entry are found
  //
  ptrCur = _searchSection (Private->Head, Order, tmpSection);
  ptrPrev = ptrCur;
  if (ptrCur != NULL) {
    ptrCur = ptrCur->ptrNext;
  }
  while (ptrCur != NULL) {
    if (*(ptrCur->ptrEntry) == '\0') {
      //
      // reached another section
      //
      break;
    }
    if ((StriCmp (tmpSection, ptrCur->ptrSection ) == 0) &&
        (StriCmp (tmpEntry, ptrCur->ptrEntry )     == 0)) {
      if (StriCmp( tmpString, ptrCur->ptrValue) != 0) {
        tmpPtr = StrDup (tmpString);
        if (tmpPtr == NULL) {
          return EFI_OUT_OF_RESOURCES;
        }
        Free (ptrCur->ptrValue);
        ptrCur->ptrValue = tmpPtr;
        Private->Modified = TRUE;
      }
      return EFI_SUCCESS;
    }
    ptrPrev = ptrCur;
    ptrCur = ptrCur->ptrNext;
  }

  //
  // if not, should add a new item
  //
  ptrNew = (INI *) Malloc(sizeof(INI));
  MemSet (ptrNew, 0, sizeof(INI));
  if (ptrNew == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrSection = StrDup (tmpSection);
  if (ptrNew->ptrSection == NULL) {
    _freeItem (ptrNew);
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrEntry = StrDup (tmpEntry);
  if (ptrNew->ptrEntry == NULL) {
    _freeItem (ptrNew);
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrValue = StrDup (tmpString);
  if (ptrNew->ptrValue == NULL) {
    _freeItem (ptrNew);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // 1. if only section is found
  //
  if (ptrPrev != NULL) {
    ptrNew->commentNo = 0;
    ptrNew->ptrNext = ptrPrev->ptrNext;
    ptrPrev->ptrNext = ptrNew;
    if (Private->Tail == ptrPrev) {
      Private->Tail = ptrNew;
    }
    Private->Modified = TRUE;
    return EFI_SUCCESS;
  }

  //
  // 2. if section is not found, should add a new section head
  //
  ptrCur = ptrNew;

  ptrNew = (INI *)Malloc (sizeof(INI));
  MemSet (ptrNew, 0, sizeof(INI));
  if (ptrNew == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrSection = StrDup (tmpSection);
  if ( ptrNew->ptrSection == NULL ) {
    _freeItem (ptrNew);
    _freeItem (ptrCur);
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrEntry = StrDup ("");
  if ( ptrNew->ptrEntry == NULL ) {
    _freeItem (ptrNew);
    _freeItem (ptrCur);
    return EFI_OUT_OF_RESOURCES;
  }
  ptrNew->ptrValue = StrDup ("");
  if ( ptrNew->ptrValue == NULL ) {
    _freeItem (ptrNew);
    _freeItem (ptrCur);
    return EFI_OUT_OF_RESOURCES;
  }

  ptrCur->commentNo = 0;
  ptrCur->ptrNext   = NULL;
  ptrNew->commentNo = 0;
  ptrNew->ptrNext   = ptrCur;
  if (Private->Tail != NULL) {
    Private->Tail->ptrNext = ptrNew;
  } else {
    Private->Head = ptrNew;
  }
  Private->Tail = ptrCur;

  Private->Modified = TRUE;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiIniRmSectionByOrder (
  IN EFI_INI_FILE_HANDLE                    This,
  IN UINT32                                 Order,
  IN CHAR16                                 *Section
  )
/*++

Routine Description:

  One interface function of the EFI_INI_FILE to remove a section by order.

Arguments:

  This        - the interface instance structure.
  Order       - the section's order.
  Section     - Unicode section name.

Returns:

  EFI_SUCCESS           - remove section successfully.
  EFI_INVALID_PARAMETER - invalid parameters.
  EFI_NOT_FOUND         - section not found.

--*/
{
  INI                              *ptrCur;
  INI                              *ptrPrev;
  INI                              *ptrSect;
  INI                              *ptrNext;
  EFI_INI_FILE_PRIVATE_DATA        *Private;
  CHAR8                            ptrSection[MAX_STRING_LEN + 1];
  CHAR8                            tmpSection[MAX_STRING_LEN + 1];

  Private = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (This);

  if (Section == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrSection, Section, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }
  StrCpy (tmpSection, ptrSection);
  _alltrim (tmpSection);

  ptrSect = _searchSection (Private->Head, Order, tmpSection);
  if (ptrSect == NULL) {
    return EFI_NOT_FOUND;
  }

  ptrCur = Private->Head;
  ptrPrev = NULL;
  while (ptrCur != NULL) {
    if (ptrCur == ptrSect) {
      break;
    }
    ptrPrev = ptrCur;
    ptrCur = ptrCur->ptrNext;
  }

  _rmComment (&(Private->CommentLineHead), ptrSect);
  ptrNext = ptrSect->ptrNext;
  _freeItem (ptrSect);
  ptrCur = ptrNext;
  while (ptrCur != NULL) {
    if (*(ptrCur->ptrEntry) == '\0') {
      //
      // reached another section
      //
      break;
    }
    _rmComment (&(Private->CommentLineHead), ptrCur);
    ptrNext = ptrCur->ptrNext;
    _freeItem (ptrCur);
    ptrCur = ptrNext;
  }

  if (ptrPrev == NULL) {
    Private->Head = ptrNext;
  } else {
    ptrPrev->ptrNext = ptrNext;
  }

  if (ptrNext == NULL) {
    Private->Tail = ptrPrev;
  }

  Private->Modified = TRUE;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiIniGetOrderNum (
  IN EFI_INI_FILE_HANDLE                    This,
  IN CHAR16                                 *Section,
  OUT UINT32                                *OrderNum
  )
/*++

Routine Description:

  One interface function of the EFI_INI_FILE to get the number of sections with the same name.

Arguments:

  This        - the interface instance structure.
  Section     - Unicode section name.
  OrderNum    - return the number of sections with the same name.

Returns:

  EFI_SUCCESS           - get number successfully.
  EFI_INVALID_PARAMETER - invalid parameters.

--*/
{
  INI                              *ptrCur;
  EFI_INI_FILE_PRIVATE_DATA        *Private;
  CHAR8                            ptrSection[MAX_STRING_LEN + 1];
  CHAR8                            tmpSection[MAX_STRING_LEN + 1];

  Private = EFI_INI_FILE_PRIVATE_DATA_FROM_THIS (This);

  if ((OrderNum == NULL) || (Section == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (WcsToMbs (ptrSection, Section, MAX_STRING_LEN + 1) == -1) {
    return EFI_INVALID_PARAMETER;
  }

  StrCpy (tmpSection, ptrSection);
  _alltrim (tmpSection);

  *OrderNum = 0;
  ptrCur = Private->Head;
  while (ptrCur != NULL) {
    if (StriCmp (tmpSection, ptrCur->ptrSection) == 0) {
      ++ (*OrderNum);
    }

    ptrCur = _getNextSection (ptrCur);
  }

  return EFI_SUCCESS;
}

//
// Internal functions
//

VOID
_initFile (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile
  )
/*++

Routine Description:

  Initialize a new ini file.

--*/
{
  IniFile->Signature                 = EFI_INI_FILE_PRIVATE_DATA_SIGNATURE;
  IniFile->Handle.Revision           = 0x10000;
  IniFile->Handle.GetString          = EfiIniGetString;
  IniFile->Handle.SetString          = EfiIniSetString;
  IniFile->Handle.RmSection          = EfiIniRmSection;
  IniFile->Handle.GetStringByOrder   = EfiIniGetStringByOrder;
  IniFile->Handle.SetStringByOrder   = EfiIniSetStringByOrder;
  IniFile->Handle.RmSectionByOrder   = EfiIniRmSectionByOrder;
  IniFile->Handle.GetOrderNum        = EfiIniGetOrderNum;
  IniFile->Handle.Flush              = EfiIniFlush;
  IniFile->DevPath                   = NULL;
  IniFile->FileName                  = NULL;
  IniFile->Head                      = NULL;
  IniFile->Tail                      = NULL;
  IniFile->CommentLineHead           = NULL;
  IniFile->isUnicode                 = FALSE;
  IniFile->Modified                  = FALSE;
}

VOID
_freeIniFile (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile
  )
/*++

Routine Description:

  Free an ini file and all the resources related to the ini file.

--*/
{
  IniFile->Handle.GetString          = NULL;
  IniFile->Handle.SetString          = NULL;
  IniFile->Handle.RmSection          = NULL;
  IniFile->Handle.GetStringByOrder   = NULL;
  IniFile->Handle.SetStringByOrder   = NULL;
  IniFile->Handle.RmSectionByOrder   = NULL;
  IniFile->Handle.GetOrderNum        = NULL;
  IniFile->Handle.Flush              = NULL;
  if (IniFile->FileName != NULL) {
    Free (IniFile->FileName);
    IniFile->FileName = NULL;
  }
  if (IniFile->DevPath != NULL) {
    Free (IniFile->DevPath);
    IniFile->DevPath = NULL;
  }
  _freePointer(IniFile);
  Free (IniFile);
}

VOID
_freePointer (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile
  )
/*++

Routine Description:

  Free all content of an ini file.

--*/
{
  INI         *ptrCur;
  INI         *ptrTmp;
  COMMENTLINE *ptrCommentCur;
  COMMENTLINE *ptrCommentTmp;

  ptrCur = IniFile->Head;

  while (ptrCur != NULL) {
    Free (ptrCur->ptrSection);
    Free (ptrCur->ptrEntry);
    Free (ptrCur->ptrValue);
    ptrCur = ptrCur->ptrNext;
  }

  while (IniFile->Head != NULL) {
    ptrTmp = IniFile->Head->ptrNext;
    Free (IniFile->Head);
    IniFile->Head = ptrTmp;
  }
  IniFile->Tail = NULL;

  ptrCommentCur = IniFile->CommentLineHead;

  while (ptrCommentCur != NULL) {
    Free (ptrCommentCur->ptrComment);
    ptrCommentCur = ptrCommentCur->ptrNext;
  }

  while (IniFile->CommentLineHead != NULL) {
    ptrCommentTmp = IniFile->CommentLineHead->ptrNext;
    Free (IniFile->CommentLineHead);
    IniFile->CommentLineHead = ptrCommentTmp;
  }
}

VOID
_prosessLine (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile,
  IN CHAR8                        *ptrLine,
  OUT CHAR8                       *ptrSection,
  OUT BOOLEAN                     *isSectionGot,
  OUT UINT32                      *commentNo
  )
/*++

Routine Description:

  Parse a line.

--*/
{
  CHAR8 ptrEntry[MAX_STRING_LEN + 1];
  CHAR8 ptrValue[MAX_STRING_LEN + 1];
  INI   *ptrItem;

  StrCpy (ptrLine, _alltrim (ptrLine));

  if (*ptrLine == '#') {
    // it's a comment line
    _getcomment (IniFile, ptrLine, commentNo);
  } else if ((*ptrLine == '[') && (StrChr (ptrLine, ']') != NULL)) {
    // it's a section head
    _getsection (IniFile, ptrLine, ptrSection, commentNo);
    *isSectionGot = TRUE;
  } else if (StrChr (ptrLine, '=') != NULL) {
    _getentry (ptrLine, ptrEntry, ptrValue);

    if (*isSectionGot == TRUE) {
      ptrItem = (INI *)Malloc (sizeof(INI));
      ptrItem->ptrSection = (CHAR8 *) Calloc (StrLen(ptrSection) + 1, sizeof(CHAR8));
      ptrItem->ptrEntry   = (CHAR8 *) Calloc (StrLen(ptrEntry) + 1, sizeof(CHAR8));
      ptrItem->ptrValue   = (CHAR8 *) Calloc (StrLen(ptrValue) + 1, sizeof(CHAR8));

      ptrItem->commentNo = *commentNo;
      StrCpy (ptrItem->ptrSection, ptrSection);
      StrCpy (ptrItem->ptrEntry, ptrEntry);
      StrCpy (ptrItem->ptrValue, ptrValue);

      (*commentNo) ++;

      _additem (IniFile, ptrItem);
    }
  }
}

VOID
_getcomment(
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile,
  IN CHAR8                        *ptrStr,
  OUT UINT32                      *commentNo
  )
/*++

Routine Description:

  Get comment line.

--*/
{
  static COMMENTLINE *ptrCommentLineCurrent = NULL;
  COMMENTLINE        *ptrCommentLineNew;
  UINT32             Index;
  UINT32             Length;

  //
  // skip '\n' & '\r' at end of comment line
  //
  Length = (UINT32) StrLen (ptrStr);
  for (Index = Length; Index > 0; Index --) {
    if (ptrStr[Index - 1] != '\n' && ptrStr[Index - 1] != '\r') {
      break;
    }
  }
  ptrStr[Index] = '\0';

  ptrCommentLineNew = (COMMENTLINE *) Malloc (sizeof(COMMENTLINE));
  ptrCommentLineNew->ptrComment = (CHAR8 *) Calloc (StrLen(ptrStr) + 1, sizeof(CHAR8));

  ptrCommentLineNew->commentNo = *commentNo;
  StrCpy (ptrCommentLineNew->ptrComment, ptrStr);

  if (IniFile->CommentLineHead == NULL) {
    IniFile->CommentLineHead = ptrCommentLineNew;
    IniFile->CommentLineHead->ptrNext = NULL;
    ptrCommentLineCurrent = IniFile->CommentLineHead;
  } else {
    ptrCommentLineNew->ptrNext = NULL;
    ptrCommentLineCurrent->ptrNext = ptrCommentLineNew;
    ptrCommentLineCurrent = ptrCommentLineNew;
  }
}

VOID
_getsection (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile,
  IN CHAR8                        *ptrStr,
  OUT CHAR8                       *ptrSection,
  OUT UINT32                      *commentNo
  )
/*++

Routine Description:

  Parse one line and generate section.

--*/
{
  CHAR8 *p, *q;
  INI   *ptrItem;

  p = StrChr (ptrStr, '[');
  q = StrChr (ptrStr, ']');

  *q = '\0' ;

  _alltrim (++p);

  if (StrLen (p) <= MAX_STRING_LEN) {
    if (*p == '\0') {
      StrCpy (ptrSection, "UNKNOWN");
    } else {
      StrCpy (ptrSection, p);
    }
  } else {
    StrnCpy (ptrSection, p, MAX_STRING_LEN);
    ptrSection[MAX_STRING_LEN] = '\0';
  }

  ptrItem = (INI *)Malloc (sizeof(INI));

  ptrItem->ptrSection = (CHAR8 *) Calloc (StrLen(ptrSection) + 1, sizeof(CHAR8));
  ptrItem->ptrEntry   = (CHAR8 *) Calloc (1, sizeof(CHAR8));
  ptrItem->ptrValue   = (CHAR8 *) Calloc (1, sizeof(CHAR8));

  ptrItem->commentNo  = *commentNo;
  StrCpy (ptrItem->ptrSection, ptrSection);
  StrCpy (ptrItem->ptrEntry, "");
  StrCpy (ptrItem->ptrValue, "");

  (*commentNo) ++;

  _additem (IniFile, ptrItem);
}

CHAR8 *_alltrim(
  CHAR8 *ptrStr
  )
/*++

Routine Description:

  Remove the space from both side of the string and the ending '\n' or '\r'.

--*/
{
  CHAR8   *tmp = ptrStr;
  UINT32  Length;
  UINT32  Index;

  //
  // skip the ' ' at beginning of string
  //
  while (*tmp == ' ') {
    tmp ++;
  }

  //
  // skip '\n' & ' ' & '\r' at end of string
  //
  Length = (UINT32) StrLen (tmp);
  for (Index = Length; Index > 0; Index --) {
    if (tmp[Index - 1] != '\n' && tmp[Index - 1] != ' ' && tmp[Index - 1] != '\r') {
      break;
    }
  }

  tmp[Index] = '\0';
  StrCpy (ptrStr, tmp);

  return ptrStr;
}

VOID
_additem (
  IN EFI_INI_FILE_PRIVATE_DATA    *IniFile,
  IN INI                          *ptrItem
  )
/*++

Routine Description:

  Insert new item to the end of ini table .

--*/
{
  if (IniFile->Head == NULL) {
    IniFile->Head = ptrItem;
    IniFile->Tail = ptrItem;
    IniFile->Head->ptrNext = NULL;
  } else {
    ptrItem->ptrNext = NULL;
    IniFile->Tail->ptrNext = ptrItem;
    IniFile->Tail = ptrItem;
  }
}

VOID
_getentry (
  IN CHAR8                        *ptrStr,
  IN CHAR8                        *ptrEntry,
  OUT CHAR8                       *ptrValue
  )
/*++

Routine Description:

  Parse one line and generate the entry and value.

--*/
{
  CHAR8 *p, *p2;
  UINTN Len;

  p = StrChr (ptrStr, '=');

  *p = '\0';

  _alltrim (ptrStr);

  if (StrLen (ptrStr) <= MAX_STRING_LEN) {
    if (*ptrStr == '\0') {
      StrCpy (ptrEntry, "UNKNOWN");
    } else {
      StrCpy (ptrEntry, ptrStr);
    }
  } else {
    StrnCpy (ptrEntry, ptrStr, MAX_STRING_LEN);
    ptrEntry[MAX_STRING_LEN] = '\0';
  }

  _alltrim (++ p);
  p2 = StrChr (p, '#');
  if (p2 != NULL) {
    *p2 = '\0';
    _alltrim (p);
  }

  Len = StrLen (p);

  if (StrLen (p) <= MAX_STRING_LEN) {
    StrCpy (ptrValue, p);
  } else {
    StrnCpy (ptrValue, p, MAX_STRING_LEN);
    ptrValue[MAX_STRING_LEN] = '\0';
  }
}

INI *
_searchSection (
  IN INI                          *Head,
  IN UINT32                       Order,
  OUT CHAR8                       *Section
)
/*++

Routine Description:

  Search for the specific section in the ini table

--*/
{
  INI     *ptrCur;
  UINT32  CurOrder;

  CurOrder = 0;
  ptrCur = Head;
  while (ptrCur != NULL) {
    if (StriCmp (Section, ptrCur->ptrSection) == 0) {
      if (CurOrder == Order) {
        break;
      }
      ++ CurOrder;
    }

    ptrCur = _getNextSection (ptrCur);
  }

  return ptrCur;
}

INI *
_getNextSection (
  IN INI                          *CurSection
)
/*++

Routine Description:

  Search for the next section in the ini table

--*/
{
  INI   *ptrCur;

  ptrCur = CurSection->ptrNext;
  while (ptrCur != NULL) {
    if (*(ptrCur->ptrEntry) == '\0') {
      break;
    }
    ptrCur = ptrCur->ptrNext;
  }

  return ptrCur;
}

VOID
_freeItem (
  IN INI                          *ptrItem
  )
/*++

Routine Description:

  Free an INI item

--*/
{
  if (ptrItem->ptrSection != NULL) {
    Free (ptrItem->ptrSection);
    ptrItem->ptrSection = NULL;
  }
  if (ptrItem->ptrEntry != NULL) {
    Free (ptrItem->ptrEntry);
    ptrItem->ptrEntry = NULL;
  }
  if (ptrItem->ptrValue != NULL) {
    Free (ptrItem->ptrValue);
    ptrItem->ptrValue = NULL;
  }
  Free (ptrItem);
}

VOID
_rmComment (
  IN COMMENTLINE                  **CmtHead,
  IN INI                          *ptrItem
)
{
  COMMENTLINE *ptrCmtCur;
  COMMENTLINE *ptrCmtPrev;
  COMMENTLINE *ptrCmtNext;

  ptrCmtCur = *CmtHead;
  ptrCmtPrev = NULL;
  while (ptrCmtCur != NULL) {
    if (ptrCmtCur->commentNo == ptrItem->commentNo) {
      ptrCmtNext = ptrCmtCur->ptrNext;
      Free (ptrCmtCur->ptrComment);
      Free (ptrCmtCur);
      if (ptrCmtPrev == NULL) {
        *CmtHead = ptrCmtNext;
      } else {
        ptrCmtPrev->ptrNext = ptrCmtNext;
      }
      ptrCmtCur = ptrCmtNext;
    } else {
      ptrCmtPrev = ptrCmtCur;
      ptrCmtCur = ptrCmtCur->ptrNext;
    }
  }
}

CHAR16 *
TplStrDuplicate (
  IN CHAR16             *String
  )
{
  EFI_STATUS  Status;
  CHAR16      *Buffer;

  if (String == NULL) {
    return NULL;
  }

  Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  (EfiStrLen (String) + 1) * sizeof(CHAR16),
                  (VOID **)&Buffer
                  );
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  EfiStrCpy (Buffer, String);

  return Buffer;
}
