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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  EntsDebug.c
  
Abstract:

  Implementation of debug services 
  
--*/
#include "Efi.h"
#include <Library/EntsLib.h>

static EFI_FILE *mLogFile = NULL;

//
// Local Function Definition
//
EFI_STATUS
EFIAPI
ENTSOpen (
  IN EFI_DEVICE_PATH_PROTOCOL               *DevicePath,
  IN CHAR16                                 *FileName,
  IN BOOLEAN                                OverwriteFile,
  OUT EFI_FILE                              **FileHandle
  );

EFI_STATUS
EFIAPI
ENTSWrite (
  IN EFI_FILE                               *FileHandle,
  IN CHAR16                                 *String
  );

EFI_STATUS
EFIAPI
ENTSClose (
  IN EFI_FILE                               *FileHandle
  );


EFI_STATUS
CreateDirectory (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName
  );

EFI_STATUS
EntsInitializeDebugServices (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath
  )
/*++

Routine Description:

  Initialize the debug services.

Arguments:

  DevicePath  - Pointer to EFI_DEVICE_PATH_PROTOCOL instance.
  FilePath    - FilePath string.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Open the system log file
  //
  FileName = EntsPoolPrint (L"%s\\%s", FilePath, EFI_ENTS_FILE_LOG);
  if (FileName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = ENTSOpen (
            DevicePath,
            FileName,
            TRUE, // Overwrite
            &mLogFile
            );
  if (EFI_ERROR (Status)) {
    EntsFreePool (FileName);
    return Status;
  }
  //
  // Free resources
  //
  EntsFreePool (FileName);

  return EFI_SUCCESS;
}

EFI_STATUS
CloseDebugServices (
  VOID
  )
/*++

Routine Description:

  Free the debug services.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  //
  // Check the pre-conditions for debug services
  //
  if (mLogFile == NULL) {
    return EFI_SUCCESS;
  }
  //
  // Close the system log file
  //
  Status = ENTSClose (mLogFile);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mLogFile = NULL;

  return EFI_SUCCESS;
}

VOID
EfiEntsDebug (
  IN UINTN              Level,
  IN CHAR16             *Format,
  ...
  )
/*++

Routine Description:

  Ents debugging services.

Arguments:

  Level   - Debug level like ERROR, WARNING, TRACE etc.
  Format  - String format.
  ...     - Variables.

Returns:

  None.

--*/
{
  EFI_STATUS  Status;
  VA_LIST     Marker;
  CHAR16      Buffer[ENTS_MAX_BUFFER_SIZE];
  CHAR16      String[ENTS_MAX_BUFFER_SIZE+64];

  if ((Level & EFI_ENTS_D_LEVEL) == 0) {
    return ;
  }

  VA_START (Marker, Format);
  EntsVSPrint (Buffer, ENTS_MAX_BUFFER_SIZE, Format, Marker);
  VA_END (Marker);

  //
  // Deal with different error level
  //
  switch (Level) {
  case EFI_ENTS_D_ERROR:
  	EntsSPrint(String, ENTS_MAX_BUFFER_SIZE+64, L"ERROR: %s\n", Buffer);
    break;

  case EFI_ENTS_D_WARNING:
  	EntsSPrint(String, ENTS_MAX_BUFFER_SIZE+64, L"WARNING: %s\n", Buffer);
    break;

  case EFI_ENTS_D_TRACE:
  	EntsSPrint(String, ENTS_MAX_BUFFER_SIZE+64, L"TRACE: %s\n", Buffer);
    break;

  default:
    return ;
  }

  if (mLogFile != NULL) {
    //
    // Record into the system log file
    //
    Status = ENTSWrite (
              mLogFile,
              String
              );
    if (EFI_ERROR (Status)) {
      return ;
    }
  } else {
    //
    // Print the message into screen before the ENTS debug service is avariable.
    //
    EntsPrint (String);
  }
}

VOID
EfiEntsStatus (
  IN CHAR16             *Format,
  ...
  )
/*++

Routine Description:

  Worker function for EFI_ENTS_STATUS marco.

Arguments:

  Format  - Format string.
  ...     - Variables.

Returns:

  None.

--*/
{
  EFI_STATUS  Status;
  VA_LIST     Marker;
  CHAR16      Buffer[ENTS_MAX_BUFFER_SIZE];
  CHAR16      *String;

  //
  // Check the pre-conditions for debug services
  //
  if (mLogFile == NULL) {
    return ;
  }

  VA_START (Marker, Format);
  EntsVSPrint (Buffer, ENTS_MAX_BUFFER_SIZE, Format, Marker);
  VA_END (Marker);

  //
  // Record into the system log file
  //
  String = EntsPoolPrint (L"STATUS: %s\n", Buffer);

  Status = ENTSWrite (
            mLogFile,
            String
            );
  if (EFI_ERROR (Status)) {
    EntsFreePool (String);
    return ;
  }
  //
  // Free resources
  //
  EntsFreePool (String);
}
//
// Local Functions Implementation
//
EFI_STATUS
EFIAPI
ENTSOpen (
  IN EFI_DEVICE_PATH_PROTOCOL               *DevicePath,
  IN CHAR16                                 *FileName,
  IN BOOLEAN                                OverwriteFile,
  OUT EFI_FILE                              **FileHandle
  )
/*++

Routine Description:

  To open a file.

Arguments:

  DevicePath    - The file's root device path.
  FileName      - The file's name relative to the root.
  OverwriteFile - Whether to overwrite the file.
  FileHandle    - Return the file's handle.

Returns:

  EFI_SUCCESS   - Open the file successfully.
  EFI_NOT_READY - To overwrite an opened file is not allowed.
  EFI_UNSUPPORTED - The file is not supported.
  EFI_OUT_OF_RESOURCES - Not enough memory.

--*/
{
  EFI_STATUS                      Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Vol;
  EFI_HANDLE                      DeviceHandle;
  EFI_FILE_HANDLE                 RootDir;
  EFI_FILE_HANDLE                 Handle;
  UINTN                           BufSize;
  UINT8                           Buffer[2];

  //
  //  Determine device handle for fs protocol on specified device path
  //
  Status = gntBS->LocateDevicePath (
                    &gEfiSimpleFileSystemProtocolGuid,
                    &DevicePath,
                    &DeviceHandle
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  //  Determine volume for file system on device handle
  //
  Status = gntBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiSimpleFileSystemProtocolGuid,
                    (VOID *) &Vol
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
  // Determine the existence of the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ,
                      0
                      );
  if (Status == EFI_NOT_FOUND) {
    //
    // The file not exist, create it
    //
    Status = CreateFile (RootDir, FileName, &Handle);
    if (EFI_ERROR (Status)) {
      RootDir->Close (RootDir);
      return Status;
    }
    //
    // Write the head of Unicode text file
    //
    Buffer[0] = 0xff;
    Buffer[1] = 0xfe;
    BufSize   = 2;
    Status    = Handle->Write (Handle, &BufSize, Buffer);
    //
    //    if (EFI_ERROR (Status)) {
    //
    Handle->Close (Handle);
    RootDir->Close (RootDir);
    return Status;
    //
    //    }
    //
  } else if (EFI_ERROR (Status)) {
    RootDir->Close (RootDir);
    return Status;
  }

  if (OverwriteFile) {
    //
    // Overwrite the file
    //
    //
    // Delete the file
    //
    Status = Handle->Delete (Handle);

    //
    // EFI_FILE.Delete() return a warning status
    //
    if (Status != EFI_SUCCESS) {
      RootDir->Close (RootDir);
      return EFI_UNSUPPORTED;
    }
    //
    // Recreate the file
    //
    Status = RootDir->Open (
                        RootDir,
                        &Handle,
                        FileName,
                        EFI_FILE_MODE_CREATE | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ,
                        0
                        );
    if (EFI_ERROR (Status)) {
      RootDir->Close (RootDir);
      return Status;
    }
    //
    // Write the head of Unicode text file
    //
    Buffer[0] = 0xff;
    Buffer[1] = 0xfe;
    BufSize   = 2;
    Status    = Handle->Write (Handle, &BufSize, Buffer);
    if (EFI_ERROR (Status)) {
      Handle->Close (Handle);
      return Status;
    }
  } else {
    //
    // Append the file
    //
    //
    // Set position to the end of file
    //
    Status = Handle->SetPosition (Handle, (UINT64) -1);
    if (EFI_ERROR (Status)) {
      RootDir->Close (RootDir);
      return Status;
    }
  }

  RootDir->Close (RootDir);

  *FileHandle = Handle;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ENTSClose (
  IN EFI_FILE                               *FileHandle
  )
/*++

Routine Description:

  Close a file.

Arguments:

  FileHandle  - The opened file's handle.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  //
  // Delete the item
  //
  FileHandle->Close (FileHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ENTSWrite (
  IN EFI_FILE                               *FileHandle,
  IN CHAR16                                 *String
  )
/*++

Routine Description:

  One interface function of the TestOutputLibrary to open a file.

Arguments:

  FileHandle  - The opened file's handle.
  String      - String to be written.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  UINTN       BufSize;

  //
  // Write the String to the file
  //
  BufSize = EntsStrLen (String) * 2;
  Status  = FileHandle->Write (FileHandle, &BufSize, String);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = FileHandle->Flush (FileHandle);

  return Status;
}

EFI_STATUS
CreateFile (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName,
  OUT EFI_FILE_HANDLE             *Handle
  )
/*++

Routine Description:

  Create a file.

Arguments:

  RootDir   - Root directory.
  FileName  - File name string.
  Handle    - Pointer to EFI_FILE_HANDLE instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *StringEnd;
  CHAR16      CSaved;

  //
  // Create the parent directory
  //
  StringEnd = FileName + EntsStrLen (FileName) - 1;
  while (StringEnd >= FileName) {
    if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
      break;
    }

    StringEnd--;
  }

  if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
    CSaved      = *StringEnd;
    *StringEnd  = L'\0';

    if (EntsStrLen (FileName) != 0) {
      Status = CreateDirectory (RootDir, FileName);
      if (EFI_ERROR (Status)) {
        *StringEnd = CSaved;
        return Status;
      }
    }

    *StringEnd = CSaved;
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
CreateDirectory (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Create a directory.

Arguments:

  RootDir   - Root directory.
  FileName  - File name string.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.
  
--*/
{
  EFI_STATUS      Status;
  CHAR16          *StringEnd;
  CHAR16          CSaved;
  EFI_FILE_HANDLE Handle;

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
  StringEnd = FileName + EntsStrLen (FileName) - 1;
  while (StringEnd >= FileName) {
    if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
      break;
    }

    StringEnd--;
  }

  if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
    CSaved      = *StringEnd;
    *StringEnd  = L'\0';

    if (EntsStrLen (FileName) != 0) {
      Status = CreateDirectory (RootDir, FileName);
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

STATIC
VOID *
__AllocatePool (
  IN UINTN                Size
  )
{
  EFI_STATUS  Status;
  VOID        *p;

  Status = gntBS->AllocatePool (EfiBootServicesData, Size, &p);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "AllocatePool: out of pool  %x\n", Status));
    p = NULL;
  }

  return p;
}

STATIC
VOID
__FreePool (
  IN VOID                 *Buffer
  )
{
  ASSERT (Buffer);
  gntBS->FreePool (Buffer);
}

EFI_MEMORY_DESCRIPTOR *
_LibMemoryMap (
  OUT UINTN               *NoEntries,
  OUT UINTN               *MapKey,
  OUT UINTN               *DescriptorSize,
  OUT UINT32              *DescriptorVersion
  )
{
  EFI_STATUS            Status;
  EFI_MEMORY_DESCRIPTOR *Buffer;
  UINTN                 BufferSize;

  ASSERT (NoEntries != NULL);
  ASSERT (MapKey != NULL);
  ASSERT (DescriptorSize != NULL);
  ASSERT (DescriptorVersion != NULL);
  //
  // Initialize for GrowBuffer loop
  //
  Buffer      = (EFI_MEMORY_DESCRIPTOR *)&Buffer;
  BufferSize  = sizeof (EFI_MEMORY_DESCRIPTOR);

Retry:
  Status = gntBS->GetMemoryMap (
                  &BufferSize,
                  Buffer,
                  MapKey,
                  DescriptorSize,
                  DescriptorVersion
                  );
  if(Status == EFI_BUFFER_TOO_SMALL)
  {
    Buffer = __AllocatePool(BufferSize);
  	goto Retry;
  }

  if(EFI_ERROR(Status)) {
    return NULL;
  }

  //
  // Convert buffer size to NoEntries
  //
  if (!EFI_ERROR (Status)) {
    *NoEntries = BufferSize / *DescriptorSize;
  }

  return Buffer;
}

EFI_STATUS
LibGetFreePages (
  IN UINT64 *NoFreePages
  )
{
  EFI_STATUS              Status;
  UINTN                   Index;
  UINTN                   DescriptorSize;
  UINT32                  DescriptorVersion;
  UINTN                   NoDesc;
  UINTN                   MapKey;
  UINT64                  NoPages[EfiMaxMemoryType];
  EFI_MEMORY_DESCRIPTOR   *Desc;
  EFI_MEMORY_DESCRIPTOR   *MemMap;

  MemMap = NULL;
  Status = EFI_SUCCESS;
  
  MemMap = _LibMemoryMap (&NoDesc, &MapKey, &DescriptorSize, &DescriptorVersion);
  if ((NULL == MemMap) && (NoDesc == 0)) {
    Status = EFI_NOT_FOUND;
    goto Done;
  }

  EntsSetMem (NoPages, EfiMaxMemoryType * sizeof (UINT64) , 0);

  for (Desc = MemMap, Index = 0; Index < NoDesc; Index += 1) {
    NoPages[Desc->Type] += Desc->NumberOfPages;
    Desc = NextMemoryDescriptor (Desc, DescriptorSize);
  }

  *NoFreePages = NoPages[EfiConventionalMemory];

Done:
  if (MemMap != NULL) {
    __FreePool (MemMap);
  }

  return Status;
}
