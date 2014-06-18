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

  TestRecovery.c

Abstract:

  Driver to publish the Test Recovery Library Protocol.

--*/

#include "SctLib.h"
#include "EfiTest.h"
#include "TestRecovery.h"

//
// Prototypes
//

EFI_STATUS
TestRecoveryEntryPoint (
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
  IN EFI_TSL_INIT_INTERFACE           *This,
  IN OUT EFI_HANDLE                   *LibHandle,
  OUT VOID                            **PrivateLibInterface
  );

EFI_STATUS
EFIAPI
TslClose (
  IN EFI_TSL_INIT_INTERFACE           *This,
  IN EFI_HANDLE                       LibHandle
  );

//
// Prototypes of EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
//
EFI_STATUS
EFIAPI
TrlReadResetRecord (
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL           *This,
  OUT UINTN                                       *Size,
  OUT VOID                                        *Buffer
  );

EFI_STATUS
EFIAPI
TrlWriteResetRecord (
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL           *This,
  IN UINTN                                        Size,
  IN VOID                                         *Buffer
  );

//
// Prototypes of EFI_TRL_PRIVATE_INTERFACE
//
EFI_STATUS
EFIAPI
TrlSetConfig (
  IN EFI_TRL_PRIVATE_INTERFACE                   *This,
  EFI_DEVICE_PATH_PROTOCOL                       *DevicePath,
  CHAR16                                         *FileName
  );

//
// Name and Description of EFI_TEST_RECOVERY_LIBRARY_PROTOCOL
//
CHAR16 *gTrlName        = L"Test Recovery Library";
CHAR16 *gTrlDescription = L"EFI Test Recovery Library";

//
// Internal functions
//

EFI_STATUS
TrlFreePointer (
  TEST_RECOVERY_PRIVATE_DATA            *Private
  );

//
// Entry point
//
EFI_STATUS
TestRecoveryEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
/*++

Routine Description:

  Test recovery library driver's entry point.

Arguments:

  ImageHandle   - the driver image handle.
  SystemTable   - the system table.

Returns:

  EFI_SUCCESS         - the driver is loaded successfully.
  EFI_ALREADY_STARTED - the driver has already been loaded before.

--*/
{
  EFI_STATUS                     Status;
  EFI_LOADED_IMAGE_PROTOCOL      *LoadedImage;
  TSL_INIT_PRIVATE_DATA          *Private;

  // Initialize driver lib
  SctInitializeDriver (ImageHandle, SystemTable);

  //
  // Fill in the Unload() function
  //
  Status = tBS->OpenProtocol (
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
  Status = tBS->OpenProtocol (
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
  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (TSL_INIT_PRIVATE_DATA),
                  (VOID **)&Private
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (Private, sizeof(TSL_INIT_PRIVATE_DATA));
  Private->Signature            = TSL_INIT_PRIVATE_DATA_SIGNATURE;
  Private->ImageHandle          = ImageHandle;
  Private->TslInit.Revision     = 0x10000;
  Private->TslInit.LibraryGuid  = gEfiTestRecoveryLibraryGuid;
  Private->TslInit.Open         = TslOpen;
  Private->TslInit.Close        = TslClose;

  //
  // Install TslInit protocol
  //
  Status = tBS->InstallProtocolInterface (
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

  ImageHandle - the driver image handle.

Returns:

  EFI_SUCCESS - unload successfully.

--*/
{
  EFI_STATUS                     Status;
  EFI_TSL_INIT_INTERFACE         *TslInit;
  TSL_INIT_PRIVATE_DATA          *Private;

  //
  // Open the TslInit protocol
  //
  Status = tBS->OpenProtocol (
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
    Status = tBS->UninstallProtocolInterface (
                    ImageHandle,
                    &gEfiTslInitInterfaceGuid,
                    TslInit
                    );
    Private = TSL_INIT_PRIVATE_DATA_FROM_THIS (TslInit);
    tBS->FreePool (Private);
  }

  return Status;
}

EFI_STATUS
EFIAPI
TslOpen (
  EFI_TSL_INIT_INTERFACE          *This,
  IN OUT EFI_HANDLE               *LibHandle,
  OUT VOID                        **PrivateLibInterface
  )
/*++

Routine Description:

  One interface function of the TslInit to open the support library.

Arguments:

  This                - the protocol instance structure.
  LibHandle           - a library handle to bind the TestRecoveryLibrary
                        protocol.
  PrivateLibInterface - private interface of TestRecoveryLibrary protocol.

Returns:

  EFI_SUCCESS           - open the TestRecoveryLibrary successfully.
  EFI_INVALID_PARAMETER - invalid parameter, LibHandle is NULL.
  EFI_ALREADY_STARTED   - the TestRecoveryLibrary has been bind on the LibHandle
                          before.

--*/
{
  EFI_STATUS                      Status;
  TEST_RECOVERY_PRIVATE_DATA      *Private;
  TSL_INIT_PRIVATE_DATA           *TslPrivate;

  //
  // Check parameter
  //
  if (LibHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  TslPrivate = TSL_INIT_PRIVATE_DATA_FROM_THIS (This);
  //
  // Open the TestRecoveryLibrary protocol to perform the supported test.
  //
  if (*LibHandle != NULL) {
    Status = tBS->OpenProtocol (
                    *LibHandle,
                    &gEfiTestRecoveryLibraryGuid,
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
  // Initialize the TestRecoveryLibrary private data
  //
  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (TEST_RECOVERY_PRIVATE_DATA),
                  (VOID **)&Private
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (Private, sizeof(TEST_RECOVERY_PRIVATE_DATA));
  Private->Signature = TEST_RECOVERY_PRIVATE_DATA_SIGNATURE;
  Private->TestRecovery.LibraryRevision     = 0x10000;
  Private->TestRecovery.Name                = gTrlName;
  Private->TestRecovery.Description         = gTrlDescription;
  Private->TestRecovery.ReadResetRecord     = TrlReadResetRecord;
  Private->TestRecovery.WriteResetRecord    = TrlWriteResetRecord;
  Private->PrivateInterface.SetConfig       = TrlSetConfig;

  if (PrivateLibInterface != NULL) {
    *PrivateLibInterface = (VOID *)&(Private->PrivateInterface);
  }

  //
  // Install TestRecoveryLibrary protocol
  //
  Status = tBS->InstallProtocolInterface (
                  LibHandle,
                  &gEfiTestRecoveryLibraryGuid,
                  EFI_NATIVE_INTERFACE,
                  &(Private->TestRecovery)
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

  One interface function of the TslInit to close the support library.

Arguments:

  This        - the protocol instance structure.
  LibHandle   - a library handle.

Returns:

  EFI_SUCCESS - close the TestRecoveryLibrary successfully.

--*/
{
  EFI_STATUS                          Status;
  TEST_RECOVERY_PRIVATE_DATA          *Private;
  TSL_INIT_PRIVATE_DATA               *TslPrivate;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *TestRecovery;

  TslPrivate = TSL_INIT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Open the TestRecoveryLibrary protocol to perform the supported test.
  //
  Status = tBS->OpenProtocol (
                  LibHandle,
                  &gEfiTestRecoveryLibraryGuid,
                  (VOID **)&TestRecovery,
                  TslPrivate->ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Uninstall TestRecoveryLibrary protocol
  //
  Status = tBS->UninstallProtocolInterface (
                  LibHandle,
                  &gEfiTestRecoveryLibraryGuid,
                  TestRecovery
                  );
  Private = TEST_RECOVERY_PRIVATE_DATA_FROM_TRL (TestRecovery);
  TrlFreePointer (Private);
  tBS->FreePool (Private);

  return Status;
}

EFI_STATUS
EFIAPI
TrlReadResetRecord (
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL     *This,
  OUT UINTN                                 *Size,
  OUT VOID                                  *Buffer
  )
/*++

Routine Description:

  One interface function of the TestRecoveryLibrary to read reset record.

Arguments:

  This        - the protocol instance structure.
  Size        - return the bytes been read.
  Buffer      - buffer to store the record, it can't less than 1024Bytes.

Returns:

  EFI_SUCCESS           - read the record successfully.
  EFI_INVALID_PARAMETER - invalid parameters.

--*/
{
  EFI_STATUS                          Status;
  EFI_HANDLE                          DeviceHandle;
  EFI_FILE_HANDLE                     RootDir;
  EFI_FILE_HANDLE                     Handle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL     *Vol;
  TEST_RECOVERY_PRIVATE_DATA          *Private;
  EFI_DEVICE_PATH_PROTOCOL            *PreDevicePath;

  Private = TEST_RECOVERY_PRIVATE_DATA_FROM_TRL (This);

  //
  //  Determine device handle for fs protocol on specified device path
  //
  PreDevicePath = Private->DevicePath;
  Status = tBS->LocateDevicePath (
                  &gEfiSimpleFileSystemProtocolGuid,
                  &PreDevicePath,
                  &DeviceHandle
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  //  Determine volume for file system on device handle
  //
  Status = tBS->HandleProtocol (
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
  // Open file for read
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      Private->FileName,
                      EFI_FILE_MODE_READ,
                      0
                      );
  if (EFI_ERROR (Status)) {
    RootDir->Close (RootDir);
    return Status;
  }

  *Size = MAX_BUFFER_SIZE;
  Status = Handle->Read (Handle, Size, Buffer);
  Handle->Close (Handle);
  RootDir->Close (RootDir);
  return Status;
}

EFI_STATUS
EFIAPI
TrlWriteResetRecord (
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL     *This,
  IN UINTN                                  Size,
  IN VOID                                   *Buffer
  )
/*++

Routine Description:

  One interface function of the TestRecoveryLibrary to write reset record.

Arguments:

  This        - the protocol instance structure.
  Size        - the bytes to be write, it can't bigger than 1024Bytes.
  Buffer      - buffer contain the record to be written.

Returns:

  EFI_SUCCESS           - write the record successfully.
  EFI_INVALID_PARAMETER - invalid parameters.

--*/
{
  EFI_STATUS                          Status;
  EFI_HANDLE                          DeviceHandle;
  EFI_FILE_HANDLE                     RootDir;
  EFI_FILE_HANDLE                     Handle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL     *Vol;
  TEST_RECOVERY_PRIVATE_DATA          *Private;
  EFI_DEVICE_PATH_PROTOCOL            *PreDevicePath;

  Private = TEST_RECOVERY_PRIVATE_DATA_FROM_TRL (This);

  //
  //  Determine device handle for fs protocol on specified device path
  //
  PreDevicePath = Private->DevicePath;
  Status = tBS->LocateDevicePath (
                  &gEfiSimpleFileSystemProtocolGuid,
                  &PreDevicePath,
                  &DeviceHandle
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  //  Determine volume for file system on device handle
  //
  Status = tBS->HandleProtocol (
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
  // Open file for read
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      Private->FileName,
                      EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                      0
                      );
  if (Status == EFI_NOT_FOUND) {
    //
    // The file not exist, create it
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
  } else if (Status == EFI_SUCCESS) {
    //
    // The file exist, delete it
    //
    Status = Handle->Delete (Handle);
    //
    // EFI_FILE.Delete() return a warning status
    //
    if (Status != EFI_SUCCESS) {
      Handle->Close (Handle);
      RootDir->Close (RootDir);
      return EFI_UNSUPPORTED;
    }

    //
    // Recreate the file
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
  } else {
    RootDir->Close (RootDir);
    return Status;
  }

  //
  // Write buffer
  //
  Status = Handle->Write (Handle, &Size, Buffer);
  Handle->Close (Handle);
  RootDir->Close (RootDir);
  return Status;
}

EFI_STATUS
EFIAPI
TrlSetConfig (
  IN EFI_TRL_PRIVATE_INTERFACE              *This,
  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  CHAR16                                    *FileName
  )
/*++

Routine Description:

  One private interface function of the TestRecoveryLibrary to set config.

Arguments:

  This        - the private interface instance structure.
  DevicePath  - device path of the reset record file.
  FileName    - filename of the reset record file.

Returns:

  EFI_SUCCESS           - set config successfully.
  EFI_OUT_OF_RESOURCES  - not enough memory.
  EFI_INVALID_PARAMETER - invalid parameters.

--*/
{
  EFI_STATUS                      Status;
  TEST_RECOVERY_PRIVATE_DATA      *Private;

  Private = TEST_RECOVERY_PRIVATE_DATA_FROM_PI (This);
  TrlFreePointer (Private);

  if ((DevicePath == NULL) || (FileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // DevicePath & FileName
  //
  Private->DevicePath = SctDuplicateDevicePath (DevicePath);
  if (Private->DevicePath == NULL) {
    TrlFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }
  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  (SctStrLen (FileName) + 1) * 2,
                  (VOID **)&(Private->FileName)
                  );
  if (EFI_ERROR (Status)) {
    TrlFreePointer (Private);
    return Status;
  }
  SctStrCpy (Private->FileName, FileName);

  return EFI_SUCCESS;
}

//
// Internal functions
//

EFI_STATUS
TrlFreePointer (
  TEST_RECOVERY_PRIVATE_DATA  *Private
  )
{
  EFI_STATUS                    Status;

  //
  // Free DevicePath and FileName
  //
  if (Private->DevicePath != NULL) {
    Status = tBS->FreePool (Private->DevicePath);
    Private->DevicePath = NULL;
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }
  if (Private->FileName != NULL) {
    Status = tBS->FreePool (Private->FileName);
    Private->FileName = NULL;
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
} 
