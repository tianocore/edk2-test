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
                                                                
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  RandomNumberGeneratorProtocol.h

Abstract:

  EFI Random Number Generator Protocol

--*/

#ifndef _RANDOM_NUMBER_PROTOCOL_H_
#define _RANDOM_NUMBER_PROTOCOL_H_

//
// Global ID for the Random Number Protocol
//
#define EFI_RANDOM_NUMBER_PROTOCOL_GUID    \
  { 0x3152bca5, 0xeade, 0x433d, 0x86, 0x2e, 0xc0, 0x1c,0xdc, 0x29, 0x1f, 0x44 }



typedef struct _EFI_RNG_PROTOCOL EFI_RNG_PROTOCOL;;

typedef EFI_GUID EFI_RNG_ALGORITHM;

typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_INFO) (
  IN     EFI_RNG_PROTOCOL     *This,
  IN OUT UINTN                *RNGAlgorithmListSize,
     OUT EFI_RNG_ALGORITHM    *RNGAlgorithmList
);

typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_RNG) (
  IN     EFI_RNG_PROTOCOL     *This,
  IN     EFI_RNG_ALGORITHM    *RNGAlgorithm, OPTIONAL
  IN     UINTN                RNGValueLength,
     OUT UINT8                *RNGValue
);

//
// Interface structure for the Random Number Protocol
//
struct _EFI_RNG_PROTOCOL {
  EFI_RNG_GET_INFO GetInfo;
  EFI_RNG_GET_RNG  GetRNG;
};

extern EFI_GUID gEfiRandomNumberProtocolGuid;

#endif
