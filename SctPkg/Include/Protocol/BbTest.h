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

  BbTest.h

Abstract:

  This file defines the EFI Black-Box Test Protocol.

--*/

#ifndef _EFI_BB_TEST_H_
#define _EFI_BB_TEST_H_

//
// Includes
//

//
// EFI Black-Box Test Protocol Definitions
//

#define EFI_BB_TEST_GUID                \
  { 0x8C41CE3E, 0xB255, 0x4966, 0xB5, 0x3C, 0x39, 0x76, 0x5A, 0xE1, 0x11, 0xD0 }

#define EFI_BB_TEST_REVISION            0x00010000

#define EFI_IHV_BB_TEST_GUID           \
  { 0x27e36cde, 0xa7e7, 0x4a4a, 0x9b, 0x5f, 0xa3, 0x9a, 0x56, 0x75, 0xcb, 0x80 }

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_BB_TEST_ENTRY EFI_BB_TEST_ENTRY;
typedef struct _EFI_BB_TEST_PROTOCOL EFI_BB_TEST_PROTOCOL;

//
// EFI Black-Box Test Entry Point
//

typedef
EFI_STATUS
(EFIAPI *EFI_BB_ENTRY_POINT) (
  IN  EFI_BB_TEST_PROTOCOL              *This,
  IN  VOID                              *ClientInterface,
  IN  EFI_TEST_LEVEL                    TestLevel,
  IN  EFI_HANDLE                        SupportHandle
  );

//
// EFI Black-Box Test Entry
//

struct _EFI_BB_TEST_ENTRY {
  EFI_BB_TEST_ENTRY                     *Next;
  EFI_GUID                              EntryId;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TEST_LEVEL                        TestLevelSupportMap;
  EFI_GUID                              *SupportProtocols;
  EFI_TEST_ATTRIBUTE                    CaseAttribute;
  EFI_BB_ENTRY_POINT                    EntryPoint;
};

//
// EFI Black-Box Test Protocol
//

struct _EFI_BB_TEST_PROTOCOL {
  UINT64                                TestRevision;
  EFI_GUID                              CategoryGuid;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_BB_TEST_ENTRY                     *EntryList;
};

//
// Global ID for EFI Black-Box Test Protocol
//

extern EFI_GUID gEfiBbTestGuid;
extern EFI_GUID gEfiIHVBbTestGuid;

#endif
