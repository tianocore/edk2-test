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

  EftpImplement.c

Abstract:

  EAS execution services implementations.

--*/

#include "SctLib.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (Eftp)
#include EFI_PROTOCOL_DEFINITION(ServiceBinding)
#include "Eas.h"
#include "EftpImplement.h"

#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (ManagedNetwork)

STATIC EFI_FILE                     *mRealFileHandle      = NULL;
STATIC UINTN                        mRealFileSize         = 0;
STATIC VOID                         *mRealFileBuffer      = NULL;
STATIC UINT64                       mTransferSize         = 0;

STATIC EFI_MANAGED_NETWORK_PROTOCOL *TmpMnp               = NULL;
STATIC EFI_SERVICE_BINDING_PROTOCOL *TmpMnpSb             = NULL;
STATIC EFI_HANDLE                   TmpMnpInstanceHandle  = NULL;
STATIC EFI_EFTP_PROTOCOL            *EftpIo               = NULL;
STATIC EFI_SERVICE_BINDING_PROTOCOL *TmpEftpSb            = NULL;
STATIC EFI_HANDLE                   TmpEftpInstanceHandle = NULL;

STATIC
UINTN
UnicodeToChar (
  OUT CHAR8  *Dst,
  IN  CHAR16 *Src
  )
/*++

Routine Description:

  UnicodeToChar.

Arguments:

  Dst - Dest char8 string.
  Src - Src char16 string.

Returns:

  Length of string that tranversed.

--*/
{
  UINTN Index;

  for (Index = 0; Index < SctStrLen (Src); Index++) {
    Dst[Index] = (CHAR8) (Src[Index] & 0xff);
  }

  Dst[Index] = 0;
  return Index;
}

STATIC
EFI_STATUS
OpenEftpProtocol (
  VOID
  )
{
  EFI_STATUS                         Status;
  EFI_HANDLE                         ControllerHandle;

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gEfiManagedNetworkServiceBindingProtocolGuid, 
             &ControllerHandle
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = tBS->HandleProtocol (
                 ControllerHandle,
                 &gEfiEftpServiceBindingProtocolGuid,
                 (VOID **)&TmpEftpSb
                 );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"No Eftp driver has found!\n"));
    return Status;
  }

  TmpEftpInstanceHandle = NULL;
  Status      = TmpEftpSb->CreateChild (TmpEftpSb, &TmpEftpInstanceHandle);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Create EFTP child failed with %r.\n", Status));
    return Status;
  }

  Status = tBS->HandleProtocol (
                 TmpEftpInstanceHandle,
                 &gEfiEftpProtocolGuid,
                 (VOID **) &EftpIo
                 );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"OpenEftpProtocol: Get EFI_EFTP_PROTOCOL fail - %r", Status));
    TmpEftpSb->DestroyChild (TmpEftpSb, TmpEftpInstanceHandle);
    return Status;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
CloseEftpProtocol (
  VOID
  )
{
  EFI_STATUS                           Status;

  Status = TmpEftpSb->DestroyChild (TmpEftpSb, TmpEftpInstanceHandle);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CloseMnpProtocol: DestroyChild error ! - %r\n", Status));
    return Status;
  }

  EftpIo                 = NULL;
  TmpEftpSb              = NULL;
  TmpEftpInstanceHandle  = NULL;

  return EFI_SUCCESS;

}

//
// Internal Function
//
STATIC
EFI_STATUS
OpenRealFile (
  IN EFI_HANDLE          Handle,
  IN CHAR16              *FileName,
  OUT EFI_FILE           **FileHandle
  )
/*++

Routine Description:

  Open Real file by name.

Arguments:

  Handle      - File handler.
  FileName    - File name string.
  FileHandle  - Pointer to EFI_FILE instance.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  Others                - Some failure happened.
  
--*/
{
  EFI_LOADED_IMAGE_PROTOCOL       *Image;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  EFI_HANDLE                      DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFileSystem;
  EFI_FILE                        *Root;
  EFI_STATUS                      Status;

  Status = tBS->HandleProtocol (
                mImageHandle,
                &gEfiLoadedImageProtocolGuid,
                (VOID **)&Image
                );
  if (EFI_ERROR (Status)) {
    SctPrint (L"Error: HandleProtocol LoadedImage ! - %r\n", Status);
    return Status;
  }

  Status = tBS->HandleProtocol (
                Image->DeviceHandle,
                &gEfiDevicePathProtocolGuid,
                (VOID **)&DevicePath
                );
  if (EFI_ERROR (Status)) {
    SctPrint (L"Error: HandleProtocol DevicePath ! - %r\n", Status);
    return Status;
  }

  Status = tBS->LocateDevicePath (
                &gEfiSimpleFileSystemProtocolGuid,
                &DevicePath,
                &DeviceHandle
                );
  if (EFI_ERROR (Status)) {
    SctPrint (L"Error: LocateDevicePath SimpleFileSystem ! - %r\n", Status);
    return Status;
  }

  Status = tBS->HandleProtocol (
                DeviceHandle,
                &gEfiSimpleFileSystemProtocolGuid,
                (VOID *) &SimpleFileSystem
                );
  if (EFI_ERROR (Status)) {
    SctPrint (L"Error: HandleProtocol SimpleFileSystem ! - %r\n", Status);
    return Status;
  }

  Status = SimpleFileSystem->OpenVolume (
                              SimpleFileSystem,
                              &Root
                              );
  if (EFI_ERROR (Status)) {
    SctPrint (L"Error: SimpleFileSystem->OpenVolume() ! - %r\n", Status);
    return Status;
  }

  Status = Root->Open (
                  Root,
                  FileHandle,
                  FileName,
                  EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
                  0
                  );
  if (EFI_ERROR (Status)) {
    SctPrint (L"Error: Root->Open() ! - %r\n", Status);
    return Status;
  }

  Status = Root->Close (Root);
  if (EFI_ERROR (Status)) {
    SctPrint (L"Error: Root->Close() ! - %r\n", Status);
    return Status;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
CloseRealFile (
  IN EFI_FILE           *FileHandle
  )
/*++

Routine Description:

  Close real file by handler.

Arguments:

  FileHandle  - Pointer to EFI_FILE instance.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  Others                - Some failure happened.
  
--*/
{
  if (mRealFileBuffer != NULL) {
    SctFreePool (mRealFileBuffer);
    mRealFileBuffer = NULL;
  }

  if (FileHandle != NULL) {
    FileHandle->Close (FileHandle);
    FileHandle = NULL;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
WriteRealFile (
  IN EFI_FILE        *FileHandle,
  IN UINTN           *FileSize,
  IN VOID            *FileBuffer
  )
/*++

Routine Description:

  Write filebuffer intot realfile.

Arguments:

  FileHandle  - Pointer to EFI_FILE instance.
  FileSize    - Fill buffer size to be written.
  FileBuffer  - Buffer to be written.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  Others                - Some failure happened.
  
--*/
{
  EFI_STATUS  Status;

  //
  // Write the data to the file
  //
  Status = FileHandle->Write (
                        FileHandle,
                        FileSize,
                        FileBuffer
                        );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
ReadRealFile (
  IN EFI_FILE        *FileHandle,
  OUT UINTN          *FileSize,
  OUT VOID           **FileBuffer
  )
/*++

Routine Description:

  Read real file into filebuffer.

Arguments:

  FileHandle  - Pointer to EFI_FILE instance.
  FileSize    - Fill buffer size to be written.
  FileBuffer  - Buffer to be written.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_OUT_OF_RESOURCES  - FileInfo is NULL.
  Others                - Some failure happened.
  
--*/
{
  EFI_FILE_INFO *FileInfo;
  UINTN         BufferSize;
  EFI_STATUS    Status;

  //
  // Get file information
  //
  FileInfo    = NULL;
  BufferSize  = sizeof (EFI_FILE_INFO) + 1024;
  FileInfo    = EntsAllocatePool (BufferSize);
  if (FileInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SctSetMem (FileInfo, BufferSize, 0);

  Status = FileHandle->GetInfo (
                        FileHandle,
                        &gEfiFileInfoGuid,
                        &BufferSize,
                        (VOID *) FileInfo
                        );
  if (EFI_ERROR (Status)) {
    SctFreePool (FileInfo);
    return Status;
  }
  //
  // Allocate buffer according to file size
  //
  *FileSize   = (UINTN) (FileInfo->FileSize);
  *FileBuffer = EntsAllocatePool (*FileSize);
  if (*FileBuffer == NULL) {
    SctFreePool (FileInfo);
    return EFI_OUT_OF_RESOURCES;
  }

  EntsFreePool (FileInfo);
  SctSetMem (*FileBuffer, *FileSize, 0);

  //
  // Read the data to the buffer
  //
  Status = FileHandle->Read (
                        FileHandle,
                        FileSize,
                        *FileBuffer
                        );
  if (EFI_ERROR (Status)) {
    EntsFreePool (*FileBuffer);
    return Status;
  }

  return EFI_SUCCESS;
}
//
// External Function Implementation
//
EFI_STATUS
EftpDispatchFileTransferComd (
  ENTS_CMD_TYPE Operation
  )
/*++

Routine Description:

  Dispatch an get_file command, download file from SCT management side.

Arguments:

  Operation - Operation type, defined in ENTS_CMD_TYPE.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_UNSUPPORTED       - File was not supported.
  Others                - Some failure happened.

--*/
{
  EFI_STATUS                        Status;
  EFI_EFTP_TOKEN                    Token;
  EFI_EFTP_CONFIG_DATA              EftpCfgData;
  CHAR8                             FileName[MAX_FILENAME_LEN];
  CHAR8                             ModeStr[MAX_MODE_STR_LEN];
  UINTN                             MacAddrLen;

  //
  // Open file to be transferred.
  //
  Status = OpenRealFile (mImageHandle, (gEasFT->Cmd)->ComdArg, &mRealFileHandle);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"File %s is not supported.\n", (gEasFT->Cmd)->ComdArg));
    return EFI_UNSUPPORTED;
  }

  //
  // ReadRealFile for PUT_FILE
  //
  if (Operation == PUT_FILE) {
    Status = ReadRealFile (mRealFileHandle, &mRealFileSize, &mRealFileBuffer);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Real File Error - %r\n", Status));
      Status = EFI_UNSUPPORTED;
      goto Cleanup1;
    }
  }

  Status = GetMacAddress(EftpCfgData.SrcMac);
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"EftpDispatchFileTransferComd: GetMacAddress - %r", Status));
    return Status;
  }

  EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"EftpCfgData.SrcMac :%x:%x:%x:%x:%x:%x",
    EftpCfgData.SrcMac[0], EftpCfgData.SrcMac[1],
    EftpCfgData.SrcMac[2], EftpCfgData.SrcMac[3],
    EftpCfgData.SrcMac[4], EftpCfgData.SrcMac[5]
    ));

  //
  // GetVariable from ENTS_SERVER_MAC_ADDRESS_NAME to get ServerMac address
  // It was recorded once MnpMonitor receive the first packet from server.
  //
  MacAddrLen = NET_ETHER_ADDR_LEN;
  Status = GetContextRecord(
             gntDevicePath,
             SCT_PASSIVE_MODE_RECORD_FILE,
             ENTS_SERVER_MAC_ADDRESS_NAME,
             &MacAddrLen,
             &EftpCfgData.DstMac
             );
  if(EFI_ERROR(Status)) {
  	EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"EftpDispatchFileTransferComd: GetContextRecord fail - %r", Status));
    goto Cleanup1;
  }

  EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"EftpCfgData.DstMac :%x:%x:%x:%x:%x:%x",
    EftpCfgData.DstMac[0], EftpCfgData.DstMac[1],
    EftpCfgData.DstMac[2], EftpCfgData.DstMac[3],
    EftpCfgData.DstMac[4], EftpCfgData.DstMac[5]
    ));

  Status = OpenEftpProtocol ();
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"OpenEftpProtocol fail - %r", Status));
    goto Cleanup1;
  }

  //
  // Set Time event (Optional)
  //
  //
  // Configure EFTP protocol instance.
  //
  EftpCfgData.TimeoutValue  = EFTP_DEFAULT_TIMEOUT_VALUE;
  EftpCfgData.TryCount      = EFTP_DEFAULT_RETRY_VALUE;

  Status                    = EftpIo->Configure (EftpIo, &EftpCfgData);
  if (EFI_ERROR (Status)) {
    SctPrint (L"Eftp->Configure return %r.\n", Status);
    goto Cleanup2;
  }

  SctCopyMem (ModeStr, "octet", 6);

  if (SctStrLen ((gEasFT->Cmd)->ComdArg) > MAX_FILENAME_LEN) {
    SctPrint (L"Too long Filename.\n");
    goto Cleanup2;
  }

  UnicodeToChar (FileName, (gEasFT->Cmd)->ComdArg);
  Token.Filename        = FileName;
  Token.OverrideData    = NULL;
  Token.ModeStr         = ModeStr;
  Token.OptionCount     = 0;
  Token.OptionList      = NULL;
  Token.Context         = NULL;
  Token.TimeoutCallback = NULL;
  Token.BufferSize      = 0;
  Token.Buffer          = NULL;
  Token.CheckPacket     = NULL;
  Token.PacketNeeded    = NULL;

Operation_start:
  //
  // User Synchronize mode to download file.
  //
  Token.Event = NULL;

  switch (Operation) {

  case GET_FILE:
    //
    // Download file
    //
    Token.CheckPacket = NULL;
    Token.BufferSize  = MAX_REAL_FILE_SIZE;
    Token.Buffer      = EntsAllocatePool ((UINTN) Token.BufferSize);

    SctPrint (L"Begin download ... ");
    Status = EftpIo->ReadFile (EftpIo, &Token);
    if (EFI_ERROR (Status)) {
      SctPrint (L"EftpIo ReadFile return %r.\n", Status);
    }

    SctPrint (L"End download ! ");

    if (!EFI_ERROR (Status)) {
      //
      // write real file
      //
      mRealFileSize = (UINTN) Token.BufferSize;
      Status        = WriteRealFile (mRealFileHandle, &mRealFileSize, Token.Buffer);
      if (EFI_ERROR (Status)) {
        SctPrint (L"Write File Error - %r\n", Status);
      }

      if (Token.Buffer != NULL) {
        SctFreePool (Token.Buffer);
      }

    } else if (Status == EFI_BUFFER_TOO_SMALL) {
      mTransferSize = MAX_REAL_FILE_SIZE;
      SctPrint (L"Buffer too small, try to allocate a larger buffer(%ld).\n", mTransferSize);
      Token.Buffer = EntsAllocatePool ((UINTN) mTransferSize);
      if (Token.Buffer == NULL) {
        SctPrint (L"Allocate buffer (%ld bytes) failed.\n", mTransferSize);
        goto Cleanup2;
      }

      Token.Status = EFI_SUCCESS;
      goto Operation_start;
    } else if (EFI_ERROR (Status)) {
      SctPrint (L"Download error - %r\n", Status);
    }

    break;

  case PUT_FILE:
    //
    // Upload file
    //
    Token.PacketNeeded  = NULL;
    mTransferSize       = mRealFileSize;
    Token.Buffer        = EntsAllocatePool ((UINTN) mRealFileSize);
    if (Token.Buffer == NULL) {
      SctPrint (L"Allocate buffer (%ld bytes) failed.\n", mRealFileSize);
      goto Cleanup2;
    }

    Token.BufferSize = mRealFileSize;
    SctCopyMem (Token.Buffer, mRealFileBuffer, (UINTN) mRealFileSize);

    SctPrint (L"Begin upload ... ");
    Status = EftpIo->WriteFile (EftpIo, &Token);
    if (EFI_ERROR (Status)) {
      SctPrint (L"WriteFile return %r.\n", Status);
    }

    SctPrint (L"End upload ! ");

    if (Token.Buffer != NULL) {
      EntsFreePool (Token.Buffer);
    }

    if (EFI_ERROR (Status)) {
      SctPrint (L"Upload error - %r\n", Status);
    }
    break;

  default:
    break;
  }

Cleanup2:
  CloseEftpProtocol();
Cleanup1:
  CloseRealFile (mRealFileHandle);
  return Status;
}
