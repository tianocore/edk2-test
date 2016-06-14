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

  Pkcs7verify.h

Abstract:

  PKCS7 Verify Protocol 

--*/


#ifndef __PKCS7_VERIFY_PROTOCOL_H__
#define __PKCS7_VERIFY_PROTOCOL_H__


#define EFI_PKCS7_VERIFY_PROTOCOL_GUID \
  { \
    0x47889fb2, 0xd671, 0x4fab, { 0xa0, 0xca, 0xdf, 0xe, 0x44,\ 0xdf, 0x70, 0xd6 } \
  }

//***********************************************************************
// Signature Database
//***********************************************************************
///
/// The format of a signature database.
///
#pragma pack(1)

typedef struct {
  ///
  /// An identifier which identifies the agent which added the signature to the list.
  ///
  EFI_GUID          SignatureOwner;
  ///
  /// The format of the signature is defined by the SignatureType.
  ///
  UINT8             SignatureData[1];
} EFI_SIGNATURE_DATA;

typedef struct {
  ///
  /// Type of the signature. GUID signature types are defined in below.
  ///
  EFI_GUID            SignatureType;
  ///
  /// Total size of the signature list, including this header.
  ///
  UINT32              SignatureListSize;
  ///
  /// Size of the signature header which precedes the array of signatures.
  ///
  UINT32              SignatureHeaderSize;
  ///
  /// Size of each signature.
  ///
  UINT32              SignatureSize;
  ///
  /// Header before the array of signatures. The format of this header is specified
  /// by the SignatureType.
  /// UINT8           SignatureHeader[SignatureHeaderSize];
  ///
  /// An array of signatures. Each signature is SignatureSize bytes in length.
  /// EFI_SIGNATURE_DATA Signatures[][SignatureSize];
  ///
} EFI_SIGNATURE_LIST;
#pragma pack()

typedef struct _EFI_PKCS7_VERIFY_PROTOCOL EFI_PKCS7_VERIFY_PROTOCOL;

#define OPTIONAL

/**
  Processes a buffer containing binary DER-encoded PKCS7 signature.
  The signed data content may be embedded within the buffer or separated. Funtion
  verifies the signature of the content is valid and signing certificate was not
  revoked and is contained within a list of trusted signers.

  @param[in]     This                 Pointer to EFI_PKCS7_VERIFY_PROTOCOL instance.
  @param[in]     SignedData           Points to buffer containing ASN.1 DER-encoded PKCS7
                                      signature.
  @param[in]     SignedDataSize       The size of SignedData buffer in bytes.
  @param[in]     InData               In case of detached signature, InData points to
                                      buffer containing the raw message data previously
                                      signed and to be verified by function. In case of
                                      SignedData containing embedded data, InData must be
                                      NULL.
  @param[in]     InDataSize           When InData is used, the size of InData buffer in
                                      bytes. When InData is NULL. This parameter must be
                                      0.
  @param[in]     AllowedDb            Pointer to a list of pointers to EFI_SIGNATURE_LIST
                                      structures. The list is terminated by a null
                                      pointer. The EFI_SIGNATURE_LIST structures contain
                                      lists of X.509 certificates of approved signers.
                                      Function recognizes signer certificates of type
                                      EFI_CERT_X509_GUID. Any hash certificate in AllowedDb
                                      list is ignored by this function. Function returns
                                      success if signer of the buffer is within this list
                                      (and not within RevokedDb). This parameter is
                                      required.
  @param[in]     RevokedDb            Optional pointer to a list of pointers to
                                      EFI_SIGNATURE_LIST structures. The list is terminated
                                      by a null pointer. List of X.509 certificates of
                                      revoked signers and revoked file hashes. Except as
                                      noted in description of TimeStampDb signature
                                      verification will always fail if the signer of the
                                      file or the hash of the data component of the buffer
                                      is in RevokedDb list. This list is optional and
                                      caller may pass Null or pointer to NULL if not
                                      required.
  @param[in]     TimeStampDb          Optional pointer to a list of pointers to
                                      EFI_SIGNATURE_LIST structures. The list is terminated
                                      by a null pointer. This parameter can be used to pass
                                      a list of X.509 certificates of trusted time stamp
                                      signers. This list is optional and caller must pass
                                      Null or pointer to NULL if not required.
  @param[out]    Content              On input, points to an optional caller-allocated
                                      buffer into which the function will copy the content
                                      portion of the file after verification succeeds.
                                      This parameter is optional and if NULL, no copy of
                                      content from file is performed.
  @param[in,out] ContentSize          On input, points to the size in bytes of the optional
                                      buffer Content previously allocated by caller. On
                                      output, if the verification succeeds, the value
                                      referenced by ContentSize will contain the actual
                                      size of the content from signed file. If ContentSize
                                      indicates the caller-allocated buffer is too small
                                      to contain content, an error is returned, and
                                      ContentSize will be updated with the required size.
                                      This parameter must be 0 if Content is Null.

  @retval EFI_SUCCESS                 Content signature was verified against hash of
                                      content, the signer's certificate was not found in
                                      RevokedDb, and was found in AllowedDb or if in signer
                                      is found in both AllowedDb and RevokedDb, the
                                      signing was allowed by reference to TimeStampDb as
                                      described above, and no hash matching content hash
                                      was found in RevokedDb.
  @retval EFI_SECURITY_VIOLATION      The SignedData buffer was correctly formatted but
                                      signer was in RevokedDb or not in AllowedDb. Also
                                      returned if matching content hash found in RevokedDb.
  @retval EFI_COMPROMISED_DATA        Calculated hash differs from signed hash.
  @retval EFI_INVALID_PARAMETER       SignedData is NULL or SignedDataSize is zero.
                                      AllowedDb is NULL.
  @retval EFI_INVALID_PARAMETER       Content is not NULL and ContentSize is NULL.
  @retval EFI_ABORTED                 Unsupported or invalid format in TimeStampDb,
                                      RevokedDb or AllowedDb list contents was detected.
  @retval EFI_NOT_FOUND               Content not found because InData is NULL and no
                                      content embedded in SignedData.
  @retval EFI_UNSUPPORTED             The SignedData buffer was not correctly formatted
                                      for processing by the function.
  @retval EFI_UNSUPPORTED             Signed data embedded in SignedData but InData is not
                                      NULL.
  @retval EFI_BUFFER_TOO_SMALL        The size of buffer indicated by ContentSize is too
                                      small to hold the content. ContentSize updated to
                                      required size.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_PKCS7_VERIFY_BUFFER) (
  IN EFI_PKCS7_VERIFY_PROTOCOL    *This,
  IN VOID                         *SignedData,
  IN UINTN                        SignedDataSize,
  IN VOID                         *InData          OPTIONAL,
  IN UINTN                        InDataSize,
  IN EFI_SIGNATURE_LIST           **AllowedDb,
  IN EFI_SIGNATURE_LIST           **RevokedDb      OPTIONAL,
  IN EFI_SIGNATURE_LIST           **TimeStampDb    OPTIONAL,
  OUT VOID                        *Content         OPTIONAL,
  IN OUT UINTN                    *ContentSize
  );

/**
  Processes a buffer containing binary DER-encoded detached PKCS7 signature.
  The hash of the signed data content is calculated and passed by the caller. Function
  verifies the signature of the content is valid and signing certificate was not revoked
  and is contained within a list of trusted signers.

  @param[in]     This                 Pointer to EFI_PKCS7_VERIFY_PROTOCOL instance.
  @param[in]     Signature            Points to buffer containing ASN.1 DER-encoded PKCS
                                      detached signature.
  @param[in]     SignatureSize        The size of Signature buffer in bytes.
  @param[in]     InHash               InHash points to buffer containing the caller
                                      calculated hash of the data. The parameter may not
                                      be NULL.
  @param[in]     InHashSize           The size in bytes of InHash buffer.
  @param[in]     AllowedDb            Pointer to a list of pointers to EFI_SIGNATURE_LIST
                                      structures. The list is terminated by a null
                                      pointer. The EFI_SIGNATURE_LIST structures contain
                                      lists of X.509 certificates of approved signers.
                                      Function recognizes signer certificates of type
                                      EFI_CERT_X509_GUID. Any hash certificate in AllowedDb
                                      list is ignored by this function. Function returns
                                      success if signer of the buffer is within this list
                                      (and not within RevokedDb). This parameter is
                                      required.
  @param[in]     RevokedDb            Optional pointer to a list of pointers to
                                      EFI_SIGNATURE_LIST structures. The list is terminated
                                      by a null pointer. List of X.509 certificates of
                                      revoked signers and revoked file hashes. Signature
                                      verification will always fail if the signer of the
                                      file or the hash of the data component of the buffer
                                      is in RevokedDb list. This parameter is optional
                                      and caller may pass Null if not required.
  @param[in]     TimeStampDb          Optional pointer to a list of pointers to
                                      EFI_SIGNATURE_LIST structures. The list is terminated
                                      by a null pointer. This parameter can be used to pass
                                      a list of X.509 certificates of trusted time stamp
                                      counter-signers.

  @retval EFI_SUCCESS                 Signed hash was verified against caller-provided
                                      hash of content, the signer's certificate was not
                                      found in RevokedDb, and was found in AllowedDb or
                                      if in signer is found in both AllowedDb and
                                      RevokedDb, the signing was allowed by reference to
                                      TimeStampDb as described above, and no hash matching
                                      content hash was found in RevokedDb.
  @retval EFI_SECURITY_VIOLATION      The SignedData buffer was correctly formatted but
                                      signer was in RevokedDb or not in AllowedDb. Also
                                      returned if matching content hash found in RevokedDb.
  @retval EFI_COMPROMISED_DATA        Caller provided hash differs from signed hash. Or,
                                      caller and encrypted hash are different sizes.
  @retval EFI_INVALID_PARAMETER       Signature is NULL or SignatureSize is zero. InHash
                                      is NULL or InHashSize is zero. AllowedDb is NULL.
  @retval EFI_ABORTED                 Unsupported or invalid format in TimeStampDb,
                                      RevokedDb or AllowedDb list contents was detected.
  @retval EFI_UNSUPPORTED             The Signature buffer was not correctly formatted
                                      for processing by the function.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_PKCS7_VERIFY_SIGNATURE) (
  IN EFI_PKCS7_VERIFY_PROTOCOL   *This,
  IN VOID                        *Signature,
  IN UINTN                       SignatureSize,
  IN VOID                        *InHash,
  IN UINTN                       InHashSize,
  IN EFI_SIGNATURE_LIST          **AllowedDb,
  IN EFI_SIGNATURE_LIST          **RevokedDb       OPTIONAL,
  IN EFI_SIGNATURE_LIST          **TimeStampDb     OPTIONAL
  );

///
/// The EFI_PKCS7_VERIFY_PROTOCOL is used to verify data signed using PKCS7
/// structure. The PKCS7 data to be verified must be ASN.1 (DER) encoded.
/// SHA256 must be supported as digest algorithm with RSA digest encryption.
/// Support of other hash algorithms is optional.
///

typedef struct _EFI_PKCS7_VERIFY_PROTOCOL {
EFI_PKCS7_VERIFY_BUFFER VerifyBuffer;
EFI_PKCS7_VERIFY_SIGNATURE VerifySignature;
} EFI_PKCS7_VERIFY_PROTOCOL;


extern EFI_GUID gBlackBoxEfiPkcs7VerifyProtocolGuid;


extern EFI_GUID   gBlackBoxEfiCertSha256Guid;
extern EFI_GUID   gBlackBoxEfiCertRsa2048Guid;
extern EFI_GUID   gBlackBoxEfiCertRsa2048Sha256Guid;
extern EFI_GUID   gBlackBoxEfiCertSha1Guid;
extern EFI_GUID   gBlackBoxEfiCertRsa2048Sha1Guid;
extern EFI_GUID   gBlackBoxEfiCertX509Guid;
extern EFI_GUID   gBlackBoxEfiCertX509Sha256Guid;


#endif