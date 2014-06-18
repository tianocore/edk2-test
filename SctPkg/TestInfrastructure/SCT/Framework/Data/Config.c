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

  Config.c

Abstract:

  This file provides the services to manage the configuration data.

--*/

#include "Sct.h"

//
// Internal definitions
//

#define EFI_SCT_SECTION_CONFIG              L"Configuration Data"

//
// Internal functions declaration
//

EFI_STATUS
InitializeConfigData (
  OUT EFI_SCT_CONFIG_DATA         *ConfigData
  );

EFI_STATUS
ConfigGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
ConfigSetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  );


//
// External functions implementation
//

EFI_STATUS
LoadConfigData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_SCT_CONFIG_DATA         *ConfigData
  )
/*++

Routine Description:

  Load configuration data from a file.

Arguments:

  DevicePath    - Device path of the file.
  FileName      - Name of the file.
  ConfigData    - Pointer to the configuration data.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  CHAR16                Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  UINT32                Revision;
  EFI_INI_FILE_HANDLE   IniFile;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (ConfigData == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load config data from <%s>", FileName));

  //
  // Initialize the configuration data
  //
  Status = InitializeConfigData (ConfigData);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initilize config data - %r", Status));
    FreeConfigData (ConfigData);
    return Status;
  }

  //
  // Open the file
  //
  Status = gFT->TplProtocol->EfiIniOpen (
                               gFT->TplProtocol,
                               DevicePath,
                               FileName,
                               &IniFile
                               );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open config file - %r", Status));
    FreeConfigData (ConfigData);
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // If the configuration file does not exist, use the default setting
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Config file doesn't exist"));
    return EFI_SUCCESS;
  }

  //
  // Check the revision info
  //
  Status = ConfigGetString (IniFile, L"Revision", Buffer);
  if (EFI_ERROR (Status)) {
    //
    // Without the revision info, ignore the configuration data
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without revision"));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return EFI_SUCCESS;
  }

  Status = SctHexStrToShort (Buffer, &Revision);
  if (EFI_ERROR (Status) || (Revision != ConfigData->Revision)) {
    //
    // With unsupported revision info, ignore the configuration data
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid revision"));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return EFI_SUCCESS;
  }

  //
  // Get the maximum run time of a test case
  //
  Status = ConfigGetString (IniFile, L"TestCaseMaxRunTime", Buffer);
  if (!EFI_ERROR (Status)) {
    SctStrToInt (Buffer, &ConfigData->TestCaseMaxRunTime);
  }

  //
  // Get the screen output enabled
  //
  Status = ConfigGetString (IniFile, L"EnableScreenOutput", Buffer);
  if (!EFI_ERROR (Status)) {
    SctStrToBoolean (Buffer, &ConfigData->EnableScreenOutput);
  }

  //
  // Get the BIOS ID string
  //
  Status = ConfigGetString (IniFile, L"BiosId", Buffer);
  if (!EFI_ERROR (Status)) {
    tBS->FreePool (ConfigData->BiosId);
    ConfigData->BiosId = SctStrDuplicate (Buffer);
  }

  //
  // Get the platform number
  //
  Status = ConfigGetString (IniFile, L"PlatformNumber", Buffer);
  if (!EFI_ERROR (Status)) {
    SctStrToInt (Buffer, &ConfigData->PlatformNumber);
  }

  //
  // Get the configuration number
  //
  Status = ConfigGetString (IniFile, L"ConfigurationNumber", Buffer);
  if (!EFI_ERROR (Status)) {
    SctStrToInt (Buffer, &ConfigData->ConfigurationNumber);
  }

  //
  // Get the scenario string
  //
  Status = ConfigGetString (IniFile, L"ScenarioString", Buffer);
  if (!EFI_ERROR (Status)) {
    tBS->FreePool (ConfigData->ScenarioString);
    ConfigData->ScenarioString = SctStrDuplicate (Buffer);
  }

  //
  // Get the edit command string
  //
  Status = ConfigGetString (IniFile, L"EditCommandString", Buffer);
  if (!EFI_ERROR (Status)) {
    tBS->FreePool (ConfigData->EditCommandString);
    ConfigData->EditCommandString = SctStrDuplicate (Buffer);
  }

  //
  // Check error
  //
  if ((ConfigData->BiosId         == NULL) ||
      (ConfigData->ScenarioString == NULL)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    FreeConfigData (ConfigData);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Close the file
  //
  gFT->TplProtocol->EfiIniClose (
                      gFT->TplProtocol,
                      IniFile
                      );

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SaveConfigData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_SCT_CONFIG_DATA          *ConfigData
  )
/*++

Routine Description:

  Save the configuration data into a file.

Arguments:

  DevicePath    - Device path of the file.
  FileName      - Name of the file.
  ConfigData    - Pointer to the configuration data.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  CHAR16                Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  EFI_INI_FILE_HANDLE   IniFile;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (ConfigData == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Save config data into <%s>", FileName));

  //
  // Open the file
  //
  Status = gFT->TplProtocol->EfiIniOpen (
                               gFT->TplProtocol,
                               DevicePath,
                               FileName,
                               &IniFile
                               );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open config file - %r", Status));
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // Not exist, create the file
    //
    Status = gFT->TplProtocol->EfiIniCreate (
                                 gFT->TplProtocol,
                                 DevicePath,
                                 FileName,
                                 &IniFile
                                 );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create config file - %r", Status));
      return Status;
    }
  }

  //
  // Save the revision
  //
  Status = SctShortToHexStr (ConfigData->Revision, Buffer);
  if (!EFI_ERROR (Status)) {
    ConfigSetString (IniFile, L"Revision", Buffer);
  }

  //
  // Save the maximum run time of a test case
  //
  Status = SctIntToStr (ConfigData->TestCaseMaxRunTime, Buffer);
  if (!EFI_ERROR (Status)) {
    ConfigSetString (IniFile, L"TestCaseMaxRunTime", Buffer);
  }

  //
  // Save the screen output enabled
  //
  Status = SctBooleanToStr (ConfigData->EnableScreenOutput, Buffer);
  if (!EFI_ERROR (Status)) {
    ConfigSetString (IniFile, L"EnableScreenOutput", Buffer);
  }

  //
  // Save the BIOS ID string
  //
  ConfigSetString (IniFile, L"BiosId", ConfigData->BiosId);

  //
  // Save the platform number
  //
  Status = SctIntToStr (ConfigData->PlatformNumber, Buffer);
  if (!EFI_ERROR (Status)) {
    ConfigSetString (IniFile, L"PlatformNumber", Buffer);
  }

  //
  // Save the configuration number
  //
  Status = SctIntToStr (ConfigData->ConfigurationNumber, Buffer);
  if (!EFI_ERROR (Status)) {
    ConfigSetString (IniFile, L"ConfigurationNumber", Buffer);
  }

  //
  // Save the scenario string
  //
  ConfigSetString (IniFile, L"ScenarioString", ConfigData->ScenarioString);

  //
  // Save the edit command string
  //
  ConfigSetString (IniFile, L"EditCommandString", ConfigData->EditCommandString);

  //
  // Close the file
  //
  gFT->TplProtocol->EfiIniClose (
                      gFT->TplProtocol,
                      IniFile
                      );

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeConfigData (
  IN EFI_SCT_CONFIG_DATA          *ConfigData
  )
/*++

Routine Description:

  Free the configuration data.

  Notice: It just frees the data in this structure, but does not free the
  structure itself.

Arguments:

  ConfigData    - Pointer to the configuration data.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  //
  // Check parameters
  //
  if (ConfigData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Free the items of configuration data
  //
  if (ConfigData->BiosId != NULL) {
    tBS->FreePool (ConfigData->BiosId);
    ConfigData->BiosId = NULL;
  }

  if (ConfigData->ScenarioString != NULL) {
    tBS->FreePool (ConfigData->ScenarioString);
    ConfigData->ScenarioString = NULL;
  }

  if (ConfigData->EditCommandString != NULL) {
    tBS->FreePool (ConfigData->EditCommandString);
    ConfigData->EditCommandString = NULL;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
InitializeConfigData (
  OUT EFI_SCT_CONFIG_DATA         *ConfigData
  )
/*++

Routine Description:

  Initialize the config data.

--*/
{
  //
  // Check parameters
  //
  if (ConfigData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize the config data structure
  //
  SctZeroMem (ConfigData, sizeof(EFI_SCT_CONFIG_DATA));

  //
  // Initialize the items of config data
  //
  ConfigData->Signature           = EFI_SCT_CONFIG_DATA_SIGNATURE;
  ConfigData->Revision            = EFI_SCT_CONFIG_DATA_REVISION;

  ConfigData->TestCaseMaxRunTime  = TEST_CASE_MAX_RUN_TIME_DEFAULT;
  ConfigData->EnableScreenOutput  = ENABLE_SCREEN_OUTPUT_DEFAULT;

  ConfigData->BiosId              = SctStrDuplicate (BIOS_ID_DEFAULT);
  ConfigData->PlatformNumber      = PLATFORM_NUMBER_DEFAULT;
  ConfigData->ConfigurationNumber = CONFIGURATION_NUMBER_DEFAULT;
  ConfigData->ScenarioString      = SctStrDuplicate (SCENARIO_STRING_DEFAULT);

  ConfigData->EditCommandString   = SctStrDuplicate (EDIT_COMMAND_DEFAULT);

  ConfigData->TestLevel           = EFI_TEST_LEVEL_MINIMAL | EFI_TEST_LEVEL_DEFAULT;
  ConfigData->VerboseLevel        = EFI_VERBOSE_LEVEL_DEFAULT;

  //
  // Check error
  //
  if ((ConfigData->BiosId         == NULL) ||
      (ConfigData->ScenarioString == NULL)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ConfigGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Get a string from a configuration section.

--*/
{
  UINT32      BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetString (
                    IniFile,
                    EFI_SCT_SECTION_CONFIG,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}


EFI_STATUS
ConfigSetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  )
/*++

Routine Description:

  Set a string into a configuration section.

--*/
{
  return IniFile->SetString (
                    IniFile,
                    EFI_SCT_SECTION_CONFIG,
                    Key,
                    Buffer
                    );
}
