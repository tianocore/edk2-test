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

  Hash2.h

Abstract:

  Hash 2 Protocol 

--*/


#ifndef __HASH2_PROTOCOL_H__
#define __HASH2_PROTOCOL_H__

#define EFI_HASH2_SERVICE_BINDING_PROTOCOL_GUID \
  { \
    0xda836f8d, 0x217f, 0x4ca0, { 0x99, 0xc2, 0x1c, 0xa4, 0xe1, 0x60, 0x77, 0xea } \
  }

#define EFI_HASH2_PROTOCOL_GUID \
  { \
    0x55b1d734, 0xc5e1, 0x49db, { 0x96, 0x47, 0xb1, 0x6a, 0xfb, 0xe, 0x30, 0x5b } \
  }

  
  
#define EFI_HASH_ALGORITHM_SHA1_GUID \
  { \
    0x2ae9d80f, 0x3fb2, 0x4095, {0xb7, 0xb1, 0xe9, 0x31, 0x57, 0xb9, 0x46, 0xb6 } \
  }

#define EFI_HASH_ALGORITHM_SHA224_GUID \
  { \
    0x8df01a06, 0x9bd5, 0x4bf7, {0xb0, 0x21, 0xdb, 0x4f, 0xd9, 0xcc, 0xf4, 0x5b } \
  } 

#define EFI_HASH_ALGORITHM_SHA256_GUID \
  { \
    0x51aa59de, 0xfdf2, 0x4ea3, {0xbc, 0x63, 0x87, 0x5f, 0xb7, 0x84, 0x2e, 0xe9 } \
  } 

#define EFI_HASH_ALGORITHM_SHA384_GUID \
  { \
    0xefa96432, 0xde33, 0x4dd2, {0xae, 0xe6, 0x32, 0x8c, 0x33, 0xdf, 0x77, 0x7a } \
  } 

#define EFI_HASH_ALGORITHM_SHA512_GUID \
  { \
    0xcaa4381e, 0x750c, 0x4770, {0xb8, 0x70, 0x7a, 0x23, 0xb4, 0xe4, 0x21, 0x30 } \
  }

#define EFI_HASH_ALGORTIHM_MD5_GUID \
  { \
    0xaf7c79c, 0x65b5, 0x4319, {0xb0, 0xae, 0x44, 0xec, 0x48, 0x4e, 0x4a, 0xd7 } \
  }

#define EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID \
  { \
    0x24c5dc2f, 0x53e2, 0x40ca, {0x9e, 0xd6, 0xa5, 0xd9, 0xa4, 0x9f, 0x46, 0x3b } \
  }

#define EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID \
  { \
    0x8628752a, 0x6cb7, 0x4814, {0x96, 0xfc, 0x24, 0xa8, 0x15, 0xac, 0x22, 0x26 } \
  }


//
// NOTE:
// Algorithms EFI_HASH_ALGORITHM_SHA1_NOPAD and
// EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID are not compatible with
// EFI_HASH2_PROTOCOL and will return EFI_UNSUPPORTED if used with any
// EFI_HASH2_PROTOCOL function.
//

//
// Note: SHA-1 and MD5 are included for backwards compatibility.
// New driver implementations are encouraged to consider stronger algorithms.
//

typedef struct _EFI_HASH2_PROTOCOL EFI_HASH2_PROTOCOL;

typedef UINT8  EFI_MD5_HASH2[16];
typedef UINT8  EFI_SHA1_HASH2[20];
typedef UINT8  EFI_SHA224_HASH2[28];
typedef UINT8  EFI_SHA256_HASH2[32];
typedef UINT8  EFI_SHA384_HASH2[48];
typedef UINT8  EFI_SHA512_HASH2[64];

typedef union {
  EFI_MD5_HASH2     Md5Hash;
  EFI_SHA1_HASH2    Sha1Hash;
  EFI_SHA224_HASH2  Sha224Hash;
  EFI_SHA256_HASH2  Sha256Hash;
  EFI_SHA384_HASH2  Sha384Hash;
  EFI_SHA512_HASH2  Sha512Hash;
} EFI_HASH2_OUTPUT;

/**
  Returns the size of the hash which results from a specific algorithm.

  @param[in]  This                  Points to this instance of EFI_HASH2_PROTOCOL.
  @param[in]  HashAlgorithm         Points to the EFI_GUID which identifies the algorithm to use.
  @param[out] HashSize              Holds the returned size of the algorithm's hash.

  @retval EFI_SUCCESS           Hash size returned successfully.
  @retval EFI_INVALID_PARAMETER This or HashSize is NULL.
  @retval EFI_UNSUPPORTED       The algorithm specified by HashAlgorithm is not supported by this driver
                                or HashAlgorithm is null.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_HASH2_GET_HASH_SIZE)(
  IN  CONST EFI_HASH2_PROTOCOL     *This,
  IN  CONST EFI_GUID               *HashAlgorithm,
  OUT UINTN                        *HashSize
  );

/**
  Creates a hash for the specified message text. The hash is not extendable.
  The output is final with any algorithm-required padding added by the function.

  @param[in]  This          Points to this instance of EFI_HASH2_PROTOCOL.
  @param[in]  HashAlgorithm Points to the EFI_GUID which identifies the algorithm to use.
  @param[in]  Message       Points to the start of the message.
  @param[in]  MessageSize   The size of Message, in bytes.
  @param[in,out]  Hash      On input, points to a caller-allocated buffer of the size
                              returned by GetHashSize() for the specified HashAlgorithm.
                            On output, the buffer holds the resulting hash computed from the message.

  @retval EFI_SUCCESS           Hash returned successfully.
  @retval EFI_INVALID_PARAMETER This or Hash is NULL.
  @retval EFI_UNSUPPORTED       The algorithm specified by HashAlgorithm is not supported by this driver
                                or HashAlgorithm is Null.
  @retval EFI_OUT_OF_RESOURCES  Some resource required by the function is not available
                                or MessageSize is greater than platform maximum.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_HASH2_HASH)(
  IN CONST EFI_HASH2_PROTOCOL      *This,
  IN CONST EFI_GUID                *HashAlgorithm,
  IN CONST UINT8                   *Message,
  IN UINTN                         MessageSize,
  IN OUT EFI_HASH2_OUTPUT          *Hash
  );

/**
  This function must be called to initialize a digest calculation to be subsequently performed using the
  EFI_HASH2_PROTOCOL functions HashUpdate() and HashFinal().

  @param[in]  This          Points to this instance of EFI_HASH2_PROTOCOL.
  @param[in]  HashAlgorithm Points to the EFI_GUID which identifies the algorithm to use.

  @retval EFI_SUCCESS           Initialized successfully.
  @retval EFI_INVALID_PARAMETER This is NULL.
  @retval EFI_UNSUPPORTED       The algorithm specified by HashAlgorithm is not supported by this driver
                                or HashAlgorithm is Null.
  @retval EFI_OUT_OF_RESOURCES  Process failed due to lack of required resource.
  @retval EFI_ALREADY_STARTED   This function is called when the operation in progress is still in processing Hash(),
                                or HashInit() is already called before and not terminated by HashFinal() yet on the same instance.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_HASH2_HASH_INIT)(
  IN CONST EFI_HASH2_PROTOCOL      *This,
  IN CONST EFI_GUID                *HashAlgorithm
  );

/**
  Updates the hash of a computation in progress by adding a message text.

  @param[in]  This          Points to this instance of EFI_HASH2_PROTOCOL.
  @param[in]  Message       Points to the start of the message.
  @param[in]  MessageSize   The size of Message, in bytes.

  @retval EFI_SUCCESS           Digest in progress updated successfully.
  @retval EFI_INVALID_PARAMETER This or Hash is NULL.
  @retval EFI_OUT_OF_RESOURCES  Some resource required by the function is not available
                                or MessageSize is greater than platform maximum.
  @retval EFI_NOT_READY         This call was not preceded by a valid call to HashInit(),
                                or the operation in progress was terminated by a call to Hash() or HashFinal() on the same instance.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_HASH2_HASH_UPDATE)(
  IN CONST EFI_HASH2_PROTOCOL      *This,
  IN CONST UINT8                   *Message,
  IN UINTN                         MessageSize
  );

/**
  Finalizes a hash operation in progress and returns calculation result.
  The output is final with any necessary padding added by the function.
  The hash may not be further updated or extended after HashFinal().

  @param[in]  This          Points to this instance of EFI_HASH2_PROTOCOL.
  @param[in,out]  Hash      On input, points to a caller-allocated buffer of the size
                              returned by GetHashSize() for the specified HashAlgorithm specified in preceding HashInit().
                            On output, the buffer holds the resulting hash computed from the message.

  @retval EFI_SUCCESS           Hash returned successfully.
  @retval EFI_INVALID_PARAMETER This or Hash is NULL.
  @retval EFI_NOT_READY         This call was not preceded by a valid call to HashInit() and at least one call to HashUpdate(),
                                or the operation in progress was canceled by a call to Hash() on the same instance.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_HASH2_HASH_FINAL)(
  IN CONST EFI_HASH2_PROTOCOL      *This,
  IN OUT EFI_HASH2_OUTPUT          *Hash
  );

///
/// This protocol describes hashing functions for which the algorithm-required message padding and
/// finalization are performed by the supporting driver.
///
struct _EFI_HASH2_PROTOCOL {
  EFI_HASH2_GET_HASH_SIZE          GetHashSize;
  EFI_HASH2_HASH                   Hash;
  EFI_HASH2_HASH_INIT              HashInit;
  EFI_HASH2_HASH_UPDATE            HashUpdate;
  EFI_HASH2_HASH_FINAL             HashFinal;
};




extern EFI_GUID gBlackBoxEfiHash2ServiceBindingProtocolGuid;
extern EFI_GUID gBlackBoxEfiHash2ProtocolGuid;

extern EFI_GUID gBlackBoxEfiHash2AlgorithmSha1Guid;
extern EFI_GUID gBlackBoxEfiHash2AlgorithmSha224Guid;
extern EFI_GUID gBlackBoxEfiHash2AlgorithmSha256Guid;
extern EFI_GUID gBlackBoxEfiHash2AlgorithmSha384Guid;
extern EFI_GUID gBlackBoxEfiHash2AlgorithmSha512Guid;
extern EFI_GUID gBlackBoxEfiHash2AlgorithmMD5Guid;
extern EFI_GUID gBlackBoxEfiHash2AlgorithmSha1NoPadGuid;
extern EFI_GUID gBlackBoxEfiHash2AlgorithmSha256NoPadGuid;

#endif