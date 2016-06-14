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

  EfiCompliantBbTestRequired.c

Abstract:

  Check the required elements in EFI Spec.

--*/

//
// Includes
//

#include "SctLib.h"
#include "EfiCompliantBbTestMain_efi.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (Decompress)
#include EFI_PROTOCOL_DEFINITION (Ebc)

//
// Internal functions declaration
//

EFI_STATUS
CheckSystemTable (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
CheckBootServices (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
CheckRuntimeServices (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
CheckLoadedImageProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
CheckDevicePathProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
CheckDecompressProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
CheckEbcProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// External functions implementation
//

EFI_STATUS
RequiredElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  )
/*++

Routine Description:

  Check the required elements, which defined in the EFI spec 1.10, section
  2.6.1.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;

  //
  // Locate the standard test library protocol
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Check the EFI System Table
  //
  CheckSystemTable (StandardLib);

  //
  // Check the EFI Boot Services
  //
  CheckBootServices (StandardLib);

  //
  // Check the EFI Runtime Services
  //
  CheckRuntimeServices (StandardLib);

  //
  // Check the LOADED_IMAGE Protocol
  //
  CheckLoadedImageProtocol (StandardLib);

  //
  // Check the DEVICE_PATH Protocol
  //
  CheckDevicePathProtocol (StandardLib);

  //
  // Check the DECOMPRESS Protocol
  //
  CheckDecompressProtocol (StandardLib);

  //
  // Check the EBC Interpreter
  //
  CheckEbcProtocol (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

//
// Internal functions implementation
//

EFI_STATUS
CheckSystemTable (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_TEST_ASSERTION  AssertionType;
  UINT32              CRC32;
  UINT32              LocalCRC32;
  EFI_STATUS          Status;

  //
  // Check the EFI System Table
  //
  CRC32 = gtST->Hdr.CRC32;
  gtST->Hdr.CRC32 = 0;

  LocalCRC32 = 0;
  Status = SctCalculateCrc32 ((UINT8 *)gtST, gtST->Hdr.HeaderSize, &LocalCRC32);
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    if ((gtST->Hdr.Signature       == EFI_SYSTEM_TABLE_SIGNATURE      ) &&
        (gtST->Hdr.Revision        >= 0x0001000A                      ) &&
        (gtST->Hdr.Reserved        == 0x00000000                      ) &&
        (gtST->RuntimeServices     != NULL                            ) &&
        (gtST->BootServices        != NULL                            ) &&
        (LocalCRC32                == CRC32)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    gtST->Hdr.CRC32 = CRC32;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid001,
                 L"EFI Compliant - EFI System Table must be implemented",
                 L"%a:%d:Signature - %lX, Expected - %lX",
                 __FILE__,
                 (UINTN)__LINE__,
                 gtST->Hdr.Signature,
                 EFI_SYSTEM_TABLE_SIGNATURE
                 );

  //
  // Record the entire EFI System Table
  //
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  Hdr.Signature        : %lX\n"
                 L"  Hdr.Revision         : %X\n"
                 L"  Hdr.HeaderSize       : %X\n"
                 L"  Hdr.CRC32            : %X\n"
                 L"  Hdr.Reserved         : %X\n",
                 gtST->Hdr.Signature,
                 gtST->Hdr.Revision,
                 gtST->Hdr.HeaderSize,
                 gtST->Hdr.CRC32,
                 gtST->Hdr.Reserved
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  FirmwareVendor       : %s\n"
                 L"  FirmwareRevision     : %X\n"
                 L"  ConsoleInHandle      : %X\n"
                 L"  ConIn                : %X\n"
                 L"  ConsoleOutHandle     : %X\n"
                 L"  ConOut               : %X\n"
                 L"  StandardErrorHandle  : %X\n"
                 L"  StdErr               : %X\n"
                 L"  RuntimeServices      : %X\n"
                 L"  BootServices         : %X\n"
                 L"  NumberOfTableEntries : %X\n"
                 L"  ConfigurationTable   : %X\n",
                 gtST->FirmwareVendor,
                 gtST->FirmwareRevision,
                 gtST->ConsoleInHandle,
                 gtST->ConIn,
                 gtST->ConsoleOutHandle,
                 gtST->ConOut,
                 gtST->StandardErrorHandle,
                 gtST->StdErr,
                 gtST->RuntimeServices,
                 gtST->BootServices,
                 gtST->NumberOfTableEntries,
                 gtST->ConfigurationTable
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
CheckBootServices (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_TEST_ASSERTION  AssertionType;
  UINT32              CRC32;
  UINT32              LocalCRC32;
  EFI_STATUS          Status;

  //
  // Check the EFI Boot Services Table
  //
  CRC32 = gtBS->Hdr.CRC32;
  gtBS->Hdr.CRC32 = 0;

  LocalCRC32 = 0;
  Status = SctCalculateCrc32 ((UINT8 *)gtBS, gtBS->Hdr.HeaderSize, &LocalCRC32);
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    if ((gtBS->Hdr.Signature                       == EFI_BOOT_SERVICES_SIGNATURE) &&
        (gtBS->Hdr.Revision                        >= 0x0001000A                 ) &&
        (gtBS->Hdr.Reserved                        == 0x00000000                 ) &&
        (gtBS->RaiseTPL                            != NULL                       ) &&
        (gtBS->RestoreTPL                          != NULL                       ) &&
        (gtBS->AllocatePages                       != NULL                       ) &&
        (gtBS->FreePages                           != NULL                       ) &&
        (gtBS->GetMemoryMap                        != NULL                       ) &&
        (gtBS->AllocatePool                        != NULL                       ) &&
        (gtBS->FreePool                            != NULL                       ) &&
        (gtBS->CreateEvent                         != NULL                       ) &&
        (gtBS->SetTimer                            != NULL                       ) &&
        (gtBS->WaitForEvent                        != NULL                       ) &&
        (gtBS->SignalEvent                         != NULL                       ) &&
        (gtBS->CloseEvent                          != NULL                       ) &&
        (gtBS->CheckEvent                          != NULL                       ) &&
        (gtBS->InstallProtocolInterface            != NULL                       ) &&
        (gtBS->ReinstallProtocolInterface          != NULL                       ) &&
        (gtBS->UninstallProtocolInterface          != NULL                       ) &&
        (gtBS->HandleProtocol                      != NULL                       ) &&
        (gtBS->RegisterProtocolNotify              != NULL                       ) &&
        (gtBS->LocateHandle                        != NULL                       ) &&
        (gtBS->LocateDevicePath                    != NULL                       ) &&
        (gtBS->InstallConfigurationTable           != NULL                       ) &&
        (gtBS->LoadImage                           != NULL                       ) &&
        (gtBS->StartImage                          != NULL                       ) &&
        (gtBS->Exit                                != NULL                       ) &&
        (gtBS->UnloadImage                         != NULL                       ) &&
        (gtBS->ExitBootServices                    != NULL                       ) &&
        (gtBS->GetNextMonotonicCount               != NULL                       ) &&
        (gtBS->Stall                               != NULL                       ) &&
        (gtBS->SetWatchdogTimer                    != NULL                       ) &&
        (gtBS->ConnectController                   != NULL                       ) &&
        (gtBS->DisconnectController                != NULL                       ) &&
        (gtBS->OpenProtocol                        != NULL                       ) &&
        (gtBS->CloseProtocol                       != NULL                       ) &&
        (gtBS->OpenProtocolInformation             != NULL                       ) &&
        (gtBS->ProtocolsPerHandle                  != NULL                       ) &&
        (gtBS->LocateHandleBuffer                  != NULL                       ) &&
        (gtBS->LocateProtocol                      != NULL                       ) &&
        (gtBS->InstallMultipleProtocolInterfaces   != NULL                       ) &&
        (gtBS->UninstallMultipleProtocolInterfaces != NULL                       ) &&
        (gtBS->CalculateCrc32                      != NULL                       ) &&
        (gtBS->CopyMem                             != NULL                       ) &&
        (gtBS->SetMem                              != NULL                       ) &&
        (LocalCRC32                                == CRC32           )) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  gtBS->Hdr.CRC32 = CRC32;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid002,
                 L"EFI Compliant - EFI Boot Services Table must be implemented",
                 L"%a:%d:Signature - %lX, Expected - %lX",
                 __FILE__,
                 (UINTN)__LINE__,
                 gtBS->Hdr.Signature,
                 EFI_BOOT_SERVICES_SIGNATURE
                 );

  //
  // Record the entire EFI Boot Services Table
  //
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  Hdr.Signature                       : %lX\n"
                 L"  Hdr.Revision                        : %X\n"
                 L"  Hdr.HeaderSize                      : %X\n"
                 L"  Hdr.CRC32                           : %X\n"
                 L"  Hdr.Reserved                        : %X\n",
                 gtBS->Hdr.Signature,
                 gtBS->Hdr.Revision,
                 gtBS->Hdr.HeaderSize,
                 gtBS->Hdr.CRC32,
                 gtBS->Hdr.Reserved
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  RaiseTPL                            : %X\n"
                 L"  RestoreTPL                          : %X\n"
                 L"  AllocatePages                       : %X\n"
                 L"  FreePages                           : %X\n"
                 L"  GetMemoryMap                        : %X\n"
                 L"  AllocatePool                        : %X\n"
                 L"  FreePool                            : %X\n",
                 gtBS->RaiseTPL,
                 gtBS->RestoreTPL,
                 gtBS->AllocatePages,
                 gtBS->FreePages,
                 gtBS->GetMemoryMap,
                 gtBS->AllocatePool,
                 gtBS->FreePool
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  CreateEvent                         : %X\n"
                 L"  SetTimer                            : %X\n"
                 L"  WaitForEvent                        : %X\n"
                 L"  SignalEvent                         : %X\n"
                 L"  CloseEvent                          : %X\n"
                 L"  CheckEvent                          : %X\n",
                 gtBS->CreateEvent,
                 gtBS->SetTimer,
                 gtBS->WaitForEvent,
                 gtBS->SignalEvent,
                 gtBS->CloseEvent,
                 gtBS->CheckEvent
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  InstallProtocolInterface            : %X\n"
                 L"  ReinstallProtocolInterface          : %X\n"
                 L"  UninstallProtocolInterface          : %X\n"
                 L"  HandleProtocol                      : %X\n"
                 L"  Reserved                            : %X\n"
                 L"  RegisterProtocolNotify              : %X\n"
                 L"  LocateHandle                        : %X\n"
                 L"  LocateDevicePath                    : %X\n",
                 gtBS->InstallProtocolInterface,
                 gtBS->ReinstallProtocolInterface,
                 gtBS->UninstallProtocolInterface,
                 gtBS->HandleProtocol,
                 gtBS->Reserved,
                 gtBS->RegisterProtocolNotify,
                 gtBS->LocateHandle,
                 gtBS->LocateDevicePath
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  InstallConfigurationTable           : %X\n",
                 gtBS->InstallConfigurationTable
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  LoadImage                           : %X\n"
                 L"  StartImage                          : %X\n"
                 L"  Exit                                : %X\n"
                 L"  UnloadImage                         : %X\n"
                 L"  ExitBootServices                    : %X\n"
                 L"  GetNextMonotonicCount               : %X\n"
                 L"  Stall                               : %X\n"
                 L"  SetWatchdogTimer                    : %X\n",
                 gtBS->LoadImage,
                 gtBS->StartImage,
                 gtBS->Exit,
                 gtBS->UnloadImage,
                 gtBS->ExitBootServices,
                 gtBS->GetNextMonotonicCount,
                 gtBS->Stall,
                 gtBS->SetWatchdogTimer
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  ConnectController                   : %X\n"
                 L"  DisconnectController                : %X\n"
                 L"  OpenProtocol                        : %X\n"
                 L"  CloseProtocol                       : %X\n"
                 L"  OpenProtocolInformation             : %X\n"
                 L"  ProtocolsPerHandle                  : %X\n"
                 L"  LocateHandleBuffer                  : %X\n"
                 L"  LocateProtocol                      : %X\n",
                 gtBS->ConnectController,
                 gtBS->DisconnectController,
                 gtBS->OpenProtocol,
                 gtBS->CloseProtocol,
                 gtBS->OpenProtocolInformation,
                 gtBS->ProtocolsPerHandle,
                 gtBS->LocateHandleBuffer,
                 gtBS->LocateProtocol
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  InstallMultipleProtocolInterfaces   : %X\n"
                 L"  UninstallMultipleProtocolInterfaces : %X\n",
                 gtBS->InstallMultipleProtocolInterfaces,
                 gtBS->UninstallMultipleProtocolInterfaces
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  CalculateCrc32                      : %X\n"
                 L"  CopyMem                             : %X\n"
                 L"  SetMem                              : %X\n",
                 gtBS->CalculateCrc32,
                 gtBS->CopyMem,
                 gtBS->SetMem
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
CheckRuntimeServices (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_TEST_ASSERTION  AssertionType;
  UINT32              CRC32;
  UINT32              LocalCRC32;
  EFI_STATUS          Status;

  //
  // Check the EFI Runtime Services Table
  //
  CRC32 = gtRT->Hdr.CRC32;
  gtRT->Hdr.CRC32 = 0;

  LocalCRC32 = 0;
  Status = SctCalculateCrc32 ((UINT8 *)gtRT, gtRT->Hdr.HeaderSize, &LocalCRC32);
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    if ((gtRT->Hdr.Signature             == EFI_RUNTIME_SERVICES_SIGNATURE) &&
        (gtRT->Hdr.Revision              >= 0x0001000A                    ) &&
        (gtRT->Hdr.Reserved              == 0x00000000                    ) &&
        (gtRT->GetTime                   != NULL                          ) &&
        (gtRT->SetTime                   != NULL                          ) &&
        (gtRT->GetWakeupTime             != NULL                          ) &&
        (gtRT->SetWakeupTime             != NULL                          ) &&
        (gtRT->SetVirtualAddressMap      != NULL                          ) &&
        (gtRT->ConvertPointer            != NULL                          ) &&
        (gtRT->GetVariable               != NULL                          ) &&
        (gtRT->GetNextVariableName       != NULL                          ) &&
        (gtRT->SetVariable               != NULL                          ) &&
        (gtRT->GetNextHighMonotonicCount != NULL                          ) &&
        (gtRT->ResetSystem               != NULL                          ) &&
        (LocalCRC32                      == CRC32                         )) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  gtRT->Hdr.CRC32 = CRC32;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid003,
                 L"EFI Compliant - EFI Runtime Services Table must be implemented",
                 L"%a:%d:Signature - %lX, Expected - %lX",
                 __FILE__,
                 (UINTN)__LINE__,
                 gtRT->Hdr.Signature,
                 EFI_RUNTIME_SERVICES_SIGNATURE
                 );

  //
  // Record the entire EFI Runtime Services Table
  //
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  Hdr.Signature             : %lX\n"
                 L"  Hdr.Revision              : %X\n"
                 L"  Hdr.HeaderSize            : %X\n"
                 L"  Hdr.CRC32                 : %X\n"
                 L"  Hdr.Reserved              : %X\n",
                 gtRT->Hdr.Signature,
                 gtRT->Hdr.Revision,
                 gtRT->Hdr.HeaderSize,
                 gtRT->Hdr.CRC32,
                 gtRT->Hdr.Reserved
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  GetTime                   : %X\n"
                 L"  SetTime                   : %X\n"
                 L"  GetWakeupTime             : %X\n"
                 L"  SetWakeupTime             : %X\n"
                 L"  SetVirtualAddressMap      : %X\n"
                 L"  ConvertPointer            : %X\n"
                 L"  GetVariable               : %X\n"
                 L"  GetNextVariableName       : %X\n"
                 L"  SetVariable               : %X\n",
                 gtRT->GetTime,
                 gtRT->SetTime,
                 gtRT->GetWakeupTime,
                 gtRT->SetWakeupTime,
                 gtRT->SetVirtualAddressMap,
                 gtRT->ConvertPointer,
                 gtRT->GetVariable,
                 gtRT->GetNextVariableName,
                 gtRT->SetVariable
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"  GetNextHighMonotonicCount : %X\n"
                 L"  ResetSystem               : %X\n",
                 gtRT->GetNextHighMonotonicCount,
                 gtRT->ResetSystem
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
CheckLoadedImageProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  EFI_TEST_ASSERTION          AssertionType;

  //
  // Check the LOADED_IMAGE protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiLoadedImageProtocolGuid,
                   NULL,
                   &LoadedImage
                   );

  if (!EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid004,
                 L"EFI Compliant - LOADED_IMAGE protocol must exist",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
CheckDevicePathProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_TEST_ASSERTION        AssertionType;

  //
  // Originally the test is designed to disconnect all EFI 1.10 drivers and
  // make sure at least one device path exists. But it may change the test
  // environment. So here we didn't disconnect all EFI 1.10 drivers.
  //

  //
  // Check the DEVICE_PATH protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiDevicePathProtocolGuid,
                   NULL,
                   &DevicePath
                   );

  if (!EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid005,
                 L"EFI Compliant - DEVICE_PATH protocol must exist",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
CheckDecompressProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                Status;
  EFI_DECOMPRESS_PROTOCOL   *Decompress;
  EFI_TEST_ASSERTION        AssertionType;

  //
  // Check the DECOMPRESS protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiDecompressProtocolGuid,
                   NULL,
                   &Decompress
                   );

  if ((Status                 == EFI_SUCCESS) &&
      (Decompress->GetInfo    != NULL       ) &&
      (Decompress->Decompress != NULL       )) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid006,
                 L"EFI Compliant - DECOMPRESS protocol must exist",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Record the entire DECOMPRESS protocol
  //
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"  GetInfo    : %X\n"
                   L"  Decompress : %X\n",
                   Decompress->GetInfo,
                   Decompress->Decompress
                   );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
CheckEbcProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_EBC_PROTOCOL    *Ebc;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the EBC Interpreter protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiEbcProtocolGuid,
                   NULL,
                   &Ebc
                   );

  if ((Status                   == EFI_SUCCESS) &&
      (Ebc->CreateThunk         != NULL       ) &&
      (Ebc->UnloadImage         != NULL       ) &&
      (Ebc->RegisterICacheFlush != NULL       ) &&
      (Ebc->GetVersion          != NULL       ))  {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid007,
                 L"EFI Compliant - EBC Interpreter protocol must exist",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Record the entire EBC Interpreter protocol
  //
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"  CreateThunk         : %X\n"
                   L"  UnloadImage         : %X\n"
                   L"  RegisterICacheFlush : %X\n"
                   L"  GetVersion          : %X\n",
                   Ebc->CreateThunk,
                   Ebc->UnloadImage,
                   Ebc->RegisterICacheFlush,
                   Ebc->GetVersion
                   );
  }

  //
  // EBC Image Execution test will be included in the Protocol's Black-Box Test
  //

  //
  // Done
  //
  return EFI_SUCCESS;
}
