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

  EfiCompliantBbTestPlatform.c

Abstract:

  Check the platform specific elements in EFI Spec.

--*/

//
// Includes
//

#include "SctLib.h"
#include "EfiCompliantBbTestMain_efi.h"
#include EFI_PROTOCOL_DEFINITION (SimpleTextIn)
#include <UEFI/Protocol/SimpleTextOut.h>
#include <UEFI/Protocol/UgaDraw.h>
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

EFI_STATUS
CheckConsoleProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  );

EFI_STATUS
CheckGraphicalConsoleProtocols (
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

  Check the platform specific elements, which defined in the EFI spec 1.10,
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
                   &StandardLib
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
                   &ProfileLib
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
                   L"EFI Compliant - Cannot open INI file",
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
  // Check the graphical console protocols
  //
  CheckGraphicalConsoleProtocols (StandardLib, IniFile);

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
  // Check the Debug support protocols
  //
  CheckDebugProtocols (StandardLib, IniFile);

  //
  // Check the driver override protocols
  //
  CheckDriverOverrideProtocols (StandardLib, IniFile);

  //
  // Close the INI file
  //
  CloseIniFile (ProfileLib, IniFile);

  //
  // Done
  //
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
  // Need two or warning
  //
  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - Console protocols must be implemented",
                 L"%a:%d:Text Input - %s, Text Output - %s",
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
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the UGA_DRAW protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiUgaDrawProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the UGA_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiUgaIoProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  //
  // UEFI forum may want to drop UGA I/O protocol as a required implementation.
  // So here we skip the check to this protocol.
  //

  //
  // Need *one* or warning
  //
  AssertionType = NeedOneOrWarning (ValueA);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - Graphical console protocols must be implemented",
                 L"%a:%d:UGA Draw - %s, UGA IO (not required) - %s",
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

  //
  // Need one or warning
  //
  AssertionType = NeedOneOrWarning (ValueA);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - Pointer protocols must be implemented",
                 L"%a:%d:Pointer - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  //
  // Done
  //
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

  //
  // Need four or warning
  //
  AssertionType = NeedFourOrWarning (ValueA, ValueB, ValueC, ValueD);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - Boot from disk protocols must be implemented",
                 L"%a:%d:Block IO - %s, Disk IO - %s, Simple FS - %s, Unicode Collation - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No",
                 ValueC ? L"Yes" : L"No",
                 ValueD ? L"Yes" : L"No"
                 );

  //
  // Done
  //
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
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the SIMPLE_NETWORK protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimpleNetworkProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the PXE_BASE_CODE protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiPxeBaseCodeProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  //
  // Check the BIS protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiBisProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  //
  // BIS protocol indicates the ability to validate a boot image received
  // through a network device. UEFI forum may think it is not one of platform
  // specific elements. So here we skip the check to this protocol.
  //

  //
  // Need *two* or warning
  //
  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - Boot from network protocols must be implemented",
                 L"%a:%d:SNP - %s, PXE BC - %s, BIS (not required) - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No",
                 ValueC ? L"Yes" : L"No"
                 );

  //
  // Done
  //
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

  //
  // Need one or warning
  //
  AssertionType = NeedOneOrWarning (ValueA);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - UART protocols must be implemented",
                 L"%a:%d:Serial IO - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  //
  // Done
  //
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
  BOOLEAN             ValueC;
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

  //
  // Check the DEVICE_IO protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiDeviceIoProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  //
  // UEFI forum may want to eliminate Device IO protocol and require all drivers
  // today to use PCI I/O protocols. So here we skip the check to this protocol.
  //

  //
  // Need *two* or warning
  //
  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - PCI Bus support protocols must be implemented",
                 L"%a:%d:PCI Root Bridge - %s, PCI IO - %s, Device IO (not required) - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No",
                 ValueC ? L"Yes" : L"No"
                 );

  //
  // Done
  //
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
  // Check the USB_HC protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiUsbHcProtocolGuid,
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

  //
  // Need two or warning
  //
  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - USB Bus support protocols must be implemented",
                 L"%a:%d:USB HC - %s, USB IO - %s",
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
  // Check the SCSI_PASS_THRU protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiScsiPassThruProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Need one or warning
  //
  AssertionType = NeedOneOrWarning (ValueA);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                        L"ScsiPassThru",
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
                 L"EFI Compliant - SCSI Pass Thru protocol must be implemented",
                 L"%a:%d:SCSI Pass Thru - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
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

  //
  // Need two or warning
  //
  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - Debug support protocols must be implemented",
                 L"%a:%d:Debug Support - %s, Debug Port - %s",
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

  //
  // Need one or warning
  //
  AssertionType = NeedOneOrWarning (ValueA);

  //
  // For platform-specific elements, throw out a warning in default
  //
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
                 L"EFI Compliant - Platform Driver Override protocols must be implemented",
                 L"%a:%d:Platform Driver Override - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No"
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}
