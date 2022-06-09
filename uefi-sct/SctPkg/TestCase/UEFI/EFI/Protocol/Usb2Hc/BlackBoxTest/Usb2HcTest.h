/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  Usb2HcTest.h

Abstract:
  Header file for Usb Host Controller Protocol Interface testing.


--*/
#ifndef _USB2_HC_TEST_H
#define _USB2_HC_TEST_H

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include <UEFI/Protocol/Usb2Hc.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#define USB2_HC_TEST_REVISION 0x00010001

//
// Definitions
//
#define USB2_HC_GETCAPABILITY_BASIC_MANUAL_GUID \
  { \
    0xc5ea463e, 0xee7f, 0x433c, \
    { \
      0x87, 0x4c, 0x8a, 0x2f, 0xd8, 0xb6, 0x11, 0x75 \
    } \
  }

#define USB2_HC_RESET_BASIC_AUTO_GUID \
  { \
    0x3eeabd64, 0xcf3b, 0x40eb, \
    { \
      0x85, 0x76, 0x19, 0x87, 0x35, 0x55, 0xb9, 0x3d \
    } \
  }

#define USB2_HC_GETSTATE_BASIC_AUTO_GUID \
  { \
    0x672b37fc, 0xd8d9, 0x461b, \
    { \
      0xb2, 0x9d, 0xc9, 0x67, 0xef, 0xb9, 0xa9, 0xf2 \
    } \
  }

#define USB2_HC_SETSTATE_BASIC_AUTO_GUID \
  { \
    0xa5092e0, 0x7b93, 0x46f1, \
    { \
      0xb4, 0x7a, 0x3, 0x43, 0x4, 0xc, 0x94, 0x45 \
    } \
  }

#define USB2_HC_GETROOTHUBPORTSTATUS_BASIC_AUTO_GUID \
  { \
    0x841b238, 0x750d, 0x480d, \
    { \
      0xb1, 0x1f, 0x5d, 0x75, 0xc, 0x89, 0xb5, 0x22 \
    } \
  }

#define USB2_HC_GETROOTHUBPORTSTATUS_BASIC_MANUAL_GUID \
  { \
    0xf2757018, 0xcbca, 0x4b41, \
    { \
      0xbf, 0x8b, 0x8d, 0x3d, 0x45, 0xf8, 0x5e, 0x69 \
    } \
  }

#define USB2_HC_SETROOTHUBPORTFEATURE_BASIC_AUTO_GUID \
  { \
    0x78c75591, 0xdd7a, 0x448b, \
    { \
      0x99, 0x34, 0x48, 0xc3, 0xc0, 0x4d, 0x86, 0x13 \
    } \
  }

#define USB2_HC_CLEARROOTHUBPORTFEATURE_BASIC_AUTO_GUID \
  { \
    0x7dba9091, 0x2f12, 0x4a5e, \
    { \
      0xa6, 0xc6, 0x84, 0x3a, 0x76, 0xa3, 0x1c, 0xad \
    } \
  }

#define USB2_HC_CLEARROOTHUBPORTFEATURE_BASIC_MANUAL_GUID \
  { \
    0x6f85440c, 0x9ba3, 0x499f, \
    { \
      0x9d, 0xc0, 0x6c, 0x24, 0x37, 0x9c, 0x15, 0x47 \
    } \
  }

#define USB2_HC_GETCAPABILITY_CONFORMANCE_AUTO_GUID \
  { \
    0x89914191, 0x2fad, 0x41e7, \
    { \
      0x8e, 0xee, 0xa5, 0xfc, 0xb, 0xa3, 0x6, 0x86 \
    } \
  }

#define USB2_HC_RESET_CONFORMANCE_AUTO_GUID \
  { \
    0x4ff62206, 0x86a6, 0x4666, \
    { \
      0xbe, 0x24, 0x1f, 0x77, 0x0, 0xcf, 0x67, 0xc0 \
    } \
  }

#define USB2_HC_GETSTATE_CONFORMANCE_AUTO_GUID \
  { \
    0x34a17e4a, 0x8d44, 0x4e9b, \
    { \
      0x83, 0x85, 0x81, 0x23, 0xb4, 0x51, 0x3, 0xc9 \
    } \
  }

#define USB2_HC_SETSTATE_CONFORMANCE_AUTO_GUID \
  { \
    0xe4dbfa0f, 0x6b8d, 0x4f7b, \
    { \
      0xbe, 0xea, 0x1a, 0x6d, 0x1b, 0x2, 0x2, 0x1f \
    } \
  }

#define USB2_HC_CONTROLTRANSFER_CONFORMANCE_AUTO_GUID \
  { \
    0x5c0ea65b, 0x45b, 0x4829, \
    { \
      0xbe, 0x50, 0x18, 0xc7, 0x6b, 0x77, 0x58, 0x17 \
    } \
  }

#define USB2_HC_CONTROLTRANSFER_CONFORMANCE_MANUAL_GUID \
  { \
    0x78b12ce5, 0x88b9, 0x485b, \
    { \
      0x82, 0x8a, 0xd7, 0xf2, 0x2, 0xff, 0x44, 0xd3 \
    } \
  }

#define USB2_HC_BULKTRANSFER_CONFORMANCE_AUTO_GUID \
  { \
    0xd0d4f7db, 0xa43d, 0x44bb, \
    { \
      0xaa, 0x54, 0x95, 0x7b, 0xd3, 0x78, 0xcf, 0xd3 \
    } \
  }

#define USB2_HC_ASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  { \
    0x5041cd9, 0x8948, 0x47c0, \
    { \
      0xaf, 0xe6, 0xa9, 0xe4, 0x2f, 0xea, 0x7b, 0x1a \
    } \
  }

#define USB2_HC_SYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  { \
    0x96b5f134, 0x9722, 0x468d, \
    { \
      0x9b, 0xf4, 0xf3, 0x3e, 0xb1, 0xfe, 0xfb, 0xc5 \
    } \
  }

#define USB2_HC_ASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  { \
    0xd5ddec35, 0x59eb, 0x445e, \
    { \
      0xb6, 0xd8, 0x42, 0xcc, 0xb2, 0x36, 0x2f, 0x9f \
    } \
  }

#define USB2_HC_ISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  { \
    0xa254487a, 0x5b6f, 0x453e, \
    { \
      0xb2, 0x6c, 0x49, 0x83, 0xe5, 0xe, 0xe0, 0xe6 \
    } \
  }

#define USB2_HC_GETROOTHUBPORTSTATUS_CONFORMANCE_AUTO_GUID \
  { \
    0x41efe42c, 0x67f5, 0x4ee5, \
    { \
      0x9e, 0xa7, 0xa9, 0x19, 0x85, 0x28, 0xca, 0x89 \
    } \
  }

#define USB2_HC_SETROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID \
  { \
    0x5a4fdab, 0xf368, 0x4970, \
    { \
      0xa1, 0xc4, 0xdd, 0xcd, 0x77, 0xeb, 0x4a, 0x48 \
    } \
  }

#define USB2_HC_CLEARROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID \
  { \
    0xde93af74, 0xe31, 0x4c29, \
    { \
      0x9f, 0xb1, 0x58, 0x17, 0xf4, 0xf6, 0xee, 0xea \
    } \
  }

//
// Prototypes
//
//
// TDS 4.1.1
//
EFI_STATUS
EFIAPI
Usb2HcGetCapabilityBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetCapability() Basic Manual Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 4.2.1
//
EFI_STATUS
EFIAPI
Usb2HcResetBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->Reset() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 4.3.1
//
EFI_STATUS
EFIAPI
Usb2HcGetStateBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetState() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 4.4.1
//
EFI_STATUS
EFIAPI
Usb2HcSetStateBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->SetState() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 4.5.1
//
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetRootHubPortStatus() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 4.6.1
//
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetRootHubPortStatus() Basic Manual Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 4.7.1
//
EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->SetRootHubPortFeature() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 4.8.1
//
EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ClearRootHubPortFeature() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 4.9.1
//
EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ClearRootHubPortFeature() Basic Manual Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
;

//
// TDS 5.1.1
//
EFI_STATUS
EFIAPI
Usb2HcGetCapabilityConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetCapability() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.2.1
//
EFI_STATUS
EFIAPI
Usb2HcResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->Reset() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.3.1
//
EFI_STATUS
EFIAPI
Usb2HcGetStateConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetState() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.4.1
//
EFI_STATUS
EFIAPI
Usb2HcSetStateConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->Setstate() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.5.1
//
EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ControlTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.6.1
//
EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ControlTransfer() Conformance manual Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.7.1
//
EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->BulkTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.8.1
//
EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->AsyncInterruptTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.9.1
//
EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->SyncInterruptTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.14.1
//
EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->AsyncIsochronousTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.13.1
//
EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->IsochronousTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.10.1
//
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetRootHubPortStatus() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.11.1
//
EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->SetRootHubPortFeature() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

//
// TDS 5.12.1
//
EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ClearRootHubPortFeature() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

--*/
;

EFI_STATUS
EFIAPI
InitializeBBTestUsb2Hc (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:

  Creates/installs the BlackBox Interface and the Entry Point list.

Arguments:

  ImageHandle              - The image handle.
  SystemTable              -The system table.

Returns:

 EFI_SUCCESS               - The interface was installed successfully.
 EFI_OUT_OF_RESOURCES      - Failed due to the lack of resources.
 EFI_INVALID_PARAMETER     - One of parameters is invalid.

--*/
;

EFI_STATUS
EFIAPI
BBTestUsb2HcUnload (
  IN EFI_HANDLE           ImageHandle
  )
/*++

Routine Description:

  Unloads the BlackBox Interface and the Entry Point list.

Arguments:

  ImageHandle   - The image handle.

Returns:

  EFI_SUCCESS   -The interface was uninstalled successfully.

--*/
;

VOID
StallForChangeDevice (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN UINTN                                Time
  )
/*++

Routine Description:

  Unloads the BlackBox Interface and the Entry Point list.

Arguments:

  ImageHandle   - The image handle.

Returns:

  EFI_SUCCESS   -The interface was uninstalled successfully.

--*/
;

VOID
MaskTimerInterrupt (
  VOID
  )
/*++

Routine Description:

  Mask timer interrupt

Arguments:

  None

Returns:

  VOID

--*/
;

VOID
UnmaskTimerInterrupt (
  VOID
  )
/*++

Routine Description:

  Unmask timer interrupt
Arguments:

  None

Returns:

  VOID

--*/
;

BOOLEAN
AutoJudge (
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  )
/*++

Routine Description:

  Assistant function to auto judge the user's choice, correct or uncorrect.

Arguments:

  Seconds    - Time inteval
  Default    - Default value to judge
  Message    - String to desplay on screen

Returns:

  TRUE       - correct choice respectively
  FALSE      - uncorrect choice respectively

--*/
;
#endif
