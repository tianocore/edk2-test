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
CheckPointerProtocols (
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
CheckUartProtocols (
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
CheckScsiProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckBootFromIScsi (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );
  
EFI_STATUS
CheckBootFromScsi (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckEbcProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckDebugProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckDriverOverrideProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

//
// External functions implementation
//

EFI_STATUS
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
  // Check the general network application
  //
  CheckUefiNetworkApplication (StandardLib, IniFile);

  //
  // Check the general V6 network application
  //  
  CheckUefiV6NetworkApplication (StandardLib, IniFile);
  
  //
  // Check the pointer protocols
  //
  CheckPointerProtocols (StandardLib, IniFile);

  //
  // Check the boot from disk protocols
  //
  CheckBootFromDiskProtocols (StandardLib, IniFile);

  //
  // Check the boot from network protocols
  //
  CheckBootFromNetworkProtocols (StandardLib, IniFile);

  //
  // Check the UART support protocols
  //
  CheckUartProtocols (StandardLib, IniFile);

  //
  // Check the PCI support protocols
  //
  CheckPciProtocols (StandardLib, IniFile);

  //
  // Check the USB support protocols
  //
  CheckUsbProtocols (StandardLib, IniFile);

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
  CheckDriverOverrideProtocols (StandardLib, IniFile);

  //
  // Check the EBC Interpreter
  //
  CheckEbcProtocol (StandardLib, IniFile);

  //
  // Close the INI file
  //
  CloseIniFile (ProfileLib, IniFile);

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
  CHAR16              String[10];
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
                   &Interface
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
                   &Interface
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
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"ConsoleDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
                 L"%a:%d:Text Input - %s, Text Output - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No"
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
  CHAR16              String[10];
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
                     &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"HiiConfigSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
    
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
      MaxLength = 10;
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"HiiFontSupport",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  CHAR16              String[10];
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
                   &Interface
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
                   &Interface
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
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"GraphicalConsoleDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
CheckPointerProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the SIMPLE_POINTER protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimplePointerProtocolGuid,
                   NULL,
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"PointerDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  CHAR16              String[10];
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
                   &Interface
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
                   &Interface
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
                   &Interface
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
                   &gEfiUnicodeCollationProtocolGuid,
                   NULL,
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromDiskDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  CHAR16              String[10];
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
                   &Interface
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
                   &Interface
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
                   &Interface
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
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromNetworkDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
                 L"%a:%d:SNP - %s, PXE BC - %s, BIS (not required) - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No"
                 );

  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    AssertionType = NeedOneOrWarning (ValueC);

    if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
      MaxLength = 10;
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"ValidateBootImageThruNet",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
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
                   L"%a:%d:BIS - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ValueC ? L"Yes" : L"No"
                 );

  }

  return EFI_SUCCESS;
}

EFI_STATUS
CheckUartProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the SERIAL_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSerialIoProtocolGuid,
                   NULL,
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"UartDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  CHAR16              String[10];
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
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"PciBusSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  CHAR16              String[10];
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
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"UsbBusSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
CheckScsiProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the Extended SCSI_PASS_THRU protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiExtScsiPassThruProtocolGuid,
                   NULL,
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"ExtScsiPassThru",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
CheckDebugProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
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
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"DebugSupport",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
CheckDriverOverrideProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
  BOOLEAN             ValueA;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the DRIVER_OVERRIDE protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiPlatformDriverOverrideProtocolGuid,
                   NULL,
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"PlatformDriverOverride",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
CheckUefiNetworkApplication (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{

  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
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
  Guid[6] =     gEfiIp4ConfigProtocolGuid;

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
                     &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile != NULL)) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"UefiNetworkApplication",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid012,
                   L"UEFI Compliant - UEFI General Network Application required",
                   L"%a:%d:MnpSB-%s, ArpSB-%s, Ip4SB-%s, Dhcp4SB-%s, Tcp4SB-%s, Udp4SB-%s, Ip4Config-%s",
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

  }else if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid012,
                   L"UEFI Compliant - UEFI General Network Application required",
                   L"%a:%d:MnpSB-%s, ArpSB-%s, Ip4SB-%s, Dhcp4SB-%s, Tcp4SB-%s, Udp4SB-%s, Ip4Config-%s",
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
  } else {
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

    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
        (IniFile != NULL)) {
      MaxLength = 10;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"UefiNetworkApplication",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiCompliantBbTestPlatformAssertionGuid012,
                   L"UEFI Compliant-UEFI General Network Application required",
                   L"%a:%d:MnpSB-%s,ArpSB-%s,Ip4SB-%s,Dhcp4SB-%s,Tcp4SB-%s,Udp4SB-%s,Ip4Config-%s,"
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
CheckBootFromScsi (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
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
                   &Interface
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
                   &Interface
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
                   &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromScsi",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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

    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
      MaxLength = 10;

      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"ExtScsiPassThruSupport",
                          String,
                          &MaxLength
                        );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  CHAR16              String[10];
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
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the EFI_ISCSI_INITIATOR_NAME_PROTOCOL
  //
  Status = gtBS->LocateProtocol (
                   &gEfiAuthenticationInfoProtocolGuid,
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromIscsi",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
CheckEbcProtocol (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  EFI_EBC_PROTOCOL    *Ebc;
  EFI_TEST_ASSERTION  AssertionType;
  UINT32              MaxLength;
  CHAR16              String[10];
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) && 
      (IniFile != NULL)) {
    MaxLength = 10;

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


#define EFI_DHCP6_SERVICE_BINDING_PROTOCOL_GUID \
{0x9fb9a8a1,0x2f4a,0x43a6,0x88,0x9c,0xd0,0xf7,0xb6,0xc4,0x7a,0xd5}
#define EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID \
{0xec20eb79,0x6c1a,0x4664,0x9a,0xd,0xd2,0xe4,0xcc,0x16,0xd6, 0x64}
#define EFI_IP6_SERVICE_BINDING_PROTOCOL_GUID \
{0xec835dd3,0xfe0f,0x617b,0xa6,0x21,0xb3,0x50,0xc3,0xe1,0x33,0x88}
#define EFI_UDP6_SERVICE_BINDING_PROTOCOL_GUID \
{0x66ed4721,0x3c98,0x4d3e,0x81,0xe3,0xd0,0x3d,0xd3,0x9a,0x72,0x54}
#define EFI_IP6_CONFIG_PROTOCOL_GUID \
{0x937fe521,0x95ae,0x4d1a,0x89,0x29,0x48,0xbc,0xd9,0xa,0xd3,0x1a}
#define EFI_VLAN_CONFIG_PROTOCOL_GUID \
{0x9e23d768,0xd2f3,0x4366,0x9f,0xc3,0x3a,0x7a,0xba,0x86,0x43,0x74}

#define EFI_DHCP6_PROTOCOL_GUID \
{0x87c8bad7,0x595,0x4053,0x82,0x97,0xde,0xde,0x39,0x5f,0x5d,0x5b}
#define EFI_TCP6_PROTOCOL_GUID \
{0x46e44855,0xbd60,0x4ab7,0xab,0xd,0xa6,0x79,0xb9,0x44,0x7d,0x77}
#define EFI_IP6_PROTOCOL_GUID \
{0x2c8759d5,0x5c2d,0x66ef,0x92,0x5f,0xb6,0x6c,0x10,0x19,0x57,0xe2}
#define EFI_UDP6_PROTOCOL_GUID \
{0x4f948815,0xb4b9,0x43cb,0x8a,0x33,0x90,0xe0,0x60,0xb3,0x49,0x55}

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

EFI_STATUS
CheckUefiV6NetworkApplication (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{

  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
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
                     &Interface
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
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile != NULL)) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"UEFIIPv6Support",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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

  }else if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
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
                       &Interface
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
    if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
        (IniFile != NULL)) {
      MaxLength = 10;
  
      Status = IniFile->GetString (
                          IniFile,
                          SECTION_NAME_PLATFORM_SPECIFIC,
                          L"UEFIIPv6Support",
                          String,
                          &MaxLength
                          );
      if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
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
                       &Interface
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
      if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
        (IniFile       != NULL               )) {
        MaxLength = 10;

        Status = IniFile->GetString (
                            IniFile,
                            SECTION_NAME_PLATFORM_SPECIFIC,
                            L"VlanSupport",
                            String,
                            &MaxLength
                            );
        if (!EFI_ERROR (Status) && (SctStriCmp (String, L"yes") == 0)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
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
