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
  Portions of Copyright (c) 2013 - 2014, ARM Ltd. All rights reserved.<BR>
   
--*/
/*++

Module Name:

  StandardTest.c

Abstract:

  Driver to publish the Standard Test Library Protocol.

--*/

#include "SctLib.h"
#include "EfiTest.h"
#include "StandardTest.h"
#include <Library/EntsLib.h>

//
// Prototypes
//

EFI_STATUS
EFIAPI
StandardTestEntryPoint (
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
// Prototypes of EFI_STANDARD_TEST_LIBRARY_PROTOCOL
//
EFI_STATUS
EFIAPI
StslRecordAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_TEST_ASSERTION                     Type,
  IN EFI_GUID                               EventId,
  IN CHAR16                                 *Description,
  IN CHAR16                                 *Detail,
  ...
  );

EFI_STATUS
EFIAPI
StslRecordMessage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_VERBOSE_LEVEL                      VerboseLevel,
  IN CHAR16                                 *Message,
  ...
);

EFI_STATUS
EFIAPI
StslGetResultCount (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_TEST_ASSERTION                     Type,
  OUT UINT32                                *Count
);

//
// Prototypes of EFI_STANDARD_TSL_PRIVATE_INTERFACE
//
EFI_STATUS
EFIAPI
StslSetConfig (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This,
  IN EFI_LIB_CONFIG_DATA                    *Config
  );

EFI_STATUS
EFIAPI
StslBeginLogging (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This
  );

EFI_STATUS
EFIAPI
StslEndLogging (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This,
  IN EFI_STATUS                             TestStatus
  );

//
// Name and Description of EFI_STANDARD_TEST_LIBRARY_PROTOCOL
//
CHAR16 *gStslName        = L"Standard Test Library";
CHAR16 *gStslDescription = L"EFI Standard Test Library";

//
// Internal functions
//
EFI_STATUS
StslCloseAllFiles (
  IN STANDARD_TEST_PRIVATE_DATA   *Private
  );

EFI_STATUS
StslWriteLogFile (
  IN STANDARD_TEST_PRIVATE_DATA   *Private,
  IN CHAR16                       *String
  );

EFI_STATUS
StslWriteKeyFile (
  IN STANDARD_TEST_PRIVATE_DATA   *Private,
  IN CHAR16                       *String
  );

EFI_STATUS
StslWriteLogFileName (
  IN STANDARD_TEST_PRIVATE_DATA   *Private
  );

EFI_STATUS
StslFreePointer (
  IN STANDARD_TEST_PRIVATE_DATA   *Private
  );

//
// Global variables and definitions
//

CHAR16 *DashLine = L"------------------------------------------------------------\r\n";

#define IS_LEAP(y) (((((y) % 4) == 0) && (((y) % 100) != 0)) || (((y) % 400) == 0))

static const UINTN  MonthLengths[2][12] = {
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

#define MINS_PER_HOUR       60
#define HOURS_PER_DAY       24
#define SECS_PER_MIN        60
#define SECS_PER_HOUR       (SECS_PER_MIN * MINS_PER_HOUR)
#define SECS_PER_DAY        (SECS_PER_HOUR * HOURS_PER_DAY)
#define DAYS_PER_NYEAR      365
#define DAYS_PER_LYEAR      366

UINT32
SecondsElapsedFromBaseYear (
  IN UINT16             BaseYear,
  IN UINT16             Year,
  IN UINT8              Month,
  IN UINT8              Day,
  IN UINT8              Hour,
  IN UINT8              Minute,
  IN UINT8              Second
  ) ;

CHAR16 *
StslStrDuplicate (
  IN CHAR16             *String
  );

EFI_GUID *
StslGuidsDuplicate (
  IN EFI_GUID           *Guid
  );

//
// Entry point
//
EFI_STATUS
EFIAPI
StandardTestEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
/*++

Routine Description:

  Standard test library driver's entry point.

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
  EfiInitializeEntsLib   (ImageHandle, SystemTable);

  //
  // Initialize NetAssertionConfigData.
  //
  Status = NetAssertionUtilityInstall();
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_WARNING, L"NetAssertionUtilityInstall fail - %r", Status));
  }

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
  Private->TslInit.LibraryGuid  = gEfiStandardTestLibraryGuid;
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

  ImageHandle     - the driver image handle.

Returns:

  EFI_SUCCESS     - unload successfully.

--*/
{
  EFI_STATUS                      Status;
  EFI_TSL_INIT_INTERFACE          *TslInit;
  TSL_INIT_PRIVATE_DATA           *Private;

  NetAssertionUtilityUninstall();

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
  EFI_ALREADY_STARTED   - the StandardTestLibrary has been bind on the
                          LibHandlebefore.

--*/
{
  EFI_STATUS                      Status;
  STANDARD_TEST_PRIVATE_DATA      *Private;
  TSL_INIT_PRIVATE_DATA           *TslPrivate;

  //
  // Check parameter
  //
  if (LibHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  TslPrivate = TSL_INIT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Open the StandardTestLibrary protocol to perform the supported test.
  //
  if (*LibHandle != NULL) {
    Status = tBS->OpenProtocol (
                    *LibHandle,
                    &gEfiStandardTestLibraryGuid,
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
  // Initialize the StandardTestLibrary private data
  //
  Status = tBS->AllocatePool(
                  EfiBootServicesData,
                  sizeof (STANDARD_TEST_PRIVATE_DATA),
                  (VOID **)&Private
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (Private, sizeof(STANDARD_TEST_PRIVATE_DATA));
  Private->Signature                        = STANDARD_TEST_PRIVATE_DATA_SIGNATURE;
  Private->StandardTest.LibraryRevision     = 0x10000;
  Private->StandardTest.Name                = gStslName;
  Private->StandardTest.Description         = gStslDescription;
  Private->StandardTest.RecordAssertion     = StslRecordAssertion;
  Private->StandardTest.RecordMessage       = StslRecordMessage;
  Private->StandardTest.GetResultCount      = StslGetResultCount;
  Private->PrivateInterface.SetConfig       = StslSetConfig;
  Private->PrivateInterface.BeginLogging    = StslBeginLogging;
  Private->PrivateInterface.EndLogging      = StslEndLogging;

  if (PrivateLibInterface != NULL) {
    *PrivateLibInterface = (VOID *) &Private->PrivateInterface;
  }

  //
  // Install StandardTestLibrary protocol
  //
  Status = tBS->InstallProtocolInterface (
                  LibHandle,
                  &gEfiStandardTestLibraryGuid,
                  EFI_NATIVE_INTERFACE,
                  &Private->StandardTest
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

  EFI_SUCCESS   - close the StandardTestLibrary successfully.

--*/
{
  EFI_STATUS                          Status;
  STANDARD_TEST_PRIVATE_DATA          *Private;
  TSL_INIT_PRIVATE_DATA               *TslPrivate;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardTest;

  TslPrivate = TSL_INIT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Open the StandardTestLibrary protocol to perform the supported test.
  //
  Status = tBS->OpenProtocol (
                  LibHandle,
                  &gEfiStandardTestLibraryGuid,
                  (VOID **)&StandardTest,
                  TslPrivate->ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if ( EFI_ERROR (Status) ) {
    return Status;
  }

  //
  // Uninstall StandardTestLibrary protocol
  //
  Status = tBS->UninstallProtocolInterface (
                  LibHandle,
                  &gEfiStandardTestLibraryGuid,
                  StandardTest
                  );
  Private = STANDARD_TEST_PRIVATE_DATA_FROM_STSL (StandardTest);
  if (Private != NULL) {
    StslFreePointer (Private);
    tBS->FreePool (Private);
  }
  return Status;
}

EFI_STATUS
EFIAPI
StslRecordAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_TEST_ASSERTION                     Type,
  IN EFI_GUID                               EventId,
  IN CHAR16                                 *Description,
  IN CHAR16                                 *Detail,
  ...
  )
/*++

Routine Description:

  Records the test result.

Arguments:

  This          - Standard test library protocol instance.
  Type          - Test result.
  EventId       - GUID for the checkpoint.
  Description   - Simple description for the checkpoint.
  Detail        - Format string for the detail test information.

Returns:

  EFI_SUCCESS           - record the assertion successfully.
  EFI_BAD_BUFFER_SIZE   - the Description string is too long.
  EFI_INVALID_PARAMETER - invalid Type.

--*/
{
  EFI_STATUS                      Status;
  VA_LIST                         Marker;
  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  CHAR16                          AssertionDetail[EFI_MAX_PRINT_BUFFER];
  CHAR16                          AssertionType[10];
  STANDARD_TEST_PRIVATE_DATA      *Private;

  Private = STANDARD_TEST_PRIVATE_DATA_FROM_STSL (This);

  //
  // Check the parameter
  //
  if (SctStrLen (Description) + 14 > EFI_MAX_PRINT_BUFFER) {
    return EFI_BAD_BUFFER_SIZE;
  }

  //
  // Build assertion detail string
  //
  VA_START(Marker, Detail);
  SctVSPrint (AssertionDetail, EFI_MAX_PRINT_BUFFER, Detail, Marker);
  VA_END (Marker);

  if ( SctStrLen (AssertionDetail) + 5 < EFI_MAX_PRINT_BUFFER) {
    SctStrCat (AssertionDetail, L"\r\n");
  }

  //
  // Write log file detail data
  //
  switch (Type) {
  case EFI_TEST_ASSERTION_PASSED:
    SctStrCpy (AssertionType, L"PASS");
    Private->PassCount ++;
    break;
  case EFI_TEST_ASSERTION_WARNING:
    SctStrCpy (AssertionType, L"WARNING");
    Private->WarningCount ++;
    break;
  case EFI_TEST_ASSERTION_FAILED:
    SctStrCpy (AssertionType, L"FAILURE");
    Private->FailCount ++;
    break;
  default:
    return EFI_INVALID_PARAMETER;
    break;
  }

  SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
      L"%s -- %s\n"
      L"%g\n"
      L"%s\n",
      Description, AssertionType,
      &EventId,
      AssertionDetail);
  Status = StslWriteLogFile (Private, Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Send assertion to remotion computer if the network 
  // record assertion utility installed.
  //
  NetRecordAssertion((NET_EFI_TEST_ASSERTION) Type, EventId, Buffer);
  
  //
  // write key file detail line
  //
  SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%g:%s|%s:%s",
          &EventId, AssertionType, Description, AssertionDetail);
  if ( SctStrLen (Buffer) + 3 < EFI_MAX_PRINT_BUFFER ) {
    SctStrCat (Buffer, L"\r\n");
  }
  Status = StslWriteKeyFile (Private, Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return Status;
}

EFI_STATUS
EFIAPI
StslRecordMessage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_VERBOSE_LEVEL                      VerboseLevel,
  IN CHAR16                                 *Message,
  ...
)
/*++

Routine Description:

  Records the test message.

Arguments:

  This          - Standard test library protocol instance.
  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.
  Message       - Format string for the detail test information.

Returns:

  EFI_SUCCESS   - record the message successfully.

--*/
{
  EFI_STATUS                      Status;
  VA_LIST                         Marker;
  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  STANDARD_TEST_PRIVATE_DATA      *Private;

  Status = EFI_SUCCESS;
  Private = STANDARD_TEST_PRIVATE_DATA_FROM_STSL (This);

  if (VerboseLevel <= Private->VerboseLevel) {
    VA_START(Marker, Message);
    SctVSPrint (Buffer, EFI_MAX_PRINT_BUFFER, Message, Marker);
    VA_END (Marker);

    if ( SctStrLen (Buffer) + 3 < EFI_MAX_PRINT_BUFFER ) {
      SctStrCat (Buffer, L"\r\n");
    }
    Status = StslWriteLogFile (Private, Buffer);
  }

  return Status;
}

EFI_STATUS
EFIAPI
StslGetResultCount (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *This,
  IN EFI_TEST_ASSERTION                     Type,
  OUT UINT32                                *Count
)
/*++

Routine Description:

  Gets the number of test results.

Arguments:

  This          - Standard test library protocol instance.
  Type          - Specifies the kind of test results to be returned.
  Count         - Number of specified test results.

Returns:

  EFI_SUCCESS   - get the assertion count successfully.

--*/
{
  STANDARD_TEST_PRIVATE_DATA      *Private;

  Private = STANDARD_TEST_PRIVATE_DATA_FROM_STSL (This);

  switch (Type) {
  case EFI_TEST_ASSERTION_PASSED:
    *Count = Private->PassCount;
    break;
  case EFI_TEST_ASSERTION_WARNING:
    *Count = Private->WarningCount;
    break;
  case EFI_TEST_ASSERTION_FAILED:
    *Count = Private->FailCount;
    break;
  default:
    return EFI_INVALID_PARAMETER;
    break;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
StslSetConfig (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This,
  IN EFI_LIB_CONFIG_DATA                    *Config
  )
/*++

Routine Description:

  One private interface function of the StandardTestLibrary to set config.

Arguments:

  This                  - the private interface instance structure.
  Config                - config data.

Returns:

  EFI_SUCCESS           - set config successfully.
  EFI_OUT_OF_RESOURCES  - not enough memory.
  EFI_INVALID_PARAMETER - invalid config data, some pointers are NULL

--*/
{
  STANDARD_TEST_PRIVATE_DATA      *Private;
  EFI_LIB_CONFIG_FILE_DATA        *FileConf;
  EFI_LIB_CONFIG_FILE_HANDLE      *PrivateFileConf;

  Private = STANDARD_TEST_PRIVATE_DATA_FROM_PI (This);
  StslFreePointer (Private);

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
      StslFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }

    PrivateFileConf->FileName = StslStrDuplicate (FileConf->FileName);
    if (PrivateFileConf->FileName == NULL) {
      StslFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    StslFreePointer (Private);
    return EFI_INVALID_PARAMETER;
  }

  //
  // SystemKeyFile
  //
  FileConf                            = &Config->SystemKeyFile;
  PrivateFileConf                     = &Private->SystemKeyFile;
  PrivateFileConf->EnableScreenOutput = FileConf->EnableScreenOutput;
  PrivateFileConf->OverwriteFile      = FileConf->OverwriteFile;

  if ((FileConf->DevicePath != NULL) && (FileConf->FileName != NULL)) {
    PrivateFileConf->DevicePath = SctDuplicateDevicePath (FileConf->DevicePath);
    if (PrivateFileConf->DevicePath == NULL) {
      StslFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }

    PrivateFileConf->FileName = StslStrDuplicate (FileConf->FileName);
    if (PrivateFileConf->FileName == NULL) {
      StslFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    StslFreePointer (Private);
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
      StslFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }

    PrivateFileConf->FileName = StslStrDuplicate (FileConf->FileName);
    if (PrivateFileConf->FileName == NULL) {
      StslFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    StslFreePointer (Private);
    return EFI_INVALID_PARAMETER;
  }

  //
  // CaseKeyFile
  //
  FileConf                            = &Config->CaseKeyFile;
  PrivateFileConf                     = &Private->CaseKeyFile;
  PrivateFileConf->EnableScreenOutput = FileConf->EnableScreenOutput;
  PrivateFileConf->OverwriteFile      = FileConf->OverwriteFile;

  if ((FileConf->DevicePath != NULL) && (FileConf->FileName != NULL)) {
    PrivateFileConf->DevicePath = SctDuplicateDevicePath (FileConf->DevicePath);
    if (PrivateFileConf->DevicePath == NULL) {
      StslFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }

    PrivateFileConf->FileName = StslStrDuplicate (FileConf->FileName);
    if (PrivateFileConf->FileName == NULL) {
      StslFreePointer (Private);
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    StslFreePointer (Private);
    return EFI_INVALID_PARAMETER;
  }

  //
  // BiosId
  //
  Private->BiosId = StslStrDuplicate (Config->BiosId);
  if (Private->BiosId == NULL) {
    StslFreePointer (Private);
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
  Private->ScenarioString = StslStrDuplicate (Config->ScenarioString);
  if (Private->ScenarioString == NULL) {
    StslFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Test Information
  //
  Private->TestRevision = Config->TestRevision;

  Private->TestName = StslStrDuplicate (Config->TestName);
  if (Private->TestName == NULL) {
    StslFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  SctCopyMem (&Private->EntryId, Config->EntryId, sizeof(EFI_GUID));

  Private->EntryName = StslStrDuplicate (Config->EntryName);
  if (Private->EntryName == NULL) {
    StslFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  Private->EntryDescription = StslStrDuplicate (Config->EntryDescription);
  if (Private->EntryDescription == NULL) {
    StslFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  Private->SupportProtocols = StslGuidsDuplicate (Config->SupportProtocols);
  if (Private->SupportProtocols == NULL) {
    StslFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  Private->VerboseLevel         = Config->VerboseLevel;

  //
  // Recovery Information
  //
  Private->IsRecovery           = Config->IsRecovery;
  if (Config->IsRecovery) {
    Private->PassCount      = Config->PassCount;
    Private->WarningCount   = Config->WarningCount;
    Private->FailCount      = Config->FailCount;
  } else {
    Private->PassCount      = 0;
    Private->WarningCount   = 0;
    Private->FailCount      = 0;
  }

  //
  // TestCategory
  //
  Private->TestCategory = StslStrDuplicate (Config->TestCategory);
  if (Private->TestCategory == NULL) {
    StslFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // DevicePath
  //
  Private->DevicePath = StslStrDuplicate (Config->DevicePath);
  if (Private->DevicePath == NULL) {
    StslFreePointer (Private);
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
StslBeginLogging (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This
  )
/*++

Routine Description:

  One private interface function of the StandardTestLibrary to begin logging.

Arguments:

  This          - the private interface instance structure.

Returns:

  EFI_SUCCESS   - begin logging successfully.

--*/
{
  EFI_STATUS                        Status;
  STANDARD_TEST_PRIVATE_DATA        *Private;
  CHAR16                            Buffer[EFI_MAX_PRINT_BUFFER];
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL  *Output;
  EFI_LIB_CONFIG_FILE_HANDLE        *FileConf;
  EFI_GUID                          *Guid;
  EFI_TIME                          *CurrentTime;

  Private = STANDARD_TEST_PRIVATE_DATA_FROM_PI (This);
  Output = Private->OutputProtocol;

  StslCloseAllFiles (Private);

  //
  // Open log and key files
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
  if (EFI_ERROR (Status)) {
    StslCloseAllFiles (Private);
    return Status;
  }

  //
  // Open system key file
  //
  FileConf = &Private->SystemKeyFile;
  Status = Output->Open (
                     Output,
                     FileConf->DevicePath,
                     FileConf->FileName,
                     FileConf->OverwriteFile,
                     &FileConf->FileHandle
                     );
  if (EFI_ERROR (Status)) {
    StslCloseAllFiles (Private);
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
  if (EFI_ERROR (Status)) {
    StslCloseAllFiles (Private);
    return Status;
  }

  //
  // Open case key file
  //
  FileConf = &Private->CaseKeyFile;
  Status = Output->Open (
                     Output,
                     FileConf->DevicePath,
                     FileConf->FileName,
                     FileConf->OverwriteFile,
                     &FileConf->FileHandle
                     );
  if (EFI_ERROR (Status)) {
    StslCloseAllFiles (Private);
    return Status;
  }

  //
  // Write log file header data
  //

  if (Private->IsRecovery) {
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
        L"%s"
        L"      *********RECOVERY*********\n"
        L"%s",
        DashLine, DashLine);
    StslWriteLogFile (Private, Buffer);

    CurrentTime = &Private->StartTime;
    tRT->GetTime (CurrentTime, NULL);

  } else {
    StslWriteLogFile (Private, DashLine);
    
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%s\n", Private->EntryName);
    StslWriteLogFile (Private, Buffer);
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Revision 0x%08x\n", Private->TestRevision);
    StslWriteLogFile (Private, Buffer);
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Test Entry Point GUID: %g\n", &Private->EntryId);
    StslWriteLogFile (Private, Buffer);
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Test Support Library GUIDs: \n");
    StslWriteLogFile (Private, Buffer);

    Guid = Private->SupportProtocols;
    while (SctCompareMem (Guid, &gEfiNullGuid, sizeof(EFI_GUID) ) != 0) {
      SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"  %g\n", Guid);
      StslWriteLogFile (Private, Buffer);
      Guid ++;
    }

    StslWriteLogFile (Private, DashLine);
    
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%s\n", Private->BiosId);
    StslWriteLogFile (Private, Buffer);
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Test Configuration #%d\n", Private->ConfigurationNumber);
    StslWriteLogFile (Private, Buffer);
    
    StslWriteLogFile (Private, DashLine);
    
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%s\n", Private->EntryDescription);
    StslWriteLogFile (Private, Buffer);
    
    StslWriteLogFile (Private, DashLine);

    StslWriteLogFileName (Private);
    CurrentTime = &Private->StartTime;
    tRT->GetTime (CurrentTime, NULL);
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Test Started: %t\n", CurrentTime);
    StslWriteLogFile (Private, Buffer);

    StslWriteLogFile (Private, DashLine);

    //
    // Write key file header line
    //
    SctSPrint (
      Buffer, EFI_MAX_PRINT_BUFFER, L"|HEAD|||%d|%s|%02d-%02d-%04d|%02d:%02d:%02d|%g|0x%08lx|%s|%s|%s|%s\n",
      Private->ConfigurationNumber,
      Private->ScenarioString,
      CurrentTime->Day,
      CurrentTime->Month,
      CurrentTime->Year,
      CurrentTime->Hour,
      CurrentTime->Minute,
      CurrentTime->Second,
      &Private->EntryId,
      Private->TestRevision,
      Private->EntryName,
      Private->TestName,
      Private->TestCategory,
      Private->DevicePath
      );

    StslWriteKeyFile (Private, Buffer);
  }

  //
  // Initial private data
  //
  Private->BeginLogging   = TRUE;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
StslEndLogging (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This,
  IN EFI_STATUS                             TestStatus
  )
/*++

Routine Description:

  One private interface function of the StandardTestLibrary to end logging.

Arguments:

  This          - the private interface instance structure.

Returns:

  EFI_SUCCESS   - end logging successfully.

--*/
{
  STANDARD_TEST_PRIVATE_DATA      *Private;
  CHAR16                          Buffer[EFI_MAX_PRINT_BUFFER];
  CHAR16                          Buffer1[EFI_MAX_PRINT_BUFFER];
  CHAR16                          Str[20];
  EFI_TIME                        CurrentTime;
  UINT32                          SecondsElapsed;
  UINT32                          DaysElapsed;
  UINT32                          HoursElapsed;
  UINT32                          MunitesElapsed;

  Private = STANDARD_TEST_PRIVATE_DATA_FROM_PI (This);

  //
  // Write log file terminator data
  //
  SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
          L"\nReturned Status Code: %r\n", TestStatus);
  StslWriteLogFile (Private, Buffer);

  if ((Private->PassCount    > 0 ) &&
      (Private->WarningCount == 0) &&
      (Private->FailCount    == 0)) {
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
            L"\n%s: [PASSED]\n", Private->EntryName);
  } else if ((Private->PassCount    > 0 ) &&
             (Private->WarningCount > 0 ) &&
             (Private->FailCount    == 0)) {
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
            L"\n%s: [PASSED WITH WARNINGS]\n", Private->EntryName);
  } else if ((Private->PassCount    >= 0) &&
             (Private->WarningCount >= 0) &&
             (Private->FailCount    > 0 )) {
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
            L"\n%s: [FAILED]\n", Private->EntryName);
  } else {
    SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
            L"\n%s: [NOT SUPPORTED]\n", Private->EntryName);
  }
  StslWriteLogFile (Private, Buffer);
  
  SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
      L"  Passes........... %d\n"
      L"  Warnings......... %d\n"
      L"  Errors........... %d\n",
      (UINTN)Private->PassCount,
      (UINTN)Private->WarningCount,
      (UINTN)Private->FailCount);
  StslWriteLogFile (Private, Buffer);

  StslWriteLogFile (Private, DashLine);
  SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"%s\n", Private->BiosId);
  StslWriteLogFile (Private, Buffer);
  SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Revision 0x%08x\n", Private->TestRevision);
  StslWriteLogFile (Private, Buffer);
  SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER, L"Test Entry Point GUID: %g\n", &Private->EntryId);
  StslWriteLogFile (Private, Buffer);
  StslWriteLogFile (Private, DashLine);

  StslWriteLogFileName (Private);

  tRT->GetTime (&CurrentTime, NULL);

  SecondsElapsed = SecondsElapsedFromBaseYear (
                     Private->StartTime.Year,
                     CurrentTime.Year,
                     CurrentTime.Month,
                     CurrentTime.Day,
                     CurrentTime.Hour,
                     CurrentTime.Minute,
                     CurrentTime.Second
                   ) -
                   SecondsElapsedFromBaseYear (
                     Private->StartTime.Year,
                     Private->StartTime.Year,
                     Private->StartTime.Month,
                     Private->StartTime.Day,
                     Private->StartTime.Hour,
                     Private->StartTime.Minute,
                     Private->StartTime.Second
                   );

  DaysElapsed     = SecondsElapsed / SECS_PER_DAY;
  SecondsElapsed -= DaysElapsed * SECS_PER_DAY;
  HoursElapsed    = SecondsElapsed / SECS_PER_HOUR;
  SecondsElapsed -= HoursElapsed * SECS_PER_HOUR;
  MunitesElapsed  = SecondsElapsed / SECS_PER_MIN;
  SecondsElapsed -= MunitesElapsed * SECS_PER_MIN;

  SctStrCpy (Buffer1, L"Elapsed Time: ");
  MyUINTToStr (DaysElapsed, Str);
  SctStrCat (Buffer1, Str);
  SctStrCat (Buffer1, L" Days ");
  MyUINTToStr (HoursElapsed, Str);
  SctStrCat (Buffer1, Str);
  SctStrCat (Buffer1, L":");
  MyUINTToStr (MunitesElapsed, Str);
  SctStrCat (Buffer1, Str);
  SctStrCat (Buffer1, L":");
  MyUINTToStr (SecondsElapsed, Str);
  SctStrCat (Buffer1, Str);
  SctStrCat (Buffer1, L"\n");

  //To do: investigate the Sprint()
  //SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
  //        L"Elapsed Time: %d Days %02d:%02d:%02d\n",
  //        DaysElapsed, HoursElapsed, MunitesElapsed, SecondsElapsed);
  
  SctSPrint (Buffer, EFI_MAX_PRINT_BUFFER,
      L"Test Finished: %t\n"
      L"%s\r\n"
      L"%s", // -----------------------------
      &CurrentTime,
      Buffer1,
      DashLine);
  StslWriteLogFile (Private, Buffer);

  //
  // Write key file terminator line
  //
  SctSPrint (
    Buffer, EFI_MAX_PRINT_BUFFER, L"|TERM|%04x|%02d-%02d-%04d|%02d:%02d:%02d|%d %02d:%02d:%02d\n",
    (UINT16)(TestStatus & 0xFFFF),
    CurrentTime.Day,
    CurrentTime.Month,
    CurrentTime.Year,
    CurrentTime.Hour,
    CurrentTime.Minute,
    CurrentTime.Second,
    DaysElapsed,
    HoursElapsed,
    MunitesElapsed,
    SecondsElapsed
    );
  StslWriteKeyFile (Private, Buffer);

  //
  // Close log and key files
  //
  StslCloseAllFiles (Private);

  Private->BeginLogging   = FALSE;

  return EFI_SUCCESS;
}

//
// Internal functions
//

EFI_STATUS
StslCloseAllFiles (
  IN STANDARD_TEST_PRIVATE_DATA   *Private
  )
{
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL  *Output;
  EFI_LIB_CONFIG_FILE_HANDLE        *FileConf;

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
  // Close system key file
  //
  FileConf = &Private->SystemKeyFile;
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

  //
  // Close case key file
  //
  FileConf = &Private->CaseKeyFile;
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
StslWriteLogFile (
  IN STANDARD_TEST_PRIVATE_DATA   *Private,
  IN CHAR16                       *String
  )
{
  EFI_STATUS                        Status;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL  *Output;
  EFI_FILE_HANDLE                   FileHandle;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL      *ConOut;

  Output = Private->OutputProtocol;
  ConOut = tST->ConOut;

  Status = EFI_SUCCESS;

  //
  // System log file
  //
  if (Private->SystemLogFile.EnableScreenOutput) {
    Status = ConOut->OutputString (ConOut, String);
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
  }

  FileHandle = Private->SystemLogFile.FileHandle;
  if (FileHandle != NULL) {
    Status = Output->Write (Output, FileHandle, String);
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
  }

  //
  // Case log file
  //
  if (Private->CaseLogFile.EnableScreenOutput) {
    Status = ConOut->OutputString (ConOut, String);
    if ( EFI_ERROR (Status) ) {
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
StslWriteKeyFile (
  IN STANDARD_TEST_PRIVATE_DATA   *Private,
  IN CHAR16                       *String
  )
{
  EFI_STATUS                        Status;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL  *Output;
  EFI_FILE_HANDLE                   FileHandle;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL      *ConOut;

  Output = Private->OutputProtocol;
  ConOut = tST->ConOut;

  Status = EFI_SUCCESS;

  //
  // System key file
  //
  if (Private->SystemKeyFile.EnableScreenOutput) {
    Status = ConOut->OutputString (ConOut, String);
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
  }

  FileHandle = Private->SystemKeyFile.FileHandle;
  if (FileHandle != NULL) {
    Status = Output->Write (Output, FileHandle, String);
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
  }

  //
  // Case key file
  //
  if (Private->CaseKeyFile.EnableScreenOutput) {
    Status = ConOut->OutputString (ConOut, String);
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
  }

  FileHandle = Private->CaseKeyFile.FileHandle;
  if (FileHandle != NULL) {
    Status = Output->Write (Output, FileHandle, String);
  }

  return Status;
}

EFI_STATUS
StslWriteLogFileName (
  IN STANDARD_TEST_PRIVATE_DATA   *Private
  )
{
  EFI_STATUS                        Status;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL  *Output;
  EFI_FILE_HANDLE                   FileHandle;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL      *ConOut;
  CHAR16                            String[EFI_MAX_PRINT_BUFFER];

  Output = Private->OutputProtocol;
  ConOut = tST->ConOut;

  Status = EFI_SUCCESS;

  //
  // System log file
  //
  SctSPrint (String, EFI_MAX_PRINT_BUFFER, L"Logfile: \"%s\"\n",
          Private->SystemLogFile.FileName);
  if (Private->SystemLogFile.EnableScreenOutput) {
    Status = ConOut->OutputString (ConOut, String);
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
  }

  FileHandle = Private->SystemLogFile.FileHandle;
  if (FileHandle != NULL) {
    Status = Output->Write (Output, FileHandle, String);
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
  }

  //
  // Case log file
  //
  SctSPrint (String, EFI_MAX_PRINT_BUFFER, L"Logfile: \"%s\"\n",
          Private->CaseLogFile.FileName);
  if (Private->CaseLogFile.EnableScreenOutput) {
    Status = ConOut->OutputString (ConOut, String);
    if ( EFI_ERROR (Status) ) {
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
StslFreePointer (
  IN STANDARD_TEST_PRIVATE_DATA   *Private
  )
{
  EFI_LIB_CONFIG_FILE_HANDLE      *FileConf;

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
  // Free DevicePath and FileName of SystemKeyFile
  //
  FileConf = &Private->SystemKeyFile;
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
  // Free DevicePath and FileName of CaseKeyFile
  //
  FileConf = &Private->CaseKeyFile;
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

  //
  // Free TestCategory
  //
  if (Private->TestCategory != NULL) {
    tBS->FreePool (Private->TestCategory);
    Private->TestCategory = NULL;
  }

  //
  // Free DevicePath
  //
  if (Private->DevicePath != NULL) {
    tBS->FreePool (Private->DevicePath);
    Private->DevicePath = NULL;
  }

  return EFI_SUCCESS;
}

UINT32
SecondsElapsedFromBaseYear (
  IN UINT16             BaseYear,
  IN UINT16             Year,
  IN UINT8              Month,
  IN UINT8              Day,
  IN UINT8              Hour,
  IN UINT8              Minute,
  IN UINT8              Second
  )
{
  UINTN       Seconds;
  UINT32      LeapYear;
  INTN        Index;

  Seconds  = 0;
  for (Index = BaseYear; Index < Year; Index ++) {
    if (IS_LEAP(Index)) {
      Seconds += DAYS_PER_LYEAR * SECS_PER_DAY;
    } else {
      Seconds += DAYS_PER_NYEAR * SECS_PER_DAY;
    }
  }

  LeapYear = IS_LEAP(Year);
  for (Index = 0; Index < Month - 1; Index ++) {
    Seconds += MonthLengths[LeapYear][Index] * SECS_PER_DAY;
  }

  for (Index = 0; Index < Day - 1; Index ++) {
    Seconds += SECS_PER_DAY;
  }

  for (Index = 0; Index < Hour; Index ++) {
    Seconds += SECS_PER_HOUR;
  }

  for (Index = 0; Index < Minute; Index ++) {
    Seconds += SECS_PER_MIN;
  }

  return (UINT32) (Seconds + Second);
}

CHAR16 *
StslStrDuplicate (
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
StslGuidsDuplicate (
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

//
// Add a private function to cross the issue of SctSPrint()
//
EFI_STATUS
MyUINTToStr (
  IN UINTN        Num,
  OUT CHAR16      *StringNum
)
{
  UINTN          CurrentNum;

  
  CurrentNum = Num % 10;
  Num = Num/10;
  
  StringNum[0] = (CHAR16)( L'0' + Num );
  StringNum[1] = (CHAR16)( L'0' + CurrentNum );
  StringNum[2] = '\0';
  
  return EFI_SUCCESS;
}
