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
                                                                
  Copyright 2006 - 2015 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  TestLogging.c

Abstract:

  Driver to publish the Test Logging Library Protocol.

--*/

#include "SctLib.h"
#include "EfiTest.h"
#include "TestLogging.h"

//
// Prototypes
//

EFI_STATUS
EFIAPI
TestLoggingEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

EFI_STATUS
EFIAPI
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
// Prototypes of EFI_TEST_LOGGING_LIBRARY_PROTOCOL
//
EFI_STATUS
EFIAPI
TllLine (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN EFI_VERBOSE_LEVEL                      VerboseLevel,
  IN UINT32                                 Length
  );

EFI_STATUS
EFIAPI
TllEnterFunction (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN CHAR16                                 *FunctionName,
  IN CHAR16                                 *Fmt,
  ...
  );

EFI_STATUS
EFIAPI
TllExitFunction (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN CHAR16                                 *FunctionName,
  IN CHAR16                                 *Fmt,
  ...
  );

EFI_STATUS
EFIAPI
TllDumpMask (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN EFI_VERBOSE_LEVEL                      VerboseLevel,
  IN UINT32                                 BitMask,
  IN UINT32                                 Length
  );

EFI_STATUS
EFIAPI
TllDumpBuf (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN EFI_VERBOSE_LEVEL                      VerboseLevel,
  IN CHAR16                                 *Buffer,
  IN UINT32                                 Length,
  IN UINT32                                 Flags
  );

//
// Prototypes of EFI_TLL_PRIVATE_INTERFACE
//
EFI_STATUS
EFIAPI
TllSetConfig (
  IN EFI_TLL_PRIVATE_INTERFACE              *This,
  IN EFI_LIB_CONFIG_DATA                    *Config
  );

EFI_STATUS
EFIAPI
TllBeginLogging (
  IN EFI_TLL_PRIVATE_INTERFACE              *This
  );

EFI_STATUS
EFIAPI
TllEndLogging (
  IN EFI_TLL_PRIVATE_INTERFACE              *This,
  IN EFI_STATUS                             TestStatus
  );

//
// Name and Description of EFI_TEST_LOGGING_LIBRARY_PROTOCOL
//
CHAR16 *gTllName        = L"Test Logging Library";
CHAR16 *gTllDescription = L"EFI Test Logging Library";

//
// Internal functions
//
EFI_STATUS
TllCloseAllFiles (
  TEST_LOGGING_PRIVATE_DATA                 *Private
  );

EFI_STATUS
TllWriteLogFile (
  TEST_LOGGING_PRIVATE_DATA                 *Private,
  CHAR16                                    *String
  );

EFI_STATUS
TllFreePointer (
  TEST_LOGGING_PRIVATE_DATA                 *Private
  );

CHAR16 *
TllStrDuplicate (
  IN CHAR16             *String
  );

EFI_GUID *
TllGuidsDuplicate (
  IN EFI_GUID           *Guids
  );

//
// Entry point
//
EFI_STATUS
EFIAPI
TestLoggingEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
/*++

Routine Description:

  Test logging library driver's entry point.

Arguments:

  ImageHandle         - the driver image handle.
  SystemTable         - the system table.

Returns:

  EFI_SUCCESS         - the driver is loaded successfully.
  EFI_ALREADY_STARTED - the driver has already been loaded before.

--*/
{
  EFI_STATUS                      Status;
  EFI_LOADED_IMAGE_PROTOCOL       *LoadedImage;
  TSL_INIT_PRIVATE_DATA           *Private;

  //
  // Initialize driver lib
  //
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
  Private->TslInit.LibraryGuid  = gEfiTestLoggingLibraryGuid;
  Private->TslInit.Open         = TslOpen;
  Private->TslInit.Close        = TslClose;

  //
  // Install TslInit protocol
  //
  Status = tBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gEfiTslInitInterfaceGuid,
                  EFI_NATIVE_INTERFACE,
                  &Private->TslInit
                  );

  return Status;
}

EFI_STATUS
EFIAPI
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
  EFI_STATUS                      Status;
  EFI_TSL_INIT_INTERFACE          *TslInit;
  TSL_INIT_PRIVATE_DATA           *Private;

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

  Opens the test support library to get the handle with the public interface
  and the private interface.

Arguments:

  This              - TSL Initiation Interface instance.
  LibHandle         - The pointer to the handle on which the public interface
                      is installed.
  PrivateInterface  - The private interface of the test support library.

Returns:

  EFI_SUCCESS           - open the TestLoggingLibrary successfully.
  EFI_INVALID_PARAMETER - invalid parameter, LibHandle is NULL.
  EFI_ALREADY_STARTED   - the TestLoggingLibrary has been bind on the LibHandle
                          before.

--*/
{
  EFI_STATUS                      Status;
  TEST_LOGGING_PRIVATE_DATA       *Private;
  TSL_INIT_PRIVATE_DATA           *TslPrivate;

  //
  // Check parameter
  //
  if (LibHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  TslPrivate = TSL_INIT_PRIVATE_DATA_FROM_THIS (This);
  //
  // Open the TestLoggingLibrary protocol to perform the supported test.
  //
  if (*LibHandle != NULL) {
    Status = tBS->OpenProtocol (
                    *LibHandle,
                    &gEfiTestLoggingLibraryGuid,
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
  // Initialize the TestLoggingLibrary private data
  //
  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (TEST_LOGGING_PRIVATE_DATA),
                  (VOID **)&Private
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (Private, sizeof(TEST_LOGGING_PRIVATE_DATA));
  Private->Signature                       = TEST_LOGGING_PRIVATE_DATA_SIGNATURE;
  Private->TestLogging.LibraryRevision     = 0x10000;
  Private->TestLogging.Name                = gTllName;
  Private->TestLogging.Description         = gTllDescription;
  Private->TestLogging.Line                = TllLine;
  Private->TestLogging.EnterFunction       = TllEnterFunction;
  Private->TestLogging.ExitFunction        = TllExitFunction;
  Private->TestLogging.DumpMask            = TllDumpMask;
  Private->TestLogging.DumpBuf             = TllDumpBuf;
  Private->PrivateInterface.SetConfig      = TllSetConfig;
  Private->PrivateInterface.BeginLogging   = TllBeginLogging;
  Private->PrivateInterface.EndLogging     = TllEndLogging;

  if (PrivateLibInterface != NULL) {
    *PrivateLibInterface = (VOID *) &Private->PrivateInterface;
  }

  //
  // Install TestLoggingLibrary protocol
  //
  Status = tBS->InstallProtocolInterface (
                  LibHandle,
                  &gEfiTestLoggingLibraryGuid,
                  EFI_NATIVE_INTERFACE,
                  &Private->TestLogging
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

  EFI_SUCCESS   - close the TestLoggingLibrary successfully.

--*/
{
  EFI_STATUS                          Status;
  TEST_LOGGING_PRIVATE_DATA           *Private;
  TSL_INIT_PRIVATE_DATA               *TslPrivate;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *TestLogging;

  TslPrivate = TSL_INIT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Open the TestLoggingLibrary protocol to perform the supported test.
  //
  Status = tBS->OpenProtocol (
                  LibHandle,
                  &gEfiTestLoggingLibraryGuid,
                  (VOID **)&TestLogging,
                  TslPrivate->ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Uninstall TestLoggingLibrary protocol
  //
  Status = tBS->UninstallProtocolInterface (
                  LibHandle,
                  &gEfiTestLoggingLibraryGuid,
                  TestLogging
                  );
  Private = TEST_LOGGING_PRIVATE_DATA_FROM_TLL (TestLogging);
  TllFreePointer (Private);
  tBS->FreePool (Private);

  return Status;
}

EFI_STATUS
EFIAPI
TllLine (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN EFI_VERBOSE_LEVEL                      VerboseLevel,
  IN UINT32                                 Length
  )
/*++

Routine Description:

  Writes a line into the log file. Generally it is for separating the different
  test results or message.

Argument:

  This          - Test logging library protocol instance.
  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.
  Length        - Length of the line.

Returns:

  EFI_SUCCESS           - record the dash line successfully.
  EFI_INVALID_PARAMETER - invalid Length, too long.

--*/
{
  EFI_STATUS                      Status;
  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  UINTN                           Index;
  TEST_LOGGING_PRIVATE_DATA       *Private;

  Private = TEST_LOGGING_PRIVATE_DATA_FROM_TLL (This);
  Status = EFI_SUCCESS;

  if (Length + 3 >= EFI_MAX_PRINT_BUFFER) {
    return EFI_INVALID_PARAMETER;
  }

  if (VerboseLevel <= Private->VerboseLevel) {
    SctZeroMem (Buffer, sizeof(Buffer));
    for (Index = 0; Index < Length; Index ++) {
      Buffer[Index] = L'-';
    }
    SctStrCat (Buffer, L"\r\n");
    Status = TllWriteLogFile (Private, Buffer);
  }

  return Status;
}

EFI_STATUS
EFIAPI
TllEnterFunction (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN CHAR16                                 *FunctionName,
  IN CHAR16                                 *Fmt,
  ...
  )
/*++

Routine Description:

  Records the tracing message of entering a function. This message will only be
  recorded when the test is run in EXHAUSTIVE mode.

Argument:

  This          - Test logging library protocol instance.
  FunctionName  - Name of enter function.
  Message       - Format string for the detail test information.

Returns:

  EFI_SUCCESS   - record entering function successfully.

--*/
{
  EFI_STATUS                      Status;
  VA_LIST                         Marker;
  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  TEST_LOGGING_PRIVATE_DATA       *Private;

  Status = EFI_SUCCESS;
  Private = TEST_LOGGING_PRIVATE_DATA_FROM_TLL (This);

  if (Private->VerboseLevel >= EFI_VERBOSE_LEVEL_EXHAUSTIVE) {
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Enter function %s: ", FunctionName);
    Status = TllWriteLogFile (Private, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    VA_START(Marker, Fmt);
    SctVSPrint (Buffer, EFI_MAX_PRINT_BUFFER, Fmt, Marker);
    VA_END (Marker);

    if (SctStrLen (Buffer) + 3 < EFI_MAX_PRINT_BUFFER) {
      SctStrCat (Buffer, L"\r\n");
    }
    Status = TllWriteLogFile (Private, Buffer);
  }

  return Status;
}

EFI_STATUS
EFIAPI
TllExitFunction (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN CHAR16                                 *FunctionName,
  IN CHAR16                                 *Fmt,
  ...
  )
/*++

Routine Description:

  Records the tracing message of exiting a function. This message will only be
  recorded when the test is run in EXHAUSTIVE mode.

Argument:

  This          - Test logging library protocol instance.
  FunctionName  - Name of exit function.
  Message       - Format string for the detail test information.

Returns:

  EFI_SUCCESS   - record exitting function successfully.

--*/
{
  EFI_STATUS                      Status;
  VA_LIST                         Marker;
  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  TEST_LOGGING_PRIVATE_DATA       *Private;

  Status = EFI_SUCCESS;
  Private = TEST_LOGGING_PRIVATE_DATA_FROM_TLL (This);

  if (Private->VerboseLevel >= EFI_VERBOSE_LEVEL_EXHAUSTIVE) {
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Exit function %s: ", FunctionName);
    Status = TllWriteLogFile (Private, Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    VA_START(Marker, Fmt);
    SctVSPrint (Buffer, EFI_MAX_PRINT_BUFFER, Fmt, Marker);
    VA_END (Marker);

    if (SctStrLen (Buffer) + 3 < EFI_MAX_PRINT_BUFFER) {
      SctStrCat (Buffer, L"\r\n");
    }
    Status = TllWriteLogFile (Private, Buffer);
  }

  return Status;
}

EFI_STATUS
EFIAPI
TllDumpMask (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN EFI_VERBOSE_LEVEL                      VerboseLevel,
  IN UINT32                                 BitMask,
  IN UINT32                                 Length
  )
/*++

Routine Description:

  Dump a bit-map mask.

Argument:

  This          - Test logging library protocol instance.
  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.
  BitMask       - Bit Mask to be dumpped.
  Length        - The number of bits to be dumpped.

Returns:

  EFI_SUCCESS   - dump mask successfully.

--*/
{
  EFI_STATUS                      Status;
  TEST_LOGGING_PRIVATE_DATA       *Private;
  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  UINTN                           BitPos;

  Status = EFI_SUCCESS;
  Private = TEST_LOGGING_PRIVATE_DATA_FROM_TLL (This);

  if (Length > 32) {
    return EFI_INVALID_PARAMETER;
  }
  if (VerboseLevel <= Private->VerboseLevel) {
    SctZeroMem (Buffer, sizeof(Buffer));
    for (BitPos = 0; BitPos < Length; BitPos++) {
      if (BitMask & (1<<BitPos)) {
        if (Buffer[0] == L'\0') {
          SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%02dH", BitPos);
        } else {
          SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%s %02dH", Buffer, BitPos);
        }
      }
    }
    if (Buffer[0] == L'\0') {
      SctStrCpy (Buffer, L"none\r\n");
    } else {
      SctStrCat (Buffer, L"\r\n");
    }
    Status = TllWriteLogFile (Private, Buffer);
  }
  return Status;
}

EFI_STATUS
EFIAPI
TllDumpBuf (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *This,
  IN EFI_VERBOSE_LEVEL                      VerboseLevel,
  IN CHAR16                                 *Buffer,
  IN UINT32                                 Length,
  IN UINT32                                 Flags
  )
/*++

Routine Description:

  Dump a buffer in Hex, ASCII, or both styles.

Argument:

  This          - Test logging library protocol instance.
  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.
  Buffer        - Buffer to be dumpped.
  Length        - The number of bytes to be dumpped.
  Flags         - Dumpping format. HEX, ASCII, or BOTH.

Returns:

  EFI_SUCCESS   - dump buffer successfully.

--*/
{
  TEST_LOGGING_PRIVATE_DATA       *Private;
  CHAR16                          HexBuffer[EFI_MAX_PRINT_BUFFER / 4];
  CHAR16                          AsciiBuffer[EFI_MAX_PRINT_BUFFER / 4];
  CHAR16                          OutBuffer[EFI_MAX_PRINT_BUFFER];
  UINT32                          Index;

  Private = TEST_LOGGING_PRIVATE_DATA_FROM_TLL (This);

  if ((Length == 0) || !((Flags & EFI_DUMP_HEX) || (Flags & EFI_DUMP_ASCII))) {
    return EFI_INVALID_PARAMETER;
  }
  SctZeroMem (HexBuffer, sizeof(HexBuffer));
  SctZeroMem (AsciiBuffer, sizeof(AsciiBuffer));
  if (VerboseLevel <= Private->VerboseLevel) {
    for (Index = 0; Index < Length; Index++) {
      //
      // Prepare one buffer data
      //
      if (HexBuffer[0] == L'\0') {
        SctSPrint (HexBuffer, EFI_MAX_PRINT_BUFFER/4, L"%04xH",
                Buffer[Index]);
      } else {
        SctSPrint (HexBuffer, EFI_MAX_PRINT_BUFFER/4, L"%s %04xH",
                HexBuffer, Buffer[Index]);
      }
      if ((Buffer[Index] >= 0x0020) && (Buffer[Index] < 0x007F)) {
        SctSPrint (AsciiBuffer, EFI_MAX_PRINT_BUFFER/4, L"%s%c",
              AsciiBuffer, Buffer[Index]);
      } else {
        SctSPrint (AsciiBuffer, EFI_MAX_PRINT_BUFFER/4, L"%s.",
              AsciiBuffer);
      }
      //
      // Dump one line buffer data
      //
      if (Index % 8 == 7) {
        if ((Flags & EFI_DUMP_HEX) && (Flags & EFI_DUMP_ASCII)) {
          SctSPrint (OutBuffer, EFI_MAX_PRINT_BUFFER, L"%08x: %s - %s\n", Index/8*8,
                  HexBuffer, AsciiBuffer);
        } else if (Flags & EFI_DUMP_HEX) {
          SctSPrint (OutBuffer, EFI_MAX_PRINT_BUFFER, L"%08x: %s\n", Index/8*8,
                  HexBuffer);
        } else {
          SctSPrint (OutBuffer, EFI_MAX_PRINT_BUFFER, L"%08x: %s\n", Index/8*8,
                  AsciiBuffer);
        }
        TllWriteLogFile (Private, OutBuffer);
        SctZeroMem (HexBuffer, sizeof(HexBuffer));
        SctZeroMem (AsciiBuffer, sizeof(AsciiBuffer));
      }
    }
    //
    // Dump the left buffer data, currently Index == Length
    //
    if (Index % 8 != 0) {
      if ((Flags & EFI_DUMP_HEX) && (Flags & EFI_DUMP_ASCII)) {
        SctSPrint (OutBuffer, EFI_MAX_PRINT_BUFFER, L"%08x: %s - %s\n", Index/8*8,
                HexBuffer, AsciiBuffer);
      } else if (Flags & EFI_DUMP_HEX) {
        SctSPrint (OutBuffer, EFI_MAX_PRINT_BUFFER, L"%08x: %s\n", Index/8*8,
                HexBuffer);
      } else {
        SctSPrint (OutBuffer, EFI_MAX_PRINT_BUFFER, L"%08x: %s\n", Index/8*8,
                AsciiBuffer);
      }
      TllWriteLogFile (Private, OutBuffer);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TllSetConfig (
  IN EFI_TLL_PRIVATE_INTERFACE              *This,
  IN EFI_LIB_CONFIG_DATA                    *Config
  )
/*++

Routine Description:

  One private interface function of the TestLoggingLibrary to set config.

Arguments:

  This                  - the private interface instance structure.
  Config                - config data.

Returns:

  EFI_SUCCESS           - set config successfully.
  EFI_OUT_OF_RESOURCES  - not enough memory.
  EFI_INVALID_PARAMETER - invalid config data, some pointers are NULL

--*/
{
  TEST_LOGGING_PRIVATE_DATA       *Private;
  EFI_LIB_CONFIG_FILE_DATA        *FileConf;
  EFI_LIB_CONFIG_FILE_HANDLE      *PrivateFileConf;

  Private = TEST_LOGGING_PRIVATE_DATA_FROM_PI (This);
  TllFreePointer (Private);

  //
  // OutputProtocol
  //
  Private->OutputProtocol = Config->OutputProtocol;

  //
  // SystemLogFile
  //
  FileConf                            = &Config->SystemLogFile;
  PrivateFileConf                     = &Private->SystemLogFile;
  PrivateFileConf->EnableScreenOutput = FileConf->EnableScreenOutput;
  PrivateFileConf->OverwriteFile      = FileConf->OverwriteFile;

  if ((FileConf->DevicePath != NULL) && (FileConf->FileName != NULL)) {
    PrivateFileConf->DevicePath = SctDuplicateDevicePath (FileConf->DevicePath);
    if (PrivateFileConf->DevicePath == NULL) {
      TllFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }

    PrivateFileConf->FileName = TllStrDuplicate (FileConf->FileName);
    if (PrivateFileConf->FileName == NULL) {
      TllFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    TllFreePointer (Private);
    return EFI_INVALID_PARAMETER;
  }

  //
  // CaseLogFile
  //
  FileConf                            = &Config->CaseLogFile;
  PrivateFileConf                     = &Private->CaseLogFile;
  PrivateFileConf->EnableScreenOutput = FileConf->EnableScreenOutput;
  PrivateFileConf->OverwriteFile      = FileConf->OverwriteFile;

  if ((FileConf->DevicePath != NULL) && (FileConf->FileName != NULL)) {
    PrivateFileConf->DevicePath = SctDuplicateDevicePath (FileConf->DevicePath);
    if (PrivateFileConf->DevicePath == NULL) {
      TllFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }

    PrivateFileConf->FileName = TllStrDuplicate (FileConf->FileName);
    if (PrivateFileConf->FileName == NULL) {
      TllFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    TllFreePointer (Private);
    return EFI_INVALID_PARAMETER;
  }

  //
  // BiosId
  //
  Private->BiosId = TllStrDuplicate (Config->BiosId);
  if (Private->BiosId == NULL) {
    TllFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // PlatformNumber & ConfigurationNumber
  //
  Private->PlatformNumber       = Config->PlatformNumber;
  Private->ConfigurationNumber  = Config->ConfigurationNumber;

  //
  // ScenarioString
  //
  Private->ScenarioString = TllStrDuplicate (Config->ScenarioString);
  if (Private->ScenarioString == NULL) {
    TllFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Test Information
  //
  Private->TestRevision = Config->TestRevision;

  Private->TestName = TllStrDuplicate (Config->TestName);
  if (Private->TestName == NULL) {
    TllFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  SctCopyMem (&Private->EntryId, Config->EntryId, sizeof(EFI_GUID));

  Private->EntryName = TllStrDuplicate (Config->EntryName);
  if (Private->EntryName == NULL) {
    TllFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  Private->EntryDescription = TllStrDuplicate (Config->EntryDescription);
  if (Private->EntryDescription == NULL) {
    TllFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  Private->SupportProtocols = TllGuidsDuplicate (Config->SupportProtocols);
  if (Private->SupportProtocols == NULL) {
    TllFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  Private->VerboseLevel         = Config->VerboseLevel;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TllBeginLogging (
  IN EFI_TLL_PRIVATE_INTERFACE              *This
  )
/*++

Routine Description:

  One private interface function of the TestLoggingLibrary to begin logging.

Arguments:

  This        - the private interface instance structure.

Returns:

  EFI_SUCCESS - begin logging successfully.

--*/
{
  EFI_STATUS                          Status;
  TEST_LOGGING_PRIVATE_DATA           *Private;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL    *Output;
  EFI_LIB_CONFIG_FILE_HANDLE          *FileConf;

  Private = TEST_LOGGING_PRIVATE_DATA_FROM_PI (This);
  Output = Private->OutputProtocol;

  TllCloseAllFiles (Private);

  //
  // Open log files
  //

  //
  // Open system log file
  //
  FileConf = &Private->SystemLogFile;
  Status = Output->Open (
             Output,
             FileConf->DevicePath,
             FileConf->FileName,
             FileConf->OverwriteFile,
             &FileConf->FileHandle
           );
  if ( EFI_ERROR(Status) ) {
    TllCloseAllFiles (Private);
    return Status;
  }

  //
  // Open case log file
  //
  FileConf = &Private->CaseLogFile;
  Status = Output->Open (
             Output,
             FileConf->DevicePath,
             FileConf->FileName,
             FileConf->OverwriteFile,
             &FileConf->FileHandle
           );
  if ( EFI_ERROR(Status) ) {
    TllCloseAllFiles (Private);
    return Status;
  }

  //
  // Initial private data
  //
  Private->BeginLogging   = TRUE;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TllEndLogging (
  IN EFI_TLL_PRIVATE_INTERFACE              *This,
  IN EFI_STATUS                             TestStatus
  )
/*++

Routine Description:

  One private interface function of the TestLoggingLibrary to end logging.

Arguments:

  This        - the private interface instance structure.

Returns:

  EFI_SUCCESS - end logging successfully.

--*/
{
  TEST_LOGGING_PRIVATE_DATA           *Private;

  Private = TEST_LOGGING_PRIVATE_DATA_FROM_PI (This);

  //
  // close log files
  //
  TllCloseAllFiles (Private);

  Private->BeginLogging   = FALSE;

  return EFI_SUCCESS;
}

//
// Internal functions
//

EFI_STATUS
TllCloseAllFiles (
  TEST_LOGGING_PRIVATE_DATA                 *Private
  )
{
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL    *Output;
  EFI_LIB_CONFIG_FILE_HANDLE          *FileConf;

  Output = Private->OutputProtocol;

  //
  // Close system log file
  //
  FileConf = &Private->SystemLogFile;
  if (FileConf->FileHandle != NULL) {
    Output->Close (
               Output,
               FileConf->FileHandle
             );
    FileConf->FileHandle = NULL;
  }

  //
  // Close case log file
  //
  FileConf = &Private->CaseLogFile;
  if (FileConf->FileHandle != NULL) {
    Output->Close (
               Output,
               FileConf->FileHandle
             );
    FileConf->FileHandle = NULL;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
TllWriteLogFile (
  TEST_LOGGING_PRIVATE_DATA                 *Private,
  CHAR16                                    *String
  )
{
  EFI_STATUS                          Status;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL    *Output;
  EFI_FILE_HANDLE                     FileHandle;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL        *ConOut;

  Output = Private->OutputProtocol;
  ConOut = tST->ConOut;

  Status = EFI_SUCCESS;

  //
  // System log file
  //
  if (Private->SystemLogFile.EnableScreenOutput) {
    Status = ConOut->OutputString (ConOut, String);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  FileHandle = Private->SystemLogFile.FileHandle;
  if (FileHandle != NULL) {
    Status = Output->Write (Output, FileHandle, String);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  //
  // Case log file
  //
  if (Private->CaseLogFile.EnableScreenOutput) {
    Status = ConOut->OutputString (ConOut, String);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  FileHandle = Private->CaseLogFile.FileHandle;
  if (FileHandle != NULL) {
    Status = Output->Write (Output, FileHandle, String);
  }

  return Status;
}

EFI_STATUS
TllFreePointer (
  TEST_LOGGING_PRIVATE_DATA                 *Private
  )
{
  EFI_LIB_CONFIG_FILE_HANDLE    *FileConf;

  //
  // Free DevicePath and FileName of SystemLogFile
  //
  FileConf = &Private->SystemLogFile;
  if (FileConf->DevicePath != NULL) {
    tBS->FreePool (FileConf->DevicePath);
    FileConf->DevicePath = NULL;
  }

  if (FileConf->FileName != NULL) {
    tBS->FreePool (FileConf->FileName);
    FileConf->FileName = NULL;
  }

  //
  // Free DevicePath and FileName of CaseLogFile
  //
  FileConf = &Private->CaseLogFile;
  if (FileConf->DevicePath != NULL) {
    tBS->FreePool (FileConf->DevicePath);
    FileConf->DevicePath = NULL;
  }

  if (FileConf->FileName != NULL) {
    tBS->FreePool (FileConf->FileName);
    FileConf->FileName = NULL;
  }

  //
  // Free BiosId
  //
  if (Private->BiosId != NULL) {
    tBS->FreePool (Private->BiosId);
    Private->BiosId = NULL;
  }

  //
  // Free ScenarioString
  //
  if (Private->ScenarioString != NULL) {
    tBS->FreePool (Private->ScenarioString);
    Private->ScenarioString = NULL;
  }

  //
  // Free TestName
  //
  if (Private->TestName != NULL) {
    tBS->FreePool (Private->TestName);
    Private->TestName = NULL;
  }

  //
  // Free EntryName
  //
  if (Private->EntryName != NULL) {
    tBS->FreePool (Private->EntryName);
    Private->EntryName = NULL;
  }

  //
  // Free EntryDescription
  //
  if (Private->EntryDescription != NULL) {
    tBS->FreePool (Private->EntryDescription);
    Private->EntryDescription = NULL;
  }

  //
  // Free SupportProtocols
  //
  if (Private->SupportProtocols != NULL) {
    tBS->FreePool (Private->SupportProtocols);
    Private->SupportProtocols = NULL;
  }

  return EFI_SUCCESS;
}

CHAR16 *
TllStrDuplicate (
  IN CHAR16             *String
  )
{
  EFI_STATUS  Status;
  CHAR16      *Buffer;

  if (String == NULL) {
    return NULL;
  }

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  (SctStrLen (String) + 1) * sizeof(CHAR16),
                  (VOID **)&Buffer
                  );
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  SctStrCpy (Buffer, String);

  return Buffer;
}

EFI_GUID *
TllGuidsDuplicate (
  IN EFI_GUID           *Guids
  )
{
  EFI_STATUS  Status;
  UINTN       NoGuids;
  EFI_GUID    *Guid;
  EFI_GUID    *Buffer;

  if (Guids == NULL) {
    return NULL;
  }

  NoGuids = 0;
  Guid    = Guids;

  while (SctCompareMem (Guid, &gEfiNullGuid, sizeof(EFI_GUID)) != 0) {
    NoGuids ++;
    Guid ++;
  }

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  (NoGuids + 1) * sizeof(EFI_GUID),
                  (VOID **)&Buffer
                  );
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  SctCopyMem (Buffer, Guids, (NoGuids + 1) * sizeof(EFI_GUID));

  return Buffer;
}
