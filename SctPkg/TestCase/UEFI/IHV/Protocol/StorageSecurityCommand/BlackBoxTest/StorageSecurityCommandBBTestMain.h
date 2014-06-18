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

  StorageSecurityCommandBBTestMain.h

Abstract:

  BB test header file of Storage Security Command Protocol

--*/


#ifndef _STORAGE_SEC_COMMAND_BBTEST_H_
#define _STORAGE_SEC_COMMAND_BBTEST_H_

//
// Includes
//

#include "Efi.h"
#include <UEFI/Protocol/StorageSecurityCommand.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/DevicePathUtilities.h>
#include <UEFI/Protocol/DevicePathToText.h>


//
// Definitions
//

#define STORAGE_SECURITY_COMMAND_PROTOCOL_TEST_REVISION     0x00010000

#define MAXIMUM(a,b)                        ((a)>(b)?(a):(b))
#define MINIMUM(a,b)                        ((a)<(b)?(a):(b))


//
// Global ID for the EFI Storage Security Command Protocol
//
#define IHV_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID \
  { \
     0x52e7f26a, 0x13c8, 0x4eee, { 0xb4, 0x5e, 0x21, 0xc7, 0xa0, 0xa3, 0x34, 0x5e } \
  }


//
// Entry GUIDs
//

//
// Conformance
//
#define STORAGE_SECURITY_COMMAND_PROTOCOL_RECEIVEDATA_CONFORMANCE_AUTO_GUID \
  { 0xe091bfcd, 0x290b, 0x44c0, { 0x92, 0x57, 0xc5, 0xfa, 0x61, 0x60, 0xd9, 0x68 } }


#define STORAGE_SECURITY_COMMAND_PROTOCOL_SENDDATA_CONFORMANCE_AUTO_GUID \
  { 0xa4bae301, 0x8de8, 0x4afc, { 0xa4, 0x4a, 0x66, 0x9f, 0xbb, 0x8e, 0x33, 0xba } }

//
// Function
//


//
// Global variables
//


//
// Prototypes
//

EFI_STATUS
InitializeBBTestStorageSecurityCommand (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );

EFI_STATUS
BBTestStorageSecurityCommandProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Conformance test case prototypes
//

EFI_STATUS
BBTestReceiveDataConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSendDataConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Function test case prototypes
//


//
// Stress test case prototypes
//


//
// Internal support function prototypes
//

#define ROUNDUP512(x) (((x) == 0) ? 512 : (((x) + (512 - 1)) & ~512))

#define SECURITY_PROTOCOL_TCG      0x02
#define SECURITY_PROTOCOL_IEEE1667 0xEE

#endif

