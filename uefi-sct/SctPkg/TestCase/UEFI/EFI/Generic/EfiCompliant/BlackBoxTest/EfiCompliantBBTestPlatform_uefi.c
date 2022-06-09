/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EfiCompliantBbTestPlatform.c

Abstract:

  Check the platform specific elements in EFI Spec.

--*/

//
// Includes
//

#include "SctLib.h"
#include "EfiCompliantBbTestMain_uefi.h"
#include EFI_PROTOCOL_DEFINITION (SimpleTextIn)
#include EFI_PROTOCOL_DEFINITION (SimpleTextInEx)
#include EFI_PROTOCOL_DEFINITION (SimpleTextOut)
#include EFI_PROTOCOL_DEFINITION (UgaDraw)
#include EFI_PROTOCOL_DEFINITION (UgaIo)
#include EFI_PROTOCOL_DEFINITION (SimplePointer)
#include EFI_PROTOCOL_DEFINITION (BlockIo)
#include EFI_PROTOCOL_DEFINITION (DiskIo)
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)
#include EFI_PROTOCOL_DEFINITION (UnicodeCollation)
#include EFI_PROTOCOL_DEFINITION (SimpleNetwork)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCode)
#include EFI_PROTOCOL_DEFINITION (Bis)
#include EFI_PROTOCOL_DEFINITION (SerialIo)
#include EFI_PROTOCOL_DEFINITION (PciRootBridgeIo)
#include EFI_PROTOCOL_DEFINITION (PciIo)
#include EFI_PROTOCOL_DEFINITION (DeviceIo)
#include EFI_PROTOCOL_DEFINITION (UsbHostController)
#include EFI_PROTOCOL_DEFINITION (UsbIo)
#include EFI_PROTOCOL_DEFINITION (ScsiPassThru)
#include EFI_PROTOCOL_DEFINITION (DebugSupport)
#include EFI_PROTOCOL_DEFINITION (DebugPort)
#include EFI_PROTOCOL_DEFINITION (PlatformDriverOverride)

#include EFI_PROTOCOL_DEFINITION (ScsiPassThruExt)
#include EFI_PROTOCOL_DEFINITION (DevicePathFromText)
#include EFI_PROTOCOL_DEFINITION (DevicePathToText)
#include EFI_PROTOCOL_DEFINITION (GraphicsOutput)
#include EFI_PROTOCOL_DEFINITION (EdidActive)
#include EFI_PROTOCOL_DEFINITION (EdidDiscovered)
#include EFI_PROTOCOL_DEFINITION (ManagedNetwork)
#include <Protocol/NetworkInterfaceIdentifier.h>
#include EFI_PROTOCOL_DEFINITION (IScsiInitiatorName)
#include EFI_PROTOCOL_DEFINITION (ScsiIo)
#include EFI_PROTOCOL_DEFINITION (Arp)
#include EFI_PROTOCOL_DEFINITION (Ip4)
#include EFI_PROTOCOL_DEFINITION (Tcp4)
#include EFI_PROTOCOL_DEFINITION (Udp4)
#include EFI_PROTOCOL_DEFINITION (Dhcp4)
#include EFI_PROTOCOL_DEFINITION (Mtftp4)
#include EFI_PROTOCOL_DEFINITION (Ip4Config)
#include EFI_PROTOCOL_DEFINITION (Ebc)
#include EFI_PROTOCOL_DEFINITION (HiiConfigAccess)
#include EFI_PROTOCOL_DEFINITION (HiiConfigRouting)
#include EFI_PROTOCOL_DEFINITION (HiiDatabase)
#include EFI_PROTOCOL_DEFINITION (HiiString)
#include EFI_PROTOCOL_DEFINITION (HiiFont)
#include EFI_PROTOCOL_DEFINITION (AuthenticationInfo)
#include <Protocol/ServiceBinding.h>

extern EFI_GUID gGlobalVariableGuid;

//
// Module definitions
//

#define SECTION_NAME_PLATFORM_SPECIFIC      L"Platform Specific"
#define SECTION_NAME_CONFIGURATION_SPECIFIC L"Test Configuration Specific"
#define CONFIN_TITLE_STRING                 L"|=================  Configuration Environment  =================|"
#define MAX_SIZE                            0xFF

#define EFI_DHCP6_SERVICE_BINDING_PROTOCOL_GUID \
 { 0x9fb9a8a1, 0x2f4a, 0x43a6, {0x88, 0x9c, 0xd0, 0xf7, 0xb6, 0xc4, 0x7a, 0xd5 }}
#define EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID \
 { 0xec20eb79, 0x6c1a, 0x4664, {0x9a, 0xd, 0xd2, 0xe4, 0xcc, 0x16, 0xd6,  0x64 }}
#define EFI_IP6_SERVICE_BINDING_PROTOCOL_GUID \
{ 0xec835dd3, 0xfe0f, 0x617b, {0xa6, 0x21, 0xb3, 0x50, 0xc3, 0xe1, 0x33, 0x88 }}
#define EFI_UDP6_SERVICE_BINDING_PROTOCOL_GUID \
{ 0x66ed4721, 0x3c98, 0x4d3e, {0x81, 0xe3, 0xd0, 0x3d, 0xd3, 0x9a, 0x72, 0x54 }}
#define EFI_IP6_CONFIG_PROTOCOL_GUID \
{ 0x937fe521, 0x95ae, 0x4d1a, {0x89, 0x29, 0x48, 0xbc, 0xd9, 0xa, 0xd3, 0x1a }}
#define EFI_VLAN_CONFIG_PROTOCOL_GUID \
{ 0x9e23d768, 0xd2f3, 0x4366, {0x9f, 0xc3, 0x3a, 0x7a, 0xba, 0x86, 0x43, 0x74 }}

#define EFI_DHCP6_PROTOCOL_GUID \
{ 0x87c8bad7, 0x595, 0x4053, {0x82, 0x97, 0xde, 0xde, 0x39, 0x5f, 0x5d, 0x5b }}
#define EFI_TCP6_PROTOCOL_GUID \
{ 0x46e44855, 0xbd60, 0x4ab7, {0xab, 0xd, 0xa6, 0x79, 0xb9, 0x44, 0x7d, 0x77 }}
#define EFI_IP6_PROTOCOL_GUID \
{ 0x2c8759d5, 0x5c2d, 0x66ef, {0x92, 0x5f, 0xb6, 0x6c, 0x10, 0x19, 0x57, 0xe2 }}
#define EFI_UDP6_PROTOCOL_GUID \
{ 0x4f948815, 0xb4b9, 0x43cb, {0x8a, 0x33, 0x90, 0xe0, 0x60, 0xb3, 0x49, 0x55 }}

EFI_GUID gEfiDhcp6ServiceBindingProtocolGuid = EFI_DHCP6_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiTcp6ServiceBindingProtocolGuid  = EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiIp6ServiceBindingProtocolGuid   = EFI_IP6_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiUdp6ServiceBindingProtocolGuid  = EFI_UDP6_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiIp6ConfigProtocolGuid           = EFI_IP6_CONFIG_PROTOCOL_GUID;
EFI_GUID gEfiVlanConfigProtocolGuid          = EFI_VLAN_CONFIG_PROTOCOL_GUID;

EFI_GUID gEfiDhcp6ProtocolGuid               = EFI_DHCP6_PROTOCOL_GUID;
EFI_GUID gEfiTcp6ProtocolGuid                = EFI_TCP6_PROTOCOL_GUID;
EFI_GUID gEfiIp6ProtocolGuid                 = EFI_IP6_PROTOCOL_GUID;
EFI_GUID gEfiUdp6ProtocolGuid                = EFI_UDP6_PROTOCOL_GUID;

EFI_GUID gEfiIp4Config2ProtocolGuid = { 0x5b446ed1, 0xe30b, 0x4faa, {0x87, 0x1a, 0x36, 0x54, 0xec, 0xa3, 0x60, 0x80 }};

EFI_GUID gEfiNvmExpressPassThruProtocolGuid = { 0x52c78312, 0x8edc, 0x4233, {0x98, 0xf2, 0x1a, 0x1a, 0xa5, 0xe3, 0x88, 0xa5 }};

EFI_GUID gEfiAtaPassThruProtocolGuid = {0x1d3de7f0,0x807,0x424f, {0xaa,0x69,0x11,0xa5,0x4e,0x19,0xa4,0x6f }};

EFI_GUID gEfiDns4ServiceBindingProtocolGuid = { 0xb625b186, 0xe063, 0x44f7, {0x89, 0x5, 0x6a, 0x74, 0xdc, 0x6f, 0x52, 0xb4 }};

EFI_GUID gEfiDns4ProtocolGuid = { 0xae3d28cc, 0xe05b, 0x4fa1, {0xa0, 0x11, 0x7e, 0xb5, 0x5a, 0x3f, 0x14, 0x1 }};

EFI_GUID gEfiDns6ServiceBindingProtocolGuid = { 0x7f1647c8, 0xb76e, 0x44b2, {0xa5, 0x65, 0xf7, 0xf, 0xf1, 0x9c, 0xd1, 0x9e }};

EFI_GUID gEfiDns6ProtocolGuid = { 0xca37bc1f, 0xa327, 0x4ae9, {0x82, 0x8a, 0x8c, 0x40, 0xd8, 0x50, 0x6a, 0x17 }};

EFI_GUID gEfiTlsServiceBindingProtocolGuid = { 0x952cb795, 0xff36, 0x48cf, {0xa2, 0x49, 0x4d, 0xf4, 0x86, 0xd6, 0xab, 0x8d }};

EFI_GUID gEfiTlsConfigurationProtocolGuid = { 0x1682fe44, 0xbd7a, 0x4407, {0xb7, 0xc7, 0xdc, 0xa3, 0x7c, 0xa3, 0x92, 0x2d }};

EFI_GUID gEfiTlsProtocolGuid = { 0xca959f, 0x6cfa, 0x4db1, {0x95, 0xbc, 0xe4, 0x6c, 0x47, 0x51, 0x43, 0x90 }};

EFI_GUID gEfiHttpServiceBindingProtocolGuid = {0xbdc8e6af, 0xd9bc, 0x4379, {0xa7, 0x2a, 0xe0, 0xc4, 0xe7, 0x5d, 0xae, 0x1c }};

EFI_GUID gEfiHttpUtilitiesProtocolGuid = { 0x3E35C163, 0x4074, 0x45DD, {0x43, 0x1E, 0x23, 0x98, 0x9D, 0xD8, 0x6B, 0x32 }};

EFI_GUID gEfiHttpProtocolGuid = {0x7A59B29B, 0x910B, 0x4171, {0x82, 0x42, 0xA8, 0x5A, 0x0D, 0xF2, 0x5B, 0x5B }};

EFI_GUID gEfiBlueToothHcProtocolGuid = { 0xb3930571, 0xbeba, 0x4fc5, {0x92, 0x3, 0x94, 0x27, 0x24, 0x2e, 0x6a, 0x43 }};

EFI_GUID gEfiBlueToothServiceBindingProtocolGuid = { 0x388278d3, 0x7b85, 0x42f0, {0xab, 0xa9, 0xfb, 0x4b, 0xfd, 0x69, 0xf5, 0xab }};

EFI_GUID gEfiBlueToothIoProtocolGuid = { 0x467313de, 0x4e30, 0x43f1,{ 0x94, 0x3e, 0x32, 0x3f, 0x89, 0x84, 0x5d, 0xb5 }};

EFI_GUID gEfiBlueToothConfigProtocolGuid = { 0x62960cf3, 0x40ff, 0x4263,{0xa7, 0x7c, 0xdf, 0xde, 0xbd, 0x19, 0x1b, 0x4b }};

EFI_GUID gEfiEapProtocolGuid = { 0x5d9f96db, 0xe731, 0x4caa, {0xa0, 0x0d, 0x72, 0xe1, 0x87, 0xcd, 0x77, 0x62 }};

EFI_GUID gEfiEapManagement2ProtocolGuid = { 0x5e93c847, 0x456d, 0x40b3, {0xa6, 0xb4, 0x78, 0xb0, 0xc9, 0xcf, 0x7f, 0x20 }};

EFI_GUID gEfiEapConfigProtocolGuid = { 0xe5b58dbb, 0x7688, 0x44b4, {0x97, 0xbf, 0x5f, 0x1d, 0x4b, 0x7c, 0xc8, 0xdb }};

EFI_GUID gEfiIPSecConfigProtocolGuid = { 0xce5e5929, 0xc7a3, 0x4602, {0xad, 0x9e, 0xc9, 0xda, 0xf9, 0x4e, 0xbf, 0xcf }};

EFI_GUID gEfiIPSec2ProtocolGuid = { 0xa3979e64, 0xace8, 0x4ddc, {0xbc, 0x07, 0x4d, 0x66, 0xb8, 0xfd, 0x09, 0x77 }};

EFI_GUID gEfiBlueToothAttributeProtocolGuid = { 0x898890e9, 0x84b2, 0x4f3a, { 0x8c, 0x58, 0xd8, 0x57, 0x78, 0x13, 0xe0, 0xac }};

EFI_GUID gEfiBlueToothLEConfigProtocolGuid = { 0x8f76da58, 0x1f99, 0x4275, { 0xa4, 0xec, 0x47, 0x56, 0x51, 0x5b, 0x1c, 0xe8 }};

typedef struct CONFIG_ERROR_DATA {
  UINT8                ErrorCount;
  CHAR16               *TitleString;
  EFI_INI_FILE_HANDLE  ConfigINI;
} CONFIG_ERROR_DATA;

//
// The Max length of pre-defined string value(yes or no)
// in the EfiCompliant.ini
// which is the platform specific configuration
//
#define MAX_LENGTH  10

//
// Internal functions declarations
//

EFI_TEST_ASSERTION
NeedOneOrWarning (
  IN BOOLEAN                      ValueA
  );

EFI_TEST_ASSERTION
NeedTwoOrWarning (
  IN BOOLEAN                      ValueA,
  IN BOOLEAN                      ValueB
  );

EFI_TEST_ASSERTION
NeedThreeOrWarning (
  IN BOOLEAN                      ValueA,
  IN BOOLEAN                      ValueB,
  IN BOOLEAN                      ValueC
  );

EFI_TEST_ASSERTION
NeedFourOrWarning (
  IN BOOLEAN                      ValueA,
  IN BOOLEAN                      ValueB,
  IN BOOLEAN                      ValueC,
  IN BOOLEAN                      valueD
  );

EFI_TEST_ASSERTION
NeedOrWarning (
  IN UINTN                        ValueCount,
  IN BOOLEAN                      *Value
  );
  
EFI_STATUS
CheckConsoleProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckHiiProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckGraphicalConsoleProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckPointerProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckBootFromDiskProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckBootFromNetworkProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckUefiNetworkApplication (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );
  
EFI_STATUS
CheckUefiV6NetworkApplication (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );  

EFI_STATUS
CheckUartProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckPciProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckUsbProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckNVMeProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckBootFromNVMe (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckScsiProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );
  
EFI_STATUS
CheckBootFromScsi (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckBootFromIScsi (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckDebugProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckDriverOverrideProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckATAProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckEbcProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckDNS4Protocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckDNS6Protocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckTLSProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckHTTPProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckEAPProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckBlueToothClassicProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckBlueToothLEProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckIPSecProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

CONFIG_ERROR_DATA*
ConstructionAndAcquisition (
  IN CHAR16                               *TitleString,
  IN EFI_INI_FILE_HANDLE                  ConfigINI
);

EFI_STATUS
GenTestConfigTitle (
  IN      EFI_INI_FILE_HANDLE  IniFile,
  IN OUT  EFI_TEST_ASSERTION   *AssertionType,
  IN      CHAR16               *TestItemString
);

EFI_STATUS
GenTestConfigContent (
  IN CHAR16                               *ProtocolGUIDString,
  IN BOOLEAN                              Value
);

//
// External functions implementation
//

EFI_STATUS
EFIAPI
PlatformSpecificElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  )
/*++

Routine Description:

  Check the platform specific elements, which defined in the EFI spec 2.3.1,
  section 2.6.2.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib;
  EFI_INI_FILE_HANDLE                 IniFile;
  EFI_INI_FILE_HANDLE                 ConfigINI;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL     *Volume;
  EFI_HANDLE                          DeviceHandle;
  EFI_FILE                            *Root;
  EFI_FILE                            *OldFile;
  CONFIG_ERROR_DATA                   *ErrorData;
  UINT32                              Index;
  BOOLEAN                             GenConfigINI;
  CHAR16                              String[MAX_LENGTH];
  CHAR16                              *FilePath;
  CHAR16                              *TitleString[] = {
    L"<|If fail item is not 0, it mean platform config  have error ___",
    L"<|occur or EfiCompliant.ini setting have wrong. ________________",
    L"<|Please sent this file and EfiCompliant.ini to platform owner .",
    L"<|EfiCompliant.ini is in the : SCT\\Dependency\\EfiCompliantBBTest",
    L"<|==============================================================",
    NULL
  };

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
  // Locate the test profile library protocol
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **)&ProfileLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  //  Check PlatformConfig.ini file is exise or not.
  //
  ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &DevicePath,
                         &FilePath
                       );
  Status = OpenIniFile (
             ProfileLib,
             L"Report",
             L"PlatformConfig.ini",
             &ConfigINI
           );
  if (ConfigINI != NULL) {
    //
    // If file exise, delete it.
    //
    CloseIniFile (ProfileLib, ConfigINI);

    Status = gtBS->LocateDevicePath (
                     &gEfiSimpleFileSystemProtocolGuid,
                     &DevicePath,
                     &DeviceHandle
                   );
    if (EFI_ERROR (Status)) {
      return Status;
    }

     Status = gtBS->HandleProtocol (
                      DeviceHandle,
                      &gEfiSimpleFileSystemProtocolGuid,
                      (VOID*)&Volume
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = Volume->OpenVolume(Volume, &Root);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = Root->Open (
                     Root,
                     &OldFile,
                     SctPoolPrint (L"%s\\Report\\PlatformConfig.ini", FilePath),
                     EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                     0
                   );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = OldFile->Delete (OldFile);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Root->Close (Root);
  }

  //
  // Open the INI file
  //
  Status = OpenIniFile (
             ProfileLib,
             EFI_COMPLIANT_BB_TEST_INI_PATH,
             EFI_COMPLIANT_BB_TEST_INI_FILE,
             &IniFile
             );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UEFI Compliant - Cannot open INI file",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  GenConfigINI = FALSE;
  Index = MAX_LENGTH;
  Status = IniFile->GetString (
                      IniFile,
                      SECTION_NAME_CONFIGURATION_SPECIFIC,
                      L"GEN_CONFIG_INI_FILE_ON",
                      String,
                      &Index
                    );
  if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
    GenConfigINI = TRUE;
  }

  if (GenConfigINI == TRUE) {
    //
    // Create the config.ini file.
    //
    ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &DevicePath,
                         &FilePath
                       );

    Status = ProfileLib->EfiIniCreate (
                           ProfileLib,
                           DevicePath,
                           SctPoolPrint (L"%s\\Report\\PlatformConfig.ini", FilePath),
                           &ConfigINI
                         );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"UEFI Compliant - Cannot create or open INI file",
                     L"%a:%d:",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      return Status;
    }
    //
    //  Gen PlatformConfig.ini title and description.
    //
    ConfigINI->SetStringByOrder (
                    ConfigINI,
                    0x00,
                    CONFIN_TITLE_STRING,
                    L"<|Unavailable (Fail) item have :",
                    SctPoolPrint (L":   \"%02d\"   --", 0x00)
                  );
    for (Index=0; TitleString[Index] != NULL ;Index++) {
      ConfigINI->SetString (
                   ConfigINI,
                   CONFIN_TITLE_STRING,
                   TitleString[Index],
                   L"|>"
                 );
    }
    ConstructionAndAcquisition (NULL, ConfigINI);
  }

  //
  // Check the console protocols
  //
  CheckConsoleProtocols (StandardLib, IniFile);

  //
  // Check the Hii protocols
  //
  CheckHiiProtocols (StandardLib, IniFile);

  //
  // Check the graphical console protocols
  //
  CheckGraphicalConsoleProtocols (StandardLib, IniFile);

    //
  // Check the pointer protocols
  //
  CheckPointerProtocol (StandardLib, IniFile);

  //
  // Check the boot from disk protocols
  //
  CheckBootFromDiskProtocols (StandardLib, IniFile);

  //
  // Check the boot from network protocols
  //
  CheckBootFromNetworkProtocols (StandardLib, IniFile);  

  //
  // Check the general network application
  //
  CheckUefiNetworkApplication (StandardLib, IniFile);

  //
  // Check the general V6 network application
  //  
  CheckUefiV6NetworkApplication (StandardLib, IniFile);

  //
  // Check the UART support protocols
  //
  CheckUartProtocol (StandardLib, IniFile);

  //
  // Check the PCI support protocols
  //
  CheckPciProtocols (StandardLib, IniFile);

  //
  // Check the USB support protocols
  //
  CheckUsbProtocols (StandardLib, IniFile);

  //
  // Check the NVMe support protocols
  //
  CheckNVMeProtocol (StandardLib, IniFile);

  //
  // Check the boot from NVMe protocols
  //
  CheckBootFromNVMe (StandardLib, IniFile);

  //
  // Check the SCSI support protocols
  //
  CheckScsiProtocols (StandardLib, IniFile);

  //
  // Check Boot from scsi peripheral
  //
  CheckBootFromScsi (StandardLib, IniFile);

  //
  // Check Boot from Iscsi peripheral
  //
  CheckBootFromIScsi (StandardLib, IniFile);

  //
  // Check the Debug support protocols
  //
  CheckDebugProtocols (StandardLib, IniFile);

  //
  // Check the driver override protocols
  //
  CheckDriverOverrideProtocol (StandardLib, IniFile);

  //
  // Check the ATA support protocols
  //
  CheckATAProtocol (StandardLib, IniFile);

  //
  // Check the EBC Interpreter
  //
  CheckEbcProtocol (StandardLib, IniFile);

  //
  // Check the DNS4 protocols
  //
  CheckDNS4Protocols (StandardLib, IniFile);

  //
  // Check the DNS6 protocols
  //
  CheckDNS6Protocols (StandardLib, IniFile);

  //
  // Check the TLS protocols
  //
  CheckTLSProtocols (StandardLib, IniFile);

  //
  // Check the HTTP protocols
  //
  CheckHTTPProtocols (StandardLib, IniFile);

  //
  // Check the EAP protocols
  //
  CheckEAPProtocols (StandardLib, IniFile);

  //
  // Check the BlueTooth protocols
  //
  CheckBlueToothClassicProtocols (StandardLib, IniFile);
  CheckBlueToothLEProtocols (StandardLib, IniFile);

  //
  // Check the IPSec protocols
  //
  CheckIPSecProtocols (StandardLib, IniFile);

  //
  // Close the INI file
  //
  CloseIniFile (ProfileLib, IniFile);

  //
  // Save data to platform.ini
  //
  if (GenConfigINI == TRUE) {
    ErrorData = ConstructionAndAcquisition (L"END", ConfigINI);
    //
    //  Update fail count.
    //
    ConfigINI->SetStringByOrder (
                    ConfigINI,
                    0x00,
                    L"|=================  Configuration Environment  =================|",
                    L"<|Unavailable (Fail) item have :",
                    SctPoolPrint (L":   \"%02d\"   --", ErrorData->ErrorCount)
                  );
    //
    // If have error occor and GenTestINI flag is on, gen the report file.
    //
    CloseIniFile (ProfileLib, ConfigINI);
  }
  return EFI_SUCCESS;
}

//
// Internal functions implementation
//

EFI_TEST_ASSERTION
NeedOneOrWarning (
  IN BOOLEAN                      ValueA
  )
{
  if (ValueA) {
    return EFI_TEST_ASSERTION_PASSED;
  } else {
    return EFI_TEST_ASSERTION_WARNING;
  }
}

EFI_TEST_ASSERTION
NeedTwoOrWarning (
  IN BOOLEAN                      ValueA,
  IN BOOLEAN                      ValueB
  )
{
  if (ValueA && ValueB) {
    //
    // Both are true
    //
    return EFI_TEST_ASSERTION_PASSED;
  }

  if (!ValueA && !ValueB) {
    //
    // Both are false
    //
    return EFI_TEST_ASSERTION_WARNING;
  }

  //
  // In different states
  //
  return EFI_TEST_ASSERTION_FAILED;
}

EFI_TEST_ASSERTION
NeedThreeOrWarning (
  IN BOOLEAN                      ValueA,
  IN BOOLEAN                      ValueB,
  IN BOOLEAN                      ValueC
  )
{
  if (ValueA && ValueB && ValueC) {
    //
    // All are true
    //
    return EFI_TEST_ASSERTION_PASSED;
  }

  if (!ValueA && !ValueB && !ValueC) {
    //
    // All are false
    //
    return EFI_TEST_ASSERTION_WARNING;
  }

  //
  // In different states
  //
  return EFI_TEST_ASSERTION_FAILED;
}

EFI_TEST_ASSERTION
NeedFourOrWarning (
  IN BOOLEAN                      ValueA,
  IN BOOLEAN                      ValueB,
  IN BOOLEAN                      ValueC,
  IN BOOLEAN                      ValueD
  )
{
  if (ValueA && ValueB && ValueC && ValueD) {
    //
    // All are true
    //
    return EFI_TEST_ASSERTION_PASSED;
  }

  if (!ValueA && !ValueB && !ValueC && !ValueD) {
    //
    // All are false
    //
    return EFI_TEST_ASSERTION_WARNING;
  }

  //
  // In different states
  //
  return EFI_TEST_ASSERTION_FAILED;
}

EFI_TEST_ASSERTION
NeedOrWarning (
  IN UINTN                        ValueCount,
  IN BOOLEAN                      *Value
  )
{
  UINTN       Index;
  BOOLEAN     Pass;
  BOOLEAN     Warn;
  
  Pass = TRUE;
  Warn = TRUE;
  
  for (Index = 0; Index < ValueCount; Index ++) {
    Pass = Pass && (*(Value + Index));
    Warn = Warn && (!(*(Value + Index)));
  } 
  
  if (Pass) {
    //
    // All are true
    //
    return EFI_TEST_ASSERTION_PASSED;
  }

  if (Warn) {
    //
    // All are false
    //
    return EFI_TEST_ASSERTION_WARNING;
  }

  //
  // In different states
  //
  return EFI_TEST_ASSERTION_FAILED;
}

EFI_STATUS
CheckConsoleProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the SIMPLE_INPUT protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimpleTextInProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the SIMPLE_TEXT_OUTPUT protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimpleTextOutProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  //
  // Check the SIMPLE_TEXT_INPUT_EX protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimpleTextInputExProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  AssertionType = NeedThreeOrWarning (ValueA, ValueB, ValueC);
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"ConsoleDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"ConsoleDevices")) {
        GenTestConfigContent (L"gEfiSimpleTextInProtocolGuid     ", ValueA);
        GenTestConfigContent (L"gEfiSimpleTextOutProtocolGuid    ", ValueB);
        GenTestConfigContent (L"gEfiSimpleTextInputExProtocolGuid", ValueC);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid001,
                 L"UEFI Compliant - Console protocols must be implemented",
                 L"%a:%d:Text Input - %s, Text Output - %s, Text InputEx - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No",
                 ValueC ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckHiiProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  UINTN               Index;
  EFI_GUID            Guid[5];
  BOOLEAN             Value[5];
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  Guid[0] =     gEfiHiiDatabaseProtocolGuid;
  Guid[1] =     gEfiHiiStringProtocolGuid;
  Guid[2] =     gEfiHiiConfigRoutingProtocolGuid;
  Guid[3] =     gEfiHiiConfigAccessProtocolGuid;
  Guid[4] =     gEfiHiiFontProtocolGuid;

  for (Index = 0; Index < 5; Index ++) { 
    Status = gtBS->LocateProtocol (
                     &Guid[Index],
                     NULL,
                     (VOID **) &Interface
                   );
    if (!EFI_ERROR (Status)) {
      Value[Index] = TRUE;
    } else {
      Value[Index] = FALSE;
    }
  }

  AssertionType = NeedOrWarning (4, Value);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"HiiConfigSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"HiiConfigSupport")) {
        GenTestConfigContent (L"gEfiHiiDatabaseProtocolGuid     ", Value[0]);
        GenTestConfigContent (L"gEfiHiiStringProtocolGuid       ", Value[1]);
        GenTestConfigContent (L"gEfiHiiConfigRoutingProtocolGuid", Value[2]);
        GenTestConfigContent (L"gEfiHiiFontProtocolGuid         ", Value[3]);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid017,
                 L"UEFI Compliant - Hii protocols must be implemented",
                 L"%a:%d:HiiDatabase - %s, HiiString - %s, HiiConfigRouting - %s, HiiConfigAccess - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Value[0] ? L"Yes" : L"No",
                 Value[1] ? L"Yes" : L"No",
                 Value[2] ? L"Yes" : L"No",
                 Value[3] ? L"Yes" : L"No"
                 );

  //
  // To check the gEfiHiiFontProtocolGuid
  //
  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    AssertionType = NeedOneOrWarning (Value[4]);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL )) {
      MaxLength = MAX_LENGTH;
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"HiiFontSupport",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"HiiFontSupport")) {
          GenTestConfigContent (L"gEfiHiiFontProtocolGuid", Value[4]);
        }
      }
    }

    //
    // Record test result
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid017,
                   L"UEFI Compliant - Hii protocols must be implemented",
                   L"%a:%d:HiiFont - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Value[4] ? L"Yes" : L"No"
                 );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
CheckGraphicalConsoleProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the GOP protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiGraphicsOutputProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the EDID Discovered protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiEdidDiscoveredProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  //
  // Check the EDID Active protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiEdidActiveProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  AssertionType = NeedThreeOrWarning (ValueA, ValueB, ValueC);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"GraphicalConsoleDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"GraphicalConsoleDevices")) {
        GenTestConfigContent (L"gEfiGraphicsOutputProtocolGuid", ValueA);
        GenTestConfigContent (L"gEfiEdidDiscoveredProtocolGuid", ValueB);
        GenTestConfigContent (L"gEfiEdidActiveProtocolGuid    ", ValueC);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid002,
                 L"UEFI Compliant - Graphic Console Device",
                 L"%a:%d:GOP - %s, EDID Discovered - %s, EDID Active - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No",
                 ValueC ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckPointerProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the SIMPLE_POINTER protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimplePointerProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  AssertionType = NeedOneOrWarning (ValueA);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"PointerDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"PointerDevices")) {
        GenTestConfigContent (L"gEfiSimplePointerProtocolGuid", ValueA);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid003,
                 L"UEFI Compliant - Pointer protocols must be implemented",
                 L"%a:%d:Pointer - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckBootFromDiskProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  BOOLEAN             ValueD;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the BLOCK_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiBlockIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the DISK_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiDiskIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  //
  // Check the SIMPLE_FILE_SYSTEM protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimpleFileSystemProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  //
  // Check the UNICODE_COLLATION protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiUnicodeCollation2ProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueD = TRUE;
  } else {
    ValueD = FALSE;
  }

  AssertionType = NeedFourOrWarning (ValueA, ValueB, ValueC, ValueD);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromDiskDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"BootFromDiskDevices")) {
        GenTestConfigContent (L"gEfiBlockIoProtocolGuid         ", ValueA);
        GenTestConfigContent (L"gEfiDiskIoProtocolGuid          ", ValueB);
        GenTestConfigContent (L"gEfiSimpleFileSystemProtocolGuid", ValueC);
        GenTestConfigContent (L"gEfiUnicodeCollationProtocolGuid", ValueD);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid004,
                 L"UEFI Compliant - Boot from disk protocols must be implemented",
                 L"%a:%d:Block IO - %s, Disk IO - %s, Simple FS - %s, Unicode Collation - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No",
                 ValueC ? L"Yes" : L"No",
                 ValueD ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckBootFromNetworkProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             Value[3];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;
  UINTN               DataSize;
  UINT8               Data;

  //
  // Check the PXE_BASE_CODE protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiPxeBaseCodeProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the SIMPLE_NETWORK protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimpleNetworkProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    Value[0] = TRUE;
  } else {
    Value[0] = FALSE;
  }

  //
  // Check the MANAGED_NETWORK_PROTOCOL
  //
  Status = gtBS->LocateProtocol (
                   &gEfiManagedNetworkProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    Value[1] = TRUE;
  } else {
    Value[1] = FALSE;
  }

  //
  // Check the EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL
  //
  Status = gtBS->LocateProtocol (
                   &gEfiNetworkInterfaceIdentifierProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    Value[2] = TRUE;
  } else {
    Value[2] = FALSE;
  }

  if (Value[0] == TRUE || Value[1] == TRUE || Value[2] == TRUE){
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  //
  // Check the SetupMode variable value
  //
  DataSize = 1;   
  Status = gtRT->GetVariable (
                   L"SetupMode",
                   &gGlobalVariableGuid,
                   NULL,
                   &DataSize,
                   &Data
                   );
  
  if ((!EFI_ERROR (Status)) && (Data == 0)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromNetworkDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"BootFromNetworkDevices")) {
        GenTestConfigContent (L"gEfiPxeBaseCodeProtocolGuid               ", ValueA);
        GenTestConfigContent (L"gEfiSimpleNetworkProtocolGuid             ", Value[0]);
        GenTestConfigContent (L"gEfiManagedNetworkProtocolGuid            ", Value[1]);
        GenTestConfigContent (L"gEfiNetworkInterfaceIdentifierProtocolGuid", Value[2]);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid005,
                 L"UEFI Compliant - Boot from network protocols must be implemented",
                 L"%a:%d:PXE BC - %s, SNP - %s, MNP - %s, UNDI - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 Value[0] ? L"Yes" : L"No",
                 Value[1] ? L"Yes" : L"No",
                 Value[2] ? L"Yes" : L"No"
                 );

  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    AssertionType = NeedOneOrWarning (ValueC);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"ValidateBootImageThruNet",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"ValidateBootImageThruNet")) {
          GenTestConfigContent (L"Variable \"SetupMode\"", ValueC);
        }
      }
    }

    //
    // Record test result
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid005,
                   L"UEFI Compliant - Validating a boot image received through a network device must be implemented",
                   L"%a:%d:SetupMode equal zero - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueC ? L"Yes" : L"No"
                 );

  }

  return EFI_SUCCESS;
}


EFI_STATUS
CheckUefiNetworkApplication (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{

  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  UINTN               Index;
  EFI_GUID            Guid[15];
  BOOLEAN             Value[15];
  VOID                *Interface;
  EFI_SERVICE_BINDING_PROTOCOL    *TempInterface;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_HANDLE          ChildHandle = NULL;
  
  Guid[0] =     gEfiManagedNetworkServiceBindingProtocolGuid;
  Guid[1] =     gEfiArpServiceBindingProtocolGuid;
  Guid[2] =     gEfiIp4ServiceBindingProtocolGuid;
  Guid[3] =     gEfiDhcp4ServiceBindingProtocolGuid;
  Guid[4] =     gEfiTcp4ServiceBindingProtocolGuid;
  Guid[5] =     gEfiUdp4ServiceBindingProtocolGuid;
  Guid[6] =     gEfiIp4Config2ProtocolGuid;

  Guid[7] =     gEfiManagedNetworkProtocolGuid;
  Guid[8] =     gEfiArpProtocolGuid;
  Guid[9] =     gEfiIp4ProtocolGuid;
  Guid[10] =    gEfiDhcp4ProtocolGuid;
  Guid[11] =    gEfiTcp4ProtocolGuid;
  Guid[12] =    gEfiUdp4ProtocolGuid;

  for (Index = 0; Index < 7; Index ++) { 
    Status = gtBS->LocateProtocol (
                     &Guid[Index],
                     NULL,
                     (VOID **) &Interface
                   );
    if (!EFI_ERROR (Status)) {
      Value[Index] = TRUE;
    } else {
      Value[Index] = FALSE;
    }
  }
  
  AssertionType = NeedOrWarning (7, Value);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"UefiNetworkApplication",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"UefiNetworkApplication")) {
        GenTestConfigContent (L"gEfiManagedNetworkServiceBindingProtocolGuid", Value[0]);
        GenTestConfigContent (L"gEfiArpServiceBindingProtocolGuid           ", Value[1]);
        GenTestConfigContent (L"gEfiIp4ServiceBindingProtocolGuid           ", Value[2]);
        GenTestConfigContent (L"gEfiDhcp4ServiceBindingProtocolGuid         ", Value[3]);
        GenTestConfigContent (L"gEfiTcp4ServiceBindingProtocolGuid          ", Value[4]);
        GenTestConfigContent (L"gEfiUdp4ServiceBindingProtocolGuid          ", Value[5]);
        GenTestConfigContent (L"gEfiIp4Config2ProtocolGuid                  ", Value[6]);
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid012,
                   L"UEFI Compliant - UEFI General Network Application required",
                   L"%a:%d:MnpSB-%s, ArpSB-%s, Ip4SB-%s, Dhcp4SB-%s, Tcp4SB-%s, Udp4SB-%s, Ip4Config2-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Value[0] ? L"Y" : L"N",
                   Value[1] ? L"Y" : L"N",
                   Value[2] ? L"Y" : L"N",
                   Value[3] ? L"Y" : L"N",
                   Value[4] ? L"Y" : L"N",
                   Value[5] ? L"Y" : L"N",
                   Value[6] ? L"Y" : L"N"
                   );

  }  else {
    for (Index = 0; Index < 6; Index ++) {
      Status = gtBS->LocateProtocol (
                       &Guid[Index],
                       NULL,
                       (VOID **)&TempInterface
                       );
      switch (Index) {
        case 0:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        case 1:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        case 2:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        case 3:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        case 4:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        default:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
      }
   
      Status = gtBS->LocateProtocol (
                       &Guid[Index+7],
                       NULL,
                       (VOID **)&Interface
                       );
      if (!EFI_ERROR (Status)) {
        Value[Index+7] = TRUE;
      } else {
        Value[Index+7] = FALSE;
      }
   
      switch (Index) {
        case 0:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        case 1:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        case 2:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        case 3:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        case 4:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        default:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
      }
    } 

    AssertionType = NeedOrWarning (13, Value);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }

    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"UefiNetworkApplication",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"UefiNetworkApplication")) {
          GenTestConfigContent (L"gEfiManagedNetworkServiceBindingProtocolGuid", Value[0]);
          GenTestConfigContent (L"gEfiArpServiceBindingProtocolGuid           ", Value[1]);
          GenTestConfigContent (L"gEfiIp4ServiceBindingProtocolGuid           ", Value[2]);
          GenTestConfigContent (L"gEfiDhcp4ServiceBindingProtocolGuid         ", Value[3]);
          GenTestConfigContent (L"gEfiTcp4ServiceBindingProtocolGuid          ", Value[4]);
          GenTestConfigContent (L"gEfiUdp4ServiceBindingProtocolGuid          ", Value[5]);
          GenTestConfigContent (L"gEfiIp4Config2ProtocolGuid                  ", Value[6]);
          GenTestConfigContent (L"gEfiManagedNetworkProtocolGuid              ", Value[7]);
          GenTestConfigContent (L"gEfiArpProtocolGuid                         ", Value[8]);
          GenTestConfigContent (L"gEfiIp4ProtocolGuid                         ", Value[9]);
          GenTestConfigContent (L"gEfiDhcp4ProtocolGuid                       ", Value[10]);
          GenTestConfigContent (L"gEfiTcp4ProtocolGuid                        ", Value[11]);
          GenTestConfigContent (L"gEfiUdp4ProtocolGuid                        ", Value[12]);
        }
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid012,
                   L"UEFI Compliant-UEFI General Network Application required",
                   L"%a:%d:MnpSB-%s,ArpSB-%s,Ip4SB-%s,Dhcp4SB-%s,Tcp4SB-%s,Udp4SB-%s,Ip4Config2-%s,"
                   L"Mnp-%s,Arp-%s,Ip4-%s,Dhcp4-%s,Tcp4-%s,Udp4-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Value[0] ? L"Y" : L"N",
                   Value[1] ? L"Y" : L"N",
                   Value[2] ? L"Y" : L"N",
                   Value[3] ? L"Y" : L"N",
                   Value[4] ? L"Y" : L"N",
                   Value[5] ? L"Y" : L"N",
                   Value[6] ? L"Y" : L"N",
                   Value[7] ? L"Y" : L"N",
                   Value[8] ? L"Y" : L"N",
                   Value[9] ? L"Y" : L"N",
                   Value[10] ? L"Y" : L"N",
                   Value[11] ? L"Y" : L"N",
                   Value[12] ? L"Y" : L"N"
                   );
    
  }

  return EFI_SUCCESS;
}

EFI_STATUS
CheckUefiV6NetworkApplication (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{

  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  UINTN               Index;
  EFI_GUID            Guid[15];
  BOOLEAN             Value[15];
  VOID                *Interface;
  EFI_SERVICE_BINDING_PROTOCOL    *TempInterface;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_HANDLE          ChildHandle = NULL;
  
  Guid[0] =     gEfiDhcp6ServiceBindingProtocolGuid;
  Guid[1] =     gEfiTcp6ServiceBindingProtocolGuid;
  Guid[2] =     gEfiIp6ServiceBindingProtocolGuid;
  Guid[3] =     gEfiUdp6ServiceBindingProtocolGuid;
  Guid[4] =     gEfiIp6ConfigProtocolGuid;

  Guid[5] =     gEfiDhcp6ProtocolGuid;
  Guid[6] =     gEfiTcp6ProtocolGuid;
  Guid[7] =     gEfiIp6ProtocolGuid;
  Guid[8] =     gEfiUdp6ProtocolGuid;

  Guid[9] =     gEfiVlanConfigProtocolGuid;

  for (Index = 0; Index < 5; Index ++) {
    Status = gtBS->LocateProtocol (
                     &Guid[Index],
                     NULL,
                     (VOID **) &Interface
                     );
    if (!EFI_ERROR (Status)) {
      Value[Index] = TRUE;
    } else {
      Value[Index] = FALSE;
    }
  }
  
  AssertionType = NeedOrWarning (5, Value);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"UEFIIPv6Support",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"UEFIIPv6Support")) {
        GenTestConfigContent (L"gEfiDhcp6ServiceBindingProtocolGuid", Value[0]);
        GenTestConfigContent (L"gEfiTcp6ServiceBindingProtocolGuid ", Value[1]);
        GenTestConfigContent (L"gEfiIp6ServiceBindingProtocolGuid  ", Value[2]);
        GenTestConfigContent (L"gEfiUdp6ServiceBindingProtocolGuid ", Value[3]);
        GenTestConfigContent (L"gEfiIp6ConfigProtocolGuid          ", Value[4]);
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid015,
                   L"UEFI Compliant - UEFI V6 General Network Application required",
                   L"%a:%d:Dhcp6SB-%s, Tcp6SB-%s, Ip6SB-%s, Udp6SB-%s, Ip6Config-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Value[0] ? L"Y" : L"N",
                   Value[1] ? L"Y" : L"N",
                   Value[2] ? L"Y" : L"N",
                   Value[3] ? L"Y" : L"N",
                   Value[4] ? L"Y" : L"N"
                   );

  } else {
    for (Index = 0; Index < 4; Index ++) {
      Status = gtBS->LocateProtocol (
                       &Guid[Index],
                       NULL,
                       (VOID **) &TempInterface
                       );
      switch (Index) {
        case 0:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        case 1:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        case 2:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        case 3:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
          break;
        default:
          TempInterface->CreateChild(TempInterface, &ChildHandle);
      }

      Status = gtBS->LocateProtocol (
                       &Guid[Index+5],
                       NULL,
                       (VOID **) &Interface
                       );
      if (!EFI_ERROR (Status)) {
        Value[Index+5] = TRUE;
      } else {
        Value[Index+5] = FALSE;
      }
      
      switch (Index) {
        case 0:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        case 1:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        case 2:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        case 3:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
          break;
        default:
          TempInterface->DestroyChild(TempInterface, ChildHandle);
          ChildHandle = NULL;
      }
    } 

    AssertionType = NeedOrWarning (9, Value);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    //
    // If warning, check with INI file to decide they must exist or not
    //
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"UEFIIPv6Support",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"UEFIIPv6Support")) {
          GenTestConfigContent (L"gEfiDhcp6ServiceBindingProtocolGuid", Value[0]);
          GenTestConfigContent (L"gEfiTcp6ServiceBindingProtocolGuid ", Value[1]);
          GenTestConfigContent (L"gEfiIp6ServiceBindingProtocolGuid  ", Value[2]);
          GenTestConfigContent (L"gEfiUdp6ServiceBindingProtocolGuid ", Value[3]);
          GenTestConfigContent (L"gEfiIp6ConfigProtocolGuid          ", Value[4]);
          GenTestConfigContent (L"gEfiDhcp6ProtocolGuid              ", Value[5]);
          GenTestConfigContent (L"gEfiTcp6ProtocolGuid               ", Value[6]);
          GenTestConfigContent (L"gEfiIp6ProtocolGuid                ", Value[7]);
          GenTestConfigContent (L"gEfiUdp6ProtocolGuid               ", Value[8]);
        }
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid015,
                   L"UEFI Compliant-UEFI V6 General Network Application required",
                   L"%a:%d:Dhcp6SB-%s, Tcp6SB-%s, Ip6SB-%s, Udp6SB-%s, Ip6Config-%s,"
                   L"Dhcp6-%s,Tcp6-%s,Ip6-%s,Udp6-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Value[0] ? L"Y" : L"N",
                   Value[1] ? L"Y" : L"N",
                   Value[2] ? L"Y" : L"N",
                   Value[3] ? L"Y" : L"N",
                   Value[4] ? L"Y" : L"N",
                   Value[5] ? L"Y" : L"N",
                   Value[6] ? L"Y" : L"N",
                   Value[7] ? L"Y" : L"N",
                   Value[8] ? L"Y" : L"N"
                   );
    
    if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
      Status = gtBS->LocateProtocol (
                       &Guid[9],
                       NULL,
                       (VOID **) &Interface
                       );
      if (!EFI_ERROR (Status)) {
        Value[9] = TRUE;
      } else {
        Value[9] = FALSE;
      }

      AssertionType = NeedOneOrWarning (Value[9]);

      if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }
      
      //
      // If warning, check with INI file to decide they must exist or not
      //
      if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL )) {
        MaxLength = MAX_LENGTH;

        Status = IniFile->GetString (
                            IniFile,
                            SECTION_NAME_PLATFORM_SPECIFIC,
                            L"VlanSupport",
                            String,
                            &MaxLength
                            );
        if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          if (!GenTestConfigTitle (IniFile, &AssertionType, L"VlanSupport")) {
            GenTestConfigContent (L"gEfiVlanConfigProtocolGuid", Value[9]);
          }
        }
      }

      //
      // Record test result
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiCompliantBbTestPlatformAssertionGuid011,
                     L"UEFI Compliant - VLAN protocols must be implemented",
                     L"%a:%d:VLAN - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Value[9] ? L"Yes" : L"No"
                     );
      
    }
  }

  return EFI_SUCCESS;
}


EFI_STATUS
CheckUartProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the SERIAL_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSerialIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  AssertionType = NeedOneOrWarning (ValueA);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"UartDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"UartDevices")) {
        GenTestConfigContent (L"gEfiSerialIoProtocolGuid", ValueA);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid006,
                 L"UEFI Compliant - UART protocols must be implemented",
                 L"%a:%d:Serial IO - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckPciProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the PCI_ROOT_BRIDGE_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiPciRootBridgeIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the PCI_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiPciIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"PciBusSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"PciBusSupport")) {
        GenTestConfigContent (L"gEfiPciRootBridgeIoProtocolGuid", ValueA);
        GenTestConfigContent (L"gEfiPciIoProtocolGuid          ", ValueB);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid007,
                 L"UEFI Compliant - PCI Bus support protocols must be implemented",
                 L"%a:%d:PCI Root Bridge - %s, PCI IO - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckUsbProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the USB_HC2 protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiUsb2HcProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the USB_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiUsbIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"UsbBusSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"UsbBusSupport")) {
        GenTestConfigContent (L"gEfiUsb2HcProtocolGuid", ValueA);
        GenTestConfigContent (L"gEfiUsbIoProtocolGuid ", ValueB);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid008,
                 L"UEFI Compliant - USB Bus support protocols must be implemented",
                 L"%a:%d:USB HC - %s, USB IO - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckNVMeProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the NVM Express Pass Thru protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiNvmExpressPassThruProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  AssertionType = NeedOneOrWarning (ValueA);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"NVMExpressPassThru",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"NVMExpressPassThru")) {
        GenTestConfigContent (L"gEfiNvmExpressPassThruProtocolGuid", ValueA);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid018,
                 L"UEFI Compliant - NVM Express Pass Thru protocol must be implemented",
                 L"%a:%d:NVM Express Pass Thru protocol - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckBootFromNVMe (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the NVME Pass Thru protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiNvmExpressPassThruProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the BLOCK_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiBlockIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  AssertionType = NeedOneOrWarning (ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromNVMe",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"BootFromNVMe")) {
        GenTestConfigContent (L"gEfiBlockIoProtocolGuid", ValueB);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid019,
                 L"UEFI Compliant - Boot from block-oriented NVMe peripheral",
                 L"%a:%d:Block IO - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueB ? L"Yes" : L"No"
                 );

  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    AssertionType = NeedOneOrWarning (ValueA);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }

    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;

      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"NVMExpressPassThru",
                          String,
                          &MaxLength
                        );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"NVMExpressPassThru")) {
          GenTestConfigContent (L"gEfiNvmExpressPassThruProtocolGuid", ValueA);
        }
      }
    }

    //
    // Record test result
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid019,
                   L"UEFI Compliant - Boot from block-oriented NVMe peripheral",
                   L"%a:%d:NVMExpressPassThru - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Yes" : L"No"
                   );
  }


  return EFI_SUCCESS;
}



EFI_STATUS
CheckScsiProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the Extended SCSI_PASS_THRU protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiExtScsiPassThruProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  AssertionType = NeedOneOrWarning (ValueA);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"ExtScsiPassThru",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"ExtScsiPassThru")) {
        GenTestConfigContent (L"gEfiExtScsiPassThruProtocolGuid", ValueA);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid009,
                 L"UEFI Compliant - Ext SCSI Pass Thru protocol must be implemented",
                 L"%a:%d:Ext SCSI Pass Thru - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckBootFromScsi (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the Extended SCSI_PASS_THRU protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiExtScsiPassThruProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the SCSI_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiScsiIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  //
  // Check the BLOCK_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiBlockIoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  AssertionType = NeedTwoOrWarning (ValueB, ValueC);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromScsi",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"BootFromScsi")) {
        GenTestConfigContent (L"gEfiBlockIoProtocolGuid", ValueB);
        GenTestConfigContent (L"gEfiScsiIoProtocolGuid ", ValueC);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid013,
                 L"UEFI Compliant - Boot from SCSI peripheral",
                 L"%a:%d:SCSI IO - %s, Block IO - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueC ? L"Yes" : L"No", 
                 ValueB ? L"Yes" : L"No"
                 );

  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    AssertionType = NeedOneOrWarning (ValueA);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }

    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;

      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"ExtScsiPassThruSupport",
                          String,
                          &MaxLength
                        );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"ExtScsiPassThruSupport")) {
          GenTestConfigContent (L"gEfiExtScsiPassThruProtocolGuid", ValueA);
        }
      }
    }

    //
    // Record test result
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid013,
                   L"UEFI Compliant - Boot from SCSI peripheral",
                   L"%a:%d:Ext SCSI Pass Thru - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Yes" : L"No"
                   );
  }


  return EFI_SUCCESS;
}

EFI_STATUS
CheckBootFromIScsi (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;  
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the EFI_ISCSI_INITIATOR_NAME_PROTOCOL
  //
  Status = gtBS->LocateProtocol (
                   &gEfiIScsiInitiatorNameProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the EFI_AUTHENTICATION_INFO_PROTOCOL
  //
  Status = gtBS->LocateProtocol (
                   &gEfiAuthenticationInfoProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromIscsi",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"BootFromIscsi")) {
        GenTestConfigContent (L"gEfiIScsiInitiatorNameProtocolGuid", ValueA);
        GenTestConfigContent (L"gEfiAuthenticationInfoProtocolGuid", ValueB);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid014,
                 L"UEFI Compliant - Boot from iSCSI peripheral",
                 L"%a:%d: Iscsi Initiator Name - %s, Authentication Info - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No"
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
CheckDebugProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the DEBUG_SUPPORT protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiDebugSupportProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the DEBUG_PORT protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiDebugPortProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"DebugSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"DebugSupport")) {
        GenTestConfigContent (L"gEfiDebugSupportProtocolGuid", ValueA);
        GenTestConfigContent (L"gEfiDebugPortProtocolGuid   ", ValueB);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid010,
                 L"UEFI Compliant - Debug support protocols must be implemented",
                 L"%a:%d:Debug Support - %s, Debug Port - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckDriverOverrideProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the DRIVER_OVERRIDE protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiPlatformDriverOverrideProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  AssertionType = NeedOneOrWarning (ValueA);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"PlatformDriverOverride",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"PlatformDriverOverride")) {
        GenTestConfigContent (L"gEfiPlatformDriverOverrideProtocolGuid", ValueA);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid011,
                 L"UEFI Compliant - Platform Driver Override protocols must be implemented",
                 L"%a:%d:Platform Driver Override - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckATAProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the DRIVER_OVERRIDE protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiAtaPassThruProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  AssertionType = NeedOneOrWarning (ValueA);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"AtaPassThru",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"AtaPassThru")) {
        GenTestConfigContent (L"gEfiAtaPassThruProtocolGuid", ValueA);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid020,
                 L"UEFI Compliant - Ata Pass Thru protocols must be implemented",
                 L"%a:%d:Ata Pass Thru - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckEbcProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  EFI_EBC_PROTOCOL    *Ebc;
  EFI_TEST_ASSERTION  AssertionType;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  CHAR16              *AssertString = NULL;               
  
  //
  // Check the EBC Interpreter protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiEbcProtocolGuid,
                   NULL,
                   (VOID **) &Ebc
                   );

  if (Status == EFI_SUCCESS)  {
    if((Ebc->CreateThunk        != NULL) &&
       (Ebc->UnloadImage        != NULL) &&
       (Ebc->RegisterICacheFlush!= NULL) &&
       (Ebc->GetVersion         != NULL)
       ) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"EBCSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  if (SctStriCmp (String, L"yes") == 0) {
    AssertString = L"UEFI Compliant - EBC Interpreter protocol must exist in this platform";
  } else {
    AssertString = L"UEFI Compliant - EBC Interpreter protocol is optional in this platform";
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid016,
                 AssertString,
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Record the entire EBC Interpreter protocol
  //
  if (Ebc != NULL) {
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

  return EFI_SUCCESS;
}





EFI_STATUS
CheckDNS4Protocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{

  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  VOID                *Interface;
  EFI_SERVICE_BINDING_PROTOCOL    *TempInterface;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_HANDLE          ChildHandle = NULL;
  

  Status = gtBS->LocateProtocol (
                   &gEfiDns4ServiceBindingProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }
  
  AssertionType = NeedOneOrWarning (ValueA);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"DNS4Support",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"DNS4Support")) {
        GenTestConfigContent (L"gEfiDns4ServiceBindingProtocolGuid", ValueA);
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid021,
                   L"UEFI Compliant - DNS4 support is required",
                   L"%a:%d:DNS4SB-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N"
                   );

  }  else {
    Status = gtBS->LocateProtocol (
                       &gEfiDns4ServiceBindingProtocolGuid,
                       NULL,
                       (VOID **) &TempInterface
                       );

    TempInterface->CreateChild(TempInterface, &ChildHandle);


    Status = gtBS->LocateProtocol (
                     &gEfiDns4ProtocolGuid,
                     NULL,
                     (VOID **) &Interface
                     );
    if (!EFI_ERROR (Status)) {
      ValueB = TRUE;
    } else {
      ValueB = FALSE;
    }

    TempInterface->DestroyChild(TempInterface, ChildHandle);
    ChildHandle = NULL;

    AssertionType = NeedOneOrWarning (ValueB);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    //
    // If warning, check with INI file to decide they must exist or not
    //
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"DNS4Support",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"DNS4Support")) {
          GenTestConfigContent (L"gEfiDns4ServiceBindingProtocolGuid", ValueA);
          GenTestConfigContent (L"gEfiDns4ProtocolGuid              ", ValueB);
        }
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid021,
                   L"UEFI Compliant - DNS4 support is required",
                   L"%a:%d:DNS4SB-%s, DNS4-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N",
                   ValueB ? L"Y" : L"N"
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
CheckDNS6Protocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{

  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  VOID                *Interface;
  EFI_SERVICE_BINDING_PROTOCOL    *TempInterface;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_HANDLE          ChildHandle = NULL;
  

  Status = gtBS->LocateProtocol (
                   &gEfiDns6ServiceBindingProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }
  
  AssertionType = NeedOneOrWarning (ValueA);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"DNS6Support",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"DNS6Support")) {
        GenTestConfigContent (L"gEfiDns6ServiceBindingProtocolGuid", ValueA);
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid022,
                   L"UEFI Compliant - DNS6 support is required",
                   L"%a:%d:DNS6SB-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N"
                   );

  }  else {
    Status = gtBS->LocateProtocol (
                       &gEfiDns6ServiceBindingProtocolGuid,
                       NULL,
                       (VOID **) &TempInterface
                       );

    TempInterface->CreateChild(TempInterface, &ChildHandle);


    Status = gtBS->LocateProtocol (
                     &gEfiDns6ProtocolGuid,
                     NULL,
                     (VOID **) &Interface
                     );
    if (!EFI_ERROR (Status)) {
      ValueB = TRUE;
    } else {
      ValueB = FALSE;
    }

    TempInterface->DestroyChild(TempInterface, ChildHandle);
    ChildHandle = NULL;

    AssertionType = NeedOneOrWarning (ValueB);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    //
    // If warning, check with INI file to decide they must exist or not
    //
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"DNS6Support",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"DNS6Support")) {
          GenTestConfigContent (L"gEfiDns6ServiceBindingProtocolGuid", ValueA);
          GenTestConfigContent (L"gEfiDns6ProtocolGuid              ", ValueB);
        }
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid022,
                   L"UEFI Compliant - DNS6 support is required",
                   L"%a:%d:DNS6SB-%s, DNS6-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N",
                   ValueB ? L"Y" : L"N"
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
CheckTLSProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{

  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_SERVICE_BINDING_PROTOCOL    *TempInterface;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_HANDLE          ChildHandle = NULL;
  

  Status = gtBS->LocateProtocol (
                   &gEfiTlsServiceBindingProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  Status = gtBS->LocateProtocol (
                   &gEfiTlsConfigurationProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }  
  
  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"TLSSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"TLSSupport")) {
        GenTestConfigContent (L"gEfiTlsServiceBindingProtocolGuid", ValueA);
        GenTestConfigContent (L"gEfiTlsConfigurationProtocolGuid ", ValueB);
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid023,
                   L"UEFI Compliant - TLS support is required",
                   L"%a:%d:TLSSB-%s, TLSConfig-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N",
                   ValueB ? L"Y" : L"N"
                   );

  }  else {
    Status = gtBS->LocateProtocol (
                       &gEfiTlsServiceBindingProtocolGuid,
                       NULL,
                       (VOID **) &TempInterface
                       );

    TempInterface->CreateChild(TempInterface, &ChildHandle);


    Status = gtBS->LocateProtocol (
                     &gEfiTlsProtocolGuid,
                     NULL,
                     (VOID **) &Interface
                     );
    if (!EFI_ERROR (Status)) {
      ValueC = TRUE;
    } else {
      ValueC = FALSE;
    }

    TempInterface->DestroyChild(TempInterface, ChildHandle);
    ChildHandle = NULL;

    AssertionType = NeedOneOrWarning (ValueC);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    //
    // If warning, check with INI file to decide they must exist or not
    //
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"TLSSupport",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"TLSSupport")) {
          GenTestConfigContent (L"gEfiTlsServiceBindingProtocolGuid", ValueA);
          GenTestConfigContent (L"gEfiTlsConfigurationProtocolGuid ", ValueB);
          GenTestConfigContent (L"gEfiTlsProtocolGuid              ", ValueC);
        }
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid023,
                   L"UEFI Compliant - TLS support is required",
                   L"%a:%d:TLSSB-%s, TLSConfig-%s, TLS-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N",
                   ValueB ? L"Y" : L"N",
                   ValueC ? L"Y" : L"N"
                   );
  }

  return EFI_SUCCESS;
}


EFI_STATUS
CheckHTTPProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{

  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_SERVICE_BINDING_PROTOCOL    *TempInterface;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_HANDLE          ChildHandle = NULL;
  

  Status = gtBS->LocateProtocol (
                   &gEfiHttpServiceBindingProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  Status = gtBS->LocateProtocol (
                   &gEfiHttpUtilitiesProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }  
  
  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"HTTPSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"HTTPSupport")) {
        GenTestConfigContent (L"gEfiHttpServiceBindingProtocolGuid", ValueA);
        GenTestConfigContent (L"gEfiHttpUtilitiesProtocolGuid     ", ValueB);
      }
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid024,
                   L"UEFI Compliant - HTTP support is required",
                   L"%a:%d:HTTPSB-%s, HTTP Utilities-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N",
                   ValueB ? L"Y" : L"N"
                   );

  }  else {
    Status = gtBS->LocateProtocol (
                       &gEfiHttpServiceBindingProtocolGuid,
                       NULL,
                       (VOID **) &TempInterface
                       );

    TempInterface->CreateChild(TempInterface, &ChildHandle);


    Status = gtBS->LocateProtocol (
                     &gEfiHttpProtocolGuid,
                     NULL,
                     (VOID **) &Interface
                     );
    if (!EFI_ERROR (Status)) {
      ValueC = TRUE;
    } else {
      ValueC = FALSE;
    }

    TempInterface->DestroyChild(TempInterface, ChildHandle);
    ChildHandle = NULL;

    AssertionType = NeedOneOrWarning (ValueC);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    //
    // If warning, check with INI file to decide they must exist or not
    //
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"HTTPSupport",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"HTTPSupport")) {
          GenTestConfigContent (L"gEfiHttpServiceBindingProtocolGuid", ValueA);
          GenTestConfigContent (L"gEfiHttpUtilitiesProtocolGuid     ", ValueB);
          GenTestConfigContent (L"gEfiHttpProtocolGuid              ", ValueC);
        }
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid024,
                   L"UEFI Compliant - HTTP support is required",
                   L"%a:%d:HTTPSB-%s, HTTP Utilities-%s, HTTP-%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N",
                   ValueB ? L"Y" : L"N",
                   ValueC ? L"Y" : L"N"
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
CheckEAPProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;  
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  Status = gtBS->LocateProtocol (
                   &gEfiEapProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  Status = gtBS->LocateProtocol (
                   &gEfiEapConfigProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  Status = gtBS->LocateProtocol (
                   &gEfiEapManagement2ProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }  

  AssertionType = NeedThreeOrWarning (ValueA, ValueB, ValueC);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"EAPSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"EAPSupport")) {
        GenTestConfigContent (L"gEfiEapProtocolGuid           ", ValueA);
        GenTestConfigContent (L"gEfiEapConfigProtocolGuid     ", ValueB);
        GenTestConfigContent (L"gEfiEapManagement2ProtocolGuid", ValueC);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid025,
                 L"UEFI Compliant - EAP Support protocols must be implemented",
                 L"%a:%d:EAP - %s, EAP Config - %s, EAP Management2 - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No",
                 ValueC ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
CheckBlueToothClassicProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  BOOLEAN             ValueD;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_SERVICE_BINDING_PROTOCOL    *TempInterface;
  EFI_HANDLE          ChildHandle = NULL;
    

  Status = gtBS->LocateProtocol (
                   &gEfiBlueToothHcProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  Status = gtBS->LocateProtocol (
                   &gEfiBlueToothServiceBindingProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  Status = gtBS->LocateProtocol (
                   &gEfiBlueToothConfigProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }  

  AssertionType = NeedThreeOrWarning (ValueA, ValueB, ValueC);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BlueToothClassicSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"BlueToothClassicSupport")) {
        GenTestConfigContent (L"gEfiBlueToothHcProtocolGuid            ", ValueA);
        GenTestConfigContent (L"gEfiBlueToothServiceBindingProtocolGuid", ValueB);
        GenTestConfigContent (L"gEfiBlueToothConfigProtocolGuid        ", ValueC);
      }
    }

    //
    // Record test result
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid026,
                   L"UEFI Compliant - BlueTooth Classic Support protocols must be implemented",
                   L"%a:%d:BLUETOOTH HC - %s, BLUETOOTH Service Binding - %s, BLUETOOTH Config - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Yes" : L"No",
                   ValueB ? L"Yes" : L"No",
                   ValueC ? L"Yes" : L"No"
                   );
  }

  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    Status = gtBS->LocateProtocol (
                       &gEfiBlueToothServiceBindingProtocolGuid,
                       NULL,
                       (VOID **) &TempInterface
                       );

    TempInterface->CreateChild(TempInterface, &ChildHandle);


    Status = gtBS->LocateProtocol (
                     &gEfiBlueToothIoProtocolGuid,
                     NULL,
                     (VOID **) &Interface
                     );
    if (!EFI_ERROR (Status)) {
      ValueD = TRUE;
    } else {
      ValueD = FALSE;
    }
    
    TempInterface->DestroyChild(TempInterface, ChildHandle);
    ChildHandle = NULL;

    AssertionType = NeedOneOrWarning (ValueD);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    //
    // If warning, check with INI file to decide they must exist or not
    //
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
      MaxLength = MAX_LENGTH;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"BlueToothClassicSupport",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        if (!GenTestConfigTitle (IniFile, &AssertionType, L"BlueToothClassicSupport")) {
          GenTestConfigContent (L"gEfiBlueToothHcProtocolGuid            ", ValueA);
          GenTestConfigContent (L"gEfiBlueToothServiceBindingProtocolGuid", ValueB);
          GenTestConfigContent (L"gEfiBlueToothConfigProtocolGuid        ", ValueC);
          GenTestConfigContent (L"gEfiBlueToothIoProtocolGuid            ", ValueD);
        }
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid026,
                   L"UEFI Compliant - BlueTooth Classic Support protocols must be implemented",
                   L"%a:%d:BLUETOOTH HC - %s, BLUETOOTH Service Binding - %s, BLUETOOTH Config - %s, BLUETOOTH IO - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Y" : L"N",
                   ValueB ? L"Y" : L"N",
                   ValueC ? L"Y" : L"N",
                   ValueD ? L"Y" : L"N"
                   );    

  }

  return EFI_SUCCESS;
}

EFI_STATUS
CheckBlueToothLEProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  Status = gtBS->LocateProtocol (
                   &gEfiBlueToothHcProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  Status = gtBS->LocateProtocol (
                   &gEfiBlueToothAttributeProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  Status = gtBS->LocateProtocol (
                   &gEfiBlueToothLEConfigProtocolGuid,
                   NULL,
                   (VOID **) &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  AssertionType = NeedThreeOrWarning (ValueA, ValueB, ValueC);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BlueToothLESupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"BlueToothLESupport")) {
        GenTestConfigContent (L"gEfiBlueToothHcProtocolGuid       ", ValueA);
        GenTestConfigContent (L"gEfiBlueToothAttributeProtocolGuid", ValueB);
        GenTestConfigContent (L"gEfiBlueToothLEConfigProtocolGuid ", ValueC);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid028,
                   L"UEFI Compliant - BlueTooth LE Support protocols must be implemented",
                   L"%a:%d:BLUETOOTH HC - %s, BLUETOOTH Attribute - %s, BLUETOOTH LE Config - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueA ? L"Yes" : L"No",
                   ValueB ? L"Yes" : L"No",
                   ValueC ? L"Yes" : L"No"
                   );


  return EFI_SUCCESS;
}



EFI_STATUS
CheckIPSecProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[MAX_LENGTH];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the IPSEC_CONFIG protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiIPSecConfigProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the IPSEC2 protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiIPSec2ProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && (IniFile != NULL)) {
    MaxLength = MAX_LENGTH;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"IPSecSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      if (!GenTestConfigTitle (IniFile, &AssertionType, L"IPSecSupport")) {
        GenTestConfigContent (L"gEfiIPSecConfigProtocolGuid", ValueA);
        GenTestConfigContent (L"gEfiIPSec2ProtocolGuid     ", ValueB);
      }
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid027,
                 L"UEFI Compliant - IPsec protocols must be implemented",
                 L"%a:%d:IPSEC_CONFIG - %s, IPSEC2 - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No"
                 );

  return EFI_SUCCESS;
}

CONFIG_ERROR_DATA*
ConstructionAndAcquisition (
  CHAR16               *TitleString,
  EFI_INI_FILE_HANDLE  ConfigINI
){
  UINTN  Index;
  static CONFIG_ERROR_DATA Data;

  if (TitleString == NULL && ConfigINI != NULL) {
    //
    //  If only gave ConfigINI, init struct.
    //
    gtBS->AllocatePool (EfiBootServicesData ,MAX_SIZE, (VOID**)&(Data.TitleString));
    Data.ConfigINI   = ConfigINI;
    Data.ErrorCount  = 0;

    return NULL;
  } else if (TitleString != NULL && ConfigINI == NULL) {
    //
    // If Only gave TitleString, update the title and error count +1.
    //
    for (Index=0; Data.TitleString[Index]=TitleString[Index], TitleString[Index]!=0; Index++);
    Data.ErrorCount++;

    return &Data;
  } else if (TitleString != NULL && ConfigINI != NULL) {
    //
    // If Both not NULL, end of the function, free the buffer.
    //
    gtBS->FreePool (Data.TitleString);
    return &Data;
  }
  //
  // If both NULL, just return struct data.
  //
  return &Data;
}

EFI_STATUS
GenTestConfigTitle (
  IN      EFI_INI_FILE_HANDLE  IniFile,
  IN OUT  EFI_TEST_ASSERTION   *AssertionType,
  IN      CHAR16               *TestItemString
){
  CONFIG_ERROR_DATA *ErrorData;
  EFI_STATUS        Status;
  CHAR16            String[MAX_LENGTH];
  UINT32            MaxLength;

  //
  // Check need to gen config.ini or not.
  //
  MaxLength = MAX_LENGTH;
  Status = IniFile->GetString (
                      IniFile,
                      SECTION_NAME_CONFIGURATION_SPECIFIC,
                      L"GEN_CONFIG_INI_FILE_ON",
                      String,
                      &MaxLength
                    );
  if (EFI_ERROR (Status) || !(SctStriCmp (String, L"yes") == 0)) {
    return EFI_UNSUPPORTED;
  }

  //
  //  If platform owner is not sure platform config yet, this item can skip this test.
  //
  MaxLength = MAX_LENGTH;
  Status = IniFile->GetString (
                      IniFile,
                      SECTION_NAME_CONFIGURATION_SPECIFIC,
                      L"IGNORE_COMPLIANT_TEST_CSV",
                      String,
                      &MaxLength
                    );
  if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
    *AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  ErrorData = ConstructionAndAcquisition (TestItemString, NULL);
  //
  // Set title
  //
  ErrorData->ConfigINI->SetStringByOrder (
               ErrorData->ConfigINI,
               ErrorData->ErrorCount,
               SctPoolPrint (L"%02d. %s",ErrorData->ErrorCount, TestItemString),
               L"Device Status  :",
               L":  Unavailable"
             );

  return EFI_SUCCESS;
}

EFI_STATUS
GenTestConfigContent (
  IN CHAR16   *ProtocolGUIDString,
  IN BOOLEAN  Value
){
  CONFIG_ERROR_DATA *ErrorData;

  ErrorData = ConstructionAndAcquisition (NULL, NULL);
  //
  // Gen content
  //
  ErrorData->ConfigINI->SetString (
               ErrorData->ConfigINI,
               SctPoolPrint (L"%02d. %s",ErrorData->ErrorCount, ErrorData->TitleString),
               SctPoolPrint (L" %s  <-| Status  :", ProtocolGUIDString),
               Value ? L":  Exist in system !": L":  Not exist in system !"
             );

  return EFI_SUCCESS;
}

