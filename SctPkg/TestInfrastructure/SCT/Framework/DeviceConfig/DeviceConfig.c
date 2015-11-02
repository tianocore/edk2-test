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

  DeviceConfig.c

Abstract:

  This file provides the services for gathering the device configuration.

--*/

#include "Sct.h"

#include EFI_PROTOCOL_DEFINITION (PciIo)

#define EFI_SCT_SECTION_DEVICE_CONFIG       L"Device Configuration"

#define SCAN_DEVICES_ALL                    0
#define SCAN_DEVICES_WITH_OPTION_ROM        1

//
// Format in the configuration file:
//
// [Device Configuration]
// DevicePath          = <string>
// DeviceType          = < SCSI Raid | SCSI Fiber | NIC | USB  |
//                         Video     | Serial     | PCI | Other >
// DriverBinding       = <Yes/No>
// DriverDiagnostics   = <Yes/No>
// DriverConfiguration = <Yes/No>
// UnloadSupported     = <Yes/No>
// RuntimeSupported    = <Yes/No>
//

//
// Internal function declaration
//

EFI_STATUS
PageBreakPrint (
  IN BOOLEAN                Init,
  IN CHAR16                 *String
  );

EFI_STATUS
DeviceConfigHelp (
  VOID
  );

EFI_STATUS
DeviceConfigInsert (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINTN                  HandleIndex
  );

EFI_STATUS
DeviceConfigList (
  IN EFI_INI_FILE_HANDLE    IniFile
  );

EFI_STATUS
DeviceConfigRemove (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINTN                  OrderIndex
  );

EFI_STATUS
DeviceConfigScan (
  IN UINTN                  ScanType
  );

EFI_STATUS
DeviceConfigVerbose (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINTN                  OrderIndex
  );

EFI_STATUS
DeviceConfigScanDrivers (
  IN EFI_HANDLE             Handle
  );

BOOLEAN
DeviceConfigInsertHandle (
  IN OUT UINTN              *NoHandles,
  IN OUT EFI_HANDLE         *HandleBuffer,
  IN EFI_HANDLE             Handle
  );

EFI_STATUS
DeviceConfigParser (
  IN  CHAR16                *String,
  OUT CHAR16                *Option,
  OUT UINTN                 *Index
  );

EFI_STATUS
DeviceConfigGetOrderNum (
  IN EFI_INI_FILE_HANDLE    IniFile,
  OUT UINT32                *OrderNum
  );

EFI_STATUS
DeviceConfigRmSection (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order
  );

EFI_STATUS
DeviceConfigGetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  OUT CHAR16                *Buffer
  );

EFI_STATUS
DeviceConfigSetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  IN CHAR16                 *Buffer
  );

//
// External function implementation
//

EFI_STATUS
SctDeviceConfig (
  VOID
  )
{
  EFI_STATUS            Status;
  CHAR16                *FileName;
  CHAR16                InputBuffer[11];
  CHAR16                Option;
  UINTN                 Index;
  EFI_INI_FILE_HANDLE   IniFile;

  //
  // Enable cursor
  //
  tST->ConOut->EnableCursor (tST->ConOut, TRUE);

  //
  // Create the name of device configuration file
  //
  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_DEVICE_CONFIG
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Open the device configuration file
  //
  Status = gFT->TplProtocol->EfiIniOpen (
                               gFT->TplProtocol,
                               gFT->DevicePath,
                               FileName,
                               &IniFile
                               );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open device config file - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // Not exist, create the device configuration file
    //
    Status = gFT->TplProtocol->EfiIniCreate (
                                 gFT->TplProtocol,
                                 gFT->DevicePath,
                                 FileName,
                                 &IniFile
                                 );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create device config file - %r", Status));
      tBS->FreePool (FileName);
      return Status;
    }
  }

  tBS->FreePool (FileName);

  //
  // Print out the help information
  //
  DeviceConfigHelp ();

  while (TRUE) {
    //
    // Let user choose the operation
    //
    SctInput (L"-", InputBuffer, 10);
    SctPrint (L"\n");

    DeviceConfigParser (InputBuffer, &Option, &Index);

    //
    // Quit
    //
    if ((Option == L'Q') || (Option == L'q')) {
      break;
    }

    switch (Option) {
    //
    // Scan all devices in the system
    //
    case L'S':
    case L's':
      DeviceConfigScan (Index);
      break;

    //
    // List all devices in the configuration file
    //
    case L'L':
    case L'l':
      DeviceConfigList (IniFile);
      break;

    //
    // Insert one device into the configuration file
    //
    case L'I':
    case L'i':
      DeviceConfigInsert (IniFile, Index);
      break;

    //
    // Remove one device from the configuration file
    //
    case L'R':
    case L'r':
      DeviceConfigRemove (IniFile, Index);
      break;

    //
    // Show verbose information from the configuration file
    //
    case L'V':
    case L'v':
      DeviceConfigVerbose (IniFile, Index);
      break;

    //
    // Help information
    //
    case L'H':
    case L'h':
    case L'?':
      DeviceConfigHelp ();
      break;

    //
    // Others
    //
    default:
      break;
    }
  }

  //
  // Close the device configuration file
  //
  gFT->TplProtocol->EfiIniClose (
                      gFT->TplProtocol,
                      IniFile
                      );

  //
  // Done
  //
  return Status;
}

//
// Internal function implementation
//

EFI_STATUS
PageBreakPrint (
  IN BOOLEAN                Init,
  IN CHAR16                 *String
  )
{
  static UINTN    Row;
  EFI_STATUS      Status;
  UINTN           MaxColumns;
  UINTN           MaxRows;
  UINTN           Length;
  EFI_INPUT_KEY   Key;

  //
  // Initialize
  //
  if (Init) {
    Row = 0;
    return EFI_SUCCESS;
  }

  //
  // Get the maximum columns and rows
  //
  tST->ConOut->QueryMode (
                tST->ConOut,
                tST->ConOut->Mode->Mode,
                &MaxColumns,
                &MaxRows
                );

  //
  // Compare with the current Row number
  //
  Length  = SctStrLen (String);
  if (Row + (Length + MaxColumns - 1) / MaxColumns >= MaxRows) {
    Row = 0;
    SctPrint (L"  Press 'q' to exit, any other key to continue");

    for (; ;) {
      tBS->Stall (10000);

      Status = tST->ConIn->ReadKeyStroke (
                            tST->ConIn,
                            &Key
                            );
      if (!EFI_ERROR (Status)) {
        SctPrint (L"\n");

        if ((Key.UnicodeChar == L'Q') || (Key.UnicodeChar == L'q')) {
          return EFI_ABORTED;
        }

        break;
      }
    }
  }

  //
  // Print out
  //
  Row += (Length + MaxColumns - 1) / MaxColumns;
  SctPrint (L"%s", String);

  return EFI_SUCCESS;
}


EFI_STATUS
DeviceConfigHelp (
  VOID
  )
{
  SctPrint (
    L"H           - Print this help information\n"
    L"I <Handle>  - Insert one device into the configuration file\n"
    L"L           - List all devices in the configuration file\n"
    L"Q           - Quit\n"
    L"R <Index>   - Remove one device from the configuration file\n"
    L"S <Type>    - Scan devices in the system\n"
    L"              (Type 0: All, Type 1: With Option ROM)\n"
    L"V <Index>   - List one device in the configuration file in verbose mode\n"
    L"\n"
    L"For new users, select 'S' first to get the devices with Option ROM, and\n"
    L"then use 'I <Handle>' to insert the devices which should be tested into\n"
    L"the configuration file. For more information of this handle, please refer\n"
    L"to the 'DH' command in Shell environment.\n"
    );

  return EFI_SUCCESS;
}

EFI_STATUS
DeviceConfigInsert (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINTN                  HandleIndex
  )
{
  EFI_STATUS                Status;
  UINTN                     NoHandles;
  EFI_HANDLE                *HandleBuffer;
  EFI_HANDLE                Handle;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  CHAR16                    *DevicePathStr;
  UINT32                    OrderNum;
  CHAR16                    InputBuffer[2];
  CHAR16                    *Buffer;

  //
  // Locate all handles
  //
  Status = tBS->LocateHandleBuffer (
                 AllHandles,
                 NULL,
                 NULL,
                 &NoHandles,
                 &HandleBuffer
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Locate handle buffer - %r", Status));
    return Status;
  }

  if ((HandleIndex == 0) || (HandleIndex > NoHandles)) {
    SctPrint (L"  Invalid handle number!\n");
    tBS->FreePool (HandleBuffer);
    return EFI_INVALID_PARAMETER;
  }

  Handle = HandleBuffer[HandleIndex - 1];
  tBS->FreePool (HandleBuffer);

  //
  // Check the Device Path Protocol on this handle
  //
  Status = tBS->HandleProtocol (
                 Handle,
                 &gEfiDevicePathProtocolGuid,
                 (VOID **)&DevicePath
                 );
  if (EFI_ERROR (Status)) {
    SctPrint (L"  Invalid handle number!\n");
    return EFI_INVALID_PARAMETER;
  }

  //
  // The handle passes all checks. Now add it to the configuration file
  //

  //
  // Get the number of devices in the configuration file
  //
  Status = DeviceConfigGetOrderNum (
             IniFile,
             &OrderNum
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get order - %r", Status));
    return Status;
  }

  //
  // Record the device path
  //
  DevicePathStr = SctDevicePathToStr (DevicePath);

  Status = DeviceConfigSetString (
             IniFile,
             OrderNum,
             L"DevicePath",
             DevicePathStr
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config set string - %r", Status));
    tBS->FreePool (DevicePathStr);
    return Status;
  }

  tBS->FreePool (DevicePathStr);

  //
  // Device Type, let user choose the device type
  //
  SctPrint (
    L"Select the device type:\n"
    L"  R - SCSI Raid\n"
    L"  F - SCSI Fiber\n"
    L"  N - NIC\n"
    L"  U - USB\n"
    L"  V - Video\n"
    L"  S - Serial\n"
    L"  P - PCI\n"
    L"  O - Other\n"
    );

  SctInput (L"Enter choice: ", InputBuffer, 2);
  SctPrint (L"\n");

  while (TRUE) {
    Buffer = NULL;

    if ((InputBuffer[0] == L'R') || (InputBuffer[0] == L'r')) {
      Buffer = L"SCSI Raid";
    } else if ((InputBuffer[0] == L'F') || (InputBuffer[0] == L'f')) {
      Buffer = L"SCSI Fiber";
    } else if ((InputBuffer[0] == L'N') || (InputBuffer[0] == L'n')) {
      Buffer = L"NIC";
    } else if ((InputBuffer[0] == L'U') || (InputBuffer[0] == L'u')) {
      Buffer = L"USB";
    } else if ((InputBuffer[0] == L'V') || (InputBuffer[0] == L'v')) {
      Buffer = L"Video";
    } else if ((InputBuffer[0] == L'S') || (InputBuffer[0] == L's')) {
      Buffer = L"Serial";
    } else if ((InputBuffer[0] == L'P') || (InputBuffer[0] == L'p')) {
      Buffer = L"PCI";
    } else if ((InputBuffer[0] == L'O') || (InputBuffer[0] == L'o')) {
      Buffer = L"Other";
    }

    if (Buffer != NULL) {
      Status = DeviceConfigSetString (
                 IniFile,
                 OrderNum,
                 L"DeviceType",
                 Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config set string - %r", Status));
        return Status;
      }

      break;
    }

    SctInput (L"Invalid input! Enter choice again: ", InputBuffer, 2);
    SctPrint (L"\n");
  }

  //
  // Driver Binding
  //
  SctInput (
    L"Should test the Driver Binding Protocol? [Y(Default)/N]: ",
    InputBuffer,
    2
    );
  SctPrint (L"\n");

  while (TRUE) {
    Buffer = NULL;

    if (InputBuffer[0] == L'\0') {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'Y') || (InputBuffer[0] == L'y')) {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'N') || (InputBuffer[0] == L'n')) {
      Buffer = L"No";
    }

    if (Buffer != NULL) {
      Status = DeviceConfigSetString (
                 IniFile,
                 OrderNum,
                 L"DriverBinding",
                 Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config set string - %r", Status));
        return Status;
      }

      break;
    }

    SctInput (L"Invalid input! Enter again [Y(Default)/N]: ", InputBuffer, 2);
    SctPrint (L"\n");
  }

  //
  // Driver Diagnostics
  //
  SctInput (
    L"Should test the Driver Diagnostics Protocol? [Y(Default)/N]: ",
    InputBuffer,
    2
    );
  SctPrint (L"\n");

  while (TRUE) {
    Buffer = NULL;

    if (InputBuffer[0] == L'\0') {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'Y') || (InputBuffer[0] == L'y')) {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'N') || (InputBuffer[0] == L'n')) {
      Buffer = L"No";
    }

    if (Buffer != NULL) {
      Status = DeviceConfigSetString (
                 IniFile,
                 OrderNum,
                 L"DriverDiagnostics",
                 Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config set string - %r", Status));
        return Status;
      }

      break;
    }

    SctInput (L"Invalid input! Enter again [Y(Default)/N]: ", InputBuffer, 2);
    SctPrint (L"\n");
  }

  //
  // Driver Configuration
  //
  SctInput (
    L"Should test the Driver Configuration Protocol? [Y(Default)/N]: ",
    InputBuffer,
    2
    );
  SctPrint (L"\n");

  while (TRUE) {
    Buffer = NULL;

    if (InputBuffer[0] == L'\0') {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'Y') || (InputBuffer[0] == L'y')) {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'N') || (InputBuffer[0] == L'n')) {
      Buffer = L"No";
    }

    if (Buffer != NULL) {
      Status = DeviceConfigSetString (
                 IniFile,
                 OrderNum,
                 L"DriverConfiguration",
                 Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config set string - %r", Status));
        return Status;
      }

      break;
    }

    SctInput (L"Invalid input! Enter again [Y(Default)/N]: ", InputBuffer, 2);
    SctPrint (L"\n");
  }

  //
  // Unload Supported function
  //
  SctInput (
    L"Should test the Unload Supported function? [Y(Default)/N]: ",
    InputBuffer,
    2
    );
  SctPrint (L"\n");

  while (TRUE) {
    Buffer = NULL;

    if (InputBuffer[0] == L'\0') {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'Y') || (InputBuffer[0] == L'y')) {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'N') || (InputBuffer[0] == L'n')) {
      Buffer = L"No";
    }

    if (Buffer != NULL) {
      Status = DeviceConfigSetString (
                 IniFile,
                 OrderNum,
                 L"UnloadSupported",
                 Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config set string - %r", Status));
        return Status;
      }

      break;
    }

    SctInput (L"Invalid input! Enter again [Y(Default)/N]: ", InputBuffer, 2);
    SctPrint (L"\n");
  }

  //
  // Runtime Supported function
  //
  SctInput (
    L"Should test the Runtime Supported funtion? [Y(Default)/N]: ",
    InputBuffer,
    2
    );
  SctPrint (L"\n");

  while (TRUE) {
    Buffer = NULL;

    if (InputBuffer[0] == L'\0') {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'Y') || (InputBuffer[0] == L'y')) {
      Buffer = L"Yes";
    } else if ((InputBuffer[0] == L'N') || (InputBuffer[0] == L'n')) {
      Buffer = L"No";
    }

    if (Buffer != NULL) {
      Status = DeviceConfigSetString (
                 IniFile,
                 OrderNum,
                 L"RuntimeSupported",
                 Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config set string - %r", Status));
        return Status;
      }

      break;
    }

    SctInput (L"Invalid input! Enter again [Y(Default)/N]: ", InputBuffer, 2);
    SctPrint (L"\n");
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
DeviceConfigList (
  IN EFI_INI_FILE_HANDLE    IniFile
  )
{
  EFI_STATUS                Status;
  UINT32                    Order;
  UINT32                    OrderNum;
  CHAR16                    Buffer[EFI_SCT_MAX_BUFFER_SIZE];

  //
  // Get the number of devices in the configuration file
  //
  Status = DeviceConfigGetOrderNum (
             IniFile,
             &OrderNum
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get order - %r", Status));
    return Status;
  }

  //
  // Print the device path of each device
  //
  for (Order = 0; Order < OrderNum; Order++) {
    Status = DeviceConfigGetString (
               IniFile,
               Order,
               L"DevicePath",
               Buffer
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
      return Status;
    }

    SctPrint (L"%x: %s\n", Order + 1, Buffer);
  }

  //
  // No device in the configuration file
  //
  if (OrderNum == 0) {
    SctPrint (L"  No device in the configuration file.\n");
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
DeviceConfigRemove (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINTN                  OrderIndex
  )
{
  EFI_STATUS                Status;
  UINT32                    Order;
  UINT32                    OrderNum;
  CHAR16                    Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  CHAR16                    InputBuffer[2];

  //
  // Get the number of devices in the configuration file
  //
  Status = DeviceConfigGetOrderNum (
             IniFile,
             &OrderNum
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get order - %r", Status));
    return Status;
  }

  if ((OrderIndex == 0) || (OrderIndex > OrderNum)) {
    SctPrint (L"  Invalid index number!\n");
    return EFI_INVALID_PARAMETER;
  }

  Order = (UINT32) (OrderIndex - 1);

  //
  // Print the device path to confirm with user
  //
  Status =  DeviceConfigGetString (
             IniFile,
             Order,
             L"DevicePath",
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
    return Status;
  }

  SctPrint (L"Remove '%s'.\n", Buffer);

  SctInput (L"Are you sure? [Y/N]: ", InputBuffer, 2);
  SctPrint (L"\n");

  while (TRUE) {
    if ((InputBuffer[0] == L'N') || (InputBuffer[0] == L'n')) {
      break;
    } else if ((InputBuffer[0] == L'Y') || (InputBuffer[0] == L'y')) {
      Status = DeviceConfigRmSection (
                 IniFile,
                 Order
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config remove section - %r", Status));
        return Status;
      }

      break;
    }

    SctInput (L"Invalid input! Enter again [Y/N]: ", InputBuffer, 2);
    SctPrint (L"\n");
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
DeviceConfigScan (
  IN UINTN                  ScanType
  )
{
  EFI_STATUS                Status;
  UINTN                     Index;
  UINTN                     NoHandles;
  EFI_HANDLE                *HandleBuffer;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  CHAR16                    *DevicePathStr;
  CHAR16                    *TempStr;
  BOOLEAN                   Found;

  //
  // Check parameters
  //
  if ((ScanType != SCAN_DEVICES_ALL            ) &&
      (ScanType != SCAN_DEVICES_WITH_OPTION_ROM)) {
    SctPrint (L"  Invalid scan type!\n");
    return EFI_INVALID_PARAMETER;
  }

  //
  // This operation could print out more than one page information, so we
  // initialize the page-break print at here and let this operation can be
  // paused after one page.
  //
  PageBreakPrint (TRUE, NULL);

  //
  // Locate all handles
  //
  Status = tBS->LocateHandleBuffer (
                 AllHandles,
                 NULL,
                 NULL,
                 &NoHandles,
                 &HandleBuffer
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Locate handle buffer - %r", Status));
    return Status;
  }

  //
  // Check the Option ROM on each PCI IO handle
  //
  Found = FALSE;

  for (Index = 0; Index < NoHandles; Index++) {
    //
    // Skip the handle without the Device Path Protocol
    //
    Status = tBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gEfiDevicePathProtocolGuid,
                   (VOID **)&DevicePath
                   );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Skip the handle without the PCI IO Protocol
    //
    if (ScanType == SCAN_DEVICES_WITH_OPTION_ROM) {
      Status = tBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gEfiPciIoProtocolGuid,
                     (VOID **)&PciIo
                     );
      if (EFI_ERROR (Status)) {
        continue;
      }

      //
      // Skip the handle without Option ROM
      //
      if ((PciIo->RomSize == 0) || (PciIo->RomImage == NULL)) {
        continue;
      }
    }

    Found = TRUE;

    //
    // Print out the device information
    //
    DevicePathStr = SctDevicePathToStr (DevicePath);
    TempStr = SctPoolPrint (L"%x: %s\n", Index + 1, DevicePathStr);
    tBS->FreePool (DevicePathStr);

    Status = PageBreakPrint (FALSE, TempStr);
    tBS->FreePool (TempStr);
    if (EFI_ERROR (Status)) {
      tBS->FreePool (HandleBuffer);
      return EFI_SUCCESS;
    }

    //
    // Print out the driver information
    //
    Status = DeviceConfigScanDrivers (HandleBuffer[Index]);
    if (EFI_ERROR (Status)) {
      tBS->FreePool (HandleBuffer);
      return EFI_SUCCESS;
    }
  }

  tBS->FreePool (HandleBuffer);

  //
  // No device with Option ROM
  //
  if (!Found) {
    SctPrint (L"  No device with Option ROM.\n");
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
DeviceConfigVerbose (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINTN                  OrderIndex
  )
{
  EFI_STATUS                Status;
  UINT32                    Order;
  UINT32                    OrderNum;
  CHAR16                    Buffer[EFI_SCT_MAX_BUFFER_SIZE];

  //
  // Get the number of devices in the configuration file
  //
  Status = DeviceConfigGetOrderNum (
             IniFile,
             &OrderNum
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get order - %r", Status));
    return Status;
  }

  if ((OrderIndex == 0) || (OrderIndex > OrderNum)) {
    SctPrint (L"  Invalid index number!\n");
    return EFI_INVALID_PARAMETER;
  }

  Order = (UINT32) (OrderIndex - 1);

  //
  // Print the device information in verbose mode
  //

  //
  // Device path
  //
  Status = DeviceConfigGetString (
             IniFile,
             Order,
             L"DevicePath",
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
    return Status;
  }

  SctPrint (L"Device Path : %s\n", Buffer);

  //
  // Device type
  //
  Status = DeviceConfigGetString (
             IniFile,
             Order,
             L"DeviceType",
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
    return Status;
  }

  SctPrint (L"Device Type : %s\n", Buffer);

  //
  // Driver Binding Protocol
  //
  Status = DeviceConfigGetString (
             IniFile,
             Order,
             L"DriverBinding",
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
    return Status;
  }

  SctPrint (L"Driver Binding Protocol : %s\n", Buffer);

  //
  // Driver Diagnostics Protocol
  //
  Status = DeviceConfigGetString (
             IniFile,
             Order,
             L"DriverDiagnostics",
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
    return Status;
  }

  SctPrint (L"Driver Diagnostics Protocol : %s\n", Buffer);

  //
  // Driver Configuration Protocol
  //
  Status = DeviceConfigGetString (
             IniFile,
             Order,
             L"DriverConfiguration",
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
    return Status;
  }

  SctPrint (L"Driver Configuration Protocol : %s\n", Buffer);

  //
  // Unload Supported function
  //
  Status = DeviceConfigGetString (
             IniFile,
             Order,
             L"UnloadSupported",
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
    return Status;
  }

  SctPrint (L"Unload Supported : %s\n", Buffer);

  //
  // Runtime Supported
  //
  Status = DeviceConfigGetString (
             IniFile,
             Order,
             L"RuntimeSupported",
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Device config get string - %r", Status));
    return Status;
  }

  SctPrint (L"Runtime Supported : %s\n", Buffer);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
DeviceConfigScanDrivers (
  IN EFI_HANDLE             Handle
  )
{
  EFI_STATUS                            Status;
  UINTN                                 Index1;
  UINTN                                 Index2;
  BOOLEAN                               Result;
  UINTN                                 NoHandles;
  EFI_HANDLE                            *HandleBuffer;
  UINTN                                 ProtocolBufferCount;
  EFI_GUID                              **ProtocolBuffer;
  UINTN                                 EntryCount;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY   *EntryBuffer;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImage;
  EFI_COMPONENT_NAME_PROTOCOL           *ComponentName;
  CHAR16                                *DriverName;
  CHAR16                                *FilePathStr;
  CHAR16                                *TempStr;

  //
  // Locate all handles in the system. The data in this Handle Buffer is not
  // useful in this function. But the Buffer is used to store the Handles
  // related to the input controller handle
  //
  Status = tBS->LocateHandleBuffer (
                 AllHandles,
                 NULL,
                 NULL,
                 &NoHandles,
                 &HandleBuffer
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Locate protocols on this handle
  //
  Status = tBS->ProtocolsPerHandle (
                 Handle,
                 &ProtocolBuffer,
                 &ProtocolBufferCount
                 );
  if (EFI_ERROR (Status)) {
    tBS->FreePool (HandleBuffer);
    return Status;
  }

  //
  // Scan each protocol on this handle
  //
  NoHandles = 0;

  for (Index1 = 0; Index1 < ProtocolBufferCount; Index1++) {
    //
    // Locate open protocol information
    //
    Status = tBS->OpenProtocolInformation (
                   Handle,
                   ProtocolBuffer[Index1],
                   &EntryBuffer,
                   &EntryCount
                   );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Scan each open protocol entry
    //
    for (Index2 = 0; Index2 < EntryCount; Index2++) {
      if ((EntryBuffer[Index2].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER          ) ||
          (EntryBuffer[Index2].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)) {
        Result = DeviceConfigInsertHandle (
                   &NoHandles,
                   HandleBuffer,
                   EntryBuffer[Index2].AgentHandle
                   );

        if (Result) {
          //
          // It is a new driver handle
          //
          Status = tBS->HandleProtocol (
                         EntryBuffer[Index2].AgentHandle,
                         &gEfiComponentNameProtocolGuid,
                         (VOID **)&ComponentName
                         );
          if (!EFI_ERROR (Status)) {
            Status = ComponentName->GetDriverName (
                                      ComponentName,
                                      "eng",
                                      &DriverName
                                      );
            if (!EFI_ERROR (Status)) {
              TempStr = SctPoolPrint (L"  Managed by driver <%s>\n", DriverName);
            } else {
              TempStr = SctPoolPrint (L"  Managed by driver <UNKNOWN>\n");
            }

            Status = PageBreakPrint (FALSE, TempStr);
            tBS->FreePool (TempStr);
            if (EFI_ERROR (Status)) {
              tBS->FreePool (HandleBuffer);
              return Status;
            }

            continue;
          }

          //
          // Can not locate the Component Name Protocol. Try the file path in
          // the Loaded Image Protocol
          //
          Status = tBS->HandleProtocol (
                         EntryBuffer[Index2].AgentHandle,
                         &gEfiLoadedImageProtocolGuid,
                         (VOID **)&LoadedImage
                         );
          if (!EFI_ERROR (Status)) {
            FilePathStr = SctDevicePathToStr (LoadedImage->FilePath);
            TempStr = SctPoolPrint (L"  Managed by driver : %s\n", FilePathStr);
            tBS->FreePool (FilePathStr);

            Status = PageBreakPrint (FALSE, TempStr);
            tBS->FreePool (TempStr);
            if (EFI_ERROR (Status)) {
              tBS->FreePool (HandleBuffer);
              return Status;
            }
          }
        }
      }
    }
  }

  //
  // Free resources
  //
  tBS->FreePool (HandleBuffer);

  //
  // Done
  //
  return EFI_SUCCESS;
}

BOOLEAN
DeviceConfigInsertHandle (
  IN OUT UINTN              *NoHandles,
  IN OUT EFI_HANDLE         *HandleBuffer,
  IN EFI_HANDLE             Handle
  )
{
  UINTN     Index;

  for (Index = 0; Index < *NoHandles; Index++) {
    if (HandleBuffer[Index] == Handle) {
      return FALSE;
    }
  }

  HandleBuffer[*NoHandles] = Handle;
  (*NoHandles) ++;

  return TRUE;
}

EFI_STATUS
DeviceConfigParser (
  IN  CHAR16                *String,
  OUT CHAR16                *Option,
  OUT UINTN                 *Index
  )
{
  CHAR16  *Buffer;

  //
  // Skip the leading space characters
  //
  Buffer = String;
  while (*Buffer != L'\0') {
    if ((*Buffer != L' ') && (*Buffer != L'\t')) {
      break;
    }
    Buffer++;
  }

  *Option = *Buffer;
  *Index  = 0;

  if (*Buffer == L'\0') {
    return EFI_SUCCESS;
  }

  //
  // Skip the space characters between option and index
  //
  Buffer++;
  while (*Buffer != L'\0') {
    if ((*Buffer != L' ') && (*Buffer != L'\t')) {
      break;
    }
    Buffer++;
  }

  *Index = 0;
  while (*Buffer != L'\0') {
    if ((*Buffer >= L'0') && (*Buffer <= L'9')) {
      *Index = (*Index << 4) + (*Buffer - L'0');
    } else if ((*Buffer >= L'A') && (*Buffer <= L'F')) {
      *Index = (*Index << 4) + (*Buffer - L'A' + 10);
    } else if ((*Buffer >= L'a') && (*Buffer <= L'f')) {
      *Index = (*Index << 4) + (*Buffer - L'a' + 10);
    } else {
      break;
    }

    Buffer++;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
DeviceConfigGetOrderNum (
  IN EFI_INI_FILE_HANDLE    IniFile,
  OUT UINT32                *OrderNum
  )
/*++

Routine Description:

  Get the number of device configuration section.

--*/
{
  return IniFile->GetOrderNum (
                    IniFile,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    OrderNum
                    );
}

EFI_STATUS
DeviceConfigRmSection (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order
  )
/*++

Routine Description:

  Remove one section from the device configuration file.

--*/
{
  return IniFile->RmSectionByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_DEVICE_CONFIG
                    );
}

EFI_STATUS
DeviceConfigGetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  OUT CHAR16                *Buffer
  )
/*++

Routine Description:

  Get a string from the device configuration file.

--*/
{
  UINT32  BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}

EFI_STATUS
DeviceConfigSetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  IN CHAR16                 *Buffer
  )
/*++

Routine Description:

  Set a string into the device configuration file.

--*/
{
  return IniFile->SetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    Key,
                    Buffer
                    );
}
