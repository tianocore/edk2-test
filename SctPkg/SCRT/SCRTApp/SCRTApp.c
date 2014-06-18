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

  SCRTApp.c

--*/

#include "SCRTApp.h"
#include "ParseConf.h"

EFI_GUID  gRuntimeFuncAddressGuid = RUNTIME_FUNC_ADDRESS_GUID;

VOID
PrintUsage ( 
  VOID
  )
/*++

Routine Description:

  Print usage information for this utility.
  
Arguments:

  NONE

Returns:

  NONE
  
--*/  
{
  SctPrint(L"SCRTApp Usage:\n");
  SctPrint(L"  -f  FileName  FileName is test case configuration file\n");
  SctPrint(L"  -g  FileName  FileName is test case result/log file\n");
  SctPrint(L"Example:\n");
  SctPrint(L"SCRTApp -f SCRT.conf\n");
  SctPrint(L"SCRTApp -g SCRT.log\n");
}


EFI_STATUS
InitializeSCRT (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:

  Go to virtual mode to test the UEFI Runtime Services.

Arguments:

  ImageHandle  - Handle for the image of this driver
  SystemTable  - Pointer to the EFI System Table

Returns:

  EFI_STATUS

--*/
{
  UINTN                   MemoryMapSize;
  UINTN                   VirtualMapSize;
  UINTN                   MapKey;
  UINTN                   DescriptorSize;
  UINTN                   VirtualFunc;
  UINT32                  DescriptorVersion;
  VOID                    *FileBuffer;
  UINTN                   FileSize;
  UINTN                   ArgIndex;
  CHAR16                  **Argv;
  CHAR16                  InfFileName[200];
  BOOLEAN                 GenLogFlag;
  EFI_STATUS              Status;
  MEMORY_FILE             InfMemoryFile;
  EFI_FILE_INFO           *FileInfo;
  CONF_INFO               ConfInfo;
  EFI_FILE_HANDLE         FileHandle;
  EFI_MEMORY_DESCRIPTOR   *MemoryMap;
  EFI_MEMORY_DESCRIPTOR   *TempVirtualMemoryMap;
  EFI_MEMORY_DESCRIPTOR   *VirtualMemoryMap;
  UINTN                   HandOffAddr;
  UINTN                   Index;
  SCRT_STUB_TABLE         *StubTable;
  BOOLEAN                 SctTableFound;
  
  VirtualMapSize        = 0;
  MemoryMapSize         = 0;
  MemoryMap             = NULL;
  FileHandle            = NULL;
  FileInfo              = NULL;
  FileBuffer            = NULL;
  GenLogFlag            = FALSE;
  SctTableFound         = FALSE;
  HandOffAddr            = 0;

  ConfInfo.InfoData = 0;

  SctShellApplicationInit (ImageHandle, SystemTable);
  
  Status = SctShellFilterNullArgs ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Initialize Configuration File Name
  //
  SctStrCpy (InfFileName, L"");

  //
  // Parse the arguments
  //
  SctShellGetArguments (&ArgIndex, &Argv);

  if ((ArgIndex != 3) || ((SctStrCmp (Argv[1], L"-f")) && (SctStrCmp(Argv[1], L"-g")))) {
    SctPrint(L"SCRTApp: invalid option\n");
    PrintUsage ();
    return EFI_INVALID_PARAMETER;
  } else {
    SctStrCpy (InfFileName, Argv[2]);
  }


  if (GenLogFlag) {
    SCRTLogProcess(InfFileName);
  } else {   

    //
    // Open the Configuration file
    //  
    Status = SctOpenFileByName (
               InfFileName,
               &FileHandle,
               EFI_FILE_MODE_READ,
               0
               );
    if (EFI_ERROR (Status)) {
      SctPrint(L"Fail to open the configuration file\n");     
      return Status;
    }
  
    //
    // If the file is directory, abort
    //
    Status = SctGetFileInfo (FileHandle, &FileInfo);
    if (EFI_ERROR (Status)) {
      SctPrint(L"Fail to open the configuration file: %r\n", Status);
      return EFI_ABORTED;
    } else if (FileInfo->Attribute & EFI_FILE_DIRECTORY) {
      SctPrint(L"%s is a directory\n", InfFileName);
      return EFI_ABORTED;
    }

    //
    // Malloc memory for read file.
    //
    FileBuffer = SctAllocatePool (CONF_FILE_SIZE);
    if (FileBuffer == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
  
    FileSize   = CONF_FILE_SIZE;
    Status     = SctReadFile (FileHandle, &FileSize, FileBuffer);
    if (!EFI_ERROR (Status) && (FileSize == 0)) {
      return EFI_NOT_FOUND; 
    }
  
    //
    // Initialize info file structures
    //
    InfMemoryFile.FileImage           = FileBuffer;
    InfMemoryFile.CurrentFilePointer  = FileBuffer;
    InfMemoryFile.Eof                 = (VOID*)((UINTN)FileBuffer + FileSize);
  
    //
    // Parse the FV inf file for header information
    //
    ParseConf (&InfMemoryFile, &ConfInfo);
    //
    // Dont't use FileBuffer any more, Free it.
    //
    SctFreePool (FileBuffer);
  

    for (Index = 0; Index < tST->NumberOfTableEntries; Index++) {
      if (SctCompareGuid (&gRuntimeFuncAddressGuid, &(tST->ConfigurationTable[Index].VendorGuid)) == 0) {
        StubTable = tST->ConfigurationTable[Index].VendorTable;
        if (StubTable->Signature != SCRT_STUB_TABLE_SIGNATURE) {
          SctPrint(L"Find Corrupted SCRT Table!\n");
          return EFI_COMPROMISED_DATA;
        } else {
          SctTableFound =TRUE;
          VirtualFunc = (UINTN)StubTable->FuncAddr;
          SctPrint(L"Find RuntimeFunc @ 0x%x registered in SCRT Table\n",VirtualFunc);        
        }
      }
    }

    if (!SctTableFound) {
      SctPrint(L"Fail to find SCRT Table!\n");
      return EFI_UNSUPPORTED;
    }
  
    //
    // Change RuntimeTestFunc physical address to virtual address in advance. Each Arch, IA32, X64,
    // IPF and ARM  has its own strategy.
    //
    ConvertRuntimeFuncPtr(&VirtualFunc);
  
    //
    // Allocate memory prior to GetMemoryMap. IA32/X64 needs memory for pagetables, and IPF needs for IVA.
    //
    DoMemoryAllocation(VirtualFunc);
  
    //
    // Prepare runtime hand-off information.
    //
    RuntimeHandOff(&ConfInfo, &HandOffAddr);
  
    //
    // First call GetMemoryMap() to query the current System MemoryMap Size.
    //
    tBS->GetMemoryMap (
          &MemoryMapSize,
          MemoryMap,
          &MapKey,
          (VOID *) &DescriptorSize,
          (VOID *) &DescriptorVersion
          );
    //
    // The memory size needs add a constant, because there are two SctAllocatePool ()
    // before the second GetMemoryMap(), the action of allocate pool will increase
    // the MemoryMapSize. The constant of 1024 is enough.
    //
    MemoryMapSize += 1024;
  
    Status = tBS->AllocatePool (
                  EfiRuntimeServicesData,
                  MemoryMapSize,
                  (VOID **)&MemoryMap
                  );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  
    Status = tBS->AllocatePool (
                  EfiRuntimeServicesData,
                  MemoryMapSize,
                  (VOID **)&VirtualMemoryMap
                  );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = tBS->GetMemoryMap (
                  &MemoryMapSize,
                  MemoryMap,
                  &MapKey,
                  (VOID *) &DescriptorSize,
                  (VOID *) &DescriptorVersion
                  );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  
    TempVirtualMemoryMap = VirtualMemoryMap;
    SctZeroMem ((VOID *) VirtualMemoryMap, MemoryMapSize);

    //
    // Change Runtime Usage MemoryMap entry from physical address to virtual address.
    // Each Arch, IA32, X64,IPF and ARM has its own strategy.
    //
    PrepareVirtualAddressMap (MemoryMapSize,DescriptorSize,MemoryMap,TempVirtualMemoryMap, &VirtualMapSize);

    MemoryMapSize = 0;
    MemoryMap = NULL;
    do{
        Status = tBS->GetMemoryMap (
                      &MemoryMapSize,
                      MemoryMap,
                      &MapKey,
                      (VOID *) &DescriptorSize,
                      (VOID *) &DescriptorVersion
                      );
        if (Status == EFI_BUFFER_TOO_SMALL) {
        	MemoryMapSize += 1024;
            Status = tBS->AllocatePool (
                        EfiRuntimeServicesData,
                        MemoryMapSize,
                        (VOID **)&MemoryMap
                        );
          if (!EFI_ERROR (Status)) {

          Status = tBS->GetMemoryMap (
                        &MemoryMapSize,
                        MemoryMap,
                        &MapKey,
                        (VOID *) &DescriptorSize,
                        (VOID *) &DescriptorVersion
                        );
          }
          else{
        	  MemoryMapSize = 0;
        	   MemoryMap = NULL;
          }
        }
        if(!(EFI_ERROR (Status))){
            //
            // Call ExitBootServices to terminate all boot services.
            //
            Status = tBS->ExitBootServices (ImageHandle, MapKey);
            if (EFI_ERROR (Status)){
                MemoryMapSize = 0;
                MemoryMap = NULL;
            }
        }
    }while(EFI_ERROR (Status));

    //
    // Call VirtualAddressMap to change the address of the runtime components of the firmware 
    // to the new virtual address.
    //
    Status = tRT->SetVirtualAddressMap (
                  VirtualMapSize,
                  DescriptorSize,
                  DescriptorVersion,
                  VirtualMemoryMap
                  );
  
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // Enable Virtual addressing mode to invoke Runtime Test Function.
    //
    JumpVirtualMode(VirtualFunc, HandOffAddr);
  
    //
    // Should never be here
    //

  }

  return EFI_SUCCESS;
}
