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
                                                                
  Copyright 2016 - 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Hash2BBTestMain.h

Abstract:

  Test Driver of Hash2 Protocol header file

--*/

#ifndef _HASH2_BB_TEST_MAIN
#define _HASH2_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/Hash2.h>
#include "Guid.h"


#define EFI_HASH2_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_HASH2_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xc623051b, 0x36bf, 0x4cb2, {0xac, 0x52, 0x4e, 0xce, 0x2, 0xb4, 0xf5, 0x3e }}

#define EFI_HASH2_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x93a72a08, 0xd5a, 0x4656, {0xb1, 0x64, 0x7b, 0x37, 0xbf, 0x43, 0x49, 0x8f }}

#define EFI_HASH2_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xfa3c7bf6, 0xa2ca, 0x4bf7, {0x8d, 0x48, 0x38, 0x1d, 0x6a, 0x39, 0x3c, 0xcc }}




//
// Entry GUIDs for Conf Test
//
#define EFI_HASH2_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x5f33702e, 0x77a1, 0x48d1, {0x88, 0xe2, 0xdc, 0x3f, 0x73, 0x1b, 0x91, 0x14 }}

#define EFI_HASH2_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xba20715a, 0x2a43, 0x4672, {0x8e, 0xf0, 0x74, 0x41, 0xd5, 0x1, 0x15, 0xb1 }}

#define EFI_HASH2_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x9ead776, 0x54f0, 0x458a, {0x96, 0x55, 0xcc, 0xa1, 0x2b, 0xef, 0x93, 0x6a }}

#define EFI_HASH2_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0xec1e15cc, 0x4304, 0x48a4, {0xa9, 0xb7, 0x93, 0xcc, 0x73, 0x8, 0x16, 0x1a }}

#define EFI_HASH2_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0x75a2ea21, 0x1e6b, 0x46bd, {0x8f, 0xec, 0xaa, 0xeb, 0x5f, 0x26, 0x8f, 0xab }}

typedef struct _EFI_HASH2_SERVICE_BINDING_PROTOCOL EFI_HASH2_SERVICE_BINDING_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI EFI_SERVICE_BINDING_CREATE_CHILD) (
    IN EFI_HASH2_SERVICE_BINDING_PROTOCOL *This,
    IN OUT EFI_HANDLE *ChildHandle
);

typedef
EFI_STATUS
(EFIAPI EFI_SERVICE_BINDING_DESTROY_CHILD) (
    IN EFI_HASH2_SERVICE_BINDING_PROTOCOL *This,
    IN EFI_HANDLE ChildHandle
);

typedef struct _HASH_PRIVATE_DATA {
    EFI_HASH2_PROTOCOL hashServiceProtocol;
    EFI_HANDLE ChildHandle;
    EFI_HANDLE HashInterface;
    int NumberCreated;
    int Destroy;
    EFI_HANDLE ImageHandle;
    EFI_HANDLE HashDriverBindingHandle;	
} HASH_PRIVATE_DATA;

struct _EFI_HASH2_SERVICE_BINDING_PROTOCOL {
    EFI_SERVICE_BINDING_CREATE_CHILD *CreateChild;
    EFI_SERVICE_BINDING_DESTROY_CHILD *DestroyChild;
    HASH_PRIVATE_DATA PrivateData;	
};

#define HASH_PRIVATE_DATA_FROM_SERVICE_BINDING_THIS(x) (&x->PrivateData)
#define HASH_PRIVATE_DATA_FROM_HASH_THIS(x) (HASH_PRIVATE_DATA*)(x)

//
//
//
EFI_STATUS
EFIAPI
InitializeHash2BBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadHash2BBTest (
  IN EFI_HANDLE                   ImageHandle
  );

EFI_STATUS
Hash2ServiceBindingCreateChild (
  IN EFI_HASH2_SERVICE_BINDING_PROTOCOL    *This,
  EFI_HANDLE                               *ChildHandle,
  EFI_HASH2_PROTOCOL                       **Hash
);

EFI_STATUS
Hash2ServiceBindingDestoryChild (
	IN EFI_HASH2_SERVICE_BINDING_PROTOCOL    *This,
	EFI_HANDLE                               ChildHandle
);  
  
//
//Test Cases
//
EFI_STATUS
BBTestGetHashSizeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestHashConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestHashInitConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestHashUpdateConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestHashFinalConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetHashSizeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestHashFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestHashMultiBlocksFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


#endif

