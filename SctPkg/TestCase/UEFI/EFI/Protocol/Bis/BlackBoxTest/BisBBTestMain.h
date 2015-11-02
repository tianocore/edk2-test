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

  BisBBTestMain.h

Abstract:

  BB test header file of Bis Protocol

--*/


#ifndef _BOOT_INTEGRITY_SERVICES_H_
#define _BOOT_INTEGRITY_SERVICES_H_

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Bis.h>

#define BIS_TEST_REVISION 0x00010000

//
// file names definition
//
#define DUMP_CERTIFICATE_FILE_NAME                L"Certificate.dump"
#define DUMP_TOKEN_FILE_NAME                      L"Token.dump"
#define CREDENTIAL_FILE_NAME                      L"Credential"
#define DATA_FILE_NAME                            L"Dataobject"
#define CERTIFICATE_FILE_NAME                     L"Certificate"
#define SECTION_NAME                              "TestObject"

//
// Prototypes of BB Test
//

//
// TDS 3.1
//
EFI_STATUS
BBTestManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Prototypes of Internal Functions
//
EFI_STATUS
ReadFloppyFile (
  IN CHAR16       *FileName,
  OUT UINT32      *Length,
  OUT VOID        **Buffer
  );

EFI_STATUS
WriteFloppyFile (
  IN CHAR16      *FileName,
  IN OUT UINT32  Length,
  IN VOID        *Buffer
  );

VOID
PressAnyKey ();

BOOLEAN
PressYes ();

CHAR16 *
AlgToStr (
  BIS_ALG_ID      AlgId
);

//
// Entry GUIDs
//

#define BIS_MANUAL_TEST_GUID \
  { 0x26f4f004, 0x3616, 0x455e, 0xb1, 0x4a, 0xce, 0x74, 0x38, 0x6d, 0x4c, 0xa5 }

#endif
