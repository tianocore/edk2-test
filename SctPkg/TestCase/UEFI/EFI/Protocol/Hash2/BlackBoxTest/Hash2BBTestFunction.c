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
                                                                
  Copyright 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

    Hash2BBTestFunction.c

Abstract:

    for EFI Driver Hash2 Protocol's Function Test

--*/

#include "Hash2BBTestMain.h"

extern EFI_GUID gHashAlgorithmGuids[6];

UINT8 Hash2OutSHA1[20]   = {0x97,0x00,0x93,0x67,0x8b,0x18,0x21,0x27,0xf6,0x0b,0xb5,0x1b,0x8a,0xf2,0xc9,0x4d,0x53,0x9e,0xca,0x3a};
UINT8 Hash2OutSHA224[28] = {0xfd,0x66,0x39,0xaf,0x1c,0xc4,0x57,0xb7,0x21,0x48,0xd7,0x8e,0x90,0xdf,0x45,0xdf,\
	                        0x4d,0x34,0x4c,0xa3,0xb6,0x6f,0xa4,0x45,0x98,0x14,0x8c,0xe4};
UINT8 Hash2OutSHA256[32] = {0xe9,0xc0,0xf8,0xb5,0x75,0xcb,0xfc,0xb4,0x2a,0xb3,0xb7,0x8e,0xcc,0x87,0xef,0xa3,\
	                        0xb0,0x11,0xd9,0xa5,0xd1,0x0b,0x09,0xfa,0x4e,0x96,0xf2,0x40,0xbf,0x6a,0x82,0xf5};
UINT8 Hash2OutSHA384[48] = {0x39,0xe0,0xcc,0x1b,0x02,0xb8,0xc0,0x82,0xb6,0x46,0x43,0xcd,0xca,0xe0,0xe6,0x18,\
	                        0x0e,0x46,0x0e,0x1f,0x71,0x78,0x24,0xc7,0x8b,0x17,0xf9,0x46,0xc9,0x86,0x4c,0x90,\
	                        0xc0,0x4c,0x55,0x06,0x7b,0x23,0x1e,0x69,0xb0,0xad,0x5b,0xd1,0x9d,0x12,0xa0,0x65};
UINT8 Hash2OutSHA512[64] = {0x56,0x93,0x50,0x08,0x5b,0x22,0x3b,0xa8,0x54,0xdf,0xc5,0xd6,0x07,0x64,0x3c,0xeb,\
	                        0x85,0xe4,0x60,0x7e,0x46,0xe5,0xa9,0xad,0x36,0x96,0xf8,0x98,0xe2,0x9d,0x8a,0x3f,\
	                        0xe2,0x26,0x10,0x95,0x61,0x67,0xce,0xfb,0x7e,0x2b,0xa7,0x69,0xe7,0x40,0xf9,0x4b,\
	                        0x31,0xe4,0xe3,0xc5,0x21,0x95,0xba,0x65,0xe6,0x4b,0xa4,0x0d,0x82,0x34,0x35,0x91};
UINT8 Hash2OutMD5[16]    = {0x88,0x27,0xa4,0x11,0x22,0xa5,0x02,0x8b,0x98,0x08,0xc7,0xbf,0x84,0xb9,0xfc,0xf6};

UINT8 *Hash2OutStd[6]={
Hash2OutSHA1,
Hash2OutSHA224,
Hash2OutSHA256,
Hash2OutSHA384,
Hash2OutSHA512,
Hash2OutMD5
};

UINTN Length[6] = {20, 28, 32, 48, 64, 16};

EFI_STATUS
BBTestGetHashSizeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HASH2_SERVICE_BINDING_PROTOCOL    *Hash2SB;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_HANDLE                            ChildHandle = NULL;
  EFI_HASH2_PROTOCOL                    *Hash2 = NULL;
  UINTN                                 HashSize;
  UINT8                                 Index;

  Hash2SB = (EFI_HASH2_SERVICE_BINDING_PROTOCOL*)ClientInterface;
  if (Hash2SB == NULL)
  	return EFI_UNSUPPORTED;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = Hash2ServiceBindingCreateChild(Hash2SB, &ChildHandle, &Hash2);

  for (Index = 0; Index < 6; Index++) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
    Status = Hash2->GetHashSize (Hash2, &gHashAlgorithmGuids[Index], &HashSize);
	if (Status == EFI_SUCCESS) {
	  if (HashSize != Length[Index])
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      if (Status != EFI_UNSUPPORTED) 
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHash2BBTestFunctionAssertionGuid001,
                   L"HASH2_PROTOCOL.GetHashSize - GetHashSize() returns EFI_UNSUPPORTED or EFI_SUCCESS and HashSize match the HashAlgorithm.",
                   L"%a:%d: Status - %r, Index - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }

  Status = Hash2ServiceBindingDestoryChild(Hash2SB, ChildHandle);   

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestHashFunctionTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HASH2_SERVICE_BINDING_PROTOCOL    *Hash2SB;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_HANDLE                            ChildHandle = NULL;
  EFI_HASH2_PROTOCOL                    *Hash2 = NULL;
  UINTN                                 HashSize;
  UINT8                                 Index;

  CHAR8                                 Message[] = "ABCDEF";
  UINTN                                 MessageSize = 6;
  UINT8                                 Hash2Out[64];

  Hash2SB = (EFI_HASH2_SERVICE_BINDING_PROTOCOL*)ClientInterface;
  if (Hash2SB == NULL)
  	return EFI_UNSUPPORTED;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = Hash2ServiceBindingCreateChild(Hash2SB, &ChildHandle, &Hash2);

  for (Index = 0; Index < 6; Index++) {
  	SctZeroMem(Hash2Out, 64);
    Status = Hash2->GetHashSize (Hash2, &gHashAlgorithmGuids[Index], &HashSize);
	if (Status == EFI_SUCCESS) {
      Status = Hash2->Hash (Hash2, &gHashAlgorithmGuids[Index], Message, MessageSize, Hash2Out);
      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if (0 != SctCompareMem(Hash2Out, Hash2OutStd[Index], Length[Index]) )
          AssertionType = EFI_TEST_ASSERTION_FAILED;
	  }
	  else
        AssertionType = EFI_TEST_ASSERTION_FAILED; 

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gHash2BBTestFunctionAssertionGuid002,
                     L"HASH2_PROTOCOL.Hash - Hash() returns EFI_SUCCESS with the correct Hash Output.",
                     L"%a:%d: Status - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
    }
  }

  Status = Hash2ServiceBindingDestoryChild(Hash2SB, ChildHandle); 

  return EFI_SUCCESS;  
}

EFI_STATUS
BBTestHashMultiBlocksFunctionTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1, Status2, Status3, Status4, Status5;
  EFI_HASH2_SERVICE_BINDING_PROTOCOL    *Hash2SB;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_HANDLE                            ChildHandle = NULL;
  EFI_HASH2_PROTOCOL                    *Hash2 = NULL;
  UINTN                                 HashSize;
  UINT8                                 Index;

  CHAR8                                 Message1[] = "ABC";
  CHAR8                                 Message2[] = "DEF";
  UINTN                                 MessageSize = 3;
  UINT8                                 Hash2Out[64];

  Hash2SB = (EFI_HASH2_SERVICE_BINDING_PROTOCOL*)ClientInterface;
  if (Hash2SB == NULL)
  	return EFI_UNSUPPORTED;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = Hash2ServiceBindingCreateChild(Hash2SB, &ChildHandle, &Hash2);

  for (Index = 0; Index < 6; Index++) {
  	SctZeroMem(Hash2Out, 64);
    Status = Hash2->GetHashSize (Hash2, &gHashAlgorithmGuids[Index], &HashSize);
	if (Status == EFI_SUCCESS) {
      Status1 = Hash2->HashInit (Hash2, &gHashAlgorithmGuids[Index]);
	  Status2 = Hash2->HashInit (Hash2, &gHashAlgorithmGuids[Index]);
	  
      Status3 = Hash2->HashUpdate (Hash2, Message1, MessageSize);
	  Status4 = Hash2->HashUpdate (Hash2, Message2, MessageSize);
	  Status5 = Hash2->HashFinal (Hash2, Hash2Out);

      
      if ((Status1 == EFI_SUCCESS) && (Status2 == EFI_ALREADY_STARTED) && (Status3 == EFI_SUCCESS) && (Status4 == EFI_SUCCESS) && (Status5 == EFI_SUCCESS)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if (0 != SctCompareMem(Hash2Out, Hash2OutStd[Index], Length[Index]) )
          AssertionType = EFI_TEST_ASSERTION_FAILED;
	  }
	  else
        AssertionType = EFI_TEST_ASSERTION_FAILED; 

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gHash2BBTestFunctionAssertionGuid003,
                     L"HASH2_PROTOCOL.Hash - HashInit()/HashUpdate()/HashFinal() returns EFI_SUCCESS with the correct Hash Output.",
                     L"%a:%d: Status1 - %r, Status2 - %r, Status3 - %r, Status4 - %r, Status5 - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1, Status2, Status3, Status4, Status5,
                     Index
                     );
    }
  }

  Status = Hash2ServiceBindingDestoryChild(Hash2SB, ChildHandle);

  return EFI_SUCCESS;  
}  