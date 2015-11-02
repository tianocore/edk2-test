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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
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

#define IHV_USB2_HC_PROTOCOL_GUID \
  { 0x2b280458, 0x3bab, 0x4402, 0x88, 0x69, 0xef, 0x2f, 0x9a, 0xc0, 0xb5, 0x46 }

//
// Definitions
//
#define USB2_HC_GETCAPABILITY_BASIC_MANUAL_GUID \
  { 0x1b676e57, 0x58a0, 0x4595, { 0xae, 0x75, 0x69, 0xe1, 0xda, 0x30, 0x7, 0x48 } }

#define USB2_HC_RESET_BASIC_AUTO_GUID \
  { 0x546fb5e0, 0x51c4, 0x449a, { 0xa0, 0xd5, 0x58, 0xb9, 0xab, 0x14, 0x2f, 0x92 } }

#define USB2_HC_GETSTATE_BASIC_AUTO_GUID \
  { 0xac2d0e59, 0x68a9, 0x467e, { 0xa0, 0x8c, 0x75, 0x51, 0x52, 0x3a, 0x4d, 0x3c } }

#define USB2_HC_SETSTATE_BASIC_AUTO_GUID \
  { 0xc2b71bfc, 0xfdbe, 0x459f, { 0x91, 0x1d, 0xe1, 0x1e, 0xd, 0x8a, 0x77, 0xc6 } }

#define USB2_HC_GETROOTHUBPORTSTATUS_BASIC_AUTO_GUID \
  { 0x7eaf3fa8, 0xb811, 0x479a, { 0xb2, 0x19, 0x43, 0x8d, 0x80, 0xcf, 0x2c, 0x60 } }

#define USB2_HC_GETROOTHUBPORTSTATUS_BASIC_MANUAL_GUID \
  { 0x6827e70f, 0xbed0, 0x4b08, { 0xb2, 0xf9, 0x20, 0x5c, 0x63, 0xf0, 0xa5, 0xcb } }

#define USB2_HC_SETROOTHUBPORTFEATURE_BASIC_AUTO_GUID \
  { 0x1bfb98fe, 0x7437, 0x4e9d, { 0x91, 0x4d, 0xbb, 0xf8, 0xfa, 0xff, 0xb7, 0x94 } }

#define USB2_HC_CLEARROOTHUBPORTFEATURE_BASIC_AUTO_GUID \
  { 0xd1435638, 0x651, 0x448e, { 0x81, 0x2e, 0xfd, 0xad, 0xbf, 0x39, 0x85, 0x95 } }

#define USB2_HC_CLEARROOTHUBPORTFEATURE_BASIC_MANUAL_GUID \
  { 0xa492d790, 0x1d4d, 0x45d7, { 0xaa, 0x33, 0x76, 0xa0, 0x96, 0x21, 0xd2, 0xe2 } }

#define USB2_HC_GETCAPABILITY_CONFORMANCE_AUTO_GUID \
  { 0x7e4bc4d5, 0x5262, 0x4629, { 0xae, 0xe, 0x86, 0x27, 0x1f, 0x7d, 0x18, 0xef } }

#define USB2_HC_RESET_CONFORMANCE_AUTO_GUID \
  { 0xa01191ed, 0x1b, 0x40aa, { 0xae, 0xc4, 0x6, 0x1f, 0x43, 0x3, 0x77, 0x90 } }

#define USB2_HC_GETSTATE_CONFORMANCE_AUTO_GUID \
  { 0x23cf8f65, 0x195f, 0x4d83, { 0x84, 0xbe, 0x7e, 0x98, 0x54, 0xa8, 0xce, 0x68 } }

#define USB2_HC_SETSTATE_CONFORMANCE_AUTO_GUID \
  { 0xa79d142c, 0xed86, 0x4389, { 0x86, 0xf, 0xd6, 0xb8, 0x78, 0xc9, 0x64, 0xf6 } }

#define USB2_HC_CONTROLTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0xfcb447f3, 0x1547, 0x4d09, { 0x82, 0x38, 0x48, 0x7a, 0xcb, 0x3f, 0xbb, 0xbe } }

#define USB2_HC_CONTROLTRANSFER_CONFORMANCE_MANUAL_GUID \
  { 0x88a5b6b7, 0x4f4c, 0x412a, { 0xbf, 0xd3, 0x73, 0xd5, 0x1d, 0x78, 0x64, 0xc } }

#define USB2_HC_BULKTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x237aeb26, 0x8167, 0x41b4, { 0x95, 0xe4, 0x57, 0x72, 0x5a, 0xe3, 0x19, 0x5d } }

#define USB2_HC_ASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0xd92e395, 0x1774, 0x440a, { 0x85, 0x1a, 0xe2, 0x3d, 0xae, 0xdc, 0x2e, 0x9f } }

#define USB2_HC_SYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0xbd44312a, 0xd161, 0x4334, { 0xbd, 0x26, 0x9d, 0xe1, 0x55, 0x83, 0x8, 0x52 } }

#define USB2_HC_ASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0xb3f0db88, 0xf0b, 0x4356, { 0xb8, 0x54, 0xc, 0x3f, 0x18, 0xd5, 0x70, 0x23 } }

#define USB2_HC_ISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x5bfcb62a, 0x100a, 0x41bb, { 0xbf, 0xa2, 0x90, 0xb, 0xd6, 0xef, 0x2, 0x6b } }

#define USB2_HC_GETROOTHUBPORTSTATUS_CONFORMANCE_AUTO_GUID \
  { 0xc6d6b6d8, 0x43a1, 0x4372, { 0x81, 0xb6, 0xd1, 0xe3, 0x1a, 0x13, 0x40, 0x3b } }

#define USB2_HC_SETROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID \
  { 0x1af7393d, 0x30a1, 0x46a2, { 0xbe, 0x0, 0xe4, 0xb0, 0x99, 0xd9, 0x1e, 0x27 } }

#define USB2_HC_CLEARROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID \
  { 0x66e4674d, 0xdeb8, 0x42fa, { 0x89, 0x2a, 0x9d, 0x4f, 0xd0, 0x4b, 0x94, 0xb2 } }

//
// Prototypes
//
//
// TDS 4.1.1
//
EFI_STATUS
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
