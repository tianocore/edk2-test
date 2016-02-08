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

  RegularExpressionProtocol.h

Abstract:

  EFI Regular Expression Protocol

--*/

#ifndef _REGEX_PROTOCOL_H_
#define _REGEX_PROTOCOL_H_

//
// Global ID for the Random Number Protocol
//
#define EFI_REGULAR_EXPRESSION_PROTOCOL_GUID    \
  { 0xB3F79D9A, 0x436C, 0xDC11, 0xB0, 0x52, 0xCD, 0x85,0xDF, 0x52, 0x4C, 0xE6 }


typedef struct _EFI_REGULAR_EXPRESSION_PROTOCOL EFI_REGULAR_EXPRESSION_PROTOCOL;;

typedef EFI_GUID EFI_REGEX_SYNTAX_TYPE;

typedef struct {
 CONST CHAR16 *CapturePtr;
 UINTN Length;
} EFI_REGEX_CAPTURE;

typedef
EFI_STATUS
(EFIAPI *EFI_REGULAR_EXPRESSION_GET_INFO) (
  IN     EFI_REGULAR_EXPRESSION_PROTOCOL *This,
  IN OUT UINTN                           *RegExSyntaxTypeListSize,
  OUT    EFI_REGEX_SYNTAX_TYPE           *RegExSyntaxTypeList
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REGULAR_EXPRESSION_MATCH) (
  IN  EFI_REGULAR_EXPRESSION_PROTOCOL *This,
  IN  CHAR16                          *String,
  IN  CHAR16                          *Pattern,
  IN  EFI_REGEX_SYNTAX_TYPE           *RegExSyntaxTypeList, OPTIONAL
  OUT BOOLEAN                         *Result,
  OUT EFI_REGEX_CAPTURE               **Captures, OPTIONAL
  OUT UINTN                           *CapturesCount
  );

//
// Interface structure for the Regular Expression Protocol
//
struct _EFI_REGULAR_EXPRESSION_PROTOCOL {
  EFI_REGULAR_EXPRESSION_MATCH     MatchString;
  EFI_REGULAR_EXPRESSION_GET_INFO  GetInfo;
} ;

extern EFI_GUID gBlackBoxEfiRegularExpressionProtocolGuid;

#endif
