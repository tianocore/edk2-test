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

  EfiCompliantBbTestRequired.c

Abstract:

  Check the required elements in EFI Spec.

--*/

//
// Includes
//

#include "SctLib.h"
#include "EfiCompliantBbTestMain_uefi.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (Decompress)
#include EFI_PROTOCOL_DEFINITION (DevicePathUtilities)

EFI_GUID gGlobalVariableGuid = EFI_GLOBAL_VARIABLE;

#define  GlobalVariableNum    32
#define  MAX_BUFFER_SIZE      1024

typedef struct _VARIABLE_PAIR {
  CHAR16    Name[30];
  UINT32    Attributes;
} VARIABLE_PAIR;

VARIABLE_PAIR  VariableArray[GlobalVariableNum] = {
  {L"LangCodes",                                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"Lang",                 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"Timeout",              EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"PlatformLangCodes",                                EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"PlatformLang",         EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"ConIn",                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"ConOut",               EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"ErrOut",               EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"ConInDev",                                         EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"ConOutDev",                                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"ErrOutDev",                                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"Boot",                 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"BootOrder",            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"BootNext",             EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"BootCurrent",                                      EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"BootOptionSupport",                                EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"Driver",               EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"DriverOrder",          EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"Key",                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"HwErrRecSupport",      EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"SetupMode",                                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"KEK",                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS},
  {L"PK",                   EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS},
  {L"SignatureSupport",                                 EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"SecureBoot",                                       EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"KEKDefault",                                       EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"PKDefault",                                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"dbDefault",                                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"dbxDefault",                                       EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"OsIndicationsSupported",                           EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"OsIndications",        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS},
  {L"VendorKeys",                                       EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS}
};

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
CheckDevicePathUtilityProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
CheckGloballyDefinedVariables(
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
                   (VOID **)&StandardLib
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
  // Check the Device Path Utility Protocol
  //
  CheckDevicePathUtilityProtocol (StandardLib);
  
  //
  // Check Globally Defined Variables
  //
  CheckGloballyDefinedVariables(StandardLib);

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
        (gtST->Hdr.Revision        >= 0x00020000                      ) &&
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
                 L"UEFI Compliant - EFI System Table must be implemented",
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
        (gtBS->Hdr.Revision                        >= 0x00020000                 ) &&
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
        (gtBS->CreateEventEx                       != NULL                       ) &&
        (LocalCRC32                                == CRC32                      )) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    gtBS->Hdr.CRC32 = CRC32;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid002,
                 L"UEFI Compliant - EFI Boot Services Table must be implemented",
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
  // Check new boot service introduced by UEFI spec
  //
  if (gtBS->Hdr.Revision >= 0x00020000) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"  CreateEventEx                       : %X\n", 
                   gtBS->CreateEventEx
                   );
  } else {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"  CreateEventEx                       : Not available\n"
                   );
  }


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
        (gtRT->Hdr.Revision              >= 0x00020000                    ) &&
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
        (gtRT->QueryVariableInfo         != NULL                          ) &&
        (gtRT->QueryCapsuleCapabilities  != NULL                          ) &&
        (gtRT->UpdateCapsule             != NULL                          ) &&
        (LocalCRC32                      == CRC32                         )) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    gtRT->Hdr.CRC32 = CRC32;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid003,
                 L"UEFI Compliant - EFI Runtime Services Table must be implemented",
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
  // Check new runtime service introduced by UEFI spec
  //
  if (gtRT->Hdr.Revision >= 0x00020000) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"  QueryVariableInfo         : %X\n"
                   L"  QueryCapsuleCapabilities  : %X\n"
                   L"  UpdateCapsule             : %X\n", 
                   gtRT->QueryVariableInfo,
                   gtRT->QueryCapsuleCapabilities,
                   gtRT->UpdateCapsule
                   );
  } else {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"  QueryVariableInfo         : Not available\n"
                   L"  QueryCapsuleCapabilities  : Not available\n"
                   L"  UpdateCapsule             : Not available\n"
                   );
  }
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
                   (VOID **)&LoadedImage
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
                 L"UEFI Compliant - LOADED_IMAGE protocol must exist",
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
                   (VOID **)&DevicePath
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
                 L"UEFI Compliant - DEVICE_PATH protocol must exist",
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
                   (VOID **)&Decompress
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
                 L"UEFI Compliant - DECOMPRESS protocol must exist",
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
CheckDevicePathUtilityProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                           Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DPathUtility;
  EFI_TEST_ASSERTION                  AssertionType;

  //
  // Check the Device Path Utility protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiDevicePathUtilitiesProtocolGuid,
                   NULL,
                   (VOID **)&DPathUtility
                   );

  if ((Status                                   == EFI_SUCCESS) &&
      (DPathUtility->GetDevicePathSize          != NULL       ) &&
      (DPathUtility->DuplicateDevicePath        != NULL       ) &&
      (DPathUtility->AppendDevicePath           != NULL       ) &&
      (DPathUtility->AppendDeviceNode           != NULL       ) &&
      (DPathUtility->AppendDevicePathInstance   != NULL       ) &&
      (DPathUtility->GetNextDevicePathInstance  != NULL       ) &&
      (DPathUtility->IsDevicePathMultiInstance  != NULL       ) &&
      (DPathUtility->CreateDeviceNode           != NULL       ))  {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestRequiredAssertionGuid008,
                 L"UEFI Compliant - DevicePathUtility",
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
                   L"  GetDevicePathSize         : %X\n"
                   L"  DuplicateDevicePath       : %X\n"
                   L"  AppendDevicePath          : %X\n"
                   L"  AppendDeviceNode          : %X\n",
                   L"  AppendDevicePathInstance  : %X\n"
                   L"  GetNextDevicePathInstance : %X\n"
                   L"  IsDevicePathMultiInstance : %X\n"
                   L"  CreateDeviceNode          : %X\n",
                   DPathUtility->GetDevicePathSize,
                   DPathUtility->DuplicateDevicePath,
                   DPathUtility->AppendDevicePath,
                   DPathUtility->AppendDeviceNode,
                   DPathUtility->AppendDevicePathInstance,
                   DPathUtility->GetNextDevicePathInstance,
                   DPathUtility->IsDevicePathMultiInstance,
                   DPathUtility->CreateDeviceNode
                   );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CheckGloballyDefinedVariables(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{

  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  UINTN                 VariableNameSize;
  CHAR16                VariableName[MAX_BUFFER_SIZE];
  CHAR16                *VariableNamePtr;
  CHAR16                C;
  EFI_GUID              VendorGuid;
  UINT32                Index;
  UINT32                CharIndex;
  UINT32                Attribute;
  UINTN                 DataSize;
  VOID                  *Data;

  BOOLEAN               Found;
  BOOLEAN               Pass;

  //
  // Walk through the entire variable list
  //
  VariableName[0] = L'\0';

  DataSize        = 0;
  Data            = NULL;
  Pass            = TRUE;

  while (TRUE) {
    VariableNameSize = MAX_BUFFER_SIZE * sizeof (CHAR16);
    AssertionType    = EFI_TEST_ASSERTION_PASSED;
    Status = gtRT->GetNextVariableName (
                     &VariableNameSize,         // VariableNameSize
                     VariableName,              // VariableName
                     &VendorGuid                // VendorGuid
                     );

    if (EFI_ERROR(Status)) {
      break;
    }

    VariableNamePtr = VariableName;

    if ( SctCompareGuid (&VendorGuid, &gGlobalVariableGuid) == 0 ) {
      
      Found = FALSE;
      
      for (Index = 0; Index < GlobalVariableNum; Index++) {
        if ((SctStrCmp (VariableNamePtr, VariableArray[Index].Name) == 0)) {
          Found  = TRUE;
          Status = gtRT->GetVariable (
                            VariableName,
                            &gGlobalVariableGuid,
                            &Attribute,
                            &DataSize,
                            Data
                            );

          if (Status == EFI_BUFFER_TOO_SMALL) {
            if (Data != NULL) {
              gtBS->FreePool (Data);
            }
            gtBS->AllocatePool (
                    EfiBootServicesData,
                    DataSize, 
                    &Data
                    );
          
            Status = gtRT->GetVariable (
                             VariableName,
                             &gGlobalVariableGuid,
                             &Attribute,
                             &DataSize,
                             Data
                             );
          }
          
          gtBS->FreePool (Data);
          Data     = NULL;
          DataSize = 0;
          
          if (Attribute != VariableArray[Index].Attributes) {
            AssertionType   = EFI_TEST_ASSERTION_FAILED;
            //
            // Record the info, include variable name / attributes
            //
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"VariableName: %s, VariableAttribute: 0x%08x, Correct Attribute: 0x%08x\n",
                           VariableName,
                           Attribute,
                           VariableArray[Index].Attributes
                           );
            break;
          } else {
            break;
          }
        } else if (SctStrnCmp (VariableNamePtr, L"Boot", 4) == 0) {
          if ((SctStrnCmp (VariableNamePtr, L"BootOrder", 9) == 0) ||
            (SctStrnCmp (VariableNamePtr, L"BootNext", 8) == 0) ||
            (SctStrnCmp (VariableNamePtr, L"BootCurrent", 11) == 0) ||
            (SctStrnCmp (VariableNamePtr, L"BootOptionSupport", 17) == 0)) {
            continue;
            }

          Found = TRUE;
          
          VariableNamePtr += 4;
          for (CharIndex = 0; CharIndex < 4; CharIndex++) {
            C = *VariableNamePtr;
            if ((C >= '0'  &&  C <= '9')  ||  (C >= 'A'  &&  C <= 'F')) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
            VariableNamePtr++;
          }
          
          if (AssertionType == EFI_TEST_ASSERTION_PASSED && *VariableNamePtr != L'\0') {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
          if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
            //
            // Record the info, include variable name
            //
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"VariableName: %s\n",
                           VariableName
                           );
            break;
          }

          if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
            Status = gtRT->GetVariable (
                             VariableName,
                             &gGlobalVariableGuid,
                             &Attribute,
                             &DataSize,
                             Data
                             );

            if (Status == EFI_BUFFER_TOO_SMALL) {
              if (Data != NULL) {
                gtBS->FreePool (Data);
              }
              gtBS->AllocatePool (
                      EfiBootServicesData, 
                      DataSize, 
                      &Data
                      );
          
              Status = gtRT->GetVariable (
                               VariableName,
                               &gGlobalVariableGuid,
                               &Attribute,
                               &DataSize,
                               Data
                               );
            }
            gtBS->FreePool (Data);
            Data     = NULL;
            DataSize = 0;
            
            if (Attribute != VariableArray[11].Attributes) {
              AssertionType   = EFI_TEST_ASSERTION_FAILED;
              //
              // Record the info, include variable name / attributes
              //
              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_DEFAULT,
                             L"VariableName: %s, VariableAttribute: 0x%08x, Correct Attribute: 0x%08x\n",
                             VariableName,
                             Attribute,
                             VariableArray[11].Attributes
                             );
              break;
            } else {
              break;
            }
          }
        } else if (SctStrnCmp (VariableNamePtr, L"Driver", 6) == 0) {
          if (SctStrnCmp (VariableNamePtr, L"DriverOrder", 11) == 0) {
            continue;
          } 

          Found = TRUE;

          VariableNamePtr += 6;
          for (CharIndex = 0; CharIndex < 4; CharIndex++) {
            C = *VariableNamePtr;
            if ((C >= '0'  &&  C <= '9')  ||  (C >= 'A'  &&  C <= 'F')) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
            VariableNamePtr++;
          }

          if (AssertionType == EFI_TEST_ASSERTION_PASSED && *VariableNamePtr != L'\0') {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
          if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
            //
            // Record the info, include variable name
            //
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"VariableName: %s\n",
                           VariableName
                           );
            break;
          }
          
          if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
            Status = gtRT->GetVariable (
                             VariableName,
                             &gGlobalVariableGuid,
                             &Attribute,
                             &DataSize,
                             Data
                             );

            if (Status == EFI_BUFFER_TOO_SMALL) {
              if (Data != NULL) {
                gtBS->FreePool (Data);
              }
              gtBS->AllocatePool (
                      EfiBootServicesData, 
                      DataSize, 
                      &Data
                      );
          
              Status = gtRT->GetVariable (
                               VariableName,
                               &gGlobalVariableGuid,
                               &Attribute,
                               &DataSize,
                               Data
                               );
            }

            gtBS->FreePool (Data);
            Data     = NULL;
            DataSize = 0;
            
            if (Attribute != VariableArray[16].Attributes) {
              AssertionType   = EFI_TEST_ASSERTION_FAILED;
              //
              // Record the info, include variable name / attributes
              //
              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_DEFAULT,
                             L"VariableName: %s, VariableAttribute: 0x%08x, Correct Attribute: 0x%08x\n",
                             VariableName,
                             Attribute,
                             VariableArray[16].Attributes
                             );
              break;
            } else {
              break;
            }
          }
        } else if (SctStrnCmp (VariableNamePtr, L"Key", 3) == 0) {

          Found = TRUE;

          VariableNamePtr += 3;
          for (CharIndex = 0; CharIndex < 4; CharIndex++) {
            C = *VariableNamePtr;
            if ((C >= '0'  &&  C <= '9')  ||  (C >= 'A'  &&  C <= 'F')) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
            VariableNamePtr++;
          }

          if (AssertionType == EFI_TEST_ASSERTION_PASSED && *VariableNamePtr != L'\0') {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
          
          if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
            //
            // Record the info, include variable name
            //
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"VariableName: %s\n",
                           VariableName
                           );
            break;
          }
          
          if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
            Status = gtRT->GetVariable (
                             VariableName,
                             &gGlobalVariableGuid,
                             &Attribute,
                             &DataSize,
                             Data
                             );

            if (Status == EFI_BUFFER_TOO_SMALL) {
              if (Data != NULL) {
                gtBS->FreePool (Data);
              }
              gtBS->AllocatePool (
                      EfiBootServicesData, 
                      DataSize, 
                      &Data
                      );
          
              Status = gtRT->GetVariable (
                               VariableName,
                               &gGlobalVariableGuid,
                               &Attribute,
                               &DataSize,
                               Data
                               );
            }
            gtBS->FreePool (Data);
            Data     = NULL;
            DataSize = 0;
            
            if (Attribute != VariableArray[18].Attributes) {
              AssertionType   = EFI_TEST_ASSERTION_FAILED;
              //
              // Record the info, include variable name / attributes
              //
              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_DEFAULT,
                             L"VariableName: %s, VariableAttribute: 0x%08x, Correct Attribute: 0x%08x\n",
                             VariableName,
                             Attribute,
                             VariableArray[18].Attributes
                             );
              break;
            } else {
              break;
            }
          }
        } else {
          continue;
        }
        
      }  // End for loop 

      //
      // The Golabl Variable is not defined in Spec
      //
      if (Found == FALSE && AssertionType == EFI_TEST_ASSERTION_PASSED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"VariableName: %s  is not defined in the Spec\n",
                       VariableName
                       );
      }
    }// End if loop compare guid
    
    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiCompliantBbTestRequiredAssertionGuid009,
                     L"UEFI Compliant - Globally Defined Variables",
                     L"%a:%d, Illegal Variable : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     VariableName
                     );
      Pass = FALSE;
    }

  }// End while loop
  
  if (AssertionType == EFI_TEST_ASSERTION_PASSED && Pass == TRUE) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestRequiredAssertionGuid009,
                   L"UEFI Compliant - Globally Defined Variables",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   ); 
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
