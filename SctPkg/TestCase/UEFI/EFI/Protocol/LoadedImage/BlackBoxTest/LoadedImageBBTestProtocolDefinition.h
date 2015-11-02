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

  ProtocolDefinition.h

Abstract:

  Include for those protocols that will be used during the
    Loaded Image Protocol Test

--*/

#ifndef _LOADED_IMAGE_BBTEST_PROTOCOL_DEFINITION_H
#define _LOADED_IMAGE_BBTEST_PROTOCOL_DEFINITION_H

//
// Include
//
#include "Efi.h"

extern EFI_GUID gBlackBoxEfiLoadedImageProtocolGuid;

//
// LoadedImageTestNoInterfaceProtocol1
//
#define LOADED_IMAGE_TEST_NO_INTERFACE_PROTOCOL_1_GUID \
  {0x525399b6, 0x46f5, 0x45f1, 0x9b, 0x70, 0x17, 0x7b, 0x97, 0x94, 0x4d, 0xe2 };

extern EFI_GUID mLoadedImageTestNoInterfaceProtocol1Guid;

//
// LoadedImageTestNoInterfaceProtocol2
//
#define LOADED_IMAGE_TEST_NO_INTERFACE_PROTOCOL_2_GUID \
  {0xd6aa6fc3, 0x5718, 0x482a, 0xba, 0xa, 0xd7, 0x76, 0x7d, 0xf6, 0xbc, 0xed };

extern EFI_GUID mLoadedImageTestNoInterfaceProtocol2Guid;

//
// LoadedImageTestNoInterfaceProtocol3
//
#define LOADED_IMAGE_TEST_NO_INTERFACE_PROTOCOL_3_GUID \
  {0xb19f569d, 0xe882, 0x48c3, 0x89, 0xd4, 0x1c, 0x8d, 0x4, 0xdd, 0x5c, 0x9f };

extern EFI_GUID mLoadedImageTestNoInterfaceProtocol3Guid;

//
// LoadedImageTestNoInterfaceProtocol4
//
#define LOADED_IMAGE_TEST_NO_INTERFACE_PROTOCOL_4_GUID \
  {0x16e5a318, 0x5c1e, 0x41ef, 0xa5, 0x6, 0x1a, 0xa, 0xa9, 0xb2, 0x24, 0x96 };

extern EFI_GUID mLoadedImageTestNoInterfaceProtocol4Guid;

//
// LoadedImageTestNoInterfaceProtocol5
//
#define LOADED_IMAGE_TEST_NO_INTERFACE_PROTOCOL_5_GUID \
  {0x83b76f53, 0x9414, 0x4758, 0x83, 0xe9, 0xc9, 0x7e, 0x67, 0x0, 0xf0, 0xd4 };

extern EFI_GUID mLoadedImageTestNoInterfaceProtocol5Guid;

//
// LoadedImageTestNoInterfaceProtocol6
//
#define LOADED_IMAGE_TEST_NO_INTERFACE_PROTOCOL_6_GUID \
  {0xf04a896d, 0x50a7, 0x404c, 0x96, 0xb3, 0xdb, 0xae, 0x5c, 0x3a, 0xb7, 0x23 };

extern EFI_GUID mLoadedImageTestNoInterfaceProtocol6Guid;

#endif
